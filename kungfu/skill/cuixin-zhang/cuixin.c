inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

int perform(object me, object target)
{
	int damage, p,level,damage2;
	string msg;
        
	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("催心断肠只能对战斗中的对手使用。\n");

	//if( !target->is_busy())
	//	return notify_fail("催心断肠只能对忙乱中的对手使用。\n");

	if( me->query_temp("weapon"))
		return notify_fail("你拿着武器！\n");   

	if( (int)me->query_skill("cuixin-zhang",1) < 180 )
		return notify_fail("你的掌法修为不足，使不出催心断肠。\n");

	if( (int)me->query("neili") < 800 )
		return notify_fail("你现在内力太弱，不能打出催心断肠。\n");

	if( (int)me->query("jiali") < 100 )
		return notify_fail("你现在加力太弱，不能打出催心断肠。\n");

	if (me->query_skill_prepared("strike") != "cuixin-zhang")
			return notify_fail("你现在无法使用催心断肠！\n");
            
	msg = HIR"\n$N趁着$n手忙脚乱之时，使出“催心断肠”！\n"NOR;
	
	damage=200;//没解开的伤害
	
	damage=(int)me->query_skill("cuixin-zhang",1)+me->query_skill("strike",1);	
	
	damage += random(me->query("jiali") * 3);
	
	if(me->query("quest/jiuyin2/cuixin/pass")) {
       message_vision(RED"\n$N忽然想起陈玄风所授秘诀，掌心顿时涌起一团红光。",me);		
	   damage *= 10;
	  if(target->query("neili") < me->query("neili")) damage *= 2;	
	}
   else
   {
	   damage *= 5;
   }
   
   if(random(me->query("combat_exp"))>target->query("combat_exp")/2
		||random(me->query_skill("cuixin-zhang",1))> target->query_skill("dodge",1)/2)
	{    
      damage2=COMBAT_D->do_chemis_attack(me,target,1,damage,"结果重重的打在$n的胸口，$n登时鲜血狂喷。");
  if (wizardp(me)) write("\n伤害为:"+damage2);	  
	//p = (int)target->query("qi")*100/(int)target->query("max_qi");
	//msg += "结果重重的打在$n的胸口，$n登时鲜血狂喷。\n";
	//msg += "( $n"+eff_status_msg(p)+" )\n"; 
   //     message_vision(msg, me, target);
	}
	else
	{
		msg  =  msg + CYN"$n凭借灵巧的身法躲开了这一招。\n"NOR;
		message_vision(msg, me, target);
		me->start_busy(1+random(2));
	}
   
	me->add("neili", -350);
	//me->add("jingli", -150);
	me->start_busy(random(2)+1);
	me->start_perform(2,"催心断肠");
	return 1;
}

string perform_name(){ return HIR"催心断肠"NOR; }

int help(object me)
{
        write(HIR"\n摧心掌之「催心断肠」："NOR"\n\n");
        write(@HELP
        要求：  当前内力 800 以上；
                最大内力 1500 以上；
                当前精力 1000 以上；
                摧心掌等级 180 以上；
                激发掌法为摧心掌；
                激发招架为摧心掌；
                备掌法为摧心掌；
                且手无兵器。
		若得陈玄风口授秘诀，则催心掌威力全开。

HELP
        );
        return 1;
}
