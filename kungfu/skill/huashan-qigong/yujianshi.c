// yujianshi.c Ԧ��ʽ  By lsxk@hsbbs 2007/7/24
// ����Ϊ����������  By lsxk@hsbbs

#include <ansi.h>

inherit F_SSERVER;

string exert_name() {return HIG"Ԧ��ʽ"NOR;}

int check_fight(object me);
int exert(object me)
{
        object weapon = me->query_temp("weapon");  
        int skill;
		skill=me->query_skill("huashan-jianfa",1);

        if(!me->is_fighting() )
                return notify_fail("��Ԧ��ʽ��ֻ����ս����ʹ�á�\n");

        if((int)me->query_skill("huashan-qigong", 1) < 350 )
                return notify_fail("��Ļ�ɽ�����ȼ�����������ʹ�á�Ԧ��ʽ����\n");
    
        if ((int)me->query_skill("huashan-jianfa", 1) < 350 )
                return notify_fail("��Ļ�ɽ����������죬�����������ӡ�Ԧ��ʽ����������\n");
    
        if((int)me->query_skill("force", 1) < 350 )
                return notify_fail("��Ļ����ڹ��ȼ�����������ʹ�á�Ԧ��ʽ����\n");

        if (!weapon 
         || weapon->query("skill_type") != "sword"
         ||( me->query_skill_mapped("parry") != "huashan-jianfa" &&  me->query_skill_mapped("parry") != "dugu-jiujian")
         ||( me->query_skill_mapped("sword") != "huashan-jianfa" &&  me->query_skill_mapped("sword") != "dugu-jiujian") )
                return notify_fail("�������޷�ʹ�á�Ԧ��ʽ����\n");
    
        if ((int)me->query("max_neili") < 3500 )
                return notify_fail("���������Ϊ̫�ͣ�����ʹ�á�Ԧ��ʽ����\n");

        if ((int)me->query("neili") < 1500 )
                return notify_fail("����������̫��������ʹ�á�Ԧ��ʽ����\n");

        if ((int)me->query("jingli") < 800 )
                return notify_fail("�����ھ���̫�٣�����ʹ�á�Ԧ��ʽ����\n");

        if(me->query_temp("hsqg/yjs"))
                return notify_fail("��������ʹ�á�Ԧ��ʽ����\n");

        if(me->query_temp("hsqg/juli"))
                return notify_fail("��������ʹ�á�������������\n");
        if (me->query_skill_mapped("force") != "huashan-qigong")
 
			return notify_fail("����ڹ������޷�ʹ�á�Ԧ��ʽ����\n");

        message_vision(HIM"$N�������У����±�ʹ����ɽ�ڹ���ѧ֮��"HIR"Ԧ��ʽ"HIM"����ֻ��$N����"+weapon->query("name")+HIM"�����趯�������ɳ��ʯһ�㣬���н�������!\n"NOR, me);
        if (me->query_skill("huashan-qigong",1)<450)
            me->start_exert(2+random(2),"��Ԧ��ʽ��");
		else me->start_exert(1+random(1),"��Ԧ��ʽ��");
        
		me->add("neili", -500);
        me->add("jingli", -300);
        if( me->query_skill("huashan-qigong",1)<=350)

			me->start_busy(1);

		

        if(me->query("quest/huashan")=="����")
		{
		    skill = me->query_skill("huashan-jianfa", 1)+me->query_skill("sword", 1)/5;
            message_vision(HIG"\n$N����ɽ���������ľ������õ��������У���ʱ������裡\n"NOR,me);
			//me->add_temp("apply/attack",skill/5);
			//me->add_temp("apply/sword",skill/6);
		
		CHAR_D->addfightbuff(me,"attack|damage",skill/6,skill/6,"huashan-qigong|force","hsqg/yjs1",0);
		}
        else 
	    {
			skill = me->query_skill("huashan-jianfa", 1)+me->query_skill("huashan-qigong", 1)/10;
			//me->set_temp("hsqg/yjs",skill);
            message_vision(HIC"\n$N���������������ľ������õ��������У���ʱ�����ݺᣡ\n"NOR,me);
			//me->add_temp("apply/damage",skill/10);			
			CHAR_D->addfightbuff(me,"attack",skill/10,skill/10,"huashan-qigong|force","hsqg/yjs2",0);		
		}
      	
		//me->add_temp("apply/attack",  skill/6);
		//me->add_temp("apply/damage",skill/10);     
	
 CHAR_D->addfightbuff(me,"damage|attack",skill/7,skill/7,"huashan-qigong|force","hsqg/yjs",HIM"$N����һ�󲻼ã���Ԧ��ʽ���޷������ˡ�");
       
        //me->set_temp("hsqg/yjs", skill);

        //call_out("check_fight", 1, me);
        return 1;
}

void check_fight(object me)
{  
        object wep;
        int i;

        if (!me) return;
		i = me->query_temp("hsqg/yjs");
        wep = me->query_temp("weapon"); 
		
        if( !me->is_fighting()
         || me->query_skill_mapped("force") != "huashan-qigong"
         || !wep
		 || wep->query("skill_type")!="sword")
		{

          me->add_temp("apply/attack", -i/6);
           me->add_temp("apply/damage", -i/10);
		   
		   if(me->query("quest/huashan")=="����")
               me->add_temp("apply/damage",-i/10);
		   if(me->query("quest/huashan")=="����")
		   {
               me->add_temp("apply/attack",-i/5);
			   me->add_temp("apply/sword",-i/6);
		   }
		   me->delete_temp("double_attack");
           me->delete_temp("hsqg/yjs");
           if(living(me) && !me->is_ghost())
              message_vision(HIG"$Nһ�ס�Ԧ��ʽ��ʹ�꣬΢΢һЦ������������\n"NOR, me);
           return;
        }
        call_out("check_fight", 1, me);

}
int help(object me)
{
   write(HIG"\n��ɽ������"HIG"Ԧ��ʽ"HIG"����"NOR"\n");
   write(@HELP
   ��ɽ�����˻�ɽһ�ɻ����ڹ����䲻��������ϼ�񹦾����������
   ���Ҳ����ͬС�ɣ��ˡ�Ԧ��ʽ���������ǽ��ڲ�����ѧ���ٵж�
   ��ʱ�����������Լ������С���ɽ���ڵ���Խ���������Խ����
   ��Ӧ�֣�����֮���˹������������ࡣ�����������ڵ��ӻ�����������
   �����ʵ��˺������ڵ����Խ��������������С���Ч���Բ�ͬ��
   
   ָ�exert yujianshi

Ҫ��
	��ɽ���� 350 ����
	��ɽ���� 350 ����
	�����ڹ� 350 ����
	������� 3500 ���ϣ�
	��ǰ���� 1500 ���ϣ�
	��ǰ���� 800 ���ϣ�
	������ɽ����Ϊ�м�,350С�ɣ�450��ɡ�
HELP
   );
   return 1;
}
