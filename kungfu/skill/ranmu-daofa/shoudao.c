// shoudao.c 手刀

// by sohu@xojh 

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, string arg)
{
      object weapon, target;
      int i, j, z;       
     j = me->query_skill("ranmu-daofa", 1);
     weapon = me->query_temp("weapon");  
      

      if( !target ) target = offensive_target(me);

      if( !target || !me->is_fighting(target) )
           return notify_fail("「手刀」只能在战斗中对对手使用。\n");

      if (weapon)
		   return notify_fail("你手持武器，无法施展燃木刀法中「手刀」绝技。\n");
	  if (me->query_skill_mapped("strike") != "ranmu-daofa"
		||me->query_skill_prepared("strike") != "ranmu-daofa")
		   return notify_fail("你现在激发掌法非燃木刀法，无法使出「手刀」绝技！\n");
	  if (me->query_skill_mapped("blade") != "ranmu-daofa")
		   return notify_fail("你现在激发刀法非燃木刀法，无法使出「手刀」绝技！\n");
	  if (!me->query("quest/sl/rmdf/shoudao/pass"))
		   return notify_fail("你虽然听说过手刀绝技，但尚未得到传授，无法使出「手刀」绝技！\n");

       if(me->query_skill("ranmu-daofa", 1) < 500 )
                return notify_fail("你的燃木刀法火候不够，使不出「手刀」绝技。\n");

        if(me->query_skill("blade", 1) < 500 )
                return notify_fail("你的基本刀功还不够娴熟，使不出「手刀」绝技。\n");
        if(me->query_skill("strike", 1) < 500 )
                return notify_fail("你的基本掌法还不够娴熟，使不出「手刀」绝技。\n");

        if( (int)me->query_skill("force",1) < 500 )
                return notify_fail("你的基本内功等级不够，使不出「手刀」绝技。\n");

        if( (int)me->query_str() < 80)
                return notify_fail("你的膂力还不够强劲，需70，使不出「手刀」绝技。\n");

   
        if(me->query_skill("yijin-jing", 1) < 500 )   
                return notify_fail("你的易筋经修为不够，无法使用「手刀」绝技。\n");  

        if(me->query_temp("rmdf/shoudao")) 
			return notify_fail("你现在正在使用「手刀」绝技。\n"); 
//金刚伏魔仅为空手，兵器不能用金刚伏魔加成
        if (me->query_temp("fumo"))
			return notify_fail("你现在正在使用大力金刚拳「金刚伏魔」神功。\n"); 
        if (me->query("max_neili") < 15000)
			return notify_fail("你的最大内力不够。\n");

        if (me->query("neili") < 1000)
			return notify_fail("你的内力不够。\n");
        if (me->query("jingli") < 800)
			return notify_fail("你的精力不够。\n");
		
        message_vision(HBRED+HIY"$N有心炫耀，单臂削出，虽是空手，所使的却是正宗“燃木刀法”招式，向$n连续劈出九九八十一刀！\n"NOR,me,target);
        message_vision(HBRED+HIY"$N此刻是以手掌作戒刀，狠砍狠斫，全是少林派武功的路子。$N劲气汹涌，一刀劈落，波的一响！\n"NOR,me,target);

		me->add("neili", -1500);
        me->add("jingli", -1000);
        
		me->add_temp("apply/attack", j/2); 
        me->add_temp("apply/damage", j/3);
		me->add_temp("apply/strike", j/3);

		me->set_temp("rmdf/shoudao",5);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if (me->is_fighting())
		{
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		}
		if (me->is_fighting())
		{
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		}
		if (me->is_fighting())
		{
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		}
		if (me->is_fighting())
		{
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		}
		me->delete_temp("rmdf/shoudao");
/*
		if (me->is_fighting()&&)
		{
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		}*/
		me->add_temp("apply/attack", -j/2); 
        me->add_temp("apply/damage", -j/3);
		me->add_temp("apply/strike", -j/3);

		me->start_perform(5,"燃木手刀");
        return 1;
}

string perform_name(){ return HBRED+HIY"手刀绝技"NOR; }

int help(object me)
{
        write(HIY"\n燃木刀法之「手刀绝技」："NOR"\n\n");
        write(@HELP
	燃木刀法乃是少林三大终极兵器之一，是刀法的集大成武技
	此招乃是少林七十二绝技中不传之秘，武功练到高深处后，
	凭借深厚内力，可以做到以掌化刀，厉害无比。此门武功由
	少林玄苦大师修习，自玄苦大师圆寂后，此武技无人修成，
	当一代高僧鸠摩智凭借小无相神功演化燃木刀法大战少林寺
	时，使得此门武技名扬天下。
	
	注意：修习手刀绝技需要身兼少林基础刀法修罗刀的杀意和
		慈悲刀的慈悲之意，在杀伐和慈悲的融合中懂得手刀的
		精髓。切记，切记！
	
	指令：perform strike.shoudao 

要求：  
	当前内力需求 1000 以上；
	最大内力需求 15000 以上；
	当前精力需求 800 以上；
	燃木刀法等级 500 以上；
	易筋经功等级 500 以上；
	基本刀法等级 500 以上；
	基本掌法等级 500 以上；	
	激发掌法为燃木刀法；
	激发刀法为燃木刀法；
	激发招架为燃木刀法或慈悲刀；
	激发内功为易筋经神功；
	且空手。

HELP
        );
        return 1;
}
