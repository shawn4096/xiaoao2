// kunlun-zhang.pfm ���߰���
// By jpei
//edit by sohu
#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HIW"���ص���"NOR; }


int perform(object me, object target)
{
        int i,damage;

        if( !target ) target = offensive_target(me);
        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("���ص��ƾ���ֻ����ս����ʹ�á�\n");       
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("�ȷ������е�������˵�ɣ�\n");
        if((int)me->query_skill("strike", 1) < 450 )
                return notify_fail("��Ļ����Ʒ�̫�ͣ��޷�ʹ�����ص���֮������\n");  
        if((int)me->query_skill("kunlun-zhang", 1) < 450 )
                return notify_fail("������ص��ƻ�������죬����ʹ�����ص���֮������\n");
        if (me->query_skill_prepared("strike") != "kunlun-zhang"
		   || me->query_skill_mapped("parry") != "kunlun-zhang"
           || me->query_skill_mapped("strike") != "kunlun-zhang")
                return notify_fail("�㲻ʹ�����ص��ƣ�������ʹ�����ص���֮��������\n");   
        
		if( (int)me->query("max_neili", 1) < 12000 )
                return notify_fail("��������Ϊ̫ǳ���޷��˾��˵У�\n");                
        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("�������������������ܷ������ص���֮������\n");
        if(!me->query("quest/kl/klz/diezhang/pass"))
                return notify_fail("��û��ѧ����У����ܷ������ص���֮������\n");

		if(userp(me) && (int)me->query_skill("xuantian-wuji", 1) < 450 )
                return notify_fail("��������ڹ��ȼ�����������Ӧ�����ص���֮������\n");
        if(userp(me) && me->query_skill_mapped("force") != "xuantian-wuji")
                return notify_fail("����ڹ��ķ����ԣ����Ӳ������ص��ƾ���֮����\n");                                                                                     
        if (userp(me) && me->query_skill_mapped("parry") != "kunlun-zhang")
                return notify_fail("��Ŀǰ�޷�ʹ�����ص���������\n");

        if( me->query_str(1) < 75 )
                return notify_fail("��ĺ����������75���޷�ʹ�����ص��ơ�\n");  

		
		if (me->query("gender")=="����")
		{
			i=me->query_skill("strike",1)/3  + me->query_skill("kunlun-zhang",1)/3 + me->query_skill("force",1)/3 ;
		}else
			i=me->query_skill("strike",1)/4  + me->query_skill("kunlun-zhang",1)/4 ;



		i = i /4;
		damage=me->query_str()*i;

		if(!userp(me))  i = i / 3;               //npc�ͷ���������Ϊ1/3^M
 
		
		me->add_temp("apply/strength", i /10);
        me->add_temp("apply/strike", i/2);
        me->add_temp("apply/damage", i/2);
        me->add_temp("apply/attack",i);


		message_vision(HIY"$N�������������ַ���һ�ƣ���Ӳ����Ӳ����ֻ���á��顱��һ����Ӳ��Ӳ�������������������ˣ��м�ʵ��˿��������أ�\n"NOR,me, target);
        me->add("neili", -300);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

        if ( me->is_fighting(target) ){
			message_vision(MAG"$N����˫����������������ƺ�$n������ӣ�������֮��ȴ�ֳ���һ��һ��֮����\n"NOR,me, target);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query("gender")=="����"?3:1);
       }

	
        if ( me->is_fighting(target)){
			message_vision(HIG"$nֻ������Է�С����һ������ڿմ�����$N���ŵ�һ��ȴ��������ͭǽ���ڡ�\n"NOR,me, target);
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"),me->query("gender")=="����"?3:1);
	    }
        if ( me->is_fighting(target)){
			message_vision(HIW"$Nʹ��һ��ǧ�Ҿ��㣬������������$n��ǰ�أ��Ʒ�����֮����\n"NOR,me, target);
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"),me->query("gender")=="����"?3:1);
	    }

       if ( me->is_fighting(target) && me->query_skill("kunlun-zhang", 1) > 220 )
       {
			message_vision(WHT"�͵���һ�ɾ���ײ����$n�Լ��ľ��������������ټ���$N��������ֱ�ȵ�$n������Ѫ\n"NOR,me, target);        
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query("gender")=="����"?3:1);
            if (me->query_temp("xtwj/riyue")&&me->query("jiali")>50 && me->query("quest/kl/klz/diezhang/pass"))
		   {
				
           		COMBAT_D->do_attack(target, target, me->query_temp("weapon"), me->query("gender")=="����"?3:1);
		   }
		   target->apply_condition("neishang",1);
            
			damage = i * 2 ;               
            damage = damage  + random(damage);
			if (damage > 5000 ) damage = 4500+random(1000);
			if( me->query("max_neili") /2 > target->query("neili")  )
            {          
              target->receive_damage("qi", damage,me);
              target->receive_wound("qi", damage/3,me);
            }
			if(userp(me) && me->query("env/damage")) 
				tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ damage+ WHT"�㹥���˺���\n"NOR); 
			if(userp(target)&& target->query("env/damage")) 
				tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ damage+ WHT"���˺���\n"NOR);

       }

		me->add_temp("apply/strength",- i /10);
		me->add_temp("apply/strike", -i/2);
		me->add_temp("apply/damage",- i/2);
		me->add_temp("apply/attack",-i);


        me->add("neili", -(200+random(100)));
        me->start_perform(4, "���ص���");
        return 1;
}



int help(object me)
{
	write(WHT"\n�����Ʒ�֮��"HIG"���ص���"WHT"����"NOR"\n");
	write(@HELP
	�������ս������ʱ����������Ӳ����ս������Ҳ��
	�����Ʒ��������Կ��������Ʒ�������ã������ޱ�
	��Ȼ��������ʮ���Ƹ��ͣ���Ҳ�������֮����
	����ʹ�����޼�������������50���ϣ������ʵ��ķ�
	��Ч������������������̡�
	������Ӳ��Ӳ������Ӳ�������������ơ�
	
	ָ�perform strike.diezhang

Ҫ��
	�����Ʒ��ȼ� 450 ���ϣ�
	�����޼��ȼ� 450 ����
	�����Ʒ��ȼ� 450 ����
	��ǰ����Ҫ�� 1000 ���ϣ�
	�������Ҫ�� 12000 ���ϡ�
	����������� 75 ���ϣ�
	�����Ʒ�Ϊ�����ƣ�
	�����м�Ϊ�����ƣ�
	�����ڹ�Ϊ�����޼�����
	�����ұ��Ʒ�Ϊ�����ƣ�
HELP
	);
	return 1;
}
