// zongheng.c created by sohu@xojh
//���������˲��Ħ�Ǵ�ս����������
inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>
#include <combat.h>
string perform_name(){ return HIG"�����ݺ�"NOR; }
//int check_fight(object me);
//int hdy_ran(object me,object target);
int perform2(object me, object target);

int perform(object me, object target)
{
    int i,y,j,c,h,l;          
      
    if( objectp(me->query_temp("weapon")) )
		return notify_fail("�������ݺ᡹ֻ�ܿ���ʹ�á�\n");   
  	if( !target ) target = offensive_target(me);
    if( !objectp(target)
	     || !me->is_fighting(target) )
		return notify_fail("�������ݺ᡹ֻ����ս���жԶ���ʹ�á�\n");        
	if (!me->query("quest/dls/hyd/pass"))
		return notify_fail("����Ȼ��˵���������ݺ᡹����������δ����\n");
	if (me->query_temp("hyd/zongheng"))
		return notify_fail("������ʩչ�������ݺ᡹������\n");  
	if((int)me->query_skill("huoyan-dao",1) < 500)
		return notify_fail("��Ļ��浶��Ϊ������ Ŀǰ����ʹ�á������ݺ᡹! \n");
  
	if((int)me->query_skill("longxiang-boruo",1) < 500)
		return notify_fail("��������������Ϊ������ Ŀǰ����ʹ�á������ݺ᡹! \n");
		if((int)me->query_skill("force",1) < 500)
		return notify_fail("��������������Ϊ������ Ŀǰ����ʹ�á������ݺ᡹! \n");

	if( me->query_skill_mapped("strike") != "huoyan-dao"
		||me->query_skill_prepared("strike") != "huoyan-dao"
		||me->query_skill_mapped("parry") != "huoyan-dao")
		return notify_fail("�����ʹ�û��浶������ʹ�á������ݺ᡹�ľ�����\n");
	
	if( (int)me->query("max_neili") < 15000 )
		return notify_fail("������������Ϊ������\n");
	if((int)me->query("neili")<1500)
		return notify_fail("��ĵ�ǰ����������\n"); 
	if((int)me->query("jingli")<1000)
		return notify_fail("��ĵ�ǰ����������\n"); 
  
	message_vision(HIC "\n\nֻ��$N��ɫ��Ȼ������̴֧�����ڿ��У�����һ�ƻӳ�����������֮����Ѹ�����׵ع���$n��\n"
					+"$n�������ƣ������Ʒ������̴���ѱ����ţ�ȴ�����Ⱥ�֮�֣�ֻ���������ƣ��۶���ɢ��\n"
					+"$N��Ȼ$N��ָ΢�ţ���������һ��Ϊ��������������ɢȥ�����Ǵ����»��浶�����������ݺ᡹��\n\n"NOR,me, target);
    if (me->query("quest/dls/longxiang/pass")&&me->query_temp("xs/longxiang"))
    {
		i = (int)me->query_skill("huoyan-dao", 1)/3+(int)me->query_skill("longxiang-boruo", 1)/3;
    }else i = (int)me->query_skill("huoyan-dao", 1)/3+(int)me->query_skill("longxiang-boruo", 1)/6;
        
        //y = (int)target->query_skill("parry", 1)+(int)me->query_skill("force", 1)/3;
        me->add("neili", -400);
       
        me->set_temp("hyd/zh",i);
		// me->add_temp("apply/parry", i/5);
		me->add_temp("apply/attack", i/2);
        me->add_temp("apply/damage", i/5);
        me->set_temp("hyd/zongheng",6);
    if ( me->is_fighting(target))		
		COMBAT_D->do_attack(me, target, 0, 3);
	if ( me->is_fighting(target))		
		COMBAT_D->do_attack(me, target, 0, 3);
	if ( me->is_fighting(target))		
		COMBAT_D->do_attack(me, target, 0, 3);
	if ( me->is_fighting(target))		
		COMBAT_D->do_attack(me, target, 0, 3);
	if ( me->is_fighting(target))		
		COMBAT_D->do_attack(me, target, 0, 3);
    if ( me->is_fighting(target)){		
		COMBAT_D->do_attack(me, target, 0, 3);  
	}	
		
        me->add("jingli", -random(500));
        me->add("neili",  -random(800));
                
             
	if (objectp(target)
		&& me->is_fighting()
		&& me->query("quest/dls/longxiang/pass")
		&& me->query_temp("xs/longxiang"))
	{
		message_vision(CYN"\n$N�����������ת��Ϣ��ԽսԽ�£�������ʽ̤��������һ�С�ȼ�־������ֶ�����\n"+
					HBBLU+RED"$N�����浶������������⾳ʩչ���������ɾ������ű��̶�ȥ�����ƻ�������ȴѸ���ޱ�!\n"NOR,me, target);
		remove_call_out("perform2");
		call_out("perform2",1,me,target);
		
	}	   
      
          me->add_temp("apply/attack", -i/2);
          me->add_temp("apply/damage", -i/5);
		//  me->add_temp("apply/parry", -i/5);
		  me->delete_temp("hyd/zongheng");
		  me->delete_temp("hyd/zh");
		  me->start_perform(6,"�������ݺ᡹");
          return 1;
                 
}

