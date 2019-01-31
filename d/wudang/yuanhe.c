// /area/jiangbei/wudang/yuanhe.c 元和观
// By River@SJ

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", HIW"元和观"NOR);
        set("long", @LONG
元和观是武当山进玄岳门古神道上的第一座道观。据道藏记载，玄天上帝
修练得道后，曾掌管“元和迁校府”，故这座道观取名“元和观”。这里，迁，
是放逐的意思；校，是指枷锁等刑具。事实上，元和观是武当派处罚违犯清规
戒律的武当弟子的机构。
LONG
        );

        set("exits", ([
                "southup" : __DIR__"gsdao2",
                "northdown" : __DIR__"gsdao1",
                "east" : __DIR__"yuanhe1",
        ]));

        set("objects",([
                __DIR__"npc/daotong" : 1,
        ]));

        set("no_clean_up", 0);
        set("outdoors", "武当");

        setup();
}
void init()
{
	object me=this_player();
	object mmr1,mmr2;
	 if (!me->query_temp("mwd/start")) return;
	
	 if (me->query_temp("mwd/step1") && !me->query_temp("mwd/step2"))
	 {
		  
				mmr1=new("d/wudang/taiji/attacker");
				mmr1->do_copy(me);
				mmr1->set("combat_exp",(int)me->query("combat_exp")*6/5);
				mmr1->move(this_object());
				mmr1->kill_ob(me);
				me->kill_ob(mmr1);
				
		
				mmr2=new("d/wudang/taiji/attacker");
				mmr2->do_copy(me);
				mmr2->set("combat_exp",(int)me->query("combat_exp")*6/5);
				mmr2->move(this_object());   
				mmr2->kill_ob(me);
				me->kill_ob(mmr2);
			
	 }
	 return ;
}

int valid_leave(object me, string dir)
{
        object mmr;

	    if (!me->query_temp("mwd/start") ||!me->query_temp("mwd/step1")) return ::valid_leave(me, dir);
	   
	   //只有上山才算正解，否则都算失败，重来

		if ( objectp(mmr=present("mmattacker",this_object())))
		{
				mmr->kill_ob(me);
				me->kill_ob(mmr);
				//mmr2->kill_ob(me);
		}else {
				
				me->set_temp("mwd/step2",1);
		}
        return ::valid_leave(me, dir);
     

}