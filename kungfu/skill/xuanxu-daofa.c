#include <ansi.h>
inherit SKILL;

mapping *action = ({
([     "action" : "$N����б��������Ծ������,һ�С�����չ�᡹�����е�$w��$n��$l������ȥ",
       "force" : 150,
        "dodge" : -10,
        "parry" : 5,
       "damage": 30,
       "lvl" : 0,
       "skill_name" : "����չ��",
       "damage_type" : "����"
]),
([     "action" : "$Nһ�С����ɽ�ڡ�������$w��$n�����̻�ȥ����δʹ�ϣ�����ֱ��$n��$l",
       "force" : 180,
        "dodge" : -10,
        "parry" : 10,
       "damage": 50,
       "lvl" : 20,
       "skill_name" : "���ɽ��",
       "damage_type" : "����"
]),
([     "action" : "$Nб������������$n��࣬һ�С��鵶��ˮ��,$w��������ƽƽ��ɨ$n��ǰ��",
       "force" : 220,
        "dodge" : -15,
        "parry" : 15,
       "damage": 70,
       "lvl" : 40,
       "skill_name" : "�鵶��ˮ",
       "damage_type" : "����",
]),
([     "action" : "$Nһ�С����Ƽ��ա������е�$w��$n�鿳һ�������к���ת��$n��$l��ȥ",
       "force" : 280,
        "dodge" : -10,
        "parry" : 10,
       "damage": 75,
       "lvl" : 60,
       "skill_name" : "���Ƽ���",
       "damage_type" : "����"
]),
([     "action" : "$N���浶���������Ծ��һ�С���ӥ���¡���ֱ��$n�Ҽ磬��ͽ���涵�˸���Բ������ͻ��,б��$n��$l",
       "force" : 320,
        "dodge" : -10,
        "parry" : 5,
       "damage": 90,
       "lvl" : 80,
       "skill_name" : "��ӥ����",
       "damage_type" : "����"
]),
([     "action" : "$N��Ȼ���з���һ�С������ѩ�������е�$w���������⣬��$n��$l��ȥ",
       "force" : 400,
        "dodge" : -10,
        "parry" : -5,
       "damage": 120,
       "lvl" : 100,
       "skill_name" : "�����ѩ",
       "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }


int valid_learn(object me)
{
       if ((int)me->query("max_neili") < 50)
               return notify_fail("�������������ϰ���鵶����\n");
       if ((int)me->query_skill("yinyun-ziqi", 1) < 20)
               return notify_fail("������������̫ǳ��\n");
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
		string msg;
        level   = (int) me->query_skill("xuanxu-daofa",1);
        if (me->query_temp("xxd/xuanxu")&&random(10)>8)
        {
			msg=HIW"$N���е������䣬��˸�����������ɸ����ᣬʩչ�������־������ƣ�\n"NOR;
			if (!random(2)) {

				return ([
					"action": msg,
					"dodge":  random(30),
					"parry":  random(30),
					"damage": 150 + random(100),
					"force":  300+random(200),
					"damage_type": "����"
				]);
			}else {
				me->add_temp("apply/blade",me->query_skill("xuanxu-daofa",1)/4);
				return ([
					"action": HIR"$N���е������䣬�󿪴�ϣ����������գ�ʩչ�������־������ƣ�\n"NOR,
					"dodge":  random(30),
					"parry":  random(30),
					"damage": 250 + random(100),
					"force":  300+random(200),
					"damage_type": "����"
				]);
				me->add_temp("apply/blade",-me->query_skill("xuanxu-daofa",1)/4);

			}

        }
		for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       object weapon;

       if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "blade")
               return notify_fail("��ʹ�õ��������ԡ�\n");
       if ((int)me->query("jingli") < 20)
               return notify_fail("����������������鵶����\n");
       me->receive_damage("jingli", 20);
       me->add("neili", -10);
       return 1;
}

mixed hit_ob(object me, object target, int damage_bonus)
{
        string msg;
		int i,j;
		object weapon;
		i=me->query_skill("xuanxu-daofa",1);
		j=me->query_skill("zhenshan-mianzhang",1);
		weapon=me->query_temp("weapon");
        if (random(me->query_str(1))>target->query_con(1)/2
		&& me->query_skill("xuanxu-daofa",1)>150
		&& me->query_skill_mapped("strike")=="zhenshan-mianzhang"
		&& me->query_skill_prepared("strike")=="zhenshan-mianzhang"
		&& !random(4)
		)   {
              msg = HIC"$N�����������֣����һ�У�����$n��ע�⣬���ֺ�Ȼʩչ������ɽ���ơ��е����ƹ���\n"NOR;
			  if (random(me->query_skill("strike",1)) > target->query_skill("parry",1)/2) {
                  msg += HIR"$nΪ$N�����ᾢ�����ˣ��Ŀ�һ���ʹ�������̲�ס����һ����Ѫ��\n"NOR;
			      
                  weapon->unequip(); 
				  target->start_busy(1+random(2));
				  target->receive_damage("qi",i+j*2,me);
				  target->receive_wound("qi",j/2,me);
                  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);  
				  weapon->wield();
			  }    
			   else {
                  msg += HIR"$nʶ����$N����ͼ�����һ�������˿�ȥ��\n"NOR;
				  me->add_busy(1+random(1));
				  }
              message_vision(msg, me, target);
        }
        return 1;
        
}


string perform_action_file(string action)
{
        return __DIR__"xuanxu-daofa/" + action;
}

