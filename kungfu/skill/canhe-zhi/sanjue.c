//����ָ cre by sohu@xojh
//��һ�� ���ָ��
//�ڶ��� ����Ҷָ
//������ �黨ָ

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int next1(object me, object target, int i);
int next2(object me, object target, int i);

int perform(object me,object target)
{
        object weapon;
        string msg;
        int ap,dp;
        int i = me->query_skill("finger",1) / 2 + me->query_skill("canhe-zhi",1) /2 ;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("������ָ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("force") != "shenyuan-gong")
                return notify_fail("����ڹ��������칦���޷�ʹ�á�����ָ����\n");

        if(!me->query("quest/mr/canhe/sanjue/pass"))
                return notify_fail("����Ȼ��˵��������ָ������������һֱû���������о��ϣ����������ã�\n");

        if( me->query_skill("shenyuan-gong", 1) < 500 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ�á�����ָ����\n");

        if( me->query_skill("canhe-zhi", 1) < 500 )
                return notify_fail("���ָ����δ���ɣ�����ʹ�á�����ָ����\n");

        if (me->query_temp("weapon"))
                return notify_fail("���������������޷�ʹ�á�����ָ����\n");
   
        if (me->query_skill_prepared("finger") != "canhe-zhi"
            || me->query_skill_mapped("finger") != "canhe-zhi")
                return notify_fail("��û�м�����ʹ�òκ�ָ���������޷�ʹ�á�������ָ�������й�����\n");  

        if(me->query_skill_mapped("parry") != "canhe-zhi"
        && me->query_skill_mapped("parry") != "douzhuan-xingyi")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ�á�����ָ����\n");

        if(me->query("max_neili") < 3500 )
                return notify_fail("���������Ϊ����������ʹ�á�����ָ����\n");
        if(me->query("neili") < 1000 )
                return notify_fail("�������������㣬����ʹ�á�����ָ����\n");
        if(me->query("jingli") < 600 )
                return notify_fail("�����ھ������㣬����ʹ�á�����ָ����\n");
        if(me->query_temp("chz/sanjue"))
                return notify_fail("������ʹ�á�����ָ����\n");

        if(me->query_skill("finger", 1) < 500 )
                return notify_fail("��Ļ���ָ��������죬�����ڽ�����ʹ�á�����ָ����\n");


        msg = HBRED"\n$Nʹ��Ľ���ϼҴ��似�κ�ָ������ʩչ�����в�ָͬ�����������Բ�ͬ�����ǲκ�ָ����������ָ����\n"NOR;
		msg+=HIR"$N��ƫ���У�ָ̧��̣����������¡��͡���һ�����������־���"+HIW+"�����ָ��"+HIR+"����\n"NOR;
              message_vision(msg, me, target);
		
        me->start_perform(3, "������ָ��");
        
		me->add_temp("apply/attack", me->query_skill("canhe-zhi") /4);

		me->add_temp("apply/damage", me->query_skill("canhe-zhi") /4);
        me->set_temp("chz/sanjue", 1);
             
        //��һ�й������ָ
        if (me->is_fighting(target))
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("canhe-zhi") /4);
		
me->add_temp("apply/damage", -me->query_skill("canhe-zhi") /4);

        me->add("neili", -150);

        if ( me->query_skill("canhe-zhi", 1) > 500)
                next1(me, target, i);
        else 
                me->delete_temp("chz/sanjue");
        return 1;
}

int next1(object me, object target, int i)

{
        string msg;
        int damage, ap,dp;
        object weapon;

        if (!me) return 0;

        weapon = me->query_temp("weapon");
        if (weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("chz/sanjue");
                return 0;
        }
        msg = HIR"\n������$N˫�ֺ�ʮ��΢΢һЦ���ĵ��黨֮�⣬����һָ��һ��������������Ϯ��$n��ǰ��\n"NOR;
		msg+=HIC"����������ʮ�������м�Ϊ����Ĺ���"+HIR+"���黨ָ����\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_con(1)/100000;
        dp = target->query("combat_exp", 1) * target->query_con(1)/100000;
        
		if((userp(target)&& random(ap + dp) > dp )|| !userp(target)){
                msg += HIB"$nֻ��һ��������ᾢ�����Լ��ľ�����������ͻ��\n"NOR;
                damage = me->query_skill("canhe-zhi",1)*3;

				damage += me->query_skill("finger")*3;
				
damage += random(damage);
        if ( damage > 2000 )
				damage = 2000 + (damage - 2000)/100;

		if(damage>= target->query("qi")) damage= target->query("qi")-1;

           target->add("neili",-(300+random(150)));
           target->receive_damage("qi", damage, me);
        if(userp(me) && me->query("env/damage"))
        	tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage+ WHT"�㹥���˺���\n"NOR);
		
if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage+ WHT"���˺���\n"NOR);
		
        
			target->receive_wound("qi", damage/3, me);
            msg += damage_msg(damage, "����");
            message_vision(msg, me, target);
            COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", me->query_skill("canhe-zhi") /4);

		me->add_temp("apply/damage", me->query_skill("canhe-zhi") /4);

        if(!random(3))
			target->add_condition("no_perform", 1);
        if(!random(3))
			target->add_condition("no_exert", 1);
        if(!userp(target))    target->add_busy(2);
        if (me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        me->add_temp("apply/attack", -me->query_skill("canhe-zhi") /4);

		me->add_temp("apply/damage", -me->query_skill("canhe-zhi") /4);

                me->add("neili",-200);
                me->add("jingli",-80);
                me->start_perform(3, "������ָ��");
        }
        else {
                msg  += CYN"\n$nһ��������Ծ��Σ��֮�ж������һ����\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                me->add_busy(random(2));
        }
        if (me->query_skill("canhe-zhi", 1) > 450 && objectp(target))
                next2(me, target, i);
        else
                me->delete_temp("chz/sanjue");
        return 1;
}

