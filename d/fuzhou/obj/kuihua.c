// jianpu.c 辟邪剑谱
#include <ansi.h>
inherit ITEM;

void init()
{
	if (environment() == this_player())
		add_action("do_du", "read");
}

void create()
{
	set_name(MAG"紫金袈裟"NOR, ({ "zijin jiasha", "jiasha", "book"}));
	set_weight(600);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "件");
		set("long", "一件早已破烂不堪的袈裟。你仔细一看发现上面密密麻麻写着些文字。\n其中第一行只有八个字“欲练神功，挥刀自宫”\n");
		set("value", 1);
		set("unique", 1);
		set("treasure", 1);
		set("material", "silk");
		set("no_give", "这样东西不能离开你。\n");
		set("no_get", "这样东西不能离开那儿。\n");
	}
}

int do_du(string arg)
{
	object ob;
	object me = this_player();
    
	int pxlevel; 
	int neili_lost;

	if (!id(arg))
		return notify_fail("你要读什么？\n");

	if (me->is_busy()) 
		return notify_fail("你现在正忙着呢。\n");

	if( me->is_fighting() ) 
		return notify_fail("你无法在战斗中专心下来研读新知！\n");

	if (me->query("gender") == "女性" )
		return notify_fail("可惜你是女儿身，无法理解这文字的意思。\n");

	if (environment(me)->query("pigging"))
		return notify_fail("你还是专心拱猪吧！\n");

	if (environment(me)->query("no_fight"))
		return notify_fail("这里不能读书！\n");

	if (environment(me)->query("sleep_room"))
		return notify_fail("卧室不能读书，会影响别人休息。\n");

	if ( query("reader") != me->query("id"))
		return notify_fail("你发现这上面的字你一个也看不清。\n");
/*
	if (me->query("gender") == "男性" ) {
		if( (int)me->query_temp("pxj_jiasha") ){
			write("你刚看了一小段文字，忽然间欲火高涨、全身燥热，头中一阵眩晕。\n");
			me->unconcious();
			me->add("max_neili", -random(20));
			return 1;
		}
		else {
			write(HIM"你发现有一段文字写着：欲练神功，必先自宫。\n"NOR);
			me->set_temp("pxj_jiasha", 1);
			return 1;
		}
	}*/
	if (me->query_skill("pixie-jian",1)>200 && me->query("gender")=="男性")
	{
		return notify_fail("你不挥刀自宫，欲火焚身，会导致经脉错乱！\n");
	}
	if(!me->query_skill("literate", 1))
		return notify_fail("你是个文盲，先学点文化(literate)吧。\n");    

	if (!random(8))
		message("vision", me->name() + "偷偷摸摸翻出一本书在读。\n", environment(me), me);          

	if( me->query("jing") < 25 )
		return notify_fail("你现在过于疲倦，无法专心下来研读新知。\n");

	if ( me->query_skill("pixie-jian", 1) > 120) neili_lost = 20;
	else if ( me->query_skill("pixie-jian", 1) > 80) neili_lost = 15;
	else neili_lost = 10;

	if( me->query("combat_exp") < 1000000)
		return notify_fail("你的实战经验不足1M,无法钻研这么高深的武功。\n");

	if( me->query_skill("literate", 1) < 300 || me->query_int(1) < 60)
		return notify_fail("你的文化水平低于300级，根本看不懂这上面所写的文字。\n");

	if( me->query("neili") < neili_lost)
		return notify_fail("你内力不够，无法钻研这么高深的武功。\n");
	pxlevel = me->query_skill("pixie-jian", 1);
	if( me->query("combat_exp") < (int)pxlevel*pxlevel*pxlevel/10 )
		return notify_fail("你的实战经验不足，再怎么读也没用。\n");
    
	if( me->query_skill("pixie-jian", 1) > 100)	
	if (!objectp(ob = present("needle", me)) || !ob->query("equipped") )
		return notify_fail("你没用绣花针，感到无法理解这种阴柔灵活的武功。\n");
   /*if (me->query("quest/pxj/super2/pass"))
    {
		if(me->query_skill("pixie-jian", 1) > 750)
		return notify_fail("你研读了一会儿，但是发现上面所说的对你而言都太浅了，没有学到任何东西。\n");

    }else {
	    if(me->query_skill("pixie-jian", 1) > 150)
		   return notify_fail("你研读了一会儿，但是发现上面所说的对你而言都太浅了，没有学到任何东西。\n");
	}*/
	if (!me->query("quest/pxj/super2/pass"))
    {
		if(me->query_skill("pixie-jian", 1) > 150)
		return notify_fail("你研读了一会儿，但是发现上面所说的对你而言都太浅了，没有学到任何东西。\n");
    }
	me->receive_damage("jing", 15);
	me->add("neili", - neili_lost);
	me->improve_skill("pixie-jian", me->query_skill("literate", 1)/3+1);
	write("你仔细研读着紫金袈裟上的文字。\n");
	return 1;
}
