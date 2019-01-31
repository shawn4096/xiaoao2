// xuedao-jing.c Ѫ����
// write by iceland
//xuedao-daofa.c �޸ĳɵ�������by sohu

#include <ansi.h>
#include <skill.h>
#include <combat.h>
#include <weapon.h>
inherit F_SSERVER;
inherit SKILL;

mapping *action = ({
([
	"action" : "$N���Բ���һ�С�նͷʽ�����ִӱ��������һ����ֱ��$n���",
	"skill_name" : "նͷʽ",
	"lvl" : 0,
	"damage_type" : "����",
]),
([
	"action" : "$NͻȻ�����ڵأ�$nĿ�ɿڴ�֮�ʣ�һ�С����ŵ���������$w���¶���ֱ��$n��С��",
	"skill_name" : "���ŵ�",
	"lvl" : 20,
	"damage_type" : "����",
]),
([
	"action" : "$N���һ�㣬һ������ͷ���ŵأ�һ�С�ȥ��硹��$wһ����������ң����ҵ�������ʮ��",
	"skill_name" : "ȥ���",
	"lvl" : 40,
	"damage_type" : "����",
]),
([
	"action" : "$N�ֽ�һ�������ڿ��У�һ�С����Ǿ��졹������$w���ֶ���������$n��$l",
	"skill_name" : "���Ǿ���",
	"lvl" : 60,
	"damage_type" : "����",
]),
([
	"action" : "$N��ɫ���죬���С��Ǻǡ��ͺ�һ�С����С���$w�鶯�쳣����$n��$l���߹�ȥ",
	"skill_name" : "����",
	"lvl" : 80,
	"damage_type" : "����",
]),
([
	"action" : "$Nһ�С������䡹������$w΢΢һ�����������͡��������죬��$nͷ���ء�����������",
	"skill_name" : "������",
	"lvl" : 100,
	"damage_type" : "����",
]),
([
	"action" : "$Nը�װ���һ����һʽ��ħ����$w��$n§�����б���������������ͣ��Ʋ��ɵ�",
	"skill_name" : "ħ����",
	"lvl" : 120,
	"damage_type" : "����",
]),
});

