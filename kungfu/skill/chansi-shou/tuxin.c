//金蛇吐信
//by sjxa@winnerlife
//2014-08-07
inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>


string perform_name() {return HIG"金蛇吐信"NOR;}

void back(object target);

int perform(object me, object target)
{
	
		int lvl,lv, i, hit;
		string weapon,msg;

		lvl = me->query_skill("chansi-shou",1);
        lv =(int)lvl/15;

		if( !target ) target = offensive_target(me);

        if( !objectp(target) || !me->is_fighting(target) )
                return notify_fail("【神龙吐信】只能在战斗中使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用【神龙吐信】！\n");   
				
        if( (int)me->query_skill("chansi-shou", 1) < 250 )
                return notify_fail("你的神龙缠丝手还不够娴熟，使不出【神龙吐信】绝技。\n");
                
        if (me->query_skill_prepared("hand") != "chansi-shou"
			|| me->query_skill_mapped("parry") != "chansi-shou"
            || me->query_skill_mapped("hand") != "chansi-shou")
                return notify_fail("你激发不对，现在无法使用【神龙吐信】进行攻击。\n");  

        if( (int)me->query_skill("dulong-dafa", 1) < 250 )
                return notify_fail("你的毒龙大法等级还不够，使不出【神龙吐信】绝技。\n");
                
        if (me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("你的内功有误，无法使用【神龙吐信】。\n");               
		            
        if( me->query("max_neili") < 3000 )
                return notify_fail("你现在内力太弱，使不出【神龙吐信】。\n"); 
                     
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在真气太弱，使不出【神龙吐信】。\n");
		
        if( (int)target->query_temp("chss/duozhu") ) 
                return notify_fail("对方已经瞎了！\n");
	//主体
	  //起式
		message_vision(MAG"$N揉身上前，双臂突然以不可思议的角度，抢攻一招，$n淬不及防顿时招数大乱。\n"NOR, me, target);
	  // attack
        message_vision(RED"$N微微一声轻笑，猛然使出【"HIY"神龙吐信"RED"】，一步跨上$n肩头，左右双手直取$n双目。\n"NOR, me, target);
		if (me->query("gender")=="女性")
		{
			i=3;
			lvl=lvl+me->query_skill("dulong-dafa",1)/5;
		}
		else i=2;

		if (random(me->query("combat_exp"))>target->query("combat_exp")/i
			||random(me->query_dex(1))>target->query_dex(1)/i)
		{
			message_vision(HIR"$n惨叫一声，双目顿时血流如注，目不能视。\n"NOR,me,target);
			target->set_temp("chss/duozhu", 1);
			target->add_temp("apply/attack", - lvl/3);
			target->add_temp("apply/dodge", - lvl/2);
			target->add_temp("apply/parry", -lvl);
			target->receive_damage("qi", 2000+random(3000),me);
			target->receive_wound("qi", 1000+random(1000),me);
			target->set_temp("chss/duozhu",lvl);
			target->set_temp("block_msg/all",1);
			if (objectp(target))
				call_out("back", 3 + lv,target);
		}
		else if (random(me->query_int(1))>target->query_int(1)/i)
		{
			message_vision(HIW"$n见势不妙，急忙收腹缩身收招躲避，堪堪躲过一击，但还是被惊出一身冷汗。\n"NOR,me,target);
			target->receive_damage("qi", random(1000),me);
			target->receive_wound("qi", random(400),me);
			me->add_busy(1+random(2));
		}
		else {
			message_vision(HIC"$n早已预料到此招，抱头缩颈一个滚翻，总算躲开了$N这一招！\n"NOR,me,target);
			me->start_busy(2);
		} 		
			
		me->add("neili",-random(400));
		me->add("jingli",-random(200));
		if (!me->query("quest/sld/chss/pass"))
		{
			me->add_busy(1);
			me->start_perform(2, "「金蛇吐信」");
		}
		return 1;
}

void back(object target)
{
	int lvl;
	if(!target) return;
	
	lvl==target->query("chss/duozhu");

   	target->add_temp("apply/attack", lvl/3);
	target->add_temp("apply/dodge",lvl/2);
	target->add_temp("apply/parry", lvl);
    target->set_temp("block_msg/all", 0);
	target->delete_temp("chss/duozhu");

    if(living(target)) 
		tell_object(target, HIW "啊！总算双目没有被真正弄瞎，你又可以看见事物啦！\n" NOR);
	return;
}



int help(object me)
{
   write(WHT"\n金蛇缠丝手之「"HIG"神龙吐信"WHT"」："NOR"\n");
   write(@HELP
	金蛇缠丝手乃是神龙教不传之秘，是教中高手
	观摩神龙岛上的蛇斗演化而来，端的是刁钻阴
	险，滑不留手。施展后宛如神龙吐信，一不小
	会受到强烈的攻击，甚至有可能出现被金蛇夺
	珠而导致失明的危险。女性效果强于男性。
	
   注意：女性解开缠丝手谜题后，此招大飞,可以
	   作为起手式组合使用。

	指令：perform hand.tuxin
	   
要求：
	最大内力的要求 3000 以上；
	当前内力的要求 1000 以上；
	神龙缠丝手等级 250 以上；	
	毒龙大法的等级 250 以上；
	激发手法且备神龙缠丝手
	激发招架为金蛇缠丝手；
	激发内功为毒龙大法；
	女性优势明显；
    
HELP
      );
   return 1;
 }
