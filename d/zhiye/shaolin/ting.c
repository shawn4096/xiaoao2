// Room: /d/shaolin/ting.c
// Date: bren

#include <room.h>
#include <ansi.h>
inherit ROOM;
int do_diao(object me,object wei);
int do_check(object me);
int thinking(object me);


void create()
{
	set("short", HIG"迎客亭"NOR);
	set("long", 
"苍松掩映之中，一座石亭赫然眼中。只见亭上匾额中龙飞凤舞的题着『"HIY"迎客亭"NOR"』\n"
"三个大字。凡江湖人士，在此需放下随身所带的兵器，才可进入寺内。亭内有两名\n"
"知客僧正在忙碌的招待来往的香客。\n"
    );

	set("exits", ([
		"northup" : __DIR__"shijie9",
		"southdown" : __DIR__"shijie8",
	]));
	set("outdoors", "shaolin");
	set("objects",([
		CLASS_D("shaolin") + "/xu-tong" : 1,
		CLASS_D("shaolin") + "/xu-ming" : 1,
		CLASS_D("shaolin") + "/weitian" : 1,
	]));
	setup();
}

void init()
{
	object me,wei;
	me=this_player();
	add_action("do_quit","quit");

	if (me->query_temp("qinjian/askhe"))
	{
	
		if (!objectp(wei=present("wei tianwang",environment(me))))
		{
			wei=new("kungfu/class/shaolin/weitian");
			wei->move(environment(me));
		}

		message_vision(HIY"$N站在那里左顾右盼，一旁的卫天望喝道，“鬼鬼祟祟一看就不是好东西。”，\n"NOR,me);
		call_out("do_diao",3+random(3),me,wei);
		me->delete_temp("qinjian/askhe");

	}

}
int do_diao(object me,object wei)
{
	object he;    
	if (!objectp(he=present("he zudao",environment(me))))
	{
		he=new("kungfu/class/kunlun/hezudao");
		he->move(environment(me));
	/*	he->delete("chat_msg_combat");
		he->set("chat_msg_combat", ({
  			(: perform_action, "sword.feihua" :),  		
			//(: exert_function, "qinjian" :),
		}));
		setup();*/

	}
		message_vision(HIC"蓦地里喀喇一声，石亭屋顶破裂，掉下一大块物事来。众人都吃了一惊，\n"NOR,me);
		
		do_check(me);
		he->kill_ob(wei);
		wei->kill_ob(he);
		me->set_temp("qinjian/lookfight",1);
		return 1;
}

int do_check(object me)
{
	object wei,he;
	me=this_player();
	wei=present("wei tianwang",environment(me));
	he=present("he zudao",environment(me));

	if (objectp(wei)) 
	{
		call_out("do_check",1,me);
		return 1;
	}
	
	if (!objectp(he=present("he zudao",environment(me)))) return;
	else {
		message_vision(HIR"\n\n\n\n\n何足道看了看了$N一眼说道，方才我施展的武技你可都看清楚了？能否参悟（canwu）就看你自己了。\n\n\n\n"NOR,me);
		add_action("do_lingwu","canwu");
		destruct(he);
	}
	return 1;
}

int do_lingwu()
{
	object me;
	//int i,j,x;
	
	me = this_player();       
    if (!me->query_temp("qinjian/lookfight"))
    	return notify_fail("何足道在远处喝道，你本事是非之人，来问此问题作甚？\n");
	
	if (!me->query("family")
		|| me->query("family/master_id")!="he zudao"
		|| me->query("family/family_name")!="昆仑派")
		return notify_fail("何足道在远处喝道，你非我派弟子，来问此问题作甚？\n");

	
    if( me->query_skill("xuantian-wuji", 1) < 350 )
		return notify_fail("你的玄天无极造诣不够350，还无法领悟我派两仪剑法的精要所在！\n");
	
	if( me->query("quest/kl/xtwj/qinjian/pass") )
		return notify_fail("你已经解密了这个琴剑绝技，又何故开此玩笑呢？\n");

	if ((int)me->query("int")<30)
		return notify_fail("这迅雷剑诀很看悟性，你先天悟性30，别来找我！\n");
	
	
	if( time()- me->query("quest/kl/xtwj/qinjian/time")<86400)
		return notify_fail("嗯？你不是刚来请教过我这门绝技的奥秘吗？还是再努力段时间吧！\n");
  
	call_out("thinking",1,me);
	me->delete_temp("qinjian/lookfight");
	return 1;
 
}

