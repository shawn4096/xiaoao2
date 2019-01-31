// feidao.c   ���ҵ���֮���ɵ�����.
// Create by lsxk@hsbbs 2007/5/11
#include <ansi.h>

inherit F_SSERVER;
private int remove_effect(object me);

string perform_name() {return HIW"�ɵ���"NOR;}

int perform(object me,object target)
{
        object weapon = me->query_temp("weapon");  
        int skill;
    
        if(!me->is_fighting() )
                return notify_fail("���ɵ�����ֻ����ս����ʹ�á�\n");

		if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("���ɵ�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        
		if ((int)me->query_skill("hujia-daofa", 1) < 350 )
                return notify_fail("��ĺ��ҵ���������죬���ò������ɵ�������\n");
		if (me->query_skill("blade",1)<350)
                return notify_fail("��Ļ�����������350������ʹ���������֣���\n");
		if (me->query_skill("force",1)<350)
                return notify_fail("��Ļ����ڹ�����350������ʹ���������֣���\n");

        if (!weapon 
         || weapon->query("skill_type") != "blade"
         || me->query_skill_mapped("parry") != "hujia-daofa"
         || me->query_skill_mapped("blade") != "hujia-daofa")
                return notify_fail("����书���ò��ԣ��޷�ʹ�á��ɵ�������\n");
    
        if ((int)me->query("neili") < 1500 )
                return notify_fail("����������̫��������ʹ�á��ɵ�������\n");

        if ((int)me->query("jingli") < 1500 )
                return notify_fail("�����ھ���̫�٣�����ʹ�á��ɵ�������\n");

        if ((int)me->query_temp("hjdf/fdj"))
                return notify_fail("������ʹ�á��ɵ�����������\n"); 


        message_vision(HIC "$N��ʱһ����ȣ�����"+weapon->name()+HIC"����һ��,ʹ�����ҵ���֮���ɵ�����������\n"+
        "���ҵ�����������һ���������֣������˳��к�Ѱ������������֮��$N��·����ʹ��������������Ȼ����������\n"+
        "���Ժ�ÿ��һ�б��ǹ����������֮��������֮��˾�ǧ��Ҳ��\n"NOR, me);

        if (me->query("quest/ѩɽ�ɺ�/�书/lengquanshengong_teach")
        && me->query_temp("lqsg/lq")
        && me->query_skill_mapped("force") == "lengquan-shengong")
            message_vision(HIW"��$N����Ȫ��֮��"HIB"��Ȫ"HIW"����������£�����"+weapon->name()+HIW"�����ط��Ű�ɫ��\n"NOR, me);
       
		if (me->query_skill("hujia-daofa",1)<450)
			me->start_perform(2,"���ɵ�����");
        me->add("neili", -200);          
        me->add("jingli", -100);
    
        skill = me->query_skill("hujia-daofa", 1);
        me->add_temp("apply/blade",  skill/4);
        me->add_temp("apply/attack",  skill/4);
        me->set_temp("hjdf/fdj", 1);

        call_out("check_fight",1,me,target,weapon,(int)me->query_skill("hujia-daofa",1)/50);
        return 1;
}

void check_fight(object me,object target,object weapon,int amount)
{  
        object wep,wep2;

        if (!me) return;
        wep = me->query_temp("weapon");  
        if(!me->is_fighting()
         || !living(me)
         || me->is_ghost()
         || me->query_skill_mapped("blade") != "hujia-daofa"
         || !wep
		 || amount<0
         || weapon != wep )
           remove_effect(me);
        else {
			if (objectp(wep2=present("fei dao",me))&& !random(2))
			{
				message_vision(HIW"\n$N��շת��Ų�䣬������ͻ��˳�ִӺ��г����"+wep2->query("name")+HIW"����$n��\n"NOR,me,target);
				
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
				wep2->add_amount(-1);
				if ((int)wep2->query_amount()<1)
				{
					message_vision(HIC"������������"+wep2->query("name")+HIC"�Ѿ������ˣ�\n"NOR);
					destruct(wep2);
				}
			}
			call_out("check_fight", 1, me,target,weapon,amount--);
		}
}

private int remove_effect(object me)
{         
        int skill;
        skill = (int)me->query_skill("hujia-daofa", 1);
 
        me->add_temp("apply/blade",  -skill/4);
        me->add_temp("apply/attack",  -skill/4);
        me->delete_temp("hjdf/fdj");
        if(living(me) && !me->is_ghost())
           message_vision(HIW"$Nһ�ס��ɵ�����ʹ�꣬������һ��������\n"NOR, me);
        return 0;
}

int help(object me)
{
   write(WHT"\n���ҵ�����"HIW"�ɵ���"WHT"����"NOR"\n");
   write(@HELP
	�ˡ��ɵ�������Ϊ���ҵ���֮�������ԣ���ȴ�����˺��ҵ���
	�ľ��衰������죬Ѱ�������������ˡ���ʹ��ʱ���ܶ�ʱ
	����������������������ʣ����Ⲣ����ȫ����ֻ�е�����
	�ɹ����������󣬲���������ʾ�����е�����������ʹ���߻�
	���־�ѧ��Ȫ��֮����Ȫ�����������ศ��ɣ��������ˣ�
	
	ָ�perform blade.feidao

Ҫ��
	��ǰ���� 1500 ���ϣ�
	��ǰ���� 1500 ���ϣ� 
	���ҵ��� 350 ���ϣ�
	�������� 350 ���ϣ�
	�����ڹ� 350 ���ϣ�
	��������Ϊ���ҵ�����
	�����м�Ϊ���ҵ���(����Ч)

HELP
   );
   return 1;
}
