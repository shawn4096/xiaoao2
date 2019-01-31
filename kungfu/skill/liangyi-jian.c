// liangyi-jian.c (kunlun) �����������ǽ���
//update by cool 981104

#include <ansi.h>
inherit SKILL;
//mixed hit_ob(object me, object victim, int damage_bonus, int factor);

mapping *action = ({
([
	"action":"$Nһʽ��˳ˮ���ۡ���$N����$wָ���Լ����ؿڣ�����бб�����⣬��������$n��$l",
	"lvl" : 0,
	"skill_name" : "˳ˮ����",
	"damage_type":"����"
]),
([
	"action":"$N����΢�࣬���ֺ�ڣ�����$wһ�С���ɨǧ������ֱ��$n�������ȥ",
	"lvl" : 10,
	"skill_name" : "��ɨǧ��",
	"damage_type":"����"
]),
([
	"action":"$N�����ǰ��$w��Ȼ���䵯�������ⱬ����һ�С��ͱڶ��ơ����͵ش���$n���ؿ�",
	"lvl" : 20,
	"skill_name" : "�ͱڶ���",
	"damage_type":"����"
]),
([
	"action":"$N�������������ƽ�ƶ�������ָ���������ֽ����첻����һ�С�����ָ·��������$n",
	"lvl" : 40,
	"skill_name" : "����ָ·",
	"damage_type":"����"
]),
([
	"action":"$N���к��䣬ʹ��һ�С����ɻ�����ȫ��б�ƣ����߰���б����ż����Ю��һ�����ƣ����˼���׽��",
	"lvl" : 60,
	"skill_name" : "���ɻ�",
	"damage_type":"����"
]),
([
	"action":"$N����$w�������𣬷�����£�һ�С���Įƽɳ�������ߵ��ƣ�����$n��$l",
	"lvl" : 80,
	"skill_name" : "��Įƽɳ",
	"damage_type":"����"
]),
([
	"action":"$Nһ�С�ľҶ��������$N����$w������бָ���죬���϶��£�����$n��$l",
	"lvl" : 100,
	"skill_name" : "ľҶ����",
	"damage_type":"����"
]),
([
	"action":"$N��ǰһ����$w΢΢�����������㣬һ�С����Ӳ��ߡ����ն���ʼ�����಻������$n",
	"lvl" : 120,
	"skill_name" : "���Ӳ���",
	"damage_type":"����"
]),
([
	"action":"$N���ֽ���һ�٣�������ʯ�⣬һ�С��������ơ����ý�����ס$n���б�����$wֱָ$n���ʺ�",
	"lvl" : 140,
	"skill_name" : "��������",
	"damage_type":"����"
]),
([
	"action":"$N����ؽ�������б����һ�С����ɷ��١�������Ӱ����ֱк��������ס$n�Ϸ�",
	"lvl" : 160,
	"skill_name" : "���ɷ���",
	"damage_type":"����"
]),
([
	"action":"$Nһʽ��ѩӵ���š���$N���н������ţ�һ����������������$n",
	"lvl" : 180,
	"skill_name" : "ѩӵ����",
	"damage_type":"����"
]),
([
	"action":"$N�ڿն���ͻȻʹ��һ�С�������ɫ����������Ϣ�ؼ���$n�ı�����ȥ",
	"lvl" : 200,
	"skill_name" : "������ɫ",
	"damage_type":"����"
]),
});
mapping *action_fh = ({
([
	"action":"$Nһʽ�����ɻ�����$N����$w��Ȼ��бת������Ȼ����һʽ�����ǽ�����ʽ��$w��������$n��$l",
	"lvl" : 200,
	"skill_name" : "���ɻ�",
	"damage_type":"����"
]),
([
	"action":"$Nһʽ����ں�Ҷ����$w��˫�������󣬳ʹ�̬֮����Ȼ�ɿ�����бת����$w����һ�����⣬����$n��$l",
	"lvl" : 250,
	"skill_name" : "��ں�Ҷ",
	"damage_type":"����"
]),
([
	"action":"$Nһʽ����Ҷ��ҡ����$w��Ȼ������Ϊ����̬֮���������������ѿ�׼���ƣ�$w���һ����Ȼ�����$n��$l",
	"lvl" : 250,
	"skill_name" : "��Ҷ��ҡ",
	"damage_type":"����"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;
	if (!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ( me->query("max_neili") < 1000)
		return notify_fail("�������������\n");
	//if ( me->query("family/master_id")!="he zudao"||me->query("family/master_name")!="�����")
	//	return notify_fail("��ò�����������Դ��ڣ��޷���ϰ���ǽ���\n");
	if ( me->query_skill("xuantian-wuji", 1) < 160)
		return notify_fail("��������޼������̫ǳ��\n");

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
	int i,level,j,n;
    string msg;
	level = (int) me->query_skill("liangyi-jian",1);
	//���ɻ���������������ɱ��
	for (i = sizeof(action_fh); i > 0; i--) {
		if (level >= action_fh[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			if( me->query_temp("lyj/feihua1") ) {
				return ([
					"action": HIR+replace_string(replace_string(replace_string(action_fh[j]["action"], "$w", "$W"), "$W", "$w"HIR), NOR, HIR)+NOR,
					"lvl": action_fh[j]["lvl"],
					"damage_type": action_fh[j]["damage_type"],
					"force": 200 +random(350),
					"dodge": random(30)-10,
					"parry": random(20),
					"damage": 200 +random(50),
				]);
			}
		}
	}

//�ͱڶ���
       if( intp(n = me->query_temp("lyj/duanyun")) && n > 0 ){
                switch(n){
                   case 4: msg = WHT"$n��������ƫ�󣬼�������ת����ֻ��һɲ��$N�����Ȼ��������ȻɲʱϮ�����ף�"NOR;break;
                   case 3: msg = WHT"$n��������ƫ�ң���������ת����ֻ��һɲ��$N�����Ȼ��������ȻϮ�����ף�"NOR; break;
                   case 2: msg = WHT"$n��������ƫ�ϣ���������ת����ֻ��һɲ��$N�����Ȼ��������ȻϮ������"NOR;break;
                   case 1: msg = WHT"$n��������ƫ�£���������ת����ֻ��һɲ��$N�����Ȼ��������ȻϮ������"NOR; break;
				   default:break;
                }
				n=n-1;
                return ([
                        "action":msg,
                        "damage_type":"����",
                        "dodge": 20,
				    	"damage":me->query("xtwj/wuji")?(200+random(50)):(120+random(50)),
                       
						"force": level + me->query("jiali"),
                        "skill_name" : "�ͱڶ���",
                ]);
        }

	 for (i = sizeof(action); i > 0; i--) {
		if (level >= action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
		//Ѹ��
		if( me->query_temp("lyj/xunlei1") ) {
				return ([
					"action": WHT+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"WHT), NOR, WHT)+NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 +random(350),
					"dodge": random(30)-10,
					"parry": random(20),
					"damage": 180 +random(50),
				]);
		}
		if( me->query_temp("lianhuan") ) {
				return ([
					"action": BLU+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"BLU), NOR, BLU)+NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 +random(350),
					"dodge": random(30)-10,
					"parry": random(20),
					"damage": 180 +random(50),
				]);
		}
		if( me->query_temp("ly_hebi") ) {
				return ([
					"action": HIC+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIC), NOR, HIC)+NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 +random(350),
					"dodge": random(30)-10,
					"parry": random(20),
					"damage": 140 +random(50),
				]);
			}
		if( me->query_temp("lyj/feihua") ) {
				return ([
					"action": HIC+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIC), NOR, HIC)+NOR,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 +random(350),
					"dodge": random(30)-10,
					"parry": random(20),
					"damage": 120 +random(50),
				]);
			}
		return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 200 +random(350),
				"dodge": random(30)-10,
				"parry": random(20),
				"damage": 80 +random(140),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("liangyi-jian", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("neili") < 20)
		return notify_fail("����������������ǽ�����\n");
	if ( me->query("jingli") < 50)
		return notify_fail("����������������ǽ�����\n");
	me->receive_damage("jingli", 40);
	me->add("neili",  -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"liangyi-jian/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int i;
	string msg;
	object weapon,weapon2;
	weapon=me->query_temp("weapon");
	weapon2=present("blade",me);
	i = me->query_skill("liangyi-jian",1)/5;
	if (me->query_skill_mapped("sword")!="liangyi-jian")
		return 0;
	
	if( me->query_temp("ly_hebi")
	 && !me->query_temp("hebi_hit") 
	 && random(10) > 5
	 && me->query_skill_mapped("parry") == "liangyi-jian") {
		me->set_temp("hebi_hit", 1);
		me->add_temp("apply/attack", i);
		COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 1);  
		me->add_temp("apply/attack", -i);
		me->delete_temp("hebi_hit");
	}
	//���ǽ�--���Ǿ�
   if( me->query_temp("lyj/liangyi")
	 &&	objectp(weapon2)
	 && random(10) > 7
	 && me->query_skill_mapped("sword") == "liangyi-jian"
	 && me->query_skill_mapped("parry") == "liangyi-jian") 
	{		
		
		switch (random(5))
		{
			case 0:
				message_vision(HIB"$N���һ�������ȵ������������ǣ�����һ�ơ������ִӱ������ó�һ��"+weapon2->query("name")+HIB",Ȼ��ӵ��ӱ��󷴻��˸����Σ�����������ն��$n��\n"
								HIC+"$N��Ϊ�������Ǿ�Ҫ�죬����ֽӿڵ�����̫�����ȣ����Ǻϵ¡������ֽ�����"+weapon->query("name")+HIC"����ԴԴ�����ݳ���\n"NOR,me,victim);
				if (random(me->query("combat_exp"))>victim->query("combat_exp")/2)
				{
					message_vision(HIY"$N�������ǽ��ͷ����ǵ�����ʽ�����һ�����ϵ������޷죬����һ����һ����į��ͻȻ��������֪�����ϲ����$n��ʱ��æ����������\n"NOR,me,victim);
					victim->add_busy(2);
					victim->apply_condition("no_exert",2);
				}
				break;
			case 1:
				message_vision(HIB"$N�����ǵ���������������ٲ����������ֵ�"+weapon2->query("name")+HIB",���ƹ�֮������Ȼ�������Ѿ�ʩչ�˷����ǵĵļ��£������ཻ��\n"
									HIC+"$N����"+weapon->query("name")+HIC"���е��ַ�Ѹ�����ף������ǽ���'����ɽ�'����һ˲֮ǰ��������$n��ͷ������ߡ�$n��ʱ�󾪡�\n"NOR,me,victim);
		        victim->receive_damage("qi",damage_bonus,me);
				message_vision(HIR"$nһʱ����Ϊ$N�������ǽ������ˣ�\n"NOR,me,victim);
				victim->receive_wound("qi",damage_bonus/4,me);
				message_vision(HIY"������$N�����ֿ�����$n�ı۰�\n"NOR,me,victim);
				
				break;

			case 2:
				message_vision(HIB"$N����"+weapon2->query("name")+HIB"�����ǵ����й��У�����"+weapon->query("name")+"�������ǽ����������$n����·��,\n"
								+"���ǽ��������ǵ�����Ȼ�����б𣬵����ǴӰ����л������ٻع���ԣ���˵����;��ͬ�顣һ��һ��ԽʹԽ˳�֣�����˫����ϵ������ޱȡ�\n"NOR,me,victim);
				victim->apply_condition("no_perform",2);
				message_vision(HIG"$nֻ����ǰ�����Ҿ�Ϊ���Ǿ����������޷����У�\n"NOR,me,victim);

				break;
			case 3:
				message_vision(HIB"���ǻ��������󻯰��ԣ�����˰���ʮ���У�������ϣ���ʮ��������ʮ�ı�֮��������ǧ���ʮ���ֱ仯��\n"NOR,me,victim);
				message_vision(HIY"$nֻ����ǰ�����Ҿ�Ϊ���Ǿ����������޷����У����������һƬ��Ļ������˷������ܰ�Χ��\n"NOR,me,victim);
				victim->add_busy(1);
				COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);  
				COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3); 
				break;
			case 4:
				message_vision(HIB"$N������������ض�λ��ɽ��ͨ�����׷��ౡ��ˮ�����䣬�������������˳��֪�����桰��\n"
								+"ͬʱ�������ǽ���������λ��Ǭλ��˳���������ǵ������Ƿ��������֮��������Բ���з���������ɡ�\n"NOR,me,victim);
				message_vision(HIG"$n���д󼱣������ͻ����ÿһ����Ϊ$N������������þ�������\n"NOR,me,victim);

				victim->receive_damage("jingli",damage_bonus/2,me);
				victim->receive_damage("jing",damage_bonus/4,me);
				break;
		}
/*
		me->add_temp("apply/attack", i);
		me->add_temp("apply/sword", i);
		me->add_temp("apply/damage", i);
		message_vision(HIR"$N���еĽ���ȫ����Ϊ����бб��������Щб�ƽ����ж�Ȼ�����һ�������ƣ���$n����ʤ����\n"NOR,me,victim);
		victim->add_busy(1);
		COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);  
		me->add_temp("apply/attack", -i);
		me->add_temp("apply/sword", -i);
		me->add_temp("apply/damage", -i);	*/
		


	} 


}

