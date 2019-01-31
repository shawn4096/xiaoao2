#include <ansi.h>
#include <room.h>
inherit ROOM;

string show_hua();

void create()
{
	set("short", "百狐斋");
        set("long", @LONG
这里就是杜老板的百狐斋，其实一看就知道这不过是一间破旧的
草堂， 只见堂内陈设简陋，墙上却挂满了画(hua)，这些都是杜老板
自己画的他平时就靠卖这些画为生。
LONG );
	set("objects", ([
		__DIR__"npc/dufeng" : 1,
	]));

	set("exits", ([
	        "north"  : __DIR__"xiaoxiang2",
	]));

	set("no_fight", 1);

	set("item_desc", ([
		"hua" : (: show_hua :),
	]));

	//set("coor/x", 10);
	//set("coor/y", -140);
	//set("coor/z", 0);
	setup();

}

string show_hua()
{
	return HIW "\n只见每副画所画的均是狐，有白狐、赤狐、黑狐、蓝狐、紫狐\n"
               "……或静、或嬉、或怒、或媚，或狡黠、或机灵、或娇憨，千\n"
               "姿百态，形神兼具。\n\n" NOR;
}
