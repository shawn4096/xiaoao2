#include <ansi.h>
inherit SKILL;
mapping *action = ({
([
	"action" : HIW"$N�����転������аħ��˫צ���ץ�������������󷭴������ּ��죬�����ָץ��$n$l"NOR,
	"lvl" : 0,
	"damage_type" : "ץ��"
]),
([
	"action" : HIW"ͻȻ��Ӱ������$N�ȵ�$n�����������֣������ָ��$n$l������ȥ"NOR,
	"weapon" : "��ָ",
	"lvl" : 10,
	"damage_type" : "����"
]),
([
	"action" : HIW"$N�ֱ۹ؽڿ���һ�죬�ֱ۶�Ȼ���˰�ߣ�һ�ư���$n$l����ָ��Ҫ���$n��$l"NOR,
	"weapon" : "��ָ",
	"lvl" : 20,
	"damage_type" : "����"
]),
([
	"action" : HIW"$N˫��΢�ţ�ʮ������ָ��ӳ���Ұ׹�â��ͻȻ�����צ����ָ�͵ز���"NOR,
	"weapon" : "��צ",
	"lvl" : 30,
	"damage_type" : "����"
]),
([
	"action" : HIW"$N����ͻȻ��$n��ǰ��Χ�¹���������ת���������߰˰㣬���������һ�죬�����ֱָ��$n$l"NOR,
	"weapon" : "�����ָ",
	"lvl" : 40,
	"damage_type" : "����"
]),
([
	"action" : HIW "$N��צ��Σ���צ������һ��" HIR "��������ǡ�" HIW "ֱ����$n��$l" NOR,
	"lvl"   : 100,
	"skill_name" : "�������" ,
	"damage_type" : "ץ��"
]),
([
	"action" : HIW "$N˫��������צ��צצ����$n��" HIR "������������" HIW "����$n��$lץ��" NOR,
	"lvl"   : 120,
	"skill_name" : "��������" ,
	"damage_type" : "ץ��"
]),
([
        "action" : HIW "$N����Χ��$nһת��ʹ��" HIR "�����޵�����" HIW "��$n��$l����ȫ������צӰ��" NOR,
	"lvl"   : 140,
	"skill_name" : "���޵���" ,
	"damage_type" : "ץ��"
]),
([
	"action" : HIW "$Nʹһ��" HIR "�������ơ�" HIW "��˫צ�ó�����צӰץ��$nȫ��" NOR,
	"lvl"   : 160,
	"skill_name" : "������" ,
	"damage_type" : "ץ��"
]),
([
	"action" : HIW "$N����������һ��" HIR "��Ψ�Ҷ���" HIW "˫צ������$n�������" NOR,
	"lvl"   : 180,
	"skill_name" : "Ψ�Ҷ���" ,
	"damage_type" : "ץ��"
]),
});

int valid_enable(string usage)
{ 
	return usage=="claw" || usage=="parry" ;
}
int valid_combine(string combo) { return combo=="jiuyin-shenzhang"; }

int valid_learn(object me)
{
	if( (int)me->query_skill("jiuyin-shenzhua", 1 ) < 140 )
		return notify_fail("�����ڲ���ѧϰ������צ��\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��������צ������֡�\n");
	if ((int)me->query_skill("claw", 1) < 50)
		return notify_fail("��Ļ���צ����򲻹����޷�ѧϰ��\n");
	if ((int)me->query_skill("jiuyin-zhengong", 1) < 50)
		return notify_fail("��ľ����湦��򲻹����޷�ѧϰ��\n");
	if ((int)me->query_skill("jiuyin-baiguzhua", 1) > 1)
		return notify_fail("��ѧ�˾����׹�ץ���޷�ѧϰ������צ��\n");
	if ((int)me->query_skill("daode-jing", 1) < 50)
		return notify_fail("��ĵ�ѧ�ķ���򲻹����޷�ѧϰ��\n");
	if ((int)me->query("max_neili") < 1000)
		return notify_fail("�������̫�����޷���������צ��\n");
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
	level   = (int) me->query_skill("jiuyin-shenzhua",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level >= action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action":	action[j]["action"],
				"weapon":	action[j]["weapon"],
				"damage":	300+random(100),
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"force":	300 + random(350),
				"dodge":	random(30),
				"parry":	random(30),
			]);
		}
	}
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 60)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 30)
		return notify_fail("�������������������צ��\n");
	me->receive_damage("jingli", 50);
	me->add("neili", -20 );
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"jiuyin-shenzhua/" + action;
}



