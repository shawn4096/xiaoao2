//chan.c
//秋风佛尘的拂尘缠绕
//by sohu
//为女玩家设定,源自孙不二、丘处机

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int i;
	object weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("拂尘缠绕诀只能对战斗中的对手使用。\n");

	if(me->query_skill("qiufeng-chenfa",1) < 150)
		return notify_fail("你的「秋风尘法」还不够娴熟，不会使用拂尘缠绕诀。\n");
	if(me->query_skill("whip",1) < 150)
		return notify_fail("你的「基本鞭法」还不够娴熟，不会使用拂尘缠绕诀。\n");
	if( !weapon 
		|| weapon->query("skill_type") != "whip"
		|| me->query_skill_mapped("whip") != "qiufeng-chenfa" 
		|| me->query_skill_mapped("parry") != "qiufeng-chenfa" ) 
		return notify_fail("你现在无法使用拂尘缠绕诀。\n");

	if( me->query("neili") < 500 )
		return notify_fail("你的内力不够500。\n");
	if( me->query("jingli") < 500 )
		return notify_fail("你的精力不够500。\n");

	if( me->query("max_neili") < 1500 )
		return notify_fail("你的最大内力不够1500。\n");
	if( me->query("max_jingli") < 1300 )
		return notify_fail("你的最大精力不够1300。\n");
	if( target->is_busy() )
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");
	if (me->query("gender")=="男性") i=2;
	if (me->query("gender")=="女性") i=3;
	
	message_vision(HIW "\n$N忽然将手中的"+weapon->query("name")+HIW"使出「秋风尘法」的拂尘缠绕诀的功夫，形成一个圆圈套向$n的咽喉！\n"NOR,me,target);

	if(random(me->query("combat_exp") )> target->query("combat_exp")/i
		||random(me->query_dex(1)) > target->query_dex(1)/i)
	{
		message_vision(HIY "\n结果$p被$P一卷，圈住脖子，顿时气血一滞。\n" NOR,me,target);
		target->add_busy(1+(int)me->query_skill("qiufeng-chenfa",1)/100);
		target->apply_condition("no_exert",1);
		if (me->query("per")>27 && me->query("gender")=="女性" )
		{
			message_vision(HIG "\n$n只觉$N宛如仙女下发，明艳不可方物，顿时一愣，动作有些迟缓！\n"NOR,me,target);
			target->add_busy(1);
		}
		//target->
	}
	else {
		message_vision(HIW "可是$p看破了$P的拂尘缠绕诀，身子一跃便躲开了。\n" NOR,me,target);
		me->start_perform(1,"拂尘缠绕诀");
	}
	//message_vision(msg, me, target);

	me->add("jingli", -100);
	me->add("neili", -200);
    return 1;
}

string perform_name(){ return HIW"拂尘缠绕诀"NOR; }

int help(object me)
{
        write(HIG"\n「秋风尘法」之「拂尘缠绕诀」："NOR"\n\n");
        write(@HELP
	「秋风尘法」是全真教入门武技，拂尘本为道家常用道具
	教中弟子在行走江湖之际，将深厚功力融入拂尘，可以用
	做鞭法使用。门中弟子往往凭此武技既宣化教育教中，也
	用作防身之用。
	拂尘缠绕诀是以长鞭的旋转之力，将对方裹住，从而限制
	对方行动的招式，一旦对方中了，势必呼吸困难。女性略
	有优势，尤其貌美女子。
    
指令：perform whip.chan
		
要求：  
	当前内力需求 500 以上；
	最大内力需求 1500 以上；
	当前精力需求 500 以上；
	最大精力需求 1300 以上；
	当前精力需求 500 以上；
	秋风尘法等级 150 以上；
	基本鞭法等级 150 以上:
	激发鞭法为秋风尘法；
	激发招架为秋风尘法；
	且手持鞭子类兵器。

HELP
        );
        return 1;
}
