 // sandou 灵蛇三闪击

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int lv;
      object weapon;

      weapon = me->query_temp("weapon");
	  lv = me->query_skill("lingshe-bianfa",1);
      if( !target ) target = offensive_target(me);
     
      if( !target || !me->is_fighting(target) )
      return notify_fail("「灵蛇三闪击」只能在战斗中对对手使用。\n");

      if (!weapon || weapon->query("skill_type") != "whip"
       || me->query_skill_mapped("whip") != "lingshe-bianfa")
      return notify_fail("你手里没有鞭，无法使用「灵蛇三闪击」！\n");             

      if( (int)me->query_skill("lingshe-bianfa",1) < 100 )
			return notify_fail("你的灵蛇鞭法不够娴熟，不能使用「灵蛇三闪击」！\n");
      if( (int)me->query_skill("dulong-dafa",1) < 100 )
			return notify_fail("你的毒龙大法不够娴熟，不能使用「灵蛇三闪击」！\n");

      if( (int)me->query_skill("whip", 1) < 100 )
			return notify_fail("你的基本鞭法等级不够，不能使用「灵蛇三闪击」！\n");
      if( (int)me->query_skill("dodge", 1) < 100 )
			return notify_fail("你的基本轻功等级不够，不能使用「灵蛇三闪击」！\n");

      if( (int)me->query("neili") < 300 )
			return notify_fail("你的内力太少，不能使用「灵蛇三闪击」！\n");
	  if( (int)me->query("jingli") < 500 )
			return notify_fail("你的精力太少，不能使用「灵蛇三闪击」！\n");
      if( (int)me->query_skill("qusheshu", 1) < 20 )
			return notify_fail("你的驱蛇术等级不够，不会使用「怪蛇缠」。\n");
	  if(me->query_skill_mapped("force") != "dulong-dafa")
       		return notify_fail("你现在使用的内功与毒龙大法相抵触，不能使用「灵蛇三闪击」。\n");
      if(me->query("gender")!="女性")
            return notify_fail("你非女性，无法使用「怪蛇缠」。\n");
      message_vision(HIB"\n$N嘴里发出嘶嘶的怪叫几声，手中"+weapon->query("name")+HIB+"连续抖动三下，连续抖动手中鞭子三下\n形成三道若隐若现的鞭影，循着诡异的途径向$n袭去！\n"NOR, me,target);
      
	  me->add("neili", -200); 
      me->add("jingli", -50);

      //target->add_busy(1);
	  //me->start_busy(2);
	  if (!userp(target)) 
	  {
		  lv += lv+me->query_dex();
		 // lv=lv+
	  }
	  if (me->query_skill("poison",1)>150)
	  {
		  lv=lv+me->query_skill("poison",1);
	  }
      me->set_temp("lsbf/sandou",1);
      me->add_temp("apply/attack", lv/2);
	  me->add_temp("apply/whip", lv/4);
	  me->add_temp("apply/damage", lv/4);
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);  
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);  
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
      
	  if (me->is_fighting(target)
		  &&me->query_skill("lingshe-bianfa",1)>250)
      {
			message_vision(HIG"$N将手中的"+weapon->query("name")+HIG"反手施展出「万蛇嘶鸣」招式，鞭头形成无数道尖锐的啸叫，刺向$n。\n"NOR,me,target);
			me->add_temp("apply/attack", lv/2);
			me->add_temp("apply/damage", lv/5);
			weapon->unequip();
			//target->add_busy(2);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  
			me->add_temp("apply/damage", -lv/5);
			me->add_temp("apply/attack", -lv/2);
			weapon->wield();
      }
	  me->add_temp("apply/attack", -lv/2);
      me->add_temp("apply/whip", -lv/4);
	  me->add_temp("apply/damage", -lv/4);
	  me->delete_temp("lsbf/sandou");	
      me->start_perform(3,"「灵蛇三闪击」");
      return 1;
}
string perform_name(){ return HIB"灵蛇三闪击"NOR; }

int help(object me)
{
        write(HIC"\n灵蛇鞭法"+HIB"「灵蛇三闪击」"NOR"\n");
        write(@HELP
	灵蛇鞭法乃是神龙教教主洪安通根据所豢养的灵蛇习性所创
	一方面是为了武林争雄，另外一方面也凭此驱使蛇阵前行动
	此武学讲究灵动犀利、阴险毒辣，且带毒，舞动之际，宛如
	蛟龙出海，万蛇出洞，厉害非常。是神龙教女弟子的入门武
	功。
	注意：伤害与毒计和身法有关联,250级后再出一招万蛇嘶鸣

	指令：perform whip.sandou

要求：
	当前内力要求 500 以上；
	当前精力要求 300 以上；
	基本鞭法要求 100 以上；
	灵蛇鞭法要求 100 以上；
	毒龙大法要求 100 以上；
	基本轻功等级 100 以上；
	驱蛇术的等级 20  以上；
	激发鞭法为灵蛇鞭法。
	激发招架为灵蛇鞭法。
	内功激发毒龙大法；
	手持鞭类武器

HELP
        );
        return 1;
}
