// canglang-goufa.c 沧浪钩法
// by aug   99.9.10

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([
	"action" : "$N双脚并步，身体立起，一招「莲叶托桃」，$w向前平刺$n的档部",
	"lvl" : 0,
	"skill_name" : "莲叶托桃",
	"damage_type" : "割伤"
]),
([
	"action" : "$N一招「群魔乱舞」，$w舞动护住全身向$n撞去",
	"lvl" : 40,
	"skill_name" : "群魔乱舞",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N使一招「尔虞我诈」，右脚向后回撤，$w随身体右后撤，突然向左前方刺向$n的左手",
	"lvl" : 80,
	"skill_name" : "尔虞我诈",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N一招「殊路同归」，$w中宫直进，一上一下刺向$n的右肩",
	"lvl" : 100,
	"skill_name" : "殊路同归",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N右手$w向后撤，再向前平平托起，一招「描龙绣凤」刺向$n的右脸",
	"lvl" : 140,
	"skill_name" : "描龙绣凤",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N一转身，$w向后斜带，一招「飞横拔户」，砍向$n的左臂",
	"lvl" : 160,
	"skill_name" : "飞横拔户",
	"damage_type" : "割伤"
]),
([
	"action" : "$N右脚向前一步，左膝提起，一招「不阴不阳」，$w向前上方刺向$n的后心",
	"lvl" : 180,
	"skill_name" : "不阴不阳",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N一反身，使一招「鱼死网破」，$w不顾一切得劈向$n的腰间",
	"lvl" : 200,
	"skill_name" : "鱼死网破",
	"damage_type" : "割伤"
]),
});

int valid_enable(string usage) { return usage == "hook" || usage == "parry"; }

int valid_learn(object me)
{
	object weapon;
	if (me->query("family/family_name")!="神龙教" )
		return notify_fail("沧浪钩法只能神龙教弟子使用请教。\n");
	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "hook")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query("max_neili") < 50)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("dulong-dafa", 1) < 20)
		return notify_fail("你的毒龙大法火候太浅，无法学习沧浪钩法。\n");
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
	int i,level,temp,j;
	object target;
	object *enemy;
        level = me->query_skill("canglang-goufa",1);

	enemy = me->query_enemy();
	if(sizeof(enemy) > 0) {
		target = enemy[random(sizeof(enemy))];
		temp = target->query_skill("dodge");
		if (!temp) temp=1;

		i = me->query_skill("hook",1)*100 / temp;
		if( i > 200) i=200;
		if( i < 50) i=50;
		if ( random(300) < (50+i) && me->query("neili") > 500 && !random(4))
			if ( me->query_skill_prepared("leg")=="shenlong-tuifa"
			 && me->query_skill("dulong-dafa",1) > 450 
			 && me->query_skill("canglang-goufa",1) > 450 
			 && me->query_skill("huagu-mianzhang",1) > 450 
			 && me->query_skill_mapped("force")=="dulong-dafa" )
				call_out("autopfm",1,me,target);
	}
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 150 +random(300),
				"dodge": random(30),
				"parry": random(30),
				"damage": 60 + random(100),
			]);
		}
	}
}

