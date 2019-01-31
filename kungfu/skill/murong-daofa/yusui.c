//yusui.c ���鵶��
//cre by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;
int perform(object me,object target)
{
        int skill;
        object weapon = me->query_temp("weapon");
        skill = me->query_skill("murong-daofa",1);
        
		if (!me->query("quest/mr/mrdf/yusui/pass"))
			return notify_fail("��ֻ����˵�����鵶���������ȴ��֪�������ʹ�á�\n");                

		
        if( !target ) target = offensive_target(me);

        if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))               
                return notify_fail("���鵶��ֻ�ܶ�ս���еĶ���ʹ�á�\n");                

        if( (int)me->query_skill("murong-daofa", 1) < 250 )
                return notify_fail("��ĵ�����δ���ɣ�����ʹ�����鵶�⣡\n");        

        if (!weapon
         || weapon->query("skill_type") != "blade"
         || me->query_skill_mapped("blade") != "murong-daofa")
                return notify_fail("������û�е����޷�ʹ�����鵶�⣡\n");




        if(me->query_skill_mapped("parry") != "xingyi-zhang")
		if(me->query_skill_mapped("parry") != "douzhuan-xingyi")

			if(me->query_skill_mapped("parry") != "murong-daofa")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ�����鵶�⣡\n");

        if((int)me->query("max_neili") < 3000 )
                return notify_fail("������������Ϊ����������ʹ�����鵶�⣡\n");      

        if((int)me->query("neili") < 500 )
                return notify_fail("�������������㣬����ʹ�����鵶�⣡\n");      

        if((int)me->query_skill("blade", 1) < 250 )
                return notify_fail("��Ļ�������������죬�����ڵ����м���ʹ�����鵶�⡣\n");
        if((int)me->query_skill("murong-daofa", 1) < 250 )
                return notify_fail("���Ľ�ݵ���������죬�����ڵ����м���ʹ�����鵶�⡣\n");

        if(me->query_temp("mrdf/yusui"))
                return notify_fail("������ʩչ���鵶�������\n");

        message_vision(CYN"\n$N�����е�"+weapon->query("name")+CYN"һ�������������£���ʱ����ƬƬ���⣬����������̣�\n"+
			"$Nʩչ������Ľ�ݵ�������"HIW"�����鵶�⡹"CYN"$nֻ����ǰһƬ���⣬�����ⷴ���¼�Ϊҫ�ۣ�\n"NOR, me,target);
        me->add("neili", -200); 
        me->add("jingli", -150);
        

        me->add_temp("apply/attack", skill/8); 
        me->add_temp("apply/blade",skill/5);
		me->add_temp("apply/damage",skill/8);
		
		me->set_temp("mrdf/yusui",skill); 
		me->set("mrdf/yusui",skill);//������ʱ�����������˳�����ֵ
        call_out("xs_attack",1,me,(int)skill/20);
			
		return 1;
}

int xs_attack(object me,int count)
{
	object weapon;
	
	int skill;
	
	if (!me) return 1;

	skill=me->query("mrdf/yusui");
	weapon=me->query_temp("weapon");
	if (count<0
		|| !me->is_fighting()
		|| me->query_skill_mapped("blade")!="murong-daofa"
		|| !weapon
		|| weapon->query("skill_type")!="blade")
	{
		me->add_temp("apply/attack", -skill/8); 
        me->add_temp("apply/blade",-skill/5);
		me->add_temp("apply/damage",-skill/8);
		me->delete_temp("mrdf/yusui");
		me->delete("mrdf/yusui");
		message_vision(CYN"\n$N�����չ�������һ����,��Ľ�ݵ��������鵶�⡹ͣ��������\n"NOR, me);

		me->start_perform(4,"���鵶��");

		return 1;

	}   
	 
     call_out("xs_attack",1,me,count--);
}

string perform_name(){ return HIW"���鵶��"NOR; }

int help(object me)
{
        write(HIC"\nĽ�ݵ���֮"+HIW+"�����鵶�⡹"NOR"\n\n");
        write(@HELP
	Ľ�ݵ�������Ľ�ݼ����д����ҳ��ǵ���Ҫ�����似��Ľ����
	�������Ǵ�������ᣬ��Ľ�ݴ���ʼ�������ھ���֮�䣬����
	����ʵս���������Ѿ��ںϲ����������ɵĵ���������һ����
	�������м��ơ��˵��������ޱȣ�����ʤ������Ϊ��Ϊ�ҳ���
	�ã������ڹ���������Ҫ��������Խ����������ǿ��
	
	ע�⣺����ΪĽ�ݵ����������ڣ����ھ�������Ϊ���鲻Ϊ��
		ȫ��Ѫ��֮�£��������ͬѯ�ʽ������ɡ�
	
ָ�perform blade.yusui

Ҫ��
	��ǰ����Ҫ�� 500 ���ϣ�
	�������Ҫ�� 3000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	Ľ�ݵ����ȼ� 250 ���ϣ�
	���������ȼ� 250 ���ϣ�
	�����м�ΪĽ�ݵ�����ת���ƣ�
	���гֵ�
                
HELP
        );
        return 1;
}
