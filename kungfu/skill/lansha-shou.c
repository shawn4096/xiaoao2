// lansha-shou.c ��ɰ�� Ѫ����
// Edit By sohu@xojh

#include <ansi.h>
inherit SKILL;
string *du=({
"ice_poison",
"ill_dongshang",
"ill_fashao",
"ill_kesou",
"ill_shanghan",
"ill_zhongshu",
"cold_poison",
"flower_poison",
"rose_poison",
"sanpoison",
"chilian_poison",
"wugong_poison",
"zhizhu_poison",
"xiezi_poison",
"chanchu_poison",
});
mapping *action = ({
([      "action" : "$N��ǰһ����˫�ƶ�Ȼ����������˿˿�������$n��$l",
        "force" : 100,
        "attack": 25,
        "dodge" : 15,
        "parry" : 20,
        "damage": 110,
        "damage_type" : "����"
]),
([      "action" : "$N���ƻ��أ��������Ĵ��ż���֮������$n��$l",
        "force" : 130,
        "attack": 30,
        "dodge" : 10,
        "parry" : 15,
        "damage": 120,
        "damage_type" : "����"
]),
([      "action" : "$N˫���ĳ��������磬��Ȼ����������Ϣ������$n��$l",
        "force" : 180,
        "attack": 50,
        "dodge" : 20,
        "parry" : 30,
        "damage": 130,
        "damage_type" : "����"
]),
([      "action" : "$N�ֽ�һ��������һԾ�����ƿ�����������$n��$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 135,
        "damage_type" : "����"
]),
([      "action" : "$N��Цһ����˫��һ�������ƺ�Ȼ�������߻���$n��$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 235,
        "damage_type" : "����"
]),
([      "action" : "$N���μ��Σ�һԾ����$n��ǰ�����ƴ��ų��캮������$n��$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 135,
        "damage_type" : "����"
]),
([      "action" : "$N���쳤Х��˫���Ʒ���ǧ�Ų����ĺ���������$n��$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 135,
        "damage_type" : "����"
]),
([      "action" : "$N������Ȼһ�䣬��Ӱǧ����ã���$n�޷�����",
        "force" : 250,
        "attack": 45,
        "dodge" : 15,
        "parry" : 20,
        "damage": 125,
        "damage_type" : "����"
]),
([      "action" : "$N����һ����Х��˫��Я������ű���ֱֱ����$n",
        "force" : 330,
        "attack": 35,
        "dodge" : 25,
        "parry" : 20,
        "damage": 115,
        "damage_type" : "����"
])
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"|| usage == "throwing"; }

int valid_combine(string combo) { return combo == "hongsha-zhang"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����ɰ�ֱ�����֡�\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹����޷���ϰ��ɰ�֡�\n");

        if ((int)me->query("max_neili") < 800)
                return notify_fail("�������̫�����޷���ϰ��ɰ�֡�\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("lansha-shou", 1))
                return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷������������ɰ�֡�\n");
        if (me->query_skill("xuedao-jing", 1) < 50 )
                return notify_fail("��ı����ڹ�ˮƽ���ޣ��޷������������ɰ�֡�\n");
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
        int i, level;
        level   = (int) me->query_skill("lansha-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 50)
                return notify_fail("�������̫���ˡ�\n");

        if ((int)me->query("neili") < 70)
                return notify_fail("���������������ɰ�֡�\n");

        me->receive_damage("qi", 40);
        me->add("neili", -60);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{

	int level, jiali, time,level2;
	object weapon;

        int lvl;
        int flvl;
	int damage,damage2;
	object target;

        level = (int) me->query_skill("lansha-shou",1);
        level2= (int) me->query_skill("lansha-shou",1);

	if (me->query_skill("poison",1)<100) return;

	if (random(10)>7 
		&& level>=150 
		&& me->query_skill_mapped("force") == "xuedao-jing" )
	{
            victim->receive_damage("qi",random(level)+10,me);
            victim->receive_wound("qi",15 + random(50),me);
            victim->apply_condition(du[random(sizeof(du))], 25);
            victim->apply_condition(du[random(sizeof(du))], 25);
            victim->apply_condition(du[random(sizeof(du))], 25);
            victim->apply_condition(du[random(sizeof(du))], 25);
            victim->apply_condition(du[random(sizeof(du))], 25);
            victim->apply_condition(du[random(sizeof(du))], 25);
			if (!victim->is_busy()) victim->start_busy(2);	
			return HIB "$N" HIB "ͻȻ���ƣ�Ȼ��Ѹ�ٷ���! ���о�Ȼ�ж�ɰ�����Ʒ羡Ȼ��������֮ɫ��\n" HIB "$n" HIB "��Ȼ�е�һ��Ī���Ķ��ģ�ȫ��̱������Ƥ���ϡ�!\n"NOR;
	}


}

string perform_action_file(string action)
{
        return __DIR__"lansha-shou/" + action;
}
