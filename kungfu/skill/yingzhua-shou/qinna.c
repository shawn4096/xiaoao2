// By sohu@xojh ӥצ������

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
          || environment(target)!= environment(me))return notify_fail("ӥצ��ֻ����ս����ʹ�á�\n");
          weapon = target->query_temp("weapon");

        if( userp(me) 
        &&( me->query_skill_mapped("parry") != "yingzhua-shou"))
                return notify_fail("�����þ������������ü���ӥצ���мܵ�����²���ʹ�á�\n");

        if( userp(me) && (me->query_skill_mapped("force") != "shenghuo-shengong"
        || me->query_skill_prepared("hand") != "yingzhua-shou") )
                return notify_fail("����ڹ����Ʒ����ԣ��������ܷ��ӳ������þ����������ơ�\n");  

        if((int)me->query_skill("shenghuo-shengong", 1)  < 180 )
             return notify_fail("���ʥ���񹦵ȼ���������ʹ���������þ�������\n");

        if((int)me->query_skill("yingzhua-shou",1) < 180 ) 
             return notify_fail("���ӥץ���ȼ�����������ʹ�á����þ�������\n");

		if(target->is_busy() ) 
             return notify_fail("�Է��Թ˲�Ͼ���ֺα�ȥ��������\n");
        if( me->query_temp("weapon"))
                return notify_fail("���ȷ������е�������˵�ɣ���\n");     


        if((int)me->query("neili") < 1500)
             return notify_fail("��������������������þ�������\n");

        if((int)me->query("jingli") < 500)
             return notify_fail("��ľ����������������þ�������\n");
      
        message_vision(HIW"\n$N��Ȼ�ֱ۱��ǣ��ܡ��á�ָ����������ӥ��צ�Ӱ�ģ��仯��ˣ���$n������ץȥ��\n" NOR, me, target);

 
        if (random(me->query_str(1)) > target->query_dex(1)/2 
			||random(me->query("combat_exp"))>target->query("combat_exp")/2)
		{
              message_vision(HIY"\n$n�����ܣ�����$N˫�����總��֮��һ�㣬һʱ���죬����ҪѨ�ѱ�$N����ץס��\n"NOR, me, target);
			  message_vision(RED"\n$nһ���ʹ��������ӥצ����ʵ��������Ȼ��$n�Ĺ�ͷ�������ˡ�\n"NOR, me, target);
			  target->receive_damage("qi",2000+random(1000),me);
			  target->receive_wound("qi",500+random(500),me);
			  
              target->add_busy(2+random(3));		   
         }
           else{
              message_vision( HIM"\n$n������˵ӥצ�ֵ�����֮�����������з������͵������μ�ת������������\n"NOR, me, target);
              me->start_busy(1);
              me->start_perform(2,"�����þ�����");
           }
           return 1;

}

int help(object me)
{
        write(HIC"\nӥצ�ַ�֮�����þ�������"NOR"\n\n");
        write(@HELP 
	ӥצ�־����������̻��̷���üӥ���������ĳ���������
	�ǽ����ø�����������ں���һ��ľ�������˫��
	��ս�����У��ȿ���ͨ�����������������жԷ���Ѩ����
	�ֿ���ͨ����ɱ��һ���µС�
	
	ָ��:perform hand.qinna
				
Ҫ��
	��ǰ���� 1500 ���ϣ�
	��ǰ���� 500 ���ϣ�
	ӥצ�ֹ��ȼ� 180 ���ϣ�
	�����ڹ��ȼ� 180 ���ϣ�
	�����ַ��ȼ� 180 ���ϣ�
	�����ַ�Ϊӥצ�֣�
	�����м�Ϊӥצ�֣�
	�����ڹ�Ϊʥ���񹦡�
HELP
        );
        return 1;
}