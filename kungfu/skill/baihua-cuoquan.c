
// Cuff：  查拳、燕青拳、太祖长拳、六合拳、少林长拳、八极拳
// Claw：  大擒拿手、小擒拿手、鹰爪功、虎爪手
// Strike：八卦掌、武当绵掌、游身八卦掌

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N单手上抬，一招查拳的「冲天炮」，对准$n的$l猛击下去",
        "force" : 420,
        "attack": 130,
        "dodge" : 45,
        "parry" : 45,
        "damage": 80,
        "damage_type":  "砸伤"
]),
([      "action": "$N一招燕青拳的「白鹤亮翅」，身子已向左转成弓箭步，两臂向后成钩手，呼\n"
                  "的一声轻响，反击$n$l",
        "force" : 512,
        "attack": 145,
        "dodge" : 10,
        "parry" : 75,
        "damage": 85,
        "damage_type":  "瘀伤"
]),
([      "action": "$N往后一纵，施展小擒拿手的手法，双手对着$n$l处的关节直直抓去",
        "force" : 410,
        "attack": 170,
        "dodge" : 35,
        "parry" : 35,
        "damage": 178,
        "damage_type":  "抓伤"
]),
([      "action": "$N左拳拉开，右拳转臂回扰，一招少林的少林长拳突然击出，带着许许风声贯向$n",
        "force" : 460,
        "attack": 150,
        "dodge" : 62,
        "parry" : 60,
        "damage": 90,
        "lvl"   : 30,
        "damage_type":  "瘀伤"
]),
([      "action": "只见$N运足气力，使出八极拳中的「八极翻手式」，双掌对着$n的$l平平攻去",
        "force" : 480,
        "attack": 160,
        "dodge" : 40,
        "parry" : 40,
        "damage": 85,
        "damage_type":  "瘀伤"
]),
([      "action": "$N大喝一声，左手往$n身后一抄，右掌往$n反手击去，正是八卦掌的招式",
        "force" : 510,
        "attack": 155,
        "dodge" : 30,
        "parry" : 30,
        "damage": 95,
        "damage_type":  "瘀伤"
]),
([      "action": "$N提气游走，左手护胸，右手一招游身八卦掌的「游空探爪」，迅速拍向$n$l",
        "force" : 510,
        "attack": 150,
        "dodge" : 45,
        "parry" : 45,
        "damage": 110,
        "damage_type":  "瘀伤"
]),
([      "action": "只见$N拉开架式，双手将武当派的绵掌使得密不透风，招招不离$n的$l",
        "force" : 460,
        "attack": 155,
        "dodge" : 160,
        "parry" : 160,
        "damage": 105,
        "damage_type":  "瘀伤"
]),
([      "action": "$N突然飞身一跃而起，双手握做爪状，朝着$n的$l猛然抓去，凛然是鹰爪功的招式",
        "force" : 470,
        "attack": 185,
        "dodge" : 60,
        "parry" : 60,
        "damage": 155,
        "damage_type":  "抓伤"
]),
([      "action": "只见$N身形一矮，双手翻滚，合抱为圈，一招太极拳「云手」直拿$n的$l",
        "force" : 350,
        "attack": 90,
        "dodge" : 210,
        "parry" : 230,
        "damage": 65,
        "damage_type":  "瘀伤"
]),
([      "action": "只见$N跨前一步，左手一记大擒拿手护住上盘，右手顺势一带，施一招摔碑手击向$n",
        "force" : 520,
        "attack": 155,
        "dodge" : 41,
        "parry" : 37,
        "damage": 103,
        "damage_type":  "瘀伤"
]),
([      "action": "$N一个转身，趁$n不备，反手将$n牢牢抱住猛的朝地面摔去，竟然是蒙古的摔角招式",
        "force" : 560,
        "attack": 185,
        "dodge" : 75,
        "parry" : 60,
        "damage": 125,
        "damage_type":  "摔伤"
]),
});

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练百花错拳必须空手。\n");

        if (me->query("int") < 25)
                return notify_fail("你的先天悟性太差，无法学习百花错拳。\n");

        if (me->query("dex") < 15)
                return notify_fail("你的先天身法孱弱，无法学习百花错拳。\n");

        if (me->query("max_neili") < 3000)
                return notify_fail("你的内力修为远远不足，难以练习百花错拳。\n");

        if ((int)me->query_skill("force") < 400)
                return notify_fail("你的内功火候尚浅，无法学习百花错拳。\n");

        if ((int)me->query_skill("cuff", 1) < 120)
                return notify_fail("你的拳法根基有限，无法体会百花错拳要诣。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("baihua-cuoquan", 1))
                return notify_fail("你的基本拳法火候不足，无法领会更高深的百花错拳。\n");

        return 1;
}

int valid_enable(string usage) { return usage=="cuff" ||  usage=="parry"; }  

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("baihua-cuoquan", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 100 )
                return notify_fail("你现在手足酸软，休息一下再练吧。\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("你的内力不够了。\n");

        me->receive_damage("jingli", 80);

        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("baihua-cuoquan", 1);

        if (damage_bonus < 150 || lvl < 150) return 0;

        if (damage_bonus / 6 > victim->query_con())
        {
                victim->receive_wound("qi", (damage_bonus - 100) / 3, me);
                return HIR "只听$n" HIR "前胸「咔嚓」一声脆响，竟像是"
                       "肋骨断折的声音。\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"baihua-cuoquan/" + action;
}
