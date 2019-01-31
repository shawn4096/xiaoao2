//金蛇缠丝手
// by sjxa@winnerlife
//2014-08-07
//edit buy sohu  chansi-shou.c
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : HIY"[缠]"HIB"$N眼中闪过一丝历芒，十指并拢，双手闪电般分前后齐出，分别缠向$n的左右双臂"NOR ,
"damage_type" : "瘀伤",
"lvl" : 0,
"skill_name" : "[缠]",
]),
([      "action" : HIY"[绕]"HIB"$N双臂如若无骨，以不可思议的角度直袭$n的后颈["HIG"大椎穴"HIB"]，令$n感觉招式滞涩无从下手"NOR,
"damage_type" : "瘀伤",
"lvl" : 20,
"skill_name" : "[绕]",
]),
([      "action" : HIY"[环]"HIB"$N轻吸一口气，全身骨骼发出一阵轻响，双臂成环，以匪夷所思的柔软度罩向$n脖子，然后迅速的一勒"NOR,
"damage_type" : "瘀伤",
"lvl" : 40,
"skill_name" : "[环]",
]),
([      "action" : HIY"[转]"HIB"$N脚下生风，绕着$n飞速游走，突然身形一转，绕到$n背后，探手直取["HIW"肩井"HIB"]、["HIW"三焦"HIB"]二穴"NOR,
"damage_type" : "瘀伤",
"lvl" : 80,
"skill_name" : "[转]",
]),
([      "action" : HIY"[盘]"HIB"$N一缩身，冲到$n面前时却突然收招从$n胯下钻过，转身死死勒住$n的腰部将$n头下脚上向地面撞去"NOR,
"damage_type" : "瘀伤",
"lvl" : 100,
"skill_name" : "[盘]",
]),
([      "action" : HIY"[附]"HIB"$N冲到$n身前，突然双臂互抱一个筋斗跌向$n怀中，同时手肘外翻直袭$n["HIC"天溪"HIB"]、["HIC"神封"HIB"]二穴"NOR,
"damage_type" : "瘀伤",
"lvl" : 120,
"skill_name" : "[附]",
]),
([      "action" : HIY"[藏]"HIB"$N运力于臂，双手藏于后背，猛然贴地直奔$n，瞬间即至，双臂陡然探出直取$n脚踝"NOR,
"damage_type" : "瘀伤",
"lvl" : 140,
"skill_name" : "[藏]",
]),
([      "action" : HIY"[圈]"HIB"$N左手五指并拢拍向$n胸口，右臂突然暴涨三尺，从$n腋下绕过，点向$n背部的["HIR"肺俞穴"HIB"]"NOR,
"damage_type" : "瘀伤",
"lvl" : 160,
"skill_name" : "[圈]",
]),
});

int valid_enable(string usage) { return usage=="hand" ||  usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练金蛇缠丝手必须空手。\n");
	if (me->query("gender")=="男性")
		return notify_fail("练金蛇缠丝手必须女性。\n");
	if ((int)me->query_skill("dulong-dafa", 1) < 250)
		return notify_fail("你的毒龙大法火候不够250，无法学金蛇缠丝手。\n");
	if ((int)me->query("max_neili") < 250)
		return notify_fail("你的内力太弱，无法练金蛇缠丝手。\n");
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
		level = (int)me->query_skill("chansi-shou", 1);

		for(i = sizeof(action); i > 0; i--)
		{
			if(level > action[i-1]["lvl"])
			{
				j = NewRandom(i, 20, level/5);
				if(me->query_temp("chss/lw"))
				{
					switch(me->query_temp("chss/lw"))
					{
						case 4: msg = HIW"$N眼中闪过一丝历芒，十指并拢，双手闪电般分前后齐出，分别缠向$n的左右双臂"NOR; break;
						case 3: msg = HIW"$N双臂如若无骨，以不可思议的角度直袭$n的后颈["HIG"大椎穴"HIW"]，令$n感觉招式滞涩无从下手"NOR; break;
						case 2: msg = HIW"$N冲到$n身前，突然双臂互抱一个筋斗跌向$n怀中，同时手肘外翻直袭$n["HIC"天溪"HIW"]、["HIC"神封"HIW"]二穴"NOR; break;
						case 1: msg = HIW"$N脚下生风，绕着$n飞速游走，突然身形一转，绕到$n背后，探手直取["HIG"肩井"HIW"]、["HIG"三焦"HIW"]二穴"NOR; break;
					}
					me->add_temp("chss/lw", -1);                  
			
					return 
					([
					"action":msg,
					"damage_type": "瘀伤",
					"force": 300 +random(300),
					"dodge": random(30),
					"parry": random(20)+20,
					"damage": 150 + random(100),
					]);
				}
				else
				{
					return 
					([
					"action": action[j]["action"],
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 150,
					"dodge": random(30),
					"damage": 100 + random(50),
					"parry": random(30),
					]);
				}
			}
		}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("chansi-shou", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 50)
		return notify_fail("你的精力不够。\n");
	if ( me->query("neili") < 20)
		return notify_fail("你的内力不够练金蛇缠丝手。\n");
	me->receive_damage("jingli", 40 );
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)

{
	return __DIR__"chansi-shou/" + action;
}