//sanzhang.c �����������ƣ�ģ������ create by sohu@xojh


#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int next1(object me, object target, int i);
int next2(object me, object target, int i);

int perform(object me,object target)
{
        object weapon;
        string msg;
        int ap,dp,damage;
        int i = me->query_skill("xianglong-zhang",1);

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("�������������ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        //�ǽ��ܲ��ÿ�
        if(me->query("xlz/sanzhao")!="pass")
                return notify_fail("����Ȼ��˵���������������ơ�������һֱû���������о��ϣ����������ã�\n");

        if( me->query_skill("xianglong-zhang", 1) < 500 )
                return notify_fail("��Ľ����ƻ�δ���ɣ�����ʹ�á������������ơ���\n");

        if( me->query_skill("strike", 1) < 500 )
                return notify_fail("��Ļ����Ʒ���δ���ɣ�����ʹ�á������������ơ���\n");

        if (objectp(weapon = me->query_temp("weapon")))
                return notify_fail("�������б������޷�ʹ�ÿ����������ƣ�\n");
   
        if (me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("�������޷�ʹ�á������������ơ����й�����\n");  

        if(me->query_skill_mapped("parry") != "xianglong-zhang")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ�á������������ơ���\n");
        if(me->query_str(1) < 80 )
                return notify_fail("�����Ч��������������ʹ�á������������ơ���\n");
        if(me->query("max_neili") < 10000 )
                return notify_fail("���������Ϊ����������ʹ�á������������ơ���\n");
        if(me->query("neili") < 2500 )
                return notify_fail("�������������㣬����ʹ�á������������ơ���\n");
        if(me->query("jingli") <2500 )
                return notify_fail("�����ھ������㣬����ʹ�á������������ơ���\n");
         if(me->query_temp("xlz/sanzhang"))
                return notify_fail("������ʹ�á������������ơ���\n");
         damage=me->query_skill("xianglong-zhang",1)+me->query_skill("strike",1)+me->query_skill("force",1)+me->query_skill("huntian-qigong",1);
		 damage=damage*me->query_str()/10+random(damage);
         if ( damage > 6000 )
				damage = 6000 + (damage - 6000)/10;
		 me->set_temp("xlz/sanzhang1",damage);
         msg = HBRED+HIY"\n$N���з�ŭ������������������һ�������ֺ���һ�ƣ�����$n��ȥ�����ǽ���ʮ���Ƶ�һ�С������лڡ�!\n"+
			 "$N����֮ʱ����$n�������ʮ�����ɣ���˵���㵽����������֮�ʣ���������Ѳ����߰��ɡ�\n"NOR;
         

         //me->start_perform(2, "�������������ơ�");
         me->add_temp("apply/attack", me->query_skill("xianglong-zhang") /2);

		 me->add_temp("apply/damage", me->query_skill("xianglong-zhang") /4);
         me->set_temp("xlz/sanzhang", i);
         me->set_temp("xlz/hanglong",1);    
		 if (random(me->query_str(1)) > target->query_str(1)/3 
			 ||random(me->query("combat_exp")) > target->query("combat_exp")/3 
			 )
           {
			  msg+= HIC "\n$nֻ����������֮�У�����������ǿ��Ҳ����һ�ƿɻ�����������ġ�����$n����$N�Ĵ�������$N���ް��С��֮�ġ�\n"NOR;
			  msg+=HIW"Ȼ��$N��ʮ������֮����ƣ����ϲ�������������Լ�����,һʱ���죬�پ���æ����������\n"NOR;
			  target->receive_damage("qi", damage,me);
			  target->receive_wound("qi", damage/4,me);
			  if (!target->is_busy()) target->start_busy(1+random(2));
			  else target->add_busy(1+random(2));
			  msg += HBRED"\n$nΪ$N���п����лھ��������֣����޿ɱܣ���������ֻ��̧��ӭ��������һ�ơ�\n"NOR;
			  target->apply_condition("no_perform",1+random(2));
			
		  }else msg +=RED"\n$n�����ڹ����Ķ����˹���$N����һ����������ʽ���������а��ݣ�������ʮ���ơ���Ȼ�����鴫��\n"NOR;
        message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		me->add_temp("apply/attack", -me->query_skill("xianglong-zhang") /2);
		
		me->add_temp("apply/damage", -me->query_skill("xianglong-zhang") /4);

        me->add("neili", -800);

        if (objectp(target)&& me->query_skill("xianglong-zhang", 1) > 450)
                next1(me, target, i);
        else {
                me->delete_temp("xlz/sanzhang");
				me->delete_temp("xlz/hanglong");
		}
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
                me->delete_temp("xlz/sanzhang");
                return 0;
        }
        msg = HBRED"\n�ⲻ��$Nһ�Ƽȳ���������������$n�������⣬����һ�С������лڡ���������ǰ�ƣ�˫����������һ����ɽ��������$nѹ��������\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1)/1000;
        dp = target->query("combat_exp", 1) * target->query_con(1)/1000;
	    msg += HIR"\nֻһ˲֮�䣬$n�����Ϣ���ͣ��Է���������ŭ����ӿ���Ʋ��ɵ���������һ�����εĸ�ǽ�����Լ���ǰ���������\n"NOR;
		me->set_temp("xlz/hanglong",1); 
		if((userp(target)&& random(ap + dp) > dp/2 )|| !userp(target)){
                msg += HIR"\n$n��֮�£����ﻹ����ԣ��˼�Բߣ���֪���ǵ��Ƴ�ӭ���Ʊر۶����ۣ�˵����ȫ���Ǿ��飬\n"NOR;
				//msg += HIR"$n��æ��˫������������Բ��ס��ǰ��ͬʱ���������Ʈ����ˡ�\n"NOR;
                damage = me->query_skill("xianglong-zhang",1)*3;

				damage += me->query_skill("strike")*3;
				
				damage += me->query_temp("xlz/sanzhang1");
                me->delete_temp("xlz/sanzhang1");
				me->set_temp("xlz/sanzhang2",damage);

		        if(damage>= target->query("qi",1)) damage= target->query("qi",1)-1;

                if (target->query("neili")>3500)
                    target->add("neili",-3500);
				else target->set("neili",10);
				//��նԷ�����
                target->receive_damage("qi", damage, me);
                if(userp(me) && me->query("env/damage"))
        	       tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage+ WHT"�㹥���˺���\n"NOR);
		
        if(userp(target)&& target->query("env/damage"))
			       tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage+ WHT"���˺���\n"NOR);
		
        target->receive_wound("qi", damage/3, me);
                msg += damage_msg(damage, "����");
                message_vision(msg, me, target);
                COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", me->query_skill("xianglong-zhang") /2);

		me->add_temp("apply/damage", me->query_skill("xianglong-zhang") /4);

        //if(random(3))
			target->add_condition("no_exert", 1+random(2));
        if(random(3))
			target->add_condition("no_force", 1);
        if(!userp(target))    target->add_busy(2+random(2));
        
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("xianglong-zhang") /2);

		me->add_temp("apply/damage", -me->query_skill("xianglong-zhang") /4);

                me->add("neili",-800);
                me->add("jingli",-80);
                me->start_perform(3, "�������������ơ�");
        }
        else {
                msg += HIC"\n$n��æ��˫������������Բ��ס��ǰ��ͬʱ���������Ʈ����ˡ�\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                //me->add_busy(random(1));
        }
		//me->start_perform(1, "�������������ơ�");
        if (objectp(target)&&me->query_skill("xianglong-zhang", 1) > 500)
                next2(me, target, i);
        else {
                me->delete_temp("xlz/sanzhang");
		        me->delete_temp("xlz/hanglong"); 
		}
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
                me->delete_temp("tz/sanzhang");
                return 0;
        }
        msg = HBMAG"\n����$nƣ�ڷ���֮�ʣ�$N��������һ�С������лڡ���ǰ������δ�������������ֵ���\n"
		      +HIY"$n��������ֱ����棬����бб�ӳ�����$N������ƫ��һ���������ұ����飬������Ϣ��ʱ���ǡ�\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1);
        dp = target->query("combat_exp", 1) * target->query_str(1);
       if((userp(target)&& random(ap + dp) > dp/2 )|| !userp(target)){

                    damage = me->query_skill("xianglong-zhang",1)*3;

					damage += me->query_skill("strike",1)*3;

					damage += me->query_temp("xlz/sanzhang2");
					me->delete_temp("xlz/sanzhang2");

                if ( damage > 8000 )
					damage = 8000 + (damage -8000)/10;
				if( damage>= target->query("qi",1)) damage= target->query("qi",1)-1;
                target->set_temp("xlz/sanzhang",me->query_skill("xianglong-zhang",1));
                target->add_temp("apply/attack", -me->query_skill("xianglong-zhang",1));
                target->add_temp("apply/dodge",  -me->query_skill("xianglong-zhang",1));
                target->add_temp("apply/parry", -me->query_skill("xianglong-zhang",1));
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/4, me);
                msg += damage_msg(damage, "����");

                message_vision(msg, me, target);
        if(userp(me) && me->query("env/damage"))
			tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage+ WHT"�㹥���˺���\n"NOR);
		
