// juanduo.c �������� ����־�
// cre by sohu@xojh 2014/9
// Դ����Ī��ķ�������
#include <ansi.h>


//��Ī�����΢�ӣ���˿��ת���Ѿ�ס������ͷ����һ���������֣�������ʹ���������ϵ�ǧ������˿������֮���������˹��������2�Ƴ������ơ�
//������˫�۾�����Щ�ѳֲ�ס��Σ���г���Ծ�������ڿ���бб�ܹ����Ž���һ�����ɾ�ж��
//����һ���˿�ľ�ֱͦ������һ����ǹ������������ȥ�������˿��������֮�������һ���ɾ�����ָ������Ҫ����Ѩ����һ��֮��ȴҲ��Ϊ������
//��Ī�����ܹ����ȣ������������˿�罫�����ﳤ����ס�����ɾ����Է���������һ��һ�ţ�����һ�죬������Ϊ���أ�����������������ȴ���������ϼ����ȥ��
inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon;
	object ob;		
	string msg;
	int i;
	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("����ɨ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "whip")
			return notify_fail("��ʹ�õ��������ԡ�\n");
	ob = target->query_temp("weapon");
	i=me->query_skill("yinsuo-jinling",1);
	if (me->query_skill_mapped("force")=="yunu-xinjing"&&me->query("gender")=="Ů��")
		i=i+me->query_skill("yunu-xinjing",1)/5;
	if (userp(target))
		i=i+me->query_skill("strike",1)/5;

	if (me->query_skill_mapped("force")!="yunu-xinjing")
		return notify_fail("�㼤�����ڹ����ԣ��޷�ʩչ����̾�����\n");
	if (me->query_skill_mapped("whip")!="yinsuo-jinling"
		||me->query_skill_mapped("parry")!="yinsuo-jinling")
		return notify_fail("�㼤�����似����,�޷�ʩչ����̾�����\n");
	if (me->query_skill_mapped("strike")!="wudu-shenzhang"
		||me->query_skill_prepared("strike")!="wudu-shenzhang")
		return notify_fail("�㼤�����Ʒ����嶾����,�޷�ʩչ����̾�����\n");
	if( (int)me->query_skill("yinsuo-jinling", 1) < 250 )
		return notify_fail("����������岻�����죬�����ܡ���̾���\n");
	if( (int)me->query_skill("whip", 1) < 250 )
		return notify_fail("��Ļ����޷��������죬�����ܡ���̾���\n");
	if(me->query_dex() < 50 )
		return notify_fail("��ĺ����������������ܡ���̾���\n");
	if( (int)me->query_skill("yunu-xinjing",1)< 250)
		return notify_fail("����ڹ���Ϊ̫������޷����Ѩ��\n");
	if( (int)me->query_temp("ysjl/duoci"))
		return notify_fail("�������ʹ���������塸��̾�����\n");
	if( (int)me->query("max_neili")<2500)
		return notify_fail("�������������ʩչ����̾�������.\n");
	if ( (int)me->query("jingli") < 500 )
		return notify_fail("�����������ʩչ����̾�����\n");		
	if ( (int)me->query("neili") < 500 )
		return notify_fail("�����������ʩչ����̾�����\n");
	me->add("neili", - 300);
	me->add("jingli", - 100);
	if (ob)
	    message_vision(HIC"$N����"+weapon->query("name")+HIC"΢�ӣ���Ӱ��ת���Ѿ�ס��$n���е�"+ob->query("name")+HIC"�����һ���������֣���\n"+
					"Ȼ�����ʹ����"+weapon->query("name")+HIC"�ϵ�����ı��ӽ�"+ob->query("name")+HIC"֮���������˹�����\n"NOR,me,target);
	else message_vision(HIC"$N����"+weapon->query("name")+HIC"΢�ӣ���Ӱ��ת���Ѿ�ס��$n���ϱۣ����һ�������ţ���\n"NOR,me,target);
	me->set_temp("ysjl/duoci",1);
    //��,��һ��
		me->add_temp("apply/attack",i/5);
		me->add_temp("apply/damage",i/5);
		me->add_temp("apply/whip",i/5);
	
	if( random( me->query_skill("whip",1)) > target->query_skill("parry",1 )/2
		||random(me->query_dex(1))>target->query_dex(1)/2)
	{
		if (ob)
		{
			message_vision(HIY"\n\n$nֻ��һ�ɴ���Ҫ����"+ob->query("name")+HIY"�����ȥ��æ�˾��ضᣬ��֪������͸\n"+
							"ͻȻ$N���֮���Ѳ�֪���˺δ�����һ˲�䣬������֫�ٺ����ǿտյ���������������\n"NOR,me,target);
			ob->unequip();
			ob->move(environment(target));

		}
		else {
			message_vision(HIY"$n��ʱΪ"+weapon->query("name")+HIY"��ס�����ζ�ʱ���ơ�\n"NOR,me,target);
			target->add_busy(2);
		}
	
	}else {
			message_vision(HIY"$nΣ���г���Ծ�������ڿ���бб�ܹ����Ž�$Nһ�����ɾ�ж����\n"NOR,me,target);
			me->add_busy(1);
	}
	//��һ��
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);   
	 
	 //�ڶ��У���
	
	 if (random( me->query_skill("whip",1)) >  target->query_skill("parry",1 )/2
		||random(me->query_dex(1))>target->query_dex(1)/2)
	 {
		 message_vision(HIR"$N"+weapon->query("name")+HIR"һ���˿�ľ�ֱͦ������һ����ǹ����$n������ȥ���������������֮�\n"
						+"������һ���ɾ�����ָ������Ҫ����Ѩ����һ��֮��ȴҲ��Ϊ������\n"NOR,me,target);
		 target->receive_damage("qi",random(4000),me);
		 target->receive_wound("qi",random(1000),me);
	 }
	
	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	//���������У�����2��
	 message_vision(HIB"$N��$n����ǳЦ���������������ĵ����ؿ�����,���˫�ֻζ���������������!\n"NOR,me,target);
	 weapon->unequip();
	 me->add_temp("apply/strike",i/4);
	 me->add_temp("apply/damage",i/6);
	 me->set_temp("wdsz/duoci",2);
	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
	 me->delete_temp("wdsz/duoci");
	 me->add_temp("apply/damage",-i/6);
	 me->add_temp("apply/strike",-i/4);
		
	 weapon->wield();
	 me->add_temp("apply/attack",-i/5);
	 me->add_temp("apply/damage",-i/5);
	 me->add_temp("apply/whip",-i/5);
	
	 me->delete_temp("ysjl/duoci");
	 me->start_perform(4,"��̾�");
	 me->add_busy(2);
	 return 1;
}
string perform_name(){ return HBYEL+HIR"��̾�"NOR; }

