//chaodu.c  般若掌超度连环诀

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("超度连环诀只能对战斗中的对手使用。\n");

        if( me->query_temp("lianhuan") )
                return notify_fail("你已在使用超度连环诀了！\n");

        weapon = me->query_temp("weapon");
        if( objectp(weapon) )
                return notify_fail("你手中拿着家伙，如何能够施展连环诀？\n");

        if( me->query_skill_mapped("force") != "yijin-jing" )
                return notify_fail("你所用的并非易筋经神功，无法配合掌法施展连环诀！\n");

        if( me->query_skill("force",1) < 300 )
                return notify_fail("你的易筋经气功火候未到，无法配合施展连环诀！\n");

        if( me->query_dex() < 60 )
                return notify_fail("你的有效身法火候未到，无法配合施展连环诀！\n");
        if( me->query_skill("banruo-zhang",1) < 300 )
                return notify_fail("你般若掌修为不足，还不会使用超度诀！\n");


        if( me->query_skill("strike",1) < 300 )
                return notify_fail("你基本掌法修为不足，还不会使用连环诀！\n");

        if( me->query("neili") <= 1500 )
                return notify_fail("你的内力不够施展连环诀！\n");
		if( me->query("max_neili") <= 3500 )
                return notify_fail("你的内力不够施展连环诀！\n");
        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力不够施展连环诀！\n");

        skill = me->query_skill("banruo-zhang",1);
        
        message_vision(HIR "\n$N大喝一声，运掌如电,掌风霍霍，招招连环，正是佛门般若掌绝技之伏魔超度决！\n\n" NOR, me, target);

        me->set_temp("lianhuan", 1);
		if (me->query_skill("banruo-zhang",1)<349)
		{ 
			me->add_busy(1+random(2));
		}
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), skill/5);
        me->add("neili", -300);
        me->add("jingli", -100);
        
        return 1;
}

void remove_effect(object me, int amount)
{
        me->delete_temp("lianhuan");

        if ( me->is_fighting() ) {
                message_vision(HIR "\n$N的易筋经神功运行完毕，将内力收回丹田，手上招数也逐渐慢了下来。\n" NOR, me);
        }
        else {
                tell_object(me, HIR "\n你的易筋经功运行完毕，将内力缓缓收回丹田。\n\n" NOR);
        }
}
//般若掌是少林七十二绝技里最精妙的掌法，而且越练越强，学无止境。也就是说般若掌是没有威力上限的。
string perform_name(){ return HIY"超度连环诀"NOR; }
int help(object me)
{
        write(HIY"\n般若掌之「超度连环诀」："NOR"\n");
        write(@HELP
		般若掌是少林七十二绝技里最精妙的掌法，而且越练越强，学无止境。也就是说般若掌是没有威力上限的。
		同样是鸠摩智使出少林绝技，般若掌七尺凌空断铜炉的威力远在拈花指，燃木刀，如影随形腿等其他绝技之上，
		可见般若掌是威力与招式并重的高深武学。同时，般若掌还有护体神功，它又是门攻守兼备绝学，绝对称得上
		是七十二绝技里的极品。不过修炼起来难度也比较高，一般人都要花三四十年，即便是修炼一指禅历史第三快
		的橙观，也花了至少三十年。
		
		定位：超度为诀类，可以和一些技能实现嵌套，组合使用。		

        要求：  最大内力 3500 以上；      
                当前内力 1500  以上；  
                般若掌等级 300 以上；
                易筋经等级 300 以上；
                激发掌法为般若掌；
                且手无兵器；
				有效身法不得小于60。
                可以和大力金刚拳互备，350级后小飞。
                
HELP
        );
        return 1;
}