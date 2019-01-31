// murong-daofa.c Ľ�ݵ���

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$NͻȻ���һ�������С���һ�С�"HIY"����ǵ���׳־"NOR"�����������϶�����$n��$lնȥ",
	"lvl" : 0,
	"skill_name" : "����ǵ���׳־",
	"damage_type" : "����"
]),
([
	"action" : "$N���λ���һ�С�"HIR"�䵶��ת��Ǭ��"NOR"��������$w�ڿ��м��ٻγ������⻷������$n��$l",
	"lvl" : 30,
	"skill_name" : "�䵶��ת��Ǭ��",
	"damage_type" : "����"
]),
([
	"action" : "$N��һ����һ�С�"HIG"ң����ǧ��ѩ"NOR"��, $w�Ӳ���˼��ķ����$n�ľ���նȥ",
	"lvl" : 70,
	"skill_name" : "ң����ǧ��ѩ",
	"damage_type" : "����",
]),
([
	"action" : "$N����ӯ�ޱȣ�һ�С�"HIM"׳־����������"NOR"�����������⻯����㷱�ǣ���$n��$l��ȥ",
	"lvl" : 100,
	"skill_name" : "׳־����������",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query("max_neili") < 50)
		return notify_fail("�������������\n");
	if ((int)me->query_skill("shenyuan-gong", 1) < 10)
		return notify_fail("�����Ԫ�����̫ǳ��\n");
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
	int i, j, level;
	string msg;
	level = (int) me->query_skill("murong-daofa",1);

	for(i = sizeof(action); i > 0; i--) {
		if(level >= action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			if( me->query_temp("mrdf/liandao"))
			{
				
				switch (me->query_temp("mrdf/liandao"))
				{
					case 7:msg=HIY"$N���������һƬ��Ӱ����$nȦס��Ȼ���Ȼ�򶫿�һ����ʩչ�����������µĽ�ħ������ʽ"NOR;break;
					case 6:msg=HIC"$N��Ȼ����������һ����ʩչ�����ǹ�����ɽ�����Ϻ��Ĳ�ʮ��·"NOR;break;
					case 5:msg=HIG"���$N��Ȼ��ת������һ�����𣬺������磬�ֱ����˽���ʷ�ҵġ��ط��������"NOR;break;
					case 4:msg=CYN"������$N����ʹһʮһ��������һʮһ���ɱ�ĵ������������£���һ��ͬ"NOR;break;
					case 3:msg=YEL"$N����ƮȻ��ת��˳�ַ�ת��������$n��ͷ����һ�ǣ�����������ͯ���Ĺ��Ϻ��������ġ��ȱ�����ֻ�Ƶж���ɱ��"NOR;break;
					case 2:msg=HIR"$N�õ�����$n���У����ǽ�����������ܵе��������ǡ���ɽ�����С�֮һ�����ǳ����󿳵���������$Nȴ�Ķ����ڵ���"NOR;break;
					case 1:msg=MAG"$N��ʽ������ȴ��Ȼ�����ɽ���$n��ȥ����ͼ��$n��һ���������������Ļ��˵ĵ��Ⱦ���"NOR;break;				
				}
				me->add_temp("mrdf/liandao", -1); 
				return ([
					"action":msg,
					"damage": 150+random(50),
					"damage_type": "����",
					"dodge": random(35),
					"parry": random(35),
					"force": 350+random(150),
				]);
			}

			if ( me->query_temp("mr_daoying")){
				return ([
					"action":CYN+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"CYN), NOR, CYN)+NOR,
					"damage": 100+random(50),
					"damage_type": "����",
					"dodge": random(35),
					"parry": random(35),
					"force": 200+random(300),
				]);
			}
			
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" :"����",
				"force": 40 +random(40),
				"dodge": random(30),
				"parry": random(30),
				"damage": 60 +random(50),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("murong-daofa", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 40)
		return notify_fail("�������������Ľ�ݵ�����\n");
	if ( me->query("neili") < 20)
		return notify_fail("�������������Ľ�ݵ�����\n");
	me->receive_damage("jingli", 30);
	me->add("neili",-10);
	return 1;
}
	   
string perform_action_file(string action)
{
	return __DIR__"murong-daofa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int weapon,tweapon,skill;
	weapon=me->query_temp("weapon");
	tweapon=victim->query_temp("weapon");
	skill=me->query_skill("murong-daofa",1);
	if (!weapon) return;
	
	if (me->query_temp("mrdf/yusui")
		&& random(10)>2)
	{
		switch (random(4))
		{
			case 0:
				message_vision(HIW"$N������˸��һƬ�貣�$n��ʱ�о���ǰһƬ��㱣�\n"NOR,me,victim);
				victim->add_busy(1);
				break;
			case 1:
				message_vision(RED"$N������һ��ת�����õ����ڻ���˳����$n����һ����\n"NOR,me,victim);
				victim->receive_damage("qi",1500+random(2000),me);
				//victim->receive_wound("qi",500+random(1000),me);
				me->add("neili",-100);
				break;
			case 2:
				message_vision(YEL"$N�����е�"+weapon->query("name")+YEL"���һ����������$n���ڵ��У�\n"NOR,me,victim);
				message_vision(YEL"$n�����ͻ��ʼ�հ��Ѳ���$N�ĵ������֣�һʧ��֮�䣬�۰�����һ����\n"NOR,me,victim);

				//victim->receive_damage("qi",1000+random(2000),me);
				victim->receive_wound("qi",1000+random(1000),me);
				me->add("neili",-100);
				break;
			case 3:
				if (!tweapon) break;
				
				message_vision(HIG"$nֻ�����е�"+tweapon->query("name")+HIG"Ϊ$N�ֳ�"+weapon->query("name")+HIG"���û�������������\n"NOR,me,victim);

				if (random(me->query_str(1))>victim->query_str(1)/2
					&& random(me->query_skill("blade",1))>victim->query_skill("parry",1)/2)
				{
					message_vision(HIY"$nֻ��һ�ɴ�������������"+tweapon->query("name")+HIY"�·��Լ�˦��ȥ�Ƶ÷��˳�ȥ��\n"NOR,me,victim);
					tweapon->move(environment(victim));
				}
				break;		
		}
	}
	//��Ӱ��
		if (me->query_temp("mr_daoying")&&random(10)>6)
		{
			if(objectp(victim) && me->is_fighting(victim))
			{
                weapon->unequip(); 
				message_vision(HIC"$N����"+weapon->query("name")+HIC"���һƬ���⣬��Ȼ�ӵ�������$n�ĳ�һ�ƣ�\n"NOR,me,victim);
				me->add_temp("apply/strike",skill/4);
				me->add_temp("apply/damage",skill/5);
                COMBAT_D->do_attack(me,victim, me->query_temp("weapon"),userp(me)?3:1);
				me->add_temp("apply/strike",-skill/4);
				me->add_temp("apply/damage",-skill/5);
				weapon->wield();
			}

		}
}