int next2(object me, object target, int i)
{
        string msg;
        int damage, ap, dp;
        object weapon;
        if( !me ) return 0;
        weapon = me->query_temp("weapon");
        if (weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("chz/sanjue");
                return 0;
        }

        msg = HIY"\n$n�����ڹ�����֮�ʣ�$Nָ���ֻ�Ϊ����Ҷָ֮�ƣ�ָ������������ָ��$n�������Ѩ��\n"NOR;
        ap = me->query("combat_exp") * me->query_str(1)/100000;
        dp = target->query("combat_exp") * target->query_str(1)/100000;
		//100000����ap,dp���Է���� by sohu@xojh
       if(objectp(target)&&((userp(target)&& random(ap + dp) > dp) || !userp(target))){

                    damage = me->query_skill("canhe-zhi",1)*3;

					damage += me->query_skill("finger",1)*3;

					damage += random(damage);
                if ( damage > 3000 )
					damage = 3000 + (damage - 3000)/100;
				//if( damage>= target->query("qi",1)) damage= target->query("qi",1)-1;

            
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                
				msg += damage_msg(damage, "����");
                message_vision(msg, me, target);

        if(objectp(target) && me->query("env/damage"))
			tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage+ WHT"�㹥���˺���\n"NOR);
		//
if(userp(target)&& target->query("env/damage"))
			//tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage+ WHT"���˺���\n"NOR);
		
COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", (int)me->query_skill("shenyuan-gong") /4);

		me->add_temp("apply/damage", (int)me->query_skill("shenyuan-gong") /4);
        if (me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -(int)me->query_skill("shenyuan-gong") /4);

	    me->add_temp("apply/damage", -(int)me->query_skill("shenyuan-gong") /4);
                me->add("neili",- 150);
                me->add("jingli",-80);
                me->start_perform(3 + random(2),"������ָ��");
				
        } 
        else {
                msg = msg + HIW "$nһ�������ţ����������������ܹ���\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
        me->delete_temp("chz/sanjue");
        return 1;
}



string perform_name(){ return HIG"����ָ"NOR; }
int help(object me)
{
        write(HIG"\n�κ�ָ��֮"+RED"������ָ����"NOR"\n\n");
        write(@HELP
	�κ�ָ����Ľ���ϵľ�ѧ�������������ת���ƣ�����Ľ��
	�Ҵ��ľ����似���κ�ָ��ǿ�������������������������
	�Է���������ϰ�òκ�ָ�ľ����ؼ���������������������
	�ɵ�ָ��������
	����ָ����������ָ����Ϊ����ָ��֮��������һ��Ϊ����
	���ָ���ڶ���Ϊ�黨ָ��������Ϊ����Ҷָ������Ľ����
	��ϰ�����书�ľ�����ʽ��

ָ�perform finger.sanjue

Ҫ��
	��ǰ���� 1000 ���ϣ�
	������� 8000 ���ϣ�
	�κ�ָ�ȼ� 500 ���ϣ�
	��Ԫ���ȼ� 500 ���ϣ�
	����ָ��Ϊ�κ�ָ��
	�м�Ϊ�κ�ָ��ת����
	��ָ��Ϊ�κ�ָ��
	�����ޱ���,

HELP
        );
        return 1;
}
