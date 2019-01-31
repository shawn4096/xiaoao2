// jingtao 惊涛骇浪

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
string perform_name(){ return HIY"惊涛骇浪"NOR; }
void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lev;
        lev = me->query_skill("huagu-mianzhang", 1) +me->query_skill("dulong-dafa", 1)/6;
       // lev2 = me->query_skill("strike", 1)/6;
		if (!userp(target))
		{
			lev=lev+me->query_skill("dulong-dafa", 1)/8;
		}
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「惊涛骇浪」只能在战斗中使用。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「惊涛骇浪」！\n");   
        if( (int)me->query_skill("huagu-mianzhang", 1) < 220 )
                return notify_fail("你的化骨绵掌还不够娴熟，使不出「惊涛骇浪」绝技。\n");
        if (me->query_skill_prepared("strike") != "huagu-mianzhang"
		 || me->query_skill_mapped("parry") != "huagu-mianzhang"
		 || me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("你现在无法使用「惊涛骇浪」进行攻击。\n");  

        if( (int)me->query_skill("dulong-dafa", 1) < 220 )
                return notify_fail("你的毒龙大法等级还不够，使不出「惊涛骇浪」绝技。\n");
		if( (int)me->query_skill("strike", 1) < 220 )
                return notify_fail("你的基本掌法等级还不够，使不出「惊涛骇浪」绝技。\n");
        if(me->query("gender")=="女性") 
        	return notify_fail("你不是男人，尚不能使用化骨诀。\n");
		if( me->query("jingli") < 1000 )
                return notify_fail("你现在精力太弱，使不出「惊涛骇浪」。\n");      
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在真气太弱，使不出「惊涛骇浪」。\n");
        message_vision(HIB"\n$N心中默想教主种种教诲，心中迸发出一种莫名的力量,手中掌力犹如惊涛骇浪一般全力击出！\n"NOR,me);
        me->add_temp("apply/attack", lev/4);
		me->add_temp("apply/strike", lev/4);
        me->add_temp("apply/damage",lev/6);
		if (!userp(target))
		{
			me->add_temp("apply/attack",lev/5);
			me->add_temp("apply/damage",lev/6);
			target->add_busy(2);
			me->set_temp("hgmz/jthit",1);
		}
		//me->set_temp("action_flag", member_array("strike", keys(me->query_skill_prepare())));
        me->set_temp("hgmz/jingtao",1);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
        if(me->is_fighting(target)) 
		{
                if( random(me->query("combat_exp"))>target->query("combat_exp")/2)
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                else
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        }
		if(me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(target)?1:3);
		me->add_temp("apply/attack", -lev/4);
        me->add_temp("apply/strike", -lev/4);
		me->add_temp("apply/damage",-lev/6);
		if (me->query_temp("hgmz/jthit"))
		{
			me->add_temp("apply/attack",-lev/5);
			me->add_temp("apply/damage",-lev/6);
			me->delete_temp("hgmz/jthit");
		}

		me->delete_temp("hgmz/jingtao");

		me->add_busy(1);
        me->add("neili", -300);
		me->add("jingli", -200);
		me->start_perform(4,"「惊涛骇浪」");
        return 1;
}
int help(object me)
{
   write(HIY"\n化骨绵掌「"HIY"惊涛骇浪"HIY"」："NOR"\n");
   write(@HELP
	化骨绵掌是蛇岛独门武技，是一种极为难练的阴毒功夫，
	被化骨绵掌击中的人开始浑如不觉，但两个时辰后掌力
	发作，全身骨骼会其软如绵，处处寸断，脏腑破裂，惨
	不堪言，再无救治。
	「惊涛骇浪」绝技是化骨绵掌中最直接和最迅速的绝技。

	指令：perform strike.jingtao

要求：
	当前内力要求 1000 以上；
	当前精力要求 1000 以上；
	化骨绵掌等级 220 以上；
	毒龙大法等级 220 以上；
	基本掌法等级 220 以上；
	激发掌法为化骨绵掌；
	激发招架为化骨绵掌；
	其备掌法为化骨绵掌；
	激发内功为毒龙大法；
	男性使用；
          
HELP
   );
   return 1;
}
