//by caiji@SJ
//�����������˲�����3�ᣬ975ҳ1996��11����ӡ��/�������������
// By Spiderii@ty ȡ��call die��Ч���ж�
//by kingso add verify

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
string perform_name(){ return HIC"����"NOR; }
int perform(object me, object target)
{
        object weapon;
        int damage,p;
        string msg,dodge_skill,tmp;;
		weapon = me->query_temp("weapon");
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        ||  !living(target))
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( (int)me->query_skill("tianshan-zhang", 1) < 100 )
                return notify_fail("�����ɽ�ȷ�����̫ǳ���������ˡ�\n");

        if( (int)me->query_skill("staff", 1) < 100 )
                return notify_fail("��Ļ����ȷ�����̫ǳ���������ˡ�\n");

        if( (int)me->query_skill("huagong-dafa", 1) < 100 )
                return notify_fail("����ڹ�����̫ǳ���������ˡ�\n");
                
        if( (int)me->query("max_neili") < 1400 )
                return notify_fail("�������̫ǳ���������ˡ�\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("��������������������ˡ�\n");
        if( (int)me->query("jingli") < 500 )
                return notify_fail("��ľ����������������ˡ�\n");

		if ( me->query_temp("tsz/feizhi"))
                return notify_fail("������ʹ�á���������\n");
        
		if (!objectp(weapon) 
			|| weapon->query("skill_type") != "staff"
            || me->query_skill_mapped("staff") != "tianshan-zhang")
                return notify_fail("��ʹ���ˡ�������ô?\n");
                 
       
		
        message_vision(BLU "\n$N���һ���������š�������һ�����죬$N�����е�"+weapon->query("name")+BLU"����$n��\n"NOR,me,target);
		 me->set_temp("tsz/feizhi", 1); 
        if(  random((int)me->query_skill("dodge",1)) >(int)target->query_skill("dodge",1)/2
			|| random((int)me->query("combat_exp"))>(int)target->query("combat_exp")/3)
		{
           //write(HIC"TESET1\n"NOR);
		   damage = 4 * ((int)me->query_skill("tianshan-zhang", 1)+me->query_skill("huagong-dafa", 1));
           damage = damage + random(damage) + 5*me->query("jiali");
		   if (!userp(target)) damage=2*damage;
		 
           me->add("neili", -200);
           me->add("jingli",-100);
           if (!userp(target))
           	   if(damage>4500) damage=4500+random(1000);
		   else if(damage>3000) damage=3000+random(1000);
           
		   message_vision(HIR"$n������������������"+weapon->query("name")+HIR"���ػ��У�\n"NOR,me,target);
 
		   target->receive_damage("qi", damage,me);
           target->receive_wound("qi", damage/3,me);
           
           //p = (int)target->query("qi")*100/(int)target->query("max_qi");
         //  target->set_temp("last_damage_from", me);
          // msg += damage_msg(damage, "����");
          // msg += "( $n"+eff_status_msg(p)+" )\n";
         //  msg = replace_string( msg, "$l", "�ؿ�" );
       //    msg = replace_string( msg, "$w", weapon->query("name"));
		   
		  // message_vision(msg, me, target);
           
		  // COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

		   
		}   
        else {
			

             // dodge_skill = target->query_skill_mapped("dodge");
              //if( !dodge_skill ) dodge_skill = "dodge";
              //if (stringp(tmp = SKILL_D(dodge_skill)->query_dodge_msg(target, 1)))
		      //msg = tmp;
              me->add("neili", -100);
              me->start_busy(1); 
             // if( weapon->unequip())
              
			  if ( me->query("quest/xx/tsz/laoyue/pass") 
			   && me->query_skill_mapped("dodge")=="zhaixingshu"
			   && me->query("env/��ɽ�ȷ�")=="��������") 
			  {
				message_vision(HIC"$N����һ�ݣ�ժ�����������������ɳ�ȥ��"+weapon->query("name")+HIC"��ס��\n"NOR,me);
				me->add("neili",-random(150));
				me->add("jingli",-random(100));
		   
		       }//else weapon->move(environment(me));
			  
			  else if( random(me->query("kar"))< 5
              &&(int)target->query_encumbrance() *100 / (int)target->query_max_encumbrance()<85)
			  {
                	weapon->move(target);
                	message_vision(HIY"$n��������һ�ӣ���ѷ�����"+weapon->query("name")+HIY"�������У�\n"NOR,me,target);
              } 
			  else if(random(me->query("kar"))<1)
			  {
                        
                        message_vision(HIY"$n�����������ϣ����ŷ�����"+weapon->query("name")+HIY"һ����"+weapon->query("name")+HIY"��ʱ��Ϊ���Σ�\n"NOR,me,target);
                       // weapon->set("name", "�ϵ���" + weapon->query("name"));
                        //weapon->set("value", 0);
						//weapon->set("no_get", 1);
                      //  weapon->set("weapon_prop", 0);
						weapon->broken("��ϵ�");
						//weapon->move(environment(me));
               } else weapon->move(environment(me));
                
				
        }
        me->delete_temp("tsz/feizhi"); 
        me->start_perform(3, "��������");
        return 1;
}

int help(object me)
{
   write(HIC"\n��ɽ�ȷ�����������"NOR"\n");
   write(@HELP
	��ɽ�ȷ���λ�������ɳ��������似����������
	���޵����Դ˺��н���������Ϊ��ɽ�ȷ�����ȥ
	�޻ص����������Խ������������������������
	�ֵ�������
	ע�⣺������ʦ����̹�����ɽ�ȷ���ʹ�ú���
	���µļ��ɣ����ɳ�ȥ�������ջ�������������
	һ���������;�����

	set ��ɽ�ȷ� ��������

	perform staff.feizhi
	
Ҫ��
	�������Ҫ�� 1400 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	��ɽ�ȷ��ȼ� 100 ���ϣ�
	�����󷨵ȼ� 100 ���ϣ�
	�����ȷ�Ϊ��ɽ�ȷ���
	�����ڹ�Ϊ�����󷨣�
	�����м�Ϊ��ɽ�ȷ���
	�������������

HELP
   );
   return 1;
}

