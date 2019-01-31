// bahuang-gong.c 八荒六合唯我独尊功
// bahuang-gong.c
#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

#include "force.h"

int valid_learn(object me)
{
		mapping fam  = me->query("family");
	if (!fam || fam["family_name"] != "灵鹫宫" )
			 	return notify_fail("你并非天山灵鹫宫弟子，如何习得了八荒六合唯我独尊功。\n");
		
	if ( me->query("gender") == "无性")
		return notify_fail("你无根无性，阴阳不调，难以领会高深的八荒六合唯我独尊功。\n");

	if ((int)me->query_skill("bahuang-gong", 1) > me->query_skill("force", 1) + 10
	 && me->query_skill("bahuang-gong", 1) >= 200 )
		return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

	return valid_public(me);
}

int practice_skill(object me)
{
	if((int)me->query_skill("bahuang-gong", 1) >= 200 ){
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200){
			me->improve_skill("bahuang-gong", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("你现在的修为不足以提高八荒六合唯我独尊功了。\n");
	}
	else return notify_fail("你现在的八荒六合唯我独尊功修为只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return SKILL_D("bahuang-gong/") + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIM + me->name() +"盘膝而坐，鼻孔中两道红色气团缭绕，面色红白变幻。" NOR,
        "start_my_msg" : "你盘膝而坐，运起八荒六合唯我独尊功，丹田真气升腾而起，开始打坐。\n",

		"start_other_msg" : "只见"+ me->name() +"鼻孔中两道白气循环缭绕，头顶汗气蒸腾。\n",
		"end_my_msg" : "你只觉真力运转顺畅，周身气力充沛，气沉丹田，站起身来。\n",
		"end_other_msg" : me->name() +"收起鼻孔间的白气，精神抖擞，站起身来。\n",
	]);
}

int ob_hit(object ob, object me, int damage)
{
    int m_bhdz,t_force,i;
    m_bhdz = random((int)me->query_skill("bahuang-gong",1));
    t_force = (int)ob->query_skill("force",1);
    if( !ob ) ob = offensive_target(me);
     
	 i = - damage;
    if((int)me->query_skill("bahuang-gong",1)>=350)
    if(me->query_temp("bhg/bahuang")
		&& random(10)>5
    	&&me->query("bhg/biguan")>=2){    	
		
    	if(m_bhdz > t_force*9/10 && !random(3)){            
			if (me->query("neili")>=1000) {	
			i = - damage/3;
            message_vision(HIC"$N八荒六合诀神功陡发，将「八荒六合劲」聚集于全身，将毕生修为贯穿于$N各处经脉之中,隐隐形成气盾。\n"NOR,me,ob);						
            me->add("neili",-1000);			
			if (ob->query("qi")<damage) damage=ob->query("qi")-100;
            ob->receive_damage("qi", damage);
			}
            return i;
        }
    	 else if(m_bhdz > t_force*6/10 && !random(2)){
            i = - damage/2;
            message_vision(HIM"$N默念「八荒六合劲」心诀，八荒六合唯我独尊劲气弥漫，顿时化解$n了攻击。\n"NOR,me,ob);
			if (ob->query("neili")>=2000) {		
            me->add("neili",2000);
            ob->add("neili",-2000);
			}
            COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);       
            return i;
        }
        else if(m_bhdz > t_force*5/10 && !random(1)){
            i = - damage/3;
            message_vision(HIM"$N猛然领悟「八荒六合」之精髓，$n招数被「八荒六合劲气」卸掉$n部分攻击。\n"NOR,me,ob);
			if (ob->query("neili")>=1000) {		
            me->add("neili",1000);
            ob->add("neili",-1000);
			}
            COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);          
            return i;
        }
       
    }
    return 0;
}
mixed hit_ob(object me, object target)
{
	string msg;
	object weapon;
	int j;
	j = me->query_skill("bahuang-gong", 1);
	weapon=target->query_temp("weapon");
	if (j<450) return 0;
    if (me->query("bhg/biguan")<2) return 0;
   
	if (me->query_temp("bhg/duzun"))
	{
		j=j+me->query_skill("force", 1);
	    j=j+random(j);
	}	
  
	if ( random(me->query_str(1)) >= target->query_dex(1)/2
	 && j > 120 
	 && random(10) > 7
	 && random(me->query("combat_exp")) > target->query("combat_exp")/2
	 && me->query("neili") > 500) 
      {
		switch(random(3)) {
			case 0 :
				msg = HIW"$N八荒六合唯我独尊功已然大成，随手一招「逍遥游」使出，围绕$n急速旋转，运使内劲戳向$n周身大穴！\n";
				msg += HIR"$n只觉全身一麻，已被一招点中「膻中穴」！\n"NOR; 
				target->add_busy(1+random(3));
				me->add("neili",-random(300));
				target->add_condition("no_exert",1+random(2));
				break;
			case 1 :
				msg = CYN"$N劲气澎湃，左手伸出，小指在$n右腕“太渊穴”上轻轻一拂,将$n笼罩于内！\n"NOR;
				msg+=HIW"$n一不小心为$N所制，身形顿时受制。\n"NOR;
				target->recevied_damage("neili", j);
				if ( target->query("neili") < 0 )
					target->set("neili", 0);
				if (weapon)
				{
					weapon->move(environment(target));

				}
				target->add_busy(1+random(2));
				target->add_condition("no_perform",1);
				break;

            case 2 :
				msg = HIR"$N八荒六合唯我独尊功劲力陡然逆转，由至阳化至阴，化作一股无形剑气，点中$n的太阳、少阳、阳明等经脉。\n";
			    msg += "$n但觉伤口处阵阵麻痒，又是针刺般的疼痛，直如万蚁咬啮。\n\n"NOR; 
				target->recevied_damage("qi", 3*j);
				target->recevied_wound("qi", j/2);
				target->apply_condition("shengsi_poison",2+random(2));
				me->add("neili",-random(2000));
				break;
		  
		  }
		message_vision(msg, me, target);
	}
}
