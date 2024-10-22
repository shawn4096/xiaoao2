// sixiang-zhang.c -四象掌

inherit SKILL;
#include <ansi.h>
mapping *action = ({
([
	"action" : "$N向$n遥遥一鞠，一式「三阳开泰」，双掌大开大阖，挡开$n的进击！",
	"damage_type" : "瘀伤",
	"lvl" : 0,
	"skill_name" : "三阳开泰"
]),
([
	"action" : "紧跟着$N面含微笑，一式「五气呈祥」，双掌云缠雾绕，同时攻向$n全身各处！",
	"damage_type" : "瘀伤",
	"lvl" : 10,
	"skill_name" : "五气呈祥"
]),
([
	"action" : "$N划身错步，一式「逆流捧沙」，双掌内拢外托，攻向$n的左肩！",
        "damage_type" : "劈伤",
	"lvl" : 20,
	"skill_name" : "逆流捧沙"
]),
([
	"action" : "$N一式「雷洞霹雳」，双掌以迅雷不及掩耳之势，劈向$n的两额太阳穴！",
        "damage_type" : "瘀伤",
	"lvl" : 30,
	"skill_name" : "雷洞霹雳"
]),
([
	"action" : "$N使一式「摘星换斗」，劲气弥漫，双掌如轮，一环环向$n的后背斫去",
        "damage_type" : "劈伤",
	"lvl" : 40,
	"skill_name" : "摘星换斗"
]),
([
	"action" : "$N一式「梵心降魔」，双掌似让非让，似顶非顶，气浪如急流般使$n陷身其中！",
	"damage_type" : "瘀伤",
	"lvl" : 50,
	"skill_name" : "梵心降魔"
]),
});
string perform_action_file(string action)
{
        return __DIR__"sixiang-zhang/" + action;
		//return __DIR__ "shigu-bifa/" + action;
}
int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练四象掌必须空手。\n");
	if ( me->query_skill("linji-zhuang", 1) < 20)
		return notify_fail("你的临济十二庄火候不够，无法学习四象掌。\n");
	if ( me->query("max_neili") < 150)
		return notify_fail("你的内力太弱，无法练四象掌。\n");
	return 1;
}
int valid_combine(string combo) 
{
	return combo == "jieshou-jiushi";
}
string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me,object weapon)
{
	int i, level, j;

	if ( me->query_skill("sixiang-zhang", 1) > 80
	 && me->query_skill("linji-zhuang", 1) > 80
	 && me->query_skill("strike", 1) > 80
	 && me->query("neili") > 500
	 && random(me->query_int(1)) > 25
	 && !random(3)
	 && environment(me)->query("outdoors")) {
		me->add("neili", -60);
		return ([
	        "action":HIY"霎时间,日丽风静，云海平铺，美丽以极。阳光从$N背面斜射下来，形成彩色光环，\n"+
				"$N见到自己的身影清晰地出现在银色世界上。$N在战斗间隙瞬间顿悟到\n"+
				HIC+"『光环随人动，人影在环中』"HIY"，使出了"+HIW"四象掌绝学"HIY"『金顶佛光』"NOR,
			"weapon" : HIY"金顶佛光"NOR,
			"force": 500,
			"dodge": 15,
			"parry": 15,
			"damage": 250+random(100),
			"damage_type": "瘀伤"
		]);
	}

        level   = (int) me->query_skill("sixiang-zhang",1);
        for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"weapon": action[j]["weapon"],
				"force":150+random(300),
				"dodge":random(30),
				"damage": 100+random(100),
				"parry":random(30),
			]);
		}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("sixiang-zhang", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;
	if (me->query("jingli") < 40)
		return notify_fail("你的精力太低了。\n");
	if (me->query("neili") < 20)
		return notify_fail("你的内力不够练四象掌。\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}
