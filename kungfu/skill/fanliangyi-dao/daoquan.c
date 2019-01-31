// shenfeng.c 刀夹掌
// by look
#include <ansi.h>

inherit F_SSERVER;


int perform(object me, object target)
{
        int lvl;
        object weapon = me->query_temp("weapon");
        lvl = ( (int)me->query_skill("fanliangyi-dao", 1) + (int)me->query_skill("poyu-quan", 1) ) /4;

        if( !target ) target = offensive_target(me);
     
        if( !target || !me->is_fighting(target) )
                return notify_fail("「刀夹掌」只能在战斗中对对手使用。\n");
	
        if (!weapon || weapon->query("skill_type") != "blade"
        || me->query_skill_mapped("blade") != "fanliangyi-dao")
                return notify_fail("你手里没有刀，无法使用「刀夹掌」！\n");             
        if (me->query_skill_mapped("blade") != "fanliangyi-dao"
			||me->query_skill_mapped("parry") != "fanliangyi-dao")
                return notify_fail("你没有激发反两仪刀，无法使用「刀夹掌」！\n");             

        if( (int)me->query_skill("fanliangyi-dao",1) < 100 )
                return notify_fail("你的反两仪刀不够娴熟，不能使用「刀夹掌」！\n");
      
        if( (int)me->query_skill("blade",1) < 100 )
                return notify_fail("你的基本刀法等级不够，不能使用「刀夹掌」！\n");  

        if( (int)me->query_skill("poyu-quan", 1) < 100 )
                return notify_fail("你的破玉拳法等级不够，不能使用「刀夹掌」！\n");
        if( (int)me->query_skill("qimen-bagua", 1) < 100 )
                return notify_fail("你的奇门八卦等级不够，不能使用「刀夹掌」！\n");

        if( (int)me->query_skill("zixia-gong", 1) < 100 )
			if( (int)me->query_skill("hushan-qigong", 1) < 100 )
                return notify_fail("你的华山内功等级不够，不能使用「刀夹掌」！\n");

        if( (int)me->query("max_neili") < 800 )
                return notify_fail("你的内力太弱，不能使用「刀夹掌」！\n");
      
        if( (int)me->query("neili") < 400 )
                return notify_fail("你的内力太少了，无法使用出「刀夹掌」！\n");   
                                                                                 
        if (me->query_skill_prepared("cuff") != "poyu-quan"
          || me->query_skill_mapped("cuff") != "poyu-quan")
                return notify_fail("你现在无法使用「刀夹掌」进行攻击。\n");


        message_vision(HIC"\n$N仰天一声清啸，运足内力使出「刀夹掌」，向$n雷霆般地打出两拳一刀！\n"NOR, me,target);
        me->add("neili", -(300+random(100))); 
        me->add("jingli", -100);      
        me->add_temp("apply/attack", lvl/4);
		me->add_temp("apply/cuff", lvl/3);
		me->add_temp("apply/damage", lvl/5);
		me->add_temp("apply/blade", lvl/5);

        weapon->unequip(); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(objectp(target)&&me->is_fighting(target))
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
       weapon->wield();
       if(objectp(target)&&me->is_fighting(target))
		{ 
       //       weapon->unequip();
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
         //     weapon->wield();
        }
		me->add_temp("apply/attack", -lvl/2);
		me->add_temp("apply/cuff", -lvl/3);
		me->add_temp("apply/damage", -lvl/5);
		me->add_temp("apply/blade", -lvl/5);

        me->start_busy(1);
	    me->start_perform(4 , "「刀夹掌」");
        return 1;
}
string perform_name(){ return HIR"刀夹掌"NOR; }
int help(object me)
{
        write(HIC"\n反两仪刀之「刀夹掌」："NOR"\n");
        write(@HELP
	此套刀法的步法招数与「昆仑派」的「正两仪剑法」一样，
	均从四象八卦中变化而出，都有八八六十四般变化。当初
	华山高矮二长老在光明顶一战，世人方知道这反两仪刀也
	是了不得的绝学。
	刀夹掌乃是反两仪刀绝学，瞬间施展出两拳一刀，非
	功力深厚者不能施展。

	指令：perform blade.hebi

要求：
	华山气功（紫霞功）的等级 100  以上；
	反两仪刀的等级 100  以上；
	基本刀法的等级 100  以上；
	奇门八卦的等级 100  以上
	当前内力的要求 1000  以上；
	当前精力的要求 1000  以上；
	激发刀法为反两仪刀；
	激发招架为反两仪刀；
	激发内功不限；
	手持刀。
HELP
        );
        return 1;
}
