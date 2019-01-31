// Room: gudi.c 谷底
// Created by Numa 1999-12-04

#include <ansi.h>
inherit ROOM;

string do_zb1();

void create()
{
        set("short", HIW"谷底"NOR);
        set("long", @LONG
谷内怪石嶙峋，竟没有一点出路可寻。此处的严寒非寻常地方可比，
各个方向似乎都不断的有寒风吹来，寒冷异常。山谷一处低洼之地有大量
的阴寒之气蒸腾，四周结满寒冰，白茫茫的一片。在洼地正中心有一块看
起来甚是奇怪的怪石(stone)。
LONG);
        set("item_desc",([
                "怪石": (: do_zb1 :),
                "石":   (: do_zb1 :),
                "stone":(: do_zb1 :),
        ]));
        set("outdoors", "嵩山");
        setup();
}

string do_zb1()
{
        object me = this_player();
        
        if (!me->query_temp("ss/zsb_5"))
                return "你所见之处皆是怪石，毫无次序的堆在谷中,看了半天看不出啥来。\n";
        //me->delete_temp("ss/zsb_5");
        me->set_temp("ss/zsb_end",1);
        return "你所见之处皆是怪石，毫无次序的堆在谷中。在其中一堆石头中似乎有东西在闪烁。\n";
}



void init()
{
        object ob = this_player();
        if (userp(ob))
        {
                if (ob->query_skill("hanbing-zhenqi",1) < 500)
                {
                        message_vision(HIW"$N初下谷，冷的全身发麻，慌张的顺着绳子爬了回去。\n"NOR,ob);
                        ob->move(__DIR__"dtlxia");
                        message_vision(BLU"$N脸色发青，冷的浑身直哆嗦。\n"NOR,ob);
                        return;
                }
                else if (ob->query_skill("hanbing-zhenqi",1) > 550)
                        message_vision(HIW"$N顺着绳子爬了下来，并没有什么异样的感觉。\n"NOR,ob);
                else
                {
                        ob->set_temp("ss/get_cold",1);
                        message_vision(HIW"$N初下谷，只感觉这里和外界温差极大，不由得打了个冷颤。\n"NOR,ob);
                }
        }
        add_action("do_back",({"climb","pa"}));
        add_action("do_resist",({"resist","diyu","kangheng"}));
        add_action("do_move",({"fan","move"}));
}

int do_back(string arg)
{
        object me = this_player();
        
        if (!arg)
                return notify_fail("什么？\n");
        if (arg != "up" && arg != "back")
                return notify_fail("你要往哪里爬？\n");

        if(me->query_encumbrance() * 100 / me->query_max_encumbrance() > 20)
                return notify_fail("你背那么多东西，不怕掉下来吗？\n");
        
        message_vision("$N撮了撮手，一提气，顺着山壁爬了上去。\n",me);
        me->add("jingli",100);
        me->add("neili",200);
        me->delete_temp("ss");
        me->move(__DIR__"dtlxia");
        tell_room(environment(me),me->name(1)+"从谷底爬了上来，累的气喘吁吁。\n",({me}));
        return 1;
}

int do_move(string arg)
{
        object me = this_player();
        object ob, *clone;
        int i, j;
        
        if (!arg)
                return 0;
        if (arg != "stone" && arg != "石头" && arg != "怪石")
                return 0;
        if (!me->query_temp("ss/zsb_end"))
                return notify_fail("没事别乱搬石头，吃饱了撑的？\n");

        if (me->query("neili") < 2000)
        {
                message_vision("$N用尽全力想要搬开石头，没想到一不留神，石头砸在了自己脚上。\n",me);
                me->unconcious();
                return 1;
        }
        me->add("neili",-1000);
        message_vision("$N用尽全力，大喝一声将石头搬了开来。\n",me);

        ob = unew(__DIR__"obj/ice");

        if(!clonep(ob))
                return notify_fail("你发现下面什么都没有。\n");
        i = ob->query("unique");
        clone = filter_array(children(base_name(ob)), (: clonep :));
        j = sizeof(clone);
        while (j--)
                if (!clone[j]->query("clone_by_wizard"))
                        i--; 
        if(clonep(ob) && i < 0)
        {
                destruct(ob);
                return notify_fail("你发现下面什么都没有。\n");
        }

        tell_object(me,"你发现石头中居然有一块玄冰，中间似乎冻有什么东西。\n");
        ob->set_temp("find_by",me->query("id"));
        ob->move(this_object());
        me->delete_temp("ss/zsb_end");
        me->set_temp("ss/zsb_get",1);
        return 1;
}
        
