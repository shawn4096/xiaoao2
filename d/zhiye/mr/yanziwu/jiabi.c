// /u/beyond/mr/jiabi.c
// this is made by beyond
// update 1997.6.20
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short",HIW"夹壁"NOR);
	set("long",@long
这是书架后面的一道夹壁，要用力推开书架的后面。才有可能出去。
书架背后摆满了一些常见秘籍，乃是慕容核心弟子修行之秘密所在。在左
侧的一面墙上，描绘有一副图，定睛看去乃是一副经络运行图（picture）。
long);
	set("exits",([
             "north" : __DIR__"hssg",
	]));
	set("item_desc",([
		"picture" : "这幅图乃是慕容核心弟子参演慕容心法的经络图，凡慕容弟子当在此认真研究(yanjiu)。\n"
	]));
	setup();
}

void init()
{
	
	add_action("do_push", "push");
	add_action("do_read", "yanjiu");
}

int do_push(string arg)
{
	object me;
	me = this_player();

	if (arg !="shujia") 
		return notify_fail("你要干什么？\n");
	if( arg=="shujia"){
		write("你推了一下书架，书架向两边一移。\n");
		message("vision", me->name() + "身行一闪突然不见了。\n", environment(me), ({me}) );
		me->move(__DIR__"shufang");
		message("vision", me->name() + "走了过来。\n", environment(me), ({me}) );
	}
	return 1;
}

int get_object(object ob)
{
        if(userp(ob))
        return 1;
        return 0;
}

int valid_leave(object me, string dir)
{
	mapping myfam;
	object *obj;
     
	myfam = (mapping)me->query("family");
     
	if ( myfam && myfam["family_name"] != "姑苏慕容" &&dir=="north") {
		return notify_fail("一位慕容家丁忽然从阴暗处跳了出来，拦住了你说道：擅闯还施水阁者死！！\n说完，那位家丁身形一晃，又退回暗处。\n");
	}
     
	obj = filter_array(deep_inventory(me),(:get_object:));
	if( sizeof(obj) && dir=="north" ){
		tell_object(me,"你一不小心，被门槛绊倒了。\n");
		obj[0]->move(environment(me));
		me->unconcious();
		return 0;
	}
	return ::valid_leave(me, dir);
}
int do_read(string arg)
{
	object me=this_player();	
	if (!arg||arg!="picture") 
		return notify_fail("你要读什么？\n");

	if ( me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢。\n");	

	if ( me->query("neili") < 100 )
		return notify_fail("你的真气不够。\n");

	if (environment(me)->query("pigging"))
		return notify_fail("你还是专心拱猪吧！\n");

	if (environment(me)->query("pending"))
		return notify_fail("此地不宜研习「紫氤吟」！\n");

	if (environment(me)->query("sleep_room"))
		return notify_fail("卧室不宜修练，会影响别人休息。\n");
 
	if (environment(me)->query("no_fight"))
		return notify_fail("此地不宜研习「紫氤吟」！\n");

	if ( me->query("jing") < 40 )
		return notify_fail("你的精太少了，不够研读「紫氤吟」。\n");
	if ( me->query_skill("literate", 1) < 10 )
		return notify_fail("你读书写字知识太少了，赶紧学点文化知识吧。\n");
	if ( me->query_skill("douzhuan-xingyi", 1) < 100 )
		return notify_fail("你的斗转星移连100级都不到，基本就是皮毛，参悟也参悟不出什么内容来。\n");
	if ( me->query_skill("murong-xinfa", 1) > 200 )
		return notify_fail("你研读了一会儿，但是发现上面所说的对你而言都太浅了，没有学到任何东西。\n");
	tell_object(me, "你仔细研读着墙上的「慕容心法」的精妙之处。\n");
	if ( me->query_skill("murong-xinfa", 1) > 150 )
	{
		me->receive_damage("jing", 10+random(50) );
		me->improve_skill("murong-xinfa", (int)me->query_int()/4);
	}else if (me->query_skill("murong-xinfa", 1) > 100)
	{
		me->receive_damage("jing", random(50) );
		me->improve_skill("murong-xinfa", (int)me->query_int()/3);
	}
	return 1;
}