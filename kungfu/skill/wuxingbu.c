//Cracked by Roath
// wuxingbu.c 
//kane

inherit SKILL;

mapping *action = ({
([	"action" : "$nһ�������ذδС������ϴ������ߣ��ܹ�$N������\n",
	"dodge"  : 10
]),
([	"action" : "$nһ�������ӷ��������һ���෭��������$N���������ơ�\n",
	"dodge"  : 20
]),
([	"action" : "$n���Ʋ��������ʹ�С���¿�������������һ�������$N�Ĺ�����\n",
	"dodge"  : 30
]),
});

mapping query_action(object me, object weapon)
{
	int zhaoshu, level;

	zhaoshu = sizeof(action);
	level   = (int) me->query_skill("wuxingbu");

	return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
	return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
{
	return 1;
}

string query_dodge_msg(string limb)
{
// The following codes are buggy, because "me" is the attacker instead
// of defender.
/*
	object me, ob;
	mapping action;

	me = this_player();
	action = query_action(me, ob);

	return action["action"];
*/
        return action[random(sizeof(action))]["action"];
}

int practice_skill(object me)
{

	return notify_fail("�㲻�������β���\n");
}
