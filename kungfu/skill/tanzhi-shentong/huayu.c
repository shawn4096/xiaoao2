// huayu.c ���컨��

#include <ansi.h>
inherit F_SSERVER;
string perform_name(){ return CYN"���컨��"NOR; }

int perform(object me, object target)
{
	string msg, *limbs, limb;
	object weapon;
        int damage, num, lvl, p,skill;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character() 
	 || !me->is_fighting(target))
		return notify_fail("���컨��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	//if (!(me->query("thd/perform") & 16))
	if (!me->query("thd/wuji/huayu"))
		return notify_fail("����Ȼ��˵�������컨�ꡱ��һ�У�����ȴδ���ڡ�\n");

	lvl = me->query_skill("tanzhi-shentong", 1);
    skill=lvl+me->query_skill("bihai-chaosheng", 1)/4;
	if (lvl < 250)
		return notify_fail("��ĵ�ָ��ͨ������죬�޷�ʹ�����컨�ꡣ\n");

	if (me->query_skill("throwing", 1) < 250)
		return notify_fail("��Ļ�������������죬�޷�ʹ�����컨�ꡣ\n");

   if ( me->query_skill_mapped("throwing") != "tanzhi-shentong")
		return notify_fail("�����ڵ�������޷�ʹ�����컨�ꡣ\n");

	if ( me->query_skill("bihai-chaosheng", 1) < 250 )
		return notify_fail("��ı̺��������ȼ��������޷�ʹ�����컨�ꡣ\n");

	weapon = me->query_temp("weapon");

	if (!weapon)
		return notify_fail("���컨�����װ����������ʹ�á�\n");

	//if ((num = weapon->query_amount()) < lvl / 20)
	if ((num = weapon->query_amount()) <= 2)
		return notify_fail("�������ͱ��ң���������İ����Ѿ�����ʹ�����컨���Ҫ���ˣ�\n");

	if (me->query("neili") < 1000)
		return notify_fail("��������������޷�ʹ�����컨�ꡣ\n");

	if (me->query("jingli") < 900)
		return notify_fail("��ľ����������޷�ʹ�����컨�ꡣ\n");

	msg = HIW"\n$N˫���ڱ�����һץ��ץ��" + CHINESE_D->chinese_number(lvl / 100) + weapon->query("base_unit") + weapon->query("name") + HIW"��������ָ������ص��˳�ȥ��$n"HIW"ֻ����ǰ�ƺ�����һ�������꣡\n"NOR;
    weapon->add_amount(-(int)lvl/100);
    damage = (int)me->query_skill("tanzhi-shentong",1) + (int)me->query_skill("force",1) + (int)me->query_skill("finger",1) + me->query_temp("thd/is_fast");
    if (random(me->query_dex()) > (int)target->query_dex() / 2
		||random(me->query("combat_exp"))>target->query("combat_exp")/2)
	{
		limbs = target->query("limbs");
		limb = limbs[random(sizeof(limbs))];
		msg += HIC"$n���������������ۡ��ؼ������������������У�\n"NOR;
		if (objectp(target)&&target->query_temp("thd/tan"))
		{
			message_vision(HBYEL"$N��$n�Ѿ������־�����Ѩ�������е�"NOR+weapon->query("name")+HBYEL"�����컨��֮�Ʒ���������������\n"NOR,me,target);
			damage=2*damage;
		}
		damage=damage*2+random(damage);
		if (!userp(target)) damage=damage*2;
		if (damage>6000) damage=damage+(damage-6000)/100;
		
		target->receive_damage("qi", damage, me);
        target->receive_wound("qi", damage/3, me);
		me->add("neili", -400);
		me->add("jingli", -100);
		p = (int)target->query("eff_qi") * 100 / (int)target->query("max_qi");
		msg += COMBAT_D->damage_msg(damage, "����");
		msg = replace_string( msg, "$l", limb);
		msg = replace_string( msg, "$w", weapon->name());
		msg += "( $n" + COMBAT_D->eff_status_msg(p) + " )\n";
        if(userp(me) && me->query("env/damage"))
			tell_object(me,WHT"���"+ target->query("name") +"�����"RED+damage+ WHT"�㹥���˺���\n"NOR);
		
if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+damage+ WHT"���˺���\n"NOR); ;
	}
	    else {
		me->add("neili", -150);
		me->add("jingli", -50);
		msg += HIY"$n�ŵø�æ��ͷ����������Ǳ������Ա�һ�������ſ����ض��˹�ȥ��\n" NOR;
		target->add_busy(1+random(2));
	}
	message_vision(msg, me, target);
	me->add_temp("apply/attack",skill/4);
	me->add_temp("apply/damage",skill/4);
	me->add_temp("apply/throwing",skill/4);
    if (objectp(target)&&me->is_fighting(target)&&me->query_skill("tanzhi-shentong",1)>280)
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
    if (objectp(target)&&me->is_fighting(target)&&me->query_skill("tanzhi-shentong",1)>300)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("tanzhi-shentong",1)>350)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("tanzhi-shentong",1)>400)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("tanzhi-shentong",1)>450)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/attack",-skill/4);
	me->add_temp("apply/damage",-skill/4);
	me->add_temp("apply/throwing",-skill/4);
	me->start_perform(4, "�����컨�꡹");
	me->start_busy(random(2));
	if (num <= (int)lvl / 50)
	{
		if (weapon) weapon->unequip();
		tell_object(me, "\n���" + weapon->query("name") + "�������ˣ�\n");
	}
	//weapon->add_amount(-(lvl/20));
	return 1;
}

int help(object me)
{
        write(HIC"\n��ָ��֮ͨ�����컨�꡹��"NOR"\n");
        write(@HELP
	һ��ͬʱ��������İ������ö��ַ���ʤ����
	���޿ɱܡ�ͬʱ�����ʹ�ð����������࣬��
	������ʹ�ñ���ע�⣬����ս�з��ְ�������
	�ˡ�����ʽ��ʹ�ù������漼������������ǿ
	��������Լ����ԡ�
	ע�⣬���͵�ָ��ͨ�ĵ��־���ϣ���������

	perform huayu
	
Ҫ��  
	�̺������ȼ� 250 ���ϣ�
	��ָ��ͨ�ȼ� 250 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	���������תʹ�ù����˺����ӣ�
	����׼��������
HELP
        );
        return 1;
}