// ITEM: /d/huashan/obj/zhengqijue.c
// Date: Look 99/03/25

inherit ITEM;

void create()
{
	set_name( "正气诀要", ({ "shu", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一册华山派正气诀上册。上面画满了各种打坐吐呐的姿势。\n");
        set("value", 50);
		set("material", "paper");
		set("skill", ([
			"name":	"zhengqi-jue",	// name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost":	20+random(20),	// jing cost every time study this
			"difficulty":	30,	// the base int to learn this skill
			"max_skill":	200	// the maximum level you can learn
		]) );
	}
}
void init()
{
	if (environment() == this_player())
		add_action("do_du", "read");
}

int do_du(string arg)
{
	
	object me = this_player();
       int lv;
	
	if (!id(arg)) 
		return notify_fail("你要读什么？\n");

	if ( me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢。\n");	

	if ( me->query("neili") < 100 )
		return notify_fail("你的真气不够。\n");

	if (environment(me)->query("pigging"))
		return notify_fail("你还是专心拱猪吧！\n");

	if (environment(me)->query("pending"))
		return notify_fail("此地不宜研习「正气诀」！\n");

	if (environment(me)->query("sleep_room"))
		return notify_fail("卧室不宜修练，会影响别人休息。\n");
 
	if (environment(me)->query("no_fight"))
		return notify_fail("此地不宜研习「正气诀」！\n");

	if ( me->query("jing") < 40 )
		return notify_fail("你的精太少了，不够研读「正气诀」。\n");
	if ( me->query_skill("literate", 1) < 10 )
		return notify_fail("你读书写字的知识太少了，赶紧学点文化知识吧。\n");
	if ( me->query_skill("zhengqi-jue", 1) > 200 )
		return notify_fail("你研读了一会儿，但是发现上面所说的对你而言都太浅了，没有学到任何东西。\n");
	
	tell_object(me, "你仔细研读着「正气诀」的精妙之处，感觉浩然正气油然而生。\n");
	me->receive_damage("jing", random(50) );
	me->improve_skill("zhengqi-jue", me->query_int());
	return 1;
}