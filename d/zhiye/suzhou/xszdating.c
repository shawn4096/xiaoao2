#include <room.h>

inherit ROOM;

void create()
{
	set("short", "����ׯ����");
	set("long", @LONG
��������ׯ��������֮�أ��������Ǹߴ���������ڷ�
һ�����ֻ���һ�����������ŵڣ�ׯ���ͷ������ںȲ裬������
����������廭��һ���㰸ȼ��̴�����������������š�
LONG
);
        set("objects",([
			"d/motianya/npc/shiqing" : 1,
			"d/motianya/npc/minrou" : 1,
        ]));
		set("exits", ([
			"north" : __DIR__"xszyuanzi",
		]));
		//set("outdoors", "suzhou");
	    set("incity",1);
		setup();
}


