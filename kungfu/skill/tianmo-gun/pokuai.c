// pokuai.c ������� ���Կ��ƿ�
// cre by sohu@xojh
// dueto ��һ��ʹ�����ε���ʽ���㼴���ף����ⲻ���������ӣ�������һɲ�Ǽ����������������ȡ�Է������崦��

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HIW"�Կ��ƿ�"NOR; }
int perform(object me,object target)
{
    object weapon;
    int i,j,lev,jiali;
    
    if( !target ) target = offensive_target(me);
     
    if( !userp(me) && userp(target) )
                return notify_fail("���Կ��ƿ졹ֻ�������ʹ�á�\n");
    if (me->query("quest/hmy/tmgf/jueji")!="pass")
	            return notify_fail("����δ�ڻ��ͨ������ʹ������ħ����֮���ƿ������\n");
    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("���Կ��ƿ졹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

     if (me->query_skill_mapped("force") != "tianmo-gong" && me->query_skill_mapped("force") != "xixing-dafa" )
             return notify_fail("����ʹ�õ������ڹ����ԡ�\n");  

     if(me->query_skill("xixing-dafa", 1)<450)
          if(me->query_skill("tianmo-gong", 1) < 450)
                return notify_fail("�������ڵ��ڹ���Ϊ��ʹ�������Կ��ƿ졹��\n");  

    if( (int)me->query_skill("tianmo-gun", 1) < 450 ) 
                return notify_fail("���������ħ����δ���ɣ��޷�ʹ�á��Կ��ƿ졹��\n");

    if((int)me->query_skill("club", 1) < 450 )
                return notify_fail("��Ļ�������������죬����ʹ�á��Կ��ƿ졹��\n");

    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "club"
        || me->query_skill_mapped("club") != "tianmo-gun")
                return notify_fail("�����ʹ�ù���������ʹ�����Կ��ƿ졹!\n");
                
   if((int)me->query_str() < 60)
           return notify_fail("�������������ǿ����ʹ�������Կ��ƿ졹������\n");

   if(me->query_skill_mapped("parry") != "tianmo-gun")
           return notify_fail("���Կ��ƿ졹��Ҫʹ����ħ���мܡ�\n"); 

   if((int)me->query("max_neili") < 10000 )
           return notify_fail("��������Ϊ��ǳ��ʹ�������Կ��ƿ졹��\n");  

   if( (int)me->query("neili") < 6000 )
           return notify_fail("����������̫����ʹ�������Կ��ƿ졹��\n");

    message_vision(HIW"\n$N������"+weapon->name()+HIW+"���ٻ��裬�γ�������Ӱ������������ֻ�$n���������ͬ��λ��\n"+
	   "$nֻ��"+weapon->name()+HIW+"��������������������������ħ���Կ��ƿ�ķ��š�\n"NOR, me, target);

    lev = (int)me->query_skill("tianmo-gun",1);
//ע������Ǵ����
    if( me->query_temp("xxdf/powerup") ) {           
           lev += (int)me->query_skill("xixing-dafa",1)/2;
    }     
   
        me->set_temp("tmgf/pokuai", 1);
        jiali = ((int)me->query("str",1)/2 + (int)me->query("con",1))/2 + (int)me->query("jiali")/20 ;
        
		me->add_temp("apply/damage",  lev/5);
        me->add_temp("apply/attack",  lev/3);
        me->add_temp("apply/strength", jiali);
       
		message_vision(HIC"$N������ר��$n�����̣����ǹ���$n���ؾȵķ�λ����$N�����������ס�����֮����������ȥ��$nԽ��Խ�ľ���\n"NOR,me,target);
		target->add_busy(1+random(2));
        
		for (i=0;i<6;i++){
          j = i;
          if (i<1) j = 1;
          if (i>1) j = 3;
		  if (!random(4)&&me->is_fighting(target)){
		       message_vision(HIY"$n���$N��籩���Ľ���������������̶��������԰�,�ؿ���ѹ��ʯ�����������ͻ���\n"NOR,me,target);
			   target->apply_condition("no_exert",1);
		  }
		  if (me->is_fighting(target))
		      COMBAT_D->do_attack(me, target, me->query_temp("weapon"),j);
          me->add("neili", -100);  
        }
   
        me->add("neili", -200);
        me->add_temp("apply/damage",  -lev/5);
        me->add_temp("apply/attack",  -lev/3);
        me->add_temp("apply/strength", -jiali);

        me->delete_temp("tmgf/pokuai");
		me->start_perform(4,"���Կ��ƿ졹");
        return 1;
}

int help(object me)
{
	write(HIW"\n��ħ����֮���Կ��ƿ졹��"NOR"\n");
	write(@HELP
	��ħ�������������ʮ����ħ֮����Գ��ħ���ų˷�͡��׺���ħ���ų���
	�ֵܶ����������������𽭺�������ʮ����Χ����ɽ�����䲻����ʹ��
	���ž����Ӵ�ʧ��������������˵�ڻ�ɽ��ɽʯ�����ֹ���ħ����ʽ��
	��������д�������Լ�̽����
	�����书��Ψ�첻�ƣ��Կ��ƿ�������ħ��������������Ĳ������š�
	��������Խ����ж���Ŀ��ƹ�Ч��
	
	ָ�perform club.pokuai

Ҫ��
	������� 10000 ���ϣ�
	��ǰ���� 6000 ���ϣ�
	������ħ���ȼ� 450 ���ϣ�
	��ħ�������Ǵ󷨵ȼ� 450 ���ϣ�
	��С������С��60��
	�����м�Ϊ������ħ����
HELP
	);
	return 1;
}
