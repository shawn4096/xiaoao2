// lianhuan.c  ����������
// Create by lsxk@hsbbs 2007/5/15

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

string perform_name(){ return CYN"����������"NOR; }

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lev;
        lev = ((int)me->query_skill("tiezhang-zhangfa", 1) + (int)me->query_skill("force", 1))/3;
        //if(!userp(me)) lev = lev / 2;

		if( !target ) target = offensive_target(me);

        if( !target 
          || !me->is_fighting(target)
          || !objectp(target)

		  || environment(target)!= environment(me))
                return notify_fail("�����������ơ�����ֻ����ս����ʹ�á�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á����������ơ�����?\n");   
        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 400 )
                return notify_fail("��������Ʒ���������죬ʹ���������������ơ�������\n");

        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
        || me->query_skill_mapped("parry") != "tiezhang-zhangfa"
        || me->query_skill_mapped("strike") != "tiezhang-zhangfa")
                return notify_fail("�������޷�ʹ�á����������ơ��������й�����\n");  

        if( (int)me->query_skill("force", 1) < 400)
                return notify_fail("��Ļ����ڹ��ȼ���������ʹ���������������ơ�������\n");

        if( me->query("max_neili") < 3500)
                return notify_fail("������������Ϊ̫�ʹ���������������ơ���\n"); 

        if( (int)me->query("neili") <1500 )
                return notify_fail("����������̫����ʹ���������������ơ���\n"); 

        if( (int)me->query("max_jingli") < 2000)
                return notify_fail("�����ھ�����Ϊ̫�ʹ���������������ơ���\n"); 

        if( (int)me->query("jingli") < 600 )
                return notify_fail("�����ھ���̫�ʹ���������������ơ���\n"); 

        message_vision(HIM"\n$NͻȻ���һ����������磬˫�������ĳ������������Ʒ�֮���衸���������ơ�������\n"NOR,me);

        me->add_temp("apply/strike", lev);

		me->add_temp("apply/attack", lev);
        me->add_temp("apply/strength",(int)me->query("str"));
        me->add_temp("apply/damage", lev);
        me->set_temp("tiezhang", 1);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (lev>449)?3:1);
        //if(me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (lev>449)?3:1);
        //if(me->is_fighting(target)) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        //if(me->is_fighting(target)) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 4);
        me->add_temp("apply/strike", -lev);
 
		me->add_temp("apply/attack", -lev);
        me->add_temp("apply/strength",-(int)me->query("str"));
        me->add_temp("apply/damage", -lev);

        me->start_busy(1+random(2));
        me->start_perform(4,"�����������ơ�");
        me->add("neili", -500);
        me->delete_temp("tiezhang");
        return 1;
}
int help(object me)
{
        write(HIR"\n�����Ʒ�֮��������������"NOR"\n\n");
        write(@HELP 
	���������������������Ʒ��Ĳ���֮�գ��Ǳ��ź��ĵ��Ӳ��Ĵ��ڡ�
	���Ʒ��þ����ϴ������Ϲٽ��ϵ��ڿ�����������в��Ͼ���ϸ��
	���ɣ����������ص����ں��˸�ͷ������ն��������Ҷ������
	�ƾ������������Ʒ��бȽ������һ����̬����������Ȼ���Ʒ���
	�����õ���ʽȴ�����Ʒ��ķ�ʽģ����������Ϲٰ�������������
	Ϊ�˼����һ����ս�ļ�λ���������϶��ں���һ�𡣸��Ʒ�
	�ѽ���ɣ�����Ϊ������ʽ���ӣ���Ȼ���������Ʒ����ϳ���ѧ��
	ȴɥʧ�������Ʒ��ľ���ζ��������Ե�ɺϣ��⿪�ں�һ�����ں�
	������ô��������Ҳ�������ʡ�
        
	perform strike.lianhuan

Ҫ��
	��ǰ���� 1500 ���ϣ�
	������� 3500 ���ϣ�
	��ǰ���� 2000 ���ϣ�
	�����Ʒ��ȼ� 400 ���ϣ�
	�����ڹ��ȼ� 400 ���ϣ�
	�����Ʒ��ȼ� 400 ���ϣ�
	�����Ʒ�Ϊ�����Ʒ���
	�����м�Ϊ�����Ʒ���
	�����ڹ����ޡ�
HELP
        );
        return 1;
}