int do_resist(string arg)
{
        object me = this_player();
        object ob = this_object();
        
        if (!arg)
                return 0;
		//抱冰
		if (!present("xuan bing",environment(me)))
		{
			message_vision("你所处环境没有玄冰，怎么抵抗着寒风也没什么效果。\n",me);
			return 1;
		}
		//
		if (!me->query_temp("hbzq/askzuo")) 
		{
			me->add_condition("cold_poison",10);

			return notify_fail(HIC"寒风呼啸，你冻得瑟瑟发抖，但终因不知道抵御着寒气的法门，所以逐渐为寒气所伤。\n"NOR);
		}

        if (arg == "hanfeng" || arg == "cold" || arg == "hanleng" ||arg == "玄冰"||arg == "寒冷"||arg == "寒冰"||arg == "寒风")
        {
                /*if (!me->query("ss/hb_improve"))
                        return 0;
                if (!me->query_temp("ss/get_cold"))
                        return notify_fail("你要做什么？\n");*/
				if (!me->query_temp("hbzq/askzuo"))
                        return notify_fail("没有师傅指点，你在这瞎捉摸啥？\n");
        
                if (me->query_skill("hanbing-zhenqi",1) < 450
                ||  me->query("max_neili") < 3000)
                        return notify_fail("你的寒冰真气修为如此之差(不足450)，强行与寒风相抗衡恐怕会有生命危险。\n");

                if (me->is_busy() || me->is_fighting())
                        return notify_fail("你正忙着呢！\n");
        
                if (me->query("jingli")<50)
                        return notify_fail("你现在太累了，还是休息一下吧！\n");

                if (me->query("neili")<100)
                        return notify_fail("你现在太累了，还是休息一下吧！\n");

                if (me->query("jing")<50)
                        return notify_fail("你现在太累了，还是休息一下吧！\n");
                
//              me->delete_temp("ss/get_cold");
                tell_object(me,BLU"你静静盘腿而坐，运用体内寒冰真气和外界的寒风相抗衡。\n"NOR);
                tell_room(ob,HIW + me->name(1) + "盘腿而坐，周身被一股白气笼罩着。\n"NOR,({me}));
				me->add_temp("ss/kangheng",1);

                me->start_busy(5);
                remove_call_out("hb_improving");
                call_out("hb_improving",4,me);
                return 1;
        }
        else
                return notify_fail("你要和什么相抗衡？\n");
}

int hb_improving(object me)
{
        int i,num;
/*      
        if (!me)
        {
                remove_call_out("hb_improving");
                return 1;
        }
*/      
        if (!me->query("songshan_point"))
                i = 100;
        else
                i = me->query("songshan_point")/3;
        if (i<100)
                i = 100;
        if (i>600)
                i = 600;
        
        me->receive_damage("jingli",30);
        me->receive_damage("neili",50);
        if (random(5)>3)
        {
                tell_object(me,"突然一阵强风吹来，你也不由得打了个冷颤。\n");
                me->receive_damage("jing",30);
        }
        i += (400 - me->query_skill("hanbing-zhenqi",1))*2;
        if (i>800)
                i = 800;
		me->improve_skill("hanbing-zhenqi", i*2/3 + random(i));
        tell_object(me,HIC"你在与寒风的抗衡当中寒冰真气的修为也大大提升。\n"NOR);
		//增加参悟触发
		
		num=me->query_temp("ss/kangheng",1);
		
		if (random(num)>10 
			&& me->query_temp("hbzq/askzuo")
			&& !me->query_temp("ss/iscold"))
		{
			message_vision(HIR"$N正在与寒风抗衡之际，功力运转不绝，身旁的那块"HIW"玄冰"HIR"陡然间发出一股极寒之气，侵入$N的心脉。\n",me);
			//me->receive_wound("qi",random(1000),"寒毒侵入心脉而");
			message_vision(HIR"\n\n$N一时不查，哇地突出一口鲜血，此时想起师傅的叮嘱，急忙运转寒冰真气心法，开始疗毒(liaodu)治愈。\n",me);

			me->apply_condition("cold_poison",5);
			me->set_temp("ss/iscold",1);
				
			add_action("do_heal","liaodu");
		}
        return 1;
}
//构思寒冰真气的参悟之地
//自我疗毒
int do_heal(object me)
{
	me=this_player();
	me->delete_temp("hbzq/askzuo");
	//me->start_busy(2);
	if (me->query("family/family_name") != "嵩山派" )
		return notify_fail("你不是嵩山派弟子，参悟不出什么内容来。\n");
	if (me->query_skill("hanbing-zhenqi",1) < 450){
		return notify_fail("你寒冰真气功力不足450，来此作甚？\n");
	}
	if (me->is_busy())
	{
		return notify_fail("你正在忙碌中。\n");
	}
	if (!me->query("quest/ss/dichuan")){
		return notify_fail("你非核心弟子，还是去好好把为我五岳并派大计去多请几个高手来吧？\n");
	}
	
	if (me->query_skill_mapped("force")!="hanbing-zhenqi")
	{
		return notify_fail("你的内功不是寒冰真气,无法进行领悟。\n");
	}
    if (me->query("quest/ss/hbzq/pass")){
		return notify_fail("say 你已经开了这个谜题,还来此聒噪作甚？？\n");       	
	}
	if (time()-me->query("quest/ss/hbzq/time")<86400){
		return notify_fail("say 你也太勤快点了耶？？\n");    	
					
	}
		    message_vision(HIW"$N盘膝而坐，脸色苍白一片，哇地吐出一口鲜血，显然是受伤不轻。\n"NOR,me);
		    message_vision(HIC"$N为这股寒气所侵，知道此时正是生死存亡之际，哪里敢大意，寒冰真气急忙去抵抗这股寒毒。\n",me);
	
				me->start_busy(999);
				remove_call_out("thinking");
				call_out("thinking",1,me);
			//	me->delete_temp("chaozong/ask",1);
				return 1;
}

