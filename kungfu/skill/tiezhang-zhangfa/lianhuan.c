// lianhuan.c  夺命连环掌
// Create by lsxk@hsbbs 2007/5/15

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

string perform_name(){ return CYN"夺命连环掌"NOR; }

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lev;
        lev = ((int)me->query_skill("tiezhang-zhangfa", 1) + (int)me->query_skill("force", 1))/3;
        //if(!userp(me)) lev = lev / 2;

		if( !target ) target = offensive_target(me);

        if( !target 
          || !me->is_fighting(target)
          || !objectp(target)

		  || environment(target)!= environment(me))
                return notify_fail("「夺命连环掌」绝技只能在战斗中使用。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「夺命连环掌」绝技?\n");   
        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 400 )
                return notify_fail("你的铁掌掌法还不够娴熟，使不出「夺命连环掌」绝技。\n");

        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
        || me->query_skill_mapped("parry") != "tiezhang-zhangfa"
        || me->query_skill_mapped("strike") != "tiezhang-zhangfa")
                return notify_fail("你现在无法使用「夺命连环掌」绝技进行攻击。\n");  

        if( (int)me->query_skill("force", 1) < 400)
                return notify_fail("你的基本内功等级还不够，使不出「夺命连环掌」绝技。\n");

        if( me->query("max_neili") < 3500)
                return notify_fail("你现在内力修为太差，使不出「夺命连环掌」。\n"); 

        if( (int)me->query("neili") <1500 )
                return notify_fail("你现在真气太弱，使不出「夺命连环掌」。\n"); 

        if( (int)me->query("max_jingli") < 2000)
                return notify_fail("你现在精力修为太差，使不出「夺命连环掌」。\n"); 

        if( (int)me->query("jingli") < 600 )
                return notify_fail("你现在精力太差，使不出「夺命连环掌」。\n"); 

        message_vision(HIM"\n$N突然大喝一声，运掌如风，双掌连环拍出，正是铁掌掌法之精髓「夺命连环掌」绝技！\n"NOR,me);

        me->add_temp("apply/strike", lev);

		me->add_temp("apply/attack", lev);
        me->add_temp("apply/strength",(int)me->query("str"));
        me->add_temp("apply/damage", lev);
        me->set_temp("tiezhang", 1);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (lev>449)?3:1);
        //if(me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (lev>449)?3:1);
        //if(me->is_fighting(target)) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        //if(me->is_fighting(target)) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 4);
        me->add_temp("apply/strike", -lev);
 
		me->add_temp("apply/attack", -lev);
        me->add_temp("apply/strength",-(int)me->query("str"));
        me->add_temp("apply/damage", -lev);

        me->start_busy(1+random(2));
        me->start_perform(4,"「夺命连环掌」");
        me->add("neili", -500);
        me->delete_temp("tiezhang");
        return 1;
}
int help(object me)
{
        write(HIR"\n铁掌掌法之「连环绝技」："NOR"\n\n");
        write(@HELP 
	铁掌连环绝技乃是铁掌掌法的不传之谜，非本门核心弟子不的传授。
	该掌法该经由上代帮主上官剑南的在抗击金兵过程中不断精雕细琢
	而成，其中最大的特点是融合了斧头帮的离魂斩绝技、柳叶刀法刀
	掌绝技。乃铁掌掌法中比较另类的一种形态，本质上仍然是掌法，
	但采用的招式却是以掌法的方式模拟出来。据上官帮主叙述，乃是
	为了纪念当初一起征战的几位副帮主或长老而融合在一起。该掌法
	已近大成，但因为其中招式驳杂，虽然乃是铁掌掌法的上乘武学，
	却丧失了铁掌掌法的精纯味道。若机缘巧合，解开融合一或者融合
	二，那么连环绝技也将大放异彩。
        
	perform strike.lianhuan

要求：
	当前内力 1500 以上；
	最大内力 3500 以上；
	当前精力 2000 以上；
	铁掌掌法等级 400 以上；
	基本内功等级 400 以上；
	基本掌法等级 400 以上；
	激发掌法为铁掌掌法；
	激发招架为铁掌掌法；
	激发内功不限。
HELP
        );
        return 1;
}