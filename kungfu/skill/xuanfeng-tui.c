// 旋风扫叶腿
// Modified by Darken@SJ
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N纵身向前，忽然伸出左腿，一式「魁星踢斗」，直踢$n的头部",
        "force" : 150,
        "dodge" : -2,
        "parry" : -2,
        "lvl" : 0,
        "skill_name" : "魁星踢斗",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N身形一闪，已从$n身边掠过，右足反踢，正是一招「倒踢紫金冠」，踹向$n的背心",
        "force" : 200,
        "dodge" : -1,
        "parry" : 2,
        "lvl" : 8,
        "skill_name" : "倒踢紫金冠",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N身体半蹲，右足画出个半圆，使出「旁敲侧击」，扫向$n的膝部",
        "force" : 250,
        "dodge" : 5,
        "parry" : 2,
        "lvl" : 18,
        "skill_name" : "旁敲侧击",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N上身微侧，左足倏地弹出，连环三腿，分踢$n的头部，胸部和裆部，正是「连环三踢」",
        "force" : 300,
        "dodge" : -4,
        "parry" : 6,
        "lvl" : 30,
        "skill_name" : "连环三踢",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N右足独立，左足随身形反转横扫，又左足立定，右足横扫向前，一招「秋风扫落叶」，踢向$n的$l",
        "force" : 350,
        "dodge" : 5,
        "parry" : 4,
        "lvl" : 50,
        "skill_name" : "秋风扫落叶",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N跃起在半空，双足乱舞，带起无数劲风，「凤舞九天」！迅捷无伦地卷向$n",
        "force" : 400,
        "dodge" : -5,
        "parry" : 10,
        "lvl" : 80,
        "skill_name" : "凤舞九天",
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="leg" || usage=="parry"; }
 int valid_combine(string combo) { return combo=="luoying-zhang"; } 

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("学旋风扫叶腿时手里不能拿武器。\n");
        if (me->query("max_neili") >= 1000) return 1;
        if ((int)me->query_skill("bihai-chaosheng", 1) < 30)
                return notify_fail("你的碧海潮生功火候不够，无法学旋风扫叶腿。\n");
        if (me->query("family/family_name")!="桃花岛")
                return notify_fail("你不是桃花岛弟子，学了也用不了。\n");

		if (me->query_skill_mapped("force") != "bihai-chaosheng")
                return notify_fail("修习旋风扫叶腿必须有碧海潮生功配合。\n");
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力太弱，无法练旋风扫叶腿。\n");
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
        level = (int)me->query_skill("xuanfeng-tui",1) + (int)me->query_skill("luoying-zhang",1);
        adjust = level/5;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level > action[i-1]["lvl"]) {
                    j = NewRandom(i, 20, level/5);
                    if (me->query_perform() == "狂风绝技")
                        return ([  
                        "action" : HIG+action[j]["action"]+NOR,
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
        int lvl = me->query_skill("xuanfeng-tui", 1);
        int i = sizeof(action);
        mapping learned = me->query_learned();

        if (!mapp(learned)) learned = ([]);
        if (!learned["xuanfeng-tui"])
                while (i--) 
                        if (lvl == action[i]["lvl"])
                                return notify_fail("你将已经学会的所有招式练习了一遍，发现如果不去找师父学新的招式就无法获得进步了。\n");;

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练旋风扫叶腿时手里不能拿武器。\n");
        if ((int)me->query("jingli") < 40)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("你的内力不够练旋风扫叶腿。\n");
        me->receive_damage("jingli", 30);
        me->add("neili", -10);
        return 1;
}

string perform_action_file(string action)
{
      return __DIR__"xuanfeng-tui/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl = me->query_skill("leg",1);
		if (me->query_skill("xuanfeng-tui",1)> 449 && me->query("thd/wuji/kuangfeng"))
		{
			lvl = me->query_skill("leg",1)+2*me->query_skill("xuanfeng-tui",1);
		} //解密后，450大飞
        if ((random(lvl) > 100 && random(me->query_dex()) > victim->query_dex()/2 ||
             random(me->query_temp("thd/is_fast")) > 200) && victim->query("jiali")) {
                victim->set("jiali",0);
                victim->add("neili", -lvl*2);
				victim->apply_condition("no_exert",1+random(1));
                message_vision(HIR"$n被$N这一腿的踢中丹田部位，感觉全身真气立即逆转涣散！\n"NOR,me, victim);
        }
}