mapping *action_xd = ({
([
	"action" : RED"$N���Բ���һ�С�նͷʽ�����ִӱ��������һ����ֱ��$n"RED"���"NOR,
	"skill_name" : "նͷʽ",
	"lvl" : 200,
	"damage_type" : "����",
]),
([
	"action" : MAG"$NͻȻ�����ڵأ�$n"RED"Ŀ�ɿڴ�֮�ʣ�һ�С����ŵ���������$w"+MAG"���¶���ֱ��$n"MAG"��С��"NOR,
    "skill_name" : "���ŵ�",
	"lvl" : 120,
	"damage_type" : "����",
]),
([
	"action" : HBYEL"$N���һ�㣬һ������ͷ���ŵأ�һ�С�ȥ��硹��$w"+HBYEL"һ����������ң����ҵ�������ʮ��"NOR,
	"skill_name" : "ȥ���",
	"lvl" : 140,
	"damage_type" : "����",
]),
([
	"action" : BLU"$N�ֽ�һ�������ڿ��У�һ�С����Ǿ��졹������$w"+BLU"���ֶ���������$n"BLU"��$l"NOR,
	"skill_name" : "���Ǿ���",
	"lvl" : 160,
	"damage_type" : "����",
]),
([
	"action" : HIR"$N��ɫ���죬���С��Ǻǡ��ͺ�һ�С����С���$w"+HIR"�鶯�쳣����$n"HIR"��$l���߹�ȥ"NOR,
	"skill_name" : "����",
	"lvl" : 180,
	"damage_type" : "����",
]),
([
	"action" : HIY"$Nһ�С������䡹������$w"+HIY"΢΢һ�����������͡��������죬��$n"HIY"ͷ���ء�����������"NOR,
	"skill_name" : "������",
	"lvl" : 100,
	"damage_type" : "����",
]),
	
	([
	"action" : HBRED"$Nը�װ���һ����һʽ��ħ����$w"+HBRED"��$n"HBRED"§�����б���������������ͣ��Ʋ��ɵ�"NOR,
	"skill_name" : "ħ����",
	"lvl" : 320,
	"damage_type" : "����",]),
	
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if (me->query("max_neili") < 150)
		return notify_fail("�������������\n");
	if (me->query_skill("xuedao-jing", 1) < 20)
		return notify_fail("���Ѫ�������̫ǳ��\n");
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
	int i, level, j;
	level   = (int) me->query_skill("xuedao-daofa",1);
		//��ֽ����
	if (me->query_temp("xddf/shendao"))
	{
			for(i = sizeof(action_xd); i > 0; i--)
		    if(level > action_xd[i-1]["lvl"])
			{
				j = NewRandom(i, 20, level/5);
				return ([  
					"action": action_xd[j]["action"],
					"lvl": action_xd[j]["lvl"],
					"damage_type" : action_xd[j]["damage_type"],
					"force":150+random(300),
					"dodge":random(100),
					"damage":250+random(100),
					"parry":random(30),
				]);    
			}
		
	}	
	//���ĵ�

	if (me->query_temp("xddf/chuanxin")){
		return ([  
				"action": HBRED+HIW"$N���·�����һ�С��񵶴��ġ�ʹ�����Ӽ�Ϊ����ŹֵĽǶȷ��ִ���$n��ǰ��\n"NOR,
				"lvl": action_xd[j]["lvl"],
				"damage_type" : action_xd[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(100),
				"damage":350+random(200),
				"parry":random(30),
			]);
	}
	//���Ǿ���
	/*
	if (me->query_temp("xddf/liuxing")){
		return ([  
				"action": YEL"$N�����е����ֶ��ɣ�һ�С����Ǿ��졹����һ���������ֵĺ�⣬�������ǻ���$n\n"NOR,
				"lvl": action_xd[j]["lvl"],
				"damage_type" : action_xd[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(100),
				"damage":350+random(200),
				"parry":random(30),
			]);
	}*/
	//ҹս�˷���

	if (me->query_temp("xddf/bafang")){
		for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				"action": random(2)?BLU+action[j]["action"]+NOR:HIG+action[j]["action"]+NOR,
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(30),
				"damage":200+random(100),
				"parry":random(30),
			]);
	      }
	}

