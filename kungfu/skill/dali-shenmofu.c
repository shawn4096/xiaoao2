// cred by sohu@xojh   ��ħ��ͷ
//dali-shenfu  ���ɾ���
// cred by sohu@xojh
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N�߾�����$w��һʽ����ɽ����������ǰ����ʽ�ǳ��򵥣���$n��$l��ȥ���Ʋ��ɵ�",
        "force" : 160,
        "dodge" : 5,
        "damage" : 10,
        "lvl" : 350,
        "skill_name" : "��ɽʽ",
        "damage_type" : "����"
]),
([      "action" : "$Nһʽ�����ء����������ף��綨������$w������$n��$l��ȥ���������",
        "force" : 200,
        "dodge" : 10,
        "damage" : 20,
        "lvl" : 350,
        "skill_name" : "����ʽ",
        "damage_type" : "����"
]),
([      "action" : "$N�Ӷ�$w�����������츫Ӱ��һʽ���������������ʱ����$n��ȫ��",
        "force" : 240,
        "dodge" : -15,
        "damage" : 40,
        "lvl" : 60,
        "skill_name" : "����ʽ",
        "damage_type" : "����"
]),
([      "action" : "$N�Ӷ�$w����������������������һʽ���������������������ʱ����$n��ȫ��",
        "force" : 240,
        "dodge" : -15,
        "damage" : 40,
        "lvl" : 60,
        "skill_name" : "����ʽ",
        "damage_type" : "����"
]),
([      "action" : "$N�Ӷ�$w�����������츫Ӱ��һʽ����硹�������ʱ����$n��ȫ��",
        "force" : 240,
        "dodge" : -15,
        "damage" : 40,
        "lvl" : 60,
        "skill_name" : "���ʽ",
        "damage_type" : "����"
]),
([      "action" : "$N�����ӳ���ʮ��ͷ������һƬ��Ӱ������һʽ�����꡹��$w����$n������",
        "force" : 280,
        "dodge" : -10,
        "damage" : 60,
        "lvl" : 90,
        "skill_name" : "����ʽ",
        "damage_type" : "����"
]),
([      "action" :HIR"$N��ʽ�򵥣��������һ������������һʽ�����ҡ���$w"HIR"����$n��$l���Ѵﷵ豹���֮��"NOR,
        "force" : 300,
        "dodge" : -10,
        "damage" : 380,
        "lvl" : 350,
        "skill_name" : "����ʽ",
        "damage_type" : "����"
]),
});


int valid_enable(string usage)
{
    object me=this_player();
	if (me->query("quest/hmy/dlsmf/pass")&&me->query("gender")=="����")
       return usage == "axe" || usage == "parry"; 
}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 1000)
                return notify_fail("�����������1000,�޷�ѧϰ��\n");
        if (me->query_str() < 60)
                return notify_fail("��ı�������60��̫���ˡ�\n");
        if ((int)me->query_skill("tianmo-gong", 1) < 100)
			//||(int)me->query_skill("xixing-dafa", 1) < 100)
                return notify_fail("�����ħ�������Ǵ󷨻��̫ǳ��\n");
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
      int i, j,level;
		weapon=me->query_temp("weapon");
        level   = (int) me->query_skill("dali-shenmofu",1);
        for(i = sizeof(action); i > 0; i--)
			if(level > action[i-1]["lvl"]){
			   j = NewRandom(i, 20, level/4);
			   	if( me->query_temp("dlf/duanyun")){
				  return ([
					"action" : HIR+replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIR)+NOR,
					"force" : 150 + random(100),
					"dodge": random(20),
					"damage": 150 + random(100),
					"lvl" :  action[j]["lvl"],
					"parry": random(20),
					"weapon" : "����",
					"damage_type" : random(2)?"����":"����",
				   ]);
			    }
				
				
				if( me->query_temp("dlf/leiting")){
				  return ([
					"action" : HIW+replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIW)+NOR,
					"force" : 250 + random(100),
					"dodge": random(20),
					"damage": 250 + random(100),
					"lvl" :  action[j]["lvl"],
					"parry": random(20),
					"weapon" : "����",
					"damage_type" : random(2)?"����":"����",
				   ]);
			    }
                  return ([  
			    	"action": action[j]["action"],
				    "lvl": action[j]["lvl"],
				    "damage_type" : action[j]["damage_type"],
				    "force":100+random(250),
				    "dodge":random(20)-10,
				    "damage":100+random(60),
				    "parry":random(10),
			    ]);
		} 
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "axe")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("jingli") < 50)
                return notify_fail("�������������ϰ��������ħ������\n");
        if ((int)me->query("neili") < 10)
                return notify_fail("�������������ϰ��������ħ������\n");
        if (me->query_skill("qixian-wuxingjian",1)>1)
		        return notify_fail("������ħ����ǿ��ı���Ϊǰ����������ͽ������鶯���򲻷������޷���ϰ������ħ����\n");
	    if (me->query_skill("tianmo-gun",1)> 1)
				return notify_fail("��ħ����׾�����͸����ĸ��͹��򲻷���������壬���޷���ϰ������ħ����\n");
		
		
		me->receive_damage("jingli", 30);        
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"dali-shenmofu/" + action;
}
