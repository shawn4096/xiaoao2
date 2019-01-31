// canglang-goufa.c ���˹���
// by aug   99.9.10

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([
	"action" : "$N˫�Ų�������������һ�С���Ҷ���ҡ���$w��ǰƽ��$n�ĵ���",
	"lvl" : 0,
	"skill_name" : "��Ҷ����",
	"damage_type" : "����"
]),
([
	"action" : "$Nһ�С�Ⱥħ���衹��$w�趯��סȫ����$nײȥ",
	"lvl" : 40,
	"skill_name" : "Ⱥħ����",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹһ�С�������թ�����ҽ����س���$w�������Һ󳷣�ͻȻ����ǰ������$n������",
	"lvl" : 80,
	"skill_name" : "������թ",
	"damage_type" : "����"
]),
([
	"action" : "$Nһ�С���·ͬ�项��$w�й�ֱ����һ��һ�´���$n���Ҽ�",
	"lvl" : 100,
	"skill_name" : "��·ͬ��",
	"damage_type" : "����"
]),
([
	"action" : "$N����$w��󳷣�����ǰƽƽ����һ�С�����������$n������",
	"lvl" : 140,
	"skill_name" : "�������",
	"damage_type" : "����"
]),
([
	"action" : "$Nһת��$w���б����һ�С��ɺ�λ���������$n�����",
	"lvl" : 160,
	"skill_name" : "�ɺ�λ�",
	"damage_type" : "����"
]),
([
	"action" : "$N�ҽ���ǰһ������ϥ����һ�С�������������$w��ǰ�Ϸ�����$n�ĺ���",
	"lvl" : 180,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([
	"action" : "$Nһ����ʹһ�С��������ơ���$w����һ�е�����$n������",
	"lvl" : 200,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "hook" || usage == "parry"; }

int valid_learn(object me)
{
	object weapon;
	if (me->query("family/family_name")!="������" )
		return notify_fail("���˹���ֻ�������̵���ʹ����̡�\n");
	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "hook")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query("max_neili") < 50)
		return notify_fail("�������������\n");
	if ((int)me->query_skill("dulong-dafa", 1) < 20)
		return notify_fail("��Ķ����󷨻��̫ǳ���޷�ѧϰ���˹�����\n");
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
	int i,level,temp,j;
	object target;
	object *enemy;
        level = me->query_skill("canglang-goufa",1);

	enemy = me->query_enemy();
	if(sizeof(enemy) > 0) {
		target = enemy[random(sizeof(enemy))];
		temp = target->query_skill("dodge");
		if (!temp) temp=1;

		i = me->query_skill("hook",1)*100 / temp;
		if( i > 200) i=200;
		if( i < 50) i=50;
		if ( random(300) < (50+i) && me->query("neili") > 500 && !random(4))
			if ( me->query_skill_prepared("leg")=="shenlong-tuifa"
			 && me->query_skill("dulong-dafa",1) > 450 
			 && me->query_skill("canglang-goufa",1) > 450 
			 && me->query_skill("huagu-mianzhang",1) > 450 
			 && me->query_skill_mapped("force")=="dulong-dafa" )
				call_out("autopfm",1,me,target);
	}
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 150 +random(300),
				"dodge": random(30),
				"parry": random(30),
				"damage": 60 + random(100),
			]);
		}
	}
}

