#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIR"�ص�"NOR);
        set("long", @LONG
�����������ص���ɽ�����������죬��֪ͨ���δ��������ʯ�ڷǳ�
��ʪ������������ˮԴ��
LONG);
        set("objects", ([
                    __DIR__"npc/hama" : 1,
        ]));
        set("exits", ([
              "westdown" : __DIR__"midao2",
              "east" : __DIR__"midao",
        ]));
        setup(); 
}

void init()
{    
  	object me = this_player();
     	if (random(me->query("kar")) <8 && me->query_con() < 35){ 
        	tell_object(me, HIB "���Ȼ�е�����һ����ԭ��������Ŀ������ǡ���ͨ������\n" NOR );      
             	tell_room(environment(me), me->name()+"ͻȻ��ɫ��ü�Ϊ�ѿ�������������˿�����\n" NOR,({ me }));
             	me->receive_damage("neili", 50);
             	me->receive_damage("jingli", 50);
             	me->receive_wound("jing", 20);
             	}           
}