    // by xjqx 2008/12/30

#include <ansi.h>
inherit F_SSERVER;
int perform(object me,object target)
{
        int j = me->query_skill("tianmo-dao", 1)+me->query_skill("tianmo-zhang",1)/6;
        
		object weapon = me->query_temp("weapon");
        
		if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
               return notify_fail("�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");                

        if(!me->query_skill("xixing-dafa", 1) && !me->query_skill("tianmo-gong", 1))
                return notify_fail("����ڹ����ԣ��޷�ʹ�á����������\n");  

        if(me->query_skill("tianmo-gong", 1) < 250)
                return notify_fail("�������ڵ��ڹ���Ϊ��ʹ���������������\n");  

        if( (int)me->query_skill("tianmo-dao", 1) < 250 )
                return notify_fail("��ĵ�����δ���ɣ�����ʹ�þ������\n");        

        if (!weapon
         || weapon->query("skill_type") != "blade"
         || me->query_skill_mapped("blade") != "tianmo-dao")
                return notify_fail("������û�е����޷�ʹ�þ������\n");

        if((int)me->query_skill("tianmo-zhang", 1) < 250 )
                return notify_fail("�����ħ�Ʒ���δ���ɣ�����ʹ�þ������\n");  

        if (me->query_skill_mapped("force") != "tianmo-gong" )
          if(me->query_skill_mapped("force") != "xixing-dafa")
                return notify_fail("����ʹ�õ������ڹ����ԡ�\n");   

        if(me->query_skill_mapped("strike") != "tianmo-zhang" 
         || me->query_skill_prepared("strike") != "tianmo-zhang")
                return notify_fail("��û������ħ�ƣ��޷�ʹ�þ������\n");

     //   if(me->query_skill_mapped("parry") != "tianmo-zhang")
        if(me->query_skill_mapped("parry") != "tianmo-dao")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ�þ������\n");

        if((int)me->query("max_neili") < 3000 )
                return notify_fail("������������Ϊ����������ʹ�þ������\n");      

        if((int)me->query("neili") < 500 )
                return notify_fail("�������������㣬����ʹ�þ������\n");      

        if((int)me->query_skill("blade", 1) < 250 )
                return notify_fail("��Ļ�������������죬�����ڵ����м���ʹ�þ������\n");

        if((int)me->query_skill("strike", 1) < 250 )
                return notify_fail("��Ļ����Ʒ�������죬�����ڵ����м���ʹ�þ������\n");     

        message_vision(HIR"\n$Nŭ��һ����ʹ��������̾���֮�����������ֻ�����쵶Ӱ��Ӱ����ǵ�ͻϮ$n��ȥ��\n"NOR, me,target);
        me->set_temp("tmd/jingshen",1);
        me->add("neili", -400); 
        me->add("jingli", -250);
        if (!userp(me)) j=j/3;
        
        me->add_temp("apply/attack", j);
        me->add_temp("apply/damage", j/3);
        me->add_temp("apply/parry",j);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
        if(objectp(target) && me->is_fighting(target))
        {
                //weapon->unequip(); 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);
                //weapon->wield(); 
        }
        if(objectp(target) && me->is_fighting(target) && me->query_skill("tianmo-dao",1)>120)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
        if(objectp(target) && me->is_fighting(target) && me->query_skill("tianmo-dao",1)>200)
        {
                weapon->unequip(); 
				target->set_temp("must_be_hit",1); //��������̫�ͣ��Ӹ�һ�б��У����job��  by renlai
				message_vision(RED"$N�����б����������䣬������ǰһ�ƣ���������һ������ʽ��Ȼ��Щ���죬������ȴ������\n"NOR,me,target);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
                weapon->wield();
				target->delete_temp("must_be_hit");

        }
        if(objectp(target) && me->is_fighting(target) && random((int)me->query_str()) > 30 && me->query_skill("tianmo-dao",1)>250) {
			    me->set_temp("tmd/pfm1",1);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
				me->delete_temp("tmd/pfm1");

		}
        me->add_temp("apply/parry",-j);
        me->add_temp("apply/attack", -j);
        me->add_temp("apply/damage", -j/3);
        me->delete_temp("tmd/jingshen");
       // if (me->query_skill("tianmo-dao",1)<449)
     //   {
			me->start_busy(1+random(2));
         // }
		me->start_perform(3+random(2),"�����");
        return 1;
}
string perform_name(){ return HIY"�����"NOR; }

int help(object me)
{
        write(HIR"\n��ħ����֮�����������"NOR"\n\n");
        write(@HELP
	��ħ������������̵���������������ǽ�
	ȫ��������һ��ȫ������������������
	�������г��֣�����Է�����ν���������
	�񣬽������к��ر��ֳ�����
	
	ָ�perform blade.jingshen

Ҫ��  
	��ǰ�������� 500  ���ϣ�
	����������� 3000 ���ϣ�
	��ħ�����ȼ� 250 ���ϣ�
	��ħ�󷨻����Ǵ󷨵ȼ� 250 ���ϣ�
	���������ȼ� 250 ���ϣ�
	�����ڹ��ȼ� 250 ���ϣ�
	�����Ʒ��ȼ� 250 ���ϣ�
	��ħ�Ʒ��ȼ� 250 ���ϣ�
	��������Ϊ��ħ����
	�����м�Ϊ��ħ����
	�����Ʒ�Ϊ��ħ��;
	�����ڹ�Ϊ���Ǵ󷨻���ħ����
	���ֱֳ���,��ʽԽ�Ǿ���������Խ�Ǵ󣬾��������������Լ�׽����
	�е����������ɣ�����Ϊ�ˡ�
	ע�⣺��ħ��120,200,250�����½������һ�У�Խ��Խǿ��

HELP
        );
        return 1;
}
