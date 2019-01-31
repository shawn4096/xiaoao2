//shigu.c 一阳书指
#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

string perform_name(){ return HIR"一阳书指"NOR; }

int perform(object me, object target)
{
      string msg; 
      int i, damage,p;                                  
      object weapon = me->query_temp("weapon");

      if (!weapon || weapon->query("skill_type") != "brush")
         return notify_fail("你手里没有笔，无法写出一阳书指！\n");

      if( !target ) target = offensive_target(me);
       
      if( !target || !me->is_fighting(target) )
         return notify_fail("一阳书指只能在战斗中对对手使用。\n");
      if (!me->query("quest/tls/yiyangshu/pass"))
         return notify_fail("你只是听说过一阳书指绝技，但却不会使用。\n");
   
      if((int)me->query_skill("yingou-bifa",1) < 400 )
         return notify_fail("你的银钩笔法还不够娴熟，不会写一阳书指！\n");
       if(me->query_int() < 50 )
         return notify_fail("你的后天悟性不够50，不会写一阳书指！\n");
      
      if((int)me->query_skill("literate",1) < 300 )
         return notify_fail("你的读书写字等级不够，不能写出一阳书指！\n");  
	  if(me->query("family/family_name") !="天龙寺" )
	//	  || me->query("family/master_name")!="一灯大师"
         return notify_fail("你不是天龙寺弟子，无法写出一阳书指！\n");  
	   if(me->query_skill_mapped("force")!="qiantian-yiyang" )
         return notify_fail("你的内功需激发乾天一阳，否则不能写出一阳书指！\n");  
      //if((int)me->query_skill("yiyang-zhi",1) < 400 )
         //return notify_fail("你的一阳指等级不够，不能写出一阳书指！\n");
      if((int)me->query_skill("qiantian-yiyang",1) < 400 )
         return notify_fail("你的乾天一阳等级不够，不能写出一阳书指！\n");
      if (me->query_skill_mapped("force")!="qiantian-yiyang")
		  if(me->query_skill_mapped("force")!="kurong-changong")
         return notify_fail("你激发的内功不是乾天一阳或枯荣禅功，不能写出一阳书指！\n");

      if((int)me->query("max_neili") < 5000 )
         return notify_fail("你的内力太弱，无法写出强劲有力的一阳书指! \n");
      
      if((int)me->query("neili") < 800 )
         return notify_fail("你的内力太少了，写出的一阳书指无刚阳之气！\n");       

      if((int)me->query("jingli") < 500 )
         return notify_fail("你的精力太少了，写出的一阳书指无刚阳之气！\n");       
         
      if(me->query_skill_mapped("brush") != "yingou-bifa"
       || me->query_skill_mapped("parry") != "yingou-bifa")
         return notify_fail("你现在无法写出「一阳书指」！\n");
	  if (me->query_temp("ygbf/yiyang"))
	     return notify_fail("你现在正在施展「一阳书指」！\n");


      i = me->query_skill("yingou-bifa",1)+me->query_skill("qiantian-yiyang",1)+me->query_skill("yiyang-zhi",1)+me->query_skill("literate",1);
      i=i/4;                                                                                 
      me->set_temp("ygbf/yiyang",i);
      msg = HBYEL+HIR"$N运起乾天一阳功，将一阳指法融入到银钩笔法的招式中，内力嗤嗤作响，威力陡增！\n" NOR;
      me->add("neili", - random(500));
      me->add("jingli", -100);
    
      message_vision(msg, me, target);
	  me->add_temp("apply/brush",i/3);
	  me->add_temp("apply/attack",i/3);
	  me->add_temp("apply/damage",i/6);
      //me->start_perform(6,"「一阳书指」");
      call_out("effect_check",2,me,target,i);
	  return 1;
}

void effect_check (object me, object target, int count)
{
        int i;
		if (!me) return;
	
	    i=me->query_temp("ygbf/yiyang");
		
		if (objectp(me) && me->query_temp("ygbf/yiyang"))
		{
           if (count-- > 0 && me->is_fighting(target))
		   {
               call_out("effect_check", 2, me, target, count);
               return;
           }
		}         
            
		tell_object(me,HIY"长吁一口气，将蓄积的一阳功力缓缓释放。\n"NOR);
        me->add_temp("apply/brush",-i/3);
		me->add_temp("apply/attack",-i/3);
		me->add_temp("apply/damage",-i/6);
        me->delete_temp("ygbf/yiyang");
        
		return;   
}
int help(object me)
{
	write(HIR"\n银钩笔法之「一阳书指」绝技："NOR"\n");
	write(@HELP
	银钩笔法乃是一灯大师大弟子朱子柳的独门武技，因其状元出身
	且悟性高，所以拜师一灯大师后，武技突飞猛进，成为四大弟子
	中武功最高者。这门功夫厉害之处在于将一阳指和书法融合在一
	起，招式中夹杂着点穴，令人防不胜防。
	后来在大胜关与霍都一战，采用一阳书指绝技，以普通毛笔对战
	霍都，用一阳指力方式施展出「书法绝技」，由此名扬天下。
	
	指令：perform brush.yiyangshu

要求：	
	最大内力 5000 以上；		
	当前内力 800 以上；
	当前精力 500  以上；
	银钩笔法 400 以上；
	有效悟性 50 以上；
	读书写字 300 以上；
	激发笔法为银钩笔法
	激发招架为银钩笔法；
	激发内功乾天一阳功；
	手持笔类武器。
	
HELP
	);
	return 1;
}

