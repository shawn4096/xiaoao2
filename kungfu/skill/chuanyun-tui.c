// �����ȷ�
//written by cool
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N���Ӽ�ת���ҽ����������һʽ������Ϊ�Ρ�����ɨ$n������",
	"damage_type" : "����",
	"lvl" : 0,
	"skill_name" : "����Ϊ��"
]),
([
	"action" : "$N�����߳��������������£��ҽŽ���������߳���һʽ��׷����硹��˫���Ⱥ�����$n��$l",
	"damage_type" : "����",
	"lvl" : 15,
	"skill_name" : "׷�����"
]),
([
	"action" : "$Nһʽ�����Ҵ���������ź��ߣ��漴����ǰ���䲽���ҽ�Ѹ�ٷ�������$n��$l",
        "damage_type" : "����",
	"lvl" : 30,
	"skill_name" : "���Ҵ���"
]),
([
	"action" : "$NͻȻһ���󷭣�һʽ�����߱�������˫�Ȼζ�����$n��$l��ȥ",
        "damage_type" : "����",
	"lvl" : 45,
	"skill_name" : "���߱���"
]),
([
	"action" : "$Nʹһʽ�����Ʋ��¡����εض���˫�������߳�������$n���ؿ�",
        "damage_type" : "����",
	"lvl" : 60,
	"skill_name" : "���Ʋ���"
]),
([
	"action" : "$N������������һʽ����ɨ���ݡ������Ⱥ�ɨ$n��$l",
	"damage_type" : "����",
	"lvl" : 75,
	"skill_name" : "��ɨ����"
]),
([
	"action" : "$N˫������һ�С������Ƶ�����һ������$n���ţ���һ��ȴ��ɨ$nС��",
	"lvl" : 90,
	"skill_name" : "�����Ƶ�",
	"damage_type" : "����"
]),
([
	"action" : "$N����һ�ƣ���ǰ����$n��ͷ����һʽ����Ӱ���١�������ͻȻ����$n��$l",
	"damage_type" : "����",
	"lvl" : 105,
	"skill_name" : "��Ӱ����"
]),
([
	"action" : "$N�ȷ缤����˫�ȴ��䣬���������޷���һ��"HIR"�������ɽ��"NOR"������$n��$l",
	"lvl" : 120,
	"skill_name" : "�����ɽ",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹһʽ"HIY"���������¡�"NOR"��������ն���˫��������ֻ��������Ӱ������$n",
	"damage_type" : "����",
	"lvl" : 135,
	"skill_name" : "��������"
]),
([
	"action" : "$N˫���뻮�����Ž��²������ǣ�һ��"HIW"�������ء�"NOR"��һ����ɽ�����Ľ�����ֱ��$n����",
	"lvl" : 150,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([
	"action" : "$NͻȻ�������ת��һ��"HIW"����ɽѩƮ��"NOR"����Ӱ���裬��ʱ֮�佫$n����˷����׹�ס",
	"lvl" : 180,
	"skill_name" : "��ɽѩƮ",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="leg" ||  usage=="parry"; }
int valid_combine(string combo) { return combo=="sanyin-shou"; }


int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������ȱ�����֡�\n");
	if ((int)me->query_skill("xuantian-wuji", 1) < 20)
		return notify_fail("��������޼�����򲻹����޷�ѧ�����ȡ�\n");
	if ((int)me->query("max_neili") < 50)
		return notify_fail("�������̫�����޷��������ȡ�\n");
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
	level = (int)me->query_skill("chuanyun-tui", 1);
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 100 +random(350),
				"dodge": 20+random(20),
				"parry": random(10),
			]);
		}
	}
}

mixed hit_ob(object me, object target, int damage_bonus)
{
	int lvl,qi;

	lvl = (int)me->query_skill("chuanyun-tui", 1);
	qi =(int)target->query("qi");

	if( me->query_skill_prepared("leg") != "chuanyun-tui" )
		return 0;

	if(  random(lvl) > 200 && random(10)==1) {
		message_vision(HIR"$N��öԷ�������ͻȻ����һ�����˾�ʹ��һ�ǲ��ߣ���$n���ؿڻ�����\n"NOR,me,target);
		message_vision(HIR"$n�ܴ��ػ�����ʱֻ�����ؿ�һ���飬�������裬�����������ˡ�\n"NOR,me,target);
            target->apply_condition("no_exert", 1);
            target->receive_damage("qi", qi/2,me);
            target->receive_wound("qi", qi/5,me);
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("chuanyun-tui", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 30)
		return notify_fail("�������̫���ˡ�\n");
	if ( me->query("neili") < 10)
		return notify_fail("������������������ȡ�\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -5);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"chuanyun-tui/" + action;
}
