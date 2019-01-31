// wudu-bian �嶾�� �嶾�̾���

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
int valid_enable(string usage) { 
	if (this_player()->query("gender")=="Ů��")
	{
		return (usage == "whip") || (usage == "parry"); 
	}
}
int valid_learn(object me)
{
       object weapon;

       if( (int)me->query("max_neili") < 100 )
               return notify_fail("����������㣬û�а취���嶾��, ����Щ���������ɡ�\n");
       if (me->query("family/family_name")!="�������")
               return notify_fail("���������̵��ӣ����������к������ϡ�\n");
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
		string str;
		if (!me) return;
		level=(int) me->query_skill("wudu-bian",1);      

		weapon=me->query_temp("weapon");

		if(me->query_temp("wdb/wudu"))
		{
			switch(me->query_temp("wdb/wudu"))
			{
				case 4: str = HIB"$N���е�"+weapon->query("name")+HIB"�����嶾�ޡ���һ��������ʽ��"HIG"��������"HIC"��š��һ�ɣ�״����ǹ������$n���ʺ�"NOR; break;
				case 3: str = HIC"$N���Ӻ�Ȼ�׷���˫�ŷ�����״���󡣬һʽ��"HIY"�����"HIC"����$nʹ���������嶾�ޡ����϶�������$n"NOR; break;
				case 2: str = HIY"$N����ת��˫���������裬ǧ��ǧ��֮״���ԡ��嶾�ޡ���"HIR"�ٱ����"HIY"����ʽ˦������β�ζ�������$n������"NOR; break;
				case 1: str = HIG"$N�������Һ�Ȼ���ټ��ۣ�˦�����еĳ��ޣ����嶾�޷��С�"HIC"֩����˿"HIG"������ʽ˳�ƶ���"NOR; break;
				default: str = HIR"$Nת���ܣ���$n���β���������"HIY"Ы˦β"HIR"��������"+weapon->query("name")+HIR"��Ȼ�ӿ��·ɳ�������$N�����ಿλ"NOR; break;
			}
			me->add_temp("wdb/wudu", -1);
			return ([
				"action":str,
				"damage": 200 + random(50),
				"damage_type": "����",
				"dodge": random(30),
				"parry": random(30),
				"force": 250 + random(250),
			]);
		}

/*
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
		}   */     

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
      // if ((int)me->query_skill("tianmo-dafa", 1) < 30)
        //       return notify_fail("��Ķ����󷨻��̫ǳ��\n");
       if ((int)me->query("jingli") < 50)
               return notify_fail("��������������嶾�ޡ�\n");
       me->receive_damage("jingli", 15);
       return 1;
}

string perform_action_file(string action)
{
       return __DIR__"wudu-bian/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	string msg;
	object weapon;
	int lvl= me->query_skill("wudu-bian", 1);
	weapon=me->query_temp("weapon");

	if (random(10)<6) return;

	if (!weapon||weapon->query("skill_type")!="whip") return;
	
	

	if(random(me->query_skill("wudu-bian", 1)) > 100
		&& me->query("neili") > 1000
		&& me->query_skill("poison",1) > 100
        && random(me->query("neili")) > victim->query("neili")/3)
	{
           // if(victim->query("neili")/3 < me->query("neili"))
			switch(random(5))
			{
				case 0:
					message_vision(BLU"$N��Ӱ�Ӷ�����ž���죬���ڹ������£�һ���������ֵġ�"HIG"�߶�"BLU"������������$n���澭������\n"NOR,me,victim);
					victim->add_condition("snake_poison", 1);
					break;
				case 1:
					message_vision(MAG"$N�������£�һ�ɻ�ɫ�ġ�"WHT"��򼶾"MAG"��˳��"+weapon->query("name")+MAG"����$n���澭������\n"NOR,me,victim);
					victim->add_condition("wugong_poison", 1);
					break;
				case 2:
					message_vision(CYN"$N�����˹���һ��Ѫ��ɫ�ġ�"HIR"Ы�Ӷ�"CYN"��˳��"+weapon->query("name")+CYN"����$n��������\n"NOR,me,victim);
					victim->add_condition("xiezi_poison", 1);
					break;
				case 3:
					message_vision(YEL"$N˳��һ�飬һ���������ġ�"HIB"֩�붾"YEL"��˳��"+weapon->query("name")+YEL"����$n���澭������\n"NOR,me,victim);
					victim->add_condition("zhizhu_poison", 1);
					break;
				case 4:
					message_vision(WHT"$N���޳ɻ������ͳ�һ�ɡ�"HIY"��ܶ�"WHT"��˳��"+weapon->query("name")+WHT"����$n���澭������\n"NOR,me,victim);
					victim->add_condition("hama_poison", 1);
					break;
			}
			
	}
	   
}
