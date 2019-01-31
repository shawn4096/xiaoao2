//By KinGSo@舞林 2006年5月
inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>
string perform_name(){ return HIG"绵掌"NOR; }
int perform(object me, object target)
{
        int damage, p;
        int ns;
        string msg;
        
        if( !target ) target = offensive_target(me);

        
        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「绵掌」只能对战斗中的对手使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器！\n");   
        if( (int)me->query_skill("huagu-mianzhang",1) < 300 )
                return notify_fail("你的化骨绵掌掌法修为不足，使不出绵掌。\n");
		if( (int)me->query_skill("strike",1) < 300 )
                return notify_fail("你的基本掌法修为不足，使不出绵掌。\n");
        if( (int)me->query("neili") < 1500 )
                return notify_fail("你现在内力太弱，不能打出绵掌。\n");
        if( (int)me->query("max_neili") < 3000 )
                return notify_fail("你现在内力太弱，不能打出绵掌。\n");
		if( (int)me->query_skill("poison", 1) < 145 )
                return notify_fail("你的毒计功力不足，不能化骨。\n");
		if( (int)me->query_skill("shenlong-yaoli", 1) < 145 )
                return notify_fail("你的神龙药理功力不足，不能化骨。\n");
        if( (int)me->query("jiali") < 100 )
                return notify_fail("你现在加力不足，怎么使用绵掌暗劲。\n");
        if( me->query_skill_mapped("force")!="dulong-dafa" )
                return notify_fail("你激发的内功不符，怎么使用绵掌暗劲。\n");
		if (me->query_skill_prepared("strike") != "huagu-mianzhang"
			|| me->query_skill_mapped("parry") != "huagu-mianzhang"
            || me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("你现在无法使用绵掌！\n");                
       if(me->query("gender")=="女性") 
        	return notify_fail("你不是男人，尚不能使用化骨诀。\n");
        msg = HBGRN+HIW "$N面带诡异的笑容,一掌轻飘飘的向$n拍了过去！\n"NOR;
        if (random(me->query_skill("strike",1)) > target->query_skill("parry",1)/2
        || me->query("combat_exp") > random(target->query("combat_exp")/3))
           {
                msg +=HIR "结果只听扑的一声，$n被一掌拍中！\n"NOR;

				target->add_busy(1);
                ns = (int)me->query_skill("huagu-mianzhang",1) /20;
                damage = (int)me->query_skill("huagu-mianzhang",1)+(int)me->query_skill("dulong-dafa",1)+(int)me->query_skill("poison",1)+(int)me->query_skill("shenlong-yaoli",1);
                damage += random(me->query("jiali") * me->query_str());
                damage *= 3;
                if(target->query("neili") < me->query("neili")) damage *= 2;
                if (damage>7000) damage=7000+random(1000);  
                
				target->add_condition("neishang", ns + random(ns));
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
				if (!random(2))
					target->add_condition("huagu_poison",1);

                me->add("neili", -damage/2);
                if (me->query("neili") < 0)
                      me->set("neili",0);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += HIG"打在$n的胸口，甚是轻柔,$n见得这掌如此阴柔,心中甚是不解。\n"NOR;
                msg += "( $n"+eff_status_msg(p)+" )\n"; 
          
        }
		else {
                me->start_busy(2);
                msg += HIG"$n见这招平淡无其，随意一让，$N这一掌便即落空。\n"NOR;
        }

        message_vision(msg, me, target);
		me->add("jingli",-random(200));
		me->add("neili",-random(300));
		me->add_busy(2);
		me->start_perform(4,"绵掌");
        return 1;
}

int help(object me)
{
   write(HIG"\n化骨绵掌「"HIG"绵掌"NOR"」："NOR"\n");
   write(@HELP
	化骨绵掌是蛇岛独门武技，是一种极为难练的阴毒功夫，
	被化骨绵掌击中的人开始浑如不觉，但两个时辰后掌力
	发作，全身骨骼会其软如绵，处处寸断，脏腑破裂，惨
	不堪言，再无救治。
	化骨绵掌中「绵掌」绝技主要以阴柔之内劲伤敌，并附
	加内伤效果，并有概率被化骨毒所伤。	
   
	指令：perform strike.mianzhan

要求：
	最大内力要求 3000 以上；
	当前内力要求 1500 以上；
	化骨绵掌等级 300 以上；
	伤敌加力要求 100 以上。
	神龙药理要求 145 以上；
	毒计等级要求 145 以上；
	激发掌法为化骨绵掌；
	且备掌法为化骨绵掌；	
	激发招架为化骨绵掌；
	激发内功为毒龙大法；
	男性玩家使用；

HELP
   );
   return 1;
}

