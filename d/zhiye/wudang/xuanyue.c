// /d/wudang/xuanyuemen.c ������
// By River@SJ

#include <ansi.h>
#include <wanted.h>

inherit ROOM;

void create()
{
        set("short", HIY"������"NOR);
        set("long", "�����ǰ���������������䵱ɽ������һ����ľ��ï�ĸ�ɽ������ɽ�屻
�������֣��Ѽ�ȫò��һ��ʯ���������ϣ���Լ�ɼ���������͡�һ������ʯ
��(fang)��ɽ�������䵱ɽ����̫��ɽ��Ϊ��ʮ������֮һ���ж�ʮ�߷塢��
ʮ���ҡ���ʮ�Ľ�����̨���微����̶�������š��������һ���أ���������
��ɭ�ޣ����ղ��죬�����ľ����������������䵱��ӭ�����͵ĵ�һվ��
"HIG"\n\t\t\t  ��  ��  ɽ\n\n"NOR
        );

        set("exits", ([
                "east" : __DIR__"wdroad8",
                "southup" :__DIR__"shijie1",
        ]));
        set("outdoors","�䵱");
        set("item_desc", ([
                "fang" : HIG"\n
                    ������������������
                ��    ����������������   
                      ����        ����  
                      ����   ��   ������ 
                      ����        ������ 
                      ����        ������                         
                      ����   ��   ����  
                      ����        ������                          
                      ����        ������������������������������ 
                      ����   ɽ   ����
                      ����        ���� 
                      ����������������
                      ����������������\n\n"NOR,
        ]));
        
        setup();
}

int valid_leave(object me, string dir)
{
        object mmr;
	    if (!me->query_temp("mwd/start")) return ::valid_leave(me, dir);
	   
		if (objectp(mmr=present("mmattacker",this_object())))
		{
				mmr->kill_ob(me);
				me->kill_ob(mmr);
				//mmr2->kill_ob(me);
		}else {
	
				me->set_temp("mwd/step1",1);
		}
        return ::valid_leave(me, dir);
}

void init()
{
	object me=this_player();
	object mmr1,mmr2;
     
	 if (me->query_temp("mwd/start")&& !me->query_temp("mwd/step1"))
	 {
		  
				mmr1=new("d/wudang/taiji/attacker");
				mmr1->do_copy(me);
				mmr1->move(this_object());
				mmr1->kill_ob(me);
		
				mmr2=new("d/wudang/taiji/attacker");
				mmr2->do_copy(me);
				mmr2->move(this_object());   
				mmr2->kill_ob(me);
	 }
	 return ;
}
