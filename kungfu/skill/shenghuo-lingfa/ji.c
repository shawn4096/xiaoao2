// ji.c ʥ���--��
// By River@SJ
// Modified by snowman@SJ 26/04/2001
// bug bug bug fix by lane@SJ �����洦�� pfm ������Щ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int checking(object me, object target);
int perform(object me, object target)
{
	int skill,count,i;
	object weapon,weapon2;
	object *inv;
	 //�ж��Ƿ���2������
	 weapon=me->query_temp("weapon");
	 inv = all_inventory(me);
     for(count=0, i=0; i<sizeof(inv); i++) {
           if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
           if( inv[i]->query("skill_type") == "dagger" ) 
		   {
			   weapon2 = inv[i];
			   break;
		   }
     }

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á������־���\n");

	if((int)me->query("neili") < 5000 )
		return notify_fail("�������������\n");

	if((int)me->query("jingli") < 3000 )
		return notify_fail("��ľ���������\n");

	if((int)me->query_temp("shlf_ji"))
		return notify_fail("���Ѿ���˫���˫�������ҶԷ��ˡ�\n");

	skill = (int)me->query_skill("shenghuo-lingfa", 1);

	if(skill < 400)
		return notify_fail("���ʥ����ȼ���������\n");

	if (!me->query_skill("jiuyang-shengong"))
	  if(me->query_skill("shenghuo-shengong", 1) < 400)
		return notify_fail("���ʥ���񹦵ȼ���������\n");

	if(! weapon || !weapon2)
		return notify_fail("��û���������ʵ�ֱ˴�˫����\n");

	/*if( weapon->query_amount() < 2 && weapon->query("dagger_count") < 2 )
		return notify_fail("��ֻ��һ�����ƣ���ô˫����\n");*/
	

	if ( me->query_skill_mapped("dagger") != "shenghuo-lingfa"
	 || me->query_skill_mapped("cuff") != "shenghuo-lingfa"
	 || me->query_skill_prepared("cuff") != "shenghuo-lingfa"
	 && userp(me))
		return notify_fail("������Ƚ�ʥ��������ʹ�á�\n");

	if( me->query_skill_mapped("parry") != "shenghuo-lingfa"
	&& me->query_skill_mapped("parry") != "qiankun-danuoyi")
		return notify_fail("����Ҫ�����м�Ϊʥ���������ʹ�ô˾�����\n");

	me->add("jingli", -50);
	me->add("neili", -100);
	message_vision(HIY"\n$N������ǰ��˫�ֽ�����"+weapon->query("name")+HIY"�໥һ�����һ���������ǽ����ʮ�ֹŹ֡�\n"NOR,me);
	
	me->set_temp("shlf_ji", 1);
	checking(me,target);
	return 1;
}

int check_fight(object me, object target)
{
	object weapon;
	int skill;
	
	if (!me ||!me->query_temp("shlf_ji") || !living(me)){
		if( target) {
			skill= target->query_temp("ji");
			target->add_temp("apply/attack", skill/5);
			target->add_temp("apply/defense", skill/5);
			target->add_temp("apply/dodge", skill/5);
			target->delete_temp("ji");
			message_vision(HIW"\n$n���ߵ���������ʧȥ����־�ָֻ�����Ȼ��\n"NOR,me,target);
			return 1;
		}
		return 1;
	}
	if (!target){
			me->delete_temp("shlf_ji");
			return 1;
	}
	me->delete_temp("shlf_ji");
	skill = me->query_skill("shenghuo-lingfa", 1);
	if(!weapon = me->query_temp("weapon")){
		if(target->is_busy()) target->start_busy(1);
		target->add_temp("apply/attack", skill/5);
		target->add_temp("apply/defense", skill/5);
		target->add_temp("apply/dodge", skill/5);
		message_vision(HIW"\n$N�����������ƣ�$n���ߵ�����ʧȥ����־�ָֻ�����Ȼ��\n"NOR,me,target);
	}
	else if(environment(me) != environment(target)){
		if(target->is_busy()) target->start_busy(1);
		target->add_temp("apply/attack", skill/5);
		target->add_temp("apply/defense", skill/5);
		target->add_temp("apply/dodge", skill/5);
		message_vision(HIW"\n$N�뿪$n�ˣ�$n���ߵ�����ʧȥ����־�ָֻ�����Ȼ��\n"NOR,me,target);
	}
	else if(!target->is_busy()){
		target->add_temp("apply/attack", skill/5);
		target->add_temp("apply/defense", skill/5);
		target->add_temp("apply/dodge", skill/5);
		message_vision(HIW"\n$n���ߵ���������ʧȥ����־�ָֻ�����Ȼ��\n"NOR,me,target);
	}
	else if(!me->is_fighting(target)){
		if(target->is_busy()) target->start_busy(1);
		target->add_temp("apply/attack", skill/5);
		target->add_temp("apply/defense", skill/5);
		target->add_temp("apply/dodge", skill/5);
		message_vision(HIW"\n$N����սȦ��$n���ߵ�����ʧȥ����־�ָֻ�����Ȼ��\n"NOR,me,target);
	}
	else if (userp(me) && me->query_skill_mapped("dagger") != "shenghuo-lingfa"
	 || me->query_skill_mapped("cuff") != "shenghuo-lingfa"){
		if(target->is_busy()) target->start_busy(1);
		me->start_busy(1);
		target->add_temp("apply/attack", skill/5);
		target->add_temp("apply/defense", skill/5);
		target->add_temp("apply/dodge", skill/5);
		message_vision(HIW"\n$N������ʥ���������$n���ߵ�����ʧȥ����־�ָֻ�����Ȼ��\n"NOR,me,target);
	}
	else {
		me->set_temp("shlf_ji", 1);
		call_out("check_fight", 1, me, target, weapon);
		return 1;
	}
	return 1;
}

