//嫉世愤俗
//按照new system要求，命中率为A+
// edit by sohu@xojh

#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;

string perform_name() {return HIY"嫉世愤俗"NOR;}

int perform(object me, object target)
{
          int lvl,lvl2;

        lvl = me->query_skill("anran-zhang", 1) ;
		
		if (userp(me))
		    lvl=lvl/2;
		else lvl=lvl/4;
	    
		if (me->query("gender")=="女性") lvl/=4;
		if (me->query("gender")=="无性")
			return notify_fail("你阴阳不调和，「嫉世愤俗」只能在战斗中使用。\n");
;

        if( !target ) target = offensive_target(me);

        if( !target 
         || !me->is_fighting(target) )
                return notify_fail("「嫉世愤俗」只能在战斗中使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「嫉世愤俗」！\n");   

        if( (int)me->query_skill("anran-zhang", 1) < 250 )
                return notify_fail("你的黯然销魂掌还不够娴熟，使不出「嫉世愤俗」绝技。\n");

        if( (int)me->query_skill("force", 1) < 250 )
                return notify_fail("你的基本内功等级还不够，使不出「嫉世愤俗」绝技。\n");

        if ( me->query_skill_mapped("strike") != "anran-zhang"
          || me->query_skill_prepared("strike") != "anran-zhang"
          || me->query_skill_mapped("parry") != "anran-zhang"
           )
             return notify_fail("你现在无法使用「嫉世愤俗」绝技！\n");       

        if((int)me->query("max_neili") < 3500 )
                return notify_fail("你现在内力太弱，使不出「嫉世愤俗」。\n");      

        if((int)me->query("neili") < 1000 )
                return notify_fail("你现在真气太弱，使不出「嫉世愤俗」绝技。\n");
		if((int)me->query("jingli") < 500 )
                return notify_fail("你现在真气太弱，使不出「嫉世愤俗」绝技。\n");
     
		if (me->query("divorce"))
					return notify_fail("你如此滥情，难以使用发挥出黯然销魂掌绝技。\n"); 
        me->set_temp("jishi", 3); 
        message_vision(HIY"\n$N突然一阵心烦意乱之意涌上心头，正是「嫉世愤俗」绝技，而所打出的掌力竟然威力大增！\n"NOR,me,target);
        me->add_temp("apply/damage", lvl/3);
        me->add_temp("apply/attack", lvl);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if (present(target,environment(me)) && me->is_fighting(target))
	    {
		    if (me->query_skill("anran-zhang",1)<350)
		                  target->add_busy(1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        }
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

        me->add_temp("apply/damage", -lvl/3);
        me->add_temp("apply/attack", -lvl);

        me->add("neili", -random(300));
        me->add("jingli", -random(150));
        me->delete_temp("jishi");
        me->start_perform(3,"嫉世愤俗");        
        me->start_busy(1+random(1));
        return 1;
}

//愤世嫉俗 愤青，作为初级武技 150，刷三清后设计

int help(object me)
{
        write(HIB"\n黯然销魂掌"+HIY"「嫉世愤俗」"NOR"\n");
        write(@HELP

	杨过自和小龙女在绝情谷断肠崖前分手，心中日夜思念
	期盼小龙女，渐渐形销骨立，了无生趣。他在海潮之中
	苦练，终于悟出了一十七招掌法。他将这套掌法定名为
	黯然杞人忧天掌，取的是江淹「别赋」中那句黯然杞人
	忧天者，唯别而已矣之意。这掌法中逆中有正，正反相
	冲，无一不是妙到巅毫。受伤越重威力越大，实是置死
	地而得后生!
	愤世嫉俗乃是杨过年轻时期比较激烈的掌法绝技，一出
	手，即为连环三招，不避不让，以攻代守，实乃黯然掌
	重要的绝技，滥情者无法使用。
	
	perform strike.jishi

要求：
	基本掌法要求 250 级以上
	黯然掌法要求 250 级以上
	基本内功要求 250 级以上
	最大内力要求 3500 以上	
	当前内力要求 1000 以上
	当前精力要求 500 以上
	空手且激发掌法和招架为黯然掌
HELP
        );
        return 1;
}
