//create by sohu@xojh


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
        int i = me->query_skill("tiezhang-zhangfa",1);

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("�����ƾ�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        //�ǽ��ܲ��ÿ�
        if(!me->query("tiezhang/pass"))
                return notify_fail("����Ȼ��˵�������ƾ�����������һֱû���������о��ϣ����������ã�\n");

        if( me->query_skill("tiezhang-zhangfa", 1) < 450 )
                return notify_fail("��������Ʒ���δ���ɣ�����ʹ�á����ƾ�������\n");

        if( me->query_skill("strike", 1) < 450 )
                return notify_fail("��Ļ����Ʒ���δ���ɣ�����ʹ�á����ƾ�������\n");

        if (objectp(weapon = me->query_temp("weapon")))
                return notify_fail("�������б������޷�ʹ�����ƾ�����\n");
   
        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa")
                return notify_fail("�������޷�ʹ�á����ƾ��������й�����\n");  

        if(me->query_skill_mapped("parry") != "tiezhang-zhangfa")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ�á����ƾ�������\n");

        if(me->query("max_neili") < 9000 )
                return notify_fail("���������Ϊ����������ʹ�á����ƾ�������\n");
        if(me->query("neili") < 2500 )
                return notify_fail("�������������㣬����ʹ�á����ƾ�������\n");
        if(me->query("jingli") <2500 )
                return notify_fail("�����ھ������㣬����ʹ�á����ƾ�������\n");
         if(me->query_temp("tz/tiezhang"))
                return notify_fail("������ʹ�á����ƾ�������\n");
         damage=me->query_skill("tiezhang-zhangfa",1)+me->query_skill("strike",1)+me->query_skill("force",1);
		 damage=damage*me->query_str()/10+random(damage);
      
         msg = HBBLU"\n$Nʹ�������ƾ��������У���Ȼ˫��ƽ�֣������������ۼ������ϣ�˿�����κλ��ɣ�ƽƽ����$n������ȥ��\n"NOR;
         

         me->start_perform(2, "�����ƾ�����");
         me->add_temp("apply/attack", me->query_skill("tiezhang-zhangfa") /3);

		 me->add_temp("apply/damage", me->query_skill("tiezhang-zhangfa") /4);
         me->set_temp("tz/tiezhang", i);
             
      //��һ�й�����Ϲ�ͷ
		 if (random(me->query("str")) > target->query("str")/2 
			 ||random(me->query("combat_exp")) > target->query("combat_exp")/2 
			 ||random(me->query_dex(1)) > target->query_dex(1)/2 )
           {
			  msg+= HBBLU "$n�о�ȫ��������ȫ����������ס������ǿ����ɽ������ѹ�˹���,ֻ��Ӳ��Ӳ������һ�С�\n"NOR;
			  target->receive_damage("qi", damage,me);
			  target->receive_wound("qi", damage/2,me);
			  msg += HBRED"$n��$N��һ�ƴ������󴦣��ϱ۹Ǵ���һ�����������Ȼ���˲��ᡣ\n"NOR;
			  target->apply_condition("no_exert",1);
			
		  }else msg +=HBYEL"$n���Ͼ�����������Ȼ��$N����һ�е�������ȴ���ɵþ���һ���亹��\n"NOR;
        message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		me->add_temp("apply/attack", -me->query_skill("tiezhang-zhangfa") /3);
		
me->add_temp("apply/damage", -me->query_skill("tiezhang-zhangfa") /4);

        me->add("neili", -350);

        if ( me->query_skill("tiezhang-zhangfa", 1) > 349)
                next1(me, target, i);
        else 
                me->delete_temp("tz/tiezhang");
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
                me->delete_temp("tz/tiezhang");
                return 0;
        }
        msg = HBRED"\n������$N�����ǰ�������ĳ������ֳ�ץ��ͬʱϮ��������ǿ����ɽ������ѹ�˹�����\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_con(1)/10000;
        dp = target->query("combat_exp", 1) * target->query_con(1)/10000;
        if((userp(target)&& random(ap + dp) > dp )|| !userp(target)){
                msg += HIC"$n�Ѿ�������$N������һץ��Ȼ���ͣ���Զ����������ôһ����������������\n"NOR;
                damage = me->query_skill("tiezhang-zhangfa",1)*3;

				damage += me->query_skill("strike")*3;
				
damage += random(damage);
        if ( damage > 5000 )
				damage = 5000 + (damage - 1000)/10;

		if(damage>= target->query("qi",1) && target->query("qi",1)>100 ) damage= target->query("qi",1)-1;

                target->add("neili",-(300+random(150)));
                target->receive_damage("qi", damage, me);
       // if(userp(me) && me->query("env/damage"))
       // 	tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage+ WHT"�㹥���˺���\n"NOR);
		
       // if(userp(target)&& target->query("env/damage"))
		//	tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage+ WHT"���˺���\n"NOR);
		
        target->receive_wound("qi", damage/3, me);
                msg += damage_msg(damage, "����");
                message_vision(msg, me, target);
                COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", me->query_skill("tiezhang-zhangfa") /3);

		me->add_temp("apply/damage", me->query_skill("tiezhang-zhangfa") /4);

        if(random(3))
			target->add_condition("no_perform", 1);
        //if(random(3))
			//target->add_condition("no_exert", 1);
        if(!userp(target))    target->add_busy(2);
        
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("tiezhang-zhangfa") /3);

		me->add_temp("apply/damage", -me->query_skill("tiezhang-zhangfa") /4);

                me->add("neili",-200);
                me->add("jingli",-80);
                me->start_perform(3, "�����ƾ�����");
        }
        else {
                msg  += CYN"\n$n��æ�˺��ӱܣ�Σ��֮�ж��������һ����\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                me->add_busy(random(2));
        }
		//me->start_perform(1, "�����ƾ�����");
        if (me->query_skill("tiezhang-zhangfa", 1) > 449)
                next2(me, target, i);
        else
                me->delete_temp("tz/tiezhang");
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
                me->delete_temp("tz/tiezhang");
                return 0;
        }
        msg = HBMAG"\n����$nƣ�ڷ���֮�ʣ�$N��Ȼ��һ����������մ��˸�������\n"+HIW"���Ƹ�������������ȴ����֮������ʽ�˵��Ǿ����ޱ�\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1);
        dp = target->query("combat_exp", 1) * target->query_str(1);
       if((userp(target)&& random(ap + dp) > dp )|| !userp(target)){

                    damage = me->query_skill("tiezhang-zhangfa",1)*3;

					damage += me->query_skill("strike",1)*3;

					damage += random(damage);
                if ( damage > 8000 )
					damage = 8000 + (damage - 1000)/10;
				//if( damage>= target->query("qi",1)) damage= target->query("qi",1)-1;

                target->add_temp("apply/attack", -target->query_skill("tiezhang-zhangfa",1));
                target->add_temp("apply/dodge",  -target->query_skill("tiezhang-zhangfa",1));
                target->add_temp("apply/parry", -target->query_skill("tiezhang-zhangfa",1));
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                msg += damage_msg(damage, "����");

                message_vision(msg, me, target);
      //  if(userp(me) && me->query("env/damage"))
		//	tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage+ WHT"�㹥���˺���\n"NOR);
		
//if(userp(target)&& target->query("env/damage"))
			//tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage+ WHT"���˺���\n"NOR);
		
COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", me->query_skill("tiezhang-zhangfa") /3);

		me->add_temp("apply/damage", me->query_skill("tiezhang-zhangfa") /4);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("tiezhang-zhangfa") /3);

	    me->add_temp("apply/damage", -me->query_skill("tiezhang-zhangfa") /4);
                me->add("neili",- 150);
                me->add("jingli",-80);
                me->start_perform(3 + random(2),"�����ƾ�����");
                call_out("back", 5 + random(me->query("jiali") / 20), target);
        } 
        else {
                msg = msg + HIW "$nһ�����ذδУ�Ծ�����ɣ������ܹ���\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
        me->delete_temp("tz/tiezhang");
		 me->start_perform(4, "�����ƾ�����");
        return 1;
}

