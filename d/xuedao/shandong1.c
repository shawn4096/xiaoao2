// shandong1.c
// Modified by Java Apr.27 1998
#include <ansi.h>
inherit ROOM;
int do_kanshou(string arg);
int do_attack(object ob);
int give_reward(object ob);
int do_wanzi(object me);

#include "/d/xuedao/npc/attacker.h"

void create()
{
        set("short","山洞");
        set("long",@LONG
野外一个神秘巨大山洞，阵阵幽香由洞内传来，偶尔带出些血腥气
因为香气的吸引，不少动物在山洞外逡巡往返。洞中央摆放了一个巨大
的铜鼎(tongding ),一旁的小喇嘛正在往里添火。香气正是从这个鼎内
飘出来，东侧摆放了不少木头架子，架子上摆满了各种新鲜的血肉，血
刀门弟子不断将打来的新鲜血肉送到这儿来，练成五肉和五露等秘药。
LONG );
        set("exits",([
                "out" : __DIR__"sroad8",
        ]));
        set("objects", ([
                __DIR__"npc/lianyao_lama" :1,
			__DIR__"obj/xueding" :1,
				"/kungfu/class/xuedao/miaoke" :1,
        ]));
		set("item_desc", ([
           "tongding" : "    这是由黄铜铸成的特殊铜鼎，重约二百多斤，鼎身纹有各种藏传佛教\n"+
                             "的吉祥图案。鼎内火势正旺，正是炼丹的紧要关头! 为了保护不备打扰\n"+
                             "必须在此警戒(jingjie)守候各种野兽或敌人的破坏偷袭。\n",
        ]));

        setup();
		//set("outdoors", "xuedao");
        replace_program(ROOM);
}
void init()
{
	add_action("do_kanshou","jingjie");
	add_action("do_lianwan","lianwan");

}

//血刀警戒任务
//xdjjjob
int do_kanshou(string arg)
{
	
       mapping fam;
       int exp;
       object me;
       object ob = this_player();
	   if (!arg||arg!="铜鼎")
	   {	
		   return notify_fail("你要警戒什么？\n");
	   }
	   if(!present("miao ke",  environment(ob) ) )
           return notify_fail("主事之人不在，你要警戒什么？\n");

       me = present("miao ke",  environment(ob) );
       fam = ob->query("family");
       exp = ob->query("combat_exp");

	   if (!ob->query_temp("xdjj/askmiaoke"))
	   {
		   return notify_fail("此处是血刀门要地，警戒铜鼎需要得到妙可的许可！\n");
	   }

       if(ob->is_busy()) return notify_fail("你现在正忙着呢。\n");

       message_vision(CYN"$N想在此协助妙可喇嘛血刀警戒炼药，担任警戒任务。\n"NOR,ob);

       if (!fam || fam["family_name"] !="血刀门")
             return notify_fail(GRN"妙可告诉你："+RANK_D->query_respect(this_player())+"与本派素无来往，我看还是不必劳您大驾了！\n"NOR);

       if (exp < 150000)
             return notify_fail("你的实战经验不足，还是先去打猎获得些经验值再说吧！\n");

       if (exp > 2500000)
             return notify_fail("你已经可以初步纵横江湖了，可以去找老祖做更重要的工作了，这些任务就交给你师弟来做吧！\n");

       if(ob->query("job_name") == "血刀警戒")
		{
            message_vision(CYN"妙可说道："+ob->query("name")+"，你刚做完血刀警戒任务，还是先去歇息片刻再来吧！\n"NOR,ob);
            return 1; 
		}
	   if(ob->query_condition("job_busy")){
            message_vision(CYN"妙可说道："+ob->query("name")+"，你正工作忙碌中，还是先去歇息片刻再来吧！\n"NOR,ob);
            return 1; 
       }

       if (ob->query_condition("xdjj_job"))
             return notify_fail("你正在为血刀门担任巡山警戒任务。\n");

        ob->set_temp("xdjj_job",1);
        ob->set_temp("apply/short", ({RED"血刀警戒"NOR+" "+ob->query("name")+"("+capitalize(ob->query("id"))+")"}));
        message_vision(CYN"妙可说道：好吧，"+ob->query("name")+"，你来的正是时候，我这儿正缺人手。\n"NOR,ob);
        message_vision(CYN"妙可说道：此铜鼎丹炉乃血刀门至宝，血刀武功崛起武林，全凭此炉功能。\n"
							+"最近我听说有武林正派人士正组织人来偷袭我派，"+ob->query("name")+"你一定要小心看护。\n"NOR,ob);
        call_out("give_reward",200+random(30),ob);
        ob->add_busy(1);
        ob->set("job_name", "血刀警戒");
		ob->apply_conditon("xdjj_job",20);
		ob->set_temp("xdjj_job",1);
        
        if(random(10) > 5)
		{
			ob->set_temp("xd/xdjj/second",1);
			call_out("do_attack",20+random(20),ob);
		}
		else call_out("do_attack",100+random(60),ob);
			
        return 1;   
}

