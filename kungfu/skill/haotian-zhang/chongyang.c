//sohu@xojh
//����������


#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
#include <combat_msg.h>

string *xing=({"��"HIR"�����"NOR"��","��"HIG"������"NOR"��","��"HIY"������"NOR"��","��"HIB"��Ȩ��"NOR"��","��"HIM"�����"NOR"��","����"HIC"������"NOR"��","����"HIW"ҡ����"NOR"��"});
int next1(object me, object target);

int next(object me, object target);

int perform(object me, object target)
{
	int skill;
	string weapon;
	int damage;
	string *limbs,str,type, limb,qxing;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("��������������ֲ���ʩչ��\n");

	if( me->query_skill_mapped("strike") != "haotian-zhang" )
		return notify_fail("�����õĲ����������ƣ�����ʩչ���������ƣ�\n");

	if( me->query_skill_prepared("strike") != "haotian-zhang" )
		return notify_fail("�������Ĳ����������ƣ�����ʩչ���������ƣ�\n");

	if( me->query_skill_mapped("force") != "xiantian-gong" )
		return notify_fail("�����õĲ����������칦��ʩչ�������������ƣ�\n");
	
	if( me->query_skill_mapped("parry") != "haotian-zhang"
		&& me->query_skill_mapped("parry") != "kongming-quan")
		return notify_fail("�����õ��мܲ�������ƻ����ȭ������ʩչ���������ƣ�\n");
	
	if( !me->query("quest/qz/htz/chongyang/pass"))
		return notify_fail("����δϰ�ø����񹦣�ʩչ�������������ƣ�\n");

	if( me->query_skill("force",1) < 500 )
		return notify_fail("��Ļ��������δ�����޷�ʩչ���������ƣ�\n");
	if( me->query_skill("xiantian-gong",1) < 500 )
		return notify_fail("������칦���δ�����޷�ʩչ���������ƣ�\n");
	if( me->query_skill("haotian-zhang",1) < 500 )
		return notify_fail("�������ƻ��δ�����޷�ʩչ���������ƣ�\n");
	
	if( me->query_skill("yuanyang-lianhuantui",1) < 500 )
		return notify_fail("���ԧ�������ȷ����δ�����޷�ʩչ���������ƣ�\n");

	if( me->query_skill("strike",1) < 500 )
		return notify_fail("������������Ҫ��տ���������Ʒ�����Чʩչ��\n");

	if( me->query("neili") <= 3000 )
		return notify_fail("�����������3000,�޷�ʹ�����������ƣ�\n");

	message_vision(HIC "$NĬ�����칦��������ձ���������Ȼ��˸��������ƹ�Ȼ�������󣬾�Ȼ�������Ƕ�֮����\n"
	+"$N"HIC"������Ѿõ�������Ȼ�ŷ������һ��������������ʩչ������ƾ������������ƣ�\n\n" NOR, me, target);

	skill = me->query_skill("haotian-zhang",1)+ me->query_skill("xiantian-gong",1) / 6;
	
	me->add_temp("apply/attack",skill/5);
	me->add_temp("apply/damage",skill/5);

	me->set_temp("htz/chongyang",1);
	qxing=xing[random(sizeof(xing))];

	message_vision(qxing +HIY"һ�Σ������Ƕ�֮�������������Х������\n\n" NOR, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

	message_vision(qxing +HIC"һ�Σ��ڶ���������תѸ������\n\n" NOR, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

	message_vision(qxing +HIG"һ�Σ�������������Ӱ���Σ�\n\n" NOR, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	


	if (me->query("env/����������")=="�����۶�"&&me->query_temp("htz/sanhua")>0 && me->query_skill("haotian-zhang",1)>500)
	{
		me->add_temp("htz/sanhua",-1);
		message_vision(HIR "$N�����������ͷ����һ������С������ת���ع���˫�֣����ɾ���������һ����Ȼ����һ�ƣ�\n\n" NOR, me, target);
		me->add_temp("apply/strike",skill/6);
		me->add_temp("apply/damage",skill/6);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		me->add_temp("apply/strike",-skill/6);
		me->add_temp("apply/damage",-skill/6);
		me->add("neili",-1000);
		me->add("jingli",-600);
	}
	if (me->query("env/����������")=="�����۶�"&&me->query_temp("htz/sanhua")>0 && me->query_skill("haotian-zhang",1)>550)
	{
		me->add_temp("htz/sanhua",-1);
		message_vision(HIY "$N�����۶�����������ɢ��ͷ���ĵڶ�����������������˫�ƣ��������£�\n\n" NOR, me, target);
		me->add_temp("apply/strike",skill/5);
		me->add_temp("apply/damage",skill/5);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		me->add_temp("apply/strike",-skill/5);
		me->add_temp("apply/damage",-skill/5);
		me->add("neili",-1200);
		me->add("jingli",-700);

	}
	if (me->query("env/����������")=="�����۶�"&&me->query_temp("htz/sanhua")>0 && me->query_skill("haotian-zhang",1)>600)
	{
		me->add_temp("htz/sanhua",-1);
		message_vision(HIM "$N�����ͷ��һ�����������Ʒ��У����ɾ������ӣ��Ʒ���������쳣��\n\n" NOR, me, target);
		me->add_temp("apply/strike",skill/5);
		me->add_temp("apply/damage",skill/5);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		me->add_temp("apply/strike",-skill/5);
		me->add_temp("apply/damage",-skill/5);
		me->add("neili",-1200);
		me->add("jingli",-700);

	}

	message_vision( HIY "\n������$NͻȻ�ڿշ���ʹ��һ��ԧ�������ȣ����ȷ�۵糸��������$n\n" NOR,me,target);
	if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/2)
	{
		if( ( target->query_skill("dodge")+target->query_skill("parry") ) < random((me->query_skill("strike") + me->query_skill("force"))*2/3) )
		{
			message_vision(HIR"ֻ��$Nһ���ҽУ����������������Ŀڡ�����$nһ������ͻȻƽƽ�ɳ����ڵ�һ�죬���������������֮�⣬ֱͦͦ�����ڵ��£���Ҳ������\n\n"NOR, target,target );
                        damage = (int)target->query("eff_qi");
                        target->receive_wound("qi", (damage>0?damage:-damage), me);
                        damage = (int)target->query("qi");
                        target->receive_wound("qi", (damage>0?damage+1:1-damage), me);
			me->add("neili", -me->query("jiali"));
		}
		else
		{
			damage = random((int)me->query_skill("strike")+me->query("jiali")) ;
			if(damage > 5000) damage = 5000;
			//if(damage < 1000) damage = 1000;
			me->add("neili", -me->query("jiali"));

			target->receive_damage("qi", damage,  me);
			target->receive_wound("qi", damage/3, me);

			limb = target->query("limbs");
			type = "����";
			message_vision("ֻ��$Nһ���ҽУ���������������$P"+limb[random(sizeof(limb))]+"�������$P��ˤ�˸���ͷ��\n",target);

			str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
			message_vision("($N"+str+")\n", target);
		}
		me->start_busy(1+random(2));
	}
	else if( ( random( target->query_skill("dodge") ) >  me->query_skill("strike")*2/3) && random(5) == 1 )
	{
		message_vision(HIR"$N�;��þ�����������֪�����æ���������$n���˸��գ��װ��Լ����ص���һ�ӡ�\n\n"NOR, target,me );
		me->receive_wound("qi", 30+random(50),  me);
		me->start_busy(2+random(2));
		str = COMBAT_D->status_msg((int)me->query("qi") * 100 /(int)me->query("max_qi"));
		message_vision("($N"+str+")\n", me);
	}
	else
	{
		message_vision( "$N�ۼ���һ���������ͣ�����˫��һ�㣬Ծ���ĳߣ��㿪��$n��һ�У�����Ҳ����һ���亹��\n\n" NOR,  target,me);
		me->start_busy(2);
	}
	//��˪�Ʊ���
	if (objectp(target)&&me->is_fighting())
	{
		next(me,target);
		//return 1;
	}
	me->add_temp("apply/attack",-skill/5);
	me->add_temp("apply/damage",-skill/5);
	me->add("neili", -random(me->query_skill("strike",1)/4) -100 );
	me->start_busy( 2+random(2) );
	me->start_peform(6,"����������");
	return 1;
}


int next(object me, object target)
{
        string msg;
        int damage, ap, dp;
        object weapon;
        if( !me ) return 0;
        weapon = me->query_temp("weapon");
        if (weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("htz/lianhuan");
                return 0;
        }
		if (me->query_skill_mapped("strike")!="haotian-zhang"
		||me->query_skill_prepared("strike")!="haotian-zhang") return 0;
		
        msg = HIG"\n$N����һ��������ʩչ�������"HBCYN+HIG"����˪�Ʊ��ơ�"NOR+HIG"������\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1)/100000;
        dp = target->query("combat_exp", 1) * target->query_str(1)/100000;
		//100000����ap,dp���Է���� by sohu@xojh
       if(objectp(target)&&((userp(target)&& random(ap + dp) > dp) || !userp(target)))
	   {

                    damage = me->query_skill("haotian-zhang",1)*3;

					damage += me->query_skill("strike",1)*3;

					damage += random(damage);
                if ( damage > 6000 )
					damage = 6000 + (damage - 1000)/100;
				//if( damage>= target->query("qi",1)) damage= target->query("qi",1)-1;
                
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
                me->start_perform(3 + random(2),"�����������ơ�");
        } 
        else {
                msg = msg + HIW "$nһ�����ذδУ�Ծ�����ɣ������ܹ���\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
        me->delete_temp("htz/lianhuan");
		me->start_perform(6,"����������");
        return 1;
}


string perform_name(){ return HIR"����������"NOR; }
int help(object me)
{
        write(HIC"\n�����֮�����������ơ���"NOR"\n");
        write(@HELP
	��������������ʦ���������۱������ǣ�����������������
	֮���������Ʒ���������ʽ���棬����������������
	�������ǰ��ϣ�ң���Ӧ��������������������������ȫ��
	������Ȼ��ˣ�����Խ����񣬴�������Խ��
	
	ע�⣺set ���������� �����۶� Ч�������ͷ�ͷ�������
	������������Ϊ�ķ��������������޴󣬹������������á�

	ָ�perform strike.chongyang

Ҫ��
	���칦���ĵȼ� 500  ���ϣ�
	ԧ�������ȵȼ� 500  ���ϣ�
	�����ȷ��ĵȼ� 500  ���ϣ�
	����Ʒ��ĵȼ� 500  ����
	�����Ʒ��ĵȼ� 500  ����
	�����ڹ��ĵȼ� 500  ����
	��ǰ������Ҫ�� 3000  ���ϣ�
	�����ұ��Ʒ�Ϊ����ƣ�
	�����ȷ�Ϊԧ�������ȣ�
	�����ڹ�Ϊ���칦��
	�����ұ��Ʒ�Ϊ����ơ�
HELP
        );
        return 1;
}
