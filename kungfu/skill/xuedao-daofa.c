// xuedao-jing.c 血刀经
// write by iceland
//xuedao-daofa.c 修改成刀法种类by sohu

#include <ansi.h>
#include <skill.h>
#include <combat.h>
#include <weapon.h>
inherit F_SSERVER;
inherit SKILL;

mapping *action = ({
([
	"action" : "$N略略侧身，一招「斩头式」反手从背后横劈出一刀，直奔$n的项颈",
	"skill_name" : "斩头式",
	"lvl" : 0,
	"damage_type" : "割伤",
]),
([
	"action" : "$N突然横卧于地，$n目瞪口呆之际，一招「破膛刀」，手中$w由下而上直劈$n的小腹",
	"skill_name" : "破膛刀",
	"lvl" : 20,
	"damage_type" : "割伤",
]),
([
	"action" : "$N足尖一点，一个倒翻头顶着地，一招「去魂电」，$w一闪，自左而右，由右到左连出十刀",
	"skill_name" : "去魂电",
	"lvl" : 40,
	"damage_type" : "割伤",
]),
([
	"action" : "$N怪叫一声，飞腾空中，一招「流星经天」，手中$w脱手而出，疾射$n的$l",
	"skill_name" : "流星经天",
	"lvl" : 60,
	"damage_type" : "割伤",
]),
([
	"action" : "$N脸色诡异，喉中“呵呵”低吼，一招「蛇行」，$w灵动异常的在$n的$l游走过去",
	"skill_name" : "蛇行",
	"lvl" : 80,
	"damage_type" : "割伤",
]),
([
	"action" : "$N一招「三界咒」，手中$w微微一抖，“嗤嗤嗤”三声轻响，向$n头、胸、腹连劈三刀",
	"skill_name" : "三界咒",
	"lvl" : 100,
	"damage_type" : "割伤",
]),
([
	"action" : "$N炸雷般大喝一声，一式「魔分身」$w照$n搂肩带背斜劈下来，力道凶猛，势不可挡",
	"skill_name" : "魔分身",
	"lvl" : 120,
	"damage_type" : "割伤",
]),
});

