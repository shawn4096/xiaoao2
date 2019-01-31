//piao.c 飘
//BY BOBO@SJ
// modified by darken@SJ

#include <combat.h>
#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return HIC"水上飘"NOR; }

void remove_effect(object me, int improve);
int help(object me);
int perform(object me)
{
      string msg;                                   
      int improve;
      
      if( (int)me->query_skill("shuishangpiao",1) < 140 )
           return notify_fail("你的水上飘不够娴熟，不会使用「飘」！\n");

      if( (int)me->query_skill("guiyuan-tunafa",1) < 140 )
           return notify_fail("你的归元吐纳法等级不够，不能使用「飘」！\n");  

      if (me->query_skill("force",1)<140)
           return notify_fail("你的基本内功，不能使用「飘」。\n");

      if( (int)me->query_dex() < 28 )
           return notify_fail("你的身法太低，不能使用「飘」！\n");
      
      if( (int)me->query_skill("dodge", 1) < 120 )
           return notify_fail("你的基本轻功太差，身体笨拙，不能使用「飘」！\n");
      
      if( (int)me->query("max_neili") < 1500 )
           return notify_fail("你的内力太少了，无法使用出「飘」！\n");   
      if( (int)me->query("neili") < 500 )
           return notify_fail("你的内力太少了，无法使用出「飘」！\n");   
      if (me->query_skill_mapped("dodge") != "shuishangpiao")
           return notify_fail("你现在激发的轻功无法用「飘」绝技。\n");

      if( me->query_temp("piao"))
           return notify_fail("你正在使用水上飘的特殊防御「飘」！\n");
       
      msg = HIC"$N突然深吸一口气，双目精光一闪，一抬腿如蜻蜓点水般，身体轻轻飘出数丈" +
               "又轻轻飘了过来！\n" NOR;
      
      message_vision(msg, me); 
      improve = (int)me->query_skill("shuishangpiao",1);
      me->add_temp("apply/dexerity", improve/10);
      me->set_temp("piao", 1); 
	  if (me->query("quest/tiezhang/piao"))
	  {
	   me->add_temp("apply/attack",improve/10);
	   me->add_temp("apply/armor",improve/8);
	   me->add_temp("apply/defense",improve/5);
	   }
      me->add("neili", -(100 + (int)me->query_skill("shuishangpiao",1)/10));           
      me->start_call_out((: call_other, __FILE__, "remove_effect", me, improve :), me->query_skill("shuishangpiao", 1)/5);
      return 1;
}

void remove_effect(object me, int improve)
{
      if(!me) return;
      me->add_temp("apply/dexerity", - improve/10);
	  if (me->query("quest/tiezhang/piao"))
	  {
	   me->add_temp("apply/attack",-improve/10);
	   me->add_temp("apply/armor",-improve/8);
	   me->add_temp("apply/defense",-improve/5);
	   }
       me->delete_temp("piao");
      tell_object(me, HIC"你轻轻呼出一口气，散去了丹田凝聚的内力。\n"NOR);
}

int help(object me)
{
        write(HIR"\n水上漂之「漂」："NOR"\n\n");
        write(@HELP 
		铁掌水上漂裘千仞以铁掌掌法和水上漂绝技享誉江湖，想当初裘千仞和周伯通
		彼此追逐，奔驰万里，周伯通始终未能追的上裘千仞，由此可见此绝技的威力。
		学要提醒的是，若能从裘千仞帮主哪儿解开水上漂绝技，则会大幅提升躲避防御。
        要求：  当前内力 500 以上；
                最大内力 1500 以上；
                当前精力 500 以上；
                基本轻功等级 140 以上；
                基本内功等级 140 以上；
                激发轻功为水上漂；                              
HELP
        );
        return 1;
}