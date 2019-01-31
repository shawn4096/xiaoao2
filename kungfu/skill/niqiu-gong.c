// niqiu-gong.c 泥鳅功，瑛姑绝技，在泥潭中练习所得
//cre by sohu@xojh

#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
HIW"哪知$n身子微侧，左手前臂斜推轻送，竟将$N的劲力力化在一旁。\n"NOR,
HIR"$N只觉$n肩上却似涂了一层厚厚的油脂，溜滑异常，竟然避开了$N的凌厉攻势。\n"NOR,
HIM"$n身手快捷之极，早已乘势直上，双手五指成锥，分截$N胸口“神封”、“玉书”两穴，确是上乘点穴功夫。\n"NOR,
HIC"$N只觉一股劲力从$n身上右臂发出，撞向自己上臂，敌在主位，己处奴势，当下仍以刚才用过的“泥鳅功”将$N的手臂滑了开去。\n"NOR,
MAG"$N一触到$n的肩头，却似碰到一件异常油腻滑溜之物一般，竟然抓之不住\n"NOR,
CYN"$n一低头，人似水蛇，已从$N腋下　钻了过去\n"NOR,
CYN"$n宛如一个泥鳅，滑不留手，$N拿捏不住，给溜了过去\n"NOR,
HIG"$N刚触及$n腰间，但不知怎的，触处只觉油光水滑，给$n一溜便溜了去。\n"NOR,

});

int valid_enable(string usage) { return (usage == "dodge"); }

int valid_learn(object me)
{
	if ( me->query_skill("force", 1) < 100)
		return notify_fail("你的基本内功等级不够100级，无法领悟泥鳅功法的要诀。\n");
	if ( me->query_skill("dodge", 1) < 100)
		return notify_fail("你的基本轻功等级不够100级，无法领悟泥鳅功法的要诀。\n");
	return 1;
}

string query_dodge_msg(object me)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if((int)me->query("jingli") < 30 )
		return notify_fail("你该休息一下了，等会再练泥鳅功吧。\n");
        me->receive_damage("jingli", 10);
	
		return 1;
}

mapping query_action(object me, object weapon)
{
	int level,out;
	level   = (int) me->query_skill("niqiu-gong",1);
	out = (stringp(environment(me)->query("outdoors"))?1:0);
	
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
	int mdodge, tdodge;
	int j = 0;
	mdodge = me->query_skill("niqiu-gong", 1);
	tdodge = ob->query_skill("dodge",1);
	
    if (me->query_skill_mapped("dodge") != "niqiu-gong") return 0;
	if (me->query("neili") < 5000) return 0;
	if (mdodge<450) return 0;
	if (!me->query_temp("niqiu/fast")) return 0;  
	
	if (me->query("env/泥鳅功")!="泥鳅") return 0;
	
	if (me->query("quest/niqiugong/pass") && random(10)>7) 		
	{
		message_vision(HIC "$N忽然身子一阵扭曲，蜿蜒而行，宛如一条泥鳅般油滑无比，堪堪躲过这致命一击。\n" NOR,me,ob);
	    return -damage;
	 }
    else if (me->query("gender")=="女性"&& random(10)>6) 
    {
		if( random(me->query_dex(1)) > ob->query_dex(1)/3)	 
			//|| random(me->query_int(1))>ob->query_int(1)/3	 )
		{
		
			msg=random(2) ? HIR+dodge_msg[random(sizeof(dodge_msg))]+NOR:
				HIC+dodge_msg[random(sizeof(dodge_msg))]+NOR;
			message_vision(msg,me,ob);
			j=-damage/3;		
		}
    }else if (me->query("gender")=="男性"&& random(10)>7)
    {
		if( random(me->query_dex(1)) > ob->query_dex(1)/2)	 
			// || random(me->query_int(1))>ob->query_int(1)/2	 )
		{
		
			msg=random(2) ? HIR+dodge_msg[random(sizeof(dodge_msg))]+NOR:
				HIC+dodge_msg[random(sizeof(dodge_msg))]+NOR;
			message_vision(msg,me,ob);
			j=-damage/4;		
		}	
    }
	
	return j;   
}
string perform_action_file(string action)
{
	return __DIR__"niqiu-gong/" + action;
}
