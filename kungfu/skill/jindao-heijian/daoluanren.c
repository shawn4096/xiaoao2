//jindao-heijian ���������з�
//by fqyy 2003.5.9
/*
�󵶺���
�ҽ�б�̡����������Ը���Ϊ��������������Ϊ�ȣ�������е����ӽ�Ȼ�෴��һ��ͬʹ��
�������Ǿ�������֮�£����������˫�ֱ���ԽʹԽ��������������ȴ�ֵ��������������
��ã������ศ�������������к����ľ�����

�뵽�˴����͵ء����ҹ����ҽ������ʹ����ƽ����ѧ������
�����з��������ڽ��������ᣬ��ʱͻȻӲ��������������յĵ����������س���ľ��
��ȴ������ϴ��ȫ�ߵ���������·�ӣ����ɽ������䵶������������޷���
*/

//�޶�Ϊnizhuan 

#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;
void remove_effect(object me, object weapon,object weapon2, int count);
int perform(object me, object target)
{
	int i,skill;
	object *inv;
	object weapon2;
        object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("���������з�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
		if (!me->query_temp("jdhj/nizhuan"))
		{
			return notify_fail("�𵶺ڽ�ȫƾһ������������ת�𵶺ڽ�����ת����ʽ��\n");
		}

        if( me->query_dex() < 60 )
                return notify_fail("�������������������㣬����ʹ�����������з���\n");
        
        if( me->query_skill("dodge") < 450 )
                return notify_fail("���������з���Ҫ�������Ṧ��ϣ�������Чʩչ��\n");

        if( me->query_skill("sword") < 450 )
                return notify_fail("�㽣��δ��¯����֮����������ʹ�����������з���\n");
        if( me->query_skill("blade") < 450 )
                return notify_fail("�㵶��δ��¯����֮����������ʹ�����������з���\n");
        if( me->query_skill("jindao-heijian",1) < 450 )
                return notify_fail("��𵶺ڽ�δ��¯����֮����������ʹ�ý�Ȧ��նԷ���\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("�����������ʹ�����������з���\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ�������ʹ�����������з���\n");

        if (!weapon)
                return notify_fail("�������޽�����ʹ�����������з�����\n");
        if (me->query_temp("jdhj/luanren",1))
                return notify_fail("������ʹ�����������з��޷������������з���\n");
    //    if (me->query_temp("jindao-heijian/nizhuan",1)&&me->query_skill("jindao-heijian",1)<300)
                //return notify_fail("����㹦�����ʹ�����������з�����\n");
        if ( me->query_skill_mapped("sword") != "jindao-heijian"
          || me->query_skill_mapped("parry") != "jindao-heijian"
          || me->query_skill_mapped("blade") != "jindao-heijian"
          && userp(me))
             	return notify_fail("������Ƚ��ڽ����໥��ϡ�\n");
       inv = all_inventory(me);
       for(i=0; i<sizeof(inv); i++) 
	   {
            if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
			if (weapon->query("skill_type") == "blade")
			{
				   if( inv[i]->query("skill_type") == "sword" ) 
				   {
					   weapon2 = inv[i];
					   i = 3;
					   break;
					}
			}
			if (weapon->query("skill_type") == "sword") 
			{
				if( inv[i]->query("skill_type") == "blade" ) 
			    {
				   weapon2 = inv[i];
				   i = 2;
				   break;
			    }
		    }
       }
		if (!objectp(weapon2)) return notify_fail("��ֻ��һ�ֱ����������������з���\n");
	
		message_vision(YEL"\n$N�󵶺����ҽ�б�̡����������Ը���Ϊ��������������Ϊ�ȣ�������е����ӽ�Ȼ�෴��һ��ͬʹ��\n"+
					"�������Ǿ�������֮�£���$N˫�ֱ���ԽʹԽ��������������ȴ�ֵ����������������ã������ศ��\n"+
					"�����������к����ľ�����\n\n" NOR, me);
		
        skill = me->query_skill("jindao-heijian", 1)/4*i;
        //skill = me->query_skill("jindao-heijian", 1)/4*i;
   
		me->add_temp("apply/attack", skill/5 );
        me->add_temp("apply/damage", skill/5 );
        
        me->set_temp("jdhj/luanren",skill);
		if (wizardp(me))
		{
			write("skill="+skill);
		}
        //if( me->is_fighting() && userp(me))
        //	me->start_busy(1);
       // me->start_perform(1,"���������з�");
        me->add("neili", -800);
        me->add("jingli", -500);
		//call_out("remove_effect", 1, me, weapon,weapon2, skill/3);
		
		remove_effect(me,weapon,weapon2,skill/3);
		return 1;
}

void remove_effect(object me, object weapon,object weapon2, int count)
{
        int skill;
		if ( !me||!me->query_temp("jdhj/luanren") ) return;
        skill=me->query_temp("jdhj/luanren");
		
        if (count-- < 0
			||me->query_skill_mapped("sword")!="jindao-heijian"
			||me->query_skill_mapped("blade")!="jindao-heijian"
			||me->query_skill_mapped("parry")!="jindao-heijian"
			||!me->query_temp("weapon")
			||!objectp(weapon2)
			||weapon != me->query_temp("weapon")
			||!me->is_fighting())
		{
			me->add_temp("apply/attack", - skill/5);
          	me->add_temp("apply/damage", - skill/5);
          	me->delete_temp("jdhj/luanren");
			message_vision(YEL"\n$N������Щ���ǣ��������Լ�ˣ������ջ��˹��ơ�\n\n" NOR, me);
			return;
        }
            call_out("remove_effect", 1, me, weapon,weapon2, count);
}
string perform_name(){ return YEL"���������з�"NOR; }

int help(object me)
{
        write(HIC"\n�𵶺ڽ�"+YEL"�����������з���"NOR"\n");
        write(@HELP
	�𵶺ڽ������˹ȹ����ƵļҴ��书�����ֽ����ֺڽ�
	������������֮�������ڽ��˴�����֮Ч�������Ը�
	��Ϊ�����ڽ�������Ϊ����������Ϻ�����˷���ʤ����
	������������ǧ�߼޸������ƺ󣬶������书ȥ���澫��
	�����ơ����ﵽ¯����֮�����������似��ȱ��Ҳ����
	Ȼ��������ǧ�����ԡ��������ơ�����������ȱ�㡣
	���Ƶ��ӿ���ƾ����ݽ����ǧ�߲������ǧ�ߵ�ָ�㣬
	����Ź��򽫸��ϲ�¥��
	�ڽ��������ᣬ��ʱͻȻӲ��������������յĵ�����
	�����س���ľ�ݽ�ȴ������ϴ��ȫ�ߵ���������·��
	���ɽ������䵶������������޷���

	ע�⣺set �𵶺ڽ� ������ �л������Է�������
	
	ָ�perform sword(blade).nizhuan

Ҫ��
	��ǰ����Ҫ�� 1000 ���ϣ�
	��ǰ����Ҫ�� 1000 ���ϣ�
	�𵶺ڽ��ȼ� 450 ���ϣ�
	�����Ṧ�ȼ� 450 ���ϣ�
	���������ȼ� 450 ���ϣ�
	���������ȼ� 450 ���ϣ�	
	�������ȼ� 60 ���ϣ�	
	��������Ϊ�𵶺ڽ���
	��������Ϊ�𵶺ڽ���
	�����м�Ϊ�𵶺ڽ���
	�����ڹ����ޣ�
	�ֳֵ�(��)�����������ϴ���Ӧ����������

HELP
        );
        return 1;
}
