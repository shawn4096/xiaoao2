//cre by sohu@xojh 2014/9
//chilian.c 赤练神掌绝技
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([	"action" : "$N一招「斜阳照路」，左掌叠于右掌之上，劈向$n",
	"force" : 80,
        "attack": 2,
	"dodge" : 30,
        "parry" : 1,
	"damage": 5,
	"lvl"   : 0,
	"skill_name" : "斜阳照路",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N一招「千山鸟飞绝」，面色凝重，双掌轻飘飘地拍向$n",
	"force" : 100,
        "attack": 8,
	"dodge" : 25,
        "parry" : 3,
	"damage": 30,
	"lvl"   : 20,
	"skill_name" : "千山鸟飞绝",
	"damage_type" : "内伤"
]),
([	"action" : "$N一招「长空明净」，双掌幻化一片掌影，将$n笼罩于内。",
	"force" : 130,
        "attack": 12,
	"dodge" : 43,
        "parry" : 4,
	"damage": 35,
	"lvl"   : 30,
	"skill_name" : "长空明净",
	"damage_type" : "瘀伤"
]),

([	"action" : "$N一招「万水千山」，向$n的$l连击数掌",
	"force" : 150,
        "attack": 15,
	"dodge" : 55,
        "parry" : 8,
	"damage": 50,
	"lvl"   : 40,
	"skill_name" : "万水千山",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N一招「万径人踪灭」，只见一片掌影攻向$n",
	"force" : 180,
        "attack": 22,
	"dodge" : 52,
        "parry" : 0,
	"damage": 30,
	"lvl"   : 60,
	"skill_name" : "万径人踪灭",
	"damage_type" : "瘀伤"
]),

([	"action" : "$N双掌平挥，一招「过关斩将」击向$n",
	"force" : 230,
        "attack": 23,
	"dodge" : 65,
        "parry" : 11,
	"damage": 90,
	"lvl"   : 80,
	"skill_name" : "过关斩将",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N一招「彩云遮月」，只见一片掌影攻向$n",
	"force" : 260,
        "attack": 28,
	"dodge" : 63,
        "parry" : 5,
	"damage": 100,
	"lvl"   : 100,
	"skill_name" : "彩云遮月",
	"damage_type" : "内伤"
]),

([	"action" : "$N施出「高山流水」，右手横扫$n的$l，左手攻向$n的胸口",
	"force" : 280,
        "attack": 25,
	"dodge" : 77,
	"damage": 120,
        "parry" : 12,
	"lvl"   : 120,
	"skill_name" : "高山流水",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N左掌虚晃，右掌一记「夕阳西下」击向$n的头部",
	"force" : 320,
        "attack": 31,
	"dodge" : 80,
        "parry" : 15,
	"damage": 150,
	"lvl"   : 140,
	"skill_name" : "夕阳西下",
        "damage_type" : "瘀伤"
]),
([	"action" : "$N施出「五毒噬体」，双掌同时击向$n的$l",
	"force" : 360,
        "attack": 32,
	"dodge" : 81,
        "parry" : 10,
	"damage": 180,
	"lvl"   : 160,
	"skill_name" : "五毒噬体",
        "damage_type" : "瘀伤"
])
});

int valid_enable(string usage)
{
	return usage == "parry" || usage == "strike";
}

