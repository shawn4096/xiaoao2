//cre by sohu@xojh 2014/9
//chilian.c �������ƾ���
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([	"action" : "$Nһ�С�б����·�������Ƶ�������֮�ϣ�����$n",
	"force" : 80,
        "attack": 2,
	"dodge" : 30,
        "parry" : 1,
	"damage": 5,
	"lvl"   : 0,
	"skill_name" : "б����·",
	"damage_type" : "����"
]),
([	"action" : "$Nһ�С�ǧɽ��ɾ�������ɫ���أ�˫����ƮƮ������$n",
	"force" : 100,
        "attack": 8,
	"dodge" : 25,
        "parry" : 3,
	"damage": 30,
	"lvl"   : 20,
	"skill_name" : "ǧɽ��ɾ�",
	"damage_type" : "����"
]),
([	"action" : "$Nһ�С�������������˫�ƻû�һƬ��Ӱ����$n�������ڡ�",
	"force" : 130,
        "attack": 12,
	"dodge" : 43,
        "parry" : 4,
	"damage": 35,
	"lvl"   : 30,
	"skill_name" : "��������",
	"damage_type" : "����"
]),

([	"action" : "$Nһ�С���ˮǧɽ������$n��$l��������",
	"force" : 150,
        "attack": 15,
	"dodge" : 55,
        "parry" : 8,
	"damage": 50,
	"lvl"   : 40,
	"skill_name" : "��ˮǧɽ",
        "damage_type" : "����"
]),
([	"action" : "$Nһ�С��������𡹣�ֻ��һƬ��Ӱ����$n",
	"force" : 180,
        "attack": 22,
	"dodge" : 52,
        "parry" : 0,
	"damage": 30,
	"lvl"   : 60,
	"skill_name" : "��������",
	"damage_type" : "����"
]),

([	"action" : "$N˫��ƽ�ӣ�һ�С�����ն��������$n",
	"force" : 230,
        "attack": 23,
	"dodge" : 65,
        "parry" : 11,
	"damage": 90,
	"lvl"   : 80,
	"skill_name" : "����ն��",
        "damage_type" : "����"
]),
([	"action" : "$Nһ�С��������¡���ֻ��һƬ��Ӱ����$n",
	"force" : 260,
        "attack": 28,
	"dodge" : 63,
        "parry" : 5,
	"damage": 100,
	"lvl"   : 100,
	"skill_name" : "��������",
	"damage_type" : "����"
]),

([	"action" : "$Nʩ������ɽ��ˮ�������ֺ�ɨ$n��$l�����ֹ���$n���ؿ�",
	"force" : 280,
        "attack": 25,
	"dodge" : 77,
	"damage": 120,
        "parry" : 12,
	"lvl"   : 120,
	"skill_name" : "��ɽ��ˮ",
        "damage_type" : "����"
]),
([	"action" : "$N������Σ�����һ�ǡ�Ϧ�����¡�����$n��ͷ��",
	"force" : 320,
        "attack": 31,
	"dodge" : 80,
        "parry" : 15,
	"damage": 150,
	"lvl"   : 140,
	"skill_name" : "Ϧ������",
        "damage_type" : "����"
]),
([	"action" : "$Nʩ�����嶾���塹��˫��ͬʱ����$n��$l",
	"force" : 360,
        "attack": 32,
	"dodge" : 81,
        "parry" : 10,
	"damage": 180,
	"lvl"   : 160,
	"skill_name" : "�嶾����",
        "damage_type" : "����"
])
});

int valid_enable(string usage)
{
	return usage == "parry" || usage == "strike";
}

