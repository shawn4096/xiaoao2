// By sohu@xojh
#include <ansi.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h"

string perform_name() { return HIR"���־�"NOR; }

int perform(object me, object target)
{
        int damage, p;
        object weapon, weapon1;
        string msg, dodge_skill, *limbs, limb;
        
        if( !target ) target = offensive_target(me);
        weapon = me->query_temp("weapon");
        if( !objectp(target)  || !target->is_character() || !me->is_fighting(target) 
         || environment(target)!=environment(me))
                return notify_fail("��ָ��ֻͨ�ܶ�ս���еĶ���ʹ�á�\n");
        if( (int)me->query_skill("tanzhi-shentong", 1) < 300 )
                return notify_fail("��ĵ�ָ��ͨ��δ�����ʹ��������ָ��ͨ��\n");
        if( (int)me->query_skill("bihai-chaosheng", 1) < 300)
                return notify_fail("��ı̺���������δ�����\n");     
        if( (int)me->query_skill("throwing", 1) < 300 )
                return notify_fail("��Ļ���������δ�����ʹ��������ָ��ͨ��\n");
		if( me->query_skill_mapped("finger") !="tanzhi-shentong" 
			|| me->query_skill_mapped("parry") !="tanzhi-shentong"
			|| me->query_skill_prepared("finger") !="tanzhi-shentong")
                return notify_fail("��ļ������书���ԣ�ʹ��������ָ��ͨ��\n");
        if (me->query_skill_mapped("force")!="bihai-chaosheng")
                return notify_fail("��ļ������ڹ����ԣ�ʹ��������ָ��ͨ��\n");
		if( (int)me->query("max_neili", 1) < 3000 )
                return notify_fail("����ڹ���Ϊ������ʹ����ָ��ͨ������\n");
        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("�������������ʹ����ָ��ͨ������\n");
        if(target->is_busy())     
                return notify_fail("�Է����Թ˲�Ͼ�أ��ŵ������ɡ�\n");
		if( me->query_temp("thd/tan"))     
                return notify_fail("������ʹ�õ�ָ��ͨ��\n");
		if( target->query_temp("thd/tan"))     
                return notify_fail("�Է��Ѿ����˵�ָ��ͨ��\n");
       // if (!objectp(weapon = me->query_temp("weapon")) 
			//&& (int)me->query_skill("tanzhi-shentong", 1) < 350)
               // return notify_fail("�������޷�ʹ�õ�ָ��ͨ���־���\n");
       if(weapon && (weapon->query("skill_type") != "throwing"
        || me->query_skill_mapped("throwing") != "tanzhi-shentong"))
                return notify_fail("�����ڵ������޷�ʹ�õ�ָ��ͨ���־���\n");
        if(weapon){
                if(weapon->query("skill_type") != "throwing" || me->query_skill_mapped("throwing") != "tanzhi-shentong")
                         return notify_fail("�����ڵ������޷�ʹ�õ�ָ��ͨ��\n");
                msg = HBRED"\nֻ��$N"HBRED"˫��΢�Σ�������ָ����"+weapon->name()+HBRED+"����һ�������$P���������ֱ��$n"HBRED"��ȥ��\n"NOR; 
                }
        else msg = HBGRN"\n$N"HBGRN"�����ھ���ָ����׼�������$n"HBGRN"һ����һ˿�����������������$p��ǰ��Ѩ��\n"NOR; 
        
        me->add("neili", -350);
      
        limbs = target->query("limbs");
        limb = limbs[random(sizeof(limbs))];
        me->set_temp("thd/tan",1);

        if( random((int)me->query_dex()) < (int)target->query_dex()/2) {
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
				me->start_busy(2);
				me->delete_temp("thd/tan");
				message_vision(msg, me, target);
				me->start_perform(2, "���־�");
                return;
        } else if (weapon && objectp( weapon1 = target->query_temp("weapon")) && random(2)) {
                if( random((int)me->query_dex()) > (int)target->query_dex()/2
					||random(me->query("combat_exp"))>target->query("combat_exp")/2){
                         weapon1->unequip();
                         weapon1->move(environment(target));
                         target->reset_action();
						 msg += HIR"$n"HIR"ֻ�����ֱ�һ�飬�ѱ�$N"HIR"��"+weapon->name()+HIR+"������Ѩ�������������ذ����е�"+weapon1->name()+HIR+"׹�أ�\n"NOR;
                         if(!target->is_busy()) target->start_busy(3);
                         else target->add_busy(3+random(2));
						 if (userp(target))
						 	target->add_busy(2);
						 target->set_temp("thd/tan",1);
						 
						 
                } else {
                         dodge_skill = target->query_skill_mapped("dodge");
                         if( !dodge_skill ) dodge_skill = "dodge";
                         msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                }
        } else {
                damage = me->query_skill("finger",1) + me->query_skill("throwing",1) + me->query_temp("thd/is_fast");
                if(me->query("neili") > target->query("neili")*2)
                         damage *= 3;
                target->receive_damage("qi", damage, me);
				target->receive_wound("qi", damage/3, me);
                if(weapon)
                         target->receive_wound("qi", damage/3+random(damage/3), me);
                if(!target->is_busy()) 
                         target->start_busy(3+random(2));
				else target->add_busy(2+random(2));
				if (userp(target))
				{
					target->add_busy(2);
				}
				target->set_temp("thd/tan",1);

                p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
                msg += damage_msg(damage, "����");
                msg += "( $n" + eff_status_msg(p) + " )\n";
                msg = replace_string(msg, "$l", limb);
                msg = replace_string(msg, "$w", weapon?weapon->name():"���ν���"); 
        }
        call_out("remove_tan",1,me,target,(int)me->query_skill("tanzhi-shentong",1)/20);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
        message_vision(msg, me, target);
		
		if (me->query_skill("tanzhi-shentong",1)<350)
           me->start_perform(2, "���־�");
        me->delete_temp("thd/tan");
		return 1;
}

