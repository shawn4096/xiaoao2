//sanxian ��������
//by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>
void next1(object me, object target);
void next2(object me, object target);

int perform(object me,object target)
{
	int i;
	string msg;
    object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("�����������ʹ���������֣�\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ�������ʹ���������֣�\n");

        if (!weapon ||weapon->query("skill_type")!="blade")
                return notify_fail("�������޵�����ʹ���������֣���\n");
		if (me->query_skill("blade",1)<300)
                return notify_fail("��Ļ�����������300������ʹ���������֣���\n");
		if (me->query_skill("force",1)<300)
                return notify_fail("��Ļ����ڹ�����300������ʹ���������֣���\n");

		if (me->query_skill("hujia-daofa",1)<300)
                return notify_fail("��ĺ��ҵ�������300������ʹ���������֣���\n");
       // if (!me->query_temp("hujia-daofa/luanren",1)||!me->query_temp("hujia-daofa/nizhuan",1))
               // return notify_fail("�㲻ʹ�á�����(perform yinyang)����(perform nizhuan)�з�����ô�����������ַ�ס�����ж���\n");

        if ( me->query_skill_mapped("blade") != "hujia-daofa" )
             	return notify_fail("������ȼ�������Ϊ���ҵ�����\n");
      //  if (me->query_temp("hjdf/yunlong"))
				// return notify_fail("������ʩչ���ҵ����е��������֡�\n");
	
	message_vision( HIC"$N����"+weapon->query("name")+HIC"һ��һ�С������ġ��������������ѽ�$n������ס��\n"+
		"�漴$N��������ȴ����ס��$n��ǰ�����ң���$n�������ܶ���֮����\n"NOR,me,target);
	
	me->start_perform(5,"���������֡�");
	//me->set_temp("hjdf/yunlong",1);
	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
	   || random(me->query_int())>target->query_int()/2)
	{
		
		msg = HIR "\n\n$nֻ��һ�С��ᵣ�����š���Ӳ����$N���С�\n" NOR;
		target->add_busy(2);
	}
	else {
		msg = HIW "����$n������$N����ͼ���ɿ�������ȥ��\n" NOR;
		me->start_busy(1);
	}
	message_vision(msg, me, target);
	if (objectp(target)&&me->is_fighting())
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);

	if (objectp(target)&&me->is_fighting())
		next1(me, target);
	return 1;
}

void next1(object me, object target)
{
	string msg;
	int damage;
	object weapon;

	if (!me) return ;
		weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("hjdf/yunlong");
		return ;
	}

	msg = YEL"\n$N���´Ӷ��������������������š�������λ����б��ֱ�壬���ֺ��ҷ��С�\n"+
		"ֻҪ$nײ���ˣ�����Ҳ�����ˣ����㲻ײ�ϣ�ֻҪһ��һ������ʱ��ᱻ���뵶Ӱ�С�\n"NOR;

	if(random(me->query("combat_exp"))>target->query("combat_exp")/2
		||random(me->query_skill("hujia-daofa",1))> target->query_skill("dodge",1)/2 )
	{
		msg = msg + HIR"$n˫�����������ֻҪ�ٸ�$N��㿳�ϼ�����$n�ֱ��ϵĽ���ҲҪ�����ˡ�\n"NOR;
		damage = me->query_skill("hujia-daofa",1)+me->query_skill("force",1);
		damage += me->query_skill("blade",1);
		damage=damage*me->query_str()/20;
		damage += random(damage);
		
		target->add("neili",-(1000+random(500)));
		if (target->query("neili")<0) target->set("neili",10);
		
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		if (wizardp(me)) write("damage2="+damage);
	    
		msg += damage_msg(damage, "����");
		msg = replace_string(msg, "$w", weapon->query("name"));
		msg = replace_string(msg, "$l", "�ֱ�");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-300);
		me->add("jingli",-100);
	} else {
		msg  =  msg + CYN"$nƾ�����ɵ����㿪����һ�С�\n"NOR;
		message_vision(msg, me, target);
		me->start_busy(1+random(2));
		target->start_busy(1+random(2));
	}
	me->start_perform(5,"��������");

	if (objectp(target)&&me->is_fighting())
		next2(me, target);
	return;

}

void next2(object me, object target)
{
	string msg;
	int damage;
	object weapon;

	if( !me) return ;

	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("hjdf/yunlong");
		return ;
	}

	msg = WHT "\n$N����Ծ�𣬷�����ǰһ����ֱ���뻳�������䣬"+weapon->query("name")+WHT"�ѻ���$n����硣\n"NOR;

	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
		||random(me->query_str()) >target->query_dex()/3)
	{
		msg = msg + HIC "$n��"+weapon->query("name")+HIC"��һ����Ȼ��������ʲô����$nȴ��ɫ��䣡\n"NOR;
		damage = me->query_skill("hujia-daofa",1)+me->query_skill("force",1);
		damage += me->query_skill("blade",1);
		damage=damage*me->query_str()/20;
		damage += random(damage);
		
		//if (!target->is_busy()) target->start_busy(damage/500);
		target->add_temp("apply/attack", -200);
		target->add_temp("apply/dodge", -200);
		target->add_temp("apply/parry", -200);
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
				if (wizardp(me)) write("damage3="+damage);

		msg += damage_msg(damage, "����");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "�ֱ�");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-300);
		me->add("jingli",-150);
		if (objectp(target))
			call_out("back", 5+random(5), target);
	} else {
		msg = msg + HIW "$n�����Ṧ����ǰһԾ���㿪һ�ԡ�\n" NOR;
		message_vision(msg, me, target);
		me->start_busy(1 + random(2));
		target->start_busy(1+random(2));
	}
	me->delete_temp("hjdf/yunlong");
	me->start_perform(4,"��������");
	return;
}

void back(object target)
{
	if (!target) return;
	target->add_temp("apply/attack", 200);
	target->add_temp("apply/dodge", 200);
	target->add_temp("apply/parry", 200);
}
string perform_name(){ return HIC"��������"NOR; }

int help(object me)
{
   write(WHT"\n���ҵ���֮��"HIG"��������"WHT"����"NOR"\n");
   write(@HELP
	�ˡ��������֡��������ھ�������ϣ��Ժ��ҵ�����
	�������ʽ�����������������һ�����ֲ�����������
	��Ҫ�����ḻ��ս���������Ӧ�ı��������ԡ����Է�
	Ϊ�������У�������һ���̶ȵ�������æµ״̬��

	ָ�perform blade.yunlong

Ҫ��
	��ǰ���� 1000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	���ҵ��� 300 ���ϣ�
	�������� 300 ���ϣ�
	�����ڹ� 300 ���ϣ�
	��������Ϊ���ҵ�����
	���гֵ���

HELP
   );
   return 1;
}
