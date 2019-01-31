// xuanxu.c 玄虚

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
void check_fight(object me);
int perform(object me, object target)
{
      string msg;             
      object weapon = me->query_temp("weapon");                      
      int j = (int)me->query_skill("xuanxu-daofa", 1);
      
	  if( !target ) target = offensive_target(me);
     
      if( me->is_busy() )
        return notify_fail("你正忙着呢。\n");
      if( !target || !me->is_fighting(target) )
        return notify_fail("玄虚诀只能在战斗中对对手使用。\n");
             
      if( (int)me->query_skill("xuanxu-daofa", 1) < 200 )
        return notify_fail("你的玄虚诀法不够娴熟，不能使玄虚诀！\n");
      
      if( (int)me->query_skill("force", 1) < 200 )
        return notify_fail("你的基本内功等级不够，不能使用玄虚诀！\n");

      if( (int)me->query_skill("blade", 1) < 200 )
        return notify_fail("你的基本刀法等级不够，不能使用玄虚诀！\n");  
      
      if( (int)me->query_skill("taoism", 1) < 150 )
        return notify_fail("你对道家心法领悟不够精深，无法使用出玄虚诀！\n");
      
      if( (int)me->query("max_neili") < 2000 )
        return notify_fail("你的内力太弱，不能使用玄虚诀！\n");
      
      if( (int)me->query("neili") < 500 )
        return notify_fail("你的内力太少了，无法使用出玄虚诀！\n");   

      if (!weapon || weapon->query("skill_type") != "blade"
		  || me->query_skill_mapped("parry") != "xuanxu-daofa"
          || me->query_skill_mapped("blade") != "xuanxu-daofa")
        return notify_fail("你没有激发玄虚刀法。\n");

                                                                                 
      if( me->query_temp("xxd/xuanxu")   )
          return notify_fail("你正在使用玄虚诀！\n");

      msg = HIY"$N使出玄虚诀法中的绝技玄虚决，刀出成环，只绞的$n眼前一片影环。\n"NOR;
      me->add("neili", -200);
	  me->add("jingli", -100);

      me->set_temp("xxd/xuanxu", j);
	  me->add_temp("apply/attack",j/5);
	  me->add_temp("apply/damage",j/6);
	  me->add_temp("apply/blade",j/5);

	  call_out("check_fight",1,me);

    //  me->start_call_out( (: call_other, __FILE__, "remove_effect", me, j :), j);
   //   me->start_call_out( (: call_other, __FILE__, "check_fight", me, target :), 1);
      message_vision(msg, me, target);   

      return 1;
}

void check_fight(object me)
{
    object weapon;  
	int j;
	if (!me||!me->query_temp("xxd/xuanxu")) return;
	weapon=me->query_temp("weapon");
	j=me->query_temp("xxd/xuanxu");

    if(me->query_skill_mapped("blade") != "xuanxu-daofa"
       || !weapon
       || weapon->query("skill_type") != "blade"
       || !me->is_fighting() 
	   || me->query_skill_mapped("parry") != "xuanxu-daofa")
	{
	
		  me->add_temp("apply/attack",-j/5);
		  me->add_temp("apply/damage",-j/6);
		  me->add_temp("apply/blade",-j/5);
		  me->delete_temp("xxd/xuanxu");
		  message_vision(HIC"$N气息绵长，缓缓将胸中的浊气吐出，玄虚诀劲气逐渐消退!\n"NOR,me);
		  return;
	}
	call_out("check_fight",1,me);

}
string perform_name(){ return HIC"玄虚诀"NOR; }
int help(object me)
{
         write(HIB"\n玄虚诀法之"+HIY"「玄虚诀」"NOR"\n");
        write(@HELP
	玄虚诀法乃是武当入门弟子的武技，该刀法乃是开山祖师
	张三丰早期闯荡江湖时所使用的武功。总共十七招，后来
	俞岱岩凭借此武功追杀盗贼，在第八招上那汪洋巨盗给斩
	杀。以此享誉江湖。
	玄虚诀是将武当独门心法融入到刀法中，阴阳相合，刚柔
	并济，实战中往往出其不意。
	
	指令：perform blade.xuanxu

要求：
	基本内功：200
	玄虚诀法：200
	基本刀法：200
	道学心法：150
	最大内力：2000
	当前内力：500
	激发刀法玄虚刀法
	激发招架玄虚刀法
	内功不限
	备震山绵掌。
	手持刀类武器
HELP
        );
        return 1;
}
