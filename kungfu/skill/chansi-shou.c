//���߲�˿��
// by sjxa@winnerlife
//2014-08-07
//edit buy sohu  chansi-shou.c
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : HIY"[��]"HIB"$N��������һ˿��â��ʮָ��£��˫��������ǰ��������ֱ����$n������˫��"NOR ,
"damage_type" : "����",
"lvl" : 0,
"skill_name" : "[��]",
]),
([      "action" : HIY"[��]"HIB"$N˫�������޹ǣ��Բ���˼��ĽǶ�ֱϮ$n�ĺ�["HIG"��׵Ѩ"HIB"]����$n�о���ʽ��ɬ�޴�����"NOR,
"damage_type" : "����",
"lvl" : 20,
"skill_name" : "[��]",
]),
([      "action" : HIY"[��]"HIB"$N����һ������ȫ���������һ�����죬˫�۳ɻ����Է�����˼�����������$n���ӣ�Ȼ��Ѹ�ٵ�һ��"NOR,
"damage_type" : "����",
"lvl" : 40,
"skill_name" : "[��]",
]),
([      "action" : HIY"[ת]"HIB"$N�������磬����$n�������ߣ�ͻȻ����һת���Ƶ�$n����̽��ֱȡ["HIW"�羮"HIB"]��["HIW"����"HIB"]��Ѩ"NOR,
"damage_type" : "����",
"lvl" : 80,
"skill_name" : "[ת]",
]),
([      "action" : HIY"[��]"HIB"$Nһ�����嵽$n��ǰʱȴͻȻ���д�$n���������ת��������ס$n��������$nͷ�½��������ײȥ"NOR,
"damage_type" : "����",
"lvl" : 100,
"skill_name" : "[��]",
]),
([      "action" : HIY"[��]"HIB"$N�嵽$n��ǰ��ͻȻ˫�ۻ���һ�������$n���У�ͬʱ�����ֱⷭϮ$n["HIC"��Ϫ"HIB"]��["HIC"���"HIB"]��Ѩ"NOR,
"damage_type" : "����",
"lvl" : 120,
"skill_name" : "[��]",
]),
([      "action" : HIY"[��]"HIB"$N�����ڱۣ�˫�ֲ��ں󱳣���Ȼ����ֱ��$n��˲�伴����˫�۶�Ȼ̽��ֱȡ$n����"NOR,
"damage_type" : "����",
"lvl" : 140,
"skill_name" : "[��]",
]),
([      "action" : HIY"[Ȧ]"HIB"$N������ָ��£����$n�ؿڣ��ұ�ͻȻ�������ߣ���$nҸ���ƹ�������$n������["HIR"����Ѩ"HIB"]"NOR,
"damage_type" : "����",
"lvl" : 160,
"skill_name" : "[Ȧ]",
]),
});

int valid_enable(string usage) { return usage=="hand" ||  usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����߲�˿�ֱ�����֡�\n");
	if (me->query("gender")=="����")
		return notify_fail("�����߲�˿�ֱ���Ů�ԡ�\n");
	if ((int)me->query_skill("dulong-dafa", 1) < 250)
		return notify_fail("��Ķ����󷨻�򲻹�250���޷�ѧ���߲�˿�֡�\n");
	if ((int)me->query("max_neili") < 250)
		return notify_fail("�������̫�����޷������߲�˿�֡�\n");
	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
		int i, level, j;
		string msg;
		level = (int)me->query_skill("chansi-shou", 1);

		for(i = sizeof(action); i > 0; i--)
		{
			if(level > action[i-1]["lvl"])
			{
				j = NewRandom(i, 20, level/5);
				if(me->query_temp("chss/lw"))
				{
					switch(me->query_temp("chss/lw"))
					{
						case 4: msg = HIW"$N��������һ˿��â��ʮָ��£��˫��������ǰ��������ֱ����$n������˫��"NOR; break;
						case 3: msg = HIW"$N˫�������޹ǣ��Բ���˼��ĽǶ�ֱϮ$n�ĺ�["HIG"��׵Ѩ"HIW"]����$n�о���ʽ��ɬ�޴�����"NOR; break;
						case 2: msg = HIW"$N�嵽$n��ǰ��ͻȻ˫�ۻ���һ�������$n���У�ͬʱ�����ֱⷭϮ$n["HIC"��Ϫ"HIW"]��["HIC"���"HIW"]��Ѩ"NOR; break;
						case 1: msg = HIW"$N�������磬����$n�������ߣ�ͻȻ����һת���Ƶ�$n����̽��ֱȡ["HIG"�羮"HIW"]��["HIG"����"HIW"]��Ѩ"NOR; break;
					}
					me->add_temp("chss/lw", -1);                  
			
					return 
					([
					"action":msg,
					"damage_type": "����",
					"force": 300 +random(300),
					"dodge": random(30),
					"parry": random(20)+20,
					"damage": 150 + random(100),
					]);
				}
				else
				{
					return 
					([
					"action": action[j]["action"],
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 150,
					"dodge": random(30),
					"damage": 100 + random(50),
					"parry": random(30),
					]);
				}
			}
		}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("chansi-shou", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 50)
		return notify_fail("��ľ���������\n");
	if ( me->query("neili") < 20)
		return notify_fail("����������������߲�˿�֡�\n");
	me->receive_damage("jingli", 40 );
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)

{
	return __DIR__"chansi-shou/" + action;
}