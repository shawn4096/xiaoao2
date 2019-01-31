//sanjue.c 
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
  	string msg;
        int i;
        object weapon;
	if( !target ) target = offensive_target(me);
	if( !target || !me->is_fighting(target) )
		return notify_fail("����Ħ��������ֻ����ս���жԶ���ʹ�á�\n");
    weapon = me->query_temp("weapon");
    if(!weapon||weapon->query("skill_type")!="sword")
        return notify_fail("�����ʹ���ڽ�ʱ����ʹ������Ħ����������\n");
    if( (int)me->query_skill("force", 1) < 100 )
		return notify_fail("��Ļ����ڹ�������죬����ʹ�á���Ħ��������\n");
	if( (int)me->query_skill("dodge", 1) < 100 )
		return notify_fail("��Ļ����Ṧ������죬����ʹ�á���Ħ��������\n");
	if( (int)me->query_skill("damo-jian", 1) < 100 )
		return notify_fail("��Ĵ�Ħ����������죬����ʹ�á���Ħ��������\n");
     if(me->query_skill_mapped("sword")!="damo-jian"||me->query_skill_mapped("parry")!="damo-jian")
        return notify_fail("��û�м�����Ħ��������ʹ�á���Ħ��������\n");
	if( (int)me->query_skill("yijin-jing", 1) < 100 )
		return notify_fail("����׽�ڹ���Ϊ����������ʹ�á���Ħ��������\n");
    if( me->query_temp("sl/sanjue"))
		return notify_fail("������ʹ�á���Ħ����������\n");
	if( (int)me->query("max_neili", 1) < 1400 )
		return notify_fail("����������̫��������ʹ�á���Ħ��������\n");
	if( (int)me->query("neili", 1) < 400 )
		return notify_fail("����������̫��������ʹ�á���Ħ��������\n");
    if((int)me->query("jingli",1)< 200)
        return notify_fail("�����ھ���̫�٣�����ʹ�á���Ħ��������\n");
        i = me->query_skill("damo-jian", 1);
        msg = HIY "$N��Хһ��������������Ҷ����裬Ѹ����ɰ㷢������������\n"NOR;
        me->set_temp("sl/sanjue",1);
        if (userp(me) && me->query_skill("damo-jian",1)<350)
        {
          me->add_temp("apply/damage", i/4);
        }
		if (userp(me)&&me->query("class")!="bonze")
		{
          me->add_temp("apply/damage", i/6);
          me->add_temp("apply/attack", i/3);
		}
		me->add_temp("apply/strength", i/6);
        me->add_temp("apply/attack", i); 
  	    message_vision(msg, me, target);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
        if (userp(me)&&me->query("class")!="bonze"&&me->is_fighting())
        {
			message_vision(HIR"$N���޷�������û��ʲô���������������ƣ���$n��Ȼ�翹�����ɵ�ɱ�Ĵ���\n"NOR,me,target);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        }
	    me->add("neili", -200);
        //me->add("jingli",-100);
        me->start_busy(1);
	    me->add_temp("apply/strength",-i/6);
        me->add_temp("apply/attack", -i); 
		if (userp(me)&&me->query_skill("damo-jian",1)<350)
        {
          me->add_temp("apply/damage", -i/4);
        }
		if (userp(me)&&me->query("class")!="bonze")
		{
          me->add_temp("apply/damage", -i/6);
          me->add_temp("apply/attack", -i/3);
		}
		me->delete_temp("sl/sanjue");
        me->start_perform(3,"������");
        message_vision(HIC"$Nһ����Х������������������\n"NOR, me,target);
      return 1;
}
string perform_name(){ return HIC"������"NOR; }
int help(object me)
{
         write(HIC"\n��Ħ����֮������������"NOR"\n");
        write(@HELP
	��Ħ���������Ǵ�Ħ����Ϊ�˳�ħ�������������������������似��
	��Ħ�������ܹ����У�����������Ѹ���ޱȡ������׼��������
	�������ƣ�ɱ�����ڣ�����΢���ơ�350������ԭ�������𽥼�����
	Ҫ��
		�����ڹ���100
		�����Ṧ��100
		��Ħ������100
		�׽����100
		���������1400
		��ǰ������500
		��ǰ������200
		�輤����Ħ����       
HELP
        );
        return 1;
}

