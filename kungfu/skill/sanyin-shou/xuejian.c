// xuejian.c ��ѩ�Ľ�
//sohu@xojh

#include <ansi.h>
inherit F_SSERVER;
string perform_name(){ return CYN"��ѩ�Ľ�"NOR; }

int perform(object me, object target)
{
	string msg, *limbs, limb;
	object weapon;
    int damage, num, lvl, p,skill,i;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character() 
	 || !me->is_fighting(target))
		return notify_fail("��ѩ�Ľ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (!me->query("quest/kl/sys/xuejian/pass"))
		return notify_fail("����Ȼ��˵������ѩ�Ľ�����һ�У�����ȴ�򲻶��������ء�\n");

	lvl = me->query_skill("sanyin-shou", 1);
    skill=lvl+me->query_skill("xuantian-wuji", 1)/5;
	if (lvl < 250)
		return notify_fail("��������ֲ�����죬�޷�ʹ�÷�ѩ�Ľ���\n");

	if (me->query_skill("throwing", 1) < 300)
		return notify_fail("��Ļ�������������죬�޷�ʹ�÷�ѩ�Ľ���\n");

    if ( me->query_skill_mapped("throwing") != "sanyin-shou")
		return notify_fail("�����ڵ�������޷�ʹ�÷�ѩ�Ľ���\n");
	if ( me->query_skill("hand", 1) < 300 )
		return notify_fail("��Ļ����ַ��ȼ��������޷�ʹ�÷�ѩ�Ľ���\n");
	if ( me->query_skill("sanyin-shou", 1) < 300 )
		return notify_fail("��������ֵȼ��������޷�ʹ�÷�ѩ�Ľ���\n");

	if ( me->query_skill("force", 1) < 300 )
		return notify_fail("��Ļ����ڹ��ȼ��������޷�ʹ�÷�ѩ�Ľ���\n");

	weapon = me->query_temp("weapon");

	if (!weapon
		||weapon->query("skill_type")!="throwing")
		return notify_fail("��ѩ�Ľ�����װ����������ʹ�á�\n");

	if ((num = weapon->query_amount()) <= 2)
		return notify_fail("�������ͱ��ң���������İ����Ѿ�����ʹ�÷�ѩ�Ľ���Ҫ���ˣ�\n");

	if (me->query("neili") < 1000)
		return notify_fail("��������������޷�ʹ�÷�ѩ�Ľ���\n");

	if (me->query("jingli") < 1000)
		return notify_fail("��ľ����������޷�ʹ�÷�ѩ�Ľ���\n");
	i=lvl/100;

	message_vision(HIW"\n$N��Ƥ����ץ��" + CHINESE_D->chinese_number(i) + weapon->query("base_unit") + weapon->query("name") + HIW"������������ȥ�����ѩ�Ľ���\n"NOR,me,target);
    
	weapon->add_amount(-i);
    
	damage = (int)me->query_skill("sanyin-shou",1) + (int)me->query_skill("force",1) + (int)me->query_skill("throwing",1) ;
    
	if (random(me->query_dex()) > (int)target->query_dex() / 2
		||random(me->query_skill("throwing",1))>target->query_skill("parry",1)/2)
	{
		limbs = target->query("limbs");
		limb = limbs[random(sizeof(limbs))];
		//���������ְ������˺�����
		if (objectp(target) && target->query_temp("sys/sanyin"))
		{
			message_vision(HBYEL"$N��$n���������ְ��������е�"NOR+weapon->query("name")+HBYEL"�Է�ѩ�Ľ�֮�Ʒ���������������\n"NOR,me,target);
			damage=2*damage;
		}
		message_vision(HIR"$n���������������ۡ��ؼ�������"+chinese_number(i)+HIR"���������У�\n"NOR,me,target);
		damage=damage*2+random(damage);
		
		if (!userp(target)) damage=damage*2;
		if (damage>6000) damage=damage+(damage-6000)/100;
		
		target->receive_damage("qi", damage, me);
        target->receive_wound("qi", damage/3, me);
		me->add("neili", -400);
		me->add("jingli", -100);
		
		p = (int)target->query("eff_qi") * 100 / (int)target->query("max_qi");
		msg = COMBAT_D->damage_msg(damage, "����");
		msg = replace_string( msg, "$l", limb);
		msg = replace_string( msg, "$w", weapon->name());
		msg += "( $n" + COMBAT_D->eff_status_msg(p) + " )\n";
        message_vision(msg, me, target);

		if(userp(me) && me->query("env/damage"))
			tell_object(me,WHT"���"+ target->query("name") +"�����"RED+damage+ WHT"�㹥���˺���\n"NOR);
		
if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+damage+ WHT"���˺���\n"NOR); 
		

	}
	else {
			me->add("neili", -150);
			me->add("jingli", -50);
			message_vision(HIY"$n�ŵø�æ��ͷ��������Ǳ������Ա�һ�������ſ����ض��˹�ȥ��\n" NOR,me,target);					
			//target->add_busy(2+random(2));

	}

	me->add_temp("apply/attack",skill/3);
	me->add_temp("apply/damage",skill/4);
	me->add_temp("apply/throwing",skill/4);
	me->set_temp("sys/xuejian",1);
    if (objectp(target)&&me->is_fighting(target)&&me->query_skill("sanyin-shou",1)>200)
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
    if (objectp(target)&&me->is_fighting(target)&&me->query_skill("sanyin-shou",1)>250)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("sanyin-shou",1)>300)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("sanyin-shou",1)>350)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("sanyin-shou",1)>450)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->delete_temp("sys/xuejian");

	me->add_temp("apply/attack",-skill/3);
	me->add_temp("apply/damage",-skill/4);
	me->add_temp("apply/throwing",-skill/4);
	me->start_perform(4, "����ѩ�Ľ���");
	me->start_busy(1+random(2));
	if (num <= (int)lvl / 50)
	{
		weapon->unequip();
		tell_object(me, "\n���" + weapon->query("name") + "�������ˣ�\n");
	}
	me->add("neili", -350);
	me->add("jingli", -200);
	return 1;
}

int help(object me)
{
        write(HIC"\n������֮����ѩ�Ľ�����"NOR"\n");
        write(@HELP
	���������ʿ�ڹ�������ѩɽ�ɽ������������ַ�
	һ��ͬʱ�������İ������ö��ַ���ʤ�������޿�
	�ܡ�ͬʱ�����ʹ�ð����������࣬��������ʹ�ñ�
	��ע�⣬����ս�з��ְ��������ˡ�����ʽ��ʹ�ù�
	�����漼������������ǿ��������Լ����ԡ�
	ע�⣬���������ֵ�����������ϣ���������������
	���г�����̡�

	perform hand.xuejian
	
Ҫ��  
	�����ڹ��ȼ� 300 ���ϣ�
	���������ȼ� 300 ����
	�����ַ��ȼ� 300 ����
	�����ַ��ȼ� 300 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 1000 ����
	�����ַ������֣�
	�������������֣�
	���ַ�Ϊ������
	��������ְ���ʹ�ù����˺����ӣ�
	����׼��������
HELP
        );
        return 1;
}
