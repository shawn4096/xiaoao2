#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"ǧѰ����"NOR);
        set("long",@LONG
��ʥ����������ǧѰ���У�����������ߵ�һ��������ʮ���㣬
��������ߣ���������С����ͬ���ƴ�����ʽ����������������ֻ��
�����ƶˣ�������פ�����㵹֮�ơ����Ļ����ʷ��Σ��ֶ��㣬�²�
������ʯ���������Ľ���ͷ����ʯʨ���ϲ㶫��������ʯ�ձڣ�����
ǭ������Ӣ������������ġ�����ɽ�����ĸ����֣�ׯ�����棬����
���ǡ�ÿ���������뿪���裬���ð�ɫ����ʯ����һ��
LONG);
        set("outdoors", "������");
        set("exits", ([
                "south" : __DIR__"yz6",
                "north" : __DIR__"yz3",		
        ]));
	
        set("coor/x",-350);
  set("coor/y",-300);
   set("coor/z",20);
   setup();
}