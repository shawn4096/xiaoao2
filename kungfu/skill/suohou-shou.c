// suohou-shou 锁喉擒拿手
// Lklv@SJ 2001.10.05

#include <ansi.h>
#include <combat.h>

inherit SKILL;

string *action_msg = ({
"$N左手扬起，右手伸出，五指曲张，对着$n的颈部便抓。",
"只见一阵劲风直逼向前$N单臂伸出，手指直取$n的哽嗓咽喉。",
"$N左手一掠，将$n防守招数尽格在外门，右手疾探而出对$n的喉头抓到",
"$N身形急跳，早落到$n的身后，一双冰冷的大手抓向$n的后颈",
"$N双臂弯出，柔若无骨，如两条软鞭一般，紧紧缠住$n的脖子不放",
});

int valid_enable(string usage)
{
	return usage == "hand" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
	int lvl;
	lvl = (int)me->query_skill("suohou-shou", 1);

	if ( random(lvl) > 200 && me->query("neili") > 800 && !random(3))
	{
		if ( lvl <= 150) 
		{
			me->add("neili", -50);
			return ([
				"action": HIC"$N右手一抬，势做阴柔，无声无息袭向$n，跟着左爪突然而出，以阳刚之力，左右合击直取$n的喉咙。",
				"damage_type": "内伤"NOR,
				"dodge": 10,
				"parry": 5,
				"damage": 100+random(50),
				"force" : 300,
			]);
		}
		else {
			me->add("neili", -80);
			return ([
				"action":HIY "$N内力勃发，姿势凶狠，眼露凶光，招招不离$n的要害部位,似乎要将$n生吞活剥。\n"
				"$N双手连扬，连出阴招，不离锁喉，撩阴。$n稍有疏忽不免死得惨酷无比。"NOR,
				"damage_type": "抓伤",
				"dodge": 15,
				"parry": 10,
				"damage": 180+random(50),
				"force" : 350,
			]);
		}
	}
	return ([
		"action": action_msg[random(sizeof(action_msg))],
		"damage_type": random(2)?"抓伤":"内伤",
		"dodge": random(20)-10,
		"parry": random(10),
		"damage": 80+random(50),
		"force": 100+random(250),
	]);
}

int practice_skill(object me)
{
	if ( me->query("jingli") < 30)
		return notify_fail("你的体力不够练锁喉擒拿手。\n");
	if ( me->query("neili") < 15)
		return notify_fail("你的内力不够练锁喉擒拿手。\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -5);
	return 1;
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练锁喉擒拿手必须空手。\n");

	if ( me->query("max_neili") < 100)
		return notify_fail("你的内力不够。\n");
	if ( me->query_skill("huntian-qigong", 1) < 30)
		return notify_fail("你的混天气功火候不到。\n");
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"suohou-shou/" + action;
}
