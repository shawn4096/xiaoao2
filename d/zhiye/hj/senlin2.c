// senlin.c
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
       set("short","��Ҷ��");
       set("long", @LONG
���Ǽ�����ɽ���µ�һƬ��Ҷ�֣��������޳�Ⱥ�������̸��ź��һ����
�롣������һ�����ʵ�ɽ��������ɽ�ˣ�ɽ�������ѩ��ɽ��ȴ����������
�����߱��Ǵ��ԭ�������ڵĹ�����������������������������ţ���Ȼ��ʧ
�˵�·��
LONG);
        set("exits", ([
             "east"  : __DIR__"senlin"+(1+random(4)),
             "west"  : __DIR__"senlin"+(1+random(4)),
             "south" : __DIR__"senlin"+(1+random(4)),
             "north" : __DIR__"senlin"+(1+random(4)),               
        ]));
        
        set("objects", ([
                         __DIR__"npc/huilang" : 1,
        ]));

        set("outdoors", "��ɽ");
        set("coor/x",-320);
  set("coor/y",140);
   set("coor/z",0);
   set("coor/x",-320);
  set("coor/y",140);
   set("coor/z",0);
   set("coor/x",-320);
 set("coor/y",140);
   set("coor/z",0);
   setup();           
}

int valid_leave(object me, string dir)
{
	
	 if(!me->query_temp("correct_dir") && userp(me))
         me->set_temp("correct_dir", keys(query("exits"))[random(sizeof(query("exits")))]);
	 
        if( dir != me->query_temp("correct_dir"))
                me->set_temp("ts_sl", 0);
        else    me->add_temp("ts_sl", 1);

        if( me->query_temp("ts_sl") > 5 + random(5) ) {
                me->move(__DIR__"senlin");
                me->delete_temp("ts_sl");
                me->delete_temp("correct_dir");
                return notify_fail("���۵ð���������ҵ�����ȷ�ķ���\n");
        }
        return ::valid_leave(me,dir);
}