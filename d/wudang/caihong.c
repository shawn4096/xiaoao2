// /d/wudang/caihong.c 彩虹(石梁)
// by ydh and shang

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIM"雨后彩虹"NOR);
        set("long", @LONG
你走入山坞中，这里是九渡涧的下流，各岭之水均在此交汇，然后突然倾
泻而下注入山涧形成壮观的瀑布。一条天然石梁横跨两岸，远处观看在是一条
雨后彩虹。再往上就是陡峭的十八盘了。
LONG
        );

        set("exits", ([
                "southup" : __DIR__"shibapan",
                "northup" : __DIR__"wangbei",
        ]));
        set("objects",([
               __DIR__"npc/youke" : 1,
        ]));

        set("no_clean_up", 0);

        set("outdoors", "武当");

        setup();
}

int valid_leave(object me, string dir)
{
        object mmr;

	    if (!me->query_temp("mwd/start") ||!me->query_temp("mwd/step3")) return ::valid_leave(me, dir);
	   

		if ( objectp(mmr=present("mmrobber",this_object())))
		{
				mmr->kill_ob(me);
				me->kill_ob(mmr);
				//mmr2->kill_ob(me);
		}else {
				
				me->set_temp("mwd/step4",1);
		}
        return ::valid_leave(me, dir);
     

}


void init()
{
	object me=this_player();
	object mmr1,mmr2;
	 if (!me->query_temp("mwd/start")) return;
	 
	 if (me->query_temp("mwd/step3")&& !me->query_temp("mwd/step4"))
	 {
		  message_vision(HIY"\n\n敌人来拦截的高手越来越强，你不禁心中焦虑，不知道山上的情况怎样？\n"NOR,me);
				mmr1=new("d/wudang/taiji/robber");
				mmr1->do_copy(me);
				
				mmr1->move(this_object());
				mmr1->kill_ob(me);
				me->kill_ob(mmr1);
		
				mmr2=new("d/wudang/taiji/robber");
				mmr2->do_copy(me);
				
				mmr2->move(this_object());   
				mmr2->kill_ob(me);
				me->kill_ob(mmr2);
			
	 }
	 return ;
}
