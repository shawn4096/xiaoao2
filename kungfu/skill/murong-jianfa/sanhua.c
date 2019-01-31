// cred by sohu@sojh

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int next1(object me, object target, int i);
int next2(object me, object target, int i);

int perform(object me,object target)
{
        object weapon;
        string msg;
        int i = me->query_skill("murong-jianfa",1) / 4;
        int ap,dp;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("��Ůɢ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("force") != "shenyuan-gong")
                return notify_fail("����ڹ�������Ԫ�����޷�ʹ����Ůɢ����\n");

        if( me->query_skill("shenyuan-gong", 1) < 150 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ����Ůɢ����\n");

        if( me->query_skill("murong-jianfa", 1) < 150 )
                return notify_fail("��Ľ�����δ���ɣ�����ʹ����Ůɢ����\n");

        if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "murong-jianfa")
                return notify_fail("������û�н����޷�ʹ����Ůɢ����\n");

        if(me->query_skill_mapped("parry") != "murong-jianfa"
        && me->query_skill_mapped("parry") != "douzhuan-xingyi")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ����Ůɢ����\n");
        if(me->query("max_neili") < 1500 )
                return notify_fail("���������Ϊ����������ʹ����Ůɢ����\n");
        if(me->query("neili") < 500 )
                return notify_fail("�������������㣬����ʹ����Ůɢ����\n");
        if(me->query("jingli") < 600 )
                return notify_fail("�����ھ������㣬����ʹ����Ůɢ����\n");
        if(me->query_temp("sanhua"))
                return notify_fail("������ʹ����Ůɢ����\n");

        if(me->query_skill("sword", 1) < 150 )
                return notify_fail("��Ļ�������������죬�����ڽ�����ʹ����Ůɢ����\n");

        if( target->is_busy() )
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        message_vision(HIG"\n$Nʹ��Ľ�ݽ���֮����Ůɢ��������Ԫ������ת��"+weapon->query("name")+HIG"֮�ϣ�����ó���㽣��ֱ��$nȫ�����ҪѨ��\n"NOR,me,target);
		//message_vision();
        
		me->start_perform(3, "����Ůɢ����");
        ap = me->query("combat_exp", 1)/100000;
        dp = target->query("combat_exp", 1)/100000; 
        i = random(i/8) + 3;
        if ( i > 5 ) i = 5;
        if( random(ap + dp ) > dp 
			||random(me->query_int(1))>target->query_int(1)/2 ) 
		{
                message_vision(MAG "$n��Ȼ������Щ�ۻ����ң�һʱ��������$N���˸����ֲ�����\n" NOR,me,target);
                target->add_busy(i);
                me->set_temp("sanhua", 1);
                me->add("neili", -150);
        }
        else {
                me->add("neili", -80);
                message_vision(MAG "����$n������$N����ͼ����û���ϵ���\n" NOR,me,target);
                me->start_busy(random(2));
        }
       // message_vision(msg, me, target);
        if ( me->query_skill("murong-jianfa", 1) > 150)
                next1(me, target, i);
        else 
                me->delete_temp("sanhua");
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
                me->delete_temp("sanhua");
                return 0;
        }
        msg = HIR"\n������$N����һת�������ǰ���Ӳ���˼��ĽǶȴ���$n��" + HIY"������Ѩ��"HIR + "��\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1);
        dp = target->query("combat_exp", 1) * target->query_con(1);
        if( random(ap + dp) > dp ){
                msg += CYN"$nֻ��ȫ�������ɡ�����Ѩ����к������\n"NOR;
                damage = me->query_skill("murong-jianfa",1);
                damage += me->query_skill("sword")* 3;
                damage += random(damage);
                if ( damage > 5000 )
                        damage = 5000 + (damage - 5000)/10;
                target->add("neili",-(300+random(150)));
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                msg += damage_msg(damage, "����");
                msg = replace_string(msg, "$w", weapon->name());
                msg = replace_string(msg, "$l", "������Ѩ��");
                message_vision(msg, me, target);
                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+damage+ WHT"�㹥���˺���\n"NOR);
				
if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+damage+ WHT"���˺���\n"NOR);

				COMBAT_D->report_status(target, random(2));
                me->add("neili",-200);
                me->add("jingli",-80);
                me->start_perform(3, "����Ůɢ����");
        }
        else {
                msg  += CYN"$nһ����¿�����Σ��֮�ж������һ����\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                me->add_busy(random(2));
        }
        if (me->query_skill("murong-jianfa", 1) > 200)
                next2(me, target, i);
        else
                me->delete_temp("sanhua");
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
                me->delete_temp("sanhua");
                return 0;
        }
        msg = HIC"\n����$nƣ�ڷ���֮�ʣ�$N��������Ԫ������۵糸�ش̳���������\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1);
        dp = target->query("combat_exp", 1) * target->query_dex(1);
        if( random(ap + dp) > dp ) {
                msg += HIW "���һ��������$n��" + HIR"��̴��Ѩ��"HIW + "��\n"NOR;
                damage = me->query_skill("murong-jianfa",1);
                damage += me->query_skill("sword",1);
				damage *=3;
                damage += random(damage);
                if ( damage > 8000 )
                        damage = 8000 + (damage - 8000)/100;
                target->add_temp("apply/attack", 80);
                target->add_temp("apply/dodge", 80);
                target->add_temp("apply/parry", 80);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                msg += damage_msg(damage, "����");
                msg = replace_string(msg, "$w", weapon->name());
                msg = replace_string(msg, "$l", "��̴��Ѩ��");
                message_vision(msg, me, target);
                COMBAT_D->report_status(target, random(2));
                me->add("neili",- 150);
                me->add("jingli",-80);
                me->start_perform(3 + random(2),"����Ůɢ����");
                call_out("back", 5 + random(me->query("jiali") / 20), target);
        } 
        else {
                msg = msg + HIW "$nһ�����ذδУ�Ծ�����ɣ������ܹ���\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
        me->delete_temp("sanhua");
        return 1;
}

void back(object target)
{
        if (!target) return;
        target->add_temp("apply/attack", -80);
        target->add_temp("apply/dodge", -80);
        target->add_temp("apply/parry", -80);
}

string perform_name(){ return HIG"��Ůɢ��"NOR; }
int help(object me)
{
        write(HIG"\nĽ�ݽ���֮"+HIR"����Ůɢ����"NOR"\n\n");
        write(@HELP
	Ľ�ݽ���������Ľ���似�еľ�����ʽ���Ǻ��ĵ��Ӳ���
	�佣���ص��Ǽ��ݲ������ں����½������������ֱ����
	�ã����ڲ�ͬ����������Ľ�ݼҴ��ڹ�֧�֣���Ϊ���ָ�
	��һ��¥�����м���ָ�������⿪��ת���ƾ����似����
	������һ��¥��

ָ�perform sword.sanhua

Ҫ��  
	��ǰ�������� 500 ���ϣ�
	����������� 1500 ���ϣ�
	��ǰ�������� 600 ���ϣ�
	Ľ�ݽ����ȼ� 150 ���ϣ�
	��Ԫ�����ȼ� 150 ���ϣ�
	���������ȼ� 150 ���ϣ�
	��������ΪĽ�ݽ�����
	�����м�ΪĽ�ݽ�����ת���ƣ�
	�����ڹ�Ϊ��Ԫ����
HELP
        );
        return 1;
}
