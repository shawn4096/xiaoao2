// ningxue.c  ��Ѫ��צ֮����Ѫ����
// Create By lsxk@hsbbs 2007/5/13 
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string *xue_name = ({"��׶Ѩ","�ٻ�Ѩ","־��Ѩ","�羮Ѩ","�͹�Ѩ","�ڹ�Ѩ","���Ѩ","����Ѩ",
                     "����Ѩ","����Ѩ","����Ѩ","�׺�Ѩ","��̨Ѩ","�縮Ѩ","���Ѩ","����Ѩ",
                     "����Ѩ","����Ѩ","˿����Ѩ","����Ѩ","����Ѩ","��׵Ѩ","����Ѩ","����Ѩ", });

string perform_name() {return RED"��Ѫ��"NOR;}
int remove_effect(object me,int count);

 int perform(object me, object target)
 {
         int j;
         string msg,xuedao;
         j = me->query_skill("ningxue-shenzhua", 1);

         if( !target ) target = offensive_target(me);

         if( !target 
           || !me->is_fighting(target)
           || !living(target)
           || environment(target)!= environment(me))
                 return notify_fail("����Ѫ����ֻ����ս���жԶ���ʹ�á�\n");

         if( objectp(me->query_temp("weapon")) )
                 return notify_fail("�������ֲ���ʹ�á���Ѫ������\n");

         if( (int)me->query_skill("ningxue-shenzhua", 1) < 150 )
                 return notify_fail("�����Ѫ��צ������죬ʹ��������Ѫ����������\n");

         if( (int)me->query_skill("force", 1) < 200 )
                 return notify_fail("������ڹ�������ʹ��������Ѫ����������\n");

         if( (int)me->query_dex() < 30 )
                return notify_fail("���������㣬�޷�ʹ�á���Ѫ��������!\n");

         if (me->query_skill_prepared("claw") != "ningxue-shenzhua"
          || me->query_skill_mapped("claw") != "ningxue-shenzhua"
          || me->query_skill_mapped("parry") != "ningxue-shenzhua")
                 return notify_fail("��Ҫȫ��������Ѫ��צ�������ʹ������Ѫ����������\n");

         if( (int)me->query("max_neili") < 2000)
                 return notify_fail("��������Ϊ̫��޷�ʹ�á���Ѫ����������\n");

         if( (int)me->query("neili") < 1500 )
                 return notify_fail("����������̫�����޷�ʹ�á���Ѫ����������\n");
         if( me->query_temp("nxsz/ningxue"))
                 return notify_fail("����������ʹ�á���Ѫ����������\n");

        // if( (int)me->query("combat_exp",1)*2/3 > (int)target->query("combat_exp",1) && userp(target))
          //       return notify_fail("����������ã���ȴ��˱��꣬�������ã����á�����������\n");

         xuedao = xue_name[random(sizeof(xue_name))];

        message_vision(HBWHT+HIR"$N������Ѫ����ȫ��������ת��������$N˫��,������ɫ�ɰױ����ת���Σ�ð��һ����������\n"NOR,me);
		message_vision(HIR "\n$N�����ƻ���̧��������Ϣ֮�ʣ�������$n�ġ�"+HIY+xuedao+HIR+"��ץ��ȥ��\n"NOR,me,target);
		
		me->add_temp("apply/attack",j/3);
		me->add_temp("apply/damage",j/4);
		me->add_temp("apply/claw",j/4);
		me->set_temp("nxsz/ningxue",j);
		call_out("remove_effect",1,me,j/20);


        if (random(j) > (int)target->query_skill("parry",1)/3
			||random(me->query("combat_exp"))>target->query("combat_exp")/2)
		{
             message_vision(HIR"�ۿ�$N��ץ����$n�Ѿ����֮ң��$n�޷���ܣ���"+HIY+xuedao+HIR+"������ץ�����š�\n"NOR,me,target);
                 
                   target->receive_wound("qi",j*3,me);
                  target->receive_damage("qi",j*6,me);
                  target->apply_condition("nxsz_hurt",j/8);
				  target->add_busy(2);
                 // message_vision(msg, me, target);
                  COMBAT_D->report_status(target);

         } else {
             message_vision(CYN"\n$n���з�����һ�����ӷ��������$N��ץ�磬��$N�������飬��ǰ��֮�ƣ���$n����������\n"NOR,me,target);
                // message_vision(msg, me, target);
                 me->set_temp("nxsz_pfm",1);
                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                 me->delete_temp("nxsz_pfm");
         }               

         me->add("neili", -500);
        // me->start_busy(2+random(2));
         
       //  me->start_perform(2+random(4),"����Ѫ����");
         return 1;
 }
 


int remove_effect(object me,int count)
{
	int j;
	if (!me) return 0;
	j=me->query_temp("nxsz/ningxue");
	
	if (count<0
		||!me->is_fighting()
		||me->query_skill_mapped("claw")!="ningxue-shenzhua"
		||me->query_skill_prepared("claw")!="ningxue-shenzhua")
	{

		me->add_temp("apply/attack",-j/3);
		me->add_temp("apply/damage",-j/4);
		me->add_temp("apply/claw",-j/4);
		me->delete_temp("nxsz/ningxue");
		message_vision(HBWHT+HIR"$N˫����Ѫ��һ�ɣ�˫��˲���ɺ�ת��Ϊɷ�ף�\n"NOR,me);
		return 1;
	}
	call_out("remove_effect",1,me,count--);
}

int help(object me)
{
   write(WHT"\n��Ѫ��צ��"RED"��Ѫ��"WHT"����"NOR"\n");
   write(@HELP
	����Ѫ��צ������ػ��ܶ����½��������ĳ������ա������У�
	���д���צ֮�ˣ������ȫ��ѪҺ�����������ɽ���һ�㣬��ҩ
	���Ρ���Ѫ�����Ĺ�Ч������������Ѫ��צ�Ĺ������������ö�
	���ܰ��ˡ�
	
	ָ�perform claw.ningxue

Ҫ��
	��ǰ���� 1500 ���ϣ�
	������� 2000 ���ϣ� 
	������ 30 ���ϣ� 
	��Ѫ��צ�ȼ� 150 ���ϣ�
	��Ч�ڹ��ȼ� 200 ���ϣ�
	����צ��Ϊ��Ѫ��צ��
	�����м�Ϊ��Ѫ��צ��
	��צ�������ޱ�����

HELP
   );
   return 1;
}