mixed hit_ob(object me, object target)
{
	string msg;
	object tweapon;
	object weapon=me->query_temp("weapon");
	object *inv;

	if (!weapon||!target) return;
	tweapon=target->query_temp("weapon");

	if ( random(me->query_str(1)) >= target->query_str(1)/3
	 && random(10) > 5
	 && me->query("jingli") > 300
	 && weapon
	 && weapon->query("skill_type")=="hook"
	 && me->query("gender")=="男性"
	 && me->query_skill_mapped("hook")=="canglang-goufa"
	 && me->query_temp("clgf/canglang")
	 && random(me->query("combat_exp")) > random(target->query("combat_exp")/2)
	 && me->query("env/沧浪钩法")=="钩" 
	 && me->query("neili") > 500) 
     {
		 
		   
		   
		   switch(random(5)) 
		  {
			case 0 :
				if (tweapon)
				{
					message_vision(HIM"$N左手虚控，右手"+weapon->query("name")+HIM"的钩头勾住对方的"+tweapon->query("name")+HIM"斜上一划！\n"NOR,me,target);
					if (random(me->query_skill("canglang-goufa",1))>target->query_skill("parry",1)/2)
					{
						message_vision(CYN"$N觉得一股大力传来，根本把持不住，手中兵器脱手而出！\n"NOR,target);
						tweapon->move(environment(target));
					}

				}else {
					message_vision(HIR"$N左手虚控，右手"+weapon->query("name")+HIR"的钩头勾住$n的防具关键点上，斜上一划，顿时将对方的防具划破！\n"NOR,me,target);
					target->receive_damage("qi",2000+random(500),me);
					target->receive_wound("qi",1000+random(500),me);
				}
				
				break;
			case 1 :
				message_vision(HIW"$N双钩并举，交叉一起，然后向外猛然一拉，力道极为凶猛！\n"NOR,me);
				if (tweapon&&weapon->query("sharpness")>tweapon->query("rigidity"))
				{
					message_vision(WHT"\n结果$n手中"+tweapon->query("name")+WHT"应手而断！\n"NOR,me,target);
					tweapon->unequip();
					tweapon->move(environment(target));
					tweapon->set("name", "断掉的" + tweapon->query("name"));
					tweapon->set("value", 49);
					tweapon->set("weapon_prop", 0);
					target->reset_action();
				
				}else{
					message_vision(WHT"\n虽然躲过这招凶猛的斜拉招式，但仓促间却也为钩头所伤！\n"NOR,me,target);

					target->apply_condition("no_exert",1);
					target->receive_wound("qi",2000+random(1000),me);
				}
				break;
			case 2 :
				message_vision(HIC"$N用手中的双钩一钩一拉，形成一股巨大的拉扯之力，$n一个站立不稳，身体转动起来，宛如陀螺！”。\n"NOR,me,target);
				message_vision(HIR"$n只觉得自己天旋地转，身形无法控制！\n"NOR,me,target);

			  	target->add_busy(2);
				target->receive_wound("jing",1000+random(1000),me);
				break;
			default:break;

		}
			
		
	}
	
}

void autopfm(object me,object target)
{
	object weapon,weapon1;
	int i;

	if(!me || !target ) return;
	weapon = me->query_temp("weapon");
	weapon1 = target->query_temp("weapon");  
	
	if(!weapon) return;
	if ( me->add("neili",-75) <0 ) me->set("neili",0);

	i = me->query_skill("canglang-goufa", 1);
	me->add_temp("apply/attack",i/4);
	//if (!me->query("quest/sld/clgf/canglang/pass")) return;
	
	if (me->query("env/沧浪钩法")=="钩")
	{
	
		if(target->query_temp("weapon"))
		{
			message_vision(HIC"\n$N手中"+weapon->query("name")+HIC"连晃了四、五个虚招，$n一个没留神就给锁住了兵器！\n$N乘机连出两、三掌！"NOR,me,target);
			weapon1->move(environment(me)); 
			weapon->unequip(); 
			if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, 0, random(3)?1:3);
			if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, 0, random(3)?1:3);
			if (me->is_fighting(target) && random(2)==1) COMBAT_D->do_attack(me, target, 0, 3);
			weapon->wield(); 
		}
		else {
			message_vision(HIC"\n$N手中"+weapon->query("name")+HIC"连晃了四、五个虚招，$n一个没留神就给$N钩住了手脚！\n$N乘机又连出了$n两掌！"NOR,me,target);
			weapon->unequip(); 
			if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, 0, 1);
			if (me->is_fighting(target) && random(2)==1) COMBAT_D->do_attack(me, target, 0, 3);
			weapon->wield(); 
		}
	}
	me->add_temp("apply/attack",-i/4);
}

int practice_skill(object me)
{
	int lvl = me->query_skill("canglang-goufa", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

        if ((int)me->query("jingli") < 40)
                return notify_fail("你的体力不够练沧浪钩法。\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("你的内力不够练沧浪钩法。\n");
        me->receive_damage("jingli", 30);
        me->add("neili", -10);
        return 1;
}

string perform_action_file(string action)
{
	return __DIR__"canglang-goufa/" + action;
}
