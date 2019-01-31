// roudao.c 胡家刀法之「柔刀诀」
// Create By lsxk@hsbbs 2007/5/12

#include <ansi.h>

inherit F_SSERVER;
string perform_name() {return HIG"柔刀诀"NOR;}
int perform(object me, object target)
{
        string msg;
		int skill=me->query_skill("hujia-daofa",1);
        object weapon = me->query_temp("weapon");
        int busy;

        if( !target ) target = offensive_target(me);

         if( !objectp(target)
          ||!target->is_character()
          ||!me->is_fighting(target) )
                return notify_fail("「柔刀诀」只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 450 )
                return notify_fail("你的胡家刀法不够娴熟，不会使用「柔刀诀」。\n");

        if ((int)me->query_skill("blade", 1) < 450 )
                return notify_fail("你的基本刀法不够娴熟，不会使用「柔刀诀」。\n");

        if ((int)me->query_skill("force", 1) < 450 )
                return notify_fail("你的基本内功不够娴熟，不会使用「柔刀诀」。\n");

        if (!weapon
         || weapon->query("skill_type") != "blade"
         || me->query_skill_mapped("blade") != "hujia-daofa")
//         || me->query_skill_mapped("parry") != "hujia-daofa")
                return notify_fail("你必须使用胡家刀法才能使用「柔刀诀」。\n");

        if( (int)me->query("neili") < 2000 )
                return notify_fail("你现在内力太弱，不能使用「柔刀诀」。\n");
        if( (int)me->query("jingli") < 1000 )
                return notify_fail("你现在体力太弱，不能使用「柔刀诀」。\n");

        if( target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");
		if( target->query_temp("hjdf/rdj"))
                return notify_fail(target->name() + "已经为你柔刀诀所中，放胆攻击吧！\n");
     //    if( me->query_temp("hjdf/rdj"))
               // return notify_fail( "你正在施展柔刀诀！\n");
		msg = HIG "$N招式一变竟使出胡家刀法之「柔刀诀」!此招一出，$N出招立即变得缓慢，但慢中却带柔劲，刀刃竟不出$n周身半尺！。\n"NOR;
		msg +=HIC"\n$N招式看似缓慢将周身围得水泄不通，实则乃是采用后发制人的高明招式，伺机而动。\n"NOR;
        me->add("neili", -200);
        me->add("jingli", -140);
        busy = (int)me->query_skill("hujia-daofa", 1)/150;
        if(random(me->query("combat_exp")) >  target->query("combat_exp")/2
           ||random(me->query_skill("force",1))>target->query("force",1)/2 )
		{
               msg += HIY"\n结果$p一个大意，身形滞缓，竟被$P攻得无法出招，当下暗暗吃惊！！\n" NOR;
               target->add_busy(busy);
               //me->set_temp("hjdf/rdj",skill);
			   target->add_temp("apply/parry",-skill/3);
			   target->add_temp("apply/dodge",-skill/4);
			   target->set_temp("hjdf/rdj",skill);
               call_out("check_fight", (int)skill/30, target,); 
        } else {
                msg += "\n$p大吃一惊，立即运足轻功逃脱了$P的刀刃范围，但也惊地心神不宁！\n" NOR;
                me->start_busy(2);
                target->add("neili",-600);
               // target->apply_condition("no_exert",1);
        }
		//me->start_perform(6,"「柔刀诀」");

        message_vision(msg, me, target);
        return 1;
}

void check_fight(object target)
{
      
		int skill;
		if (!target||!target->query_temp("hjdf/rdj")) return;
		skill=target->query_temp("hjdf/rdj");

		target->add_temp("apply/parry",-skill/3);
		target->add_temp("apply/dodge",-skill/4);
		target->delete_temp("hjdf/rdj");
		message_vision(HIG"$N身中「柔刀诀」的负面虚弱得到缓解。\n"NOR, target);
        return;

}
int help(object me)
{
   write(WHT"\n胡家刀法「"HIG"柔刀诀"WHT"」："NOR"\n");
   write(@HELP
	此「柔刀诀」乃巧用内劲，配合胡家刀法巧妙的招式，
	攻敌一个措手不及。此招乃十分依靠最基本的内功修
	为，越比敌人深厚，成功率就越高！柔刀诀乃是很好
	的防御招式，以慢打快，陷敌于刀气弥漫之中。此招
	乃是极为狠辣的防守反击招式。命中和战斗经验以及
	内功修为有关。目标中招后，防御力大幅下降。
	
	指令：perform blade.roudao

要求：
	胡家刀法 450 级，
	基本刀法 450 级，
	基本内功 450 级，
	最大内力 5000 以上，
	当前内力 2000 以上，
	当前精力 1000 以上，
	激发刀法为胡家刀法。
	手持刀类武器；
HELP
   );
   return 1;
}
