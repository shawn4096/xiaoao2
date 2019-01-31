// tiannu.c  ��Ůɢ��
//cre by sohu@xojh 2014
#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("����Ůɢ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
		
	if( (int)me->query_skill("tianyu-qijian", 1) < 150 )
		return notify_fail("��������潣������죬����ʹ�á�\n");
	if( me->query_skill_mapped("sword")!="tianyu-qijian"
		||me->query_skill_mapped("parry")!="tianyu-qijian")
		return notify_fail("��û�м��������潣������ʹ�á�\n");                        
	if( (int)me->query_skill("bahuang-gong", 1) < 150 )
		return notify_fail("��İ˻�����Ψ�Ҷ��𹦲����ߡ�\n");
			
	if( (int)me->query("neili", 1) < 600 )
		return notify_fail("����������̫��������ʹ�á���Ůɢ������\n");
			
	msg = CYN "$N����Ϣ�������󼲶���"+weapon->query("name")+CYN"���������ǧ�������������ǵط���$n��\n"NOR;

	if (random(me->query_skill("sword",1)) > target->query_skill("parry",1)/2
		||random(me->query_skill("combat_exp"))>target->query("combat_exp")/2)
	{
		if (me->query("gender")=="Ů��"&& me->query("per")>28)
		{
				msg += HIG "$N����׿������Ǳ����������������ӣ�$n���鲻�ɵ�һ����\n"NOR;
				target->add_busy(2);
		}
		if (!userp(target)) target->add_busy(2);
			//target->start_busy( (int)me->query_skill("tianyu-qijian") / 20 + 1);
		
		damage = (int)me->query_skill("bahuang-gong", 1);
		damage = damage +  (int)me->query_skill("tianyu-qijian", 1);
		damage = damage +  (int)me->query_skill("sword", 1);
		damage=damage*me->query("per")/5;
		if (damage>5000) damage=5000+random(1000);
		
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		me->add("neili", -100);
		msg += HIR"ֻ��$N������Ϊһ�ߣ�����$n,\n$nֻ��һ���������Ķ�������ͷһ����Ѫ���������\n"NOR;
		me->start_busy(random(2));
	} else 
	{
		msg += CYN"����$p�͵���ǰһԾ,������$P�Ĺ�����Χ��\n"NOR;
		me->add("neili", -100);
		me->start_busy(2);
	}
	message_vision(msg, me, target);
	me->start_perform(3,"����Ůɢ����");
	return 1;
}
string perform_name(){ return CYN"��Ůɢ��"NOR; }

int help(object me)
{
        write(WHT"\n�����潣֮����Ůɢ������"NOR"\n\n");
        write(@HELP
	�����潣������ɽͯ�Ѿ�ѧ֮һ������ɽ��
	ԨԴ����ң��������أ��������֧֮һ��
	���������潣���⾳������Ȼ�����Ʈ��֮
	�⣬���Ʒ����Ƶ���������ȴ�̲�����ɱ��
	����Ůɢ����������ģ����Ů̬֮���Խ���
	��������ɢ�£��γ�һƬ�ܼ��Ľ���������
	���������У��γɼ��籩��ʽ�Ĺ�����
	ע�⣺����Ư��Ů���������ơ�
		
	perform sword.tiannu

Ҫ��
	��ǰ����Ҫ�� 600 ����;
	�����潣�ȼ� 150 ���ϣ�
	���������ȼ� 150 ���ϣ�
	�˻Ĺ����ȼ� 150 ���ϣ�
	��������Ϊ�����潣��
	�����м�Ϊ�����潣��
	���ֳֽ��������


HELP
        );
        return 1;
}