int valid_learn(object me)
{
    /*if (me->query("character") != "心狠手辣") 
                return notify_fail("练五毒神掌必须要心狠手辣，我看你这点做得还不够。\n"); */
	if (!me->query("quest/gumu/wdsz/pass") ) 
               return notify_fail("练五毒神掌必须要李莫愁的亲自指点。\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练五毒神掌必须空手。\n");

        if ((int)me->query_skill("force",1) < 150)
                return notify_fail("你的内功火候不够，无法练五毒神掌。\n");

	if ((int)me->query("max_neili") < 1200)
		return notify_fail("你的内力太弱，无法练五毒神掌。\n");

        if ((int)me->query_skill("strike", 1) < 120)
                return notify_fail("你的基本掌法火候不够，无法练五毒神掌。\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("wudu-shenzhang", 1))
		return notify_fail("你的基本掌法水平有限，无法领会更高深的五毒神掌。\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	string msg;
	level = (int) me->query_skill("wudu-shenzhang",1);
	//夺刺
	if ( me->query_temp("wdsz/duoci")) 
	{
				switch(me->query_temp("wdsz/duoci"))
				{
					
					case 2: msg = HIR"$N身体滴溜溜一转，到了$n身后，左掌顺力拍出，这一招看似平和，实是内涵一股黑气，腥臭无比"NOR; break;
					case 1: msg = HIW"最后$N猛一吐气，双掌有如推门，向外轻轻一推即收，同时一股若隐若现的腥臭气息传来"NOR; break;
					default : msg = HIB"$N突然脚下一晃，欺进$n，右掌一翻，单掌向$p软肋斜拍而去"NOR; break;
				}
				me->add_temp("wdsz/duoci", -1);
				return ([
					"action": msg,
					"force": 250 + random(350),
					"parry": random(20)+10,
					"dodge": random(20)+10,
					"damage": 100 + random(100),
					"damage_type": "瘀伤"
				]);
	}
	//赤练掌
	if ( me->query_temp("wdsz/chilian")) 
	{
				switch(me->query_temp("wdsz/chilian"))
				{
					case 3: msg = HIB"$N突然脚下如凌波，快速欺进$n身侧，紧接着右掌一翻，单掌向$p顶门直拍而下"NOR; break;
					case 2: msg = HIR"$N身体滴溜溜一转，到了$n身后，左掌顺力拍出，这一招看似平和，实是内涵一股黑气，腥臭无比"NOR; break;
					case 1: msg = HIW"最后$N猛一吐气，双掌有如推门，向外轻轻一推即收，同时一股若隐若现的腥臭气息传来"NOR; break;
					default : msg = HIB"$N突然脚下一晃，欺进$n，右掌一翻，单掌向$p软肋斜拍而去"NOR; break;
				}
				me->add_temp("wdsz/chilian", -1);
				return ([
					"action": msg,
					"force": 250 + random(350),
					"parry": random(20)+10,
					"dodge": random(20)+10,
					"damage": 150 + random(100),
					"damage_type": "瘀伤"
				]);
	}
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) {
			
			
			return action[NewRandom(i, 20, level/5)];

		}
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int poison, i;

	poison = (me->query_skill("poison", 1) - victim->query_skill("poison", 1))/3;
	poison += me->query_skill("wudu-shenzhang",1)/15;

	if ( userp(victim)) {
		poison /= 3;
		i = 120;
	}
	else
		i = 50;


	if(me->query_skill("wudu-shenzhang", 1) > 150
	&& me->query_skill("poison", 1) > 50
	&& random(me->query_skill("poison", 1)) > random( victim->query_skill("medicine", 1))
	&& victim->query_condition("snake_poison") < 200
	&& me->query("neili") > 500
	&& random(10)>6
	&& !victim->query("job_npc")) {
		if (me->query("env/五毒神掌") == "五毒") {
			poison += random(poison/2);
			me->add("neili",-100-random(50));
			me->add("jingli",-20-random(30));
			message_vision(BLU"$N阴柔内力一催，手掌上显出五种极其耀眼的颜色！\n"NOR, me);
		}
		victim->add_condition("snake_poison", poison);
		message_vision(BLU"$N不小心为五毒神掌毒所伤，身子一晃，脸上黑气弥漫！\n"NOR, victim);
		if (victim->query_condition("snake_poison") > 180)
			message_vision(HBRED"$N体内积毒已深，恐怕有生命危险！\n"NOR, victim);
		if (userp(me)
		 && userp(victim)
		 && !victim->query_temp("kill_other/"+me->query("id"))
		 && !me->query_temp("other_kill/"+victim->query("id"))
		 && ! me->query_temp("revenge/"+victim->query("id"))
		 && !victim->query_condition("killer")
               && (!me->query_temp("special_die") || !victim->query_temp("special_die")))
			me->add_condition("killer", 5);
	}
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 50)
		return notify_fail("你的体力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练五毒神掌。\n");

	me->receive_damage("jingli", 30+random(20));
	if (me->query("neili")>13)
	{
		me->add("neili", -13);
	}
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"wudu-shenzhang/" + action;
}
