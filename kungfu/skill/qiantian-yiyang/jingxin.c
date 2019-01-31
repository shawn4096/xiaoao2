// jingxin.c 静心诀
// 这是官府，是否和官府影响力挂钩？
#include <ansi.h>

int exert(object me)
{
	int skill;
	skill = me->query_skill("buddhism", 1)/10;

	if(me->is_fighting())
	      return notify_fail("你正在战斗中，如何可以静下心来？\n");

	if((int)me->query_skill("qiantian-yiyang",1) < 100 )
	      return notify_fail("你的乾天一阳功不够娴熟，内力的冲撞使你静不下心来！\n");
/*
	if(me->query("class") == "bonze" )
	      return notify_fail("你已经出家，内力的冲撞使你静不下心来！\n");*/

	if((int)me->query_skill("buddhism",1) < 50 )
	      return notify_fail("你的佛学修为不够，无法静下心来潜修！\n");

	if (me->query("neili") < 500  ) 
		return notify_fail("你的内力不够。\n");

	if (me->query_temp("qtyy/jingxin"))
		return notify_fail("你正在运使静心诀。\n");
       
	me->add("neili", -250);

	message_vision(GRN "\n$N双目微闭，只觉心中清静平和，渐渐进入忘我之境。\n" NOR, me);
    if (me->query("yideng/ronghe")=="pass")
    {
		message_vision(GRN "\n$N先天功和乾天一阳相辅相成，浑然忘我。\n" NOR, me);
		skill=skill+me->query_skill("qiantian-yiyang",1)/30;
    }
	me->set_temp("qtyy/jingxin", skill);  
	me->add_temp("apply/intelligence",skill);
    me->add_temp("apply/dexerity",skill);
	call_out("remove_effect", 1, me, me->query_skill("qiantian-yiyang",1)/10);
	return 1;
}

void remove_effect(object me, int d)
{
	int i;

	if (!me) return;
	if (me->query_skill_mapped("force") == "qiantian-yiyang"
	    && --d > 0) {
		call_out("remove_effect", 1, me, d);
		return;
	}
	i = me->query_temp("qtyy/jingxin");
	me->add_temp("apply/intelligence", -i);
    me->add_temp("apply/dexerity",-i);
	me->delete_temp("qtyy/jingxin");
	tell_object(me, HIY "你缓缓舒了口气，从静心状态中退了出来。\n" NOR);
}

string exert_name(){ return GRN"静心诀"NOR; }

int help(object me)
{
        write(GRN"\n乾天一阳功之「静心诀」："NOR"\n\n");
        write(@HELP
	因大理崇尚佛法，最接近禅宗，所以举国之下皆以修禅为胜
	乾天一阳功主要的修炼方式就是通过禅坐方式获得，所以修
	习静心诀后会明心见性,并获得临时身法的增加。

	perform jingxin

要求：
	当前内力的要求 500 以上；
	乾天一阳功等级 100 以上；
	禅宗心法的等级 50 以上；
                

HELP
        );
        return 1;
}
