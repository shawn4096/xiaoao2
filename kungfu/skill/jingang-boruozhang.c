// jingang-boruozhang.c -��հ�����
#include <ansi.h>;
#include "/kungfu/skill/eff_msg.h";
inherit SKILL;
string *xue_name = ({ 
"�͹�Ѩ","����Ѩ","����Ѩ","��ԪѨ","����Ѩ","�м�Ѩ","�н�Ѩ","��ͻѨ","�ٻ�Ѩ",
}); 

mapping *action = ({
([
	"action" : "$Nǰ���߳������Ƚż��أ�һʽ����ճ�����������ֱ��������$n����������·",
	"damage_type" : "����",
	"lvl" : 0,
	"skill_name" : "��ճ���"
]),
([
	"action" : "$N���ƻ�һ��Բ��һʽ��������ա�������б������������$n����ǰ��Ѩ",
	"damage_type" : "����",
	"lvl" : 12,
	"skill_name" : "�������"
]),
([
	"action" : "$Nʹһʽ���ƶ����롹�����������������ɺ����һ��˦����ն��$n��$l",
	"damage_type" : "����",
	"lvl" : 18,
	"skill_name" : "�ƶ�����"
]),
([
	"action" : "$N���ƻ��أ���ȭ�����󷢣�һʽ����������������������$n��$l",
	"damage_type" : "����",
	"lvl" : 24,
	"skill_name" : "��������"
]),
([
	"action" : "$Nʹһʽ������ء���ȫ�������ת��˫��һǰһ���͵�����$n���ؿ�",
	"damage_type" : "����",
	"lvl" : 30,
	"skill_name" : "�����"
]),
([
	"action" : "$N���Ʊ�������һ������һʽ�����б��¡���˫�Ƽ�����$n�ļ�ͷ",
	"damage_type" : "����",
	"lvl" : 36, 
	"skill_name" : "���б���"
]),
([
	"action" : "$N���ϸ߸�Ծ��һʽ����ɽ��ˮ�����Ӹ����£���������$n��ȫ��",
	"damage_type" : "����",
	"lvl" : 42,
	"skill_name" : "��ɽ��ˮ"
]),
([
	"action" : "$Nʹһʽ��ժ�ǻ�����������������˫�����֣�һ������$n��$l�ȥ",
	"damage_type" : "����",
	"lvl" : 48,
	"skill_name" : "ժ�ǻ���"
]),
([
	"action" : "$N�������»��أ�һʽ����������������Ȼ��Ϊ�������꣬����$n",
	"damage_type" : "����",
	"lvl" : 54,
	"skill_name" : "��������"
]), 
([
	"action" : "$Nһʽ����շ�ħ����˫�ֺ�ʮ������$n΢΢һҾ��ȫ���ھ�����˰���ӿ����",
	"damage_type" : "����",
	"lvl" : 60,
	"skill_name" : "��շ�ħ"
])
});

