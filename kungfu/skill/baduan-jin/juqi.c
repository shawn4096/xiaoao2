// juqi.c ����  By sohu@xojh
// ����Ϊ�����Ӻ��������Ͷ�����  

#include <ansi.h>

inherit F_SSERVER;

string exert_name() {return HIW"����"NOR;}

int exert(object me)
{
        object weapon = me->query_temp("weapon");  
        int skill;
		skill=me->query_skill("baduan-jin",1)/10;
        if(!me->is_fighting() )
                return notify_fail("��������ֻ����ս����ʹ�á�\n");

        if((int)me->query_skill("baduan-jin", 1) < 100 )

			return notify_fail("��İ˶ν��ȼ�����������ʹ�á���������\n");
    
    
    
        if ((int)me->query("neili") < 500 )
                return notify_fail("����������̫��������ʹ�á���������\n");

        if ((int)me->query("jingli") < 500 )
                return notify_fail("�����ھ���̫�٣�����ʹ�á���������\n");

        if(me->query_temp("bdj/juqi"))
                return notify_fail("��������ʹ�ð˶ν�����������\n");


        if (me->query_skill_mapped("force") != "baduan-jin")
                return notify_fail("����ڹ������޷�ʹ�á���������\n");

        message_vision(HIW"$N����һ��������������ת���о���������˲���!\n"NOR, me);
        me->start_exert(3+random(2),"��������");
        me->add("neili", -200);          
        me->add("jingli", -100);
    if (me->query("quest/baduanjin/pass2"))
	{
		message_vision(HIW"$N����ð˶ν�֮���裬�����������ñ���һ���ĵá�!\n"NOR, me);
		skill=me->query_skill("baduan-jin",1)/5;		
	}	
	    me->add_temp("apply/parry",  skill);
		me->add_temp("apply/attack",  skill);
        me->set_temp("bdj/juqi", skill);

        call_out("check_fight", 0, me);
        return 1;
}

void check_fight(object me)
{  
        int i;

        if (!me) return;
        if( !me->is_fighting()
         || !living(me)
         || me->is_ghost()
         || me->query_skill_mapped("force") != "baduan-jin")
		{
			i = me->query_temp("bdj/juqi");
			me->add_temp("apply/parry", -i);
			me->add_temp("apply/attack", -i);
			me->delete_temp("bdj/juqi");
			if(living(me) && !me->is_ghost())
              message_vision(HIY"$N����������֧�������غ��˿����������ָֻ�����ǰģ����\n"NOR, me);
           return;
        } 
        call_out("check_fight", 1, me);
}

int help(object me)
{
    write(YEL"\n�˶ν���"HIW"����"YEL"����"NOR"\n");
   write(@HELP
	�˶ν����ǽ���������һ��Ѱ�������ڹ����䲻�����������ڹ���
	����������Ҳ����ͬС�ɣ��ˡ����������������ھ�����֫��
	һ���̶ȵ��������ʵս�мܺ�һ�������С�
	������һֱ�д��ԣ��˶ν���������һ�����������......
	   
	ָ�exert juqi

Ҫ��
	�˶ν� 100 ����
	��ǰ���� 500 ���ϣ�
	��ǰ���� 500 ���ϣ�
	
HELP
   );
   return 1;
}