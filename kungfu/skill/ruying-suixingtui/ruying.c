// ruying 如影随形
// by snowman@SJ 
// Modify by snowman@SJ 22/02/2000

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	mapping pre;
	string *skill, a, b;
	int i;

	if( !target ) target = offensive_target(me);

     if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
		return notify_fail("「如影随形」只能在战斗中对对手使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("使用「如影随形」时双手必须空着！\n");
	if( me->query_temp("fumo"))
		 return notify_fail("你正在使用大金刚拳的特殊攻击「金刚伏魔」！\n");
	if( (int)me->query_skill("ruying-suixingtui", 1) < 350 )
		return notify_fail("你的如影随形腿不够娴熟，不会使用「如影随形」。\n");

	if( (int)me->query_skill("yijin-jing", 1) < 350 )
		return notify_fail("你的易筋经等级不够，不能使用「如影随形」。\n");

	if (me->query_skill_mapped("force") != "yijin-jing")
		return notify_fail("你目前的内功无法支持你使用「如影随形」进行攻击。\n");  
			
	if( (int)me->query_dex() < 60 )
		return notify_fail("你的身法不够强，不能使用「如影随形」。\n");

	if (me->query_skill_prepared("leg") != "ruying-suixingtui"
	|| me->query_skill_mapped("leg") != "ruying-suixingtui")
		return notify_fail("你现在无法使用「如影随形」进行攻击。\n");  
											       
	if( (int)me->query("max_neili") < 5000 )
		return notify_fail("你现在内力修为太弱，不能使用「如影随形」。\n");
	if( (int)me->query("neili") < 1500 )
		return notify_fail("你目前内力太少，不能使用「如影随形」。\n");

	if( (int)me->query("jingli") < 500 )
		return notify_fail("你现在精力太少，不能使用「如影随形」。\n");


	message_vision(YEL"\n$N猛吸一口真气，体内劲力瞬时爆发，纵身而起，双脚幻起一片脚影，势若奔雷，向$n踢去！\n" NOR,me, target);
	
	pre = me->query_skill_prepare();
	skill = keys(pre);     
	
	for (i=0; i<sizeof(skill); i++){
		if(skill[i]=="leg") continue; 
		a = skill[i];
		b = pre[skill[i]];
		me->prepare_skill(a);
	}

	i = (int)me->query_skill("ruying-suixingtui", 1)+(int)me->query_skill("yijin-jing", 1)/2;
 
        me->add_temp("apply/attack", i);
        me->add_temp("apply/strength", i/15);
        me->add_temp("apply/leg",i/3);
        me->add_temp("apply/damage", i/4);
        me->add_temp("apply/dodge", i);


	me->set_temp("sl_rysxt", 5);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_RIPOSTE);
	me->add("neili", -80);
	if(me->is_fighting(target)){
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_RIPOSTE);
		me->add("neili", -80);
	}
	if(me->is_fighting(target) && me->query_skill("ruying-suixingtui", 1) >= 250){
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_RIPOSTE);
		me->add("neili", -80);
	}
	if(me->is_fighting(target) && me->query_skill("ruying-suixingtui", 1) >= 350){
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		me->add("neili", -100);
	}
	
	me->add_temp("apply/attack",- i);
    me->add_temp("apply/strength",- i/15);
    me->add_temp("apply/leg",- i/3);
    me->add_temp("apply/damage",- i/4);
    me->add_temp("apply/dodge", - i);
	
	// 5th kick is type_super. cannot be done in normal fight.
	//if(me->is_fighting(target) && me->is_killing(target->query("id"))
	  // && random(me->query_skill("ruying-suixingtui", 1)) >= 400) {
	if(me->is_fighting(target) && me->query_skill("ruying-suixingtui", 1) >= 500)
	{
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		me->add("neili", -150);
	}
	if (me->query("quest/sl/rysxt/pass")
		&&objectp(target)
		&&me->is_fighting()
		&&me->query_skill("ruying-suixingtui",1)>550)
	{
		message_vision(HBRED+HIY"$N双脚连续踢出，幻出一片脚影，将前几招蓄积的功力瞬间释放，势若奔雷!\n及至最后，这一片脚影化至无形，正是如影随形腿终极绝技---"NOR+HIC"「无影脚」！"NOR,me,target);
		me->add_temp("apply/leg",i/4);
		me->add_temp("apply/damage",i/4);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		me->add_temp("apply/leg",- i/4);
		me->add_temp("apply/damage",- i/4);
	}
	message_vision(YEL "\n$N连环飞腿使完，全身一转，稳稳落在地上，气定神闲。\n" NOR,me);
	me->prepare_skill(a,b);
	me->reset_action();

   

	me->delete_temp("sl_rysxt");

	me->start_busy(2);           

    me->start_perform(4,"「如影随形腿」");

	return 1;
}


string perform_name(){ return HIY"如影随行"NOR; }
int help(object me)
{
        write(HIB"\n如影随形腿之「如影随形」："NOR"\n");
        write(@HELP
	如影随形为少林七十二绝技之一，乃是少林绝技中腿法的极致。
	利用坚实的腿功和强大的内力，身子纵起空中，双腿不断连环
	踢出，令对手防不胜防，躲无可躲，端的是厉害非常。当初大
	轮寺鸠摩智一代圣僧，将偷学到的如影随形腿利用小无相功施
	展出来，虽然功力并不如易筋经激发的效果好，但其招式之精
	妙以及气势之雄浑，却是模仿的淋漓极致,550级解密后会出最
	后一招无影脚。
		
	注意：「如影随行腿」绝技最大的功效是连续进攻，一招比一
		招狠，练至绝顶招式，可连续出六招，气势如虹。最后一
		招需要解密获得。

要求：  
	最大内力 5000 以上；      
	当前内力 1500  以上；  
	如影随行腿等级 350 以上；
	易筋经等级 350 以上；
	激发腿法为如影随行腿；
	激发招架为如影随行腿；
	且手无兵器；
	有效身法不得小于60。
	需和如来千叶手互备有特殊功效。
                
HELP
        );
        return 1;
}
