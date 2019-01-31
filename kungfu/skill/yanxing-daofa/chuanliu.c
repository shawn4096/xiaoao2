// chuanliu.c
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int skill,i;
	i=0;
	weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);
	
	if( !objectp(target)
	 || !me->is_fighting(target) )
		return notify_fail("你只能在战斗中使用雁行穿柳刀。\n");

	if (!objectp(weapon) || (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");

	if((int)me->query_skill("force", 1) < 350 )
		return notify_fail("你的基本内功等级不够，不能使用雁行穿柳刀。\n");

	//if (me->query_skill_mapped("force") != "linji-zhuang")
		//return notify_fail("你所使用的内功不对。\n");

	if ((int)me->query_skill("yanxing-daofa", 1) < 350 )
		return notify_fail("你的雁行刀法等级不够，不能使用雁行穿柳刀！\n");

	if ((int)me->query_skill("blade", 1) < 350 )
		return notify_fail("你的基本刀法极不够娴熟，不能使用雁行穿柳刀！\n");

	if ( me->query_skill_mapped("blade") != "yanxing-daofa"
	 || me->query_skill_mapped("parry") != "yanxing-daofa" )
		return notify_fail("你现在无法使用雁行穿柳刀！\n");

	if ((int)me->query("neili") < 2000 )
		return notify_fail("你现在真气太弱，不能使用雁行穿柳刀！\n");

	if ((int)me->query("max_neili") < 5000 )
		return notify_fail("你现在内力太弱，不能使用雁行穿柳刀！\n");

	if (me->query_temp("em/chuanliu") ) 
		return notify_fail("你已经在使用雁行穿柳刀了！\n");
    
	message_vision(HIY"\n$N运起临济十二庄，劲力涌动，只见其手中" + weapon->name() +HIY"陡然一亮。\n"NOR, me);
	skill = me->query_skill("yanxing-daofa",1)/6;
	skill += random(skill);
	//if ( skill > 100) skill = 100 + random(skill-100)/10;
	if (me->query_skill("jiuyin-zhengong",1))
    {
		i=(int)me->query_skill("jiuyin-zhengong",1)/60;
		message_vision(HIB"\n$N将自己九阴速成领悟的招式融合到刀法之中，手中的" + weapon->name() +HIB"又再次亮了"+chinese_number(i)+"次。\n"NOR, me,target);
		
    }
    skill += i*60;
	if ( skill > 200) skill = 200 + random(skill-200)/10;
	if (userp(me))
	{
		me->add_temp("apply/attack", skill);
		me->add_temp("apply/damage", skill);
		me->add_temp("apply/strength", skill/10);
	}
	
	//me->add_temp("apply/blade", skill);
	//me->add_temp("apply/damage", skill);
	me->set_temp("em/chuanliu", skill);
    
   
	
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	if (me->is_fighting(target)&& me->query_skill("yanxing-daofa", 1) > 350)
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);

	
	me->add("neili", -300);
	if (me->query("gender")!="男性" || me->query("class")=="bonze"||!me->query("quest/em/yxdf/jueji/pass"))
	{
		if (me->query_skill("yanxing-daofa",1)<400)
		{ 
		//me->start_busy(random(2));
			me->start_perform(2, "雁行穿柳刀");
		}
		else if (me->query_skill("yanxing-daofa",1)<450)
			me->start_perform(1, "雁行穿柳刀");
		message_vision(YEL"你非俗世男人，对于这种刀法的狠辣威猛之刀意终是有些晦涩难懂。\n"NOR,me);
	}
	//if (objectp(target)&&me->is_fighting())
		call_out("remove_effect", 1, me, target, weapon, skill);
	return 1;
}

void remove_effect(object me, object target,object weapon, int skill)
{
	//int skill=me->query_temp("em/chuanliu");
	if(!me) return;
	if(!me->is_fighting(target)
	|| !weapon
	|| me->query_temp("weapon") != weapon
	|| me->query_skill_mapped("blade") != "yanxing-daofa"
	|| me->query_skill_mapped("parry") != "yanxing-daofa"){
		if( weapon)
			message_vision(HIW"$N手上"+weapon->query("name")+HIW"的刀气渐渐的消失了！\n"NOR, me);
		if (userp(me))
	    {
		   me->add_temp("apply/attack", -skill);
		   me->add_temp("apply/damage", -skill);
		   me->add_temp("apply/strength", -skill/10);
	    }

		me->delete_temp("em/chuanliu");
		return;
	}
	call_out("remove_effect", 1, me, target, weapon, skill);
}

string perform_name(){ return HIR"雁行穿柳刀"NOR; }

int help(object me)
{
        write(HIR"\n雁行刀法之「雁行穿柳刀」："NOR"\n\n");
        write(@HELP 
	雁行刀法乃是峨眉俗家弟子武技，可以向孤鸿子
	学习习得。因雁行刀乃俗家弟子使用，刀法无需
	和临济庄配合使用，也是一门不俗的武技。
	穿柳刀是将刀法施展开后，即便遇到柔软的垂柳
	也能一刀穿过，重点是将全身劲气聚集于刀上，
	心与气合，力与心合，武器伤害威力将大幅提升
	注意：俗世男解开孤鸿子谜题后，威力大增

	指令：perform blade.chuanliu

要求：
	当前内力需求 2000 以上；
	最大内力需求 5000 以上；
	雁行刀法等级 350 以上；
	基本内功等级 350 以上；
	基本刀法等级 350 以上；
	激发刀法为雁行刀法；
	激发招架为雁行刀法；
	激发内功不限；
	且手持刀类兵器,
	

HELP
        );
        return 1;
}