mapping *action_xd = ({
([
	"action" : RED"$N略略侧身，一招「斩头式」反手从背后横劈出一刀，直奔$n"RED"的项颈"NOR,
	"skill_name" : "斩头式",
	"lvl" : 200,
	"damage_type" : "割伤",
]),
([
	"action" : MAG"$N突然横卧于地，$n"RED"目瞪口呆之际，一招「破膛刀」，手中$w"+MAG"由下而上直劈$n"MAG"的小腹"NOR,
    "skill_name" : "破膛刀",
	"lvl" : 120,
	"damage_type" : "割伤",
]),
([
	"action" : HBYEL"$N足尖一点，一个倒翻头顶着地，一招「去魂电」，$w"+HBYEL"一闪，自左而右，由右到左连出十刀"NOR,
	"skill_name" : "去魂电",
	"lvl" : 140,
	"damage_type" : "割伤",
]),
([
	"action" : BLU"$N怪叫一声，飞腾空中，一招「流星经天」，手中$w"+BLU"脱手而出，疾射$n"BLU"的$l"NOR,
	"skill_name" : "流星经天",
	"lvl" : 160,
	"damage_type" : "割伤",
]),
([
	"action" : HIR"$N脸色诡异，喉中“呵呵”低吼，一招「蛇行」，$w"+HIR"灵动异常的在$n"HIR"的$l游走过去"NOR,
	"skill_name" : "蛇行",
	"lvl" : 180,
	"damage_type" : "割伤",
]),
([
	"action" : HIY"$N一招「三界咒」，手中$w"+HIY"微微一抖，“嗤嗤嗤”三声轻响，向$n"HIY"头、胸、腹连劈三刀"NOR,
	"skill_name" : "三界咒",
	"lvl" : 100,
	"damage_type" : "割伤",
]),
	
	([
	"action" : HBRED"$N炸雷般大喝一声，一式「魔分身」$w"+HBRED"照$n"HBRED"搂肩带背斜劈下来，力道凶猛，势不可挡"NOR,
	"skill_name" : "魔分身",
	"lvl" : 320,
	"damage_type" : "割伤",]),
	
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");
	if (me->query("max_neili") < 150)
		return notify_fail("你的内力不够。\n");
	if (me->query_skill("xuedao-jing", 1) < 20)
		return notify_fail("你的血刀经火候太浅。\n");
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
	level   = (int) me->query_skill("xuedao-daofa",1);
		//批纸削腐
	if (me->query_temp("xddf/shendao"))
	{
			for(i = sizeof(action_xd); i > 0; i--)
		    if(level > action_xd[i-1]["lvl"])
			{
				j = NewRandom(i, 20, level/5);
				return ([  
					"action": action_xd[j]["action"],
					"lvl": action_xd[j]["lvl"],
					"damage_type" : action_xd[j]["damage_type"],
					"force":150+random(300),
					"dodge":random(100),
					"damage":250+random(100),
					"parry":random(30),
				]);    
			}
		
	}	
	//穿心刀

	if (me->query_temp("xddf/chuanxin")){
		return ([  
				"action": HBRED+HIW"$N脚下发力，一招「神刀穿心」使出，从极为刁钻古怪的角度反手刺向$n的前心\n"NOR,
				"lvl": action_xd[j]["lvl"],
				"damage_type" : action_xd[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(100),
				"damage":350+random(200),
				"parry":random(30),
			]);
	}
	//流星经天
	/*
	if (me->query_temp("xddf/liuxing")){
		return ([  
				"action": YEL"$N将手中刀脱手而飞，一招「流星经天」包裹一道若隐若现的红光，宛如流星划向$n\n"NOR,
				"lvl": action_xd[j]["lvl"],
				"damage_type" : action_xd[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(100),
				"damage":350+random(200),
				"parry":random(30),
			]);
	}*/
	//夜战八方诀

	if (me->query_temp("xddf/bafang")){
		for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				"action": random(2)?BLU+action[j]["action"]+NOR:HIG+action[j]["action"]+NOR,
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(30),
				"damage":200+random(100),
				"parry":random(30),
			]);
	      }
	}

