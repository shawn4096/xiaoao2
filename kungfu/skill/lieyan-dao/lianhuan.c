//lianhuan
//����������Դ�Է�����ʽ
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
        object weapon;
		weapon= me->query_temp("weapon");  
		i=me->query_skill("lieyan-dao",1);
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query("neili") <= 400 )
                return notify_fail("�����������ʹ������������\n");
        if( me->query("max_neili") <= 1400 )
                return notify_fail("�����������ʹ������������\n");

        if( me->query("jingli") <= 300 )
                return notify_fail("��ľ�������ʹ������������\n");
        if( me->query_skill("lieyan-dao",1) <= 250 )
                return notify_fail("�����浶����250������ʹ������������\n");
        if( me->query_skill("shenghuo-shengong",1) <= 250 )
                return notify_fail("���,ʥ���񹦲���250������ʹ������������\n");

        if (!weapon||weapon->query("skill_type")!="blade")
                return notify_fail("�������޵�����ʹ��������������\n");
		
        if (me->query_skill_mapped("blade") != "lieyan-dao"
				&& userp(me))
             	return notify_fail("������ȼ������浶��\n");
		if (me->query_skill_mapped("parry") != "lieyan-dao"
			  && me->query_skill_mapped("parry") != "qiankun-danuoyi"
			  && userp(me))
             	return notify_fail("����Ҫ�������浶��Ǭ����Ų�ơ�\n");

	message_vision( RED"$N���·������ڿն��𣬵�ͷֱ�������޻���,������ɽ��$n���в���ΪȻ���ƺ�Ҫ���Ա����ܡ�\n"+
		"��$N�ĵ����ٽ�$nͷ��֮�ʣ���Ȼ��Ȼ���У�����������$n��˫�֡�\n"NOR,me,target);
	
	me->start_perform(5,"������������");
	if(random(me->query_skill("lieyan-dao",1))  >target->query_skill("dodge",1)/3
		||random(me->query_str())>target->query_str()/2)
	{
		message_vision(CYN "$n�������Σ�ֻ��һ�С�����ж�ס���Ӳ����$N���С�\n" NOR,me,target);
		target->add_busy(random(2) + 2);
		target->add_temp("apply/attack",i/4);
		target->add_temp("apply/damage",i/4);
		target->add_temp("apply/blade",i/4);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),2);
		target->add_temp("apply/attack",-i/4);
		target->add_temp("apply/damage",-i/4);
		target->add_temp("apply/blade",-i/4);
	}
	else {
		message_vision(HIW "����$n������$N����ͼ���ɿ�������ȥ��\n" NOR,me,target);
		me->start_busy(1);
	}
 // 	message_vision(msg, me, target);
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
	damage = me->query_skill("lieyan-dao",1)+me->query_skill("shenghuo-shengong",1);
	damage += me->query_skill("blade",1)+me->query_skill("qiankun-danuoyi",1);
	damage=damage*3;
	damage += random(damage);
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		return ;
	}

	message_vision(CYN"\n$N�ڶ����������ϣ��з����һ��һģһ��,ֻ�ǵ��ƾ�Ȼ���ǣ�\n"+
		"$n���鼫��ḻ�������޷��ƽ�$N�Ɀ׾���ص�һ�У�����ͬ��Ӳ��֮�⣬�����Ʋߡ�\n"NOR,me,target);

	if(random(me->query("max_neili"))> target->query("max_neili")/2
		||random(me->query_skill("force",1)) >target->query_skill("force",1)/3
	    ||target->is_busy())
	{
		msg = HIR"$N��$n������ƴ��$n˫�����������ֻҪ�ٸ�$N��㿳�ϼ�����$n�ֱ��ϵĽ���ҲҪ�����ˡ�\n"NOR;
		if (!target->is_busy()) target->start_busy(damage/500);
		target->add("neili",-(500+random(150)));
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		msg += damage_msg(damage, "����");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "�ֱ�");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		if (me->query("env/damage"))
		{
			tell_object(me,"�������"+damage+"���˺���\n");
		}
		me->add("neili",-300);
		me->add("jingli",-100);
	} else {
		message_vision( CYN"$n�������Ӳ������������һ�С�\n"NOR,me,target);
		me->start_busy(1+random(2));
		
	}		
	//message_vision(msg, me, target);
	me->start_perform(4,"������������");

	if (objectp(target)&&me->is_fighting())
		next2(me, target);

}


void next2(object me, object target)
{
	string msg;
	int damage;
	object weapon;

	if( !me ) return ;

	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		return ;
	}

	message_vision(YEL "\n$n����δ����$N������˳�Ƶݳ�����������ǿ�������������������ڣ�����էй�������������\n"NOR,me,target);

	if(random(me->query("combat_exp")>target->query("combat_exp")/3 
		||random(me->query_str()) >target->query_str())/3)
   {
		msg=HIW "$n��ʱ�Ѹ�$N�������ƣ��ۼ�������Ϯ��æ����ƽ��һ�����������$n���ģ�\n"NOR;
		damage = me->query_skill("lieyan-dao",1)+me->query_skill("shenghuo-shengong",1);
		damage += me->query_skill("blade",1)+me->query_skill("qiankun-danuoyi",1);
		damage=damage*4;
		damage += random(damage);
	    if (objectp(target)&&!target->query("lyd/lianhuan")) 
		{
			target->add_temp("apply/attack", 100);
			target->add_temp("apply/dodge", 100);
			target->add_temp("apply/parry", 100);
			target->set_temp("lyd/lianhuan",1);
		}
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		msg += damage_msg(damage, "����");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "����");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		if (me->query("env/damage"))
		{
			tell_object(me,"�������"+damage+"���˺���\n");
		}

		me->add("neili",-300);
		me->add("jingli",-150);
		if (objectp(target))
			call_out("back", 5 + random(me->query("jiali") / 20), target);
	} else {
		message_vision(HIW "$n������������д󾪡�\n" NOR,me,target);
		me->start_busy(1 + random(2));
		
	}
	me->start_perform(4,"������������");

}

void back(object target)
{
	if (!target||!target->query_temp("lyd/lianhuan")) return;
	target->add_temp("apply/attack", 100);
	target->add_temp("apply/dodge", 100);
	target->add_temp("apply/parry", 100);
	return;
}
string perform_name(){ return HIM"��������"NOR; }

int help(object me)
{
        write(HIC"\n���浶��"+HIR"��ʥ�����桹"NOR"\n");
        write(@HELP
	���浶�����������ż����书��Դ����ң�����з����Ĵ���
	����ʹ�书��Ϊ���ӣ��������ݶ���������ڲ�����Ϊ����
	�ݺ����̵Ķ�ͷ�����ư�ͷ�ӵ�����ʾ�����⣬ʵ�����̵�
	�󹦳���
	����������Դ�Է��������޼�������ʱ��ʩչ�书��Ҫ����
	һ�����֣�ȫ���Ը�����Է�����������������

	ָ�perform blade.lianhuan

Ҫ��
	�������Ҫ�� 1400 ���ϣ�
	��ǰ����Ҫ�� 400 ���ϣ�
	��ǰ����Ҫ�� 300 ���ϣ�
	���浶���ȼ� 250 ���ϣ�
	ʥ���񹦵ȼ� 250 ���ϣ�
	��������Ϊ���浶����
	�����м�Ϊ���浶��Ǭ����Ų��
	�ֳֵ���������

HELP
        );
        return 1;
}