int help(object me)
{
	write(WHT"\n��������֮"HBYEL+HIR"����̾�����"NOR"\n");
	write(@HELP
	���������ǹ�Ĺ��С��Ů�Ķ����似�������书����
	�����֣��Խ�����ʩչ����ʽ������Ī�⣬�Թ�
	��Ѩ��Ϊ������ʽز�������ߣ�Բת���⡣
	��̾�������Դ����Ī��ķ�������������޲��ƶ�
	����������ȡ����Ρ���󣬻����Ϊ���־�������
	�Է������õ�����æ����֮�ʣ����������嶾����
	
	perform whip.duoci
	
Ҫ��
	��ǰ����Ҫ�� 500 ���ϣ�
	��ǰ����Ҫ�� 500 ���ϣ�
	�������Ҫ�� 2500 ����
	��������ȼ� 250 ���ϣ�
	��Ů�ľ��ȼ� 250 ���ϣ�
	�����޷��ȼ� 250 ���ϣ�
	��Ч���ȼ� 50  ���ϣ�
	�����޷�Ϊ�������壻
	�����м�Ϊ�������壻
	�����Ʒ�Ϊ�嶾���ƣ�
	�ұ��Ʒ�Ϊ�嶾���ƣ�
	�ֱֳ����������
HELP
	);
	return 1;
}