// tianshan-zhang.c, ��ɽ�ȷ�
// by pishou
// modified �������� by caiji@SJ 5/17/2001
// Modified by lklv for killer

#include <ansi.h>
inherit SKILL;
int lvl_temp;

mapping *action = ({
([
	"action": "$N�߾�$w, һ�С�ѩ���������������������$n��$l",
	"lvl" : 0,
	"damage_type": "����"
]),
([
	"action": "$Nʹ��һ�С���ɽѩҰ��������$w��ס����ɨ��$n��$l",
	"lvl" : 30,
	"damage_type": "����"
]),
([
	"action": "$Nʹ��һ�С������ѩ�����Ӷ�����$w�Ӹ����������$n��$l",
	"lvl" : 60,
	"damage_type": "����"
]),
([
	"action": "�����ú�һ�����죬$Nһ�С�ѩ����ơ�������$w��������$n��$l",
	"lvl" : 90,
	"damage_type": "����"
]),
});

string query_skill_name(int level)
{
	int i = sizeof(action);
	while (i--)
		if(level > action[i]["lvl"])
			return action[i]["skill_name"];
}

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "staff")
		return notify_fail("�����ϵ�����������������ɽ�ȷ���\n");

	if ((int)me->query("max_neili") < 200)
		return notify_fail("�㻹���ȼ��о������������ɡ�\n");
	return 1;
}

int practice_skill(object me)
{
	int lvl = me->query_skill("tianshan-zhang", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 40)
		return notify_fail("����Ъ���������ɡ�\n");

	if ( me->query("neili") < 20)
		return notify_fail("����Ъ���������ɡ�\n");

	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level, j;

	level=(int)me->query_skill("tianshan-zhang",1);
/*
	if( me->query_skill("staff", 1) >= 100
	 && me->query_skill("tianshan-zhang", 1) >= 100
	 && me->query_skill("huagong-dafa",1) >= 100
	 && me->query("neili") >= 800
	 && me->query_skill("poison",1) >= 100
	 && !me->query_temp("tsz/lw")
     && random(level) > 100
	 && weapon
     && random(10) > 7)
	{

		return ([
			"action": BLU"$N�ٺ�һ����Ц,�������ȶ�һĨ,$w"+BLU+"��ת�Ӷ������Ƹ�Ϊ����"NOR,
			"damage": 200 + random(180),
			"parry": random(40),
			"dodge": random(40),
			"force": 400,
			"damage_type": "����"
		]);
	}
	*/
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
            //׷��
			if (me->query_temp("tsz/zhuihun"))
			{
				return ([
					"action" : HIB+replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIB)+NOR,
					"force" : 200 + random(350),
					 "dodge" : 20+random(25),
					"parry": 25 + random(15),
					"damage" : 250 + random(150),
					"damage_type" : action[j]["damage_type"],
					"lvl": action[j]["lvl"],
				]);

			}
			//����
			if(me->query_temp("tsz/lw")) {
               return ([
                          "action": HIC + replace_string(action[j]["action"],"$w","$w"HIC)+NOR,
                           "lvl": action[j]["lvl"],
                           "damage_type" : action[j]["damage_type"],
                           "damage": 200 + random(150),
                           "force":200+random(300),
                           "dodge":20+random(30),
                           "parry":10+random(30),
                   ]);
			 }
             else {
				return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"damage": 160 + random(100),
				"force":150+random(300),
				"dodge":random(30),
				"parry":random(30),
				]);
			 }
		}
	}
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	object weapon;
	int lvl,damage;

	if (!me||!victim) return;
	weapon = me->query_temp("weapon");
    if(!weapon) return;
    
	if (me->query_skill_prepared("strike") != "chousui-zhang"||me->query_skill_mapped("strike") != "chousui-zhang" ) return;

	lvl= me->query_skill("tianshan-zhang", 1);
//ɢ��Ч��
	damage=lvl+me->query_skill("huagong-dafa", 1);
	damage=damage*3+random(damage);

	if (lvl>=500
	&& me->query("env/������") != "����"
	&& me->query_skill("poison", 1) > 180
	&& (me->query("family/family_name") == "������"	|| me->query("combat_exp", 1) > 2000000 )
	&& random(me->query_skill("poison", 1)) > random( victim->query_skill("medicine", 1))
	&& !victim->query("job_npc")) {
		if( random(lvl_temp) <= 350) {
			victim->add_condition("xx_poison", random( me->query_skill("poison",1)/30) + 5);
			tell_object(victim, HIG "�������ǰһ���Σ��ƺ����˶���ԭ���Է�����Ĩ�Ķ�ҩ����ɢ���Ŷ�����\n" NOR );
			if (me->query("quest/hgdf/powerup"))
			   victim->add_busy(1);
		}
		else if( random(lvl_temp) > 350) {
			victim->add_condition("xx_poison", random( me->query_skill("poison",1)/15) + 5 );
			tell_object(victim, HIG "����ñ����еĵط�һ����ľ���ƺ����˶���ԭ���Է�������ͿĨ�ж�ҩ��\n" NOR );
            if (me->query("quest/hgdf/powerup"))
			   victim->add_busy(2+random(2));
		}
		if (userp(me)
		 && userp(victim)
		 && !victim->query_temp("kill_other/"+me->query("id"))
		 && !me->query_temp("other_kill/"+victim->query("id"))
		 && !me->query_temp("revenge/"+victim->query("id"))
		 && !victim->query_condition("killer") )
			me->add_condition("killer", 5);
	}
	//���
	if (victim
		&&random(10)>6
		&&me->query_skill_mapped("dodge")=="zhaixingshu"
		&&me->query_temp("tsz/lpf"))
	{
		message_vision(HIC"$N���һ�������ֽ����е�"+weapon->query("name")+HIC"������$n!\n"NOR,me,victim);
		victim->receive_damage("qi",damage,me);
		victim->receive_wound("qi",damage/2,me);
		//message_vision(HIC"$N��������ժ�����������ڿ�������ת�����ֽ����е�"+weapon->query("name")+"����$n!\n"NOR,me,victim);

	}
	//׷����ӹ���  	
        
	if( random(10)> 6 && me->query_temp("tsz/zhuihun"))
    {
   	          
         message_vision(HIB "$N�����е�"+HIW+weapon->query("name")+HIB"һ�գ����־���һ�г����ƣ��Ʒ��ȳ�����Ȼ�Ǻ��о綾��\n" NOR,me, victim);
         me->add_temp("apply/attack", lvl/2);
         me->add_temp("apply/strength", lvl/25);
         me->add_temp("apply/damage", lvl/4);
         weapon->unequip(); 
         if (me->is_fighting(victim))
			COMBAT_D->do_attack(me, victim, me->query_temp("weapon"),3); 
         weapon->wield();
         me->add_temp("apply/attack", -lvl/2);
         me->add_temp("apply/strength", -lvl/25);
         me->add_temp("apply/damage", -lvl/4);
 
     }
}

string perform_action_file(string action)//add by caiji
{
	return __DIR__"tianshan-zhang/" + action;
}
