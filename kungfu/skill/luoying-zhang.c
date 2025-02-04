// 落英神剑掌
// Modified by Darken@SJ

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N纵身向前，掌势一发即收，双掌连晃，已抢到$n的面前，使出「落英缤纷」，虚虚实实，若有若无地袭向$n",
        "force" : 100,
        "dodge" : 30,
        "parry" : -2,
        "lvl" : 0,
        "skill_name" : "落英缤纷",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N左足一点，跃起丈余，在半空连转两个圈子，凌空挥掌，掌做剑形，一招「江城飞花」，向$n当头击下",
        "force" : 150,
        "dodge" : -1,
        "parry" : 5,
        "lvl" : 7,
        "skill_name" : "江城飞花",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N左足在前，右足在后，单臂画了个弧线，正是「雨打桃花」，劈头盖脸地向$n按去",
        "force" : 200,
        "dodge" : 5,
        "parry" : 2,
        "lvl" : 15,
        "skill_name" : "雨打桃花",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N身形一转，已经欺到$n近前，立掌如剑，单手横劈，飕飕风响，一招「雨急风狂」划向$n的$l",
        "force" : 250,
        "dodge" : -5,
        "parry" : 6,
        "lvl" : 28,
        "skill_name" : "雨急风狂",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N身形连晃，倏忽间已围着$n转了几个圈子，掌影飘飘，正是一招「无边落木」，从四面八方向$n袭去",
        "force" : 300,
        "dodge" : 8,
        "parry" : 5,
        "lvl" : 45,
        "skill_name" : "无边落木",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N长笑一声，踏上一步，双掌连击，虚招多而实招少，霎时化作「满天花雨」，将$n的全身都笼罩在掌影之中",
        "force" : 350,
        "dodge" : -2,
        "parry" : 10,
        "damage" : 35,
        "lvl" : 60,
        "skill_name" : "满天花雨",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N暗暗运劲，力贯双臂，身子如剑般扑向$n，两掌一前一后，使出一招「断艳残红」，狠狠地按向$n的前胸",
        "force" : 400,
        "dodge" : -8,
        "parry" : 8,
        "lvl" : 80,
        "skill_name" : "断艳残红",
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"|| usage=="sword"; }
int valid_combine(string combo) { return combo=="xuanfeng-tui"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("学落英神剑掌必须空手。\n");
		if (me->query("family/family_name")!="桃花岛")
                return notify_fail("你不是桃花岛弟子，学了也用不了。\n");
        if (me->query("max_neili") >= 1000) return 1;
        if ((int)me->query_skill("bihai-chaosheng", 1) < 20)
                return notify_fail("你的碧海潮生功火候不够，无法学落英神剑掌。\n");
        if (me->query_skill_mapped("force") != "bihai-chaosheng")
                return notify_fail("修习落英神剑掌必须有碧海潮生功配合。\n");
        if ((int)me->query("max_neili") < 80)
                return notify_fail("你的内力太弱，无法练落英神剑掌。\n");
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
        int i, j, level, adjust;
        level = (int) me->query_skill("luoying-zhang",1) + (int) me->query_skill("xuanfeng-tui",1);
        adjust = level/5;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level > action[i-1]["lvl"]) {
                    j = NewRandom(i, 20, level/5);
                    
					if (me->query_temp("lyz/luoying"))
					{
						return ([  
							"action" : random(2)?HIM+action[j]["action"]+NOR:HIG+action[j]["action"]+NOR,
							"force" : action[j]["force"] + adjust,
							"dodge" : action[j]["dodge"] + adjust,
							"damage" : action[j]["damage"] + adjust,
							"damage_type" : "刺伤",
                        ]);

					}
					
					if (me->query_perform() == "狂风绝技")
                        return ([  
                        "action" : HIM+action[j]["action"]+NOR,
                        "force" : action[j]["force"] + adjust,
                        "dodge" : action[j]["dodge"] + adjust,
                        "damage" : action[j]["damage"] + adjust,
                        "damage_type" : action[j]["damage_type"],
                        ]);
                    else 
                        return ([  
                        "action" : action[j]["action"],
                        "force" : action[j]["force"],
                        "dodge" : action[j]["dodge"] + adjust/2,
                        "damage" : action[j]["damage"],
                        "damage_type" : action[j]["damage_type"],
                        ]);
                }
}

int practice_skill(object me)
{
        int lvl = me->query_skill("luoying-zhang", 1);
        int i = sizeof(action);
        mapping learned = me->query_learned();

        if (!mapp(learned)) learned = ([]);
        if (!learned["luoying-zhang"])
                while (i--) 
                        if (lvl == action[i]["lvl"])
                                return notify_fail("你将已经学会的所有招式练习了一遍，发现如果不去找师父学新的招式就无法获得进步了。\n");;

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练落英神剑掌必须空手。\n");
        if ((int)me->query("jingli") < 40)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("你的内力不够练落英神剑掌。\n");
        me->receive_damage("jingli", 30);
        me->add("neili", -10);
        return 1;
}

string perform_action_file(string action)
{
      return __DIR__"luoying-zhang/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int i;
		int lvl = me->query_skill("strike")+ me->query_skill("luoying-zhang");
	    if (me->query("thdjj/ronghe")=="pass") i=3;
		else i=1;
        if ((random(lvl) > 100 && random(me->query_dex(1)) > victim->query_dex(1)/2 ||
             random(me->query_temp("thd/is_fast")) > 200) && !victim->query_temp("must_be_hit")) {
                victim->set_temp("must_be_hit", 1);
                call_out("remove_effect", 2+random(3), victim);
                message_vision(HIR"$n被$N所幻化出的漫天掌影弄得晕头转向，根本分不出哪招为实，哪招为虚！\n"NOR, me, victim);
				if (victim->is_busy()) victim->add_busy(1+random(1));
				else victim->start_busy(1+random(1));
        }
		//桃花影落飞神剑
		else if (random(me->query_temp("thd/is_fast"))>200 && me->query("thd/wuji/luoying")&& random(me->query_int())> victim->query_int()/2 )
		{
           message_vision(HIM"$N忽然领悟'桃花影落飞神剑'的精髓，忽然变掌法为剑招施展出来，$n淬不及防，为$N连攻两招！\n"NOR, me, victim);
		
		   COMBAT_D->do_attack(me,victim, me->query_temp("weapon"), i);
           COMBAT_D->do_attack(me,victim, me->query_temp("weapon"), i);
		 }
       
		
}

void remove_effect(object victim)
{
        if (!victim) return;
        victim->delete_temp("must_be_hit", 1);
}

