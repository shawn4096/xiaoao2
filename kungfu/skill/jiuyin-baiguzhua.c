// jiuyin-baiguzhua.c �����׹�צ

#include <ansi.h>
inherit SKILL;
mapping *action = ({
([
	"action" : BLU"$N�����転������аħ��˫צ���ץ�������������󷭴������ּ��죬�����ָץ��$n$l"NOR,
	"lvl" : 0,
   	"damage_type" : "ץ��"
]),
([
	"action" : BLU"ͻȻ��Ӱ������$N�ȵ�$n�����������֣������ָ��$n$l������ȥ"NOR,
	"weapon" : "��ָ",
	"lvl" : 10,
	"damage_type" : "����"
]),
([
	"action" : BLU"$N�ֱ۹ؽڿ���һ�죬�ֱ۶�Ȼ���˰�ߣ�һ�ư���$n$l����ָ��Ҫ���"NOR,
	"weapon" : "��ָ",
   	"lvl" : 20,
	"damage_type" : "����"
]),
([
	"action" : BLU"$N˫��΢�ţ�ʮ������ָ��ӳ���Ұ׹�æ��ͻȻ�����צ����ָ�͵ز���"NOR,
	"weapon" : "��צ",
	"lvl" : 30,
   	"damage_type" : "����"
]),
([
	"action" : BLU"$N����ͻȻ��$n��ǰ��Χ�¹���������ת���������߰˰㣬���������һ�죬�����ֱָ��$n$l"NOR,
	"weapon" : "�����ָ",
	"lvl" : 40,
	"damage_type" : "����"
]),
([
	"action" : BLU "$N��צ��Σ���צ������һ��" HIR "��������ǡ�" BLU "ֱ����$n��$l" NOR,
	"lvl"   : 100,
	"skill_name" : "�������" ,
	"damage_type" : "ץ��"
]),
([
	"action" : BLU "$N˫��������צ��צצ����$n��" HIR "������������" BLU "����$n��$lץ��" NOR,
	"lvl"   : 120,
	"skill_name" : "��������" ,
	"damage_type" : "ץ��"
]),
([
	"action" : BLU "$N����Χ$nһת��ʹ��" HIR "�����޵�����" BLU "��$n��$l����ȫ������צӰ��" NOR,
	"lvl"   : 140,
	"skill_name" : "���޵���" ,
	"damage_type" : "ץ��"
]),
([
	"action" : BLU "$Nʹһ��" HIR "�������ơ�" BLU "��˫צ�ó�����צӰץ��$nȫ��" NOR,
	"lvl"   : 160,
	"skill_name" : "������" ,
	"damage_type" : "ץ��"
]),
([
	"action" : BLU "$N����������һ��" HIR "��Ψ�Ҷ���" BLU "˫צ������$n�������" NOR,
	"lvl"   : 180,
	"skill_name" : "Ψ�Ҷ���" ,
	"damage_type" : "ץ��"
]),
});

int valid_enable(string usage)
{
	return usage=="claw" || usage=="parry" ;
}

int valid_combine(string combo) 
{
	object me;
	me = this_player(); 

	if ( me->query_int(1) > 30)
		return combo=="cuixin-zhang"; 
}


