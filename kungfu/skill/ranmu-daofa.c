// ranmu-daofa.c 燃木刀法

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([
	"action" : "$N面带微笑，一招「烈火烧身」，举$w对着$n连环砍了八八六十四刀，刀气纵横，宛如烈火般扑向$p，迅雷不可挡",
	"lvl" : 0,
	"skill_name" : "烈火烧身",
	"damage_type" : "割伤"
]),
([
	"action" : "$N运起内功一招「点木生火」，在$w上带出火红的无比劲气，迅速划了一个大弧，从上而下劈向$n的$l",
	"lvl" : 30,
	"skill_name" : "点木生火",
	"damage_type" : "割伤"
]),
([
	"action" : "$N手臂一沉一拉，使出「张弓望月」，双手持着$w划出一道雪亮刀光，就在$n躲避之时猛地拦腰反切，劈向$n的$l",
	"lvl" : 60,
	"skill_name" : "张弓望月",
	"damage_type" : "割伤"
]),
([
	"action" : "$N挥舞$w上劈下撩，左挡右开，使出一招「烈火腾云」，卷起阵阵刀风，每一圈都都划出不同的气流，齐齐罩向$n",
	"lvl" : 90,
	"skill_name" : "烈火腾云",
	"damage_type" : "割伤"
]),
([
	"action" : "$N一招「火中取栗」，划个大圈后左脚跃步落地，手中$w往前直伸，刀走剑势，挟着炙热的风声点向$n的$l",
	"lvl" : 120,
	"skill_name" : "火中取栗",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N腾空而起，半空中一招「玉石俱焚」猛烈扑下，手中$w迅速连劈，满天流光般的刀影排山倒海般地向$n的全身卷去",
	"lvl" : 150,
	"skill_name" : "玉石俱焚",
	"damage_type" : "割伤"
]),
});
/*
mapping *sd_action = ({
([
	"action" : "$N面带微笑，一招「烈火烧身」，举手掌对着$n连环砍了八八六十四刀，刀气纵横，宛如烈火般扑向$p，迅雷不可挡",
	"lvl" : 0,
	"skill_name" : "烈火烧身",
	"damage_type" : "割伤"
]),
([
	"action" : "$N运起内功一招「点木生火」，在手中以内劲带出火红的劲气，迅速划了一个大弧，从上而下劈向$n的$l",
	"lvl" : 30,
	"skill_name" : "点木生火",
	"damage_type" : "割伤"
]),
([
	"action" : "$N手臂一沉一拉，使出「张弓望月」，双手合掌划出一道刀气，就在$n躲避之时猛地拦腰反切，劈向$n的$l",
	"lvl" : 60,
	"skill_name" : "张弓望月",
	"damage_type" : "割伤"
]),
([
	"action" : "$N挥舞双掌上劈下撩，左挡右开，使出一招「烈火腾云」，卷起阵阵刀风，每一圈都都划出不同的气流，齐齐罩向$n",
	"lvl" : 90,
	"skill_name" : "烈火腾云",
	"damage_type" : "割伤"
]),
([
	"action" : "$N一招「火中取栗」，划个大圈后左脚跃步落地，手中单掌往前直伸，刀走剑势，挟着炙热的风声点向$n的$l",
	"lvl" : 120,
	"skill_name" : "火中取栗",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N腾空而起，半空中一招「玉石俱焚」猛烈扑下，双掌迅速连劈，满天流光般的刀影排山倒海般地向$n的全身卷去",
	"lvl" : 150,
	"skill_name" : "玉石俱焚",
	"damage_type" : "割伤"
]),
([
	"action" : "$N腾空而起，半空中一招「玉石俱焚」猛烈扑下，双掌迅速连劈，满天流光般的刀影排山倒海般地向$n的全身卷去",
	"lvl" : 150,
	"skill_name" : "玉石俱焚",
	"damage_type" : "割伤"
]),
});
*/

int valid_enable(string usage) { return usage == "blade" || usage == "parry"|| usage == "strike"; }

