// nianhua-zhi.c -拈花指
#include <ansi.h>
#include <combat.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N侧身抬臂，右指划了个半圈，一式「瓶花落砚」击向$n的$l",
	"lvl" : 0,
	"skill_name" : "瓶花落砚",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N左掌虚托，一式「寒梅吐蕊」，右指穿腋疾出，指向$n的胸前",
	"lvl" : 0,
	"skill_name" : "寒梅吐蕊",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N俯身斜倚，左手半推，右手一式「初杏问酒」，向$n的$l划过",
	"lvl" : 0,
	"skill_name" : "初杏问酒",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N双目微睁，一式「露草斜阳」，双手幻化出千百个指影，拂向$n的$l",
	"lvl" : 20,
	"skill_name" : "露草斜阳",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N一式「仰月承霖」，左掌护住丹田，右手斜指苍天，蓄势点向$n的$l",
	"lvl" : 40,
	"skill_name" : "仰月承霖",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N双掌平托胸前，十指叉开，一式「叶底留莲」，指向$n的周身大穴",
	"lvl" : 60,
	"skill_name" : "叶底留莲",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N双掌翻飞，一式「清风拂桂」，指端迸出无数道劲气，射向$n的全身",
	"lvl" : 80,
	"skill_name" : "清风拂桂",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N一式「菊圃秋霜」，并指如刃，一束束锐利无俦的刀气，凌虚向$n的$l砍去",
	"lvl" : 100,
	"skill_name" : "菊圃秋霜",
	"damage_type" : "刺伤"
]),
([
	"action" : HIC"$N一式「伽叶微笑」，双手食指交叉，指端射出一缕罡气，穿过$n的$l"NOR,
	"lvl" : 150,
	"skill_name" : "伽叶微笑",
	"damage_type" : "刺伤"
]),
([
	"action" : HIY"$N左掌竖立胸前，一式「佛祖拈花」，右手食指扣住拇指，轻轻对着$n一弹"NOR,
	"lvl" : 170,
	"skill_name" : "佛祖拈花",
	"damage_type" : "刺伤"
])
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }

int valid_combine(string combo) 
{
	object me;
	me = this_player(); 

	if ((int)me->query_int(1) > 40)
		return combo=="sanhua-zhang"; 
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练拈花指必须空手。\n");
	if ( me->query_skill("yijin-jing", 1) < 60)
		return notify_fail("你的易筋经内功火候不够，无法学拈花指。\n");
	if ((int)me->query_int(1) > 30) {
		return 1;
	}
	else {
		if ( me->query_skill("banruo-zhang", 1)
		 && me->query_skill("yizhi-chan", 1)
		 && me->query_skill("jingang-quan", 1)
		 && me->query_skill("longzhua-gong", 1)
		 && me->query_skill("qianye-shou", 1)
		 && me->query_skill("ruying-suixingtui", 1)
		 && me->query_skill("sanhua-zhang", 1))
			return notify_fail("你的功力不够，无法同时学习两种以上的上乘功夫。\n");
	}
	if ( me->query("max_neili") < 600)
		return notify_fail("你的内力太弱，无法练拈花指。\n");
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
	int i, level, j;
	level   = (int) me->query_skill("nianhua-zhi",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
					
			j = NewRandom(i, 20, level/5);
			return ([
				"action": action[j]["action"],
				"damage_type": action[j]["damage_type"],
				"lvl": action[j]["lvl"],
				"damage": action[j]["lvl"]>149?150+random(80):90+random(80),
				"force": 150 + random(300),
				"dodge": random(30),
				"parry": random(30),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("nianhua-zhi", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 40)
		return notify_fail("你的精力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练拈花指。\n");
	if ( me->query_skill("buddhism") < 220)
	{
		if ( me->query_skill("banruo-zhang", 1)
		 || me->query_skill("yizhi-chan", 1)
		 || me->query_skill("jingang-quan", 1)
		 || me->query_skill("qianye-shou", 1)
		 || me->query_skill("longzhua-gong", 1)
		 || me->query_skill("ruying-suixingtui", 1))
			return notify_fail("你的佛法领悟力不够，无法同时修习两种以上的上乘空手功夫。\n");
	}

	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"nianhua-zhi/" + action;
}
