// jinzhen.c ����ɽ�
// by sohu@xojh 2014

#include <ansi.h>
#include <combat.h>
int strike_attack(object me,object target);

inherit F_SSERVER;
int perform(object me, object target)
{
        int damage,skill;
        string msg;
		object weapon;
		skill=me->query_skill("liangyi-jian",1);
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
			return notify_fail("������ɽ١�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
		if (!objectp(weapon = me->query_temp("weapon"))
			|| (string)weapon->query("skill_type") != "sword")
            return notify_fail("��ʲô��Ц��ûװ��������ʹ������ɽ١���\n");
                
		if( (int)me->query_skill("liangyi-jian",1)<200)
			return notify_fail("��������ǽ���������죬����ʹ�á�����ɽ١���\n");
		if( me->query_skill_mapped("sword")!="liangyi-jian"
			||me->query_skill_mapped("sword")!="liangyi-jian")
			return notify_fail("��û�м��������ǽ���������ʹ�á�����ɽ١���\n");

		if( (int)me->query_skill("xuantian-wuji",1)<200)
			return notify_fail("��������޼���������񣬲���ʹ�á�����ɽ١���\n"); 
		if( (int)me->query_skill("sword",1)<200)
			return notify_fail("��Ļ�������������񣬲���ʹ�á�����ɽ١���\n"); 
        if( (int)me->query("max_neili",1)<1500)
			return notify_fail("�������������̫��������ʹ�á�����ɽ١���\n");                
		if( (int)me->query("neili",1)<400)
			return notify_fail("�����ڵ�ǰ����̫��������ʹ�á�����ɽ١���\n");
		if( (int)me->query("jingli",1)<300)
			return notify_fail("�����ڵ�ǰ����̫��������ʹ�á�����ɽ١���\n");
		if( (int)me->query_dex(1)<50)
			return notify_fail("��������Ч��̫��������ʹ�á�����ɽ١���\n");	
	                        
		message_vision(HIW "$N˫�־�������"+weapon->query("name")+HIW"���������,ʹ�����������ǽ����е�����ʽ"HIR"������ɽ١���\n" NOR,me);
				
		
        if (random(me->query("neili")) > target->query("neili")/3 
			||random(me->query_dex())>target->query_dex()/2 )
		{
			               
			message_vision(HIR "$N���С�����ɽ١���ʽ�򵥣���������Ǿ�ʩչ���������$nֻ���������㣬��һ�����С�\n" NOR,me,target);
			damage= skill+(int)me->query_skill("dodge",1)+(int)me->query_skill("xuantian-wuji",1);
			damage = damage*2 + random(damage);                
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/2,me);

			//msg=HIY"������������Ϊ�������з�ʩ����ʱ����������\n"NOR;
			if( damage < 2000 ) 
				msg = HIY"���$n��$N������һ�����ƺ�һ������ʱ��Ѫ��ע��\n"NOR;
			else if( damage < 3000 ) msg = HIY"���$n��$N������������������һ������������\n"NOR;
			else if( damage < 5000 ) msg = RED"���$n��$N���ص����������������ܵ������׻�һ�㣬��������������\n"NOR;
			else msg = HIR"���$n��$N�ġ�����ɽ١���͸ǰ�ģ���ǰһ�ڣ��������ɳ�������\n"NOR;
			message_vision(msg, me, target);
			if (objectp(me)&&me->is_fighting())
				call_out("strike_attack",1,me,target);
		}
		else
		{
			me->start_busy(1);
            msg = CYN"����$p������$P����ͼ����û���ϵ���\n"NOR;
			message_vision(msg, me, target);
		}
		me->add("neili",-100);
		me->add("neili",-80);
		me->start_perform(3,"����ɽ�");
		return 1;
}

int strike_attack(object me,object target)
{
	if (!me||!target) return 0;
	
	if (me->is_fighting()
		&&me->query("gender")=="Ů��"
		&&me->query_skill_mapped("leg")=="chuanyun-tui"
		&&me->query_skill_prepared("leg")=="chuanyun-tui")
	{
			message_vision(HIR "$N������ӯ�������Ṧ�����ļ�Ϊ��ʵ��������ݣ�˳��һ������$n��\n" NOR,me,target);
			me->add_temp("apply/attack",me->query_skill("chuanyun-tui",1)/4);
			me->add_temp("apply/damage",me->query_skill("chuanyun-tui",1)/5);
			me->add_temp("apply/leg",me->query_skill("chuanyun-tui",1)/5);
			COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			me->add_temp("apply/attack",me->query_skill("chuanyun-tui",1)/4);
			me->add_temp("apply/damage",me->query_skill("chuanyun-tui",1)/5);
			me->add_temp("apply/leg",me->query_skill("chuanyun-tui",1)/5);

	}
	if (me->is_fighting()
		&&me->query("gender")=="����"
		&&me->query_skill_mapped("cuff")=="zhentian-quan"
		&&me->query_skill_prepared("cuff")=="zhentian-quan")
	{
			message_vision(HIY "$N��������������ȭ��ʱ����������˳��һȭ����$n��ǰ�أ�\n" NOR,me,target);
			me->add_temp("apply/attack",me->query_skill("zhentian-quan",1)/4);
			me->add_temp("apply/damage",me->query_skill("zhentian-quan",1)/5);
			me->add_temp("apply/cuff",me->query_skill("zhentian-quan",1)/5);
			COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			me->add_temp("apply/attack",me->query_skill("zhentian-quan",1)/4);
			me->add_temp("apply/damage",me->query_skill("zhentian-quan",1)/5);
			me->add_temp("apply/cuff",me->query_skill("zhentian-quan",1)/5);

	}
	return 1;
}

string perform_name() {return RED"����ɽ�"NOR;}

int help(object me)
{
    write(WHT"\n���ǽ�����"RED"����ɽ�"WHT"����"NOR"\n");
    write(@HELP
	���ǽ������������ɾ���������������ʥ������Դ˽�����ɨ
	�������ۡ����������ִ�ս��һս������ƾ��ľ��Ǵ˽�����
	���ǽ��������ڵ������ǽ�������������Ѹ�ݣ�������ʤ����
	ȴ�������鶯��䷢�ӵ����¡��������Ṧ�ã������ǽ���
	����������һ��¥��
	����ɽ������ǽ���������ʽ����ʽ�򵥣������̤ѩ�޺۵�
	��ʽ���Խ����룬ֱ�̶Է����仯��ˣ�����ַ���ʤ����

	ָ�perform sword.jinzhen
	
Ҫ��
	�����޼��ȼ� 200 �����ϣ�
	���ǽ����ȼ� 200 �����ϣ�
	���������ȼ� 200 �����ϣ�
	�������Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 400 ���ϣ�
	��ǰ����Ҫ�� 300 ���ϣ�
	�����������ǽ���
	�����м����ǽ���
	���ֳֽ���������    

HELP
	);
	return 1;
}
