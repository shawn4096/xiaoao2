// luomu.c �ޱ���ľ Create By lsxk@hsbbs 2007/7/25
/* �ǵ�ȥ�����£�ʦ������ѩ���裬�������ߣ��ۼ���һ�ڵ��ӽ�
   �۽��������ʩչ�����С��ޱ���ľ��������������һ������һ
   ����ÿһ���������˰����Ʈ������һ��ѩ������ʦ�ﶼ���ƺ�
   �ʣ�˵������ʦ�磬��һ���ҿɷ����ˣ���ɽ��ȷ������������
   �ˡ���
*/

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return HIC"�ޱ���ľ"NOR;}

int perform(object me,object target)
{
    object weapon;
    int lvl,i=me->query_skill("huashan-jianfa",1);
	lvl=i;
	/*if (me->query("quest/huashan") != "����") 
		return notify_fail("�㲻�ǻ�ɽ���ڵ��ӣ�����õ����⻪ɽ������\n");*/
	if (me->query("quest/huashan")=="����")
	   lvl=i+me->query_skill("force",1)/5;
    if( !target ) target = offensive_target(me);
     
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("���ޱ���ľ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if(me->query_skill_mapped("force") != "zixia-gong"
	&&me->query_skill_mapped("force") != "huashan-qigong")
                return notify_fail("����ڹ������޷�ʹ�á��ޱ���ľ����\n");

    if( (int)me->query_skill("zixia-gong", 1) < 500
	&&(int)me->query_skill("huashan-qigong", 1) < 500 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ�á��ޱ���ľ����\n");

    if((int)me->query_skill("force", 1) < 500 )
                return notify_fail("��Ļ����ڹ�������죬�޷�֧�֡��ޱ���ľ����\n");

    if( (int)me->query_skill("huashan-jianfa", 1) < 500 ) 
                return notify_fail("��Ľ�����δ���ɣ�����ʹ�á��ޱ���ľ����\n");

    if( (int)me->query_skill("huashan-shenfa", 1) < 500 ) 
                return notify_fail("��Ļ�ɽ����δ���ɣ�����ʹ�á��ޱ���ľ����\n");

    if((int)me->query_skill("sword", 1) < 500 )
                return notify_fail("��Ļ�������������죬�����ڽ�����ʹ�á��ޱ���ľ����\n");

    if((int)me->query_skill("dodge", 1) < 500 )
                return notify_fail("��Ļ����Ṧ������죬����ʹ�á��ޱ���ľ����\n");

    if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "huashan-jianfa"
        || me->query_skill_mapped("parry") != "huashan-jianfa")
                return notify_fail("�������޽������ʹ�á��ޱ���ľ����\n");
                
    if((int)me->query("max_neili") < 15000 )
                return notify_fail("���������Ϊ����������ʹ�á��ޱ���ľ����\n");

    if((int)me->query("neili") < 2000 )
                return notify_fail("�������������㣬����ʹ�á��ޱ���ľ����\n");

    if((int)me->query("jingli") < 1000 )
                return notify_fail("������̫���ˣ�����ʹ�á��ޱ���ľ����\n");

    message_vision(HBMAG"\n$N��Хһ��,��ʹ�����ޱ���ľ������!����$Nһ������һ����ÿһ�����ڰ���м���һ��������,�����¼���\n"NOR, me,target);
    if (me->query_temp("zxg/jianyi"))
    {
      message_vision(HIY"$N����߶�֮�£����ޱ���ľ�ľ��������˵ǧ�ٿ���ľ�ϵ�Ҷ�ӷ׷�Ʈ�䣬����˷��Ķ����֡�\n"NOR,me);
    }
    me->add("neili", -800);
    me->add("jingli",-500);
    me->set_temp("hsjf/luomu",1);
    
    
    if (me->query("quest/huashan")=="����")
    {
		me->add_temp("apply/attack", lvl/3);
		me->add_temp("apply/sword",lvl/5);
		me->add_temp("apply/damage",lvl/5);
		message_vision(HIR"$N����ʱ������ᵽ������������������,���С��ޱ���ľ����$N����ʩչ������Ȼ������������\n"NOR, me);
		//me->start_perform(3,"���ޱ���ľ��");
    }
	else {
		me->add_temp("apply/attack", lvl/4);
		//me->start_perform(5,"���ޱ���ľ��");
	}
    if(me->query_temp("zxg/zixia")){
        message_vision(HIM"$N������ϼ�񹦷��ӵ����쾡��,����"NOR+weapon->query("name")+HIM"�������������ˡ�֮����\n"NOR, me);
        me->add_temp("apply/damage", (int)me->query_skill("zixia-gong",1)/4);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(1)?3:1);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        target->set_temp("must_be_hit",1);

    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		target->delete_temp("must_be_hit");
        me->add_temp("apply/damage", -(int)me->query_skill("zixia-gong",1)/4);
    }
    else{
	    me->add_temp("apply/damage", (int)me->query_skill("huashan-jianfa",1)/5);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),i>550?3:1);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),i>450?3:1);
    	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),i>450?3:1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	    me->add_temp("apply/damage", -(int)me->query_skill("huashan-jianfa",1)/5);
    }

    if (me->query("quest/huashan")=="����")
    {		
		me->add_temp("apply/attack", -lvl/3);
		me->add_temp("apply/sword",-lvl/5);
		me->add_temp("apply/damage",-lvl/5);
		//me->start_perform(3,"���ޱ���ľ��");
    }
	else {
     me->add_temp("apply/attack", -lvl/4);
	}
    me->delete_temp("hsjf/luomu");
    me->start_busy(1);
    //target->start_busy(1);
	me->start_perform(5,"���ޱ���ľ��");

    return 1;
}

int help(object me)
{
   write(WHT"\n��ɽ������"HIC"�ޱ���ľ"WHT"����"NOR"\n");
   write(@HELP
	���������˸�����������ɽ�����������ɡ����������ơ�����
	���ޱ���ľ�����ǻ�ɽ�������裬�Ǿ�ͨ��ɽ�������޷�ʹ�ã�����
	һ��ʹ����������һ������һ����˲������ֻ������������޴�Ľ�
	�У���������ϼ����ϣ����������л������������������������
	�ߣ�����250,350,450�������ɲ�ͬ�̶ȵķ�Ծ�������ھ�����
    
	ָ�perform sword.luomu

Ҫ��
	��ɽ����������ϼ��500��,��ϼ���ж����Ծ�����������ơ�
	��ɽ���� 500 ����
	��ɽ�� 500 ����
	�����ڹ� 500 ����
	�������� 500 ����
	�����Ṧ 500 ����
	��ǰ���� 2000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	������� 15000 ���ϣ�

HELP
   );
   return 1;
}

