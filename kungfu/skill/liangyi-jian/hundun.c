//hundun.c 
//by sohu@xoojh 2016

#include <ansi.h>
inherit F_SSERVER;
void finish();
int perform(object me, object target)
{
        object weapon;
        int i=me->query_skill("liangyi-jian",1);

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ��"HIG"���罣��"NOR"��\n");
        weapon = me->query_temp("weapon");
        if( !me->query("quest/kl/lyj/hundun/pass"))
                return notify_fail("��ֻ�����������ž������޷�ʩչ��"HIG"���罣��"NOR"��\n");
		if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
			|| me->query_skill_mapped("parry") != "liangyi-jian"
            || me->query_skill_mapped("sword") != "liangyi-jian")
                return notify_fail("������û�н����޷�ʹ��"HIG"���罣��"NOR"��\n");
        if( (int)me->query_skill("liangyi-jian", 1) < 500 )
                return notify_fail("��������ǽ���������죬�޷�ʩչ��"HIG"���罣��"NOR"��\n");
        if( (int)me->query_skill("sword", 1) < 500 )
                return notify_fail("��Ļ�������������죬�޷�ʩչ��"HIG"���罣��"NOR"��\n");
        if( (int)me->query_skill("xuantian-wuji", 1) < 500 )
                return notify_fail("��������޼���������죬�޷�ʩչ��"HIG"���罣��"NOR"��\n");
		if( me->query_temp("lyj/hundun") )
                return notify_fail("�������ʹ��"HIG"���罣��"NOR"������\n");
		if( me->query_skill_mapped("force")!="xuantian-wuji")
                return notify_fail("�㼤�����ڹ��������޼������޷�ʩչ��"HIG"���罣��"NOR"��\n");
         
		if ( (int)me->query("max_neili") < 12500)
                return notify_fail("�����������������޷�ʩչ��"HIG"���罣��"NOR"��\n");
        if ( (int)me->query("neili") < 1000)
                return notify_fail("��������������޷�ʩչ��"HIG"���罣��"NOR"��\n");
        if ((int)me->query("jingli") < 1000)
                return notify_fail("��ľ����������޷�ʩչ��"HIG"���罣��"NOR"��\n");

        message_vision(HIB"\n$N"HIB"�����޼��������޼���������������ʽ���಻������$n��ȫ��û��һ�Ż��罣��֮�С�\n"NOR, me,target);
        me->set_temp("lianhuan", 1);
		
		me->set_temp("lyj/hundun",1);
        me->add("neili", -100-random(100));
        me->add("jingli", -100);
        
		message_vision(HBBLU+HIW"$N���е�"+weapon->query("name")+HBBLU+HIW"��������ˮһ�㣬��$n��ȥ,���Ʋ��أ�ȴҲ�̲�����ɱ����\n"NOR,me, target);
        message_vision(HBBLU+HIW"ȫ�������޼�������ת��"+weapon->query("name")+HBBLU+HIW"�����γ�һ���������ֵġ����罣��������\n"NOR,me, target);

		me->add_temp("apply/attack",i/4);
		me->add_temp("apply/damage",i/5);
		me->add_temp("apply/sword",i/5);
	/*	
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		*/
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		
	
		if (objectp(target)&&me->is_fighting())
				call_out("check_fight", 1, me, 1+i/30);
		else
			call_out("finish",1);
		return 1;
}
//��������

void remove_effect(object me)
{
         int i=me->query_skill("liangyi-jian",1);
         object target = offensive_target(me);
         if(!me) return;
		 
		 me->delete_temp("lianhuan");
         
		 if(!living(me)) return;
         
		 if (objectp(target)&&me->is_fighting()) 
		 {
             message_vision(HIB"\n\n$N"HIB"����������֯���������ķ�����ӿ�룬���ذ�$nǰ�����ҽ��С�\n"+
				 "$nֻ��������ѹ��������$N�ġ�"HIG"���罣��"HIB"���ѽ�$n����Χס��\n"NOR, me,target);
             me->set_temp("lianhuan", 5);
             me->set_temp("lianhuan2", 1);
			 target->add_busy(2);
			 target->set_temp("must_be_hit",1);
			 me->add_temp("apply/damage",i/5);
			 if(me->is_fighting(target) )
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			 if(me->is_fighting(target) )
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			 if(me->is_fighting(target) )
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			 target->delete_temp("must_be_hit");
			 me->add_temp("apply/damage",-i/5);
			 return;
		   }
   
}
void finish()
{
       int i;
	   object me = this_player();
	   if (!me) return;
       me->delete_temp("lianhuan"); 
       me->delete_temp("lianhuan2");

	   me->delete_temp("lyj/hundun");
	   i=me->query_skill("liangyi-jian",1);

	   me->add_temp("apply/attack",-i/4);
	   me->add_temp("apply/damage",-i/5);
	   me->add_temp("apply/sword",-i/5);
    
	   me->start_perform(5,"��"HIG"���罣��"NOR"��");
	   me->start_busy(1+random(2));

       message_vision(WHT"$N��������һ���������罣�������ˣ������ָ�����Ȼ��\n"NOR, me);
	   message_vision(HIB"\n$N"HIB"��"HIG"�����罣����"HIB"����ʹ�꣬$N����ƮƮ����ɷ��\n"NOR, me);

	   return;
}


