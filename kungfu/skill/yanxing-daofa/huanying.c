// huanying.c
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int skill;
	if( !target ) target = offensive_target(me);

	if(!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if( !objectp(target)
	 || !me->is_fighting(target) )
		return notify_fail("����Ӱ��ֻ����ս���жԶ���ʹ�á�\n");

	if((int)me->query_skill("force", 1) < 100 )
		return notify_fail("��Ļ����ڹ��ȼ����������ܺ�����Ӱ��\n");       

	

	if((int)me->query_skill("yanxing-daofa", 1) < 150 )
		return notify_fail("������е����ȼ����������ܺ�����꣡\n");    

	if((int)me->query_skill("blade", 1) < 150 )
		return notify_fail("��Ļ���������������죬���ܺ�������Ļ�Ӱ��\n");    

	if( me->query_skill_mapped("blade") != "yanxing-daofa"
	 || me->query_skill_mapped("parry") != "yanxing-daofa")
		return notify_fail("�������޷���������Ӱ���й�����\n"); 

	if((int)me->query("neili") < 700 )
		return notify_fail("����������̫�������ܺ�����Ӱ��\n");

	if((int)me->query("max_neili") < 2000 )
		return notify_fail("����������̫�������ܺ�����Ӱ��\n");

	if ((int)me->query_temp("��Ӱ", 1) ) 
		return notify_fail("���Ѿ����������Լ��Ļ�Ӱ��\n");
    
	message_vision(HIY"\n$Nǰ�����ߣ��������������иֵ�ԽʹԽ�죬�����������⻯���������Ρ�\n"+
			"$n�������е���֮�����λ�Ӱ�����Ի������޴룬��֪�ĸ�$N���棬�ĸ��Ǽ١�\n\n"NOR, me, target);

	if (me->query_skill("yanxing-daofa")<350)
	{	
		me->start_busy(1+random(1));
		}
	me->add("neili", -200);    
	skill = me->query_skill("yanxing-daofa", 1)/3;
	me->set_temp("��Ӱ", 1);
	me->set_temp("huanying",skill);
	//��������������
	if (me->query("gender")!="����" || me->query("class")!="bonze"||!me->query("quest/em/yxdf/jueji/pass"))
		me->start_perform(1+random(3), "�����λ�Ӱ��");
	me->add_temp("apply/attack",skill);
	me->add_temp("apply/damage",skill/2);
	call_out("remove_effect", 1, me, skill);
	return 1;
}

void remove_effect(object me,int count)
{
	int skill;
	object weapon;
	if (!me) return;
	weapon=me->query_temp("weapon");

	skill=me->query_temp("huanying");
	if(!me->is_fighting()
	 || me->query_skill_mapped("blade") != "yanxing-daofa"
	 || !weapon
	 || weapon->query("skill_type")!="blade"
	 || count < 1){
		message_vision("�Ǹ�"HIY"��Ӱ"NOR"�ڰ���ǻ���һ�󣬾���ʧ�ڵص��ˣ�\n", me);
		me->delete_temp("��Ӱ");
		me->add_temp("apply/attack",-skill);
	    me->add_temp("apply/damage",-skill/2);
		me->delete_temp("huanying");
		return;
	}
	else {
		call_out("remove_effect", 1, me, count -1);
	}
}

string perform_name(){ return HIC"���λ�Ӱ"NOR; }

int help(object me)
{
        write(HIC"\n���е���֮�����λ�Ӱ����"NOR"\n\n");
        write(@HELP
	���е������Ƕ�ü�׼ҵ����似��������º���
	ѧϰϰ�á�������Ҫ���ټ�ׯ���ʹ�ã�������
	����С��İ��ؾ����ں�Ȼ������������У���
	�����ֵ�ע���������������鲻�ḻ������ϵ�
	��ƭ����ü����ֻ��ʩչ��ü��һ�ž���������
	���ơ��ͻ����Է����ؿڣ�����˺���
	ע�⣺�׼����ӽ⿪�º�������󣬴��з�Ծ
	
	ָ�perform blade.huanying

Ҫ��  
	��ǰ�������� 700 ���ϣ�
	����������� 2000 ���ϣ�
	���е����ȼ� 150 ���ϣ�
	�����ڹ��ȼ� 150 ���ϣ�
	���������ȼ� 150 ���ϣ�
	��������Ϊ���е�����
	�����м�Ϊ���е�����
	�����ڹ����ޣ�
	���ֱֳ���,350��С�ɡ�

HELP
        );
        return 1;
}