//Ѫ������֮���ŭĿ
	if (me->query_temp("xddf/jingang")){
		return ([  
				"action": HBYEL+HIW"$NȫȻ���ˣ�������Ȼ����ǰ�������ɴ���������ʽ��һ�С�����ٵء�����$nͷ��\n"NOR,
				"lvl": action_xd[j]["lvl"],
				"damage_type" : action_xd[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(100),
				"damage":350+random(200),
				"parry":random(30),
			]);
	}
	//������
	if (me->query_temp("xddf/chilian"))
	{
		if (me->query_temp("xuedao/yuxue")&&me->query_skill("xuedao-daofa",1)>449)
		{
			for(i = sizeof(action_xd); i > 0; i--)
		    if(level > action_xd[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				"action": action_xd[j]["action"],
				"lvl": action_xd[j]["lvl"],
				"damage_type" : action_xd[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(100),
				"damage":250+random(100),
				"parry":random(30),
			]);
	      }

		}
		
	}
	//��Ѫ��
	if (me->query_temp("xddf/jixue1")){
		for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				"action": random(2)?RED+action[j]["action"]+NOR:MAG+action[j]["action"]+NOR,
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(30),
				"damage":220+random(100),
				"parry":random(30),
			]);
	      }
	}
	else {
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(30),
				"damage":100+random(100),
				"parry":random(30),
			]);
	   }
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("xuedao-daofa", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if (me->query("jingli") < 40)
		return notify_fail("�������������������Ѫ������\n");
	if (me->query("neili") < 20)
		return notify_fail("�������������������Ѫ������\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xuedao-daofa/" + action;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
	object weapon,teapon; 
	int i,damage; 
	string msg;

	weapon = me->query_temp("weapon");
	if( !objectp(weapon) ) return;
	i = me->query_skill("xuedao-daofa", 1);
	damage=i+me->query_skill("xuedao-jing", 1);
	damage=damage*3+random(damage);

	if(i> 150 
		&& me->query("jiali")
       	&& me->query("max_neili") > 1500 
		&& me->query("neili") > 1000 
		&& random(10) >= 7
       	&& (random(me->query_int()) > 30 ||random(me->query_dex()) > 30)
		&& weapon->query("id")=="xue dao"
       	&& me->query_skill_mapped("parry") == "xuedao-daofa"
       	&& random(me->query("combat_exp")) > victim->query("combat_exp")/3)
	{
		if(i<350)
			msg = HIB"$NŭХһ����"+weapon->name()+HIB"��ʱ�������ɫ�Ĺ�ʣ�һ������ĺ�ɫ��â���������\n"NOR;
		else 
		{
			if(!me->query_temp("xuedao/yuxue") || !random(4))
				msg = HBBLU"ͻȻ"+weapon->name()+HBBLU"����ҫ�۵Ĺ�â�������ռ����������������ļµ�ɱ����\n"NOR;
			else
				msg = HBBLU"$N"+weapon->name()+HBBLU"��ɢ���������ε����·�ǧ������磬��$n���ؿ���Ѩ�񱼵ض�ȥ��\n"NOR;				
            if(random(4)==1) victim->add_busy(2);
			me->add_temp("apply/attack",me->query_skill("xuedao-daofa",1)/4);
			me->add_temp("apply/damage",me->query_skill("xuedao-daofa",1)/4);
			if (present(victim,environment(me)) && me->is_fighting(victim))
		       COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
			me->add_temp("apply/attack",-me->query_skill("xuedao-daofa",1)/4);
			me->add_temp("apply/damage",-me->query_skill("xuedao-daofa",1)/4);
		}
		message_vision(msg, me,victim); 
	}
	
	if( random(10) >= 7
		&& i>550
       	&& me->query_skill_mapped("parry") == "xuedao-daofa"
       	&& me->query_temp("xddf/chilian"))
	{
		   switch (random(3))
		   {
				case 0:
					message_vision( HIB"$N������ұ��"+weapon->name()+HIB"��ʱ��������ת���У���ʱ��$nȦ��������\n"NOR,me,victim);
					message_vision( HIC"$$n�ۼ������������ʱ�ֽųٻ�����æ����������\n"NOR,me,victim);

					victim->add_busy(2);
					if (!victim->query_condition("no_perform"))
						victim->apply_condition("no_perform",1);
					break;
				case 1:
					message_vision( HIM"$N���е�"+weapon->name()+HIM"����˳��һת��һ������$n�ı۰�\n"NOR,me,victim);
					victim->receive_damage("qi",damage,me);
					victim->receive_wound("qi",damage/5,me);
					break;
		   		case 2:
					message_vision( RED"$N����ζ�"+weapon->name()+RED"���������ߣ����Ѷ��У�˲�����$n������\n"NOR,me,victim);
					if (random(me->query_skill("xuedao-daofa",1))>victim->query_skill("parry",1)/2)
					{
						message_vision( RED"$nһʱ���飬Ϊ"+weapon->name()+RED"����������ֻ��������һʹ����ʱ��Ϊ���ڣ���\n"NOR,me,victim);
						victim->set("jiali",0);
						victim->apply_condition("broken_arm",1); 
						//victim->receive_damage("qi",damage,me);
						victim->receive_wound("qi",damage/2,me);

					}
					else 
						message_vision( RED"$N��������������һ����������$n�ľ�����\n"NOR,me,victim);

					break;

		   }
		
	}
}