mixed hit_ob(object me, object target)
{
	string msg;
	object tweapon;
	object weapon=me->query_temp("weapon");
	object *inv;

	if (!weapon||!target) return;
	tweapon=target->query_temp("weapon");

	if ( random(me->query_str(1)) >= target->query_str(1)/3
	 && random(10) > 5
	 && me->query("jingli") > 300
	 && weapon
	 && weapon->query("skill_type")=="hook"
	 && me->query("gender")=="����"
	 && me->query_skill_mapped("hook")=="canglang-goufa"
	 && me->query_temp("clgf/canglang")
	 && random(me->query("combat_exp")) > random(target->query("combat_exp")/2)
	 && me->query("env/���˹���")=="��" 
	 && me->query("neili") > 500) 
     {
		 
		   
		   
		   switch(random(5)) 
		  {
			case 0 :
				if (tweapon)
				{
					message_vision(HIM"$N������أ�����"+weapon->query("name")+HIM"�Ĺ�ͷ��ס�Է���"+tweapon->query("name")+HIM"б��һ����\n"NOR,me,target);
					if (random(me->query_skill("canglang-goufa",1))>target->query_skill("parry",1)/2)
					{
						message_vision(CYN"$N����һ�ɴ��������������ѳֲ�ס�����б������ֶ�����\n"NOR,target);
						tweapon->move(environment(target));
					}

				}else {
					message_vision(HIR"$N������أ�����"+weapon->query("name")+HIR"�Ĺ�ͷ��ס$n�ķ��߹ؼ����ϣ�б��һ������ʱ���Է��ķ��߻��ƣ�\n"NOR,me,target);
					target->receive_damage("qi",2000+random(500),me);
					target->receive_wound("qi",1000+random(500),me);
				}
				
				break;
			case 1 :
				message_vision(HIW"$N˫�����٣�����һ��Ȼ��������Ȼһ����������Ϊ���ͣ�\n"NOR,me);
				if (tweapon&&weapon->query("sharpness")>tweapon->query("rigidity"))
				{
					message_vision(WHT"\n���$n����"+tweapon->query("name")+WHT"Ӧ�ֶ��ϣ�\n"NOR,me,target);
					tweapon->unequip();
					tweapon->move(environment(target));
					tweapon->set("name", "�ϵ���" + tweapon->query("name"));
					tweapon->set("value", 49);
					tweapon->set("weapon_prop", 0);
					target->reset_action();
				
				}else{
					message_vision(WHT"\n��Ȼ����������͵�б����ʽ�����ִټ�ȴҲΪ��ͷ���ˣ�\n"NOR,me,target);

					target->apply_condition("no_exert",1);
					target->receive_wound("qi",2000+random(1000),me);
				}
				break;
			case 2 :
				message_vision(HIC"$N�����е�˫��һ��һ�����γ�һ�ɾ޴������֮����$nһ��վ�����ȣ�����ת���������������ݣ�����\n"NOR,me,target);
				message_vision(HIR"$nֻ�����Լ�������ת�������޷����ƣ�\n"NOR,me,target);

			  	target->add_busy(2);
				target->receive_wound("jing",1000+random(1000),me);
				break;
			default:break;

		}
			
		
	}
	
}

void autopfm(object me,object target)
{
	object weapon,weapon1;
	int i;

	if(!me || !target ) return;
	weapon = me->query_temp("weapon");
	weapon1 = target->query_temp("weapon");  
	
	if(!weapon) return;
	if ( me->add("neili",-75) <0 ) me->set("neili",0);

	i = me->query_skill("canglang-goufa", 1);
	me->add_temp("apply/attack",i/4);
	//if (!me->query("quest/sld/clgf/canglang/pass")) return;
	
	if (me->query("env/���˹���")=="��")
	{
	
		if(target->query_temp("weapon"))
		{
			message_vision(HIC"\n$N����"+weapon->query("name")+HIC"�������ġ�������У�$nһ��û����͸���ס�˱�����\n$N�˻������������ƣ�"NOR,me,target);
			weapon1->move(environment(me)); 
			weapon->unequip(); 
			if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, 0, random(3)?1:3);
			if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, 0, random(3)?1:3);
			if (me->is_fighting(target) && random(2)==1) COMBAT_D->do_attack(me, target, 0, 3);
			weapon->wield(); 
		}
		else {
			message_vision(HIC"\n$N����"+weapon->query("name")+HIC"�������ġ�������У�$nһ��û����͸�$N��ס���ֽţ�\n$N�˻���������$n���ƣ�"NOR,me,target);
			weapon->unequip(); 
			if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, 0, 1);
			if (me->is_fighting(target) && random(2)==1) COMBAT_D->do_attack(me, target, 0, 3);
			weapon->wield(); 
		}
	}
	me->add_temp("apply/attack",-i/4);
}

int practice_skill(object me)
{
	int lvl = me->query_skill("canglang-goufa", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

        if ((int)me->query("jingli") < 40)
                return notify_fail("����������������˹�����\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("����������������˹�����\n");
        me->receive_damage("jingli", 30);
        me->add("neili", -10);
        return 1;
}

string perform_action_file(string action)
{
	return __DIR__"canglang-goufa/" + action;
}
