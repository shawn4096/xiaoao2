//cre by sohu
//��˪�Ʊ���
//ȫ����似

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
        int i = me->query_skill("haotian-zhang",1) ;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("��˪�Ʊ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("����ڹ��������칦���޷�ʹ����˪�Ʊ��ƣ�\n");


        if( me->query_skill("xiantian-gong", 1) < 250 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ����˪�Ʊ��ƣ�\n");

        if( me->query_skill("haotian-zhang", 1) < 250 )
                return notify_fail("�������Ʒ���δ���ɣ�����ʹ����˪�Ʊ��ƣ�\n");

        if (me->query_temp("weapon"))
               return notify_fail("�������б������޷�ʹ����˪�Ʊ��ƣ�\n");
   
        if (me->query_skill_prepared("strike") != "haotian-zhang"
            || me->query_skill_mapped("strike") != "haotian-zhang")
                return notify_fail("��û�м�����ʹ������ƣ������޷�ʹ�á���˪�Ʊ��ơ����й�����\n");  
        if (me->query_skill_mapped("leg") != "yuanyang-lianhuantui")
                return notify_fail("����Ҫ�����ȷ�Ϊԧ�������ȣ�����ʹ�á���˪�Ʊ��ơ����й�����\n");  

        if(me->query_skill_mapped("parry") != "haotian-zhang"
			&& me->query_skill_mapped("parry") != "kongming-quan")
                return notify_fail("����мܹ��򲻶ԣ��޷�ʹ����˪�Ʊ��ƣ�\n");

        if(me->query("max_neili") < 3500 )
                return notify_fail("���������Ϊ����������ʹ����˪�Ʊ��ƣ�\n");
        if(me->query("neili") < 1000 )
                return notify_fail("�������������㣬����ʹ����˪�Ʊ��ƣ�\n");
        if(me->query("jingli") < 600 )
                return notify_fail("�����ھ������㣬����ʹ����˪�Ʊ��ƣ�\n");
        if(me->query_temp("htz/pobing"))
                return notify_fail("������ʹ����˪�Ʊ��ƣ�\n");

        if(me->query_skill("strike", 1) < 250 )
                return notify_fail("��Ļ��������Ʒ�������죬�����ڽ�����ʹ����˪�Ʊ��ơ�\n");


        msg = HBRED+HIW"\n$Nȫ������������ʹ������ƾ���"NOR+HIR"����˪�Ʊ��ơ�"+HBRED+HIW"��$nֻ��$N��������ӿ���ȣ��Ʋ��ɵ���\n"NOR;
        message_vision(msg, me, target);
		
		if (target->query_skill_prepared("strike")=="hanbing-shenzhang"
			||target->query_skill_prepared("strike")=="huagu-mianzhang"
			||target->query_skill_prepared("strike")=="hanbing-mianzhang"
			||target->query_skill_prepared("hand")=="songyang-shou")
		{
			if (random(me->query("combat_exp"))>target->query("combat_exp")/2)
			{
				message_vision(HIM"$N��$nʩչ�����������������칦���Ķ��������������������$n����������!\n"NOR,me,target);
				target->start_busy(3);
				target->apply_condition("no_perform",1);
			}
		}
            me->add_temp("apply/attack", me->query_skill("haotian-zhang") /4);

			me->add_temp("apply/damage", me->query_skill("haotian-zhang") /4);
            me->set_temp("htz/pobing", 1);
             
        //��һ�й���
        if (me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("haotian-zhang") /4);
		
me->add_temp("apply/damage", -me->query_skill("haotian-zhang") /4);

        me->add("neili", -150);
//�ϱ���
		weapon = target->query_temp("weapon");

		if( objectp(weapon) 
			&& me->query("env/�����")=="��"
			&& me->query_temp("xtg/wuqi"))
		{
			ap =   me->query("force")/5
			+ (int)me->query("haotian-zhang")/5
			+ (int)me->query_str()
			+ (int)me->query("jiali");

			dp = (int)weapon->weight() / 500
			+ (int)target->query_str()
			+ (int)target->query("jiali")
			+ (int)target->query_skill("parry")/3;

			ap = ap/2 + random(ap/2);

			if( ap > 3 * dp ) {
				message_vision(HIY"ֻ��$N���ϵ�$n"+HIY+"�ѱ�һ����ϡ�\n"NOR, target, weapon);
				weapon->unequip();
				weapon->move(environment(target));
				weapon->set("name", "�ϵ���" + weapon->query("name"));
				weapon->set("value", 0);
				weapon->set("weapon_prop", 0);
				target->reset_action();
				me->add("neili", -150); // to break weapon takes more neili
			} else if( ap > 2 * dp ) {
				message_vision(HIW"$Nֻ��������" + weapon->name() + "��һ����ðѳֲ��������ַɳ���\n" NOR, target);
				weapon->unequip();
				weapon->move(environment(target));
				target->reset_action();
				me->add("neili", -120); // to break weapon takes more neili
			} else if( ap > dp ) {
				message_vision("$Nֻ��������" + weapon->name() + "һ����Щ���֣�\n", target);
				me->add("neili", -100); // to break weapon takes more neili
			}
		}


        if ( me->query_skill("xiantian-gong", 1) > 250)
                next1(me, target, i);
        else  me->delete_temp("htz/pobing");
        me->start_perform(3, "����˪�Ʊ��ơ�");
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
                me->delete_temp("htz/pobing");
                return 0;
        }
        msg = HIY"\nһ��Խ����������������������$N��ǰ��˫�����ƣ�ӡ��$n����ǰ������������糱ˮ��ӿ��$n��\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1)/10000;
        dp = target->query("combat_exp", 1) * target->query_str(1)/10000;
        if((userp(target)&& random(ap + dp) > dp )|| !userp(target)){
                msg += HIR"$nֻ����һ�����ײ����ӿ���ȣ�ֱײ���Լ���ǰ�ǹ���á�\n"NOR;
                damage = me->query_skill("haotian-zhang",1)*3;

				damage += me->query_skill("strike")*3;
				
damage += random(damage);
        if ( damage > 3000 )
				damage = 3000 + (damage - 1000)/10;

		if(damage>= target->query("qi")) damage= target->query("qi")-1;

                target->add("neili",-(300+random(150)));
                target->receive_damage("qi", damage, me);
        if(userp(me) && me->query("env/damage"))
        	tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage+ WHT"�㹥���˺���\n"NOR);
		
if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage+ WHT"���˺���\n"NOR);
		
        target->receive_wound("qi", damage/2, me);
                msg += damage_msg(damage, "����");
                message_vision(msg, me, target);
                COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", me->query_skill("haotian-zhang") /4);

		me->add_temp("apply/damage", me->query_skill("haotian-zhang") /4);

        if(!random(5))
			target->add_condition("no_perform", 1);
        if(!random(5))
			target->add_condition("no_exert", 1);
        if(!userp(target))    target->add_busy(2);
        if (me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        me->add_temp("apply/attack", -me->query_skill("haotian-zhang") /4);

		me->add_temp("apply/damage", -me->query_skill("haotian-zhang") /4);

                me->add("neili",-200);
                me->add("jingli",-80);
                me->start_perform(3, "����˪�Ʊ��ơ�");
        }
        else {
                msg  += CYN"\n$nһ��������Ծ��Σ��֮�ж������һ����\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                me->add_busy(random(2));
        }
        if (me->query_skill("haotian-zhang", 1) > 250)
                next2(me, target, i);
        else
                me->delete_temp("htz/pobing");
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
                me->delete_temp("htz/pobing");
                return 0;
        }
		if (me->query_skill_mapped("leg")!="yuanyang-lianhuantui") return 0;
		
        msg = HIG"\n$nֻ���Է������೤�������ڹ���ʵ�˵ã�ֻ��ƣ�ڷ��أ���ʱ$N˲�����ƣ�����ȴ��һ��ԧ���ȵ���ʽ��һ��ɨ����\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1)/100000;
        dp = target->query("combat_exp", 1) * target->query_str(1)/100000;
		//100000����ap,dp���Է���� by sohu@xojh
       if(objectp(target)&&((userp(target)&& random(ap + dp) > dp) || !userp(target)))
	   {

                    damage = me->query_skill("haotian-zhang",1)*3;

					damage += me->query_skill("strike",1)*3;

					damage += random(damage);
                if ( damage > 4000 )
					damage = 4000 + (damage - 1000)/100;
				//if( damage>= target->query("qi",1)) damage= target->query("qi",1)-1;

                target->add_temp("apply/attack", -180);
                target->add_temp("apply/dodge", -180);
                target->add_temp("apply/parry", -180);
                target->set_temp("htz/pobing",1);

				target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                
				msg += damage_msg(damage, "����");
                message_vision(msg, me, target);

				if(objectp(target) && me->query("env/damage"))
					tell_object(me,WHT"���"+ target->query("name") +"�����"HIR+ damage+ WHT"�㹥���˺���\n"NOR);
				//
if(userp(target)&& target->query("env/damage"))
					//tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"HIR+ damage+ WHT"���˺���\n"NOR);
				
COMBAT_D->report_status(target, random(2));

				me->add_temp("apply/attack", (int)me->query_skill("xiantian-gong") /4);

				me->add_temp("apply/damage", (int)me->query_skill("xiantian-gong") /4);
				if (me->is_fighting(target))
						COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

				me->add_temp("apply/attack", -(int)me->query_skill("xiantian-gong") /4);

				me->add_temp("apply/damage", -(int)me->query_skill("xiantian-gong") /4);
                me->add("neili",- 150);
                me->add("jingli",-80);
                me->start_perform(3 + random(2),"����˪�Ʊ��ơ�");
				if (objectp(target))
				    call_out("back", 5 + random(me->query("jiali") / 20), target);
        } 
        else {
                msg = msg + HIW "$nһ�����ذδУ�Ծ�����ɣ������ܹ���\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
        me->delete_temp("htz/pobing");
		me->start_perform(3,"��˪�Ʊ���");
        return 1;
}

