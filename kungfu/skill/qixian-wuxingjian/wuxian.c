// music.c
// modified by action@SJ 2009/1/10
// updated BY Zmud@Sjmud 10/3/2009
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	string msg, dodge_skill;
	object weapon;
	int ap, dp,i,skill;
    
	weapon = me->query_temp("weapon");
	if( !target ) target = offensive_target(me);
  
	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target)
	|| !living(target) )
		return notify_fail("「五弦音律」只能对战斗中的对手使用。\n");
    
	if( (int)me->query_skill("qixian-wuxingjian", 1) < 350 )
		return notify_fail("你的七弦无形剑等级不足，无法使用「五弦音律」。\n");

	if( (int)me->query_skill("sword", 1) < 350 )
		return notify_fail("你的基本剑法等级不足，无法使用「五弦音律」。\n");

	if( (int)me->query_skill("force", 1) < 350 )
		return notify_fail("你的基本内功等级不足，无法使用「五弦音律」。\n");

	if( (int)me->query("max_neili") < 5000 )
		return notify_fail("你的内力不足，无法使用「五弦音律」。\n");

	if( (int)me->query("neili") < 2000 )
		return notify_fail("你的真气不够。\n");		

	if(me->query_skill_mapped("sword") != "qixian-wuxingjian"
	 || me->query_skill_mapped("parry") != "qixian-wuxingjian"  )
		return notify_fail("你没有激发七炫无形剑，无法使用「五弦音律」？\n");
    //只有琴剑方可运使此招
	if (me->query_temp("qxwxj/wuxian"))
		return notify_fail("你正在使用「五弦音律」进行攻击。\n");
	
	if( !objectp(weapon)	 
	 || weapon->query("skill_type") != "sword"
	 || !weapon->query("qinjian"))
		return notify_fail("你手中无琴，你如何使得了「五弦音律」？\n");
	
	if( target->is_busy() )
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");
		
	ap = COMBAT_D->skill_power(me, "sword", SKILL_USAGE_ATTACK) + me->query("combat_exp")/10000;
	dp = COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE) + target->query("combat_exp")/10000;

	ap += me->query_int(1) * me->query_dex(1) ;
	dp += target->query_int(1) * target->query_con(1) ;
	
    skill=me->query_skill("qixian-wuxingjian",1);
	if( me->query_skill("qixian-wuxingjian", 1) > 350 )
		ap += random(ap/2);
        
		msg = "\n  "HIB"$N气定神闲，手指往" + weapon->name() +HIB"轻轻一弹，" + weapon->name() +HIB"旋即发出一阵震耳欲聋的高频音律，让四周之人感觉天旋地暗！\n"NOR;
        message_vision(msg, me, target);  
                   
       message_vision(HIM"\n在" + weapon->name() +HIR"上拨弦发声，并非故示闲暇，却是在琴音之中灌注上乘内力，用以扰乱"+
          "\n敌人心神，宫、商、角、徽、羽，依次迸发，绵绵密密，$n内力和琴音一起共鸣，$n便不知不觉自己招式已为琴音所制。\n"NOR,me,target);


	if ( random( ap + dp ) > dp
		||random(me->query_int())>target->query_int()) {
		message_vision(HIR "\n$n只觉得$N内力激荡，" + weapon->name() +HIR"发出的「"HIB"五弦音律"HIM"」犹如一柄利剑般穿透$n的鼓膜。\n"NOR,me,target);
		
		target->add_busy(2+random(2));
		if( !userp(target) ) target->add_busy(3);
		//对方陷入混乱，打不中
		if( target->query_temp("lost_attack") < 1 )
			target->add_temp("lost_attack", 3+random(2));
		
		target->apply_condition("neishang",3);
		target->apply_condition("no_exert",2);
		target->add("neili",-3000);
		me->add("neili", -500);
		me->add("jingli", -300);
		me->set_temp("qxwxj/wuxian",skill);
		call_out("remove_effect",1,me,target,skill/10);
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
        message_vision(HIC "\n可是$n看出$N企图，急忙凝神聚气，努力使自己不受「"HIB"五弦音律"NOR+HIC"」的干扰，将$n招数化解在无形之中。\n" NOR,me,target);

	    me->add("neili", -100);
		me->add("jingli", -50);
		me->start_busy(1);		
	}
	if (me->query_skill("qixian-wuxingjian",1)<350)
	   me->start_busy(1);
	if (me->query_skill("qixian-wuxingjian",1)<450) 
		me->start_perform(2, "「五弦音律」");

	message_vision(msg, me, target);
	return 1;
}


void remove_effect(object me, object target, int count)
{
        int skill;
		if (!objectp(me)) return;
	    skill=me->query_temp("qxwxj/wuxian");
		
		if (objectp(me) && me->query_temp("qxwxj/wuxian")){
                if (count-- > 0 && me->is_fighting(target)) {
                        call_out("remove_effect", 1, me, target, count);
                
                        return;
                }
		}
        message_vision(HIY"$N将手指从琴上拿开，急速喘息几口真气，方才一阵疾攻，消耗颇大，不得不缓缓收功。\n"NOR,me);
        me->delete_temp("qxwxj/wuxian");
        
		return;
   
}

string perform_name(){ return HIC"五弦音律"NOR; }
int help(object me)
{
         write(HIB"\n七弦无形剑"+HIC"「五弦音律」"NOR"\n");
        write(@HELP
	“七弦无形剑”乃是梅庄四友中老大，黄钟公的成名绝技。“七弦无形剑”
	是黄钟公自创的绝技。对敌的时候，通过在琴音之中灌注上乘内力，用
	以扰乱敌人心神，对方内力和琴音一生共鸣，便不知不觉地为琴音所制。
	琴音舒缓，对方出招也跟着舒缓；琴音急骤，对方出招也跟着急骤。但
	黄钟公琴上的招数却和琴音恰正相反。他出招快速而琴音加倍悠闲，对
	方势必无法挡架。
	「五弦音律」的主要作用是以深厚内力激发琴音，以五种琴音干扰袭扰
	对方，形成牵制,350后小飞，450后大飞。
	
	指令：perform sword.wuxian

要求：
	基本内功等级 350 以上；
	基本剑法等级 350 以上；
	七弦无形剑   350 以上；
	最大内力需求 5000以上；
	当前内力需求 2000以上
	无需特定门派内功支持。
	需带琴类武器并装备;

HELP
        );
        return 1;
}
