// lianhuan.c for huashan-jianfa
// by tiantian@SJ 11/05/2000.
// update by lsxk@hsbbs 2007/7/26 for��ǿ����ʹ������.

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return MAG"�����������ɽ�"NOR;}

int perform(object me,object target)
{
    object weapon;
    
    if( !target ) target = offensive_target(me);
     
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("�����������ɽ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if(me->query_skill_mapped("force") != "huashan-qigong"
      &&me->query_skill_mapped("force") != "zixia-gong" )
                return notify_fail("��������ڹ����ԣ��޷�ʹ�ö����������ɽ���\n");
    if( (int)me->query_skill("huashan-qigong", 1) < 160
      &&(int)me->query_skill("zixia-gong", 1) < 160 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ�ö����������ɽ���\n");
    if( (int)me->query_skill("huashan-jianfa", 1) < 160 ) 
                return notify_fail("��Ľ�����δ���ɣ�����ʹ�ö����������ɽ���\n");
    if((int)me->query_skill("sword", 1) < 160 )
                return notify_fail("��Ļ�������������죬�����ڽ�����ʹ�ö����������ɽ���\n");
    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("�������޽������ʹ�ö����������ɽ���\n");
                
    if((int)me->query("max_neili") < 2500 )
                return notify_fail("���������Ϊ����������ʹ�ö����������ɽ���\n");
    if((int)me->query("neili") < 2000 )
                return notify_fail("�������������㣬����ʹ�ö����������ɽ���\n");
    if((int)me->query_temp("wudui"))
                return notify_fail("������ʹ����˫�޶ԣ�\n");

        message_vision(MAG"\n$N"MAG"��Хһ����ʹ��ƽ���������������������ǻ�ɽ���ھ�ѧ��"HIR"�����������ɽ�"MAG"����\n"NOR, me,target);

   
    me->set_temp("hsjf/lianhuan",1);
    me->add("neili", -200);
    me->add_temp("apply/attack",  me->query_skill("huashan-jianfa", 1)/4);
	//��ϼ��������450����
    if(me->query("quest/zixia/pass")&& me->query_skill("zixia-gong",1)>449)
   {
        message_vision(HIC"\n$N��������һ��������������ʢ�������ڽ��У������Ϲ���˸��ֱָ$n�ġ�����Ѩ����\n"NOR,me,target);
		target->start_busy(1);
        me->add_temp("apply/armor",  me->query_skill("huashan-jianfa", 1)/3);
		me->add_temp("apply/attack",  me->query_skill("huashan-jianfa", 1)/3);
        me->add_temp("apply/strength",   me->query_skill("huashan-jianfa", 1)/3);
    }
    if(me->query("quest/huashan")=="����")
   {
        target->start_busy(1+ random(2));
        me->add_temp("apply/damage",  me->query_skill("huashan-jianfa", 1)/3);
        me->add_temp("apply/sword",   me->query_skill("huashan-jianfa", 1)/3);
    }
    message_vision(HIC"\n$N�����ڿ�Ծ�𣬽��ⲻס������������������ͷֱ��$n�����š�\n"NOR,me,target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
   	if (me->is_fighting(target))
		message_vision(HIY"\n$N�������������˵��˽��ϣ�����һ������������$n��������\n"NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
   	if (me->is_fighting(target))
	    message_vision(HIR"\n$NȦת�������������ã�����$n�ĺ��ģ���һ�����п켫��$n�������۾���ʵ�����Զ�ܡ�\n"NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        me->add_temp("apply/attack",  -me->query_skill("huashan-jianfa", 1)/4);
     if(me->query("quest/huashan")=="����" && target->is_busy())
     {
        message_vision(HIC"$N�����ھ�����ɽ�������ɽ��İ��ؾ�����͸����$n��æ����֮�ʣ�˳���ƽ������ش�ȥ��\n"NOR,me,target);
        target->receive_damage("qi", me->query_skill("huashan-jianfa", 1),me);
        target->receive_wound("qi", me->query_skill("huashan-jianfa", 1)/2,me);
		target->set_temp("must_be_hit",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		target->delete_temp("must_be_hit",1);
      }
	if(me->query("quest/huashan")=="����")
    {
        me->add_temp("apply/damage", - me->query_skill("huashan-jianfa", 1)/3);
        me->add_temp("apply/sword",    - me->query_skill("huashan-jianfa", 1)/3);
     }
    if(me->query("quest/zixia/pass")&& me->query_skill("zixia-gong",1)>449)
   {
       // message_vision(HIC"$N��������һ��������������ʢ�������ڽ��У������Ϲ���˸��ֱָ$n�ġ�����Ѩ����\n"NOR,me,target);
		//target->start_busy(1);
        me->add_temp("apply/armor",  -me->query_skill("huashan-jianfa", 1)/3);
		me->add_temp("apply/attack",  -me->query_skill("huashan-jianfa", 1)/3);
        me->add_temp("apply/strength",   -me->query_skill("huashan-jianfa", 1)/3);
    }
	
    me->delete_temp("hsjf/lianhuan");
    me->start_busy(1);
	me->start_perform(4,"�������������ɽ���");
    return 1;
}

int help(object me)
{
   write(WHT"\n��ɽ������"MAG"�����������ɽ�"WHT"����"NOR"\n");
   write(@HELP
    ����ǻ�ɽ���ھ����������������ɽ��������껪ɽ�ɽ��ڡ�����֮
    �������ڻ�ɽ��Ů��Ƚ����ᣬ���ڵ����������˴���ɱ����������
    �ں��֣���������ս����Ҳ�����ڵ����ڵ��Ӻ�Ȼ�����ڵ�������
    ���ڵ���Ϊħ����������ȴ�����������֮��������ɽ��Ů��һս��
    ���������ڵ��Ӿ�ȻҲ����ϰ���У���ֻ��ͽ�м��ƣ������˲�����
    �ڵ���֮�����ĳɡ��������⿪��ϼ������������ϼ������ע������
	Ҳ�Բ��ס�

    ָ�perform sword.lianhuan

Ҫ��
	��ɽ���� ���� ��ϼ�� 160��
	��ɽ����Ҫ�� 160 ����
	��������Ҫ�� 160 ����
	�������Ҫ�� 2500 ���ϣ�
	��ǰ����Ҫ�� 2000 ���ϡ�
	��ϰ����ϼ����450�����ٴη�Ծ��
HELP
   );
   return 1;
}