int do_leave(object ob)
{
        object me;
        ob = this_player();
        me = present("miao ke",  environment(ob));

        if( ob->query_temp("xdjj_job")<1 )
            return notify_fail("你并没有在为血刀警戒。\n");

        ob->delete_temp("xdjj_job");
        if (!me) return notify_fail("你想趁妙可不在时偷懒？这可绝对不行。\n");
			me->add("job_time/血刀警戒",-1);
        if (me->query("job_time/血刀警戒") < 0) me->set("job_time/血刀警戒",0);
        ob->delete_temp("apply/short");
        ob->apply_condition("job_busy",16);//add by caiji@SJ
        // busy must > 15,because of a bug
        ob->apply_condition("xdjj_job",16);// add by caiji@SJ
        //busy must > 15,because of a bug
        message_vision(CYN"$N打算放弃这轮血刀警戒铜鼎的任务。\n"NOR,ob);
        message_vision(CYN"妙可说道：唉…，"+ob->query("name")+"，既然你干不了我也不勉强你，下次好好干吧！\n"NOR,ob);
        return 1;
}

int do_attack(object ob)
{
        mapping skills;
        string *sk;
        int exp,i,lv;
        object att;
        if(!ob || !ob->query_temp("xdjj_job")) return 1;
        
		if(!present("miao ke",environment(ob))) {
             tell_object(ob,"血刀警戒任务失败。\n");
			 ob->apply_condition("xdjj_job",8);
             ob->delete_temp("xdjj_job");
             return 1;
        }
        exp = ob->query("combat_exp");
        lv = ob->query("max_pot") - 100;
       //if( ob->query("combat_exp")<500000) lv-=20;
       // else if (ob->query("combat_exp") < 1000000) lv-=15;
       // else if (ob->query("combat_exp") < 1500000) lv-=10;
        
		if (ob->query("combat_exp")<800000)
		{
			lv=lv-30;
		}else if (ob->query("combat_exp")<1000000)
		{
			lv=lv-20;
		}
		else if (ob->query("combat_exp")<1500000)
		{
			lv=lv-10;
		}

        if(lv < 100) lv = 100;

		if (ob->query_temp("xd/xdjj/second")>0)
			i=i+20+random(10);
		att = new(__DIR__"npc/attacker");
		do_copy(ob);

        att->set("qi",(int)ob->query("qi"));
        att->set("max_qi", (int)ob->query("max_qi") );
        att->set("eff_qi", (int)ob->query("max_qi") );
        att->set("jing",(int)ob->query("jing"));
        att->set("eff_jing",(int)ob->query("max_jing"));
        att->set("neili",(int)ob->query("max_neili") );
        att->set("max_neili",(int)ob->query("max_neili") );
        att->set("jingli",(int)ob->query("jingli"));
        att->set("eff_jingli",(int)ob->query("eff_jingli"));
        att->set("combat_exp", exp);
		
		att->set("owner",ob->query("id"));
		att->set("long",att->query("long")+"\n这是专门尾随"+ob->query("name")+"而来的侠客！\n");
	  
		skills = att->query_skills();
        
		if (mapp(skills)){
             sk = keys(skills);
             for (i=0;i<sizeof(sk);i++)
             skills[sk[i]] = lv;
        }
		message_vision(HIY"\n忽听外面有人喊道，“师兄，找到淫贼们的巢穴了！”\n"NOR,ob);
		message_vision(HIC"	落~~~~\n"HIR"	花~~~~\n"HIY"	流~~~~\n"HIW"	水~~~~\n"NOR,ob);
        message_vision(HIR"\n"+ob->query("name")+"你这淫贼，纳命来！一名"+att->name()+"破门而入，对$N发起猛烈的攻击！\n\n"NOR,ob);
        att->move(environment(ob));
        att->kill_ob(ob);

        return 1;
}