void check_fight(object me, int i)
{
    object weapon, target;
    int jl;

    if (!me ) return;
    
    target = offensive_target(me);
     
    if( !living(me) 
        || !target 
        || !me->is_fighting(target) 
        || !living(target)
        || environment(target)!=environment(me)
        || !me->query_temp("lianhuan"))
              call_out("finish",1);

    else if(me->query_skill_mapped("sword") != "liangyi-jian"){
                tell_object(me, HIR"����ʱ�Ļ���������������ʹ�á�"HIG"���罣��"NOR"��������\n");
                call_out("finish",1);
				return;
                }
    else if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"){
                tell_object(me, HIR"����ʱ�Ļ���������������ʹ�á�"HIG"���罣��"NOR"��������\n");
                call_out("finish",1);
				return;
                }
    else if ((int)me->query("neili") < 200 ){
                tell_object(me, HIR"���������ã�ֻ�û����ջء�"HIG"���罣��"NOR"����\n");
                call_out("finish",1);
				return;
                }
    else if ((int)me->query("jingli") < 100 ){
                tell_object(me, HIR"��������֧��ֻ�û����ջء�"HIG"���罣��"NOR"����\n");
                call_out("finish",1);
				return;
                }
    //else if(me->is_busy()) 
              //  call_out("check_fight", 1, me, i);
    
    else{
           me->add("neili", -180);
		   jl=100;
           jl= me->query_skill("liangyi-jian",1)+me->query_skill("xuantian-wuji",1);
           me->add("jingli", -30);
           message_vision(HBBLU+HIW"\n$N�Ľ�����֯������������������������$n������ţ���ж��ٻ����ٲ����ѡ�\n"NOR, me,target);
           if (jl<0 ) jl=100;
		   
		   if (random(me->query_skill("force",1)) > target->query_skill("force",1) /2 
               || random(me->query_dex(1)) > target->query_dex(1) /2  )
		   { 
               message_vision(HIC"\n$nֻ�����Լ�����$N�������ƣ���������������ת���磡\n"NOR, me,target);
               target->apply_condition("no_exert", 1);
			   message_vision(HIB"\n$nֻ�����Լ��������·�һ˿˿�ĳ��˳����Ƶã�\n"NOR, me,target);
			   if (target->query("jingli")>1200)
				   target->add("jingli",-200-random(1000));
				else target->set("jingli",0);
		
				target->add_busy(1+random(2));
				target->receive_damage("jing", -(jl+random(200)),me);
				if (target->query("neili")>1500)
					target->add("neili", -(jl+random(200))); 
				else target->set("neili",0);
          } 
		   me->add_temp("lianhuan",-1);                       
           i--;
          //����ͷ�����������
		  if (me->query_temp("lianhuan")<=2 
			  && me->query_skill("liangyi-jian", 1) >500 
			  && !me->query_temp("lianhuan2")) 
			  remove_effect(me);  
		  //������ҪĿ���ǽ������⹥��
		  //else  
		  call_out("check_fight",2, me, i);
    }
}



string perform_name(){ return HBBLU+HIW"���罣��"NOR; }
int help(object me)
{
write(HIW"\n���ǽ���֮"HBBLU+HIW"�����罣������"NOR"\n\n");
write(@HELP
	���罣�������ǽ����о��У�������ڹ�ͨ�����⼤��
	���н�������֮�⣬Ҳ���ھ�����֮�Σ������γ�һ��
	���������Է�����Χ��һƬ����ĺ����С���������
	�侫���������ǳ���
	ע�⣺���Ź�����뼤�������޼�����һ��ʹ�ü�Ϊ��
	�����ݾ��棬��ȫ������ʽ��ĵ��ˣ��м��мǡ�
	
	ָ�perform sword.hundun

Ҫ��
	�������Ҫ�� 12500 �����ϣ�
	��ǰ����Ҫ�� 1000 �����ϣ�
	��ǰ����Ҫ�� 1000 �����ϣ�
	���ǽ����ȼ� 500 ���ϣ�
	�����޼��ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�
	��������Ϊ���ǽ�����
	�����ڹ�Ϊ�����޼�����
	���ý��������
HELP
);
return 1;
}