mixed hit_ob(object me, object victim)
{
  
		
		string msg;
		int damage;
		damage=me->query_skill("jiuyin-baiguzhua", 1)+me->query_skill("poision",1)+me->query_skill("daode-jing",1);
		damage=damage*me->query_str()/6+random(damage);
		
		if (!me->query_temp("jysz/shenzhua")) return 0;
	

		if (random(me->query_con()) >= victim->query_con()/2
			&& me->query_skill("jiuyin-shenzhua",1) > 450 
			&& me->query_skill("force",1) > 450
			&& me->query("jingli")>300
			&& random(10)>6
			&& me->query("env/������צ")=="����"
			&& random(me->query("combat_exp")) > victim->query("combat_exp")/2 
			&& me->query("neili")>500)
	   {
			  switch(random(5))				       
			  {
				case 0 :
				   msg = YEL "$N���ֳ�צ���������汱���ϳ������������ζ����׵����۵���һ���㣬��֧���Ҿ����ġ�����������Ѩ���������ʮָצ������\n";
				   if (random(me->query_skill("claw",1))>victim->query_skill("parry",1)/2)
				   {               
					   msg = msg + "$nֻ��ͷ������$N��ָ���룬ͷ�����ѣ�ʹ��һ����\n"NOR; 
					   victim->recevied_damage("qi",  damage/2,me);
					   me->add("neili",-600);
					   victim->add_condition("bgz_poison", 2+random(2));
				   }else msg = msg + HIW"$n��æ����������\n"NOR; 
					message_vision(msg, me, victim);
				   break;
				case 1 :
				   msg = HIR "$N��צ��Σ��������򿪵���ǰ���ţ������׻����Ρ��������������������ڴ˸�Ϊ������б��$n��ͷ��ȥ��\n";
				   if (random(me->query_str())>victim->query_dex()/2)
				   {
				   
					   msg += "$nֻ��ǰ���ʹ���ѱ�$N���˸�������������\n"NOR;
					   victim->recevied_damage("qi",  damage,me);               
					   victim->add_condition("bgz_poison", 2+random(3));
					   me->add("neili",-400);
				   } else msg = msg + HIC"$nһ�������Ŷ�����У����ɵ�����һ���亹��\n"NOR; 
				   message_vision(msg, me, victim);
				   
				   break;
				case 2 :
				   msg = HIB "$N��Хһ������������ָ�������޼᲻�ƣ��ݵ����ԣ��紩��������˫��ָ������������������ֱ��$nͷ����ȥ��\n";
				   if (random(me->query_str())>victim->query_str()/2)
				   {
				   
					   msg += "$nֻ��ͷ����ʹ�ޱȣ�������������һ�㣬��ǰһ�裬��$N����ͷ����\n"NOR;
					   victim->recevied_damage("qi", damage,me);   
					   victim->recevied_damage("qi", damage/3,me); 
					   victim->add_condition("bgz_poison", 2+random(3));
					   me->add("neili",-400);
				   } else msg = msg + HIC"$n���һ��������㿪��\n"NOR; 
				   message_vision(msg, me, victim);
				   
				   break;
				case 3 :
				   message_vision(HBBLU "����$n�����Ѿ�������δ��֮ʱ��$N���س�϶���������ֻ��ţ�˫צ�������У���ָ����$nͷ����\n" NOR,me,victim);
				   me->add_temp("apply/damage",  me->query_skill("jiuyin-shenzhua", 1)/6);

				   COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(2)?1:3);
				   me->add_temp("apply/damage", -me->query_skill("jiuyin-shenzhua", 1)/6);
	   
				   break;
				case 4 :
				   message_vision(HBMAG "$N������ˣ�˫��ָ�׼������͵���$n�ĺ���ץȥ���ۿ�һ�����֮�±�Ҫš��$n�ĺ�����\n" NOR,me, victim);
				   message_vision(HBMAG "$n�о�������ת��һ����Ϣ��Ϊ$N���ƣ�\n" NOR,me, victim);
			//	   victim->recevied_damage("qi", damage,me);   
				 //  victim->recevied_damage("qi", damage/3,me); 
				   victim->add_condition("no_perform",1);
				   victim->add_condition("no_exert",1);
				 //  victim->add_busy(2);
				   break;
			  } 
     
			 
	   }
}
