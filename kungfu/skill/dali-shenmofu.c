// cred by sohu@xojh   天魔斧头
//dali-shenfu  范松绝技
// cred by sohu@xojh
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N高举手中$w，一式「开山」，伏身向前，招式非常简单，向$n的$l砍去，势不可挡",
        "force" : 160,
        "dodge" : 5,
        "damage" : 10,
        "lvl" : 350,
        "skill_name" : "开山式",
        "damage_type" : "砍伤"
]),
([      "action" : "$N一式「劈地」，起身立蹲，肩定斧背，$w缓缓向$n的$l劈去，力大沉猛",
        "force" : 200,
        "dodge" : 10,
        "damage" : 20,
        "lvl" : 350,
        "skill_name" : "劈地式",
        "damage_type" : "劈伤"
]),
([      "action" : "$N挥动$w，掀起了漫天斧影，一式「翻江」，斧风顿时笼罩$n的全身",
        "force" : 240,
        "dodge" : -15,
        "damage" : 40,
        "lvl" : 60,
        "skill_name" : "翻江式",
        "damage_type" : "砍伤"
]),
([      "action" : "$N挥动$w，向四周依次劈出几斧，一式「蹈海」，斧光霍霍，顿时笼罩$n的全身",
        "force" : 240,
        "dodge" : -15,
        "damage" : 40,
        "lvl" : 60,
        "skill_name" : "蹈海式",
        "damage_type" : "砍伤"
]),
([      "action" : "$N挥动$w，掀起了漫天斧影，一式「狂风」，斧风顿时笼罩$n的全身",
        "force" : 240,
        "dodge" : -15,
        "damage" : 40,
        "lvl" : 60,
        "skill_name" : "狂风式",
        "damage_type" : "砍伤"
]),
([      "action" : "$N连续挥出数十斧头，掀起一片幻影，正是一式「暴雨」，$w笼罩$n的周身",
        "force" : 280,
        "dodge" : -10,
        "damage" : 60,
        "lvl" : 90,
        "skill_name" : "暴雨式",
        "damage_type" : "劈伤"
]),
([      "action" :HIR"$N招式简单，心无杂念，一招劈出，正是一式「无我」，$w"HIR"砍向$n的$l，已达返璞归真之境"NOR,
        "force" : 300,
        "dodge" : -10,
        "damage" : 380,
        "lvl" : 350,
        "skill_name" : "无我式",
        "damage_type" : "砍伤"
]),
});


int valid_enable(string usage)
{
    object me=this_player();
	if (me->query("quest/hmy/dlsmf/pass")&&me->query("gender")=="男性")
       return usage == "axe" || usage == "parry"; 
}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 1000)
                return notify_fail("你的内力不足1000,无法学习。\n");
        if (me->query_str() < 60)
                return notify_fail("你的臂力不足60，太低了。\n");
        if ((int)me->query_skill("tianmo-gong", 1) < 100)
			//||(int)me->query_skill("xixing-dafa", 1) < 100)
                return notify_fail("你的天魔功或吸星大法火候太浅。\n");
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
      int i, j,level;
		weapon=me->query_temp("weapon");
        level   = (int) me->query_skill("dali-shenmofu",1);
        for(i = sizeof(action); i > 0; i--)
			if(level > action[i-1]["lvl"]){
			   j = NewRandom(i, 20, level/4);
			   	if( me->query_temp("dlf/duanyun")){
				  return ([
					"action" : HIR+replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIR)+NOR,
					"force" : 150 + random(100),
					"dodge": random(20),
					"damage": 150 + random(100),
					"lvl" :  action[j]["lvl"],
					"parry": random(20),
					"weapon" : "斧锋",
					"damage_type" : random(2)?"劈伤":"砍伤",
				   ]);
			    }
				
				
				if( me->query_temp("dlf/leiting")){
				  return ([
					"action" : HIW+replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIW)+NOR,
					"force" : 250 + random(100),
					"dodge": random(20),
					"damage": 250 + random(100),
					"lvl" :  action[j]["lvl"],
					"parry": random(20),
					"weapon" : "斧锋",
					"damage_type" : random(2)?"劈伤":"砍伤",
				   ]);
			    }
                  return ([  
			    	"action": action[j]["action"],
				    "lvl": action[j]["lvl"],
				    "damage_type" : action[j]["damage_type"],
				    "force":100+random(250),
				    "dodge":random(20)-10,
				    "damage":100+random(60),
				    "parry":random(10),
			    ]);
		} 
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "axe")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("jingli") < 50)
                return notify_fail("你的体力不够练习「大力神魔斧」。\n");
        if ((int)me->query("neili") < 10)
                return notify_fail("你的内力不够练习「大力神魔斧」。\n");
        if (me->query_skill("qixian-wuxingjian",1)>1)
		        return notify_fail("大力神魔斧以强大的臂力为前提条件，这和剑法的灵动功夫不符，你无法修习大力神魔斧。\n");
	    if (me->query_skill("tianmo-gun",1)> 1)
				return notify_fail("天魔棍藏拙绝技和斧法的刚猛功夫不符，功力相冲，你无法练习大力神魔斧。\n");
		
		
		me->receive_damage("jingli", 30);        
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"dali-shenmofu/" + action;
}
