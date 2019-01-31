// qipan.c 棋盘

inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIC"玉石棋盘"NOR, ({ "yushi qipan", "qipan", "qi pan"}));
	set_weight(500);
	set("no_get",1);
	set("no_drop",1);
	set("no_steal",1);
	//set();
	set_max_encumbrance(10000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "个");
		set("long", "一个怪异的大玉石头，上面宛如被刀削平了一般。\n上面纵横交错刻画了一个巨大的棋盘！\n上面摆满了黑白两色棋子,呈胶着状态。\n");
		set("value", 500);
		set("no_steal", 1);

	}
}

//int is_container() { return 1; }