int thinking(object me)
{
  int i,j;
  if(!me) return 0;
  if(me->query_temp("qinjian/canwu")<(3+random(3)))
    { me->add_temp("qinjian/canwu",1);
          if(random(2)) tell_object(me,HIG"\n你认真回想着刚才何足道和卫天望打斗时的一招一式...\n"NOR);
             else tell_object(me,HIY"\n突然间，你灵光一闪，回想起何足道一手抚琴，一手挥剑的过程，似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	}
 
  else
   {  
	  me->delete_temp("qinjian/canwu");
  
	  i=random(10);
	  j=random(me->query("kar"));
      if (i == 3 
		// && random(total) >= 80 
	     && me->query("kar") <= 30
		 && j > 27  )
	  {
       
          tell_object(me,HIM"\n你玄天无极功真气由膻中，入缺盆，过阳池外关，交与三焦手少阳之脉，一呼一吸，引而不发，在体内流转不休！\n"NOR);
          message_vision(HIC"\n$N对如何使用玄天无极劲来同时驱动剑法和琴技同时使用的技巧似乎有些了解了。”\n"NOR,me); 
          tell_object(me,HIR"你对如何使用玄天无极功驱动内力实施琴剑双绝似乎有些了解了，剩下的就是勤加练习了！\n"NOR);
          me->set("quest/kl/xtwj/qinjian/pass",1);
          //me->set("title",HIC"全真教先天功传人"NOR);
          log_file("quest/xtwjqinjian", sprintf("%s(%s) 失败%d次成功解开琴剑双绝。富源j：%d；随机数i：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/kl/xtwj/qinjian/fail"),
          j,
		  i,
          me->query("combat_exp")) );
          me->start_busy(1);
       }
      else
       {
          tell_object(me,HIG"\n你沉思许久，不得要领。\n"NOR);
          message_vision(HIC"\n$N摇了摇头，深深地叹了口气。\n"NOR,me); 
          tell_object(me,HBBLU"\n很可惜，你本次尝试琴剑双绝秘密失败！\n"NOR);
          tell_object(me,HBBLU"你目前的经验是" + me->query("combat_exp") + "，现在时间是书剑"+ NATURE_D->game_time() + "，请记录。\n"NOR);
          tell_object(me,HBBLU"你将在间隔24小时后获得下一次机会！。\n\n"NOR);
		  log_file("quest/xtwjqinjian", sprintf("%s(%s) 解密玄天无极琴剑双绝失败%d次。富源j：%d；随机数i：%d；经验：%d。\n",   
          me->name(1),
          me->query("id"), 
          me->query("quest/kl/xtwj/qinjian/fail"),
          j,
		  i,
          me->query("combat_exp")) );
          me->add("quest/kl/xtwj/qinjian/fail",1);
          me->set("quest/kl/xtwj/qinjian/exp", me->query("combat_exp") );
          me->start_busy(1);
          me->set("quest/kl/xtwj/qinjian/time",time());
        } 

     }

}


int do_quit()
{
        object ob = this_player();
	if (ob->query_condition("sl_lunzhi") > 0){
		write("你正在轮值，不能退出游戏。\n");
                return 1;
        }
        return 0;
}

int valid_leave(object me, string dir)
{
	object *inv;
	mapping myfam;
	int i;

	myfam = (mapping)me->query("family");
  	if (!me->query("luohan_winner") && !present("yingxiong ling", me))
		if (me->query("gender") == "女性" && dir == "northup" ) {
			if(objectp(present("xu tong", environment(me))))
				return notify_fail("虚通伸手拦住你白眼一翻说道：千年以来，少林向不许女流擅入。\n"
				 + RANK_D->query_respect(me) +"请下山去吧，免得自讨没趣。\n");
			if(objectp(present("xu ming", environment(me))))
				return notify_fail("虚明迈步挡在你身前，双手合什说道：阿弥陀佛，"
					"这位" + RANK_D->query_respect(me) + "请留步，\n恕小寺不接待女"
                			"客。女施主倘若一心向佛，何妨去峨眉山随喜？\n");
		}
	if ((!myfam || myfam["family_name"] != "少林派" ) && dir == "northup") {
        	inv = all_inventory(me);
        	for(i=sizeof(inv)-1; i>=0; i--)
            	if(inv[i]->query("weapon_prop") && (inv[i]->query("equipped"))) {
                	if(objectp(present("xu tong", environment(me))))
                    		return notify_fail("虚通拦住你说道：这位" +
                        RANK_D->query_respect(me) + "请放下兵刃。少林千年的"
                        "规矩，外客不得持兵刃上山。\n");
                	if(objectp(present("xu ming", environment(me))))
                    		return notify_fail("虚明迈步挡在你身前，双手合什说道：阿"
                        "弥陀佛，这位" + RANK_D->query_respect(me) + "请收起"
                        "兵刃。\n佛门清静之地，不便随意舞刀弄剑。还请施主鉴"
                        "谅。\n");
		}
	}

	if (!me->query("muren_winner")
	 && mapp(myfam)
	 && myfam["family_name"]== "少林派" 
	 && me->query("class") == "bonze" 
	 && dir == "southdown" ) {
		if(objectp(present("xu tong", environment(me))))
			return notify_fail("虚通伸手拦住你躬身说道：这位师兄武功还未练好，不能"
                              "下山，免得折了咱们少林的名声！\n");
		if(objectp(present("xu ming", environment(me))))
			return notify_fail("虚明伸手拦住你躬身说道：这位师兄武功还未练好，不能"
                              "下山，免得折了咱们少林的名声！\n");
	}

	if (me->query_condition("sl_lunzhi") > 0)
		return notify_fail("你正在轮值，不能离开！\n");

	if(me->query("no_quest") && dir == "northup")
		return notify_fail("\n");

	return ::valid_leave(me, dir);
}
