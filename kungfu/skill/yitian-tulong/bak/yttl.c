//tulong.c ����
// By Spiderii@ty
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
 
string perform_name() {return HIR"����������"NOR;}

int perform(object me, object target)
{
        object weapon;
        int skill;

        if( !target ) target = offensive_target(me);
	
        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
    
         weapon =  me->query_temp("weapon");

		if((int)me->query_skill("yitian-tulong",1) < 250 )
         return notify_fail("�������������������������ʹ������������\n");
      
      if((int)me->query_skill("literate",1) < 250 )
         return notify_fail("��Ķ���д�ֵȼ�������ʹ������������\n");  

      if((int)me->query_skill("sword",1) < 250 )
         return notify_fail("��Ļ�������������������\n");

        if( me->query("neili") <= 3000 )
                return notify_fail("�����������ʹ����������\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ�������ʹ����������\n");

        if( me->query_temp("yttlg/tulong"))
                return notify_fail("������������������\n");

        if( !me->query_temp("weapon") || (me->query_temp("weapon"))->query("skill_type") != "sword" )
                return notify_fail("�������޽�����ʹ������������\n");
                
	
        if (me->query_skill_mapped("sword") != "yitian-tulong")
				return notify_fail("��û�м������������������ʹ�ó���������\n");

		message_vision(HIY "\n$N������" + weapon->query("name") + HIY"���ʣ��ڿ���д��������ÿһ�ְ������У���������仯��\n" +
        "�������п��ϣ����ݴ����Ʈѩ�裬���ش��绢���󲽣��������ۻ�ս������캨����\n" NOR, me, target);

        skill = me->query_skill("yitian-tulong",1);
        if (me->query_skill_mapped("force")=="yinyun-ziqi"
			&& me->query_skill("yinyun-ziqi",1)>350)
			skill += me->query_skill("yinyun-ziqi",1)/5;
        
		me->set_temp("yttlg/tulong",skill);
        me->add_temp("apply/attack", skill/3);
        me->add_temp("apply/damage", skill/5);
        me->add_temp("apply/parry",skill/10);        
        me->add_temp("apply/dodge", skill/10);
       
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
       
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
       
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
       
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);

       me->add("neili", -me->query_skill("force",1));
       me->add("jingli", - 100);
       me->start_perform(5, "������");
	   
	   me->add_temp("apply/attack", -skill/3);
       me->add_temp("apply/damage", -skill/5);
       me->add_temp("apply/parry", -skill/10);        
       me->add_temp("apply/dodge",-skill/10);
       me->delete_temp("yttlg/tulong");
       message_vision(HIG "\n$N�Խ����ʣ���ʮ�ĸ���һ����һ��ķ���ʩչ������ʼ�գ�\n\n" NOR, me);

       return 1;
}

int help(object me)
{
   write(HIG"\n����������֮��"HIW"����������"HIG"����"NOR"\n");
	write(@HELP   
	�����ڡ��������𣬱����������������£�Ī
	�Ҳ��ӡ����첻����˭�����档���Ĺ��´�˵��
	�������������ٵ�֮��,�䵱��������,��
	���Ϊ�����ˣ�����ݱ��������������������
	��֮���������ֻ����������ʮ�ĸ�����Ϊһ
	�׶������ֵ������书�������䵱�Ŵ�ɽ
	
	�Ŵ�ɽ�򽭺��ų��������������鷨���輫�
	��˶��������������������������ǽ�������
	�����⾳�����书��ʽ֮�У���Ѩ����������
	�ܶ�����ΪѸ�͡�

	ָ�perform sword.yttl

Ҫ��
	��������Ϊ 250 ��
	����д��Ϊ 250 ��
	���������� 250 ��
	��ǰ����   3000 ���ϣ�
	��ǰ����   1000 ���ϣ�
	���г��н���������           
	˵��������������������������
	���Լ��鷨�ݱ������Ҫ�����
	���鷨���裬����֮�󣬲��ж�
	�мܼ�����
HELP
	);
	return 1;
}
