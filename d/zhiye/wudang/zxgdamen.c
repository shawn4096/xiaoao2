// /d/wudang/zxgdamen.c  紫霄宫大门
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",MAG"紫霄宫大门"NOR);
        set("long", @LONG
你已到了展旗峰下，前面就是武当山最为宏大的宫宇紫霄宫了。殿宇依山
而筑，高低错落有致。周围古木参天，翠竹成林，鸟语花香，景色清幽，好一
个修道成仙处。这里是武当师徒的主要活动场所。
LONG
        );
        set("exits", ([
                "enter" : __DIR__"zixia",
                "northdown" :__DIR__"shijie3",
        ]));

        set("objects",([
                CLASS_D("wudang")+ "/fengsong" : 1,
                __DIR__"npc/daotong" :2,
        ]));
        
        set("outdoors","武当");
        setup();
}

int valid_leave(object me, string dir)
{	   
	  	if (!me->query_temp("mwd/start"))  return ::valid_leave(me, dir);

		if (dir =="enter" && objectp(present("mmguard",this_object()))) 
		{
		   	   
				message_vision(HIC"你正要向前走，忽然从旁边窜出几个人来，堵住了山口，\n喝道，“此山是我开，此树是我栽，若想从此处过，留下买路钱！”\n"NOR,me);
				return notify_fail("几个穿隐形衣的大内高手将你挡了下来。\n");
				
		}else {
		
			if (me->query_temp("mwd/step5"))
			{			
				me->set_temp("mwd/step6",1);			
				message_vision(HIC"$N将这一批人杀完后，听了下，四周万籁俱静，似乎山上没有什么异常，不由地心中舒了口气。\n"NOR,me);
				message_vision(HIC"$N暗自盘算了一下，心想，还是赶紧上山看看情况再说。\n"NOR,me);
			}
		}
        return ::valid_leave(me, dir);
}

void init()
{
	object me=this_player();
	object mmr1,mmr2,mmr3;
	 if (!me->query_temp("mwd/start")) return;

	 if (me->query_temp("mwd/step5")&& !me->query_temp("mwd/step6"))
	 {
		  	    message_vision(HIR"\n又是一批黑衣人出来拦截，显然是有针对性而来！\n"NOR,me);
				message_vision(HIR"\n你想起了师傅年岁已高，几位师兄又不在山上，心中更是变得异常愤怒！\n"NOR,me);
				mmr1=new("d/wudang/taiji/robber");
				mmr1->do_copy(me);
				mmr1->move(this_object());
				mmr1->kill_ob(me);
				me->kill_ob(mmr1);
		
				mmr2=new("d/wudang/taiji/guard");
				mmr2->do_copy(me,12);
				mmr2->move(this_object());  
				mmr2->kill_ob(me);
				me->kill_ob(mmr2);
			/*	mmr3=new("d/wudang/taiji/guard");
				mmr3->do_copy(me,12);
				mmr3->move(this_object());
				mmr3->kill_ob(me);	
				mmr4=new("d/wudang/taiji/guard");
				mmr4->do_copy(me,15);
				mmr4->move(this_object());
				mmr4->kill_ob(me);			*/
			
	 }
	 return ;
}