void remove_tan(object me,object target,int i)
{
   if (!me) return;
   if (!target || !living(target)) return;

   if ( i<0 ||!me->is_fighting() )
   {
       me->delete_temp("thd/tan");
	   target->delete_temp("thd/tan");
	   message_vision(HIY"$N�����չ�������ָ��ͨ����ѹ��������,����һ������\n"NOR,me);
	   return;
   }
   if (random(6)>3)
   {
	   message_vision(HIG"$N�˾�����ָ�������ڵ�ָ��ͨ�����е���$n��\n"NOR,me,target);
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
   }
   call_out("remove_tan",1,me,target,i-3);
   return;
}

int help(object me)
{
        write(HIR"\n��ָ��֮ͨ�����־�����"NOR"\n");
        write(@HELP

	��ָ��ͨ���ǻ���а�Ķ����似���Դ�����
	ʩչ��ָ��ͨ��������ϣ����̺���������
	�ھ�������ͬһ��ϸ���������֣����ǽ���
	�����Ӿ�����������˺�����֮���ʹ����
	Ѫ���ڣ������������б���Ҳ�п����޷�ʹ
	�������䡣ע������������С�

	perform finger.tan

Ҫ��
	�̺������ȼ� 300 ���ϣ�
	��ָ��ͨ�ȼ� 300 ���ϣ�
	����ָ���ȼ� 300 ���ϣ�
	���������ȼ� 300 ���ϣ�
	�������Ҫ�� 3000 ���ϣ�
	�����ұ�ָ��Ϊ��ָ��ͨ��
	�����мܵ�ָ��ͨ��
	�����ڹ��̺�������
	���������תʹ�ù����˺����ӣ�
	����ϰ���ʹ��,350�����Ծ��
HELP
);
        return 1;
}

