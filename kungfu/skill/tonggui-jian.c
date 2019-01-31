#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N�ݲ���ǰ������$wбб�̳������Ʋ�Ҫ��һ�㣬��ն$n��ȥ",
        "force" : 290,
        "attack": 171,
        "parry" : -240,
        "dodge" : -231,
        "damage": 260,
        "damage_type" : "����"
]),
([      "action": "$N����$w�͵ķ����ݳ�������$n��$l����ʩȫΪƴ��������",
        "force" : 340,
        "attack": 152,
        "parry" : -241,
        "dodge" : -192,
        "damage": 232,
        "damage_type" : "����"
]),
([      "action": "$N�治¶ɫ�����ζ�Ȼ�ӿ죬����$wһ�����һ����������$n��ȥ",
        "force" : 320,
        "attack": 158,
        "parry" : -245,
        "dodge" : -183,
        "damage": 220,
        "damage_type" : "����"
]),
([      "action": "$N����$w��â��˸����������â�еݳ�ɱ�ţ���ȫ����$n����֮��",
        "force" : 390,
        "attack": 168,
        "parry" : -193,
        "dodge" : -175,
        "damage": 230,
        "damage_type" : "����"
]),
});

int valid_enable(string usage)
{
        return usage == "sword"||usage=="parry";
}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 1000)
                return notify_fail("���������Ϊ���㣬�޷�ѧϰͬ�齣����\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("����ڹ���򲻹����޷�ѧϰͬ�齣����\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("��Ľ�����Ϊ���㣬�޷�ѧϰͬ�齣����\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("tonggui-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������ͬ�齣����\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("tonggui-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;
        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 50)
                return notify_fail("�������������ͬ�齣����\n");

        if ((int)me->query("neili") < 70)
                return notify_fail("�������������ͬ�齣����\n");

        me->receive_damage("qi", 40);
        me->add("neili", -60);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tonggui-jian/" + action;
}

mixed hit_ob(object me, object victim, int damage)
{
		
		if (!me->query("quest/qz/tgj/pass")) return;
		
		if (random(10) > 7
			&&me->query_temp("tgj/tonggui")) 
        {
			switch (random(3))
			{
				case 0:
					message_vision(MAG"$N�Ӷ����г��������ܲ��ʣ����ӷ�����ȫ��������$n�����ƺ���Щ���ӣ�\n"NOR,me,victim);
					victim->receive_damage("jing",200+random(400),me);
					victim->receive_wound("jing",100+random(200),me);
					break;
				case 1:
					message_vision(HIY"$N״�������ȫ�ǽ�����ʽ�������·���$n��������һ��!\n"NOR,me,victim);
					victim->add_busy(1);
					victim->apply_condition("no_exert",1);
					break;
				case 2:
					message_vision(HIR"$N��Ȼ���˵��Ѵ���ƴ������˼����ʽ����Ϭ����\n"NOR,me,victim);
				    COMBAT_D->do_attack(me, victim, me->query_temp("weapon"),3);

					break;
			}
        	
        }

}