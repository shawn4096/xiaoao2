#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string perform_name(){ return HIC"谁与争锋"NOR; }
void remove_effect(object me, int skill);

int perform(object me, object target)
{
      string msg; 
      int i; 
      int skill;	  
      object weapon = me->query_temp("weapon");

      if (!weapon || weapon->query("skill_type") != "sword")
         return notify_fail("你手中无剑，如何使得出谁与争锋！\n");

      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
         return notify_fail("谁与争锋只能在战斗中对对手使用。\n");
             
      if((int)me->query_skill("yitian-tulong",1) < 300 )
         return notify_fail("你的倚天屠龙功还不够娴熟，尚使不出谁与争锋！\n");
      
      if((int)me->query_skill("literate",1) < 250 )
         return notify_fail("你的读书写字等级不够，不能写出谁与争锋！\n");

      if((int)me->query_skill("sword",1) < 300)
         return notify_fail("你的基本剑法等级不够，不能写出谁与争锋！\n");  
      
      if((int)me->query("max_neili") < 3500 )
         return notify_fail("你的内力修为似乎不够! \n");
      
      if((int)me->query("neili") < 1500 )
         return notify_fail("你的当前内力似乎不够！\n"); 
	  if((int)me->query("neili") < 1000 )
         return notify_fail("你的当前精力似乎不够！\n"); 
	 
	  if(target->query_temp("yttl/zf"))
	       return notify_fail("对方已经中了你的争锋绝技！\n");
	   
      if( target->is_busy() )
         return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

      if (me->query_skill_mapped("sword") != "yitian-tulong"
       || me->query_skill_mapped("parry") != "yitian-tulong")
         return notify_fail("你现在无法写出「谁与争锋」！\n");

      i = random((int)(me->query_skill("yitian-tulong",1)/100));
      if(i < 2) i=2;
      if(i > 4) i=4;                                                                                 
      msg = HIC"$N长啸一声，手中"+weapon->query("name")+HIC"直划下来，当真是星剑光芒，如矢应机，\n"+
               "霆不暇发，电不及飞，这一直乃是“锋”字的最后一笔！\n" NOR;
      me->add("neili", - 200);
	  
	  skill = me->query_skill("yitian-tulong",1);
        if (me->query_skill_mapped("force")=="yinyun-ziqi"
			&& me->query_skill("yinyun-ziqi",1)>350)
			skill += me->query_skill("yinyun-ziqi",1)/5;        			
	  
	  
      if(random(me->query_int(1)) > target->query_int(1)/2
        ||  random(me->query("combat_exp")) > target->query("combat_exp")/2) 
	  {
            target->start_busy(i+1);
            msg += HIR"$n猝不及防，但见"+weapon->query("name")+HIR"剑光雪亮，只得连连招架，毫无还手之力。\n"NOR;
			target->set_temp("yttl/zf",1);
			target->receive_damage("qi",1000+random(1000),me);
			target->receive_wound("qi",500+random(1000),me);	
			
            target->add_temp("apply/parry",-skill/5); //削弱对手       
            target->add_temp("apply/dodge",-skill/5);
			
			msg += RED"$n为那"+weapon->query("name")+RED"劲气刺中胸前穴道，溅起些许血花！\n"NOR;
			call_out("remove_effect", 5, target,skill);

      }
      else {
            me->start_busy(2);
            target->start_busy(1);
            msg += HIY"$n见$N招式犀利，心下已是暗暗警惕，当下抽身急退，躲过了这一招。\n"NOR;
      }
      message_vision(msg, me, target);
      if (me->query_skill("yitian-tulong",1)<350)
      {
		  me->start_perform(1,"「谁与争锋」");
      }
      return 1;
}

void remove_effect(object target,int skill)
{
	if(!target) return;	
	target->delete_temp("yttl/zf");
	target->add_temp("apply/parry",skill/5);        
    target->add_temp("apply/dodge",skill/5);	
	tell_object(target, HIR"\n你运气一周脸色好了许多，只觉得胸口被点穴道气血运转总算通畅了。\n"NOR);
}


int help(object me)
{
   write(HIG"\n倚天屠龙功之「"HIR"谁与争锋"HIG"」："NOR"\n");
	write(@HELP
	起因于“武林至尊，宝刀屠龙。号令天下，莫敢不从。
	倚天不出，谁与争锋。”的故事传说。后来当张三丰
	寿诞之日,武当遭逢遭逢大变,俞岱岩为人所伤，遭人
	荼毒，张三丰神情郁郁，情之所至，信手挥洒，将这
	二十四个字演为一套独步武林的特殊武功，后传于武
	当张翠山因江湖号称铁钩银划，在书法造诣极深，因
	此而享誉江湖。
	【谁与争锋】源自：待到月涌中天，张三丰长啸一声
	右掌直划下来，当真是星剑光芒，如矢应机，霆不暇
	发，电不及飞，这一直乃是“锋”字的最后一笔。  
	
	指令：perform sword.zhengfeng

要求：
	最大内力要求 3500 以上，
	当前内力要求 1500 以上，
	当前精力要求 1000 以上，
	基本剑法等级 300 级以上，
	读书写字等级 250 级以上，
	倚天屠龙功   300 级以上，
	激发剑法，招架为倚天屠龙功
	且手中持有武器          
	说明：这峰字最后一笔犀利无匹，敌人猝不及防之下，
	往往只能疲于招架，毫无还手之力。
	350级后小飞。
HELP
	);
	return 1;
}
