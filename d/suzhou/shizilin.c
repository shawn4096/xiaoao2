#include <room.h>

inherit ROOM;

void create()
{
	set("short", "ʨ����");
	set("long", @LONG
��һ�߽�ʨ���֣��㲻��Ϊ��������԰�ֵ������������۷���ʨ���ֶ�
�϶�ɽ��������ˮ�����С���ɽ������֮�ơ���ɽ���͵��֣�����������ʯ
�����಻�ϣ�����Ī�⡣���֮�䣬���������ɼ���������������Թ�����
�ɵò�Ϊ֮��̾���ѡ�
LONG
	);

	set("exits", ([
	"west" : __DIR__"nandajie1",
	"east" :__DIR__"yanyutang",
			"south" :__DIR__"xszgate",

        "northeast" : __DIR__"zhibaixuan",
        ]));
 	set("outdoors", "suzhou");
   set("incity",1);
	setup();
}


