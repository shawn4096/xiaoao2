// By sohu@xojh ����������

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
          
		  weapon = me->query_temp("weapon");
		if (weapon)
			return notify_fail("�����������֡����ֲ���ʹ�á�\n");
		if (userp(me) 
			&& ! me->query("quest/gb/shs/qinna/pass"))
                return notify_fail("��������������Ԫ��̣������ڻ�����ʹ�á�������һ�У�\n");
        if( me->query_skill_mapped("parry") != "suohou-shou")
                return notify_fail("�����������֡��������������Ʒ������мܵ�����²���ʹ�á�\n");
        if( me->query_skill_prepared("hand") != "suohou-shou" )
                return notify_fail("����ַ����ԣ��������ܷ��ӳ������������֡������ơ�\n");  

        if((int)me->query_skill("force", 1)  < 250 )
             return notify_fail("��Ļ����ڹ��ȼ���������ʹ���������������֡���\n");

        if((int)me->query_skill("suohou-shou",1) < 250 ) 
             return notify_fail("��������Ʒ��ȼ�����������ʹ�á����������֡���\n");


        if( me->query_temp("weapon"))
                return notify_fail("���ȷ������е�������˵�ɣ���\n");     

		if( target->is_busy())
                return notify_fail("�Է��Թ˲�Ͼ�����ֽ����ɣ�\n");
        if((int)me->query("neili") < 1500)
             return notify_fail("��������������������������֡���\n");

        if((int)me->query("jingli") < 500)
             return notify_fail("��ľ����������������������֡���\n");
      
        message_vision(HIW"\n$N��Ȼ�ֱ۱��ǣ��ܡ��á�ָ������ʱ��Ϊӥצʱ��Ϊ��ץ���仯��ˣ���$n������ץȥ��\n" NOR, me, target);

        
        if (random(me->query_str(1)) > target->query_dex(1)/2 
			||random(me->query("combat_exp"))>target->query("combat_exp")/2){
              message_vision(HIC"\n$n�����ܣ�����$N˫�����總��֮��һ�㣬һʱ���죬����ҪѨ�ѱ�$N����ץס��\n"NOR, me, target);
              target->add_busy(1+random(3));
		      //target->apply_condition("no_perform",1+random(1));
              //me->start_perform(5,"�����������֡�");
           }
           else{
              message_vision( HIM"\n$n������˵���������ֵ�����֮�����������з������͵������μ�ת������������\n"NOR, me, target);
              me->start_busy(1);
              me->start_perform(2,"�����þ�����");
           }
		  me->add("neili",-250);
		  me->add("jingli",-200);
	
           return 1;

}

int help(object me)
{
        write(HIC"\n���������ַ�֮�����þ�������"NOR"\n\n");
        write(@HELP 
	���������־�������ؤ���������ĳ����������ǽ�����
	�������ں���һ��ľ�������˫����ս�����У��ȿ���ͨ
	�����������������жԷ���Ѩ��������ס�Է���Ҫ����λ
	�ƵУ�����������250��С�ɡ�
	ע�⣺���кͱ����Լ�ս�������й�,�������Ԫ���

	ָ�perform hand.qinna
			
Ҫ��  				
	��ǰ���� 1500 ���ϣ�
	��ǰ���� 500 ���ϣ�
	�������õȼ� 250 ���ϣ�
	�����ڹ��ȼ� 250 ���ϣ�
	�����ַ��ȼ� 250 ���ϣ�
	�����ַ�Ϊ���������֣�
	�����м�Ϊ���������֣�
	�ҿ���
HELP
        );
        return 1;
}