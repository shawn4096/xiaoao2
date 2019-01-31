//    /kungfu/skill/suixing-tui.c ��Ӱ������

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N������ǰ����Ȼ������ȣ�һʽ������ִ�ԡ���ֱ��$n��ͷ��",
	"lvl" : 0,
	"skill_name" : "����ִ��",
	"damage_type" : "����"
]),
([
	"action" : "$N����һ����˫���أ�һʽ�����ǰ��¡����ڿ��������߽ţ�ֱ��$n��ͷ���ء���",
	"lvl" : 40,
	"skill_name" : "���ǰ���",
	"damage_type" : "����"
]),
([
	"action" : "$N����ǰ�㣬��Ż�Բ������ʹ��һʽ������ޱߡ���ɨ��$n������",
	"lvl" : 80,
	"skill_name" : "����ޱ�",
	"damage_type" : "����"
]),
([
	"action" : "$N����ٿ�ص������������ȣ�����$n��ͷ�����ز����ɲ�������һʽ��ת���ֻء�",
	"lvl" : 120,
	"skill_name" : "ת���ֻ�",
	"damage_type" : "����"
]),
([
	"action" : "$N������������������η�ת��ɨ��һ�С����켫�֡�������$n��$l",
	"lvl" : 150,
	"skill_name" : "���켫��",
	"damage_type" : "����"
]),
([
	"action" : "$NԾ���ڰ�գ�˫������������磬һʽ������ȱ���Ѹ�����׵ؾ���$n",
	"lvl" : 180,
	"skill_name" : "����ȱ�",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="leg" || usage=="parry"; }

int valid_combine(string combo) 
{
	object me;
	me = this_player(); 

	if ((int)me->query_int(1) > 40)
		return combo=="qianye-shou"; 
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("ѧ��Ӱ������ʱ���ﲻ����������\n");
	if ( me->query_skill("yijin-jing", 1) < 60)
		return notify_fail("����׽�ڹ���򲻹����޷�ѧ��Ӱ�����ȡ�\n");
	if ( me->query_skill("leg", 1) < 350)
		return notify_fail("��Ļ����ȹ���δС�ɣ�����350�����޷�ѧ��Ӱ�����ȡ�\n");
	if ( me->query_skill("shaolin-tantui", 1) < 350)
		return notify_fail("������ֵ��ȹ���δС�ɣ�����350������������Ӱ�����ȡ�\n");

	if ( me->query_skill("buddhism") < 220)
	{
		if ( me->query_skill("banruo-zhang", 1)
		 || me->query_skill("yizhi-chan", 1)
		 || me->query_skill("jingang-quan", 1)
		 || me->query_skill("nianhua-zhi", 1)
		 || me->query_skill("longzhua-gong", 1)
		 || me->query_skill("sanhua-zhang", 1))
			return notify_fail("��ķ��������������޷�ͬʱѧϰ�������ϵ��ϳ˿��ֹ���\n");
	}

	if ((int)me->query("max_neili") < 600)
		return notify_fail("�������̫�����޷�����Ӱ�����ȡ�\n");
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
	string msg;
	level   = (int) me->query_skill("ruying-suixingtui",1);
        
	if (me->query_temp("sl_rysxt")){
		switch(me->query_temp("sl_rysxt")){
			case 5: msg = HIY"$N��ȻԾ�����һ��һ������ʱ֮���߳�һ�С��硹�־��Ĵ����ȣ�ֱϮ$nǰ��"NOR; break;
			case 4: msg = HIY"������$N���ȹ��أ�������һŤ�������ȵ�һ�С�Ӱ���־���������������$n"NOR; break;
			case 3: msg = HIY"ֻ��$N�ҽž���δ���������һת������˳��ɨ��һ�С��桹�־�����Ӱ����"NOR; break;
			case 2: msg = HIY"�����$N��δ�󳷣��Ѿ������Ρ��־����ھ�ֱ͸�ż⣬��$n�ظ�����������ʮ��"NOR; break;
			case 1: msg = HIR"��ʱ$N˫��չ��������һ��ǿ�ҵ����磬˫����ʱ�벢������Ӱ���Ρ�һ�����ں���$n����֮��"NOR; break;
		}
		me->add_temp("sl_rysxt", -1);                  
		return([
			"action": msg,
			"force" : 300+random(200),
			"dodge" : random(35),
			"parry" : random(35),
            "damage": 140 + random(140),

			"damage_type" : me->query_temp("sl_rysxt")?"����":"����",
		]);
	}
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			
			return ([
				"action": action[j]["action"],
				"damage_type": action[j]["damage_type"],
				"lvl": action[j]["lvl"],
				"force": 150 + random(300),
				"damage": 80 + random(80),
				"dodge": random(30),
				"parry": random(30),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("ruying-suixingtui", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;
	if ( me->query_skill("buddhism") < 220)
	{
		if ( me->query_skill("banruo-zhang", 1)
		 || me->query_skill("yizhi-chan", 1)
		 || me->query_skill("jingang-quan", 1)
		 || me->query_skill("nianhua-zhi", 1)
		 || me->query_skill("longzhua-gong", 1)
		 || me->query_skill("sanhua-zhang", 1))
			return notify_fail("��ķ��������������޷�ͬʱ��ϰ�������ϵ��ϳ˿��ֹ���\n");
	}
	if ((int)me->query("jingli") < 40)
		return notify_fail("��ľ���̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("���������������Ӱ�����ȡ�\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"ruying-suixingtui/" + action;
}

mixed hit_ob(object me, object target)
{
	string msg;
	int i,j,damage;
	j = me->query_skill("ruying-suixingtui", 1);
    i=me->query_skill("shaolin-tantui",1);
	damage=i+j;
	damage=damage+me->query_skill("yijin-jing",1)+me->query_skill("leg",1);
	damage=damage*me->query_dex()/10;
	if (!me->query("quest/sl/rysxt/tiezhou/pass")) return;
	
	if (!me || !target) return;

	if( random(20) >= 12 
	&& j > 200 
	&& me->query("neili") > target->query("neili")
	&& me->query("neili") > 1000 
	&& me->query("max_neili") > 1500
	&& me->query_skill("shaolin-tantui",1)>450)
	//&& random(j) > random(target->query_skill("dodge",1))
	{
		
		switch(random(4))
		{
			case 0 :
			if (me->query_skill("shaolin-tantui",1)>450)
			{
				
				msg = HIC"$N����������һʽ"HIR"�����ֵ��ȡ�"HIC"����շ���֮�ʣ���Ȼ������$n���ؿڣ�\n";
				msg += "$nֻ����Ȼһ�죬�ѱ���һ�С����ȡ����У�\n"NOR; 
				target->add_busy(random(1));
				target->receive_damage("qi",damage/3,me);
				
			}
				break;
			case 1 :
				if (me->query_skill("shaolin-tantui",1)>450)
				{	
					msg = HIW"$N˫�������߳���һʽ"HIR"��ԧ�������ȡ�"HIW"��һƬ��Ӱ����$n���ظ��䣡\n";
					msg += "���$n��Ѫ��ӿ����ʱ��Ѫ����,��������\n"NOR;
					if (damage>target->query("neili"))
					{
						target->set("neili",0);
					}else
						target->add("neili",-damage);

					target->add_condition("no_exert",1);
					target->receive_wound("qi",damage/2,me);
				}
				break;
			case 2 :
				if (me->query_skill("ruying-suixingtui",1)>450)
				{	
					msg = MAG"$N���ٱ���$n������Խ��Խ�죬����Ծ��һʽ"HIC"�������ȡ�"MAG"����$n���֮�ʣ�һ�Ŵ���$n�����У�\n";
					msg += "���$n�о���������������˿���᲻����������\n"NOR;
					target->add_busy(1);
					target->add_condition("no_perform",1);
					target->receive_wound("qi",damage/2,me);
				}
				break;
			case 3 :
				if (me->query_skill("ruying-suixingtui",1)>500)
				{	
					msg = WHT"$N����Ծ�𣬼���ת����˫����ת������磬�γ�һ�����磬����"HIB"�������ȡ�"MAG"����ʽ��\n";
					me->add_temp("apply/damage",me->query_skill("ruying-suixingtui",1)/4);
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
					me->add_temp("apply/damage",-me->query_skill("ruying-suixingtui",1)/4);

				}
				break;
		}
		message_vision(msg, me, target);
	}
}