if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage+ WHT"���˺���\n"NOR);
		
COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", me->query_skill("xianglong-zhang") /2);

		me->add_temp("apply/damage", me->query_skill("xianglong-zhang") /4);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("xianglong-zhang") /2);

	    me->add_temp("apply/damage", -me->query_skill("xianglong-zhang") /4);
                me->add("neili",- 1000);
                me->add("jingli",-80);
                me->start_perform(3 + random(2),"�������������ơ�");
                call_out("back", 5 + random(me->query("jiali") / 20), target);
        } 
        else {
                msg = msg + HIW "$n���������ݳ�����֮�⣬Ψ�ֵ�������׷�������Ƶ��أ��������������ϡ�\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
        me->delete_temp("tz/tiezhang");
		me->start_perform(5, "�������������ơ�");
        return 1;
}

void back(object target)
{
        if (!target) return;
        target->add_temp("apply/attack", target->query_temp("xlz/sanzhang"));
        target->add_temp("apply/dodge", target->query_temp("xlz/sanzhang"));
        target->add_temp("apply/parry", target->query_temp("xlz/sanzhang"));
}

string perform_name(){ return HBRED+HIY"������������"NOR; }
int help(object me)
{
        write(HBRED+HIY"\n����ʮ���Ʒ�֮�������������ơ���"NOR"\n\n");
        write(@HELP 
	����ʮ�����������ֵ�һ���ؤ��������������֮һ���������Ტ�ã�������գ�
	�������ᣬ���ظ��������������վ��ᾢ���Ϊһ��������ǿ���������̺��£���
	����֮���������ᣬ�������յ�һ���Ʒ�֮�������˫����������������˵����
	����ѧ�е��۷���裬�������Ƽ����棬���������������������������ʽ��
	��������������书����Ҫ֮����ȫ���˾�������ȫƾ��ǿ����ȡʤ���������޼�
	���ݡ��޹̲��ƣ����������ޣ���ÿ��һ�ƾ���������Х֮�ơ�ÿ��һ�о��߾���
	��������
	����ʮ���Ʊ���õ������Ĵ��ڷ���ϰ�ã������������С����ǽ��������վ���֮
	һ���������������ʩչ������������̷���ϰ�á�
	
	ָ�perform strike.sanzhang

Ҫ��	
	������� 10000 ���ϣ�
	��ǰ���� 2500 ���ϣ�
	��ǰ���� 2500 ���ϣ�
	�����Ƶȼ� 500 ���ϣ�
	�����Ʒ��� 500 ���ϣ�
	��Ч���� 80 ���ϣ�
	�����Ʒ������ƣ�
	�����ڹ�Ϊ����������
	�����м�Ϊ�����ơ�
HELP
        );
        return 1;
}
