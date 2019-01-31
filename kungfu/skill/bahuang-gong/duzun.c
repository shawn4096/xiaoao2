// duzun.c
// action@SJ 2009/1/17
// edited by sohu@xojh  ��һ��30����ǰ�չ�һ�ξͿ��ԣ��ڶ���40��ǰ��������60��
#include <ansi.h>
inherit F_CLEAN_UP;

string exert_name(){ return HIR"Ψ�Ҷ���"NOR; }

int exert(object me, object target)
{
	int skill,i;
    i=1;
	if( me->query("neili") < 2000 )
		return notify_fail("�������������\n");
	if( me->query("jingli") < 1000 )
		return notify_fail("��ľ���������\n");
    if( me->query("bhg/biguan") < 1 )
		return notify_fail("����û�бչز���˻Ĺ������ܼ������ڹ���\n");
	if( me->query_skill("bahuang-gong", 1) < 350 )
		return notify_fail("��İ˻�����Ψ�Ҷ��𹦵ȼ�������\n");

	if( me->query_skill_mapped("force") != "bahuang-gong" )
		return notify_fail("����ڹ����ԡ�\n");

	if( me->query_temp("bhg/duzun") )
		return notify_fail("���Ѿ����ˡ��˻�����Ψ�Ҷ����ˡ�\n");

	skill = me->query_skill("bahuang-gong")/5;
	if (me->query("bhg/biguan")<0) return 0; 
	//�������һ�β���Ч����Ҳ����˵26��ʱ�����ʹ�ã��е����
	i=me->query("bhg/biguan");
    skill=skill*i;
	me->receive_damage("neili", -300);
	message_vision(HBGRN+HIW "$N�����³����İ�����ס$N�Դ���Χ�����Ʋ�ɢ������������Ũ����Ϊһ�Ű�����$N��Ŀ����û�ˣ�\n"
	                          +"���ų���һ��������������ת����,ֻ����$Nȫ��ǽڸ�����죬���籬������\n" NOR, me);
    
    
	me->set_temp("bhg/duzun", skill); 
   // me->add_temp("apply/armor", me->query_skill("bahuang-gong", 1)/5); 
    me->add_temp("apply/hand", skill);
	me->add_temp("apply/strike", skill);
    me->add_temp("apply/attack", skill);
    me->add_temp("apply/damage", skill/4);
	call_out("remove_effect", 1, me, skill);
	me->start_exert(1, "Ψ�Ҷ���");
	if( me->is_fighting() )
		me->start_busy(random(2));
	return 1;
}

void remove_effect(object me, int count)
{
	int skill;
	if( objectp(me) && me->query_temp("bhg/duzun") ) {
		if( count-- > 0 ) {
			call_out("remove_effect", 1, me, count);
			return;
		}
		skill = me->query_temp("bhg/duzun");
     me->add_temp("apply/hand", -skill);
	 me->add_temp("apply/strike",- skill);
     me->add_temp("apply/attack", -skill);
     me->add_temp("apply/damage", -skill/4);
     me->delete_temp("bhg/duzun");
		message_vision(HIR"$N���������ὥϡ���������Ű���Ҳ�������ˣ�$N�ǿ��в�������������ð���������$N����˫�ۣ�����վ��\n"NOR,me);
	}
}

int help(object me)
{
	write(HIW"\n�˻�����Ψ�Ҷ���֮��Ψ�Ҷ��𹦡���"NOR"\n\n");
        write(@HELP
	�˻�����Ψ�Ҷ�����������ң���������ɾ���֮һ
	����ͯ���޳ִ˹���������ʦ�ֵı�ڤ�񹦡�ʦ����
	��ˮ������С�������࿹�⡣�˻�����Ψ�Ҷ���ԭ
	��������֮��ǿ���Ĺ�����ÿ��ʮ����Ҫ�չ�һ�Σ�
	���ϻ�ͯһ�Σ�ÿһ�λ�ͯ��������������������
	��,�չ����κ����������ͷţ��������֡�
	
	ָ�yun duzun

Ҫ��
	��ǰ����  1000 ���ϣ�
	��ǰ����  2000  ���ϣ�
	�˻�����Ψ�Ҷ���  350  �����ϣ�
HELP
        );
        return 1;
}