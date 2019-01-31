// cuixin-zhang.c ������ by XiaoYao 4/22/99
// By KinGSo 2006��4��28�� ���±༭ ������AUTO PFM
// �޸�Ϊ���� skill

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : HIG "$Nʹһ�С�������ӿ����˫��Ʈ�Ʋ�������$n$l"NOR,
        "force" : 260,
        "dodge" : 2,
        "skill_name" : "������ӿ",
        "lvl" : 0,
        "damage_type" : "����"
]),
([      "action" :HIC "$Nٿ������$n��ǰ��һ�С��ﲨ���ˡ�ֱ��$n��$l"NOR,
        "force" : 340,
        "dodge" : 0,
        "skill_name" : "�ﲨ����",
        "lvl" : 30,
        "damage_type" : "����"
]),
([      "action" : HIY"$N������$nһת��һ�С����ײ�����$n$l��������"NOR,
        "force" : 420,
        "dodge" : -2,
        "skill_name" : "���ײ���",
        "lvl" : 50,
        "damage_type" : "����"
]),
([      "action" : HIB"$N���ΰ����ڰ��һ�С����羪�ס������ͻ�$n��$l"NOR,
        "force" : 460,
        "dodge" : -4,
        "skill_name" : "���羪��",
        "lvl" : 90,
        "damage_type" : "����"
]),
([      "action" :HIM "$Nʹһ�С���ɳ��Ӱ������������ֱ��$n��$l"NOR,
        "force" : 510,
        "dodge" : -6,
        "skill_name" : "��ɳ��Ӱ",
        "lvl" : 120,
        "damage_type" : "����"
]),
([      "action" :BLU "$Nһ�����ʹ�������Ǵ��ġ����ó�������Ӱ�����Ʋ���$n��$l"NOR,
        "force" : 560,
        "dodge" : -8,
        "skill_name" : "���Ǵ���",
        "lvl" : 150,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_combine(string combo) 
{
	object me;
	me = this_player(); 

	  if ((int)me->query_int() > 1)
		return combo=="jiuyin-baiguzhua"; 
}


int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������Ʊ�����֡�\n");
        if((int)me->query_skill("cuixin-zhang", 1 ) < 120)
                return notify_fail("��Ĵ����Ƶȼ�������������ѧϰ��\n");
        if( (int)me->query_skill("jiuyin-shenzhang", 1 ) >= 1)
                return notify_fail("ѧ�˾������ƣ���Ҫ�����ƣ�\n");
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������̫�����޷��������ơ�\n");
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
        int i, level,j;
        level = (int) me->query_skill("cuixin-zhang",1);
        for(i = sizeof(action); i > 0; i--) {
                if(level > action[i-1]["lvl"])
				{
					j = NewRandom(i, 20, level/5);
					
					if (me->query("quest/jiuyin2/cuixin/pass"))			
					{
					return ([  
				"action":	HIR+action[j]["action"]+NOR,
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"force":	600+random(350),
				"dodge":	random(20)+10,
				"damage":	650+random(150),
				"parry":	random(25),
			     ]);		
					}				 
				return action[NewRandom(i, 5, level/5)];	
				}
		}					

}


int practice_skill(object me)
{
        if ((int)me->query("qi") < 30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("������������������ơ�\n");
        me->receive_damage("qi", 25);
        me->add("neili", -10);
        return 1;
}

void skill_improved(object me)
{
    tell_object(me, "���������ź�Ȼ���ĵ�����һ��а�\n");
    me->add("shen", -(me->query_skill("cuixin-zhang", 1)*100));
}

string perform_action_file(string action)
{
        return __DIR__"cuixin-zhang/" + action;
}
mixed hit_ob(object me, object target)
{
    string msg;
    int j;
    j = me->query_skill("cuixin-zhang", 1);
   
    if (random(me->query_con()) >= target->query_con()/4 && j > 120 &&
        me->query_skill("parry",1) > 120 &&
        me->query("jingli")>300 && 
        !target->is_busy() &&
        random(me->query("combat_exp"))> target->query("combat_exp")/2 && 
        me->query("neili")>500 &&
		me->query("quest/jiuyin2/cuixin/pass"))
     {
          switch(random(2))
          {
            case 0 :
               msg = HIG "$NĬ�˴����������ھ�����˫�ƹ���$n��һ�ɴ��Ķϳ���İԵ��ھ�ӿ��$n��������\n";
               msg = msg + "$nֻ���Ŀڴ���˺�Ѱ�����ܣ��ѱ�һ�л���"HIR"��������"HIG"���ڣ�\n"NOR; 
               target->recevied_damage("qi", j*3 +random(300));
               target->add_busy(1+random(3));
               target->apply_condition("cx_poison", random(j) /2);
               me->add("neili",-50);
               break;
            case 1 :
               msg = HIY "$NĬ�˴���������˫�ƴ���һ�������������$n�������ڣ�\n";
               msg += "$nֻ���ؿ�һʹ���ѱ�һ�в�����"HIR"������������\n"NOR;
               target->recevied_damage("qi", j*2 + random(300));
               target->add_condition("cx_poison",  random(j) /3);
               target->add_busy(1+random(2));
               me->add("neili",-50);
               //message_vision(msg, me, target);
              
               break;
            
          }         
          message_vision(msg, me, target);
   }
   return ;
}


