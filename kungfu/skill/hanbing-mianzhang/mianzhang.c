// Created by Numa 2000.1.25
// Modified by darken@SJ

#include <ansi.h>
#include <combat.h> 
#include "/kungfu/skill/eff_msg.h"
inherit F_SSERVER;

string perform_name() {return HIY"�������ᾢ"NOR;}

int perform(object me,object target)
{
        int damage,skill, p, win;
        int tmp;
        string msg;
         win=0;
        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) 
         || !living(target))
                return notify_fail("�������ơ����ᾢ������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if (me->query_temp("weapon"))
                return notify_fail("�������ơ����ᾢ������ֻ�ܿ���ʹ�ã�\n");

        if( (int)me->query_skill("hanbing-mianzhang", 1) < 250 )
                return notify_fail("��ĺ������ƻ�򲻹���\n");
 
        if( (int)me->query_skill("parry", 1) < 250 )
                return notify_fail("��Ļ����мܻ�򲻹���\n");
        if( (int)me->query_skill("dodge", 1) < 250 )
                return notify_fail("��Ļ����Ṧ��򲻹���\n");
        if( (int)me->query_skill("shenghuo-shengong", 1) < 250 )
                return notify_fail("���ʥ���񹦻�򲻹���\n");
                
        if( (int)me->query("max_neili") < 3500 )
                return notify_fail("���������Ϊ������\n");

        if( (int)me->query("neili") < 800 )
                return notify_fail("�������������\n");

        if( (int)me->query("jingli") < 500 )
                return notify_fail("��ľ���������\n");        

        if (me->query_skill_prepared("strike") != "hanbing-mianzhang"
         || me->query_skill_mapped("strike") != "hanbing-mianzhang")
                return notify_fail("�������޷�ʹ�ú������ơ�\n");
       
        if( me->query_temp("hbmz/yinrou"))
               return notify_fail("������ʹ�ú����������ᾢ������\n");
 
        me->add("neili", -200);
        me->add("jingli", -50);
        message_vision(HIR "\n$N��Ȼ�����੹�Ц���������Ѹ�ݵ������ߣ���Ȼ����˫�Ƴ�����״����$n������Ҫ����\n" NOR,me, target);
		skill = me->query_skill("hanbing-mianzhang",1);     
       // me->add_temp("apply/attack", skill/3);
       // me->add_temp("apply/damage", skill/5);
      //  me->add_temp("apply/strike", skill/5);
		me->set_temp("hbmz/yinrou",skill);
	    me->add_temp("apply/attack", skill/3);               
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
		me->add_temp("apply/attack", -skill/3);    

        msg = HIB "\n$N������ǰ���ƣ����������������鰴������������ȴ�������壬һ�ɺ���ֱ��$n��ȥ��\n" NOR;
        if (random(me->query("combat_exp")) > target->query("combat_exp")/2
			||random(me->query_dex(1)) > target->query_dex(1)/2 ){
                msg += HIC"$n��Ҫ���ܣ�ֻ��һ�ɺ���Ϯ����������ʱ��������˸������\n"NOR;
                damage = (int)me->query_skill("force") + (int)me->query_skill("hanbing-mianzhang")*2;
				damage=damage*me->query_dex(1)/10; //��Ҫ�����������书�ص�
                damage = damage+random(damage);
                if (damage > 4000) damage = 4000 + (damage - 4000)/100;
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/4,me);
				target->apply_condition("hb_poison",1);
				target->start_busy(1+random(2));
                me->add("neili", -200);
                me->add("jingli", -50);
                if (wizardp(me)) tell_object(me,HIW"damage��"+damage + "��\n"NOR);
                p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
                msg += damage_msg(damage, "����");
                msg += "( $n" + eff_status_msg(p) + " )\n";
				
				win=1;
        }
        else{ 
                msg += BLU"$n�������Ắ�����������ϣ���ʱ��ȫ��������ƺ�ѪҺ��Ҫ��������һ�㡣\n"NOR;
                win = 0;
        }
        message_vision(msg, me, target);
	
     //�ڶ���
	  if (win == 1){  
          msg =HIW"����$n�������֮�ʣ�$N����������Ʒ�����Ȼ�ĵ���\n"NOR;
           if (random(me->query("combat_exp")) > target->query("combat_exp")/2
			  ||random(me->query_skill("strike",1)) > target->query_skill("parry",1)/2
		    ){
              msg += HIR"$n��֪����������ܣ�ȴ������������㣬��һ�ƽ��ʵʵ����$n��ǰ�أ�\n"NOR;
              damage=damage*me->query_str(1)/10;
			  damage=damage+random(damage);
             // if(!userp(me)&&damage > 6000) damage = 6000 + (damage - 6000)/100;
			 if(damage > 5000) damage = 5000 + (damage - 5000)/100;
              me->add("neili", -200);
              me->add("jingli", -50);
              target->receive_damage("qi", damage,me);
              target->receive_wound("qi", damage/3,me);
              if (wizardp(me)) tell_object(me,HIW"damage��"+damage + "��\n"NOR);
              p = (int)target->query("qi") * 100 / (int)target->query("max_qi"); 
              msg += damage_msg(damage, "����");
              msg += "( $n" + eff_status_msg(p) + " )\n";
			  me->add_temp("apply/attack", skill/3);
			  me->add_temp("apply/damage", skill/5);
			  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
			  me->add_temp("apply/attack", -skill/3);
			  me->add_temp("apply/damage", -skill/5);
           }
           else {
              msg +=HIY "$n����������������ϣ������ޱȣ�����ȫ������ľ���ʹ����ǡ�\n"NOR;
           }
           message_vision(msg, me, target); 
		  // COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        }
       
        me->start_perform(4,"�������ᾢ");
		me->delete_temp("hbmz/yinrou");
        me->start_busy(1+random(1));
        target->add_busy(1+random(2));
        return 1;
}

int help(object me)
{
        write(HIC"\n��������֮��"+HIY"�������ᾢ"NOR"��\n\n");
        write(@HELP
	�����������ᾢ�����������������似���������У�һ��һ��
	½��ʹ���������ޱȡ����������书ȫƾ�ṦƮ�ݺ��Ʒ�����
	���ԣ����������Ʒ���Ҫ��ϸߡ�����ڳ��Դ���ʱ��ע�⡣
	
	ָ�perform strike.mianzhang

Ҫ��
	��ǰ���� 800  ���ϣ�
	��ǰ���� 500  ���ϣ�
	������� 3500 ���ϣ�
	�������Ƶȼ� 250 ���ϣ�
	ʥ���񹦵ȼ� 250 ���ϣ�
	�����Ṧ�ȼ� 250 ���ϣ�
	�����Ʒ�Ϊ�������ƣ�
	�����м�Ϊ�������ƻ�Ǭ����Ų�ơ�

HELP
        );
        return 1;
}
