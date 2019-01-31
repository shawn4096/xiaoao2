//群魔乱舞
//xjqx 2008/12/30

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name(){ return HIG"群魔乱舞"NOR; }

int perform(object me,object target)
{
    object weapon;
    int i;
    
    if( !target ) target = offensive_target(me);
     
    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("群魔乱舞只能对战斗中的对手使用。\n");

    if (me->query_skill_mapped("force") != "tianmo-gong" 
		&& me->query_skill_mapped("force") != "xixing-dafa" )
             return notify_fail("你所使用的特殊内功不对。\n");  
    if(me->query_skill("xixing-dafa", 1)<250)
       if(me->query_skill("tianmo-gong", 1) < 250)
                return notify_fail("以你现在的内功修为还使不出「群魔乱舞」。\n");   
    if( (int)me->query_skill("tianmo-gun", 1) < 250 ) 
                return notify_fail("你的日月天魔棍还未练成，不能使用群魔乱舞！\n");
    if((int)me->query_skill("club", 1) < 250 )
                return notify_fail("你的基本棍法不够娴熟，不能在使用群魔乱舞。\n");
    if((int)me->query_dex()<35 )
                return notify_fail("你的身法还不够，还不能使用群魔乱舞。\n");
    if (!objectp(weapon = me->query_temp("weapon")) 
		|| weapon->query("skill_type") != "club"
        || me->query_skill_mapped("club") != "tianmo-gun"
        || me->query_skill_mapped("parry") != "tianmo-gun")
                return notify_fail("你现在使得了群魔乱舞么？\n");
                
    if((int)me->query("max_neili") < 1200 )
                return notify_fail("你的内力修为不够，不能使用群魔乱舞！\n");
    if((int)me->query("neili") < 800 )
                return notify_fail("你现在真气不足，不能使用群魔乱舞！\n");

        message_vision(HIG"\n$N将手中"+weapon->name()+HIG+"随意向四周舞动，棍风凌冽异常，将$n笼罩在$N的乱棍之内，随后连出四招。\n"NOR, me, target);

        i = (int)me->query_skill("tianmo-gun",1);
        me->add("neili", -200);
        me->add_temp("apply/attack",  i/3);
        me->add_temp("apply/damage",  i/5);
        me->set_temp("tmg/lw",1);
		target->add_busy(1);
        if (objectp(target)&&me->is_fighting(target))
       		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(i<450)?1:3);
        if (objectp(target)&&me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        if (objectp(target)&&me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(i<450)?1:3);
		if (objectp(target)&&me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        me->add_temp("apply/attack",  -i/3);
        me->add_temp("apply/damage",  -i/5);
        me->delete_temp("tmg/lw");
        me->start_perform(3+random(2),"「群魔乱舞」");

        me->start_busy(3);
        target->start_busy(1);
        return 1;
}

int help(object me)
{
   write(WHT"\n天魔棍法「"HIG"群魔乱舞"WHT"」："NOR"\n");
   write(@HELP
	天魔棍法是日月神教高级武功，乃是上代十大神魔张乘云
	张乘风所留，后来十大长老围攻华山，这二位长老下落不
	明，以至于这门武功中非常重要的武功失传，若能解开这
	个谜题，天魔棍法威力又上一个台阶。
	 
	指令：perform club.luanwu

要求：
	最大内力需求 1200 以上；
	当前内力需求 800 以上；
	日月天魔棍等级 250 以上；
	吸星大法等级 250 以上；
	后天身法需求 35 以上；
	激发招架为日月天魔棍。

HELP
   );
   return 1;
}
