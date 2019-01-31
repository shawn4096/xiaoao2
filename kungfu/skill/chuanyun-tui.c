// 穿云腿法
//written by cool
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N身子疾转，右脚贴地伸出，一式「划地为牢」，横扫$n的下盘",
	"damage_type" : "瘀伤",
	"lvl" : 0,
	"skill_name" : "划地为牢"
]),
([
	"action" : "$N左腿踢出，不待左腿落下，右脚紧跟着凌空踢出，一式「追风逐电」，双脚先后踢向$n的$l",
	"damage_type" : "瘀伤",
	"lvl" : 15,
	"skill_name" : "追风逐电"
]),
([
	"action" : "$N一式「左右穿花」，左脚横踹，随即向右前方落步，右脚迅速发力踢向$n的$l",
        "damage_type" : "瘀伤",
	"lvl" : 30,
	"skill_name" : "左右穿花"
]),
([
	"action" : "$N突然一个后翻，一式「倒踢北斗」，双腿晃动，向$n的$l踢去",
        "damage_type" : "瘀伤",
	"lvl" : 45,
	"skill_name" : "倒踢北斗"
]),
([
	"action" : "$N使一式「登云步月」，拔地而起，双腿连续踢出，击向$n的胸口",
        "damage_type" : "内伤",
	"lvl" : 60,
	"skill_name" : "登云步月"
]),
([
	"action" : "$N身子盘旋飞起，一式「横扫九州」，右腿横扫$n的$l",
	"damage_type" : "内伤",
	"lvl" : 75,
	"skill_name" : "横扫九州"
]),
([
	"action" : "$N双腿骤起，一招「天清云淡」，一腿劈向$n面门，另一腿却横扫$n小腹",
	"lvl" : 90,
	"skill_name" : "天清云淡",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N左手一绕，向前击向$n的头部，一式「无影无踪」，右腿突然踢向$n的$l",
	"damage_type" : "瘀伤",
	"lvl" : 105,
	"skill_name" : "无影无踪"
]),
([
	"action" : "$N腿风激荡，双腿错落，来势神妙无方，一招"HIR"「日入空山」"NOR"，劈向$n的$l",
	"lvl" : 120,
	"skill_name" : "日入空山",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N使一式"HIY"「雷霆天下」"NOR"，身体凌空而起，双腿连环，只见漫天腿影笼罩着$n",
	"damage_type" : "震伤",
	"lvl" : 135,
	"skill_name" : "雷霆天下"
]),
([
	"action" : "$N双手齐划，跟着脚下步踩七星，一招"HIW"「北风卷地」"NOR"，一股排山倒海的脚力，直劈$n面门",
	"lvl" : 150,
	"skill_name" : "北风卷地",
	"damage_type" : "内伤"
]),
([
	"action" : "$N突然滴溜溜的转身，一招"HIW"「天山雪飘」"NOR"，腿影飞舞，霎时之间将$n四面八方彻底裹住",
	"lvl" : 180,
	"skill_name" : "天山雪飘",
	"damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="leg" ||  usage=="parry"; }
int valid_combine(string combo) { return combo=="sanyin-shou"; }


int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练穿云腿必须空手。\n");
	if ((int)me->query_skill("xuantian-wuji", 1) < 20)
		return notify_fail("你的玄天无极功火候不够，无法学穿云腿。\n");
	if ((int)me->query("max_neili") < 50)
		return notify_fail("你的内力太弱，无法练穿云腿。\n");
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
	level = (int)me->query_skill("chuanyun-tui", 1);
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 100 +random(350),
				"dodge": 20+random(20),
				"parry": random(10),
			]);
		}
	}
}

mixed hit_ob(object me, object target, int damage_bonus)
{
	int lvl,qi;

	lvl = (int)me->query_skill("chuanyun-tui", 1);
	qi =(int)target->query("qi");

	if( me->query_skill_prepared("leg") != "chuanyun-tui" )
		return 0;

	if(  random(lvl) > 200 && random(10)==1) {
		message_vision(HIR"$N瞅得对方破绽，突然抢上一步，运劲使出一记侧踢，往$n的胸口击出。\n"NOR,me,target);
		message_vision(HIR"$n受此重击，顿时只觉得胸口一阵发麻，经脉受阻，难以运气疗伤。\n"NOR,me,target);
            target->apply_condition("no_exert", 1);
            target->receive_damage("qi", qi/2,me);
            target->receive_wound("qi", qi/5,me);
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("chuanyun-tui", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 30)
		return notify_fail("你的体力太低了。\n");
	if ( me->query("neili") < 10)
		return notify_fail("你的内力不够练穿云腿。\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -5);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"chuanyun-tui/" + action;
}
