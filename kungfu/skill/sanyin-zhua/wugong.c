// wugong.c 蜈蚣抓
// cre by sohu@xojh

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

void check_fight(object me,object target);
int perform(object me, object target)
{
        string msg;
        int skill;
        skill = (int)me->query_skill("sanyin-zhua", 1)+(int)me->query_skill("huagong-dafa", 1)/4;                

       if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("「蜈蚣抓」只能在战斗中对对手使用。\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("使用「蜈蚣抓」时双手必须空着！\n");

        if( (int)me->query_skill("sanyin-zhua", 1) < 350 )
                return notify_fail("你的三阴蜈蚣抓不够娴熟，不会使用「蜈蚣抓」。\n");

        if( (int)me->query_skill("huagong-dafa", 1) < 350 )
                return notify_fail("你的化功大法内功等级不够，不能使用「蜈蚣抓」。\n");

        if( (int)me->query_dex() < 27 )
                return notify_fail("你的身法不够强，不能使用「蜈蚣抓」。\n");

        if (me->query_skill_prepared("claw") != "sanyin-zhua"
        || me->query_skill_mapped("claw") != "sanyin-zhua")
                return notify_fail("你现在无法使用「蜈蚣抓」进行攻击。\n");
        if( (int)me->query("max_neili") < 3500 )
                return notify_fail("你现在内力太弱，不能使用「蜈蚣抓」。\n");
        if( (int)me->query("neili") < 1500 )
                return notify_fail("你现在内力太弱，不能使用「蜈蚣抓」。\n");

        if( target->query_temp("syz/wugong")   )
                return notify_fail(target->name() + "已经为你「蜈蚣抓」所伤，放胆攻击吧。！\n");

// 42          me->start_perform(2,"三阴蜈蚣抓")
        msg = HIC "$N双手张开，陡然向外一分，双掌幻起一片掌影，正是星宿派三阴蜈蚣爪绝技「蜈蚣抓」\n" NOR;
		msg += HIB "$N运起化功大法，宛如蜈蚣竖起千手千脚，渐至无穷之势，霎时幻起漫天的抓影。\n" NOR;
		msg += HBBLU+HIW "$N劲力弥漫，双爪挥舞间，若隐若现的带出些灰色有毒气体。\n" NOR;

        message_vision(msg, me, target);
        if (random(me->query("combat_exp")) > target->query("combat_exp")/2
			||random(me->query_skill("claw",1))>target->query_skill("parry",1)/3)
		{
          msg = HIY "\n$n忽觉一股难闻的气味呛的极为难受，身形停滞，$n只觉得四周都是$N的抓影，压得$n喘不过气来。\n" NOR;
          message_vision(msg, me, target);
          if (me->query_skill("poison",1)>target->query_skill("poison",1)
			  &&!target->query_condition("xx_poison"))
          {
			  message_vision(HIB"$n忽觉经脉一阵寒意，随即刺痛无比，显然已经为中了三阴抓的毒！\n"NOR,me,target);
			  target->add_condition("xx_poison",2);
          }
		  if (!userp(target))
		 		  target->add_busy(3);
		  else target->add_busy(1);

		  target->add_temp("apply/attack", -skill/5);
          target->add_temp("apply/dodge", -skill/5);
          target->add_temp("apply/parry", -skill/5); 
          target->set_temp("syz/wugong",skill);   
		  target->apply_condition("no_exert",2);
          me->add("neili", -400);
          me->add("jingli",-150);

		  if (objectp(target))
		      call_out("check_fight",skill/50,me,target);                      
          //return 1;
        }
		else if (objectp(target)&&objectp(me)) 
		{
		        message_vision(HIC"$N慌乱中镇定心神，仔细看清了$n的抓影，顺势一搁一挡，破了这漫天抓影。\n"NOR,target,me);
				me->add_busy(1);
        }

		if (me->query_skill("sanyin-zhua",1)<450)
        {
			me->start_busy(1);
			me->start_perform(2,"「蜈蚣抓」");
        }
        me->add("neili", -100);
        me->add("jingli", -100);
        return 1;
}

void check_fight(object me, object target) 
{ 
       
	   int skill;
	   
       if (!objectp(target)) return;
	   skill=target->query_temp("syz/wugong");
       if(target->query_temp("syz/wugong") )
	   {

        target->add_temp("apply/attack", skill/5);
        target->add_temp("apply/dodge", skill/5);
        target->add_temp("apply/parry", skill/5);
        target->delete_temp("syz/wugong");
        tell_object(target, HIB"你奋力一挣，挣脱了三阴蜈蚣抓的负面影响，状态又恢复如常。\n"NOR);
       }
	   return;
}

string perform_name(){ return HIY"蜈蚣抓"NOR; }
int help(object me)
{
        write(HIB"\n三阴蜈蚣抓之「蜈蚣抓」："NOR"\n");
        write(@HELP
	三阴蜈蚣抓为星宿派绝技，源自模仿蜈蚣的形态而创
	一招既出，不断演化，一分二，二为四，四成八，渐
	渐成为蜈蚣千手千脚的形态。蜈蚣抓的要诀就是快，
	以快速的招式压制对方，使对方的防御受到压制，另
	外因为三阴抓武功是由毒相伴相城，若对方毒计水准
	比较低，则会中了臭名昭著的星宿毒。
	注意：「蜈蚣抓」绝技最大的功效是降低对方的攻防。

	指令：perform claw.wugong

要求：  
	最大内力的需求 3500 以上；      
	当前内力的需求 1500  以上；  
	三阴蜈蚣抓等级 350 以上；
	化功大法的等级 350 以上；
	激发抓法为三阴蜈蚣抓；
	激发招架为三阴蜈蚣抓；
	且手无兵器,450后飞跃；
	若和抽髓掌互备有特殊功效。
                
HELP
        );
        return 1;
}

