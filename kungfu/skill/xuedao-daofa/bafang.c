//bafang.c  ҹս�˷�ʽ
//by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>
void next1(object me, object target);
void next2(object me, object target);

int perform(object me,object target)
{
		int damage,skill;
		string msg;
		object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);
		
		skill=me->query_skill("xuedao-daofa",1);
        
		if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��ҹս�˷�ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("�����������ʹ�á�ҹս�˷�ʽ����\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ�������ʹ�á�ҹս�˷�ʽ����\n");

        if (!weapon ||weapon->query("skill_type")!="blade")
                return notify_fail("�������޵�����ʹ�á�ҹս�˷�ʽ������\n");
		if (me->query_skill("blade",1)<220)
                return notify_fail("��Ļ�����������220������ʹ�á�ҹս�˷�ʽ������\n");
		if (me->query_skill("force",1)<220)
                return notify_fail("��Ļ����ڹ�����220������ʹ�á�ҹս�˷�ʽ������\n");

		if (me->query_skill("xuedao-daofa",1)<220)
                return notify_fail("���Ѫ����������220������ʹ�á�ҹս�˷�ʽ������\n");

        if ( me->query_skill_mapped("blade") != "xuedao-daofa" )
             	return notify_fail("������ȼ�������ΪѪ��������\n");
		if ( me->query_skill_mapped("parry") != "xuedao-daofa" && me->query_skill_mapped("parry") != "jingang-liantishu")
             	return notify_fail("����мܲ��ԣ����뼤������ΪѪ������������������\n");
		if ( me->query_skill_mapped("force") != "xuedao-jing" )
			if ( me->query_skill_mapped("force") != "shenzhao-jing" )
             	return notify_fail("�㼤�����ڹ��͵���������\n");

        if (me->query_temp("xddf/bafang"))
				return notify_fail("������ʩչѪ�������еġ�ҹս�˷�ʽ����\n");
		message_vision( HIY"$N����"NOR+weapon->query("name")+HIY"����ʮ������������˷��������ˣ�����Ѫ�����еġ�ҹս�˷�ʽ��\n"+
		"ͬʱ����һ�㣬��$n������ȥ���漴$N�ӵ����䣬����˷�������ס����$n�������ܶ���֮����\n"NOR,me,target);

		me->start_perform(4,"��ҹս�˷�ʽ��");
		me->set_temp("xddf/bafang",1);
		damage=skill+me->query_skill("jingang-liantishu",1)+me->query_skill("xuedao-jing",1);
		damage=damage*me->query_str(1)/15+random(damage);
		//��һ�п������ж�
		if(random(me->query("combat_exp")) > target->query("combat_exp")/2
		   || random(me->query_int())>target->query_int()/2)
		{
			
			msg = HIR "\n\n$n�ĵ�һ�����죬���й�������֮�����ѿ�����$n��ǰ�ء�\n" NOR;
			target->receive_damage("qi",damage,me);
			target->receive_damage("qi",damage/3,me);
			if(userp(me) && me->query("env/damage"))
				   tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage*5/4+ WHT"�㹥���˺���\n"NOR); 

		}
		else {
			msg = HIC "����$n������$N����ͼ���ɿ�������ȥ��\n" NOR;
			me->start_busy(1);
		}
		message_vision(msg, me, target);
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/damage",skill/4);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/damage",-skill/4);

		if (objectp(target)&&me->is_fighting())
			next1(me, target);
		else me->delete_temp("xddf/bafang");
		return 1;
}

void next1(object me, object target)
{
	string msg;
	int damage;
	object weapon;

	if (!me) return ;
	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target))
	{
		me->delete_temp("xddf/bafang");
		return ;
	}

	message_vision(HIR"\n$N�������䣬����������ʮ������һ������һ����һ����֮������������ȥ������������Ŀ��Ͼ�ӡ�\n"+
		"ֻҪ$nײ���ˣ�����Ҳ�����ˣ����㲻ײ�ϣ�ֻҪһ��һ������ʱ��ᱻ���뵶Ӱ�С�\n"NOR,me,target);
	
//�ڶ����ж����ͻ����似
	if(random(me->query("dex"))>target->query("dex")/2
		||random(me->query_skill("xuedao-daofa",1))> target->query_skill("dodge",1)/2 )
	{
		msg =  HIY"$n˫�����������ֻҪ�ٸ�$N��㿳�ϼ�����$n�ֱ��ϵĽ���ҲҪ�����ˡ�\n"NOR;
		damage = me->query_skill("xuedao-daofa",1)+me->query_skill("force",1);
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
		if(userp(me) && me->query("env/damage"))
			   tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage*4/3+ WHT"�㹥���˺���\n"NOR); 

		me->add("neili",-300);
		me->add("jingli",-100);
	} else {
		message_vision(CYN"$nƾ�����ɵ����㿪����һ�С�\n"NOR,me, target);
		me->start_busy(1+random(2));
		target->start_busy(1+random(2));
	}
	//me->start_perform(4,"��ҹս�˷�ʽ��");

	if (objectp(target) && me->is_fighting() && me->query_skill("xuedao-daofa",1)>=350)
		next2(me, target);
	else me->delete_temp("xddf/bafang");

	return;

}