int thinking(object me)
{
  int i,j,s; 
  if(!me) return 0;
  i=random(me->query("kar"));
  s=20;

  if(me->query("m-card-vip")) s =  18;
  if(me->query("y-card-vip")) s =  15;
  if(me->query("buyvip"))     s =  10;
  j=random(s);
  me->set("quest/ss/hbzq/time",time());
  me->delete_temp("ss/iscold");

 // me->set("quest/ss/hbzq/thinking",1);

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟寒冰真气时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_hbzq")<(20+random(10)))
  {  
	  me->add_temp("canwu_hbzq",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你认真调动寒冰真气与这股寒毒抗衡，忽觉心脉一暖.\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n忽然，你真气流转不休，身子一暖，似乎抓住了一些明悟,。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你陷入馄饨状态，大脑一片空明，似乎要抓住那个线索了！..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，甚是无聊，神情抑郁，似乎有些累了.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎遇到瓶颈了..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n你思维漂浮在空中，宛如婴儿沐浴.神清气爽.\n"NOR);
			break;
		default:tell_object(me,YEL"\n你叹了一口气，精神总是不能有效集中.\n"NOR);
			break;
	  }      

	  tell_room(environment(me),HIC""+me->query("name")+"面色苍白，眉头紧皱，似乎在抵抗着什么...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (i>25
			&& j<4
			&& random(me->query("con"))>40
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
		 message_vision(HIY"\n$N忽然一阵悸动，先前凝固不动的寒冰真气仿佛活了般的，自发运转起来。\n"NOR,me); 
		 message_vision(HIC"\n起于尾闾，行于督脉，经百汇而贯通而下，过十三重楼，直达丹田部位，循环往复不休。\n"NOR,me); 
         message_vision(HIG"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断领悟，终于领悟了寒冰真气的奥秘，寒冰真气至此彻底豁然贯通！已臻大成。”\n"NOR,me); 
         log_file("quest/sshanbing", sprintf("%s(%s) 成功！第%d次参悟，机缘巧合下，成功参悟寒冰真气的奥秘，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/ss/hbzq/fail"),
		 i,
		 j,
         me->query("combat_exp")));
		 me->start_busy(1);
		 me->set("quest/ss/hbzq/time",time());
		 me->set("quest/ss/hbzq/pass",1);
		 me->set("title",HBBLU+HIW"寒冰真气真传"NOR);		 
		 me->set("mytitle/quest/hanbingtitle",HBBLU+HIW"寒冰真气真传"NOR);
		 me->delete_temp("canwu_hbzq");
		 me->delete_temp("ss_iscold");
		 me->delete_temp("hbzq/askzuo");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来又是一无所获啊。”\n"NOR,me); 
		 message_vision(HIY"\n参悟寒冰真气绝技解密失败！\n"NOR,me); 
         log_file("quest/sshanbing", sprintf("%s(%s) 失败！第%d次失败参悟寒冰真气，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/ss/hbzq/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/ss/hbzq/fail",1);
		 me->set("quest/ss/hbzq/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_hbzq");
		 me->delete_temp("ss_iscold");
		 me->delete_temp("hbzq/askzuo");
		 return 1;
   }

}