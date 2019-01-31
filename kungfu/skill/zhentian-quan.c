//震天拳
//cool 981010
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N马步一立，身子微曲，暗喝一声，一招「望月拜天」，一拳直捅$n的$l",
	"lvl" : 0,
	"skill_name" : "望月拜天",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N“哈哈”一笑，左拳由下至上，右拳平平击出，一招「跨日向天」，交替打向$n",
	"lvl" : 20,
	"skill_name" : "跨日向天",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N对$n一声大喝，使一招「长虹经天」，左拳击出，随即右拳跟上，两重力道打向$n的$l",
	"lvl" : 40,
	"skill_name" : "长虹经天",
	"damage_type" : "震伤"
]),
([
	"action" : "$N使出「一臂擎天」，一声大吼，一拳凌空打出，拳风直逼$n的$l",
	"lvl" : 60,
	"skill_name" : "一臂擎天",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N一声长啸，双拳交错击出，一招「石破天惊」，拳风密布$n的前后左右",
	"lvl" : 80,
	"skill_name" : "石破天惊",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N双拳互错，变幻莫测，一招「秋风不尽」，前后左右，瞬息之间向$n攻出了四四一十六拳",
	"lvl" : 100,
	"skill_name" : "秋风不尽",
	"damage_type" : "瘀伤",
]),
([
	"action" : "$N一声清啸，呼的一拳，一招「山回路转」，自巧转拙，却是去势奇快，向$n的$l猛击过去",
	"lvl" : 120,
	"skill_name" : "山回路转",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N双拳交错，若有若无，一招「天衣无缝」，拍向$n的$l",
	"lvl" : 140,
	"skill_name" : "天衣无缝",
        "damage_type" : "瘀伤"
]),
([
	"action" : "$N一招"HIC"「青山断河」"NOR"，右手一拳击出，左掌紧跟着在右拳上一搭，变成双掌下劈，击向$n的$l",
	"lvl" : 160,
	"skill_name" : "青山断河",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N闷喝一声，双拳向上分开，一记"HIR"「举火烧天」"NOR"，拳划弧线，左右同时击向$n的$l",
	"lvl" : 180,
	"skill_name" : "举火烧天",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N怒吼一声，凌空飞起，一式"HIY"「天崩地裂」"NOR"，双拳居高临下，齐齐捶向$n",
	"lvl" : 200,
	"skill_name" : "天崩地裂",
	"damage_type" : "内伤"
]),
([
	"action" : "$N仰天大笑，势若疯狂，衣袍飞舞，一招"HIG"「无法无天」"NOR"，拳风凌厉，如雨点般向$n打去",
	"lvl" : 220,
	"skill_name" : "无法无天",
	"damage_type" : "内伤"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }
int valid_combine(string combo) { return combo=="kunlun-zhang"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练「震天拳」必须空手。\n");
	if ((int)me->query_skill("xuantian-wuji", 1) < 25)
		return notify_fail("你的「玄天无极功」火候不够，无法学「震天拳」。\n");
	if ((int)me->query("max_neili") < 50)
		return notify_fail("你的内力太弱，无法练「震天拳」。\n");
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
	if( me->query_skill("cuff", 1) >= 220 
	 && me->query_skill("zhentian-quan", 1) >= 220 
	 && me->query_skill("strike",1) >= 220
	 && me->query_skill("kunlun-zhang",1) >= 220
	 && me->query("neili") >= 500
	 && me->query_skill_mapped("strike")  == "kunlun-zhang"
	 && me->query_skill_mapped("cuff") == "zhentian-quan"
	 && random(5)==1) {
		return ([
			"action": HIW"$N手中招式突然加快，一招"HIR"「拳掌双绝」"HIW"，脚下缩地成寸，拳风阵阵隔空击出，随即双腿连环飞起，劈向$n"NOR,
			"parry": 15+random(15),
			"dodge": 20+random(20),
			"force": 250+random(350),
			"damage_type": "击伤"
		]);
	}
	level   = (int) me->query_skill("zhentian-quan",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 200 +random(150),
				"dodge": random(10),
				"parry": random(30),
			]);
		}
	}
}

mixed hit_ob(object me, object target, int damage_bonus)
{
	int lvl,qi;

	lvl = (int)me->query_skill("zhentian-quan", 1);
	qi =(int)target->query("qi");

	if( me->query_skill_prepared("cuff") != "zhentian-quan" )
		return 0;

	if(  random(lvl) > 100 && random(10)==1) {
		message_vision(HIR"$N瞅得对方破绽，突然抢上一步，握掌为拳，使出一记正拳，运劲往$n的肩膀上击出。\n"NOR,me,target);
		message_vision(HIR"$n无暇躲闪，只觉得肩膀一阵发麻，气血受阻，任何招式都无法使出。\n"NOR,me,target);
            target->apply_condition("no_perform", 1);
            target->receive_damage("qi", qi/5);
            target->receive_wound("qi", qi/5);
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("zhentian-quan", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 30)
		return notify_fail("你的精力太低了。\n");
	if ( me->query("neili") < 10)
		return notify_fail("你的内力不够练「震天拳」。\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -5);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"zhentian-quan/" + action;
}
