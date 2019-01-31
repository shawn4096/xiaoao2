//tianmo-gun.c ������ħ��
//By xjqx@SJ 2009/1/1
#include <ansi.h>
inherit SKILL; 

mapping *action = ({
([      "action":"$N�������ˣ�����$wӭ��һ����һ�С��ºڷ�ߡ�������$n��ͷ�������ҽ�������",
        "lvl"   :0,
        "skill_name" :"�ºڷ��",
        "damage_type":"����"
]),
([      "action":"$N�����ɫ������$w��һ�С���糤�š������������$n��$l����ɨȥ��",
        "lvl"   :20,
        "skill_name" :"��糤��",
        "damage_type":"����"
]),
([      "action":"$N����һת������$w����һ�ϣ������⽫��δ��֮�ʣ�һ�С����·ת������$n��ͷ���¡�",
        "lvl"   :50,
        "skill_name" :"���·ת",
        "damage_type":"����"
]),
([      "action":"$N����һת��һ�С��������⡹$w�ó������Ӱ������ʵʵ��Ϯ��$n��$l��",
        "lvl"   :80,
        "skill_name" :"��������",
        "damage_type":"����"
]),
([      "action":"$N����ʱ���������죬$w�䴦������ϼǧ�ƣ�һʽ���������桹������������ȫȻ����$n���С�",
        "lvl"   :120,
        "skill_name" :"��������",
        "damage_type":"����"
]),
([      "action":"$n��Ȼ����$N����һ̧ͷֻ��$Nһʽ�����R�L��������������һ�㾶ֱɨ��$n$l��",
        "lvl"   :150,
        "skill_name" :"���R�L��",
        "damage_type":"����"
]),
([      "action":"$n��Ȼ����$N����һ̧ͷֻ��$Nһʽ����Գ���ҡ�����������һ�㾶ֱɨ��$n$l��",
        "lvl"   :150,
        "skill_name" :"��Գ����",
        "damage_type":"����"
]),
});

int valid_enable(string usage) { return usage == "club" || usage == "parry"; }

int valid_learn(object me)
{
   if(!me->query_skill("xixing-dafa", 1)||(int)me->query_skill("tianmo-gong",1)<200)
   if(me->query_skill("tianmo-gong", 1) < 200 )
           return notify_fail("��ħ����Ҫǿ����֧�֣���������ڹ�����̫ǳ������ѧ��ħ����\n");

     if ((int)me->query_skill("club", 1) < 200)
         return notify_fail("��Ļ���������򲻹���\n");

     if ((int)me->query("max_neili") < 3500)
         return notify_fail("�������̫�ͣ��޷�ѧ������ħ����\n");

     if ((int)me->query_skill("club", 1) < (int)me->query_skill("tianmo-gun", 1))
         return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������������ħ����\n");

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

	level = (int) me->query_skill("tianmo-gun",1);
	
	if ( me->query_temp("tmg/luanwu")){
				return ([
					"action" : action[j]["action"],
					"damage": 150+random(150),
					"damage_type": "����",
					"dodge": random(35),
					"parry": random(35),
					"force": 200+random(300),
				]);
			}
	if ( me->query_temp("tmg/pokuai")){
				return ([
					"action" : action[j]["action"],
					"damage": 200+random(180),
					"damage_type": "����",
					"dodge": random(35),
					"parry": random(35),
					"force": 200+random(500),
				]);
			}
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action" : action[j]["action"],
				"force" : 200 + random(350),
				"dodge" : random(25)-5,
				"parry": 20-random(10),				
				"damage_type" : action[j]["damage_type"],
				"lvl": action[j]["lvl"],
				"damage" : 100 + random(120),
			]);
		}
	}
				
}

int practice_skill(object me)
{
     object weapon;

     if (! objectp(weapon = me->query_temp("weapon")) ||
        (string)weapon->query("skill_type") != "club")
            return notify_fail("��ʹ�õ��������ԡ�\n");

     if ((int)me->query("jingli") < 70)
            return notify_fail("�������������������ħ����\n");

     if ((int)me->query("neili") < 80)
            return notify_fail("�������������������ħ����\n");
     if (me->query_skill("dali-shenmofu",1)>1)
			return notify_fail("������ħ����ǿ��ı���Ϊǰ����������͹�����Զ�����������򲻷������޷���ϰ��ħ����\n");
	 if (me->query_skill("qixian-wuxingjian",1)>1)
			return notify_fail("��ħ����׾�����ͽ������鶯���򲻷���������壬���޷���ϰ��ħ����\n");
       me->receive_damage("jingli", random(60));
     return 1;
}

string perform_action_file(string action)
{
     return __DIR__"tianmo-gun/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
  object weapon=me->query_temp("weapon");
  //���ܺ󷽿�ʹ��
  if (objectp(victim)
	  && me->is_fighting(victim)
	  && random(5)>2
	  && me->query("env/��׾")
	  && me->query("quest/hmy/tmgf/jueji")=="pass"
	  )
  {
 
    switch (random(3))
    {
	 case 0:
		 message_vision(HIY"$N��������ת���֣��������е�"+weapon->query("name")+HIY"�γ�һ�ɾ��磬��$n��������\n"NOR,me,victim);
         if (random(me->query_skill("force",1))>victim->query_skill("force",1)/2)
         {
	       message_vision(HIG"$nһʱ���飬Ϊ����ɨ�н��ף����ɵ�һ���ʹ������\n"NOR,me,victim);
		   victim->receive_damage("qi",4000+random(2000),me);
		   victim->receive_wound("qi",1000+random(1000),me);
          }
		  else message_vision(HIW"$n��ȻһЦ��������������$N����Ĺ�������������\n"NOR,me,victim);
     break;
       case 1:
		 message_vision(HIC"$N��Ӱ���أ�ָ��������ȫȻ�����·������Ʊ�׾����ÿһ�ж�ǡ�û�����$n�ı���֮����\n"NOR,me,victim);
         if (random(me->query("str"))>victim->query("dex")/2)
         {
	       message_vision(CYN"$n�о��������ƣ���ʽ������ɬ��\n"NOR,me,victim);
		   victim->apply_condition("no_perform",2);
          }else message_vision(HIW"$n��Цһ������ʽ���䣬�ָֻ�����ǰ������ˮ��\n"NOR,me,victim);
     break;
	 case 2:
		 message_vision(HIW"$N���ٻ���"+weapon->query("name")+HIW",�γ�������Ӱ������������ֻ�$n���������ͬ��λ��\n"NOR,me,victim);
         if (random(me->query_skill("tianmo-gun",1))>victim->query_skill("parry",1)/2)
         {
	       message_vision(RED"$n�پ��Լ��Ĵ�������$N��Ӱ������֮�У����к��о�Ϊ�Է�����ס��\n"NOR,me,victim);
		   victim->add_condition("no_perform",1);
		   me->add_temp("apply/club",me->query_skill("tianmo-gun",1)/4);
		   COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
           COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
		   COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
		   me->add_temp("apply/club",-me->query_skill("tianmo-gun",1)/4);
          }else message_vision(WHT"$n��Цһ������ʽ���䣬�ָֻ�����ǰ������ˮ��\n"NOR,me,victim);
     break;
   
    }

   }
  

}