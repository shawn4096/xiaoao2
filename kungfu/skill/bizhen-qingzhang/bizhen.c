// bizhen.c  �������� ����
// sohu@xojh
 
#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

int effect_back(object me, int count);

string perform_name() {return HBBLU HIG"����"NOR;}

int perform(object me, object target)
{
        int lev;
        
        if( !target ) target = offensive_target(me);

         if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) 
         || !living(target) )
                return notify_fail("�����롹ֻ����ս����ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á����롹��\n");   

        if( (int)me->query_skill("bizhen-qingzhang", 1) < 350 )
                return notify_fail("����Ʒ���������죬ʹ���������롹������\n");

        if((int)me->query_skill("force",1) < 350 ) 
                return notify_fail("����ڹ���Ϊ��������ʹ���������롹������\n");
             

        if (me->query_skill_prepared("strike") != "bizhen-qingzhang" 
         || me->query_skill_mapped("strike") != "bizhen-qingzhang" )
                return notify_fail("�������޷�ʹ�á����롹��\n");    
 

        if( (int)me->query("neili") < 1000)
                return notify_fail("����������̫����ʹ���������롹��\n");

        if( (int)me->query("jingli") < 400 )
                return notify_fail("�����ھ���̫�٣�ʹ���������롹��\n");
        if( me->query_temp("bzqz/bizhen") )
                return notify_fail("������ʩչ�����롹������\n");
 
        lev = (int)me->query_skill("bizhen-qingzhang", 1); 
       
		message_vision(HIG "$Nչ���Ʒ�������ǧ����ö���뷴�����죬��������ӿ���ȣ���͸˫�ƣ�������˿��˲�������ͷţ�\n" NOR, me);
		message_vision(HIG "$N��������������ʣ�ȴҲ�����������ۣ�ǧǧ����ö���뻯��һ����Ӱ������һ�������������Ӱ��������\n" NOR, me);

        me->add_temp("apply/damage", lev/10);
        me->add_temp("apply/attack", lev/5);       
        me->add_temp("apply/strike", lev/5);
		me->add_temp("apply/dodge", lev/4);

		if (random(me->query_skill("force",1))>target->query_skill("dodge",1)/2
			||random(me->query_dex(1))>target->query_dex(1)/2)
		{
			message_vision(RED"$nһʱ�����Ϊ$N�����������סѨ������ʱһ����Ѫ��ӿ��\n" NOR, me,target);
			target->apply_condition("no_exert",2);
			target->add_busy(2);
		}
		me->set_temp("bzqz/bizhen",lev);
        
        me->add("neili", -400);
        me->add("jingli", -100);
		effect_back(me,(int)lev/20);
		//call_out("effect_back",1,me,(int)lev/20);
        return 1 ;
}

int effect_back(object me,int count)
{
	int lev;
	if (!me||!me->query_temp("bzqz/bizhen")) return 0;
	lev=me->query_temp("bzqz/bizhen");
	if (count--<0
		||me->query_skill_mapped("strike")!="bizhen-qingzhang"
		||me->query_skill_prepared("strike")!="bizhen-qingzhang"
		||!me->is_fighting())
	{
        me->add_temp("apply/damage", -lev/10);
        me->add_temp("apply/attack", -lev/5);       
        me->add_temp("apply/strike",-lev/5);
		me->add_temp("apply/dodge", -lev/4);

		me->delete_temp("bzqz/bizhen");

		message_vision(HIG "$N��ʩչ�ġ����롹���������չ���\n" NOR, me);
		return 1;
	}
	call_out("effect_back",1,me,count--);
}
int help(object me)
{
   write(HIC"\n�������ơ�" HIG"����"HIC"����"NOR"\n\n");
   write(@HELP
	����������Ħ���ʿл�̿͵Ķ����ؼ���һ��ʩչ
	��������ſգ�������Ϊ��ӿ�������Ʒ����쳣��
	�ص�һ�ֹ�����������������Ч������������
	��ӿȥ��������ˣ����ֻ��ܵ������ķ�ѨЧ��
	
	ָ�perform strike.bizhen

Ҫ��: 
	��ǰ���� 1000 ���ϣ�
	��ǰ���� 400 ���ϣ�
	�������Ƶȼ� 350 ���ϣ�
    �����ڹ��ȼ� 350 ���ϣ�
	�����Ʒ�Ϊ�������ƣ�
	�ڹ����ޣ�
	���֣����������ơ�

HELP
   );
   return 1;
}

