// wofo.c yizhi-chan perform 皈依我佛
// By Spiderii 效果修改
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

void remove_effect(object me);

int perform(object me, object target)
{
	string msg;
	int busy ;
      if( !target ) target = offensive_target(me);
     
      if( !objectp(target) || !me->is_fighting(target) )
	  return notify_fail("「皈依我佛」只能在战斗中对对手使用。\n");
	     
      if( objectp(me->query_temp("weapon")) )
	  return notify_fail("你必须空手使用「皈依我佛」！\n");
      
      if( (int)me->query_skill("yizhi-chan",1) < 250 )
	  return notify_fail("你的一指禅不够娴熟，不会使用「皈依我佛」！\n");

      if( (int)me->query_skill("yijin-jing",1) < 250 )
	  return notify_fail("你的易筋经内功等级不够，不能使用「皈依我佛」！\n");  
      
      if( (int)me->query_str() < 25 )
	  return notify_fail("你的臂力不够强，不能使用「皈依我佛」！\n");
      
      if( (int)me->query("max_neili") < 2000 )
	  return notify_fail("你的内力太弱，不能使用「皈依我佛」！\n");
      
      if( (int)me->query("neili") < 500 )
	  return notify_fail("你的内力太少了，无法使用出「皈依我佛」！\n");   
										 
      if (me->query_skill_prepared("finger") != "yizhi-chan"
       || me->query_skill_mapped("finger") != "yizhi-chan")
		return notify_fail("你现在无法使用「皈依我佛」进行攻击。\n");										 
      if( me->query_temp("wofo"))
		return notify_fail("你正在使用一指禅的特殊攻击「皈依我佛」！\n");
	  if( target->is_busy())
		return notify_fail("对方已经手忙脚乱了,你无法使用「皈依我佛」！\n");

	  if (target->is_busy()) return notify_fail("对方正自顾不暇，放胆攻击吧！\n");
       
    
      message_vision(HIY"$N突然身行纵向半空，右手屈指弹出，嗤的一声，一股劲气激射而出，罩向$n周身大穴。\n" NOR, me, target);   
      busy=3+random(me->query_skill("yizhi-chan",1))/100;
      if(busy>8)
      busy=8;
      if( wizardp(me)) tell_object(me,sprintf("busy=%d\n",busy));
     
	  if( random(me->query("combat_exp"))  > target->query("combat_exp")/2
		  ||random(me->query_skill("finger",1))>target->query_skill("parry",1)/3)
	  {
  	
       
		message_vision(HIW"\n$n只感到穴道一麻，浑身劲气立散，动弹不得。\n"NOR, me, target); 
		me->set_temp("wofo",1);  
		me->add("neili", -350);    
		target->start_busy(busy);    
					
		//call_out("remove_effect", me->query_skill("yizhi-chan") / 20 + 2, me);
      }
      else {
		msg = HIY"$n看出$N的企图，一闪身，敏捷地躲过了$N的这一招！\n"NOR;	  
		message_vision(msg, me, target);					
		me->start_busy(1+random(2));
		me->add("neili", - 100);
      }
	  if (me->query_skill("yizhi-chan",1)<350 ||!me->query("quest/sl/yzc/pass"))
	  {
		me->start_perform(2,"皈依我佛");
		//me->start_busy(random(2));
	  }
	   me->delete_temp("wofo");
      return 1;
}

/*
void remove_effect(object me)
{
	if (!me) return;
	me->delete_temp("wofo");
       
	message_vision(HIR"$N的「皈依我佛」运功完毕，脸色好看多了。\n"NOR, me);
}*/
string perform_name(){ return HIY"皈依我佛"NOR; }

int help(object me)
{
        write(HIB"\n一指禅之「皈依我佛」："NOR"\n");
        write(@HELP
	少林内劲一指禅功为少林七十二艺之一，乃众多少林先辈心血的结晶
	其功法特点是：将全身劲力集于一指，攻敌之身达到“打其表面伤其内
	击中前心震后心”之目的。这一指乾坤蕴含大千世界，万法归一的意境
	当功力达到高深境界时，内力劲气，可将对手全身穴道笼罩，一旦被点
	中会随机让对方封招、闭气功效。一指禅功，全凭易筋经深厚的功力支
	撑，功力越强，威力越大。为少林中后期的秘传武功。
	注意：倘若和互备武功配合，会有出人意料的攻击结果。若能机缘巧合
	得到玄澄大师的指点，则一指禅威力将再次提升。

	指令;perform finger.wofo

要求：  
	最大内力 2000 以上；      
  	当前内力 500  以上；  
	一指禅等级 250 以上；
	易筋经等级 250 以上；
	激发指法为一指禅；               
	且手无兵器,350后飞跃，极大缩短后续pfm时间。；
                               
HELP
        );
        return 1;
}