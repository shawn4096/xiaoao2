// pfm canhe by sohu@xojh 2013

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
        int i = me->query_skill("canhe-zhi",1) + me->query_skill("finger",1) /3 ;
        if (me->query("shenyuan/super"))
         i += me->query_skill("shenyuan-gong",1) /2;
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("�������㡹ֻ�ܶ�ս���еĶ���ʹ�á�\n");


        if(me->query_skill_mapped("force") != "shenyuan-gong")
                return notify_fail("����ڹ�������Ԫ�����޷�ʹ�á������㡹��\n");


        if(!me->query("quest/mr/canhezhi/pass"))
                return notify_fail("����Ȼ��˵���������㡹����������һֱû���������о��ϣ����������ã�\n");

        if( me->query_skill("shenyuan-gong", 1) < 500 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ�á������㡹��\n");

        if( me->query_skill("canhe-zhi", 1) < 500 )
                return notify_fail("���ָ����δ���ɣ�����ʹ�á������㡹��\n");

        if( me->query_temp("weapon"))
                        return notify_fail("���������ű������޷�ʹ�á������㡹��\n");
   
        if (me->query_skill_prepared("finger") != "canhe-zhi"

			|| me->query_skill_mapped("finger") != "canhe-zhi")
                return notify_fail("�������޷�ʹ�á������㡹���й�����\n");  


        if(me->query("max_neili") < 9000 )
                return notify_fail("���������Ϊ����������ʹ�á������㡹��\n");
        if(me->query("neili") < 3000 )
                return notify_fail("�������������㣬����ʹ�á������㡹��\n");
        if(me->query("jingli") < 2000 )
                return notify_fail("�����ھ������㣬����ʹ�á������㡹��\n");
        if(me->query_temp("chz/ch"))
                return notify_fail("������ʹ�á������㡹��\n");

        if(me->query_skill("finger", 1) < 500 )
                return notify_fail("��Ļ���ָ��������죬����ʹ�á������㡹��\n");


        msg = HIY"\n$Nͻ�ذεض������������£�ָ����$n�����ȥ�����϶��£���������!\n"NOR;
        msg += HIM"$N���Լ���Ľ�ݲ�������Ĳκ�ָ�����������������ӳ�������һָ"+HIR"�������������"+HIM",��ν��֮���ҡ�\n"NOR;
        message_vision(msg, me, target);
        me->start_perform(3, "�������㡹");

        me->set_temp("chz/ch", 1); //��������Ϊ�˴����κ�ָ��auto
        me->add_temp("apply/attack", i );
        me->add_temp("apply/damage", i /3);  
		me->add_temp("apply/finger", i /3);  
        
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
        me->add_temp("apply/attack", -i );
        me->add_temp("apply/damage", -i /3);
		 me->add_temp("apply/finger", -i /3);
        me->add("neili", -150);
        if (me->query_skill("shenyuan-gong", 1) > 350)
                next1(me, target, i);
        else 
                me->delete_temp("chz/ch");
        return 1;
}

