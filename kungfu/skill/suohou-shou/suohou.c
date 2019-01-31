// suohou.c ���� cre by sohu@xojhu 2014.1

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        string pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

    
	
		if (me->query_temp("weapon"))
			return notify_fail("�����������֡����ֲ���ʹ�á�\n");
        if (! target || ! me->is_fighting(target))
                return notify_fail("����������ֻ����ս���жԶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʹ�á�������\n");
                
        if ((int)me->query_skill("suohou-shou", 1) < 200)
                return notify_fail("���������������죬����ʹ�á�������\n");
       // if ((int)me->query_skill("huntian-qigong", 1) < 200)
                //return notify_fail("��Ļ���������������죬����ʹ�á�����������\n");  
		if ((int)me->query_skill("hand", 1) < 200)
                return notify_fail("��Ļ����ַ���������죬����ʹ�á�����������\n"); 
		if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("��Ļ����ڹ���������죬����ʹ�á�����������\n"); 
        if ((int)me->query("neili", 1) < 200)
                return notify_fail("����������̫��������ʹ�á�������\n");
        if ((int)me->query("max_neili", 1) < 1500)
                return notify_fail("�������������̫��������ʹ�á�������\n");
		if ((int)me->query("max_jingli", 1) < 1200)
                return notify_fail("�����ھ���̫��������ʹ�á�������\n");
		if (me->query_skill_mapped("hand")!="suohou-shou")
                return notify_fail("������û�м��������֣�����ʹ�á�������\n"); 
        msg = HIY "$N" HIY "��Цһ��������һԾ������¶�׹⣬���ֶ�Ȼץ"
              "��$n" HIY "�ĺ���\n\n" NOR;
        me->add("neili", -200);

        //me->want_kill(target);
        ap = me->query_skill("hand",1)+me->query_skill("suohou-shou",1);
        dp = target->query_skill("dodge",1)+target->query_skill("parry",1);
        if (random(ap+dp) > dp || !living(target)||random(me->query_str(1))>target->query_dex(1)/2)
        {
                //me->start_busy(2);
                me->add("neili", -180);
                damage = 0;

                if (me->query("neili") > target->query("neili") * 2 && userp(target))
                {
                        msg += HIR "\n���ֻ�����������������죬$N" HIR "��ָ�ѽ�$n"
                               HIR "���������飬$n" HIR "һ���������������̱����ȥ��\n" NOR;
                        damage = -1;
						
                } else
                {
                        target->add_busy(1 + random(3));
       
                        damage = ap + (int)me->query_skill("force",1);
                        damage = damage + random(damage);
                        
                        if (arrayp(limbs = target->query("limbs")))
                                limb = limbs[random(sizeof(limbs))];
                        else
                                limb = "Ҫ��";
                        msg += HIC "\n$n��æ��Ų������ֻ�������ꡱһ����$N"
                               HIC "��ָ������$n" HIC "��" +HIR+ limb +NOR "��$n"
                               HIC "һ���ҽУ���Ѫ�ɽ�������\n" NOR;
					    target->receive_damage("qi",damage,me);
						target->receive_wound("qi",damage/3,me);
						//target->recieve_wound("jing",damage/4,me);
                       // msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 66, pmsg);
                }
        } else 
        {
                me->start_busy(2);
                msg += CYN"����$p������$P����ͼ�����μ������㿪����һץ��\n"NOR;
        }

        message_combatd(msg, me, target);
		//me->add_temp("apply/attack",);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1); 
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1); 
        if (damage < 0)
        {
                target->receive_wound("qi",(int)target->query("qi")*2/3,me);
                //target->die();
        }
		
        return 1;
}

string perform_name(){ return HIR"�������"NOR; }

int help(object me)
{
        write(HIC"\n���������ַ�֮�������������"NOR"\n\n");
        write(@HELP 
	���������־�������ؤ���������ĳ����������ǽ�����
	�������ں���һ��ľ�������˫����ս�����У��ȿ���ͨ
	�����������������жԷ���Ѩ�����ֿ���ͨ���������һ
	���µС����Է��ʺ�Ҫ��֮������ס��һ�б�������ؤ��
	���ھ�����
	
	ָ�perform hand.suohou
			
Ҫ��  
	������� 1500 ���ϣ�
	����� 1200 ���ϣ�
	�������õȼ� 200 ���ϣ�
	�����ڹ��ȼ� 200 ���ϣ�
	�����ַ��ȼ� 200 ���ϣ�
	�����ַ�Ϊ���������֣�
	�����м�Ϊ���������֣�
	�ҿ���
HELP
        );
        return 1;
}