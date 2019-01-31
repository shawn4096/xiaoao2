// yinyun-ziqi.c ������

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) {if (this_player()->query("family/family_name")=="�䵱��"|| this_player()->query("cw_mp/�䵱��")|| this_player()->query("expell/family_name")=="�䵱��" )
return usage == "force"; }

#include "force.h"

int valid_learn(object me)
{

		mapping fam  = me->query("family");


	int lvl = (int)me->query_skill("yinyun-ziqi", 1);
	int t = 1, j;

	for( j = 1; j < lvl / 10; j++) t *= 2;
	if( t > 5000 ) t = 5000;
	if( me->query("gender") == "����" && lvl > 49 )
		return notify_fail("���޸����ԣ�����������������������������񹦡�\n");
	if ((!fam || fam["family_name"] != "�䵱��" )&& !me->query("cw_mp/�䵱��") )
			 	return notify_fail("�㲢���䵱�ɵ��ӣ����ϰ�����䵱�񹦡�\n");

	if( me->query("class") == "bonze" )
		return notify_fail("�����������������ϣ���Υ��������徻֮�⣬" +RANK_D->query_respect(me)+"���޴˹������������\n");

	if( (int)me->query_skill("force", 1) < 15 )
		return notify_fail("��Ļ����ڹ���򻹲�����\n");

	if( (int)me->query_skill("yinyun-ziqi", 1) > me->query_skill("force", 1) + 10
	&& me->query_skill("yinyun-ziqi", 1) >= 200 )
		return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

	if( (lvl > 10 && lvl < 100 && (int)me->query("shen") < t * 200)
	|| ( lvl >=100 && (int)me->query("shen") < 10000) )
		return notify_fail("�����������̫���ˡ�\n");

	if( me->query("menggu") )
		return notify_fail("����Ͷ���ɹţ��޷��ٽ�һ�������������\n");

	return valid_public(me);
}

int practice_skill(object me)
{
	if( (int)me->query_skill("yinyun-ziqi", 1) >= 200 ) {
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200) {
			me->improve_skill("yinyun-ziqi", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("�����ڵ���Ϊ����������������ˡ�\n");
	}
	else return notify_fail("�����ڵ���������Ϊֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"yinyun-ziqi/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : MAG + me->name()+"ͷ�������������ɫ����" NOR,
		"start_my_msg" : "����ϥ������˫Ŀ���գ�������һ�������뵤�������һ����Ϣ��������Ѩ��������������֮����\n",
		"start_other_msg" : me->name()+"��ϥ����������˫�����ճ�ȭ����һ�ᣬͷ��ð����������\n",
		"halt_msg" : "$N΢һ��ü������Ϣѹ�ص������һ������վ��������\n",
		"end_my_msg" : "�㽫��Ϣ����������ʮ�����죬���ص��ֻ����ȫ��ů����ġ�\n",
		"end_other_msg" : me->name()+"����һ������һ���½�վ�����������о���һ����\n"
	]);
}
// mixed hit_ob  ���Ӳ�˿�������������ġ���̫��ȭһЩ��ʽ�ںϵ��ڹ����������������
/*
mixed hit_ob(object me,object ob,int damage)
{
   if (!me->query("tjg/taiji")) return;
   // ��˿����busy,tjg/chansi
   // �����Է��������ڶ��й���������
   // ���,��
   // ���𣬽���̫��ȭ��ȡ��ȭ����
   // ����������
   // �������ж϶Է��ڹ�
   // ����busy,���������
   // 

}

*/
mixed ob_hit(object ob, object me, int damage)
{
	    int ap, dp;
        int  lvl,i;
        lvl = me->query_skill("yinyun-ziqi", 1);
        if ( lvl < 500
          || me->query("neili") < 2000
          || me->query_skill_mapped("force") != "yinyun-ziqi")
         	return 0;
        if (!me->query_temp("yyzq/taiji")) return 0;       
		//if(!me->query("tjg/pass")) return 0;
         	
        ap = ob->query_skill("force");
        dp = me->query_skill("force");

        if (random(dp)> ap*2 /3 && random(me->query("neili")) > ob->query("neili")*2/3 )
        {
	        i = -damage;
            ob->receive_damage("qi", damage/4,me);
            //ob->receive_wound("qi", damage/5, me);

            message_vision(HIC"$N�Ѿ���������"HIG"����Բͨ"HIC"֮�����ֽ���ƽ��ѧ����������������գ�̫���񹦼���Ƿ��켫֮����"
                                  "\n����$N���ⲻ�þ���"HIY"��˿����"HIC"͸����ǰ�����ң�ȫ�޶���$n����������̶��\n"NOR,me,ob);
            ob->add_busy(1+random(2));			
            
            COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), userp(ob)?1:3); //�����֧��Ŷ
            return i;                              
         }    
        else if (random(dp)> ap /2 && random(me->query_con(1)) > ob->query_con(1)/2 )
         {
	      i = -damage;        //�������������й�����
          ob->receive_damage("qi", damage/5,me);
          //ob->receive_wound("qi", damage/3,me);
          message_vision(HIC"$N��������ǧ��֮�����Ҿ��ӱ˾���������ֱ���������ˣ�����������ת��������������ǿ��ǿ��"
                                   "\n�ǹ�������$N���ϣ�ȴ������ȥ����������˿��û���ܵ��˺���\n$n��ɫһ�ף��ܵ������������˺���\n"NOR,me,ob);
          return i;                               
          }      
 
        else if (random(dp+ap)> ap )
        {
	        i = - damage/3 - random(damage*2/3);  //����һС����ȫ���Ĺ���                                
            message_vision(HIC"$N��"HIM"̫����"HIC"���ᾢ���˱�ȫ������̼�ʹ������֫�ٺ�������ȫ����ȱ�ݴ����ް�͹�����޶�������"
                                   "\n$N�����������������죬����ʹ��������֮�������������ʹ��\n"NOR,me,ob);
            return i;
         }                          
 
         return 0;  

} 
