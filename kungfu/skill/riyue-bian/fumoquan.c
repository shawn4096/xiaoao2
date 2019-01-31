#include <ansi.h>

inherit F_SSERVER;
private int remove_effect(object me, int amount);
int perform(object me,object target)
{
        object weapon,wp2;
        int skill;
     	if( !target ) target = offensive_target(me);
        if(!me->is_fighting() )
                return notify_fail("����շ�ħȦ��ֻ����ս����ʹ�á�\n");

        if((int)me->query_skill("yijin-jing", 1) < 350 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á���շ�ħȦ����\n");
    
        if ((int)me->query_skill("riyue-bian", 1) < 350 )
                return notify_fail("������±޷�������죬�����������ӡ���շ�ħȦ����\n");
        weapon= me->query_temp("weapon");
		wp2=target->query_temp("weapon");  
		if (!me->query("quest/sl/ryb/fumoquan/pass"))
	            return notify_fail("����Ȼ��˵����ħȦ����������δ�������⣬�޷����ӡ���շ�ħȦ����\n");

        if (!weapon 
         || weapon->query("skill_type") != "whip"
         || me->query_skill_mapped("whip") != "riyue-bian")
                return notify_fail("�������޷�ʹ�á���շ�ħȦ������߷�������\n");
    
        if ((int)me->query("neili") < 1500 )
                return notify_fail("����������̫��������ʹ�á���շ�ħȦ����\n");

        if ((int)me->query("jingli") < 500 )
                return notify_fail("�����ھ���̫�٣�����ʹ�á���շ�ħȦ����\n");


        if( me->query_temp("jgq/fumo"))
                return notify_fail("������ʹ�ô���ȭ�����⹥������շ�ħ����\n");
		if ( me->query("class")!="bonze" ) 
                return notify_fail("���ɮ�ˣ���������̫�أ��޷���ʹ����շ�ħȦ����\n");
        if ( (int)me->query_temp("ryb/fumoquan") ) 
                return notify_fail("������ʹ�á���շ�ħȦ����\n");

  
        if (me->query_skill_mapped("force") != "yijin-jing")
                return notify_fail("����ڹ������޷�ʹ�á���շ�ħȦ����\n");
 
        message_vision(RED "$N���з�š�"HIY"�ҷ�ȱ�����"RED"���������Ѫ��ɮ�۶���������������"+weapon->name()+RED"����ת���������ն̣�\n"+
                           "�����൱���ܡ�"+weapon->name()+RED"����������������ƻã����۵�����ô�������������Ǳ����˳�ȥ��\n"NOR, me); 
 
       if (me->query_skill("riyue-bian",1)<450)
        {		
			me->start_busy(1);
			me->start_perform(1,"����շ�ħȦ��");

        }
        me->add("neili", -400);          
        me->add("jingli", -300);
		
        skill = me->query_skill("riyue-bian", 1);
		
		if (target->query("shen")<-10000
			||(target->query_skill_mapped("dagger")=="shenghuo-lingfa" && objectp(wp2)&&wp2->query("skill_type")=="dagger"))
		{
			skill=skill+me->query_temp("yijin-jing",1)/4;
			
			message_vision(YEL"$Nʩչ�������ڵķ��Ź���,���ÿ�����$n�Ĺ�����$n�پ�ѹ��������\n"NOR,me,target);
		}
        me->add_temp("apply/armor",  skill/4);
        me->add_temp("apply/parry",  skill/3);
        me->add_temp("apply/dodge",  skill/3);
		me->add_temp("apply/whip", skill/2);
        me->add_temp("apply/strength",  skill/8);
        me->set_temp("ryb/fumoquan", skill);
		call_out("check_fight",1,me,(int)skill/30);
        return 1; 
}

void check_fight(object me, int amount)
{  
        object wep;
		int skill;
        if (!me) return;
		skill=me->query_temp("ryb/fumoquan");
        wep = me->query_temp("weapon");  
        if(!me->is_fighting()
         || !wep
		 || amount<0
		 || wep->query("skill_type")!="whip" )
	{
			me->add_temp("apply/armor",  -skill/4);
			me->add_temp("apply/parry",  -skill/3);
			me->add_temp("apply/dodge",  -skill/3);
			me->add_temp("apply/whip", -skill/2);
			me->add_temp("apply/strength",  -skill/8);
			me->delete_temp("ryb/fumoquan");

			if(living(me) && !me->is_ghost())
				message_vision(RED"���ã�$N��ʹ��շ�ħȦ����������ƽϢ��һ���ָֻ���ԭ״��\n"NOR, me);
			return;
	}
       call_out("check_fight", 1, me, amount--);
}
//�Ƿ��Ƿ�ħȦ����������������Ч����
string perform_name(){ return HBYEL+HIR"��շ�ħȦ"NOR; }

int help(object me)
{
	write(HIC"\n���±ޡ���շ�ħȦ����"NOR"\n");
	write(@HELP
	���±���������������֮һ��������������������֮�����ɸջ�����书
	��ʱ�����ڹ��Դ��������տ�����������������¶��ǵľ��硣Խ��Խ����
	����Խ�̹���Խǿ�����������������շ����ġ����޼ɾ�лѷ�������գ�
	��һ�ֿ�������ɮ����һս��Ȼ�ɾ������޼ɵ���������ͬʱ���������ϵ�
	���±�Ҳ�������¡�
	��շ�ħȦ���Ը���ķ𷨣��Խ������֮�����뵽�޷�֮�У����������
	��ķ�����ͬʱ�������±޵Ĺ����������������������߻������似��һ��
	���ƹ�Ч��450��С�ɡ�
	
	ָ�perform whip.fumoquan

Ҫ��	
	��ǰ���� 1500 ���ϣ� 
	��ǰ���� 500 ���ϣ� 
	�׽�ȼ� 350 ���ϣ�
	���±޷��ȼ� 350 ���ϣ�
	�����ķ��ȼ� 200 ���ϣ�
	�����޷�Ϊ���±޷���
	�������±޷�Ϊ�мܣ�
	�����׽Ϊ�ڹ���
	װ�������������     
HELP
	);
	return 1;
}
