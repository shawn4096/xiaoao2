// canhe-zhi.c �κ�ָ
// by leontt 1/5/2000

#include <ansi.h>
inherit SKILL;
void back(object target);
mapping *action = ({
([
	"action" : "$N���缤����˫ָ������ã�һ�С�Ŀ��ʶ�����׺ݵ���$n��$l��ȥ",
	"lvl" : 0,
	"skill_name" : "Ŀ��ʶ��",
	"damage_type" : "����"
]),
([
	"action" : "$N���һ����ʮָ���·ַɣ�һ�С������㾦����˫ֱָȡ$n��$l",
	"lvl" : 20,
	"skill_name" : "�����㾦",
	"damage_type" : "����"
]),
([
	"action" : "$Nʮָ���������ʵ��һ�С���˷���롹��ǰ�����ң�˲Ϣ����$n����������",
	"lvl" : 40,
	"skill_name" : "��˷����",
	"damage_type" : "����",
]),
([
	"action" : "$N�����ڿն���һ�С��ܳ���������������죬��$n��$l�Ͳ���ȥ",
	"lvl" : 60,
	"skill_name" : "�ܳ�����",
	"damage_type" : "����"
]),
([
	"action" : "$N����һ�������������ߵ�$n��ǰ��һ�С����ϲ�����������$n��$l",
	"lvl" : 70,
	"skill_name" : "���ϲ���",
	"damage_type" : "����"
]),
([
	"action" : "$Nһ�С��˱����᡹������һȭ���������ƻ�ָ��һ��һָ��ջ���$n��$l",
	"lvl" : 80,
	"skill_name" : "�˱�����",
	"damage_type" : "����"
]),
([
	"action" : "$N˫�ƻ�ָ��ָ�д��ƣ�˫�����ƣ�һ�С���н��������һ����ɽ������������ֱ��$n$l",
	"lvl" : 90,
	"skill_name" : "��н����",
	"damage_type" : "����"
]),
([
	"action" : "$NͻȻ���м�ת��һ�С����μ�����ʮָ���裬��ʱ֮�佫$n����˷�����ס��",
	"lvl" : 100,
	"skill_name" : "���μ�",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���κ�ָ������֡�\n");
	if ( me->query_skill("shenyuan-gong", 1) < 15)
		return notify_fail("�����Ԫ����򲻹����޷�ѧ�κ�ָ��\n");
	if ( me->query("family/master_name")!="Ľ�ݲ�")
		return notify_fail("�κ�ָֻ�ܸ�Ľ�ݲ�������ϰ��\n");
	if ( me->query("max_neili") < 100)
		return notify_fail("�������̫�����޷����κ�ָ��\n");
	return 1;
}

string query_skill_name(int level)
{
	int i = sizeof(action);
	while (i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level, j;
	level   = (int) me->query_skill("canhe-zhi",1);
   

	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
            //������
			if( me->query_temp("chz/ch")){
				return ([  
					"action": HIR+action[j]["action"]+NOR,
					"lvl" : action[j]["lvl"],
                    "force" : 150 + random(100),
                    "dodge": random(30)- 5 ,
                    "damage": 200 + random(50),
                    "parry": random(150),
					"damage_type" : random(2)?"����":"����",
				]);
			}
			if( me->query_temp("chz/ci")){
				return ([  
					"action": CYN+action[j]["action"]+NOR,
					"lvl" : action[j]["lvl"],
                    "force" : 150 + random(100),
                    "dodge": random(30)- 5 ,
                    "damage": 180 + random(50),
                    "parry": random(150),
					"damage_type" : random(2)?"����":"����",
				]);
			}
			//��ָ����
			if (me->query_temp("mrjf/lianhuan") && (int)me->query_skill("canhe-zhi",1) > 349) {
                   return ([
                           "action": HIG+action[j]["action"]+NOR,
                           "lvl": action[j]["lvl"],
                           "damage_type": action[j]["damage_type"],
                           "force": 350 + random(350),
                           "dodge": 20+random(35),
                           "parry": 10+random(20),
					       "damage": 150+random(50),
                   ]);
			}
            else {
				return ([
					"action": action[j]["action"],
					"lvl": action[j]["lvl"],
					"damage_type": action[j]["damage_type"],
					"force": 200 + random(350),
					"dodge": random(30)-10,
					"parry": random(20),
					"damage": 100+random(50),
				]);
			}
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("canhe-zhi", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query("jingli") < 50)
		return notify_fail("��ľ���̫���ˡ�\n");
	if ( me->query("neili") < 20)
		return notify_fail("��������������κ�ָ��\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{        
	return __DIR__"canhe-zhi/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	string msg;
	int j;
	j = me->query_skill("canhe-zhi", 1);
	
	if (!objectp(victim)) return;

	if (me->query("shenyuan/powerup"))
	{
		j=j+me->query_skill("shenyuan-gong", 1);
	    j=j+random(j);
	}
	//if ( me->query_temp("mr_ci") ) return 0;
  
	if ( random(me->query_str(1)) >= victim->query_dex(1)/3
		&&j > 120 
		&& random(10) > 5
	 	&& random(me->query("combat_exp")) > victim->query("combat_exp")/2
		&& me->query("neili") > 500
		&& me->query("canhe/pass")) 
       {
		switch(random(6)) {
			case 0 :
				message_vision( HIW"$Nһ�С��黨ָ��ʹ����ָ����ƮƮ�ص���$n���γ�������Ϣ���ھ�����$n�����Ѩ��\n",me,victim);
				message_vision( HIR"$nֻ��ȫ��һ�飬�ѱ�һ�е��С�����Ѩ����\n"NOR,me,victim); 
				victim->add_busy(1+random(3));
				me->add("neili",-random(300));
				break;
			case 1 :
				message_vision(CYN"$Nָ��Ϭ����������ָ����һ�����ν�������$n�������ڣ�$nֻ���ؿ�һʹ��ȫ��������к������\n"NOR,me,victim);
				victim->recevied_damage("neili", j);
				if ( victim->query("neili") < 0 )
					victim->set("neili", 0);
				me->add("neili",-random(500));
				break;

            case 2 :
				message_vision(HIR"$N�ݻ��ɡ��������ָ��֮�ƣ�����ʵ�޻���ֱ�Ӵ���$n���ؿڡ�\n",me,victim);
			    message_vision(RED"$nֻ���Ŀ�Ϊ��һָ���У�һ�ɾ�ʹ��������Ѫ���������\n"NOR,me,victim); 
				victim->recevied_damage("qi", random(1500),me);
				victim->recevied_wound("qi", random(500),me);
				me->add("neili",-random(200));
				break;
		    case 3 :
				message_vision(HIY"$N���γɡ�����Ҷָ������Сָ��Ĵָ����չ�������绨����Ϯ����$n�ġ�̫��Ѩ����\n",me,victim);
			    message_vision(RED "$n��Ȼ�������������⵽�׻��㣬�������죬ͬʱ����һ��ѣ�Σ�\n"NOR,me,victim); 
				victim->recevied_damage("jing", random(500),me);
				victim->recevied_wound("jing", random(200),me);
				me->add("neili",-random(300));
				break;
            case 4 :
				message_vision(HIG"$N��ƮƮת��$n����󣬡�һָ��������ӿ��������Ǭ��һ��������$n�ġ���׵Ѩ��\n",me,victim);
			    message_vision(HIR"$n��Ȼ����һ�����飬�����ǧ�����������������ҧ������ܣ�\n"NOR,me,victim); 
				victim->recevied_damage("jingli", random(800),me);
				victim->recevied_wound("jingli", random(300),me);
				me->add("neili",-random(300));
				break;
			case 5 :
				message_vision(HIR"$N˳����ʽ����ʽ�ֱ�Ϊ����ָ�������򣬴���$n�ġ�˫Ŀ������$nĿ��Ͼ�ӡ�\n"NOR,me,victim);
			    if (random(me->query_str(1))>victim->query_dex(1)/3)
			    {
					message_vision(HIY"$n��Ȼ˫ĿΪ��ָ��ָ�羢�����ˣ�һ����ʹ��������ʱ����һƬ�ڰ�֮�У�\n"NOR,me,victim); 		

					victim->set_temp("chuomu", 1);
                    victim->add_temp("apply/attack", - 200);
                    victim->add_temp("apply/dodge", - 200);
                    victim->add_temp("apply/parry", -150);
                    victim->receive_damage("qi", random(1500),me);
                    victim->receive_wound("qi", random(800),me);
                    victim->set_temp("block_msg/all",1);
                    call_out("back", 20+random(10), victim);
			    }
				else {
					
					message_vision(HIC "$n��æ���Ա���������������ɱ�У���ȫ��ȴ�������ŵ��亹���ܣ�\n"NOR,me,victim); 
                    me->add_busy(1+random(1));
				}
			    
				me->add("neili",-random(150));
				break;
		  }
		//message_vision(msg, me, victim);
	}
}


void back(object target)
{
	if(!target) return;
        target->add_temp("apply/attack", 200);
        target->add_temp("apply/dodge", 200);
        target->add_temp("apply/parry", 150);
        target->set_temp("block_msg/all", 0);
		
        if(living(target)) 
              tell_object(target, HIW "��������˫Ŀû�б��������ˣ����ֿ��Կ�����������\n" NOR);
        target->delete_temp("chuomu");
	return;
}
