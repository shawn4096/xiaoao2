// luohan-quan.c �޺�ȭ

#include <ansi.h>
#include <combat.h>

inherit SKILL;

#include <combat_msg.h>

mapping *action = ({
([
	"action" : "$N�����ϲ���һʽ����ݺ��ܡ��������ַֿ�����ȭΪ�ƣ�����$n��$l",
	"lvl" : 0,
	"skill_name" : "��ݺ���",
	"damage_type" : "����"
]),
([
	"action" : "$N�����̤��ȫ����ת��һ�С����ﳯ�����������͵ز���$n��$l",
	"lvl" : 10,
	"skill_name" : "���ﳯ��",
	"damage_type" : "����"
]),
([
	"action" : "$N˫�ִ󿪴��أ�����߾٣�ʹһ�С����Ӷ�Ӧ����˫ȭ��$n��$l��ȥ",
	"lvl" : 20,
	"skill_name" : "���Ӷ�Ӧ",
	"damage_type" : "����"
]),
([
	"action" : "$N����Ȧ���������⵱�أ����ڳ��ϣ�һ�С�ƫ�����ǡ�����$n��$l",
	"lvl" : 30,
	"skill_name" : "ƫ������",
	"damage_type" : "����"
]),
([
	"action" : "$Nʹһ�С��ຣ��ͷ��������ǰ̽��˫�ֻ��˸���Ȧ������$n��$l",
	"lvl" : 40,
	"skill_name" : "�ຣ��ͷ",
	"damage_type" : "����"
]),
([
	"action" : "$N˫�ƻ�����һ�ǡ�Юɽ���������Ƴ���磬һ�����е�$n��$l",
	"lvl" : 50,
	"skill_name" : "Юɽ����",
	"damage_type" : "����"
]),
([
	"action" : "$Nʩ��������������˫ȭȭ����磬ͬʱ����$nͷ���أ�������Ҫ��",
	"lvl" : 60,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([
	"action" : "$N����ڿۣ�����������һʽ�������������˫�����밴��$n��$l",
	"lvl" : 70,
	"skill_name" : "�������",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }

int valid_combine(string combo) {
	if(this_player()->query_skill("wuxiang-zhi", 1) >= 200
	&& this_player()->query_skill("luohan-quan",1) >= 200
	&& this_player()->query_con(1) > 45
	&& this_player()->query_int(1) > 45)
		return combo=="wuxiang-zhi";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���޺�ȭ������֡�\n");
	if ( me->query_skill("yijin-jing", 1) < 20&& me->query_skill("hunyuan-yiqi", 1) < 20)
		return notify_fail("����׽���Ԫһ���ڹ���򲻹����޷�ѧ�޺�ȭ��\n");
	if ( me->query("max_neili") < 50)
		return notify_fail("�������̫�����޷����޺�ȭ��\n");
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
	level = (int) me->query_skill("luohan-quan",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level >= action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			if( me->query_skill("wuxiang-zhi", 1))
				return ([
					"action": action[j]["action"],
					"damage_type": action[j]["damage_type"],
				    "damage":100+random(100),
					"lvl": action[j]["lvl"],
					"force": 200 + random(350),
					"dodge": random(30)-10,
					"parry": random(20),
				]);
				else return ([
					"action": action[j]["action"],
					"damage_type": action[j]["damage_type"],
					"damage":80+random(80),
					"lvl": action[j]["lvl"],
					"force": 100 + random(250),
					"dodge": random(20)-10,
					"parry": random(10),
				]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("luohan-quan", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 50)
		return notify_fail("�������̫���ˡ�\n");
	if ( me->query("neili") < 20)
		return notify_fail("��������������޺�ȭ��\n");
	if ( me->query_skill("wuxiang-zhi", 1)) {
		me->receive_damage("jingli", 40);
		me->add("neili", -15);
	}
	else {
		me->receive_damage("jingli", 20);
		me->add("neili", -5);
	}
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int j,dam;
    //�⿪����ķ�豹������������
	//if( damage_bonus < 100 ) return 0;
	j = me->query_skill("luohan-quan", 1)+me->query_skill("wuxiang-zhi", 1)+me->query_skill("force", 1);
    j=j/2;
	if ( random(10) > 4
	 //&& !victim->is_busy()
	 && j > 450
	 && me->query_skill_mapped("cuff") == "luohan-quan"
	 && me->query_skill_prepared("cuff") == "luohan-quan"
	 && me->query_skill_mapped("finger") == "wuiang-zhi"
	 && me->query_skill_prepared("finger") == "wuxiang-zhi"
	 && me->query("neili") > 3000
	 && me->query("max_neili") > 20000
	 && me->query("quest/�����˲�/�书/quanli")
	 && random(j) > victim->query_skill("dodge",1)/2 ) 
	{
		
		if (random(2)){
		   message_vision(HIW"$N�Ѿ���Ϥ����ͨ�޺�ȭ�ľ��⣬����˫�ַ�ת�������������Ѩ���������ڽ���Ѩ���������⣬\n"+
			"�������£������Ѩ��������Ѩ֮�ϣ�����Ѩ������Ѩ֮�£�˫��������֯��һƬ���ϣ��պý�����ҪѨ��ס���ַ�����֮��"NOR,me,victim);
		   dam=j*me->query_str();
		   dam=dam+random(dam);
		   if (dam>8000) dam=8000+random(dam/2);//��ʱ���Ǳ�̫����		
		   victim->receive_damage("qi",dam,me);
		   victim->receive_wound("qi",dam/4,me);
		   
		}else {
		   message_vision(HIY"$n��$N��һ����ϵ�˿˿��ۣ��������߹���պ���ȥ��Ҫ$Nһ������һ�㣬������ͬ��ʦ�ֵܲ��У�\n"+
			"�����������޷� һ������̫��ͻȻ��һʱ���飬��ʱ������æ����֮�С�\n"NOR,me,victim);
           if (userp(victim))
		      victim->add_busy(2+random(2));
		   else victim->add_busy(4+random(2));
		
		}
       return;

	}
}
int help(object me)
{
        write(HIB"\n�޺�ȭ�����"NOR"\n\n");
        write(@HELP
        �޺�ȭ���ഫ��������ɮ�˴�Ħ������ͨ��δ����Ħ��������ԭ������������˵���ڣ�
		����ɮ������Ƽ��ݡ�����������ή����˯������ز���ߣ���ȻԻ�����������䲻
		������Ϊ�أ�Ȼ�಻�ݲ��������ԣ�ʹ�����ɢҲ�������ԣ�����ǿ����������ǿ����
		������Ҳ�������Ǵ��޺�ȭʮ���֣�����ɮ�ڣ������������£�������������棬����
		��ʼҲ���ڵ�ʱ��ν�޺�ȭ�ߣ�ֻ��ʮ���֣��ಢ���������֮��Ŀ��
		�޺�ȭ��������ʼ֮ʮ����Ҳ�������ָ�ʦ��֮��ͳ�ڷ�����ֹʮ���֣�������������
		ʧ���档�Դ�Ħ��ʦ�����������Ҿ��ֶ��гд����ӣ������ۻ����ǳ����Ħ��������
		�������������֣�����𴫣�ֱָ���ģ����Գɷ𡣡����������У�ʼ�������š�����Ϊ�ڡ�
		�����ھ��񣬲����ں������ɣ���������������סԵ��ֹ�Ĳ��ң���Ҳ�ơ������ķ��޺�ȭ����
		��ʫԻ������Ħ����һ���ޣ�ȫƾ�����ù�����Ҫ����Ѱ�𷨣��ʼ�պ�ɶ�ͥ����������
		�޺�ȭԪʼʮ���֣�ÿ�����ƶ���������׮��������ʹ�����������㣬�ֿ�ʹ�����ȹ̣�
		�������⣬�������Σ��Ⱦ��ֶ����׽�ϴ�蹦���޲���Ҳ���ɻ�����˫��֮Ч��


        Ҫ��
			������� 50;
			�޺�ȭ���������ָ��ϻ������auto�������֡�	
               
               

HELP
        );
        return 1;
}

string perform_action_file(string action) 
{ 
       return __DIR__"luohan-quan/" + action; 
} 