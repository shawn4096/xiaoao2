#include <room.h>

inherit ROOM;

void create()
{
	set("short", "����ׯ�ſ�");
	set("long", @LONG
�����ǽ�������������ׯ���ſڵ��������ʯʨ�ӣ���������
ׯ��ɫ���Ժڰ�ɫΪ������ǽ���ߣ����ӳ�Ƭ��ׯ��Ժ���ڰڷ���
�����������ģ�һ�������������ң��ſ����������֡�����ׯ��

LONG
);
        set("objects",([
        //__DIR__"npc/binv" : 2,
        ]));
	set("exits", ([
	"north" : __DIR__"shizilin",
	"south" :__DIR__"xszyuanzi",
        ]));
 	set("outdoors", "suzhou");
   set("incity",1);
	setup();
}


