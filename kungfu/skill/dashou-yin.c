// dashou-yin.c ���ڴ���ӡ
//  by iceland
#include <ansi.h>
inherit SKILL;
mapping *action = ({
([
	"action" : "$Nʹ��һ�С���������ӡ����˫�ƺ�ʮ��ֱֱײ��$n��ǰ��",
	"skill_name" : "��������ӡ",
	"lvl" : 0,
	"damage_type" : "����",
]),
([
	"action" : "$Nʹ��һ�С����ƹ���ӡ��������Ծ��˫���繴��ץ��$n��$l",
	"skill_name" : "���ƹ���ӡ",
	"lvl" : 10,
	"damage_type" : "����",
]),
([
	"action" : "$Nʹ��һ�С�׼���ĸӡ����������ָ��ֱȡ$n��$l",
	"skill_name" : "׼���ĸӡ",
	"lvl" : 20,
	"damage_type" : "����",
]),
([
	"action" : "$Nʹ��һ�С���������ӡ����ŭ��һ����һ�Ƶ�ͷ����$n��$l",
	"skill_name" : "��������ӡ",
	"lvl" : 30,
	"damage_type" : "����",
]),
([
	"action" : "$Nʹ��һ�С�ҩʦ�����ӡ�����ͳ���ǰ�����������㹥��$n",
	"skill_name" : "ҩʦ�����ӡ",
	"lvl" : 40,
	"damage_type" : "����",
]),
([
	"action" : "$Nʹ��һ�С����½��ӡ������������˫������ɨ��$n��$l",
	"skill_name" : "���½��ӡ",
	"lvl" : 50,
	"damage_type" : "����",
]),
([
	"action" : "$Nʹ��һ�С����ֽ��ӡ���������Ծ��˫��ǰ�������ץ��$n���ʺ�",
	"skill_name" : "���ֽ��ӡ",
	"lvl" : 60,
	"damage_type" : "����",
]),
([
	"action" : "$Nʹ��һ�С������ǻ�ӡ������ʱ��������������г���������Ӱ����$n��$l",
	"skill_name" : "�����ǻ�ӡ",
	"lvl" : 70,
	"damage_type" : "����",
]),
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����ڴ���ӡ������֡�\n");
	if ( me->query("max_neili") < 100)
		return notify_fail("�������̫���ˣ����������ڴ���ӡ��\n");
	if ( me->query_skill("longxiang-boruo", 1) < 20)
		return notify_fail("���������������̫ǳ������ѧ���ڴ���ӡ��\n");
	if ( me->query_skill("force", 1) < 20)
		return notify_fail("��Ļ����ڹ����̫ǳ������ѧ���ڴ���ӡ��\n");
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
	level   = (int) me->query_skill("dashou-yin",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) 
		{
			j = NewRandom(i, 20, level/5);
			if ( me->query_temp("dls/dsy"))
			{
				return ([  
				"action": YEL+action[j]["action"]+NOR,
				"lvl": action[j]["lvl"],
				"damage":180+random(80),
				"damage_type" : action[j]["damage_type"],
				//"weapon": action[j]["weapon"],
				"force":100+random(250),
				"dodge":random(20)-10,
				"parry":random(10),
			   ]);
			}
			else{
				return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage":50+random(50),
				"damage_type" : action[j]["damage_type"],
				//"weapon": action[j]["weapon"],
				"force":100+random(250),
				"dodge":random(20)-10,
				"parry":random(10),
				]);
			}
		}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("dashou-yin", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 30)
		return notify_fail("����������������������ڴ���ӡ��\n");
	if ( me->query("neili") < 10)
		return notify_fail("����������������������ڴ���ӡ��\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -5);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"dashou-yin/" + action;
}

mixed hit_ob(object me, object target)
{
    string msg;
    int j;
	if (!me) return;

    j = me->query_skill("dashou-yin", 1);
	if (!target) return;

	if (!me->query("quest/dls/dsy/tianyin/pass")) return;
	
    if (objectp(target)
		&& random(me->query_con()) >= target->query_con()/4 
		&& j > 120 
		&& me->query_skill("parry",1) > 120 
		&& me->query("jingli")>300 
		//&& !target->is_busy()
		&& !random(3) 
		&& random(me->query("combat_exp")) > target->query("combat_exp")/2 
		&& me->query("neili")>500)
     {
          switch(random(2))
          {
            case 0 :
               message_vision(HIG "$NĬ�˴���ӡ���ھ�����˫�ƹ���$n��һ�ɰԵ��ھ�ӿ��$n��������������\n"+
								 "$nֻ�����ֵ����б�˺�Ѱ�����ܣ���Ȼ"HIR"��������"HIG"�Ѿ�Ϊ$N���ˣ�\n"NOR,me,target); 
               target->receive_damage("qi", j*3 +random(1000),me);
               target->add_condition("dsy_poison", 1);
			   me->add("neili",-60);
               break;
            case 1 :
               message_vision(HIY "$N����ɱ�ƿ״����̬ׯ�ϣ�ΡȻ������������ŭĿ��$n���˶��࣬���ɵش��һ����\n"NOR,me,target);
               target->add_busy(1+random(2));
               me->add("neili",-50);
               //message_vision(msg, me, target);               
               break;
            
          }         
       //   message_vision(msg, me, target);
   }
   
}
