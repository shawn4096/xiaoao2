// murong-daofa.c 慕容刀法

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N突然大喝一声「看招」，一招「"HIY"劈天盖地满壮志"NOR"」，刀锋自上而下向$n的$l斩去",
	"lvl" : 0,
	"skill_name" : "劈天盖地满壮志",
	"damage_type" : "割伤"
]),
([
	"action" : "$N移形换步一招「"HIR"弯刀逆转倒乾坤"NOR"」，手中$w在空中急速晃出无数光环，套向$n的$l",
	"lvl" : 30,
	"skill_name" : "弯刀逆转倒乾坤",
	"damage_type" : "割伤"
]),
([
	"action" : "$N猛一挫身，一招「"HIG"遥看万疆千里雪"NOR"」, $w从不可思议的方向冲$n的颈中斩去",
	"lvl" : 70,
	"skill_name" : "遥看万疆千里雪",
	"damage_type" : "割伤",
]),
([
	"action" : "$N身法轻盈无比，一招「"HIM"壮志豪气满江湖"NOR"」，无数刀尖化作点点繁星，向$n的$l挑去",
	"lvl" : 100,
	"skill_name" : "壮志豪气满江湖",
	"damage_type" : "割伤"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query("max_neili") < 50)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("shenyuan-gong", 1) < 10)
		return notify_fail("你的神元功火候太浅。\n");
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
	int i, j, level;
	string msg;
	level = (int) me->query_skill("murong-daofa",1);

	for(i = sizeof(action); i > 0; i--) {
		if(level >= action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			if( me->query_temp("mrdf/liandao"))
			{
				
				switch (me->query_temp("mrdf/liandao"))
				{
					case 7:msg=HIY"$N将手中舞成一片刀影，将$n圈住，然后忽然向东砍一刀，施展的正是少林寺的降魔刀法招式"NOR;break;
					case 6:msg=HIC"$N忽然又向西劈出一刀，施展的正是广西黎山洞黎老汉的柴刀十八路"NOR;break;
					case 5:msg=HIG"随后$N忽然回转而削，一刀而起，呼呼带风，又变作了江南史家的‘回风拂柳刀‘"NOR;break;
					case 4:msg=CYN"紧跟着$N又连使一十一刀，共是一十一种派别的刀法，花样翻新，无一雷同"NOR;break;
					case 3:msg=YEL"$N空中飘然而转，顺手反转刀背，在$n肩头击上一记，这是宁波天童寺心观老和尚所创的‘慈悲刀’只制敌而不杀人"NOR;break;
					case 2:msg=HIR"$N用刀架在$n颈中，正是金刀杨老令公上阵擒敌的招数，是‘后山三绝招’之一，本是长柄大砍刀的招数，$N却改而用于单刀"NOR;break;
					case 1:msg=MAG"$N刀式渐尽，却忽然间最后飞脚向$n踢去！试图将$n踢一个斛斗，那是西夏回人的弹腿绝技"NOR;break;				
				}
				me->add_temp("mrdf/liandao", -1); 
				return ([
					"action":msg,
					"damage": 150+random(50),
					"damage_type": "割伤",
					"dodge": random(35),
					"parry": random(35),
					"force": 350+random(150),
				]);
			}

			if ( me->query_temp("mr_daoying")){
				return ([
					"action":CYN+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"CYN), NOR, CYN)+NOR,
					"damage": 100+random(50),
					"damage_type": "割伤",
					"dodge": random(35),
					"parry": random(35),
					"force": 200+random(300),
				]);
			}
			
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" :"割伤",
				"force": 40 +random(40),
				"dodge": random(30),
				"parry": random(30),
				"damage": 60 +random(50),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("murong-daofa", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 40)
		return notify_fail("你的体力不够练慕容刀法。\n");
	if ( me->query("neili") < 20)
		return notify_fail("你的内力不够练慕容刀法。\n");
	me->receive_damage("jingli", 30);
	me->add("neili",-10);
	return 1;
}
	   
string perform_action_file(string action)
{
	return __DIR__"murong-daofa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int weapon,tweapon,skill;
	weapon=me->query_temp("weapon");
	tweapon=victim->query_temp("weapon");
	skill=me->query_skill("murong-daofa",1);
	if (!weapon) return;
	
	if (me->query_temp("mrdf/yusui")
		&& random(10)>2)
	{
		switch (random(4))
		{
			case 0:
				message_vision(HIW"$N刀光闪烁，一片璀璨，$n顿时感觉眼前一片恍惚！\n"NOR,me,victim);
				victim->add_busy(1);
				break;
			case 1:
				message_vision(RED"$N滴溜溜一个转身，利用刀光掩护，顺手向$n劈出一刀！\n"NOR,me,victim);
				victim->receive_damage("qi",1500+random(2000),me);
				//victim->receive_wound("qi",500+random(1000),me);
				me->add("neili",-100);
				break;
			case 2:
				message_vision(YEL"$N将手中的"+weapon->query("name")+YEL"舞成一个刀花，将$n裹在当中！\n"NOR,me,victim);
				message_vision(YEL"$n左冲右突，始终摆脱不了$N的刀光笼罩，一失神之间，臂膀中了一刀！\n"NOR,me,victim);

				//victim->receive_damage("qi",1000+random(2000),me);
				victim->receive_wound("qi",1000+random(1000),me);
				me->add("neili",-100);
				break;
			case 3:
				if (!tweapon) break;
				
				message_vision(HIG"$n只觉手中的"+tweapon->query("name")+HIG"为$N手持"+weapon->query("name")+HIG"所幻化刀光所包裹！\n"NOR,me,victim);

				if (random(me->query_str(1))>victim->query_str(1)/2
					&& random(me->query_skill("blade",1))>victim->query_skill("parry",1)/2)
				{
					message_vision(HIY"$n只觉一股大力传来，手中"+tweapon->query("name")+HIY"仿佛自己甩出去似得飞了出去！\n"NOR,me,victim);
					tweapon->move(environment(victim));
				}
				break;		
		}
	}
	//刀影掌
		if (me->query_temp("mr_daoying")&&random(10)>6)
		{
			if(objectp(victim) && me->is_fighting(victim))
			{
                weapon->unequip(); 
				message_vision(HIC"$N手中"+weapon->query("name")+HIC"舞成一片刀光，忽然从刀光中向$n拍出一掌！\n"NOR,me,victim);
				me->add_temp("apply/strike",skill/4);
				me->add_temp("apply/damage",skill/5);
                COMBAT_D->do_attack(me,victim, me->query_temp("weapon"),userp(me)?3:1);
				me->add_temp("apply/strike",-skill/4);
				me->add_temp("apply/damage",-skill/5);
				weapon->wield();
			}

		}
}
