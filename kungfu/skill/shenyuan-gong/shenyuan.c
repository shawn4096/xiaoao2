// shenyuan.c yun shenyuan ������ս���������൱�ķ���

#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int skill);

string exert_name(){ return HIB"��Ԫ��"NOR; }

int exert(object me, object target)
{
	int skill;

	
	if (!me->is_fighting())
	    if (!me->query("quest/mr/dzxy/pass"))
		  return notify_fail("��ֻ����ս����ʹ����Ԫ����\n");

	skill = me->query_skill("shenyuan-gong",1);
	
	if( (int)me->query_skill("shenyuan-gong",1) < 100 )
		return notify_fail("��Ŀǰ�ȼ��������в���ʹ����Ԫ����\n");

	if( (int)me->query("neili") < skill  )
		return notify_fail("�������������\n");
 
	if( (int)me->query_temp("shenyuan") ) 
		return notify_fail("���Ѿ���������Ԫ���ˡ�\n");

	me->add("neili", -300);
	me->set_temp("shenyuan", skill);
	me->set_temp("sy/shenyuan",skill);

	message_vision(HIY "$N����Ľ�ݾ�ѧ��Ԫ�����ƺ���֪�书·�������������ɶ��ˡ�\n" NOR, me);
	if (me->query("quest/mr/dzxy/pass"))
	{
		message_vision(HBGRN+HIW "$N������Ķ�ת�����ķ��ںϵ���Ԫ��֮�У������ڻ��ͨ����ת�������������˷��ԡ�\n" NOR, me);
		me->add_temp("apply/parry", skill/2);	
   	    me->add_temp("apply/dexerity", skill/15);
	    me->add_temp("apply/strength",skill/15);
	    me->add_temp("apply/attack", skill/4);
		me->set_temp("syg/sypowerup",1);
	}
	else {

	    me->add_temp("apply/parry", skill/10);	
	    me->add_temp("apply/strength",skill/30);
	    me->add_temp("apply/attack", skill/5);
    }
    if (me->query_skill("shenyuan-gong",1)<450)
    {
		me->start_busy(1);
		me->start_exert(1, "��Ԫ��");
    }
	
	call_out("remove_effect", 1, me, skill);
	
	
	//me->start_busy(1);

	return 1;
}

void remove_effect(object me, int skill)
{
	int skill1;
	if (!me) return;
	skill1=me->query_temp("sy/shenyuan");

	if ( !me->is_fighting() || skill<0)
	{

		if (me->query("quest/mr/dzxy/pass"))
		{
		    message_vision(HBGRN+HIW"$N��Ԫ��һ�ͣ�����һ�����������չ����ָֻ�������״̬��\n"NOR,me);

			me->delete_temp("shenyuan");
			me->add_temp("apply/parry", -skill1/2);	
   			me->add_temp("apply/dexerity", -skill1/15);
			me->add_temp("apply/strength",-skill1/15);
			me->add_temp("apply/attack", -skill1/4);


		}else {
			message_vision(HIB"$N�����չ����ָֻ�������״̬��\n"NOR,me);
			me->delete_temp("shenyuan");
			me->add_temp("apply/parry", -skill1/10);	   			
			me->add_temp("apply/strength",-skill1/30);
			me->add_temp("apply/attack", -skill1/5);
		}
		return;
	}	
	call_out("remove_effect",2,me,skill-6);	
	return;
}

int help(object me)
{
        write(YEL"\n��Ԫ��"+HIB"����Ԫ����"NOR"\n");
        write(@HELP
	��Ԫ�����ǹ���Ľ�����ҵĶ����ڹ���ϰ���ţ�
	�������ԣ������Ƿ壬��Ľ�ݡ����ɼ�����Ľ��
	������ֻ������Ľ�����Զ�ת���ƾ�ѧ���ｭ
	�����䱾�ʾ���һ�ֽ�������������ţ���
	����Ҫ�����ɺͶԶԷ��似����Ϥ���˽⣬��
	����ȴ��Ҫ�������������̶ȡ�
	��Ԫ��֮��Ԫ����������������������Լ���
	����ʹ������š����⿪������Ԫ�����Ͷ�
	ת���Ƽ��ɷ����ڻ��ͨ����ʹĽ���似����
	ʤһ�����Խ������Խ��

	ʹ��ָ�yun shenyuan

Ҫ��
	�����ڹ��ȼ� 100 ���ϣ�
	��Ԫ�����ȼ� 100 ���ϣ�
	350��С�ɣ�450���ɡ�

HELP
        );
        return 1;
}
