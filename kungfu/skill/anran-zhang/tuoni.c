//tuoni.c �����ˮ 
//cre by sohu@xojh 
// ��һ�У����ƣ�Ȼ�������������У����ֲ�һ�С�

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int check_fight(object me,object target);

string *pictures=({
"�ľ�����","�������","��������","�ǻ��չ�","��������","��ʬ����", "ӹ������"
});
int perform(object me,object target)
{
        string picture;
        int i;       
        i = me->query_skill("anran-zhang", 1);

        picture = pictures[random(sizeof(pictures))];

        if( !target ) target = offensive_target(me);

        if( !target
         || !me->is_fighting(target) )
               return notify_fail("�������ˮ��ֻ����ս���жԶ���ʹ�á�\n");
        if (me->query("gender")=="����")
               return notify_fail("��������ȫ��ʹ��������Ȼ�����⡹������\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á������ˮ��������\n");   

        if( me->query_skill_prepared("strike") != "anran-zhang"
         || me->query_skill_mapped("strike") != "anran-zhang"
         || me->query_skill_mapped("parry") != "anran-zhang"
         )
               return notify_fail("����������ʹ�á������ˮ��������\n"); 

        if((int)me->query_skill("anran-zhang", 1) < 500 )
               return notify_fail("�����Ȼ�����ˮ�Ʒ���򲻹���ʹ�����������ˮ��������\n");

        if((int)me->query_skill("strike", 1) < 500 )
               return notify_fail("��Ļ�������������죬ʹ�����������ˮ��������\n");

        if((int)me->query_skill("force",1) < 500 )
               return notify_fail("����ڹ��ȼ�������ʹ�����������ˮ��������\n");

		if ((int)me->query("divorce")>0)
					return notify_fail("��������飬����ʹ�÷��ӳ���Ȼ�����������\n"); 
        if((int)me->query_str() < 80)
               return notify_fail("�������������ǿ����ʹ�����������ˮ��������\n");

        if((int)me->query_dex() < 30)
                return notify_fail("�����������Ѹ�ͣ�ʹ�����������ˮ��������\n");

      
        if((int)me->query("neili") < 200 )
                return notify_fail("�������������\n");

        if((int)me->query("jingli") < 100)
                return notify_fail("��ľ���������\n");
		if(me->query_temp("arz/daishui"))
                return notify_fail("����ʹ�á������ˮ��������\n");
		
		if (me->query("divorce"))
					return notify_fail("��������飬����ʹ�÷��ӳ������ˮ������\n"); 
		
		if( me->query("eff_qi") < (int)me->query("max_qi"))
              i=(int)me->query_skill("force",1)/2;
		  else i=(int)me->query_skill("force",1)/4;
			  
		//if ((int)me->query("divorce")>1)
		//	i=i/(int)me->query("divorce");
		
		if (me->query("gender")=="Ů��")
			i=i/3;
		
		me->set_temp("arz/daishui",1);
        message_vision(HIC"\n$N��������Ʈ����������ˮ������Ʈ�ݣ��������������ֱ�����ˮ֮��\n"+
                       HIY"Ȼ������ȴ����֮�������ƴ��ż�ǧ����ɳһ�㣬����������֮������һ��"HIR"�������ˮ����\n"NOR,me,target);
		//����,�ж� int
		
		if (random(me->query_skill("force",1)*me->query_int(1))>(target->query_skill("force",1)*me->query_int(1)/3))
		{
				
			message_vision(HIB"$nһ��С��Ϊ������ж�ʱ����һ�������Ǳ��֮�У���������ӿ��һ�˸߹�һ�ˡ�һ��"+HIR+picture+NOR,me,target);
			target->add_busy(3+random(2));
			target->apply_condition("no_exert",2);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
					
		}
		//����,�ж�str
		if (random(me->query_str(1))>(me->query_str(1)/3))
		{
				
			message_vision(RED"$N�����Ʒ���ʹ�ۡ���ʹ�ƣ�ȫ����������,������ת��������ӿ���ȣ�Яǧ�����������˳��һ��"+HIG+picture+RED"��\n"NOR,me,target);
			target->receive_damage("qi",1000+random(4000),me);
			target->receive_wound("qi",1000+random(1000),me);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);					
		}
		me->set_temp("arz/sanzhao",3);
		me->add_temp("apply/strike", i);
		me->add_temp("apply/attack", i);
		me->add_temp("apply/damage", i);
		message_vision(HIY"$N�˲��ܿ�,����$n�Ĺ������漴�������У�����󺣿��Ρ�\n"NOR,me,target);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("arz/sanzhao",-1);
       	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("arz/sanzhao",-1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("arz/sanzhao",-1);

		me->add_temp("apply/strike", -i);
		me->add_temp("apply/attack", -i);
		me->add_temp("apply/damage", -i);
        me->add("jingli", -random(300));
        me->add("neili", -random(600));

        me->start_perform(3,"�����ˮ");
        me->delete_temp("arz/sanzhao");
        me->delete_temp("arz/daishui");

        if (me->is_fighting())
        	call_out("check_fight", 0 , me, target);
        return 1;
}
int check_fight(object me,object target)
{
		if (!target||!me||!me->is_fighting()) return 1;
		
       message_vision(HIC"$N�������꣬��������һ��"HIR"����ʬ���⡹"HIC"���߳�һ�š���һ�ŷ���ʱ�л��㱣�����ԼԼ���������ޡ�\n"

						+"��һ�����ͻأ��$n����ܵù���,ȴ�������һ�죬����$n���ؿڡ�\n"NOR,me,target);
	   target->set_temp("must_be_hit",1);
	   me->add_temp("apply/damage",me->query_skill("anran-zhang",1)/5);
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	   me->add_temp("apply/damage",-me->query_skill("anran-zhang",1)/5);
	   target->delete_temp("mush_be_hit");
	   return 1;

}


string perform_name(){ return HIC"�����ˮ"NOR; }

int help(object me)
{
        write(HIB"\n��Ȼ�����ˮ��"+HIC"�������ˮ��"NOR"\n");
        write(@HELP

	����Ժ�С��Ů�ھ���ȶϳ���ǰ���֣�������ҹ˼��
	����С��Ů����������������������Ȥ�����ں���֮��
	���������������һʮ�����Ʒ������������Ʒ�����Ϊ
	��Ȼ��������ƣ�ȡ���ǽ��͡��𸳡����Ǿ���Ȼ���
	�����ߣ�Ψ�������֮�⡣���Ʒ�������������������
	�壬��һ������ۺ�������Խ������Խ��ʵ������
	�ض��ú���!
	�����ˮ��˫�Ƴ�����̬֮�����������켺����������
	ʵ�����Ʊ�����ˮ֮������䶯������Ȼ�Ƶľ�����
	Ů�������������Ե����ɡ������Һ�����������һ��
	��״̬�������������������޷�ʹ�á���
	
	perform strike.tuoni

Ҫ��
	�����Ʒ�Ҫ�� 500 ������
	��Ȼ�Ʒ�Ҫ�� 500 ������
	�����ڹ�Ҫ�� 500 ������
	��ǰ����Ҫ�� 2000 ����
	��ǰ����Ҫ�� 1000 ����
	��ǰ����Ҫ�� 80  ����
	��ǰ��Ҫ�� 30  ����
	�����Ҽ����Ʒ����м�Ϊ��Ȼ��
HELP
        );
        return 1;
}
