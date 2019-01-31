// shijiushi.c 玉女十九式
// Update by lsxk@hsbbs 调整剑宗和气宗使用效果。

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
#define MAX_HITS    19
 
string perform_name() {return HIW"玉女十九式"NOR;}

int perform(object me, object target)
{
        string weapon;
        int i,j;
        j=19; //剑宗招式
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("玉女十九式只能对战斗中的对手使用。\n");
       //若是气宗必须判断内功，但若是剑宗则可以不判断内功。。
		if (me->query("huashan/quest") == "气宗")
        {
           if (me->query_skill_mapped("force") != "zixia-gong"
               &&me->query_skill_mapped("force") != "huashan-qigong")
                return notify_fail("你的内功有误，无法使用「玉女十九式」。\n");
        }       

        if( me->query_dex() < 60 )
                return notify_fail("你在身法上先天禀赋不足，不能使用玉女十九式！\n");
        
        if( me->query_skill("zixia-gong", 1) < 350
         && me->query_skill("huashan-qigong", 1) < 350)
                return notify_fail("你的特殊内功火候未到，无法施展玉女十九式！\n");

        if( (int)me->query_skill("huashan-jianfa",1) < 350 )
                return notify_fail("你的华山剑法火候不足，无法使用精妙绝伦的玉女十九式！\n");

        if( me->query_skill("dodge") < 350 )
                return notify_fail("玉女十九式需要超绝的轻功配合，方能有效施展！\n");

        if( me->query_skill("sword") < 350 )
                return notify_fail("你剑法未到炉火纯青之境，还不会使用玉女十九式！\n");

        if( me->query("neili") <= 2000 )
                return notify_fail("你的内力不够使用玉女十九式！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力不够使用玉女十九式！\n");

        if( me->query_temp("hsj_19"))
                return notify_fail("你正在运用玉女十九式！\n");

      if(!me->query_temp("weapon") || (me->query_temp("weapon"))->query("skill_type") != "sword" )
                return notify_fail("你手中无剑怎能使用玉女十九式？！\n");

        weapon = (me->query_temp("weapon"))->query("name");

        message_vision(HIC "\n$N运剑如风，精妙非常的“玉女剑十九式”一式式施展开来。" + weapon + HIC"如银龙出海,幻起道道电光！\n" +
        "顷刻之间，$N将“玉女十九剑”中那十九式的数百招一气呵成的使了出来，这数百招便如一招，剑法之快，直是匪夷所思。\n" NOR, me, target);
        me->set_temp("hsj_19",1);
        //女性增加防御
		if(me->query("gender")=="女性")
	      { 
			me->add_temp("apply/dodge",me->query_skill("huashan-jianfa",1)/3);
			me->add_temp("apply/parry",me->query_skill("huashan-jianfa",1)/3);
			me->add_temp("apply/dexerity",me->query_skill("huashan-jianfa",1)/5);
			me->add_temp("apply/damage",me->query_skill("huashan-jianfa",1)/5);
			message_vision(HIW"$N双手握剑，面沉似水，但姿态飘逸，宛如凌波仙子，手中的剑法却明显大异往昔，更加凌厉。\n"NOR,me);
		  }
		//气宗增加命中,招式减少
		if(me->query("quest/huashan")=="气宗")
	    {
			me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1)/4);
			me->add_temp("apply/sword",me->query_skill("huashan-jianfa",1)/6);
            j= 10;
		}
        j=random(j);
		if (j<7 && me->query("quest/huashan")=="剑宗") j=7;
		else if (j< 5 && me->query("quest/huashan")=="气宗") j=5;
		//else j=j;
        me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1)/4);
        for( i = 0; i < j; i ++ ) {        
          //剑宗增加伤害
		  if (me->query("quest/huashan") == "剑宗"){
             me->add_temp("apply/damage",(int)me->query_skill("huashan-jianfa",1)/4);
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
             me->add_temp("apply/damage",-(int)me->query_skill("huashan-jianfa",1)/4);
          } 
		  else if(me->query("quest/huashan") == "气宗"){
             if(!random(3)) target->set_temp("must_be_hit",1);
             if(!target->is_busy()){
                 message_vision(HIW"\n$N将浑厚内功气劲附着于手中的"+weapon+HIW+"上，$n只觉一股劲风袭来，剑气凛冽异常!\n"+
                     HIC"$n感觉自己宛如陷入一片剑林之中，顿觉四处受制！\n"NOR,me,target);
                 target->start_busy(2+random(3));
				 //气宗增加对方busy
			  }			
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:3);
             target->delete_temp("must_be_hit");
          }		 
		  else              
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?1:2);
             //me->add("neili",-100);    
      
      }
        me->add("neili", -300);
        if(me->query("quest/huashan")=="气宗")
	     { 
			 me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/4);
		     me->add_temp("apply/sword",-me->query_skill("huashan-jianfa",1)/6);
		 }
        if(me->query("gender")=="女性")
	      { 
		  me->add_temp("apply/dodge",-me->query_skill("huashan-jianfa",1)/3);
          me->add_temp("apply/parry",-me->query_skill("huashan-jianfa",1)/3);
          me->add_temp("apply/dexerity",-me->query_skill("huashan-jianfa",1)/5);
		  me->add_temp("apply/damage",-me->query_skill("huashan-jianfa",1)/5);
		  }
		me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/4);
		me->add("jingli", -100);
        me->delete_temp("hsj_19");
        me->start_perform(4+random(2));
        me->start_busy(2+random(2));
        return 1;
}

int help(object me)
{
   write(WHT"\n华山剑法「"HIW"玉女十九式"WHT"」："NOR"\n");
   write(@HELP
	这招「玉女十九式」乃穷华山先辈心血而创，华山剑宗，气宗对其理
	解却各有所不同，剑宗讲究剑招轻盈灵巧，行云流水，而气宗却讲究
	以深厚内力驭剑，攻敌破绽，一招即出，绝无不中之理。因此，剑宗
	使用，出招数以及威力均强与气宗，而气宗使用，则命中率远高于剑
	宗，并有几率让敌人忙乱。需要注意的是气宗比较强调内功的重要性
	剑宗注重剑招的威力，因此，剑宗不太重视此招是否和内功相匹配。
	注意：此招乃剑宗绝技，剑宗使用比气宗有额外优势。
	
	指令：perform sword.shijiushi

要求：
	华山气功 或者 紫霞神功 350级,剑宗不限
	后天身法大于 60
	华山剑法需求 350 级，
	基本剑法需求 350 级，
	基本轻功需求 350 级，
	当前内力需求 2000 以上，
	当前精力需求 1000 以上。
HELP
   );
  return 1;
}
