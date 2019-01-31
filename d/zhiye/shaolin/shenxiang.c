// Room: /d/shaolin/shanlu1.c
// Date: YZC 96/01/19

#include <room.h>
inherit ROOM;
#include <ansi.h>
int do_drop();
int do_fang(string arg);
void create()
{
	set("short", "神像");
	set("long", @LONG
这是一座神像的顶部，上面落满了尘土。从这看下去
下面一片空荡荡的。
LONG
	);
	setup();
}

void init()
{
	object me = this_player();
	add_action("do_tiao","jump");
	add_action("do_fang","fang");
	add_action("do_drop","drop");

}

int do_tiao(string arg)
{
	object me=this_player();
    if (arg !="down" && arg !="地面")
		return notify_fail("你要向哪儿跳？");
	
	tell_object(me,HIC+me->query("name")+"嗖的一声飞身跃下，调到大雄宝殿的地上。\n"NOR);
	me->move("d/shaolin/daxiong");
	return 1;

}
int do_drop()
{
	object me=this_player();
	message_vision(HIC"神像之上乃神圣之地，你以为垃圾场啊，乱扔乱放？\n"NOR,me);
    return 1;

}
int do_fang(string arg)
{
	object baitie;
	object me=this_player();
	
	if (!objectp(baitie=present("bai tie",me)))
		return notify_fail("你要放什么到神像上？");

	if (arg !="bai tie")
		return notify_fail("这是神像，不能随便乱扔东西。\n");
	
	tell_object(me,HIC+me->query("name")+"将何足道给你的拜帖挂在神像头顶上，同时嘿嘿冷笑起来。\n"NOR);
	tell_object(me,HIC+me->query("name")+"自言自语道，“这次让这帮子秃驴们够受的。”。\n"NOR);
	tell_object(me,HIC+me->query("name")+"自言自语道，“我可以回去给师傅汇报了，至于什么经在油中就由他去吧“\n"NOR);
	me->delete_temp("kl/baihe/jump");
	me->set_temp("kl/baihe/fangxin",1);
	baitie->move("/d/shaolin/shenxiang");
	return 1;

}
