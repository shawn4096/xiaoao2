//sanxian ���������
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
                return notify_fail("���������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("�����������ʹ�û�������壡\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ�������ʹ�û�������壡\n");

        if (!weapon ||weapon->query("skill_type")!="blade")
                return notify_fail("�������޵�����ʹ�û�������壿��\n");
		if (me->query_skill("blade",1)<350)
                return notify_fail("��Ļ�����������350������ʹ�û�������壿��\n");
		if (me->query_skill("force",1)<350)
                return notify_fail("��Ļ����ڹ�����350������ʹ�û�������壿��\n");
		
		if (me->query_skill("fanliangyi-dao",1)<350)
                return notify_fail("��ķ����ǵ�������350������ʹ�û�������壿��\n");

        if ( me->query_skill_mapped("blade") != "fanliangyi-dao"
			|| me->query_skill_mapped("blade") != "fanliangyi-dao" )
             	return notify_fail("������ȼ����������м�Ϊ�����ǵ�����\n");
      //  if (me->query_temp("flyd/sanshenfeng"))
				// return notify_fail("������ʩչ�����ǵ����еĻ�������塣\n");
		if (userp(me)&&!me->query("quest/hs/flyd/sanshenfeng/pass"))
             	return notify_fail("������Ƚ⿪�����似����ʩչ�����ǵ�����\n");

	message_vision( HIR"$N����"+weapon->query("name")+HIR"����һƬ��Ӱ����ʽȴ�����Ǿ�������ȫ�뷴!\n"+
		"$N��������Ƭ����ȴ��$n���֣���$n�о�ǰ�����Ҿ�Ϊ�������ء�\n"NOR,me,target);
	
	me->start_perform(5,"����������塹");
	//me->set_temp("flyd/sanshenfeng",1);
	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
	   || random(me->query_int())>target->query_int()/2)
	{
		
		msg = HIC "\n\n$n����������ζ�����û���ܿ����У���ʱ��Щ���ҡ�\n" NOR;
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
	int damage,damage2;
	object weapon;

	if (!me) return ;
		weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("flyd/sanshenfeng");
		return ;
	}

	msg = YEL"\n$N����ת�������Ȼ���У��Ӳ���˼��ĽǶȷ��ֳ�����һ������$n��ǰ�أ��˵���������֡�\n"NOR;

	if(random(me->query("combat_exp"))>target->query("combat_exp")/2
		||random(me->query_skill("fanliangyi-dao",1))> target->query_skill("dodge",1)/2 )
	{
		msg = msg + HIR"$n����������Ϊ$Nһ�����У���ʱ��Ѫ�Ľ���\n"NOR;
		damage = me->query_skill("fanliangyi-dao",1)+me->query_skill("force",1);
		damage += me->query_skill("blade",1);
		damage=damage*me->query_str()/50;
		damage += random(damage);
		
		target->add("neili",-(1000+random(500)));
		if (target->query("neili")<0) target->set("neili",10);
		
		//����ĳ�ͳһ��ѧ�˺����� by renlai
		
		//����1�ǿ���Ѫ
		damage2=COMBAT_D->do_chemis_attack(me,target,1,damage);		
		
		if (wizardp(me)) write("damage2="+damage2);	    
		msg += damage_msg(damage2, "����");
		msg = replace_string(msg, "$w", weapon->query("name"));
		msg = replace_string(msg, "$l", "�ֱ�");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-350);
		//me->add("jingli",-100); �����������Ѿ��۳�����
		
	} else {
		msg  =  msg + CYN"$nƾ�����ɵ����㿪����һ�С�\n"NOR;
		message_vision(msg, me, target);
		me->start_busy(1+random(2));
		target->start_busy(1+random(2));
	}
	me->start_perform(5,"���������");

	if (objectp(target)&&me->is_fighting())
		next2(me, target);
	return;

}

void next2(object me, object target)
{
	string msg;
	int damage,damage2;
	object weapon;

	if( !me) return ;

	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("flyd/sanshenfeng");
		return ;
	}

	msg = HIG "\n$N����Ʈ������˸����������������䣬"+weapon->query("name")+HIG"������ĥ����ʽ��������$n��\n"NOR;

	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
		||random(me->query_str()) >target->query_dex()/3)
	{
		msg = msg + HIC "$n��"+weapon->query("name")+HIC"ǰ����������$n����ʱΪ��������ס��\n"NOR;
		damage = me->query_skill("fanliangyi-dao",1)+me->query_skill("force",1);
		damage += me->query_skill("blade",1);
		damage=damage*me->query_str()/50;
		damage += random(damage);
		
		//if (!target->is_busy()) target->start_busy(damage/500);
		
		target->add_temp("apply/attack", -200);
		target->add_temp("apply/dodge", -200);
		target->add_temp("apply/parry", -200);
		//target->receive_damage("qi", damage,me);
		//target->receive_wound("qi", damage/3,me);
		//��ѧ�˺�
		damage2=COMBAT_D->do_chemis_attack(me,target,1,damage);		
				if (wizardp(me)) write("damage3="+damage2);

		msg += damage_msg(damage, "����");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "�ֱ�");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-350);
		//me->add("jingli",-150);
		if (objectp(target))
			call_out("back", 5+random(5), target);
	} else {
		msg = msg + HIW "$n�����Ṧ����ǰһԾ���㿪һ�ԡ�\n" NOR;
		message_vision(msg, me, target);
		me->start_busy(1 + random(2));
		target->start_busy(1+random(2));
	}
	me->delete_temp("flyd/sanshenfeng");
	me->start_perform(4,"���������");
	return;
}

void back(object target)
{
	if (!target) return;
	target->add_temp("apply/attack", 200);
	target->add_temp("apply/dodge", 200);
	target->add_temp("apply/parry", 200);
}
string perform_name(){ return RED"����"MAG"��"HIC"���"NOR; }

int help(object me)
{
   write(WHT"\n�����ǵ���֮��"HIG"���������"WHT"����"NOR"\n");
   write(@HELP
	���׵����Ĳ��������롸�����ɡ��ġ������ǽ�����һ����
	������������б仯���������а˰���ʮ�İ�仯������
	��ɽ�߰��������ڹ�����һս�����˷�֪���ⷴ���ǵ�Ҳ
	���˲��õľ�ѧ��
	������������Ƿ����ǵ���ѧ��ʩչ������е���������
	�����޴�

	ָ�perform blade.sanshenfeng

Ҫ��
	��ǰ���� 1000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	�����ǵ��� 350 ���ϣ�
	�������� 350 ���ϣ�
	�����ڹ� 350 ���ϣ�
	��������Ϊ�����ǵ�����
	���гֵ���

HELP
   );
   return 1;
}
