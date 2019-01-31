//三阴手
//sanyin-shou.c

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "在呼呼风声中，$N使一招「阴风怒号」，双手如钩如戢，插向$n的$l",
        "force" : 100,
        "attack": 28,
        "dodge" : 17,
        "parry" : 0,
        "damage": 13,
        "lvl"   : 0,
        "skill_name" : "阴风怒号" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N身形一跃，费神扑上，使出一招「断筋折骨」，右手直直抓向$n的$l",
        "force" : 130,
        "attack": 35,
        "dodge" : 20,
        "parry" : 5,
        "damage": 20,
        "lvl"   : 10,
        "skill_name" : "断筋折骨" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N双手平伸，十指微微上下抖动，一招「伤肝破胆」打向$n的$l",    
        "force" : 160,
        "attack": 39,
        "dodge" : 32,
        "parry" : 10,
        "damage": 25,
        "lvl"   : 20,
        "skill_name" : "伤肝破胆" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N使出一招「噬神摄精」，悄无声息的游走至$n身前，猛的一爪奋力抓向$n的$l",
        "force" : 172,
        "attack": 42,
        "dodge" : 38,
        "parry" : 19,
        "damage": 29,
        "lvl"   : 40,
        "skill_name" : "噬神摄精" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N双手平提胸前，左手护住面门，一招「虐目贯耳」右手推向$n的$l",
        "force" : 187,
        "attack": 45,
        "dodge" : 41,
        "parry" : 21,
        "damage": 33,
        "lvl"   : 60,
        "skill_name" : "虐目贯耳" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N使出「穿心透骨」，低喝一声，双手化掌为爪，一前一后抓向$n的$l",
        "force" : 203,
        "attack": 51,
        "dodge" : 49,
        "parry" : 22,
        "damage": 36,
        "lvl"   : 80,
        "skill_name" : "穿心透骨" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N右腿斜插$n二腿之间，一招「五马分尸」，上手取目，下手反勾$n的裆部",
        "force" : 245,
        "attack": 56,
        "dodge" : 53,
        "parry" : 27,
        "damage": 41,
        "lvl"   : 100,
        "skill_name" : "五马分尸" ,
        "damage_type" : "抓伤"
]),
([      "action": "$N使出「搜魂摄魄」，双爪如狂风骤雨般对准$n的$l连续抓出",
        "force" : 270,
        "attack": 61,
        "dodge" : 58,
        "parry" : 38,
        "damage": 45,
        "lvl"   : 120,
        "skill_name" : "搜魂摄魄" ,
        "damage_type" : "抓伤"
])
});
string	*msg = ({
"$N身子左侧，一式「月下踏径」，右手$w从身体下方突然甩出，直射向$n的$l",
"$w破空飞出，一式「长虹经天」，缓缓一个弧线，由左自右，绕向$n的$l，",
"$N双手连扬，一式「破云见日」，两把$w向$n撒出，笼罩$n的全身上下",
"$N向空中一撒，却是$n一招「秋日落叶」，十多枚$w由空中缓缓落下",
"$N身形急速向前滑动，一式「雪地追踪」，三枚$w向$n的胁下射去",
"$N一式「回首沧桑」，身体一转，反手掷出数枚$w，飞向$n的背部",
"$N凌空一纵，一招「雨打浮萍」，居高临下，手中$w疾射，直向$n的$l",
"$N一招「流星电闪」，手指弹出五枚$w，一点黑光射向$n的头部",
});

int valid_enable(string usage) { return usage == "hand" ||  usage == "parry"||  usage == "throwing"; }

int valid_combine(string combo)
{
        return combo == "chuanyun-tui";
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练三阴手必须空手。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的内功火候不够，无法学三阴手。\n");
		if (me->query("family/family_name")!="昆仑派")
                return notify_fail("你非昆仑弟子，无法学三阴手。\n");

        if ((int)me->query("max_neili") < 250)
                return notify_fail("你的内力太弱，无法练三阴手。\n");

        if ((int)me->query_skill("hand",1) < 30)
                return notify_fail("你的基本手法等级太低，无法学三阴手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("sanyin-shou", 1))
                return notify_fail("你的基本手法水平有限，无法领会更高深的三阴手。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
		if (!this_player()->query_temp("weapon"))
		{
			for (i = sizeof(action); i > 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
		}
       
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("sanyin-shou",1);
        if (!this_player()->query_temp("weapon"))
		{
			for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
		}
		else {
			if (me->query_temp("sys/xuejian"))
			{
					
			   return ([
				"action":YEL+replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$W"), "$W", "$w"YEL)+NOR,
				"damage": 100 + random(60),
				"damage_type":"刺伤",
				"dodge": random(20)-10,
				"parry": random(10),
				"force": 100 + random(250),
				
				]);
			}			
			return ([
				"action":msg[random(sizeof(msg))],
				"damage": 60 + random(60),
				"damage_type":"刺伤",
				"dodge": random(20)-10,
				"parry": random(10),
				"force": 100 + random(250),
				
			]);

		}
	

}

int practice_skill(object me)
{
        if (me->query_temp("weapon") ||
            me->query_temp("secondary_weapon"))
                return notify_fail("你必须空手练习！\n");

        if ((int)me->query("qi") < 70)
                return notify_fail("你的体力太低了。\n");

        if ((int)me->query("neili") < 80)
                return notify_fail("你的内力不够练三阴手。\n");

        me->receive_damage("qi", 60);
        me->add("neili", -69);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"sanyin-shou/" + action;
}
