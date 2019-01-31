// zhemei.c
// /kungfu/skill/zhemei-shou/
// Program by ying
//modified by zhuifeng@SJFY 2010/07/17

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

void remove_effect(object me, int improve);

int perform(object me, object target)
{
	string msg;
	int improve, ap, dp, skill, i;

        if( !objectp(target) || !me->is_fighting(target) )
                return notify_fail("「折梅展」只能在战斗中使用。\n");
                
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「折梅展」！\n");   
                
        if( (int)me->query_skill("zhemei-shou", 1) < 400 )
                return notify_fail("你的天山折梅手还不够娴熟，使不出「折梅展」绝技。\n");     
                
        if( (int)me->query_skill("hand", 1) < 400 )
                return notify_fail("你的基本手法还不够娴熟，使不出「折梅展」绝技。\n");                                                      
/*
        if (me->query_skill_mapped("force") != "bahuang-gong" )
        if (me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("你所使用的内功不对，使不出「折梅展」绝技。\n");  
                
        if ( me->query_skill_mapped("parry") != "zhemei-shou"
	            && me->query_skill_mapped("hand") != "zhemei-shou")
		            return notify_fail("你现在无法使用「折梅展」。\n");*/
		            
		if (me->query_skill_prepared("hand") != "zhemei-shou"
	             || me->query_skill_mapped("hand") != "zhemei-shou")
	              return notify_fail("你现在无法使用「折梅展」。\n");

        if( (int)me->query_temp("zhemei") > 0 )
                return notify_fail(HIG"你刚刚用过「折梅展」，等一会再使用吧。NOR\n"NOR);
			
		if( target->query_temp("zhemei"))
	            return notify_fail("对方已经中了你的「折梅展」！\n");

        if( (int)me->query("neili", 1) < 1500 )
                return notify_fail("你现在内力太弱，不能使用「折梅展」绝技。\n");
        if( (int)me->query("max_neili", 1) < 5000 )
                return notify_fail("你现在最大内力不足，不能使用「折梅展」绝技。\n");
        if( me->query("jingli") < 1000 )
		            return notify_fail("你现在精力不够, 不能使用「折梅展」绝技! \n");
                
        message_vision(HIM"$N手法突然加快，使出天山「折梅展」绝技，迅速扑向并抓住$n一只手臂，用力弯折。\n" NOR,me, target);        

	    me->set_temp("zhemei", 1);


	    ap = COMBAT_D->skill_power(me, "hand", SKILL_USAGE_ATTACK);
	    dp = COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE);

	    if ( target->is_busy())
		dp -= dp/3;
		if (me->query_skill_mapped("force")=="bahuang-gong")
		{
			skill = me->query_skill("zhemei-shou", 1) + me->query_skill("bahuang-gong",1) /2;
		}
		/*
		if (me->query_skill_mapped("force")=="beiming-shengong")
		{
			skill = me->query_skill("zhemei-shou", 1) + me->query_skill("beiming-shengong",1) /2;
		}
		*/
        i = skill/3;
	

        //275级后飞跃
        if (me->query_skill_mapped("force")=="bahuang-gong"
		    ||me->query_skill_mapped("force")=="xiaowu-xiang"
			||me->query_skill_mapped("force")=="beiming-shengong")
        {
			if ( skill > 300 )
				i = to_int( skill/3 * skill/300);
			message_vision(HIC"$N将逍遥派内功融合到折梅手招式中，威力陡增！\n"NOR,me);
			me->add_temp("apply/strength",skill/10);
			me->set_temp("xiaoyao/addstrtemp",1);
        }else 
		{
			if ( skill > 350 )
				i = to_int( skill/3 * skill/350);
		}
		//弱化npc
		if(!userp(me)) i = i / 3;

	    me->add_temp("apply/attack", i);
	    me->add_temp("apply/hand", i);
        me->add_temp("apply/damage", i);
		

	    if(random(ap + dp) > dp /3  && !target->query_temp("zhemei")) 
		{
			msg = HIR"结果$n的手臂被$N弯折得无法动弹，只觉一阵阵疼痛难忍，几乎折断，当下无法动弹！\n"NOR;
			message_vision(msg, me, target);
			improve = me->query("str");
			target->add_busy(random(2)+3);
			target->add_temp("apply/strength", -improve);
			target->set_temp("zhemei", improve);
			target->add_condition("no_fight", 2);
			target->add_condition("no_perform", 2);
			target->set_temp("must_be_hit", 1);
			//赠送三招
			if (present(target,environment(me)) && me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			if (present(target,environment(me)) && me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
			if ( skill > 150)
			   if (present(target,environment(me)) && me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
		
		me->add("neili", -random(1000));
		me->add("jingli", -150);
		call_out("check_fight", 1, me, target ,improve, me->query_skill("zhemei-shou")/50);
	}
	else {
		msg = WHT"不料$n臂力异于常人，勇猛异常，用力反震，反将$N震退数步！\n"NOR;
		message_vision(msg, me, target);
		if (present(target,environment(me)) && me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
		if ( skill > 100)
			if (present(target,environment(me)) && me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
	}
	me->add_temp("apply/attack", -i);
	me->add_temp("apply/hand", -i);
    me->add_temp("apply/damage", -i);
	if (me->query_temp("xiaoyao/addstrtemp"))
	{
		me->add_temp("apply/strength",-skill/10);
		me->delete_temp("xiaoyao/addstrtemp");
	}
	me->start_busy(1+random(1));
	me->add("neili", -100);
	me->add("jingli", -100);

	me->delete_temp("zhemei");
	if (me->query_skill_mapped("force")=="beiming-shengong"
	||me->query_skill_mapped("force")=="bahuang-gong")
	{
		//me->start_perform(2, "「折梅展」");
	}
    else me->start_perform(4, "「折梅展」");

	return 1;
}

void remove_effect(object target, int improve)
{
	if(!target) return;
	target->add_temp("apply/strength", improve);
    target->delete_temp("zhemei");

	target->delete_temp("must_be_hit");
	tell_object(target, HIR"\n你运力不断舒展手臂，不一会儿就感觉手臂已经恢复原状。\n"NOR);
}

void check_fight(object me, object target, int improve, int count)
{
	if(! target) return;
	if(! me
	|| ! me->is_fighting(target)
	|| me->query_skill_mapped("hand") != "zhemei-shou"
	|| me->query_skill_prepared("hand") != "zhemei-shou"
	|| me->query_temp("weapon")
	|| count < 0 ){
		remove_effect(target , improve);
		return;
	}
    
	call_out("check_fight", 1, me, target, improve, count -1);
}

string perform_name(){ return HIM"折梅展"NOR; }

int help(object me)
{
	write(YEL"\n天山折梅手之"HIM"「折梅展」："NOR"\n");
	write(@HELP
	天山折梅手是逍遥派高手天山童佬的绝学，虚竹曾赖以成名。天山折梅手
	共包括三路掌法，三路擒拿法，一共六路武功，天下任何招数武功，都能
	自行化在这‘六路折梅手’之中。天山折梅手灵鹫宫有明显优势。
	
	指令：perform hand.zhemei

要求：
	当前内力 1500 以上；
	当前精力 1000 以上；
	最大内力 5000 以上：
	天山折梅手等级 400 以上；
        
HELP
	);
	return 1;
}
