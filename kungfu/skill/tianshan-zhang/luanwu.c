//By lsxk@hsbbs 2007/10/19
//群魔乱舞

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name(){ return HIB"群魔"HIR"乱舞"NOR; }

int perform(object me,object target)
{
    object weapon;
    int i;
    
    if( !target ) target = offensive_target(me);
     
    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("群魔乱舞只能对战斗中的对手使用。\n");

    if(me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("你的内功不是化功大发，无法使用群魔乱舞！\n");
    if( (int)me->query_skill("huagong-dafa", 1) < 160 )
                return notify_fail("你的内功还未练成，不能使用群魔乱舞！\n");
    if( (int)me->query_skill("tianshan-zhang", 1) < 160 ) 
                return notify_fail("你的天山杖法还未练成，不能使用群魔乱舞！\n");
    if((int)me->query_skill("staff", 1) < 160 )
                return notify_fail("你的基本杖法不够娴熟，不能在使用群魔乱舞。\n");
    if((int)me->query_skill("poison", 1) < 100 )
                return notify_fail("你的毒技不够娴熟，不能在使用群魔乱舞。\n");
    if((int)me->query_dex(1) < 30 )
                return notify_fail("你的身法还不够灵巧，不能使用群魔乱舞。\n");
	if (me->query_skill_mapped("claw") != "sanyin-zhua"
        || me->query_skill_prepared("claw") != "sanyin-zhua")
                return notify_fail("你需激发并准备三阴蜈蚣爪，否则无法使得群魔乱舞。\n");
    if (!objectp(weapon = me->query_temp("weapon")) 
		|| weapon->query("skill_type") != "staff"
        || me->query_skill_mapped("staff") != "tianshan-zhang"
        || me->query_skill_mapped("parry") != "tianshan-zhang")
                return notify_fail("你现在使得了群魔乱舞么？\n");
                
    if((int)me->query("max_neili") < 1500 )
                return notify_fail("你的内力修为不够，不能使用群魔乱舞！\n");
    if((int)me->query("neili") < 500 )
                return notify_fail("你现在真气不足，不能使用群魔乱舞！\n");

        message_vision(HIB"\n$N突然一声怪叫，脚步飘忽不定，瞬间已然向$n挥出数招，气势吓人之极！\n"NOR,me,target);

       
        i = (int)me->query_skill("tianshan-zhang",1);
		if (me->query_skill("huagong-dafa",1)>350)
		    i += (int)me->query_skill("huagong-dafa",1)/5;
        if (!userp(target))
			i += (int)me->query_skill("huagong-dafa",1)/5;
		me->add("neili", -300);
        me->add_temp("apply/attack",  i/2);
        me->add_temp("apply/damage",  i/5);
        me->set_temp("tsz/lw",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(i<250)?1:3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),(i<350)?1:3);       
       // COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	
     if (me->is_fighting(target))
	 { 
		 weapon->unequip(); 
	     me->add_temp("apply/claw", i);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1); 
		 me->add_temp("apply/claw", -i);
         weapon->wield();
	 }
	 if (me->is_fighting(target))
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack",  -i/2);
        me->add_temp("apply/damage",  -i/5);
        me->delete_temp("tsz/lw");
    me->start_busy(1);
    target->start_busy(1);
	me->start_perform(4+random(2),"「群魔乱舞」");
    return 1;
}

int help(object me)
{
   write(WHT"\n天山杖法「"HIB"群魔"HIR"乱舞"WHT"」："NOR"\n");
   write(@HELP
	天山杖法定位成星宿派初期中期武技，威力不俗
	星宿弟子以此横行江湖，此招为天山杖法中挥舞
	杖子向四周敌人横扫一片的招数。
	
	perform staff.luanwu
  
要求：
	最大内力要求 1500 以上；
	当前内力要求 500 以上；
	天山杖法等级 160 以上；
	化功大法等级 160 以上；
	后天身法要求 30 以上；
	毒技等级要求 100 以上；
	激发招架为天山杖法,
	激发杖法为天山杖法；
	激发且备爪法为三阴蜈蚣爪；
	需持杖类武器。
	350后飞跃，450后略微增强。

HELP
   );
   return 1;
}
