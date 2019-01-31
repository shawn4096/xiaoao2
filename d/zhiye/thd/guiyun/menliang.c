//新增门梁
//menliang.c 增加情节道具房间，不影响正常地图 by sohu@xojh
#include <ansi.h>
inherit ROOM;
int do_jump(string arg);
int story1(object me);
int story2(object me);
int do_look(string arg);
void create()
{
	set("short","门梁");
	set("long",@LONG这是连接中厅与后厅的门廊上的一根横梁，门廊高耸，灯光昏暗。
实乃是藏身的好地方，从这里向北望去，却见从屋内透过灯光，一位极为漂亮的妙龄
少女和一群丫鬟正围坐在一起。
LONG
);
	/*  set("object",([
	__DIR__"obj/luchenfen.c" :     1,
	]));  
	set("exits",([
		"east" : __DIR__"zoulang2",
		"south" : __DIR__"houting",
        "north" : __DIR__"wofang1",
	]) );*/
	set("no_clean_up",0);
	set("indoors", "归云庄");
	setup();
}
void init()
{
	//增加判断
	
	if (this_player()->query_temp("slbw/askguo3"))
	{ 
		add_action("do_look","toukan");
		}
	add_action("do_jump","jump");
	add_action("do_jump","tiao");
	
}

int do_look(string arg)
{
	object me = this_player();

	if (me->is_busy() || me->is_fighting())	return notify_fail("你正忙着呢！\n");
	
	if (arg == "屋内"||arg == "indoors"||arg == "里屋" )
	{
		message_vision(HIC"$N用手指戳破窗户上窗纸，向屋内看去。\n"NOR, me);
		call_out("story1",5,this_player());
		return 1;
	}
	return 0; 
}

int do_jump(string arg)
{
	object me = this_player();

	if (me->is_busy() || me->is_fighting())	return notify_fail("你正忙着呢！\n");
	
	if (arg == "down" )
	{
		message_vision(HIC"$N从门廊上轻轻跃了下来。\n"NOR, me);
		me->move("/d/thd/guiyun/zoulang3");
		return 1;
	}
	return 0; 
}

int story1(object me)
{
    
    message_vision(HIG"\n等不到小半个时辰，只听得墙外喀的一声微响，$N缩在屋檐之后，只见围墙外跃进两条黑影，瞧身形正是两个乞丐。\n"
	+"两丐走到楼下，口中轻声吹哨，一名丫鬟揭开竹帘，说道：“是丐帮的英雄到了么？请上来罢。”。\n"
		   +"其中一个年龄较老的乞丐说道：“在下姓黎，这是我的师侄，名叫余兆兴。”\n"
		   +"\n\n程大小姐道：“原来是黎前辈，余大哥。丐帮众位英雄行侠仗义，武林中人人佩服，小女子今日得见两位尊范，甚是荣幸。请坐。”\n"
		   +"\n黎生又道：“姑娘请到令堂房中歇宿，这几位尊使也都带了去，在下自有对付那狂徒的法子。”程大小姐道：“晚辈虽然武艺低微，\n"
		   +"这事要老前辈一力承当，晚辈怎过意得去？”\n"
		   +"\n\n黎生道：“我们洪帮主与贵派老教主王真人素来交好，大家都是一家人，姑娘何必分甚么彼此？”程大小姐本来似乎跃跃欲试，但听黎生\n"
		   +"这么说了，不敢违拗，行了个礼，说道：“那么一切全仗黎老前辈和余大哥了。”说罢，带了丫鬟盈盈下楼而去。\n"
		   +HIW"\n\n黎生走到小姐床边，揭开绣被，鞋也不脱，满身肮脏的就躺在香喷喷的被褥之上，对余兆兴道：“你下楼去，和大伙儿四下守着，不得\n"
		   +"我号令，不可动手。”余兆兴答应了而去。黎生盖上绸被，放下纱帐，熄灭灯烛，翻身朝里而卧。\n", me);
		   call_out("story2",5,this_player());
    return 1;

}
int story2(object me)
{

    message_vision(HIY"\n\n约莫过了一个更次，听得前面当铺中的更夫“的笃、的笃、当当当”的打过三更，接着“拍”的一声，花园中投进一颗石子来。\n"
	                  +"过得片刻，围墙外窜进八人，径跃上楼，打着了火折子，走向小姐床前，随即又吹熄火折。就在这火光一闪之际，看清来人的形貌，\n"
		              +"\n\n原来都是欧阳克那些女扮男装、身穿白衣的女弟子。四名女弟子走到床前，揭开帐子，将绸被兜头罩在黎生身上，牢牢搂住，\n"
		              +"另外两名女弟子张开一只大布袋，抬起黎生放入袋中，抽动绳子，已把袋口收紧。众女抖被罩头、张袋装人等手法熟练异常，”\n"
		              +"想是一向做惯了的，黑暗之中顷刻而就，全没声响。四名女弟子各执布袋一角。抬起布袋，跃下楼去。\n"
	                  , this_player());
    me->delete_temp("slbw/askguo6");
	me->delete_temp("slbw/tiaoliang");
	me->set_temp("slbw/askcheng",1);
    return 1;

}
