// By Spiderii �ϲ���Щ���߰����pobian.posuo�ȵȡ�����

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HIG"����"NOR; }

int perform(object me, object target)
{
        string msg, *skillname, *skilltype = ({});
        object weapon,weapon1;
	    mapping skills;
		int i,damage;
        int skill = me->query_skill("dugu-jiujian",1);
        
        if( !target ) target = offensive_target(me);
		
		//weapon=me->query_temp("weapon");
        weapon1=target->query_temp("weapon");
        
		if( !objectp(target)
        ||  !target->is_character()
		||  !living(target)
        ||  !me->is_fighting(target) )
                return notify_fail("�����С�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon"))
            || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (skill < 400 )
                return notify_fail("��Ķ��¾Ž����������\n");
        if ( me->query_skill("sword",1)< 400 )
                return notify_fail("��Ļ����������������\n");
        if (me->query_skill_mapped("sword") != "dugu-jiujian" )
                return notify_fail("�������޷�ʹ�á����С���\n");


        if ((string)me->query_skill_mapped("parry") != "dugu-jiujian" 
            && userp(me))
                return notify_fail("�������޷�ʹ�á����С���\n");


	   // if(target->query_temp("dgjj/pozhao"))
				//return notify_fail("�����Ѿ���������и�����ס�ˡ�\n");
        //if(me->query_skill("strike",1)<450||me->query_skill("cuff",1)<450)
				//return notify_fail("��Ļ����Ʒ���ȭ��̫�ͣ��޷�ʹ�ö��¾Ž�֮���С�\n");
        if((int)me->query("jingli") < 2000)
                return notify_fail("��ľ���������\n"); 
        if((int)me->query("neili") < 2000)
                return notify_fail("�������������\n"); 
        message_vision(HIC"\n$N�زؽ��⣬���������������������$n��ʽ�е��������ڣ����Ƕ��¾Ž��Ѵﵽ�շ�����ľ��磡\n"NOR,me,target);
		message_vision(HBYEL+HIR"\n$N�������Ƕ��¾Ž��ġ�����ʽ����\n"NOR,me,target);
        me->add("jingli", -1000);
        me->start_perform(3,"�����С�");
       if ( random(me->query_int(1)) >= target->query_int(1)/2
			|| random(me->query("combat_exp")) > target->query("combat_exp")/2 )
	   {
		   

           message_vision(HIG"\n$n����$Nһ��������ʱ���������գ�ʱ��������ơ��Ļ�����֮�䣬ֻ�������书�����Ӳ���ƽʱһ�룡\n"NOR,me,target);

           //weapon1 = target->query_temp("weapon");
		   //��������
          if (weapon1) {
               switch((string)weapon->query("skill_type"))
               {
                  case("sword")    : skilltype += ({"apply/sword"}); 
                                     break;
                  case("blade")    : skilltype += ({"apply/blade"}); 
                                     break;
                  case("axe")      : skilltype += ({"apply/axe"}); 
                                     break;
                  case("brush")    : skilltype += ({"apply/brush"}); 
                                     break;
                  case("club")     : skilltype += ({"apply/club"}); 
                                     break;
                  case("hammer")   : skilltype += ({"apply/hammer"}); 
                                     break;
                  case("dagger")   : skilltype += ({"apply/dagger"}); 
                                     break;
                  case("spear")    : skilltype += ({"apply/spear"}); 
                                     break;
                  case("hook")     : skilltype += ({"apply/hook"}); 
                                     break;
                  case("stick")    : skilltype += ({"apply/stick"}); 
                                     break;
                  case("staff")    : skilltype += ({"apply/staff"}); 
                                     break;
                  case("whip")     : skilltype += ({"apply/whip"}); 
                                     break;
                  case("throwing") : skilltype += ({"apply/throwing"}); 
                                     break;
							
			   }
				//������������и��ʴ���Է�������
				message_vision(HIY"$N���¾Ž��Ѿ��ڻ��ͨ������������$nһ��С�ģ�Ϊ$N�������󡰹�ԪѨ�������е�"+weapon1->query("name")+HIY"������ϡ�\n"NOR,me,target);
				weapon1->move(environment(target));
				target->add_busy(1+random(2));
			
            }
			else {
                  skills = target->query_skill_prepare();
                  if ( skills ) {
                       skillname = keys(skills);
                       foreach (string item in skillname) {
                          if (!target->query_skill(item))
                                  continue;
                          switch(item) { 
                              case("cuff")   : skilltype += ({"apply/cuff"}); 
                                               break;
                              case("strike") : skilltype += ({"apply/strike"}); 
                                               break;
                              case("finger") : skilltype += ({"apply/finger"}); 
                                               break;
                              case("hand")   : skilltype += ({"apply/hand"}); 
                                               break;
                              case("leg")    : skilltype += ({"apply/leg"}); 
                                               break;
                              case("claw")   : skilltype += ({"apply/claw"}); 
                                               break;
                          }
                          i++;
                    }
				  //�������Ѫ��busy
				  if (objectp(target))
				  {
					 target->set_temp("faint_by",me);//����һ����ǣ�����Ī���������� by renlai
					 //target->set_temp("last_damage_from", "��"+me->query("name")+"��ʹ���¾Ž�������ɱ");
					message_vision(HIR"$N���¾Ž������ޱȣ�$n˫�ֺ���һ���ʹ����ʱΪ"+weapon->query("name")+HIR"�����У���Ѫֱ����\n"NOR,me,target);
					damage=me->query_skill("sword",1)+me->query_skill("dugu-jiujian",1)+me->query_skill("force",1);
					if (!userp(target)){
						damage=damage*4;
						damage=damage+random(damage);
					}
					else
						damage=damage*3+random(damage);
					target->receive_damage("qi",damage,me);
					target->receive_wound("qi",damage/2,me);
					target->add_busy(1+random(2));
				   }

               }
				
            
            }
			
			if (!target->query_temp("dgjj/pozhao"))
			{		
		//����û�����������unarmed
				if (sizeof(skilltype) == 0) skilltype += ({"apply/unarmed"});
		//�����Է���ʽ�ͻ�������
				for (i=0; i < sizeof(skilltype); i++)
					target->add_temp(skilltype[i],-skill);
				message_vision(RED"\n$N���¾Ž��������ؾȣ�$nֻ���Լ�����������⡸"HIG"����ʽ"RED"�����ƣ�������Ϊ���ͣ�\n"NOR,me,target);
				
				//target->add_temp("apply/attack",-skill/2);
				//target->add_temp("apply/damage",-skill/2);
				target->add_temp("apply/dodge",-skill/3);
				target->add_temp("apply/parry",-skill/3);
				target->add_temp("apply/defense",-skill/3);
				target->add_temp("apply/dexerity",-skill/10);
				target->apply_condition("no_perform", 2+random(2));
				target->set_temp("dgjj/pozhao",skill);
				target->delete("jiali");			
				call_out("remove_effect", (int)skill/60, target, (int)skill/30, skilltype);
		   }
        } else {
            message_vision(HIG"\n$nͻ��$N����һ�ͣ���ʽ�޷����ᣬ�о�����Ϊ���¾Ž�����ɵ�ѹ����ʱ���ᡣ\n"NOR,me,target);
			me->add_busy(2);

        }
        //message_vision(msg,me,target);
		//���������������
		me->set_temp("dgjj/pozhao",1);
	    if ( me->is_fighting(target))
		        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if ( me->is_fighting(target))
		        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if ( me->is_fighting(target))
		        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if ( me->is_fighting(target))
		        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->delete_temp("dgjj/pozhao");

		me->add_busy(2+random(1));
		me->start_peform(4,"����");
        return 1;
}

