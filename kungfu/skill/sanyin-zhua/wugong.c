// wugong.c ���ץ
// cre by sohu@xojh

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

void check_fight(object me,object target);
int perform(object me, object target)
{
        string msg;
        int skill;
        skill = (int)me->query_skill("sanyin-zhua", 1)+(int)me->query_skill("huagong-dafa", 1)/4;                

       if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("�����ץ��ֻ����ս���жԶ���ʹ�á�\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("ʹ�á����ץ��ʱ˫�ֱ�����ţ�\n");

        if( (int)me->query_skill("sanyin-zhua", 1) < 350 )
                return notify_fail("����������ץ������죬����ʹ�á����ץ����\n");

        if( (int)me->query_skill("huagong-dafa", 1) < 350 )
                return notify_fail("��Ļ������ڹ��ȼ�����������ʹ�á����ץ����\n");

        if( (int)me->query_dex() < 27 )
                return notify_fail("���������ǿ������ʹ�á����ץ����\n");

        if (me->query_skill_prepared("claw") != "sanyin-zhua"
        || me->query_skill_mapped("claw") != "sanyin-zhua")
                return notify_fail("�������޷�ʹ�á����ץ�����й�����\n");
        if( (int)me->query("max_neili") < 3500 )
                return notify_fail("����������̫��������ʹ�á����ץ����\n");
        if( (int)me->query("neili") < 1500 )
                return notify_fail("����������̫��������ʹ�á����ץ����\n");

        if( target->query_temp("syz/wugong")   )
                return notify_fail(target->name() + "�Ѿ�Ϊ�㡸���ץ�����ˣ��ŵ������ɡ���\n");

// 42          me->start_perform(2,"�������ץ")
        msg = HIC "$N˫���ſ�����Ȼ����һ�֣�˫�ƻ���һƬ��Ӱ�������������������צ���������ץ��\n" NOR;
		msg += HIB "$N���𻯹��󷨣������������ǧ��ǧ�ţ���������֮�ƣ���ʱ���������ץӰ��\n" NOR;
		msg += HBBLU+HIW "$N����������˫צ����䣬�������ֵĴ���Щ��ɫ�ж����塣\n" NOR;

        message_vision(msg, me, target);
        if (random(me->query("combat_exp")) > target->query("combat_exp")/2
			||random(me->query_skill("claw",1))>target->query_skill("parry",1)/3)
		{
          msg = HIY "\n$n����һ�����ŵ���ζǺ�ļ�Ϊ���ܣ�����ͣ�ͣ�$nֻ�������ܶ���$N��ץӰ��ѹ��$n������������\n" NOR;
          message_vision(msg, me, target);
          if (me->query_skill("poison",1)>target->query_skill("poison",1)
			  &&!target->query_condition("xx_poison"))
          {
			  message_vision(HIB"$n��������һ���⣬�漴��ʹ�ޱȣ���Ȼ�Ѿ�Ϊ��������ץ�Ķ���\n"NOR,me,target);
			  target->add_condition("xx_poison",2);
          }
		  if (!userp(target))
		 		  target->add_busy(3);
		  else target->add_busy(1);

		  target->add_temp("apply/attack", -skill/5);
          target->add_temp("apply/dodge", -skill/5);
          target->add_temp("apply/parry", -skill/5); 
          target->set_temp("syz/wugong",skill);   
		  target->apply_condition("no_exert",2);
          me->add("neili", -400);
          me->add("jingli",-150);

		  if (objectp(target))
		      call_out("check_fight",skill/50,me,target);                      
          //return 1;
        }
		else if (objectp(target)&&objectp(me)) 
		{
		        message_vision(HIC"$N��������������ϸ������$n��ץӰ��˳��һ��һ��������������ץӰ��\n"NOR,target,me);
				me->add_busy(1);
        }

		if (me->query_skill("sanyin-zhua",1)<450)
        {
			me->start_busy(1);
			me->start_perform(2,"�����ץ��");
        }
        me->add("neili", -100);
        me->add("jingli", -100);
        return 1;
}

void check_fight(object me, object target) 
{ 
       
	   int skill;
	   
       if (!objectp(target)) return;
	   skill=target->query_temp("syz/wugong");
       if(target->query_temp("syz/wugong") )
	   {

        target->add_temp("apply/attack", skill/5);
        target->add_temp("apply/dodge", skill/5);
        target->add_temp("apply/parry", skill/5);
        target->delete_temp("syz/wugong");
        tell_object(target, HIB"�����һ�����������������ץ�ĸ���Ӱ�죬״̬�ָֻ��糣��\n"NOR);
       }
	   return;
}

string perform_name(){ return HIY"���ץ"NOR; }
int help(object me)
{
        write(HIB"\n�������ץ֮�����ץ����"NOR"\n");
        write(@HELP
	�������ץΪ�����ɾ�����Դ��ģ��������̬����
	һ�мȳ��������ݻ���һ�ֶ�����Ϊ�ģ��ĳɰˣ���
	����Ϊ���ǧ��ǧ�ŵ���̬�����ץ��Ҫ�����ǿ죬
	�Կ��ٵ���ʽѹ�ƶԷ���ʹ�Է��ķ����ܵ�ѹ�ƣ���
	����Ϊ����ץ�书���ɶ������ǣ����Է�����ˮ׼
	�Ƚϵͣ�������˳������������޶���
	ע�⣺�����ץ���������Ĺ�Ч�ǽ��ͶԷ��Ĺ�����

	ָ�perform claw.wugong

Ҫ��  
	������������� 3500 ���ϣ�      
	��ǰ���������� 1500  ���ϣ�  
	�������ץ�ȼ� 350 ���ϣ�
	�����󷨵ĵȼ� 350 ���ϣ�
	����ץ��Ϊ�������ץ��
	�����м�Ϊ�������ץ��
	�����ޱ���,450���Ծ��
	���ͳ����ƻ��������⹦Ч��
                
HELP
        );
        return 1;
}

