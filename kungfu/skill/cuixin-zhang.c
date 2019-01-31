// cuixin-zhang.c 催心掌 by XiaoYao 4/22/99
// By KinGSo 2006年4月28日 重新编辑 并增加AUTO PFM
// 修改为公众 skill

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : HIG "$N使一招「风起云涌」，双手飘移不定击向$n$l"NOR,
        "force" : 260,
        "dodge" : 2,
        "skill_name" : "风起云涌",
        "lvl" : 0,
        "damage_type" : "瘀伤"
]),
([      "action" :HIC "$N倏忽欺至$n身前，一招「扬波起浪」直拍$n的$l"NOR,
        "force" : 340,
        "dodge" : 0,
        "skill_name" : "扬波起浪",
        "lvl" : 30,
        "damage_type" : "瘀伤"
]),
([      "action" : HIY"$N身形绕$n一转，一招「风雷并起」向$n$l接连出掌"NOR,
        "force" : 420,
        "dodge" : -2,
        "skill_name" : "风雷并起",
        "lvl" : 50,
        "damage_type" : "瘀伤"
]),
([      "action" : HIB"$N身形拔起，在半空一招「急电惊雷」右掌猛击$n的$l"NOR,
        "force" : 460,
        "dodge" : -4,
        "skill_name" : "急电惊雷",
        "lvl" : 90,
        "damage_type" : "瘀伤"
]),
([      "action" :HIM "$N使一招「含沙射影」，纵起丈余直击$n的$l"NOR,
        "force" : 510,
        "dodge" : -6,
        "skill_name" : "含沙射影",
        "lvl" : 120,
        "damage_type" : "瘀伤"
]),
([      "action" :BLU "$N一声大喝使出「夺魄催心」，幻出满天掌影，掌掌不离$n的$l"NOR,
        "force" : 560,
        "dodge" : -8,
        "skill_name" : "夺魄催心",
        "lvl" : 150,
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_combine(string combo) 
{
	object me;
	me = this_player(); 

	  if ((int)me->query_int() > 1)
		return combo=="jiuyin-baiguzhua"; 
}


int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练催心掌必须空手。\n");
        if((int)me->query_skill("cuixin-zhang", 1 ) < 120)
                return notify_fail("你的催心掌等级不够，还不能学习。\n");
        if( (int)me->query_skill("jiuyin-shenzhang", 1 ) >= 1)
                return notify_fail("学了九阴神掌，还要催心掌？\n");
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力太弱，无法练催心掌。\n");
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
        int i, level,j;
        level = (int) me->query_skill("cuixin-zhang",1);
        for(i = sizeof(action); i > 0; i--) {
                if(level > action[i-1]["lvl"])
				{
					j = NewRandom(i, 20, level/5);
					
					if (me->query("quest/jiuyin2/cuixin/pass"))			
					{
					return ([  
				"action":	HIR+action[j]["action"]+NOR,
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"force":	600+random(350),
				"dodge":	random(20)+10,
				"damage":	650+random(150),
				"parry":	random(25),
			     ]);		
					}				 
				return action[NewRandom(i, 5, level/5)];	
				}
		}					

}


int practice_skill(object me)
{
        if ((int)me->query("qi") < 30)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("你的内力不够练催心掌。\n");
        me->receive_damage("qi", 25);
        me->add("neili", -10);
        return 1;
}

void skill_improved(object me)
{
    tell_object(me, "你练着练着忽然从心底生出一股邪念！\n");
    me->add("shen", -(me->query_skill("cuixin-zhang", 1)*100));
}

string perform_action_file(string action)
{
        return __DIR__"cuixin-zhang/" + action;
}
mixed hit_ob(object me, object target)
{
    string msg;
    int j;
    j = me->query_skill("cuixin-zhang", 1);
   
    if (random(me->query_con()) >= target->query_con()/4 && j > 120 &&
        me->query_skill("parry",1) > 120 &&
        me->query("jingli")>300 && 
        !target->is_busy() &&
        random(me->query("combat_exp"))> target->query("combat_exp")/2 && 
        me->query("neili")>500 &&
		me->query("quest/jiuyin2/cuixin/pass"))
     {
          switch(random(2))
          {
            case 0 :
               msg = HIG "$N默运催心掌力，内劲聚于双掌攻向$n，一股催心断肠般的霸道内劲涌入$n的心脉！\n";
               msg = msg + "$n只觉心口处被撕裂般的难受，已被一招击中"HIR"「心脉」"HIG"所在！\n"NOR; 
               target->recevied_damage("qi", j*3 +random(300));
               target->add_busy(1+random(3));
               target->apply_condition("cx_poison", random(j) /2);
               me->add("neili",-50);
               break;
            case 1 :
               msg = HIY "$N默运催心掌力，双掌带起一道无形罡气，将$n笼罩于内！\n";
               msg += "$n只觉胸口一痛，已被一招差点震断"HIR"「心脉」！。\n"NOR;
               target->recevied_damage("qi", j*2 + random(300));
               target->add_condition("cx_poison",  random(j) /3);
               target->add_busy(1+random(2));
               me->add("neili",-50);
               //message_vision(msg, me, target);
              
               break;
            
          }         
          message_vision(msg, me, target);
   }
   return ;
}


