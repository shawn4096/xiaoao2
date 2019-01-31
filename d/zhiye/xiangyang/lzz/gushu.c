// Room: zhengt.c
// Looklove y2k/4/26
// 排名不分前后，纯属搞笑 LInuX@sj

#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",HIG"古树上"NOR);
        set("long", @LONG
这是古树树杈之上，你趴在哪儿，可以轻松看到树下的人来人往。
若你不出声，则没有人能发现你。四周绿叶正好将你覆盖住，风轻轻吹
过，甚是静谧。
LONG
        );
/*
        set("exits", ([
                  "south" : __DIR__"tjing",
        ]));*/

       
	setup();
}
void init()
{
	object me=this_player();
	add_action("do_jump","jump");
	if (me->query_temp("bangjue/askfu"))
	{
		message_vision(HIC"$N刚把身子藏好，忽然听到远处有人走来。\n"NOR,me);
		call_out("do_teach",1,me);
	}
}
int do_jump(string arg)
{

	object me=this_player();
	if (!arg || arg !="down")
	{
		return notify_fail("你要往哪儿跳？\n");
	}
	message_vision("$N纵身而下，跳下古树。\n",me);
	me->move("d/xiangyang/lzz/huayuan");
	return 1;

}

int do_teach(object me)
{
	object huang,huang1,lu1,lu;
	message_vision(HIG"$N顿时一惊,下意识屏住呼吸，这时远处传来两个人说话的声音，由远及近。$N心中大惊，急忙将身形隐入树荫中。\n"NOR,me);

	message_vision(HIC"\n\n\n黄蓉说道，“鲁长老，前一阵我传给你的打狗棒法你练习的怎么样了？”\n"NOR,me);
	message_vision(HIY"\n\n鲁有脚似乎有些窘迫，面红耳赤。黄蓉说道，鲁长老你先练习下，我替你看看。\n这时，黄蓉忽然感觉身体不适，到树荫下稍作休息。\n"NOR,me);
	message_vision(RED"\n\n黄蓉忽然冲树上喝道，谁在树上？给我下来！\n"NOR,me);
	me->delete_temp("bangjue/askfu");
	me->delete_temp("bangjue/asklu");
	me->set_temp("bangjue/cang",1);
}