// for pfm zhangdao
mapping *action1 = ({
([
	"action" : "$N���΢Ц��һ�С��һ������������ƶ���$n�������˰˰���ʮ�ĵ��������ݺᣬ�����һ������$p��Ѹ�ײ��ɵ�",
	"lvl" : 0,
	"skill_name" : "�һ�����",
	"damage_type" : "����"
]),
([
	"action" : "$N�����ڹ�һ�С���ľ���𡹣��������ϴ��������ޱȾ�����Ѹ�ٻ���һ���󻡣����϶�������$n��$l",
	"lvl" : 20,
	"skill_name" : "��ľ����",
	"damage_type" : "����"
]), 
([
	"action" : "$N�ֱ�һ��һ����ʹ�����Ź����¡������ƻ���һ��ѩ�����⣬����$n���֮ʱ�͵��������У�����$n��$l",
	"lvl" : 40,
	"skill_name" : "�Ź�����",
	"damage_type" : "����"
]),
([
	"action" : "$N���������������ã����ҿ���ʹ��һ�С��һ����ơ����������󵶷磬ÿһȦ����������ͬ����������������$n",
	"lvl" : 60,
	"skill_name" : "�һ�����",
	"damage_type" : "����"
]),
([
	"action" : "$Nһ�С�����ȡ������������Ȧ�����Ծ����أ�������ǰֱ�죬���߽��ƣ�Ю�����ȵķ�������$n��$l",
	"lvl" : 90,
	"skill_name" : "����ȡ��",
	"damage_type" : "����" 
]),
([
	"action" : "$N�ڿն��𣬰����һ�С���ʯ��١��������£�����Ѹ�����������������ĵ�Ӱ��ɽ���������$n��ȫ���ȥ",
	"lvl" :100,
	"skill_name" : "��ʯ���",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { 
	if (this_player()->query("sl/jgbr/pass")) return usage=="strike" ||  usage=="parry";
    else return notify_fail("��������հ�������ʽ����ȴ�޷�ʹ�á�\n");
}

int valid_combine(string combo) 
{
	object me;
	me = this_player(); 

	if ( me->query_int(1) > 40)
		return combo=="jingang-zhi"; 
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����հ����Ʊ�����֡�\n");
	if ( me->query_skill("yijin-jing", 1) < 300)
		return notify_fail("����׽�ڹ���򲻹����޷�ѧ��հ����ơ�\n");
	if ( me->query_int(1) > 30){
		return 1;
	}
	else {
		if ( me->query_skill("jingang-quan", 1)
		 && me->query_skill("yizhi-chan", 1)
		 && me->query_skill("longzhua-gong", 1)
		 && me->query_skill("nianhua-zhi", 1)
		 && me->query_skill("qianye-shou", 1)
		 && me->query_skill("ruying-suixingtui", 1)
		 && me->query_skill("sanhua-zhang", 1))
			return notify_fail("��Ĺ����������޷�ͬʱѧϰ�������ϵ��ϳ˹���\n");
	}
	if ((int)me->query("max_neili") < 600)
		return notify_fail("�������̫�����޷��������ơ�\n");
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
	int i, level, j, num=0;
	object ob;

	level = (int)me->query_skill("jingang-boruozhang",1);
	ob = me->select_opponent();	
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action": action[j]["action"],
				"damage_type": action[j]["damage_type"],
				"lvl": action[j]["lvl"],
				"force": 150 + random(300),
				"dodge": random(30),
				"damage": 100+random(80),
				"parry": random(30),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("jinbang-boruozhang", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 40)
		return notify_fail("��ľ���̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("������������������ơ�\n"); 
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}


string perform_action_file(string action)
{
	return __DIR__"jingang-boruozhang/" + action;
}


int hit_ob(object me, object ob, int damage)
{
        string name,msg;
        int skill, neili, neili1, sh;
        int j = 0;
		skill = me->query_skill("jingang-banruozhang", 1);
        neili = me->query("neili");
        neili1 = ob->query("neili");
        name = xue_name[random(sizeof(xue_name))];

         	                  
        if(random(me->query_str(1)) > ob->query_dex(1)/2
         && me->query("combat_exp") > ob->query("combat_exp")/2
         && me->query_skill_mapped("parry") == "jingang-banruozhang"
         && neili > 3000 
         && skill > 450 
         && random(10) > 6){
                
				switch (random(3))
				{
				  case 0:
                       random(2)?msg=HIY"$N�ڹ�ǿ������հ������Ѿ������Ź���ļ��£��Ʒ��������������죬�����£�$n��Щվ�����ȡ�\n"NOR:
					              msg=HIC"$N����Ϊ�˵ã���Ȼһ�ƴ�$n�����´���������$n��"+HIR+name+HIC"����\n"NOR;
				       ob->start_busy(1+random(2));
					   ob->receive_damage("qi",skill*3);
					   message_vision(msg,me,ob);
					   COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), userp(me)?3:1);

					break;
				  case 1:
                       ob->receive_damage("qi", (damage>2000)?2000:damage,me );
                       ob->receive_wound("qi", (damage>2000)?2000:damage,me );
				       ob->add_busy(1+random(2));
              	       j = (int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi");
              	       random(2)?message_vision(HIR "$N�������ƾ�����������ת���ȭ״�ջ��������䣬�����ơ�Ȼ���Ȼ˫�������\n"NOR,me,ob):
					           message_vision(HIB"$N����֮����Ȼ�緢�����������Ʊ�ӿ������ͬʱ������ǰ���������$n��"+HIC+name+HIB"��\n"NOR,me,ob);
                       msg = damage_msg(damage, "����") + "( $n"+eff_status_msg(j)+" )\n";
                       message_vision(msg,me,ob);
					   COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), userp(me)?3:1);
					  break;
				  case 2:
                      message_vision(RED"$N��$n���������������ĳ����������������ӿ��\n"NOR,me,ob);
				      COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), userp(me)?3:1);
				      COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), userp(me)?3:1);
					  break;				
				}             
                return 1; 
          }                    
}