int valid_learn(object me)
{
    /*if (me->query("character") != "�ĺ�����") 
                return notify_fail("���嶾���Ʊ���Ҫ�ĺ��������ҿ���������û�������\n"); */
	if (!me->query("quest/gumu/wdsz/pass") ) 
               return notify_fail("���嶾���Ʊ���Ҫ��Ī�������ָ�㡣\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���嶾���Ʊ�����֡�\n");

        if ((int)me->query_skill("force",1) < 150)
                return notify_fail("����ڹ���򲻹����޷����嶾���ơ�\n");

	if ((int)me->query("max_neili") < 1200)
		return notify_fail("�������̫�����޷����嶾���ơ�\n");

        if ((int)me->query_skill("strike", 1) < 120)
                return notify_fail("��Ļ����Ʒ���򲻹����޷����嶾���ơ�\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("wudu-shenzhang", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷�����������嶾���ơ�\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	string msg;
	level = (int) me->query_skill("wudu-shenzhang",1);
	//���
	if ( me->query_temp("wdsz/duoci")) 
	{
				switch(me->query_temp("wdsz/duoci"))
				{
					
					case 2: msg = HIR"$N���������һת������$n�������˳���ĳ�����һ�п���ƽ�ͣ�ʵ���ں�һ�ɺ������ȳ��ޱ�"NOR; break;
					case 1: msg = HIW"���$N��һ������˫���������ţ���������һ�Ƽ��գ�ͬʱһ���������ֵ��ȳ���Ϣ����"NOR; break;
					default : msg = HIB"$NͻȻ����һ�Σ��۽�$n������һ����������$p����б�Ķ�ȥ"NOR; break;
				}
				me->add_temp("wdsz/duoci", -1);
				return ([
					"action": msg,
					"force": 250 + random(350),
					"parry": random(20)+10,
					"dodge": random(20)+10,
					"damage": 100 + random(100),
					"damage_type": "����"
				]);
	}
	//������
	if ( me->query_temp("wdsz/chilian")) 
	{
				switch(me->query_temp("wdsz/chilian"))
				{
					case 3: msg = HIB"$NͻȻ�������貨�������۽�$n��࣬����������һ����������$p����ֱ�Ķ���"NOR; break;
					case 2: msg = HIR"$N���������һת������$n�������˳���ĳ�����һ�п���ƽ�ͣ�ʵ���ں�һ�ɺ������ȳ��ޱ�"NOR; break;
					case 1: msg = HIW"���$N��һ������˫���������ţ���������һ�Ƽ��գ�ͬʱһ���������ֵ��ȳ���Ϣ����"NOR; break;
					default : msg = HIB"$NͻȻ����һ�Σ��۽�$n������һ����������$p����б�Ķ�ȥ"NOR; break;
				}
				me->add_temp("wdsz/chilian", -1);
				return ([
					"action": msg,
					"force": 250 + random(350),
					"parry": random(20)+10,
					"dodge": random(20)+10,
					"damage": 150 + random(100),
					"damage_type": "����"
				]);
	}
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) {
			
			
			return action[NewRandom(i, 20, level/5)];

		}
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int poison, i;

	poison = (me->query_skill("poison", 1) - victim->query_skill("poison", 1))/3;
	poison += me->query_skill("wudu-shenzhang",1)/15;

	if ( userp(victim)) {
		poison /= 3;
		i = 120;
	}
	else
		i = 50;


	if(me->query_skill("wudu-shenzhang", 1) > 150
	&& me->query_skill("poison", 1) > 50
	&& random(me->query_skill("poison", 1)) > random( victim->query_skill("medicine", 1))
	&& victim->query_condition("snake_poison") < 200
	&& me->query("neili") > 500
	&& random(10)>6
	&& !victim->query("job_npc")) {
		if (me->query("env/�嶾����") == "�嶾") {
			poison += random(poison/2);
			me->add("neili",-100-random(50));
			me->add("jingli",-20-random(30));
			message_vision(BLU"$N��������һ�ߣ��������Գ����ּ���ҫ�۵���ɫ��\n"NOR, me);
		}
		victim->add_condition("snake_poison", poison);
		message_vision(BLU"$N��С��Ϊ�嶾���ƶ����ˣ�����һ�Σ����Ϻ���������\n"NOR, victim);
		if (victim->query_condition("snake_poison") > 180)
			message_vision(HBRED"$N���ڻ����������������Σ�գ�\n"NOR, victim);
		if (userp(me)
		 && userp(victim)
		 && !victim->query_temp("kill_other/"+me->query("id"))
		 && !me->query_temp("other_kill/"+victim->query("id"))
		 && ! me->query_temp("revenge/"+victim->query("id"))
		 && !victim->query_condition("killer")
               && (!me->query_temp("special_die") || !victim->query_temp("special_die")))
			me->add_condition("killer", 5);
	}
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 50)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("��������������嶾���ơ�\n");

	me->receive_damage("jingli", 30+random(20));
	if (me->query("neili")>13)
	{
		me->add("neili", -13);
	}
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"wudu-shenzhang/" + action;
}
