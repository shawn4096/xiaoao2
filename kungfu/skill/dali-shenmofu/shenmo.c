// shenmo.c 增加属性的武技 神魔诀

#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return RED"神魔诀"NOR; }

int perform(object me, object target)
{
      int lvl,lvl1;
      object weapon;
      weapon = me->query_temp("weapon");
      lvl = (int)me->query_skill("dali-shenmofu", 1);
      lvl1=(int)me->query_skill("xixing-dafa", 1);
  
    if( !target ) target = offensive_target(me);
     
      if( !target ||!living(target)|| !me->is_fighting(target) )
        return notify_fail("「神魔诀」只能在战斗中对对手使用。\n");

      if (!weapon || weapon->query("skill_type") != "axe"
       || me->query_skill_mapped("axe") != "dali-shenmofu")
        return notify_fail("你使用的兵刃不正确，无法使用「神魔诀」！\n");             
      if( me->query("quest/hmy/dlsmf/jueji")!="pass" )
        return notify_fail("你知道大力神魔斧，但尚未融会贯通，不能使用「神魔诀」！\n");
      if( (int)me->query_skill("dali-shenmofu",1) < 350 )
        return notify_fail("你的大力神魔斧不够娴熟，不能使用「神魔诀」！\n");
      
      if( (int)me->query_skill("axe",1) < 350 )
        return notify_fail("你的基本斧法等级不够，不能使用「神魔诀」！\n");  
      if (me->query_skill_mapped("force") != "tianmo-gong" )
          if(me->query_skill_mapped("force") != "xixing-dafa")
                return notify_fail("你所使用的特殊内功不对。\n"); 

       if(me->query_skill("xixing-dafa", 1)<350)
          if(me->query_skill("tianmo-gong", 1) < 350)
                return notify_fail("以你现在的内功修为还使不出「神魔诀」。\n");  


      if(me->query_skill_mapped("parry")!="dali-shenmofu")
        return notify_fail("你的招架不符，不能使用「神魔诀」！\n");

      if( (int)me->query("max_neili") < 5000 )
        return notify_fail("你的内力太弱，不能使用「神魔诀」！\n");
      
      if( (int)me->query("neili") < 1000)
        return notify_fail("你的内力太少了，无法使用出「神魔诀」！\n");   
      if( me->query_temp("dlf/shenmo"))
        return notify_fail("你正在使用「神魔诀」！\n");                                                                             
      message_vision(HIY"\n$N内功流转，浑身肌肉虬起，暗颂大力神魔斧「神魔诀」，周身劲力流转不息，宛如神魔重生，$N觉得全身充满了无穷的力量。\n"NOR, me,target);
      if (weapon)
         message_vision(YEL"\n$N浑身劲力灌注于手中的"+weapon->query("name")+YEL"中，"+weapon->query("name")+YEL"若隐若现有一层流光闪动。\n"NOR, me);

	  me->add("neili", - 500);
      me->add("jingli", -50);      
      if (userp(me))
      {
		  lvl = lvl /3;
      } else lvl=lvl/8;
      if (me->query_skill_mapped("force")=="xixing-dafa"&&me->query_skill("xixing-dafa",1)>450)
      {
		  message_vision(BLU"$N吸星大法劲力勃发，手中"+weapon->query("name")+BLU"更见威势！\n"NOR,me);
		  lvl=lvl+lvl1/6;
      }
	  me->add_temp("apply/strength", lvl /10);
	  
me->add_temp("apply/attack", lvl/2 );
	  
me->add_temp("apply/damage", lvl/3 );

	  me->add_temp("apply/axe", lvl/2 );

	  me->set_temp("dlf/shenmo", lvl);
	  
      //COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
   /*   if (present(target,environment(me)) && me->is_fighting(target))
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);*/
     call_out("remove_effect", 1, me, weapon, lvl);     
     /*
	 if (userp(me)&&!userp(target))
	  {
		 target>add_temp("apply/attack", -lvl);
	     target->add_temp("apply/damage", -lvl );
	  }*/
     if (me->query_skill("dali-shenmofu",1)<350)
      {
		   me->start_busy(1);
		   me->start_perform(2,"「神魔诀」");
      }
	 if (me->query_skill("dali-shenmofu",1)<450)
      {
		   me->start_perform(1,"「神魔诀」");
      }      
      return 1;
}

void remove_effect(object me,object weapon,int count)
{
        int i;
        if(!me) return;
        if(!me->is_fighting()
         || !weapon
         || me->query_skill_mapped("axe") != "dali-shenmofu"
         || me->query_skill_mapped("parry") != "dali-shenmofu"
         || count < 1 ){
          i = me->query_temp("dlf/shenmo");
          me->add_temp("apply/axe", -i/2);
          me->add_temp("apply/damage", -i/3);
		  me->add_temp("apply/attack", -i/2);
          me->add_temp("apply/strength", -i/10);
          me->delete_temp("dlf/shenmo");
	      message_vision(HIY"\n$N劲力已达瓶颈，此时劲气外泄，急忙收气守意，压制翻腾不已的气血。\n"NOR, me);
		 if (weapon)
		    message_vision(HIY"\n$N一套「大力神魔诀」使完，手中"NOR+weapon->name()+HIY"上的光芒渐渐也消失了。\n"NOR, me);
          return;
        }
        else {
         // me->start_perform(1,"「大力神魔诀」");
          call_out("remove_effect", 1, me, weapon, count -2);
        }
}


int help(object me)
{
        write(RED"\n大力神魔斧之「神魔诀」："NOR"\n\n");
        write(@HELP 
	大力神魔斧之绝技「神魔诀」，乃是日月十大长老大力神魔范松绝技，
	强行运使全身功力于一身，短时间内爆发斧头的最大威力，想当初十大
	长老被困华山石壁，范松以此大斧头一路开山劈路，行进十多米，以至
	仅剩最后一斧头将劈开石壁，可惜最终力尽而亡。可见这神魔诀的厉害。
	注意：350级小飞，450级后大飞。
	要求：  
		当前内力 1000 以上；
		最大内力 5000 以上；
		当前精力 500 以上；
		基本斧法等级 350 以上；
		大力神魔斧等级 350 以上；
		激发斧法为大力神魔斧法；
		激发招架为大力神魔斧法；
		激发内功为天魔功或吸星大法。
HELP
        );
        return 1;
}