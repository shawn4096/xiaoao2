// ���� pfm ��������Ч�� by Lane@SJ
// kunlun-zhang.c ������

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N�Ʒ缤����˫�ƴ��䣬���������޷���һ�С������ɽ��������$n��$l",
	"lvl" : 0,
	"skill_name" : "�����ɽ",
	"damage_type" : "����"
]),
([
	"action" : "$N˫������һ�С������Ƶ�����һ�ƻ���$n���ţ���һ��ȴ����$nС��",
	"lvl" : 30,
	"skill_name" : "�����Ƶ�",
	"damage_type" : "����"
]),
([
	"action" : "$N˫�ƻ������Ī�⣬һ�С���粻������ǰ�����ң�˲Ϣ֮����$n����������һʮ����",
	"lvl" : 60,
	"skill_name" : "��粻��",
	"damage_type" : "����",
]),
([
	"action" : "$Nһ����Х������һ�ƣ�һ�С�ɽ��·ת��������ת׾��ȴ��ȥ����죬��$n��$l�ͻ���ȥ",
	"lvl" : 100,
	"skill_name" : "ɽ��·ת",
	"damage_type" : "����"
]),
([
	"action" : "$N˫�ƽ����������ޣ�һ�С������޷졹������$n��$l",
	"lvl" : 120,
	"skill_name" : "�����޷�",
        "damage_type" : "����"
]),
([
	"action" : "$Nһ�С���ɽ�Ϻӡ�������һȭ���������ƽ���������ȭ��һ����˫������������$n��$l",
	"lvl" : 140,
	"skill_name" : "��ɽ�Ϻ�",
	"damage_type" : "����"
]),
([
	"action" : "$N˫���뻮������˫�����ƣ�һ�С������ء���һ����ɽ������������ֱ��$n����",
	"lvl" : 160,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([
	"action" : "$NͻȻ�������ת��һ�С���ɽѩƮ������Ӱ���裬��ʱ֮�佫$n����˷�����ס��",
	"lvl" : 180,
	"skill_name" : "��ɽѩƮ",
	"damage_type" : "����"
])
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }
int valid_combine(string combo) { return combo=="zhentian-quan"; }

int valid_learn(object me)
{
	mapping fam  = me->query("family");
	if (fam["family_name"] != "������" || fam["generation"] > 4)
		return notify_fail("���������Ĵ����ϵ��ӷ�����ϰ��\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������Ʊ�����֡�\n");
	if ( me->query_skill("xuantian-wuji", 1) < 120)
		return notify_fail("��������޼�����򲻹����޷��������ơ�\n");
	if(me->query("gender") != "Ů��"){
		if ( me->query_skill("zhentian-quan", 1) < 80 && !me->query_skill("kunlun-zhang", 1))
			return notify_fail("�������ȭ���ڰ�ʮ�����޷��������ơ�\n");
	}
	else {
		if ( me->query_skill("chuanyun-tui", 1) < 80 && !me->query_skill("kunlun-zhang", 1))
			return notify_fail("��Ĵ�����С�ڰ�ʮ�����޷��������ơ�\n");
	}
	if ( me->query("max_neili") < 800)
		return notify_fail("���������Ϊ�������޷��������ơ�\n");
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
	level = (int) me->query_skill("kunlun-zhang",1);

	for(i = sizeof(action); i > 0; i--) 
	{
		if(level > action[i-1]["lvl"])
		{
			j = NewRandom(i, 20, level/5);
			//����ȭ
			if (me->query_temp("klz/luoyan"))
			{
				return ([
					"action": HIC+action[j]["action"]+NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 + random(500),
					"damage": 180 + random(100),
					"dodge": random(30)-10,
					"parry": random(20),
				]);

			}
			if( me->query_temp("diezhang1") ) 
			{
				me->delete_temp("diezhang1");
				return ([
					"action": HIR"$N˫��ƽƽ�Ƴ������ƻ���֮����������������ʵ�ھ�ǰ����̣�����ɱ�У�"NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 + random(500),
					"dodge": random(30)-10,
					"parry": random(20),
				]);
			}
			else if( me->query_temp("diezhang2") > 0 ) {
				return ([
					"action": YEL+action[j]["action"]+NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 +random(350),
					"dodge": random(30),
					"parry": random(10),
				]);
			} else
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 200 +random(350),
				"dodge": random(30)-10,
				"parry": random(20),
			]);

		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("kunlun-zhang", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 50)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("������������������ơ�\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"kunlun-zhang/" + action;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	if (!me->query_temp("weapon")) return;
	
	if( victim->query("qi") < 0 ) return;

	if( me->query_temp("diezhang2") > 1
		&&!random(3) )
	{
		me->add_temp("diezhang2", -1);
		message_vision(HIW"$N�ۼ�$n���⣬һ�е���������������һ�еݳ�!\n"NOR,me,victim);

		COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(2)?1:3);
	}
	if (me->query_temp("klz/hongsha")
		&&!random(3))
	{
		message_vision(HBRED+HIW"$N�����������Ƴ�һ���������ֵĺ�ɰ�ƶ�������$n!\n"NOR,me,victim);
		victim->apply_condition("hot_poison",2+random(3));
	}
	//��ɰ����Ч

	if (me->query_temp("klz/hongsha")
		&& random(me->query_skill("kunlun-zhang", 1)) > 100
		&& me->query("neili") > 1000
		&& random(me->query_skill("poison",1)) > 120
		&& random(10)>5
		&& random(me->query("neili")) > victim->query("neili")/2)
	{

		
			switch(random(5))
			{
				case 0:
					message_vision(BLU"$N����������Ϊ��ɫ�����ڹ������£�һ���������ֵġ�"HIG"�߶�"BLU"������������$n����������\n"NOR,me,victim);
					victim->add_condition("snake_poison", 1);
					break;
				case 1:
					message_vision(MAG"$N�������£�һ�ɻ�ɫ�ġ�"WHT"��򼶾"MAG"������˫������$n���澭������\n"NOR,me,victim);
					victim->add_condition("wugong_poison", 1);
					break;
				case 2:
					message_vision(CYN"$N�����˹���һ��Ѫ��ɫ�ġ�"HIR"Ы�Ӷ�"CYN"��˳����������$n��������\n"NOR,me,victim);
					victim->add_condition("xiezi_poison", 1);
					break;
				case 3:
					message_vision(YEL"$N˫�ƱƳ�һ���������ġ�"HIB"֩�붾"YEL"������$n�Ķ�����\n"NOR,me,victim);
					victim->add_condition("zhizhu_poison", 1);
					break;
				case 4:
					message_vision(WHT"$N���ƻ��������ͳ�һ�ɡ�"HIY"��ܶ�"WHT"����������$n����������\n"NOR,me,victim);
					victim->add_condition("hama_poison", 1);
					break;
			}
				   
	}
}
