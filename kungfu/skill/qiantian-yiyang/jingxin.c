// jingxin.c ���ľ�
// ���ǹٸ����Ƿ�͹ٸ�Ӱ�����ҹ���
#include <ansi.h>

int exert(object me)
{
	int skill;
	skill = me->query_skill("buddhism", 1)/10;

	if(me->is_fighting())
	      return notify_fail("������ս���У���ο��Ծ���������\n");

	if((int)me->query_skill("qiantian-yiyang",1) < 100 )
	      return notify_fail("���Ǭ��һ����������죬�����ĳ�ײʹ�㾲����������\n");
/*
	if(me->query("class") == "bonze" )
	      return notify_fail("���Ѿ����ң������ĳ�ײʹ�㾲����������\n");*/

	if((int)me->query_skill("buddhism",1) < 50 )
	      return notify_fail("��ķ�ѧ��Ϊ�������޷���������Ǳ�ޣ�\n");

	if (me->query("neili") < 500  ) 
		return notify_fail("�������������\n");

	if (me->query_temp("qtyy/jingxin"))
		return notify_fail("��������ʹ���ľ���\n");
       
	me->add("neili", -250);

	message_vision(GRN "\n$N˫Ŀ΢�գ�ֻ�������徲ƽ�ͣ�������������֮����\n" NOR, me);
    if (me->query("yideng/ronghe")=="pass")
    {
		message_vision(GRN "\n$N���칦��Ǭ��һ���ศ��ɣ���Ȼ���ҡ�\n" NOR, me);
		skill=skill+me->query_skill("qiantian-yiyang",1)/30;
    }
	me->set_temp("qtyy/jingxin", skill);  
	me->add_temp("apply/intelligence",skill);
    me->add_temp("apply/dexerity",skill);
	call_out("remove_effect", 1, me, me->query_skill("qiantian-yiyang",1)/10);
	return 1;
}

void remove_effect(object me, int d)
{
	int i;

	if (!me) return;
	if (me->query_skill_mapped("force") == "qiantian-yiyang"
	    && --d > 0) {
		call_out("remove_effect", 1, me, d);
		return;
	}
	i = me->query_temp("qtyy/jingxin");
	me->add_temp("apply/intelligence", -i);
    me->add_temp("apply/dexerity",-i);
	me->delete_temp("qtyy/jingxin");
	tell_object(me, HIY "�㻺�����˿������Ӿ���״̬�����˳�����\n" NOR);
}

string exert_name(){ return GRN"���ľ�"NOR; }

int help(object me)
{
        write(GRN"\nǬ��һ����֮�����ľ�����"NOR"\n\n");
        write(@HELP
	�������з𷨣���ӽ����ڣ����Ծٹ�֮�½�������Ϊʤ
	Ǭ��һ������Ҫ��������ʽ����ͨ��������ʽ��ã�������
	ϰ���ľ�������ļ���,�������ʱ�������ӡ�

	perform jingxin

Ҫ��
	��ǰ������Ҫ�� 500 ���ϣ�
	Ǭ��һ�����ȼ� 100 ���ϣ�
	�����ķ��ĵȼ� 50 ���ϣ�
                

HELP
        );
        return 1;
}
