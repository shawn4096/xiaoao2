// ruozhuo.c ��׾ʵ��
// Cre by sohu@xojh 2014/6

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>


int perform(object me,object target)
{     
      	
		if( (int)me->query_skill("tianmo-zhang",1) < 350 )
           	return notify_fail("�����ħ�Ʋ�����죬����ʹ�á���׾ʵ�ɡ�������\n");
      
      	if( (int)me->query_skill("strike",1) < 350 )
           	return notify_fail("��Ļ����Ʒ��ȼ�����������ʹ�á���׾ʵ�ɡ���\n");  
      
      	if( (int)me->query_skill("tianmo-gong", 1) < 350 )
           	return notify_fail("�����ħ�����ȼ�����������ʹ�á���׾ʵ�ɡ���\n");
        if ( !me->query("quest/hmy/tmzf/ruozhuo/pass"))
            return notify_fail("����δ�����ħ�ƾ��ϣ�����ʹ�á���׾ʵ�ɡ���\n");
      	if (me->query_skill_mapped("force") != "tianmo-gong")
			if (me->query_skill_mapped("force") != "xixing-dafa")
           	return notify_fail("����ʹ�õ��ڹ����������ɹ�����\n");
        if( objectp(me->query_temp("weapon")) )
            return notify_fail("�������ֲ���ʹ�á���׾ʵ�ɡ���\n");
      	if( (int)me->query("max_neili") < 3500 )
           	return notify_fail("�������̫��������ʹ�á���׾ʵ�ɡ���\n");
       	if( (int)me->query_temp("tmzf/ruozhuo"))
           	return notify_fail("������ʹ�á���׾ʵ�ɡ���\n"); 
      	if( (int)me->query("neili") < 2000 )
           	return notify_fail("�������̫���ˣ��޷�ʹ�ó�����׾ʵ�ɡ���\n"); 
        
        return (int)call_other( this_object(), "main", me,target);
}

int main(object me,object target)
{
	    object tweapon;
	    int skill;
  	    int i;
        tweapon=target->query_temp("weapon");
      	if( me->query("neili") < 800 || me->query("jingli") < 100  )
                return notify_fail("��Ŀǰ�޷�ʹ�á���׾ʵ�ɡ���\n");   
        i=me->query_skill("tianmo-zhang", 1);       	
	    if (me->query_skill_mapped("force")=="tianmo-gong") 
			i = me->query_skill("tianmo-zhang", 1) + me->query_skill("tianmo-gong", 1)/4;
        if (me->query_skill_mapped("force")=="xixing-dafa")
			i = me->query_skill("tianmo-zhang", 1) + me->query_skill("xixing-dafa", 1)/2;
	        		
       	i = i + random(i);
       	i /= 2;

	    me->add("neili", -i);
        me->add("jingli", -50);
        message_vision(YEL"\n$N�����������ʽ����򵥣���ȴ��¶��ʵ�޻�֮�⣬���Ʊ�׾ʵ���мܣ�������ħ�Ʒ�������������׾ʵ�ɡ���\n" NOR,me);
       
        me->set_temp("tmzf/ruozhuo", i);
    
       if (me->query("env/��ħ��")=="��׾"&&objectp(target)&&me->is_fighting(target))
        {
			message_vision(HIC"$N��ħ��Խ��Խ������������ȴ���������ʹ$n���ڽ�����\n"NOR,me,target);
			if (random(me->query_skill("strike",1))>target->query_skill("parry",1)/3)
			{
				message_vision(HIY"$N�Ʒ�������$nһ��С��Ϊ�Ʒ������������ζ�ʱ�ͻ���\n"NOR,me,target);
				target->add_busy(2+random(2));
			}else 
				message_vision(YEL"$n����ǳ��ḻ�����ָ񵲺��漴�󳷣��㿪��$N�Ĺ�����\n"NOR,me,target);
            //����ǧҶ
			if (target->query_skill_prepared("hand")=="qianye-shou"&& random(me->query_skill("tianmo-zhang",1))>target->query_skill("qianye-shou",1)/2)
            {
				message_vision(HIY"$N��$n��ʽԽ��Խ�죬�������־���ǧҶ�֣����ҵ���������ʽʹ��Խ��Խ������Ӧ����׾ʵ�ɵ�Ҫ�塣\n"NOR,me,target);
				tell_object(target,HIC"����öԷ����������ÿ����Լ�����ʽ�����ɵ�һ�š�\n"NOR);
				target->apply_condition("no_perform",2);
				target->add_busy(2+random(3));

            }
			if (!tweapon)
			{
				//message_vision(HIG"$N��$n��ʽԽ��Խ�죬���м�Ϊ����������ħ�Ƶ���׾ʵ�ɵ�Ҫ�Է��ӵ����쾫�¡�\n"NOR,me,target);
				target->add_temp("apply/attack",-i);
				target->add_temp("apply/damage",-i/4);
				target->add_temp("apply/dodge",-i/4);
				message_vision(HIC"$n��Ȼ�о��Է��⼫������ʽ�ƺ�һ��ǽһ�����Լ�ѹ�˹����������ͻ���\n"NOR,me,target);
				target->set_temp("tmzf/ruozhuo",i);
				
				call_out("tmzf_effect",(int)i/20,target);
			}

        }      

		me->add_temp("apply/attack", i);
        me->add_temp("apply/strike", i);
        me->add_temp("apply/damage", i/6);
		//message_vision("i=="+i,me,target);
		//if (objectp(target)&&me->is_fighting())
			call_out("check_fight", 2 , me,i/4);
        
		if(me->query_skill("tianmo-zhang",1)<350) me->start_busy(1);

        return 1;
}

