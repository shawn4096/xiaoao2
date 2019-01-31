// huifeng.c 回风诀
// cre by sohu
// 回风三击，源自灭绝师太攻击张无忌连续进攻

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int perform(object me,object target)
{
        object weapon;
        string msg;
        int i = me->query_skill("huifeng-jian",1) / 4;

        if( !target ) target = offensive_target(me);

         if( !objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("「回风决」只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("force") != "linji-zhuang")
                return notify_fail("你的内功不是峨嵋心法，无法使用灭绝心法！\n");
        if( me->query_skill("linji-zhuang", 1) < 180 )
                return notify_fail("你的内功还未练成，不能使用「回风决」！\n");
        if( me->query_skill("huifeng-jian", 1) < 180 )
                return notify_fail("你的剑法还未练成，不能使用「回风决」！\n");
        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "huifeng-jian")
                return notify_fail("你手里没有剑，无法使用「回风决」！\n");

        if(me->query_skill_mapped("parry") != "huifeng-jian")
                return notify_fail("你的招架功夫不对，无法使用「回风决」！\n");
        if(me->query("max_neili") < 1500 )
                return notify_fail("你的内力修为不够，不能使用「回风决」！\n");
        if(me->query("neili") < 500 )
                return notify_fail("你现在真气不足，不能使用「回风决」！\n");
        if(me->query("jingli") < 500 )
                return notify_fail("你现在精力不足，不能使用「回风决」！\n");
        if(me->query_temp("miejue"))
                return notify_fail("你正在使用「回风决」！\n");
        if(me->query_skill("sword", 1) < 150 )
                return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用「回风决」。\n");
      

        message_vision(HIC "$N剑法凌厉绝伦，连环三击而出，但见$N在$n周身穿插来去，东一刺，西一劈，瞬息间便刺出数招，出手之凌厉猛。\n"+
							weapon->query("name")+HIC"微侧，第一招便即抢攻，竟不挡格对方来招，剑尖直指$n丹田要穴悍，直是匪夷所思。\n"NOR,me,target);
        me->add("neili",-200);
		me->add("jingli",-100);
		me->add_temp("apply/attack",i*2);
		me->add_temp("apply/damage",i);
		me->set_temp("hfj/huifeng",1);
        message_vision(HIR"蓦地里$N"+weapon->query("name")+HIR"疾闪，剑尖已指到了$n咽喉!\n"	NOR,me,target);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
		
		message_vision(HIY"却见$N飘身而上，半空中举剑上挑，不等$n落地，剑光已封住了$n身周数尺之地。"NOR,me,target);
		target->add_busy(2);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
		
		message_vision(HIG"$N此时挥剑斜撩，削向$n手腕。\n"NOR,me,target);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/attack",-i*2);
		me->add_temp("apply/damage",-i);
		me->start_perform(3,"「回风决」"); 
		me->delete_temp("hfj/huifeng");
		me->start_busy(1);
		
        return 1;
}

string perform_name(){ return HIC"回风诀"NOR; }

int help(object me)
{
        write(HIW"\n回风拂柳剑之「回风诀」："NOR"\n\n");
        write(@HELP
	回风拂柳剑乃是峨眉不传之秘，开山祖师郭襄因少年时期经历
	极为丰富，阅历非常深厚后来一生奇遇不断，结合家传武学，
	武功造诣极为深厚。后来因暗恋杨过不得，郁郁终生，四十岁
	后大彻大悟，出家为尼，开创峨眉武学--回风拂柳剑。
	回风诀是灭绝师太在光明顶大战张无忌时所施展的连环三击，
	该招式不在于犀利，而在于快，短时间内快速数招，攻击对手
	防不胜防，稍有不慎，就会丧生在此招之下。

	指令；perform sword.huifeng

要求：
	当前内力的需求 500 以上；
	最大内力的需求 1500 以上；
	当前精力的需求 500 以上；
	回风拂柳剑等级 180 以上；
	临济十二庄等级 180 以上；
	激发内功为临济十二庄；
	激发剑法为回风拂柳剑；
	激发招架为回风拂柳剑；
	手持剑类兵器。

HELP
        );
        return 1;
}


