//金蛇乱舞
// by sjxa@winnerlife
//2014-08-07
inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

string perform_name() {return HIR"金蛇乱舞"NOR;}

int perform(object me, object target)
{
		int lv, i, hit;
		string weapon,msg;

		lv = me->query_skill("chansi-shou",1)+me->query_skill("dulong-dafa",1)/5;		

		if( !target ) target = offensive_target(me);

        if( !objectp(target) || !me->is_fighting(target) )
                return notify_fail("【金蛇乱舞】只能在战斗中使用。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用【金蛇乱舞】！\n");   
                
        if( (int)me->query_skill("chansi-shou", 1) < 350 )
                return notify_fail("你的金蛇缠丝手还不够娴熟，使不出【金蛇乱舞】绝技。\n");
                
        if (me->query_skill_prepared("hand") != "chansi-shou"
            || me->query_skill_mapped("hand") != "chansi-shou"
			|| me->query_skill_mapped("parry") != "chansi-shou" )
                return notify_fail("你现在无法使用【金蛇乱舞】进行攻击。\n");  

        if( (int)me->query_skill("dulong-dafa", 1) < 350 )
                return notify_fail("你的毒龙大法等级还不够，使不出【金蛇乱舞】绝技。\n");
                
        if (me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("你的内功有误，无法使用【金蛇乱舞】。\n");               
		            
        if( me->query("max_neili") < 5000 )
                return notify_fail("你现在内力太弱，使不出【金蛇乱舞】。\n"); 
                     
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在真气太弱，使不出【金蛇乱舞】。\n");
      
        
		if(me->query("gender")=="女性")
		{
			msg=HBRED+HIG"$N身形游动，全身骨骼发出炒豆般的响声，骤然间闪身一击，空气中发出“嘶~~”的一声犹如【"HIY"金蛇乱舞"HBRED+HIG"】时的呼啸。\n\n"NOR;
		
			// add busy
			msg+=HBBLU"$N眼中历芒犹如实质化一般射出，$n感觉自己仿佛被一只饥饿的巨蟒死死的盯住，立时动弹不得。\n\n"NOR;
			target->add_busy(1);
			//add 异常状态
			msg+=HIR"$N手法变幻莫测以崩、钻、按、冲、横、劈、勾七种招数罩向$n全身大穴。\n"NOR;
			message_vision(msg,me,target);
	
			switch(random(3))
			{
				case 0:
					message_vision(HIW"$n一口真气竟然提不起来，原来【"HIC"天溪"HIW"】、【"HIC"神封"HIW"】已经被$N击中！\n"NOR,me,target);
					target->add_condition("no_exert",1+random(5));
					break;
				case 1:
					message_vision(HIB"$n内息大乱，原来【"HIW"肩井"HIB"】、【"HIW"三焦"HIB"】已经被$N击中！\n"NOR,me,target);
					//target->add_condition("no_perform",1+random(5));
					target->add_busy(2);
					target->receive_damage("qi",random(1000),me);
					break;
				case 2:
					message_vision(HIC"$n闷哼一声，原来【"HIG"步廊穴"HIC"】已经被$N击中！\n"NOR,me,target);
					target->start_lost(1+random(5));
					break;
			}
			// 4hit
			message_vision(HIM"\n紧跟着$N招数一变以穿、插、按、劈、钻、压、摆、挑手法瞬间击出数招。\n"NOR,me,target);
			me->set_temp("chss/lw", 4);
			message_vision(HIY"$n左支右挡，奈何$N手法变幻万千，立时身中数招。\n"NOR,me,target);
			
			me->add_temp("apply/attck",lv/2);
			me->add_temp("apply/damage",lv/4);
			
			//message_vision(HIB"                                                                   ※※  "HIY"【金】"NOR  HIB"  ※※\n"NOR,me);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);

			//message_vision(HIB"                                                                   ※※  "HIY"【蛇】"NOR  HIB"  ※※\n"NOR,me);
	
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);

			//message_vision(HIB"                                                                   ※※  "HIY"【乱】"NOR  HIB"  ※※\n"NOR,me);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

			//message_vision(HIB"                                                                   ※※  "HIY"【舞】"NOR  HIB"  ※※\n"NOR,me);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			me->add_temp("apply/attck",-lv/2);
			me->add_temp("apply/damage",-lv/4);

			
		}
		else
		{
			//男性，就只有4hit

			message_vision(HIM"\n$N招数一变以穿、插、按、劈、钻、压、摆、挑手法瞬间击出数招。\n"NOR,me,target);
			me->set_temp("chss/lw", 4);
			
			//me->add_temp("apply/attck",lv/5);
			//me->add_temp("apply/damage",lv/8);
			//message_vision(HIB"                                                                   ※※  "HIM"【神】"NOR  HIB"  ※※\n"NOR,me);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);

			//message_vision(HIB"                                                                   ※※  "HIM"【龙】"NOR  HIB"  ※※\n"NOR,me);
	
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);

			//message_vision(HIB"                                                                   ※※  "HIM"【乱】"NOR  HIB"  ※※\n"NOR,me);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),  random(3)?1:3);

			//message_vision(HIB"                                                                   ※※  "HIM"【舞】"NOR  HIB"  ※※\n"NOR,me);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),  random(3)?1:3);
			//me->add_temp("apply/attck",-lv/5);
			//me->add_temp("apply/damage",-lv/8);
		
		}
		me->delete_temp("chss/lw");

		me->start_perform(5, "「金蛇乱舞」");
		me->add("neili",-200-random(400));
		me->add("jingli",-random(200));

		return 1;

}
//帮助
int help(object me)
{
   write(WHT"\n金蛇缠丝手之「"HIR"金蛇乱舞"WHT"」："NOR"\n");
   write(@HELP
	金蛇缠丝手乃是神龙教不传之秘，是教中高手
	观摩神龙岛上的蛇斗演化而来，端的是刁钻阴
	险，滑不留手。施展后宛如万蛇攒动，如狂风
	暴雨般攻向对方。女性效果强于男性。

	perform hand.luanwu
	   
要求：
	最大内力的要求 5000 以上；
	当前内力的要求 1000 以上；
	神龙缠丝手等级 350 以上；	
	毒龙大法的等级 350 以上；
	激发手法且备神龙缠丝手
	激发招架为金蛇缠丝手；
	激发内功为毒龙大法；
	女性优势明显；
HELP
      );
   return 1;
   }