// lianji.c ʥ����������
// cre by sohu@xojh
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

	skill = (int)me->query_skill("shenghuo-lingfa", 1);

	if( !target ) target = offensive_target(me);
	 weapon=me->query_temp("weapon");
	 weapon2=target->query_temp("weapon");

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á�����������\n");

	if((int)me->query("neili") < 5000 )
		return notify_fail("�������������\n");

	if((int)me->query("jingli") < 3000 )
		return notify_fail("��ľ���������\n");

	if((int)me->query_temp("shlf/lianji"))
		return notify_fail("���Ѿ���˫���˫�������ҶԷ��ˡ�\n");

	if(!me->query("quest/mj/shlf/lianji/pass"))
		return notify_fail("��ֻ����˵�������д˾��������������á�\n");
	if(skill < 500)
		return notify_fail("���ʥ����ȼ���������\n");

	if (!me->query_skill("jiuyang-shengong"))
	  if(me->query_skill("shenghuo-shengong", 1) < 550)
		return notify_fail("���ʥ���񹦵ȼ���������\n");

	if(!weapon
		||weapon->query("skill_type")!="dagger")
		return notify_fail("��û���������ʵ�ֱ˴�˫����\n");	

	if ( me->query_skill_mapped("dagger") != "shenghuo-lingfa"
	 //|| me->query_skill_mapped("cuff") != "shenghuo-lingfa"
	 //|| me->query_skill_prepared("cuff") != "shenghuo-lingfa"
	 && userp(me))
		return notify_fail("������Ƚ�ʥ��������ʹ�á�\n");

	if( me->query_skill_mapped("parry") != "shenghuo-lingfa"
	&& me->query_skill_mapped("parry") != "qiankun-danuoyi")
		return notify_fail("����Ҫ�����м�Ϊʥ���������ʹ�ô˾�����\n");

	me->add("jingli", -1000);
	me->add("neili", -1500);
		message_vision(HBYEL+HIW"\n$N������ǰ��˫�ֽ�����"+weapon->query("name")+HBYEL+HIW"����,�絶����ذ�����䡢�ƽ����������н�$n�������ڡ�\n"NOR,me,target);
	
		me->set_temp("shlf/lianji", 12);
	  
		me->add_temp("apply/attack", skill/3);
		me->add_temp("apply/damage",skill/4);
		me->add_temp("apply/cuff",skill/4);
		me->add_temp("apply/dagger",skill/4);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);          //��1�п���
		
		weapon->unequip();
		if (me->is_fighting()&& objectp(target))
		{
			me->add_temp("apply/cuff",skill/4);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);  //��2�п���
			me->add_temp("apply/cuff",-skill/4);
		}        
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);          //��3�п���
		weapon->wield();

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);          //��4�п���
		if (me->is_fighting()&&objectp(target))
		{
			message_vision(HIG"$n��$N���һ�У�����ٿ���������ץס��$N���ֵ�"+weapon->query("name")+HIG",��Ȼ��һ�ᣬ��֪$N���ط��֡�\n"NOR,me,target);
			
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);          //��5�п���
			if (weapon2 && random(me->query_str())>target->query_str()*2/3)
			{
				message_vision(HIB"$nֻ��һ�ɴ�����������ָ���飬���е�"+weapon2->query("name")+HIB"�ѳֲ�ס�����ֶ��ɡ�\n"NOR,me,target);
				weapon2->move(environment(me));
			}

		}
		weapon->unequip();
		if (me->is_fighting()&&objectp(target))
		{
			message_vision(BLU"$n��Ȼ��ͷ��һ��ͷ����$Nײ������˴�ԭ����ѧ�д�ɣ������Լ���Ҫ���Ĳ�λ������ˣ�\n"NOR,me,target);
			me->add_temp("apply/damage",skill/4);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);  		//��6�п���
			me->add_temp("apply/damage",-skill/4);
		}
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);          //��7�п���
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);          //��8�п���
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);          //��9�п���
		if (me->is_fighting()&&objectp(target))
		{
			weapon->wield();
			message_vision(HIY"$Nͬʱ�����ǰ��˫��"+weapon->query("name")+HIY"�໥һ�����һ�죬$n����һ�������ӴӰ����ֱ��������\n"NOR,me,target);
			message_vision(HIC"$nֻ����˫��һ��ѣ�Σ���ʱ��Щͷ�����ǣ�\n"NOR,me,target);

			target->apply_condition("no_exert",2);
			target->add_busy(1);
			target->add_temp("apply/attack",-skill/3);
			target->add_temp("apply/damage",-skill/5);
			call_out("target_back",5,me,target,skill);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);          //��10�п���
		}
		if (me->is_fighting()&&objectp(target))
		{
		weapon->unequip();
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);          //��11�п���
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);          //��12�п���		
		weapon->wield();
		}
		me->add_temp("apply/attack", -skill/3);
		me->add_temp("apply/damage",-skill/4);
		me->add_temp("apply/cuff",-skill/4);
		me->add_temp("apply/dagger",-skill/4);

		me->start_perform(6,"������");
		me->add_busy(3);
		me->delete_temp("shlf/lianji");

	return 1;
}

int target_back(object me, object target,int skill)
{
	if (!target) return;
	message_vision(HIC"$N������ת�������еķ����Ż��֮��ѹ��������\n"NOR,target);
	target->add_temp("apply/attack",skill/3);
	target->add_temp("apply/damage",skill/5);
	return 1;
}


string perform_name(){ return HBYEL+HIW"������"NOR; }

int help(object me)
{
	write(HIY"\nʥ���֮������������"NOR"\n\n");
	write(@HELP
	���书Դ�Բ�˹��ɽ���ˣ��������ѧ����������
	�ߵ����������·�ߣ�ʩչ�����������˷���ʤ����
	�������־������ǽ�������������ע������У�����
	�ڹ������Դ��������Ĳ�������Է������Ի󲢴��
	���͹�����һ���似450���ɣ���Ϊʥ�������
	��ʽ����Ҫע����ǣ�������ʥ�����ں�ƥ�䣬��
	��������ִ�����͹�������������

ָ�perform dagger.lianji

Ҫ��
	��ǰ�������� 5000 ���ϣ�
	��ǰ�������� 3000 ���ϣ�
	ʥ����ȼ� 500 ���ϣ�
	ʥ���񹦵ȼ� 500 ���ϣ�
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
