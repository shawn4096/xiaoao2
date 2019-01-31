//chaodu.c  �����Ƴ���������

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_temp("lianhuan") )
                return notify_fail("������ʹ�ó����������ˣ�\n");

        weapon = me->query_temp("weapon");
        if( objectp(weapon) )
                return notify_fail("���������żһ����ܹ�ʩչ��������\n");

        if( me->query_skill_mapped("force") != "yijin-jing" )
                return notify_fail("�����õĲ����׽�񹦣��޷�����Ʒ�ʩչ��������\n");

        if( me->query_skill("force",1) < 300 )
                return notify_fail("����׽�������δ�����޷����ʩչ��������\n");

        if( me->query_dex() < 60 )
                return notify_fail("�����Ч�����δ�����޷����ʩչ��������\n");
        if( me->query_skill("banruo-zhang",1) < 300 )
                return notify_fail("���������Ϊ���㣬������ʹ�ó��Ⱦ���\n");


        if( me->query_skill("strike",1) < 300 )
                return notify_fail("������Ʒ���Ϊ���㣬������ʹ����������\n");

        if( me->query("neili") <= 1500 )
                return notify_fail("�����������ʩչ��������\n");
		if( me->query("max_neili") <= 3500 )
                return notify_fail("�����������ʩչ��������\n");
        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ�������ʩչ��������\n");

        skill = me->query_skill("banruo-zhang",1);
        
        message_vision(HIR "\n$N���һ�����������,�Ʒ�������������������Ƿ��Ű����ƾ���֮��ħ���Ⱦ���\n\n" NOR, me, target);

        me->set_temp("lianhuan", 1);
		if (me->query_skill("banruo-zhang",1)<349)
		{ 
			me->add_busy(1+random(2));
		}
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), skill/5);
        me->add("neili", -300);
        me->add("jingli", -100);
        
        return 1;
}

void remove_effect(object me, int amount)
{
        me->delete_temp("lianhuan");

        if ( me->is_fighting() ) {
                message_vision(HIR "\n$N���׽��������ϣ��������ջص����������Ҳ������������\n" NOR, me);
        }
        else {
                tell_object(me, HIR "\n����׽��������ϣ������������ջص��\n\n" NOR);
        }
}
//��������������ʮ�������������Ʒ�������Խ��Խǿ��ѧ��ֹ����Ҳ����˵��������û���������޵ġ�
string perform_name(){ return HIY"����������"NOR; }
int help(object me)
{
        write(HIY"\n������֮����������������"NOR"\n");
        write(@HELP
		��������������ʮ�������������Ʒ�������Խ��Խǿ��ѧ��ֹ����Ҳ����˵��������û���������޵ġ�
		ͬ�����Ħ��ʹ�����־������������߳���ն�ͭ¯������Զ���黨ָ��ȼľ������Ӱ�����ȵ���������֮�ϣ�
		�ɼ�����������������ʽ���صĸ�����ѧ��ͬʱ�������ƻ��л����񹦣��������Ź��ؼ汸��ѧ�����ԳƵ���
		����ʮ��������ļ�Ʒ���������������Ѷ�Ҳ�Ƚϸߣ�һ���˶�Ҫ������ʮ�꣬����������һָ����ʷ������
		�ĳȹۣ�Ҳ����������ʮ�ꡣ
		
		��λ������Ϊ���࣬���Ժ�һЩ����ʵ��Ƕ�ף����ʹ�á�		

        Ҫ��  ������� 3500 ���ϣ�      
                ��ǰ���� 1500  ���ϣ�  
                �����Ƶȼ� 300 ���ϣ�
                �׽�ȼ� 300 ���ϣ�
                �����Ʒ�Ϊ�����ƣ�
                �����ޱ�����
				��Ч������С��60��
                ���Ժʹ������ȭ������350����С�ɡ�
                
HELP
        );
        return 1;
}