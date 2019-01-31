// sanyin.c ��������
// sohu@xojh


#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int myexp, targexp, damage, skill;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

		if( me->query_temp("sys/sanyin") )
               return notify_fail("������ʩչ������������\n");
        if( objectp(weapon=me->query_temp("weapon"))&&weapon->query("skill_type")!="throwing" )
               return notify_fail("�ǰ����಻��ʩչ����������\n");

        if( me->query_skill_mapped("hand") != "sanyin-shou" )
                return notify_fail("�����õĲ��������֣�����ʩչ����������\n");

        if( me->query_skill_prepared("hand") != "sanyin-shou" )
                return notify_fail("�������Ĳ��������֣�����ʩչ����������\n");


        if( (int)me->query_skill("force",1) < 220 )
                return notify_fail("������ڹ���Ϊ̫�������������������\n");
        if( me->query_skill("hand",1) < 220 )
                return notify_fail("��Ļ����ַ���Ϊ̫�������������������\n");
        if( me->query_skill("sanyin-shou",1) < 220 )
                return notify_fail("����������Ϊ̫�������������������\n");

        if( me->query("neili") <= 800 )
                return notify_fail("�����������ʹ������������\n");
        if( me->query("jingli") <= 500 )
                return notify_fail("��ľ�������ʹ������������\n");     

        message_vision(HIB"$N������ת���˾���˫�֣�˫���ֺ��ף��ɰױ�죬�������Σ��𽥻ָ���ƽ����\n\n"NOR, me,target);
        message_vision(HIB"�漴$N��Цһ�������ֹ���$n,����侢����ӿ��\n\n"NOR, me,target);

        myexp = me->query("combat_exp")/10000;
        targexp = target->query("combat_exp")/10000;
        skill = me->query_skill("sanyin-shou",1);
        if (me->query("gender")!="Ů��")
		{
			message_vision(YEL"$Nǿ����ʹ�����֣������������׳��ʩչ���������ֵ���������!\n"NOR,me);
			skill=skill/2;
		}
		me->add_temp("apply/damage", skill/5);
        
		me->add_temp("apply/hand", skill/5);
		me->add_temp("apply/attack", skill/3);
        
		me->set_temp("sys/sanyin", skill);
    //�����Լ�����            
		call_out("remove_me",1,me);
		//����⿪���в��ԣ�����й������˵���ʽ
        if(random(myexp)>targexp/2
			||me->query("quest/kl/sys/sanyin/pass")
			||random(me->query_skill("sanyin-shou",1))>target->query_skill("parry",1)/2) 
		{

                message_vision(HIW"$n�ۼ�$n˫�������������ܣ�ֻ��ͦ������֣���ͼ�������й��ơ�\n"NOR,me,target);
				message_vision(HIW"$n�����Լ����󡰴��Ѩ��һʹ�������ɰ���ӿ�룬�ʲ���ʽ״̬����Լ�������\n"NOR,me,target);

           
				if (!target->query_temp("sys/sanyin"))
				{
					if(target->query("neili")<skill*3) 
					{
							target->set("neili", 0);
					}else target->add("neili",-skill*3);
					target->add_temp("apply/armor", -skill/5);
					target->add_temp("apply/dodge", -skill/5);
					target->add_temp("apply/parry", -skill/3);
					target->set_temp("sys/sanyin",skill);
					target->apply_condition("sys_anjin",4);
					target->add_busy(3);                
					call_out("remove_target",1,target);
				}

        }                      
        else 
        {       
                me->add_busy(1);    
                message_vision(HIY "$p�Ͻ�����Ծ�����ɣ��㿪$P�Ĺ�����\n" NOR, me, target);
                me->add("neili",-250);
                return 1;
        }
		return 1;
}

//���һָ�
int remove_me(object me)
{
	int skill;
	skill=me->query_temp("sys/sanyin");
	if ( !objectp(me) ) return 1;
        
	me->delete_temp("sys/sanyin");
	me->add_temp("apply/damage", -skill/5);
    me->add_temp("apply/hand", -skill/5);
	me->add_temp("apply/attack", -skill/3);
	message_vision(HIG"�����ģ�$N������ɢ��������һ˿˿�ؾۻص��\n\n"NOR,me);
    return 1;
}
//����ָ�
int remove_target(object target)
{
	int skill;
	if (!target) return 0;

	skill=target->query_temp("sys/sanyin");
	
        
	target->add_temp("apply/armor", skill/5);
	target->add_temp("apply/dodge", skill/5);
	target->add_temp("apply/parry", skill/3);
	
	target->delete_temp("sys/sanyin");

	message_vision(HIG"�����ģ�$N���ñ������ְ�����ɵİ��˽����ָ���\n\n"NOR,target);
    return 1;
}

string perform_name() {return HIB"��������"NOR;}

int help(object me)
{
   write(WHT"\n������֮��"HIY"��������"WHT"����"NOR"\n\n");
   write(@HELP
	���������������������ʿ�ĳ�����������������
	����Ϊ�����ʿȥ�ߴ澫���������Ů�������ɵ�
	�ص�������Ṧ�����ƣ������Ź��������ʺ�Ů
	�Ե������õļ��������ַ�������һ������ɾ���
	
	��������������ʤ�������Ĺ�������˫���Ӵ���
	˲���ڶԷ����Ѩ��ע�������������Դ��˵С���
	�ܺ������˵�Ч����Ů�Ե��������ơ�������Ҫ
	��������̺�����ȫ����

	perform hand.sanyin
		
Ҫ��: 
	��ǰ���� 500 ���ϣ�
	��ǰ���� 800 ���ϣ�
	�����ַ� 220  ���ϣ�
	�����ڹ� 220  ���ϣ�
	�����ַ� 220  ���ϣ�
	�����ַ�Ϊ�����֣�
	�ڹ����ޣ�
	����״̬��

          
HELP
   );
   return 1;
}
