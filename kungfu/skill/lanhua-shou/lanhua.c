//lanhua.c ��������ʽ
//by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>
void next1(object me, object target, int i);
void next2(object me, object target, int i);

int perform(object me,object target)
{
	int i;
	string msg;
	object weapon,tweapon;
    weapon = me->query_temp("weapon");  
        
		if( !target ) target = offensive_target(me);
		
		tweapon = target->query_temp("weapon");  

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��������ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("�����������ʹ�á�������ʽ����\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ�������ʹ�á�������ʽ����\n");

        if (weapon)
                return notify_fail("�������ñ���������ʹ�á�������ʽ������\n");
		//�����������ּ���
		if (!me->query("thd/wuji/lhs"))
				return notify_fail("��Ӻδ�͵ѧ���������֡�����\n");
	    //������pfm����
     	if (!me->query("quest/thd/lhs/lanhua/pass"))
				return notify_fail("����Ȼ��˵��������δѧ�ᣬ����ʹ�á�������ʽ������\n");

		if (me->query_skill("hand",1)<300)
                return notify_fail("��Ļ����ַ�����300������ʹ�á�������ʽ������\n");
		if (me->query_skill("force",1)<300)
                return notify_fail("��Ļ����ڹ�����300������ʹ�á�������ʽ������\n");
		if (me->query_skill("bihai-chaosheng",1)<300)
                return notify_fail("��ı̺�����������300������ʹ�á�������ʽ������\n");

		if (me->query_skill("lanhua-shou",1)<300)
                return notify_fail("��������ֵȼ�����300������ʹ�á�������ʽ������\n");

        if ( me->query_skill_mapped("hand") != "lanhua-shou" )
             	return notify_fail("������ȼ����ַ�Ϊ�����֡�\n");

      //  if (me->query_temp("lhs/lanhua"))
				//return notify_fail("������ʩչ�������еġ�������ʽ����\n");
	
	message_vision( HIG"$N��Ĵָ��ʳָ����������ָ���ţ���ָ��һ֦��������������������Ѽ����ѽ�$n��ǰ��Ѩ��ס��\n"+
		"$nֻ����ǰ��ӰѤ�ã����������־�����"+HIY"��������Ҷʽ"+HIG"����\n"NOR,me,target);

	me->start_perform(4,"��������ʽ��");
	//me->set_temp("lhs/lanhua",1);
	
	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
	   || random(me->query_int())>target->query_int()/2)
	{
		
		message_vision( HIR "\n\n$nֻ��һ������Ĵ������������Ѩһ�飬����"+HIY"��������Ҷʽ"+CYN"�����С�\n" NOR,me,target);
		if (tweapon)
		{
			message_vision(CYN"$n���е�"+tweapon->query("name")+CYN"�ѳֲ�ס�����ڵ��ϡ�\n"NOR,me,target);
			tweapon->move(environment(target));
		}
		target->add_busy(1);
	}
	else {
		msg = HIW "����$n������$N����ͼ���ɿ�������ȥ��\n" NOR;
		me->start_busy(1);
	}
	//��Ҷ�ͷ�
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	if (me->is_fighting()&&objectp(target))
		next1(me, target, i);
	return 1;
}

void next1(object me, object target, int i)
{
	string msg;
	int damage,lvl;
	object weapon;

	if (!me) return ;
	weapon = me->query_temp("weapon");
	if (weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("lhs/lanhua");
		return ;
	}
	message_vision( YEL"\n$N��ķָ��ʳָ������ָ������س������ţ�һ̧һʽ���޲���������,ٿȻ��ת��$n�����\n"+
		"�����һ���������"+HIM"�����ֵ���ʽ"+YEL"��!\n" NOR,me,target);
	if(random(me->query("combat_exp"))>target->query("combat_exp")/2
		||random(me->query_skill("lanhua-shou",1))> target->query_skill("dodge",1)/2 )
	{
		message_vision(RED"$n����"+HIM"�����ֵ���ʽ"+RED"������������$n�������Ѩ��ս���������\n"NOR,me,target);
		damage = me->query_skill("lanhua-shou",1)+me->query_skill("force",1);
		damage += me->query_skill("hand",1);
		damage=damage*me->query_dex()/20;
		damage += random(damage);
		
		target->add("neili",-(1000+random(500)));
		if (target->query("neili")<0) target->set("neili",0);
		
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		if (wizardp(me)) write("damage2="+damage);
	    
		msg = damage_msg(damage, "����");
		//msg = replace_string(msg, "$w", weapon->query("name"));
		msg = replace_string(msg, "$l", "ǰ��");
		
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-300);
		me->add("jingli",-100);
		//����
		lvl=me->query_skill("lanhua-shou",1);
		if (!target->query_temp("lhs/diewu"))
		{
		
			target->set_temp("lhs/diewu",lvl);
			target->add_temp("apply/dexerity",-lvl/20);
			target->add_temp("apply/strength",-lvl/20);
			target->add_temp("apply/constitution",-lvl/20);
			target->add_temp("apply/intelligence",-lvl/20);
			if (objectp(target))
				call_out("remove_diewu",(int)lvl/30,target);
		}
	} else {
		msg  =  CYN"$nƾ�����ɵ����㿪����һ�С�\n"NOR;
		message_vision(msg, me, target);
		me->start_busy(1+random(2));
		target->start_busy(1+random(2));
	}
	if (me->is_fighting()&&objectp(target))
		next2(me, target, i);
	return;

}

