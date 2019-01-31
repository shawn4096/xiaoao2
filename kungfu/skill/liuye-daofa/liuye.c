//pikan.c by sohu@xojh


#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
		string msg;
		int p,damage;
		int ski=me->query_skill("liuye-daofa",1);
        
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("「柳叶刀诀」只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("liuye-daofa", 1) < 160 )
                return notify_fail("你的柳叶刀刀法功力太浅，无法使用「柳叶刀诀」攻击。\n");

        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 160 )
                return notify_fail("你的铁掌掌法功力太浅，无法使用「柳叶刀诀」攻击。\n");
      
        if( (int)me->query("max_neili") < 1600 )
                return notify_fail("你的内力太浅，无法使用「柳叶刀诀」攻击。\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不足，无法使用「柳叶刀诀」攻击。\n");
        if( (int)me->query("jingli") < 500 )
                return notify_fail("你的精力不足，无法使用「柳叶刀诀」攻击。\n");
        if( target->is_busy() )
                return notify_fail("对方已经手忙脚乱，无需使用「柳叶刀诀」攻击。\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "blade"
            || me->query_skill_mapped("blade") != "liuye-daofa" 
			|| me->query_skill_mapped("force") != "guiyuan-tunafa")
                return notify_fail("你的准备功夫不对。\n");

        message_vision(HIG"$N将手中的"+weapon->query("name")+HIG"瞬间数下，柔劲闪烁，如风吹柳叶刀般的罩向$n！\n" NOR,me,target);
        
		if (random(me->query_skill("blade",1))>target->query_skill("parry",1)/2
			||random(me->query_dex(1))>target->query_dex(1)/2)
		{
		
			

	
	   		message_vision(RED"$N深悟柳叶刀刀法的精髓，细刀如柳，劲气如丝，$n左躲右闪，终为刀影所惑！\n"NOR, me, target);	
			target->add_busy(1+random(3));

		}
		else {
			msg = CYN"可是$p轻功卓越，当即躲闪一旁。\n"NOR;
			me->add("neili", -100);
			message_vision(msg, me, target);
			me->start_busy(1);
		}	
		//me->start_perform(2, "柳叶刀诀");
		me->add("neili", -100);
		me->add("jingli", -50);

        return 1;
}

string perform_name(){ return HIG"柳叶刀诀"NOR; }

int help(object me)
{
        write(HIG"\n柳叶刀刀法之「柳叶刀诀」："NOR"\n\n");
        write(@HELP 
	柳叶刀刀法乃是铁掌帮弟子入门的武技，是历代帮主
	和长老们数年抗敌后总结提炼的一套实用刀法。该
	刀法以柳叶为主，刀法细腻，阴柔兼顾，柳叶刀绝技
	是放弃刀法劈砍等粗重进攻的要诀，反而走轻盈的要
	诀，会让对手不小心为刀影所迷惑。命中与武技等级
	和身法有关。
	
	指令：perform blade.liuye
		
要求：  
	当前内力 500 以上；
	最大内力 1600 以上；
	当前精力 500 以上；
	铁掌掌法等级 160 以上；
	柳叶刀法等级 160 以上；
	基本内功等级 160 以上；
	激发招架为柳叶刀法；
	激发刀法为柳叶刀法
	激发内功为归元吐纳法。
	手持刀类武器
HELP
        );
        return 1;
}