int give_reward(object ob)
{
        int p,e,shen;
        object me,here;

        if (!ob) return 1;
        me = present("miao ke",  environment(ob));
        here=environment(ob);
		
		e = 100 + random(50)+ random(ob->query("combat_exp"))/10000;	
		//e = 200 + random(50)+ random(ob->query("combat_exp"))/10000;	

		ob->delete_temp("apply/short");
		//如果在规定时间内没做完job则不给奖励
		if(!ob->query_temp("xdjj_job")) return 1;
		
		else if((string)here->query("short") != "山洞")
		{
			ob->delete_temp("xdjj_job");
			ob->apply_condition("xdjj_job",2);
			tell_object(ob,CYN"血刀警戒时限已到，但是"+ob->query("name")+"擅离职守，任务失败了！\n"NOR);
			return 1;
        }
		else if(present("miao ke",  environment(ob)) 
			&& here->query("short") == "山洞")
			tell_object(ob,CYN"妙可说道，"+ob->query("name")+"你血刀警戒任务顺利完成！\n"NOR);
		else {    
			message_vision(CYN"妙可说道：好，时间到了！"+query("name")+"，你下去休息吧！\n"NOR,ob);
		}
	/*
		e = ob->add_exp_combat(e,"妙可","血刀警戒");
		
		shen=50+random(50);
		ob->add("shen",-shen);
		ob->add("job_time/血刀警戒",1);
		p = e/5 + random(e/10);
		
		ob->add("potential",p);
		*/
		TASKREWARD_D->get_reward(ob,"血刀警戒",-1,0,0,3 + random(2),0,0,0,"妙可");

		ob->delete_temp("xdjj");

		if ( (int)ob->query("potential", 1) > (int)ob->query("max_pot", 1))
			ob->add("potential" , ob->query("max_pot", 1));
		if (random(ob->query("job_time/血刀警戒"))>800 && random(ob->query("kar"))>26 && !ob->query("quest/xd/dichuan"))
		{
			
			message_vision(HIC"妙可对"+ob->query("name")+"竖起了大拇指，说道，“经过考验，老祖接受$N为大血刀核心弟子”\n"NOR,ob);
			ob->set("title","血刀门嫡传弟子");
			ob->set("quest/xd/dichuan",1);
		}
		if (ob->query("quest/xd/dichuan"))
		{
			ob->set("title","血刀门嫡传弟子");
		}
		
	//	tell_object(ob, GRN"你此次看守共得到"+CHINESE_D->chinese_number(e)+"点经验，"+CHINESE_D->chinese_number(p)+"点潜能,"+CHINESE_D->chinese_number(shen)+"点负神！\n"NOR);
	//	log_file("job/xdjingjie",sprintf("%8s%-10s血刀警戒获得了%3d点经验，%2d点潜能，现经验：%d。\n",
	//		ob->name(),"("+ob->query("id")+")",e,p, ob->query("combat_exp")), ob);
		remove_call_out("do_attack");
		ob->apply_condition("job_busy",2+random(2));
		ob->apply_condition("xdjj_job",4);
		ob->delete_temp("xdjj_job");
		ob->delete_temp("guard");
		ob->delete_temp("xd/xdjj");
		return 1;
}
int valid_leave(object me, string dir)
{
        
		if (dir == "out" && me->temp_temp("xdjj_job"))
        {
                message_vision(HIW"\n"+me->query("name")+"，你申请了这份工作不好好在这儿警戒，还想偷懒！\n"NOR, me);
                return notify_fail("你安心做好这份工作，这牵扯到血刀门嫡传弟子的身份！\n");
		}
      
        return ::valid_leave(me,dir);
}

