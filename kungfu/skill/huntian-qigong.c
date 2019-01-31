#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }
int ob_hit(object ob, object me, int damage);
int get_bouns(int damage,int t,int level,int flag);

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
	if ( me->query("gender") == "����")
		return notify_fail("���޸����ԣ���������������������Ļ���������\n");

        if ((int)me->query_skill("huntian-qigong", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("huntian-qigong", 1) >= 200 )
               return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

        return valid_public(me);
}

int practice_skill(object me)
{
       if((int)me->query_skill("huntian-qigong", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("huntian-qigong", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ��������߻��������ˡ�\n");       }
        else return notify_fail("�����ڵĻ���������Ϊֻ����ѧ(learn)�������������ȡ�\n");

}
void skill_improved(object me)
{
        int skill, lit;
        skill = me->query_skill("huntian-qigong", 1);
        lit = me->query_skill("literate", 1);
        if(skill >= 300 && !me->query("htqg/300") && me->query("age")>55){
                tell_object(me, HIR"\n��������о�һ�����ˣ��ӵ���ӿ�������������������������ߣ�\n"NOR);
                me->add("max_neili", random(lit + skill));
                me->set("htqg/300", 1);
        }
}


string exert_function_file(string func)
{
        return SKILL_D("huntian-qigong/") + func;
}
mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIW + me->name()+"�����⣬���۷���" NOR,
		"start_my_msg" : "���������£�˫��ƽ����˫ϥ��Ĭ��ھ�����ʼ��������ķ���\n",
		"start_other_msg" : me->name()+"�������������£�˫��ƽ����˫ϥ���촽΢΢���������ϵ����ۿ�ʼ�Ķ�������\n",
		"halt_msg" : "$N��ɫһ����Ѹ��������վ��������\n",
		"end_my_msg" : "�������뵤�������ת�����������չ���˫��̧��վ��������\n",
		"end_other_msg" : "ֻ��"+me->name()+"˫��̧��վ��������������������������\n"
	]);
}


int ob_hit(object ob, object me, int damage)
{
    int t,i;
    t = random(10); 
	i=me->query("neili")-ob->query("neili");
	if (i<=0) i=0;
	if (i>3000) i=2000+random(1000);
	
	if(!environment(me)) return 0;
	if( me->query_temp("htqg/powerup")&& t>7)		
	{
		if (random(me->query("neili"))>ob->query("neili")/2)
		{
			message_vision(HIR"$n��Ȼ��о�$N����������һ�ɴ����������ܵ��˲�С�ķ���\n"NOR,me,ob);
			ob->receive_damage("qi",random(i),me);
			ob->receive_wound("qi",100+random(100),me);
            return 1;
			//return -get_bouns(damage,t,me->query_skill("huntian-qigong",1),1);
		}
	
		//return -get_bouns(damage,t,me->query_skill("huntian-qigong",1),1);
	}
	
    if( (me->query("qi")-damage) >= 3000 ) return 0;
	
    if ( t >= 6 && me->query("env/��������")=="���" )
      {       
	       message_vision("$N"+HIY"�ۼ��Է����͵ĺܣ���������Ѫ������Хһ����ԽսԽ�£���$n������Ȼ���㣬������������������һ����\n" NOR, me,ob);
	       return -damage;
      }
}
int get_bouns(int damage,int t,int level,int flag)
{
	int dm;
	dm= (damage*flag*(t+level/20))/(t+level/20+10);
	if(flag && level>350) dm += dm/2;
	if(flag && level>450) dm += dm/2;
	
	return dm;
}
