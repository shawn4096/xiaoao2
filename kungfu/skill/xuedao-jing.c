// xuedao-jing.c
//xuedao-jing �޸ĳ��ڹ�

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
        if (me->query_skill("force", 1) < 10)
      	    return notify_fail("��Ļ����ڹ�����Ҫ��һ����ߡ�\n");

    	if ( me->query("gender") == "����")
		    return notify_fail("���޸����ԣ����������������������Ѫ������\n");

        if ((int)me->query_skill("xuedao-jing", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("xuedao-jing", 1) >= 200 )
               return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

	return valid_public(me);
}

int practice_skill(object me)
{
       if((int)me->query_skill("xuedao-jing", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("xuedao-jing", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ���������Ѫ�����ˡ�\n");       }
        else return notify_fail("�����ڵ�Ѫ������Ϊֻ����ѧ(learn)�������������ȡ�\n");

}

string exert_function_file(string func)
{
	return SKILL_D("xuedao-jing/") + func;
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

int ob_hit(object ob, object me, int damage)
{

        int lvl;
        int flvl;
		int level, jiali, time,level2,damage2;
	    int neili, neili2;
		string msg,dodge_skill,*limbs;
		object weapon;
		object target;
		damage2= (int) ob->query("neili",1)/10;
		if (damage2>= 2800) damage2 = 2800;
		level = (int) me->query_skill("xuedao-jing",1);
		if (random(10)>7
			&& level>=150 
			&& me->query_skill_mapped("force") == "xuedao-jing" )
		{
			if (!ob->is_busy()) ob->start_busy(3);	
			if (me->query("qi") <= me->query("max_qi")*2) me->add("qi",damage2);
			if (me->query("eff_qi") <= me->query("max_qi")*2) me->add("eff_qi",damage2);
			msg = HBRED+HIW"$Nʹ��Ѫ�����ܹ���������$n��������Ѫ��ȫ����˺�����˺ܶ࣡!\n"NOR;
            message_vision(msg, me, ob);
		}
		return damage;
}
