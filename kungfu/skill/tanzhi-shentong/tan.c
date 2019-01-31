// By sohu@xojh
#include <ansi.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h"

string perform_name() { return HIR"弹字诀"NOR; }

int perform(object me, object target)
{
        int damage, p;
        object weapon, weapon1;
        string msg, dodge_skill, *limbs, limb;
        
        if( !target ) target = offensive_target(me);
        weapon = me->query_temp("weapon");
        if( !objectp(target)  || !target->is_character() || !me->is_fighting(target) 
         || environment(target)!=environment(me))
                return notify_fail("弹指神通只能对战斗中的对手使用。\n");
        if( (int)me->query_skill("tanzhi-shentong", 1) < 300 )
                return notify_fail("你的弹指神通还未到火候，使不出来弹指神通。\n");
        if( (int)me->query_skill("bihai-chaosheng", 1) < 300)
                return notify_fail("你的碧海潮生功还未到火候。\n");     
        if( (int)me->query_skill("throwing", 1) < 300 )
                return notify_fail("你的基本暗器还未到火候，使不出来弹指神通。\n");
		if( me->query_skill_mapped("finger") !="tanzhi-shentong" 
			|| me->query_skill_mapped("parry") !="tanzhi-shentong"
			|| me->query_skill_prepared("finger") !="tanzhi-shentong")
                return notify_fail("你的激发的武功不对，使不出来弹指神通。\n");
        if (me->query_skill_mapped("force")!="bihai-chaosheng")
                return notify_fail("你的激发的内功不对，使不出来弹指神通。\n");
		if( (int)me->query("max_neili", 1) < 3000 )
                return notify_fail("你的内功修为不足以使出弹指神通绝技。\n");
        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("你的内力不足以使出弹指神通绝技。\n");
        if(target->is_busy())     
                return notify_fail("对方正自顾不暇呢，放胆攻击吧。\n");
		if( me->query_temp("thd/tan"))     
                return notify_fail("你正在使用弹指神通。\n");
		if( target->query_temp("thd/tan"))     
                return notify_fail("对方已经中了弹指神通。\n");
       // if (!objectp(weapon = me->query_temp("weapon")) 
			//&& (int)me->query_skill("tanzhi-shentong", 1) < 350)
               // return notify_fail("你现在无法使用弹指神通弹字诀。\n");
       if(weapon && (weapon->query("skill_type") != "throwing"
        || me->query_skill_mapped("throwing") != "tanzhi-shentong"))
                return notify_fail("你现在的武器无法使用弹指神通弹字诀。\n");
        if(weapon){
                if(weapon->query("skill_type") != "throwing" || me->query_skill_mapped("throwing") != "tanzhi-shentong")
                         return notify_fail("你现在的武器无法使用弹指神通。\n");
                msg = HBRED"\n只见$N"HBRED"双肩微晃，凝力于指，将"+weapon->name()+HBRED+"化作一道闪光从$P手中射出，直奔$n"HBRED"而去！\n"NOR; 
                }
        else msg = HBGRN"\n$N"HBGRN"暗运内劲于指，看准机会对着$n"HBGRN"一弹，一丝气劲激射而出，点向$p胸前大穴！\n"NOR; 
        
        me->add("neili", -350);
      
        limbs = target->query("limbs");
        limb = limbs[random(sizeof(limbs))];
        me->set_temp("thd/tan",1);

        if( random((int)me->query_dex()) < (int)target->query_dex()/2) {
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
				me->start_busy(2);
				me->delete_temp("thd/tan");
				message_vision(msg, me, target);
				me->start_perform(2, "弹字诀");
                return;
        } else if (weapon && objectp( weapon1 = target->query_temp("weapon")) && random(2)) {
                if( random((int)me->query_dex()) > (int)target->query_dex()/2
					||random(me->query("combat_exp"))>target->query("combat_exp")/2){
                         weapon1->unequip();
                         weapon1->move(environment(target));
                         target->reset_action();
						 msg += HIR"$n"HIR"只觉得手臂一麻，已被$N"HIR"的"+weapon->name()+HIR+"打中了穴道，不由自主地把手中的"+weapon1->name()+HIR+"坠地！\n"NOR;
                         if(!target->is_busy()) target->start_busy(3);
                         else target->add_busy(3+random(2));
						 if (userp(target))
						 	target->add_busy(2);
						 target->set_temp("thd/tan",1);
						 
						 
                } else {
                         dodge_skill = target->query_skill_mapped("dodge");
                         if( !dodge_skill ) dodge_skill = "dodge";
                         msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                }
        } else {
                damage = me->query_skill("finger",1) + me->query_skill("throwing",1) + me->query_temp("thd/is_fast");
                if(me->query("neili") > target->query("neili")*2)
                         damage *= 3;
                target->receive_damage("qi", damage, me);
				target->receive_wound("qi", damage/3, me);
                if(weapon)
                         target->receive_wound("qi", damage/3+random(damage/3), me);
                if(!target->is_busy()) 
                         target->start_busy(3+random(2));
				else target->add_busy(2+random(2));
				if (userp(target))
				{
					target->add_busy(2);
				}
				target->set_temp("thd/tan",1);

                p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
                msg += damage_msg(damage, "刺伤");
                msg += "( $n" + eff_status_msg(p) + " )\n";
                msg = replace_string(msg, "$l", limb);
                msg = replace_string(msg, "$w", weapon?weapon->name():"无形剑气"); 
        }
        call_out("remove_tan",1,me,target,(int)me->query_skill("tanzhi-shentong",1)/20);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
        message_vision(msg, me, target);
		
		if (me->query_skill("tanzhi-shentong",1)<350)
           me->start_perform(2, "弹字诀");
        me->delete_temp("thd/tan");
		return 1;
}

void remove_tan(object me,object target,int i)
{
   if (!me) return;
   if (!target || !living(target)) return;

   if ( i<0 ||!me->is_fighting() )
   {
       me->delete_temp("thd/tan");
	   target->delete_temp("thd/tan");
	   message_vision(HIY"$N缓缓收功，将弹指神通劲气压制了下来,长舒一口气。\n"NOR,me);
	   return;
   }
   if (random(6)>3)
   {
	   message_vision(HIG"$N运劲气于指，夹杂在弹指神通绝技中弹向$n。\n"NOR,me,target);
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
   }
   call_out("remove_tan",1,me,target,i-3);
   return;
}

int help(object me)
{
        write(HIR"\n弹指神通之「弹字诀」："NOR"\n");
        write(@HELP

	弹指神通乃是黄老邪的独门武技，以此争雄
	施展弹指神通的特殊诀窍，将碧海潮生功的
	内劲凝聚如同一把细剑攻击对手，或是将暗
	器附加劲气射出，在伤害对手之余更使其气
	血翻腾，并且手中若有兵器也有可能无法使
	劲而掉落。注意高身法增加命中。

	perform finger.tan

要求：
	碧海潮生等级 300 以上；
	弹指神通等级 300 以上；
	基本指法等级 300 以上；
	基本暗器等级 300 以上；
	最大内力要求 3000 以上；
	激发且备指法为弹指神通；
	激发招架弹指神通；
	激发内功碧海潮生；
	配合奇门五转使用攻击伤害增加；
	可配合暗器使用,350级后飞跃。
HELP
);
        return 1;
}

