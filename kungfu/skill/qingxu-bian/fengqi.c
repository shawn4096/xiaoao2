//qingxu.c 清虚三击

//
//by sohu
//刀白凤的功夫

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int skill,damage;
	object weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);
	skill=me->query_skill("qingxu-bian",1);
	damage=skill*me->query_dex()+random(skill);
	if (damage>4000) damage=4000+random(1000);
	
	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("清虚鞭法只能对战斗中的对手使用。\n");

	if(me->query_skill("qingxu-bian",1) < 200)
		return notify_fail("你的「凤栖于梧」还不够娴熟，不会使用清虚鞭法。\n");
	if(me->query_skill("whip",1) < 200)
		return notify_fail("你的「基本鞭法」还不够娴熟，不会使用清虚鞭法。\n");
	if(me->query_skill("force",1) < 200)
		return notify_fail("你的「基本内功」还不够娴熟，不会使用清虚鞭法。\n");
	
	if( !weapon 
	|| weapon->query("skill_type") != "whip"
	|| me->query_skill_mapped("whip") != "qingxu-bian" 
	|| me->query_skill_mapped("parry") != "qingxu-bian" ) 
		return notify_fail("你现在无法使用凤栖于梧之清虚鞭法。\n");


	if( me->query("neili") < 500 )
		return notify_fail("你的内力不够500。\n");
	if( me->query("jingli") < 500 )
		return notify_fail("你的精力不够500。\n");

	if( me->query("max_neili") < 2000 )
		return notify_fail("你的最大内力不够2000。\n");
	if( me->query("max_jingli") < 1500 )
		return notify_fail("你的最大精力不够1500。\n");
	
	message_vision(HIY "\n$N运使清虚鞭法「凤栖于梧」绝技，将手中的"+weapon->query("name")+HIY"连抖三下，绕成三个圆圈，抽向$n！\n"NOR,me,target);
	
	
	if(random(me->query("combat_exp") )> target->query("combat_exp")/2
		||random(me->query_dex(1)) > target->query_dex(1)/2)
	{
		message_vision(HIC "\n结果$p被$P扫中面部，一股大力传来，顿时$p眼冒金星！\n" NOR,me,target);
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/3,me);
	}
	else {
		message_vision(HIW "可是$p看破了$P的清虚鞭法，身子一跃便躲开了。\n" NOR,me,target);
	}
	me->set_temp("qxb/qingxu",1);


	me->add_temp("apply/attack",skill/3);
	me->add_temp("apply/damage",skill/5);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	me->delete_temp("qxb/qingxu");

	if (me->query_skill_mapped("cuff")=="duanjia-quan"
		&&me->query_skill_prepared("cuff")=="duanjia-quan")
	{
		weapon->unequip();
		message_vision(HIR"$N将手中的"+weapon->query("name")+HIR"一收，纵身而上，将段家拳一招威震天南的招式袭向$n！\n"NOR,me,target);
		me->add_temp("apply/cuff",me->query_skill("duanjia-quan")/4);
		me->add_temp("apply/damage",me->query_skill("duanjia-quan")/4);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/damage",-me->query_skill("duanjia-quan")/4);
		me->add_temp("apply/cuff",-me->query_skill("duanjia-quan")/4);
		weapon->wield();
	}


	me->add_temp("apply/attack",-skill/3);
	me->add_temp("apply/damage",-skill/5);

	me->add("jingli", -100);
	me->add("neili", -150);
	me->start_perform(4,"清虚鞭法");
    return 1;
}

string perform_name(){ return HIM"凤栖于梧"NOR; }

int help(object me)
{
        write(HIG"\n清虚鞭法之「凤栖于梧」："NOR"\n\n");
        write(@HELP
	凤栖于梧是大理家臣刀白凤的功夫，刀白凤是大理王妃，熟悉
	天南文化，所以将鞭法的心得和诀窍融入到清虚鞭法中，乃是
	独特的天南文化体现。
    
	指令：perform whip.fengqi
		
要求：  
	当前内力需求 500 以上；
	最大内力需求 2000 以上；
	当前精力需求 500 以上；
	最大精力需求 1500 以上；
	清虚鞭法等级 200 以上；
	基本鞭法等级 200 以上:
	基本内功等级 200 以上:
	激发鞭法为清虚鞭法；
	激发招架为清虚鞭法；
	激发拳法且备拳法为段家拳；
	且手持鞭子类兵器。

HELP
        );
        return 1;
}
