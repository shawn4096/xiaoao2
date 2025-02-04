//    /kungfu/skill/xingyi-zhang.c 星移掌
// by leontt /1/5/2000

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N使一招「幻形变影」，双手划了个半圈，按向$n的$l",
	"lvl" : 0,
	"skill_name" : "幻形变影",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N左手虚按，右手使一招「星星点点」，向$n的$l推去",
	"lvl" : 20,
	"skill_name" : "星星点点",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N双手握拳，向前向后划弧，一招「漫天星斗」打向$n的$l",
	"lvl" : 40,
	"skill_name" : "漫天星斗",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N左手虚划，右手一记「五斗星辰」击向$n的腰部",
	"lvl" : 60,
	"skill_name" : "五斗星辰",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N施出「北斗七星」，右手击向$n的$l，左手攻向$n的裆部",
	"lvl" : 80,
	"skill_name" : "北斗七星",
	"damage_type" : "瘀伤"
]),						   
([
	"action" : "$N跃起在半空，双掌卷起数道罡风，一式「追星赶月」迅捷无比地劈向$n",
	"lvl" : 100,
	"skill_name" : "追星赶月",
	"damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练斗转星移掌必须空手。\n");
	if ( me->query_skill("shenyuan-gong", 1) < 15)
		return notify_fail("你的神元功火候不够，无法学斗转星移掌。\n");
	if ( me->query("max_neili") < 100)
		return notify_fail("你的内力太弱，无法练斗转星移掌。\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level, j;
	string msg;
	level   = (int) me->query_skill("xingyi-zhang",1);

	if (me->query_temp("mr_riyue")){
		switch(me->query_temp("mr_riyue")){
			case 4: msg = HIC"$N双掌收在胸前，移形换步闪电般将「"HIW"气旋"HIC"」击向$n的檀中穴"NOR; break;
			case 3: msg = HIG"紧接着$N抽出左掌，身形一矮，由下而上猛袭向$n的小腹"NOR; break;
			case 2: msg = HIR"只见$N右掌随后而至，凌空一跃，犹如晴空霹雳拍向$n的头部"NOR; break;
			case 1: msg = HIY"$N在空中一个回转，携「"HIR"日月之光"HIY"」, 双掌按向$n的丹田"NOR; break;
		}    
		me->add_temp("mr_riyue", -1);
		return([
			"action": msg,
			"force" : 200 + random(300),
			"dodge" : random(30) + 10,
			"parry" : random(30) + 10,
			"damage": 150 + random(100),
			"damage_type" : me->query_temp("mr_riyue")?"内伤":"瘀伤",
		]);
	}

	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			if ( me->query_temp("mr_daoying")) {
				return ([
					"action": HIR+action[j]["action"]+NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 + random(300),
					"dodge": random(35),
					"parry": random(35),
					"damage": 100 +random(100),
				]);
			}
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 150 + random(300),
				"dodge": random(30),
				"parry": random(30),
				"damage": 100 +random(50),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("xingyi-zhang", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 40)
		return notify_fail("你的体力太低了。\n");
	if ( me->query("neili") < 20)
		return notify_fail("你的内力不够练星移掌。\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xingyi-zhang/" + action;
}
