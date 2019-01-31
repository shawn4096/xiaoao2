// wurou_wan.c 五肉子

#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name(HIG"五露丸"NOR, ({"wulu wan", "wan"}));
	set_weight(150);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "颗");
		set("unique", 1);
		set("drug", 1);
		set("treasure", 1);
		set("long", "这是一颗绿意盎然的丸子，采自大雪山五种动物血肉精华提炼而成，\n"+
			    "乃血刀门秘制丸子，既可以补充水分又可以提高自身最大精力。\n");
		set("value", 5000);
	}
}

int do_eat(string arg)
{
	int force_limit, neili_limit, improve;
	object me = this_player();

	force_limit = me->query_skill("force")* 10 + 20* me->query("age") + me->query("combat_exp") /1000;
	neili_limit = me->query("max_jingli");

	if (!id(arg))
		return notify_fail("你要吃什么？\n");

	if(query("owner") != me->query("id"))
		return notify_fail("这颗五露丸好象不是你得到的吧？\n");

	if (me->query("jingli") < me->query("max_jingli"))
		return notify_fail("你现在气血充盈，恐怕承受不了五露丸的补血功效。\n");
	if (me->query("max_jingli")>(me->query_skill("force")-me->query_temp("apply/force")) * 8)
	{
		return notify_fail("你的最大精力已经超过上限了，无法食用\n");
	}
	if (me->query_condition("medicine" ) > 0) {
		me->add("max_jingli", -20);
		message_vision(HIR"$N吃下一颗五露丸，只觉得肝肠寸断，五脏欲裂，原来服食太急太多，药效适得其反！\n"NOR, me);
		log_file("quest/jingli",sprintf("%-18s误食%s减去精力二十点。\n",
			me->name(1)+"("+capitalize(me->query("id"))+")",name()), me);
	}
	else if (neili_limit < force_limit) {
		if (random(10) > 5) {
			improve = 10 + random(10);
			message_vision(HIY "$N吃下一颗五露丸，顿然间只觉一股气血精气充盈周身。\n" NOR, me);
			me->unconcious();
			me->apply_condition("medicine", 180);
		}
		else {
			improve = 1;
			me->set("jingli", 0);
			message_vision(HIY "$N吃下一颗五露丸，顿然间只觉一股浩荡的真气直冲顶门……\n" NOR, me);
			me->apply_condition("medicine", 60);
		}
		me->add("max_jingli", improve);
		log_file("quest/jingli",sprintf("%-18s吃了%s提升精力%s点。\n",
			me->name(1)+"("+capitalize(me->query("id"))+")",name(), chinese_number(improve)), me);
	} else {
		message_vision(HIY "$N不顾精力修为已经到了极限，吃下一颗五露丸。\n" NOR, me);
		me->unconcious();
	}
	destruct(this_object());
	return 1;
}
