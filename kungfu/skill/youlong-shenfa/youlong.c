// youlong.c 游龙
// by sohu@xojh
//蛇一般动作，躲避
//增加在身法aoto躲避中

#include <ansi.h>

inherit F_SSERVER;

void remove(object me,object target,int cs);

int perform(object me, object target)
{
        string msg;
        int skill; 
        

        if( !me->is_fighting() )
                return notify_fail("「神龙游行」只能在战斗时使用！\n");
        if( (skill=(int)me->query_skill("youlong-shenfa",1)) < 300 )
                return notify_fail("你的游龙身法还不够熟练，不能使用「神龙游行」！\n");

	if (me->query_skill_mapped("dodge") != "youlong-shenfa")
		return notify_fail("只有施展游龙身法时才能使用「神龙游行」！\n");
	if( (int)me->query_skill("dulong-dafa", 1) < 300 )
        return notify_fail("你的毒龙大法功力不足，不能用「神龙游行」。\n");

	if( (int)me->query_skill("dodge", 1) < 300 )
        return notify_fail("你的基本轻功功力不足，不能用「神龙游行」。\n");
    if((int)me->query("jingli", 1)<1000)
		return notify_fail("你现在精力不足，不能使用「神龙游行」！\n");       
	if(((int)me->query("neili", 1)<1500) ) 
		return notify_fail("你现在内力不足，不能再次使用「神龙游行」！\n"); 

    if (me->query_temp("ylsf/youlong")) return notify_fail("你正在使用「神龙游行」！\n"); 
	
   	msg = HIG "\n$N忽然猛一提气，身法宛如游蛇一般，快速游走，身形立刻迅捷了数倍！\n"NOR; 
	message_vision(msg, me);
	me->add("jingli",-100);
	me->add("neili",-200);

	me->add_temp("apply/dodge",skill/6);
	me->set_temp("ylsf/youlong",skill);
	
	if (me->query("quest/sld/ylsf/youlong/pass")
		&&me->query_temp("dldf/dulong")
		&&me->is_busy())
	{
		message_vision(BLU"$N感觉自己有些忙碌，毒龙大法毒龙诀瞬间发动，强行施展神龙游行的招式\n宛如一条巨蟒般的滑不留手，瞬间化解！\n"NOR,me);
		me->start_busy(-1);
	}

	call_out("remove_youlong",60,me,(int)skill/30);
    return 1;       
}

void remove_youlong(object me,int count)
{
	int skill;
	if (!me||!me->query_temp("ylsf/youlong")) return;
	skill=me->query_temp("ylsf/youlong");	
		me->add_temp("apply/dodge",-skill/6);
		me->delete_temp("ylsf/youlong");
		message_vision(BLU"$N游龙身法停了下来，身形恢复正常！\n"NOR,me);
		return;		
}
string perform_name(){ return HIY"神龙游行"NOR; }


int help(object me)
{
   write(HIG"\n游龙身法之「"HIY"神龙游行"NOR"」："NOR"\n");
   write(@HELP
	游龙身法乃是神龙岛独特的轻功身法。原本乃是
	模仿蛇形的方式来在战斗中躲闪和进攻，起到非
	常重要的辅助进攻作用。
	神龙游行在战斗时会有机会摆脱对方的部分牵制
	此功能需解密方可习得。	
   
	指令：perform dodge.youlong

要求：
	当前内力要求 1500 以上；
	当前精力要求 1000 以上；
	游龙身法等级 300 以上；
	毒龙大法要求 300 以上。
	激发轻功为游龙身法；
	激发内功为毒龙大法；
	运使毒龙诀后会消除自己busy

HELP
   );
   return 1;
}

