//sannong ÷����Ū
//
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
    object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("÷����Ūֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("�����������ʹ��÷����Ū��\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ�������ʹ��÷����Ū��\n");

        if (!weapon || !(weapon->id("xiao")))
                return notify_fail("��������������ʹ��÷����Ū����\n");
		if (me->query_skill("sword",1)<300)
                return notify_fail("��Ļ�����������300������ʹ��÷����Ū����\n");
		if (me->query_skill("force",1)<300)
                return notify_fail("��Ļ����ڹ�����300������ʹ��÷����Ū����\n");

		if (me->query_skill("yuxiao-jian",1)<300)
                return notify_fail("������｣������300������ʹ��÷����Ū����\n");
       // if (!me->query_temp("yuxiao-jian/luanren",1)||!me->query_temp("yuxiao-jian/nizhuan",1))
               // return notify_fail("�㲻ʹ�á�����(perform yinyang)����(perform nizhuan)�з�����ô����÷����Ū��ס�����ж���\n");

        if ( me->query_skill_mapped("sword") != "yuxiao-jian" )
             	return notify_fail("������ȼ�������Ϊ���｣����\n");
        if (me->query_temp("yxj/sannong"))
				return notify_fail("������ʩչ���｣���е�÷����Ū��\n");
	
	message_vision( MAG"$N����"+weapon->query("name")+MAG"��������Ū�ַ����࣬������ģ��������ϵ�÷���������ţ���Ө���\n"+
		"$n�·��������Լ�����������𣬸о����������ޱ߼ʵĻ���һ��,���Ծ�����Щ������\n"NOR,me,target);
	
	me->start_perform(4,"��÷����Ū��");
	me->set_temp("yxj/sannong",1);
	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
	   || random(me->query_int())>target->query_int()/2)
	{
		
		msg = HBYEL+HIR "\n\n$nֻ�����Ի����˯���ֽ��ƺ������Լ����ơ�\n" NOR;
		target->add_busy(2);
	}
	else {
		msg = HIY "����$n������$N����ͼ����æҧס�Լ���⣬�������ѡ�\n" NOR;
		me->start_busy(1);
	}
	message_vision(msg, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);

	if (me->is_fighting()&&objectp(target))
		next1(me, target, i);
	else call_out("remove_effect",4,me);
	return 1;
}

void next1(object me, object target, int i)
{
	string msg;
	int damage;
	object weapon;

	if (!me) return ;
	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("yxj/sannong");
		return ;
	}

	msg = MAG"\n$N�������ģ�������Ȼ�θߣ�����÷����Ƭ���ţ�����Ʈ�ף��仨���ꡣ\n"+
		"$n�����Լ���ǰ÷������ʢ�������÷ҷ���Ц��ӭ�ˣ��̲�ס����Ҫȥժȡ��Ѥ�õ�÷����\n"NOR;

	if(random(me->query("combat_exp"))>target->query("combat_exp")/2
		||random(me->query_skill("yuxiao-jian",1))> target->query_skill("dodge",1)/2 )
	{
		msg = msg + HIR"$n����һ���ʹ������ʧ��֮��Ϊ$N���ˣ��ܵ����ˣ�\n"NOR;
		damage = me->query_skill("yuxiao-jian",1)+me->query_skill("force",1);
		damage += me->query_skill("sword",1);
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
	if (me->is_fighting()&&objectp(target))
		next2(me, target, i);
	else call_out("remove_effect",4,me);
	return;

}

void next2(object me, object target, int i)
{
	string msg;
	int damage,lvl;
	object weapon;

	if( !me ) return ;

	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("yxj/sannong");
		return ;
	}

	msg = HIW "\n$N�Ų�������ת��������ɫ��Щ���죬������չ����"+weapon->query("name")+HIW"ʩչ������Ӣ�ͷף�ɷ�Ǻÿ���\n"NOR;
	msg += HIW "\n$Nʩչ�����｣��÷����Ū��$n��������÷����˪�������߽಻���Ľڲ������ʱ������ţ�\n"NOR;
	
	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
		||random(me->query_str()) >target->query_dex()/3)
	{
		msg = msg + HIC "$n��"+weapon->query("name")+HIC"�����������糤ǹ��ꪣ���ӿ���ȣ�$n��ɫ��䣡\n"NOR;
		damage = me->query_skill("yuxiao-jian",1)+me->query_skill("force",1);
		damage += me->query_skill("blade",1);
		damage=damage*me->query_str()/20;
		damage += random(damage);
		
		//if (!target->is_busy()) target->start_busy(damage/500);
		lvl=me->query_skill("yuxiao-jian",1)+me->query_skill("qimen-bagua",1);
		target->apply_condition("no_exert",2);

		target->add_temp("apply/attack", -lvl/3);
		target->add_temp("apply/dodge", -lvl/5);
		target->add_temp("apply/parry", -lvl/5);
		target->add_temp("yxj/sannong",lvl);
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
		msg = msg + HIW "$n�����ڹ��������������ֿ�������������÷����Ū������\n" NOR;
		message_vision(msg, me, target);
		me->start_busy(1 + random(2));
		target->start_busy(1+random(2));
	}
	me->delete_temp("yxj/sannong");
	me->start_perform(3,"÷����Ū");
	return;
}

void back(object target)
{
	int lvl;
	if (!target) return;
	lvl=target->query_temp("yxj/sannong");
	target->add_temp("apply/attack", lvl/3);
	target->add_temp("apply/dodge", lvl/5);
	target->add_temp("apply/parry", lvl/5);
}
void remove_effect(object me)
{
	if (!me) return;
	me->delete_temp("yxj/sannong");
	message_vision(HIM"$N��÷����Ū�����������չ���\n"NOR,me);
	return;
}
string perform_name(){ return MAG"÷����Ū"NOR; }

int help(object me)
{
   write(WHT"\n���｣��֮��"MAG"÷����Ū"WHT"����"NOR"\n");
   write(@HELP
	�ˡ�÷����Ū���������ھ�������ϣ������｣����
	�������ʽ������������Է�������ʤ������������Ҫ
	�����ḻ��ս���������Ӧ���������������ԡ����Է�
	Ϊ�������У�������һ���̶ȵ�������æµ״̬��

	ָ�perform sword.sannong

Ҫ��
	��ǰ���� 1000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	���｣�� 300 ���ϣ�
	�������� 300 ���ϣ�
	�����ڹ� 300 ���ϣ�
	��������Ϊ���｣����
	���г��

HELP
   );
   return 1;
}
