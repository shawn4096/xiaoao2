//fogang.c 佛光普照
// by snowman@SJ

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int damage, ap, dp, p, lvl;
	float at;
	string msg, dodge_skill;
 
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target))
		return notify_fail("「佛光普照」只能在战斗中使用。\n");

	if(objectp(me->query_temp("weapon")) )
		return notify_fail("你必须空手才能使用「佛光普照」！\n");

	if( me->query_skill("linji-zhuang", 1) < 250 && !wizardp(me))
		return notify_fail("你的临济十二庄未成，不能使用「佛光普照」！\n");

	if((int)me->query("max_neili") < 2000 )
		return notify_fail("你的内力修为不足，不能使用「佛光普照」！\n"); 

	if((int)me->query("neili") < 1000 )
		return notify_fail("你现在内力不足，不能使用「佛光普照」！\n"); 

	if((int)me->query_skill("jieshou-jiushi", 1) < 250 )
		return notify_fail("你的截手九式不够娴熟，不能使用「佛光普照」。\n");

	if((int)me->query_str(1) < 50)
		return notify_fail("你的膂力不足50，无法发挥「佛光普照」的气势。\n");

	if((int)me->query_con(1) < 25)
		return notify_fail("你的根骨欠佳，无法使用「佛光普照」。\n");

	if(me->query_skill_prepared("hand") != "jieshou-jiushi"
	|| me->query_skill_mapped("hand") != "jieshou-jiushi"
	|| me->query_skill_mapped("parry") != "jieshou-jiushi")
		return notify_fail("你必须全面运用截手九式，才能使用「佛光普照」。\n");

	if(me->query_skill_mapped("force") != "linji-zhuang" && !wizardp(me))
		return notify_fail("你不使用临济十二庄，怎么能使用「佛光普照」？\n");
/*
	if(me->query_temp("huanying")) 
		return notify_fail("你正在使用无形幻影，不能再使用「佛光普照」。\n");

	if(me->query_temp("shuangdao_hebi")) 
		return notify_fail("你正在使用「双刀合璧」，无法使用「佛光普照」。\n");
*/
	msg = MAG "\n只见$N面显庄严，突然间全身骨骼中发出劈劈拍拍的轻微爆裂之声，炒豆般的\n"+
		"响声未绝，一式「"HIY"佛光普照"MAG"」，提一口真气，飘身而上，半空中手掌交错，一\n"+
		"股内劲狭带着热浪，如风如火，似雷似电，这一招拍出，招式平平淡淡，一成\n"+
		"不变，击向$n，但却挡无可挡，避无可避！\n"NOR;
    lvl = me->query_skill("hand",1) + me->query_skill("linji-zhuang",1)+ me->query_skill("jieshou-jiushi",1);
	ap = me->query("combat_exp")/ 1000 * me->query_skill("jieshou-jiushi",1) * me->query_str(1) / 200;
	dp = target->query("combat_exp")/ 1000 * target->query_skill("force", 1) * target->query_con(1)/ 200;
    if (me->query_skill("jiuyin-zhengong",1)>150)
       ap+=me->query_skill("jiuyin-zhengong",1);
	if ( target->is_busy())
		dp -= dp/3;

	if(random( ap + dp ) > dp) {
		target->add_busy(1+random(2));
		damage = me->query_skill("hand") + me->query_skill("force");
		damage += me->query("jiali") * 15;        
		if(target->query("neili") < 10) at = 8;
		else at = me->query("neili") / (target->query("neili")+1);
		
		if(at < 1){
			if(at < 0.5) damage /= 2;
			else damage /= 1;
		}
		else if (at < 2 ) at = 2;
        
		else damage = to_int(damage*at);
		damage -= target->query_temp("apply/armor") * 2;
		if (damage < 0) damage = 0;
		damage = random(damage/2) + damage;
		//克制被九阳
		if (me->query("class")=="bonze")
            damage+=me->query_skill("dacheng-fofa",1);
		if (target->query_skill_mapped("force") == "jiuyang-shengong"
		&& target->query_skill("jiuyang-shengong", 1) > 200){
			tell_object(me, HIY"\n哪知你一掌打在"+target->name(1)+"身上，却犹如江河入海，又如水乳交融，劲力登时无影无踪！\n"NOR);
			msg += "猛听得砰然一声大响，$N已打中在$n胸口，只道$p定然全身骨骼粉碎。哪知一掌过去，\n"+
				"$n脸露讶色，竟好端端的站着，$N却是脸如死灰，手掌微微发抖！\n";
			target->add_busy(1);
			message_vision(msg, me, target);
			me->add("neili", -500);
			me->add("jingli", -100);
			me->start_perform(2, "「佛光普照」");
			return 1;
		}
		if((target->query_skill_mapped("force") == "yijin-jing"
		|| target->query_skill_mapped("force") == "yinyun-ziqi")
		&& target->query_temp("fanzhen")) 
			damage /= 2;
		else
			damage *= 2;
       
        if (damage > 8000) damage = 8000 + (damage-1000)/10;
		
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", random(damage), me);
		target->receive_damage("neili", damage/4);
		me->receive_damage("neili", 500);
		if(damage >= 8000)
			msg += HBCYN"这一招乃是使上了全力，丝毫不留余地，$n的生死存亡，便决于这顷刻之间！\n"NOR;
		p = (int)target->query("qi")*100/(int)target->query("max_qi");
		msg += COMBAT_D->damage_msg(damage, "瘀伤");
		msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		message_vision(msg, me, target);
        if(userp(me) && me->query("env/damage"))
			tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR); 
