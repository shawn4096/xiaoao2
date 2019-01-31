//tianyu-qijian.c
// Write By Zhuifeng's System on 2010-7-20 17:39:23
// ��Ҳ���ո����֡��޸��·�Ծ���� jpei 2010-7-30



#include <ansi.h>
inherit SKILL;
#include <combat.h>
#include <combat_msg.h>


string *feiyue_msg = ({
""HIC"$Nʹһʽ��"+HIC+"����һ��"+HIC+"��������$w"+HIC+"����΢�񣬻ó�һ���������$n��$l��"NOR"",
""HIC"$N����ǰ��ʹ����"+RED+"���羪��"+HIC+"��������$w"+HIC+"����һ����������$n��$l"NOR"",
""HIC"$N����$w"+HIC+"һ����һ�С�"+GRN+"���ھ���"+HIC+"����ббһ�������ó�������$n��$l"NOR"",
""HIC"$N���н����ॳ���һ����һʽ��"+BLU+"�������"+HIC+"����һ���������$n��$l"NOR"",
""HIC"$Nһʽ��"+MAG+"ŭ����"+HIC+"��������$w"+HIC+"�������������ʹ$n�Ѷ���ʵ���޿ɶ��"NOR"",
""HIC"$N����$w"+HIC+"бָ���죬��â���£�һʽ��"+BLU+"�Ż�����"+NOR+"������׼$n��$lбб����"NOR"",
""HIC"$Nһʽ��"+WHT+"�����ѩ"+HIC+"�������󼱶�������������⣬����$n��$l"NOR"",
""HIC"$Nһʽ��"+HIR+"��ӵ�к"+HIC+"����$w"+HIC+"��ն�������缲�������$n���ؿ�"NOR"",
""HIC"$Nһʽ��"+HIY+"�������"+HIC+"����$w"+HIC+"ͻȻ���������һƬ���Χ��$nȫ��"NOR"",
});





mapping *action = ({

([
     "action" : "$Nʹһʽ��"+HIC+"����һ��"+NOR+"��������$w����΢�񣬻ó�һ���������$n��$l",
     "force": 200 + random(220),
     "dodge"  : 40,
     "parry"  : 30,
     "lvl"    : 1,
     "damage"    : 80 + random(140),
     "skill_name"  : "����һ��",
     "damage_type" : "����"
]),
([
     "action" : "$N����ǰ��ʹ����"+RED+"���羪��"+NOR+"��������$w����һ����������$n��$l",
     "force": 200 + random(220),
     "dodge"  : 40,
     "parry"  : 30,
     "lvl"    : 20,
     "damage"    : 80 + random(140),
     "skill_name"  : "���羪��",
     "damage_type" : "����"
]),
([
     "action" : "$N����$wһ����һ�С�"+GRN+"���ھ���"+NOR+"����ббһ�������ó�������$n��$l",
     "force": 200 + random(220),
     "dodge"  : 40,
     "parry"  : 20,
     "lvl"    : 30,
     "damage"    : 80 + random(140),
     "skill_name"  : "���ھ���",
     "damage_type" : "����"
]),
([
     "action" : "$N���н����ॳ���һ����һʽ��"+BLU+"�������"+NOR+"����һ���������$n��$l",
     "force": 200 + random(220),
     "dodge"  : 40,
     "parry"  : 20,
     "lvl"    : 40,
     "damage"    : 80 + random(140),
     "skill_name"  : "�������",
     "damage_type" : "����"
]),
([
     "action" : "$Nһʽ��"+MAG+"ŭ����"+NOR+"��������$w�������������ʹ$n�Ѷ���ʵ���޿ɶ��",
     "force": 200 + random(220),
     "dodge"  : 40,
     "parry"  : 30,
     "lvl"    : 60,
     "damage"    : 120 +random(140),
     "skill_name"  : "ŭ����",
     "damage_type" : "����"
]),
([
     "action" : "$N����$wбָ���죬��â���£�һʽ��"+BLU+"�Ż�����"+NOR+"������׼$n��$lбб����",
     "force": 200 + random(220),
     "dodge"  : 40,
     "parry"  : 30,
     "lvl"    : 70,
     "damage"    : 125 +random(140),
     "skill_name"  : "�Ż�����",
     "damage_type" : "����"
]),
([
     "action" : "$Nһʽ��"+WHT+"�����ѩ"+NOR+"�������󼱶�������������⣬����$n��$l",
     "force": 200 + random(220),
     "dodge"  : 40,
     "parry"  : 30,
     "lvl"    : 80,
     "damage"    : 150+random(140),
     "skill_name"  : "�����ѩ",
     "damage_type" : "����"
]),
([
     "action" : "$Nһʽ��"+HIR+"��ӵ�к"+NOR+"����$w��ն�������缲�������$n���ؿ�",
     "force": 200 + random(220),
     "dodge"  : 40,
     "parry"  : 30,
     "lvl"    : 90,
     "damage"    : 130+random(140),
     "skill_name"  : "��ӵ�к",
     "damage_type" : "����"
]),
([
     "action" : "$Nһʽ��"+HIY+"�������"+NOR+"����$wͻȻ���������һƬ���Χ��$nȫ��",
     "force": 200 + random(220),
     "dodge"  : 40,
     "parry"  : 30,
     "lvl"    : 100,
     "damage"    : 125+random(140),
     "skill_name"  : "�������",
     "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "parry" || usage == "sword"; }

int valid_learn(object me)
{
	object weapon;
	
	if (!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if (me->query("max_neili") < 100)
		return notify_fail("�������������\n");
	if ( ! me->query_skill("bahuang-gong", 1))
	if (me->query_skill("beiming-shengong", 1) < 50)
		return notify_fail("��İ˻�����Ψ�Ҷ�����̫ǳ��\n");
	return 1;
}

int practice_skill(object me)
{
       if ((int)me->query("jingli") < 40)
           return notify_fail("�������̫���ˡ�\n");
       if ((int)me->query("neili") < 50)
           return notify_fail("�������������ϰ�ü��ܡ�\n");
       me->receive_damage("jingli", 20);
       me->add("neili", -0);
       return 1;
}
string query_skill_name(int level)
{
   int i;
   for(i = sizeof(action); i > 0; i--)
       if(level >= action[i-1]["lvl"])
           return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
   int i, j, level;
   level   = (int) me->query_skill("tianyu-qijian",1);
   for(i = sizeof(action); i > 0; i--) {
       if(level > action[i-1]["lvl"]) {
           j = NewRandom(i, 20, level/4);
       if((int)me->query_skill("tianyu-qijian",1) >  450){
       return ([
               "action": HIC+feiyue_msg[random(sizeof(feiyue_msg))],
               "force" : 300 + random(300),
               "dodge": 50,
               "parry" : 30,
 
			   "damage" : 150+random(120),
		       "damage_type" : "����",
                ]);
       }
       else return action[j];
       }
   }
}

string perform_action_file(string action)
{
   return __DIR__"tianyu-qijian/" + action;
}

