// hunyuan-yiqi.c ��Ԫһ����
// dts@xkx, cleansword@xkx

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage)
{
	return usage == "force";
}

#include "force.h"

int valid_learn(object me)
{
	int nb, nf, nh, ns;
	nb = (int)me->query_skill("buddhism", 1);
	nf = (int)me->query_skill("force", 1);
	nh = (int)me->query_skill("hunyuan-yiqi", 1);
	ns = (int)me->query("guilty");

	if ( me->query("gender") != "����" )
		return notify_fail("�㴿��֮�壬������ϰ��Ԫһ������\n");
	//if (me->query("divorce"))
		//return notify_fail("��Ԫ��й¶������ѧϰ��Ԫһ������\n");
	if (me->query("family/family_name")!="������")
		return notify_fail("������ֵ��ӣ�����ѧϰ��Ԫһ������\n");
	if ( nb < 220 && nb <= nh )
		return notify_fail("��������ķ���Ϊ�������޷���������Ļ�Ԫһ������\n");

	if ( nf < 20)
		return notify_fail("��Ļ����ڹ���򻹲���20�����޷�����Ԫһ������\n");

	//if ( ns > 0 ) 
		//return notify_fail("���ŷ�ɮ�����䣬�޷���������Ļ�Ԫһ������\n");

	return valid_public(me);
}

int practice_skill(object me)
{
       if((int)me->query_skill("hunyuan-yiqi", 1) >= 220 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("hunyuan-yiqi", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ��������߻�Ԫһ�����ˡ�\n");       }
        else return notify_fail("�����ڵĻ�Ԫһ������Ϊֻ����ѧ(learn)�������������ȡ�\n");

}

string exert_function_file(string func)
{
	return __DIR__"hunyuan-yiqi/" + func;
}
mapping exercise_msg(object me)
{
  return ([
    "status_msg" : HIR + me->name()+"���Ϻ�����֣�����ׯ��" NOR,
      "start_my_msg" : "���������죬��������������ƣ��ų�һ�������Ϣ˳��������������\n",
          "start_other_msg" : me->name()+"�������죬һ�Ṥ�򣬴ӿڱǴ������³�����������Խ��ԽŨ������������ȫ��\n",
    "halt_msg" : "$N����һ����������Ϣ�������˻�ȥ��վ��������\n",
              "end_my_msg" : "�㽫��Ϣ���˸�С���죬���ص���չ�վ��������\n",
                  "end_other_msg" : "ֻ������"+me->name()+"�İ���������ɢ���ִӿڱǴ����˻�ȥ��\n"
                    ]);
}