void check_fight(object me,int i)
{       
        int j;
		object weapon;
        if( !me ) return; 
        if( !intp(j = me->query_temp("tmzf/ruozhuo")) ) return;

        weapon=me->query_temp("weapon");

        if( !me->is_fighting() 
	    ||  i < 1
        ||  weapon
        ||  me->query_skill_mapped("strike") != "tianmo-zhang"
        ||  me->query_skill_prepared("strike") != "tianmo-zhang")
		{
        	
			me->add_temp("apply/attack", -j);
        	me->add_temp("apply/strike", -j);
        	me->add_temp("apply/damage", -j/6);
        	me->delete_temp("tmzf/ruozhuo");
        	me->add("neili", -j );
        	me->start_perform(3, "��׾ʵ��");
			//��������׾�������
		
        	//if( living(me))
			   message_vision(YEL "\n$N�������һ�����������񻺻��ɳ���������\n" NOR, me);   
        	return;
        }
	    if (me->query_skill("tianmo-zhang",1)<450)
	       me->start_perform(2, "��׾ʵ��");
        call_out("check_fight", 1, me,i--);
}
int tmzf_effect(object target)
{
	int i;
	if (!target) return 0;
	i=target->query_temp("tmzf/ruozhuo");
	
	target->add_temp("apply/attack",i);
	target->add_temp("apply/damage",i/4);
	target->add_temp("apply/dodge",i/4);
	target->delete_temp("tmzf/ruozhuo");

	message_vision(HIC"$N����һ������������ħ������ɵ�ѹ�������ͷš�\n"NOR,target);
	return 1;
}

string perform_name(){ return HIC"��׾ʵ��"NOR; }
int help(object me)
{
	write(HIG"\n��ħ�ơ���׾ʵ�ɡ���\n"NOR);
	write(@HELP
	��ħ���������������������ǧ�������Ŀ����似���������µ���
	ϰ������Ҫ�����似�������������������뷽֤��ʦһս����ħ��
	�İ��Ϊ����֪��������׾ʵ�ɾ������������ڵľ�ѧ�����Ƴ�
	�л�������ʵ������󡣶�����ǧҶ����һ���Ŀ���Ч�����Կ���
	�����似��һ��Լ��Ч����������������̷���ϰ�á�
	ע�⣺���Ǵ�������Ч�������似350��С�ɣ�450�����ɡ�
	
	ע�⣺set ��ħ�� ��׾

	ָ�perform strike.ruozhuo

Ҫ��	
	��ħ�Ʒ��ȼ� 350 ���ϣ�
	�����Ʒ��ȼ� 350 ���ϣ�
	��ħ�����ȼ� 350 ���ϣ������Ǵ󷨣���
	����������� 3500 ���ϣ� 
	��ǰ�������� 2000 ���ϡ�
HELP
	);
	return 1;
}

