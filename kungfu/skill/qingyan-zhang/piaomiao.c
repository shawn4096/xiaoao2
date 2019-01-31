// snowyu piaomiao 
// ע��˴����������ٷ������У����˸о��˹����ܸ���������������֣���
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

void remove_effect(object me, int dam,int attack);
void checking(object me,int dam,int attack);
void checking2(object me,int dam,int attack,int old_dam,int old_att);

int perform(object me, object target)
{
        object weapon = me->query_temp("weapon");
        int lv, attack, dam,old_att,old_dam;

        old_att = (int)me->query_temp("apply/attack",1);
        old_dam = (int)me->query_temp("apply/damage",1);
        lv = (int)me->query_skill("qingyan-zhang", 1); 
        attack = lv/6;
		dam = lv/6;
		if (userp(target))
        {
			attack =attack/2;
			dam=dam/2;
		}

        if( !target ) target = offensive_target(me);
        else me->set_temp("offensive_target", target);

        if (me->query("family/family_name")!="������" && !wizardp(me))
                return notify_fail(HIW "��Ǵ�������޷�ʩչ������Ʈ�졹��\n" NOR);
    
        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail(HIW "����Ʈ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_temp("piaomiao") )
                return notify_fail(HIW "������ʹ������Ʈ�죡\n");

        if( me->query_skill("force",1) < 400 )
                return notify_fail(HIW "����ڹ����δ����\n");

        if( me->query_skill("qingyan-zhang", 1) < 400 )
                return notify_fail(HIW "��Ļ���������������δ���죬�޷�ʩչ����Ʈ�죡\n");

        if( me->query_skill("strike", 1) < 400 )
                return notify_fail(HIW "��Ļ����Ʒ���δ���죬�޷�ʩչ����Ʈ�죡\n");

        if( me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail(HIW "�����õ��ڹ��ķ�����Ǭ��һ�����޷��ۼ�������\n");
        
        if (me->query("max_neili") <= 1500)
                return notify_fail(HIW "���������Ϊ���㣬�޷���������Ʈ�죡\n" NOR);
        
        if ((int)me->query("neili", 1) < 1000)
                return notify_fail(HIW "��������������ھ�������ʩչ����Ʈ�죡\n" NOR);

        if (me->query("jingli") <= 1000)
                return notify_fail(HIW "��û���㹻������ʩչ����Ʈ�죡\n" NOR);

        if(me->is_busy()) return notify_fail(HIW "����æ����,û�취ʩչ����Ʈ�죡\n" NOR);

        message_vision(HIC"$N����Ǭ��һ���ڹ��ķ��������������������ƣ���ʱ$N���Ʒ��ף����з���һ������"HIW"����"HIC"�ֳ����Ϯ��$n��\n" NOR, me,target);

        me->add("neili", -250);
        me->add("jingli", -100);

        me->set_temp("piaomiao", 1);
        me->add_temp("apply/attack", attack);
        me->add_temp("apply/damage", dam);
        message_vision(CYN"�⼸��"HIW"����"CYN"��$N���۵ľ�������֮�£�ٿȻϮ��$n��\n" NOR, me,target);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->set_temp("piaomiao", 2);
        //me->start_call_out( (: call_other, __FILE__, "checking2", me,dam,attack,old_dam,old_att :), 12);
    //    me->start_call_out( (: call_other, __FILE__, "checking", me,dam,attack :), 1);
		//me->start_perform(1,"Ʈ������");
       // call_out("checking",0,me,dam,attack);
		checking(me,dam,attack);
		return 1;
}

void checking(object me, int dam, int attack)
{
        int pm, limit;
        object weapon, target;

        weapon = me->query_temp("weapon");
        target = me->query_temp("offensive_target");

        pm = me->query_temp("piaomiao");
        limit = 1 + (int)me->query_skill("qingyan-zhang", 1)/100;
        
        if( !target || !me->is_fighting(target) ) target = offensive_target(me);

        if( pm > limit 
			|| pm > 6 
			|| weapon
			|| me->query_skill_prepared("strike")!="qingyan-zhang"
			|| me->query_skill_mapped("strike")!="qingyan-zhang") {
                message_vision(BLU "\n$N����һ�������������ƾ����ջص��\n"NOR, me);
                remove_effect(me, dam, attack);
                me->start_busy(1);
                return;
        }

        if( !living(me) || me->is_ghost()  )
        {
                remove_effect(me, dam, attack);
                return;
        }
        if( !me->is_fighting() )
        {
                message_vision(HIM "\n$N�������һԾ�������˾�����ھ���\n"NOR, me);
                remove_effect(me, dam, attack);
                tell_object(me, MAG "\n�㽫��Ϣ������ԭ����״̬��\n\n"NOR);
                return;
        }
		me->add_temp("apply/damage",dam/2);
		message_vision(HIC"$N��Ǭ��һ�������ϻ��Ȼ����������һ���Ƴ�������$n��ǰ�ء�\n"NOR,me,target);
		if (objectp(me)&&objectp(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
        me->add_temp("apply/damage",-dam/2);
        me->start_call_out( (: call_other, __FILE__, "checking", me,dam,attack :), 1);
        return;
}

void remove_effect(object me, int dam, int attack) 
{
        if (!me) return;
        me->add_temp("apply/attack", -attack);
        me->add_temp("apply/damage", -dam);
        me->delete_temp("piaomiao");
        me->start_busy(1);
		return;
}
string perform_name() {return WHT"�������"NOR;}

int help(object me)
{
        write(BLU"\n����������֮��������翡���"NOR"\n\n");
        write(@HELP
	�������������Ǵ�����Ͼ���������������������������
	�������𽭺������Ҵ����Լ������ˡ���״�����̣�����
	�����Ƶ���ʵ���ۻ�������������Ʒ��з��������˷�
	��ʤ����Ϊ��Ҫ�ĸ����������ܡ�
	
	ָ�perform strike.piaomiao

Ҫ��
	��ǰ���� 1000  ���ϣ�
	������� 15000 ���ϣ�
	��ǰ���� 1000  ���ϣ�
	�����Ʒ� 400   ����
	�������� 400   ����
	Ǭ��һ�� 400   ����
	�����Ʒ�Ϊ���������ƣ�
	�����м�Ϊ���������ƣ�
	���Ʒ�Ϊ���������ƣ�
	�ҿ��֡�


HELP
        );
        return 1;
}
