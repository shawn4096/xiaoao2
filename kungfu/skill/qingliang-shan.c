//������
//sohu@����������������ʽ
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action":"$N����ʩչ��һ�С��������ơ������е�$w������$n������Ѩ",
        "force" : 90,
        "attack": 15,
        "dodge" : -10,
        "parry" : 20,
        "damage": 25,
        "lvl"   : 0,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([      "action":"$N��������һ�С���÷ӳѩ����$w���������£���$n�׺�Ѩ��ȥ",
        "force" : 130,
        "attack": 30,
        "dodge" : -10,
        "parry" : 30,
        "damage": 30,
        "lvl"   : 40,
        "skill_name" : "��÷ӳѩ",
        "damage_type" : "����"
]),
([      "action":"$N��ǰ����һ�����������ս�⣬����$wʹ����׷����硹������$n�ĵز�Ѩ",
        "force" : 170,
        "attack": 40,
        "dodge" : 5,
        "parry" : 32,
        "damage": 35,
        "lvl"   : 60,
        "skill_name" : "׷�����",
        "damage_type" : "����"
]),
([      "action":"$N���е�$w������ҵ�һ�Σ�ʹ�����ɻ��ڴ���ź����������$n������Ѩ",
        "force" : 190,
        "attack": 50,
        "dodge" : 5,
        "parry" : 35,
        "damage": 40,
        "lvl"   : 80,
        "skill_name" : "�ɻ��ڴ�",
        "damage_type" : "����"
]),
([      "action":"$N����Ծ��һʽ������ӱޡ������������Ӱ��$w��$n�����ȥ",
        "force" : 240,
        "attack": 60,
        "dodge" : 10,
        "parry" : 45,
        "damage": 50,
        "lvl"   : 100,
        "skill_name" : "����ӱ�",
        "damage_type" : "����"
]),
([      "action":"$N�������У�$w�Ƴ�����ѩ���ʷ棬�ӳ�����̨�۾�����һ�ʿ���һ�ʵع���$n",
        "force" : 260,
        "attack": 65,
        "dodge" : 5,
        "parry" : 50,
        "damage": 60,
        "lvl"   : 120,
        "skill_name" : "��̨�۾�",
        "damage_type" : "����"
]),
([      "action":"$Nʹ��һ�С�Ⱥɽ��Ӱ��ͦ���й�ֱ�����ʼ��������;��Ȼת�����ϱ���޷�",
        "force" : 280,
        "attack": 70,
        "dodge" : 5,
        "parry" : 52,
        "damage": 75,
        "lvl"   : 140,
        "skill_name" : "Ⱥɽ��Ӱ",
        "damage_type" : "����"
]),
([      "action":"$N����б��һ�ʣ�һ�С����׾��ơ�����ź����ʷ磬��$n��Χ����",
        "force" : 310,
        "attack": 75,
        "dodge" : 5,
        "parry" : 64,
        "damage": 90,
        "lvl"   : 150,
        "skill_name" : "���׾���",
        "damage_type" : "����"
]),
});


int valid_enable(string usage)
{
	if (this_player()->query("quest/kl/qls/pass")&&this_player()->query("quest/kl/qls/baishi"))
	{
		return usage == "brush" ||usage == "blade" || usage == "parry";
	}
}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 500)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ����̫ǳ��\n");
		if (me->query("family/family_name")!="������")
                return notify_fail("������ص��ӣ��޷�ѧ������֧����۾��������ȡ�\n");
        if ((int)me->query_skill("brush", 1) < 30)
                return notify_fail("��Ļ����ʷ����̫ǳ������30����\n");
        if ((int)me->query_skill("blade", 1) < 30)
                return notify_fail("��Ļ����������̫ǳ������30����\n");
        if ((int)me->query_skill("brush", 1) < (int)me->query_skill("qingliang-shan", 1))
                return notify_fail("��Ļ����ʷ�ˮƽ���ޣ��޷���������������ȷ���\n");

    return 1;
}

string query_skill_name(int level)
{
        int i;

        for(i = sizeof(action) - 1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i,j, level;

        level = (int) me->query_skill("qingliang-shan", 1);
        //�������
		if (me->query_temp("qls/kuaida"))
        {
			for(i = sizeof(action); i > 0; i--) 
			{ 
				if(level >= action[i-1]["lvl"]) 
				{
					j = NewRandom(i, 20, level/5);
					return ([
						"action": HIW+replace_string(action[j]["action"],"$w","$w"HIW)+NOR,
						"lvl": action[j]["lvl"],
						"damage_type": action[j]["damage_type"],
						"force": 150 + random(300),
						"dodge": random(30),
						"parry": random(30),
						"damage": 170+ random(100),
					]);
				}
			}

        }
		for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "brush")
                return notify_fail("�����ֵ������޷���ϰ�����ȷ���\n");

        if ((int)me->query("qi") < 70)
                return notify_fail("������������������ȷ���\n");

        if ((int)me->query("neili") < 70)
                return notify_fail("������������������ȷ���\n");

        me->receive_damage("qi", 65,"�����߻���ħ");
        me->add("neili", -62);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qingliang-shan/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{                
    object weapon=me->query_temp("weapon");
	
	if (me->query_skill("force",1)<250)
        return;
	//�⿪����������Ϳ�����
	if (!me->query("quest/kl/qls/pass")) return;

	if( me->query_temp("qls/zhan") 
		&& me->query("neili")>1000
		&& me->query("env/������")=="��"
		&& !random(3)) 
	{
        message_vision(HIC"$N��Ȼ�����е����Ӻ���һ�𣬻����ʷ���ʽ��$n��ȥ��\n"NOR,me,victim);
		switch (random(3))
		{
		   case 0:
               if (weapon->query("skill_type")!="brush") break;
             
			   if (random(me->query_int(1))>victim->query_int()/4)
               {
			     message_vision(HIR"$nһʱ���飬�ۻ�����֮��Ϊ$N��"+weapon->query("name")+HIR"��ס��Ѩ����\n"NOR,me,victim);
				 victim->add_busy(3+random(2));
				 victim->apply_condition("no_exert",1);
               }else {
				 message_vision(HIC"$n����$N�Ĺ�����Ȼ���أ�˳�ƻ�����$N�Ĺ��ơ�\n"NOR,me,victim);
				 me->add_busy(1);
			   }
			   break;
			case 1:
			    if (weapon->query("skill_type")!="brush") break;
  
				if (random(me->query_skill("brush",1))>victim->query_skill("parry",1)/3)
               {
			     message_vision(MAG"$N����"+weapon->query("name")+MAG"����������ʽ������$n�����š�\n"NOR,me,victim);
				 victim->receive_damage("qi",2000+random(3000),me);
				 victim->receive_wound("qi",1000+random(1000),me);
               }else {
				 message_vision(HIC"$n����һ��������ˡ�\n"NOR,me,victim);
				 me->add_busy(1);
			   }
			   break;		   
			case 2:
			  if (random(me->query_skill("blade",1))>victim->query_skill("parry",1)/3)
               {
			     message_vision(HIG"$N����"+weapon->query("name")+HIG"����������ʽ��������ƣ���������$n������Ҫ����\n"NOR,me,victim);
				 victim->receive_damage("qi",3000+random(1000),me);
				 victim->receive_damage("jing",1000+random(1000),me);
               }else {
				 message_vision(HIC"$n����һ��������ˡ�\n"NOR,me,victim);
				 me->add_busy(1);
			   }
			   break;		
		}
        
    }
	return;
}
