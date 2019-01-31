#include <ansi.h>
#include <combat.h>
//#include <combat_msg.h>

inherit F_SSERVER;
int calc_damage(int,int,object,object);

string perform_name() {return RED"��    ��"NOR;}
int perform(object me, object target)
{
	    object weapon;
        string msg,result;
        int i,total,skill,j; 
		if( !target ) target = offensive_target(me);
		skill=me->query_skill("tenglong-bifa",1);
        
		if( !objectp(target) 
			|| !target->is_character() 
			//|| !me->is_fighting(target) 
			|| !living(target))
                return notify_fail("�����̡�ֻ����ս��ʱʹ�ã�\n");
		
		if( objectp(weapon=me->query_temp("weapon")) 
			&&weapon->query("skill_type")!="dagger") 
		{                                
            return notify_fail("���������ذ�ײ����á����̡���\n");
        }
		if (me->query_skill_prepared("hand") != "chansi-shou"
            || me->query_skill_mapped("hand") != "chansi-shou" )
                return notify_fail("�������޷�ʹ�á����̡����й�����\n");  

        if( (int)me->query_skill("chansi-shou", 1) < 450 )
                return notify_fail("��Ĳ�˿�ֻ���������������ʹ�á����̡���\n");  

		
        if( (int)me->query_skill("tenglong-bifa", 1) < 450 )
                return notify_fail("��Ĳ��˹�������������������ʹ�á����̡���\n");
 		if( (int)me->query_skill("dulong-dafa", 1) < 450 )
                return notify_fail("��Ķ����󷨹������㣬�����á����̡���\n");

        if (me->query_skill_mapped("dagger") != "tenglong-bifa"
			||me->query_skill_mapped("parry") != "tenglong-bifa")
                return notify_fail("ֻ�м�������ذ��ʱ����ʹ�á����̡���\n");
        if (me->query_skill_mapped("dodge") != "youlong-shenfa")
                return notify_fail("ֻ��ʹ��������ʱ����ʹ�á����̡���\n");
        
        if((int)me->query_dex(1) < 70)
                return notify_fail("������������70������ʹ�á����̡���\n");       
        if(me->query("gender") !="Ů��")
                return notify_fail("����ֻ��Ů��ʹ�á����̡���\n");       

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("�����ھ������㣬����ʹ�á����̡���\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("�������������㣬����ʹ�á����̡���\n");  
		if (!me->query("quest/sld/tlbf/beici/pass"))
				return notify_fail("�����ڲ�����ⱳ�����ã�����ʹ�á����̡���\n");  
		if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("��������ʹ�õ��ڹ�ͬ��������ִ�������ʹ�á����̡���\n");
		//Ҫ�ж�״̬��
		if( me->query_temp("tlbf/bcbei"))
                return notify_fail("������Ǳ�������Է��У�\n");

		if( objectp(weapon=me->query_temp("weapon")))
		{
		weapon = me->query_temp("weapon");
		j=(int)skill/100;
		if (j>6) j=6;
		
		message_vision(BLU"$Nʩչ�������С��������С�������������Ϣ��Ǳ��$n�����ԣ��γ�����"+weapon->query("name")+"����׼����\n"NOR,me,target);
		call_out("beici_attack",7-j,me,target);
		me->set_temp("tlbf/bcbei",1);
		me->add("neili",-200);
		me->add("jingli",-300);
		}
	    return 1;
}

int beici_attack(object me,object target)
{
	string msg,result;
	object weapon;
	int i,total;

	if (!me||!me->query_temp("tlbf/bcbei")||!target) 
	{
		me->delete_temp("tlbf/bcbei");
		return 0;
	}
	weapon=me->query_temp("weapon");

	if (!weapon||weapon->query("skill_type")!="dagger") 
	{
		me->delete_temp("tlbf/bcbei");
		return 0;
	}
	if( !target ) target = offensive_target(me);
	//�����ַ���
	if (me->query_skill_mapped("hand")=="chansi-shou"
		||me->query_skill_prepared("hand")=="chansi-shou")
	{
	
		msg=HBMAG"$Nҧ����⣬�Ƴ�����ȫ��Ǳ�ܣ��ܲ�������Ȼ���ؼ���������$n��˫��ʩչ�����߲�˿����ʽ���㡢�����ơ�����\n"NOR;
		msg+=HIR"ͬʱ����$N��ת����"+weapon->name()+HIR"��ײ��$nС��["HIW"����Ѩ"HIR"]��\n"NOR;
		target->apply_condition("no_exert",1);
		target->set("jiali",0);
		if (random(me->query_skill("dulong-dafa",1))>target->query_skill("force",1)/2
			&&me->query("quest/sld/tlbf/beici/pass"))
		{
			msg+=HIM"$nС��["HIW"����Ѩ"HIR"]һʹ��������й����ʱ����������˲���޷����С�\n"NOR;
			if (target->query("neili")>6000)
			{
				target->receive_damage("neili",-6000);
			}
			else target->receive_damage("neili",0);
			target->apply_condition("no_perform",1);

		}	
		message_vision(msg,me,target);

	}
	
		msg=HBRED"$Nհ֮��ǰ��Ȼ�ں�ͻȻ������$n����"+weapon->name()+HBRED"�Ѿ�����$n���ģ�ֱ��ĩ����\n"NOR;

        i = calc_damage((int)me->query_skill("dodge",1),(int)me->query_skill("tenglong-bifa",1),me,target);
        total += i;
        if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
        target->receive_damage("qi", i, me );
        target->receive_wound("qi", i/2 , me);
        result = COMBAT_D->damage_msg(i,"����");
		result = replace_string( result, "$w", weapon->name() );
        result = replace_string( result, "$l", "����" );
        msg += result;
        message_vision(msg,me,target);
        COMBAT_D->report_status(target, 0);
        if(userp(me) && me->query("env/damage"))
		  tell_object(me,WHT"���"+ target->query("name") +"�����"RED+ i+ WHT"�㹥���˺���\n"NOR);    
        if(userp(target)&& target->query("env/damage"))
		  tell_object(target,WHT""+ me->query("name") +"�Ĺ������������"RED+ i+ WHT"���˺���\n"NOR); 
	    
		me->delete_temp("tlbf/bcbei");
	    me->start_perform(2,"����");
	    return 1;
		
}
int calc_damage(int skill,int skill2,object me,object target)
{
        int i;

        i = ( (skill+skill2)*2 - (int)target->query_skill("parry",1) )*10;
        if (i<0) i = -i;
        i += random(i*2/5);
        if( i < (skill2*5)) i = (int)target->query("qi",1)/3;   

        if(userp(target)) i = i* 2 / 5;
        
		return i; 
}

int help(object me)
{
   write(WHT"\n����ذ����"RED"����"WHT"����"NOR"\n");
   write(@HELP
	����ذ�����������������������Ĳ���֮��
	�仯��ˣ�����ʤ������ν��Ů�˵����Ʒ�
	�ӵ����쾡�¡�
	����������ذ���Ĺ�����ʽ�����ø�����
	�ƣ�����ȵ�����˽���֮�ʣ������Է�
	������еļ��ɡ��˼������շ��˵ľ���֮
	һ�����ڵ��͵ĵ���΢Ц������ͱ���ĵ䷶
	ע�⣬�����������ͱ��ò�˿������͵Ϯ��
	����ִ���Ч�����ȼ�Խ�ߣ�����Խ�졣��
	����Ҫ���ܷ���ϰ�á�
	 
	   
	perform dagger.beici

Ҫ��
	�������Ҫ�� 4000 ���ϣ�
	�����Ҫ�� 2500 ���ϣ�
	��ǰ����Ҫ�� 1500 ���ϣ�
	��ǰ����Ҫ�� 800 ���ϣ�
	����ذ���ȼ� 450 ���ϣ�
	��˿�ַ��ȼ� 450 ���ϣ�
	�����󷨵ȼ� 450 ���ϣ�
	������ 70 ���ϣ�
	�Ա�����Ů�ԡ�
HELP
   );
   return 1;
}
