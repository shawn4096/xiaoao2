// tuwu.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int skill,damage;
	string msg;
	object weapon;
	skill = me->query_skill("jinshe-zhui", 1);
//	if (me->query_temp("jinshe/tuwu"))
		//return notify_fail("你才用的吞云吐雾，没法接着就出招。\n");

	if (! target) target = offensive_target(me);
	if (! target ||	! me->is_fighting(target))
		return notify_fail("吞云吐雾只能在战斗中使用。\n");

    if (!objectp(weapon = me->query_temp("weapon"))
		||(string)weapon->query("skill_type") != "throwing" 
		||weapon->query_amount() < 1)
           	return notify_fail("你手里没拿暗器，不能使用绝招！\n");

	if (me->query_skill("jinshe-zhuifa", 1) < 100)
		return notify_fail("你的金蛇锥法不够娴熟，不会使用吞云吐雾。\n");

	if ((int)me->query("neili") < 300)
		return notify_fail("你内力不够了。\n");
	if (target->query_temp("block_msg/all")||target->query_temp("jszf/tuwu"))
		return notify_fail("对方已陷入你的迷雾中了。\n");
        
		weapon->add_amount(-5);
		damage=me->query_skill("jisnhe-zhuifa",1)+me->query_skill("throwing",1)+me->query_skill("jisnhe-zhangfa",1);
		damage=damage*me->query_str()/15+random(damage);
		if (weapon->query_amount()<5)
		{
			return notify_fail("你手中的暗器不多了，无法使用吞云吐雾。\n");
		}
        msg = HIY "$N" HIY "一声轻啸，身形微动，手中"+weapon->query("name")+HIY"洒出一片暗器，竟然向上飞"
              "起绕了个圈，随而迅速袭向$n" HIY "的面前。\n" NOR;
		message_vision(msg, me, target);
        if (skill / 2 + random(skill) > target->query_skill("dodge", 1)
		|| random(me->query_dex(1))>target->query_dex(1)/2	
		|| !living(target))
        {
        	me->add("neili", -200);
			if (wizardp(me)) 
			{
				write("damage="+damage);
			}
        	target->receive_damage("qi", damage, me);
        	target->receive_wound("qi", damage / 3, me);
        
        	msg = HIM "只听一阵狂风扫叶般的声响中，$N" HIM "手中的"+weapon->query("name")+
                       HIM"闪出夺目的光芒，闪耀得$n" HIM "眼冒金花，"
        	       "\n除了眼前一重重的雾气外，$n" HIM
        	       "啥也看不见了！\n" NOR;
            message_vision(msg, me, target);
        	//me->set_temp("jinshe/tuwu", 1);
        //	target->set_temp("block_msg/all", 1);
			//if (!target->query_temp("jszf/tuwu"))
			//{
				target->set_temp("jszf/tuwu",skill);
				target->add_temp("apply/dodge",-skill/2);
				target->add_temp("apply/parry",-skill/2);
			//}
			target->add_busy(2);
        	me->start_call_out((: call_other, __FILE__, "tuwu_end",target :),(int)skill/50);
        } else
        {
                msg = CYN "$n" CYN "心中暗暗一惊，急忙后"
                       "退，闪开了这枚"+weapon->query("name")+"。\n" NOR;
                message_vision(msg, me, target);
        }
		
       // me->reset_action();
	return 1;
}

void tuwu_end(object target)
{
	int skill;
	if (!target) return;

	skill=target->query_temp("jszf/tuwu");

        if (living(target))
        {
	        message_vision("$N抹了抹满脸的" HIR "鲜血" NOR "，终于睁开了眼。\n", target);
	     //   target->delete_temp("block_msg/all");
			target->add_temp("apply/dodge",skill/2);
			target->add_temp("apply/parry",skill/2);

	       // write(HIR "你终于抹掉了满脸的鲜血，看到了周围的情景。\n"NOR);
	        //if (me) me->delete_temp("jinshe/tuwu");
        }

	return;
}

string perform_name(){ return WHT"吞云"MAG"吐雾"NOR; }
int help(object me)
{
         write(HIB"\n金蛇锥法之「吞云吐雾」："NOR"\n");
        write(@HELP
	金蛇锥法是金蛇郎君独门武技，吞云吐雾是利用蛇的
	吞吐技能施展出一片暗器洒出，使得对方陷入一团迷
	雾之中不能自拔，命中和技能等级以及身法有关。
	
	指令：perform throwing.tuwu

要求：
	金蛇锥法等级：100 以上
	基本暗器等级：100 以上
	当前内力需求：1000 以上
	当前精力需求：500 以上
	需要激发金蛇锥法
	内功不限。
	手持暗器。

HELP
        );
        return 1;
}
