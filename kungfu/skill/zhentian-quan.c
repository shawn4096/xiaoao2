//����ȭ
//cool 981010
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N��һ��������΢��������һ����һ�С����°��졹��һȭֱͱ$n��$l",
	"lvl" : 0,
	"skill_name" : "���°���",
	"damage_type" : "����"
]),
([
	"action" : "$N��������һЦ����ȭ�������ϣ���ȭƽƽ������һ�С��������졹���������$n",
	"lvl" : 20,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([
	"action" : "$N��$nһ����ȣ�ʹһ�С����羭�졹����ȭ�������漴��ȭ���ϣ�������������$n��$l",
	"lvl" : 40,
	"skill_name" : "���羭��",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ����һ�����졹��һ�����һȭ��մ����ȭ��ֱ��$n��$l",
	"lvl" : 60,
	"skill_name" : "һ������",
	"damage_type" : "����"
]),
([
	"action" : "$Nһ����Х��˫ȭ���������һ�С�ʯ���쾪����ȭ���ܲ�$n��ǰ������",
	"lvl" : 80,
	"skill_name" : "ʯ���쾪",
	"damage_type" : "����"
]),
([
	"action" : "$N˫ȭ�������Ī�⣬һ�С���粻������ǰ�����ң�˲Ϣ֮����$n����������һʮ��ȭ",
	"lvl" : 100,
	"skill_name" : "��粻��",
	"damage_type" : "����",
]),
([
	"action" : "$Nһ����Х������һȭ��һ�С�ɽ��·ת��������ת׾��ȴ��ȥ����죬��$n��$l�ͻ���ȥ",
	"lvl" : 120,
	"skill_name" : "ɽ��·ת",
	"damage_type" : "����"
]),
([
	"action" : "$N˫ȭ�����������ޣ�һ�С������޷졹������$n��$l",
	"lvl" : 140,
	"skill_name" : "�����޷�",
        "damage_type" : "����"
]),
([
	"action" : "$Nһ��"HIC"����ɽ�Ϻӡ�"NOR"������һȭ���������ƽ���������ȭ��һ����˫������������$n��$l",
	"lvl" : 160,
	"skill_name" : "��ɽ�Ϻ�",
	"damage_type" : "����"
]),
([
	"action" : "$N�ƺ�һ����˫ȭ���Ϸֿ���һ��"HIR"���ٻ����졹"NOR"��ȭ�����ߣ�����ͬʱ����$n��$l",
	"lvl" : 180,
	"skill_name" : "�ٻ�����",
	"damage_type" : "����"
]),
([
	"action" : "$Nŭ��һ������շ���һʽ"HIY"��������ѡ�"NOR"��˫ȭ�Ӹ����£����봷��$n",
	"lvl" : 200,
	"skill_name" : "�������",
	"damage_type" : "����"
]),
([
	"action" : "$N�����Ц������������۷��裬һ��"HIG"���޷����졹"NOR"��ȭ����������������$n��ȥ",
	"lvl" : 220,
	"skill_name" : "�޷�����",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }
int valid_combine(string combo) { return combo=="kunlun-zhang"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��������ȭ��������֡�\n");
	if ((int)me->query_skill("xuantian-wuji", 1) < 25)
		return notify_fail("��ġ������޼�������򲻹����޷�ѧ������ȭ����\n");
	if ((int)me->query("max_neili") < 50)
		return notify_fail("�������̫�����޷���������ȭ����\n");
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
	if( me->query_skill("cuff", 1) >= 220 
	 && me->query_skill("zhentian-quan", 1) >= 220 
	 && me->query_skill("strike",1) >= 220
	 && me->query_skill("kunlun-zhang",1) >= 220
	 && me->query("neili") >= 500
	 && me->query_skill_mapped("strike")  == "kunlun-zhang"
	 && me->query_skill_mapped("cuff") == "zhentian-quan"
	 && random(5)==1) {
		return ([
			"action": HIW"$N������ʽͻȻ�ӿ죬һ��"HIR"��ȭ��˫����"HIW"���������سɴ磬ȭ��������ջ������漴˫��������������$n"NOR,
			"parry": 15+random(15),
			"dodge": 20+random(20),
			"force": 250+random(350),
			"damage_type": "����"
		]);
	}
	level   = (int) me->query_skill("zhentian-quan",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 200 +random(150),
				"dodge": random(10),
				"parry": random(30),
			]);
		}
	}
}

mixed hit_ob(object me, object target, int damage_bonus)
{
	int lvl,qi;

	lvl = (int)me->query_skill("zhentian-quan", 1);
	qi =(int)target->query("qi");

	if( me->query_skill_prepared("cuff") != "zhentian-quan" )
		return 0;

	if(  random(lvl) > 100 && random(10)==1) {
		message_vision(HIR"$N��öԷ�������ͻȻ����һ��������Ϊȭ��ʹ��һ����ȭ���˾���$n�ļ���ϻ�����\n"NOR,me,target);
		message_vision(HIR"$n��Ͼ������ֻ���ü��һ���飬��Ѫ���裬�κ���ʽ���޷�ʹ����\n"NOR,me,target);
            target->apply_condition("no_perform", 1);
            target->receive_damage("qi", qi/5);
            target->receive_wound("qi", qi/5);
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("zhentian-quan", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 30)
		return notify_fail("��ľ���̫���ˡ�\n");
	if ( me->query("neili") < 10)
		return notify_fail("�������������������ȭ����\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -5);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"zhentian-quan/" + action;
}
