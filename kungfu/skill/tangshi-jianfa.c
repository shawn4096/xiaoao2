
#include <ansi.h>
#include <combat.h>
inherit SKILL;
#include <combat_msg.h>

mapping *action = ({
([	"action" : "$N��ǰ����һ����ͬʱ���д�һ����һʽ��"+HIG"���̺�����"NOR+"��ֱ��$n��$l",
	"force" :random(30)+ 60,
	"dodge" : 5,
	"damage" : 20,
        "lvl" : 0,
	"damage_type" : "����"
]),
([      "action" : "$N��ǰ������һ�С�"+HIB"������СС"NOR+"����������ãĪ�⣬$w��ǰ���$n��$l",
        "force" :random(30)+ 80,
        "dodge" : 15,
        "damage" : 25,
        "lvl" : 10,
        "damage_type" : "����",
]),
([      "action" : "$N���ֶ���һ�У��·�������ʲô��һ�С�"+HIW"�����羪��"NOR+"���������е�$w��ǰ����$n��$l",
        "force" :random(30)+ 100,
        "dodge" : 5,
        "damage" : 35,
        "lvl" : 20,
        "damage_type" : "����",
]),
([      "action" : "$N����$w��ת��һʽ��"+HIY"��ɽ������"NOR+"��������$w�Ľ�����һ�Ⲽһ������$n��$l",
        "force" :random(30)+ 120,
        "dodge" : 10,
        "damage" : 40,
        "lvl" : 30,
        "damage_type" : "����",
]),
([      "action" : "$N���к��䣬$w��ǰһ�ᣬ����бб��ʹ��һʽ��"+HIR"�Ǻ᲻�ҹ�"NOR+"����$w����$n",
        "force" :random(30)+ 140,
        "dodge" : -5,
        "damage" : 45,
        "lvl" : 40,
        "damage_type" : "����",
]),
([  	"action" : "$N����бָ��أ����һ����һ�С�"+HIC"�����д��"NOR+"����������$n������$w�漴�̳�",
    	"force" :random(30)+ 160,
    	"dodge" : 15,
    	"damage" : 50,
    	"lvl" : 50,
    	"damage_type" : "����",
]),
([      "action" : "$N��$w��ǰһ�ᣬ�Ż��󿪣���Ȼ���أ�������"+HIR"��ǰ��Խ�㣬��ʬ����ˬ"NOR+"�����̺�����ɱ��",
        "force" :random(30)+ 140,
        "dodge" : -50,
        "damage" : 200,
        "lvl" : 200,
        "damage_type" : "����",
]),
([  	"action" : "$Nͷ����̧��������£��������֮�ģ�ʩչ��"+HIC"��ͷ����Ҳ����ͷ������"NOR+"��$w�������д̳���",
    	"force" :random(30)+ 160,
    	"dodge" : 15,
    	"damage" : 150,
    	"lvl" : 350,
    	"damage_type" : "����",
]),
([      "action" : "$N��$w������󣬺�����š��ʲô����������"+HIY"��������š���ˣ�һ�а���ɥ����"NOR+"��",
        "force" :random(30)+ 140,
        "dodge" : -50,
        "damage" : 185,
        "lvl" : 450,
        "damage_type" : "����",
]),
([  	"action" : "$Nʩչ��ʬ��������֮�أ���"+CYN"����һ�Ƚ��������纣��"NOR+"����ʽ���糤����ӣ�$w���裬��ʽ���ϲ���",
    	"force" :random(30)+ 160,
    	"dodge" : 15,
    	"damage" : 200,
    	"lvl" : 550,
    	"damage_type" : "����",
]),
});
mapping *action_ts = ({

([	"action" : HIG"$N�Ѿ�������ʫ�������⣬ʩչ�����º躣������,����Ʈ�죬������ʷɺ裬��ʽ������ֱ��$n��$l"NOR,
	"force" :random(30)+ 60,
	"dodge" : 5,
	"damage" : 40+random(40),
        "lvl" : 100,
	"damage_type" : "����"
]),
([      "action" : HIB"$N���Ӻ��㣬һ�С���������������������ãĪ�⣬��ǰ���$n��$l"NOR,
        "force" :random(30)+ 80,
        "dodge" : 15,
        "damage" :50+random(50),
        "lvl" : 120,
        "damage_type" : "����",
]),
([      "action" : HIY"$N���ֶ���һ�У��·�������ʲô��һ�С������ž��硹,��ǰ����$n��$l"NOR,
        "force" :random(30)+ 100,
        "dodge" : 5,
        "damage" : 80+random(80),
        "lvl" : 150,
        "damage_type" : "����",
]),
([      "action" : HIC"$N��ʽ��ת��һʽ����ɽ�����Ρ������ƻ�����һƬ���ƣ�����$n��$l"NOR,
        "force" :random(30)+ 120,
        "dodge" : 10,
        "damage" : 90+random(90),
        "lvl" : 200,
        "damage_type" : "����",
]),
([      "action" : MAG"$N���к��䣬��ǰһ�ᣬ����бб��ʹ��һʽ�����겻�ҹˡ�,����$n��$l"NOR,
        "force" :random(30)+ 140,
        "dodge" : -5,
        "damage" : 100+random(100),
        "lvl" : 250,
        "damage_type" : "����",
]),
([  	"action" :HIM "$N����бָ��أ����һ����һ�С������մ��졹��������$n�������漴�̳�,�����ݺᡣ"NOR,
    	"force" :random(30)+ 160,
    	"dodge" : 15,
    	"damage" : 110+random(110),
    	"lvl" : 350,
    	"damage_type" : "����",
]),
([      "action" : HIR"$N�����Ƶ������糤����ӣ������̺���������ɽ�����ƺ��뺣���������ƣ��㼯��һƬ�Ƶ��Ľ�Ӱ��"NOR,
        "force" :random(30)+ 140,
        "dodge" : -5,
        "damage" : 120+random(120),
        "lvl" : 450,
        "damage_type" : "����",
]),
([  	"action" :HIW"$N���Ƴ���Ʈ��֮����һ�ɲ���֮����ӿ������������ʫ�����ľ���������ǧ��Ŀ������һ��¥��"NOR,
    	"force" :random(30)+ 160,
    	"dodge" : 15,
    	"damage" : 140+random(140),
    	"lvl" : 550,
    	"damage_type" : "����",
]),

});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level   = (int) me->query_skill("tangshi-jianfa",1);
	if ( me->query_temp("tangshi/erguang")){
			return ([
				"action": random(2)?HIW"$N����������������ֳ�����Ȼ�ݳ����͵��｣�����֣����ַ������ĵ�һ������"NOR:HIY"$N����������������ֳ�����Ȼ�ݳ����͵��｣�����֣����ַ������ĵ�һ������"NOR,
                 "force" :random(30)+ 160,
    	        "dodge" : 15,
    	        "damage" : 250+random(100),
    	        "lvl" : 150,
    	        "damage_type" : "����",
			]);
                
	}
	
	if ( me->query_temp("tangshi/cijian")){
			return ([
				"action": random(2)?HIC"$N��Хһ����������Ȼ�ӿ죬$n���ü��У�$NͻȻ�䳤��������߲��һ���������$n����硣"NOR:MAG"$N���б���Խ��Խ�죬$n����һ����$NͻȻ�䳤��������߲��һ���������$n���Ҽ硣"NOR,
                 "force" :random(30)+ 160,
    	         "dodge" : 15,
    	        "damage" : 350+random(100),
    	         "lvl" : 150,
    	         "damage_type": "����"
			]);                
	}

	if (me->query_temp("tangshi/shiyin"))
	{
		for(i = sizeof(action_ts); i > 0; i--)
                if(level > action_ts[i-1]["lvl"])
                        return action_ts[NewRandom(i, 20, level/5)];
	}
	else
	{
	for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
	}
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query("jingli") < 30)
		return notify_fail("��ľ�����������ʬ������\n");
	me->receive_damage("jingli", 20);
	return 1;
}
string perform_action_file(string action)
{
	return __DIR__"tangshi-jianfa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	object weapon, weapon1; 
	weapon = me->query_temp("weapon");
	weapon1= victim->query_temp("weapon");
	if( !objectp(weapon) ) return;
	if (me->query_skill_mapped("sword")!="tangshi-jianfa" ||me->query_skill_mapped("parry")!="tangshi-jianfa") return;
  	
	if(!me->query_temp("tangshi/shiyin")) return;
  
	if(weapon && weapon1 &&random(10)>5)
    {
	   if(random(2))
		   message_vision(HIC"��Ȼ��$N����"+weapon->name()+HIC"��ƽ��"+weapon1->name()+HIC"��$n��"+weapon->name()+HIC"ʩչ��ȥ��ʽ����ʽ��\n"NOR, me,victim);
	   else 
		   message_vision(HIY"�����ţ�$N"+weapon->name()+HIY"һ�죬��ס"+weapon1->name()+HIY"��"+weapon->name()+HIY"��$n����ȫ�������෴�ķ���\n"NOR, me,victim);

	   if(random(me->query_str()) > victim->query_str()/3)
	   {           
           		me->add("neili", -50);
           		message_vision(HIR"$N��ʽ����ɬ�ͣ�"+weapon1->name()+HIR"����ס�����ַɳ���\n"NOR, victim);
           		weapon1->unequip();
           		weapon1->move(environment(victim));
        }
      	else {
           		message_vision(HIC"$N��ʽ����ɬ�ͣ��ֱ�����"+weapon1->name()+HIR"�������ס��\n"NOR, victim);
			    victim->add_busy(1);
       }
	   
	}
	if (random(me->query_skill("tangshi-jianfa",1))>victim->query_skill("parry",1)/2 
		&&random(10)>6)
	{
		message_vision(HIY"$N��Ȼ����ͻ�䣬һ�󼱲���"+weapon->name()+HIY",����һƬ��Ŀ�Ľ��⣬ʩչ�����̼�ʽ������ʽ��\n"NOR, me,victim);
		victim->receive_damage("qi",damage_bonus,me);
		victim->receive_wound("qi",damage_bonus/4,me);
		victim->apply_condition("no_exert",2);

	}
    
}

