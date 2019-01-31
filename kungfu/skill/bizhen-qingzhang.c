#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N身形急晃，一跃而至$n跟前，右掌带着切骨之劲砍向$n的$l",
        "force" : 180,
        "dodge" : 25,
        "parry" : 17,
        "damage": 19,
        "lvl"   : 0,
        "damage_type" : "内伤"
]),
([      "action" : "$N飞身跃起，双掌至上而下斜砍而出，顿时万千道掌寒劲从四面八方席卷$n",
        "force" : 240,
        "dodge" : 25,
        "parry" : 27,
        "damage": 25,
        "lvl"   : 30,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N平掌为刀，斜斜砍出，幻出一道道刚猛的掌劲如飓风般裹向$n的全身",
        "force" : 330,
        "dodge" : 36,
        "parry" : 35,
        "damage": 39,
        "lvl"   : 60,
        "damage_type" : "内伤"
]),
([      "action" : "$N反转右掌护住全身，身形猛跃至$n面前，力注左掌，横向$n拦腰砍去",
        "force" : 410,
        "dodge" : 81,
        "parry" : 62,
        "damage": 53,
        "lvl"   : 90,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N右掌后撤，手腕一翻，猛地挥掌砍出，幻出一道无比凌厉的掌劲直斩向$n的$l",
        "force" : 460,
        "dodge" : 35,
        "parry" : 47,
        "damage": 78,
        "lvl"   : 120,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N双手挥舞出，形成一个大圈，一股劲气澎湃汹涌而来，逼得$n踉踉后退",
        "force" : 520,
        "dodge" : 45,
        "parry" : 40,
        "damage": 85,
        "lvl"   : 150,
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { 
	if (this_player()->query("quest/xkx/bzqz/pass"))
		return usage=="strike" || usage=="parry";
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练碧针清掌必须空手。\n");

        if (!me->query("quest/xkx/bzqz/pass"))
                return notify_fail("你尚未学会碧针清掌。\n");

        if ((int)me->query("max_neili") < 2500)
                return notify_fail("你的内力太弱2500，无法练习碧针清掌。\n");

        if ((int)me->query_skill("strike", 1) < 180)
                return notify_fail("你的基本掌法火候不够，无法练习碧针清掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("bizhen-qingzhang", 1))
                return notify_fail("你的基本掌法水平有限，无法领会更高深的碧针清掌。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level,j;
        string msg;
        level = (int) me->query_skill("bizhen-qingzhang",1);
        for (i = sizeof(action); i > 0; i--) 
		{
            if (level > action[i - 1]["lvl"])
			{
				j = NewRandom(i, 20, level/5);
				if (me->query_temp("bzqz/pengpai"))
				{
					return ([  
						"action": HIC+action[j]["action"]+NOR,
						"lvl": action[j]["lvl"],
						"force" : 150 + random(100),
						"dodge": random(30)- 5 ,
						"damage": 220 + random(50),
						"parry": random(150),
						"damage_type" : random(2)?"瘀伤":"内伤",
					]);
				}
				else {
					return ([  
						"action":action[j]["action"],
						"lvl": action[j]["lvl"],
						"force" : 50 + random(50),
						"dodge": random(20),
						"damage": 120 + random(50),
						"parry": random(50),
						"damage_type" : random(2)?"瘀伤":"内伤",
					]);

				}
			}

        }

}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 100)
                return notify_fail("你的体力太低了。\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("你的内力不够练碧针清掌。\n");

        me->receive_damage("qi", 80);
        me->add("neili", -80);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus < 100) return 0;

        if (random(me->query_skill("force")) > victim->query_skill("force") / 5)
        {
                victim->receive_wound("qi", (damage_bonus - 100) / 2,me);
                return HIR "只听" + victim->name() +
                       HIR "前胸“喀嚓”一声，竟像是肋骨碎断的声音！\n" NOR;
        }else if (random(me->query_str(1)) > victim->query_str(1) / 2
			&&me->query_temp("bzqz/bizhen"))
        {
			   victim->receive_wound("qi", (damage_bonus - 100) / 4,me);
               victim->add_condition(1);
			   return victim->name() + HIY"一时不查，为碧针劲气所伤！\n" NOR;

        }
}

string perform_action_file(string action)
{
        return __DIR__"bizhen-qingzhang/" + action;
}
