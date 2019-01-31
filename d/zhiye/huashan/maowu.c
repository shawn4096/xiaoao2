// Room: /d/huashan/maowu.c
// Date: Look 99/03/25
#include <ansi.h>

inherit ROOM;
string look_gang();
string look_guo();
int do_get(string arg);

void create()
{
	set("short","茅屋");
	set("long",@long
这是一间很普通的茅屋，茅屋的四周有一圈篱笆墙，墙边有一个大缸水缸
(gang)，水缸上面有一个大盖子(gaizi)。水缸的旁边是一道木门,上面上了一
把锁(lock)，很显然主人出门去了。篱笆院内有一个石桌(desk)，上面密密麻
麻的不知是刻了些什么东西。
long);
	set("exits",([
	"southeast" : __DIR__"v-road-1",
]));
	set("item_desc",([
	"gaizi" : "这是用一棵整木做的大木盖，上面有一个把手。\n",
	"lock" : "锁上落满了灰尘，显然主人有很长时间不在了。\n",
	"desk" : "你仔细看去，上面竟然刻满了一道道的横线竖线，竟然是一个围棋盘。旁边放了一盘"+HIR+"山野果"NOR"(shanyeguo)。\n",
	"gang" : (: look_gang :),
	"shanyeguo" : (: look_guo :),
]));
	set("outdoors", "华山");
	set("guo",4);
	setup();
}
string look_gang()
{	
	object ob = this_object();
	if( ob->query("xian") == 0 )
	return("这是一个大水缸。\n");
	if( ob->query("xian") == 1 ) {
	if( ob->query("have_water") == 1)
	return("你看到水缸里盛满了清水。\n");
	if( ob->query("have_water") == 0 )
	return("你看到水桶里面的水已经干了。\n");
	}
}

void init()
{
	add_action("do_xian", "xian");
	add_action("do_fill","fill");
	add_action("do_close", "close");
	add_action("do_follow", "follow");
	add_action("do_get","na");
}
int do_xian(string arg)
{
	object me = this_player();
	object ob = this_object();
	if(!living(me) ) return 0;

        if (me->is_busy() || me->is_fighting())
	return notify_fail("你正忙着哪！\n");

	if(!arg || arg =="" || arg !="gaizi")
	return notify_fail("你要干什么？\n");

	if(ob->query("xian") > 0 ) {
	write("盖子已经是打开的了。\n", me);
	return 1;}

	if(arg == "gaizi") {
	message_vision("$N把水桶盖子掀了开来。\n", me);
	ob->set("xian", 1);
	if( ob->query("have_water") == 1 ) {
	write("你看到桶里的水已经是满的了。\n" , me);
	return 1; }
	if( ob->query("have_water") == 0 ) {
	write("你看到水桶里面的水已经干了。\n", me);
	return 1; }
	}
}

int do_fill(string arg)
{
	object me = this_player();
	object ob = this_object();
	object tong;
	tong = present("shui tong", me);
	if(!living(me) ) return 0;

        if (me->is_busy() || me->is_fighting())
	return notify_fail("你正忙着哪！\n");

	if(!arg || arg =="" || arg !="gang")
	return notify_fail("你要干什么？\n");
	
	if(arg =="gang" && present("shui tong", me) ) {
	if( ob->query("xian") < 1) {
	write("你还没有掀开水桶盖呢，怎么把小桶里的水到进大桶里？\n", me);
	return 1; }
	if( tong->query("water") < 1) {
	write("小桶里面没有水，你拿什么倒进大缸里？\n", me);
	return 1; }
	if( ob->query("have_water") == 1) {
	write("缸里的水已经是满的了。\n" , me);
	return 1; }
	message_vision("$N把小桶里面的水到进了大缸里面。\n", me);
	me->set_temp("fill", 1);
	tong->set("long","一个用木头制成的小水桶。\n");
	tong->set("weight",180000);
	tong->set("water", 0);
	ob->set("have_water", 1);
	call_out("do_yaba", 2, me);
 	return 1; }                                                              
}

int do_close(string arg)
{
	object me = this_player();
	object ob = this_object();

	if(!living(me) ) return 0;

        if (me->is_busy() || me->is_fighting())
	return notify_fail("你正忙着哪！\n");

	if(!arg || arg =="" || arg !="gaizi")
	return notify_fail("你要干什么？\n");

	if( arg == "gaizi") {
	if( ob->query("xian") == 0 ) {
	write("盖子已经是盖好的了。\n", me);
	return 1; }
	else {
	write("你将盖子盖好。\n", me);
	ob->set("xian", 0);
	return 1; }
	}
}
int valid_leave(object me,string dir)
{
	object room;
	room = find_object(__DIR__"maowu");
	remove_call_out("do_yaba");
	if(!(room=find_object(__DIR__"maowu")))
	room=load_object(__DIR__"maowu");
	if(room=find_object(__DIR__"maowu")) {
	call_out("do_clear", 0, room);
	call_out("do_back", 0, me);
	}
        return ::valid_leave(me, dir);
}

int do_follow(string arg)
{
	object me, room;
	me = this_player();
	room = find_object(__DIR__"maowu");
	if(!living(me) ) return 0;

        if (me->is_busy() || me->is_fighting())
	return notify_fail("你正忙着哪！\n");

	if(!arg || arg =="" || arg !="yaba")
	return notify_fail("你要干什么？\n");

	if( me->query_temp("fill") == 0) 
	return notify_fail("你要干什么？\n"); 

	if( !present("yaba", environment(me)) )
	return notify_fail("你要干什么？\n"); 

	if(arg == "yaba" ) {
	message_vision("$N决定跟哑巴一起行动。\n", me);
	message_vision("哑巴身行腾空而起，带着$N越到一条山壁小路上。\n", me);
	call_out("do_back", 0 , me);
	if(!(room=find_object(__DIR__"maowu")))
	room=load_object(__DIR__"maowu");
	if(room=find_object(__DIR__"maowu")) {
	call_out("do_clear", 0, room);
	}
	me->move(__DIR__"place");
	me->delete_temp("fill");
	return 1;
	}
}

void do_back()
{
	if(present("yaba",this_object())) 
	destruct(present("yaba", this_object()));
}
void do_yaba()
{
	object me = this_player();
	object ob = this_object();
	write("你刚一转身，突然看见了一个人站在你的身后，吓了你一大跳。\n", me);
	ob=new(__DIR__"npc/yaba")->move(this_object()); 
}
void do_clear(object room)
{
		room->set("have_water", 0);
}
string look_guo()
{
	object me=this_player();
	write("这是一盘香喷喷的山野果，总共有四五个放在盘子中，显然是刚洗过的样子。香脆诱人。\n");
	me->set_temp("quest/hs/houerjiu/lookguo",1);
	return "";

}
int do_get(string arg)
{
	object me=this_player();
	object guo;
	guo=new("d/huashan/npc/obj/shanyeguo");
	if (!me->query_temp("quest/hs/houerjiu/lookguo"))
	{
		return notify_fail("你要拿什么？");
	}
	if (!arg || arg!="山野果") return 0;
	
	if (this_object()->query("guo")<1)
	{
			write("盘子中的果子已经被别人都拿走了。\n");
			return 1;
	}
		message_vision("$N偷偷的向四周瞅了瞅，发现没人后从桌子上拿起一个山野果塞入口袋内。\n",me);
		
		guo->move(me);
		this_object()->add("guo",-1);
		return 1;
	
}