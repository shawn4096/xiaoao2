#include <room.h>
inherit ROOM;
#include "/d/suzhou/npc/lchj.h";//连城诀
#include <ansi.h>
int do_fail(object me);

void create()
{
        set("short", "监狱");
        set("long", @LONG
这里是监狱，约莫两丈见方的一间大石室，墙壁和顶板都是大石所砌。
墙角里放着一只粪桶，鼻中闻到的尽是臭气和霉气。从西面墙上的小窗望
去，可以见到翰林府的一角。
LONG
        );

        set("exits", ([
                  "east" : __DIR__"bingying",
        ]));
        set("objects", ([
                __DIR__"npc/dingdian" : 1,
        ]));

        set("cost", 0);
       set("coor/x",90);
  set("coor/y",-190);
   set("coor/z",0);
   set("incity",1);
	setup();
}

void init()
{
        add_action("do_guard","guard");
        add_action("do_guard","jingjie");
		add_action("do_guard","baohu");

}
int do_guard(string arg)
{
	object me;
	me=this_player();
	if (me->is_busy())
	{
		return notify_fail("你正忙路中，请稍安勿燥？\n");

	}
	if (!arg||arg!="丁典")
	{
		return notify_fail("你要在此看守警戒保护谁？\n");
	}
	if (!me->query_temp(QUESTDIR3+"kanshou"))
	{
		return notify_fail("你跟丁典大侠非亲非故，不需要你没事献殷勤！\n");

	}
	if (!present("ding dian",environment(me)))
	{
		return notify_fail("丁典不在此地，你要保护谁？\n");
	}
	if (time()-me->query(QUESTDIR+"time")<86400)
	{
		return notify_fail("你来的太频繁了，无需天天来此胡闹，明天再来？\n");

	}
	
		message_vision(HIY"$N对丁典鞠了一躬，说道，“请丁大侠放心！有我在，任何来犯之敌都伤不了你！”\n"NOR,me);
		
		call_out("attacker_come",10+random(10),me);
		
		me->start_busy(10);
	
	return 1;
}

int attacker_come()
{
	object obj,ob,me;
	me=this_player();
	ob=present("ding dian",this_object());
	if (!ob)
	{
		return notify_fail("丁典已经为血刀门人所杀，你要保护谁？\n");

	}
	tell_object(me,HIY"丁典此时已经进入无我状态，头顶蒸汽氤氲，此时显然已经进入练功的紧要关头！\n"NOR);

	tell_object(me,HIC"$N正在四处打量之际，心中着实紧张，不知血刀门高手何时能到，担心有违丁典的指示。\n" 
                       "这时，忽听一阵快速奔腾的声音传来，显然有高手在飞速朝此处奔来！\n"NOR+
						"你下意识地飞身挡在丁典面前，此时监狱外一阵喋喋怪笑，“相好的，原来你躲在这儿”！\n"NOR); 
     message_vision(HIR"\n$N只见监狱口里站着五个红衣喇嘛，喊道：丁典，拿出神照经来，饶你不死，否则明年今日就是你的忌日。\n"NOR, me);
    
	 obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));

     obj->move(environment(me));
	 obj->kill_ob(me);
	 obj->kill_ob(ob);
     
	 obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));
	 obj->kill_ob(me);
	 obj->kill_ob(ob);

     obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));    
     obj->kill_ob(me);
	 obj->kill_ob(ob);

     obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));    
     obj->kill_ob(me);
	 obj->kill_ob(ob);
	 //第五组
     obj=new("d/lanzhou/npc/heiyiren");
     obj->set("kill_id",me->query("id"));
     obj->move(environment(me));    
     obj->kill_ob(me);
	 obj->kill_ob(ob);

	 call_out("check_fight",20+random(6),me,ob);

	return 1; 
}


int check_fight(object me,object ob)
{
	
	if (!me) return 1;

	if (!present("ding dian",environment(me))||!ob)
	{
		write("丁典被血刀门高手所杀，任务失败！\n");

		do_fail(me);
		return notify_fail("丁典被血刀门高手所杀，任务失败！\n");
	}

	if (environment(ob)!=environment(me))
	{
		write("你已经离开这个区域，保护丁典任务失败！\n");
		do_fail(me);
		return notify_fail("你已经离开这个区域，保护丁典任务失败！\n");
	}
	
	if (present("heiyi ren",environment(me)))
	{
		message_vision(HIR"黑衣人眼见被众人围住，忽然大喊一声，浑然不顾自己伤势，拼尽全身力气刺向丁典!\n"NOR,me);
		if (ob)
		{
			message_vision(HIY"丁典大叫一声，为血刀门高手一刀刺死!\n"NOR,me);
			ob->die();
		}
		write("丁典被血刀门高手临终反击所杀，任务失败！\n");

		do_fail(me);
		return notify_fail("丁典被血刀门高手所杀，任务失败！\n");

	}
	me->set(QUESTDIR+"time",time());
	me->set(QUESTDIR+"combat",me->query("conbat_exp"));
	
	me->set(QUESTDIR3+"jingjieok",1);

	me->set_temp(QUESTDIR3+"jingjieok",1);

	tell_object(me,HIC"丁典说道，小侠客真是英勇，居然能将这些刺客杀死,很有武学潜质。\n"NOR);
	tell_object(me,HIC"丁典说道，我马上就要出狱去做一件大事，不能再陪你了，既然你要体验，我可以跟你说下狄云兄弟的故事。\n"NOR);
	tell_object(me,HIC"丁典说道，狄云兄弟当时也是和你一般杀了这些凶徒，然后去大雪山一带游历，好像在寻找什么人。\n"NOR);
	tell_object(me,HIC"丁典说道，前几天我出去打探时候似乎“落花流水”江南四侠都出动了。\n"NOR);
	tell_object(me,HIC"丁典说道，真是妖魔鬼怪，鬼魅魍魉都不安生啊！。\n"NOR);
	
	message_vision(HBBLU+HIW"$N已经完成监狱中丁典布置给你的任务，保护丁典成功，丁典对你好感大增！\n",me);	

	return 1;

}

int do_fail(object me)
{
	if (!me) return;
	
	me->add(QUESTDIR3+"fail",1);
	me->set(QUESTDIR+"time",time());
	me->set(QUESTDIR+"combat",me->query("conbat_exp"));
	me->delete_temp(QUESTDIR3);
	message_vision(HIC"在规定时间内丁典被人所刺杀，任务失败！\n"NOR,me);
	return 1;
}
