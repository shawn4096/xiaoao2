// tantui.c 弹腿
// by sohu@xojh

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
int perform(object me, object target)
{

	int i,damage,p;
	string msg;
	if( !target ) target = offensive_target(me);

     if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
		return notify_fail("「弹腿」只能在战斗中对对手使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("使用「弹腿」时双手必须空着！\n");

	if( (int)me->query_skill("shaolin-tantui", 1) < 100 )
		return notify_fail("你的弹腿腿不够娴熟，不会使用「弹腿」。\n");

	if( (int)me->query_skill("yijin-jing", 1) < 100 )
		return notify_fail("你的易筋经等级不够，不能使用「弹腿」。\n");

	if (me->query_skill_mapped("force") != "yijin-jing")
		return notify_fail("你目前的内功无法支持你使用「弹腿」进行攻击。\n");  
	if (me->query_skill("leg",1)<100)
		return notify_fail("你目前的基本腿法不足100，不支持你使用「弹腿」进行攻击。\n");  
		
	if( (int)me->query_dex() < 30 )
		return notify_fail("你的身法不够30，不能使用「弹腿」。\n");

	if (me->query_skill_prepared("leg") != "shaolin-tantui"
	|| me->query_skill_mapped("leg") != "shaolin-tantui")
		return notify_fail("你现在无法使用「弹腿」进行攻击。\n");  
											       
	if( (int)me->query("max_neili") < 1400 )
		return notify_fail("你现在最大内力太弱，不能使用「弹腿」。\n");
	if( (int)me->query("neili") < 500 )
		return notify_fail("你目前内力太少，不能使用「弹腿」。\n");

	if( (int)me->query("jingli") < 500 )
		return notify_fail("你现在精力太少，不能使用「弹腿」。\n");


	message_vision(HIC"\n$N轻轻跃起，躲开$n的攻击，趁$n不备，将蓄积的腿劲一股脑迸发，向$n踢出！\n" NOR,me, target);
	
		
	me->set_temp("sltt/tantui", 1);
	me->add("neili", -180);
	if(random(me->query_dex()) > target->query_dex()/2
	  ||random(me->query_skill("leg",1))>target->query_skill("dodge",1)/2)
	{
           damage = me->query_skill("leg",1)+me->query_skill("shaolin-tantui",1)+me->query_skill("dodge",1);
		   damage=damage*me->query_dex()/5;
           damage =3*damage;
		   damage += random(damage);
           
           
		   if (wizardp(me))
           {
			   message_vision("damage="+damage+"\n",me);
           }
		   
		   if (damage>3500) damage=3500+random(100);
		   if (userp(target)&& damage > 2500) damage = 2500;

		   if(damage > 2000)
              message_vision(HIR"\n突然之间，$n胸口一痛，$N这一脚正好踹在自己的胸口，一阵气血翻腾！\n\n"NOR,me,target);            
           
		   target->receive_damage("qi", damage, me);
		   target->apply_condition("neishang",3+random(2));
           target->receive_wound("qi", damage/4, me);
           
           
		 //  limbs = target->query("limbs");
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           tell_room(environment(target), HIR + target->name()+"忽感全身像被压了一块大石一样，一阵一阵眩晕憋气！\n" NOR, ({ target }));  
           msg = damage_msg(damage, "内伤");
            msg += "( $n"+eff_status_msg(p)+" )\n";
          
		   message_vision(msg, me, target);
           
		   if(userp(me) && me->query("env/damage"))
	          tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR);
           
			if(userp(target)&& target->query("env/damage"))
	         tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR);
           me->start_busy(1);
           me->add("jingli", -20);
           		   
        }        
        else {
           me->add("neili", -50);
           me->add("jingli", -50);
           tell_object(me, HIY"可是"+target->query("name")+"看破了你的企图，斜跃避开了攻击。\n"NOR);

		   me->start_busy(2);         
        }
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);

		message_vision(HIC "\n$N这一腿踢完，空中借势回旋，轻飘飘落在地上。\n" NOR,me);

		me->delete_temp("sltt/tantui");
		me->add_busy(1);           

		me->start_perform(3,"「弹腿」");

		return 1;
}


string perform_name(){ return RED"弹腿"NOR; }
int help(object me)
{
        write(HIC"\n少林弹腿之「弹腿」绝技："NOR"\n");
        write(@HELP
	少林弹腿为少林入门腿法，利用坚实的腿功和强大的内力，身
	子纵起空中，趁对方不备向对方踢出一脚绝命杀招，令对手防
	不胜防，躲无可躲，端的是厉害非常。
		
	注意：「少林弹腿」是腿法基本功，乃后期如影随形腿的必修
		功夫。少林弹腿命中依靠身法和腿法，切记！

	指令：perform leg.tantui

要求：  
	最大内力需求 1400 以上；      
	当前内力需求 500  以上
	当前精力需求 500  以上；  
	少林弹退等级 100 以上；
	易筋经功等级 100 以上；
	基本腿法等级 100 以上；	
	激发腿法为少林弹腿；
	激发招架为少林弹腿；
	且手无兵器；
	有效身法不得小于30。
                
HELP
        );
        return 1;
}