void next2(object me, object target, int i)
{
	string msg;
	int damage;
	object weapon;

	if( !me ) return ;

	weapon = me->query_temp("weapon");
	if (weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("lhs/lanhua");
		return ;
	}
	message_vision(HBCYN "\n$N��Сָ�Ϳ��Զ�׼���˵ĺϹ�Ѩ������ָ��׼����Ѩ����ָ��׼����Ѩ��ʳָ��׼���Ѩ��ķָ��׼�ڹ�Ѩ�硣\n"+
	"�����һ���������"+HIR"����������ʽ"+HBCYN"��\n"NOR,me,target);

	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
		||random(me->query_str()) >target->query_dex()/3)
	{
		message_vision(HIC"$n����"+HIR"����������ʽ"+CYN"�������ˡ�"HIR+"�Ϲ�Ѩ"+HIC+"����$nȫ�����飬�书�����������޷�ʩչ������\n" NOR,me,target);

		damage = me->query_skill("lanhua-shou",1)+me->query_skill("force",1);
		damage += me->query_skill("hand",1);
		damage=damage*me->query_str()/20;
		damage += random(damage);
		
		if (!target->query_temp("lhs/qinna"))
		{
			target->add_temp("apply/attack", -200);
			target->add_temp("apply/dodge", -200);
			target->add_temp("apply/parry", -200);
			target->set_temp("lhs/qinna",1);
			if (objectp(target))
				call_out("back", 5+random(5), target);

		}
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		target->receive_wound("jing",damage/6,me);
		
		if (wizardp(me)) write("damage3="+damage);

		msg = damage_msg(damage, "����");
		//msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "�ֱ�");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-300);
		me->add("jingli",-150);
	} else {
		msg = msg + HIW "$n�����Ṧ����ǰһԾ���㿪һ�ԡ�\n" NOR;
		message_vision(msg, me, target);
		me->start_busy(1 + random(2));
		target->start_busy(1+random(2));
	}
	me->delete_temp("lhs/lanhua");
	me->start_perform(4,"��������ʽ��");
	return;
}
/*
//����ָ�
void remove_diewu(object target)
{
	int lvl;
	if (!target) return;
	lvl=target->query_temp("lhs/diewu");
	target->add_temp("apply/dexerity",-lvl/20);
    target->add_temp("apply/strength",-lvl/20);
    target->add_temp("apply/constitution",-lvl/20);
    target->add_temp("apply/intelligence",-lvl/20);
	target->delete_temp("lhs/diewu");
	return;
}
//���ûָ�

void back(object target)
{
	if (!target) return;
	target->add_temp("apply/attack", 200);
	target->add_temp("apply/dodge", 200);
	target->add_temp("apply/parry", 200);
	target->delete_temp("lhs/qinna");
	return;
}
*/
string perform_name(){ return HBCYN+HIG"������ʽ"NOR; }

int help(object me)
{
   write(WHT"\n������֮��"HBCYN+HIG"������ʽ"WHT"����"NOR"\n");
   write(@HELP
	������ʽ�ǽ��һ����Ҵ���ѧ�����ֵľ�Ҫ��ѧ����Ҷʽ��
	������ʽ����������ʽ����ʽ����һ��ʩչ�����������ֵ�
	���������������ʽ�������������֡��졢׼���桢�塱����
	�㡣ʵ���һ�����ѧ�ľ��⣬Ů����������ơ�
	
	��Ҷʽ�����ַ��˵У�����Է�����
	����ʽ�������Է��������ԣ���Ϊ���ն���
	����ʽ��ר��ѡ��Է�����Ѩ���֣��ƶԷ�����	

ָ�perform hand.lanhua

Ҫ��
	��ǰ���� 1000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	�����ַ� 300 ���ϣ�
	�����ַ� 300 ���ϣ�
	�����ڹ� 300 ���ϣ�
	�̺����� 300 ���ϣ�
	�����ַ�Ϊ�����֣�
	�����м�Ϊ�����ֻ�ָ��ͨ
	���ֲ��ܳ���������

HELP
   );
   return 1;
}
