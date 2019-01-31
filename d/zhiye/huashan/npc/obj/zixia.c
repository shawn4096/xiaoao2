// ITEM: /d/huashan/npc/obj/zixia.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ITEM;

void create()
{
    set_name(MAG"紫霞秘籍"NOR, ({ "zixia miji", "miji", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("no_get", "这样东西不能离开那儿。\n");
		set("no_drop", 1);
		set("no_give", 1);
		set("no_stealing", 1);
		set("long", "'华山九功，紫霞第一'，这是一册华山派的紫霞神功秘籍。\n");
        set("unique", 1);
		set("treasure",1);
		set("value", 500);
		set("material", "paper");
		set("skill", ([
            "name": "zixia-gong",   // name of the skill
			"exp_required":	0,	// minimum combat experience required
			"jing_cost":	40,	// jing cost every time study this
			"difficulty":	30,	// the base int to learn this skill
			"max_skill":	350	// the maximum level you can learn
		]) );
	}
	setup();
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

	if ( !me->query("quest/huashan/zixia/pass") )
		return notify_fail("你是怎么得到「紫霞秘籍」的啊？\n");

	if ( query("owner") != me )
		return notify_fail("你是怎么得到「紫霞秘籍」的啊？\n");

	if ( me->query("neili") < 1500 )
		return notify_fail("你的真气不够。\n");

	if (environment(me)->query("pigging"))
		return notify_fail("你还是专心拱猪吧！\n");

	if (environment(me)->query("pending"))
		return notify_fail("此地不宜研习「紫霞秘籍」！\n");

	if (environment(me)->query("sleep_room"))
		return notify_fail("卧室不宜修练，会影响别人休息。\n");
 
	if (environment(me)->query("no_fight"))
		return notify_fail("此地不宜研习「紫霞秘籍」！\n");

	if ( me->query("jing") < 40 )
		return notify_fail("你的精太少了，不够研读「紫霞秘籍」。\n");

	if ( me->query_skill("zixia-gong", 1) > 250 )
		return notify_fail("你研读了一会儿，但是发现上面所说的对你而言都太浅了，没有学到任何东西。\n");
	
	tell_object(me, "你仔细研读着「紫霞秘籍」的精妙之处。\n");
	me->receive_damage("jing", random(30) );
	me->improve_skill("zixia-gong", me->query_int());
	return 1;
}