#include <ansi.h>
inherit FORCE;

int valid_enable(string usage)
{
	  if (this_player()->query("family/family_name")=="����Ľ��" )
		 // || this_player()->query("cw_mp/����Ľ��")
        return usage == "force";
}

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
		mapping fam  = me->query("family");
	if ((!fam || fam["family_name"] != "����Ľ��" )&& !me->query("cw_mp/����Ľ��") )
			 	return notify_fail("�㲢��Ľ�ݵ��ӣ����ϰ����Ľ���񹦡�\n");
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





mixed hit_ob(object me,object victim,int damage)
{
	string msg;
	int j;
	j = me->query_skill("douzhuan-xingyi", 1)+random(me->query_skill("shenyuan-gong", 1));
	//j=j/2;
	if (!objectp(victim)) return;
	
     if (me->query_skill_prepared("finger") != "canhe-zhi"
           || me->query_skill_mapped("finger") != "canhe-zhi"
		   ||!me->query_temp("shenyuan")
		   ||!me->query("quest/mr/dzxy/pass"))
      return 0;  
  
  //���ó�questģʽ��
 
	if ( random(me->query_skill("force",1)) > victim->query_skill("force",1)/2
         //&& random(10)>5
	     && me->query("jingli") > 300
		 && me->query_temp("shenyuan")
	     && random(me->query("combat_exp")) > victim->query("combat_exp")/2
         && me->query("neili") > 500
		
         || ( userp(me) && me->query_temp("lianhuan") && random(j)>=300 )
         ||( !userp(victim) && me->query_temp("lianhuan")) )
         {
		   switch(random(3))
		   {
			case 0 :
				message_vision(HIW"$NĬ����Ԫ�񹦣�һ�������ָ����ƮƮ�ص���$n��һ���ھ�������Ϣ������$n�����Ѩ��\n"NOR,me,victim);
				if (random(me->query_skill("finger",1))>victim->query_skill("parry",1)/2)
				{
					message_vision(HIR"$nֻ��ȫ��һ�飬�ѱ�һ�е��С�����Ѩ����\n"NOR,me,victim); 
				    if (me->query("quest/mr/dzxy/pass")) {
						victim->add_busy(3);
						victim->apply_condition("no_perform",2);
					}
				    else victim->add_busy(1);
						
				}
				else
                    message_vision( GRN"$nʶ����$N����ʽ�����Ա߶�����ȥ��\n"NOR,me,victim); 
				break;
			case 1 :
				//if (!random(2)) break;
				
			    message_vision(HBRED"$Nָ��Ϭ������һ�����ν�������$n�������ڣ�$nֻ���ؿ�һʹ��ȫ��������к������\n"NOR,me,victim);
				victim->recevied_damage("neili", j*2);
                victim->add_busy(1+random(2));
                victim->add_condition("no_exert",1+random(2));				
				if ( victim->query("neili") < 0 )
					victim->set("neili", 0);
				me->add("neili",-20);
				break;
			case 2 :
				if (me->query_skill_mapped("parry")!="douzhuan-xingyi") break;
				
			    msg = HIG"$N����Ľ�ݼҴ���ѧ��Ԫ��,����ӿ������϶�ת���ƾ�����Ȼʩչ����һ�С�\n"NOR;
			    if (random(me->query_str(1))>victim->query_dex(1)/2)
			    {
					 message_vision(HIC"$nֻ���Լ������й�������$N������,�������뵽��̶֮�У���������������\n"NOR,me,victim);
					victim->recevied_damage("jing", j,me);
					victim->set_temp("lost_attack",1+random(3));
					victim->add_busy(1+random(3));
					if (victim->quuery("neili")>3000)
						victim->add("neili",-random(3000));
					if ( victim->query("neili",1) < 0 )
						victim->set("neili", 0);
					me->add("neili",-20);
				}
				else 
                   message_vision(HIY"���������㣬һ�����ӻ��裬��ƮƮ�������Ծ��$N�ľ������ַ�Χ��Χ��\n"NOR,me,victim);
				break;
				//default: break;
		}
		//message_vision(msg, me, victim);
		
	}
}
