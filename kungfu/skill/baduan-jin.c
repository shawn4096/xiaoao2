// baduan-jin.c �˶ν�
//updated by sohu@xojh

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { 
	 
	return usage == "force"; }

#include "force.h"

int valid_learn(object me)
{
	int lvl = (int)me->query_skill("baduan-jin", 1);
	int t = 1, j;
	
	if (!me->query("quest/baduanjin/pass"))		
		return notify_fail("�˶ν�ֻ��ͨ�����ܺ󷽿�ѧϰ��\n");

	for( j = 1; j < lvl / 10; j++) t *= 2;
	if( t > 5000 ) t = 5000;
	//if( me->query("gender") == "����" && lvl > 49 )
		//return notify_fail("���޸����ԣ���������������������İ˶ν���\n");

    if( (int)me->query_skill("force", 1) < 10 )
		return notify_fail("��Ļ����ڹ���򻹲�����\n");

	if( (int)me->query_skill("baduan-jin", 1) > me->query_skill("force", 1) + 10
	&& me->query_skill("baduan-jin", 1) >= 200 )
		return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

	return valid_public(me);
}

int practice_skill(object me)
{
    if (!me->query("quest/baduanjin/pass"))		
		return notify_fail("�˶ν�ֻ��ͨ�����ܺ󷽿���ϰ��\n");

   if( (int)me->query_skill("baduan-jin", 1) >= 210 ) {

	if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200) {
			me->improve_skill("baduan-jin", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("�����ڵ���Ϊ��������߰˶ν��ˡ�\n");
	}
	else return notify_fail("�����ڵİ˶ν���Ϊֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"baduan-jin/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIW + me->name()+"ͷ��������Ũ���İ�������ɫ��Ϊ����" NOR,
		"start_my_msg" : "��������һ�������뵤�Ȼ���ɵ������У������������������γ�һ��Сѭ����\n",
		"start_other_msg" : me->name()+"��ϥ����������˫�����ճ�ȭ��������ת������\n",
		"halt_msg" : "$N����һ��������վ��������\n",
		"end_my_msg" : "�㽫�˶ν�����֮������������ʮ�����죬���ص��ֻ����ȫ��̩ͨ�ġ�\n",
		"end_other_msg" : me->name()+"����һ������ɢȥȫ��˶ν�������һ���½�վ��������\n"
	]);
}
