//清凉扇
//sohu@创建，昆仑外门招式
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action":"$N左手施展出一招「清心普善」，手中的$w疾点向$n的期门穴",
        "force" : 90,
        "attack": 15,
        "dodge" : -10,
        "parry" : 20,
        "damage": 25,
        "lvl"   : 0,
        "skill_name" : "清心普善",
        "damage_type" : "刺伤"
]),
([      "action":"$N吐气开声一招「寒梅映雪」，$w如灵蛇吞吐，向$n白海穴戳去",
        "force" : 130,
        "attack": 30,
        "dodge" : -10,
        "parry" : 30,
        "damage": 30,
        "lvl"   : 40,
        "skill_name" : "寒梅映雪",
        "damage_type" : "刺伤"
]),
([      "action":"$N向前跨上一步，混身充满战意，手中$w使出「追风逐电」，疾点$n的地仓穴",
        "force" : 170,
        "attack": 40,
        "dodge" : 5,
        "parry" : 32,
        "damage": 35,
        "lvl"   : 60,
        "skill_name" : "追风逐电",
        "damage_type" : "刺伤"
]),
([      "action":"$N手中的$w自左而右地一晃，使出「飞黄腾达」带着呼呼风声横打$n的章门穴",
        "force" : 190,
        "attack": 50,
        "dodge" : 5,
        "parry" : 35,
        "damage": 40,
        "lvl"   : 80,
        "skill_name" : "飞黄腾达",
        "damage_type" : "刺伤"
]),
([      "action":"$N飞身跃起，一式「快马加鞭」，卷起漫天笔影，$w向$n电射而去",
        "force" : 240,
        "attack": 60,
        "dodge" : 10,
        "parry" : 45,
        "damage": 50,
        "lvl"   : 100,
        "skill_name" : "快马加鞭",
        "damage_type" : "刺伤"
]),
([      "action":"$N凝气守中，$w逼出尺许雪亮笔锋，挥出「灵台观景」，一笔快似一笔地攻向$n",
        "force" : 260,
        "attack": 65,
        "dodge" : 5,
        "parry" : 50,
        "damage": 60,
        "lvl"   : 120,
        "skill_name" : "灵台观景",
        "damage_type" : "刺伤"
]),
([      "action":"$N使出一招「群山叠影」挺笔中宫直进，笔尖颤动，中途忽然转而向上变幻无方",
        "force" : 280,
        "attack": 70,
        "dodge" : 5,
        "parry" : 52,
        "damage": 75,
        "lvl"   : 140,
        "skill_name" : "群山叠影",
        "damage_type" : "刺伤"
]),
([      "action":"$N侧身斜刺一笔，一招「风雷卷破」卷带着呼呼笔风，将$n包围紧裹",
        "force" : 310,
        "attack": 75,
        "dodge" : 5,
        "parry" : 64,
        "damage": 90,
        "lvl"   : 150,
        "skill_name" : "风雷卷破",
        "damage_type" : "刺伤"
]),
});


int valid_enable(string usage)
{
	if (this_player()->query("quest/kl/qls/pass")&&this_player()->query("quest/kl/qls/baishi"))
	{
		return usage == "brush" ||usage == "blade" || usage == "parry";
	}
}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 500)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候太浅。\n");
		if (me->query("family/family_name")!="昆仑派")
                return notify_fail("你非昆仑弟子，无法学昆仑旁支三因观绝技清凉扇。\n");
        if ((int)me->query_skill("brush", 1) < 30)
                return notify_fail("你的基本笔法火候太浅，不足30级。\n");
        if ((int)me->query_skill("blade", 1) < 30)
                return notify_fail("你的基本刀法火候太浅，不足30级。\n");
        if ((int)me->query_skill("brush", 1) < (int)me->query_skill("qingliang-shan", 1))
                return notify_fail("你的基本笔法水平有限，无法领会更高深的清凉扇法。\n");

    return 1;
}

string query_skill_name(int level)
{
        int i;

        for(i = sizeof(action) - 1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i,j, level;

        level = (int) me->query_skill("qingliang-shan", 1);
        //清凉快打
		if (me->query_temp("qls/kuaida"))
        {
			for(i = sizeof(action); i > 0; i--) 
			{ 
				if(level >= action[i-1]["lvl"]) 
				{
					j = NewRandom(i, 20, level/5);
					return ([
						"action": HIW+replace_string(action[j]["action"],"$w","$w"HIW)+NOR,
						"lvl": action[j]["lvl"],
						"damage_type": action[j]["damage_type"],
						"force": 150 + random(300),
						"dodge": random(30),
						"parry": random(30),
						"damage": 170+ random(100),
					]);
				}
			}

        }
		for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "brush")
                return notify_fail("你所持的武器无法练习清凉扇法。\n");

        if ((int)me->query("qi") < 70)
                return notify_fail("你的体力不够练清凉扇法。\n");

        if ((int)me->query("neili") < 70)
                return notify_fail("你的内力不够练清凉扇法。\n");

        me->receive_damage("qi", 65,"练功走火入魔");
        me->add("neili", -62);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qingliang-shan/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{                
    object weapon=me->query_temp("weapon");
	
	if (me->query_skill("force",1)<250)
        return;
	//解开清凉扇谜题就可以用
	if (!me->query("quest/kl/qls/pass")) return;

	if( me->query_temp("qls/zhan") 
		&& me->query("neili")>1000
		&& me->query("env/清凉扇")=="合"
		&& !random(3)) 
	{
        message_vision(HIC"$N忽然将手中的扇子合在一起，化作笔法招式向$n戳去！\n"NOR,me,victim);
		switch (random(3))
		{
		   case 0:
               if (weapon->query("skill_type")!="brush") break;
             
			   if (random(me->query_int(1))>victim->query_int()/4)
               {
			     message_vision(HIR"$n一时不查，眼花缭乱之际为$N以"+weapon->query("name")+HIR"封住了穴道。\n"NOR,me,victim);
				 victim->add_busy(3+random(2));
				 victim->apply_condition("no_exert",1);
               }else {
				 message_vision(HIC"$n对于$N的攻击了然若胸，顺势化解了$N的攻势。\n"NOR,me,victim);
				 me->add_busy(1);
			   }
			   break;
			case 1:
			    if (weapon->query("skill_type")!="brush") break;
  
				if (random(me->query_skill("brush",1))>victim->query_skill("parry",1)/3)
               {
			     message_vision(MAG"$N手中"+weapon->query("name")+MAG"化作棍法招式，劈向$n的面门。\n"NOR,me,victim);
				 victim->receive_damage("qi",2000+random(3000),me);
				 victim->receive_wound("qi",1000+random(1000),me);
               }else {
				 message_vision(HIC"$n轻轻一纵闪身而退。\n"NOR,me,victim);
				 me->add_busy(1);
			   }
			   break;		   
			case 2:
			  if (random(me->query_skill("blade",1))>victim->query_skill("parry",1)/3)
               {
			     message_vision(HIG"$N手中"+weapon->query("name")+HIG"化作刀法招式，贴身进逼，刀刀切向$n的周身要害。\n"NOR,me,victim);
				 victim->receive_damage("qi",3000+random(1000),me);
				 victim->receive_damage("jing",1000+random(1000),me);
               }else {
				 message_vision(HIC"$n轻轻一纵闪身而退。\n"NOR,me,victim);
				 me->add_busy(1);
			   }
			   break;		
		}
        
    }
	return;
}
