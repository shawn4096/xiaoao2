// piaoyi-shenfa.c 飘翼身法
#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
"$n身子猛然贴地向后滑出丈余，好似有人用绳缚住以快迅无纶的手法向后扯动一般。\n",
"$n双膝不曲，腰不弯，陡然滑出，身子之僵硬怪诡，又和僵尸无异。\n",
"不见$n提足抬脚，突然之间倒退丈余，一转身。已在数丈之外。\n",
"只听得呼的一声，$n身子笔直的向空中飞起，直至丈余高，躲过了这一招。\n",
"$n陡然身形拔起，在空中急速盘旋，连转四个圈子，愈转愈高，一个转折落在数丈之外。\n",
"$n绕着圈子，东转西闪，滑如游鱼，在间不容发之际躲过了这招。\n",
"$n大吃一惊，不及趋避，足尖使劲，拔身急起，斜飞而上，及时的躲过了这一招。\n",
"$n有如一溜轻烟，左一闪，右一趋，正转一圈，反转一圈，已闪了开去。\n"
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me)
{
	if( !me->query_skill("jiuyang-shengong", 1))
	if ( me->query_skill("shenghuo-shengong", 1) < 10)
		return notify_fail("你的圣火神功等级太低了。\n");
	return 1; 
}

string query_dodge_msg(object me)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( (int)me->query("jingli") < 30 )
		return notify_fail("你的体力太差了，不能练飘翼身法。\n");
	me->receive_damage("jingli", 25);
	return 1;
}

int ob_hit(object ob, object me, int damage)
{
	string msg;
	int mdodge;
	int j = 0;
	mdodge = me->query_skill("piaoyi-shenfa", 1);
	
	
    if (me->query_skill_mapped("dodge") != "piaoyi-shenfa") return 0;
	if (me->query("neili") < 5000) return 0;
	if (mdodge<450) return 0;
	
    if (!me->query("quest/mj/pysf/pass")) return 0;
    if (me->query("env/飘移身法")!="青翼") return 0;
   

	if( random(me->query_dex(1)) > ob->query_dex(1)/3	 
		 || random(me->query_int(1))>ob->query_int(1)/3	 ) {	
		if (random(2)) msg=HIR+dodge_msg[random(sizeof(dodge_msg))]+NOR;
		else msg=HIC+dodge_msg[random(sizeof(dodge_msg))]+NOR;
		message_vision(msg,me,ob);
        j = -damage;		
	 }
	return j;   
}

string perform_action_file(string action)
{
        return __DIR__"piaoyi-shenfa/" + action;
}
