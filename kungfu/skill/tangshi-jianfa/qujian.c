//qujian.c
//by spiderii@ty参照SJ编写
//by sohu 重新编写并和神照经融合

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon, weapon2;
	string msg;
	int j, lvl = me->query_skill("tangshi-jianfa", 1);
    if (me->query_skill("shenzhao-jing",1)>349)
       lvl = me->query_skill("tangshi-jianfa", 1)+me->query_skill("shenzhao-jing", 1);
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("「去剑式」只能对战斗中的对手使用。\n");

	
    if( (int)me->query_skill("tangshi-jianfa", 1) < 150 ) 
                return notify_fail("你的躺尸剑法还未练成，无法使用「去剑」字诀！\n");

    if((int)me->query_skill("sword", 1) < 150 )
                return notify_fail("你的基本剑法不够娴熟，不能使用「去剑」字诀！\n");

    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "tangshi-jianfa")
                return notify_fail("你必须使用剑法，才能使出「去剑」字诀!\n");

    if(!objectp(weapon2 = target->query_temp("weapon"))||weapon2->query("skill_type")!="sword")
                return notify_fail("对方现在并没有使用剑类武器，你使用不了「去剑」字诀!\n");

  // if(me->query_skill_mapped("parry") != "tangshi-jianfa")
    //       return notify_fail("「去剑」字诀需要使用躺尸剑法招架一切敌方攻击。\n"); 

   if((int)me->query("max_neili") < 2500 )
           return notify_fail("你内力修为尚浅，使不出「去剑」字诀。\n");  

   if( (int)me->query("neili") < 500 )
           return notify_fail("你现在真气太弱，使不出「去剑」字诀。\n");


    msg =  HIW"$N清啸一声，抖直手中的兵刃，以连城剑法的「去剑」字决顺势搭上了$n的兵器！\n"NOR;
	message_vision(msg, me, target);
    me->set_temp("tangshi/qujian",1);
    if(random(2))
		   message_vision(HIC"跟着，$N翻过"+weapon->name()+HIC"，平靠"+weapon2->name()+HIC"，$N的"+weapon->name()+HIR"连转几个圈子。\n"NOR, me,target);
    else 
		   message_vision(HIY"跟着，$N"+weapon->name()+HIY"一伸，搭住"+weapon2->name()+HIY"，"+weapon->name()+HIY"如有胶水，将$n劲力全引到了相反的方向。\n"NOR, me,target);
     if( random( (int)me->query("combat_exp",1))> target->query("combat_exp") /2 
		 || random(me->query_int())> target->query_int()/2)
	  {
	     msg =HIY"只听得一阵金铁交鸣之声，结果$p的"+weapon2->name()+HIY"被$P手中的$W一连一带，远远地飞了开去！\n" NOR;
         message_vision(msg, me, target);
	     weapon2->move(environment(me));
	/*
		if (me->query("quest/shenzhao/laozu"))
         {
			msg = HIR"$N将所悟的神照经和唐诗剑法融合，运使开来，后续招式顺势而发，闪电般的击向$n！\n" NOR;
            message_vision(msg, me, target);
	  	    me->add_temp("apply/attack", lvl/3);	
	        me->add_temp("apply/damage", lvl/3);
            me->add_temp("apply/sword", lvl/3);
		 if (present(target,environment(me)) && me->is_fighting(target))
		   {
		    msg = HIC  "床前明月光，\n" NOR;
            message_vision(msg, me, target);
			COMBAT_D->do_attack(me,target, weapon, random(2)?1:3,msg);
		   }
		 if (present(target,environment(me)) && me->is_fighting(target))
		   {
		    msg = HIR  "疑是地上霜！\n" NOR;
            message_vision(msg, me, target);
			COMBAT_D->do_attack(me,target, weapon, random(2)?1:3,msg);
		   }
	     if (present(target,environment(me)) && me->is_fighting(target))
		   {
		    msg = HIG  "举头望明月！\n" NOR;
            message_vision(msg, me, target);
			COMBAT_D->do_attack(me,target, weapon, random(2)?1:3,msg);
		   }
          if (present(target,environment(me)) && me->is_fighting(target))
		   {
		    msg = HIY  "低头思故乡！\n" NOR;
            message_vision(msg, me, target);
			COMBAT_D->do_attack(me,target, weapon, random(2)?1:3,msg);
		   }  
         me->add_temp("apply/attack", -lvl/3);	
	     me->add_temp("apply/damage", -lvl/3);
		 me->add_temp("apply/sword", -lvl)/3;
	    } */ 
      } else {
         msg += "可是$p看破了$P的企图，并没有上当。\n" NOR;
         me->start_busy(1);
         message_vision(msg, me, target);
     }
	
	//me->start_busy(random(2));
	me->add("neili", -300);
	me->add("jingli", -100);
	if (me->query("shenzhao")<3)
		me->start_perform(1, "「去剑式」");
	return 1;
}

string perform_name(){ return HIY"去剑式"NOR; }

int help(object me)
{
        write(HIW"\n躺尸剑法之「去剑式」："NOR"\n\n");
        write(@HELP
	 “躺尸剑法”乃是金庸十四部武侠巨著中《连城诀》的著名武功
	主要是由反面角色“铁索横江”戚长发精研的一种剑术，他为了
	掩人耳目，把《唐诗剑法》蓄意讹传为“躺尸剑法”，其中的种
	种招数名称也改成谐音字或同声异形字，他曾把该剑术传给小
	说的主人公狄云。由此，以讹传讹,实乃滑天下之大稽。
	去剑式乃是源自言达平指导狄云中极为精妙的一招，借用剑光
	影响，以迅雷不及掩耳之式打掉对方的剑类兵器，解开神照经
	第三段后此招威力彻底释放。
	注意：此招仅对剑类武器有影响。
	
	指令：perform sword.qujian

要求：
	当前内力 2500 以上；
	最大内力 500 以上；
	躺尸剑法等级 150 以上；
	基本剑法等级 150 以上；
	解开神照经狄云question，此招飞跃

HELP
        );
        return 1;
}
