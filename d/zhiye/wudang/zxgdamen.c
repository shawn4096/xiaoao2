// /d/wudang/zxgdamen.c  ����������
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",MAG"����������"NOR);
        set("long", @LONG
���ѵ���չ����£�ǰ������䵱ɽ��Ϊ���Ĺ����������ˡ�������ɽ
�������ߵʹ������¡���Χ��ľ���죬������֣����ﻨ�㣬��ɫ���ģ���һ
���޵����ɴ����������䵱ʦͽ����Ҫ�������
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
        
        set("outdoors","�䵱");
        setup();
}

int valid_leave(object me, string dir)
{	   
	  	if (!me->query_temp("mwd/start"))  return ::valid_leave(me, dir);

		if (dir =="enter" && objectp(present("mmguard",this_object()))) 
		{
		   	   
				message_vision(HIC"����Ҫ��ǰ�ߣ���Ȼ���Աߴܳ�������������ס��ɽ�ڣ�\n�ȵ�������ɽ���ҿ������������ԣ�����Ӵ˴�����������·Ǯ����\n"NOR,me);
				return notify_fail("�����������µĴ��ڸ��ֽ��㵲��������\n");
				
		}else {
		
			if (me->query_temp("mwd/step5"))
			{			
				me->set_temp("mwd/step6",1);			
				message_vision(HIC"$N����һ����ɱ��������£����������㾲���ƺ�ɽ��û��ʲô�쳣�����ɵ��������˿�����\n"NOR,me);
				message_vision(HIC"$N����������һ�£����룬���ǸϽ���ɽ���������˵��\n"NOR,me);
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
		  	    message_vision(HIR"\n����һ�������˳������أ���Ȼ��������Զ�����\n"NOR,me);
				message_vision(HIR"\n��������ʦ�������Ѹߣ���λʦ���ֲ���ɽ�ϣ����и��Ǳ���쳣��ŭ��\n"NOR,me);
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
