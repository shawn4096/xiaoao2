// Room: /u/xdd/gumu/jishi.c
// Modify By River 98/08
inherit ROOM;
#include <ansi.h>
void create()
{
     set("short",HIC"����"NOR);
     set("long", @LONG
һƬ����������ɢ�����Ų���̯λ�������Ƶĵ���������Ҳ�д���Զ�Ĵ�
����Ū���ĸ�����Ʒ��̯����æ��ߺ�ȶ��ۡ�
LONG        );

	set("outdoors","��Ĺ");
    set("objects", ([
              "/d/quanzhen/npc/shangren": 1,
    ]));
	set("exits", ([
		"northwest" : "/d/group/entry/gmchang",
		"south" : "/d/gumu/datiepu",
	//	"northwest" : "/d/group/entry/gmchang",
	]));
	setup();
}
