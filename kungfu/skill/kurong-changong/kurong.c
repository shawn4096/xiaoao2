// By Spiderii �ϲ�ͬ���� kurong.c
// By Spiderii ���ڿ������ɣ���߷���
// by sohu�����ӿ�������ʵ��Ч������Ϊ7

#include <ansi.h>
void remove_effect(object me,int skill);


string exert_name() {return HIW"��"HIG"��"HIC"��"NOR;}

int exert(object me)
{      
   int skill;
       skill = me->query_skill("kurong-changong",1);
	   skill=skill+me->query_skill("yiyang-zhi",1)/3;
	   skill=skill/3;
	if ( !me->is_fighting())
		return notify_fail("��ֻ����ս����ʹ�á����١���\n");

	if( (int)me->query_skill("kurong-changong", 1) < 350 )
		return notify_fail("��Ŀ���������Ϊ�������޷�ʹ�á����١���\n");

	if (me->query_skill_mapped("force") != "kurong-changong")
		return notify_fail("�����ڹ��С����١���\n");

	if( (int)me->query("neili") < 15000 )
		return notify_fail("��Ŀǰ������̫���ˣ��޷�ʹ�á����١���\n");

	if( (int)me->query("max_neili") < 2000 )
		return notify_fail("���������Ϊ��ô�����ʹ�á����١���\n");

	if( me->query_temp("krcg_kurong"))
		return notify_fail("���������á����١���\n");

        // �������,���״��
    if ((int)me->query_skill("kurong-changong", 1) > 550 && me->query("quest/tls/kurong/pass"))
	{
			message_vision(HIY "$N" HIY "�������������ȫ��Ƥ�������һ����"
                                "��Ӥ������һ��ȴ�Ƹ������Ƥ�����ǿ���������"HIW"�����"HIG"���١�"HIY"���硣\n" NOR, me);
            me->add_temp("apply/damage", skill/5);
			me->add_temp("apply/finger", skill/2);
			me->add_temp("apply/strength", skill/20);
            me->add_temp("apply/attack", skill/2);
			me->add_temp("apply/armor", skill/2);
	   	    me->add_temp("apply/parry", skill/2);
			me->add_temp("apply/dodge", skill/2);

	 }
        // ȫ�٣���������
	else if ((int)me->query_skill("kurong-changong", 1) > 500 )
	{
	        message_vision(HIG "$N" HIG "���������������������ȫ��Ƥ����"
                                "�������Ӥ����⻬�������ǿ���������"HBGRN+HIW"��ȫ�پ��硹��\n" NOR, me);
		    me->add_temp("apply/attack", skill/2);
			me->add_temp("apply/armor", skill/2);
		    me->add_temp("apply/parry", skill/2);
			me->add_temp("apply/dodge", skill/2);

     }
		// ȫ�ݣ����ӷ���
    else if ((int)me->query_skill("kurong-changong", 1) > 450)
	{
	       message_vision(YEL "$N" HIW "���������������������ȫ��Ƥ����"
                                "���������Ƥ�������ϡ����ǿ�������֮"HIC"��ȫ�ݾ��硱��\n" NOR, me);
		   me->add_temp("apply/armor", skill/2);
		   me->add_temp("apply/parry", skill/2);
		   me->add_temp("apply/dodge", skill/2);
    }
		// ��ݰ��٣�����parry
    else if ((int)me->query_skill("kurong-changong", 1) > 350){
		   me->add_temp("apply/parry", skill/2);
		   me->add_temp("apply/dodge", skill/2);
	        message_vision(WHT "$N" WHT "���������������������������ʱ��"
                                "��ȫ�����ǿ�������֮"YEL"����ݰ��١����硣\n" NOR, me);
	}else {
		me->add_temp("apply/parry", skill/2);
		message_vision(WHT "$N" WHT "���������������������������ʱ�α�ȫ�����ǿ�������!\n" NOR, me);
	}
       if (me->query_skill("kurong-changong",1)<350)      
          me->start_busy(1); 
      
	   if (me->query_skill("kurong-changong",1)<450)
      	  me->start_exert(2, "�����١�");     
      
		me->add("neili", -400);
		me->set_temp("krcg_kurong",skill);
		call_out("remove_effect", 1, me, skill);
		return 1;
}

void remove_effect(object me, int skill)
{
	
	 if (!me) return;
	 skill=me->query_temp("krcg_kurong");
	 
	 if (objectp(me)) {
                if (me->is_fighting()) {
					   if (me->query("quest/tls/kurong/pass"))
					    {
							me->receive_curing("qi",random(1000));
							message_vision(HIC"$N���������Ѿ��Ƿ��켫��������ת֮�ʣ����κ�ȻΪ�ݣ���ȻΪ�٣��������Ƶõ������ת��\n"NOR,me);
					    }
                        call_out("remove_effect", 1, me, skill);
                        return;
      }

        me->delete_temp("krcg_kurong");
	    if ((int)me->query_skill("kurong-changong", 1) > 550 && me->query("quest/tls/kurong/pass"))
	    {
			me->add_temp("apply/damage", -skill/5);
			me->add_temp("apply/finger", -skill/2);
			me->add_temp("apply/strength",-skill/20);
			me->add_temp("apply/attack", -skill/2);
			me->add_temp("apply/armor", -skill/2);
			me->add_temp("apply/parry", -skill/2);
		    me->add_temp("apply/dodge", -skill/2);
	     }
        else if ((int)me->query_skill("kurong-changong", 1) > 500){
	       me->add_temp("apply/attack", -skill/2);
		   me->add_temp("apply/armor", -skill/2);
		   me->add_temp("apply/parry", -skill/2);
		   me->add_temp("apply/dodge", -skill/2);
        }
        else if ((int)me->query_skill("kurong-changong", 1) > 450){
		   me->add_temp("apply/armor", -skill/2);
		   me->add_temp("apply/parry", -skill/2);
		   me->add_temp("apply/dodge", -skill/2);
        }
		else if ((int)me->query_skill("kurong-changong", 1) > 350){
		   me->add_temp("apply/parry", -skill/2);
		   me->add_temp("apply/dodge", -skill/2);
        }
        else 
		   me->add_temp("apply/parry", -skill/2);
           message_vision(HIW"\n$N�Ŀ�������������ϣ��������ջص��\n"NOR, me);
		   
	    return;

	}
}


int help(object me)
{
        write(WHT"\n��������֮��"HIW"��"HIG"��"HIY"��"WHT"����"NOR"\n");
        write(@HELP
	�����������Ǵ����������Ժ--���������ֿ��ٳ��ϵ��ڹ��ķ�
	�ഫ�����������ڰ˿���֮�䡣��˿����ֶ����ϱ��������÷�
	�У����Ƿֱ���һ��һ�٣������ϱ��ֱ��ǣ������޳���������
	�֣��������ң������޾��� ���������޿����ٷ��Ǵ�ɡ�����
	�������������������һ����ֻ�εð�ݰ��١�
	�˿���һ����ʹ��Ҵ�����������ķ������мܣ�������һ��
	����ʹ�Է�������Ч��
	
	ָ�yun kurong

Ҫ��:
	�������� 200 �����ϣ�
	������� 2000 �㣻
	��ǰ���� 1500 �㣻
	�輤���ڹ�Ϊ����������
              
HELP
        );
        return 1;
}


