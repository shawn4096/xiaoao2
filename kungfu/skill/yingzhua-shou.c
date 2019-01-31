// qingzhua-shou.c ӥצ������
#include <ansi.h>
inherit SKILL;
mixed hit_ob(object me, object target, int damage);

string *xue_name = ({ 
"�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
"����Ѩ","����Ѩ","���Ѩ","�Ϲ�Ѩ","��ԨѨ","�쾮Ѩ","��ȪѨ","����Ѩ","����Ѩ",
}); 

string *limb=({
"����","����","����","ͷ��","С��","�ؿ�","����","�ɲ�","�Ҽ�","�ұ�","�ҽ�",
});
mapping *action = ({
([
	"action" : "$Nһʽ��������ߡ�������̧�����ְ��أ�ͻȻ����$n��$l",
	"lvl" : 0,
	"skill_name" : "�������",
	"damage_type" : "����"
]),
([
	"action" : "$N����һ�Σ�һʽ��˫����֡�����������$n�ļ�ͷ����ȭ����$n���ؿ�",
	"lvl" : 10,
	"skill_name" : "˫�����",
	"damage_type" : "����"
]),
([
	"action" : "$Nһʽ����ӥ��צ����˫�ֻ�£��צ�����ֻ��壬���ֿ���$n��$l",
	"lvl" : 20,
	"skill_name" : "��ӥ��צ",
	"damage_type" : "ץ��"
]),
([
	"action" : "$N����ס��һ����һ��б����ʽ��һʽ������չ�᡹��������$nɨ��",
	"lvl" : 30,
	"skill_name" : "����չ��",
	"damage_type" : "ץ��"
]),
([
	"action" : "$Nʹһʽ����ȸ���᡹��һ��������ŷ�����$n���ɲ���ȥ",
	"lvl" : 40,
	"skill_name" : "��ȸ����",
	"damage_type" : "����"
]),
([
	"action" : "$N����һ�죬һʽ��Գ����֡����ֱ�ͻȻ������������$n��$lһ��",
	"lvl" : 50,
	"skill_name" : "Գ�����",
	"damage_type" : "ץ��"
]),
([
	"action" : "$N˫�ֱ�ȭ��һʽ�����ڷɻ����������������ĳ���Ʈ�ݾ��ڵ�����$n��$l",
	"lvl" : 60,
	"skill_name" : "���ڷɻ�",
	"damage_type" : "����"
]),
([
	"action" : "$Nһʽ�����ɻ�����������������бб������бб������$n��$l",
	"lvl" : 70,
	"skill_name" : "���ɻ�",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��ӥצ�����ֱ�����֡�\n");
	if ( !me->query_skill("jiuyang-shengong", 1))
	if ( me->query_skill("shenghuo-shengong", 1) < 20)
		return notify_fail("���ʥ���񹦻�򲻹����޷�ѧ��ӥצ�����֡�\n");
	if ( me->query("max_neili") < 100)
		return notify_fail("�������̫�����޷���ӥצ�����֡�\n");
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
	level   = (int) me->query_skill("yingzhua-shou",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			if (me->query_temp("yzs/yingyang"))
			{
				return ([
				"action": HIY+action[j]["action"]+NOR,
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 150 +random(300),
				"damage":me->query("mj/quest/yzs")?180+random(80):130+random(50),
				"dodge": random(30),
				"parry": random(30),
				]);

			}
			
			return ([
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
				"force": 150 +random(300),
				"damage":100+random(50),
				"dodge": random(30),
				"parry": random(30),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("yingzhua-shou", 1);
	int i = sizeof(action);
	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 30)
		return notify_fail("��ľ���̫���ˡ�\n");
	if ((int)me->query("neili") < 10)
		return notify_fail("�������������ӥצ�����֡�\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -5);
	return 1;
}
mixed hit_ob(object me, object target, int damage)
{
     object weapon = me->query_temp("weapon");
	 string msg,name,dodge_skill,limb;
	 int ap,dp,lvl;
	 if (!me || !target) return;
	 lvl=me->query_skill("yingzhua-shou", 1);
     if( me->query_skill("yingzhua-shou",1 ) > 200
	 	 && me->query_skill_mapped("hand") == "yingzhua-shou"
		 && me->query_skill_prepared("hand") == "yingzhua-shou"
		 && !random(3)
		 && !target->is_busy()){
			name = xue_name[random(sizeof(xue_name))];
			message_vision(HIC"\n$N��������ǰһ�����˶Է�����֮�ʣ����ֱ���Ϊӥצ֮�ƣ���������ץ��$n��"+HIG+name+HIC"��\n"NOR,me,target);

			ap = me->query("combat_exp")/ 1000 ;
			dp = target->query("combat_exp") / 1000;
            target->start_busy(1);
			if( (random(ap + dp) > dp && me->query("mj/quest/yzs"))) {
				me->add("neili", -100);
				message_vision(CYN"���$n��"+name+"��ץ�����ţ�ȫ����������һ������ʱ���ɶ�����\n"NOR,me,target);
				target->add_busy( random((int)lvl/50) + 2);
				
				//if (weapon) weapon->unequip();
                me->add_temp("apply/hand",lvl/8);
				me->add_temp("apply/damage",lvl/8);
				message_vision(HIY"\n$N��$n���һ����ʩչ����üӥ�������־�����ӥץ�֡���\n"NOR,me,target);
			    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                me->add_temp("apply/hand",-lvl/8);
				me->add_temp("apply/damage",-lvl/8);
				//weapon->wield();
			   }
         
			else {
				dodge_skill = target->query_skill_mapped("dodge");
				if( !dodge_skill ) dodge_skill = "dodge";
				//msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
			    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
				me->add("neili", -50);
			   }
			
		
		  }
 }
string perform_action_file(string action)
{
	return __DIR__"yingzhua-shou/" + action;
}