int perform2(object me, object target)
{  

		int damage;
		string msg;
		
		if (!me->is_fighting()) return 0;
		if( !target ) target = offensive_target(me);
		
		if (random((int)me->query("neili"))>(int)target->query("neili")/2
			|| random(me->query_skill("strike",1))>target->query_skill("parry",1)/2)
        { 
           message_vision(RED "$N����һ�����ۼ���������ӿ�������������˵���������ɽ��������$n\n"+
           HIW "$n��ͣ��ʹ�������ţ�����$N�����ɵ�"HIY"���������"HIW"һ�����һ��һ����������Ϣ���ң�\n"NOR,me,target);
           damage =  8 * (int)me->query_skill("huoyan-dao", 1);
           damage = damage  + random(damage);
		   //if (damage>6000) damage=6000+(damage-6000)/10;
		   if(userp(me) && me->query("env/damage")) 
	             tell_object(me,WHT"���"+ target->query("name") +"�����"RED+damage+ WHT"�㹥���˺���\n"NOR);
           me->add("neili", -300);
           me->add("jingli",-100);
		    
           target->receive_damage("qi", damage,me);
           target->receive_wound("qi", damage/4,me);
		   target->apply_condition("no_exert",1);
		   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query_temp("xs/longxiang")?3:1);
           
        }
        else if(random(me->query_skill("force",1)) >  target->query_skill("force",1)/3){
                message_vision(RED "$nΪ$N����������ǿ���ڹ����ȣ��������У�ֻ����ȫ�����ȣ���Ϣ��ʱ�ҳ壡\n"NOR,me,target);
                target->receive_damge("qi",damage/4,me);
                target->add("neili", -random(2000));
				target->apply_condition("no_exert",1);
			    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query_temp("xs/longxiang")?3:1);
                target->start_busy(2);
                me->add("neili",-400);
        } 
        else {
                message_vision(HIY "$n�ڹ����Ǽ�Ϊ�˵ã�����ȫ������Ӳ�ǽ��˹���������������\n" NOR,me,target);
                message_vision(HIR "$Nֻ����ȫ�����ȣ���Ϣ�ҳ壡"NOR,me,target);
                me->receive_damage("qi", damage/4,target);
                me->add("neili",-random(1000));
				me->add_busy(2);
                target->add("neili",-500);
                
        }
		//message_vision(msg,me,target);
		return 1;

}
/*
int check_fight(object me)
{
      int j;
      if ( !me || !me->query_temp("honglian/lianxu")) return;
      if (me->query_temp("weapon")
       || me->query_temp("secondary_weapon")
       || me->query_skill_prepared("strike") !="huoyan-dao"
       &&me->query_temp("honglian/lianxu")){
        me->delete_temp("honglian/lianxu");
        tell_object(me, HIB"�����浶����ɢ������ĺ�����ʽ�޷������ˡ�\n"NOR);
        return;
      }
      if (!me->is_fighting()&&me->query_temp("honglian/lianxu")) {
        me->delete_temp("honglian/lianxu");
        tell_object(me, HIB"�����浶����ɢ������ĺ�����ʽ�޷������ˡ�\n"NOR);
        return;
      }
      else {

        call_out("check_fight", 1, me);
      }
}*/

int help(object me)
{
	write(HIR"\nѩɽ�ؼ��������ݺ᡹��"NOR"\n");
	write(@HELP
	���浶�����ݺ����,���Ǵ����²���֮�أ����������Ħ��
	�����Դ��似������������ս������ֶ����ܣ��ɼ����书��
	����Ī�⡣���ܺ󷽿�ʹ�ã��˴����¾����似��
Ҫ��
	������� 15000 ���ϣ�
	��ǰ���� 1500  ���ϣ�
	��ǰ���� 1000  ���ϣ�
	����������ȼ� 500 ���ϣ�
	��  ��  ���ȼ� 500 ���ϣ�
	�����ڹ��ȼ�   500 ���ϣ�    
HELP
	);
	return 1;
 }


