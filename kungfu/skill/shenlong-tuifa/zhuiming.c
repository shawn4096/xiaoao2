//追魂夺命 
//by sjxa@winnerlife
//2014-08-07

#include <ansi.h>
#include <combat.h>

 inherit F_SSERVER;

 string perform_name() {return HIC"追魂夺命"NOR;}

 int calc_damage(int,int,object,object);

 int perform(object me, object target)
 {
	 //对象定义
        object weapon;
        string msg,result;
        int i,total; 
	//使用条件判断
		if( !target ) target = offensive_target(me);

		if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
                 return notify_fail("【追魂夺命】只能对战斗中的对手使用。\n");

		if (me->query_skill_prepared("leg") != "shenlong-tuifa"
            || me->query_skill_mapped("leg") != "shenlong-tuifa"
			|| me->query_skill_mapped("parry") != "shenlong-tuifa" )
                return notify_fail("你现在无法使用【追魂夺命】进行攻击。\n");  

         if((int)me->query_skill("shenlong-tuifa", 1) < 100 )
                 return notify_fail("你的神龙腿法不够娴熟，不能使用【追魂夺命】。\n");

		 if((int)me->query_skill("leg", 1) < 100 )
                 return notify_fail("你的基本腿法不够娴熟，不能使用【追魂夺命】。\n");

         if((int)me->query_skill("dulong-dafa", 1) < 100 )
                 return notify_fail("你的毒龙大法不够深厚，不能使用【追魂夺命】。\n");

         if((int)me->query("max_neili") < 1000)
                 return notify_fail("你最大内力太弱，不能使用【追魂夺命】。\n");
		  if((int)me->query("max_neili") < 500)
                 return notify_fail("你当前内力太弱，不能使用【追魂夺命】。\n");


         if((int)me->query("jingli") < 500)
                 return notify_fail("你现在精力太弱，不能使用【追魂夺命】。\n");

         if( me->query_temp("weapon")) 
                 return notify_fail("你拿着兵器无法使用【追魂夺命】。\n");

        if (me->query_skill_mapped("parry") != "shenlong-tuifa")
                return notify_fail("你没有激发神龙腿法为招架！\n");

		if( me->query_skill_prepared("leg") != "shenlong-tuifa")
				return notify_fail("你没有激活腿法为当前武功招式！\n");

         if(me->query_skill_mapped("force") != "dulong-dafa")
                 return notify_fail("你现在所使用的内功同毒龙大法向抵触，不能使用【追魂夺命】。\n");
	//perform 主体

	//起式描述
	message_vision(HIY"$N双腿连环踢出，内劲陡然爆发，使出神龙岛绝学「"HIB"追魂夺命"HIY"」，瞬间向$n猛攻两招。\n\n"NOR,me,target);
	// 第1hit
	
	message_vision(HIG"$N凌空朝$n的胸口飞踹而至，正是神龙岛绝技「"HIY"千里追魂"HIG"」，刚猛的内劲让$n感觉劲风扑面避无可避。\n"NOR,me,target);
				i = calc_damage((int)me->query_skill("shenlong-tuifa",1),(int)me->query_skill("leg",1),me,target);
                if (i>2000) i=2000+random(1000);
              
				target->receive_damage("qi", i, me );
                //target->receive_wound("qi", i/3 , me);
                result = COMBAT_D->damage_msg(i,"瘀伤");
                msg = result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0); 
      if(userp(me) && me->query("env/damage"))             tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ i+ WHT"点攻击伤害。\n"NOR);    
      if(userp(target)&& target->query("env/damage"))      tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ i+ WHT"点伤害。\n"NOR); 
	//第2hit
	  if (me->query_skill("shenlong-tuifa",1)>160&&me->is_fighting())
	  {
	
			message_vision(HIB"$N陡然高高跃起，左足独立、右足横扫，此招正是追命腿真谛「"HIR"无形夺命"HIB"」,高速的旋转带起无数逼人锋芒的巨大气团！\n"NOR,me,target);
					i = calc_damage((int)me->query_skill("shenlong-tuifa",1),(int)me->query_skill("leg",1),me,target);
					if (i>2500) i=2500+random(1000);

					target->receive_damage("qi", i, me );
					target->receive_wound("qi", i/5 , me);
					result = COMBAT_D->damage_msg(i,"瘀伤");
					msg = result;
					message_vision(msg,me,target);
					COMBAT_D->report_status(target, 0); 
		  if(userp(me) && me->query("env/damage"))             tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ i+ WHT"点攻击伤害。\n"NOR);    
		  if(userp(target)&& target->query("env/damage"))      tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ i+ WHT"点伤害。\n"NOR); 
		 
      } 
	  //第三招描述
	  if (me->query_skill("shenlong-tuifa",1) >200 && me->is_fighting(target))
      {
		  message_vision(RED"$N在空中如瞬间一转身，身形变得柔软无比，宛如一条巨蟒,双脚连续踢出，使出「"HIC"蛇形腿"RED"」,连续两击踢出！\n"NOR,me,target);
		 		i = calc_damage((int)me->query_skill("shenlong-tuifa",1),(int)me->query_skill("leg",1),me,target);
                if (i>3000) i=3000+random(1000);

				target->receive_damage("qi", i, me );
                target->receive_wound("qi", i/4 , me);
                result = COMBAT_D->damage_msg(i,"瘀伤");
                msg = result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0); 
      }
	  
	  //收招描述
	  
	  message_vision(HIY"$N「"HIB"追魂夺命"HIY"」施展完毕，稳稳当当落在地上。\n"NOR,me,target);
	  me->add("neili",-random(200));
	  me->add("jingli",-random(100));
	  me->start_perform(3, "「追魂夺命」");
	  me->add_busy(3);
	return 1;
	
 }

//伤害计算函数
int calc_damage(int skill,int skill2,object me,object target)
{
        int i;

            i = ( (skill+skill2)*2 - (int)target->query_skill("parry",1) )*10;
            if (i<0) i = -i;
            i += random(i*2/5);
         if( i < (skill2*5)) i = (int)target->query("qi",1)/3;   

            if(userp(target)) i = i* 1 / 5;


      // return i*2 /5; 
		if (me->query("gender")=="男性") return i*2 /6; 
		else if (me->query("gender")=="女性") return i*1 /6; 
	    else return i*1 /10; 
}

//帮助
int help(object me)
{
   write(WHT"\n神龙腿法之「"HIC"追魂夺命"WHT"」："NOR"\n");
   write(@HELP
	神龙腿法为神龙岛初级入门技能，模仿神龙
	之态，凌空而起，连续蹬出几脚，令对手防
	不胜防。男性威力大，女性较弱，无性之人
	因阳气不足，威力更弱。
	
	指令：perform leg.zhuiming
	
要求：
	最大内力要求 1000 以上；
	当前内力要求 500 以上
	当前精力要求 500 以上；
	神龙腿法等级 100 以上；
	基本腿法等级 100 以上；
	毒龙大法等级 100 以上；
	需激发腿法神龙腿法；
	需备腿法为神龙腿法
	需激发内功为毒龙大法；
HELP
      );
   return 1;
   }
