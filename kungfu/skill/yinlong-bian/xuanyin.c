#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        int lvl, j,i;
	object weapon;
	lvl = me->query_skill("yinlong-bian", 1);

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target)
	|| !necessary(target) )
		return notify_fail("你只能对战斗中的对手使用玄阴诀。\n");

	if( me->query_skill("yinlong-bian", 1) < 500 )
		return notify_fail("你的银龙鞭法不够娴熟，无法施展出玄阴诀。\n");

	weapon = me->query_temp("weapon");

	if ( ! weapon 
	|| weapon->query("skill_type") != "whip"
	|| me->query_skill_mapped("whip") != "yinlong-bian"
	|| me->query_skill_mapped("parry") != "yinlong-bian")
		return notify_fail("你现在无法施展出玄阴诀。\n");
		
		
    if (!me->query("quest/jiuyin1/pass"))
		return notify_fail("你尚未习得九阴真经上册的精微秘诀，现在无法施展出玄阴诀。\n");
		
    if (me->query_skill_mapped("strike")!="jiuyin-shenzhang"
		&&me->query_skill_prepared("strike")!="jiuyin-shenzhang")
        return notify_fail("你没有激发九阴神掌，现在无法施展出玄阴诀。\n");
	if (me->query_skill_mapped("force")!="jiuyin-zhengong")		
        return notify_fail("你没有激发九阴真功，现在无法施展出玄阴诀。\n");
	if (me->query_skill("jiuyin-zhengong", 1) < 500)
		return notify_fail("你的九阴真功火候不够，无法施展出玄阴诀。\n");
	if ( me->query_skill("jiuyin-shenzhua", 1) < 500)
		return notify_fail("你的九阴神爪火候不够，无法施展出玄阴诀。\n");
    if ( me->query_skill("jiuyin-shenzhang", 1) < 500)
		return notify_fail("你的九阴神掌火候不够，无法施展出玄阴诀。\n");
	if ( me->query_skill("jiuyin-shenfa", 1) < 500)
		return notify_fail("你的九阴身法火候不够，无法施展出玄阴诀。\n");

	if ( me->query("max_neili") < 2000)
		return notify_fail("你的内力不够，无法施展出玄阴诀。\n");

	if ( me->query("neili") < 1000)
		return notify_fail("你的真气不够，无法施展出玄阴诀。\n");

	if ( me->query("jingli") < 1000)
		return notify_fail("你的精气不够，无法施展出玄阴诀。\n");

	message_vision(HIB"$N使出九阴「玄阴诀」，迅捷无比的攻向$n！\n"NOR,me, target);

	j = lvl /3;

	if ( lvl > 200 )
		j = to_int(lvl/200.0 * lvl/3.0);

	me->add_temp("apply/attack", j);
	me->add_temp("apply/whip", j);
	me->add_temp("apply/damage", j/2);

    message_vision(HIB"$N银龙鞭法已然大成，连抽数鞭，一鞭比一鞭凌利！\n"NOR,me,target);
 //       i=0;
       
    if (random(me->query_int(1)) > target->query_int(1)/3)
    {
        	message_vision(HIB"$n在$N施展的九阴真气强大压力下，连连後退，陷入一片混乱之中，更别说攻击了。\n"NOR,me,target);
        //	i=1;
			target->start_busy((int)lvl/50);
    } else{
			message_vision(HIC"$n急速后退，严密防守，以逸待劳。\n"NOR,me,target);
			target->start_busy(3+random(3));
	}
        
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        
	if ( me->is_fighting(target)&&me->query_temp("jiuyin/powerup")){
		message_vision(HIB"$N的九阴真气已然大成，运转如意，奔流不息，银龙鞭法威力大增！$n一时不查为鞭劲所伤。\n"NOR,me,target);
		target->recieve_damage("qi",random(2000),me);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
     }
	if ( me->is_fighting(target)&&me->query_temp("jiuyin/fast")) {
		message_vision(HIC"$N九阴身法运转之下，宛如鬼魅，银龙鞭法忽然间变得诡异难测。\n"NOR,me,target);
		me->add_temp("apply/whip",me->query_temp("jiuyin/fast")/2);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/whip",-me->query_temp("jiuyin/fast")/2);

    }
    if ( me->is_fighting(target)){
		
		weapon->unequip(); 
		message_vision(HIM"$N熟读道德经，道家运转虚空之意无不信手拈来，招式已经不拘一格。趁$n躲闪之际，鞭子一卷，竟空手疾攻数招。\n"NOR,me,target);
        
		me->add_temp("apply/strike",j);
		me->add_temp("apply/claw",j);
		COMBAT_D->do_attack(me, target,me->query_temp("weapon"), 3);
		COMBAT_D->do_attack(me, target,me->query_temp("weapon"), 3);
		//若互备则是双招？
		message_vision(HIM"$N将手一抖，长鞭已然回到手中。\n"NOR,me,target);
		me->add_temp("apply/strike",-j);
		me->add_temp("apply/claw",-j);
		weapon->wield();		
    }
	if ( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if ( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	if ( me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

        me->add_temp("apply/attack", -j );
        me->add_temp("apply/whip", -j);
        me->add_temp("apply/damage",-j/2);

    me->start_perform(5+random(2), "「玄阴诀」");
	me->add("neili", -400);
	me->add("jingli", -150);
	//if(i==1) target->start_busy( lvl/50 ); 
	return 1;
}

string perform_name(){ return HIB"玄阴诀"NOR; }

int help(object me)
{
        write(HIB"\n银龙鞭法之「玄阴诀」："NOR"\n\n");
        write(@HELP
        要求：  当前内力 1000 以上；
                最大内力 2000 以上；
                当前精力 1000 以上；
                银龙鞭法等级 500 以上；
                九阴真功等级 500 以上；
                九阴身法等级 500 以上；
				九阴神掌等级 500 以上；
				九阴神爪等级 500 以上；
                激发鞭法为银龙鞭法；
                激发招架为银龙鞭法；
                且手持兵器。

HELP
        );
        return 1;
}
