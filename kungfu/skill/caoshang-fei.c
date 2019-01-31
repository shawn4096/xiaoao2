// caoshang-fei.c 草上飞轻功
// Created by snowman@SJ 06/03/2001
#include <ansi.h>
inherit SKILL;
 
string *dodge_msg = ({
  	"只见$n双足一点，身子飞起，眼见无法避开的攻击，竟然给$n闪了开去。\n",
  	"$n身形一扭，竟从$N招式之间溜了过去，宛如在草上飞纵一般，轻如鸿毛。\n",
  	"$n向一旁飘然纵出，轻轻着地。\n"
  	"但是$n身形飘忽，轻轻一纵，早已避开。\n",
  	"$n身随意转，倏地往一旁挪开了三尺，避过了这一招。\n",
  	"$N但见眼前灰影一闪，$n以快捷无伦的身法已经飘了开去。\n",
  	"却见$n足不点地，往旁跃开数尺，躲了开去。\n",
  	"$n身形微晃，有惊无险地避开了$N这一招。\n"
});

int valid_enable(string usage) 
{ 
    	return usage == "dodge"; 
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("jingli") < 30 )
            	return notify_fail("你的体力太差了，不能练草上飞轻功。\n");
        me->receive_damage("jingli", 25);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"caoshang-fei/" + action;
}


int ob_hit(object ob, object me, int damage)
{
	string msg;	
	int mdodge, tdodge,i;
	int j = 0;
	mdodge = me->query_skill("caoshang-fei", 1);
	tdodge = ob->query_skill("dodge",1);
	

    if (me->query_skill_mapped("dodge") != "caoshang-fei") return 0;
	if (me->query_skill_mapped("force") != "baduan-jin") return 0;
	if (me->query("neili") < 4000) return 0;
	if (mdodge<450) return 0;	
	// && (damage>2000) && (random(3))
	if (me->query("quest/baduanjin/pass2") && (!me->query("family")) && (damage>2000) && (random(3)))
	 {
		
		message_vision(HIW "$N忽然将八段锦秘传功夫施展出来，身法变得灵动异常，躲过这致命一击。\n" NOR,me,ob);
	    return -damage;
	 } 

}


