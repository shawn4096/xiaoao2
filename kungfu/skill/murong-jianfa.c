#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N�����ָ��һʽ��ϴ����������˫�ź�����������������$wһ�Σ�ֱ��$n$l",
	"lvl" : 0,
	"damage_type" : "����"
]),
([
	"action" : "$N̤ǰ������������$w������Σ������ʵ������ʹһʽ�������������ֱ��$n��$l",
	"lvl" : 30,
	"damage_type" : "����"
]),
([
	"action" : "$Nһ�С����������$w��������׵Ľ������м��л����ֱ����$n��ȫ���Ѩ",
	"lvl" : 60,
	"damage_type" : "����"
]),
([
	"action" : "$N�����ڣ�����ָ��$n��������һ�С�����Ī��������������ǧ��һ�㣬��ɨ$n��$l",
	"lvl" : 90,
	"damage_type" : "����"
]),
([
	"action" : "$N˫����أ�ʹ�����Ϸɣ�����ֱ��$n��һ�С��ﻢ���¡��������й���ƽ��$n��$l",
	"lvl" : 120,
	"damage_type" : "����"
]),
([
	"action" : "$N��Цһ������$w�������У�һ�С���ש���񡹣�����һ��ѩ���Ľ��⣬����һ�����磬ֱ��$n��ȥ",
	"lvl" : 150,
	"damage_type" : "����"
]),
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
	if ((int)me->query_skill("shenyuan-gong", 1) < 20)
		return notify_fail("�����Ԫ�����̫ǳ��\n");
	if ((int)me->query_skill("parry", 1) < 10)
		return notify_fail("��Ļ����мܻ��̫ǳ��\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, j, level;
	level   = (int) me->query_skill("murong-jianfa",1);    
    if( me->query_temp("qixing1") > 0)
       {
              return ([
                        "action" : HIW"��תһ����"WHT"��"HIY"������"WHT"��\n\n"HIG"ֻ��$N����֮����һ������ֱ����$n��"HIC"������Ѩ��"  NOR,
                        "force" : 500 ,
                        "dodge": 0,
                        "damage": 200 ,
                        "parry": 0 ,
                        "weapon" : "����",
                        "damage_type" : "����",
                     ]);
            } 
         
             if( me->query_temp("qixing2") > 0)
             {
              return ([
                        "action" : HIM"�Ƕ��ּ���"WHT"��"HIY"��ѣ��"WHT"��\n\n"HIG"ֻ��$N�����ٶ�����ֱ����$n�ļ�ͷ��$nֻ������һʹ���漴"HIC"���羮Ѩ��"HIG"����һ����Ҵ�ʹ"  NOR,
                        "force" : 500 ,
                        "dodge": 0,
                        "damage": 250 ,
                        "parry": 0 ,
                        "weapon" : "����",
                        "damage_type" : "����",
                     ]);
             } 
         
             if( me->query_temp("qixing3") > 0)
             {
              return ([
                        "action" : MAG"ת�Ǽ�����"WHT"��"HIY"�����"WHT"��\n\n"HIG"ֻ��$N�������ϣ������ֳ�����Ȼ�������ܵĴ���$n����ף�$nֻ����΢һʹ���漴"HIC"��ӿȪѨ��"HIG"����һ�������ʹ"  NOR,
                        "force" : 500 ,
                        "dodge": 0,
                        "damage": 300 ,
                        "parry": 0 ,
                        "weapon" : "����",
                        "damage_type" : "����",
                     ]);
             }          
             if( me->query_temp("qixing4") > 0)
             {
              return ([
                        "action" : YEL"��ת�Ķ���"WHT"��"HIY"��Ȩ��"WHT"��\n\n"HIG"ֻ��$N�������ǣ���ֱ����$n�����壬$nֻ�����ϱ�һ���Ҵ̣��漴�е�"HIC"��������Ѩ��"HIG"����һ�������ʹ\n"  NOR,
                        "force" : 500 ,
                        "dodge": 0,
                        "damage": 350 ,
                        "parry": 0 ,
                        "weapon" : "����",
                        "damage_type" : "����",
                     ]);
             } 
             if( me->query_temp("qixing5") > 0)
             {
              return ([
                        "action" : HIB"�������У�"WHT"��"HIY"�����"WHT"��\n\n"HIG"ֻ��$N����ƫ�棬��ֱ����$n�����࣬$nֻ������һ�����漴"HIC"������Ѩ��"HIG"��Ȼ���Ѫ��"  NOR,
                        "force" : 500 ,
                        "dodge": 0,
                        "damage": 400 ,
                        "parry": 0 ,
                        "weapon" : "����",
                        "damage_type" : "����",
                     ]);
             } 
             if( me->query_temp("qixing6") > 0)
             {
              return ([
                        "action" : RED"�Ǿ�������"WHT"��"HIY"������"WHT"��\n\n"HIG"ֻ��$N�������ϣ����϶��´���$n��ͷ����$nͻȻ����ȫ�������������漴��Ѩ"HIC"���ٻ�Ѩ��"HIG"��Ȼ��ʹ�ޱ�"  NOR,
                        "force" : 500 ,
                        "dodge": 0,
                        "damage": 450 ,
                        "parry": 0 ,
                        "weapon" : "����",
                        "damage_type" : "����",
                     ]);
             } 
             if( me->query_temp("qixing7") > 0)
             {
              return ([
                        "action" : HIR"��ת���ƣ�"WHT"��"HIY"ҥ����"WHT"��\n\n"HIG"ֻ��$N������������������������$n�������㣬�ཫ$n�ĵ�һ��Ѩ"HIC"��̫��Ѩ��"HIG"��������Ѫ��"  NOR,
                        "force" : 500 ,
                        "dodge": 0,
                        "damage": 500 ,
                        "parry": 0 ,
                        "weapon" : "����",
                        "damage_type" : "����",
                     ]);
          }    


	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/4);
			if (me->query_temp("mrjf/lianhuan") > 0) {
				return ([
					"action" : HIC+replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIC)+NOR,
					"force" : 200 +random(100),
					"dodge": random(35),
					"parry": random(35),
					"damage" : 120 + random(100),
					"damage_type" : "����",
				]);
			}
			if (me->query_temp("qixing") > 0) {
				return ([
					"action" : HIB+replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIB)+NOR,
					"force" : 200 +random(100),
					"dodge": random(35),
					"parry": random(35),
					"damage" : 100 + random(80),
					"damage_type" : "����",
				]);
			}
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force": 150 +random(300),
				"dodge": random(30),
				"parry": random(30),
				"damage": 50 +random(50),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("murong-jianfa", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;
	if ((int)me->query("jingli") < 40)
		return notify_fail("�������������Ľ�ݽ�����\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("�������������Ľ�ݽ�����\n");
	me->receive_damage("jingli", 30);
	me->receive_damage("neili", 10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"murong-jianfa/" + action;
}

void lianhuan(object me, object victim)
{
	object weapon;
	/*int lh;
	if (me->query_temp("lianhuan"))
     	lh=3;
	else lh=1;*/
	
	if (!me || !victim || !me->is_fighting(victim))
		return;
	weapon = me->query_temp("weapon");
	if(me->query_temp("mrjf/lianhuan")
		&& !me->query_temp("lianhuan_hit")
		&& me->query_skill_prepared("finger") == "canhe-zhi"
		&& me->query_skill_mapped("finger") == "canhe-zhi"
		&& objectp(weapon))
	{
		me->set_temp("lianhuan_hit", 1);
		weapon->unequip();
		if (me->query("shenyuan/super")&&me->is_fighting(victim))
		{   
			//me->add_temp("apply/damage",me->query_skill("canhe-zhi",1)/2);
		    me->add_temp("apply/finger",me->query_skill("canhe-zhi",1)/2);
			me->add_temp("apply/attack",me->query_skill("canhe-zhi",1)/2);
			COMBAT_D->do_attack(me, victim, 0, userp(me)?3:1);
			//me->add_temp("apply/damage",-me->query_skill("canhe-zhi",1)/2);
		    me->add_temp("apply/finger",-me->query_skill("canhe-zhi",1)/2);
			me->add_temp("apply/attack",-me->query_skill("canhe-zhi",1)/2);
		}
		else 
			COMBAT_D->do_attack(me, victim, 0, 1);
		weapon->wield();
		me->add("neili", -30);
		me->delete_temp("lianhuan_hit");
	}
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	string *limbs,buwei;
	int damage;
	limbs=victim->query("limbs");
	buwei=limbs[random(sizeof(limbs))]; 
	//��������
	damage=me->query_skill("murong-jianfa",1)+me->query_skill("shenyuan-gong",1)+me->query_skill("douzhuan-xingyi",1);
	damage=damage*2+random(damage);
	if(me->query_temp("mrjf/lianhuan"))
		call_out((: lianhuan :), 1, me, victim);
	//�������������ǣ����
	if (me->query_temp("shenyuan")&&me->query_temp("mrjf/liuxu")&&objectp(victim)&&random(10)>7)
	{
		message_vision(WHT"$N���л��䣬ʩչ���������������ľ��⣬��ƮƮ��û�����죬��$n����ʤ����\n"NOR,me,victim);
		if (random(me->query_skill("murong-jianfa",1))>victim->query_skill("parry",1)/2)
		{
			message_vision(WHT"$nһ��С��Ϊ���С���������������"+HIR+buwei+WHT",��ʱ��Ѫֱ����\n"NOR,me,victim);
			victim->add_busy(1);
			victim->receive_damage("qi",damage,me);
		}
	}

}
