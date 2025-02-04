b// fuqin-shi.c 娥嵋抚琴式
// Created by snowman@SJ 06/03/2001

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([     "action": "$N口诵「蜀僧抱绿绮」，手腕一挥，$w如灵蛇婉转，不住旋动，一下子便旋到了$n身前",
       "dodge": 5,
       "parry": 10,
       "damage": 60,
       "force": 130,
       "lvl" : 0,
       "skill_name" : "蜀僧抱绿绮",
       "damage_type":  "拉伤"
]),
([     "action": "$N说道：“看这「西下峨眉峰」！”$w嗖地一声向上空飞串，内力到处，发出一片劈啪声，鞭梢忽地转下，直点$n",
       "dodge": 10,
       "parry": 10,
       "damage": 70,
       "force": 180,
       "lvl" : 30,
       "skill_name" : "西下峨眉峰",
       "damage_type":  "刺伤"
]),
([     "action": "$N力灌手臂，将$w拉向身后，猛地一声：“看「为我一挥手」”向$n抽出，鞭势过处，尘土飞扬",
       "dodge": -10,
       "parry": 10,
       "damage": 80,
       "force":  230,
       "lvl" : 60,
       "skill_name" : "为我一挥手",
       "damage_type":  "拉伤"
]),
([     "action": "$N脚行八卦，边走边念「如听万壑松」，$w在$n眼前不停旋动，忽然瞅准机会，猛地一下抽出",
       "dodge": 10,
       "parry": 10,
       "damage": 90,
       "force": 270,
       "lvl" : 90,
       "skill_name" : "如听万壑松",
       "damage_type":  "拉伤"
]),
([     "action": "$N一声高喝「客心洗流水」，将$w急度挥舞，只见漫天的鞭影渐渐聚拢，如泼水般涌向$n",
       "dodge": -5,
       "parry": 10,
       "damage": 110,
       "force": 300,
       "lvl" : 120,
       "skill_name" : "客心洗流水",
       "damage_type":  "拉伤"
]),
([     "action": "$N将内力注入$w中，来回舞动，带起一片片尖锐的哨声，这是招「余响入霜钟」，扰得$n心烦意乱，$w却乘虚而入",
       "dodge": 20,
       "parry": 10,
       "damage": 130,
       "force": 320,
       "lvl" : 150,
       "skill_name" : "余响入霜钟",
       "damage_type":  "拉伤"
]),
([     "action": "$N念道「不觉碧山暮」，鞭势变得沉重起来，挥舞中宛如脱着万斤泥沙，可看鞭梢过处，树叶、尘土无不激得飞扬出去",
       "dodge": 10,
       "parry": 10,
       "damage": 140,
       "force": 340,
       "lvl" : 180,
       "skill_name" : "不觉碧山暮",
       "damage_type":  "拉伤"
]),
([     "action": "$N放声长诵「秋云暗几重」，$w在空中如神龙乱舞，一下、两下、三下……不断抽向$n，逼得$p不断后退",
       "dodge": 15,
       "parry": 10,
       "damage": 150,
       "force": 360,
       "lvl" : 200,
       "skill_name" : "秋云暗几重",
       "damage_type":  "拉伤"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
                     
       	if( (int)me->query("max_neili") < 100 )
               return notify_fail("你的内力修为不足，没有办法练娥嵋抚琴式。\n");

        if ((int)me->query_skill("sancheng-gong", 1) < 130)
               return notify_fail("你的三乘功法火候太浅。\n");
	if ((int)me->query_skill("parry", 1) < 10)
                return notify_fail("你的基本招架火候太浅。\n");
        if ( me->query("class") != "bonze" && me->query_skill("sancheng-gong", 1) < 100 )
                return notify_fail("娥嵋抚琴式不传俗家新弟子。\n");
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
        int i, level;
        level   = (int)me->query_skill("fuqin-shi", 1);
        
        if( me->query_temp("pfm/baishui") ){
        	me->delete_temp("pfm/baishui");
        	return ([
        		"action": HIW"忽而如同秋风乍起时，吹皱一池清水，吹动一池白云，$N凝力于鞭，" + weapon->name() + HIW"如飞瀑直下，「白水抚琴式」力奔$n！"NOR,
       			"dodge": 30,
       			"damage": 160,
       			"force": 400,
       			"damage_type":  "拉伤",
        	]);
        }
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "whip")
                return notify_fail("你使用的武器不对。\n");

       	if ((int)me->query("jingli") < 40)
                return notify_fail("你的体力不够练娥嵋抚琴式。\n");
        me->receive_damage("jingli", 30);
        if ((int)me->query("neili") < 20)
                return notify_fail("你的内力不够练娥嵋抚琴式。\n");
        me->receive_damage("neili", 5);
        return 1;
}

string perform_action_file(string action)
{
	return __DIR__"fuqin-shi/" + action;
}
