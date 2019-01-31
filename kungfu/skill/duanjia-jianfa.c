//�μҽ���
//cool@SJ,990528
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N�������˸�����������$wƽƽ�ݳ���һʽ�������Ͻ�ֱ��$n��ǰ��",
	"damage_type" : "����",
	"lvl": 0,
]),
([
	"action" : "$N������ǰ��$w��һ���벻���ĽǶ�ͻȻ������һʽ���̼�������ֱ��$n������",
	"damage_type" : "����",
	"lvl": 20,
]),
([
	"action" : "$Nһ�С������ڿա�������Ծ�ڰ�գ�$w����������ֱ��$n��ͷ��",
	"damage_type" : "����",
	"lvl": 40,
]),
([
	"action" : "$N����б�ӣ�����ָ��$n�ĸ�����һ�С���Ԩ���ԡ������¶�������$n",
	"damage_type" : "����",
	"lvl": 60,
]),
([
	"action" : "$N˫����أ�б�ɶ�����$w����$n��$l����һ�С�Цָ���ϡ�",
	"damage_type" : "����",
	"lvl": 80,
]),
([ 
	"action" : "$N��Хһ�����ὣ�������͸������֮�⣬���ǶμҲ���֮�ء���¹��ԭ����������ס$n��ȫ��",
	"damage_type" : "����",
	"lvl": 100,
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;
	if (!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if (me->query("max_neili") < 100)
		return notify_fail("�������������\n");
	if ( ! me->query_skill("kurong-changong", 1))
	if (me->query_skill("qiantian-yiyang", 1) < 20)
		return notify_fail("���Ǭ��һ�����̫ǳ��\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	string msg;
	level   = (int) me->query_skill("duanjia-jianfa",1);

	if(me->query_temp("fenglei")){
		switch(me->query_temp("fenglei")){
			case 4: msg = WHT"$Nʩչ���������裢��һ��Ծ���ڿ��У�����Χ����$n��ͣ��ת���������ĸ���λ��$n�̳��Ľ�������ޱ�" NOR;break;
			case 3: msg = CYN"$N����$n�ľ����ڿ���һ����˫���ս���һ���̳�������ӥ�����գ����ˣ���һ����������һ����������$n" NOR;break;
			case 2: msg = YEL"$N���ƻ��Ļ���������$n��ע�⣬���ֽ�ת���Σ���������������������һ�����ģ���������Ϯ��$n��ȫ��" NOR; break;
			case 1: msg = MAG"$N�����³���ͻȻ����һ������ĳ���ͷ�½��ϣ����ӽ������������һƮ�����ǿ����ޱȵĴ̳�������ֱ��$n"NOR;break;
			default: msg = HIW"$N�����³���ͻȻ����һ������ĳ���ͷ�½��ϣ����ӽ������������һƮ�����ǿ����ޱȵĴ̳�������ֱ��$n" NOR; break;
		}
		me->add_temp("fenglei", -1);
		return ([
			"action":msg,
			"damage": me->query("class") =="bonze"?80:100, 
			"damage_type": "����",
			"dodge": 30, 
			"force": me->query("class")=="bonze"?80:100,
			"parry": 50,
			"skill_name" : "���״�",
		]);
	}
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			if (me->query_temp("djjf/ailao"))
			{
				return ([
					"action":random(2)?HIW+action[NewRandom(i, 20, level/5)]["action"]+NOR:HIR+action[NewRandom(i, 20, level/5)]["action"]+NOR,
					"damage": me->query("class")=="bonze"? 60:160,
					"damage_type": action[NewRandom(i, 20, level/5)]["damage_type"],
					"dodge": me->query("class")=="bonze"? 30:50,
					"force": me->query("class")=="bonze"? 100:200,
					"parry": me->query("class")=="bonze"?40:60,
				]);
			}
			return ([
				"action":action[NewRandom(i, 20, level/5)]["action"],
				"damage": me->query("class")=="bonze"? 60:100,
				"damage_type": action[NewRandom(i, 20, level/5)]["damage_type"],
				"dodge": me->query("class")=="bonze"? 30:50,
				"force": me->query("class")=="bonze"? 100:200,
				"parry": me->query("class")=="bonze"?40:60,
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("duanjia-jianfa", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 50)
		return notify_fail("��������������μҽ�����\n");
	if((int)me->query("neili") < 20)
		return notify_fail("��������������μҽ�����\n");
	if ( me->query("class") == "bonze") {
		me->receive_damage("jingli", 30);
		me->add("neili", -10);
	}
	else {
		me->receive_damage("jingli", 40);
		me->add("neili", -15);
	}
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"duanjia-jianfa/" + action;
}

mixed hit_ob(object me, object target)
{
    string msg;
    int j;
	object weapon;
	weapon=me->query_temp("weapon");
	if (!me->query("quest/tls/djjf/yanqing/pass"))
	{
		return 1;
	}
    j = me->query_skill("duanjia-jianfa", 1);
   
    if (random(me->query_int(1)) >= target->query_int(1)/2 
		&& j > 120 
		&& me->query_skill("parry",1) > 120 
        && me->query("jingli")>300  
        && random(me->query("combat_exp"))> target->query("combat_exp")/2 
        && me->query("neili")>500)
     {
          switch(random(2))
          {
            case 0 :
               msg = HBYEL+HIR "$NĬ��Ǭ��һ��������һ��ָ��������"+weapon->query("name")+HBYEL+HIR"���⣬���������͡����죬����$n��\n";
               
			   msg = msg +CYN "$nֻ���Ŀڴ�һʹ���ѱ�һ�л���"HIR"������Ѩ��"CYN"���ڣ�\n"NOR; 
               target->recevied_damage("qi", j*3 +random(300),me);
               target->add_busy(2+random(3));
               target->apply_condition("no_exert",2);
               me->add("neili",-50-random(50));
               break;
            case 1 :
               msg = HIY "$N�羨��ˮ��ĳ���һ��������Ȼ�ȵ����š����Խ���ָ����Ȼ���Խ���ʩչ����һ��ָ����ʽ��\n";
               msg += HIC"$nֻ��$N�������У���������������Ѩ��"HIR"��������"HIC"���ɵ�һʹ����\n"NOR;
               target->recevied_wound("qi", j*2 + random(300),me);
               target->add_condition("yyz_hurt",3);
               target->add_busy(1+random(2));
               me->add("neili",-50);
              
               break;
            
          }         
          message_vision(msg, me, target);
   }
   return ;
}


