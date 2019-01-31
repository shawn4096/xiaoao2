// lingshe-bianfa ���߱޷�

#include <ansi.h>

inherit SKILL;
#include <skill.h>


mapping *action = ({
([     "action":   "$N���β�����һ�С��������项������$wֱ��$n��˫Ŀ��ȥ",
       "dodge":        10,
       "parry":        20,
       "damage":       20,
       "force":        80,
       "lvl" : 0,
       "skill_name" : "��������",
       "damage_type":  "����"
]),
([     "action":   "$Nһ�С��������������$w��Ӱ���Σ���$n�ľ�����ȥ",
       "dodge":     15,
       "parry":     20,
       "damage":    30,
       "force":     100,
       "lvl" : 20,
       "skill_name" : "��������",
       "damage_type":  "����"
]),
([     "action":   "$NͻȻ������ˣ���$n�Ƚ�ʱ������һ�С�������β��������$w������֮����ֱ��$n��ǰ�ض�ȥ",
       "dodge":     10,
       "parry":     12,
       "damage":    50,
       "force":     120,
       "lvl" : 40,
       "skill_name" : "������β",
       "damage_type":  "����"
]),
([     "action":   "$N�͵�һ��������$w��������Բ����һ�С�������������Ȧ��$n������",
       "dodge":     12,
       "parry":     20,
       "damage":    60,
       "force":     140,
       "lvl" : 60,
       "skill_name" : "��������",
       "damage_type":  "����"
]),
([     "action":  "$N���ΰ���������ң�һ�С������·���������$w�γ�������Ӱ����$nӭͷ����",
       "dodge":    15,
       "parry":    20,
       "damage":   80,
       "force":    160,
       "lvl" : 80,
       "skill_name" : "�����·�",
       "damage_type":  "����"
]),
([     "action":  "$N���ؾ͵�һ����һ�С����������������$w��Ѹ�ײ����ڶ�֮��ɨ��$n��˫��",
       "dodge":    20,
       "parry":    20,
       "damage":   80,
       "force":    180,
       "lvl" : 100,
       "skill_name" : "�������",
       "damage_type":  "����"
]),
([     "action": "$N���η��ͣ�һ�С������鳲��������$w����������Ӱ����׼$n������ȥ",
       "dodge":   20,
       "parry":   30,
       "damage":   90,
       "force":   200,
       "lvl" : 120,
       "skill_name" : "�����鳲",
       "damage_type":  "����"
]),
([     "action": "$N�͵ض�ֱ���е�$w��һ�С�����������������$n�ĽŸ�ֱ�ö��ϣ�ֱ��$n��ͷ����ȥ",
       "dodge":   25,
       "parry":   30,
       "damage":  90,
       "force":   210,
       "lvl" : 120,
       "skill_name" : "��������",
       "damage_type":  "����"
])
});
int valid_enable(string usage)
{ 
	if (this_player()->query("family/family_name")!="������"&&this_player()->query("gender")!="Ů��" ) 
        return notify_fail("��������̵��ӣ��޷�ʹ�á�\n");
    if ( (int)this_player()->query_skill("dulong-dafa", 1)< 20|| (int)this_player()->query_skill("qusheshu", 1)< 20)
		return notify_fail("��Ķ����󷨻����������̫ǳ������20�����޷�ʹ�á�\n");
	else return (usage == "whip") || (usage == "parry"); 
}

int valid_learn(object me)
{
       object weapon;

       if( (int)me->query("max_neili") < 100 )
               return notify_fail("����������㣬û�а취�����߱޷�, ����Щ���������ɡ�\n");
	   if (me->query_skill("dulong-dafa",1)<20)
       	   if ((int)me->query_skill("hamagong", 1) < 20)
               return notify_fail("��Ķ����󷨻��󡹦���̫ǳ������80����\n");
       if ( !objectp(weapon = me->query_temp("weapon"))
			|| ( string)weapon->query("skill_type") != "whip" )
               return notify_fail("���������һ�����Ӳ������޷���\n");
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
        level=(int) me->query_skill("lingshe-bianfa",1);      
		if (me->query_temp("lsbf/sandou"))
		{						
			return ([
				 "action" :BLU + replace_string(replace_string(action[random(sizeof(action))]["action"], "$w", "$W"), "$W", "$w"BLU)+NOR,
				 "dodge":   25,
				 "parry":   30,
				 "damage":  190,
				 "force":   210,
				 "lvl" : 120,
			//"skill_name" : action,
				 "damage_type":  "����",
			]);						
		}       

		for(i = sizeof(action); i > 0; i--)			
			if(level > action[i-1]["lvl"]) 
				return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       object weapon;

       if (!objectp(weapon = me->query_temp("weapon"))
			|| (string)weapon->query("skill_type") != "whip")
               return notify_fail("��ʹ�õ��������ԡ�\n");
       if (me->query_skill("dulong-dafa",1)<20)
       	   //if ((int)me->query_skill("hamagong", 1) < 80)
               return notify_fail("��Ķ����󷨻��󡹦���̫ǳ������80����\n");
       if ((int)me->query("jingli") < 50)
               return notify_fail("����������������߱޷���\n");
       me->receive_damage("jingli", 15);
       return 1;
}

string perform_action_file(string action)
{
       return __DIR__"lingshe-bianfa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	string msg;
	int lvl= me->query_skill("lingshe-bianfa", 1);
	int j = (lvl - 100) / 5 + 1;
	if ( j > 10 ) j = 10;

	if (random(10)<6) return;
	
	if(random(me->query_skill("lingshe-bianfa", 1)) > 200
		&& me->query("neili") > 1000
		&& me->query_skill("poison",1) > 100
        && random(me->query("neili")) > victim->query("neili")/2){
           // if(victim->query("neili")/3 < me->query("neili"))
			message_vision(BLU"$N��Ӱ�Ӷ�����ž���죬���ڹ������£�һ���������ֵġ�"HIW"�߶�"BLU"������������$n���澭������\n"NOR,me,victim);
			victim->add_condition("snake_poison", 1);
	}
	   
}