int checking(object me, object target)
{
	int time, skill, exp, exp1, ap, dp;

	skill = (int)me->query_skill("shenghuo-lingfa", 1);
	time = random(skill/20) + 4;
	exp = me->query("combat_exp");
	exp1 = target->query("combat_exp");

	ap = exp/100 * me->query_str()/2;
	dp = exp1/100 * target->query_con()/2;
    if (me->query_temp("mj/shenghuo"))
	  	skill = (int)me->query_skill("shenghuo-lingfa", 1)+(int)me->query_skill("shenghuo-shengong", 1);
	  
	if( wizardp(me) ) tell_object(me, "˫������Ϊ��"+ap+"��"+dp+"��\n"NOR);
    
	if( random( ap + dp ) > dp 
		||random(me->query_str(1)>target->query_str(1)/2) ) {
		message_vision(HIR"ֻ�����һ�죬$n����һ����������ʱ�޷����ƣ��Ӱ����ֱ��������\n"NOR,me,target);
        message_vision(HIY"$n��$N��˫�����ӻ�ɬ������Ӱ�죬���з��꣬��������ӿ������֮���ƺ��ܵ�������\n"NOR,me,target);
		target->add_busy(time);
		target->set_temp("ji",skill);
		target->add_temp("apply/attack", -skill/5);
		target->add_temp("apply/defense", -skill/5);
		target->add_temp("apply/dodge", -skill/5);
		me->set_temp("shlf_ji", 1);
		me->add("neili", -200);
		me->add("jingli", -10);
		if (me->query_skill("shenghuo-lingfa",1)<450) me->start_busy(random(2));//���Ӵ��Ч��
		if (me->query_skill("shenghuo-shengong",1) < 450 || !me->query_temp("mj/shenghuo"))
		    me->start_perform(3, "�������־�"); //���buff����
			
		call_out("check_fight", 1, me, target);
	}
	else {
		me->start_busy(random(2));
		message_vision(CYN"$n����һ�𣬵��漴�ָ�����־��û������˫��֮�����Ի�\n"NOR,me,target);
		me->start_perform(2,"�������־�");
		me->delete_temp("shlf_ji");
	}
	return 1;
}

string perform_name(){ return HIY"˫����"NOR; }

int help(object me)
{
	write(HIY"\nʥ���֮��˫��������"NOR"\n\n");
	write(@HELP
	���书Դ�Բ�˹��ɽ���ˣ��������ѧ����������
	�ߵ����������·�ߣ�ʩչ�����������˷���ʤ����
	�������־������ǽ�������������ע������У�����
	�ڹ������Դ��������Ĳ�������Է������Ի󲢴��
	���͹�����һ���似450���ɣ���Ϊʥ�������
	��ʽ����Ҫע����ǣ�������ʥ�����ں�ƥ�䣬��
	��������ִ�����͹�������������

	ָ�perform dagger.ji

Ҫ��
	��ǰ�������� 5000 ���ϣ�
	��ǰ�������� 3000 ���ϣ�
	ʥ����ȼ� 400 ���ϣ�
	ʥ���񹦵ȼ� 400 ���ϣ�
	�����Ϊʥ�����
	����ȭ��Ϊʥ�����
	�����м�Ϊʥ�����Ǭ����Ų�ƣ�
	��ȭ��Ϊʥ�����
	���ֳ�����ذ���������
	450����ִ��Ч��.

HELP
        );
        return 1;
}