void remove_effect(object target, int count, string *skilltype)
{
        int i,skill;
        if (!objectp(target)) return;
		
		skill=target->query_temp("dgjj/pozhao");
			target->add_temp("apply/dodge",skill/3);
			target->add_temp("apply/parry",skill/3);
			target->add_temp("apply/defense",skill/3);
			target->add_temp("apply/dexerity",skill/10);
			target->delete_temp("dgjj/pozhao");
			
        for (i=0; i < sizeof(skilltype); i++)      
              target->add_temp(skilltype[i],skill);
	    
		message_vision(HIW"\n$N�ڹ���ת����������һ�𣬸о��Լ���Ϊ���¾Ž����Ƶ��书�𽥿�ʼ�ָ������ˡ�\n"NOR, target);
		return;
}

int help(object me)
{
	write(HIG"\n���¾Ž������С���"NOR"\n");
	write(@HELP
	���¾Ž����н�����������أ����йؼ����ǿ��
	���ϵл��ȣ������ƵС���Ȼ�������˶��¾Ž���
	��ǳ���Ҫ���Ƶ�֮������������ʤ���С����¾�
	���ų��ƽ������似�����к󣬻���������Է���
	�С��˵���������
	
	ָ�perform sword.pozhao

Ҫ��
	�������¾Ž�Ϊ������
	�������¾Ž�Ϊ�мܣ�
	���¾Ž��ȼ� 400 ���ϣ�
	���������ȼ� 400 ���ϣ�
	�������С�� 2000��
	��ǰ������С�� 2000��
	��ս���гֽ�ʹ�á�
HELP
        );	
        return 1;
}
