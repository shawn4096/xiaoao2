//xiao, cred by sohu@sojh yangxiao ���似�ݻ�����

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int next1(object me, object target, int skill);
int next2(object me, object target);

int perform(object me,object target)
{
        object weapon1,tweapon;
        string msg;
		int ap,dp,dam;
        int skill = me->query_skill("xiaoyao-jian",1);
        
        weapon1=me->query_temp("weapon");
        tweapon=target->query_temp("weapon");
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("��Х�־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
      

        if( me->query_skill("shenghuo-shengong", 1) < 300 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ�á�Х�־�����\n");

        if( me->query_skill("xiaoyao-jian", 1) < 300 )
                return notify_fail("�����ң������δ���ɣ�����ʹ�á�Х�־�����\n");

        if (!objectp(weapon1 = me->query_temp("weapon")) 
        || weapon1->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "xiaoyao-jian")
                return notify_fail("������û�н����޷�ʹ�á�Х�־�����\n");

        if(me->query_skill_mapped("parry") != "xiaoyao-jian"
        && me->query_skill_mapped("parry") != "qiankun-danuoyi")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ�á�Х�־�����\n");
        if(me->query("max_neili") < 3000 )
                return notify_fail("������������Ϊ����������ʹ�á�Х�־�����\n");
        if(me->query("neili") < 500 )
                return notify_fail("�������������㣬����ʹ�á�Х�־�����\n");
        if(me->query("jingli") < 600 )
                return notify_fail("�����ھ������㣬����ʹ�á�Х�־�����\n");
       // if(me->query_temp("xyjf/xiao"))
             //   return notify_fail("������ʹ�á�Х�־�����\n");

        if(me->query_skill("sword", 1) < 300 )
                return notify_fail("��Ļ�������������죬�����ڽ�����ʹ�á�Х�־�����\n");

       // if( target->is_busy() )
         //       return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        msg = HIW"\n$N���쳤Х��ʹ����ң������Х�־�����ֻ���������ľҶ�������䡣���$N��һϮ���������������ޱȡ�\n"NOR;
        me->start_perform(4, "��Х�־���");
		//��һ���ж� exp int
        ap = me->query("combat_exp") /1000;
        dp = target->query("combat_exp")/1000;
       // me->set_temp("xyjf/xiao", 1);
        if( random(ap + dp ) > dp||random(me->query_con())> target->query_con()/2) {
                msg += MAG "Ϊ$N�ĳ�Х֮����Ӱ�죬���ζ�ʱ���ɵ�һ�͡�\n" NOR;
                target->add_busy(1); 
				if (!userp(target))
					target->add_busy(2+random(2));
                me->add("neili", -150);
				message_vision(msg, me, target);
		
        }
        else {
                me->add("neili", -80);
                msg += MAG "����$nս�������쳣�ḻ���˹��ڶ�����û���ܵ�˿��Ӱ�졣\n" NOR;
                me->start_busy(random(2));
				message_vision(msg, me, target);				
        }
           //message_vision(msg, me, target);
               me->add_temp("apply/attack", (int)me->query_skill("xiaoyao-jian") /4);
		        me->add_temp("apply/damage", (int)me->query_skill("xiaoyao-jian") /4);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
                me->add_temp("apply/attack", -(int)me->query_skill("xiaoyao-jian") /4);
	            me->add_temp("apply/damage", -(int)me->query_skill("xiaoyao-jian") /4);

		if (me->is_fighting(target))
                next1(me,target,skill);
		else  me->delete_temp("xyjf/xiao");
		
        //me->start_perform(1,"Х�־�");
        return 1;
}

int next1(object me, object target, int skill)
{
        string msg;
        int damage, ap,dp;
		object weapon1,tweapon;
        weapon1=me->query_temp("weapon");
        tweapon=target->query_temp("weapon");
        if (!me) return 0;
    
        if (!weapon1 || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("xyjf/xiao");
                return 0;
        }
		if (objectp(tweapon))
		{
			message_vision(HIY"$N��$n����һ�͵ĵ��£�����$N����̧�ȣ�ͻȻ֮�䵹�����࣬һת��������$n������ߡ�\n"+
					HIG"$N������$n���е�"+tweapon->query("name")+HIG"ץȥ��\n"NOR,me,target);
            if (random(me->query("combat_exp") )>target->query("combat_exp")/3)
            {
				message_vision(HIC"$n�䲻��Ϊ$N�������е�"+tweapon->query("name")+",ȴ��$N����Ͷ����أ����ܲ��ʣ���Ȼ�ﳤ��ȥ��\n"+
					"$n��ʱΪ֮���ᣬ��ڵ�������˵����������\n"NOR,me,target);
				tweapon->move(environment(me));
				target->add_busy(1+random(2));           
			}
			else message_vision(HIC"$n��$N��������Լ��������ŭ������Ȼ�����侲��ͷ�ԡ�\n"NOR,me,target);
		}
		damage = skill*4+me->query_skill("force",1);
        damage += me->query_skill("sword",1);
        damage += 2*damage+random(damage);
        if ( damage > 4000 )
                        damage = 4000 + (damage - 4000)/10;
        
		msg = HIR"\n������$N����һת�������ǰ���ӽ���磬���ֱ����$n�����ߡ�\n"NOR;
        ap = me->query("combat_exp", 1) /10000;
        dp = target->query("combat_exp", 1) /10000;
        if( random(ap + dp) > dp ||random(me->query_str(1))>target->query_con(1)/3){
                msg += RED"$nֻ������һʹ����Ѫ��к������\n"NOR;
              
                target->add("neili",-(300+random(150)));
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/3,me);
                msg += damage_msg(damage, "����");
                msg = replace_string(msg, "$w", weapon1->name());
                msg = replace_string(msg, "$l", "������Ѩ��");
                message_vision(msg, me, target);
                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+damage+ WHT"�㹥���˺���\n"NOR);
				
if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+damage+ WHT"���˺���\n"NOR);

				COMBAT_D->report_status(target, random(2));
				if (!userp(target))
			    {        
					me->add_temp("apply/attack", (int)me->query_skill("xiaoyao-jian") /3);
					me->add_temp("apply/damage", (int)me->query_skill("xiaoyao-jian") /4);
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
					me->add_temp("apply/attack", -(int)me->query_skill("xiaoyao-jian") /3);
					me->add_temp("apply/damage", -(int)me->query_skill("xiaoyao-jian") /4);
				}
				me->add("neili",-200);
                me->add("jingli",-80);
                me->start_perform(2, "��Х�־���");
        }
		
        else {
                msg  += CYN"$n��ʶ��Σ�գ�Σ������ת��������Ȼһ����\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                me->add_busy(random(2));
        }
        if (me->is_fighting(target))
               next2(me, target);
        else 
            me->delete_temp("xyjf/xiao");
        return 1;
}

