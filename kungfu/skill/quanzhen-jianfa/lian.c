// modified by snowman@SJ 05/12/2000
// Modify By River@Sj
// Modify By jpei


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
        int i = me->query_skill("haotian-zhang",1) / 2 + me->query_skill("quanzhen-jianfa",1) /2 ;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("����ڹ��������칦���޷�ʹ����������\n");

        if(me->query("quest/quanzhen/sword/lianhuan")!=1)
                return notify_fail("����Ȼ��˵������������������һֱû���������о��ϣ����������ã�\n");

        if( me->query_skill("xiantian-gong", 1) < 400 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ����������\n");

        if( me->query_skill("quanzhen-jianfa", 1) < 400 )
                return notify_fail("��Ľ�����δ���ɣ�����ʹ����������\n");
        if( me->query_skill("sword", 1) < 400 )
                return notify_fail("��Ļ���������δ���ɣ�����ʹ����������\n");

        if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "quanzhen-jianfa")
                return notify_fail("������û�н����޷�ʹ����������\n");
   
        if (me->query_skill_prepared("strike") != "haotian-zhang"
            || me->query_skill_mapped("strike") != "haotian-zhang")
                return notify_fail("��û�м�����ʹ������ƣ������޷�ʹ�á������������й�����\n");  

        if(me->query_skill_mapped("parry") != "quanzhen-jianfa"
        && me->query_skill_mapped("parry") != "kongming-quan")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ����������\n");

        if(me->query("max_neili") < 3500 )
                return notify_fail("���������Ϊ����������ʹ����������\n");
        if(me->query("neili") < 1000 )
                return notify_fail("�������������㣬����ʹ����������\n");
        if(me->query("jingli") < 600 )
                return notify_fail("�����ھ������㣬����ʹ����������\n");
        if(me->query_temp("qzjf/lian"))
                return notify_fail("������ʹ����������\n");

        if(me->query_skill("sword", 1) < 250 )
                return notify_fail("��Ļ�������������죬�����ڽ�����ʹ����������\n");


        msg = HBRED"\n$Nʹ��ȫ�潣���������������У���Ȼ�������֣��ٽ�ƽ�̣�Ѹ���ޱȣ���������â������ȥ�ƾ��죡\n"NOR;
              message_vision(msg, me, target);

            me->start_perform(3, "����������");
            me->add_temp("apply/attack", me->query_skill("quanzhen-jianfa") /4);

			me->add_temp("apply/damage", me->query_skill("quanzhen-jianfa") /4);
            me->set_temp("qzjf/lian", 1);
             
        //��һ�й���
        if (me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("quanzhen-jianfa") /4);
		
me->add_temp("apply/damage", -me->query_skill("quanzhen-jianfa") /4);

        me->add("neili", -150);

        if ( me->query_skill("xiantian-gong", 1) > 250)
                next1(me, target, i);
        else 
                me->delete_temp("qzjf/lian");
        return 1;
}

int next1(object me, object target, int i)

{
        string msg;
        int damage, ap,dp;
        object weapon;

        if (!me) return 0;

        weapon = me->query_temp("weapon");
        if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("qzjf/lian");
                return 0;
        }
        msg = HIR"\n������$N�����ǰ��һ��ӡ��$n��ǰ��������������¡�\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_con(1)/10000;
        dp = target->query("combat_exp", 1) * target->query_con(1)/10000;
        if((userp(target)&& random(ap + dp) > dp )|| !userp(target))
		{
                msg += HBRED+HIW"$nֻ���ڵ�һ�����ײ����ֱײ���Լ���ð���ǡ�\n"NOR;
                damage = me->query_skill("quanzhen-jianfa",1)*3;

				damage += me->query_skill("sword",1)*3;
				damage+=me->query_skill("xiantian-gong",1)*3;
				
damage += random(damage);
			if ( damage > 5000 )
				damage = 5000 + (damage - 5000)/100;

		
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


                me->add("neili",-200);
                me->add("jingli",-80);
                me->start_perform(3, "����������");
        }
        else {
                msg  += CYN"\n$nһ����¿�����Σ��֮�ж������һ����\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                me->add_busy(random(2));
        }
		//����

		me->add_temp("apply/attack", me->query_skill("haotian-zhang") /4);
		me->add_temp("apply/damage", me->query_skill("haotian-zhang") /4);

			if(!random(4))
				target->add_condition("no_perform", 1);
			if(!random(4))
				target->add_condition("no_exert", 1);
			if(!userp(target))    target->add_busy(2);
		   
			message_vision(HIC"$N����"+weapon->query("name")+"���˸���������ָ���ϣ�˲������������¼���$n��\n"NOR,me,target);
			if (me->is_fighting(target))
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			me->add_temp("apply/attack", -me->query_skill("haotian-zhang") /4);

			me->add_temp("apply/damage", -me->query_skill("haotian-zhang") /4);

        if (me->query_skill("quanzhen-jianfa", 1) > 250)
                next2(me, target, i);
        else
                me->delete_temp("qzjf/lian");
        return 1;
}

