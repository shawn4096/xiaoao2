// suo.c 锁剑诀

#include <ansi.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp, damage;
		
		weapon = me->query_temp("weapon");
        if (!objectp(weapon)
			|| weapon->query("skill_type")!="sword")
           return notify_fail("你没用剑类武器，不能使用绝招！\n");
		
		if (weapon->query("id") != "jinshe sword" && weapon->query("id") != "yinshe sword")
           return notify_fail("你没用金蛇剑或银蛇剑，不能使用绝招！\n");
        skill = me->query_skill("jinshe-jianfa",1);
        
		if( !target ) target = offensive_target(me);
		if (!me->query("quest/金蛇剑法/pass"))
			return notify_fail("你尚未全部领悟金蛇剑法精妙，不能使用此绝招！\n");
        if( !me->is_fighting() )
            return notify_fail("「锁剑诀」只能对战斗中的对手使用。\n");

        if (!objectp(weapon2 = target->query_temp("weapon")))
            return notify_fail("对方没有使用兵器，你用不了「锁剑诀」。\n");

        if( skill < 450)
            return notify_fail("你的金蛇剑法等级不够, 不能使用「锁剑诀」！\n");
		if (me->query_skill_mapped("sword")!="jinshe-jianfa"
			||me->query_skill_mapped("parry")!="jinshe-jianfa")
	        return notify_fail("你没有激发金蛇剑法, 不能使用「锁剑诀」！\n");

        if( me->query("neili") < 3000 )
            return notify_fail("你的真气不够，无法运用「锁剑诀」！\n");
        if( me->query("jingli") < 1000 )
            return notify_fail("你的精力不够，无法运用「锁剑诀」！\n");
        msg = HIC "$N手中"+weapon->query("name")+HIC"画出一道蛇形金光，斜刺一拉，一招「锁剑诀」！剑尖倒钩正好挂在$n的"+weapon2->name()+HIC"上。\n";
        message_vision(msg, me, target);

        ap = me->query_skill("sword",1)/3 + skill/2;
        dp = target->query_skill("dodge",1)/2;
        
         if( random(ap) > dp/2
			 ||random(me->query_str(1))>target->query_str(1)/2
			 || !living(target))
        {
            if(userp(me))
                 me->add("neili",-200);
            msg = "$n顿时觉得眼前金光一闪，手腕一振，手中";
         
			msg += weapon2->name();
            if (weapon2->query("skill_type")=="sword")
            {
				msg += "脱手飞出！\n" NOR;
				target->add_busy(3);
				weapon2->move(environment(target));

            }else {
				msg+="竟然为其尾刺所带动，顿时带动身形一晃！\n"NOR;
				target->add_busy(1);
			}
			msg+=HIR"$n为这诡异的招式所克制，一时间真气翻涌，气息难宁，竟然无法继续出招！\n"NOR;
			target->add_condition("no_perform",1);
        }
        else
        {
            if(userp(me))
                 me->add("neili",-100);
            msg = "$n急运内力，将手中" + weapon2->name()+
"斜斜顺势一送一搭，抽了回来。\n"NOR;
            me->start_busy(1);
        }
        message_vision(msg, me, target);
		me->add("neili",-350);
		me->add("jingli",-300);

        return 1;
}


int help(object me)
{
        write(HIY"\n金蛇剑法之「锁剑诀」："NOR"\n\n");
        write(@HELP
	金蛇郎君夏雪宜所流传下来的的绝世武功. 可惜在争夺中
	金蛇秘籍被分割成好几部分, 金蛇狂舞的威力也大不如前
	相传在凑齐金蛇秘籍中的剑法, 身法, 掌法后才能发挥金
	蛇剑法的真正威力. 如果有幸可以获得金蛇剑, 可使其威
	力更上层楼。
	锁剑诀是利用金蛇剑诡异之尾刺的作用，将对方兵器牵制
	对于剑类武器会直接锁住，非剑类武器有牵制功效。

	指令：perform sword.suo

要求：
	当前内力 3000 以上;
	当前精力 1000 以上；
	金蛇剑法 450 以上；
	先天臂力不能小于30,
	激发剑法金蛇剑法；
	激发招架金蛇剑法；
	内功不限；
    需装备金蛇剑或者银蛇剑
	解开金蛇3方可使用。

HELP
        );
        return 1;
}

string perform_name(){ return HIR"锁剑诀"NOR; }
