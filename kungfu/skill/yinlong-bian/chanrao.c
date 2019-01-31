#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	object weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("缠绕诀只能对战斗中的对手使用。\n");

	if(me->query_skill("yinlong-bian",1) < 250)
		return notify_fail("你的九阴银龙鞭还不够娴熟，不会使用缠绕诀。\n");

	if( !weapon 
	|| weapon->query("skill_type") != "whip"
	|| me->query_skill_mapped("whip") != "yinlong-bian" 
	|| me->query_skill_mapped("parry") != "yinlong-bian" ) 
		return notify_fail("你现在无法使用缠绕诀。\n");

	if( me->query("neili") < 1500 )
		return notify_fail("你的内力不够。\n");

	if( target->is_busy() )
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");
	
	msg = HIG "\n$N忽然将手中的"+weapon->query("name")+HIG"使出缠绕诀，舞动并不迅捷,但东边一卷，西边一翻,招招全然出人意料之外！\n";

	if(random(me->query("combat_exp") )> target->query("combat_exp")/2
		||random(me->query_dex(1)) > target->query_dex(1)/2)
	{
		msg += HIY "\n结果$p被$P一卷，两条腿被结结实实的捆起来，在地上无法爬起。\n" NOR;
		target->start_busy((int)me->query_skill("yinlong-bian",1)/50);
		if (!me->query("quest/em/zzr/pass"))
			me->start_perform(4,"缠绕诀");
	}
	else {
		msg += HIW "可是$p看破了$P的缠绕诀，身子一跃便躲开了。\n" NOR;
		me->start_perform(2,"缠绕诀");
	}
	message_vision(msg, me, target);

	if (!me->query("quest/em/zzr/pass"))
		me->start_busy(random(2));
	me->add("jingli", -100);
	me->add("neili", -400);
    return 1;
}

string perform_name(){ return HIG"缠绕诀"NOR; }

int help(object me)
{
        write(HIG"\n九阴银龙鞭之「缠绕诀」："NOR"\n\n");
        write(@HELP
	九阴银龙鞭是九阴真经下卷中著名的武功，和摧心掌、九阴白骨抓
	齐名，这鞭法施展不靠内力，只需要足够的技巧就能施展攻敌不备
	而且防御起来也是风雨不透，甚是严密。
	缠绕诀是以长鞭的旋转之力，将对方裹住，从而限制对方行动的招
	式，一旦对方中了，势必手足被捆。峨眉弟子若机缘巧合受周芷若
	指点，此招将有小飞跃。
    
指令：perform whip.chanrao
		
要求：  
	当前内力 1500 以上；
	最大内力 1500 以上；
	当前精力 1500 以上；
	九阴银龙鞭等级 130 以上；
	激发鞭法为九阴银龙鞭；
	激发招架为九阴银龙鞭；
	且手持兵器。

HELP
        );
        return 1;
}
