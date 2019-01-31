#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
	   int skill,tg_skill,time;
	   string msg;
	   if( !target ) target = offensive_target(me);
	   if( !target || !target->is_character() || !me->is_fighting(target) )
		  return notify_fail("「金蛇游身」只能对战斗中的对手使用。\n");
	   if( (int)me->query_skill("wudu-yanluobu", 1) < 450 )
		  return notify_fail("你的五毒烟萝步火候不够，不能使出「金蛇游身」。\n");
	   if( (int)me->query_skill("dodge", 1) < 450 )
		  return notify_fail("你的基本轻功火候不够，不能使出「金蛇游身」。\n");
	   if( (int)me->query_skill("force", 1) < 450 )
		  return notify_fail("你的基本内功火候不够，不能使出「金蛇游身」。\n");
	   if( (int)me->query("neili", 1) < 1500 )
		  return notify_fail("你现在内力太弱，不能使用「金蛇游身」。\n");
	   if( target->is_busy() )
		  return notify_fail(target->name() + "目前正手忙脚乱，你还乱转什么，赶快进攻吧！\n");
	   msg = HIC "$N身行忽的一变，使出「金蛇游身」的绝技，身法越来越快。只见$N飞快的绕场游走，瞻之在前，望之在后，一时间到处都是$N的身影。\n"NOR;
	   message_vision(msg, me, target);
	   time = (int)me->query_skill("wudu-yanluobu",1)/50;
	   if (!userp(target)) 
		   skill = (int)me->query_skill("wudu-yanluobu",1) + (int)me->query_skill("dodge",1);
	   else skill=(int)me->query_skill("wudu-yanluobu",1);

	   tg_skill = (int)target->query_skill("dodge",1);
	   me->add("neili", -100);
	   if (random(skill) > tg_skill/2
		   ||random(me->query_int(1))>target->query_int(1)/2
		   || random(me->query("combat_exp"))>target->query("combat_exp")/2)
		{
		  target->add_busy(random(time)+1);
		  msg = HIR"$n不由得一阵手足无措，被$N连攻数招！\n"NOR;
		  message_vision(msg, me, target);
		  //虚弱对方
		  if (!target->query("wdylb/snake"))
		  {
			  message_vision(HBBLU+HIW"$N身形如蛇，灵动异常，$n"HBBLU+HIW"顿觉自己宛如深陷泥潭，状态极差！\n"NOR,me,target);
			  target->add_temp("apply/dodge",skill/3);
			  target->add_temp("apply/parry",skill/3);
			  target->set_temp("wdylb/snake",skill);
			  call_out("ylb_attack",1,target,time);
		  }
		  return 1;
		}
		else
		   {
			me->start_busy(2+random(2));
			msg = HIR"可是$n以静制动，紧守门户，丝毫不受$N的影响,$N自己倒累的满头大汗！\n"NOR;
			message_vision(msg, me, target);
		 }
		 return 1;
}
int ylb_attack(object target,int count)
{
	int skill;
	if (!target) return 0;
	if (!target->query_temp("wdylb/snake")) return 0;
	skill=target->query_temp("wdylb/snake");
	target->add_temp("apply/dodge",-skill/3);
	target->add_temp("apply/parry",-skill/3);
	target->delete_temp("wdylb/snake");
	tell_object(target,YEL"你精神一震，终于摆脱了这金蛇游身的虚弱影响!\N"NOR);
	return 1;
}
string perform_name(){ return HIC"金蛇游身"NOR; }
int help(object me)
{
        write(HIY"\n五毒步法之「金蛇游身」:"NOR"\n\n");
        write(@HELP
	五毒教长老级人物才可修习的秘技，当年金蛇郎君夏雪宜
	自何红药处习得，后成为其独步武林的绝技之一，传说中
	对于经验和武技要求以及悟性要求很高。

	指令：perform dodge.snake

要求：
	基本内功要求 450 级以上
	五毒阎罗步法 450 级
	基本轻功要求 450 级
	当前内功要求 1500 以上；


HELP
);
return 1;
}
