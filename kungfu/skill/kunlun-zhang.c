// 增加 pfm 叠掌特殊效果 by Lane@SJ
// kunlun-zhang.c 昆仑掌

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N掌风激荡，双掌错落，来势神妙无方，一招「日入空山」，劈向$n的$l",
	"lvl" : 0,
	"skill_name" : "日入空山",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N双掌骤起，一招「天清云淡」，一掌击向$n面门，另一掌却按向$n小腹",
	"lvl" : 30,
	"skill_name" : "天清云淡",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N双掌互错，变幻莫测，一招「秋风不尽」，前后左右，瞬息之间向$n攻出了四四一十六招",
	"lvl" : 60,
	"skill_name" : "秋风不尽",
	"damage_type" : "瘀伤",
]),
([
	"action" : "$N一声清啸，呼的一掌，一招「山回路转」，自巧转拙，却是去势奇快，向$n的$l猛击过去",
	"lvl" : 100,
	"skill_name" : "山回路转",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N双掌交错，若有若无，一招「天衣无缝」，拍向$n的$l",
	"lvl" : 120,
	"skill_name" : "天衣无缝",
        "damage_type" : "瘀伤"
]),
([
	"action" : "$N一招「青山断河」，右手一拳击出，左掌紧跟着在右拳上一搭，变成双掌下劈，击向$n的$l",
	"lvl" : 140,
	"skill_name" : "青山断河",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N双手齐划，跟着双掌齐推，一招「北风卷地」，一股排山倒海的掌力，直扑$n面门",
	"lvl" : 160,
	"skill_name" : "北风卷地",
	"damage_type" : "内伤"
]),
([
	"action" : "$N突然滴溜溜的转身，一招「天山雪飘」，掌影飞舞，霎时之间将$n四面八方都裹住了",
	"lvl" : 180,
	"skill_name" : "天山雪飘",
	"damage_type" : "瘀伤"
])
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }
int valid_combine(string combo) { return combo=="zhentian-quan"; }

int valid_learn(object me)
{
	mapping fam  = me->query("family");
	if (fam["family_name"] != "昆仑派" || fam["generation"] > 4)
		return notify_fail("昆仑掌需四代以上弟子方可修习。\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练昆仑掌必须空手。\n");
	if ( me->query_skill("xuantian-wuji", 1) < 120)
		return notify_fail("你的玄天无极功火候不够，无法练昆仑掌。\n");
	if(me->query("gender") != "女性"){
		if ( me->query_skill("zhentian-quan", 1) < 80 && !me->query_skill("kunlun-zhang", 1))
			return notify_fail("你的震天拳低于八十级，无法练昆仑掌。\n");
	}
	else {
		if ( me->query_skill("chuanyun-tui", 1) < 80 && !me->query_skill("kunlun-zhang", 1))
			return notify_fail("你的穿云腿小于八十级，无法练昆仑掌。\n");
	}
	if ( me->query("max_neili") < 800)
		return notify_fail("你的内力修为不够，无法练昆仑掌。\n");
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
	level = (int) me->query_skill("kunlun-zhang",1);

	for(i = sizeof(action); i > 0; i--) 
	{
		if(level > action[i-1]["lvl"])
		{
			j = NewRandom(i, 20, level/5);
			//落雁拳
			if (me->query_temp("klz/luoyan"))
			{
				return ([
					"action": HIC+action[j]["action"]+NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 + random(500),
					"damage": 180 + random(100),
					"dodge": random(30)-10,
					"parry": random(20),
				]);

			}
			if( me->query_temp("diezhang1") ) 
			{
				me->delete_temp("diezhang1");
				return ([
					"action": HIR"$N双掌平平推出，看似缓慢之极，毫无威力，其实内劲前赴后继，暗藏杀招！"NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 + random(500),
					"dodge": random(30)-10,
					"parry": random(20),
				]);
			}
			else if( me->query_temp("diezhang2") > 0 ) {
				return ([
					"action": YEL+action[j]["action"]+NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 +random(350),
					"dodge": random(30),
					"parry": random(10),
				]);
			} else
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 200 +random(350),
				"dodge": random(30)-10,
				"parry": random(20),
			]);

		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("kunlun-zhang", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 50)
		return notify_fail("你的体力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练昆仑掌。\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"kunlun-zhang/" + action;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	if (!me->query_temp("weapon")) return;
	
	if( victim->query("qi") < 0 ) return;

	if( me->query_temp("diezhang2") > 1
		&&!random(3) )
	{
		me->add_temp("diezhang2", -1);
		message_vision(HIW"$N眼见$n大意，一招叠掌连环跟上又是一招递出!\n"NOR,me,victim);

		COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(2)?1:3);
	}
	if (me->query_temp("klz/hongsha")
		&&!random(3))
	{
		message_vision(HBRED+HIW"$N暗运真气，逼出一股若隐若现的红砂掌毒气拍向$n!\n"NOR,me,victim);
		victim->apply_condition("hot_poison",2+random(3));
	}
	//红砂掌特效

	if (me->query_temp("klz/hongsha")
		&& random(me->query_skill("kunlun-zhang", 1)) > 100
		&& me->query("neili") > 1000
		&& random(me->query_skill("poison",1)) > 120
		&& random(10)>5
		&& random(me->query("neili")) > victim->query("neili")/2)
	{

		
			switch(random(5))
			{
				case 0:
					message_vision(BLU"$N左掌运气变为绿色，在内功激发下，一股若隐若现的「"HIG"蛇毒"BLU"」弥漫，侵入$n的上三焦。\n"NOR,me,victim);
					victim->add_condition("snake_poison", 1);
					break;
				case 1:
					message_vision(MAG"$N劲力吞吐，一股灰色的「"WHT"蜈蚣毒"MAG"」沿着双掌侵入$n的奇经八脉。\n"NOR,me,victim);
					victim->add_condition("wugong_poison", 1);
					break;
				case 2:
					message_vision(CYN"$N暗自运功，一股血红色的「"HIR"蝎子毒"CYN"」顺着右手侵入$n的任脉。\n"NOR,me,victim);
					victim->add_condition("xiezi_poison", 1);
					break;
				case 3:
					message_vision(YEL"$N双掌逼出一股蓝汪汪的「"HIB"蜘蛛毒"YEL"」侵入$n的督脉。\n"NOR,me,victim);
					victim->add_condition("zhizhu_poison", 1);
					break;
				case 4:
					message_vision(WHT"$N右掌回旋，推送出一股「"HIY"蟾蜍毒"WHT"」劲气渡入$n的下三焦。\n"NOR,me,victim);
					victim->add_condition("hama_poison", 1);
					break;
			}
				   
	}
}
