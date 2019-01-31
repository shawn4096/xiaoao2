// music.c
// modified by action@SJ 2009/1/10
// updated BY Zmud@Sjmud 10/3/2009
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	string msg, dodge_skill;
	object weapon;
	int ap, dp,i,skill;
    
	weapon = me->query_temp("weapon");
	if( !target ) target = offensive_target(me);
  
	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target)
	|| !living(target) )
		return notify_fail("���������ɡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
    
	if( (int)me->query_skill("qixian-wuxingjian", 1) < 350 )
		return notify_fail("����������ν��ȼ����㣬�޷�ʹ�á��������ɡ���\n");

	if( (int)me->query_skill("sword", 1) < 350 )
		return notify_fail("��Ļ��������ȼ����㣬�޷�ʹ�á��������ɡ���\n");

	if( (int)me->query_skill("force", 1) < 350 )
		return notify_fail("��Ļ����ڹ��ȼ����㣬�޷�ʹ�á��������ɡ���\n");

	if( (int)me->query("max_neili") < 5000 )
		return notify_fail("����������㣬�޷�ʹ�á��������ɡ���\n");

	if( (int)me->query("neili") < 2000 )
		return notify_fail("�������������\n");		

	if(me->query_skill_mapped("sword") != "qixian-wuxingjian"
	 || me->query_skill_mapped("parry") != "qixian-wuxingjian"  )
		return notify_fail("��û�м����������ν����޷�ʹ�á��������ɡ���\n");
    //ֻ���ٽ�������ʹ����
	if (me->query_temp("qxwxj/wuxian"))
		return notify_fail("������ʹ�á��������ɡ����й�����\n");
	
	if( !objectp(weapon)	 
	 || weapon->query("skill_type") != "sword"
	 || !weapon->query("qinjian"))
		return notify_fail("���������٣������ʹ���ˡ��������ɡ���\n");
	
	if( target->is_busy() )
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");
		
	ap = COMBAT_D->skill_power(me, "sword", SKILL_USAGE_ATTACK) + me->query("combat_exp")/10000;
	dp = COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE) + target->query("combat_exp")/10000;

	ap += me->query_int(1) * me->query_dex(1) ;
	dp += target->query_int(1) * target->query_con(1) ;
	
    skill=me->query_skill("qixian-wuxingjian",1);
	if( me->query_skill("qixian-wuxingjian", 1) > 350 )
		ap += random(ap/2);
        
		msg = "\n  "HIB"$N�������У���ָ��" + weapon->name() +HIB"����һ����" + weapon->name() +HIB"��������һ����������ĸ�Ƶ���ɣ�������֮�˸о������ذ���\n"NOR;
        message_vision(msg, me, target);  
                   
       message_vision(HIM"\n��" + weapon->name() +HIR"�ϲ��ҷ��������ǹ�ʾ��Ͼ��ȴ��������֮�й�ע�ϳ���������������"+
          "\n�������񣬹����̡��ǡ��ա������αŷ����������ܣ�$n����������һ������$n�㲻֪�����Լ���ʽ��Ϊ�������ơ�\n"NOR,me,target);


	if ( random( ap + dp ) > dp
		||random(me->query_int())>target->query_int()) {
		message_vision(HIR "\n$nֻ����$N����������" + weapon->name() +HIR"�����ġ�"HIB"��������"HIM"������һ�������㴩͸$n�Ĺ�Ĥ��\n"NOR,me,target);
		
		target->add_busy(2+random(2));
		if( !userp(target) ) target->add_busy(3);
		//�Է�������ң�����
		if( target->query_temp("lost_attack") < 1 )
			target->add_temp("lost_attack", 3+random(2));
		
		target->apply_condition("neishang",3);
		target->apply_condition("no_exert",2);
		target->add("neili",-3000);
		me->add("neili", -500);
		me->add("jingli", -300);
		me->set_temp("qxwxj/wuxian",skill);
		call_out("remove_effect",1,me,target,skill/10);
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
        message_vision(HIC "\n����$n����$N��ͼ����æ���������Ŭ��ʹ�Լ����ܡ�"HIB"��������"NOR+HIC"���ĸ��ţ���$n��������������֮�С�\n" NOR,me,target);

	    me->add("neili", -100);
		me->add("jingli", -50);
		me->start_busy(1);		
	}
	if (me->query_skill("qixian-wuxingjian",1)<350)
	   me->start_busy(1);
	if (me->query_skill("qixian-wuxingjian",1)<450) 
		me->start_perform(2, "���������ɡ�");

	message_vision(msg, me, target);
	return 1;
}


void remove_effect(object me, object target, int count)
{
        int skill;
		if (!objectp(me)) return;
	    skill=me->query_temp("qxwxj/wuxian");
		
		if (objectp(me) && me->query_temp("qxwxj/wuxian")){
                if (count-- > 0 && me->is_fighting(target)) {
                        call_out("remove_effect", 1, me, target, count);
                
                        return;
                }
		}
        message_vision(HIY"$N����ָ�������ÿ������ٴ�Ϣ��������������һ�󼲹��������Ĵ󣬲��ò������չ���\n"NOR,me);
        me->delete_temp("qxwxj/wuxian");
        
		return;
   
}

string perform_name(){ return HIC"��������"NOR; }
int help(object me)
{
         write(HIB"\n�������ν�"+HIC"���������ɡ�"NOR"\n");
        write(@HELP
	���������ν�������÷ׯ�������ϴ󣬻��ӹ��ĳ������������������ν���
	�ǻ��ӹ��Դ��ľ������Եе�ʱ��ͨ��������֮�й�ע�ϳ���������
	�����ҵ������񣬶Է�����������һ���������㲻֪������Ϊ�������ơ�
	�����滺���Է�����Ҳ�����滺���������裬�Է�����Ҳ���ż��衣��
	���ӹ����ϵ�����ȴ������ǡ���෴�������п��ٶ������ӱ����У���
	���Ʊ��޷����ܡ�
	���������ɡ�����Ҫ���������������������������������������Ϯ��
	�Է����γ�ǣ��,350��С�ɣ�450���ɡ�
	
	ָ�perform sword.wuxian

Ҫ��
	�����ڹ��ȼ� 350 ���ϣ�
	���������ȼ� 350 ���ϣ�
	�������ν�   350 ���ϣ�
	����������� 5000���ϣ�
	��ǰ�������� 2000����
	�����ض������ڹ�֧�֡�
	�������������װ��;

HELP
        );
        return 1;
}
