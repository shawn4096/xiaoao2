// ������ - ���컨��
// By River@SJ 

inherit F_SSERVER;
#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int num,p,damage,skill;
        string msg;
        object weapon = me->query_temp("weapon");
        damage = me->query_skill("duoming-jinhua", 1);
		skill = me->query_skill("duoming-jinhua", 1);
        
		if( !target ) target = offensive_target(me);
        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
              return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if((int)me->query_skill("duoming-jinhua", 1) < 250 )
              return notify_fail("��Ķ����𻨲�����죬������ʹ�����컨�ꡣ\n");
        if((int)me->query_skill("shenghuo-shengong", 1) < 250 )
              return notify_fail("���ʥ���񹦵ȼ�����������ʹ�����컨�ꡣ\n");
        if((int)me->query("neili", 1) < 500 
         ||(int)me->query("jingli", 1) < 1200 )
              return notify_fail("��������������������ʩչ���컨��ľ�����\n");
        if( (int)me->query_dex() < 35 )
			  return notify_fail("�����̫�ͣ��޷�ʩչ���컨��ľ�����\n");
        if ( !weapon
         || weapon->query("skill_type") != "throwing"
         || me->query_skill_mapped("throwing") != "duoming-jinhua")
              return notify_fail("�������޷�ʹ�����컨�ꡣ\n");
        num = me->query_skill("duoming-jinhua", 1) / 100;
       
        if ((weapon->query_amount()) < num)
             return notify_fail("�����ϵİ����������޷�ʹ�����컨�ꡣ\n");         
        me->add("neili", -100);
        me->add("jingli", -50);
        if (me->query_skill("duoming-jinhua",1)<300)
        {
			me->start_busy(1);
        }
        msg = HIY"\n$N��߳һ��������ƮƮ��ֻ��"+chinese_number(num)+"����������컨��֮�ƣ�������˷���$n�����ȥ��\n"NOR;
        if(random(me->query("combat_exp")) > (int)target->query("combat_exp")/2
          || (int)me->query_dex(1) > random(target->query_dex(1))){
          weapon->add_amount(-num);
          msg += HIR"ֻ��$n����������ʹ��Ĵ��һ����"+weapon->name()+HIR"��ȫ��������ȫ��ҪѨ��\n"NOR;
          me->add("neili", -200);          
          damage +=me->query_skill("throwing", 1);
          damage = damage *num*me->query_str()/20;
          damage = damage + random(damage);
          if (damage >3000) damage=3000+(damage-3000)/10; //����ʥ�������
          if (me->query("gender") =="Ů��"&&!userp(target)) damage=damage*2;
		  if (damage>target->query("qi"))
		  {
			  damage=target->query("qi");
		  }
		  target->receive_damage("qi", damage,me);
          target->receive_wound("qi", damage/4,me);
          target->start_busy(1+random(2));
          if(!target->is_killing(me->query("id"))) target->kill_ob(me);
          p = (int)target->query("qi")*100/(int)target->query("max_qi");
          msg += "( $n"+eff_status_msg(p)+" )\n";
         }
         else {
          msg += CYN"$n��ͷ����һ������������Ȼ�㿪��"+weapon->name()+CYN"�Ĺ�����\n"NOR;
          weapon->add_amount(-num);
          me->start_busy(1);
          me->add("neili",-100);
         }
         message_vision(msg, me, target);
		 me->add_temp("apply/attack",skill/3);
		 if (me->query("gender")=="Ů��"){
			 me->add_temp("apply/damage",skill/5);
			 me->add_temp("apply/throwing",skill/5);
		 }
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		 me->add_temp("apply/attack",-skill/3);
		 if (me->query("gender")=="Ů��"){
			 me->add_temp("apply/damage",-skill/5);
			 me->add_temp("apply/throwing",-skill/5);
		 }
         me->start_perform(4,"���컨��");
		 me->start_busy(random(1));
         return 1;
}
string perform_name(){ return HIR"�����컨�꡹"NOR; }

int help(object me)
{
	write(YEL"\n������֮"+HIR"�����컨�꡹"NOR"\n\n");
	write(@HELP
	���������ǽ����ţ������������Ķ����书��Ů��
	ʹ���ж�����������һ����Ѥ���ޱȡ�������������
	���ģ������µ�һ���ˣ��ֳֽ𻪣����컨�꣬������
	ΪϬ����Ů�����ô��б����������ơ�300��С��
	ע�⣺���������йأ��˺�������йء�
	
	ָ�perform throwing.huayu

Ҫ��
	��ǰ���� 500 ���ϣ�
	��ǰ���� 1200 ���ϣ�
	ʥ���� 250 ��;
	�����𻨵ȼ� 250 ���ϣ�
	��������Ϊ�����𻨣�
	���ְֳ�����


HELP
        );
        return 1;
}
