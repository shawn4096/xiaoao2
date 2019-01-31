// qudu.c for hamagong
// Modified by snowman@SJ

#include <ansi.h>

int exert(object me)
{
	mapping poison;

	if( me->is_fighting() )
		return notify_fail("战斗中运功驱毒？找死吗？\n");

	if ((int)me->query_skill("hamagong", 1) < 350)
		return notify_fail("你的蛤蟆功功修为还不够。\n");

	if ((int)me->query_skill("poison", 1) < 150)
		return notify_fail("你对“毒”还不是很精通。\n");

        if( me->query("oyf/hamagong") < 1 ) 
                return notify_fail("你的蛤蟆功功修为还不够。\n");

	if( (int)me->query("neili") < 500 )
		return notify_fail("你的真气不够。\n");

	poison = me->query_conditions_by_type("poison");
	if (!mapp(poison)) 
		return notify_fail("你深深吸了口气，口中“咕咕。。。”地叫了几声。\n");
    		
	write( HIW"\n你倒运气息，头下脚上，气血逆行，将毒气从进入身子之处逼了出去。\n" NOR);
	message("vision", HIW+me->name()+"身上白气一现即消，张口哼了一声。\n"NOR, environment(me), me);
	me->clear_conditions_by_type("poison");
	me->add("neili", -500);
	me->start_busy(6);
	return 1;
}

string exert_name(){ return HIC"驱毒"NOR; }

int help(object me)
{
	write(WHT"\n蛤蟆功「驱毒」："NOR"\n");
	write(@HELP
	欧阳锋的独门绝技蛤蟆功乃是天下武学中的绝顶功夫。
	自从他逆练九阴成疯而又夺得天下第一的称号后，这
	蛤蟆功更大逆寻常武功，更加怪异无伦。这逆转九阴
	之法，便是当年他传与杨过的绝技！
	驱毒绝技乃是将蛤蟆功劲力逆转后的特殊效果，西毒
	本善于使毒，功力逆转后将毒气可以逼出体外，是白
	陀山庄的独门内功心法。

	指令：exert qudu

要求：
	当前内力 1000 以上；
	基本内功 350 级以上；
	基本毒计 150 级以上；
	蛤蟆功法 350 级以上；
	需要成为欧阳锋义子；
HELP
);
	return 1;
}
