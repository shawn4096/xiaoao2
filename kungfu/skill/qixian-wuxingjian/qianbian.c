// qianbian.c ������ǧ���� ֮��
// cre by sohu@xojh 6/6/2014

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int i, a,j,b,c;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("��ǧ���򻯡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( !me->query("quest/hmy/qxwxj/qianbian/pass") )
		return notify_fail("����Ȼ��˵��ǧ���򻯣���ȴ�޷�ʹ�á�ǧ���򻯡���\n");
 
        if( (int)me->query_skill("qixian-wuxingjian", 1) < 500 )
		   return notify_fail("����������ν��ȼ����㣬�޷�ʹ����ǧ���򻯡���\n");
 
        if( (int)me->query_skill("sword", 1) < 500 )
		   return notify_fail("��Ļ��������ȼ����㣬�޷�ʹ����ǧ���򻯡���\n");


        if( (int)me->query_skill("force", 1) < 500 )
		    return notify_fail("��Ļ����ڹ��ȼ����㣬�޷�ʹ����ǧ���򻯡���\n");

        if( (int)me->query("max_neili") < 15000 )
		   return notify_fail("���������Ϊ̫ǳ���޷�ʹ����ǧ���򻯡���\n");

	    if( (int)me->query("neili") < 2000 )
		   return notify_fail("����������㣬�޷�ʹ����ǧ���򻯡���\n");
		
		if( (int)me->query("jingli") < 1000 )
		   return notify_fail("��ľ������㣬�޷�ʹ����ǧ���򻯡���\n");

	  
     
	    if( !objectp(weapon = me->query_temp("weapon"))
	     || weapon->query("skill_type") != "sword"
	     || me->query_skill_mapped("sword") != "qixian-wuxingjian" )
	    	return notify_fail("��ʹ���ˡ�ǧ���򻯡�ô?\n");

        i = (int)me->query_skill("qixian-wuxingjian",1) +(int)me->query_skill("xixing-dafa",1) /2;
        
        me->add("neili",-800); 
        me->add("jingli",-300); 
		message_vision(HBYEL+RED"$N����"+weapon->query("name")+HBYEL+RED"��ת��ָ��$n���������д������������ص����š�$nһ�ݣ�ֻ�������о��ް��������\n"NOR,me,target);
        message_vision(HBYEL+RED"$n�ۼ�$N�����仯�����ޱȣ�˲������任�����ϳ˽������еĹ����������е��������࣬�е�С��Ѹ�ݣ��е����ͳ��ȡ�\n"NOR,me,target);

		j=6;
		b=1;
		
		if (me->query("quest/hmy/qxwxj/qianbian/pass"))
		{
			j=12;
			b=3;						
		}

		me->set_temp("qxwxj/qianbian",j);
        
		me->add_temp("apply/attack", i/2);                 
		me->add_temp("apply/sword", i/2);
        if (me->query("quest/hmy/qxwxj/qianbian/pass"))
			me->add_temp("apply/damage", i/2);
		for(a=0;a<j;a++)
        {     	   
		        if (me->is_fighting() && objectp(target))
		        {
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), b);
		        }
                else
				{
                  	
					break;								
				}
			            
        }
		if (me->query("quest/hmy/qxwxj/qianbian/pass"))
			 me->add_temp("apply/damage", -i/2);
        
		me->add_temp("apply/sword", -i/2);
        me->add_temp("apply/attack", -i/2);		
		me->delete_temp("qxwxj/qianbian");
		
		message_vision(HIG+"$N����һ�����ߣ����������滺�������漴�������С�\n"NOR,me,target);
		
        me->start_perform( 3 + random(2), "��ǧ���򻯡�");
        me->start_busy(2);
        return 1;
}

string perform_name(){ return HIY"ǧ����"NOR; }
int help(object me)
{
        write(HIB"\n�������ν�"+HIY"��ǧ���򻯡�"NOR"\n");
        write(@HELP
	���似Դ����������������÷ׯ���αȽ��Ƕ��������������ڳ�
	���������ٵĽ��к������򶷣������������任�����ϳ˽�����
	�еĹ����������е��������࣬�е�С��Ѹ�ݣ��е����ͳ��ȡ���
	ʽ���Ǻý��У�����������������¾Ž��������޷��������п�
	�ᣬ�ɼ����Ž���������֮����
Ҫ��
	�����ڹ��ȼ� 500 ���ϣ�
	���������ȼ� 500 ���ϣ�
	�������ν�   500 ���ϣ�
	�����ض������ڹ�֧��,
	���Ǵ��ж���ӳɡ�

HELP
        );
        return 1;
}

