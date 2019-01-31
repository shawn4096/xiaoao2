// wuhu-duanmendao.c 五虎断门刀
// Modified By Numa@SJ 2000.7

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N将手中$w向右一立，随即吸气用力一纵，以「猛虎下山」之势扑向$n",
	"damage_type" : "割伤",
	"lvl" : 0,
	"skill_name" : "猛虎下山"
]),
([
	"action" : "$N一招「西风倒卷」，手中$w由下拖上直直划过$n小腹",
	"damage_type" : "割伤",
	"lvl" : 40,
	"skill_name" : "西风倒卷"
]),
([
	"action" : "$N身体由左至右旋转一周，手中$w则以一招「飞沙走石」扬向$n",
	"damage_type" : "割伤",
	"lvl" : 80,
	"skill_name" : "飞沙走石"
]),
([
	"action" : "$N全身运力一跃，约莫丈许高时急速下窜，一招「天昏地暗」直取$n顶门",
	"damage_type" : "割伤",
	"lvl" : 120,
	"skill_name" : "天昏地暗"
]),
([
	"action" : "$N蹲了一个马步，劲力皆运于$w之上，以一招「横扫天下」直逼$n双膝",
	"damage_type" : "割伤",
	"lvl" : 150,
	"skill_name" : "横扫天下"
]),
([
	"action" : "$N口中突然暴喝，左手画了个圆圈，右手以刀柄抵住手掌，一招「气吞山河」向$n猛压下去",
	"damage_type" : "割伤",
	"lvl" : 200,
	"skill_name" : "气吞山河"
]),
});

int valid_enable(string usage) {return (usage == "blade") || (usage == "parry");}

int valid_learn(object me)
{
	object weapon;

	if (!me->query("mao18/pass"))
	//if ( me->query_skill("wuhu-duanmendao", 1) < 150)
		return notify_fail("你尚未解开「五虎断门刀」绝学。\n");
	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query("max_neili") < 300)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("blade", 1) < 30)
		return notify_fail("你的基本刀法火候不够。\n");
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
	int i, level, j,n;
	string msg;
	level   = (int) me->query_skill("wuhu-duanmendao",1);

	
	//五虎刀绝技
	
	if (intp(n = me->query_temp("whdmd/wuhu")) && n > 0 )
	{
		 switch(n){
			case 4: msg = HIR"$N施展出「"HIW"白虎跳涧"HIR"」招式，一个飞跃，挥刀向$n猛然间劈了下去,气势威猛\n"NOR; break;
            case 3: msg = HIW"$N忽然间大喝一声，施展出"HIR"「一啸风生」"HIW"，绝技，趁$n一愣间，挥刀直劈$n的前胸"NOR; break;
			case 2: msg = HIG"$N刀势向下一劈，趁刀势未止，反手撩刀，正是五虎断门刀绝招"HIB"「剪扑自如」"NOR;break;
            case 1: msg = HIY"$N双手举刀，一招「"HIC"雄霸群山"HIY"」刀势不做任何变化，但却威力极其巨大\n"NOR; break;
            case 0: msg = HIM"$N手中刀势抖动，使出一招"HIW"「伏象胜狮」"HIM"将敌上半身尽数罩住，趁敌守护之机，连续出了两刀\n"NOR;break;
                  			  
         }	
		 
			return ([  
					"action" : msg,
					"force" : 150 +random(300),
					"dodge": random(30),
					"damage": 250 + random(50),
					"lvl" : action[j]["lvl"],
					"parry": random(30),
					"weapon" : random(2)?"刀气":"刀锋",
					"damage_type" : random(2)?"劈伤":"砍伤",
			]);
	}
	

	if( random(10) > 5
	&& me->query_skill("blade", 1) >= 120
	&& level >= 120
	&& me->query_skill("force") >= 150
	&& me->query("neili") >= 500
	&& random(level) >= 100 ) {
		me->add("neili", -25);
		
		//
		if (me->query("mao18/pass2")) {
			if (me->query("mao18/pass3"))
				
				switch (random(6)) {
					case 0 :
					case 2 :
					case 4 :
						return ([
							"action":	HIY"$N运气于胸，手中$w对着$n狂舞，这一式「"HIR"五虎断门"HIY"」绝学顿将$n围在刀光之中"NOR,
                            "damage":	300,
							"force":	550,
							"dodge":	random(20),
							"parry":	random(20),
							"damage_type":	"割伤"
						]);
						break;
					case 1 :
					case 3 :
						return ([
							"action":	HIR"$N双手紧攥手中$w，两眼圆瞠，猛然一式「猛虎下山」恶狠狠的扑向$n"NOR,
							"damage":	250,
							"force":	500,
							"dodge":	random(20),
							"parry":	random(20),
							"damage_type":	"割伤"
						]);
						break;
					case 5 :
						return ([
							"action":	HIC"$N目露凶光，待$n踏近前时，一式「饿虎扑食」将手中$w向$n挥舞开去"NOR,
							"damage":	220,
							"force":	450,
							"dodge":	random(20),
							"parry":	random(20),
							"damage_type":	"割伤"
						]);
						break;
				}
			else
				switch (random(3)) {
					case 0 :
					case 2 :
						return ([
							"action":	HIR"$N双手紧攥手中$w，两眼圆瞠，猛然一式「猛虎下山」恶狠狠的扑向$n"NOR,
							"damage":	200,
							"force":	500,
							"dodge":	random(20),
							"parry":	random(20),
							"damage_type":	"割伤"
						]);
						break;
					case 1 :
						return ([
							"action":	HIC"$N目露凶光，待$n踏近前时，一式「饿虎扑食」将手中$w向$n挥舞开去"NOR,
							"damage":	180,
							"force":	450,
							"dodge":	random(20),
							"parry":	random(20),
							"damage_type":	"割伤"
						]);
						break;
				}
		}
		else
			return ([
				"action":	HIC"$N目露凶光，待$n踏近前时，一式「饿虎扑食」将手中$w向$n挥舞开去"NOR,
				"damage":	160,
				"force":	450,
				"dodge":	random(30),
				"parry":	random(30),
				"damage_type":	"割伤"
			]);
	}
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action":	action[j]["action"],
				"damage_type":	action[j]["damage_type"],
				"lvl":		action[j]["lvl"],
				"force":	200 + random(350),
				"damage":	80 + random(140),
				"dodge":	random(30)-10,
				"parry":	random(20),
			]);
		}
	}
}

int practice_skill(object me)
{
	if ( me->query("jingli") < 50)
		return notify_fail("你的体力不够练五虎断门刀法。\n");
	if ( me->query("neili") < 20)
		return notify_fail("你的内力不够练五虎断门刀法。\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"wuhu-duanmendao/" + action;
}
