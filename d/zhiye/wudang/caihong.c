// /d/wudang/caihong.c �ʺ�(ʯ��)
// by ydh and shang

inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", HIM"���ʺ�"NOR);
        set("long", @LONG
������ɽ���У������ǾŶɽ�������������֮ˮ���ڴ˽��㣬Ȼ��ͻȻ��
к����ע��ɽ���γ�׳�۵��ٲ���һ����Ȼʯ�����������Զ���ۿ�����һ��
���ʺ硣�����Ͼ��Ƕ��͵�ʮ�����ˡ�
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

        set("outdoors", "�䵱");

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
		  message_vision(HIY"\n\n���������صĸ���Խ��Խǿ���㲻�����н��ǣ���֪��ɽ�ϵ����������\n"NOR,me);
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
