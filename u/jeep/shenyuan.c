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
	
	if (!me->is_fighting() && !me->query("shenyuan/powerup"))
		return notify_fail("��ֻ����ս����ʹ����Ԫ����\n");

	skill = me->query_skill("shenyuan-gong",1);
	
	if( (int)me->query_skill("shenyuan-gong",1) < 100 )
		return notify_fail("��Ŀǰ�ȼ��������в���ʹ����Ԫ����\n");

	if( (int)me->query("neili") < skill  )
		return notify_fail("�������������\n");
 
	if( (int)me->query_temp("shenyuan") ) 
		return notify_fail("���Ѿ���������Ԫ���ˡ�\n");

	me->add("neili", -300);
	
	message_vision(HIY "$N����Ľ�ݾ�ѧ��Ԫ�����ƺ���֪�书·�������������ɶ��ˡ�\n" NOR, me);
	if (me->query("shenyuan/powerup"))
	{
		message_vision(HIC "$N����ת�����ķ��ںϵ���Ԫ��֮�У������ڻ��ͨ��\n" NOR, me);
		me->add_temp("apply/parry", skill/2);	
		me->add_temp("apply/dexerity", skill/15);
		me->add_temp("apply/strength",skill/15);
		me->add_temp("apply/attack", skill/4);
	}
	else {
		me->add_temp("apply/parry", skill/10);	
		me->add_temp("apply/strength",skill/30);
		me->add_temp("apply/attack", skill/5);
    }

    if(me->query_skill("shenyuan-gong",1) < 450)
    {
		me->start_busy(1);
		me->start_exert(1, "��Ԫ��");
    }

	me->set_temp("shenyuan", skill);
	me->set_temp("sy/shenyuan", skill);
	call_out("remove_effect", 1, me, skill);

	return 1;
}

void remove_effect(object me, int skill)
{
	int skill1;
	if(!me) return;
	else skill1 = me->query_temp("sy/shenyuan");
	
	if (me->query_temp("shenyuan") && me->query("shenyuan/powerup"))
	{
		if (skill > 0) {
			skill = skill - 6;
			call_out("remove_effect", 1, me, skill);		  
			return;
		}
		message_vision(HIB"$N�����չ����ָֻ�������״̬��\n"NOR,me);
        me->delete_temp("shenyuan");
        me->add_temp("apply/parry", -skill1/2);	
   	    me->add_temp("apply/dexerity", -skill1/15);
	    me->add_temp("apply/strength",-skill1/15);
	    me->add_temp("apply/attack", -skill1/4);
	} 
	else 
	{
		if (me->is_fighting()){         
			call_out("remove_effect", 2, me, skill);		  
			return;
		}
		me->delete_temp("shenyuan");
		message_vision(HIB"$N�����չ����ָֻ�������״̬��\n"NOR,me);
		me->add_temp("apply/parry", -skill1/10);	
		me->add_temp("apply/strength",-skill1/30);
		me->add_temp("apply/attack", -skill1/5);
	}
	return;
}

int help(object me)
{
        write(YEL"\n��Ԫ��"+HIB"����Ԫ����"NOR"\n");
        write(@HELP
		��Ԫ�����ǹ���Ľ�����ҵĶ����ڹ���ϰ���ţ��������ԣ������Ƿ壬��Ľ�ݡ���
		�ɼ�����Ľ�ݵ�����ֻ������Ľ�����Զ�ת���ƾ�ѧ���ｭ�����䱾�ʾ���һ��
		��������������ţ�������Ҫ�����ɺͶԶԷ��似����Ϥ���˽⣬������ȴ
		��Ҫ�������������̶ȡ�
		��Ԫ��֮��Ԫ����������������������Լ�������ʹ������š����⿪����
		��Ԫ�����Ͷ�ת���Ƽ��ɷ����ڻ��ͨ����ʹĽ���似����ʤһ�����Խ��
		����Խ��
		Ҫ��
			�����ڹ��ȼ� 100 ���ϣ�
			���Ǵ󷨵ȼ� 100 ���ϣ�
			350��С�ɣ�450���ɡ�

HELP
        );
        return 1;
}
