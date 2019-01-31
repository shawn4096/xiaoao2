// riyue-bian.c ���±޷�

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([
	"action": "$N����������һʽ�������ɴ̡���������̧��$w�������裬���������Ҳ���ǰ�����ƣ�����մճ��ɢ",
	"lvl" : 0,
	"skill_name" : "�����ɴ�",
	"damage_type":  "����"
]),
([
	"action": "$Nһʽ��Ŀ�����̡�������$w�ж��ñ�ֱ�������ڡ�������$n���̶�������Ю��������$nһ������",
	"lvl" : 30,
	"skill_name" : "Ŀ������",
	"damage_type":  "����"
]),
([
	"action": "$N�ھ���������$w����ת������ԲȦ��һʽ��������̡���Ծ��Ӱ������$n$l����",
	"lvl" : 60,
	"skill_name" : "�������",
	"damage_type":  "����"
]),
([
	"action": "$N����������һʽ����¥�Ǵ̡���$w��$n��ǰ��Ȧ�¹���������ת��������������ʽ����Ȼ��$n$l����������",
	"lvl" : 90,
	"skill_name" : "��¥�Ǵ�",
	"damage_type":  "����"
]),
([
	"action": "$Nһ���ߺȣ�����������һʽ�������Ӵ̡���$w����ת������Ӱ�ݺᣬֱ����Բ��Բ����ֱ�������ƻã�����$n",
	"lvl" : 120,
	"skill_name" : "�����Ӵ�",
	"damage_type":  "����"
]),
([
	"action": "$N���ذα�������׹�⣬һʽ�������̡ܴ��������鶯���ͣ���ʵ����������������˷���$n��ѹ��ȥ",
	"lvl" : 150,
	"skill_name" : "�����ܴ�",
	"damage_type":  "����"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;

	if(!me->query("family") || me->query("family/family_name")!="������" )
		return notify_fail("�㲻�����ֵ��ӣ�������������±޷���\n");

	if ( me->query_skill("ranmu-daofa",1)
	 || me->query_skill("weituo-chu",1) 
	 || me->query("pass_xin"))
		return notify_fail("������д�Ħ�������Ϊ������ͬʱѧϰ������������\n");

	if ( me->query("max_neili") < 1500 )
		return notify_fail("���������Ϊ���㣬û�а취�����±޷���\n");
	if ( me->query_skill("buddhism") < 220)
	{
		if ( me->query_skill("ranmu-dao", 1)
		 || me->query_skill("weituo-chu", 1))
			return notify_fail("��ķ��������������޷�ͬʱ��ϰ�������ϵ��ϳ˱�������\n");
	}
	if ((int)me->query_skill("yijin-jing", 1) < 130)
		return notify_fail("����׽�񹦻��̫ǳ��\n");

	if ( !objectp(weapon = me->query_temp("weapon"))
	|| ( string)weapon->query("skill_type") != "whip" )
		return notify_fail("���������һ�����Ӳ������޷���\n");
	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object target)
{
	int i, level, j;
     
	if(me->query_temp("ryb/riyue"))
	{
		if (me->query_temp("ryb/rilun"))
		{
			return ([
//                         "action":HIB+action[random(sizeof(action))]["action"]+NOR,
				"action":HIY+replace_string(replace_string(action[random(sizeof(action))]["action"], "$w", "$W"), "$W", "$w"HIY)+NOR,
				"damage": 250 + random(100),
                "dodge":  20+random(30),
                "force": 350 + random(250),
                "parry": 20+random(30),
				"damage_type":"����",
			]);
		}
		if (me->query_temp("ryb/yuelun"))
		{
			return ([
//                         "action":HIB+action[random(sizeof(action))]["action"]+NOR,
				"action":HIW+replace_string(replace_string(action[random(sizeof(action))]["action"], "$w", "$W"), "$W", "$w"HIW)+NOR,
				"damage": 300 + random(100),
                "dodge":  20+random(30),
                "force": 350 + random(250),
                "parry": 20+random(30),
				"damage_type":"����",
			]);
		}
		return ([
//                         "action":HIB+action[random(sizeof(action))]["action"]+NOR,
				"action":BLU+replace_string(replace_string(action[random(sizeof(action))]["action"], "$w", "$W"), "$W", "$w"BLU)+NOR,
				"damage": 200 + random(100),
                "dodge":  20+random(30),
                "force": 350 + random(250),
                "parry": 20+random(30),
				"damage_type":"����",
		]);
	}
//����������±޷�
	if(me->query("env/���±޷�") =="����"
		&& me->query_skill("parry",1) > 500 
		&& me->query("neili") > 1000 
		&& me->query("jingli") > 300 
		&& me->query("jiali") > 100
		&& random(me->query_str(1)) >= 40 
		&& random(me->query_skill("riyue-bian",1)) > 500)
	{
		me->add("neili", -10);
		if (random(me->query_str(1)) >= 45 
			&& me->query_skill("riyue-bian",1)> 200) 
		{           
			me->add("neili", -10);
			target->add_busy(1+random(2));
			target->receive_damage("jing",1000+random(1000),me);
			target->receieve_damage("jingli",1000+random(1000),me);
			return ([
				"action": HIR "$N������$w"HIR"������Ȧ������$nԽתԽ����ԽתԽ�죬$p��ʱ�����������׵���ת�˼�����ð���ǣ�����ˤ����"NOR,
				"force": 400 + random(300),
				"dodge": 30,
				"parry": 30,
				"damage" : 180 + random(100),
				"damage_type": "ˤ��"
			]);
		}
		return ([
			"action": HIR "$N����һ�������������$w"HIR"������º�$n����һ��һ����ɽ�������ھ�����Ϣ����$n�ؿ�ײȥ��"NOR, 
			"force": 300 + random(350),
			"dodge": 30,
			"parry": 30,
			"damage" : 130 + random(140),
			"damage_type": "����"
		]);
	}
	level   = (int) me->query_skill("riyue-bian",1);
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action": action[j]["action"],
				"damage_type": action[j]["damage_type"],
				"lvl": action[j]["lvl"],
				"force": 200 + random(350),
				"dodge": random(30)-10,
				"damage": 80 + random(140),
				"parry": random(20),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("riyue-bian", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 50)
		return notify_fail("����������������±޷���\n");

	if ((int)me->query("neili") < 20 )
		return notify_fail("����������������±޷���\n");
    if ( me->query_skill("buddhism") < 220)
	{
		if ( me->query_skill("ranmu-dao", 1)
		 || me->query_skill("weituo-chu", 1))
			return notify_fail("��ķ��������������޷�ͬʱ��ϰ�������ϵ��ϳ˱�������\n");
	}
          
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
	object weapon, weapon1;    
	int ap , dp;

	weapon=me->query_temp("weapon");
	weapon1=victim->query_temp("weapon");
	if (!me->query_temp("ryb/fumoquan")) return 0;
	
	if (victim->query("shen")<-10000
		||(victim->query_skill_mapped("dagger")=="shenghuo-lingfa" && objectp(weapon1)&&weapon1->query("skill_type")=="dagger")
		&&random(10)>7)
	{
			victim->add_busy(1);
			message_vision(YEL"$Nʩչ�������ڵķ��Ź���,���ÿ�����$n�Ĺ�����$n�پ��ĸ����꣬�̲�ס�����Ц������\n"NOR,me,victim);
	}

	if(objectp(weapon) && objectp(weapon1))
	{
		if (random(me->query_skill("riyue-bian",1)) <100) return 0;
		if (random(10)>4 ) return 0;

		ap = me->query("combat_exp") /100000 * me->query("str");
		dp = victim->query("combat_exp")/ 100000 * victim->query("str");

		if( random(ap + dp ) > dp && weapon1->query("imbued") < 3 && weapon1->query("rigidity") < 5){
			message_vision(HIY"ֻ������ৡ���һ�����죬$N���е�"+weapon1->name()+HIY"�Ѿ���"+weapon->name()+HIY"��Ϊ���أ�\n"NOR, victim );
			weapon1->broken("�ϵ���");
			return 0;
		}
		else if ( weapon1->query("rigidity") < 5 )  {
			ap = me->query_str(1)+ me->query("jiali") +  me->query_skill("parry")/3;         
			dp = victim->query_str(1)+ victim->query("jiali") + victim->query_skill("parry")/3;
			ap *= me->query("combat_exp") /1000;
			dp *= victim->query("combat_exp")/1000;
			if (random(ap + dp) > dp ) {
				message_vision(HIY "ֻ�������������죬$N���е�"+weapon1->name()+HIY"�Ѿ���"+weapon->name()+"����һ���ѳֲ������ַɳ���\n"NOR, victim );
				victim->add_busy(random(2)+ 2);
				weapon1->move(environment(victim));
				victim->reset_action();
			}
		}
	}
	return 0;
}


int ob_hit(object ob, object me, int damage)
{
	//string msg;
	int j;
	object weapon;
	j = me->query_skill("riyue-bian", 1);
	if (!objectp(weapon=me->query_temp("weapon"))
		||weapon->query("skill_type")!="whip") 
		return 0;

	if (!objectp(ob)) return 0;
	
	if (me->query("yjj/powerup"))
	{
		j=j+me->query_skill("yijin-jing", 1);
	    j=j+random(j/2);
	}
	//if ( me->query_temp("mr_ci") ) return 0;
  
	if ( random(me->query_str(1)) >= ob->query_dex(1)/3
		&&j > 120 
		&& random(10) > 5
	 	&& random(me->query("combat_exp")) > ob->query("combat_exp")/2
		&& me->query("neili") > 500) 
       {
		  switch(random(3)) {
			case 0 :
				message_vision( HIW"$N���ֳû�һ����һ��"HIG"��ֱ�̾���"HIW"ʹ������ͷ��Ȼ�����ֱ�����糤ǹ��ꪣ�����$n��\n",me,ob);
				message_vision( HIR"$nֻ��������Ѩ��һʹ����ʱ�����У��۵��³�һ����Ѫ��\n"NOR,me,ob); 
				ob->add_busy(1+random(3));
				ob->receive_damage("qi",2000+random(2000),me);
				me->add("neili",-random(300));
				break;
			case 1 :
				message_vision(CYN"$N�������澭�Ĺ�����ʹ���������ӽ���������һ��"HIR"����������"CYN"����$nȦס����Ӱ��ɽ����$n�������ڣ�\n"NOR,me,ob);
				ob->recevied_wound("qi", 3000+random(2000),me);
				ob->add_condition("no_perform",1);
				
				if (ob->query("neili") < 0 )
					ob->set("neili", 0);
				me->add("neili",-random(500));
				break;

            case 2 :
				
				message_vision(HIR"$N��$n�嵽��ǰ����Ȼ���ɿ�����ʽ������ʵ�޻���һ������$n���ؿڡ�\n",me,ob);
			    message_vision(RED"$nֻ���Ŀ�Ϊ�����У�һ�ɾ�ʹ��������Ѫ���������\n"NOR,me,ob); 
				ob->recevied_damage("qi", 1000+random(1500),me);
				ob->recevied_wound("qi", 1000+random(500),me);
				me->add("neili",-random(200));
				break;
		  
		  }
		
	}
}
string perform_action_file(string action)
{
	return __DIR__"riyue-bian/" + action;
}
