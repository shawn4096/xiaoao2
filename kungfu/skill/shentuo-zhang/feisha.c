// This program is a part of NITAN MudLIB
// hama.c ��󡹦

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int damage, p, ap, dp;
        string msg, dodge_skill;

      //  if (userp(me) && ! me->query("can_perform/hamagong/hama"))
        //        return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ���ս���ɳ����\n");

        if (! target) target = offensive_target(me);

        if (! target || !target->is_character() || 
            ! me->is_fighting(target) || 
            ! living(target))
                return notify_fail("�ս���ɳ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("hamagong", 1) < 250)
                return notify_fail("��ĸ�󡹦����������������ʹ���ս���ɳ�ԵУ�\n");

        if (me->query_temp("weapon"))
                return notify_fail("�������ֲ���ʹ�á��ս���ɳ����\n");

        if (me->query_skill_mapped("force") != "hamagong")
                return notify_fail("����ڹ����޴˹���\n");

        if (me->query_skill_prepared("strike") != "shentuo-zhang" ||
            me->query_skill_mapped("strike") != "shentuo-zhang")
                return notify_fail("������Ƚ��������������Ʒ�֮�в��С�\n");

        if ((int)me->query("max_neili") < 2500)
                return notify_fail("����������������㣬ʹ���������Ƶľ����ս���ɳ��\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("�������������㣬ʹ���������Ƶľ����ս���ɳ��\n");

        if ((int)me->query_skill("strike", 1) < 250)
                return notify_fail("����Ʒ�������죬ʹ���������Ƶľ����ս���ɳ��\n");

        if (me->query_str() < 30 )
                return notify_fail("�������̫С��ʹ�����������ƾ����ս���ɳ��\n");

        msg = YEL "\n$N"YEL"���Ӷ��£�����ƽ�ƶ����������ݺᣬ������磬ʹ������$N��ƽ�����ġ��ս���ɳ�����У��Ʒ�ֱ��$n��ȥ��\n"NOR;

        ap = me->query_skill("shentuo-zhang",1);
        dp = target->query_skill("parry",1);

        if (ap / 2 + random(ap) > dp
			||random(me->query_str(1))>target->query_str(1)/2)
        {
                
                        
                me->add("neili", -200);
                
                damage = me->query_skill("shentuo-zhang",1)*me->query_str(1)/10;          
                
				if (me->query("neili") > random(target->query("neili")))
                        damage += random(damage);
                        
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                
                p = (int)target->query("eff_qi")*100/(int)target->query("max_qi");
                msg += COMBAT_D->damage_msg(damage, "����");
                msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
                call_out("perform2", 1, me, target, p, damage);    
        } else
        {
                                      
                me->add("neili", -100);
                tell_object(target, HIY"�㵫��һ��΢�����������������Ȼ������Ȼ�ѱƵ��Լ�����������֪�������æԾ�����ߡ�\n" NOR);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_vision(msg, me, target);
		 me->add("jingli", -200);
		me->start_perform(4,"�ս���ɳ");
        return 1;
}


int perform2(object me, object target, int p, int damage)
{
        int ap, dp;
        string msg, dodge_skill;

        if( !target || !me || !living(me)
           || !me->is_fighting(target) 
           || environment(target)!=environment(me) || !living(target))
                return 0;

        if( (int)me->query("neili", 1) < 500 )
                return notify_fail("���Ҫ�ٷ�һ�ƣ�ȴ�����Լ������������ˣ�\n");

        msg = HIR "\n$N���ƾ���δ��������Ҳ�����Ƴ���������������ս���ɳ���Ʒ���ɽ������ӿ��$n��\n"NOR;

        ap = me->query_skill("shentuo-zhang",1);
        dp = target->query_skill("parry",1);

     if (ap / 2 + random(ap) > dp
			||random(me->query_str(1))>target->query_str(1)/2)
        {
             
                me->add("neili", -300);
                damage = me->query_skill("shentuo-zhang",1)*me->query_str(1)/10;          

                if (me->query("neili") > random(target->query("neili")))
                        damage += random(damage);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += COMBAT_D->damage_msg(damage, "����");
                msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";                
                call_out("perform3", 1, me, target, p, damage);  
        }
       else
        {
            
                me->add("neili", -200);
                tell_object(target, HIY"�㴭Ϣδ�����־�һ�ɾ��������������æԾ�����ߣ��Ǳ��رܿ���\n" NOR);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_vision(msg, me, target);
		me->add("jingli", -200);
		me->start_perform(4,"�ս���ɳ");
        return 1;
}

int perform3(object me, object target, int p, int damage)
{
        int ap, dp;
        string msg, dodge_skill;

        if(! target || ! me || environment(me) != environment(target)) return 1;
        if(!living(target))
              return notify_fail("�����Ѿ�������ս���ˡ�\n");

        if( (int)me->query("neili", 1) < 700 )
                return notify_fail("���Ҫ�ٷ�һ�ƣ�ȴ�����Լ������������ˣ�\n");

        msg = HBYEL+HIR "\n$N˫��һ�ǣ�˫���ಢ��ǰ�����Ƴ���$n��ͬ��ǰ��Բ����ȫ�ڡ��ս���ɳ����������֮�£�\n"NOR;
       
		ap = me->query_skill("shentuo-zhang",1);
        dp = target->query_skill("parry",1);

		if (ap / 2 + random(ap) > dp
			||random(me->query_str(1))>target->query_str(1)/2)
        {
            
                me->add("neili", -400);
				damage = me->query_skill("shentuo-zhang",1)*me->query_str(1)/10;         
                if (me->query("neili") > random(target->query("neili")))
                        damage += random(damage) * 2;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                p = (int)target->query("eff_qi")*100/(int)target->query("max_qi");
                msg += COMBAT_D->damage_msg(damage, "����");
                msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";   
        } else
        {
         
                me->add("neili", -300);
                target->add("jingli", -100);
                tell_object(target, HIY"���þ�ȫ����������һ��һ����ҡҡ������վ��������������㿪����������һ����\n" NOR);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }

        message_vision(msg, me, target);
		me->add("jingli", -200);
		me->start_perform(4,"�ս���ɳ");
        return 1;
}


string perform_name(){ return HIW"�ս���ɳ"NOR; }

int help(object me)
{
	write(HIC"\n����ѩɽ��֮���ս���ɳ����"NOR"\n");
	write(@HELP
	����ѩɽ�����ǰ���ɽׯ����ŷ����Ķ��ž���������
	���ӵ��ۿ�̬֮������ѩɽ����֮����ʩչ�����У���
	���쳣�������ɽׯ�����ߺ͸�󡣬�����Ʒ����̺���
	�����󡶾��
	�ս���ɳ������Ⱥ����ɳĮ�зɽ�̬֮���������й���
	
	ָ�perform strike.shentuo

Ҫ��
	��ǰ���������� 1000 ���ϣ�
	��ǰ���������� 1000 ���ϣ�
	����ѩɽ�Ƶȼ� 250 ���ϣ�
	��󡹦�ȼ�     250 ���ϣ�
	�����Ʒ��ĵȼ� 250 ���ϣ�
	�����������   60  ���ϣ�
	�����Ʒ�Ϊ����ѩɽ�ƣ�
	�����ڹ�Ϊ��󡹦
	�����ұ��ã�
HELP
	);
	return 1;
}

