// duoming.c 苗家剑法之「连环夺命诀」。
// Write By lsxk@hsbbs 5/10/2007

#include <ansi.h>

inherit F_SSERVER;
string perform_name() {return HIY"连环夺命诀"NOR;}
int perform(object me,object target)
{
	object weapon;
   int i=me->query_skill("miaojia-jianfa",1);
   int d=me->query_skill("force",1);
   int count,hits;
   hits=(int)i/100;

	if( !target ) target = offensive_target(me);

        if( !objectp(target)|| !me->is_fighting(target) || !living(target)
	|| environment(target)!=environment(me))
           return notify_fail("此「连环夺命诀」只能对战斗中的对手使用。\n");

   if( (int)me->query_skill("miaojia-jianfa", 1) < 450 )
           return notify_fail("你的苗家剑法还未练成，不能使用「连环夺命诀」！\n");
   if((int)me->query_skill("sword", 1) < 450 )
           return notify_fail("你的基本剑法不够娴熟，无法使用「连环夺命诀」。\n");
   if((int)me->query_skill("force", 1) < 450 )
           return notify_fail("你的基本内功不够娴熟，无法使用「连环夺命诀」。\n");

	if(!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "sword"
   || me->query_skill_mapped("sword") != "miaojia-jianfa")
           return notify_fail("你手里没有剑，无法使用「连环夺命诀」！\n");

/*
   if(me->query_skill_mapped("parry") != "miaojia-jianfa")
           return notify_fail("你的招架功夫不对，无法使用「连环夺命诀」！\n");
*/
   if((int)me->query("max_neili") < 9000 )
           return notify_fail("你的内力修为不够，不能使用「连环夺命诀」！\n");
	if((int)me->query("neili") < 1000 )
           return notify_fail("你现在真气不足，不能使用「连环夺命诀」！\n");
	if((int)me->query("jingli") < 1000 )
           return notify_fail("你现在精力不足，不能使用「连环夺命诀」！\n");
    if((int)me->query_temp("mjjf/lianhuan"))
           return notify_fail("你正在使用「连环夺命诀」！\n");

	message_vision(HIY"\n$N"HIY"使出苗家剑法之「"HIW"连环夺命诀"HIY"」，但见$P手中"+weapon->name()+HIY"一阵疾舞，招招欲夺$n性命"HIY"！\n"NOR, me,target);
   if (me->query("quest/雪山飞狐/武功/lengquanshengong_teach")
    && me->query_temp("lqsg/lq")
    && me->query_skill_mapped("force") == "lengquan-shengong" )
   {
        me->set_temp("mjjf/lianhuan/lq",1);
        message_vision(HIW"$N更将冷泉神功内劲附在手中的"+weapon->name()+HIW"上，顿时四周到处弥漫吓人的剑气！\n"NOR, me,target);
     }

   me->set_temp("mjjf/lianhuan/color", 1);
   me->receive_damage("neili", 500);
   me->receive_damage("jingli", 500);

   me->add_temp("apply/attack", i/2);
   me->add_temp("apply/damage", d/4);
   me->add_temp("apply/dodge",i/2);

   for (count=0;count<hits;count++)
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

   me->add_temp("apply/damage", -d/4);
   //me->add_temp("apply/attack", -i/2);
   // me->add_temp("apply/dodge",-i/2);
   me->delete_temp("mjjf/lianhuan/color");
   me->start_perform(4, "「连环夺命诀」");
   call_out("check_fight", 1, me, i, d);
	return 1;
}
/*
void remove_effect2(object me, int i)
{
   if (me) me->add_temp("apply/dodge",-i/2);
}*/

void remove_effect(object me, int i, int d)
{
	if(!me) return;

   me->add_temp("apply/attack", -i/2);
   me->add_temp("apply/dodge",-i/2);
	if (living(me))
           message_vision(HIG"\n$N"HIG"一套「"HIW"连环夺命诀"HIG"」使完，气回丹田，剑招终于恢复正常。\n"NOR, me);
   if (me->query_temp("mjjf/lianhuan/lq")){
           message_vision(HIW"$N「"HIB"冷泉"HIW"」绝技使完，四周浓厚的剑气渐渐消失了。\n"NOR, me);
           me->delete_temp("mjjf/lianhuan/lq");
   }
   me->delete_temp("mjjf/lianhuan");
   me->start_perform(4, "「连环夺命诀」");
	d = 1 + random(2);
	me->add_busy(d);
	//call_out("remove_effect2", d+d, me, i);
	return;
}

void check_fight(object me, int j, int d)
{
	object weapon, target;
   int count;

	if (!me ) return;

	target = offensive_target(me);

   if(!living(me)
	|| !target
	|| !me->is_fighting(target)
	|| environment(target)!=environment(me)
   || !me->query_temp("mjjf/lianhuan")
	|| me->query("neili") < 200
	|| me->query("jingli") < 200)
		return remove_effect(me, j, d);

   if(me->query_skill_mapped("sword") != "miaojia-jianfa") {
           tell_object(me, HIR"你临时改换剑法，决定不再使用「连环夺命诀」绝技。\n");
		remove_effect(me, j, d);
	} else if(!objectp(weapon = me->query_temp("weapon"))
		|| weapon->query("skill_type") != "sword"){
           tell_object(me, HIR"你临时改换武器，决定不再使用「连环夺命诀」绝技。\n");
		remove_effect(me, j, d);
	} else if (me->is_busy())
           call_out("check_fight", 1, me, j, d);
	else {
		me->receive_damage("neili", 50);
		me->receive_damage("jingli", 50);
           if (objectp(target) && me->is_fighting(target)){
                   me->set_temp("mjjf/lianhuan/color", 1);
                   me->add_temp("apply/damage", d/5);
                   for (count=0;count<(random(3)+1);count++)
                   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                   me->add_temp("apply/damage", -d/5);
                   me->delete_temp("mjjf/lianhuan/color");
           }
           call_out("check_fight", 1, me, j, d);
	}
}

int help(object me)
{
   write(WHT"\n苗家剑法「"HIW"连环夺命诀"WHT"」："NOR"\n");
   write(@HELP
	此招「连环夺命诀」乃苗家剑法之精髓，使用后，能在战斗中
	接二连三的向对手施以攻击，往往另对手防不胜防！另若，使
	用者会武林绝学冷泉神功之「冷泉」绝技，则相辅相成，效果
	令人骇然！
	注意：此招等级越高，招式越多，攻击越强
	   
	指令:perform sword.duoming

要求：
	当前内力需求 1000 以上；
	最大内力需求 9000 以上；
	当前精力需求 1000 以上；
	苗家剑法等级 450 以上；
	基本内功等级 450 以上；
	基本剑法等级 450 以上；
	激发剑法为苗家剑法；
	且手持兵器。

HELP
   );
   return 1;
}
