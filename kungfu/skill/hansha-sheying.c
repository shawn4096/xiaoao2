//hanshasheying 含沙射影
// 1997-2-14
#include <ansi.h>

inherit SKILL;

string  *msg = ({
"$N手一扬，使一式「流星追月」，只听得嗖嗖数声，数枚$w前慢后快地向$n的$l射出",
"$N身形忽地高高跃起，使一式「天女散花」，手中数枚$w向$n急射而出",
"$N一式「去而复来」，手一掷，数枚$w从$n身旁掠过，到了$n身后忽然转头向$n后心飞去",
"$N身形突地倒地向外滚出，一回身，使一招「日出东方」，手中暗扣的数枚$w以迅雷不及掩耳之势射向$n下身",
"$N身形一闪，到了$n身后，反手一式「回身见礼」，手中数枚$w向$n的后心要害击去",
"$N一式「狂风骤雨」，突然双手连扬数下，十余枚$w，闪电般地飞向$n的前胸",
});

int valid_enable(string usage)
{
	return usage == "throwing" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
	return ([
		"action":msg[random(sizeof(msg))],
		"damage": 40 + random(60),
		"damage_type":random(2)?"刺伤":"割伤",
		"dodge":random(20)-10,
		"force":random(250)+100,
		"parry": random(10),
		"post_action": (: call_other, WEAPON_D, "throw_weapon" :)
	]);
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 30)
		return notify_fail("你的体力不够练含沙射影。\n");
	if ( me->query("neili") < 10)
		return notify_fail("你的内力不够练含沙射影。\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -5);
	return 1;
}

int valid_learn(object me)
{
	object weapon;
	if (!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "throwing")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query("max_neili") < 300)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("dulong-dafa", 1) < 50)
		return notify_fail("你的毒龙大法火候太浅。\n");
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"hansha-sheying/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon;
        weapon=me->query_temp("weapon");
        lvl = me->query_skill("hansha-sheying", 1);
        
		if (random(3)||!weapon) return;
 
        switch(random(3))
        {
            case 0:
              if (random(me->query_skill("throwing",1))>victim->query_skill("parry",1)/2)
              {                  
				  me->add("neili", -50);                  
				  victim->add_busy(1+random(2));
				  victim->receive_damage("qi",2000,me);
				  message_vision(HIC"$N闪身射出一枚"+weapon->query("name")+HIC",射中$n三尺寸关穴！\n"NOR,me,victim);
              }
              break;
            case 1:
              if (random(me->query_int(1))> victim->query_int(1)/3)
              {
                  me->add("neili", -20);              
                  message_vision(RED "$N双手舞动，连射数枚"+weapon->query("name")+RED"，欲发即发，欲收即收，对$n形成强大压力。\n"NOR,me,victim);
				  victim->apply_condition("no_exert",1+random(2));
				  victim->receive_damage("qi",3000,me);
				  COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);	
             }
             break;

          case 2:            
		     if (random(me->query("combat_exp",1)) > victim->query("combat_exp",1)/3)
		      {	
			      message_vision(MAG "$N大喝一声，一枚"+weapon->query("name")+MAG"，呼啸而出，射中$n大椎穴。\n"NOR,me,victim);
				  victim->receive_damage("qi",4000,me);
				 
			  }
			  break; 
			default:break;
		}
	
}

