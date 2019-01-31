// hansha.c 含沙术
//将金蛇锥绝技融入到含沙射影中
//此门功夫原本是五毒教,需要用金蛇锥独立发射
//解开金蛇1

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int skill,damage;
	string msg;
	object weapon;
	skill=me->query_skill("hansha-sheying", 1);
	damage=skill+me->query_skill("jinshe-zhuifa",1);
	damage=damage*me->query_dex()/10;

	

	if (! target) target = offensive_target(me);
	if (! target ||	! me->is_fighting(target))
		return notify_fail("含沙术只能在战斗中使用。\n");

    if (!objectp(weapon = me->query_temp("weapon"))
        // ||(string)weapon->query("id") != "jinshe zhui"
		 ||(string)weapon->query("skill_type") != "throwing"
         ||  weapon->query_amount() < 1)
           	return notify_fail("你手里没拿暗器或暗器不足，不能使用含沙术绝招！\n");
	if (!me->query("quest/jinshe2/pass"))
		return notify_fail("你尚未解开金蛇2，不能使用含沙术绝招！\n");
	if (me->query_skill("jinshe-zhuifa", 1) < 350)
		return notify_fail("你的金蛇锥法不够娴熟，不会使用含沙术。\n");
	if (me->query_skill("throwing", 1) < 350)
		return notify_fail("你的基本暗器不够娴熟，不会使用含沙术。\n");
	if (me->query("family/family_name")=="神龙教"&&me->query_skill("hansha-sheying", 1) < 350)
		return notify_fail("你的含沙射影不够娴熟，不会使用含沙术。\n");
	if (me->query_skill_mapped("throwing")!="jinshe-zhuifa"
		&& me->query_skill_mapped("parry")!="hansha-sheying")
		return notify_fail("你需要激发金蛇锥法或含沙射影，不会使用含沙术。\n");
	if ((int)me->query("neili") < 1000)
		return notify_fail("你内力不够了。\n");
	if ((int)me->query("jingli") < 500)
		return notify_fail("你精力不够了。\n");
	if (target->query_temp("block_msg/all"))
		return notify_fail("对方已经中了你的含沙射影。\n");
	if (me->query("gender")!="女性")
	{
		damage=damage/3;
	}
		weapon->add_amount(-1);

        msg = HIY "$N" HIY "一声轻啸，身形微动，手中"+weapon->query("name")+HIY"竟然向上飞"
              "起绕了个圈，随而迅速袭向$n" HIY "的面前。\n" NOR;

        if (me->query_skill("hansha-shenying",1)/ 2 + random(skill) > target->query_skill("dodge", 1) 
			||random(me->query_skill("throwing",1))>target->query_skill("parry",1)/2
			||random(me->query_str(1))>target->query_dex(1)/2
			|| !living(target))
        {
        	target->receive_damage("qi", damage, me);
        	target->receive_wound("qi", damage/3, me);
        
        	msg += HIM "$N" HIM "手中的"+weapon->query("name")+HIM"闪出夺目的光芒，闪耀得$n" HIM "眼冒金花，$n" HIM"瞬间眩晕失神！\n" NOR;
        	msg += HIR""+weapon->query("name")+HIR"预势不减，顺势透$n的胸而过！\n" NOR;
            
			message_vision(msg, me, target);
        	me->set_temp("jinshe/hansha", 1);
        	target->set_temp("block_msg/all", 1);
			if (!target->query_temp("hssy/hansha"))
			{
				target->set_temp("hssy/hansha",skill);
				target->add_temp("apply/dodge",-skill/2);
				target->add_temp("apply/parry",-skill/2);
				target->add_temp("apply/defense",-skill/2);
				message_vision(HIG"$N眼前顿时为这云雾所笼罩，宛如深陷沙中，无所着力！\n"NOR,target);
			}
        	call_out("remove_hansha",1+random(2),target);
        } else
        {
            msg += CYN "$n" CYN "心中暗暗一惊，急忙后"
                       "退，闪开了这枚金蛇锥。\n" NOR;
			me->add_busy(1);       
        }
        me->add("neili", -500);
        me->add("jingli", -300); 
		message_vision(msg, me, target);
		//me->start_perform(1,"含沙术");
        me->reset_action();
		return 1;
}

void remove_hansha(object target)
{
	int skill;
	if (!target) return;
	skill=target->query_temp("hssy/hansha",skill);
 
	      //  message_combatd("$N抹了抹满脸的" HIR "鲜血" NOR "，终于睁开了眼。\n",
			     //   target);
	        target->set_temp("block_msg/all", 0);
			if (target->query_temp("hssy/hansha"))
			{
				
				target->add_temp("apply/dodge",skill/2);
				target->add_temp("apply/parry",skill/2);
				target->add_temp("apply/defense",skill/2);
				target->set_temp("hssy/hansha",skill);
				message_vision(HIG"$N运起功力，闪开一旁，长吁一口气，消除了含沙射影的影响！\n"NOR,target);
			}
	        tell_object(target,target->query("name")+HIR "终于抹掉了满脸的鲜血，看到了周围的情景。\n"NOR);
	 
	return;
}

string perform_name(){ return HBYEL"含沙术"NOR; }
int help(object me)
{
         write(HIB"\n金蛇锥法之「含沙术」："NOR"\n");
        write(@HELP
	金蛇锥法是金蛇郎君独门武技，利用高超暗器技法
	射出一枚金蛇锥，刁钻古怪的角度射出，可以短时
	造成对方的炫目和虚弱功效，同时造成杀伤。女性
	威力大。
	
	指令：perform throwing.hansha

要求：
	金蛇锥法等级：350 以上
	基本暗器等级：350 以上
	含沙射影等级：350 (仅限神龙教)
	当前内力需求：1000 以上
	当前精力需求：500 以上
	需要激发金蛇锥法或含沙射影
	手持暗器。
	内功不限。

HELP
        );
        return 1;
}
