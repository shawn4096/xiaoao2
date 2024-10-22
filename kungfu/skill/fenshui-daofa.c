// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit SKILL;


string *action_msg = ({
        "$N轻抚手中的$w，突然间只见刀光一闪，再闪，又一闪！三道刺骨的寒气已然袭上了$n的$l",
        "只见$N倒提$w，身形急冲，就在与$n错身之际，突然反手一刀从$n后脑斜劈而下",
        "$N斜身飞起，带出一片匹练也似的刀光卷向$n的$l",
        "$N突然一脚踢出，手中的$w划出一道轻妙的圆弧，淡淡的刀光封住了$n的头脸，切断了$n的呼吸",
        "只见$N脸色一寒，一招「千里冰封」使出，从眉捷到脚跟，\n$n周身的血液都似被这无尽的刀势冻住，而生命也仿佛要离体而去",
        "$N刀势渐慢，而$w上带出的寒气却越来越浓。就在这时，\n$n的心头一紧，一道比针尖还要锐利的寒气已刺上了$n$l",
        "$N也不管三七二十一，高举$w呼！地就是一刀向$n迎面斩下！\n虽然只有一刀，可怕的刀势却似万古不化的寒冰封死了$n的一切退路",
});


int valid_learn(object me)
{
        object ob;

        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力不够，没有办法练分水刀法，多练些内力再来吧。\n");

        if (! (ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "blade"
        )
                return notify_fail("你必须先找一把刀才能练分水刀法。\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage == "blade" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        return ([ 
                "action": action_msg[random(sizeof(action_msg))], 
                "damage": 160 + random(30), 
                "attack": 100 + random(10),
                "dodge" : 100 + random(10),
                "parry" : 100 + random(10),
                "damage_type" : random(2) ? "挫伤" : "割伤", 
        ]);
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 110
            ||  (int)me->query("neili") < 110)
                return notify_fail("你的内力或气不够，没有办法练习分水刀法。\n");
                
        me->receive_damage("jingli", 40);
        me->add("neili", -100);
        write("你按着所学练了一遍分水刀法。\n");
        return 1;
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
        object weapon = me->query_temp("weapon");     
        string msg;
       
        if (( damage_bonus > 250 ) && (! userp(me)))
                return 0;

        if (((int)me->query_skill("blade", 1)/2) > random((int)victim->query_skill("force", 1)))
        {
                victim->receive_wound("qi", (300-damage_bonus),me);
                msg = HIW "$N默运真气，将分水刀法中寒气逼出，$n一个不察，已被冻伤！\n\n"NOR;
                message_combatd(msg, me, victim);
             
        }
        switch(random(3)) {
        case 0:
                victim->receive_damage("qi",damage_bonus/3*2,me);
                msg = "只见一丝寒气无声无息地钻到$n体内！\n";
                break;
                                
        case 1:  
                victim->receive_damage("qi",damage_bonus/2,me);
                msg = "$N暗使巧力，在$n的伤口上留下一道浅浅的白印！\n";
                break;
                                
        case 2:
                victim->receive_damage("qi",damage_bonus,me);
                msg = "$n突然觉得体内奇寒难忍...\n";
                break;      
        }
               
        return msg;                    
}
string perform_action_file(string action)
{
        return __DIR__"fenshui-daofa/" + action;

}