int do_lianwan()
{
	object me;
	me=this_player();
	if (!me->query_temp("xd/lianwan/askke"))
	{
		return notify_fail("你无缘无故，来此作甚？难道是奸细？");
	}
	if (this_object()->query("lianwan"))
	{
		return notify_fail("现在铜鼎正在被"+this_object()->query("lianwan/name")+"使用！\n");
	}
	if (me->query_temp("lianwan_tick"))
	{
		return notify_fail("你非常忙碌，正在炼丸中。");
	}
	if (me->query_temp("xd/lianwan/start"))
	{
		return notify_fail("你已经开始炼丸中。");
	}

	this_object()->set("lianwan/name",me->query("name"));
	
	message_vision(YEL"$N走到铜鼎前，打开鼎盖，将五种血肉和新鲜鲜血混合在一起，然后默默祈祷一番，开始点火提炼起来！\n"NOR,me);
	me->start_busy(15);
	me->set_temp("xd/lianwan/start",1);
	//remove_call_out("do_wanzi");
	call_out("do_wanzi",1,me);
	return 1;
	
}

int do_wanzi(object me)
{
	int i,j,jobs; 
	object ob;
	if(!me) return 0;
	i=random(me->query_int());
//	j=20;

//	if(me->query("m-card-vip")) j =  18;
//	if(me->query("y-card-vip")) j =  15;
//	if(me->query("buyvip"))     j =  10;
	j=me->query_skill("medicine",1);
	
	jobs=(int)me->query("job_time/血刀打猎")+(int)me->query("quest/xd/lianwan/count");
	
   if(me->query_temp("lianwan_tick")<(15+random(10)))
   {  
	  me->add_temp("lianwan_tick",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你将鼓荡内力，将火烧的极其旺盛.\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n你鼎盖上冒出丝丝热气。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你一时心气浮躁，火势有些偏大，急忙将火势压了压！..\n"NOR);
			 me->add_temp("lianwan_tick",-2);
			break;
		case 3:
			tell_object(me,HIW"\n你集中精力，盯住铜鼎，香气开始弥漫.\n"NOR);
			me->add_temp("lianwan_tick",1);

			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎即将崩溃.\n"NOR);
			me->add_temp("lianwan_tick",-2);

			break;
		case 5:
			tell_object(me,MAG"\n你功力元转如意，血鼎之中竟然飘起来浓郁的香气.\n"NOR);
			me->add_temp("lianwan_tick",3);

			break;

		default:tell_object(me,YEL"\n你扇了扇火，血鼎滋滋作响，血肉开始血气翻腾.\n"NOR);
			break;

	  }      

	  tell_room(environment(me),HIC""+me->query("name")+"你集中精力盯住血鼎，神情极为专注...\n"NOR, ({}));

	  call_out("do_wanzi",3+random(3), me);

   } 
  else if (i>30
	  && random(j)>80
	  && random(jobs)>200
	  && random(me->query("kar"))>15
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIC"\n血鼎中此时血气蒸腾，香气浓郁之极，这一炉五肉五露看来是要成了。”\n"NOR,me); 
         message_vision(HIW"\n$N心中大喜，「哈哈哈」仰天大笑几声，说道：“开！”\n"NOR,me); 
		 if (random(10)>5)
		 {
			 ob=new("d/xuedao/obj/wulu_wan");			 
		 }else ob=new("d/xuedao/obj/wurou_wan");			 
         if (ob)
		{
			 message_vision(HBYEL+HIW"\n$N经过不断实践，终于练出一炉"+ob->query("name")+"丸！”\n"NOR,me); 

			 ob->set("owner",me->query("id"));
			 ob->move(me);
		}
		 me->delete_temp("lianwan_tick");
		 me->delete_temp("xd/lianwan");

		 me->add("quest/xd/lianwan/count",1);

		 me->start_busy(1);
     }
	 else {
	     message_vision(HIB"\n忽然一股焦糊味道传来，原来是方才一不小心，火势过大，将这一炉丸子全部炼废了。”\n"NOR,me); 
		 message_vision(HIY"\n失败！你极其沮丧！\n"NOR,me); 
  
		 me->start_busy(5);
		 me->delete_temp("lianwan_tick");
		 me->add("quest/xd/lianwan/fail",1);
		 me->set("quest/xd/lianwan/time",time());

		 me->delete_temp("xd");
   }
   this_object()->delete("lianwan");
   return 1;
}