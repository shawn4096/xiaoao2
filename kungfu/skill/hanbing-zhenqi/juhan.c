// by darken@SJ
// Lklv add help at 2001.10.06
// 需要将juhan重新写，做成一个superquest，体现出寒冰真气的牛逼来 聚寒
#include <ansi.h>
inherit F_SSERVER;
string exert_name(){ return HBGRN+HIW"聚寒诀"NOR; }

int exert(object me)
{
	string msg;
	//int i;
	int lv = me->query_skill("hanbing-zhenqi",1);
    
	if (!me->is_fighting())
		return notify_fail("你只能在战斗中使用「聚寒诀」。\n");

	if (lv < 350)
		return notify_fail("以你目前的寒冰真气的修为尚无法使用「聚寒诀」。\n");

	if (me->query("neili") < 300)
		return notify_fail("你的内力不足。\n");
		
	if ( me->query_temp("ss/focus")>15)	
		return notify_fail("你已经将「聚寒诀」发挥得淋漓尽致，无需施展这门奇功了。\n");

	msg = HBBLU+HIW"$N寒冰真气随心而起，内息流动间，周身温度陡然降低，居然结了薄薄一层寒霜！\n"NOR;

	if (!me->query_temp("ss/focus")) {
		call_out("remove_effect", lv/5 + random(10), me);
	}  
	
	me->add("neili",-(200+random(50)));
    
	me->add_temp("ss/focus", (int)lv/200+1);
    
	if ( me->query_temp("ss/focus") > 15 )
		me->set_temp("ss/focus", 15);

	message_vision(msg, me);
	if (!me->query("quest/ss/hbzq/pass"))
		me->start_exert(1, "「聚寒诀」");
	return 1;
}

void remove_effect(object me)
{
	if (!me || !me->query_temp("ss/focus") ) return;
	message_vision(HIW"$N凝聚在周身的寒气渐渐的散去了。\n"NOR,me);
	me->delete_temp("ss/focus");
}

int help(object me)
{
	write(HIW"\n寒冰真气之「聚寒诀」："NOR"\n\n");
        write(@HELP
	寒冰真气乃是五岳嵩山剑派的镇派武技，想当初左盟主在少林寺
	与日月神教教主任我行一战，以寒冰真气击退了任我行的进攻，
	名骚一时。若辅助以嵩山派的武技，效果更佳。战斗中使用，提
	升本身功力,有额外伤害。解开寒冰真气谜题后大飞。
	
	指令：exert juhan
	
要求：  
	寒冰真气  350  以上；
	最大内力  2000 以上；
	当前内力  500  以上；
	当前气超过最大气的 1/3 以上。

HELP
        );
        return 1;
}
