// tianyin.c 密宗大手印之天印
#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return HIY"阿修罗天印诀"NOR; }

int perform(object me, object target)
{
	int lvl;
	string msg;

	if( !target ) target = offensive_target(me);


    if( !target  
          || !me->is_fighting(target)
          || !objectp(target)
          || environment(target)!= environment(me))
           return notify_fail("阿修罗天印只能对战斗中的对手使用。\n");

	    if( objectp(me->query_temp("weapon")) )
		   return notify_fail("你必须空手才能使用「阿修罗天印」诀！\n");		
	    if((int)me->query_skill("longxiang-boruo",1)<250)
           return notify_fail("你的龙象般若功修为不够。\n");	
        if( (int)me->query_skill("dashou-yin", 1) < 250 )
		   return notify_fail("你的密宗大手印修为不够，不能使用「阿修罗天印」诀。\n");
		if(me->query_skill_mapped("hand")!="dashou-yin" 
		||me->query_skill_prepared("hand")!="dashou-yin"
		||me->query_skill_mapped("parry")!="dashou-yin")
		   return notify_fail("你没有激发并招架密宗大手印，不能使用「阿修罗天印」诀。\n");
        if((int)me->query("max_neili",1)<1000)
           return notify_fail("你的内力修为太差无法使用本势。\n");                        
        if( (int)me->query("neili", 1) < 500 )
		   return notify_fail("你现在内力太弱，不能使用「阿修罗天印」诀。\n");
        if((int)me->query_skill("poison",1)<80)
            return notify_fail("你的毒技不够，无法配合送出掌毒。\n");			
	    //if( me->query_temp("dls/dsy"))
            //return notify_fail("你正在施展大手印绝技。\n");			
	    msg = HIY "$N默念愤怒咒，运起内功，十指翻飞，双手陡然大了数倍，带着一股紫黑之气击向$n。\n"NOR;
	    msg +=  "正是一招「"HIG"阿修罗无上梵天降魔宝印"NOR"」。\n\n"NOR;
        message_vision(msg, me, target);  
		
		me->set_temp("dls/dsy",1);
        //if( objectp(target)&&!target->is_killing(me) ) target->kill_ob(me);

        if( objectp(target)&&target->query_temp("fanzhen")){
             msg=HIY"$n 不闪不躲任由$N一掌击在胸口之上，只见金光一闪，$N的掌毒尽被反震击而回！\n"
                   +"$N失声惊叫：“金刚不坏体神功！”连忙收掌闪避。\n"NOR;     	
                me->add("neili", -300);
                me->apply_condition("dsy_poison", 1+random(1) );
             	message_vision(msg, me, target);
               // return 1;
        }	

    
	lvl =( (int)me->query_skill("poison",1) +  (int)me->query_skill("dashou-yin", 1) ) /3 ;

    //if (me->query_skill("dashou-yin",1)>350 ||!userp(me))
	      // lvl=lvl/3;
	//if (userp(target)) lvl=lvl/2;
	//else lvl=lvl/2;

		me->add_temp("apply/damage", lvl);
	    me->add_temp("apply/strength", lvl/10);
	    me->add_temp("apply/hand", lvl);
	    me->add_temp("apply/attack", lvl);
		
	if( objectp(target) && me->is_fighting() )
	{
		if (random(5)>2 && !target->query_condition("dsy_poison"))
		{
			message_vision(HIG"$N手中泛出一片绿光，印向$n的胸口，$n一不小心中毒了。\n"NOR,me,target);
			target->apply_condition("dsy_poison", random(3) + 2 );
		}
		COMBAT_D->do_attack(me, target, 0, random(2)?3:1);

	}
	if(objectp(target) && me->is_fighting() )
		COMBAT_D->do_attack(me, target, 0, me->query_skill("dashou-yin",1)>160?3:1);

	if( objectp(target) && me->is_fighting() )
		COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
    
	if (me->query("quest/dls/dsy/tianyin/pass") && objectp(target)&& me->is_fighting())
	{
		message_vision(HIR"$N口中默念“明空智慧”诀，发气呵声，不避不挡，猛然拍出一掌，印向$n的前胸！\n"NOR,me,target);
		me->add_temp("apply/hand",lvl);
		//me->add_temp("apply/damage",lvl);
		COMBAT_D->do_attack(me, target, 0, 3);
		me->add_temp("apply/hand",-lvl);
		//me->add_temp("apply/hand",lvl);
	}
	me->add_temp("apply/damage", -lvl);
	me->add_temp("apply/strength",- lvl /10);
	me->add_temp("apply/hand",- lvl);
	me->add_temp("apply/attack",- lvl);
	
    me->delete_temp("dls/dsy");
	me->start_perform(4, "阿修罗无上梵天降魔宝印");
	me->start_busy(1+random(2));
	return 1;
}


int help(object me)
{
        write(HIG"\n大手印「阿修罗无上梵天降魔宝印」："NOR"\n\n");
        write(@HELP

	阿修罗天印。以无上降魔手印及深厚龙象内力催动阿修罗血煞剧毒
	攻击敌人。倘若遇到具有反震的强劲内功，则自己会受伤，请玩家
	自己注意。攻击力与命中等参数与毒计挂钩。
	
	指令：perform hand.tianyin

要求：
	最大内力需求 1000 以上；
	当前内力需求 700  以上；
	当前精力需求 500  以上；
	大手印的等级 250  以上；
	龙象般若功法 250 以上；
	毒技等级   80   以上
HELP
        );
        return 1;
}
