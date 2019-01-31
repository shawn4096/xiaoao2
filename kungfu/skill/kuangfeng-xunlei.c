//kuangfeng-xunlei.c 狂风迅雷功  源自霍都
//霍都大战大胜庄
//设计女性玩家||轻灵线路图武技
//作为中期过度

#include <ansi.h>

inherit SKILL;
//武器招式
mapping *action = ({
([      "action" : "$N纵身跃起手中$w轻挥，斩向$n后颈",
        "force"  : 160,
        "attack" : 35,
        "parry"  : 40,
        "dodge"  : 80,
        "damage" : 125,
        "lvl"    : 0,
        "skill_name" : "风平浪静",
        "damage_type" : "刺伤"
]),
([      "action" : "$N手中$w连话三个弧形，向$n的右臂齐肩斩落",
        "force"  : 180,
        "attack" : 55,
        "parry"  : 52,
        "dodge"  : 95,
        "damage" : 148,
        "lvl"    : 30,
        "skill_name" : "风起云涌",
        "damage_type" : "刺伤"
]),
([      "action" : "$N轻吁一声，刷刷刷刷四招连发，向$n胸，腹，腰，肩四处连刺",
        "force"  : 220,
        "attack" : 81,
        "parry"  : 18,
        "dodge"  : 123,
        "damage" : 195,
        "lvl"    : 60,
        "skill_name" : "风卷残云",
        "damage_type" : "刺伤"
]),
([      "action" : "$N仰天一声清啸，斜行向前，$w横削直击，迅捷无比，击向$n的$l",
        "force"  : 280,
        "attack" : 108,
        "parry"  : 20,
        "dodge"  : 152,
        "damage" : 200,
        "lvl"    : 90,
        "skill_name" : "风流云散",
        "damage_type" : "割伤"
]),
([      "action" : "$N一手执$w，都起一个圆圈，顺势横削，右手趁$n抵挡，由下而上，一个腋下反身，拍向$n的$l",
        "force"  : 280,
        "attack" : 108,
        "parry"  : 20,
        "dodge"  : 152,
        "damage" : 220,
        "lvl"    : 90,
        "skill_name" : "风流云散",
        "damage_type" : "割伤"
]),
});
//非武器招式，手法
mapping *action_hand = ({
([      "action" : "$N纵身跃起,双手幻起一片手影，连续幻出三招，拍向$n后颈、前胸、顶门三大穴位",
        "force"  : 160,
        "attack" : 35,
        "parry"  : 40,
        "dodge"  : 80,
        "damage" : 125,
        "lvl"    : 0,
        "skill_name" : "狂风暴雨",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N左手斜斜向上，呈半弧状向下拍去，形成优美的弧形，向$n的右臂齐肩拍去",
        "force"  : 180,
        "attack" : 55,
        "parry"  : 52,
        "dodge"  : 95,
        "damage" : 148,
        "lvl"    : 30,
        "skill_name" : "雨打风吹",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N轻吁一声，身形斗转，专向$n的背后，伸出手指，点向$n胸，腹，腰，肩四处大穴",
        "force"  : 220,
        "attack" : 81,
        "parry"  : 18,
        "dodge"  : 123,
        "damage" : 195,
        "lvl"    : 60,
        "skill_name" : "云卷云舒",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N仰天一声清啸，斜行向前，左手横削直击，迅捷无比，右手化成指法招式戳向$n的$l",
        "force"  : 280,
        "attack" : 108,
        "parry"  : 20,
        "dodge"  : 152,
        "damage" : 200,
        "lvl"    : 90,
        "skill_name" : "风流云散",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N身形快速疾走，围绕$n快速转了一圈，反手拍向$n的后心，一招既出后招连连发动，迅捷无比",
        "force"  : 280,
        "attack" : 108,
        "parry"  : 20,
        "dodge"  : 152,
        "damage" : 230,
        "lvl"    : 90,
        "skill_name" : "狂风迅雷",
        "damage_type" : "内伤"
]),
});

