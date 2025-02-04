// yunu-shengfa.c 玉女身法
#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
HIW"$n一招「洛神凌波」，长袖舞动，掩住身形去处，轻飘飘腾身丈外，躲过了$N这一招。\n"NOR,
HIR"$n嫣然一笑，风姿绝代，已借这「一笑倾国」之势，避开了$N的凌厉攻势。\n"NOR,
HIM"$n使出「贵妃醉酒」，满面红晕，脚步踉跄中已饶至$N的身后。\n"NOR,
HIC"$n左足点地，眼看$N杀招堪堪袭来，一招「红拂夜奔」，身躯已借势平移，闪过一旁。\n"NOR,
MAG"$n一式「绿珠坠楼」，身体贴地滑行，真叫人匪夷所思，令$N的攻击已然扑空。\n"NOR,
});

int valid_enable(string usage) { return (usage == "dodge"); }

int valid_learn(object me)
{
	if ( me->query_skill("yunu-xinjing", 1) < 10)
		return notify_fail("你的玉女心经等级不够，无法领悟玉女身法的要诀。\n");
	return 1;
}

string query_dodge_msg(object me)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if((int)me->query("jingli") < 30 )
		return notify_fail("你该休息一下了，等会再练玉女身法吧。\n");
        me->receive_damage("jingli", 10);
	return 1;
}

mapping query_action(object me, object weapon)
{
	int level,out;
	level   = (int) me->query_skill("yunu-shenfa",1);
	out = (stringp(environment(me)->query("outdoors"))?1:0);
	
	if(me->query("family/family_name")!="古墓派")
		return ([
			"action":dodge_msg[random(sizeof(dodge_msg))], 
			"dodge": -level/3,
		]);
	if(me->query("gender") == "男性")
		return ([
			"action":dodge_msg[random(sizeof(dodge_msg))],
			"dodge": level/3 + me->query_con() - out*level/5,
		]);
	else
		return ([
			"action":dodge_msg[random(sizeof(dodge_msg))],
			"dodge": level/2 + me->query_per()*4 - out*level/5,
		]);
}
int ob_hit(object ob, object me, int damage)
{
	string msg;
	object room;
	int mdodge, tdodge,i;
	int j = 0;
	mdodge = me->query_skill("yunu-shenfa", 1);
	tdodge = ob->query_skill("dodge",1);
	room=environment(me);
	
	if (!room->query("outdoors")
		&& me->query_temp("ynxj/xinjing")
		&& !me->query_temp("ynsf/temp"))
	{
		i=20;	
		message_vision(HIW"\n此时$N正处于室内激斗，玉女身法在方寸间的灵活性展现的淋漓极致！\n"NOR,me);
		me->add_temp("apply/dodge",mdodge/2);
		me->add_temp("apply/defense",mdodge/2);
		me->set_temp("ynsf/temp",mdodge);
		call_out("ynsf_indoor",1,me);
	}else i=10;

    if (me->query_skill_mapped("dodge") != "yunu-shenfa") return 0;
	if (me->query("neili") < 5000) return 0;
	if (mdodge<450) return 0;
	//if (!me->query("env/古墓九阴")) return 0;  
	
	if (me->query("quest/jiuyingm/pass")
		&& damage>2000
		&& me->query("env/古墓九阴")
		&& random(3)) 		
	 {
		message_vision(HIW "$N忽然将九阴真经的功夫忽然施展出来，身法变得渐渐飘渺起来，躲过这致命一击。\n" NOR,me,ob);
	    return -damage;
	 }

	 if( random(me->query_dex(1)) > ob->query_dex(1)/2	 
		 && random(me->query_int(1))>ob->query_int(1)/2	
		 && i >6)
	 {
		
		
		msg=random(2) ? HIR+dodge_msg[random(sizeof(dodge_msg))]+NOR:
			HIC+dodge_msg[random(sizeof(dodge_msg))]+NOR;
		message_vision(msg,me,ob);
        j=-damage;	
		return j;   
	 }
	

}

int ynsf_indoor(object me)
{
	int mdodge;
	object room;

	if (!me) return 0;
	mdodge=me->query_temp("ynsf/temp");
	room=environment(me);
	if ((room->query("outdoors") || (me->query_skill_mapped("dodge") != "yunu-shenfa") )&&me->query_temp("ynsf/temp"))
	{
		me->add_temp("apply/dodge",-mdodge/2);
		me->add_temp("apply/defense",-mdodge/2);
		me->delete_temp("ynsf/temp");
		message_vision(HIW"$N身处室外或已改变身法导致玉女身法在室内的优势丧失！\n"NOR,me);
		return 1;
	}
	call_out("ynsf_indoor",1,me);
}