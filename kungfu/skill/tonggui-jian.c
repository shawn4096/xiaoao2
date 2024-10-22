#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N纵步上前，手中$w斜斜刺出，竟似不要命一般，疾斩$n而去",
        "force" : 290,
        "attack": 171,
        "parry" : -240,
        "dodge" : -231,
        "damage": 260,
        "damage_type" : "刺伤"
]),
([      "action": "$N手中$w猛的反身递出，疾刺$n的$l，所施全为拼命的招数",
        "force" : 340,
        "attack": 152,
        "parry" : -241,
        "dodge" : -192,
        "damage": 232,
        "damage_type" : "刺伤"
]),
([      "action": "$N面不露色，身形陡然加快，手中$w一剑快过一剑，尽数向$n刺去",
        "force" : 320,
        "attack": 158,
        "parry" : -245,
        "dodge" : -183,
        "damage": 220,
        "damage_type" : "刺伤"
]),
([      "action": "$N手中$w光芒闪烁，在许许剑芒中递出杀着，完全出自$n意料之外",
        "force" : 390,
        "attack": 168,
        "parry" : -193,
        "dodge" : -175,
        "damage": 230,
        "damage_type" : "刺伤"
]),
});

int valid_enable(string usage)
{
        return usage == "sword"||usage=="parry";
}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 1000)
                return notify_fail("你的内力修为不足，无法学习同归剑法。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的内功火候不够，无法学习同归剑法。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的剑法修为不足，无法学习同归剑法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("tonggui-jian", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的同归剑法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("tonggui-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;
        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("qi") < 50)
                return notify_fail("你的体力不够练同归剑法。\n");

        if ((int)me->query("neili") < 70)
                return notify_fail("你的内力不够练同归剑法。\n");

        me->receive_damage("qi", 40);
        me->add("neili", -60);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tonggui-jian/" + action;
}

mixed hit_ob(object me, object victim, int damage)
{
		
		if (!me->query("quest/qz/tgj/pass")) return;
		
		if (random(10) > 7
			&&me->query_temp("tgj/tonggui")) 
        {
			switch (random(3))
			{
				case 0:
					message_vision(MAG"$N挥动手中长剑，不管不问，无视防御，全力进攻！$n心中似乎有些胆怯！\n"NOR,me,victim);
					victim->receive_damage("jing",200+random(400),me);
					victim->receive_wound("jing",100+random(200),me);
					break;
				case 1:
					message_vision(HIY"$N状若疯狂，完全是进攻招式，不成章法，$n不免心中一惊!\n"NOR,me,victim);
					victim->add_busy(1);
					victim->apply_condition("no_exert",1);
					break;
				case 2:
					message_vision(HIR"$N虽然受伤但已存了拼命的心思，招式更见犀利！\n"NOR,me,victim);
				    COMBAT_D->do_attack(me, victim, me->query_temp("weapon"),3);

					break;
			}
        	
        }

}