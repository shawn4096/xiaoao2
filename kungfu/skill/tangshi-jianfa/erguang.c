//erguang.c ����ʽ
// By Spiderii
// add shenzhao 3 by sohu
#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
	int j, lvl = me->query_skill("tangshi-jianfa", 1);
    if (me->query_skill("shenzhao-jing",1)>349)
       lvl = me->query_skill("tangshi-jianfa", 1)+me->query_skill("shenzhao-jing", 1);
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("������ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	
   if( (int)me->query_skill("tangshi-jianfa", 1) < 250 )
		return notify_fail("�����ʬ��������̫ǳ���������ˡ�\n");

   if( (int)me->query_skill("sword", 1) < 250 )
		return notify_fail("��Ļ�����������̫ǳ���������ˡ�\n");


   if( (int)me->query("max_neili") < 3500 )
		return notify_fail("�������̫ǳ���������ˡ�\n");

	if( (int)me->query("neili") < 1000 )
		return notify_fail("��������������������ˡ�\n");
	
	if( target->is_busy() )
		return notify_fail("�Է��Ѿ���æ�����ˣ��Ͻ������ɡ�\n");

	
	if( !objectp(weapon = me->query_temp("weapon"))
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("sword") != "tangshi-jianfa" )
		return notify_fail("��ʹ���ˡ�����ʽ��ô?\n");
    
	me->set_temp("tangshi/erguang",1);
	j = lvl/3;

	if ( lvl > 349 )
		j = to_int(lvl/3.0 * lvl/200.0);
    //msg = HIY "ֻ��$N���б��������ֿ��ٽ��������֣����������벻���ķ�λ����$n�����ա�\n"NOR;
    message_vision(HIY "ֻ��$N���б��������ֿ��ٽ��������֣����������벻���ķ�λ����$n�����ա�\n"NOR, me, target);
    if (random(me->query("combat_exp")) > target->query("combat_exp")/3
		||random(me->query_skill("sword",1))>target->query_skill("parry",1)/2 )
	 {
        message_vision(CYN"$nֻ��������һ�����������ʹ���ѱ�$N�����Ĵ���һ���⣡\n"NOR, me, target);
		if( !target->is_busy() ) target->start_busy( (int)me->query_skill("tangshi-jianfa") / 100 );
        else target->add_busy( (int)me->query_skill("tangshi-jianfa") / 100 );
		damage = (int)me->query_skill("tangshi-jianfa", 1);
		damage = damage +  (int)me->query_skill("tangshi-jianfa", 1);
		damage = damage +  (int)me->query_skill("sword", 1);
		damage = damage*2+random(damage);
		if (me->query("quest/shenzhao/laozu")) damage = damage + 2*me->query_skill("shenzhao-jing",1);
		if (damage>5000) damage=damage+(damage-5000)/100;
		target->receive_damage("qi", damage/2,me);
		target->receive_damage("jing",random(1000),me);
		target->receive_wound("qi", damage/50,me);
		target->apply_condition("neishang",2);
		me->add("neili", -100);
		//msg = CYN"$nֻ��ֻ��������һ������������ʹ���ѱ�$N�����Ĵ���һ���⣡\n"NOR;		
		target->add_busy(2);
		if (me->query_skill("tangshi-jianfa",1)>450) target->add_busy(1);
        if (me->query("quest/shenzhao/diyun")) target->add_busy(1+random(1));
		if (me->query("quest/shenzhao/laozu")) target->add_busy(2+random(1));
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		//if (me->query_skill("tangshi-jianfa",1)<450) me->start_busy(2);
	} else 
	{
		//msg = CYN"����$p����һ��,�����$P���Ʒ硣\n"NOR;
		message_vision(CYN"����$p����һ��,�����$P���Ʒ硣\n"NOR, me, target);
		me->add("neili", -100);
		me->start_busy(2);
	}
	me->delete_temp("tangshi/erguang");	
	if (me->query_skill("tangshi-jianfa",1)<450)
	{
		me->start_busy(1+random(2));
	}
	me->add("neili", -300);
	me->add("jingli", -100);
	if (!me->query("quest/shenzhao/diyun")) me->start_perform(2, "������ʽ��");
	// �⿪����2�����
	return 1;
	
}

string perform_name(){ return HIR"����ʽ"NOR; }

int help(object me)
{
        write(HIC"\n��ʬ����֮������ʽ����"NOR"\n\n");
        write(@HELP
	����ʬ���������ǽ�ӹʮ�Ĳ����������С����Ǿ����������书
	��Ҫ���ɷ����ɫ�������Ὥ���ݳ������е�һ�ֽ�������Ϊ��
	���˶�Ŀ���ѡ���ʫ����������ﴫΪ����ʬ�����������е���
	����������Ҳ�ĳ�г���ֻ�ͬ�������֣������Ѹý�������С
	˵�����˹����ơ��ɴˣ��Զﴫ��,ʵ�˻�����֮�����
	����ʽ����Դ���Դ�ƽָ�������м�Ϊ�����һ�У����ý���
	Ӱ�죬��Ѹ�ײ����ڶ�֮ʽ��Է�һ�����⣬ʹ�ö�������æ
	��֮�С��⿪���վ��ڶ��κ���д�ɡ�
	
	ָ�perform sword.erguang

Ҫ�󣺡�
	��ǰ���� 1000 ���ϣ�
	������� 3500 ���ϣ�
	��ʬ�����ȼ� 250 ���ϣ�
	���������ȼ� 250 ���ϣ�
	��������Ϊ��ʬ������

HELP
        );
        return 1;
}
