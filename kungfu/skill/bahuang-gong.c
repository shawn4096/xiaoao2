// bahuang-gong.c �˻�����Ψ�Ҷ���
// bahuang-gong.c
#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

#include "force.h"

int valid_learn(object me)
{
		mapping fam  = me->query("family");
	if (!fam || fam["family_name"] != "���չ�" )
			 	return notify_fail("�㲢����ɽ���չ����ӣ����ϰ���˰˻�����Ψ�Ҷ��𹦡�\n");
		
	if ( me->query("gender") == "����")
		return notify_fail("���޸����ԣ���������������������İ˻�����Ψ�Ҷ��𹦡�\n");

	if ((int)me->query_skill("bahuang-gong", 1) > me->query_skill("force", 1) + 10
	 && me->query_skill("bahuang-gong", 1) >= 200 )
		return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

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
		else return notify_fail("�����ڵ���Ϊ��������߰˻�����Ψ�Ҷ����ˡ�\n");
	}
	else return notify_fail("�����ڵİ˻�����Ψ�Ҷ�����Ϊֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return SKILL_D("bahuang-gong/") + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIM + me->name() +"��ϥ�������ǿ���������ɫ�������ƣ���ɫ��ױ�á�" NOR,
        "start_my_msg" : "����ϥ����������˻�����Ψ�Ҷ��𹦣������������ڶ��𣬿�ʼ������\n",

		"start_other_msg" : "ֻ��"+ me->name() +"�ǿ�����������ѭ�����ƣ�ͷ���������ڡ�\n",
		"end_my_msg" : "��ֻ��������ת˳���������������棬�������վ��������\n",
		"end_other_msg" : me->name() +"����ǿ׼�İ����������ӣ�վ��������\n",
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
            message_vision(HIC"$N�˻����Ͼ��񹦶����������˻����Ͼ����ۼ���ȫ����������Ϊ�ᴩ��$N��������֮��,�����γ����ܡ�\n"NOR,me,ob);						
            me->add("neili",-1000);			
			if (ob->query("qi")<damage) damage=ob->query("qi")-100;
            ob->receive_damage("qi", damage);
			}
            return i;
        }
    	 else if(m_bhdz > t_force*6/10 && !random(2)){
            i = - damage/2;
            message_vision(HIM"$NĬ��˻����Ͼ����ľ����˻�����Ψ�Ҷ�������������ʱ����$n�˹�����\n"NOR,me,ob);
			if (ob->query("neili")>=2000) {		
            me->add("neili",2000);
            ob->add("neili",-2000);
			}
            COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);       
            return i;
        }
        else if(m_bhdz > t_force*5/10 && !random(1)){
            i = - damage/3;
            message_vision(HIM"$N��Ȼ���򡸰˻����ϡ�֮���裬$n���������˻����Ͼ�����ж��$n���ֹ�����\n"NOR,me,ob);
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
				msg = HIW"$N�˻�����Ψ�Ҷ�����Ȼ��ɣ�����һ�С���ң�Ρ�ʹ����Χ��$n������ת����ʹ�ھ�����$n�����Ѩ��\n";
				msg += HIR"$nֻ��ȫ��һ�飬�ѱ�һ�е��С�����Ѩ����\n"NOR; 
				target->add_busy(1+random(3));
				me->add("neili",-random(300));
				target->add_condition("no_exert",1+random(2));
				break;
			case 1 :
				msg = CYN"$N�������ȣ����������Сָ��$n����̫ԨѨ��������һ��,��$n�������ڣ�\n"NOR;
				msg+=HIW"$nһ��С��Ϊ$N���ƣ����ζ�ʱ���ơ�\n"NOR;
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
				msg = HIR"$N�˻�����Ψ�Ҷ��𹦾�����Ȼ��ת��������������������һ�����ν���������$n��̫���������������Ⱦ�����\n";
			    msg += "$n�����˿ڴ�����������������̰����ʹ��ֱ������ҧ����\n\n"NOR; 
				target->recevied_damage("qi", 3*j);
				target->recevied_wound("qi", j/2);
				target->apply_condition("shengsi_poison",2+random(2));
				me->add("neili",-random(2000));
				break;
		  
		  }
		message_vision(msg, me, target);
	}
}
