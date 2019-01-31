#include <ansi.h>
inherit SKILL;

mapping *action = ({
([     "action" : "$N刀锋斜引，身体跃起丈许,一招「劈风展翅」，手中的$w向$n的$l横劈过去",
       "force" : 150,
        "dodge" : -10,
        "parry" : 5,
       "damage": 30,
       "lvl" : 0,
       "skill_name" : "劈风展翅",
       "damage_type" : "割伤"
]),
([     "action" : "$N一招「风拂山岗」，手中$w向$n的下盘划去，招未使老，忽又直挑$n的$l",
       "force" : 180,
        "dodge" : -10,
        "parry" : 10,
       "damage": 50,
       "lvl" : 20,
       "skill_name" : "风拂山岗",
       "damage_type" : "割伤"
]),
([     "action" : "$N斜跨两步，抢到$n左侧，一招「抽刀断水」,$w自左向右平平横扫$n的前胸",
       "force" : 220,
        "dodge" : -15,
        "parry" : 15,
       "damage": 70,
       "lvl" : 40,
       "skill_name" : "抽刀断水",
       "damage_type" : "割伤",
]),
([     "action" : "$N一招「拨云见日」，手中的$w向$n虚砍一刀，刀刃忽又转向$n的$l砍去",
       "force" : 280,
        "dodge" : -10,
        "parry" : 10,
       "damage": 75,
       "lvl" : 60,
       "skill_name" : "拨云见日",
       "damage_type" : "割伤"
]),
([     "action" : "$N身随刀进，青光闪跃，一招「苍鹰望月」，直攻$n右肩，半徒刀锋兜了个半圆，方向突变,斜劈$n的$l",
       "force" : 320,
        "dodge" : -10,
        "parry" : 5,
       "damage": 90,
       "lvl" : 80,
       "skill_name" : "苍鹰望月",
       "damage_type" : "割伤"
]),
([     "action" : "$N陡然身行飞起，一招「满天飞雪」，手中的$w舞出万道寒光，向$n的$l掠去",
       "force" : 400,
        "dodge" : -10,
        "parry" : -5,
       "damage": 120,
       "lvl" : 100,
       "skill_name" : "满天飞雪",
       "damage_type" : "割伤"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }


int valid_learn(object me)
{
       if ((int)me->query("max_neili") < 50)
               return notify_fail("你的内力不够练习玄虚刀法。\n");
       if ((int)me->query_skill("yinyun-ziqi", 1) < 20)
               return notify_fail("你的氤氲紫气火候太浅。\n");
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
		string msg;
        level   = (int) me->query_skill("xuanxu-daofa",1);
        if (me->query_temp("xxd/xuanxu")&&random(10)>8)
        {
			msg=HIW"$N手中刀法互变，闪烁不定，刀法由刚至柔，施展出「虚字诀」刀势！\n"NOR;
			if (!random(2)) {

				return ([
					"action": msg,
					"dodge":  random(30),
					"parry":  random(30),
					"damage": 150 + random(100),
					"force":  300+random(200),
					"damage_type": "割伤"
				]);
			}else {
				me->add_temp("apply/blade",me->query_skill("xuanxu-daofa",1)/4);
				return ([
					"action": HIR"$N手中刀法互变，大开大合，刀法由柔变刚，施展出「玄字诀」刀势！\n"NOR,
					"dodge":  random(30),
					"parry":  random(30),
					"damage": 250 + random(100),
					"force":  300+random(200),
					"damage_type": "割伤"
				]);
				me->add_temp("apply/blade",-me->query_skill("xuanxu-daofa",1)/4);

			}

        }
		for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       object weapon;

       if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "blade")
               return notify_fail("你使用的武器不对。\n");
       if ((int)me->query("jingli") < 20)
               return notify_fail("你的体力不够练玄虚刀法。\n");
       me->receive_damage("jingli", 20);
       me->add("neili", -10);
       return 1;
}

mixed hit_ob(object me, object target, int damage_bonus)
{
        string msg;
		int i,j;
		object weapon;
		i=me->query_skill("xuanxu-daofa",1);
		j=me->query_skill("zhenshan-mianzhang",1);
		weapon=me->query_temp("weapon");
        if (random(me->query_str(1))>target->query_con(1)/2
		&& me->query_skill("xuanxu-daofa",1)>150
		&& me->query_skill_mapped("strike")=="zhenshan-mianzhang"
		&& me->query_skill_prepared("strike")=="zhenshan-mianzhang"
		&& !random(4)
		)   {
              msg = HIC"$N将刀交予左手，虚晃一招，吸引$n的注意，右手忽然施展出【震山绵掌】中的绵掌功夫。\n"NOR;
			  if (random(me->query_skill("strike",1)) > target->query_skill("parry",1)/2) {
                  msg += HIR"$n为$N的阴柔劲力所伤，心口一阵剧痛传来，忍不住吐了一口鲜血。\n"NOR;
			      
                  weapon->unequip(); 
				  target->start_busy(1+random(2));
				  target->receive_damage("qi",i+j*2,me);
				  target->receive_wound("qi",j/2,me);
                  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);  
				  weapon->wield();
			  }    
			   else {
                  msg += HIR"$n识破了$N的意图，冷哼一声，闪了开去。\n"NOR;
				  me->add_busy(1+random(1));
				  }
              message_vision(msg, me, target);
        }
        return 1;
        
}


string perform_action_file(string action)
{
        return __DIR__"xuanxu-daofa/" + action;
}

