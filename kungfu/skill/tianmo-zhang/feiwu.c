// feiwu ��ħ����
// ���жѵ���һ��ֻ��һ�У������似
// cre by sohu@xojh 
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
      string *limbs;
	int count, damage = 0;
	int arg=(int)(me->query_skill("tianmo-zhang", 1) / 40);
	if (arg<4) arg=4;
	
    if (arg>10) arg=10; //���������У���Ϊ��ʼ����
    
	if( !target ) target = offensive_target(me);

	if( !target ||!living(target)|| !target->is_character() || !me->is_fighting(target) )
		return notify_fail("����ħ���衹ֻ����ս���жԶ���ʹ�á�\n");

	if( objectp( me->query_temp("weapon")) )
		return notify_fail("ֻ�п��ֲ���ʩչ����ħ���衹��\n");
    if( me->query_skill_mapped("dodge")!="huanmo-wubu" )
		return notify_fail("��Ҫ������ħ�貽����ʩչ����ħ���衹��\n");
	if( (int)me->query_skill("tianmo-zhang", 1) < 100 )
		return notify_fail("�����ħ�Ʒ�������죬����ʹ�á���ħ���衹��\n");

	if( (int)me->query_skill("tianmo-gong", 1) < 100 )
		if( (int)me->query_skill("xixing-dafa", 1) < 100 )
		return notify_fail("��������ڹ��ȼ�����������ʹ�á���ħ���衹��\n");

	if( (int)me->query_dex() < 25 )
		return notify_fail("���������ǿ������ʹ�á���ħ���衹��\n");

	if( arg <= 1 )
		return notify_fail("����Ҫ�����вſ���ɡ���ħ���衹��\n");

	if( (int)me->query("neili", 1) < 1200 )
		return notify_fail("����������̫��������ʹ�á���ħ���衹��\n");

	if( (int)me->query("neili", 1) < 50 * arg )
		return notify_fail("�����ڵ�����ʩչ������ô���С�\n");

//	if( (int)me->query_skill("tianmo-zhang", 1) < arg * 30 )
//		return notify_fail("�����ħ�����Ʒ���û�����������־��磡\n");
    damage=me->query_skill("tianmo-zhang",1);
	message_vision(HIG"$NͻȻ������ǰһ̽������ٿ���ĳ����������У��������٣�˫�ƺ��������ĳ�"+ chinese_number(arg) +"�ơ�\n\n"
						+HIY"��Щ��ʽ�缲�籩�꣬��ǡ�Ƶ���������Ѹ���ޱȣ�$nһʱ���飬������Ƭ��Ӱ֮�С�\n"NOR,  
	              me, target);
    if (userp(target)) target->add_busy(1);
    else target->add_busy(2+random(2));
	limbs = target->query("limbs");
	for(count = 0; count < arg; count++){
	  message_vision(replace_string( HIC+SKILL_D("tianmo-zhang")->query_action(me, me->query_temp("weapon"))["action"]+NOR,	"$l", limbs[random(sizeof(limbs))]) + "��\n\n", me, target);
      damage = damage*arg;
	}    
    //message_vision("damage1="+damage,me);
	damage = (int)me->query("dex")/10 * damage;
	//message_vision("damage2="+damage,me);
	if (damage>8000) damage=8000+random(1000);
	
	if( arg*(random(me->query("combat_exp"))) > target->query("combat_exp") )
	{
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/5,me);
		COMBAT_D->report_status(target, 1);
		//COMBAT_D->report_status(target, 0);
	}
     COMBAT_D->do_attack(me,target, me->query_temp("weapon"),1);

     me->add("neili", -50 * arg);
     me->start_busy(1);
	 me->start_perform(3,"��ħ����");
	 return 1;
}
string perform_name(){ return HIY"��ħ����"NOR; }
int help(object me)
{
	write(HIG"\n��ħ��֮����ħ���衹��\n"NOR);
	write(@HELP
	��ħ���������������������ǧ�������Ŀ����似���������µ���
	ϰ������Ҫ�����似�������������������뷽֤��ʦһս����ħ��
	�İ��Ϊ����֪��
	��ħ�����������ø߳��������ƣ�Χ�ƶԷ�ʩչ��ħ�貽������
	���ƣ������ޱȣ�����������裬����������Ӻ�������һ����
	�Է���ȥ�����������ױȡ�	

ָ�perform strike.feiwu

Ҫ��	
	��ħ�Ƶȼ� 100 ���ϣ�
	�����Ʒ��ȼ� 100 ���ϣ�
	��ħ���ȼ� 100 ���ϣ������Ǵ󷨣���
	������� 1200 ���ϣ� 
	��С������ 25��
	��ǰ������Ϊ�������ʽ�йء�
	��Ҫ������ħ�貽Ϊ�����Ṧ
HELP
	);
	return 1;
}

