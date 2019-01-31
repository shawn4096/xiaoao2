// youming.c
// Modified by Lane@SJ 2005/4/14

#include <ansi.h>

inherit F_SSERVER;

int exert(object me, object target)
{
	int ap, dp;
	int nh = me->query_skill("linji-zhuang", 1)/2;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「幽冥」字诀只能对战斗中的对手使用。\n");

	if( (int)me->query_skill("linji-zhuang", 1) < 450 )
		return notify_fail("你的临济十二庄修为还不够。\n");

	if( me->query("class") != "bonze" && me->query("family/generation") > 4 )
		return notify_fail("你不是出家人，无法领会临济十二庄的「幽冥」字决！\n");

	if( (int)me->query("neili") < 1500 )
		return notify_fail("你的真气不够。\n");

	if( (int)me->query("max_neili") < 2000 )
		return notify_fail("你的内力修为不够。\n");

	if( me->query_temp("ljz/youming") )	// 修改标记（原为：yun_youming）
		return notify_fail("你正在运用临济十二庄的「幽冥」字诀！\n");

	if( me->query_temp("ljz/wuwo") )	// 改成 不能和 wuwo 同时使用
		return notify_fail("你正在运用临济十二庄的「无我」字决！\n");


	tell_object(me,MAG"你潜运临济十二庄的「幽冥」字诀。。。\n"NOR);

	if( nh > 150 ) nh = 150 + (nh - 150)/10;

	me->set_temp("ljz/youming", nh);  	// 标记修改
	me->add("neili", - 250);
	me->add_temp("apply/armor", nh);

	ap = me->query("combat_exp", 1 ) /1000 * me->query_skill("force",1);
	dp = target->query("combat_exp", 1)/ 1000 * target->query_skill("force",1);

	ap += ap/2;
    
	me->start_perform(4,"「幽冥」字诀");
	me->start_exert(4,"「幽冥」字诀");
	me->start_busy(1+random(1));

	if ( random(ap + dp) > dp||random(me->query_int(1))>target->query_int(1)/2 ) 
	{
		//message_vision(HIB"$N脸色突然变得阴森可怖，$n顿时为其面目所吓，陡然间冷汗直冒！\n"NOR, me, target);
		if (!me->query_skill("jiuyin-zhengong",1))
		{
			me->add_condition("no_perform",1+random(3));
	   	    me->add_condition("no_exert",1+random(3));
			message_vision(HIB"$N运使临济庄，脸色突然变得阴森可怖，$n顿时为其面目所吓，陡然间冷汗直冒！\n"NOR, me, target);
			me->start_perform(nh/30,"「幽冥」字诀");
		}else
		{
			message_vision(HIB"$N从九阴真经中领悟了部分的移魂大法奥秘，脸色突然变得阴森可怖，\n$n顿时为其面目所吓，陡然间冷汗直冒！\n"NOR, me, target);
			target->add_condition("no_perform",nh/30);
			target->add_condition("no_exert",nh/30);		
			me->start_perform(2,"「幽冥」字诀");

		}		
		//target->start_perform(nh/30, me->name()+"的「幽冥」字诀");
	}
	call_out("remove_effect", 1, me, target, nh);
	return 1;
}

void remove_effect(object me,object target,int count)
{
	int i;
	if( !me ) return;
	if( !target
	 || !me->is_fighting("target")
	 || count < 1 ) {
		i = me->query_temp("ljz/youming");
		me->add_temp("apply/armor", -i);
		me->delete_temp("ljz/youming");
		message_vision(HIR"$N散去了「幽冥」心法，恢复了正常。\n"NOR, me);
		return;
	}
	call_out("remove_effect", 1, me, count - 1);
}

string exert_name(){ return HIB"幽冥字决"NOR; }

int help(object me)
{
        write(HIB"\n临济十二庄「幽冥字诀」："NOR"\n\n");
        write(@HELP
	临济十二庄乃峨嵋著名的内功心法。是开山祖师郭襄融合了自己一生
	所见所闻的著名内功和心法后融合而成，既有九阳神功的刚猛，又有
	九阴真经功夫的阴柔，乃当世绝佳心法体系。解开峨嵋九阴后临济庄
	幽冥诀将产生变异。

指令：exert youming

要求：
	当前内力 1500 以上；
	最大内力 2000 以上；
	临济十二庄等级 450 以上；
	出家或俗家三代弟子；
	不能和「无我」字诀同时使用。
HELP
        );
        return 1;
}
