// juehu-shou.c -��צ������

inherit SKILL;
#include <combat.h>
#include <ansi.h>
mapping *action = ({
([
	"action" : "$Nһʽ����ţ�����������ƻ�צ����ָ�繳�����۵ɵ�ͨ�죬ֱ��$n���ɲ�",
	"lvl" : 0,
	"skill_name" : "��ţ����",
	"damage_type" : "ץ��"
]),
([
	"action" : "$N��֫���أ�ͷ���״�������������������ͻȻ��֫����һ���Ѵܵ�$n���£������͵��ϴ�����һʽ����ƣ������",
	"lvl" : 130,
	"skill_name" : "��ƣ����",
	"damage_type" : "����"
]),
([
	"action" : "$N���ָ߸߾���������磬һʽ��׳ʿ���󡹣����۾ͳ�$n�����忳ȥ",
	"lvl" : 150,
	"skill_name" : "׳ʿ����",
	"damage_type" : "����"
]),
([
	"action" : "$NһԾ����ֱ��$n��˫�����£�˫����ס$n�ľ�����һŤ����˫�ֳɹ���֮�ƣ���$n���ɲ��ݺ���ȥ������һʽ����Ҷ�����",
	"lvl" : 180,
	"skill_name" : "��Ҷ���",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹһʽ����ǰ���󡹣�����һ��Ϊ������ֻ�����������ư㳯$n�ĺ������ɲ���ȥ",
	"lvl" : 250,
	"skill_name" : "��ǰ����",
	"damage_type" : "����"
]),
([
	"action" : "$Nȫ��ؽ�žž���죬�����ֽ��һʽ�����Ӿ��������ӥצץ��$nȫ��Ҫ����˲������ӥצ�ֺ�Ϊһצֱ��$n���ɲ�ץ��",
	"lvl" : 350,
	"skill_name" : "���Ӿ���",
	"damage_type" : "ץ��"
]),
([      "action":  "$Nȫ��ؽ�žž���죬�����ֽ��һʽ�����Ӿ��ץ��$n�����۲�λ��"  ,
         "lvl" : 200,
        "skill_name" : "����",
        "damage_type": "ץ��"
]),
([      "action":  "$N������ǰ����ץΪָ������$n��С�������ֱ��ƣ�����$n��������" ,
         "lvl" : 250,
        "skill_name" : "����",
        "damage_type": "����"
]),
([      "action": "$N����һš������Ȼ�ӿ죬��$n����׼����ǰ����ת��$n�ĺ󷽣�ץ��$n��˫����"  ,
         "lvl" : 300,
        "skill_name" : "˫��ժ��",
        "damage_type": "ץ��"
]),
});

mapping *action_jh = ({
([      "action": HIR "$Nȫ��ؽ�žž���죬�����ֽ��һʽ�����Ӿ��ץ��$n�����۲�λ��" NOR ,
        "force" : 0,
        "dodge" : 0,
        "lvl" : 200,
        "skill_name" : "����",
        "damage_type": "ץ��"
]),
([      "action": HIC "$N������ǰ����ץΪָ������$n��С�������ֱ��ƣ�����$n��������" NOR ,
        "force" : 0,
        "dodge" : 0,
         "lvl" : 150,
        "skill_name" : "����",
        "damage_type": "����"
]),
([      "action": MAG "$N����һš������Ȼ�ӿ죬��$n����׼����ǰ����ת��$n�ĺ󷽣�ץ��$n��˫����" NOR ,
        "force" : 0,
        "dodge" : 0,
        "lvl" : 100,
        "skill_name" : "˫��ժ��",
        "damage_type": "ץ��"
]),
});
int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_learn(object me)
{
	if(!me->query("quest/wudang/juehu")) return notify_fail("���书����������۷�����ϰ��\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����צ�����ֱ�����֡�\n");
	if ((int)me->query_skill("yinyun-ziqi", 1) < 40)
		return notify_fail("�����������򲻹����޷�ѧ��צ�����֡�\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������̫�����޷�����צ�����֡�\n");
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
	level   = (int) me->query_skill("juehu-shou",1);
	
    if (me->query_temp("wudang/juehu"))
	{
		for(i = sizeof(action_jh); i > 0; i--) {
		  if(level > action_jh[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				//"action": action_jh[j]["action"],
				"action":HIR+action[j]["action"]+NOR,
				"lvl": action_jh[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":150+random(300),
				"dodge":random(300),
				"parry":random(300),
				"damage":200+random(100),
			]);
		  }
	    }
	}
	else
	{
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":150+random(30),
				"dodge":random(30),
				"parry":random(30),
			]);
		  }
	 }
	}
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 40)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("���������������צ�����֡�\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	//me->add("shen", -100);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"juehu-shou/" + action;
}

mixed hit_ob(object me, object target, int damage_bonus)
{
        string msg;
		int i,j;
		i=me->query_skill("juehu-shou",1);
		j=me->query_skill("yinyun-ziqi",1);
		if (random(me->query_dex(1))>target->query_con(1)/2
		&& me->query_skill("juehu-shou",1)>350
		&& me->query_skill_mapped("hand")=="juehu-shou"
		&& me->query_skill_prepared("hand")=="juehu-shou"
		&& target->query("gender")=="����"
		&& !random(4)
		)   {
              msg = MAG"$N���һ�������к���������ֱ仢צ��ʹ��һ�С���ץ�֡���\n"NOR;
			  if (random(me->query_skill("hand",1)) > target->query_skill("parry",1)/2) {
                  msg += HIR"$Nһץ����ס$n�����ۣ�$n��������һ���ʹ�������̲�ס����һ����Ѫ��\n"NOR;      
                  target->start_busy(1+random(2));
				  target->receive_damage("qi",i+j*2,me);
				  target->receive_wound("qi",j/2,me);
                  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);  
				  target->apply_condition("juehu_busy",2);
				  target->apply_condition("juehu_hurt",2);
				  //target->set("gender","����");
			  }    
			   else {
                  msg += HIC"$nʶ����$N����ͼ�����һ�������˿�ȥ��\n"NOR;
				  me->add_busy(1+random(1));
				  }
              message_vision(msg, me, target);
        }
        return 1;
        
}