//血刀刀法之金刚怒目
	if (me->query_temp("xddf/jingang")){
		return ([  
				"action": HBYEL+HIW"$N全然不顾，刀法忽然由先前的灵活多变成大力劈砍招式，一招「开天辟地」劈向$n头顶\n"NOR,
				"lvl": action_xd[j]["lvl"],
				"damage_type" : action_xd[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(100),
				"damage":350+random(200),
				"parry":random(30),
			]);
	}
	//赤练刀
	if (me->query_temp("xddf/chilian"))
	{
		if (me->query_temp("xuedao/yuxue")&&me->query_skill("xuedao-daofa",1)>449)
		{
			for(i = sizeof(action_xd); i > 0; i--)
		    if(level > action_xd[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				"action": action_xd[j]["action"],
				"lvl": action_xd[j]["lvl"],
				"damage_type" : action_xd[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(100),
				"damage":250+random(100),
				"parry":random(30),
			]);
	      }

		}
		
	}
	//祭血神刀
	if (me->query_temp("xddf/jixue1")){
		for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				"action": random(2)?RED+action[j]["action"]+NOR:MAG+action[j]["action"]+NOR,
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(30),
				"damage":220+random(100),
				"parry":random(30),
			]);
	      }
	}
	else {
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(30),
				"damage":100+random(100),
				"parry":random(30),
			]);
	   }
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("xuedao-daofa", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if (me->query("jingli") < 40)
		return notify_fail("你的体力不够，练不了血刀经。\n");
	if (me->query("neili") < 20)
		return notify_fail("你的内力不够，练不了血刀经。\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xuedao-daofa/" + action;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
	object weapon,teapon; 
	int i,damage; 
	string msg;

	weapon = me->query_temp("weapon");
	if( !objectp(weapon) ) return;
	i = me->query_skill("xuedao-daofa", 1);
	damage=i+me->query_skill("xuedao-jing", 1);
	damage=damage*3+random(damage);

	if(i> 150 
		&& me->query("jiali")
       	&& me->query("max_neili") > 1500 
		&& me->query("neili") > 1000 
		&& random(10) >= 7
       	&& (random(me->query_int()) > 30 ||random(me->query_dex()) > 30)
		&& weapon->query("id")=="xue dao"
       	&& me->query_skill_mapped("parry") == "xuedao-daofa"
       	&& random(me->query("combat_exp")) > victim->query("combat_exp")/3)
	{
		if(i<350)
			msg = HIB"$N怒啸一声，"+weapon->name()+HIB"顿时泛出赤红色的光彩，一股妖异的红色刀芒闪电而出！\n"NOR;
		else 
		{
			if(!me->query_temp("xuedao/yuxue") || !random(4))
				msg = HBBLU"突然"+weapon->name()+HBBLU"发出耀眼的光芒，整个空间立即充满了令人心悸的杀气！\n"NOR;
			else
				msg = HBBLU"$N"+weapon->name()+HBBLU"的散发出的无形刀气仿佛千万道闪电，向$n的胸口诸穴狂奔地而去。\n"NOR;				
            if(random(4)==1) victim->add_busy(2);
			me->add_temp("apply/attack",me->query_skill("xuedao-daofa",1)/4);
			me->add_temp("apply/damage",me->query_skill("xuedao-daofa",1)/4);
			if (present(victim,environment(me)) && me->is_fighting(victim))
		       COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
			me->add_temp("apply/attack",-me->query_skill("xuedao-daofa",1)/4);
			me->add_temp("apply/damage",-me->query_skill("xuedao-daofa",1)/4);
		}
		message_vision(msg, me,victim); 
	}
	
	if( random(10) >= 7
		&& i>550
       	&& me->query_skill_mapped("parry") == "xuedao-daofa"
       	&& me->query_temp("xddf/chilian"))
	{
		   switch (random(3))
		   {
				case 0:
					message_vision( HIB"$N眼神妖冶，"+weapon->name()+HIB"顿时如灵蛇婉转而行，顿时将$n圈了起来！\n"NOR,me,victim);
					message_vision( HIC"$$n眼见刀光霍霍，顿时手脚迟缓，手忙脚乱起来！\n"NOR,me,victim);

					victim->add_busy(2);
					if (!victim->query_condition("no_perform"))
						victim->apply_condition("no_perform",1);
					break;
				case 1:
					message_vision( HIM"$N手中的"+weapon->name()+HIM"刀尖顺势一转，一刀刺中$n的臂膀！\n"NOR,me,victim);
					victim->receive_damage("qi",damage,me);
					victim->receive_wound("qi",damage/5,me);
					break;
		   		case 2:
					message_vision( RED"$N轻轻晃动"+weapon->name()+RED"，刀光如蛇，蜿蜒而行，瞬间缠上$n的手腕！\n"NOR,me,victim);
					if (random(me->query_skill("xuedao-daofa",1))>victim->query_skill("parry",1)/2)
					{
						message_vision( RED"$n一时不查，为"+weapon->name()+RED"，缠中手腕，只觉得手腕一痛，顿时断为数节！！\n"NOR,me,victim);
						victim->set("jiali",0);
						victim->apply_condition("broken_arm",1); 
						//victim->receive_damage("qi",damage,me);
						victim->receive_wound("qi",damage/2,me);

					}
					else 
						message_vision( RED"$N劲气发动，轻轻一抖，摆脱了$n的纠缠！\n"NOR,me,victim);

					break;

		   }
		
	}
}
