//wanshe.c 万蛇噬体             
#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return HIB"万蛇噬体"NOR;}

int perform(object me,object target)
{
    object weapon;
    int i,damage;
	i=me->query_skill("lingshe-zhangfa",1)+me->query_skill("hamagong",1);

    if( !target ) target = offensive_target(me);
     
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("万蛇噬体只能对战斗中的对手使用。\n");
    if((int)me->query_skill("staff", 1) < 450 )
                return notify_fail("你的基本杖法不够娴熟，不能使用万蛇噬体。\n");
    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "staff"
        || me->query_skill_mapped("staff") != "lingshe-zhangfa")
                return notify_fail("你手里无杖，如何使用万蛇噬体？\n");
    if (me->query_skill("lingshe-zhangfa", 1) < 450 )
		            return notify_fail("你的灵蛇杖法还不够娴熟，使不出万蛇噬体绝技。\n");
	if (me->query_skill("hamagong", 1) < 450 )
		            return notify_fail("你的蛤蟆功等级不足，无法使用万蛇噬体。\n");
	if (me->query_skill("force") < 450 )
		            return notify_fail("你的内功等级不够，使不出万蛇噬体绝技。\n");
	if (me->query_str(1) < 70)
		            return notify_fail("你的膂力还不够强劲，使不出万蛇噬体绝技。\n");
	if (me->query_skill_mapped("force") != "hamagong")
		            return notify_fail("「万蛇噬体」需要用蛤蟆功为基础。\n");
    if (me->query("oyf/hamagong") < 3 )         
                return notify_fail("「万蛇噬体」需要在华山之巅得到欧阳锋指点才可学习使用。\n");
	  if (me->query_skill_mapped("staff") != "lingshe-zhangfa")
		  return notify_fail("你现在的状态还无法使出「万蛇噬体」绝技。\n");                
      if((int)me->query("max_neili") < 15000 )
                return notify_fail("你的内力修为不够，不能使用万蛇噬体！\n");
      if((int)me->query("neili") < 1000 )
                return notify_fail("你现在真气不足，不能使用万蛇噬体！\n");
                
        message_vision(HIR"\n$N将蛤蟆功凝于气海穴，口中发出「咕、咕、咕、咕、咕、咕、咕」的声音！\n"+
        ""HIB"突然只见$N使出灵蛇杖法最后一招「"HIM"万蛇噬体"NOR"」"HIB"，手中"+weapon->name()+HIB"向狂罩而去！\n"+
        ""HIG"此招乃欧阳锋于华山之巅为克打狗棒法第六变之天下无狗，殚精竭虑，耗尽心血而创，此招一出，便是洪七公再世，也得甘拜下风！\n"NOR,me,target);
    
    me->set_temp("lszf/wanshe",1);
    me->add("neili", -500-random(500));
    me->add_temp("apply/attack",  i/2);
    me->add_temp("apply/damage", i/3);
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
	         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
	{
         if (weapon->query("id")=="guaishe zhang")
         {
			 message_vision(HIB"$N忽然将手中怪蛇杖一抖，那两条怪蛇怪叫着瞬间喷出一股粉红色烟雾，笼罩向$n\n"NOR,me,target);
			 target->receive_wound("jing", 10,me);
             target->apply_condition("snake_poison", random(me->query_skill("lingshe-zhangfa",1)/10) + 1 +
                target->query_condition("bt_poison")); 
         }
		 message_vision(BLU"$N趁机用手中的"+weapon->query("name")+BLU"上的尖刺戳向$n的周身，宛如万蛇吐蕊状。"NOR,me,target);
		 if (random(me->query_str(1))>target->query_dex(1)/3)
		 {
			 message_vision(YEL"一不小心，为$N手中的兵器刺中穴道，顿时气血不由地一滞。\n"NOR,me,target);
			 target->add_busy(1+random(2));
			 target->apply_condition("no_exert",1);
		 }
		 else message_vision(CYN"$n轻轻向旁施展草上飞绝技，虽然有些狼狈，但还是躲了开去。\n"NOR,me,target);
		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	}
    if (me->is_fighting(target))
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

    
    damage=me->query_str(1)*damage/20+random(damage);
    if (me->is_fighting(target)
     	&& random(me->query_str(1)) > target->query_con()/2) 
	{
     	message_vision(HBRED"\n突见"+weapon->query("name")+HBRED"极速的旋转，宛若两条怪蛇交互疾行飞速缠住了$n身体！两条怪蛇迅速上串，\n"NOR,me,target);
     	target->add_busy(4+random(2));
     	message_vision(HBRED"这两条怪蛇飞身向$n咽喉部咬去，稳稳当当地咬住中了$n要害，$n像是中了蛇毒了！\n"NOR,me,target);
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/4,me);
        target->receive_damage("jing",damage/10,me);
     	target->add_condition("snake_poison",5+random(5));
     	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    }
    if (me->is_fighting(target)) {
     	message_vision(HIY"\n$N右手握"+weapon->name()+HIY"直挺，凝聚功力于"+weapon->name()+HIY"上，身行随风飘摆，而杖尖任他狂风暴雨也不移动，\n"+
	    HIY"单单直指$n心口，正是当初华山之巅欧阳锋呕心沥血最后一招破解「"HIG"天下无狗"NOR"」"HIY"的招式！\n"NOR, me, target);	   
		//target->receive_damage("qi",damage);
		target->receive_wound("qi",damage/6);
		target->apply_condition("no_perform",1+random(2));
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		}			                      
	if ( me->is_fighting(target)&&me->query_temp("hmg_nizhuan")){
		message_vision(HBBLU+HIW"\n九阴逆转之力在华山之巅再得欧阳锋指点之后，御蛇之术更胜从前，$N将九阴真力汇聚于"NOR+weapon->name()+HBBLU+HIW"\n$N将凝聚蛤蟆之力在九阴真力驱使下使出，犹如万千怪蛇凝立刻聚成一体向$n胸口重击而去！\n"NOR,me,target);
		me->set_temp("must_be_hit",1);
		me->add_temp("apply/damage",me->query_skill("hamagong",1)/4);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	    me->delete_temp("must_be_hit");
		me->add_temp("apply/damage",-me->query_skill("hamagong",1)/4);

      }
	me->delete_temp("lszf/wanshe");					
    me->add_temp("apply/attack",  -i/2);
    me->add_temp("apply/damage",  -i/3); 	
    me->start_perform(5,"「万蛇噬体」");
	me->start(2+random(2));
    return 1;
}

int help(object me)
{
        write(HIC"\n灵蛇杖法之"+HIB"「万蛇噬体」"NOR"\n\n");
        write(@HELP
	灵蛇杖法乃是白驼山武学精髓所在，欧阳锋一生以驱蛇和蛤蟆功名扬江湖，凭借此两
	大神技得意获得五绝称呼，并创立白驼山一脉武学。白驼山武学以狠辣、阴险、剧毒
	诡异为特色。万蛇噬体乃是欧阳锋晚年与洪七公在华山之巅一战，为了破解天下无狗
	的招式所创立，以至于洪七公看完后都不禁大为佩服。
	此招式为解密武功,属于绝世类别。
	要求：当前内力 1000  以上；
		当前精力 1000  以上；
		最大内力 15000 以上；
		基本杖法等级 450 以上；\
		蛤蟆功的等级 450 以上；
		后天臂力等级 70 以上；
		激发拳法为灵蛇拳法；
		激发招架为灵蛇杖法。

HELP
        );
        return 1;
}

