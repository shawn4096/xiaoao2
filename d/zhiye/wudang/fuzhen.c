// /area/jiangbei/wudang/fuzhen.c �����
// By River@SJ

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", HIW"�����"NOR);
        set("long", @LONG
�����������̫���¡����ഫ�Ǿ��ֹ���̫�ӣ�Ҳ���Ǻ�����������ʮ
�������䵱ɽ����ʱ�����ס�ĵط�����������־�����ڷ��ؼҵ�;�У�����
��Ԫ���á�����ĥ�롱�㻯��������ɽ�����������������۵ġ�
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

        set("outdoors", "�䵱");

        setup();
}

int valid_leave(object me, string dir)
{	   
	  
		if (!me->query_temp("mwd/step4")) return ::valid_leave(me, dir);
		
		if (dir =="westup" && objectp(present("mmguard",this_object())) ) 
		{
		   	   
				message_vision(HIC"����Ҫ��ǰ�ߣ���Ȼ���Աߴܳ�������������ס��ɽ�ڣ�\n�ȵ�������ɽ���ҿ������������ԣ�����Ӵ˴�����������·Ǯ����\n"NOR,me);
				return notify_fail("�����������µĴ��ڸ��ֽ��㵲��������\n");

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
		  	    message_vision(HIR"\n\n��������ʦ�������Ѹߣ���λʦ���ֲ���ɽ�ϣ����и��Ǳ���쳣��ŭ��\n"NOR,me);

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
