// posuo.c 蛇影婆娑
//将金蛇锥绝技融入到含沙射影中
//此门功夫原本是五毒教,需要用金蛇锥独立发射
//解开金蛇1

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	int skill,damage;
	string msg;
	object weapon;
	if (me->query("family/family_name")=="神龙教")
	{
		skill=me->query_skill("hansha-sheying", 1);
	}
	else skill=me->query_skill("jinshe-zhuifa", 1);
	
	damage=skill+me->query_skill("throwing",1);
	damage=damage*me->query_dex()/5;



	if (! target) target = offensive_target(me);
	if (! target ||	! me->is_fighting(target))
		return notify_fail("「蛇影婆娑」只能在战斗中使用。\n");

    if (!objectp(weapon = me->query_temp("weapon")) 
       ||(string)weapon->query("skill_type") != "throwing") 
           	return notify_fail("你手持的不是暗器，不能使用「蛇影婆娑」！\n");
    if (weapon->query_amount() < 1)
           	return notify_fail("你手持的暗器不够，无法使用「蛇影婆娑」绝招！\n");
	
	if (!me->query("quest/jinshe2/pass"))
		return notify_fail("你尚未解开金蛇2，不能使用「蛇影婆娑」绝招！\n");
	//if (!me->query("quest/sld/hssy/posuo/pass"))
		//return notify_fail("你尚未解开蛇影婆娑，不能使用「蛇影婆娑」绝招！\n");
	
	if (me->query_skill("jinshe-zhuifa", 1) < 450)
		return notify_fail("你的金蛇锥法不够娴熟，不会使用「蛇影婆娑」。\n");
	if (me->query_skill("throwing", 1) < 450)
		return notify_fail("你的基本暗器不够娴熟，不会使用「蛇影婆娑」。\n");
	if (me->query_skill("jinshe-zhangfa", 1) < 450)
		return notify_fail("你的金蛇掌法不够娴熟，不会使用「蛇影婆娑」。\n");
	if (me->query_skill("jinshe-zhuifa", 1) < 450)
		return notify_fail("你的金蛇锥法不够娴熟，不会使用「蛇影婆娑」。\n");
	if (me->query("family/family_name")=="神龙教"&&me->query_skill("chansi-shou", 1) < 450)
		return notify_fail("你的金蛇缠丝手不够娴熟，不会使用「蛇影婆娑」。\n");
	if (me->query("family/family_name")=="神龙教"&&me->query_skill("shenlong-tuifa", 1) < 450)
		return notify_fail("你的神龙腿法不够娴熟，不会使用「蛇影婆娑」。\n");
	if (me->query("family/family_name")=="神龙教"&&me->query_skill("hansha-sheying", 1) < 450)
		return notify_fail("你的含沙射影不够娴熟，不会使用「蛇影婆娑」。\n");
	if (me->query_skill_mapped("throwing")!="jinshe-zhuifa"
		&&me->query_skill_mapped("throwing")!="hansha-sheying")
		return notify_fail("你需要激发金蛇锥法或含沙射影，不会使用「蛇影婆娑」。\n");
	if ((int)me->query("neili") < 1000)
		return notify_fail("你内力不够了。\n");
	if ((int)me->query("jingli") < 500)
		return notify_fail("你精力不够了。\n");
	
	if (me->query("gener")!="女性")
	{
		skill=skill/3;
	}
	if (me->query_per(1)>25&&me->query_skill("poison",1)>150)
	{
		skill=skill+me->query_skill("poison",1);
	}
	weapon->add_amount(-1);

      message_vision(HIC "$N" HIC "清叱一声突然出手，数十道寒光随声暴射向$n，有的交击互撞，有的借力反弹，盘旋飞舞，满天而来。\n" NOR,me,target);
	  me->add_temp("apply/attack",skill/3);
	  me->add_temp("apply/damage",skill/4);
	  me->add_temp("apply/throwing",skill/4);

	  if (present("jinshe zhui",me))
	    if(random(me->query("combat_exp")) > (int)target->query("combat_exp")/2
		  || random(me->query_dex()) > (int)target->query_dex()/2) 
	  {
               
         message_vision(HIR"\n只听$n惨叫一声，无数"+HIY+"金蛇锥"+HIR+"已经击中全身要穴，看来已经被打成筛子了！\n"NOR, me, target);
         tell_object(target, HIY "啊！你全身上下都被暗器打穿了！\n" NOR);
         target->receive_damage("qi", damage,me);
         target->receive_wound("qi", damage/3,me);
         target->kill_ob(me);      
		 COMBAT_D->report_status(target, random(2));
       }
	   //神龙教含沙射影不一样
	  if (me->query("family/family_name")=="神龙教")
	   {	   
		   //第二招
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			//第三招，金蛇掌法
			weapon->unequip();
			if (me->query_skill("strike")=="jinshe-zhangfa"
				&&me->query_skill("jinshe-zhangfa",1)>450)
			{
				message_vision(HIY"\n身形一盘，身形婆娑，突然施展出金蛇掌法的功夫，手臂弯转，以不可思议角度突然攻向$n！\n"NOR, me, target);
				target->apply_condition("no_exert",1);
				me->add_temp("apply/strike",skill/3);
				//me->prepare_skill("none");
				me->prepare_skill("strike");
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				me->add_temp("apply/strike",-skill/3);
			}
			weapon->wield();
			//第四招 暗器
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			//第五招 缠丝手
			weapon->unequip();
			if (me->query_skill("hand")=="chansi-shou"
				&& me->query_skill_mapped("hand")=="chansi-shou"
				&& me->query_skill("chansi-shou",1)>450)
			{
				message_vision(HIM"\n$N妙曼玲珑，凹凸有致，双手忽变为金蛇缠丝手的招式，点、戳、缠如雨打飞花，攻向$n上半身大穴！\n"NOR, me, target);
				target->add_busy(2);
				me->prepare_skill("hand");
				me->add_temp("apply/hand",skill/3);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				me->add_temp("apply/hand",-skill/3);
			}
			weapon->wield();
	//暗器
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		//腿法
			weapon->unequip();
			if (me->query_skill("leg")=="shenlong-tuifa"
				&& me->query_skill_mapped("leg")=="shenlong-tuifa"
				&& me->query_skill("shenlong-tuifa",1)>450)
			{
				message_vision(HIR"\n$N跃起半空，瞬间连续踢出六招，以神龙腿法的招式攻向$n上半身大穴！\n"NOR, me, target);
				me->prepare_skill("leg");
				me->add_temp("apply/leg",skill/3);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				me->add_temp("apply/leg",-skill/3);
			}
			weapon->wield();
        }
		else {
			me->set_temp("jszf/posuo",1);
			me->add_temp("apply/throwing",(int)skill/3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			me->delete_temp("jszf/posuo");
			me->add_temp("apply/throwing",-(int)skill/3);
		}

		me->add_temp("apply/attack",-skill/3);
		me->add_temp("apply/damage",-skill/4);
		me->add_temp("apply/throwing",-skill/4);

		me->add("neili", -500);
        me->add("jingli", -300); 
		
		me->start_perform(5,"「蛇影婆娑」");
        me->add_busy(2);
		return 1;
}

string perform_name(){ return YEL"蛇影婆娑"NOR; }
int help(object me)
{
         write(HIB"\n金蛇锥法之「蛇影婆娑」："NOR"\n");
        write(@HELP
	金蛇锥法是金蛇郎君独门武技，蛇影婆娑是利用蛇的
	迅捷行走，快速出招，发射暗器。
	但神龙教的含沙射影武技经过后人不断演化，已经发
	生很大变异，和神龙教武功融合在一起。
	
	指令：perform throwing.posuo

要求：
	金蛇锥法等级：450 以上
	基本暗器等级：450 以上
	金蛇掌法等级  450 以上 
	含沙射影等级：450 (仅限神龙教)
	金蛇缠丝等级：450 (仅限神龙教)
	神龙腿法等级：450 (仅限神龙教)
	当前内力需求：1000 以上
	当前精力需求：500 以上
	需要激发金蛇锥法或含沙射影
	内功不限。
	手持暗器。

HELP
        );
        return 1;
}