int next2(object me, object target, int i)
{
        string msg;
        int damage, ap, dp;
        object weapon;
        if( !me ) return 0;
        weapon = me->query_temp("weapon");
        if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("qzjf/lian");
                return 0;
        }

        msg = HIC"\n����$nƣ�ڷ���֮�ʣ�$N���г����������̣�����ȴ��һ��ɨ����\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1)/100000;
        dp = target->query("combat_exp", 1) * target->query_str(1)/100000;
		//100000����ap,dp���Է���� by sohu@xojh
       if(objectp(target)&&((userp(target)&& random(ap + dp) > dp) || !userp(target)))
	   {

                    damage = me->query_skill("quanzhen-jianfa",1)*3;

					damage += me->query_skill("sword",1)*3;

					
					damage+=me->query_skill("xiantian-gong",1)*3;
					damage += random(damage);
                if ( damage > 6000 )
					damage = 6000 + (damage - 6000)/100;
				//if( damage>= target->query("qi",1)) damage= target->query("qi",1)-1;
				if (!target->query_temp("qzjf/lian"))
				{
					target->add_temp("apply/attack", -80);
					target->add_temp("apply/dodge", -80);
					target->add_temp("apply/parry", -80);
					target->set_temp("qzjf/lian",80);
					if (objectp(target))
						call_out("back", 5 + random(me->query("jiali") / 20), target);

				}

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

                me->add("neili",- 150);
                me->add("jingli",-80);
                me->start_perform(3 + random(2),"����������");
        } 
        else {
                msg = msg + HIW "$nһ�����ذδУ�Ծ�����ɣ������ܹ���\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
		me->add_temp("apply/attack", (int)me->query_skill("xiantian-gong") /4);

		me->add_temp("apply/damage", (int)me->query_skill("xiantian-gong") /4);
        message_vision(RED"$N����һ��ζ���˳�ֵ��һƬ���ǣ���$n������һƬ�����У�\n"NOR,me,target);
		if (me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -(int)me->query_skill("xiantian-gong") /4);

	    me->add_temp("apply/damage", -(int)me->query_skill("xiantian-gong") /4);

        me->delete_temp("qzjf/lian");
        return 1;
}

void back(object target)
{
        if (!target||!target->query_temp("qzjf/lian")) return;
		target->delete_temp("qzjf/lian");
        target->add_temp("apply/attack", 80);
        target->add_temp("apply/dodge", 80);
        target->add_temp("apply/parry", 80);
		tell_object(target,HIC"����������һ�𣬾�����Ȼ��ͨ����ȫ�潣��������������ж����\n"NOR);
		return;
}

string perform_name(){ return HIG"������"NOR; }
int help(object me)
{
        write(HIG"\nȫ�潣��֮"+RED"������������"NOR"\n\n");
        write(@HELP
	ȫ�潣��������������ȫ��̵����Ž������������ͨ���ϣ�
	����ԭ��β��Ѩ���ȴ�ӿȪ�ŵ׳壬ӿȪ������ϥ����ϥ
	������β�̣����趥�ϻ������������ش���ȵ�ţ���¥ʮ��
	�����ҡ��仯��΢����ȫ��̵�ȫ���ķ�������á�
	����ʹ�����У����ǵ����𴦻��ݺὭ����������ʽ������
	Ե�ɺϣ��⿪�����������ȫ�潣���������Ƿ���
	
	ָ�perform sword.lian

Ҫ��
	��ǰ�������� 1000 ���ϣ�
	����������� 3500 ���ϣ�
	��ǰ�������� 600 ���ϣ�
	ȫ�潣���ȼ� 400 ���ϣ�
	���칦���ȼ� 400 ���ϣ�
	���������ȼ� 400 ���ϣ�
	��������Ϊȫ�潣����
	�����м�Ϊȫ�潣�������ȭ��
	�����ڹ�Ϊ���칦��
	�����Ʒ�Ϊ����Ʋ�׼����
HELP
        );
        return 1;
}
