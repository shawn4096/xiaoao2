// chousui-zhang.c, ������
// by pishou
// Modified by Lklv 2002.1.30

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action": "$N�߶�����������Ӷ���˫��Ю��һ���ȳ�֮��һǰһ������$n��$l",
	"lvl" : 0,
	"damage_type": "����"
]),
([
	"action": "$N˫��һ��һ�䣬������ת����, ͻȻ��˫�Ʒ���������$n��$l",
	"lvl" : 20,
	"damage_type": "����"
]),
([
	"action": "$N����Ʈ����Χ��$nһȦȦ���ߣ�ͬʱ˫�����ģ��������󾢷紵��$n",
	"lvl" : 40,
	"damage_type": "����"
]),
([
	"action": "$NͻȻ������ȣ�Ծ�ڰ�գ������縫������������$n������������",
	"weapon" : "�Ʒ�",
	"lvl" : 60,
	"damage_type": "����"
]),
([
	"action": "$N����΢����ǰһ��������ʮ�ɹ��������һ�����뷢��ţ�����һ������$n��ȥ",
	"lvl" : 90,
	"damage_type": "����"
]),
([
	"action": "$N��¶�����Ц�ݣ��͵���ǰ�������׼$n��$l����һ�������ޱȵġ������ơ�",
	"lvl" : 120,
	"damage_type": "����"
]),
([
	"action": "$N����һת������������һ�С��������צ�������������������ץ��$n��$l",
	"weapon" : "��צ",
	"lvl" : 150,
	"damage_type": "ץ��"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="sanyin-zhua"; }

string query_skill_name(int level)
{
	int i = sizeof(action);
	while (i--)
		if(level > action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me,object weapon)
{
	string msg;
	int i, level, j;
	level   = (int) me->query_skill("chousui-zhang",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			//���϶���
			if ( me->query_temp("csz/bingcan")){
				switch(me->query_temp("csz/bingcan")){
					case 5:	msg =HIC"$N������ǰ��һ���ĳ���$n��æ���ֵ��񣬿����������죬$n�۹ǡ��߹���ϣ���ʽѰ����������ȴ��ĳ���"NOR;	break;
					case 4:	msg =HBWHT+HIB"$N�����򻰣�����������������Ƹ���Ѹ��֮�������������������ȷ��󵽣������������ȵ����������������ǰ������֮��"NOR;			break;
					case 3:	msg =HBGRN+HIB"$Nÿһȭ������ÿһ���ĳ���������������֮����$n��ȫ����$N����֮�ʣ����ɵú���Ϯ�壬��Ϊ�ѵ�"NOR;	break;
					case 2:	msg =HIG"$N�ı��϶��Ʒ�����������ǿ����������������֮�����������о綾$n����ʤ��"NOR;	break;
					case 1:	msg =HIB"$N�̼�֮�£����������ӳ���Ҫ���ƿ��Է����ĵ�һ��������$n�����,��һ�����ƾ���������Ѱ��"NOR;			break;
					case 0:	msg =HBYEL+HIG"$N̤��һ��������$n��һ�У��е��������������������������������ƣ�ÿ��һ�ƣ������һ��"NOR;	break;
					default:msg =HIB"$N�����ڵ���һ�٣����������ĳ���һ������֮��������Ʒ�ֱ�ƶ���$n��$l"NOR;	break;
				}
				me->add_temp("csz/bingcan", -1);
				return ([
					"action":	msg,
					"poison":	action[j]["poison"],
					"damage_type":	random(2)?"����":"����",
					"weapon":	action[j]["weapon"],
					"force":	150+random(200),
					"dodge":	random(30),
					"damage":	250+random(100),
					"parry":	random(30),
				]);
			}			
			//������
			if ( me->query_temp("csz/chousui")){
				switch(me->query_temp("cxz/chousui")){
					case 3:	msg =HIB"$Nҧ����⣬������Ѫ���ۼ�ȫ��������������������֣�ͻȻһת����$n��$l£ȥ"NOR;	break;
					case 2:	msg =HIB"$N����¶�������Ц�ݣ���Ӱ��ǰ��������������ɫ��˫��ɨ��$n��$l"NOR;			break;
					case 1:	msg =HIB"$NͻȻ������ת��������$n��˫�Ʒ�����Ю��һ���ȳ�֮���������ޱȵ�����$n��$l"NOR;	break;
					default:msg =HIB"$NͻȻ������ת��������$n��˫�Ʒ�����Ю��һ���ȳ�֮���������ޱȵ�����$n��$l"NOR;	break;
				}
				me->add_temp("csz/chousui", -1);
				return ([
					"action":	msg,
					"damage_type":	random(2)?"����":"����",
					"weapon":	action[j]["weapon"],
					"force":	150+random(200),
					"dodge":	random(30),
					"damage":	150+random(100),
					"parry":	random(30),
				]);
			}
			return ([  
				"action":	action[j]["action"],
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"weapon":	action[j]["weapon"],
				"force":	200+random(350),
				"dodge":	random(30)-10,
				"parry":	random(20),
			]);
		}
	}
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����ֲ����������ơ�\n");
	if ((int)me->query_skill("huagong-dafa", 1) < 10)
		return notify_fail("�㻹�������û����󷨰ɡ�\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("����������̫��, �����˳����ơ�\n");
	return 1;
}

int practice_skill(object me)
{
	int lvl = me->query_skill("chousui-zhang", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 50)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("������������������ơ�\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int poison, i,skill,damage;
	skill=me->query_skill("chousui-zhang",1);
	poison = (me->query_skill("poison", 1) - victim->query_skill("poison", 1))/5;
	poison += me->query_skill("chousui-zhang",1)/10;
	damage=skill+poison+me->query_skill("huagong-dafa",1);
	damage=damage*me->query_str()/20;
	if (damage>6000) damage=6000;
	
	if ( userp(victim)) {
		poison /= 3;
		i = 120;
	}
	else
		i = 50;
	
	//���̺󱩻���ʽ
	if (me->query_temp("csz/biyan")
		&& victim
		&& random(10)>6
		&& present("huo yan",environment(me)))
	{
		message_vision(HIG"$N�����󷨾�����ӿ��һ��������ϵĻ��棬���ۡ���һ������һ�������ĵĻ������$n��\n"NOR,me,victim);
		victim->add_busy(1);
		victim->receive_damage("qi",damage,me);
		victim->receive_wound("qi",damage/4,me);
	}
//�ж���ʽ
	if(random(me->query_skill("huagong-dafa", 1)) > i
	&& me->query_skill("chousui-zhang", 1) > 50
	&& me->query_skill("poison", 1) > 50
	&& me->query("env/������") != "����"
	&& random(me->query_skill("poison", 1)) > random( victim->query_skill("medicine", 1))
	&& victim->query_condition("xx_poison") < 200
	&& me->query("neili") > 200
	&& !victim->query("job_npc")) {
		if (me->query("env/������") == "ɢ��") {
			poison += random(poison/2);
			me->add("neili",-100-random(50));
			me->add("jingli",-20-random(30));
			message_vision(BLU"$N����һ�ߣ���צ��������ʢ��\n"NOR, me);
		}
		if (!userp(victim)) victim->add_condition("xx_poison", poison);
		else victim->add_condition("xx_poison", 2);
		message_vision(BLU"$Nһ��צ������һ�Σ������Ѿ����˶���\n"NOR, victim);
		if (victim->query_condition("xx_poison") > 50)
			message_vision(HBRED"$N���ڻ����������������Σ�գ�\n"NOR, victim);
		
		if (userp(me)
		 && userp(victim)
		 && !victim->query_temp("kill_other/"+me->query("id"))
		 && !me->query_temp("other_kill/"+victim->query("id"))
		 && ! me->query_temp("revenge/"+victim->query("id"))
		 && !victim->query_condition("killer")
               && (!me->query_temp("special_die") || !victim->query_temp("special_die")))
			me->add_condition("killer", 5);
	}
//�⿪��Ϻ�Ч���ͷ�

	if( me->query_temp("csz/bingcan")  && random(10)>6  )        
    {  
              
			if ( random(skill) > 50 && random(me->query_dex()) > victim->query_dex()/4) 
			{
                message_vision(BLU+BWHT "�ۼ�$nԽսԽ�£�$Nȴ˿�����������ϣ�����Ͷ���ƽƽ�ӳ�һ�ƣ�����һ�ɹ���ĺ���������$n\n"
                                   "$n�����ƹ��죬�Ʒ��о������Ŵ̹ǵĺ������������˸���ս�� \n"NOR,me,victim);
                if(userp(victim))
				{
					victim->add_busy(1+random(3));
					victim->add_condition("cold_poison", 2);
				}
				else 
				{
					victim->add_busy(2+random(4));
					victim->add_condition("cold_poison", 5);
				}                    
                       
			}
			else if (random(skill) > 350 && random(me->query_str()) > victim->query_str()/2)
			{
                message_vision(HIW "$N�û�̤����ǰ����$n����ǰ���һ�У�$n��δ�ֵ������Ϻ�������������$nС����\n" NOR,me,victim);
                message_vision(WHT "$nֻ�������������Ʊ�����һ�㣬�޷����ۣ���ʱ����һ���亹��\n" NOR,me,victim);
				
				if(userp(victim))
				{
                      victim->add("jing",- poison); 
                      victim->add("neili",- poison); 
                      victim->add("jingli",- poison); 
                      victim->apply_condition("no_perform", 1);
                      victim->apply_condition("no_exert", 1);
                      victim->add_condition("cold_poison", 2);
				}
				 else
				{
                      victim->add("jing",- poison*2); 
                      victim->add("neili",- poison*2); 
                      victim->add("jingli",- poison*2); 
                      victim->apply_condition("no_perform", 2+ random(4));
                      victim->apply_condition("no_exert", 2+ random(4));
                      victim->add_condition("cold_poison", 30);
				
                }  
			

			}
	}
		 
}

string perform_action_file(string action)
{
	return __DIR__"chousui-zhang/" + action;
}
