// SKILL liuyang-zhang.c

inherit SKILL;

mapping *action = ({
([	"action" : "$Nһ�С��޶ԡ������Ƶ�������֮�ϣ�����$n",
	"force" : 130,
	"dodge" : 20,
	"damage" : 10,
	"lvl" : 0,
	"skill_name" : "�޶�",
	"damage_type" : "����"
]),
([	"action" : "$Nһ�С���˫������ɫ���죬˫����ƮƮ������$n",
	"force" : 150,
	"dodge" : 10,
	"damage" : 30,
	"lvl" : 20,
	"skill_name" : "��˫",
	"damage_type" : "����"
]),
([	"action" : "$Nһ�С��޾С���˫�ƻû�һƬ��Ӱ����$n�������ڡ�",
	"force" : 150,
	"dodge" : 30,
	"damage" : 35,
	"lvl" : 30,
	"skill_name" : "�޾�",
	"damage_type" : "����"
]),

([	"action" : "$Nһ�С�����������$n��$l��������",
	"force" : 200,
	"dodge" : 25,
	"damage" : 50,
	"lvl" : 40,
	"skill_name" : "����",
    "damage_type" : "����"
]),
([	"action" : "$Nһ�С���������ֻ��һƬ��Ӱ����$n",
	"force" : 250,
	"dodge" : 20,
	"damage" : 70,
	"lvl" : 40,
	"skill_name" : "����",
	"damage_type" : "����"
]),

([	"action" : "$N˫��ƽ�ӣ�������Ӱ,�����Ʒ�,һ�С���Ϣ������$n",
	"force" : 300,
	"dodge" : 25,
	"damage" : 80,
	"lvl" : 60,
	"skill_name" : "��Ϣ",
            "damage_type" : "����"
]),
([	"action" : "$Nһ�С���Ӱ����ֻ��һƬ��Ӱ����$n",
	"force" : 350,
	"dodge" : 30,
	"damage" : 90,
	"lvl" : 70,
	"skill_name" : "��Ӱ",
	"damage_type" : "����"
]),

([	"action" : "$N������Σ�����һ�ǡ����١�����$n��ͷ��",
	"force" : 350,
	"dodge" : 50,
	"damage" : 120,
	"lvl" : 80,
	"skill_name" : "����",
           "damage_type" : "����"
]),

});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }
//int valid_combine(string combo) { return combo=="dashou-yin"; }


int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����Ӱ��ȭ������֡�\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������̫�����޷�����Ӱ��ȭ��\n");

	return 1;
}

//mapping query_action(object me, object weapon)
//{
//	int i, level;
//	level = (int) me->query_skill("wuying-shenquan",1);
//	for(i = sizeof(action); i > 0; i--)
//		if(level > action[i-1]["lvl"])
//			return action[NewRandom(i, 20, level/5)];
//}
/* ----------------
mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}
-------------------*/


mapping query_action(object me, object weapon)
{
	int i, level;
    level   = (int) me->query_skill("wuying-shenquan",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 5, level/5)];

}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 30)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("���������������Ӱ��ȭ��\n");
	me->receive_damage("qi", 25);
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"wuying-shenquan/" + action;
}
