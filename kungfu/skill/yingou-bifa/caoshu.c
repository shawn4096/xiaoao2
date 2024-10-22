//caoshu.c 草书
//edit by sohu,
#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

string perform_name(){ return HIM"草 书"NOR; }
int perform(object me, object target)
{
      string msg; 
      int i,damage,p,drk;
	  
      object weapon = me->query_temp("weapon");
	  drk=me->query_conditions("drunk");
      if (!weapon || weapon->query("skill_type") != "brush")
         return notify_fail("你手里没有笔，无法写出草书！\n");

      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
         return notify_fail("草书只能在战斗中对对手使用。\n");
             
      if( (int)me->query_skill("yingou-bifa",1) < 300 )
         return notify_fail("你的银钩笔法还不够娴熟，不会写草书！\n");
      
      if( (int)me->query_skill("literate",1) < 220 )
         return notify_fail("你的读书写字等级不够，不能写出草书！\n");  
      if( (int)me->query_int() <45 )
         return notify_fail("你的悟性不够，不能写出草书！\n");  
      if( (int)me->query_skill("qiantian-yiyang",1) < 300 )
         return notify_fail("你的乾天一阳功力等级不够，不能写出草书！\n");  

      if( (int)me->query("max_neili") < 3500 )
         return notify_fail("你的最大内力太弱，写不出龙飞凤舞的草书! \n");
      
      if( (int)me->query("neili") < 1500 )
         return notify_fail("你的当前内力太少了，写出的草书无此意念！\n"); 
      
      if (me->query_skill_mapped("brush") != "yingou-bifa"
       || me->query_skill_mapped("parry") != "yingou-bifa")
         return notify_fail("你现在无法写出「草书」！\n");

      i = me->query_skill("yingou-bifa",1)/3 + me->query_skill("brush",1) /3 + me->query_skill("literate")/2+drk;
      i = i /4;
      
	  msg = HIM"$N长袖飞舞，狂奔疾走，出招全然不依章法。只见其如疯如癫、如酒醉、如中邪，\n"+
               "笔意淋漓，笔走龙蛇！原来$N这时所书，正是唐代张旭的「自言帖」。张旭号称\n"+
				"「草圣」，乃草书之圣。\n" NOR;
	  message_vision(msg,me,target);
	  msg="\n";
      me->add("neili", - 250);
      me->add("jingli", -80);

	  me->add_temp("apply/strength", i /10);

	  me->add_temp("apply/brush",  i);
	  me->add_temp("apply/attack", i/2);
	  me->add_temp("apply/damage", i/3);

	  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  

      if (me->is_fighting(target))
	      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  

	  if (me->is_fighting(target))
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
	  if (me->is_fighting(target))
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
	  me->add_temp("apply/strength", -i/10);
	  
me->add_temp("apply/attack", -i/2);
	  me->add_temp("apply/brush", -i);
	  me->add_temp("apply/damage", -i/3);

      if( (random(me->query_skill("literate", 1)) > target->query_skill("literate", 1)/2
           || random(me->query_skill("force",1)) > target->query_skill("force",1)/2)
           && me->is_fighting(target)
           && present(target,environment(me))){
          if (!userp(target))
          {
			  target->add_busy(4);
          }
          else target->add_busy(2);             
          damage = (int)me->query_skill("yingou-bifa", 1);               
          damage = damage/2 + random(damage);
          damage = damage * i * 2 / 3;
	  if (damage > 5000 ) damage = 5000;
          target->receive_damage("qi", damage,me);
          target->receive_wound("qi", damage/3,me);  
	  msg += HIB"突然$N笔锋锋芒暴增，写到「担夫争道」的那个「道」字，最后一笔钩将上来，直划\n"+
                    "上了$n身上，顿时鲜血直流，$n踉跄後退了好几步。\n"NOR;
      p = (int)target->query("qi")*100/(int)target->query("max_qi");
      msg += "( $n"+eff_status_msg(p)+" )\n";
	  if(userp(me) && me->query("env/damage"))
		  tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR); 

	  if(userp(target)&& target->query("env/damage")) 
		  tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR); 
	  }
      else {
          me->start_busy(1);
          msg += HIG"$p当下发声长啸，右扇左袖，鼓起一阵疾风，急向$P扑去，劲风力道凌厉，令人不由\n"+
                    "自主地渐渐退後，只听$p口中不住有似霹雳般吆喝助威，$P奋袂低昂，高视阔步，和\n"+
                    "$p斗了个旗鼓相当。\n"NOR;
          if (!(target->query("neili")< 200)) 
			  target->add("neili",- 100);
       }
       message_vision(msg, me, target);
	   
	   
       
	   me->start_perform(4,"「草书」");

	   return 1;
}



int help(object me)
{
	write(HIM"\n银钩笔法之「草书」绝技："NOR"\n");
	write(@HELP
	银钩笔法乃是一灯大师大弟子朱子柳的独门武技，因其状元出身
	且悟性高，所以拜师一灯大师后，武技突飞猛进，成为四大弟子
	中武功最高者。这门功夫厉害之处在于将一阳指和书法融合在一
	起，招式中夹杂着点穴，令人防不胜防。
	后来在大胜关与霍都一战，采用「草书」绝技，以普通毛笔对战
	霍都用楷书方式施展出张旭「自言贴」，名扬天下。张旭的书法
	之意往往在于酒醉状态，所以适当的饮酒招式威力更大。
	
指令：perform brush.caoshu

要求：	
	最大内力 3500 以上；		
	当前内力 1000 以上；
	银钩笔法等级 300 以上；
	乾天一阳等级 300 以上；
	有效悟性 45 以上；
	读书写字等级 220 以上；
	激发笔法为银钩笔法
	激发招架为银钩笔法；
	手持笔类武器。
HELP
	);
	return 1;
}