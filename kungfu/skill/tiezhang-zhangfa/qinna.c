// By Spiderii@yt ��д ����������

#include <ansi.h>
string perform_name(){ return HIY"���þ���"NOR; }
inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;


        if( !target )
             target = offensive_target(me);
        if( !target 
          || !me->is_fighting(target)
          || !objectp(target)
          || !living(target)
          || environment(target)!= environment(me))return notify_fail("����������ֻ����ս����ʹ�á�\n");

          weapon = target->query_temp("weapon");

        if( userp(me) 
        &&( me->query_skill_mapped("parry") != "tiezhang-zhangfa"))
                return notify_fail("�����������֡��������������Ʒ������мܵ�����²���ʹ�á�\n");

        if( userp(me) && (me->query_skill_mapped("force") != "guiyuan-tunafa"
        || me->query_skill_prepared("strike") != "tiezhang-zhangfa") )
                return notify_fail("����ڹ����Ʒ����ԣ��������ܷ��ӳ������������֡������ơ�\n");  

        if((int)me->query_skill("guiyuan-tunafa", 1)  < 150 )
             return notify_fail("��Ĺ�Ԫ���ŷ��ȼ���������ʹ���������������֡���\n");

        if((int)me->query_skill("tiezhang-zhangfa",1) < 150 ) 
             return notify_fail("��������Ʒ��ȼ�����������ʹ�á����������֡���\n");


        if( me->query_temp("weapon"))
                return notify_fail("���ȷ������е�������˵�ɣ���\n");     

		if( target->is_busy())
                return notify_fail("�Է���������æ����֮�У�����ʩչ��������\n");     
        if((int)me->query("neili") < 1500)
             return notify_fail("��������������������������֡���\n");

        if((int)me->query("jingli") < 500)
             return notify_fail("��ľ����������������������֡���\n");
      
        message_vision(HIM"\n$N����һ��ͻȻ���У���Ѹ�ײ����ڶ�֮�ƣ����Ʊ�ץ��$n������ȥ��\n" NOR, me, target);
		me->add("jingli",-random(100));
		me->add("neili",-random(200));

        if (objectp(weapon)) //����Է������б���,��ô���
        {

              message_vision(HIM"\n$n��æ����" + weapon->name() + HIM"����$N���п켫��������ѹ����ץס" + weapon->name() + HIM"ͷ����"
								+"��Ե��������δץ�����������,��������"HIR"���������"HIM"����ʽ��\n"NOR, me, target);
              if (random(me->query_str()) > target->query_str()/2 ){

                       message_vision(HIM"\n$n����һ�ȣ����ƻ��ھ�ʹ������" + weapon->name() + HIM"���ֶ�����\n"NOR, me, target);
                       weapon->unequip();
                       weapon->move(environment(target));
                       target->start_busy(3+random(2));
					   if (!me->query("tiezhang/pass"))
							me->start_perform(1,"�����������֡�");
                }
                else
                {
                        message_vision( HIM"\n����$n�书��Ƿ�����һ��֮�£�ץס" + weapon->name() + HIM"���ţ��㾹û�жᵽ��\n"NOR, me, target);
                        me->start_busy(1);
                        me->start_perform(1,"�����������֡�");
              }
              return 1;
        }
        // ������ֲ����õı����Ļ� ,ץ�Է�����,busy
        if (random(me->query_str()) > target->query_con()/2 ){
              message_vision(HIW"\n$n�����ܣ�����$N˫�����總��֮��һ�㣬һ�����죬����ҪѨ�ѱ�$N������ס��\n"NOR, me, target);
              target->add_busy(2+random(3));
		      target->apply_condition("no_perform",1);
              if (!me->query("tiezhang/pass"))
				 me->start_perform(1,"�����������֡�");
        }
        else{
              message_vision( HIM"\n$n���з�����֪����������������Ӳ�ӣ��͵������μ�ת������������\n"NOR, me, target);
              me->start_busy(1);
              me->start_perform(3,"�����������֡�");
        }
        return 1;

}

int help(object me)
{
        write(HIC"\n�����Ʒ�֮�����þ�������"NOR"\n\n");
        write(@HELP 
	�������þ��������������������ͳ�����ԡѪ��ս������
	�����ܽ��������һ�ֿ�������еĹ��������Ǿ�����
	ǧ������ľ������������ڰ����Ź�������Ƽ�����Ϊһ
	�壬�ü��ܺ����Ƶ��ӵı�����С�й�ϵ���������Կ���
	����У����ҿ�����ס���ֶԷ������ţ�ʹ�ĶԷ�������
	ʽ����������

	ע�⣻�⿪�����ռ����⣬���þ�������Ծ��

	perform strike.qinna
		
Ҫ��
	��ǰ���� 1500 ���ϣ�
	��ǰ���� 500 ���ϣ�
	�����Ʒ��ȼ� 150 ���ϣ�
	�����ڹ��ȼ� 150 ���ϣ�
	�����Ʒ��ȼ� 150 ���ϣ�
	�����Ʒ�Ϊ�����Ʒ���
	�����м�Ϊ�����Ʒ���
	�����ڹ���Ԫ���ɷ���
HELP
        );
        return 1;
}