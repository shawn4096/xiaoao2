// duanyun.c 峭壁断云
// by sohu@xojh 2014

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int damage,skill;
        string msg;
		object weapon;
		skill=me->query_skill("liangyi-jian",1);
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
			return notify_fail("「峭壁断云」只能对战斗中的对手使用。\n");
		if (!objectp(weapon = me->query_temp("weapon"))
			|| (string)weapon->query("skill_type") != "sword")
            return notify_fail("开什么玩笑，没装备剑就想使「百丈飞瀑」？\n");
                
		if( (int)me->query_skill("liangyi-jian",1)<350)
			return notify_fail("你的正两仪剑法不够娴熟，不会使用「峭壁断云」。\n");
		if( (int)me->query_skill("xuantian-wuji",1)<350)
			return notify_fail("你的玄天无极功不够深厚，不会使用「峭壁断云」。\n"); 
		if( (int)me->query_skill("sword",1)<350)
			return notify_fail("你的基本剑法不够深厚，不会使用「峭壁断云」。\n"); 
        if( (int)me->query("max_neili",1)<2500)
			return notify_fail("你现在最大内力太弱，不能使用「峭壁断云」。\n");                
		if( (int)me->query("neili",1)<1000)
			return notify_fail("你现在当前内力太弱，不能使用「峭壁断云」。\n");
		if( (int)me->query("jingli",1)<1000)
			return notify_fail("你现在当前精力太弱，不能使用「峭壁断云」。\n");
		if( (int)me->query_dex(1)<50)
			return notify_fail("你现在有效身法太弱，不能使用「峭壁断云」。\n");	
	                        
		message_vision(HIY "$N衣衫无风自动，当下斜斜刺出一剑,使出昆仑派两仪剑法中的镇山绝技「峭壁断云」。\n"
			HIG "刹那间天昏地暗，飞沙走石，无数剑影向$n的全身要害或刺，或砍，或劈而去。\n" NOR,me,target);
		
		if (userp(target)) 
			skill=skill+me->query_skill("xuantian-wuji",1)/3;
		
		me->add_temp("apply/attack",skill/3);
		me->add_temp("apply/damage",skill/5);
		me->set_temp("lyj/duanyun",4);
		if( (int)me->query_skill("art", 1) >= 200)
		{
			if (objectp(target) && me->is_fighting())
				COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(target)?1:3);
			
			if (objectp(target) && me->is_fighting())
				COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(target)?1:3);
			if (objectp(target) && me->is_fighting())
				COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
			if (objectp(target) && me->is_fighting())
				COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
			me->add("neili", -200);
		}
        if (random(me->query("neili")) > target->query("neili")/3 
			||random(me->query_dex())>target->query_dex()/2 )
		{
			               
			message_vision(HIC "\n$N这招「峭壁断云」剑招又变，断云式宛如大雁横空，陡然一剑而出，迅若疾雷。\n" NOR,me,target);
			damage= skill+(int)me->query_skill("sword",1)+(int)me->query_skill("xuantian-wuji",1)+(int)me->query_skill("liangyi-jue",1);
			damage = damage*3 + random(damage);                
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/2,me);
			me->add("neili",-100);
			msg=HIY"这招由正互变为反，正招反施，顿时威力大增！\n"NOR;
			if( damage < 2000 ) 
				msg += HIY"\n结果$n被$N刺中了一剑，闷哼一声，顿时鲜血如注。\n"NOR;
			else if( damage < 3000 ) msg += HIY"结果$n被$N连刺两剑，「啊」地一声退了两步。\n"NOR;
			else if( damage < 5000 ) msg += RED"结果$n被$N重重的连砍数剑，有如受到数记雷击一般，连退了五六步！\n"NOR;
			
			else msg += HIR"结果$n被$N的「峭壁断云」剑透前心，眼前一黑，身子向后飞出丈许！！\n"NOR;
			
			message_vision(msg, me, target);
			
			me->add_temp("apply/damage",skill/6);
			me->add_temp("apply/sword",skill/5);
			
			COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
			if (me->query("quest/kl/lyj/duanyun/pass")&&me->query_skill("liangyi-jian",1)>400)
			{
				message_vision(HIM "\n$N深的两仪剑的轻灵精髓，「峭壁断云」余势未尽，两仪剑由正变歪，极为诡异的角度一剑刺出。\n" NOR,me,target);
				target->set_temp("must_be_hit",1);
				me->add_temp("apply/damage",skill/6);
				COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
				me->add_temp("apply/damage",-skill/6);
				target->delete_temp("must_be_hit");
			}
			me->add_temp("apply/damage",-skill/6);
			me->add_temp("apply/sword",-skill/5);

			
		}
		else
		{
			me->start_busy(3);
            msg = CYN"可是$p看破了$P的企图，并没有上当。\n"NOR;
			message_vision(msg, me, target);
		}
		me->add_temp("apply/attack",-skill/3);
		me->add_temp("apply/damage",-skill/5);
		me->delete_temp("lyj/duanyun");	
		me->start_perform(4,"峭壁断云");
		return 1;
}

string perform_name() {return HIC"峭壁断云"NOR;}

int help(object me)
{
    write(WHT"\n两仪剑法「"HIC"峭壁断云"WHT"」："NOR"\n");
    write(@HELP
	两仪剑法乃是昆仑派绝技，当初昆仑三圣何足道以此
	剑法横扫西域诸雄。后来在少林大战中一战成名，凭
	借的就是此剑法。两仪剑乃是正宗的正两仪剑法，剑
	法轻灵迅捷，不以力胜，但却将剑法灵动多变发挥到
	极致。倘若身法轻功好则两仪剑法的威力更上一层楼
	注意：若从门中长老处解密此招奥秘，威力将又产生
	小飞跃。
    
	指令：perform sword.duanyun
	
要求：
	玄天无极等级 350 级以上；
	两仪剑法等级 350 级以上；
	有效身法等级 50    以上；
	基本剑法等级 350 级以上，
	最大内力要求 2500 以上，
	当前内力要求 1000 以上，
	当前精力要求 1000 以上，
	琴棋书画要求 200 以上，
	需手持剑类武器。    

HELP
	);
	return 1;
}
