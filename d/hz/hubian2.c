// /u/beyond/hangzhou/hubian.c ������
// this is made by beyond
// update 1997.6.30
#include <ansi.h>
#include <wanted.h>
inherit ROOM;
void check_trigger();
void on_board();
void arrive();
void close_passage();
void reset();
#include "/d/hz/hubianhead.c"
void create()
{
        set("short",GRN"������"NOR);
        set("long", @LONG
��������ɽ��ˮ�㣬�̲�����������ɽɫ����ӳ��Ȥ�����ۺ������羵
���У������������续���Ρ�����֮�����������Թ����������ǳ����ޡ�
�����ġ��㡢�ᡢ�������������δ���ʫ�������ġ�ˮ�������緽�ã�ɽɫ
���������棬�������������ӣ���ױŨĨ�����ˡ�һʫ���������������ľ�
ɫ�������쾡�¡�
LONG
        );
	set("objects",([
		__DIR__"npc/jian-ke" : 2,
	]));

        set("exits", ([
		"north" : __DIR__"hggyu",
		"east" : __DIR__"hubian1",
		"south" : __DIR__"hupao",
	]));	
	set("outdoors", "����");

	setup();
}