int next2(object me, object target)
{
        string msg;
        int ap, dp,damage,skill;
		object weapon1,tweapon;
        weapon1=me->query_temp("weapon");
        tweapon=target->query_temp("weapon");
		
		skill=me->query_skill("xiaoyao-jian",1);
        
		if( !me ) return 0;
        if (!weapon1 || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("xyjf/xiao");
                return 0;
        }

        msg = HIR"\n����$nΪ$N��������ʽϮ����ƣ�ڷ���֮�ʣ�$N�������ھ���Х����������۵糸�ش̳�һ����\n"NOR;
        ap = me->query("combat_exp")/1000;
        dp = target->query("combat_exp")/1000;
        if( random(ap + dp) > dp ||random(me->query_str())>target->query_dex()/3) {
                msg += HIW "$N���е�"+weapon1->query("name")+HIW+"�����û��ͻȻһ��������$n��" +HIC"����ԪѨ��"+HIW + "��\n"NOR;
                
				damage = skill*4+me->query_skill("force",1);
				damage += me->query_skill("sword",1);
				damage += 2*damage+random(damage);
				damage+=me->query_skill("qiankun-danuoyi",1);
				damage *=4;
                damage += random(damage);
                if ( damage > 5000 )
                        damage = 5000 + (damage - 5000)/10;
               
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
				target->add_busy(1);
                msg += damage_msg(damage, "����");
                msg = replace_string(msg, "$w", weapon1->name());
                msg = replace_string(msg, "$l", "����ԪѨ��");
                message_vision(msg, me, target);
                COMBAT_D->report_status(target, random(2));
			    
				if (!userp(target))
			    {
			    
					me->add_temp("apply/attack",(int)me->query_skill("xiaoyao-jian") /2);
					me->add_temp("apply/damage", (int)me->query_skill("xiaoyao-jian") /4);
					
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
					me->add_temp("apply/attack", -(int)me->query_skill("xiaoyao-jian") /2);
					me->add_temp("apply/damage", -(int)me->query_skill("xiaoyao-jian") /4);
					me->add("neili",- 150);
					me->add("jingli",-80);
				}
                //me->start_perform(3 + random(2),"��Х�־���");
                //call_out("back", 5 + random(me->query("jiali") / 20), target);
        } 
         else {
                msg = msg + HIW "$n��Ϊ�������������࣬ʤ����ͥ�Ų�������ܹ����С�\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
				//me->start_perform(2 + random(2),"��Х�־���");
        }
        me->delete_temp("xyjf/xiao");
		me->start_perform(3 + random(2),"��Х�־���");
        return 1;
}


string perform_name(){ return HIR"Х�־�"NOR; }
int help(object me)
{
        write(HIG"\n��ң����֮"+HIR"��Х�־���"NOR"\n\n");
        write(@HELP
	�����������̹�����ʹ���뷶ң�ϳơ���ң���ɡ���һ���书���䲵�ӣ�
	��ߴ����Եļ�Ϊ����ң����������������һս�������������书��
	��������һ����ս�����书֮�����������ֵ����쾡�£���ƽ��һ
	��������ķ�ң����Ϊ̾����
	
	ָ�perform sword.xiao

Ҫ��
	��ǰ����Ҫ�� 500 ���ϣ�
	�������Ҫ�� 3000 ���ϣ�
	��ǰ����Ҫ�� 600 ���ϣ�
	��ң�����ȼ� 300 ���ϣ�
	ʥ���񹦵ȼ� 300 ���ϣ�
	���������ȼ� 300 ���ϣ�
	��������Ϊ��ң������
	�����м�Ϊ��ң������Ǭ����Ų�ƣ�
	�����ڹ����ޡ�
HELP
        );
        return 1;
}
