//cijian.c
//by spiderii@ty����SJ��д

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
	int j, lvl = me->query_skill("tangshi-jianfa", 1);
    if (me->query_skill("shenzhao-jing",1)>349)
       lvl = me->query_skill("tangshi-jianfa", 1)+me->query_skill("shenzhao-jing", 1)/2;
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("���̼�ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	
    if( (int)me->query_skill("tangshi-jianfa", 1) < 180 ) 
                return notify_fail("�����ʬ������δ���ɣ��޷�ʹ�á��̼硹�־���\n");

    if((int)me->query_skill("sword", 1) < 180 )
                return notify_fail("��Ļ�������������죬����ʹ�á��̼硹�־���\n");

    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "tangshi-jianfa")
                return notify_fail("�����ʹ�ý���������ʹ�����̼硹�־�!\n");

  // if(me->query_skill_mapped("parry") != "tangshi-jianfa")
    //       return notify_fail("���̼硹�־���Ҫʹ����ʬ�����м�һ�ез�������\n"); 

   if((int)me->query("max_neili") < 3000 )
           return notify_fail("��������Ϊ��ǳ��ʹ�������̼硹�־���\n");  

   if( (int)me->query("neili") < 1000 )
           return notify_fail("����������̫����ʹ�������̼硹�־���\n");
	
   message_vision(HIY"\n$N�������������磬�Ҽ磬��磬�Ҽ�...��,����Ʈ������$n˫�緽λ������˸��\n"NOR, me,target);
  
   j=lvl+random(lvl);
   if (me->query("quest/shenzhao/diyun") && me->query_temp("szj_power"))
	{
     message_vision(HIM"\n$N���մӵ��ƴ���������վ�Ҫ�죬���õ���ʬ����֮�ϣ�����������\n"NOR, me,target);
	 j=lvl+2*lvl;
	}
   if (!userp(me)) j=lvl/3;
     damage=j;
  
   if (random(me->query("combat_exp")) > target->query("combat_exp")/3 )
	{
        		   
		   target->receive_damage("qi",j,me);
		   target->receive_wound("qi", j/2,me);
		   target->receive_damage("jing", j/10,me);
		   me->add("neili", -100);
		message_vision(HIR"$nֻ��"+random(2)?HIG"���"NOR:HIY"�Ҽ�"NOR+HIR"һ����Ҵ�ʹ����Ѫ�ɽ������β��ɵ�Ϊ֮һ����\n"NOR,me,target);  
		if( !target->is_busy()&& !random(2) ) target->start_busy(2);
        if (me->query("quest/shenzhao/laozu"))
        {
			target->apply_condition("no_perform",1);
        }
		//message_vision(msg, me, target);
   	    me->set_temp("tangshi/cijian",3);
        me->add_temp("apply/attack", j);
        me->add_temp("apply/damage", j);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		//COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        me->add_temp("apply/attack", -j);
	    me->add_temp("apply/damage", -j);
	} else 
	{
		//msg = CYN"����$n����һ��,�����$N�Ĺ�����\n"NOR;
		message_vision(CYN"����$n����һ��,�����$N�Ĺ�����\n"NOR, me, target);
		me->add("neili", -100);
		me->start_busy(3);
	}
	
    me->delete_temp("tangshi/cijian");
	me->start_busy(random(2));
	me->add("neili", -300);
	me->add("jingli", -100);
	me->start_perform(2, "���̼�ʽ��");
	return 1;
}

string perform_name(){ return HIW"�̼�ʽ"NOR; }

int help(object me)
{
        write(HIC"\n��ʬ����֮���̼�ʽ����"NOR"\n\n");
        write(@HELP
	����ʬ���������ǽ�ӹʮ�Ĳ����������С����Ǿ����������书
	��Ҫ���ɷ����ɫ�������Ὥ���ݳ������е�һ�ֽ�������Ϊ��
	���˶�Ŀ���ѡ���ʫ����������ﴫΪ����ʬ�����������е���
	����������Ҳ�ĳ�г���ֻ�ͬ�������֣������Ѹý�������С
	˵�����˹����ơ��ɴˣ��Զﴫ��,ʵ�˻�����֮�����
	�̼�ʽ����Դ���Դ�ƽָ�������м�Ϊ�����һ�У����ý���
	Ӱ�죬��Ѹ�ײ����ڶ�֮ʽ���жԷ��ļ粿���ԶԷ��γ�ǿ��
	ɱ�ˡ��⿪���վ��ڶ��κ���д�ɡ�
	
	ָ�perform sword.cijian

Ҫ�󣺡�
	��ǰ���� 3000 ���ϣ�
	������� 1000 ���ϣ�
	��ʬ�����ȼ� 180 ���ϣ�
	���������ȼ� 180 ���ϣ�
	�����м�Ϊ��ʬ������

HELP
        );
        return 1;
}
