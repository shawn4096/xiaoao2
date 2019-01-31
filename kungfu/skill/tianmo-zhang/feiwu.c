// feiwu 天魔飞舞
// 多招堆叠在一起，只出一招，初级武技
// cre by sohu@xojh 
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
      string *limbs;
	int count, damage = 0;
	int arg=(int)(me->query_skill("tianmo-zhang", 1) / 40);
	if (arg<4) arg=4;
	
    if (arg>10) arg=10; //限制在六招，作为初始技能
    
	if( !target ) target = offensive_target(me);

	if( !target ||!living(target)|| !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「天魔飞舞」只能在战斗中对对手使用。\n");

	if( objectp( me->query_temp("weapon")) )
		return notify_fail("只有空手才能施展「天魔飞舞」。\n");
    if( me->query_skill_mapped("dodge")!="huanmo-wubu" )
		return notify_fail("需要激发幻魔舞步方能施展「天魔飞舞」。\n");
	if( (int)me->query_skill("tianmo-zhang", 1) < 100 )
		return notify_fail("你的天魔掌法并不娴熟，不会使用「天魔飞舞」。\n");

	if( (int)me->query_skill("tianmo-gong", 1) < 100 )
		if( (int)me->query_skill("xixing-dafa", 1) < 100 )
		return notify_fail("你的特殊内功等级不够，不能使用「天魔飞舞」。\n");

	if( (int)me->query_dex() < 25 )
		return notify_fail("你的身法不够强，不能使用「天魔飞舞」。\n");

	if( arg <= 1 )
		return notify_fail("至少要有两招才可组成「天魔飞舞」。\n");

	if( (int)me->query("neili", 1) < 1200 )
		return notify_fail("你现在内力太弱，不能使用「天魔飞舞」。\n");

	if( (int)me->query("neili", 1) < 50 * arg )
		return notify_fail("你现在的内力施展不了那么多招。\n");

//	if( (int)me->query_skill("tianmo-zhang", 1) < arg * 30 )
//		return notify_fail("你的天魔飞舞掌法还没有修练到那种境界！\n");
    damage=me->query_skill("tianmo-zhang",1);
	message_vision(HIG"$N突然左掌向前一探，右掌倏地拍出，身随掌行，奔行愈速，双掌忽缓忽急拍出"+ chinese_number(arg) +"掌。\n\n"
						+HIY"这些招式如疾风暴雨，又恰似电闪雷鸣，迅捷无比，$n一时不查，陷入这片掌影之中。\n"NOR,  
	              me, target);
    if (userp(target)) target->add_busy(1);
    else target->add_busy(2+random(2));
	limbs = target->query("limbs");
	for(count = 0; count < arg; count++){
	  message_vision(replace_string( HIC+SKILL_D("tianmo-zhang")->query_action(me, me->query_temp("weapon"))["action"]+NOR,	"$l", limbs[random(sizeof(limbs))]) + "！\n\n", me, target);
      damage = damage*arg;
	}    
    //message_vision("damage1="+damage,me);
	damage = (int)me->query("dex")/10 * damage;
	//message_vision("damage2="+damage,me);
	if (damage>8000) damage=8000+random(1000);
	
	if( arg*(random(me->query("combat_exp"))) > target->query("combat_exp") )
	{
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/5,me);
		COMBAT_D->report_status(target, 1);
		//COMBAT_D->report_status(target, 0);
	}
     COMBAT_D->do_attack(me,target, me->query_temp("weapon"),1);

     me->add("neili", -50 * arg);
     me->start_busy(1);
	 me->start_perform(3,"天魔飞舞");
	 return 1;
}
string perform_name(){ return HIY"天魔飞舞"NOR; }
int help(object me)
{
	write(HIG"\n天魔掌之「天魔飞舞」：\n"NOR);
	write(@HELP
	天魔掌乃是日月神教历代高手千锤百炼的空手武技，乃是门下弟子
	习练的主要空手武技。后来任我行在少林与方证大师一战，天魔掌
	的奥妙方为人所知。
	天魔飞舞乃是利用高超的身法优势，围绕对方施展幻魔舞步，不断
	出掌，快速无比，宛如蝴蝶飞舞，多道掌力叠加后凝聚在一起，向
	对方打去，威力无与伦比。	

指令：perform strike.feiwu

要求：	
	天魔掌等级 100 以上；
	基本掌法等级 100 以上；
	天魔功等级 100 以上（或吸星大法）；
	最大内力 1200 以上； 
	最小身法需求 25；
	当前内力需为蓄积的招式有关。
	需要激发幻魔舞步为特殊轻功
HELP
	);
	return 1;
}

