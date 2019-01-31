// zhen.c ̫��ȭ�������־�
// snowman
#include <ansi.h>

inherit F_SSERVER;
string *taiji_msg = ({"��ȸβ","����","��������","�׺�����","§ϥ����","��������","��̽��",
"����ʽ","������","�𼦶���","��Ů����","��������","�乭�仢","������ɽ",});

string perform_name(){ return HIG"���־�"NOR; }

int perform(object me, object target)
{
	int damage, force, ap, dp,skill;
	string msg, *limbs;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
		return notify_fail("�������־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( userp(me) 
	&&( me->query_skill_mapped("parry") != "taiji-quan"
	&& me->query_skill_mapped("parry") != "taiji-jian") )
		return notify_fail("�����־�����������̫��ȭ��̫���������мܵ�����²���ʹ�á�\n");

	if( userp(me) && (me->query_skill_mapped("force") != "yinyun-ziqi"
	|| me->query_skill_prepared("cuff") != "taiji-quan") )
		return notify_fail("����ڹ���ȭ�����ԣ��������ܷ��ӳ������־��������ơ�\n");  

	if( me->query_skill("taiji-quan", 1) < 350 )
		return notify_fail("̫��ȭҪּ�����ɷ��ɣ���̫��ȭ�ȼ�̫�ͣ��������ʹ�á������־���\n");
    if( me->query_skill("yinyun-ziqi", 1) < 350 )
		return notify_fail("̫��ȭ��Ҫ������������ϣ�û��ǿ����ڹ��������ʹ�á������־���\n");
     if( (int)me->query("max_neili", 1) < 5000 )
		return notify_fail("�������������������ǿ��ʹ�á������Ƿ��Ӳ������������ģ�\n");
	if( (int)me->query("neili", 1) < 1500 )
		return notify_fail("����������������ǿ��ʹ�á������Ƿ��Ӳ������������ģ�\n");

	if( (int)me->query("jingli", 1) < 1000 )
		return notify_fail("�����ھ���������ǿ��ʹ�á������Ƿ��Ӳ������������ģ�\n");                     

	if( me->query_temp("weapon"))
		return notify_fail("���ȷ������е�������˵�ɣ���\n");     

	limbs = target->query("limbs");
	skill=me->query_skill("taiji-quan",1);
	msg = WHT "\n$N"WHT"ʹһ��̫��ȭ��"+taiji_msg[random(sizeof(taiji_msg))]+WHT"�����ҽ�ʵ������飬����"RED"������"WHT"�־���ճ��ճ�棬�����Ѵ�ס$p"+limbs[random(sizeof(limbs))]+"��\n"NOR;
        
	force = me->query_skill("force",1) + target->query_skill("force",1);

	ap = me->query("combat_exp") /100000 * me->query_skill("force",1);
	dp = target->query("combat_exp")/ 100000 * target->query_skill("parry",1);
    if (me->query("yyzq/taiji"))
      ap+=ap/2;
	
	me->add_temp("apply/attack",skill/4);		
	me->add_temp("apply/damage",skill/8);

	if( random(ap + dp) > dp 
		||random(me->query_int(1))>target->query_int(1)/3)
	{
		target->add_busy(2+random(3));
		damage = (int)me->query_skill("force",1)+(int)me->query_skill("yinyun-ziqi",1);                
		damage=damage+random(damage);

		if(me->query("neili") > target->query("neili")*2/3) 
			damage *= 2;
		else if(me->query("neili") > target->query("neili")) 
			damage += random(damage);
		else if(me->query("neili")*1.5 < target->query("neili")) 
			damage /= 2;
		else if(me->query("neili") < target->query("neili")) 
			damage -= random(damage/2);
		else damage = damage/2 + random(damage);
                
		if(damage> 4000) damage = 4000+(damage-4000)/10; 
		target->receive_damage("jingli", damage,me);
		target->receive_damage("neili", damage/2);
	    target->receive_wound("jing", me->query_int(1)*2+ me->query_con(1)*2, me);
		me->add("neili", -300);
		me->add("jingli", -100);
		msg += HIR"����$P�ᾢ������$p����ôһ�������ӱ��Լ��ľ������ò���������ǰһ�壬���������\n"NOR;
		message_vision(msg, me, target);
		if (!userp(target)) {
			me->set_temp("tjq/jiadd",skill);
			me->add_temp("apply/damage",skill/8);
		}

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		

		if (me->query_temp("tjq/jiadd"))
		{
			me->delete_temp("tjq/jiadd");
			me->add_temp("apply/damage",-skill/4);		
		}
	}
	else{
		me->add("jingli", -25);
		me->add("neili", -100);
		msg += HIY"$p�����龰��һ�����棬��æ�ջ��Լ��ľ�����������ã��������һ�У�\n"NOR;
		message_vision(msg, me, target);
		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
	}
	

	me->add_temp("apply/attack",-skill/4);		
	me->add_temp("apply/damage",-skill/8);

	me->start_busy(1+random(1));
	me->start_perform(3, "������"); 
	
	return 1;
}

int help(object me)
{
	write(WHT"\n̫��ȭ��֮"HIG"�����־�����"NOR"\n");
	write(@HELP
	̫��ȭ�����䵱��ɽ����������������������������һ�Ź�������������
	������죬�����������������ĸ�����ѧ������ȭ���Ĵ�����ν�����
	�صĴ��£��ı����������ֵ���ѧ��ϵ����νǰ�޹��˺����ߣ�̫��ȭ��
	���־�����̫��ȭ�м�Ϊ�������ķ�������һ�����뵱�У�����������ʧ
	�Ӷ��γɱ�������ľ��档�ߵ��ڹ��͸����ԶԵ��˵ľ��ж�����˺���
	
	ָ�perform cuff.ji

Ҫ��	
	��ǰ���� 1500 ���ϣ�
	��ǰ���� 1500 ���ϣ�
	������� 5000 ���ϣ�
	������ 350  ���ϣ�
	̫��ȭ�� 350  ���ϣ�		
	����̫��ȭ�����ޱ�����
HELP
	);
	return 1;
}