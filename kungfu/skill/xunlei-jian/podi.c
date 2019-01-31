// xunlei-jian perform
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        int lvl, j;
        object weapon;
        lvl = me->query_skill("xunlei-jian", 1);
        j = 1;
        if (lvl>350) j = 3;
		
		if(!userp(me)) lvl = lvl /3;

			weapon = me->query_temp("weapon");
        if( !target ) target = offensive_target(me);
        
		if( !target || !me->is_fighting(target) )
                return notify_fail("「迅雷破地」只能在战斗中对对手使用。\n");
                
        if (!weapon || weapon->query("skill_type") != "sword"
                         || me->query_skill_mapped("sword") != "xunlei-jian")
                return notify_fail("你必须在使用剑时才能使出「迅雷破地」\n");
                         
		if( (int)me->query_skill("kunlun-zhang", 1) < 300 )
			return notify_fail("你的昆仑掌等级不够，不能使用迅雷破地！\n"); 
      
		if (me->query_skill_prepared("strike") != "kunlun-zhang"
            || me->query_skill_mapped("strike") != "kunlun-zhang")
			return notify_fail("你没激发昆仑掌，现在无法使用迅雷破地进行攻击。\n");             
      
        if(me->query_skill("xunlei-jian", 1) < 300 )
                return notify_fail("你的迅雷剑还不够娴熟，使不出「迅雷破地」。\n");
		 if(me->query_dex() < 60 )
                return notify_fail("你的后天身法还不够娴熟，使不出「迅雷破地」。\n");
        if( (int)me->query("max_neili") < 3000 )
                return notify_fail("你现在最大内力太弱，使不出「迅雷破地」。\n");
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在真气太弱，使不出「迅雷破地」。\n");



        msg = HIY"\n$N身形陡起，宛如一只大雁跃向空中，在$n不知所措之际，在空中悠然转身，猛然伏地，幻出一片剑光！\n"
			+HIB"\n\n$N使出的正是迅雷十六剑之"HIW"「迅雷破地」"HIB"绝技，顿时一片白光直向前滚去！\n\n"NOR;
        message_vision(msg, me, target);
		if (lvl>350 && me->query("quest/kl/xlj/wuxue/pass"))
		{
			lvl=lvl+me->query_skill("force", 1)/5;
		}
		me->set_temp("xlj/podi",1);
		me->add("neili", -550); 
		me->add("jingli", -200);      
		//me->add_temp("apply/strength", lvl /10 );
		me->add_temp("apply/sword", lvl/4);
		//me->add_temp("apply/parry", lvl/3);
		me->add_temp("apply/damage", lvl /5 );
		me->add_temp("apply/attack", lvl /3);
		 
		if( random(me->query_skill("xunlei-jian",1)) > (int)target->query_skill("parry",1) *2/3)
		{ 
			message_vision(HIC"$n为漫天绚烂的剑光所惑，一时不查，顿时有些手忙脚乱。\n"NOR,me,target);
			target->add_busy(1+random(2));
		}

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), j);  
		if (me->is_fighting(target))
			 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), j);  
		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), j);  
			weapon->unequip(); 
		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), j); 
			weapon->wield();
		if (me->is_fighting(target)) 
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), j);  
			
      
		//me->add_temp("apply/strength", -lvl /10 );
		me->add_temp("apply/attack", -lvl /3);
		//me->add_temp("apply/parry", -lvl/3);

		me->add_temp("apply/sword", -lvl/4 );
		me->add_temp("apply/damage", -lvl /5 );

		me->start_busy(random(1)+1);
		me->delete_temp("xlj/podi");
		me->start_perform(3+random(2),"「迅雷破地」");
		return 1;
}
string perform_name(){ return HIY"迅雷破地"NOR; }
int help(object me)
{
	write(HIY"\n迅雷剑法之「迅雷破地」："NOR"\n\n");
	write(@HELP
	迅雷剑乃是昆仑的初级剑法，由何足道观悟天地变化所得。
	因昆仑山天高地寒，雷暴天气颇多，由此领悟剑法的快捷
	本意，需要高深的身法支持,若配合踏雪绝技，更是如虎添
	翼，威力倍增。
	迅雷破地：是迅雷剑的高级剑法，模仿雷电击打地面时所
	创，在绚烂的剑法中忽然出掌，以暗含红砂掌的威力重创
	对方，令对方防不胜防。既有速度又极为具有破坏力。
	注意：350级后迅雷剑小飞。
	
	指令：perform sword.podi

要求：
	当前内力要求 1000 以上；
	最大内力要求 3000 以上；
	迅雷剑法等级 300  以上；
	昆仑掌法等级 300  以上；
	有效腿法等级 60   以上；
	激发剑法为迅雷剑法；
	激发且备昆仑掌法；
	内功不限；
	必须手拿剑类武器。
	350级后飞跃,威力提升。
HELP
);
return 1;
}
