inherit SKILL;
#include <ansi.h>

mapping *action = ({
([      "action" : "$N˫����Σ��ҽ�Ϊ֧�㣬����͵ط���һʽ�����š���Ѹ����磬����$n��$l",
        "force" : 80,
        "attack": 10,
        "dodge" : 15,
        "parry" : 15,
        "damage": 100,
        "lvl"   : 0,
        "damage_type" : "����",
        "skill_name"  : "����"
]),
([      "action" : "$N��Ŷٵأ�����һ�㣬������ת���ҽ�һʽ������ɽ����������ϣ�����$n��$l",
        "force" : 100,
        "attack": 20,
        "dodge" : 20,
        "parry" : 20,
        "damage": 115,
        "lvl"   : 30,
        "damage_type" : "����",
        "skill_name"  : "����ɽ"
]),
([      "action" : "$N����ҽŻ������ҽŷ�һ���߳���������׼��һʽ��ӥ׷���������$n",
        "force" : 140,
        "attack": 30,
        "dodge" : 25,
        "parry" : 25,
        "damage": 128,
        "lvl"   : 60,
        "damage_type" : "����",
        "skill_name"  : "ӥ׷"
]),
([      "action" : "$N˫������Ȧת��һʽ��ԧ��š�������糾������$n��ȫ��",
        "force" : 160,
        "attack": 35,
        "dodge" : 30,
        "parry" : 30,
        "damage": 120,
        "lvl"   : 90,
        "damage_type" : "����",
        "skill_name"  : "ԧ���"
]),
([      "action" : "$N˫�Ž�������һʽ�������ȡ����ŽŲ���$n����������",
        "force" : 180,
        "attack": 35,
        "dodge" : 40,
        "parry" : 40,
        "damage": 135,
        "lvl"   : 120,
        "damage_type" : "����",
        "skill_name"  : "������"
]),
([      "action" : "$N�ֺ���ԧ��ͷ�Ϲڣ��������ԧ������β���Ƚų����������ۣ��ߵ��Ļ����º�һ��һʽ���������¡����ŽŲ���$n����",
        "force" : 180,
        "attack": 35,
        "dodge" : 40,
        "parry" : 40,
        "damage": 145,
        "lvl"   : 120,
        "damage_type" : "����",
        "skill_name"  : "��������"
]),
([      "action" : "$N���һ��Ƴ�˫��ż��ǡ��ԧ����Ӱ���棬һʽ����Ӱ���롹����Ӱ����Ϯ��$nǰ������",
        "force" : 180,
        "attack": 35,
        "dodge" : 40,
        "parry" : 40,
        "damage": 150,
        "lvl"   : 120,
        "damage_type" : "����",
        "skill_name"  : "��Ӱ����"
]),

});

int valid_enable(string usage) { return usage=="leg" ||  usage=="parry"; } 

int valid_combine(string combo) 
{
		if (this_player()->query("quest/qz/combine/pass"))
			return combo == "haotian-zhang";
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("��ԧ�������ȱ�����֡�\n");

        if ((int)me->query_skill("force",1) < 20)
                return notify_fail("����ڹ���򲻹����޷�ѧԧ�������ȡ�\n");
        if (me->query("family/family_name")!="ȫ���")
                return notify_fail("ԧ����������ȫ������������޷�ѧԧ�������ȡ�\n");

        if ((int)me->query_skill("leg", 1) < 20)
                return notify_fail("��Ļ����ȷ���򲻹����޷�ѧԧ�������ȡ�\n");

        if ((int)me->query_skill("leg", 1) < (int)me->query_skill("yuanyang-lianhuantui", 1))
                return notify_fail("��Ļ����ȷ�ˮƽ���ޣ��޷����������ԧ�������ȡ�\n");

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
        int i, j,level,adjust;
        level = (int)me->query_skill("yuanyang-lianhuantui", 1);
		adjust=level;
       
		for(i = sizeof(action); i > 0; i--)
            if(level > action[i-1]["lvl"])
			{
              j = NewRandom(i, 20, level/5);
               //����
			   if (me->query_perform() == "ԧ��������")
			   {
                       return ([  
                        "action" : HIC+action[j]["action"]+NOR,
                        "force" : action[j]["force"] + adjust,
                        "dodge" : action[j]["dodge"] + adjust,
                        "damage" : action[j]["damage"] + adjust,
                        "damage_type" : action[j]["damage_type"],
                        ]);
			   }
//ԧ���
				if (me->query_temp("yylht/yuan"))
			   {
                       return ([  
                        "action" : HIR+action[j]["action"]+NOR,
                        "force" : action[j]["force"] + adjust,
                        "dodge" : action[j]["dodge"] + adjust,
                        "damage" : action[j]["damage"] + adjust/2,
                        "damage_type" : action[j]["damage_type"],
                        ]);
			   }
			   if (me->query_temp("yylht/yang"))
			   {
                       return ([  
                        "action" : HIW+action[j]["action"]+NOR,
                        "force" : action[j]["force"] + adjust,
                        "dodge" : action[j]["dodge"] + adjust,
                        "damage" : action[j]["damage"] + adjust/2,
                        "damage_type" : action[j]["damage_type"],
                        ]);
			   }
               else {
                        return ([  
                        "action" : action[j]["action"],
                        "force" : action[j]["force"],
                        "dodge" : action[j]["dodge"] + adjust/2,
                        "damage" : action[j]["damage"],
                        "damage_type" : action[j]["damage_type"],
                        ]);
			   }
            }
}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 100)
               return notify_fail("�������̫���ˡ�\n");

        if ((int)me->query("neili") < 80)
               return notify_fail("�������������ԧ�������ȡ�\n");

        me->receive_damage("jingli", 80);
        //me->add("neili", -0);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yuanyang-lianhuantui/" + action;
}
