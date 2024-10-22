// anying.c
#include <ansi.h>

inherit SKILL;
 
string *dodge_msg = ({
"只见$n一招「浮云随风」，身体向上笔直地纵起丈余，躲过了$N这一招。\n",
"$n一招「倦鸟归林」，向后纵出数丈之远，避开了$N的凌厉攻势。\n",
"$n使出「金鹏展翅」，向一旁飘然纵出，轻轻着地。\n",
"但是$n一招「旭日东升」，身形飘忽，轻轻一纵，早已避开。\n",
"$n一招「影随人移」，身随意转，倏地往一旁挪开了三尺，避过了这一招。\n",
"可是$n使出「变幻无常」，侧身一让，$N这一招扑了个空。\n",
"却见$n足不点地，一招「归去来兮」，往旁跃开数尺，躲了开去。\n",
"$n一招「似左忽右」，身形微晃，有惊无险地避开了$N这一招。\n"
});

int valid_enable(string usage) 
{ 
	return usage == "dodge";
}

int valid_learn(object me)
{
	if ( me->query_skill("linji-zhuang", 1) < 10)
		return notify_fail("你的临济十二庄等级太低了。\n");
	return 1; 
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( me->query("jingli") < 30 )
		return notify_fail("你的体力太差了，不能练暗影浮香。\n");
	me->receive_damage("jingli", 25);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"anying-fuxiang/" + action;
}

int ob_hit(object ob, object me, int damage)
{
	string msg;
	int mdodge, tdodge;
	int j = 0;
	mdodge = me->query_skill("anying-fuxiang", 1);
	tdodge = ob->query_skill("dodge",1);
	
  
    if (me->query_skill("jiuyin-zhengong")< 150) return 0;
    if (!me->query_temp("ljz/fengyun")) return 0;
   

	if( random(me->query_dex(1)) > ob->query_dex(1)/3	 
	 && me->query_skill_mapped("dodge") == "anying-fuxiang"
	 && me->query("neili") > 2000
	 && me->query("env/九阴速成")
	 //&& random(10)>5
	 && mdodge > 450 ) {
		
		msg=random(2) ? HIR+dodge_msg[random(sizeof(dodge_msg))]+NOR:
			HIY+dodge_msg[random(sizeof(dodge_msg))]+NOR;
       		
		message_vision(BLU"$N急中生智，匆忙间运使出九阴真经上的功夫，恰好躲过了$n这致命的攻击！\n" NOR,me,ob);
		j = -damage;
				
		message_vision(msg, ob, me);
		return j;
	}  
	 return j;   
}
