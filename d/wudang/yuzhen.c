// /d/wudang/yuzhengong.c 遇真宫
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIW"遇真宫"NOR);
        set("long", @LONG
这里是进香客进香还愿的遇真宫，乃武当山的第一道宫宇。宽敞无比，香
火鼎盛。宫中供着张三丰真人像。由于张真人闭关已久，外人不知其是否尚在
人间，民间传说他已得道仙逝，因此立像膜拜。
LONG
        );
        set("exits", ([
                "westup" : __DIR__"wdbolin",
                "northdown" : __DIR__"gsdao2",
        ]));

        set("outdoors","武当");

        set("objects",([
                CLASS_D("wudang")+"/zhike" : 1,
                __DIR__"obj/gdxiang" : 1,
        ]));
        setup();

}

int valid_leave(object me, string dir)
{
        object mmr;

	    if (!me->query_temp("mwd/start") ||!me->query_temp("mwd/step2")) return ::valid_leave(me, dir);
	   

		if ( objectp(mmr=present("mmrobber",this_object())))
		{
				mmr->kill_ob(me);
				me->kill_ob(mmr);
				//mmr2->kill_ob(me);
		}else {
				
				me->set_temp("mwd/step3",1);
		}
        return ::valid_leave(me, dir);
     

}

void init()
{
	object me=this_player();
	object mmr1,mmr2;
	 if (!me->query_temp("mwd/start")) return;

	 if (me->query_temp("mwd/step2")&& !me->query_temp("mwd/step3"))
	 {
		  
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
