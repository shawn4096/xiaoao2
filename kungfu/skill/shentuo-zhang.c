// This program is a part of NITAN MudLIB
// shentuo-zhang ����ѩɽ��

#include <ansi.h>
inherit SKILL;

string *action_msg = ({
        "$N˫��һ�棬ʹ��һ�С�������������������ת������Ʈ��������$n��$l",
        "$N�������һ���������ƣ��������ͣ�ʹ��һʽ����Į���������$n��$l",
        "$N���ȷ��������������ף��������޵�����$n��$l������һ�С����տ��㡹",
        "$N���η�����һʽ�������˪������Ӱ�׷ɣ������ھ��Ѱ�$n������ͳͳ��ס",
        "$N���μ�ת�������һ�С����ճ�������ͷ�½��ϣ�ɲ�Ǽ��ֽ��빥������$n��$l",
        "$N����һ����ʹ��һʽ��ѩ��ǧɽ��������������ŭ����ӿ����������$n��$l",
});


int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }

int valid_combine(string combo) 
{ 
	//�⿪�����������Ի���
	if (this_player()->query("quest/bt/stxsz/hubei/pass"))
		return combo == "lingshe-quanfa"; 
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("������ѩɽ�Ʊ�����֡�\n");

        if ((int)me->query_skill("hamagong",1) < 15)
                return notify_fail("��ĸ�󡹦��򲻹����޷�ѧ����ѩɽ�ơ�\n");

        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������̫�����޷�������ѩɽ�ơ�\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 320 + random(60), 
                "attack": 50 + random(10), 
                "dodge" : 50 + random(10), 
                "parry" : 50 + random(10), 
                "damage_type" : random(2)?"����":"����", 
        ]); 
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 60)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 60)
                return notify_fail("�����������������ѩɽ�ơ�\n");
        me->receive_damage("qi", 50);
        me->add("neili", -50);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shentuo-zhang/" + action;
}
