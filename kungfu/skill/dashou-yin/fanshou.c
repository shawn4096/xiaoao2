//fanshou.c  ���ֹ���
//By sohu@xojh ���ֹ���
// �������˺������������������£����˰ݷ�֮������˫�ֺ�ʮ��ʩ��һ��ͻȻ˫������һ�ɾ�����Ȼ�˳���
//����һ���ֻ���Ҳ���������ƣ�Ҫ����ʮ����ϰ���ڹ���֡����ɾ���մ�����
//��������ͻ������Ϊ�⹦�����ƶ�Ȼ̽������ץ����һ������һ��Ѹ��֮��������һ����ȴҲ�����鶯�����ֹ���ǿ��ǿ��Ӳ��Ӳ����������һ���ϣ������ֿ���
#include <ansi.h>
string perform_name(){ return HIC"���ֹ���"NOR; }
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
          || environment(target)!= environment(me))
		return notify_fail("�����ֹ���ֻ����ս����ʹ�á�\n");
          
		  weapon = target->query_temp("weapon");

        if( userp(me) 
        &&( me->query_skill_mapped("parry") != "dashou-yin"))
                return notify_fail("�����ֹ��󡹱������ô���ӡ�����мܵ�����²���ʹ�á�\n");

        if( userp(me) && (me->query_skill_mapped("force") != "longxiang-boruo"
        || me->query_skill_prepared("hand") != "dashou-yin") )
                return notify_fail("����ڹ����ַ����ԣ��������ܷ��ӳ������ֹ��󡹵����ơ�\n");  
		
        if((int)me->query_skill("longxiang-boruo", 1)  < 180 )
             return notify_fail("������������ȼ���������ʹ���������ֹ��󡹡�\n");

        if((int)me->query_skill("dashou-yin",1) < 180 ) 
             return notify_fail("��Ĵ���ӡ�ȼ�����������ʹ�á����ֹ��󡹡�\n");

		if (!me->query("quest/dls/dsy/tianyin/pass"))
			 return notify_fail("����ӡ���Ǵ����²���֮�أ����ȸ�����������̡����ֹ��󡹡�\n");
        if( me->query_temp("weapon"))
                return notify_fail("���ȷ������е�������˵�ɣ���\n");     

		if( target->is_busy())
                return notify_fail("�Է��Ѿ�æµ�����ˣ��ŵ������ɣ���\n");     

        if((int)me->query("neili") < 1500)
             return notify_fail("��������������������ֹ��󡹡�\n");

        if((int)me->query("jingli") < 500)
             return notify_fail("��ľ����������������ֹ��󡹡�\n");
      
        message_vision(RED"\n$N˫�ֺ�ʮ��ʩ��һ��ͻȻ˫������һ�ɾ�����Ȼ�˳���$n��Ҫ���ֻ������ڹ��࿹��ͻȻ��ʶ�����\n" NOR, me, target);
		message_vision(HIC"\n��ʱ$Nͻ������Ϊ�⹦�����ƶ�Ȼ̽������ץ$n������һ��Ѹ��֮������$n�������ֹ���ǿ��ǿ��Ӳ��Ӳ��\n"
							+"����������һ���ϣ���ž����һ�����죬�����ֿ���\n"NOR,me,target);
	
        if (random(me->query_str(1)) > target->query_dex(1)/2 
			||random(me->query("combat_exp"))>target->query("combat_exp")/2){
              message_vision(HIR"\n$n�����ܣ�����$N˫�����總��֮��һ�㣬һʱ���죬����ҪѨ�ѱ�$N����ץס��\n"NOR, me, target);
              target->add_busy(1+random(2));
			  //���ܼ���
			  target->set("jiali",0);
			  target->receive_damage("qi",500+random(1000),me);
		      target->apply_condition("no_force",1+random(1));
              //me->start_perform(5,"�����ֹ���");
           }
           else{
              message_vision( HIM"\n$n������˵����ӡ�����з��ֹ��������֮�����������з������͵������μ�ת������������\n"NOR, me, target);
              me->start_busy(1);
              me->start_perform(2,"�����ֹ���");
           }
		me->add("neili",-230);
		me->add("jingli",-150);
        if (me->query_skill("dashou-yin",1)<250)
        {
			me->start_perform(1,"���ֹ���");
        }
		return 1;

}

int help(object me)
{
        write(HIC"\n����ӡ֮�����ֹ��󡹣�"NOR"\n\n");
        write(@HELP 
	���ֹ���������Ǵ������������˵ĳ���������
	�ǽ������ճ��޳ֵ�����֮�ٶ��ĿȾ����Ȼ
	���뵽�似֮�У��ɶ�ׯ���鶯���ɺ�Ȼ���
	�죬��ʱ��֮������ַ���ʤ��������������
	�˶�����������������֮�¡�
	ע�⣺250����С��
	
	ָ��;perform hand.fanshou
				
Ҫ��
	��ǰ�������� 1500 ���ϣ�
	��ǰ�������� 500 ���ϣ�
	����ӡ�ĵȼ� 180 ���ϣ�
	�����ڹ��ȼ� 180 ���ϣ�
	�����Ʒ��ȼ� 180 ���ϣ�
	�����Ʒ�Ϊ����ӡ��
	�����м�Ϊ����ӡ��
	�����ڹ�Ϊ�����������
HELP
        );
        return 1;
}