if(userp(target)&& target->query("env/damage"))      tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR); ;

	    if(!userp(target) && (random(2)|| p < 30) )  target->unconcious();
     
		me->start_perform(4, "「佛光普照」");
    }
     else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		msg += MAG"\n$N见一击不中，左手在空中划了一道优美的弧线，混若天成，右手顺手朝$n速攻了几招！\n"NOR;
		if (me->query_temp("emjy/powerup")&& me->query_skill("jieshou-jiushi",1)>449)
		{
			msg+= HIR"\n$N将自己所习得的峨眉九阳真气运使在这招武功中，手上劲力明显增强不少，指缝间嗤嗤有声！\n"NOR;
			target->add_busy(1+random(1));
            me->add_temp("apply/damage", me->query_skill("linji-zhuang",1)/5);
            me->add_temp("apply/attack", me->query_skill("linji-zhuang",1)/5);
			me->set_temp("emjy/efft",1);
		}
		message_vision(msg, me, target);
        me->set_temp("em_foguang",1);
        me->add_temp("apply/damage",  lvl/6);
        me->add_temp("apply/attack",  lvl/6);
        me->add_temp("apply/hand",  lvl/6);
		COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
		COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
		COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);
	    me->delete_temp("em_foguang");
	    me->add_temp("apply/damage",  -lvl/6);
        me->add_temp("apply/attack",  -lvl/6);
	    me->add_temp("apply/hand",  -lvl/6);
	   if (me->query_temp("emjy/efft"))
		{
			
            me->add_temp("apply/damage", -me->query_skill("linji-zhuang",1)/5);
            me->add_temp("apply/attack", -me->query_skill("linji-zhuang",1)/5);
			me->delete_temp("emjy/efft");
		}
		me->add("neili", -200);
		me->start_perform(3, "「佛光普照」");
	}
	me->add("jingli", -100);
	me->start_busy(random(2));
	return 1;
}

string perform_name(){ return HBMAG"佛光普照"NOR; }

int help(object me)
{
	write(HBMAG"\n截手九式之「佛光普照」："NOR"\n\n");
	write(@HELP
	截手九式乃峨眉空手武功中极为厉害的招式，是当初开山祖师郭襄
	前辈将家传武功以及早年四处历练所学所得后融汇贯通的各种招式，
	既有指法，也有拳法，还有手法。后来郭襄祖师大彻大悟后重新梳
	理这门武功，成为峨眉重要武技，【佛光普照】既有慈悲之意，又
	有绝杀之形。若附着峨眉九阳功力，该招攻击又将再上一层楼。若
	开了峨眉九阴，增加命中。注意：臂力越大命中越高；
	
	指令:perform hand.foguang
	
要求：
	当前内力的需求 1000 以上；
	最大内力的需求 2000 以上；
	截手九式的等级 250 以上；
	临济十二桩等级 250 以上；
	后天膂力的需求 25  以上,
	后天根骨的需求 25 以上；
	激发手法为截手九式；
	激发招架为截手九式；
	激发内功为临济十二桩；
	空手且备截手九式。

HELP
        );
        return 1;
}
