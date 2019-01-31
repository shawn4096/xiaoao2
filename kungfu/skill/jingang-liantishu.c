// jingang-liantishu

#include <ansi.h>
inherit SKILL;
#include <combat.h>
mapping *action = ({
([
	"action" : "$Nһʽ��Τ�����ơ���˫��ֱ��ֱ�£��͹���ǰ������$n��$l",
	"lvl" : 0,       
	"damage_type" : "����"
]),
([
	"action" : "$N˫Ŀһ�ɣ������գ�����ǰ�㣬��ȭֱ������һ������$n������һ�С����ŭĿ��",
	"lvl" : 10,
	"damage_type" : "����"
]),
([
	"action" : "$Nʹ�С��𷨽�ħ������������һ�������ȭ����$n",
	"lvl" : 20,
	"damage_type" : "����"
]),
([
	"action" : "$N˫ȭ����������У����������дʣ�һ�С��������硹����$n",
	"lvl" : 30,
	"damage_type" : "����"
]),
([
	"action" : "$N������������һת������а���֡������غ�˫ȭ���������$n��$l��",
	"lvl" : 40,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { 
	// mapping fam;
     //if (this_player()->query("family"))  
	  return usage=="cuff" || usage=="strike"|| usage=="leg"|| usage=="parry"; 
	 //else return "ֻ����ͨ���շ�����ϰ�����似��\n";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����������������֡�\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������̫�����޷�������\n");
	return 1;
}
int practice_skill(object me)
{

        if (me->query_temp("weapon"))
			return notify_fail("ֻ�п��ֲ����������������");
     

        if ((int)me->query("neili") < 40)
       	        return notify_fail("����������㣬û�а취��ϰ�����������\n");

        if ((int)me->query("qi") < 50)
        	return notify_fail("������������������������\n");
		if (me->query_skill("jingang-liantishu",1)==100 && me->query("xuedao/jingmai")!="1")
		{
			//me->add("max_neili",2+random(3));
			me->set("xuedao/jingmai",1);
			message_vision(CYN"��������һ�����澭������һ��������ͨ���������������������С�ɣ�\n"NOR,me);
		}
		if (me->query_skill("jingang-liantishu",1)==200 && me->query("xuedao/jingmai")!="2")
		{
			//me->add("max_neili",4+random(4));
			me->set("xuedao/jingmai",2);

			message_vision(HIC"��������һ�����澭�����ڶ���������ͨ��������������������г�Ч��\n"NOR,me);
		}
		if (me->query_skill("jingang-liantishu",1)==300 && me->query("xuedao/jingmai")!="3")
		{
			//me->add("max_neili",8+random(8));
			me->set("xuedao/jingmai",3);

			message_vision(HIC"��������һ�����澭����������������ͨ�����������������С��Բ����\n"NOR,me);
		}
		if (me->query_skill("jingang-liantishu",1)==400 && me->query("xuedao/jingmai")!="4")
		{
			//me->add("max_neili",16+random(16));
			me->set("xuedao/jingmai",4);

			message_vision(HIC"��������һ�����澭����������������ͨ������������������������ң�\n"NOR,me);
		}
		if (me->query_skill("jingang-liantishu",1)==500 && me->query("xuedao/jingmai")!="5")
		{
			//me->add("max_neili",25+random(25));
			me->set("xuedao/jingmai",5);

			message_vision(HIC"��������һ�����澭����������������ͨ����������������������ĵã�\n"NOR,me);
		}
		if (me->query_skill("jingang-liantishu",1)==550 && me->query("xuedao/jingmai")!="6")
		{
			//me->add("max_neili",30+random(30));
			me->set("xuedao/jingmai",6);

			message_vision(HIC"��������һ�����澭����������������ͨ������������������Ƿ��켫��\n"NOR,me);
		}
		if (me->query_skill("jingang-liantishu",1)==600 && me->query("xuedao/jingmai")!="7")
		{
			//me->add("max_neili",50+random(50));
			me->set("xuedao/jingmai",7);

			message_vision(HIC"��������һ�����澭����������������ͨ�����������������Բת���⣡\n"NOR,me);
		}
		if (me->query_skill("jingang-liantishu",1)==700 && me->query("xuedao/jingmai")!="8")
		{
			//me->add("max_neili",100+random(100));
			me->set("xuedao/jingmai",8);

			message_vision(HIC"��������һ�����澭�����ڰ���������ͨ��������������������뻯����\n"NOR,me);
		}
        me->receive_damage("qi", 50);
		//������������������������
        me->add("neili",5);
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
	level   = (int) me->query_skill("jingang-liantishu",1);
	
	
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			if (me->query_temp("jglts/jingang"))
			{
				return ([  
				"action":	HIY+action[j]["action"]+NOR,
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"force":	100+random(250),
				"dodge":	random(20)-10,
				"damage":	150+random(50),
				"parry":	random(10),
			     ]);
			}
			
			return ([  
				"action":	action[j]["action"],
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"force":	100+random(250),
				"dodge":	random(20)-10,
				"parry":	random(10),
			     ]);
		     
		}
	}
}



string perform_action_file(string action)
{
	return __DIR__"jingang-liantishu/" + action;
}


//����������ĵ�����Ч


int ob_hit(object ob, object me, int damage)
{
	string msg;
	int ap, dp, j, neili, neili1;
	object weapon;

	if( damage < 100) return 0;

	neili = me->query("neili");
	neili1 = ob->query("neili");
	//�������⣬û�з���Ч��
	if(!me->query("quest/xd/jglts/jingang/pass")) {
		return 0;
	}

	if( me->query_temp("fanzhen")) {
		me->delete_temp("fanzhen");
		return 0;
	}

	if (me->query_skill("parry",1) < 350
	 || me->query_skill_mapped("parry") != "jingang-liantishu"
	 || me->query_skill_mapped("force") != "xuedao-jing"
	 || me->query("combat_exp") < ob->query("combat_exp")/3
	 || neili < 400 ) return 0;

	weapon = ob->query_temp("weapon");

	if(objectp(weapon))
		msg = weapon->query("skill_type");
	else {
		mapping prepare = ob->query_skill_prepare();
		if (!sizeof(prepare)) msg = "unarmed";
		else msg = keys(prepare)[0];
	}

	ap = COMBAT_D->skill_power(ob, msg, SKILL_USAGE_ATTACK) / 1000;
	
	if ( weapon ) ap *= 2;
	if ( ob->query("neili") > me->query("neili") * 2 ) ap += ap/2;
        
	dp = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE) / 1000;
	if ( me->is_busy() ) dp /= 2;   
	if ( me->query("neili") > ob->query("neili") * 2 ) dp *= 2;  
	else if ( me->query("neili") > ob->query("neili") / 2 * 3 ) dp += dp/2;
         
	if ( random(10) < 3 ) me->set_temp("fanzhen", 1);

	ap = ABS(ap);
	dp = ABS(dp);

	if ( me->query_temp("xdj/yuxue"))
		dp += ap/2 + random(ap/2);
	if ( wizardp(me))
		tell_object(me, sprintf("ap: %d, dp: %d\n", ap, dp));

	if( random(dp) > ap && random(3)) {
		msg = RED "$NĬ��Ѫ�����ġ���ա��⣬$N������������һ�㵭����Ѫ��֮ɫ��\n" NOR;
		tell_object(ob, RED "��ֻ������ͻȻ����һ�࣬��Ȼ���㲻��������ӭ����һ�У�\n" NOR);
		msg +=RED "$nһ�д���$N�����ϣ�ֻ���ƺ�����һ��ʯͷ��һ����\n"NOR;
		if(neili >= neili1*2 + random(damage)) {
			msg +=WHT "���$n�Ĺ�����$N�ġ�������ǡ������ˣ�\n"NOR,
			j = -damage;
		}
		else if( neili > neili1 + random(damage) ) {
			msg += WHT"���$n�Ĺ�����$N�ġ�������ǡ�������һ�룡\n"NOR,
			j = -damage/2;
		}
		else {
			msg += WHT"���$Nֻ������$n��һС��������\n"NOR,
			j = -damage/4;
		}
		message_vision(msg, me, ob);
		return j;
	}
}
//������Ч����parry
int query_effect_parry(object attacker, object me)
{
        object weapon;
        int lvl;

		if (me->query_skill_mapped("parry")=="���������"&&me->query("family/family_name")=="Ѫ����")
		
        lvl = me->query_skill("jingang-liantishu", 1);
        if (lvl < 90)  return 0;
        if (lvl < 100) return 50;
        if (lvl < 125) return 55;
        if (lvl < 150) return 60;
        if (lvl < 175) return 65;
        if (lvl < 200) return 70;
        if (lvl < 225) return 75;
        if (lvl < 250) return 80;
        if (lvl < 275) return 85;
        if (lvl < 325) return 90;
        if (lvl < 350) return 100;
		if (me->query("quest/xd/xdj/xuedao/pass")) return 120; 
		
}
