// lingshe.c 灵蛇拳法之「灵蛇劲」
// Modified by fengyue@SJ

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

string perform_name(){ return HIR"灵蛇劲"NOR; }

int perform(object me, object target)
{
	int damage, p;
	object weapon;
	string msg;
        
        if( !target ) target = offensive_target(me);

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「灵蛇劲」只能对战斗中的对手使用。\n");



	if( userp(me)&&( me->query_skill_mapped("force") != "hamagong"
        && me->query_skill_mapped("cuff") != "lingshe-quanfa") )
                return notify_fail("「灵蛇劲」必须用灵蛇拳法配合蛤蟆功才能使用。\n");

        if( me->query_skill_prepared("cuff") != "lingshe-quanfa")
                return notify_fail("你的拳法不对，根本不能用出「灵蛇劲」。\n");  

        if( me->query_skill("lingshe-quanfa", 1) < 150 )
                return notify_fail("你的拳法修为还不够！\n");

        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("你的真气不够，发挥不了威力！\n");                   
        if( me->query_temp("weapon"))
                return notify_fail("你先放下手中的武器再说吧？！\n");     

     msg = MAG"\n蛇身虽有骨而似无骨，能四面八方，任意所之，$N招式一变，使出了灵蛇拳法不传之秘"HIR"「灵蛇劲」"MAG"！\n"NOR;

	damage = me->query_skill("cuff") + me->query_skill("lingshe-quanfa") + me->query_skill("hamagong");
	damage += random(me->query("jiali") * 3);
	damage *= 2;
    
   if(target->query("neili") < me->query("neili")) damage *= 3;
   
   if (!userp(me)&& damage > 2000 && me->query("oyf/hmg")<3 ) damage = 2000+random(500); 
   

     target->receive_damage("qi", damage, me);
     target->receive_wound("qi", damage/2, me);
	p = (int)target->query("qi")*100/(int)target->query("max_qi");

	msg += HIR"$n左手挥出挡格，只道已将来拳架开，哪知便在最近之处，忽有一拳从万难料想的方位打来，结果重重的打在$n的胸口！\n"NOR;
	msg += "( $n"+eff_status_msg(p)+" )\n"; 
        message_vision(msg, me, target);

   if(userp(me) && me->query("env/damage"))             tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点伤害。\n"NOR);  
   if(userp(target)&& target->query("env/damage"))      tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR);   

   if(userp(me)) target->start_busy(2+random(2));
   

	me->set_temp("lsqf/ls",1);
   if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, 3);
   if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, 3);
   if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, 3);
    me->delete_temp("lsqf/ls",1);
	
	if (me->query_temp("hmg_nizhuan")&&me->query_temp("lsqf/wugu"))
	{
		
		if (random(10)>6 && me->is_fighting(target)&&objectp(weapon=target->query_temp("weapon"))){
		   message_vision(HIC"$N这“灵蛇拳”去势极快，倏忽之间已打到$n肩上，猛地想起灵蛇无骨要诀，拳势忽转，顺手将$n手中的兵器夺了下来。\n"NOR,me,target);
           weapon->move(environment(target));		   
		}
		message_vision(HIR"$n防不胜防，接连吃了$N三拳，这三下都是十分诡异难挡，$n登时心下慌乱，不知如何应付!\n"NOR,me,target);

		COMBAT_D->do_attack(me, target, 0, 3);
		COMBAT_D->do_attack(me, target, 0, 3);
	}
	me->add("neili", -350);
	me->add("jingli", -150);
	me->start_busy(random(1));
	me->start_perform(4,"灵蛇劲");
	return 1;
}

int help(object me)
{
   write(HIB"\n灵蛇拳法之「"HIR"灵蛇劲"HIB"」："NOR"\n");
   write(@HELP
	为西毒欧阳锋之绝学，乃是他在第一次华山论剑落败后，为
	在下回论剑时出奇制胜，参考毒蛇动作而创出的拳技。施展
	时自身手臂灵动如蛇，宛若无骨；要旨在于手臂似乎能于无
	法弯曲处弯曲，使敌人以为已将自身来拳架开，使出拳的方
	位显得匪夷所思，自身却又在离敌最近之处突然变换方向攻
	击敌人，使敌人大感窘迫而失了先机。
	灵蛇劲是灵蛇拳法的攻击性招式，一招击出，遇敌后劲力迸
	发，蛤蟆功的威力立即着体，令对方收到极大伤害。

	指令：perform cuff.lingshe

要求：
	当前内力 1000 以上；
	当前精力 1000 以上；
	灵蛇拳法 450 以上；
	基本拳法 450 以上；
	基本内功 450 以上；
	蛤蟆功   450 以上；
	激发拳法为灵蛇拳法；
	激发招架为灵蛇拳法
	空手不能持有武器；

HELP
   );
   return 1;
}
