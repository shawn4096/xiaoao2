//kaishu.c 楷书
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string perform_name(){ return HIC"楷书"NOR; }

int perform(object me, object target)
{
      string msg; 
      int i;                                  
      object weapon = me->query_temp("weapon");

      if (!weapon || weapon->query("skill_type") != "brush")
         return notify_fail("你手里没有笔，无法写出楷书！\n");

      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
         return notify_fail("楷书只能在战斗中对对手使用。\n");
             
      if((int)me->query_skill("yingou-bifa",1) < 200 )
         return notify_fail("你的银钩笔法还不够娴熟，不会写出楷书！\n");
      if((int)me->query_int() < 40 )
         return notify_fail("你的悟性不够，不能写出房玄龄碑文！\n");
	  
      if((int)me->query_skill("literate",1) < 200 )
         return notify_fail("你的读书写字等级不够，不能写出房玄龄碑文！\n");

      if((int)me->query_skill("qiantian-yiyang",1) < 200)
         return notify_fail("你的乾天一阳功等级不够，不能写出房玄龄碑文！\n");  
      
      if((int)me->query("max_neili") < 2000 )
         return notify_fail("你的内力太弱，写不出刚劲有力的楷书! \n");
      
      if((int)me->query("neili") < 500 )
         return notify_fail("你的内力太少了，写出的楷书柔弱无力！\n"); 

      //if( target->is_busy() )
         //return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

      if (me->query_skill_mapped("brush") != "yingou-bifa"
       || me->query_skill_mapped("parry") != "yingou-bifa")
         return notify_fail("你激发武技不对，现在无法写出「楷书」！\n");

      i = random((int)(me->query_skill("yingou-bifa",1)/50));
      //if(i < 3) i=3;
      if(i > 3) i=3;  
	  //if (userp(target)) i=1;
	
      msg = HIC"$N一转身，手中笔摇幌，凌空写起「房玄龄碑」碑文，书法之中有点穴，点穴之中有书法，\n"+
               "当真是银钩铁划，劲峭凌厉，而雄伟中又蕴有一股秀逸的书卷气，招招法度严谨，宛如楷书\n"+
               "般的一笔不苟！\n" NOR;
      me->add("neili", - 200);
      if(random(me->query_skill("literate", 1)) > target->query_skill("literate", 1)/2
       || random(me->query_skill("force",1)) > target->query_skill("force",1)/2){
            //me->start_busy(1);
            if (!userp(target)) target->add_busy(i);
            msg += HIR"$n对书法只是入门，哪懂得碑文的意境，只见$N手中的笔满天在自己身上各大要穴附近\n"+
                      "飞舞，只得勉力护住面门胸口要害，突感膝头一麻，原来已被$N倒转笔口，点中了穴道。\n"NOR;
			target->receive_damage("qi",random(3000),me);
					
			
      }
      else {
       
             msg += HIY"哪知$p曾临写过「房玄龄碑」，预计得到$P那一横之後会跟著写那一直，倒也守得井井有条，\n"+
                      "丝毫不见败象。\n"NOR;
             me->add_busy(1);
      }
      message_vision(msg, me, target);
      
	  if (me->is_fighting()&& objectp(target))
    	  call_out("kaishu_attack",1,me,target);
	    
	  me->start_perform(3,"「楷 书」");
      return 1;
}
int kaishu_attack(object me,object target)
{
      if (!me||!target) return 1;
    
	  message_vision(YEL"这一招楷书宛如「天女散花」，书法刚健婀娜，顾盼生姿，笔笔凌空，极尽仰扬控纵之妙，笔式一挑。\n"
							+"正好扎中$n的胸口,鲜血四溅。\n"NOR,me,target);
	  target->receive_wound("qi",2000+random(1000),me);	
	  me->add_temp("apply/damage",me->query_skill("yingou-bifa",1)/4);
		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		me->add_temp("apply/damage",-me->query_skill("yingou-bifa",1)/4);
		return 1;
}



int help(object me)
{
	write(HIC"\n银钩笔法之「楷书」绝技："NOR"\n");
	write(@HELP
	银钩笔法乃是一灯大师大弟子朱子柳的独门武技，因其状元出身
	且悟性高，所以拜师一灯大师后，武技突飞猛进，成为四大弟子
	中武功最高者。这门功夫厉害之处在于将一阳指和书法融合在一
	起，招式中夹杂着点穴，令人防不胜防。
	后来在大胜关与霍都一战，采用楷书绝技，以普通毛笔对战霍都
	用楷书方式施展出「房玄龄碑」，名扬天下。
	
指令：perform brush.kaishu

要求：	
	最大内力 2000 以上；		
	当前内力 500 以上；
	银钩笔法等级 200 以上；
	有效悟性 40 以上；
	读书写字等级 200 以上；
	激发笔法为银钩笔法
	激发招架为银钩笔法；
	手持笔类武器。
HELP
	);
	return 1;
}
