// huntian.c ������������
// Change Powerup to huntian by Looklove 2001.5.3

#include <ansi.h>
inherit F_CLEAN_UP;

string exert_name(){ return HIR"����"NOR; }

int exert(object me, object target)
{
	int skill;

	if( me->query("neili") < 500 )
		return notify_fail("�������������\n");

	if( me->query_skill("huntian-qigong", 1) < 100 )
		return notify_fail("��Ļ��������ȼ�������\n");

	if( me->query_skill_mapped("force") != "huntian-qigong" )
		return notify_fail("����ڹ����ԡ�\n");

	if( me->query_temp("htqg/powerup") )
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("huntian-qigong",1);
	//if( skill > 150 ) skill = 150;

	me->receive_damage("neili", -300);
	message_vision(HIR "$N΢һ�������𡸻��졹�񹦣�ȫ���ǽڷ���һ�󱬶�������졣\n" NOR, me);
//ؤ��ǿ�����ǹ���,���нϴ��˺�����
	
	me->delete_temp("apply/dodge");	
   	me->delete_temp("apply/attack");
	me->delete_temp("apply/damage");	
	
	me->add_temp("apply/dodge", skill/6);	
   	me->add_temp("apply/attack", skill/2);
	me->add_temp("apply/damage", skill/6);
	//me->add_temp("apply/strength", skill/10);
	me->set_temp("htqg/powerup", skill);
	me->delete_temp("htqg/shougong");

	call_out("remove_effect", 1, me, skill);
	if (me->query_skill("huntian-qigong",1)<450)
	{
		me->start_exert(1, "��������");
	}
	if( me->is_fighting()&& me->query_skill("huntian-qigong",1)<450 )
		me->start_busy(1+random(1));
	return 1;
}

void remove_effect(object me, int count)
{
	int amount;
	if(!me) return;
	if(me->query_temp("htqg/powerup")){
	if( count-- > 0 && !me->query_temp("htqg/shougong") ) {
			call_out("remove_effect", 1, me, count);
			return;
		}	
		amount = me->query_temp("htqg/powerup");		
		me->add_temp("apply/dodge", - amount/6);	
     	me->add_temp("apply/attack",- amount/2);
	    me->add_temp("apply/damage",- amount/6);
	    //me->add_temp("apply/strength",- amount/10);
		me->delete_temp("htqg/powerup");
		me->delete_temp("htqg/shougong");
		tell_object(me, HIR"��Ļ�������������ϣ��������ջص��\n"NOR);
	   return;
	   }
}

int help(object me)
{
        write(HIR"\n��������֮�����졹��"NOR"\n");
        write(@HELP
	������������ؤ����Ҫ���ڹ����ܣ�����ؤ��ľ���������ļӳ����á�
	���ص�Ҳ�Ǽ�����ɫ������Խǿ������Խǿ�������д���ֻ�о�ָ��ؤ
	�Ķ����书�����ھ��ͱ�İ��ɲ�ͬ���������ֵĴ�����ֿ���ס��һ
	�㻯�ⷽ�������£��������ھ�������ȴ����ǰ������ֻ�������书
	���;��ף���ǿ��ǿ�������������������������ҲҪ�������������
	�ķ����෴��
	���������Ϊ����������Ҫ����֮һ��ͨ���˹����Խ��������кͷ���
	���������450����ȡ��busy��
	Ҫ��
		���������ȼ���100 ���ϣ�
		��ǰ����  500 ���ϡ�
	set �������� ��� �з�����Ч
HELP
        );
        return 1;
}