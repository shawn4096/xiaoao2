// /area/jiangbei/wudang/yuanhe.c Ԫ�͹�
// By River@SJ

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", HIW"Ԫ�͹�"NOR);
        set("long", @LONG
Ԫ�͹����䵱ɽ�������Ź�����ϵĵ�һ�����ۡ��ݵ��ؼ��أ������ϵ�
�����õ������ƹܡ�Ԫ��ǨУ����������������ȡ����Ԫ�͹ۡ������Ǩ��
�Ƿ������˼��У����ָ�������̾ߡ���ʵ�ϣ�Ԫ�͹����䵱�ɴ���Υ�����
���ɵ��䵱���ӵĻ�����
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
        set("outdoors", "�䵱");

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
	   
	   //ֻ����ɽ�������⣬������ʧ�ܣ�����

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