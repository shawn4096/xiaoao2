//huanxidong1.c
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "合欢洞");
        set("long", @LONG
这是血刀门内的修欢喜禅之地，洞内传来一阵阵的靡靡之音，
不时传来女性婉转承和的声音和男人的暗哑嘶吼声，令人不由地
血脉愤张。墙上绘制了很多副男女交合的图画(hua)，每一张都令
人遐想，思绪万千，神魂颠倒，欲罢不能。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "east"   : __DIR__"huanxidong2",
			"south"   : __DIR__"kengdao4",
			"west"   : __DIR__"huanxidong3",
			"north"   : __DIR__"huanxidong4",
        ]));
        set("item_desc", ([
            "hua"   : "传自古印度的古老男女双修之术，为修欢喜禅之人的至宝。\n",
        ]));
        set("objects",([
                __DIR__"obj/bed" : 1,
        ]));
		create_door("south", "小门", "north", DOOR_CLOSED);

        setup();
}
void init()
{

	add_action("do_canchan","canchan");
}
//修炼欢喜禅闭关前，必须血战，然后闭关
int do_canchan(string arg)
{
	object me;
	me=this_player();


}