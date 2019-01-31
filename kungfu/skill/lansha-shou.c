// lansha-shou.c 蓝砂手 血刀门
// Edit By sohu@xojh

#include <ansi.h>
inherit SKILL;
string *du=({
"ice_poison",
"ill_dongshang",
"ill_fashao",
"ill_kesou",
"ill_shanghan",
"ill_zhongshu",
"cold_poison",
"flower_poison",
"rose_poison",
"sanpoison",
"chilian_poison",
"wugong_poison",
"zhizhu_poison",
"xiezi_poison",
"chanchu_poison",
});
mapping *action = ({
([      "action" : "$N跨前一步，双掌陡然攻出，带着丝丝阴风击向$n的$l",
        "force" : 100,
        "attack": 25,
        "dodge" : 15,
        "parry" : 20,
        "damage": 110,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N左掌护胸，右掌掌心带着极寒之气拍向$n的$l",
        "force" : 130,
        "attack": 30,
        "dodge" : 10,
        "parry" : 15,
        "damage": 120,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N双掌拍出满天阴风，忽然右掌悄无声息的拍向$n的$l",
        "force" : 180,
        "attack": 50,
        "dodge" : 20,
        "parry" : 30,
        "damage": 130,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N怪叫一声，身形一跃，左掌快若疾电般击向$n的$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 135,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N阴笑一声，双掌一错，右掌忽然暴长数尺击向$n的$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 235,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N身形急晃，一跃而至$n跟前，右掌带着冲天寒气击向$n的$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 135,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N仰天长啸，双掌掌风似千古不化的寒冰般扑向$n的$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 135,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N身法陡然一变，掌影千变万幻，令$n无法躲闪",
        "force" : 250,
        "attack": 45,
        "dodge" : 15,
        "parry" : 20,
        "damage": 125,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N仰天一声狂啸，双掌携带着万古冰坚直直贯向$n",
        "force" : 330,
        "attack": 35,
        "dodge" : 25,
        "parry" : 20,
        "damage": 115,
        "damage_type" : "瘀伤"
])
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"|| usage == "throwing"; }

int valid_combine(string combo) { return combo == "hongsha-zhang"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练蓝砂手必须空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够，无法练习蓝砂手。\n");

        if ((int)me->query("max_neili") < 800)
                return notify_fail("你的内力太弱，无法练习蓝砂手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("lansha-shou", 1))
                return notify_fail("你的基本手法水平有限，无法领会更高深的蓝砂手。\n");
        if (me->query_skill("xuedao-jing", 1) < 50 )
                return notify_fail("你的本门内功水平有限，无法领会更高深的蓝砂手。\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("lansha-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 50)
                return notify_fail("你的体力太低了。\n");

        if ((int)me->query("neili") < 70)
                return notify_fail("你的内力不够练蓝砂手。\n");

        me->receive_damage("qi", 40);
        me->add("neili", -60);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{

	int level, jiali, time,level2;
	object weapon;

        int lvl;
        int flvl;
	int damage,damage2;
	object target;

        level = (int) me->query_skill("lansha-shou",1);
        level2= (int) me->query_skill("lansha-shou",1);

	if (me->query_skill("poison",1)<100) return;

	if (random(10)>7 
		&& level>=150 
		&& me->query_skill_mapped("force") == "xuedao-jing" )
	{
            victim->receive_damage("qi",random(level)+10,me);
            victim->receive_wound("qi",15 + random(50),me);
            victim->apply_condition(du[random(sizeof(du))], 25);
            victim->apply_condition(du[random(sizeof(du))], 25);
            victim->apply_condition(du[random(sizeof(du))], 25);
            victim->apply_condition(du[random(sizeof(du))], 25);
            victim->apply_condition(du[random(sizeof(du))], 25);
            victim->apply_condition(du[random(sizeof(du))], 25);
			if (!victim->is_busy()) victim->start_busy(2);	
			return HIB "$N" HIB "突然受掌，然后迅速发掌! 掌中尽然有毒砂，这掌风尽然是蓝汪汪之色！\n" HIB "$n" HIB "忽然感到一股莫名的恶心，全身瘫软，嘴皮乌紫。!\n"NOR;
	}


}

string perform_action_file(string action)
{
        return __DIR__"lansha-shou/" + action;
}

