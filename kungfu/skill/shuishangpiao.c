// shuishangpiao.c 
// BY BOBO@SJ
#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
"$n足跟一支，全身后仰，一招「鲤鱼倒穿波」，反窜出丈余，躲过了$N的攻击。\n",
"$n身子悬空，宛如漂在水面上一样，身形飘忽不定，如水中百合，摇曳多姿。\n",
"$n身体忽然柔若无骨，左右摇摆，使出一招「雨打漂萍」，避过了$N的攻击。\n",
"$n使出「物换星移」，滴溜溜一个转身，从$N身旁擦身而过，反而到了$N身后。\n",
"$n见$N向自己奋力一击，招式已经用老，淡然一笑，施展‘水上漂’绝技，闪过一旁。\n",
"$n身子悬空，宛如漂在水面上一样，身形飘忽不定,遇到你的攻击，如‘蜻蜓点水’一粘即走。\n",
"$n一招「落叶随风」，身体如一片落叶一般飘了出去，身行之潇洒，迅速到了极处。\n",
});

int valid_enable(string usage) 
{ 
	return usage == "dodge";
}

int valid_learn(object me)
{
	if ( me->query_skill("guiyuan-tunafa", 1) < 10)
		return notify_fail("你的归元吐纳法等级太低了。\n");
	return 1; 
}

string query_dodge_msg()
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( me->query("jingli") < 30 )
		return notify_fail("你的体力太差了，不能练水上漂。\n");
	me->receive_damage("jingli", 25);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"shuishangpiao/" + action;
}
int ob_hit(object ob, object me, int damage)
{
	string msg;
	int mdodge, tdodge;
	int j = 0;
	mdodge = me->query_skill("shuishangpiao", 1);
	tdodge = ob->query_skill("dodge",1);
	
  
    if (!me->query("tiezhang/pass")) return 0;
    if (!me->query_temp("piao")) return 0;
   

	if( random(me->query_dex(1)) > ob->query_dex(1)/2	 
	 && me->query_skill_mapped("dodge") == "shuishangpiao"
	 && me->query("neili") > 5000
	 && mdodge > 450 ) {
		
		me->add_temp("piao", 1);
		msg=random(2) ? HIR+dodge_msg[random(sizeof(dodge_msg))]+NOR:
			HIC+dodge_msg[random(sizeof(dodge_msg))]+NOR;
       		
		tell_object(ob, BLU "你忽然发现对方似乎如漂浮在水面上一样，摇摆不定，但却恰好躲过了你的攻击！\n" NOR);
		if(random(mdodge*2) >= tdodge+random(tdodge)){
			msg +=HIY"结果$N的力道被$n轻微的摇摆给躲开了！\n"NOR, 
			j = -damage;
		}
		else if(random(me->query("dex")) > ob->query("str")/2){
			msg += MAG"结果$N的力道被躲过了一半！\n"NOR, 
			j=-damage/2;               
		}
		else {
			msg += HIW"结果$n只躲过了$N的少部分力道！\n"NOR, 
			j = -(damage/2+random(damage/2)); 
		}
		message_vision(msg, ob, me);
		return j;
	  }
	//return j;   
}
