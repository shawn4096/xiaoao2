// xinmo.c ʥ���--��ħ
// By River@SJ 
// Update By lsxk@hsbbs change perform to exert 2007/6/11
// �޸�Ϊʥ������似���Ǿ���

#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;

void remove_effect(object me,object weapon,int count);
int perform(object me, object target)
{
	int skill;
	object weapon;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("��ֻ����ս��������ʥ�������ħ������\n");

	if((int)me->query("neili") < 3500 ) 
		return notify_fail("�������������\n");

	if((int)me->query("jingli") < 3000 ) 
		return notify_fail("��ľ���������\n");

	if((int)me->query_temp("ling")) 
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = (int)me->query_skill("shenghuo-lingfa", 1);

	if(skill < 450)
		return notify_fail("���ʥ����ȼ���������\n");

   if((int)me->query_skill("qiankun-danuoyi", 1) < 120)
		return notify_fail("���Ǭ����Ų�Ƶȼ���������\n");
/*
   if((int)me->query_skill("jiuyang-shengong", 1) < 120)
           return notify_fail("������̾������ȼ���������\n");
*/
	if( !(weapon=me->query_temp("weapon"))
	|| weapon->query("skill_type") != "dagger" )
		return notify_fail("�㲻�ñ�����ô������ʥ�������ħ������\n");

	if ( me->query_skill_mapped("dagger") != "shenghuo-lingfa"
	 || me->query_skill_mapped("parry") != "qiankun-danuoyi"
	 || me->query_skill_mapped("cuff") != "shenghuo-lingfa"
	 || me->query_skill_prepared("cuff") != "shenghuo-lingfa"
	 && userp(me))
		return notify_fail("������Ƚ�ʥ�������Ǭ����Ų���໥��ϡ�\n");

//	if(userp(me) && me->query("shen") < - 20000 && !me->query_skill("jiuyang-shengong", 1))
//		return notify_fail("������̫���ˣ����ʥ���̫��Σ�ա�\n");

	if(userp(me)){
		me->add("jingli", -80);
		me->add("neili", -300);
	}

	message_vision(HIR"\n$N�˿�է�꾢�У���ʥ����еľ�΢���������ӳ��������齥�ܸ�Ӧ��ͻȻ�������������Ц��\n"+
			"�����о�������а���թ֮�⡣\n" NOR, me);
	
	skill += me->query_skill("force", 1)/3; //�޸ĳ�force�ӳ�
	skill = skill/2 + random(skill/2);
	//skill =skill/2;
	//if (me->query_temp("mj/shenghuo"))
	me->add_temp("apply/dagger", skill/5);
	me->add_temp("apply/attack", skill/3);
	me->add_temp("apply/damage", skill/5);
	me->add_temp("apply/strength", skill/5);
	me->set_temp("ling", skill);

	if (me->query_skill("shenghuo-lingfa",1)<449)   //450����
	 {
		me->start_busy(random(2));
	    me->start_exert(1, "��ħ");
		}
	call_out("remove_effect", 1, me, weapon, skill/3);
	return 1;
}

void remove_effect(object me,object weapon, int count)
{
	if ( !me ) return;
	if (objectp(me) && me->query_temp("ling")) {
		if (count-- > 0 
		&& me->is_fighting()
		&& me->query_skill_mapped("cuff") == "shenghuo-lingfa"
		&& me->query_skill_prepared("cuff") == "shenghuo-lingfa"
		&& me->query_temp("weapon")
		&& weapon == me->query_temp("weapon")) {
			call_out("remove_effect", 1, me, weapon, count);
			return;
		}
		//if (me->query_temp("mj/shenghuo"))
	    me->add_temp("apply/dagger", -me->query_temp("ling")/5);
		me->add_temp("apply/attack", - me->query_temp("ling")/3);
		me->add_temp("apply/damage", - me->query_temp("ling")/5);
		me->add_temp("apply/strength", - me->query_temp("ling")/5);
		me->delete_temp("ling");
		tell_object(me, HIR"\n����ħ�������ˣ�ʥ�����ʱ�������ᣬ���������\n"NOR);
		tell_room(environment(me), HIR+ me->name() + "��ħ�������ˣ�ʥ�����ʱ�������ᣬ���������\n"NOR, ({ me }));
	}
}

string perform_name(){ return HIR"��ħ"NOR; }

int help(object me)
{
   write(WHT"\n����ʥ���֮��"HIR"��ħ"WHT"��"NOR"\n\n");
	write(@HELP
	��ħ���������ķ����������ǻ�ɽ����������ѧ����
	����·�ߣ�������������ʤ��������ʥ���ķ�������
	���ڹ����������г��Ϻͷ�����Ż����Ѫ�Ľ������
	ʥ��������м���Ч�����ɴ���������к��˺���
	
	ָ�perform dagger.xinmo

Ҫ��
	��ǰ���������� 3500 ���ϣ�
	��ǰ���������� 3000 ���ϣ�
	ʥ����ĵȼ� 450 ���ϣ�
	Ǭ����Ų�Ƶȼ� 450 ���ϣ�
	�����Ϊʥ�����
	����ȭ��Ϊʥ�����
	�����м�ΪǬ����Ų�ƣ�
	��ȭ��Ϊʥ�����
	���ֱֳ�����
	450���ɣ�ȡ��busyЧ����
	��ʥ���������������ɱ������

HELP
        );
        return 1;
}
