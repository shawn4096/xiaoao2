// �յ�.c
// �յ�
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short","�ּ�յ�");
	set("long",@long
�������ּ��һ��յأ�һ�߽�����Ϳ����ŵ�һ��ŨŨ���ۻ�ζ�˱Ƕ�
�����ڿյ��������������ݣ����ӵ�ǽ�ڡ��ݶ�������ڴ�С�Ĵ������࣬��
�����Ǽᶨ���ݺ��е�ɽϪ��ɽ���¡�
long);
	set("exits",([
	    "north" : __DIR__"treen2",
           "south" : __DIR__"trees2",
           "northup" : __DIR__"sanroad1",
           "enter" : __DIR__"lgxroom",
	]));
	set("objects",([
	    "kungfu/class/sld/maodongzhu" : 1,
        "kungfu/class/sld/dengbingchun" : 1,
		//"/d/sld/npc/blackjz" : 1,

	]));
	set("outdoors", "������");
	set("no_fight",1);
    set("valid_startroom", 1);
    setup();
     //   "/clone/board/quanzhen_b"->foo();
    //setup();
    call_other( "/clone/board/sld_b", "???" );
}
	    	