void next2(object me, object target)
{
	string msg;
	int damage,skill;
	object weapon;

	if( !me ) return ;

	weapon = me->query_temp("weapon");
	skill=me->query_skill("xuedao-daofa",1);
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("xddf/bafang");
		return ;
	}

	message_vision(HIC "\n$N��ͷһ����Ц���ϣ�����"NOR+weapon->query("name")+HIC"��Ȼ�������ߣ�����ǰ�У����ǹ��죬��Ȼ���Ѵ���$n�����ؿڡ�\n"NOR,me,target);
//�����кͱ����й�
	if(random(me->query("str")) > target->query("str")/2
		||random(me->query_skill("blade",1)) >target->query_skill("parry",1)/3)
	{
		msg = HIC "$n��"NOR+weapon->query("name")+HIC"��һ�����������࣬$n��ɫ��䣡\n"NOR;
		damage = me->query_skill("xuedao-daofa",1)+me->query_skill("force",1);
		damage += me->query_skill("blade",1);
		damage=damage*me->query_str()/15;
		damage += random(damage);
		
		//if (!target->is_busy()) target->start_busy(damage/500);
		target->add_temp("apply/attack", -200);
		target->add_temp("apply/dodge", -200);
		target->add_temp("apply/parry", -200);
		
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		
	//	if (wizardp(me)) write("damage3="+damage);

		msg += damage_msg(damage, "����");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "�ֱ�");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		if(userp(me) && me->query("env/damage"))
			   tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage*4/3+ WHT"�㹥���˺���\n"NOR); 

		me->add("neili",-300);
		me->add("jingli",-150);
		if (objectp(target))
			call_out("back", 5+random(5), target);
	} else {
		msg = HIW "$n�����Ṧ����ǰһԾ���㿪һ�ԡ�\n" NOR;
		message_vision(msg, me, target);
		me->start_busy(1 + random(2));
		target->start_busy(1+random(2));
	}
	me->add_temp("apply/attack",skill/4);
	me->add_temp("apply/damage",skill/4);
	
	me->set_temp("xddf/bafang",1);

    if (me->query_skill("xuedao-daofa",1)>400
	    &&objectp(target)
		&&me->is_fighting())
    {
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

    }
	if (me->query_skill("xuedao-daofa",1)>450
	    &&objectp(target)
		&&me->is_fighting())
    {
		message_vision(HIR"$N�뷢���ţ��ʡ�ŭĿ����ࡹʩչ��ҹս�˷�ʽ���һ��,�Ѿ�����ħ���ľ��磡\n"NOR,me);
		me->add_temp("apply/blade",skill/4);
		me->add_temp("apply/damage",skill/5);
		me->set_temp("xddf/jingang",1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->delete_temp("xddf/jingang");
		me->add_temp("apply/blade",-skill/4);
		me->add_temp("apply/damage",-skill/5);

    }

	me->add_temp("apply/attack",-skill/4);
	me->add_temp("apply/damage",-skill/4);

	me->delete_temp("xddf/bafang");
	//me->start_perform(4,"��ҹս�˷�ʽ��");
	return;
}




void back(object target)
{
	if (!target) return;
	target->add_temp("apply/attack", 200);
	target->add_temp("apply/dodge", 200);
	target->add_temp("apply/parry", 200);
	return;
}
string perform_name(){ return HIY"ҹս�˷�ʽ"NOR; }

int help(object me)
{
   write(WHT"\nѪ������֮��"HIY"��ҹս�˷�ʽ��"WHT"����"NOR"\n");
   write(@HELP
	�ˡ�ҹս�˷�ʽ��������Ѫ�������ھ�������������
	����ʩչѪ�������й������ʽ�����䲻�����ơ���һ
	��ƾ�����������Գ��֣��ڶ�����������������
	�����ʽ����350��������ƾ���似���ƻ�������Ƴ���
	������ӭս�Է���
	ע�⣺�����м�Ϊ��Ҫ�����Է�Ϊ�������У�������
	һ���̶ȵ�������æµ״̬��

	ָ�perform blade.bafang

Ҫ��
	��ǰ���� 1000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	Ѫ������ 220 ���ϣ�
	�������� 220 ���ϣ�
	�����ڹ� 220 ���ϣ�
	Ѫ������ 220 ����
	��������ΪѪ��������
	�����ڹ�ΪѪ����
	�����м�ΪѪ���������ջ�������
	���гֵ���

HELP
   );
   return 1;
}