int valid_learn(object me)
{
	if( !me->query("quest/jiuyin2/pass") && !me->query("quest/jiuyin1/pass"))
		return notify_fail("�㲻����ϰ�����׹�צ��\n");
	if( (int)me->query_skill("jiuyin-baiguzhua", 1 ) < 150 )
		return notify_fail("�����ڲ�����ϰ�����׹�צ��\n");
	if( (int)me->query_skill("jiuyin-shenzhua", 1 ) >= 1 )
		return notify_fail("�������ץ�ˣ�����ѧ�����׹�צ��\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������׹�צ������֡�\n");
	if ((int)me->query_skill("claw", 1) < 41)
		return notify_fail("��Ļ���צ����򲻹����޷�ѧϰ��\n");
	if ((int)me->query("max_neili") < 1000)
		return notify_fail("�������̫�����޷��������׹�צ��\n");
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
	level   = (int) me->query_skill("jiuyin-baiguzhua",1);
	
	if (me->query_temp("jybgz/bgz"))
	{
			return ([
				"action":	action[j]["action"],
				"weapon":	action[j]["weapon"],
				"damage":	300+random(100),
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"force":	250 + random(300),
				"dodge":	random(30)-10,
				"parry":	random(20),
			]);
	}
	for(i = sizeof(action); i > 0; i--) {
		if(level >= action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			
			return ([
				"action":	action[j]["action"],
				"weapon":	action[j]["weapon"],
				"damage":	200+random(100),
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"force":	250 + random(300),
				"dodge":	random(30)-10,
				"parry":	random(20),
			]);
		}
	}
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 50)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("������������������׹�צ��\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"jiuyin-baiguzhua/" + action;
}

void skill_improved(object me)
{
	tell_object(me, "���������ź�Ȼ���ĵ�����һ��а�\n");
	me->add("shen", -(me->query_skill("jiuyin-baiguzhua", 1)/100));
}

mixed hit_ob(object me, object target)
{
    string msg;
    int j,damage;
    j = me->query_skill("jiuyin-baiguzhua", 1);
	damage=j+me->query_skill("poision",1)+me->query_skill("taoism",1);
	damage=damage*me->query_str()/6+random(damage);

    if (random(me->query_con()) >= target->query_con()/2
		&& j > 450 
		&& me->query_skill("force",1) > 450
		&& me->query("jingli")>300
		&& random(10)>6
		&& random(me->query("combat_exp")) > target->query("combat_exp")/2 
		&& me->query("neili")>500)
   {
          switch(random(3))
          {
            case 0 :
               msg = YEL "$N���ֳ�צ���������汱���ϳ������������ζ����׵����۵���һ���㣬��֧���Ҿ����ġ�����������Ѩ���������ʮָצ������\n";
               if (random(me->query_skill("claw",1))>target->query_skill("parry",1)/2)
               {               
				   msg = msg + "$nֻ��ͷ������$N��ָ���룬ͷ�����ѣ�ʹ��һ����\n"NOR; 
				   target->recevied_damage("qi",  damage,me);
				   me->add("neili",-600);
				   target->add_condition("bgz_poison", 2+random(2));
               }else msg = msg + HIW"$n��æ����������\n"NOR; 
               break;
            case 1 :
               msg = HIR "$N��צ��Σ��������򿪵���ǰ���ţ������׻����Ρ��������������������ڴ˸�Ϊ������б��$n��ͷ��ȥ��\n";
			   if (random(me->query_str())>target->query_dex()/2)
			   {
			   
				   msg += "$nֻ��ǰ���ʹ���ѱ�$N���˸�������������\n"NOR;
				   target->recevied_damage("qi",  damage,me);               
				   target->add_condition("bgz_poison", 2+random(3));
				   me->add("neili",-400);
			   } else msg = msg + HIC"$nһ�������Ŷ�����У����ɵ�����һ���亹��\n"NOR; 
               //message_vision(msg, me, target);
               
               break;
			case 2 :
               msg = HIB "$N��Хһ������������ָ�������޼᲻�ƣ��ݵ����ԣ��紩��������˫��ָ������������������ֱ��$nͷ����ȥ��\n";
			   if (random(me->query_str())>target->query_str()/2)
			   {
			   
				   msg += "$nֻ��ͷ����ʹ�ޱȣ�������������һ�㣬��ǰһ�裬��$N����ͷ����\n"NOR;
				   target->recevied_damage("qi", damage,me);               
				   target->add_condition("bgz_poison", 2+random(3));
				   me->add("neili",-400);
			   } else msg = msg + HIC"$n���һ��������㿪��\n"NOR; 
               //message_vision(msg, me, target);
               
               break;
          }         
          message_vision(msg, me, target);
   }
}
