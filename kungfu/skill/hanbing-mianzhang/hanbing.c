// HANBING.c �����ྡྷ
// By sohu@xojh
#include <ansi.h>

inherit F_SSERVER;
void remove_effect(object me, int count);

int perform(object me,object target)
{
	string msg;
	int skill, i, ap, dp;
	skill = me->query_skill("hanbing-mianzhang",1);
	

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !me->is_fighting(target))
		return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á������ྡྷ����\n");

	if( me->query_temp("weapon"))
		return notify_fail("������������ô��ʹ�á������ྡྷ����\n");

	if( skill < 350 )
		return notify_fail("��ġ��������ơ��ȼ�����, ������ʹ�á������ྡྷ����\n");

	if( me->query_skill_mapped("strike") != "hanbing-mianzhang")
		return notify_fail("��û�м����������ƣ������޷�ʹ�á������ྡྷ����\n");

	if (me->query_skill_prepared("strike") != "hanbing-mianzhang")
		return notify_fail("������׼���ú������ƣ��޷�ʹ�á������ྡྷ����\n");

	if ( me->query_skill_mapped("parry") != "qiankun-danuoyi"
	 && me->query_skill_mapped("parry") != "hanbing-mianzhang")
		return notify_fail("�������޷�ʹ�á������ྡྷ����\n");

	if( me->query_skill("dodge", 1) < 350 )
		return notify_fail("����Ṧ�������޷��������á������ྡྷ����\n");

	if( !me->query_skill("jiuyang-shengong", 1))
	if( me->query_skill("shenghuo-shengong", 1) < 350)
		return notify_fail("���ʥ���񹦵ȼ��������޷�ʹ�á������ྡྷ����\n");

	if((int)me->query("neili") < 3000)
		return notify_fail("�����������ʹ�á������ྡྷ����\n");
    if(target->query_condition("hb_poison") )
		return notify_fail("�Է��Ѿ����к������ƶ�������ʹ�ú����ྡྷ��\n");
    if( me->query_temp("hbmz/hb") )
		return notify_fail("������ʩչ�������ྡྷ����\n");
	if((int)me->query("jingli") < 1200)
		return notify_fail("��ľ�������ʹ�á������ྡྷ����\n");

	msg = HIW"\n$N��ǿ�������������������ƹ�����������һ�㱡���ĺ��������ϵ�������Ȼ��ǿ�˲��١�\n"NOR;
    me->set_temp("hbmz/hb",skill);
	ap = me->query("combat_exp") /10000;
	dp = target->query("combat_exp") /10000;
    me->add_temp("apply/attack",skill/3);
    me->add_temp("apply/damage",skill/6);
	me->add_temp("apply/strike",skill/5);
	if( (random(ap + dp) > dp 
		|| random(me->query_dex(1))>target->query_dex(1)/2)&& living(target) ) {
		msg += HIY"$nΪ$N����ɢ���ĺ������ȣ��̲�ס���˸����������ζ�ʱΪ֮һ����\n"NOR;
		target->start_busy(1+random(2));
		if (!userp(target))
		   target->add_busy(2);
		if (!random(3))
		  target->apply_condition("hb_poison",1+random(3));
	} else msg += HIC"$n�����������ܿ���$N����Ǻ��У�\n"NOR;
	 
//	 call_out("remove_effect",0,me,(int)skill/20);
	 remove_effect(me,(int)skill/20);
	 if (skill<350) {
	     me->start_perform(2, "�����ྡྷ");
	     me->start_busy(random(2));	
	 }
	
	message_vision(msg, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
	return 1;
}


void remove_effect(object me,int count)
{
	int amount;
	object weapon;
	if (!me) return;
//	if (!me->is_fighting()) count=0;
	weapon=me->query_temp("weapon");

	amount = me->query_temp("hbmz/hb");
	
	if( count < 0
		|| weapon
		||!me->is_fighting() 
		|| me->query_skill_prepared("strike")!="hanbing-mianzhang" 
		|| me->query_skill_mapped("strike")!="hanbing-mianzhang" )
	{
			
        me->add_temp("apply/attack",-amount/3);
        me->add_temp("apply/damage",-amount/6);
        me->add_temp("apply/strike",-amount/5);
        me->delete_temp("hbmz/hb");
		tell_object(me, HIW"�����ϵĺ������ƾ�������ɢȥ,�����������˲��١�\n"NOR);
		return;
		
	} 
	call_out("remove_effect",1,me,count--);
}


string perform_name(){ return HIW"�����ྡྷ"NOR; }

int help(object me)
{
        write(HIC"\n��������֮"+HIW"�������ྡྷ��"NOR"\n\n");
        write(@HELP
	�����ྡྷ�����������������似����ʹ�������ۼ�����
	��֮�ϣ�ʹ�����ж���350�����ɡ�Ϊ����������Ҫ��
	���������似���ܡ�������ս����������й�
	
	ָ�perform strike.hanbing
	ע�⣺
		set �������� ���� ��ҪЧ�����öԷ��ж�
		set �������� ��Ѫ ��ҪЧ����������Է����;�
	
Ҫ��  
	��ǰ���� 3000 ���ϣ�
	��ǰ���� 1200 ���ϣ�
	�������Ƶȼ� 350 ���ϣ�
	ʥ���񹦵ȼ� 350 ���ϣ�
	�����Ṧ�ȼ� 350 ���ϣ�
	�����Ʒ�Ϊ�������ƣ�
	�����м�Ϊ�������ƻ�Ǭ����Ų�ơ�

HELP
        );
        return 1;
}
