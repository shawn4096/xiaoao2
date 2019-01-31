// niqiu-gong.c �����������þ���������̶����ϰ����
//cre by sohu@xojh

#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
HIW"��֪$n����΢�࣬����ǰ��б�����ͣ�����$N�ľ���������һ�ԡ�\n"NOR,
HIR"$Nֻ��$n����ȴ��Ϳ��һ�������֬���ﻬ�쳣����Ȼ�ܿ���$N���������ơ�\n"NOR,
HIM"$n���ֿ��֮�������ѳ���ֱ�ϣ�˫����ָ��׶���ֽ�$N�ؿڡ���⡱�������顱��Ѩ��ȷ���ϳ˵�Ѩ����\n"NOR,
HIC"$Nֻ��һ�ɾ�����$n�����ұ۷�����ײ���Լ��ϱۣ�������λ������ū�ƣ��������Ըղ��ù��ġ�����������$N���ֱۻ��˿�ȥ��\n"NOR,
MAG"$Nһ����$n�ļ�ͷ��ȴ������һ���쳣���廬��֮��һ�㣬��Ȼץ֮��ס\n"NOR,
CYN"$nһ��ͷ������ˮ�ߣ��Ѵ�$NҸ�¡����˹�ȥ\n"NOR,
CYN"$n����һ���������������֣�$N����ס�������˹�ȥ\n"NOR,
HIG"$N�մ���$n���䣬����֪���ģ�����ֻ���͹�ˮ������$nһ�������ȥ��\n"NOR,

});

int valid_enable(string usage) { return (usage == "dodge"); }

int valid_learn(object me)
{
	if ( me->query_skill("force", 1) < 100)
		return notify_fail("��Ļ����ڹ��ȼ�����100�����޷���������������Ҫ����\n");
	if ( me->query_skill("dodge", 1) < 100)
		return notify_fail("��Ļ����Ṧ�ȼ�����100�����޷���������������Ҫ����\n");
	return 1;
}

string query_dodge_msg(object me)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if((int)me->query("jingli") < 30 )
		return notify_fail("�����Ϣһ���ˣ��Ȼ������������ɡ�\n");
        me->receive_damage("jingli", 10);
	
		return 1;
}

mapping query_action(object me, object weapon)
{
	int level,out;
	level   = (int) me->query_skill("niqiu-gong",1);
	out = (stringp(environment(me)->query("outdoors"))?1:0);
	
	if(me->query("gender") == "����")
		return ([
			"action":dodge_msg[random(sizeof(dodge_msg))],
			"dodge": level/3 + me->query_con() - out*level/5,
		]);
	else
		return ([
			"action":dodge_msg[random(sizeof(dodge_msg))],
			"dodge": level/2 + me->query_per()*4 - out*level/5,
		]);
}
int ob_hit(object ob, object me, int damage)
{
	string msg;
	int mdodge, tdodge;
	int j = 0;
	mdodge = me->query_skill("niqiu-gong", 1);
	tdodge = ob->query_skill("dodge",1);
	
    if (me->query_skill_mapped("dodge") != "niqiu-gong") return 0;
	if (me->query("neili") < 5000) return 0;
	if (mdodge<450) return 0;
	if (!me->query_temp("niqiu/fast")) return 0;  
	
	if (me->query("env/������")!="����") return 0;
	
	if (me->query("quest/niqiugong/pass") && random(10)>7) 		
	{
		message_vision(HIC "$N��Ȼ����һ��Ť�������Ѷ��У�����һ���������ͻ��ޱȣ��������������һ����\n" NOR,me,ob);
	    return -damage;
	 }
    else if (me->query("gender")=="Ů��"&& random(10)>6) 
    {
		if( random(me->query_dex(1)) > ob->query_dex(1)/3)	 
			//|| random(me->query_int(1))>ob->query_int(1)/3	 )
		{
		
			msg=random(2) ? HIR+dodge_msg[random(sizeof(dodge_msg))]+NOR:
				HIC+dodge_msg[random(sizeof(dodge_msg))]+NOR;
			message_vision(msg,me,ob);
			j=-damage/3;		
		}
    }else if (me->query("gender")=="����"&& random(10)>7)
    {
		if( random(me->query_dex(1)) > ob->query_dex(1)/2)	 
			// || random(me->query_int(1))>ob->query_int(1)/2	 )
		{
		
			msg=random(2) ? HIR+dodge_msg[random(sizeof(dodge_msg))]+NOR:
				HIC+dodge_msg[random(sizeof(dodge_msg))]+NOR;
			message_vision(msg,me,ob);
			j=-damage/4;		
		}	
    }
	
	return j;   
}
string perform_action_file(string action)
{
	return __DIR__"niqiu-gong/" + action;
}
