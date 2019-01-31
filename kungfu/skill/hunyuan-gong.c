//by sohu@xojh ��Ԫ�� 

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { if (this_player()->query("quest/chengkun/pass")) return usage == "force"; }

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
	if ( me->query("gender") == "����")
		return notify_fail("���޸����ԣ���������������������Ļ�Ԫ����\n");

        if ((int)me->query_skill("hunyuan-gong", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("hunyuan-gong", 1) >= 200 )
               return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

        return valid_public(me);
}

int practice_skill(object me)
{
       if((int)me->query_skill("hunyuan-gong", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("hunyuan-gong", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ��������߻�Ԫ���ˡ�\n");       }
        else return notify_fail("�����ڵĻ�Ԫ����Ϊֻ����ѧ(learn)�������������ȡ�\n");

}
void skill_improved(object me)
{
        int skill, lit;
        skill = me->query_skill("hunyuan", 1);
        lit = me->query_skill("literate", 1);
        if(skill >= 300 && !me->query("hyg/300") && me->query("age")>35){
                tell_object(me, HIR"\n��������о�һ�����ˣ��ӵ���ӿ�������������������������ߣ�\n"NOR);
                me->add("max_neili", random(lit + skill));
                me->set("hyg/300", 1);
        }
}


string exert_function_file(string func)
{
        return SKILL_D("hunyuan-gong/") + func;
}
mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIW + me->name()+"��ϥ�������������¡�" NOR,
		"start_my_msg" : "����ϥ���£�˫����ԣ�����״����ʼ�����Ԫ���ķ���һ������ӿ�����ӡ�\n",
		"start_other_msg" : me->name()+"��ϥ�������˫����ԣ��ϱ��������ϳ���һƬ���֮ɫ��\n",
		"halt_msg" : "$N΢΢����˫�ۣ�ƽϢ���ڵ��ؿڣ�����վ��������\n",
		"end_my_msg" : "����תһ�����죬���䵤�˫�ֻ���̧��վ��������\n",
		"end_other_msg" : "ֻ��"+me->name()+"˫��������̧��վ�����������ϵĳ�������ȥ��\n"
	]);
}