void back(object target)
{
        if (!target) return;
        target->add_temp("apply/attack", 180);
        target->add_temp("apply/dodge", 180);
        target->add_temp("apply/parry", 180);
		target->delete_temp("htz/pobing");
		return;
}

string perform_name(){ return HIG"��˪�Ʊ���"NOR; }
int help(object me)
{
        write(HIC"\n�����֮"+RED"����˪�Ʊ��ơ���"NOR"\n\n");
        write(@HELP
	�����������������ȫ��̵ĸ߼��Ʒ����������ͨ���ϣ�
	����ԭ��β��Ѩ���ȴ�ӿȪ�ŵ׳壬ӿȪ������ϥ����ϥ
	������β�̣����趥�ϻ������������ش���ȵ�ţ���¥ʮ��
	�����ҡ��仯��΢����ȫ��̵�ȫ���ķ�������á�����ʹ
	�����У����ǵ��������ݺὭ����������ʽ��
	ע����˪�Ʊ��ƶ������������Ʒ���һ���������á�

	ע�⣺set ����� �� �书ЧΪ��϶Է�����
			
	ָ�perform strike.pobing

Ҫ��
	��ǰ�������� 1000 ���ϣ�
	����������� 3500 ���ϣ�
	��ǰ�������� 600 ���ϣ�
	�����Ʒ��ȼ� 250 ���ϣ�
	���칦�ĵȼ� 250 ���ϣ�
	�����Ʒ��ȼ� 250 ���ϣ�
	�����ȷ��ȼ� 250 ���ϣ�
	�����Ʒ�Ϊ����Ʒ���
	�����м�Ϊ����ƻ����ȭ��
	�����ȷ�Ϊԧ�������ȣ�
	�����ڹ�Ϊ���칦��
	׼���Ʒ�Ϊ����ơ�
HELP
        );
        return 1;
}