void back(object target)
{
        if (!target) return;
        target->add_temp("apply/attack", target->query_skill("tiezhang-zhangfa",1));
        target->add_temp("apply/dodge", target->query_skill("tiezhang-zhangfa",1));
        target->add_temp("apply/parry", target->query_skill("tiezhang-zhangfa",1));
}

string perform_name(){ return HBRED+HIY"���ƾ���"NOR; }
int help(object me)
{
        write(HIR"\n�����Ʒ�֮�����ƾ�������"NOR"\n\n");
        write(@HELP 
	���ƾ����˸ðﲻ��֮�أ������ϴ������Ϲٽ��Ϻ͵�������
	��ǧ��ľ���ϸ������Ȼ��ɡ������Ʒ��̳���������������
	���ص㣬ͬʱ�־�����ף���Ȼ�Ե����Ͳ�������ʮ���ƣ���
	��ʽȴ���Ӿ�������ˮ��Ư���������ڹ�����ô���Ƶ���
	�������׷��ӳ�����
	
	perform strike.tiezhang

Ҫ��  
	��ǰ�������� 2500 ���ϣ�
	����������� 9000 ����;
	��ǰ�������� 2500 ���ϣ�
	�����Ʒ��ȼ� 450 ���ϣ�
	�����ڹ��ȼ� 450 ���ϣ�
	�����Ʒ��ȼ� 450 ���ϣ�
	�����Ʒ�Ϊ�����Ʒ���
	�����м�Ϊ�����Ʒ���
	�����ڹ����ޡ�
HELP
        );
        return 1;
}
