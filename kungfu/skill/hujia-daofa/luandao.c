// luandao.c   ���ҵ���֮�����ҵ�����.
// Create by lsxk@hsbbs 2007/5/11
#include <ansi.h>

inherit F_SSERVER;
int remove_effect(object me);
string perform_name() {return HIR"���ҵ���"NOR;}
int perform(object me,object target)
{
        object weapon = me->query_temp("weapon");  
        int skill;
    
                
		if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
				return notify_fail("�����ҵ�����ֻ����ս����ʹ�á�\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 400 )
                return notify_fail("��ĺ��ҵ���������죬���ò��������ҵ�������\n");
    	if (me->query_skill("blade",1)<400)
                return notify_fail("��Ļ�����������400������ʹ�á����ҵ���������\n");
		if (me->query_skill("force",1)<400)
                return notify_fail("��Ļ����ڹ�����400������ʹ�á����ҵ���������\n");

        if (!weapon 
         || weapon->query("skill_type") != "blade"
//         || me->query_skill_mapped("parry") != "hujia-daofa"
         || me->query_skill_mapped("blade") != "hujia-daofa")
                return notify_fail("����书���ò��ԣ��޷�ʹ�á����ҵ�������\n");
    
        if ((int)me->query("neili") < 2000 )
                return notify_fail("����������̫��������ʹ�á����ҵ�������\n");

        if ((int)me->query("jingli") < 1000 )
                return notify_fail("�����ھ���̫�٣�����ʹ�á����ҵ�������\n");

        if ((int)me->query("max_neili") < 9000 )
                return notify_fail("�����ڵ����������Ϊ����������ʹ�á����ҵ�������\n");

        if ((int)me->query_temp("hjdf/ldj"))
                return notify_fail("������ʹ�á����ҵ�����������\n"); 


        message_vision(YEL "$N��ʱ���α�죬����"+weapon->name()+YEL"���ƴ���,��ʽ���,�������Ǻ��ҵ���֮�����ҵ�����������\n"NOR,me);
		message_vision(HIY "\n����ҵ������������ᣬ�����иգ�Ѹ��ʱ�����籼�ף����ȴ���Ԩ���ţ�\n"NOR,me);

        if (me->query("quest/ѩɽ�ɺ�/�书/lengquanshengong_teach")
			&& me->query_temp("lqsg/lq")
			&& me->query_skill_mapped("force") == "lengquan-shengong")
            message_vision(HIB"��$N����Ȫ��֮��"HIW"��Ȫ"HIB"����������£�����"+weapon->name()+HIB"�����ط�����ɫ��\n"NOR, me);
        
		me->start_perform(random(3)+1,"�����ҵ�����");
        me->add("neili", -400);
        me->add("jingli", -200);
    
        skill = me->query_skill("hujia-daofa", 1)+me->query_skill("lengquan-shengong",1)/2;

        me->add_temp("apply/damage",  skill/4);
        me->add_temp("apply/attack",  skill/4);
        me->set_temp("hjdf/ldj", 1);
		
		COMBAT_D->do_attack(me,target, weapon, random(3)?3:1);
		COMBAT_D->do_attack(me,target, weapon, random(3)?3:1);
		COMBAT_D->do_attack(me,target, weapon, random(3)?3:1);
		
		if (objectp(me)&& objectp(target))
		     call_out("check_fight",1, me, target,(int)skill/50);
        else remove_effect(me);
		return 1;
}

void check_fight(object me, object target,int amount)
{  
        object weapon;
		if (!me) return;
		weapon = me->query_temp("weapon");  

        if(!me->is_fighting()
		 ||!objectp(target)
         || !living(me)
         || me->is_ghost()
         || !weapon
		 || me->query_skill_mapped("blade")!="hujia-daofa"
		 || amount< 1) 
		{
            remove_effect(me);
			return;
		}
        else { 
				message_vision(HIW"��$N������������¡�"HIR"���ҵ�"HIW"��������۵糸������"+weapon->name()+HIW"�����γ�һ�㵶����\n"NOR, me);
				
				me->add_temp("apply/damage",(int)me->query_skill("hujia-daofa",1)/10);
				
				me->set_temp("hjdf/ldja",1);
				switch (random(6))
				{
					case 0:
					case 1:
					case 2:
						COMBAT_D->do_attack(me,target, weapon, 3);
						break;
					case 4:
					case 3:
					
						COMBAT_D->do_attack(me,target, weapon, 3);
						COMBAT_D->do_attack(me,target, weapon, random(3)?3:1);
						break;
					case 5:
						COMBAT_D->do_attack(me,target, weapon, 3);
						COMBAT_D->do_attack(me,target, weapon, random(3)?3:1);
						COMBAT_D->do_attack(me,target, weapon, 3);
						break;
				}
				me->delete_temp("hjdf/ldja");
				me->add_temp("apply/damage",-(int)me->query_skill("hujia-daofa",1)/10);
			if (objectp(me)&&objectp(target))
				call_out("check_fight", 2, me, target,amount--);
			else {
				remove_effect(me);
				return;
			}
		}
}
int remove_effect(object me)
{         
        int skill;
		if (!me) return 0;
	
        skill = (int)me->query_skill("hujia-daofa", 1);
 
        me->add_temp("apply/damage",  -skill/4);
        me->add_temp("apply/attack",  -skill/4);
        me->delete_temp("hjdf/ldj");
        if(living(me) && !me->is_ghost())
           message_vision(HIY"$Nһ�ס����ҵ�����ʹ�꣬����һ���������ָֻ���������\n"NOR, me);
        return 1;
}

int help(object me)
{
   write(WHT"\n���ҵ�����"HIR"���ҵ���"WHT"����"NOR"\n");
   write(@HELP
	�ˡ����ҵ�������Ϊ���ҵ���֮�߼����ԣ�������ز�¶��ֻ��
	���ִ���ʱ�����ڶ����Գ��ش�����Ӷ��˵���ʤ��ʹ�ø���
	ʱ��Ҳ���ʱ�������ʹ���ߵ��˺����������ʣ������ǳ���
	��ʹ���߻����־�ѧ��Ȫ��֮����Ȫ�����������ศ��ɣ�
	�������ˣ�

	ָ�perform blade.luandao

Ҫ��  
	��ǰ���� 800 ���ϣ�
	��ǰ���� 800 ���ϣ�
	������� 2500 ���ϣ�
	���ҵ��� 200 ���ϣ�
	�������� 200 ���ϣ�

HELP
   );
   return 1;
}
