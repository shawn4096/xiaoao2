// huayu.c ���컨��

#include <ansi.h>
inherit F_SSERVER;
string perform_name(){ return HIG"���컨��"NOR; }

int perform(object me, object target)
{
	string msg, *limbs, limb;
	object weapon;
        int damage, num, lvl, p;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character() 
	 || !me->is_fighting(target))
		return notify_fail("���컨��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query("quest/hmy/mthy/huayu/pass")!="pass")
		return notify_fail("����Ȼ��˵�������컨�ꡱ��һ�У�����ȴδ���ڡ�\n");

	lvl = me->query_skill("mantian-huayu", 1);

	if (lvl < 250)
		return notify_fail("������컨�겻����죬�޷�ʹ�����컨�ꡣ\n");

	if (me->query_skill("throwing", 1) < 250)
		return notify_fail("��Ļ�������������죬�޷�ʹ�����컨�ꡣ\n");

    if ( me->query_skill_mapped("throwing") != "mantian-huayu")
		return notify_fail("�����ڵ�������޷�ʹ�����컨�ꡣ\n");

	if ( me->query_skill("tianmo-gong", 1) < 250 )
		if ( me->query_skill("xixing-dafa", 1) < 250 )
		return notify_fail("��������ڹ��ȼ��������޷�ʹ�����컨�ꡣ\n");

	weapon = me->query_temp("weapon");
    
	if (!weapon)
		return notify_fail("���컨�����װ����������ʹ�á�\n");

	//if ((num = weapon->query_amount()) < lvl / 20)
	if (weapon->query_amount()< 2)
		return notify_fail("�������ͱ��ң���������İ����Ѿ�����ʹ�����컨���Ҫ���ˣ�\n");
	
	if (weapon->query_amount() < lvl / 80) {
		weapon->unequip();
		tell_object(me, "\n���" + weapon->query("name") + "�����ˣ�\n");
		return notify_fail("������û�а������ã�\n");
	}

	if (me->query("neili") < 1000)
		return notify_fail("��������������޷�ʹ�����컨�ꡣ\n");

	if (me->query("jingli") < 900)
		return notify_fail("��ľ����������޷�ʹ�����컨�ꡣ\n");
	
	num=lvl/80;
	msg = HIY"\n$N��������ɳ�ȥ������һ����Ѫ�������������ץ��" + CHINESE_D->chinese_number(lvl / 80) + weapon->query("base_unit") + weapon->query("name") + HIY"���������ɢ��!\n"
	+"$n"HIY"������Ժ��룬����ħ�̺�Ѫ����Ĵ������޲����ģ����ܼ��ҳ�һ�ţ�$nֻ����ǰ�ƺ�����һ�������꣡\n"NOR;
	
		weapon->add_amount(-(lvl/80));

       damage = (int)me->query_skill("mantian-huayu",1) + (int)me->query_skill("force",1) + (int)me->query_skill("hand",1) ;
       if (random(me->query_dex()) > (int)target->query_dex() / 2
		   ||random(me->query("combat_exp"))>target->query("combat_exp")/2) {
		limbs = target->query("limbs");
		limb = limbs[random(sizeof(limbs))];
		msg += HIB"$n���������������ۡ��ؼ��������������밵�����У�\n"NOR;
		if (objectp(target)&&target->query_temp("hmy/shenzhen"))
		{
			message_vision(HBYEL"$N��$n�Ѿ��������룬���е�"NOR+weapon->query("name")+HBYEL"�����컨��֮�Ʒ���������������\n"NOR,me,target);
			damage=2*damage;
		}
		damage=damage*2+random(damage);
		if (!userp(target)) damage=damage*2;
		if (damage>5000) damage=damage+(damage-5000)/100;
		
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
		msg += HIW"$n�ŵø�æ��ͷ��������Ǳ������Ա�һ�������ſ����ض��˹�ȥ��\n" NOR;
		target->add_busy(1+random(2));
	}
	message_vision(msg, me, target);
	if (weapon->query("skill_type")=="throwing"&&!me->query_temp("anqi/damage"))
	{
		me->add_temp("apply/damage",lvl/4);
		message_vision(HIC"$N���е�"+weapon->query("name")+HIC"�����������£���ҫ��ɭɭ�ĺ��⣡\n"NOR,me);
		me->set_temp("anqi/damage",lvl);
	}
    me->add_temp("apply/throwing",lvl/2);
	me->add_temp("apply/damage",lvl/3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("mantian-huayu",1)>150)
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
    if (objectp(target)&&me->is_fighting(target)&&me->query_skill("mantian-huayu",1)>200)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("mantian-huayu",1)>250)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("mantian-huayu",1)>300)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if (objectp(target)&&me->is_fighting(target)&&me->query_skill("mantian-huayu",1)>350)
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->add_temp("apply/throwing",-lvl/2);
	me->add_temp("apply/damage",-lvl/3);
	if (me->query_temp("anqi/damage"))
	{
		me->add_temp("apply/damage",-lvl/4);
		me->delete_temp("anqi/damage");
		//message_vision(HIC"$N���е�"+weapon->query("name")+HIC"�����������£���ҫ��ɭɭ�ĺ��⣡\n"NOR,me);
	}
	me->start_perform(4, "�����컨�꡹");
	me->start_busy(1+random(2));
	
	
	return 1;
}

int help(object me)
{
        write(HIC"\n���컨��֮"HIG"�����컨�꡹��"NOR"\n");
        write(@HELP
	һ��ͬʱ�������İ������ö��ַ���ʤ�������޿ɱܡ�ͬʱ�����ʹ�ð�
	���������࣬��������ʹ�ñ���ע�⣬����ս�з��ְ��������ˡ�����ʽ��
	ʹ�ù������漼������������ǿ��250��Ծһ�Σ�300��350,450���Է�Ծ��

	ָ��;perform throwing.huayu

Ҫ��  
	��ħ�������Ǵ󷨵ȼ� 250 ���ϣ�
	���컨��ȼ� 250 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	��ϻ�ħ�貽ʹ�ù����˺����ӣ�
	����׼��������
HELP
        );
        return 1;
}
