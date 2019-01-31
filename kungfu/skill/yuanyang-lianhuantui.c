inherit SKILL;
#include <ansi.h>

mapping *action = ({
([      "action" : "$N双手虚晃，右脚为支点，左脚猛地飞起，一式「戳脚」，迅捷如风，踢向$n的$l",
        "force" : 80,
        "attack": 10,
        "dodge" : 15,
        "parry" : 15,
        "damage": 100,
        "lvl"   : 0,
        "damage_type" : "瘀伤",
        "skill_name"  : "戳脚"
]),
([      "action" : "$N左脚顿地，轻轻一点，身形猛转，右脚一式「虎下山」，合身而上，猛踹$n的$l",
        "force" : 100,
        "attack": 20,
        "dodge" : 20,
        "parry" : 20,
        "damage": 115,
        "lvl"   : 30,
        "damage_type" : "瘀伤",
        "skill_name"  : "虎下山"
]),
([      "action" : "$N左脚右脚互换，右脚飞一般踹出，既猛且准，一式「鹰追」，踢向的$n",
        "force" : 140,
        "attack": 30,
        "dodge" : 25,
        "parry" : 25,
        "damage": 128,
        "lvl"   : 60,
        "damage_type" : "瘀伤",
        "skill_name"  : "鹰追"
]),
([      "action" : "$N双足连环圈转，一式「鸳鸯脚」，足带风尘，攻向$n的全身",
        "force" : 160,
        "attack": 35,
        "dodge" : 30,
        "parry" : 30,
        "damage": 120,
        "lvl"   : 90,
        "damage_type" : "瘀伤",
        "skill_name"  : "鸳鸯脚"
]),
([      "action" : "$N双脚交叉踢起，一式「钻天腿」，脚脚不离$n的面门左右",
        "force" : 180,
        "attack": 35,
        "dodge" : 40,
        "parry" : 40,
        "damage": 135,
        "lvl"   : 120,
        "damage_type" : "瘀伤",
        "skill_name"  : "钻天腿"
]),
([      "action" : "$N手好似鸳鸯头上冠，起脚又如鸳鸯上翘尾，腿脚出击连环紧扣，高低四环上下合一，一式「姑射炼月」，脚脚不离$n周身",
        "force" : 180,
        "attack": 35,
        "dodge" : 40,
        "parry" : 40,
        "damage": 145,
        "lvl"   : 120,
        "damage_type" : "瘀伤",
        "skill_name"  : "姑射炼月"
]),
([      "action" : "$N左右换势成双配偶，恰似鸳鸯形影相随，一式「形影不离」，如影相随袭向$n前胸任脉",
        "force" : 180,
        "attack": 35,
        "dodge" : 40,
        "parry" : 40,
        "damage": 150,
        "lvl"   : 120,
        "damage_type" : "瘀伤",
        "skill_name"  : "形影不离"
]),

});

int valid_enable(string usage) { return usage=="leg" ||  usage=="parry"; } 

int valid_combine(string combo) 
{
		if (this_player()->query("quest/qz/combine/pass"))
			return combo == "haotian-zhang";
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练鸳鸯连环腿必须空手。\n");

        if ((int)me->query_skill("force",1) < 20)
                return notify_fail("你的内功火候不够，无法学鸳鸯连环腿。\n");
        if (me->query("family/family_name")!="全真教")
                return notify_fail("鸳鸯连环退是全真绝技，外派无法学鸳鸯连环腿。\n");

        if ((int)me->query_skill("leg", 1) < 20)
                return notify_fail("你的基本腿法火候不够，无法学鸳鸯连环腿。\n");

        if ((int)me->query_skill("leg", 1) < (int)me->query_skill("yuanyang-lianhuantui", 1))
                return notify_fail("你的基本腿法水平有限，无法领会更高深的鸳鸯连环腿。\n");

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
        int i, j,level,adjust;
        level = (int)me->query_skill("yuanyang-lianhuantui", 1);
		adjust=level;
       
		for(i = sizeof(action); i > 0; i--)
            if(level > action[i-1]["lvl"])
			{
              j = NewRandom(i, 20, level/5);
               //连环
			   if (me->query_perform() == "鸳鸯连环踢")
			   {
                       return ([  
                        "action" : HIC+action[j]["action"]+NOR,
                        "force" : action[j]["force"] + adjust,
                        "dodge" : action[j]["dodge"] + adjust,
                        "damage" : action[j]["damage"] + adjust,
                        "damage_type" : action[j]["damage_type"],
                        ]);
			   }
//鸳鸯脚
				if (me->query_temp("yylht/yuan"))
			   {
                       return ([  
                        "action" : HIR+action[j]["action"]+NOR,
                        "force" : action[j]["force"] + adjust,
                        "dodge" : action[j]["dodge"] + adjust,
                        "damage" : action[j]["damage"] + adjust/2,
                        "damage_type" : action[j]["damage_type"],
                        ]);
			   }
			   if (me->query_temp("yylht/yang"))
			   {
                       return ([  
                        "action" : HIW+action[j]["action"]+NOR,
                        "force" : action[j]["force"] + adjust,
                        "dodge" : action[j]["dodge"] + adjust,
                        "damage" : action[j]["damage"] + adjust/2,
                        "damage_type" : action[j]["damage_type"],
                        ]);
			   }
               else {
                        return ([  
                        "action" : action[j]["action"],
                        "force" : action[j]["force"],
                        "dodge" : action[j]["dodge"] + adjust/2,
                        "damage" : action[j]["damage"],
                        "damage_type" : action[j]["damage_type"],
                        ]);
			   }
            }
}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 100)
               return notify_fail("你的体力太低了。\n");

        if ((int)me->query("neili") < 80)
               return notify_fail("你的内力不够练鸳鸯连环腿。\n");

        me->receive_damage("jingli", 80);
        //me->add("neili", -0);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yuanyang-lianhuantui/" + action;
}
