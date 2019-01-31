// sanhua.c �����۶���
// sohu@xojh

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
void remove_effect(object me, int amount);

int perform(object me, object target)
{
	int skill,i;
	string msg;


	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("�����۶�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( !me->query("quest/qz/htz/sanhua/pass") )
		return notify_fail("����δѧ�����е�ʹ�÷�����\n");


	if( objectp(me->query_temp("weapon")) )
		return notify_fail("���ֲ���ʩչ�����۶���\n");

	if( me->query_skill_mapped("strike") != "haotian-zhang" )
		return notify_fail("�����õĲ�������ƣ�����ʩչ�����۶���\n");
	if( me->query_skill_mapped("parry") != "haotian-zhang"
		&& me->query_skill_mapped("parry") != "kongming-quan")
		return notify_fail("�����õ��мܲ�������ƻ����ȭ������ʩչ�����۶���\n");
	if( me->query_skill_prepared("strike") != "haotian-zhang" )
                return notify_fail("�������Ĳ�������ƣ�����ʩչ�����۶���\n");

	if( me->query_skill_mapped("force") != "xiantian-gong" )
                return notify_fail("�����õĲ������칦��ʩչ���������۶���\n");

	if( me->query_skill("force") < 350 )
		return notify_fail("������칦���δ�����޷�ʩչ�����۶���\n");

	if( me->query_skill("strike") < 350 )
		return notify_fail("�����۶���Ҫ��տ������Ʒ�����Чʩչ��\n");

	if( me->query("neili") <= 1500 )
		return notify_fail("�����������ʹ�������۶���\n");

	if( me->query("jing") <= 1200 )
		return notify_fail("��ľ�����ʹ�������۶���\n");
  	
	if( me->query_temp("htz/juding") )
		return notify_fail("������ʹ�������۶�������\n");
	i=me->query("quest/qz/htz/sanhua/pass");
	
	if (i>0)
		msg = HIC"$N�����������칦�������鲼ȫ��ͷ��ð��˿˿�����������ڶ���״��"+chinese_number(i)+"��"+HIW"����"+HIC"�������Ʒ�����������\n\n"NOR;
	else msg=msg = HIC"$N�����������칦�������鲼ȫ��ͷ��ð��˿˿�����������ڶ��������Ʒ�����������\n\n"NOR;
	message_vision(msg, me, target);

	skill =me->query_skill("haotian-zhang",1);
	
	me->set_temp("htz/sanhua", 3);

	if( me->query("quest/qz/htz/sanhua/pass")>1 )
	{
	   message_vision(HIW"$N�����칦��ת����������������۶��̺���������¶���ɣ�\n"NOR,me);
	   skill =me->query_skill("haotian-zhang",1)+ me->query_skill("xiantian-gong",1)/ 3;
	}
	me->set_temp("htz/juding", skill);

	me->add_temp("apply/attack", skill/4);
	me->add_temp("apply/damage",  skill/6);
	me->add_temp("apply/strike",  skill/4);
	me->add_temp("apply/strength",skill/20);

	me->add("neili", -skill/2);
	me->add("jingli", -skill/3);
	me->add("jing", -100);
	remove_effect(me,skill/15);
	//call_out("remove_effect",1,me,(int)skill/15);
	return 1; 
}


void remove_effect(object me, int amount)
{
	int skill;
	if (!me||!me->query_temp("htz/juding")) return;
	skill=me->query_temp("htz/juding");
	if (!me->is_fighting()
		||me->query_skill_prepared("strike")!="haotian-zhang"
		||me->query_skill_mapped("strike")!="haotian-zhang"
		||me->query_skill_mapped("parry")!="haotian-zhang"
		||amount<0)
	{
		me->add_temp("apply/attack", -skill/4);
		me->add_temp("apply/damage", -skill/6);
		me->add_temp("apply/strike", -skill/4);
		me->add_temp("apply/strength",-skill/20);

		me->delete_temp("htz/juding");
		//me->delete_temp("htz/sanhua");

		message_vision(	HIC "\n$N����һ��������ɢ���۶������������ջص��\n\n" NOR, me);
		return;
	}
	call_out("remove_effect",1,me,amount--);
}
string perform_name(){ return HIW"�����۶�"NOR; }

int help(object me)
{
        write(HIC"\n�����֮�������۶�����"NOR"\n");
        write(@HELP
	�������ȫ���ǰ���书֮һ���������к��ĵ��������书
	ȫƾһ���������ڣ����಻������ʹ���������Է���������
	����ȫ��߼��书�Ļ�����ȫ�����������������
	�����۶����ǽ�ȫ�������Ƴ�������ת����������������
	�칦�������ˮ�齻�ڣ�������ޣ���ʱ���ڴ������Ǳ��
	ʹ���Ʒ������޴�
	ע�⣺��������ܷ���ʹ��,��Ҫ�����������۶����緽���
		
	ָ�perform strike.juding

Ҫ��
	���칦���ĵȼ� 350  ���ϣ�
	����Ʒ��ĵȼ� 350  ���ϣ�
	�����Ʒ��ĵȼ� 350  ���ϣ�
	��ǰ������Ҫ�� 1500 ���ϣ�
	��ǰ�ľ���Ҫ�� 1200 ���ϣ�
	�����Ʒ�Ϊ����ƣ�
	�����м�Ϊ����ƻ����ȭ��
	�����ڹ����칦��
	�����ұ��Ʒ�Ϊ����ơ�
HELP
        );
        return 1;
}
