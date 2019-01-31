
#include <ansi.h>
#include <combat.h>
inherit SKILL;
#include <combat_msg.h>

mapping *action = ({
([	"action" : "$N向前跨上一步，同时口中大喊一声，一式「"+HIG"哥翁喊上来"NOR+"」直刺$n的$l",
	"force" :random(30)+ 60,
	"dodge" : 5,
	"damage" : 20,
        "lvl" : 0,
	"damage_type" : "刺伤"
]),
([      "action" : "$N向前轻跳，一招「"+HIB"马命风小小"NOR+"」，剑光渺茫莫测，$w向前轻刺$n的$l",
        "force" :random(30)+ 80,
        "dodge" : 15,
        "damage" : 25,
        "lvl" : 10,
        "damage_type" : "刺伤",
]),
([      "action" : "$N左手耳朵一招，仿佛在倾听什么，一招「"+HIW"忽听喷惊风"NOR+"」，右手中的$w向前刺向$n的$l",
        "force" :random(30)+ 100,
        "dodge" : 5,
        "damage" : 35,
        "lvl" : 20,
        "damage_type" : "刺伤",
]),
([      "action" : "$N手中$w急转，一式「"+HIY"连山布若逃"NOR+"」，手中$w的剑势像一疋布一样砍向$n的$l",
        "force" :random(30)+ 120,
        "dodge" : 10,
        "damage" : 40,
        "lvl" : 30,
        "damage_type" : "割伤",
]),
([      "action" : "$N剑招忽变，$w胸前一横，歪歪斜斜地使出一式「"+HIR"是横不敢过"NOR+"」，$w横削$n",
        "force" :random(30)+ 140,
        "dodge" : -5,
        "damage" : 45,
        "lvl" : 40,
        "damage_type" : "割伤",
]),
([  	"action" : "$N剑尖斜指向地，向后一闪，一招「"+HIC"落泥招大姐"NOR+"」，招手让$n过来，$w随即刺出",
    	"force" :random(30)+ 160,
    	"dodge" : 15,
    	"damage" : 50,
    	"lvl" : 50,
    	"damage_type" : "刺伤",
]),
([      "action" : "$N将$w胸前一横，门户大开，忽然倒地，吟道「"+HIR"闯前门越广，疑尸地上爽"NOR+"」，蕴含无限杀机",
        "force" :random(30)+ 140,
        "dodge" : -50,
        "damage" : 200,
        "lvl" : 200,
        "damage_type" : "割伤",
]),
([  	"action" : "$N头向上抬，剑尖冲下，面带必死之心，施展「"+HIC"举头亡命也，低头死故乡"NOR+"」$w连环两招刺出。",
    	"force" :random(30)+ 160,
    	"dodge" : 15,
    	"damage" : 150,
    	"lvl" : 350,
    	"damage_type" : "刺伤",
]),
([      "action" : "$N将$w横放手腕，好像在拧动什么，轻吟道「"+HIY"两个黄梨拧脆了，一行白骆丧今天"NOR+"」",
        "force" :random(30)+ 140,
        "dodge" : -50,
        "damage" : 185,
        "lvl" : 450,
        "damage_type" : "割伤",
]),
([  	"action" : "$N施展躺尸剑法不传之秘，「"+CYN"白日一扇近，长活如海流"NOR+"」招式宛如长江大河，$w挥舞，招式滔滔不绝",
    	"force" :random(30)+ 160,
    	"dodge" : 15,
    	"damage" : 200,
    	"lvl" : 550,
    	"damage_type" : "刺伤",
]),
});
mapping *action_ts = ({

([	"action" : HIG"$N已经明白唐诗剑法精意，施展出「孤鸿海上来」,姿势飘渺，宛如天际飞鸿，招式凌冽，直刺$n的$l"NOR,
	"force" :random(30)+ 60,
	"dodge" : 5,
	"damage" : 40+random(40),
        "lvl" : 100,
	"damage_type" : "刺伤"
]),
([      "action" : HIB"$N身子后倾，一招「马鸣风萧萧」，剑光渺茫莫测，向前轻刺$n的$l"NOR,
        "force" :random(30)+ 80,
        "dodge" : 15,
        "damage" :50+random(50),
        "lvl" : 120,
        "damage_type" : "刺伤",
]),
([      "action" : HIY"$N左手耳朵一招，仿佛在倾听什么，一招「俯听闻惊风」,向前刺向$n的$l"NOR,
        "force" :random(30)+ 100,
        "dodge" : 5,
        "damage" : 80+random(80),
        "lvl" : 150,
        "damage_type" : "刺伤",
]),
([      "action" : HIC"$N招式急转，一式「连山若波涛」，剑势化作像一片刀势，砍向$n的$l"NOR,
        "force" :random(30)+ 120,
        "dodge" : 10,
        "damage" : 90+random(90),
        "lvl" : 200,
        "damage_type" : "割伤",
]),
([      "action" : MAG"$N剑招忽变，胸前一横，歪歪斜斜地使出一式「池潢不敢顾」,横削$n的$l"NOR,
        "force" :random(30)+ 140,
        "dodge" : -5,
        "damage" : 100+random(100),
        "lvl" : 250,
        "damage_type" : "割伤",
]),
([  	"action" :HIM "$N剑尖斜指向地，向后一闪，一招「落日照大旗」，招手让$n过来，随即刺出,剑气纵横。"NOR,
    	"force" :random(30)+ 160,
    	"dodge" : 15,
    	"damage" : 110+random(110),
    	"lvl" : 350,
    	"damage_type" : "刺伤",
]),
([      "action" : HIR"$N剑气浩荡，宛如长江大河，其中蕴含「白日依山尽，黄河入海流」的气势，汇集成一片浩荡的剑影，"NOR,
        "force" :random(30)+ 140,
        "dodge" : -5,
        "damage" : 120+random(120),
        "lvl" : 450,
        "damage_type" : "割伤",
]),
([  	"action" :HIW"$N剑势出现飘渺之境，一股苍凉之意喷涌而出，正是唐诗剑法的绝技「欲穷千里目，更上一层楼」"NOR,
    	"force" :random(30)+ 160,
    	"dodge" : 15,
    	"damage" : 140+random(140),
    	"lvl" : 550,
    	"damage_type" : "刺伤",
]),

});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level   = (int) me->query_skill("tangshi-jianfa",1);
	if ( me->query_temp("tangshi/erguang")){
			return ([
				"action": random(2)?HIW"$N左手捏个剑诀，右手长剑陡然递出，猛地里剑交左手，右手反过来拍的一声耳光"NOR:HIY"$N右手捏个剑诀，左手长剑陡然递出，猛地里剑交右手，左手反过来拍的一声耳光"NOR,
                 "force" :random(30)+ 160,
    	        "dodge" : 15,
    	        "damage" : 250+random(100),
    	        "lvl" : 150,
    	        "damage_type" : "内伤",
			]);
                
	}
	
	if ( me->query_temp("tangshi/cijian")){
			return ([
				"action": random(2)?HIC"$N长啸一声，招数猛然加快，$n挡得几招，$N突然间长剑抖动，卟的一声轻响刺向$n的左肩。"NOR:MAG"$N手中兵器越来越快，$n眼中一花，$N突然间长剑抖动，卟的一声轻响刺向$n的右肩。"NOR,
                 "force" :random(30)+ 160,
    	         "dodge" : 15,
    	        "damage" : 350+random(100),
    	         "lvl" : 150,
    	         "damage_type": "刺伤"
			]);                
	}

	if (me->query_temp("tangshi/shiyin"))
	{
		for(i = sizeof(action_ts); i > 0; i--)
                if(level > action_ts[i-1]["lvl"])
                        return action_ts[NewRandom(i, 20, level/5)];
	}
	else
	{
	for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
	}
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query("jingli") < 30)
		return notify_fail("你的精力不够练躺尸剑法。\n");
	me->receive_damage("jingli", 20);
	return 1;
}
string perform_action_file(string action)
{
	return __DIR__"tangshi-jianfa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	object weapon, weapon1; 
	weapon = me->query_temp("weapon");
	weapon1= victim->query_temp("weapon");
	if( !objectp(weapon) ) return;
	if (me->query_skill_mapped("sword")!="tangshi-jianfa" ||me->query_skill_mapped("parry")!="tangshi-jianfa") return;
  	
	if(!me->query_temp("tangshi/shiyin")) return;
  
	if(weapon && weapon1 &&random(10)>5)
    {
	   if(random(2))
		   message_vision(HIC"忽然，$N翻过"+weapon->name()+HIC"，平靠"+weapon1->name()+HIC"，$n的"+weapon->name()+HIC"施展「去剑式」招式。\n"NOR, me,victim);
	   else 
		   message_vision(HIY"紧跟着，$N"+weapon->name()+HIY"一伸，搭住"+weapon1->name()+HIY"，"+weapon->name()+HIY"将$n劲力全引到了相反的方向。\n"NOR, me,victim);

	   if(random(me->query_str()) > victim->query_str()/3)
	   {           
           		me->add("neili", -50);
           		message_vision(HIR"$N招式渐见涩滞，"+weapon1->name()+HIR"拿捏不住，脱手飞出！\n"NOR, victim);
           		weapon1->unequip();
           		weapon1->move(environment(victim));
        }
      	else {
           		message_vision(HIC"$N招式渐见涩滞，手臂酸麻"+weapon1->name()+HIR"差点拿捏不住！\n"NOR, victim);
			    victim->add_busy(1);
       }
	   
	}
	if (random(me->query_skill("tangshi-jianfa",1))>victim->query_skill("parry",1)/2 
		&&random(10)>6)
	{
		message_vision(HIY"$N忽然剑法突变，一阵急颤动"+weapon->name()+HIY",发出一片刺目的剑光，施展出「刺肩式」的招式。\n"NOR, me,victim);
		victim->receive_damage("qi",damage_bonus,me);
		victim->receive_wound("qi",damage_bonus/4,me);
		victim->apply_condition("no_exert",2);

	}
    
}

