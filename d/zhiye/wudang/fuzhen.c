// /area/jiangbei/wudang/fuzhen.c 复真观
// By River@SJ

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", HIW"复真观"NOR);
        set("long", @LONG
复真观又名“太子坡”，相传是净乐国王太子，也就是后来的玄武大帝十
五岁入武当山修炼时最初居住的地方，又因其意志不坚在返回家的途中，被紫
气元君用“铁杵磨针”点化，复又上山修炼，因而得名复真观的。
LONG
        );

        set("exits", ([
                "west" : __DIR__"laojun",
                "westup" : __DIR__"shijie2",
                "northdown" : __DIR__"shibapan",
        ]));

        set("objects",([
               __DIR__"npc/daotong" : 2,
               CLASS_D("wudang") + "/guxu" : 1,
        ]));

        set("no_clean_up", 0);

        set("outdoors", "武当");

        setup();
}

int valid_leave(object me, string dir)
{	   
	  
		if (!me->query_temp("mwd/step4")) return ::valid_leave(me, dir);
		
		if (dir =="westup" && objectp(present("mmguard",this_object())) ) 
		{
		   	   
				message_vision(HIC"你正要向前走，忽然从旁边窜出几个人来，堵住了山口，\n喝道，“此山是我开，此树是我栽，若想从此处过，留下买路钱！”\n"NOR,me);
				return notify_fail("几个穿隐形衣的大内高手将你挡了下来。\n");

				//return 0;
		}else {
			
			if (me->query_temp("mwd/step4"))
		    {
				
				me->set_temp("mwd/step5",1);
		    }
			

		}
        return ::valid_leave(me, dir);
}

void init()
{
	object me=this_player();
	object mmr1,mmr2;
	
	 if (!me->query_temp("mwd/start")) return;

	 if (me->query_temp("mwd/step4")&& !me->query_temp("mwd/step5"))
	 {
		  	    message_vision(HIR"\n\n你想起了师傅年岁已高，几位师兄又不在山上，心中更是变得异常愤怒！\n"NOR,me);

				mmr1=new("d/wudang/taiji/robber");
				mmr1->do_copy(me);
				mmr1->move(this_object());
				mmr1->kill_ob(me);
				me->kill_ob(mmr1);
		
				mmr2=new("d/wudang/taiji/guard");
				mmr2->do_copy(me,10);
				mmr2->move(this_object());  
				mmr2->kill_ob(me);
				me->kill_ob(mmr2);
		/*		mmr3=new("d/wudang/taiji/guard");
				mmr3->do_copy(me,14);
				mmr3->move(this_object());
				mmr3->kill_ob(me);		*/		
			
	 }
	 return ;
}
