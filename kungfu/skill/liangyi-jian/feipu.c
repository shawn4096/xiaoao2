// feipu.c ���ɷ��� 
// by sohu@xojh 2014

#include <ansi.h>
#include <combat.h>
#include <weapon.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
       int damage, attp, defp;
        object obj;
        string w_name;
        object weapon,jwq;

        if( !target ) target = offensive_target(me);
		if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("�����ɷ��١�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if (!objectp(weapon = me->query_temp("weapon"))
			 || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʲô��Ц��ûװ��������ʹ�����ɷ��١���\n");
       
        if ((int)me->query_skill("liangyi-jian", 1) < 250)
                return notify_fail("������ǽ���������죬�޷�ʹ�����ǽ�����֮һ�ġ����ɷ��١���\n");
        if ((int)me->query_skill("xuantian-wuji", 1) < 250)
                return notify_fail("��������޼������̫ǳ���޷�ʹ�������ɷ��١���\n"); 
        if ((int)me->query("neili",1) < 1500)
                return notify_fail("��������������޷�ʹ�����ǽ��С����ɷ��١��ľ�����\n"); 

//ֻ���׹�һ�����͵�һ�죬���η������ϣ����������н�����Ѫð����
        
		message_vision( BBLU+HIW "$N�����ڽ�������ؽ�������б����һ�С����ɷ��١�����Ӱ����ֱк������\n"NOR, me, target );                
//		message_vision( BBLU+HIW "$N�����ڽ�������ؽ�������б����һ�С����ɷ��١�����Ӱ����ֱк������\n"NOR, me, target );                

      
     
        
        message_vision( HIW "$N���һ����Ĭ��������ֻ�������һ�������Ϊ֮һ�ϣ����������㣬$N����\n"
         + "��������ǿ���������Ϊ��������ʵ�ʵ���Ƭ������ɷ��ٰ���$n���������\n\n"NOR, me, target );
      
        attp = me->query_skill("xuantian-wuji",1) + me->query_skill("liangyi-jian",1);

        defp = target->query_skill("dodge",1);

        if( random( attp ) > random( defp )/2 
			||random(me->query_skill("dodge"))>target->query_skill("parry")/2
			|| target->is_busy()){
        
               message_vision( RED "$n�����������Ѿ�����ɢ����Ƭ���У�ȫ��Ѫ��ɽ���ǧ���ٿף�\n\n"NOR, me, target );
        
                damage = me->query_skill("liangyi-jian",1) + (int)me->query_skill("xuantian-wuji", 1)*2;
                damage = damage - random( target->query_skill("dodge",1)/3 );
                damage *= 2;
                if (damage>5000) damage = 5000+random(1000);                
               
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/3,me);
                target->add_busy(2 + random(2));
                COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
                
                //׷�ӹ���
				if( me->query_skill_mapped("force")=="xuantian-wuji"
					&& random(me->query_dex(1))>target->query_dex()/3) 
				{
				  	message_vision(HBBLU+HIW "$N�������޼����ӵ����£�����ִ���������ḧ"+weapon->query("name")+HBBLU+HIW"���⣬����Բ�£�Ȼ���ɿ��������������������\n\n"NOR 
								 +RED"$n�����㣬��$N�Ľ��Ʋ������ϣ���;���У����ⶶ�������٣�����һ�����ȣ�������$n���ȡ�$n�ҽ�һ����\n"NOR,me,target);
				//  message_vision( BBLU+HIW "$N�������޼����ӵ����£�����ִ���������ḧ"+jwq->query("name")"����Ϊ�����������������\n\n"
				//				+ NOR + RED"$n�ҽ�һ���������Ѿ������ν�����͸��\n"NOR, me, target );
                    damage *= 2;                        
                    target->receive_damage("qi", damage,me);
					target->receive_wound("qi", damage,me);

                    target->add("neili",-damage);
                    if (!userp(target))
						target->add_busy(2 + random(8));
					else target->add_busy(2);
					COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3); 
				}       
        }
        else {

                message_vision( HIY "$p���Ų�æ�ػζ����Σ�˲ʱ�����˽��ꡣ\n" NOR, me, target );
				me->add_busy(2);
        }
   //��������
        if( (int)me->query_skill("art", 1) >= 200
			&& me->query("quest/kl/lyj/feipu/pass")
			&& me->query_skill_mapped("sword")=="liangyi-jian") {
				
		 message_vision( BBLU+HIW "$N��ʦ�����ڽ��ⷢ�ӵ����쾡�£�����ִ���������ḧ���⣬����Բ�£�Ȼ���ɿ��������������������\n"NOR, me, target );    
			  	
			 me->add_temp("apply/sword",me->query_skill("liangyi-jian",1)/4);
			 me->add_temp("apply/damage",me->query_skill("liangyi-jian",1)/5);
			 me->add_temp("apply/attack",me->query_skill("liangyi-jian",1)/3);

              if (objectp(target) && me->is_fighting())
				COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
              if (objectp(target) && me->is_fighting())
				COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			  me->add_temp("apply/sword",-me->query_skill("liangyi-jian",1)/4);
			 me->add_temp("apply/damage",-me->query_skill("liangyi-jian",1)/5);
			 me->add_temp("apply/attack",-me->query_skill("liangyi-jian",1)/3);

        }
        me->add("neili", -300);
/*
        if (weapon->query("imbued") < 3)
        {
			weapon->move(environment(me));
			weapon->set("name", "�ϵ���"+weapon->query("name"));
			weapon->set("id", "cliped "+weapon->query("id"));
			weapon->unequip();
			weapon->set("value", 0);
			weapon->set("weapon_prop", 0);
			weapon->broken("���ϵ�");
			
        }*/
		
		me->start_perform(3+random(3),"�����ɷ��١�");      
        return 1;

}

string perform_name() {return HIY"���ɷ���"NOR;}

int help(object me)
{
    write(WHT"\n���ǽ�����"HIY"���ɷ���"WHT"����"NOR"\n");
    write(@HELP
	���ǽ������������ɾ���������������ʥ������Դ�
	������ɨ�������ۡ����������ִ�ս��һս������ƾ
	��ľ��Ǵ˽��������ǽ��������ڵ������ǽ�������
	������Ѹ�ݣ�������ʤ����ȴ�������鶯��䷢�ӵ�
	���¡��������黭���� 200���ҵõ���̫���ָ���
	���н�����һ��¥��ע������Ṧ������������Ҫ��
		
	ָ�perform sword.feipu
	
Ҫ��
	�����޼��ȼ� 250 �����ϣ�
	���ǽ����ȼ� 250 �����ϣ�
	���������ȼ� 250 �����ϣ�
	�������Ҫ�� 2500 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�����黭�ȼ� 160 ������
	�����������ǽ���
	�����м����ǽ���
	���ֳֽ���������    

HELP
	);
	return 1;
}


