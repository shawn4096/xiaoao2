// canglang-goufa.c ���˹���
// by aug   99.9.10
// �������֣�����sld�Ĺ��Ӻ���Ҳ����ô����
// �ĳ�dagger�������֣�olives����
// tenglong-dagger ����ذ��????����ôԽ������Խ��......
// modified by Olives@SJ 4/18/2001
// ������򽫼���6��pfm
// ������ν���������У�Ӣ����ʽ
// �ֱ��ڲ�ͬ��������ò�ͬ��pfm
// Update By lsxk@hsbbs 2007/6/6

inherit SKILL;
#include <ansi.h>
#include <combat.h>

mapping *action = ({
([
	"action":   "$N���β�����һ�С��������项������$wֱ��$n��˫Ŀ��ȥ",
	"lvl" : 0,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([
	"action":   "$Nһ�С��������������$w��Ӱ���Σ���$n��$l��ȥ",
	"lvl" : 40,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([
	"action": "$N�͵ظ���ǰ�壬һ�С�����������������$wֱ�ö��ϣ�ֱ��$n��ͷ����ȥ",
	"lvl" : 80,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([
	"action" : "$Nһ����ʹһ�С����ڻ�Ծ����$w����һ�е�����$n��$l",
	"lvl" : 100,
	"skill_name" : "��;ͬ��",
	"damage_type" : "����"
]),
([
	"action" : "$N����$w��󳷣�����ǰƽƽ����һ�С�����������$n��$l",
	"lvl" : 140,
	"skill_name" : "�������",
	"damage_type" : "����"
]),
([
	"action" : "$Nһת��$w���б����һ�С������鳲��������$n��$l",
	"lvl" : 160,
	"skill_name" : "�����鳲",
	"damage_type" : "����"
]),
([
	"action" : "$N�ҽ���ǰһ������ϥ����һ�С�����Ϸ���$w��ǰ�Ϸ�����$n��$l",
	"lvl" : 180,
	"skill_name" : "����Ϸ��",
	"damage_type" : "����"
]),
([
	"action" : "$N���λζ��������ϣ�����$n�Ļ��У�һ�С�������衹����$w�ݺݴ���$n���ؿڡ�",
	"lvl" : 200,
	"skill_name" : "�������",
	"damage_type" : "����",	
]),
});

int valid_enable(string usage) { return usage == "dagger" || usage == "parry"; }

int valid_learn(object me)
{
	object weapon;
	if (me->query("family/family_name")!="������")
		return notify_fail("����ذ��ֻ�������̵���ʹ�á�\n");
	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "dagger")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	
	if ( me->query("max_neili") < 1000)
		return notify_fail("�������������\n");
	if ( me->query_skill("dulong-dafa", 1) < 100)
		return notify_fail("��Ķ����󷨻��̫ǳ���޷�ѧϰ����ذ����\n");
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
	//С�������⹥������һ��
	level = me->query_skill("tenglong-bifa",1);

	if(me->query_temp("sld/xiaolian"))
	{
		return ([
				"action": MAG"$N�ۼ����ж�ܲ������Դ�������Լ��ؿ����䣬˳���ڵ���һ��������$n���������������$w��$n�����������£�"NOR,
				"damage_type": "����",
				"force": 600 +random(350),
				"dodge": random(30)-10,
				"parry": random(20),
				"damage": 180 + random(140),
				"attack":150+random(100),
			]);
	}
	for(i = sizeof(action); i > 0; i--)
	{
		if(level > action[i-1]["lvl"]) 
		{
			j = NewRandom(i, 20, level/5);
            if (me->query_temp("tlbf/beautya")) 
			{
				msg = HIY+replace_string(action[j]["action"],"$w","$w"HIY)+NOR;
				return ([
					"action": msg,
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 +random(350),
					"dodge": random(30)+10,
					"parry": random(20)+30,
					"damage": 200 + random(100),
				]);
			}
			
			else if(me->query_temp("sld/pfm/xiaolian"))
			{
               msg = HIM+replace_string(action[j]["action"],"$w","$w"HIM)+NOR;
				return ([
                "action": msg,
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 200 +random(350),
				"dodge": random(30)+10,
				"parry": random(20)+30,
				"damage": 150 + random(100),
				]);
			}
           else {
            
              
				return ([
					"action": action[j]["action"],
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 +random(350),
					"dodge": random(30)+10,
					"parry": random(20)+30,
					"damage": 80 + random(100),
				]);
		   }
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("tenglong-bifa", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 50)
		return notify_fail("��ľ�������������ذ����\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("�����������������ذ����\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"tenglong-bifa/" + action;
}
int ob_hit(object ob, object me, int damage)
{
	int ap,dp,lvl;
	int i,jl,neili;
	object weapon;
	weapon=me->query_temp("weapon");
		
	lvl = me->query_skill("tenglong-bifa",1);	
	ap = (int)me->query("combat_exp");
	dp = (int)ob->query("combat_exp");
	
	if( me->query_temp("weapon")
	&& random(me->query_dex(1)) > ob->query_dex(1)/2
	 && random(ap) > dp/2
	 && random(lvl) > 200
	 && me->query("neili") > 800
	 && userp(me)
	 && !random(4)) {
		i = me->query_skill("parry", 1);
		jl = me->query("jiali");
		neili = me->query("neili");
		
		me->set_temp("sld/xiaolian", 1);
		me->set("jiali", me->query_skill("force") + 200);
		me->add_temp("apply/attack", lvl/2);
		me->add_temp("apply/strength", i/4);
		me->add_temp("apply/parry", i/5);
		me->set("xiaolian", jl);
		//damage = -damage;
		message_vision(HIR"\n$N�������Ȼ����$n�������ߣ���$nһʱ��Ϊ$N��ɫ�����˲�䣬����Ծ�𣬰γ����вص�"+weapon->query("name")+HIR"����$n!\n"NOR,me,ob);

		COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 3);
		if (me->query("neili") < neili)
			me->set("neili", neili-100);
		me->set("jiali", me->query("xiaolian"));
		me->delete_temp("sld/xiaolian");
		me->delete("xiaolian");
		me->add_temp("apply/attack", -lvl/2);
		me->add_temp("apply/strength", -i/4);
		me->add_temp("apply/parry", -i/5);
		return -damage;
	}
}
mixed hit_ob(object me, object target)
{
	string msg;
	object weapon=me->query_temp("weapon");
	
	if ( random(me->query_per(1)) >= target->query_per(1)/3
	 && random(10) > 5
	 && me->query("jingli") > 300
	 && weapon
	 && weapon->query("skill_type")=="dagger"
	 && target->query("gender")=="����"
	 && me->query_skill_mapped("dagger")=="tenglong-bifa"
	 && me->query_temp("tlbf/meihuo")
	 && random(me->query("combat_exp")) > random(target->query("combat_exp")/2)
	 && me->query("neili") > 500) 
     {
		   switch(random(3)) {
			case 0 :
				msg = HIM"$N��$n��ȻһЦ��üĿ�续����$n��������������������ֻ�����Լ���Ȼ����Ѫ��ӿ����Щ�����ᣡ\n"NOR;
				target->receive_damage("jing",1000+random(500),me);
				//target->receive_wound("qi",1000+random(500),me);
				break;
			case 1 :
				msg = HIY"$N�������İױ۶�$n����һ�㣬Ц��������������ѽ������$nֻ���Լ��ڸ�����,��ѪΪ֮һ�͡�\n"NOR;
			  	target->apply_condition("no_exert",1);
				target->receive_wound("qi",2000+random(1000),me);
				break;
			case 2 :
				msg = HIC"$N���־���������$n��˵��������ū�ҵ���ߺ������\n"NOR;
				msg += HIR"$nֻ�����Լ���Ѫ��ӿ���鲻�����ƣ�\n"NOR;

			  	target->add_busy(2);
				//target->receive_wound("qi",2000+random(1000),me);
				break;

		}
		message_vision(msg, me, target);
		
	}
}
/*
int post_action()
{
	object me,target;
	

}
*/