int valid_enable(string usage) { return usage == "brush" || usage == "parry"|| usage == "hand"; } 

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 200)
                return notify_fail("你的最大内力修为不够100级，无法修习狂风迅雷功。\n");

        if ((int)me->query_skill("dodge", 1) < 100)
                return notify_fail("你的基本轻功火候不足100级，无法修习狂风迅雷功。\n");

        if ((int)me->query_dex() < 60)
                return notify_fail("你的后天身法还不够60，无法修习狂风迅雷功。\n");
        if ((int)me->query_skill("hand",1) < 20)
                return notify_fail("你的基本手法不够20，无法练狂风迅雷功。\n");
		if ((int)me->query_skill("brush",1) < 20)
                return notify_fail("你的基本笔法不够20，无法练狂风迅雷功。\n");
        if ((int)me->query_skill("brush", 1) < (int)me->query_skill("kuangfeng-xunlei", 1))
	        return notify_fail("你的基本笔法水平有限，无法领会更高深的狂风迅雷功。\n");
        
		if ((int)me->query_skill("hand", 1) < (int)me->query_skill("kuangfeng-xunlei", 1))
	        return notify_fail("你的基本手法水平有限，无法领会更高深的狂风迅雷功。\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        if (!this_player()->query_temp("weapon"))
        {
			for (i = sizeof(action_hand) - 1; i >= 0; i--)
                if (level >= action_hand[i]["lvl"])
                        return action_hand[i]["skill_name"];
        }
		else {
			for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
		}
}

mapping query_action(object me, object weapon)
{
        int i, j,level;

		weapon=me->query_temp("weapon");
        
		level = (int) me->query_skill("kuangfeng-xunlei",1);
		if (this_player()->query_temp("weapon"))
		{
			if (me->query_temp("kfxl/kfjg"))
			{
				for (i = sizeof(action); i > 0; i--)
				{
					if (level > action[i - 1]["lvl"])
					{
						j = NewRandom(i, 20, level/5);
						return([  							
							"action" :MAG+replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"MAG)+NOR,							
							"force" : action[j]["force"],
							"dodge": action[j]["dodge"],
							"damage": action[j]["damage"],
							"parry": action[j]["parry"],
							"attack" : action[j]["attack"],
							"lvl" : action[j]["lvl"],
							"skill_name" : action[j]["skill_name"],
							"damage_type" : random(2)?"刺伤":"割伤",/**/
						]);
					}
				}
			}
			for (i = sizeof(action); i > 0; i--)
    	        if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
		}
		else {
			for (i = sizeof(action); i > 0; i--)
    	        if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

		}
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "brush")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("qi") < 65)
                return notify_fail("你的体力不够练狂风迅雷功。\n");

        if ((int)me->query("neili") < 40)
                return notify_fail("你的内力不够练狂风迅雷功。\n");
        if ((int)me->query_skill("force",1) < 20)
                return notify_fail("你的基本内功不够20，无法练狂风迅雷功。\n");

        me->receive_damage("qi", 60);
        me->add("neili", -36);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"kuangfeng-xunlei/" + action;
}

mixed hit_ob(object me, object victim, int damage)
{
	
        if (random(10) > 7
			&&me->query_temp("kfxl/xlg")) 
        {
			switch (random(3))
			{
				case 0:
					message_vision(MAG"$N猛然一声大呵，宛如空中炸雷，顿时$n有些耳晕目眩之感！\n"NOR,me,victim);
					victim->receive_damage("jing",200+random(400),me);
					victim->receive_wound("jing",100+random(200),me);
					break;
				case 1:
					message_vision(HIY"$N揉身而上，左手兵器疾攻，右手以手指点、戳、截，戳中$n的“带脉”诸穴！$n气血一滞!\n"NOR,me,victim);
					victim->add_busy(1);
					victim->apply_condition("no_exert",1);
					break;
				case 2:
					message_vision(HIR"$N仰天狂笑，随机呜哩哇啦说了一通梵语，仿佛在念咒语一般！使得$n精力大受影响！\n"NOR,me,victim);
					if (victim->query("jingli")<1200) victim->set("jingli",0);
					
					victim->receive_damage("jingli",1000+random(200),me);
					break;
			}
        	
        }
}

