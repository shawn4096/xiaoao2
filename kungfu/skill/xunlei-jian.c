//xunlei-jian.c by jpei

inherit SKILL;
#include <ansi.h>
#include <combat.h>


string *msg = ({
"$N��Ȼ����һ��������$wէȻһ�֣�һʽ���������ס������쾢����ˮ��й�ذ����$n",
"$N�ɲ���ǰ��һ�С����ײ�������$w������ͣ��������$nҪ��������磬������ŷ�",
"$Nб��һ����һ�С��׷�㡹���������ԣ����������֮�У����������޾��������仯",
"$N$wб�ߣ�������㣬����ʹһ�С���ˮ�⡹��$w����ֻ����һ�������Ѵ̵���$n��$l",
"$N����΢�࣬�Ѵ�$n�����ƹ�������һ˲֮�䣬��$p��$lն��һ�����ַ���죬����һ�С���������",
"$N����һ�С�������á����潣�ߣ�������ε���$n���ᣬ�Ų�δ���������ȵ���$w��������$p$l��ȥ",
"������â���£�$Nһ�С������׳�������д󿪴�ϣ��������ϣ�����֮������˪��������������",
"$Nһ�С�����������������$w���级�籼�ף��Ƴ�һ������Ľ��⣬���ն��",
"$Nһ�С��׷����롹��$w�����߿��裬���������ϣ���ʵ��ã����Ტ��",
"$N����һ�Σ��������ɣ�һ�С������桹�� ��������$w�Ѵ���$n��$l��������������",
"����$N���δ�����ȥ��һ�С��׵���¡��������ݺᷴ����������¡¡�����಻��",
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������������\n");
	if ((int)me->query_skill("xuantian-wuji", 1) < 30)
		return notify_fail("��������޼������̫ǳ��\n");

	if ( me->query("family/family_name") != "������" )
		return notify_fail("ֻ�����ص��Ӳ���ѧϰѸ�׽�����\n");

	if ((int)me->query_skill("sword", 1) < 20)
		return notify_fail("��Ļ����������̫ǳ��\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, j, level, damage;

	level = me->query_skill("xunlei-jian", 1);
	i = random(me->query_skill("sword"))+50;
	if( i<100 ) i = 100;
	j = random(40)-5;
	damage = (random(2)+4)*35;
	if( damage < 50 ) damage =50;

		if( level > 350 ) {
			return ([
            "action": HIB+replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$w"), "$w", "$w"HIB)+NOR,
            "damage": 160 + random(100),
		    "damage_type": "����",
			"dodge":  random(20),
			"parry":  random(20),
			"force":  300 + random(250),

			]);
		}

		else return ([
			"action": msg[random(sizeof(msg))],
            "damage": 120 + random(80),
			"damage_type": "����",
			"dodge":  random(30),
			"force":  250 + random(300),
		]);
	}
int practice_skill(object me)
{
	if ( me->query_skill("xunlei-jian", 1 ) < 120)
		return notify_fail("Ѹ��ʮ�Ž�ֻ��ͨ����ʦ��ѧϰ����ߡ�\n");

	if ( me->query("jingli") < 50)
		return notify_fail("�������������Ѹ�׽���\n");
	if ( me->query("neili") < 20)
		return notify_fail("�������������ϰѸ�׽���\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xunlei-jian/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	object weapon, weapon1;
	int i;
	weapon = me->query_temp("weapon");
	weapon1= victim->query_temp("weapon");

	if( !objectp(weapon) ) return;

	i = me->query_skill("xunlei-jian", 1);

	if( weapon1 && random( i ) > 350 && living(victim)
	  && me->query_skill_mapped("parry") == "xunlei-jian"
	  && random(me->query("combat_exp")) > victim->query("combat_exp")/2 )
	{
     
	  message_vision(HIY"$N�ȵ�����С���ˣ���һ�����ˡ��ָ��ѿڣ����ֽ���һ�٣�������ʯ�⣬ֻ�����˵�һ�����죬\n"
						+"$N���ý�����ס��$n����"+weapon1->name()+HIY"��\n"NOR, me,victim);
      if( random(me->query_int()) > victim->query_int()/3 && me->query_skill_mapped("force") == "xuantian-wuji" )
	  {
		  me->add("neili", -50);
          victim->add_busy(2+random(2));
		  message_vision(HIM"$n�޷������мܣ�������������"+weapon->name()+HIM"�����Լ��ʺ�ֻ��Ʋ��"+weapon1->name()+HIM"���͵�һ��������������һ�С�\n"NOR,me,victim);
		  weapon1->unequip();
		  weapon1->move(environment(victim));
	   }
	   else {
		  message_vision(HIM"$n���µ�ת����������һ�������Ⱪ����$N�ɿ����ʣ�ֻ�ó�����ˣ�\n"NOR, me,victim);
          me->start_perform(2,"�����ʶ���С�");
					//me->add_busy(1);
	   }
	}
     
}

