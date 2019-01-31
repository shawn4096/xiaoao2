// shenhuo-shengong.c
#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
        if (me->query_skill("force", 1) < 10)
      	    return notify_fail("��Ļ����ڹ�����Ҫ��һ����ߡ�\n");

    	if ( me->query("gender") == "����")
		    return notify_fail("���޸����ԣ����������������������Ѫ���󷨡�\n");

        if ((int)me->query_skill("xuedao-dafa", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("xuedao-dafa", 1) >= 200 )
               return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

	return valid_public(me);
}

int practice_skill(object me)
{
       if((int)me->query_skill("xuedao-dafa", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("xuedao-dafa", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ���������Ѫ�����ˡ�\n");       }
        else return notify_fail("�����ڵ�Ѫ������Ϊֻ����ѧ(learn)�������������ȡ�\n");

}

string exert_function_file(string func)
{
	return SKILL_D("xuedao-dafa/") + func;
}
mapping exercise_msg(object me)
{
  return ([
    "status_msg" : HIR + me->name()+"�������࣬������һ��Ѫ������֡�" NOR,
    "start_my_msg" : "����ϥ������˫�ִ�����ǰ�������������þ����е���������һ����������ӿ�뵤�\n",
    "start_other_msg" : me->name()+"��ϥ������˫����ǰ�ش�ס���������࣬�������һ��Ѫ��֮ɫ��\n",
    "halt_msg" : "$N����΢΢����������������վ��������\n",
    "end_my_msg" : "�㽫������Ϣ��ͨ���������������۾���վ��������\n",
    "end_other_msg" : "ֻ��"+me->name()+"�����۾���վ��������ͷ�����۵ĺ�������Ʈɢ����\n",
    "heal_msg" : HIW"$N��ϥ������˫��ʮָ�ſ���������ǰ������"RED"Ѫ����"HIW"��ʼ���ˡ�\n"NOR,
    "heal_finish_msg" : HIW"$N�������⸡�֣�һ����������������\n"NOR,
    "heal_unfinish_msg" : "$N��̬ׯ�ϣ�����վ��������������Ѫ�죬�������ƻ�û����ȫ�ָ���\n",
    "heal_halt_msg" : "$N�����ͺ죬ͷ�����������������͵���һ����������������������\n",
    ]);
}