int valid_learn(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");

	if ((int)me->query_skill("riyue-bian",1)
	 || (int)me->query_skill("weituo-chu",1)
	 || me->query("passdu"))
		return notify_fail("你如果有达摩老祖的修为，方可同时学习少林三绝技。\n"); 

	if(!me->query("family") || me->query("family/family_name")!="少林派" )
		return notify_fail("你不是少林弟子，如何能用这燃木刀法？\n");

	if ( me->query("max_neili") < 1500)
		return notify_fail("你的内力不够。\n");
	if ( me->query_skill("riyue-bian",1) > 1)
		return notify_fail("你已经修习了少林三大兵器绝技之一日月鞭，无法修习燃木刀绝技。\n");
	if ( me->query_skill("weituo-chu",1) > 1)
		return notify_fail("你已经修习了少林三大兵器绝技之一韦陀杵，无法修习燃木刀绝技。\n");

	if ( me->query_skill("yijin-jing", 1) < 160)
		return notify_fail("你的易筋经内功火候太浅。\n");
	if ( me->query_skill("buddhism") < 220)
	{
		if ( me->query_skill("weituo-chu", 1)
		 || me->query_skill("riyue-bian", 1))
			return notify_fail("你的佛法领悟力不够，无法同时修习两种以上的上乘兵器功夫。\n");
	}

	if ( me->query_skill("ranmu-daofa",1) <= 200
		&& me->query_skill("cibei-dao",1) <=450)
		return notify_fail("你的慈悲刀火候不够450，领悟不了燃木刀。\n");

	if ( me->query_skill("ranmu-daofa",1) <= 200
		&&  me->query_skill("xiuluo-dao",1) <= 350)
		return notify_fail("你的修罗刀火候不够350，领悟不了燃木刀。\n");
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
	string msg;
	level = (int) me->query_skill("ranmu-daofa",1);

	if ( me->query_temp("rmdf/fenmo")){
		return ([
			"action": HIR"$N双掌夹刀合十，手中的"+weapon->name()+HIR"顿时升起一团火焰将自己包围，\n$P猛宣一声佛号，一刀直劈向$n" NOR,
			"damage": 200+ random(140),
			"dodge" : -60+random(40),
			"parry": -110+random(60),
			"force": 300 + random(350),
			"damage_type": "割伤"
		]);
	}
	//燃木刀法-手刀
	if (me->query_temp("rmdf/shoudao"))
	{
		switch(me->query_temp("rmdf/shoudao"))
		{
			case 5: msg = HIR"$N左掌虚控，右掌挥动，凝气于右掌，猛然间以手化刀，一招「燃木生火」式，削向$n的左臂"NOR; break;
			case 4: msg = HIR"紧接着$N右掌虚招，将腰身一扭，左掌顺势使出一招「风吹火旺」，雄浑劲气涌来，裹向$n周身"NOR; break;
			case 3: msg = HIR"只见$N左掌劲力未消，便凌空一转，双手合掌，顺势扫出一招「烈火腾云」压向$n"NOR; break;
			case 2: msg = HIR"半空中$N身子向前翻滚，已经运起易筋经的功夫「玉石俱焚」，内劲直透双掌，在$n胸腹处连拍了数十下"NOR; break;
			case 1: msg = HIR"这时$N双臂展动，带起一股强烈的旋风，双手霎时齐并,一招「焚天灭地」削在$n胸口之上"NOR; break;
		}
		me->add_temp("rmdf/shoudao", -1);                  
		return([
			"action": msg,
			"force" : 300+random(200),
			"dodge" : random(35),
			"parry" : random(35),
            "damage": 250 + random(140),
			"damage_type" : "内伤",
		]);
	}

	for(i = sizeof(action); i > 0; i--) 
	{
		if(level > action[i-1]["lvl"]) 
		{
			j = NewRandom(i, 20, level/5);
					
			return ([
				"action": action[j]["action"],
				"damage_type": action[j]["damage_type"],
				"lvl": action[j]["lvl"],
				"force": 200 + random(350),
				"dodge": random(30)-10,
				"damage": 80 + random(140),
				"parry": -20-random(20),
			]);
		}
	}
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 50 )
		return notify_fail("你的精力不够练燃木刀法。\n");

	if ((int)me->query("neili") < 20 )
		return notify_fail("你的内力不够练燃木刀法。\n");
	if ( me->query_skill("buddhism") < 220)
	{
		if ( me->query_skill("weituo-chu", 1)
		 || me->query_skill("riyue-bian", 1))
			return notify_fail("你的佛法领悟力不够，无法同时修习两种以上的上乘兵器功夫。\n");
	}

	me->receive_damage("jingli", 40);
	me->add("neili",-15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"ranmu-daofa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	if( userp(me)
	// && me->query_temp("fenwo_hit")
	 && victim->query("combat_exp") >= me->query("combat_exp")/2
	 && me->query("rmdf/fenmo") < me->query_skill("blade",1))
		me->add("rmdf/fenmo", 1); // for rmd's fenwo pfm
	

}
