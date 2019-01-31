
//sandu.c 散毒
//散发各种蛇毒
//激发毒龙大法
//by sohu

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>



string perform_name(){ return HBBLU"散毒"NOR; }

int perform(object me, object target)
{
		string msg;
		string str;
		string* po;
		int skill;
		str = (string)me->query("env/金蛇缠丝手"); 		
        
		po=me->query("sld/poison");		
		skill=me->query_skill("chansi-shou",1);

		if (!po)
			return notify_fail("你体内没有任何蛇毒如何【散毒】?！\n");		
		if (!str)
			return notify_fail("你想散何种蛇毒《set 金蛇缠丝手 xxx》？！\n");		
		
		
		if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("【散毒】只能在战斗时用！\n");		
        		
		if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用【散毒】！\n");   
                
        if( (int)me->query_skill("chansi-shou", 1) < 400 )
                return notify_fail("你的金蛇缠丝手还不够娴熟，使不出【散毒】绝技。\n");
		if (me->query("gender")!="女性")
				return notify_fail("你非女性，使不出【散毒】绝技。\n");        
        if (me->query_skill_prepared("hand") != "chansi-shou"
            || me->query_skill_mapped("hand") != "chansi-shou"
			|| me->query_skill_mapped("parry") != "chansi-shou" )
                return notify_fail("你现在无法使用【散毒】进行攻击。\n");  

        if( (int)me->query_skill("dulong-dafa", 1) < 400 )
                return notify_fail("你的毒龙大法等级还不够，使不出【散毒】绝技。\n");
                
        if (me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("你的内功有误，无法使用【散毒】。\n");               
		            
        if( me->query("max_neili") < 5000 )
                return notify_fail("你现在内力太弱，使不出【散毒】。\n"); 
                     
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在真气太弱，使不出【散毒】。\n");
		if( (int)me->query("jingli") < 1000 )
                return notify_fail("你现在精力太弱，使不出【散毒】。\n");
		if (me->query_temp("chss/sandu"))
			return notify_fail("你正在施展【散毒】。\n");
		if (!me->query("quest/sld/chss/sandu/pass"))
			return notify_fail("你尚未得到缠丝手真传。\n");	
		
		msg = HBBLU"\n$N平时在神龙岛上终日与毒蛇为伴，体内积蓄的各种蛇毒已入骨髓。\n"NOR;
        msg+= HBBLU"此刻临阵敌前，$N暗运真气将体内毒素逼出蛇毒，集于掌中,蓄势待发!\n"NOR;
		msg+=HBBLU"$N突然轻飘飘一掌拍出，看似很缓慢，实则避无可避。掌风带起一股恶心的腥臭味。\n"NOR;
		message_vision(msg, me, target);
		me->set_temp("chss/sandu",1);
		call_out("remove_effect",1+skill/50,me);
		return 1;
}
int remove_effect(object me)
{
	if (!me||!me->query("chss/sandu")) return 0;
	me->delete_temp("chss/sandu");
	message_vision(BLU"$N长长吐出一口白雾，将参与的毒素吐出体外!\n"NOR,me);
	return 1;
}
int help(object me)
{
   write(WHT"\n缠丝手之「"RED"散毒"WHT"」："NOR"\n");
   write(@HELP
	缠丝手是神龙岛绝技之一，其中散毒的主要
	作用是将自己平时辛苦修炼的各种蛇毒都蓄
	积在体内，通过缠丝手法将残毒逼出来，使
	得对方中蛇毒。仅限女性。
	目前开放的蛇毒有：蛇毒、蟒蛇毒、五步蛇
	毒、金血蛇毒、银血蛇毒、神龙蛇毒、蝮蛇
	毒等七种蛇毒。

	perform hand.sandu

要求：
	最大内力要求 5000 以上；
	最大精力要求 1000 以上；
	当前内力要求 1000 以上；
	毒计等级     200  以上；
	缠丝手法等级 450 以上；
	毒龙大法等级 450 以上；
	神龙药理等级 200 以上；
	空手；
HELP
   );
   return 1;
}
