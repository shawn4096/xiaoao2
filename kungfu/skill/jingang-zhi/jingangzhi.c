// jingangzhi.c ���ָ�� by sohu@xojh 2014.1 

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp,skill,j;
        int damage;

        skill=me->query_skill("jingang-zhi",1);
   //     if (userp(me) && ! me->query("sl/jgz/pass"))
               // return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ�����ָ������\n");
                        
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("�����ָ����ֻ����ս���жԶ���ʹ�á�\n");

        if (me->query_temp("weapon") ||
            me->query_temp("secondary_weapon"))
                return notify_fail("�������ֲ���ʹ�á����ָ������\n");
        if (me->query_skill("force",1) < 450)
               return notify_fail("��Ļ����ڹ���Ϊ����������ʹ����һ������\n");
		if (me->query_temp("jgz/nie"))
                return notify_fail("������ʹ�ý��ָ�����־�����һ������\n");
		if (me->query_skill("finger",1) < 450)
                return notify_fail("��Ļ���ָ����Ϊ����������ʹ����һ������\n");
        if (me->query_skill("force",1) < 450)
                return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");
        if (me->query("max_neili") < 9000)
                return notify_fail("��������������Ϊ����������ʹ����һ������\n");
		if (me->query("neili") < 3000)
                return notify_fail("��ĵ�ǰ��������Ϊ����������ʹ����һ������\n");
        if (me->query_skill("jingang-zhi", 1) < 450)
                return notify_fail("��Ĵ������ָ��Ϊ������Ŀǰ����ʹ�á����ָ������\n");

        if (me->query("jingli") < 1000)
                return notify_fail("��������������޷�ʹ�á����ָ������\n");
        if (me->query_skill_mapped("finger") != "jingang-zhi"||me->query_skill_prepared("finger") != "jingang-zhi")
                return notify_fail("��û�м����������ָ������ʹ�á����ָ������\n");
        me->set_temp("jgz/nie",3);
		message_vision(HBRED+HIY"\nֻ��$N"HIY"ʹ���������ָ�����־����������ָ�������У�����ָ��$n����֫!\n"NOR,me, target);

	    if (me->query("class")!="bone")
	      j = to_int(skill/3.0 * skill/250.0); //200����Ծһ��
        else j=to_int(skill/5.0 * skill/250.0);
	    me->add_temp("apply/attack", j/2);
	    me->add_temp("apply/finger", j/2);
	    me->add_temp("apply/damage", j/3);

	   ap = me->query("combat_exp", 1) / 1000 * me->query_skill("finger",1);
	   dp = target->query("combat_exp", 1) / 1000 * target->query_skill("parry",1);
      
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);

	   if( random(ap + dp ) > dp) {
		 message_vision(HIR"���$Nһ�е��֣�$n�������Ȼ��$N���˸����ţ�\n"NOR,me, target);
         message_vision(HIW"����$nһ���ҽд�����ͬʱ����һ��������ѵ���������Ȼ�Ѿ�Ϊ$N�������ָ��������ϣ�\n"NOR,me, target);
		 target->set_temp("must_be_hit", 1);
		 //target->receive_damage();
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		 target->delete_temp("must_be_hit");
         target->apply_condition("broken_arm",1+random(3)); 
		 me->add("neili", -300);
	   }
	   me->add_temp("apply/attack", -j/2);
	   me->add_temp("apply/finger", -j/2);
	   me->add_temp("apply/damage",-j/3);
	   me->add("neili", -400);
	   me->add("jingli", -150);
	   me->delete_temp("jgz/nie");
	   me->start_perform(4,"�����ָ����");
	   me->start_busy(1+random(2));
	   return 1;
}
string perform_name(){ return HIY"���ָ��"NOR; }

int help(object me)
{
        write(HIG"\n�������ָ֮"+HIY"�����ָ������"NOR"\n\n");
        write(@HELP
	�������ָ�������־���������ŵ���ʦ�����������������һ��������
	�ջ�Ļ�ͷ�ӣ����ƹ����������ɮ�������Ǳ��꣬�ʳ�����Ź����
	��䱻���������������Ѫ�������ѧ�䱨���������й���֮�ǣ�������
	��ʮ�����͵ѧ�ɼ��ϳ˵��书���������Լ����书��ʤ������ɮ�ڣ���
	��һ��һ�ȵ������Ħ�ô�У�з��ѡ����ڴ�У�Ͻ����ش���Ħ�þŴ��
	�ӣ��������Ħ������������ʦ����ʱ�û���������������ڵ���Ǳ����
	�н�������к��Լ��й����ڵ���λɮ��һһʹ���ִ����������������
	���������һ�ɡ��������ָ��Ϊ����������似��
	��������ͷ�ӵ������䵱ɽ���Դ˾�����ս���޼ɣ�ͬʱ��֪��λ����
	�����ô˾����Ϳ��Դ�ʦ��ץ���Կ��ƿ죬���˿��Դ�ʦ����ץ�ֲ�ɱ��
	���Դ�ʦ���ɼ����书������֮����
	���־���Ҫ����ͨ����ʹ���ָ�������Է��ֱۻ������ϣ��Ӷ���ɶ�
	�����˶�����ʧЧ״̬�������׼������ơ�

ָ��:perform finger.jingang

Ҫ��
	��ǰ���� 3000 ���ϣ�
	������� 9000 ���ϣ�
	��ǰ���� 1000 ���ϣ�
	���ָ�ȼ� 400 ���ϣ�
	�׽�ȼ� 400 ���ϣ�
	����ָ���ȼ� 400 ���ϣ�
	�����ڹ��ȼ� 400 ���ϣ�
	����ָ���ұ�Ϊ���ָ��
	�����ڹ������ơ�
HELP
        );
        return 1;
}