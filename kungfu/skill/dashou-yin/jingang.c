// jingang.c ���ڴ���ӡ֮���ӡ
//By sohu@xojh

#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return HBYEL+HIR"���ӡ��"NOR; }

int perform(object me, object target)
{
	int damage;
	string msg;

		if( !target ) target = offensive_target(me);

		if( !target || !target->is_character() || !me->is_fighting(target) )
			return notify_fail("�����ӡ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");


		if( objectp(me->query_temp("weapon")) )
			return notify_fail("�������ֲ���ʹ�á����ӡ������\n");		
		if((int)me->query_skill("longxiang-boruo",1)<100)
            return notify_fail("��������������Ϊ������\n");	
        if( (int)me->query_skill("dashou-yin", 1) < 100 )
			return notify_fail("������ڴ���ӡ��Ϊ����������ʹ�á����ӡ������\n");
        if((int)me->query("max_neili",1)<1000)
            return notify_fail("���������Ϊ̫���޷�ʹ�ñ��ơ�\n");                        
        if( (int)me->query("neili", 1) < 500 )
			return notify_fail("����������̫��������ʹ�á����ӡ������\n");
		if (me->query_skill_mapped("hand")!="dashou-yin"
		||me->query_skill_prepared("hand")!="dashou-yin")
			return notify_fail("��û�м���������ʹ�á����ӡ������\n");

		message_vision(RED "$N" RED "����ׯ�أ������գ�����Я�ž��糯$n" RED "��Ȼ�ĳ����������ھ�ѧ��"HIY"���ӡ"NOR"��!\n" NOR,me,target);

		damage = 100+random((int)me->query_skill("dashou-yin",1)
			+(int)me->query_skill("longxiang-boruo",1)
			+(int)me->query_skill("poison",1));
                
		damage = damage*2 + random(damage);
        
		me->add("neili", -150);
 
		if (userp(target)) damage=damage/2;
       
		if (damage <1000) damage=1000;
		
		message_vision( RED"$NΪ��һ���Ʒ���ѹ�ƣ���ʱ��Ϣ������\n" NOR,me,target);
	
		target->receive_damage("qi", damage,me);
		tell_object(me,"��ԶԷ������"+damage+"����˺���\n");
		//target->receive_wound("qi", damage/3,me);
        
	
          
		if (random(me->query("combat_exp")) > target->query("combat_exp")/2
			||random(me->query_str())>target->query_str()/2)
		{
			damage = 1000+random((int)me->query_skill("dashou-yin", 1)
			+(int)me->query_skill("longxiang-boruo",1)
			+(int)me->query_skill("poison",1));
			if ( (int)me->query_str() > (int)target->query_con())
				damage = random( (damage*(int)me->query_str())/5 );
			else damage = damage + random(damage/2);
            
			if ( damage > 2500 ) damage = 2500 +random(1000); 

			target->receive_damage("qi", damage,me);
			target->receive_wound("qi", damage/3,me);
			tell_object(me,"���з�������ԶԷ��������"+damage+"����˺���\n");

			me->add("neili", -150);
			
			if( damage < 1000 ) msg = HIY"$n�������֣����Ƶ���������������Ϥ�����⡣\n"NOR;
        	else if( damage < 3000 ) msg = HIY"$n������������$NӲƴ��һ�ƣ��䲻�Կ������ظ�֮����Ѫ��ӿ�Ѽ��ǲ������\n"NOR;
        	else if( damage < 5000 ) msg = RED"$n��ǿ��˫�ֻ�����У�����$N������ŭ������ԴԴ������Ю��һ������ֱ͸$n���ܣ�\n"NOR;
            else msg = HIR"$n�������ܣ���$N����һ����ӡ���ؿ�����������$nֻ��������ɢ����һ����Ѫ���������\n"NOR;
			message_vision(msg, me, target);

		} else 
		{
            me->start_busy(3);

			message_vision(CYN"����$p�������أ����������罫$P��������Ϊ���Ρ�\n"NOR,me,target);
		}
		me->start_perform(3,"���ӡ");
		return 1;
}
int help(object me)
{
        write(HIY"\n���ڴ���ӡ�����ӡ������"NOR"\n");
        write(@HELP
	���ڴ���ӡ���������ӡ����,����ս���г�ŭĿ�����
	һ�ƻӳ�������̩ɽѹ��������Է�ǿ���������Ĺ�����
	����������ͬȫ��̿���������ù����У���������
	���������ۻ����������ɡ�
	
	ָ�perform hand.jingang

Ҫ��  
	��ǰ���� 500 ���ϣ�      
	������� 1000 ���ϣ�
	��ǰ���� 300 ���ϣ�  
	���ڴ���ӡ�ȼ� 100 ���ϣ�
	�����ַ�Ϊ���ڴ���ӡ
	���ַ�����ӡ��
	
HELP
        );
        return 1;
}

