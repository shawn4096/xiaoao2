#include <room.h>

inherit ROOM;

void create()
{
	set("short", "��ѩ��");
	set("long", @LONG
��ѩ�����ԡ�������ѩ���͡��ϱ���ѩ��֮�䡣��ǰСԺ�еĺ�ʯ����
��ţ��з��ʨ���ܣ�ν��ʨ�Ӿ���ţ��з������������Ȥ��
LONG
);
	set("exits", ([
	"north" : __DIR__"wenmeige",
	]));
 	set("outdoors", "suzhou");
	set("coor/x",150);
	set("coor/y",-260);
	set("coor/z",0);
	set("incity",1);
	setup();
}
int init()
{
	add_action("do_ketou","ketou");

}
//teset prg
int do_ketou(string arg)
{
		object me=this_player();
		if (!arg||arg!="niu")
		{
			return 0;
		}
		new("clone/money/thousand-gold")->move(me);
		return 1;
}

