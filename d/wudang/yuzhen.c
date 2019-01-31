// /d/wudang/yuzhengong.c ���湬
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIW"���湬"NOR);
        set("long", @LONG
�����ǽ���ͽ��㻹Ը�����湬�����䵱ɽ�ĵ�һ��������ޱȣ���
��ʢ�����й������������������������˱չ��Ѿã����˲�֪���Ƿ�����
�˼䣬��䴫˵���ѵõ����ţ��������Ĥ�ݡ�
LONG
        );
        set("exits", ([
                "westup" : __DIR__"wdbolin",
                "northdown" : __DIR__"gsdao2",
        ]));

        set("outdoors","�䵱");

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
