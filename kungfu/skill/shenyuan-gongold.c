#include <ansi.h>
inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("��Ļ����ڹ���򻹲������޷������Ԫ����\n");

	if ( me->query("gender") == "����")
		return notify_fail("���޸����ԣ������������������������Ԫ����\n");

        if ((int)me->query_skill("shenyuan-gong", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("shenyuan-gong", 1) >= 200 )
               return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

        return valid_public(me);
}

int practice_skill(object me)
{
       if((int)me->query_skill("shenyuan-gong", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("shenyuan-gong", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ�����������Ԫ���ˡ�\n");
       }
        else return notify_fail("�����ڵ���Ԫ����Ϊֻ����ѧ(learn)�������������ȡ�\n");

              
}

string exert_function_file(string func)
{
        return __DIR__"shenyuan-gong/" + func;
}
mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIB + me->name()+"������������̬��Ϊ����" NOR,
		"start_my_msg" : "������һվ��˫�ֻ���̧������һ������������ʼ��������ת��\n",
		"start_other_msg" : me->name()+"����������һվ��˫�ֻ���̧������ʼ�������������\n",
		"halt_msg" : "$Nüͷһ�壬�������������ַ���������\n",
		"end_my_msg" : "�㽫����������������������һȦ���������뵤������֣�������һ������\n",
		"end_other_msg" : "ֻ��"+me->name()+"���۾��������ϣ��������������ַ��£�������һ������\n"
	]);
}
