// longzhua-gong.c -��צ��

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "ֻ�����ꡱ��һ�������������$Nʹһ�С�����ʽ����������Ȼ̽����ȥ����������",
	"lvl"   : 0,
	"skill_name" : "����ʽ" ,               
	"damage_type" : "ץ��"
]),
([
	"action" : "$N������𣬶������糤�羪�죬һ�С�׽Ӱʽ������ʸӦ��������Ͼ��",
	"lvl"   : 10,
	"skill_name" : "׽Ӱʽ" ,               
	"damage_type" : "ץ��"
]),
([
	"action" : "$N����һ����ʹ��������ʽ����ʮָ΢΢���¶����������ཻ�ġ����ڡ�����ʱ���緱�Ҽ���һ��",
	"lvl"   : 20,
	"skill_name" : "����ʽ" ,               
	"damage_type" : "ץ��"
]),
([
	"action" : "$N�߶�������˫צ����ʹ������ɪʽ�����������಻��������������ˮһ��",
	"lvl"   : 40,
	"skill_name" : "��ɪʽ" ,               
	"damage_type" : "ץ��"
]),
([
	"action" : "$Nʹһ�С�����ʽ���������ݺῪ�أ��������ۣ��͵ػ���$n��$l",
	"lvl"   : 60,
	"skill_name" : "����ʽ" ,               
	"damage_type" : "ץ��"
]),
([
	"action" : "$N��շ������ִ�������������һ�С�����ʽ������$n��$l",
	"lvl"   : 80,
	"skill_name" : "����ʽ" ,               
	"damage_type" : "ץ��"
]),
([ 
	"action" : "$N���н��ƣ�һ�С�����ʽ����ֱȡ$n$l��ÿһצ����ʯ���쾪���������֮��",
	"lvl"   : 100,
	"skill_name" : "����ʽ" ,               
	"damage_type" : "ץ��"
]),
([
	"action" : "$N������ת�����������צ��һ�С�����ʽ�����ƿ�֮����������",
	"lvl"   : 120,
	"skill_name" : "����ʽ" ,               
	"damage_type" : "ץ��"
]),
/*
([
	"action" : "$N�ǽڡ���������һ���죬�ֱ�ͽ����ߣ�һ�С�����ʽ������ָ��Ȼ����$n��ǰ��Ѩ",
	 "lvl"   : 150,
	"skill_name" : "����ʽ" ,               
	"damage_type" : "ץ��"
]),
([ 
	"action" : "$N�͵�һ�����ƣ�צ�����䣬һ�С���ȱʽ�������滺��������ȴ����ǿ��",
	"lvl"   : 180,
	"skill_name" : "��ȱʽ" ,               
	"damage_type" : "ץ��"
])
*/
});

int valid_enable(string usage) { return usage=="claw" ||  usage=="parry"; }

