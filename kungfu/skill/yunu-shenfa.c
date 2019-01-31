// yunu-shengfa.c ��Ů��
#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
HIW"$nһ�С������貨���������趯����ס����ȥ������ƮƮ�������⣬�����$N��һ�С�\n"NOR,
HIR"$n��ȻһЦ�����˾������ѽ��⡸һЦ�����֮�ƣ��ܿ���$N���������ơ�\n"NOR,
HIM"$nʹ����������ơ���������Σ��Ų�������������$N�����\n"NOR,
HIC"$n�����أ��ۿ�$Nɱ�п���Ϯ����һ�С����ҹ�����������ѽ���ƽ�ƣ�����һ�ԡ�\n"NOR,
MAG"$nһʽ������׹¥�����������ػ��У�����˷�����˼����$N�Ĺ�����Ȼ�˿ա�\n"NOR,
});

int valid_enable(string usage) { return (usage == "dodge"); }

int valid_learn(object me)
{
	if ( me->query_skill("yunu-xinjing", 1) < 10)
		return notify_fail("�����Ů�ľ��ȼ��������޷�������Ů����Ҫ����\n");
	return 1;
}

string query_dodge_msg(object me)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if((int)me->query("jingli") < 30 )
		return notify_fail("�����Ϣһ���ˣ��Ȼ�������Ů���ɡ�\n");
        me->receive_damage("jingli", 10);
	return 1;
}

mapping query_action(object me, object weapon)
{
	int level,out;
	level   = (int) me->query_skill("yunu-shenfa",1);
	out = (stringp(environment(me)->query("outdoors"))?1:0);
	
	if(me->query("family/family_name")!="��Ĺ��")
		return ([
			"action":dodge_msg[random(sizeof(dodge_msg))], 
			"dodge": -level/3,
		]);
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
	object room;
	int mdodge, tdodge,i;
	int j = 0;
	mdodge = me->query_skill("yunu-shenfa", 1);
	tdodge = ob->query_skill("dodge",1);
	room=environment(me);
	
	if (!room->query("outdoors")
		&& me->query_temp("ynxj/xinjing")
		&& !me->query_temp("ynsf/temp"))
	{
		i=20;	
		message_vision(HIW"\n��ʱ$N���������ڼ�������Ů���ڷ����������չ�ֵ����켫�£�\n"NOR,me);
		me->add_temp("apply/dodge",mdodge/2);
		me->add_temp("apply/defense",mdodge/2);
		me->set_temp("ynsf/temp",mdodge);
		call_out("ynsf_indoor",1,me);
	}else i=10;

    if (me->query_skill_mapped("dodge") != "yunu-shenfa") return 0;
	if (me->query("neili") < 5000) return 0;
	if (mdodge<450) return 0;
	//if (!me->query("env/��Ĺ����")) return 0;  
	
	if (me->query("quest/jiuyingm/pass")
		&& damage>2000
		&& me->query("env/��Ĺ����")
		&& random(3)) 		
	 {
		message_vision(HIW "$N��Ȼ�������澭�Ĺ����Ȼʩչ����������ý���Ʈ�����������������һ����\n" NOR,me,ob);
	    return -damage;
	 }

	 if( random(me->query_dex(1)) > ob->query_dex(1)/2	 
		 && random(me->query_int(1))>ob->query_int(1)/2	
		 && i >6)
	 {
		
		
		msg=random(2) ? HIR+dodge_msg[random(sizeof(dodge_msg))]+NOR:
			HIC+dodge_msg[random(sizeof(dodge_msg))]+NOR;
		message_vision(msg,me,ob);
        j=-damage;	
		return j;   
	 }
	

}

int ynsf_indoor(object me)
{
	int mdodge;
	object room;

	if (!me) return 0;
	mdodge=me->query_temp("ynsf/temp");
	room=environment(me);
	if ((room->query("outdoors") || (me->query_skill_mapped("dodge") != "yunu-shenfa") )&&me->query_temp("ynsf/temp"))
	{
		me->add_temp("apply/dodge",-mdodge/2);
		me->add_temp("apply/defense",-mdodge/2);
		me->delete_temp("ynsf/temp");
		message_vision(HIW"$N��������Ѹı���������Ů�������ڵ�����ɥʧ��\n"NOR,me);
		return 1;
	}
	call_out("ynsf_indoor",1,me);
}