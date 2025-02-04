// lianhuan.c for huashan-jianfa
// by tiantian@SJ 11/05/2000.
// update by lsxk@hsbbs 2007/7/26 for增强剑宗使用威力.

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return MAG"夺命连环三仙剑"NOR;}

int perform(object me,object target)
{
    object weapon;
    
    if( !target ) target = offensive_target(me);
     
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("夺命连环三仙剑只能对战斗中的对手使用。\n");

    if(me->query_skill_mapped("force") != "huashan-qigong"
      &&me->query_skill_mapped("force") != "zixia-gong" )
                return notify_fail("你的特殊内功不对，无法使用夺命连环三仙剑！\n");
    if( (int)me->query_skill("huashan-qigong", 1) < 160
      &&(int)me->query_skill("zixia-gong", 1) < 160 )
                return notify_fail("你的内功还未练成，不能使用夺命连环三仙剑！\n");
    if( (int)me->query_skill("huashan-jianfa", 1) < 160 ) 
                return notify_fail("你的剑法还未练成，不能使用夺命连环三仙剑！\n");
    if((int)me->query_skill("sword", 1) < 160 )
                return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用夺命连环三仙剑。\n");
    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("你手里无剑，如何使用夺命连环三仙剑？\n");
                
    if((int)me->query("max_neili") < 2500 )
                return notify_fail("你的内力修为不够，不能使用夺命连环三仙剑！\n");
    if((int)me->query("neili") < 2000 )
                return notify_fail("你现在真气不足，不能使用夺命连环三仙剑！\n");
    if((int)me->query_temp("wudui"))
                return notify_fail("你正在使用无双无对！\n");

        message_vision(MAG"\n$N"MAG"长啸一声，使出平生绝技，连环三击，正是华山剑宗绝学“"HIR"夺命连环三仙剑"MAG"”！\n"NOR, me,target);

   
    me->set_temp("hsjf/lianhuan",1);
    me->add("neili", -200);
    me->add_temp("apply/attack",  me->query_skill("huashan-jianfa", 1)/4);
	//紫霞功开了且450后大飞
    if(me->query("quest/zixia/pass")&& me->query_skill("zixia-gong",1)>449)
   {
        message_vision(HIC"\n$N脸上紫气一闪，周身紫气大盛，运气于剑中，剑尖紫光闪烁，直指$n的“膻中穴”。\n"NOR,me,target);
		target->start_busy(1);
        me->add_temp("apply/armor",  me->query_skill("huashan-jianfa", 1)/3);
		me->add_temp("apply/attack",  me->query_skill("huashan-jianfa", 1)/3);
        me->add_temp("apply/strength",   me->query_skill("huashan-jianfa", 1)/3);
    }
    if(me->query("quest/huashan")=="剑宗")
   {
        target->start_busy(1+ random(2));
        me->add_temp("apply/damage",  me->query_skill("huashan-jianfa", 1)/3);
        me->add_temp("apply/sword",   me->query_skill("huashan-jianfa", 1)/3);
    }
    message_vision(HIC"\n$N身子腾空跃起，剑尖不住颤动，剑气凛冽，当头直劈$n的面门。\n"NOR,me,target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
   	if (me->is_fighting(target))
		message_vision(HIY"\n$N当即将劲力都运到了剑上，呼的一剑，拦腰横削$n的腰部。\n"NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
   	if (me->is_fighting(target))
	    message_vision(HIR"\n$N圈转长剑，长剑反撩，疾刺$n的后心，这一剑变招快极，$n背后不生眼睛，实在难以躲避。\n"NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        me->add_temp("apply/attack",  -me->query_skill("huashan-jianfa", 1)/4);
     if(me->query("quest/huashan")=="剑宗" && target->is_busy())
     {
        message_vision(HIC"$N将剑宗绝技华山连环三仙剑的奥秘尽数参透，趁$n手忙脚乱之际，顺势推剑，当胸刺去！\n"NOR,me,target);
        target->receive_damage("qi", me->query_skill("huashan-jianfa", 1),me);
        target->receive_wound("qi", me->query_skill("huashan-jianfa", 1)/2,me);
		target->set_temp("must_be_hit",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		target->delete_temp("must_be_hit",1);
      }
	if(me->query("quest/huashan")=="剑宗")
    {
        me->add_temp("apply/damage", - me->query_skill("huashan-jianfa", 1)/3);
        me->add_temp("apply/sword",    - me->query_skill("huashan-jianfa", 1)/3);
     }
    if(me->query("quest/zixia/pass")&& me->query_skill("zixia-gong",1)>449)
   {
       // message_vision(HIC"$N脸上紫气一闪，周身紫气大盛，运气于剑中，剑尖紫光闪烁，直指$n的“膻中穴”。\n"NOR,me,target);
		//target->start_busy(1);
        me->add_temp("apply/armor",  -me->query_skill("huashan-jianfa", 1)/3);
		me->add_temp("apply/attack",  -me->query_skill("huashan-jianfa", 1)/3);
        me->add_temp("apply/strength",   -me->query_skill("huashan-jianfa", 1)/3);
    }
	
    me->delete_temp("hsjf/lianhuan");
    me->start_busy(1);
	me->start_perform(4,"「夺命连环三仙剑」");
    return 1;
}

int help(object me)
{
   write(WHT"\n华山剑法「"MAG"夺命连环三仙剑"WHT"」："NOR"\n");
   write(@HELP
    这就是华山剑宗绝技「夺命连环三仙剑」！当年华山派剑宗、气宗之
    争，乃在华山玉女峰比剑争夺，剑宗弟子正是用了此招杀害了数名气
    宗好手，回想起当年战场，也令现在的气宗弟子骇然。气宗弟子虽视
    剑宗弟子为魔道，但心下却不禁佩服此招之高明，华山玉女峰一战后
    有少数气宗弟子竟然也在练习此招，但只是徒有架势，威力乃不及剑
    宗弟子之三、四成。气宗若解开紫霞功，本招以紫霞劲气灌注，威力
	也自不俗。

    指令：perform sword.lianhuan

要求：
	华山气功 或者 紫霞神功 160级
	华山剑法要求 160 级，
	基本剑法要求 160 级，
	最大内力要求 2500 以上，
	当前内力要求 2000 以上。
	若习得紫霞功且450级后，再次飞跃。
HELP
   );
   return 1;
}