int valid_combine(string combo) 
{
	object me;
	me = this_player(); 

	if ( me->query_int(1) > 40)
		return combo=="yizhi-chan"; 
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����צ��������֡�\n");
	if ((int)me->query_skill("yijin-jing", 1) < 60)
		return notify_fail("����׽�ڹ���򲻹����޷�ѧ��צ����\n");
	if ((int)me->query_int(1) > 30) {
		return 1;
	}
	else {
		if ( me->query_skill("banruo-zhang", 1)
		 && me->query_skill("yizhi-chan", 1)
		 && me->query_skill("jingang-quan", 1)
		 && me->query_skill("nianhua-zhi", 1)
		 && me->query_skill("qianye-shou", 1)
		 && me->query_skill("ruying-suixingtui", 1)
		 && me->query_skill("sanhua-zhang", 1))
			return notify_fail("��Ĺ����������޷�ͬʱѧϰ�������ϵ��ϳ˹���\n");
	}
	if ((int)me->query("max_neili") < 600)
		return notify_fail("�������̫�����޷�����צ����\n");
	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action); i > 0; i--)
		if(level >= action[i-1]["lvl"])
			return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, j, level;
	string msg;
	
	level = (int) me->query_skill("longzhua-gong",1);
	for(i = sizeof(action); i > 0; i--) 	{
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			/*
			if(me->query_temp("baocan")) {
				switch(me->query_temp("baocan")) {
					case 2: msg = HBRED"$N����������ɽ���ƺ����������ٳ�����æ���ң���ʵ����ʵ����������׾��ÿһ�������ж������������ޱȵ����塣\n"NOR; break;
					case 1: msg = HIR"$N�ۼ��Է���������Χ����Ҳ����ȫ����ˣ�����˫�ƻػ�����ȻȦת������һ�죬��$n�����ϻ�����ȥ��\n"NOR; break;
					default: msg = RED"$N����������ɽ���ƺ����������ٳ�����æ���ң���ʵ����ʵ����������׾��ÿһ�������ж������������ޱȵ����塣\n"NOR;break;
				}
				me->add_temp("baocan", -1);      
				return ([
					"action": msg, 
					"force" : 200 + random(300),
					"dodge": random(35),
					"parry": random(35),
					"damage": 200 + random(200),//������ȱ�Ǿ���
					"damage_type" : "ץ��",
				]);
			}*/
           
			if( me->query_temp("lzg/lianhuan"))
			{	        
								
			 return ([  
					"action":RED+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"RED), NOR, RED)+NOR,
					"lvl" : action[j]["lvl"],
					"force" : 120 + random(250) ,
					"dodge": random(25) ,
					"damage":100 + random(80),
					"parry": random(25),//ԭ����15
					"weapon" : random(2)?"צ��":"ָ��",
					"damage_type" : random(2)?"����":"ץ��",
				]);
			}
			return ([
				"action": action[j]["action"],
				"damage_type": action[j]["damage_type"],
				"lvl": action[j]["lvl"],
				"force": 150 + random(300),
				"damage":80 + random(80),
				"dodge": random(30),
				"parry": random(30),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("longzhua-gong", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 40)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("���������������צ����\n");
	if ( me->query_skill("buddhism") < 220)
	{
		if ( me->query_skill("banruo-zhang", 1)
		 || me->query_skill("ruying-suixingtui", 1)
		 || me->query_skill("jingang-quan", 1)
		 || me->query_skill("nianhua-zhi", 1)
		 || me->query_skill("qianye-shou", 1)
		 || me->query_skill("sanhua-zhang", 1))
			return notify_fail("��ķ��������������޷�ͬʱ��ϰ�������ϵ��ϳ˿��ֹ���\n");
	}

	me->receive_damage("jingli", random(30));
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"longzhua-gong/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        string msg;
		//if (me->query_skill_mapped("finger")!="yizhi-chan" && me->query_skill_prepared("finger")!="yizhi-chan")
		  // return 0;
		int lvl = me->query_skill("yijin-jing",1)/3+ me->query_skill("longzhua-gong",1);
        if (random(lvl) > 200 
			&& random(10)>5
			&& random(me->query_str(1)) > victim->query_str(1)/2
			&& me->query_skill_mapped("finger")=="yizhi-chan"
			&& me->query_skill_prepared("finger")=="yizhi-chan"
			&& !victim->query_temp("must_be_hit")) {
                //victim->set_temp("must_be_hit", 1);
                me->add_temp("baocan",3);
				me->add_temp("shouque",3);
				//
                //call_out("remove_effect",1, victim);
               // message_vision(HBMAG"$n��$Nһ�����籩���Ľ���Ū����ͷת�򣬸����ֲ�������Ϊʵ������Ϊ�飡\n"NOR, me, victim);
                message_vision(HBMAG"$N����£�����У���Ȼ��צΪָ��ͻȻһָ���������������ʮ�������е�һָ������\n"NOR, me, victim);
				if (random(me->query_skill("finger",1))>victim->query_skill("dodge",1)/4)
				{
					message_vision(YEL"$nһ���䲻����Ϊ$N��ͻȻ������һָ������Ѩ�������β��ɵ�һ�ͣ�\n"NOR, me, victim);
					victim->add_busy(1+random(2));
					victim->apply_condition("yzc_qiankun",1);
				}else 
                 message_vision(HIW"$n���з�����̧��������ȭ��ӭ������һ�У���$N��һָ�������������Ρ�\n"NOR, me, victim);
				
        }
		else{
		
		switch (random(2))
		{
		  case 0:
               if (me->query_temp("baocan")&&me->query("quest/sl/yjj/powerup"))
		       {
                  message_vision(HBRED"$N����ʽ������"+HIY"����ʽ����ȱʽ"NOR+HBRED"���⾳�󣬸����׽�ĸ���������������Ϊ���棬�Ѵ��似�ķ�豹���֮�⡣\n"NOR, me, victim);
                  victim->set_temp("must_be_hit", 1);
				  me->add_temp("apply/damage",(me->query_skill("yijin-jing",1)+lvl));
		          COMBAT_D->do_attack(me,victim, me->query_temp("weapon"), 3);
		          me->add_temp("apply/damage",-(me->query_skill("yijin-jing",1)+lvl));
				  victim->delete_temp("must_be_hit");
	    	   }
		break;
		case 1:
		  if (me->query_temp("shouque")&& random(20)>8&&userp(me))
	    	{
               msg=random(2)?MAG"$N����������ɽ��"+HIY"��ȱʽ"+MAG"�ƺ����������ٳ�����æ���ң���ʵ����ʵ����������׾��ÿһ�������ж������������ޱȵ����壡\n"NOR:
			   HIC"$N����ʶʩչ��"+HIC"����ʽ"NOR+HIC"����ʽ����$nȦ������У�$n������Ҳ����ȫ����ˡ�\n$N˫צ�ػ�����ȻȦת������һ�죬��$n�����ϻ�����ȥ��\n"NOR;
		       if (random(me->query_int())> victim->query_int()/2)
		        {
			     msg +=HIY"$n�پ�һ�ɴ��������������������ȣ��ؿ���Ѫ���ڲ��ѡ�\n"NOR;
			     victim->receive_damage("qi",lvl,me);
			     victim->receive_wound("jing",lvl,me);			   
		        }
		       else msg +=HIW"$nʶ����$N����ͼ���������һ�ݣ��ܹ���$N���������塣\n"NOR;
		       message_vision(msg,me,victim);
		  
		     }
		break;
		
		}	
	}
		
}

void remove_effect(object victim)
{
        if (!victim) return;
        victim->delete_temp("must_be_hit", 1);
}

