//lihua.c 暴雨梨花诀

//秋风佛尘的拂尘缠绕
//by sohu
//为女玩家设定,源自孙不二、丘处机

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int skill,damage;
	object weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);
	skill=me->query_skill("qiufeng-chenfa",1);
	damage=skill*me->query_dex()+random(skill);
	if (damage>4000) damage=4000+random(1000);
	
	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target) )
		return notify_fail("暴雨梨花诀只能对战斗中的对手使用。\n");

	if(me->query_skill("qiufeng-chenfa",1) < 200)
		return notify_fail("你的「秋风尘法」还不够娴熟，不会使用暴雨梨花诀。\n");
	if(me->query_skill("whip",1) < 200)
		return notify_fail("你的「基本鞭法」还不够娴熟，不会使用暴雨梨花诀。\n");
	if(me->query_skill("force",1) < 200)
		return notify_fail("你的「基本内功」还不够娴熟，不会使用暴雨梨花诀。\n");
	
	if( !weapon 
	|| weapon->query("skill_type") != "whip"
	|| me->query_skill_mapped("whip") != "qiufeng-chenfa" 
	|| me->query_skill_mapped("parry") != "qiufeng-chenfa" ) 
		return notify_fail("你现在无法使用秋风尘法之暴雨梨花诀。\n");


	if( me->query("neili") < 500 )
		return notify_fail("你的内力不够500。\n");
	if( me->query("jingli") < 500 )
		return notify_fail("你的精力不够500。\n");

	if( me->query("max_neili") < 2000 )
		return notify_fail("你的最大内力不够2000。\n");
	if( me->query("max_jingli") < 1500 )
		return notify_fail("你的最大内力不够1500。\n");
	
	message_vision(HIY "\n$N运使秋风尘法「暴雨梨花诀」绝技，将手中的"+weapon->query("name")+HIY"展开成一朵朵梨花般的，连续向$n使出三招！\n"NOR,me,target);
	
	
	if(random(me->query("combat_exp") )> target->query("combat_exp")/2
		||random(me->query_dex(1)) > target->query_dex(1)/2)
	{
		message_vision(HIC "\n结果$p被$P扫中面部，一股大力传来，顿时$p眼冒金星！\n" NOR,me,target);
		target->receive_damage("qi",damage,me);
		if (me->query("gender")=="男性") target->receive_wound("qi",damage/6,me);
		else target->receive_wound("qi",damage/3,me);
	
	}
	else {
		message_vision(HIW "可是$p看破了$P的暴雨梨花诀，身子一跃便躲开了。\n" NOR,me,target);
	}
	me->set_temp("qfcf/baoyu",1);
	if (me->query("gender")=="女性")
		skill=skill+me->query_skill("xiantian-gong",1)/5; 

	me->add_temp("apply/attack",skill/3);
	me->add_temp("apply/damage",skill/5);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if (me->query_skill_mapped("leg")=="yuanyang-lianhuantui"
		||me->query_skill_prepared("leg")=="yuanyang-lianhuantui")
	{
		weapon->unequip();
		message_vision(HIR"$N将手中的"+weapon->query("name")+HIR"一收，身形腾空而起，一脚踹向$n！\n"NOR,me,target);
		me->add_temp("apply/leg",skill/4);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/leg",-skill/4);
		weapon->wield();
	}

	me->add_temp("apply/attack",-skill/3);
	me->add_temp("apply/damage",-skill/5);
	me->delete_temp("qfcf/baoyu");

	me->add("jingli", -100);
	me->add("neili", -150);
	me->start_perform(4,"暴雨梨花诀");
    return 1;
}

string perform_name(){ return HIR"暴雨梨花展"NOR; }

int help(object me)
{
        write(HIG"\n「秋风尘法」之「暴雨梨花展」："NOR"\n\n");
        write(@HELP
	「秋风尘法」是全真教入门武技，拂尘本为道家常用道具
	教中弟子在行走江湖之际，将深厚功力融入拂尘，可以用
	做鞭法使用。门中弟子往往凭此武技既宣化教育教中，也
	用作防身之用。
	暴雨梨花展是以手中拂尘陡然横扫而去，连续数招攻敌。
	同时如果备了腿法，腿法会辅助攻击一招。
    
指令：perform whip.lihua
		
要求：  
	当前内力需求 500 以上；
	最大内力需求 2000 以上；
	当前精力需求 500 以上；
	最大精力需求 1500 以上；
	秋风尘法等级 200 以上；
	基本鞭法等级 200 以上:
	基本内功等级 200 以上:
	激发鞭法为秋风尘法；
	激发招架为秋风尘法；
	激发腿法为鸳鸯连环退；
	备腿法为鸳鸯连环退；
	且手持鞭子类兵器。

HELP
        );
        return 1;
}
