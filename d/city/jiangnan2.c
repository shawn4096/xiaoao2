// Room: /d/city/jiangnan1.c

#include <ansi.h>

#define SHIP_TO __DIR__"jiangbei2"
#define BOAT __DIR__"boat2"

inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();

void create()
{
        set("short", "长江南岸");
        set("long", @LONG
面前是一条波涛翻滚的大江(river)。 浊流滚滚，万舟竞发。两岸渡船来
来往往，江边一长溜摆满了鱼摊，渔家就将船泊在岸边，支一块木板，板上摆
满了活蹦乱跳的鲤鱼。不远处是一个摆渡，不少过江客都在这里等待渡船。
LONG
        );

        set("exits", ([
                "west" : __DIR__"jiangnan",
        ]));

        set("item_desc", ([
                "river" : "近岸处有一叶小舟，也许喊(yell)一声船家就能听见。\n",
        ]));

        set("outdoors", "扬州");
	set("coor/x",110);
	set("coor/y",-160);
	set("coor/z",0);
	setup();
}

void init()
{
        add_action("do_yell", "yell");
        add_action("du_jiang", "dujiang");
}
int do_yell(string arg)
{
	object room, me;
	me = this_player();

	if (arg == "boat") arg = "船家";
	if (arg != "船家") arg = "哇";
	if (me->query("age") < 16  )
		message_vision("$N使出吃奶的力气喊了一声：“" + arg + "”\n", me);
	else if (me->query("neili") > 500)
		message_vision("$N吸了口气，一声“" + arg + "”，声音中正平和地远远传了出去。\n", me);
	else
		message_vision("$N鼓足中气，长啸一声：“" + arg + "！”\n", me);
	if (arg == "船家")
	{
		if (room = load_object(BOAT))
		if (!room->query("start"))
			room->arrive("jiangnan2");
		else if (query("exits/enter"))
			message_vision("岸边一只渡船上的老艄公说道：正等着你呢，上来吧。\n", me);
		else message_vision("江面上远远传来一声：“等等啊，这就来了～～～”\n", me);
	} else message_vision("江面上远远传来一阵回声：“" + arg + "～～～”\n", me);
	return 1;
}

int valid_leave(object me, string dir)
{
	if( dir =="enter" ){
		if (me->query("can_ride")) return 0;
		if (me->query_temp("ride_horse"))
			return notify_fail("骑马上船，你不怕船翻了？\n");
		me->set_temp("side", "jiangnan2");
	}

	return ::valid_leave(me, dir);
}
/*
int du_jiang()
{
        object me = this_player();

        if (!living(me)) return 0;

        write("这里的水太深太急，你渡不过去。\n");
        return 1;

}*/

int du_jiang()
{
        object me = this_player();
        object room;
        int cost = 600;

        if (!living(me)) return 0;
	room = load_object(BOAT);

        if (me->is_busy() || me->is_fighting())
                return notify_fail("你正忙着呢！\n");
	if(me->query_temp("ride_horse"))
		return notify_fail("骑在马上你不能施展「一苇渡江」的绝技 ！\n");
        if (me->query_skill("dodge") < 270)
                return notify_fail("你的修为不够！\n");
        if (me->query("max_neili") < 3500)
                return notify_fail("你的内力修为不够，怎能支持！？\n");
        if (me->query("neili") < 1000)
                return notify_fail("你的真气不够了！\n");
        if (me->query("jingli") < 1200)
                return notify_fail("你的精力不够了！\n");

        if(me->query_encumbrance()/100 > me->query("neili") + cost)
                return notify_fail("你带这么重的包袱，走路都成问题，别说飞了！\n");

        if(query("exits/enter")) return notify_fail("有船不坐，你想扮Cool啊？\n");

	if(room->query("exits/out") ) return notify_fail("江面太宽了，如果没有中途借力的地方根本没法飞越过去！\n");

        me->receive_damage("neili", 300);
        me->receive_damage("jingli", 150);
        tell_room(environment(me), YEL+me->name()+"紧了紧随身物品，紧跟着长袖飘飘，飞身跃渡长江！\n" NOR, ({me}));
        write("你一提内息，看准了江中渡船位置，使出「一苇渡江」轻功想要飞越长江。\n");
        me->move(BOAT);
        me->start_busy(3);
	if (me->query("neili") < 1000 || me->query("jingli") < 1200) {
                write("你还想提气，却发现力不从心了。\n");
                tell_room(environment(me), YEL+me->name()+"长袖飘飘，从江面上飞跃过来，站在船上，大口大口喘着气！\n" NOR, ({me}));
                return 1;
	}
//         tell_room(environment(me), YEL"只见"+me->name()+"，在船上一点，" NOR, ({me}));
        if (me->query("neili") > 100000000){
                me->start_busy(5);
                tell_room(environment(me), YEL"，正要向北跃出，突见船老大一竿子扫出，将！"YEL+me->name()+"打落在江中！\n" NOR, ({me}));
                tell_object(me, "你正要继续跃出，突然小腿一疼，“扑通”一声掉进江水之中！抬起头才发现是船老大用竿子将你扫下船的······\n");
                message_vision(HIC"船老大扯起嗓子骂道：“" + RANK_D->query_rude(me) + "也不睁开眼看看，来来回回这么多三脚猫角色往我这船跳，当老子拼命三郎是好惹的？！？！\n", me);
                tell_object(me, "你吓了一大跳，回头看看······到对岸还远，只有往回游了！\n");
                me->receive_damage("neili", 300);
                me->receive_damage("jingli", 150);
                me->move(__FILE__);
                message_vision(HIC"$N湿漉漉地从江中爬上岸来，叉着腰面对江中渡船叽叽咕咕骂个不停······！\n"NOR,me);
        }

        else {
                me->start_busy(3);
                 tell_room(environment(me), YEL"只见"+me->name()+"长袖飘飘，从江面上飞跃过来，又向北跃出！\n" NOR, ({me}));
                write("你在江中渡船上轻轻一点，又提气飞纵向北岸。\n");
                me->move(SHIP_TO);
                tell_room(environment(me), YEL"只见"+me->name()+"长袖飘飘从对岸跃来，姿态潇洒地落在岸边。\n"NOR, ({me}));
        }

        me->receive_damage("neili", 300);
        me->receive_damage("jingli", 150);
        return 1;
}

