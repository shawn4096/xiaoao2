#include <room.h>

inherit ROOM;

void create()
{
	set("short", "����ׯԺ��");
	set("long", @LONG
Ժ�����ǿ�����ǽ����ڷ���һ���ŵ�ľ׮(zhuang)������������޲�
�е���������ϵ�Ʒ�����������˲���ʯ��(shisuo)��ɳ����һ���ŵı���
���Ӱڷ��˲��ٽ���������
LONG
);
        set("objects",([
        //__DIR__"npc/binv" : 2,
        ]));
	set("exits", ([
	"north" : __DIR__"xszgate",
	"south" :__DIR__"xszdating",
        ]));
 	set("outdoors", "suzhou");
   set("incity",1);
	setup();
}


