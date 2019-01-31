//chansi.c 金蛇缠丝
//by sjxa@winnerlife
//2-14-08-08
//edit by sohu,重新定位武技名称为金蛇缠丝手，
inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

string perform_name() {return HIY"金蛇"HIW"缠丝"NOR;}

void chan(object me, object target,int count);

int perform(object me, object target)
{
		int lv, i;
		string weapon,msg;

		lv = me->query_skill("chansi-shou",1);
		lv=(int)lv/100;

		if( !target ) target = offensive_target(me);

        if( !objectp(target) || !me->is_fighting(target) )
                return notify_fail("【金蛇缠丝】只能在战斗中使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用【金蛇缠丝】！\n");   
		if( !me->query("quest/sld/chss/pass"))
                return notify_fail("你只是听说过缠丝手绝技，但不会使用【金蛇缠丝】！\n");   
                
        if( (int)me->query_skill("chansi-shou", 1) < 300 )
                return notify_fail("你的神龙缠丝手还不够娴熟，使不出【金蛇缠丝】绝技。\n");
                
        if (me->query_skill_prepared("hand") != "chansi-shou"
            || me->query_skill_mapped("hand") != "chansi-shou"
			|| me->query_skill_mapped("parry") != "chansi-shou" )
                return notify_fail("你现在无法使用【金蛇缠丝】进行攻击。\n");  

        if( (int)me->query_skill("dulong-dafa", 1) < 300 )
                return notify_fail("你的毒龙大法等级还不够，使不出【金蛇缠丝】绝技。\n");
                
        if (me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("你的内功有误，无法使用【金蛇缠丝】。\n");               
		            
        if( me->query("max_neili") < 5000 )
                return notify_fail("你现在内力太弱，使不出【金蛇缠丝】。\n"); 
                     
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在真气太弱，使不出【金蛇缠丝】。\n");

		if((int)target->query_temp("chss/chan"))
                return notify_fail("对方已经被缠住了，放手攻击吧。\n");
		if(me->query("gender")=="男性")
                return notify_fail("只有女性才能使用缠丝手的阴柔之意。\n");

        if (userp(target)) i=2;
		else i=3;
        
		
		message_vision(HBRED+HIW "正当$n力有不逮，思量如何变招之际，$N闪电般欺身向前，双臂如乌龙绞柱般缠住$n的双臂!\n" NOR,me,target);

		if (random(me->query_dex())>target->query_dex()/i
			||random(me->query_skill("hand",1))>target->query_skill("parry",1)/i)			
		{
			 message_vision(HBRED+HIW "$N趁势随$n的变招而动,一路连点$n"HIC"内关，外关，曲池，尺泽，风府，灵台"HBRED+HIW"周身各大要穴!\n" NOR,me,target);

			 target->set_temp("chss/chan", lv);
			 if (me->query("gender")=="女性")
				target->add_busy(lv+1);
			 else target->add_busy(1);
			 
			 if (objectp(target)&& me->is_fighting())
				 call_out("chan",1, me,target,lv);
		}
		else
		{
			message_vision(HIW "$n看出了你的企图，足尖轻点，抽身避过你这一招!\n" NOR,me,target);
			me->start_busy(2);
		}
		me->add("neili",-random(250));
		me->add("jingli",-random(100));
		//me->start_perform(3,"金蛇缠丝手");
	
		return 1;
}



void chan(object me, object target,int count)
{

	int lv;
	//int k;
	if(!target||!me) return;

	lv = me->query_skill("shenlong-chansishou",1);
	lv=lv/100;
	if (me->query("gender")!="女性") return;
	
	if (!me->is_fighting()
		||count<0)
	{
		message_vision(HBRED+HIC"$N内力无法再维持对$n的缠绕，不得不松开了双臂。\n" NOR,me,target);
		target->delete_temp("chss/chan");
		return;

	}

		message_vision(HBRED "$n感觉像被一条巨蟒缠绕，呼吸越来越困难，眼前景象逐渐模糊。\n" NOR,me,target);
	
		target->add("jing",- lv*20);
		target->add("neili",- lv*50);
		target->add("jingli",- lv*20);
		target->apply_condition("no_perform", 1);
		if (!userp(target))
			target->add_busy(1);
		if (objectp(me)&&objectp(target))
			call_out("chan",2, me,target,count--);
		return;
}

int help(object me)
{
   write(WHT"\n「"HIY"金蛇缠丝"WHT"」："NOR"\n");
   write(@HELP
	金蛇缠丝手乃是神龙教不传之秘，是教中高手
	观摩神龙岛上的蛇斗演化而来，端的是刁钻阴
	险，滑不留手。施展后宛如一条巨蟒般的随对
	手的变化而变化。一旦附身，甚是难以摆脱。

	perform hand.chansi
	
要求：
	最大内力的要求 5000 以上；	
	当前内力的要求 1000 以上；
	金蛇缠丝手等级 300 以上；
	毒龙大法的等级 300 以上；
	需激发且备手法为金蛇缠丝手
	激发内功为毒龙大法；
	身法高优势明显；
	仅限女性使用;
HELP
      );
   return 1;
   }