//  huima.c ����ǹ 
//Created by Redhat@Sjmud 2009/4/7

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return HBRED"����ǹ"NOR;}

int perform(object me,object target)
{
    object weapon;
    int i;
    i = me->query_skill("yangjia-qiang", 1);
    if( !target ) target = offensive_target(me);
     
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("������ǹ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if((int)me->query_skill("force", 1) < 350 )
                return notify_fail("��Ļ����ڹ�������죬�޷�֧�֡�����ǹ����\n");

    if( (int)me->query_skill("yangjia-qiang", 1) < 350 ) 
                return notify_fail("���ǹ����δ���ɣ�����ʹ�á�����ǹ����\n");

    if((int)me->query_skill("spear", 1) < 350 )
                return notify_fail("��Ļ���ǹ��������죬�����ڽ�����ʹ�á�����ǹ����\n");

    if((int)me->query_skill("dodge", 1) < 350 )
                return notify_fail("��Ļ����Ṧ������죬����ʹ�á�����ǹ����\n");

    if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "spear"
        || me->query_skill_mapped("spear") != "yangjia-qiang")
        //|| me->query_skill_mapped("parry") != "yangjia-qiang"
                return notify_fail("��������ǹ�����ʹ�á�����ǹ����\n");
                
    if((int)me->query("max_neili") < 8000 )
                return notify_fail("���������Ϊ����������ʹ�á�����ǹ����\n");

    if((int)me->query("neili") < 3000 )
                return notify_fail("�������������㣬����ʹ�á�����ǹ����\n");

    if((int)me->query("jingli") < 1000 )
                return notify_fail("������̫���ˣ�����ʹ�á�����ǹ����\n");
    if((int)me->query("yjq/huima")  )
                return notify_fail("������ʹ�á�����ǹ����\n");
      
    message_vision(HIB"\n$N��Ȼ����Ծ�𣬽����е�"+weapon->query("name")+HIB"���������ת���ﳤ��ȥ��"NOR, me,target);
	message_vision(HIG"\n$N΢΢Ťͷһ������$n�ں���������棬���ɵ���Цһ��������ʩչ�����ǹ֮"YEL"������ǹ��"HIG"����!\n"NOR, me,target);
        
    me->add("neili", -800);
    me->add("jingli",-500);
    me->set_temp("yjq/huima",1);

  
    if (random(me->query("combat_exp"))>target->query("combat_exp")/2
		||random(me->query_str())>target->query_dex()/2)
    {  
	
	    message_vision(HIY"$nȴ��$N��Ȼ�������е�"+weapon->query("name")+HIY"����һ����������������ǹ����ֱ���Լ�Ҫ��,���ɴ�ʧɫ��"NOR,me,target);
		target->set_temp("must_be_hit",1);
		target->receive_damage("qi",random(3000),me);
		target->receive_wound("qi",random(500),me);
		target->add_busy(2+random(2));
        
        me->add_temp("apply/spear",i/5);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),2);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),4);
        target->delete_temp("must_be_hit");
		me->add_temp("apply/spear", -i/5);
    	
    }else
	{
		message_vision(HIC"$n����һ�������Ŷ�����У���ȴ����һ���亹��\n"NOR,me,target);
		target->apply_condition("no_exert",1);
		target->add_busy(1);
		me->add_busy(2);
		
	}
   
    me->delete_temp("yjq/huima");
    me->start_busy(1);
	me->start_perform(3,"������ǹ��");
    target->start_busy(1);
    return 1;
}

int help(object me)
{
   write(YEL"\n���ǹ��"HIG"����ǹ"YEL"����"NOR"\n");
   write(@HELP
   ָ�perform huima
	���ǹ���Ǵ��Ա��������ҽ���ǹ�����������ϻ���
	���¶���Ϊʵս�����л���ǹ�Ǳ�ɱ������ʽ������װ
	�ܱ����õ��˴�æ׷�Ϲ����У���Ȼһǹ�̳������Է�
	�������µ���ʽ��
	Ҫ��
		���ǹ�� 350 ����
		����ǹ�� 350 ����
		������� 8000 ���ϣ�
		��ǰ���� 3000 ���ϣ�
		��ǰ���� 1000 ���ϣ�
		����ǹ��Ϊ���ǹ��
HELP
   );
   return 1;
}