// guifei ��������
// ����д�˹���---by daidai
/*
     ���������΢����������Ť�����㷴�ߣ������С����ȥ������������ܣ�
�����˳�Ʒ�������������§ס������ͷ�������־�����ס��ذ�ף������׼��
�������ģ�Ц���������ǵ�һ�У����������������������ס�ˡ���

*/
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include <combat_msg.h>

string perform_name(){ return HIY"��������"NOR; }

int perform2(object me, object target);

int perform(object me, object target)
{
        object weapon;
        string msg,dodge_skill;
		int ap,dp,damage,effect;
 	 
        if(!target) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("������������ֻ����ս��ʱʹ�ã�\n");
/*
        if(userp(me) && me->query("family/master_id")!="su quan")
                return notify_fail("������������ֻ�а�������������ã�\n");
*/
        if(!objectp(weapon=me->query_temp("weapon"))
        || weapon->query("skill_type") != "dagger")
             return notify_fail("������û��ذ�ף����ʹ�á�������������\n");
	
        if((int)(me->query("dex")+me->query_skill("dodge",1)/10) < 60 )
                return notify_fail("����������ʹ�á����������������»��˵��Լ���\n");

        if((int)me->query_skill("tenglong-bifa", 1) < 350 )
                return notify_fail("�������ذ������������������ʹ�á�������������\n");
		if((int)me->query_skill("shenlong-tuifa",1) < 350)
				return notify_fail("��������ȷ���������������ʹ�á�������������\n");
	
        if(me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("ֻ��ʹ������ذ��ʱ����ʹ�á�������������\n");

		if(me->query_skill_mapped("leg") != "shenlong-tuifa"
		|| me->query_skill_prepared("leg") != "shenlong-tuifa")
				return notify_fail("������û������׼�����޷�ʹ�á�������������\n");
		
        if( (int)me->query_skill("dulong-dafa", 1) < 350 )
                return notify_fail("��Ķ����󷨹������㣬�����á�������������\n");

        if((int)me->query("jingli", 1) < 1000)
                return notify_fail("�����ھ������㣬����ʹ�á�������������\n");

        if((int)me->query("neili", 1) < 1000)
                return notify_fail("�������������㣬����ʹ�á�������������\n");

        if(me->query("gender") != "Ů��" )
                return notify_fail("����Ů����ô��ʹ�á������������أ�\n");

		if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("��������ʹ�õ��ڹ�ͬ�������໥�ִ�������ʹ�á�������������\n");

        
     message_vision( HIY"\n$N��$n��������֮����ƴ��ȫ��ʹ���շ��˲���֮����������������������"NOR,me,target);
	// if(me->query("gender") == "����" )
	//	message_vision(MAG"\n$N����΢����ˮͰ��Ĵ����͵�һŤ�����㷴�ߣ���$nС����ȥ��\n"NOR,me,target);
	//	else 
	message_vision( MAG"\n$N����΢��,�����ޱȣ�����ӯӯһЦ�䣬������Ťȹ�׷�����ޣ���Ȼ���㷴�ߣ���$nС����ȥ��\n"NOR,me,target);
  	me->receive_damage("neili",300);
  	me->receive_damage("jingli",150);
     //   message_vision(msg,me,target);
    ap = me->query_skill("tenglong-bifa",1)*me->query_dex(1);
	dp = target->query_skill("dodge",1)* target->query_dex(1);
	
	if( target->is_busy() ) dp= dp/2;
	if(random(ap)>dp/4)
 	{
 			effect = SKILL_D("dulong-dafa")->force_effect(target->query_skill_mapped("force"));
            //effect�Ƕ����󷨵Ŀ��Ƽ���
			damage = me->query_skill("force",1)+me->query("jiali")*5;
 			damage *= (5-effect);
 			if(damage>5000)
 				damage = 5000+(damage-5000)/100;
 			target->receive_damage("qi",damage,me);
 			target->receive_wound("qi",damage/3,me);
			msg = HIY"\n$n���ܲ�������$Nһ�����У���ɫ���̱�ĲҰף�\n"NOR;
			msg += damage_msg(damage, "����");
			msg = replace_string( msg, "$l", "����");
                //	msg = replace_string( msg, "$w", "ذ��");
			                	
 			message_vision(msg,me,target);
			COMBAT_D->report_status(target);
			if ( me->is_fighting(target))
			{
				message_vision( HIC"\n$N��˳�Ʒ���������������Ц��������������$n��ͷ�������ȥ��\n"NOR,me,target);
				perform2(me, target);
			}
	}else{
             dodge_skill = target->query_skill_mapped("dodge");
             if( !dodge_skill ) dodge_skill = "dodge";
             msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
 
			 if ( me->is_fighting(target))
			 {       
				msg += HIY"\n$n�����ܹ���$N˳�Ʒ���������������Ц��������������$n��ͷ�������ȥ��\n"NOR;	 	 
				message_vision(msg,me,target);
				perform2(me, target);
			}
	}
	 message_vision( MAG"\n$n��$N§סͷ����ֻ��������һ���������Ժ�֮��ȴû������$P���־�����ס��"+weapon->name()+MAG"��\n"NOR,me,target);
	 me->set_temp("sld/pfm/guifei",1);
	 COMBAT_D->do_attack(me,target,0,1);
     
     if ( me->is_fighting(target)) 
	 {
		weapon->unequip();
		COMBAT_D->do_attack(me,target,0,3);
		weapon->wield();
	 }    
	
	me->start_busy(1);
    me->delete_temp("sld/pfm/guifei");  
	if ( random(10)>5 
		&& me->is_fighting(target))
		COMBAT_D->do_attack(me,target,0,3);
     me->start_perform(4,"������������");
	return 1;/**/
}

//�ڶ���
int perform2(object me, object target)
{
	object weapon; 

	int ap,dp,lvl;  
    if(!target) target = offensive_target(me);

    if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return 0;
	if((int)me->query("jingli", 1) < 200)
                return 0;
	if((int)me->query("neili", 1) < 400)
                return 0;
	weapon=me->query_temp("weapon");
	lvl = me->query_skill("tenglong-bifa",1);
	ap = me->query_skill("tenglong-bifa",1)*me->query_dex();
 	dp = target->query_skill("dodge",1)* target->query_dex();
	if( target->is_busy() ) dp= dp/2;
	if(random(ap)>dp/2)
	{
		message_vision( MAG"$n��$N§סͷ����ֻ��������һ���������Ժ�֮��ȴû������$P���־�����ס��"+weapon->name()+MAG"��\n"NOR,me,target); 
        me->add_temp("apply/attack",lvl);
        me->add_temp("apply/damage",lvl/2);
		me->set_temp("sld/pfm/guifei",1); 
		COMBAT_D->do_attack(me,target,0,3);     
        me->add_temp("apply/damage",-lvl/2);

		if ( me->is_fighting(target) && me->query_skill("tenglong-bifa",1) > 300) 
		{
			weapon->unequip();
			COMBAT_D->do_attack(me,target,0,3);
			weapon->wield();
		}    
		me->delete_temp("sld/pfm/guifei"); 
        me->add_temp("apply/attack",-lvl);
		me->add("neili",-250);
  		me->add("jingli",-130);
 
	} else {  
			switch(random(2))
			{
				case 2: message_vision( HIC"$n��Ȼ��ͷ������Ǳ�֮��ʹ������ʽ�Լ���ɬ��\n"NOR,me,target); target->add_temp("lost_attack", 2+random(2));	break;
				case 1: message_vision( HIC"$n��Ȼ��ͷ�����ȴҲ���´�������֮����æ���ң������·���\n"NOR,me,target);  target->add_busy(random(2) + 1);break;
				default:  message_vision( HIC"$n��Ȼ��ͷ������Ǳ�֮��ʹ������ʽ�Լ���ɬ��\n"NOR,me,target); target->add_temp("lost_attack", 2+random(2)); break;
            } 
		me->add("neili",-150);
  		me->add("jingli",-50);
	}
}


int help(object me)
 {   write(WHT"\n����ذ����"HIY"��������"WHT"����"NOR"\n");
    write(@HELP
	����ذ�����������������������Ĳ���֮��
	�仯��ˣ�����ʤ������ν��Ů�˵����Ʒ�
	�ӵ����쾡�¡�
	����������ȡ�������һ��쳾����Ц�ĵ�
	�ʣ�ӯӯһЦ�䣬�������ţ��е��ڲ���֮
	�䡣�˵������ն��������к����йء�

	perform dagger.guifei
	
Ҫ��
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	����ذ���ȼ� 350 ���ϣ�
	�����󷨵ȼ� 350 ���ϣ�
	������Ҫ�� 60 ���ϡ�
	����ذ��Ϊ����ذ��
	�����ż�Ϊ����ذ��
	�����ұ��ȷ�Ϊ�����ȷ�
HELP
   );
   return 1;
}
