//lianxin.c 练心弹
//星宿毒掌，以内功激发，弹出一股弹丸，遇到对方则爆炸，中毒+麻痹+破气

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
       object dan;
	   int damage;
       if( !target ) target = offensive_target(me);

       if( !target || !me->is_fighting(target) )
            return notify_fail("「练心弹」只能在战斗中对对手使用。\n");

       if( objectp(me->query_temp("weapon")) )
            return notify_fail("你必须空手才能使用「练心弹」！\n");

       if( (int)me->query_skill("chousui-zhang", 1) < 150 )
            return notify_fail("你的星宿毒掌还不够娴熟，使不出「练心弹」绝技。\n");

       if( (int)me->query_skill("huagong-dafa",1) < 150 )
            return notify_fail("你的化功大法修为不够，不能使用「练心弹」。\n");

       if((int)me->query_skill("poison",1)<150)
            return notify_fail("你毒计不够150无法使用练心弹。\n"); 
      // if(!present("lin huo",me)||!present("liu huang",me))
        //    return notify_fail("练心弹需要磷火，你要身带磷火和硫磺。\n"); 
	  // dan=present("lianxin dan",me);       

      
		 
     

       if (me->query_skill_prepared("strike") != "chousui-zhang"
        || me->query_skill_mapped("strike") != "chousui-zhang"
        || me->query_skill_mapped("parry") != "chousui-zhang")
           return notify_fail("你现在无法使用「练心弹」！\n");                                                                                 

       if( (int)me->query("max_neili") < 2500) 
           return notify_fail("你内力太弱，使不出「练心弹」。\n");      

       if( (int)me->query("neili") < 500)
           return notify_fail("你现在真气太弱，使不出「练心弹」。\n");
		//if (me->me->query_skill("poison",1)<150 || me->query_skill("hugong-dafa",1)<150)
     	  // if (!dan)
			//return notify_fail("你身上没有练心弹，如何使用内力弹射练心弹!\n");
       
	   //if(dan) message_vision(HIW"\n$N从怀中偷偷掏出一枚练心弹，阴阴一笑，以内力弹向$n！\n"NOR,me);
      // else 
		   message_vision(HIW"$N从地上随手抓起一块泥土，从怀中掏出些磷火和黑色药末，以内力运转凝聚成一个「练心弹」!\n"NOR,me); 
	   
	   //call_out("destroying", 1, dan);
       
	   if (userp(target)&&!target->is_killing(me))
          me->kill_ob(target);
       
	   me->add("neili", - 250);
       
	   damage=3000+random(500);
	   if( random(me->query("combat_exp")) > (int)target->query("combat_exp")*2/3
        && me->query_str() > (int)target->query_str()*2/3)
	   { 
         message_vision(HIB"\n$n眼见一道黑光向自己射来，手足无措，躲闪无及，正击在$n身上。\n"NOR, me, target);
        // me->add("max_neili", -50);
		 
		 target->receive_damge("qi",damage,me);
         target->set_temp("last_damage_from", "练心弹炸死");
         if (!userp(target)&&!random(3))
         	 target->die();
         return 1;  
       }
       else if(random(me->query("combat_exp")) > (int)target->query("combat_exp")/3
         || random(me->query_str()) > (int)target->query_str()/2)
	   {
          message_vision(HIB"\n$n见事不好，连忙纵身直起，练心弹从身下掠过，忽然间"HIG"爆炸"HIB"。$n受伤着实不轻。\n"NOR,me,target);
          tell_object(target,HIB"\n练心弹中毒气爆发，但一股腥臭气入鼻，你已中了剧毒了。\n"NOR);
         // me->add("max_neili", -100);
		  if (userp(target))
			 me->add_condition("killer", 15);
          target->apply_condition("fs_poison", 3);
          target->receive_damge("qi",damage,me);
		  target->receive_damge("qi",damage/2,me);
          target->set_temp("last_damage_from", "练心弹炸死");

          target->add_busy(1);
          return 1;
      }
      message_vision(HIB"\n$n胸有成竹，一声长啸，双掌连环劈出，把这个练心弹压向来路。\n"NOR,me,target);
      tell_object(me,HIB"\n不好，练心弹反弹向你，你虽然躲开，但毒气也侵入你的身体。\n"NOR);
     
      me->apply_condition("fs_poison",1);
      me->start_perform(3,"练心弹");
      return 1;
}

string perform_name(){ return HIY"练心弹"NOR; }

int help(object me)
{
        write(HIR"\n抽髓掌之「练心弹」："NOR"\n\n");
        write(@HELP
	星宿派的功夫主要是在<毒>字上下功夫，深的阴损毒辣其中三味
	抽髓掌乃是在战斗中，凭借深厚内功把体内存毒逼出借以伤敌的
	一门功夫。「练心弹」绝技是将毒药和炸药混合通过投掷的方式
	伤敌人，对方若臂力不够或经验稍缺，当即被练心弹炸死，毒发
	而死，端的狠毒！

	perform strike.lianxin

要求：
	当前内力需求 1500 以上;
	最大内力需求 2500 以上；
	抽髓掌法等级 150 以上；
	化功大法等级 150 以上；
	基本掌法等级 150 以上；
	基本内功等级 150 以上;
	基本毒计等级 150 以上;
	且手中无兵器。
        
HELP
        );
        return 1;
}