int next1(object me, object target, int i)
{
        string msg;
        int damage, ap, dp;
        object weapon,tweapon;
        if( !me ) return 0;
        weapon = me->query_temp("weapon");
		tweapon=target->query_temp("weapon");
        if (weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("chz/ch");
                return 0;
        }
        msg = HIC"\n$N�̶���Цһ�����ȵ������ڶ�ָ"HIM"����ת�����ơ�"HIC"С���ˣ�������ֳ�һָ��\n"+
        "$nӲ���µ�һʽ�������в�������ڶ������Ҳ����Ӳ��,��ʱ��æ���ң�ƣ���мܣ����޻���֮��!\n"NOR;

        message_vision(msg, me, target);
        
        ap = me->query("combat_exp") * me->query_str(1)/100000;
        dp = target->query("combat_exp") * target->query_dex(1)/100000;
       /* if (tweapon && random(me->query_skill("finger",1))>target->query_skill("parry",1)/3)
        {			
				message_vision(HIG"$N��ȻһЦ,ʳָ�鶯��һ�ɾ�����Ȼ������$nһ���ѳֲ�ס������һ�顣\n"+
					"���е�"+tweapon->query("name")+HIG"�����ڵء�\n"NOR,me,target);
				tweapon->move(environment(me));
				target->add_busy(1+random(1));			
        }*/
        if (ap>dp/3 ||  random(me->query_int()) > target->query_int()/3){
                   message_vision(HIB"$nһ��������Ϊ$Nʩչ���Ķ�ת���ƾ�����������ʱ���ơ�\n"NOR,me,target);
				   target->apply_condition("no_perform", 1+ random(2));
                   target->apply_condition("no_exert", 1+ random(2));
                   me->set("chz/ch",1);
                   me->add_temp("apply/attack", me->query_skill("shenyuan-gong")/2 );
                   me->add_temp("apply/damage", me->query_skill("shenyuan-gong")/4 );
                   target->add_temp("apply/attack", -80);
                   target->add_temp("apply/dodge", -80);
                   target->add_temp("apply/parry", -80);
               
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        if (me->is_fighting(target))
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        if (me->is_fighting(target))
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                  
            me->add_temp("apply/attack", -me->query_skill("shenyuan-gong")/2 );
            me->add_temp("apply/damage", -me->query_skill("shenyuan-gong") /4);
                me->add("neili",- 150);
                me->add("jingli",-80);
                me->start_perform(3 + random(2),"�������㡹");
                //target->delete_temp("must_be_hit",1);
            call_out("back", 5 + random(me->query("jiali") / 20), target);               
        } 
        else {
                msg = msg + HIW "$nһ�����ӷ���������󷽲ſ����ܹ���\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
       if (me->query_skill("canhe-zhi", 1) > 450)
                next2(me, target, i);
        //me->delete_temp("chz/ch");
        return 1;
}

int next2(object me, object target, int i)

{
        string msg;
        int damage, ap,dp;
        object weapon,weapon1;

        if (!me) return 0;
        if(!target) return 0;
        weapon = me->query_temp("weapon");
        weapon1 = target->query_temp("weapon");

        if (weapon || !living(me) || !me->is_fighting(target))
         {
                me->delete_temp("chz/ch");
                return 0;
         }

         msg = HIB"\n������$N��һָ���յ��������һ��"HIR"���������̺᡹"HIB"ָ����׶�����������\n"+
         "$n������֮�£�����ָ��Ϭ�����ƺ���Щ�����ᡣ\n"NOR;
        ap =me->query_skill("canhe-zhi",1);
        dp =target->query_skill("parry",1);
//�����100000��Ϊ�˷�ֹexp��ֵ�����ʱ����ִ������


        if( random(ap)  > dp/2 ||  me->query("int",1) > 40)
        {
             if(weapon1) msg += HIG"$nֻ�ý��������ڵ���һ����ȴ����ֵ���ס��"HIW+weapon1->name()+HIG"���±���ɣ���ž����һ��������¡�\n"NOR;
        
                damage =  me->query_skill("canhe-zhi",1)*3;
                damage += me->query_skill("finger")* 3;
                damage += random(damage);
             if ( damage > 8000 )
                        damage = 8000 + (damage - 8000)/10;

//���Բ��ܴ򱬡����˺���ͳ�����
             if ( damage >= target->query("qi",1) ) 
                        damage = target->query("qi",1) -1;
           	        
             if(weapon1) {      weapon1->unequip();
			                      weapon1->move(environment(target));
                     }
                target->start_busy(3);
                target->add("neili",-(300+random(150)));
                target->apply_condition("no_exert", 1+ random(2));
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
//��������    msg += damage_msg(damage, "����");
                message_vision(msg, me, target);
                COMBAT_D->report_status(target, random(2));
            if(target){
                me->add_temp("apply/attack", me->query_skill("canhe-zhi") );
                me->add_temp("apply/damage", me->query_skill("canhe-zhi")  );
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

                me->add_temp("apply/attack", -me->query_skill("canhe-zhi") );
                me->add_temp("apply/damage", -me->query_skill("canhe-zhi") );
              }      
                me->add("neili",-200);
                me->add("jingli",-80);
              //target->delete_temp("must_be_hit",1);
        } 
        else {
                msg  += CYN"\n$n�͵�ʮ�˹���Σ��֮�ж������һ�����Ǳ�֮����\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                target->add_busy(random(2));
                
                me->add_temp("apply/attack", me->query_skill("canhe-zhi") /2);
                me->add_temp("apply/damage", me->query_skill("canhe-zhi") /2 );

                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                me->add_temp("apply/attack", -me->query_skill("canhe-zhi") /2);
                me->add_temp("apply/damage", -me->query_skill("canhe-zhi") /2);
                               
         }

                me->delete_temp("chz/ch");
//���о�ҪCD�����ٺٹ���
                me->start_perform(5, "�������㡹");
}

void back(object target)
{
        object me = this_player();
        if (!target) return;
        target->add_temp("apply/attack", 80);
        target->add_temp("apply/dodge", 80);
        target->add_temp("apply/parry", 80);
        me->delete_temp("chz/ch");
}

string perform_name(){ return HIR"�������㡹"NOR; }
int help(object me)
{
        write(HIG"\n�κ�ָ֮"HIR"�������㡹"NOR"\n\n");
        write(@HELP
	�κ�ָ����Ľ�ݲ���֮�أ�����Ľ�ݸ�Ϊ����������������
	�Ļ����䣬�����Ѿ����ҵ�Ľ�ݲ�������ʾ��κ�ָ�������
	�������嵱���������ǲκ�ָ���ռ���ѧ������Ľ�ݲ����

	perform finger.lingkong

Ҫ��
	��ǰ������Ҫ 3000 ���ϣ�
	���������Ҫ 9000 ���ϣ�
	��ǰ������Ҫ 2000 ���ϣ�
	�κ�ָ���ȼ� 500  ���ϣ�
	��Ԫ���ĵȼ� 500  ���ϣ�
	����ָ���ȼ� 500  ���ϣ�
	����ָ���ұ�Ϊ�κ�ָ��
	�����ڹ�Ϊ��Ԫ����
HELP
        );
        return 1;
}
