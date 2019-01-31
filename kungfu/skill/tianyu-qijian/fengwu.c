//Modified by zhuifeng@SJFY
//Update by Jpei 2010

#include <ansi.h>
inherit F_SSERVER;

string perform_name(){ return HIC"凤"HIG"舞"HIY"九"HIB"天"NOR; }

int perform(object me, object target)
{
        int skill,lvl;
        object weapon;

    if( !target ) target = offensive_target(me);
     
    if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("「凤舞九天」只能对战斗中的对手使用。\n");

    if (me->query_skill_mapped("force") != "beiming-shengong")
    if (me->query_skill_mapped("force") != "bahuang-gong" )                
                return notify_fail("你的内功有误，无法使用「凤舞九天」！\n");

    if(!wizardp(me) && (int)me->query_skill("beiming-shengong", 1) < 450 )
		if(!wizardp(me) && (int)me->query_skill("bahuang-gong", 1) < 450 )
                return notify_fail("你的内功还未练成，不能使用「凤舞九天」！\n");

    if((int)me->query_skill("force", 1) < 450 )
                return notify_fail("你的基本内功不够娴熟，无法支持「凤舞九天」。\n");

    if( (int)me->query_skill("tianyu-qijian", 1) < 450 ) 
                return notify_fail("你的剑法还未练成，不能使用「凤舞九天」！\n");

    if((int)me->query_skill("sword", 1) < 450 )
                return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用「凤舞九天」。\n");

    if((int)me->query_skill("dodge", 1) < 450 )
                return notify_fail("你的基本轻功不够娴熟，不能使用「凤舞九天」。\n");

    if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "tianyu-qijian"
        || me->query_skill_mapped("parry") != "tianyu-qijian")
                return notify_fail("你手里无剑，如何使用「凤舞九天」？\n");
                
    if((int)me->query("max_neili") < 12000 )
                return notify_fail("你现在真气不足，不能使用「凤舞九天」！\n");

    if((int)me->query("neili") < 1000 )
                return notify_fail("你现在真气不足，不能使用「凤舞九天」！\n");

    if((int)me->query("jingli") < 1000 )
                return notify_fail("你现在太累了，不能使用「凤舞九天」！\n");
   
    me->add("neili",-350);
	 me->add("jingli",-250);
    lvl = me->query_skill("tianyu-qijian",1);
    skill = me->query_skill("tianyu-qijian",1)+ me->query_skill("bahuang-gong", 1) /2 ;
    skill = skill /4;
    if (me->query("family/family_name") == "灵鹫宫") skill=skill*3/2;
//削弱npc效果
    if(!userp(me)) 
		skill = skill / 3;
     me->add_temp("apply/attack", skill/2 );	
     me->add_temp("apply/damage", skill/4);
     me->add_temp("apply/sword", skill/4);
	

    message_vision(HIW"\n$N剑意忽转轻灵，手中的"+weapon->name()+""HIW"泛起道道奇异的剑光，极尽潇洒飘逸，正是天羽奇剑之「"HIC"凤"HIG"舞"HIY"九"HIB"天"HIW"」！\n" NOR,me,target);       
	if (me->query("quest/ljg/tyqj/pass1"))
	{
		message_vision(HIC"\n$N将无量玉璧的剑意融汇贯通，「凤舞九天」威力顿时大增！\n" NOR,me,target);       
		me->add_temp("apply/damage", skill/5);
		me->add_temp("apply/sword", skill/5);
	 }
//180级之前只能出三剑哦！

    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        
    if(me->is_fighting(target))
    {    
		message_vision(HIR"    第一剑！\n" NOR,me,target);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
    }
    if(me->is_fighting(target) && target->query("qi")> 0 )
    {   
		message_vision(HIR"    第二剑！\n" NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
    }
    if(me->is_fighting(target) && target->query("qi")> 0 )
    {    
		 message_vision(HIC"    第三剑！\n" NOR,me,target);
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);

	}
    if(me->is_fighting(target) && lvl >= 250 && target->query("qi")> 0 )
    {
        me->add_temp("apply/damage", skill);
        message_vision(HIY"    第四剑！\n" NOR,me,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
        
        if(me->is_fighting(target))
        {      
			message_vision(HIG"    第五剑！\n" NOR,me,target);
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        }
        me->add_temp("apply/damage", -skill);
      }


      if(me->is_fighting(target) && lvl >= 350 && target->query("qi")> 0 )
       {        
		  message_vision(HIM"    第六剑！\n" NOR,me,target);
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
 
	   }
//设置个小飞吧 。第七剑
      if(me->is_fighting(target) && lvl >= 350 && target->query("qi")> 0 ) 
      { 
        me->add_temp("apply/damage", lvl);
        target->set_temp("must_be_hit",1);
        message_vision(HBGRN+HIW" 这最后一剑携前面六剑之威，如雷霆霹雳，竟是挡无可挡！\n" NOR,me,target);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        target->delete_temp("must_be_hit") ;
        me->add_temp("apply/damage", -lvl);
        message_vision(WHT"$N剑招使毕，手中"+weapon->name()+""WHT"信手挥出！\n" NOR,me,target);
//再次飞跃，出生死符

        if(me->is_fighting(target))
		{
           if (random(me->query("combat_exp")/10000)> target->query("combat_exp")/20000 )
             {                
               message_vision(HIC "$n只觉得伤口一冷，原来已经在无声无息中被打中了一道生死符。\n" NOR,me,target);
               target->apply_condition("shengsi_poison",3);
              }
           else   
             message_vision(HIC "$n只觉得耳边一冷，连忙避让，原来却是$N无声无息中发出的一道生死符，不由得惊出了一身冷汗。\n" NOR,me,target);

        }
	  }
	      me->add_temp("apply/attack", -skill/2);
	      me->add_temp("apply/sword",  -skill/4);
	      me->add_temp("apply/damage", -skill/4);
		if (me->query("quest/ljg/tyqj/pass1"))
		{
			me->add_temp("apply/damage",-skill/5);
			me->add_temp("apply/sword", -skill/5);
		}
          me->start_busy(2);
          me->start_perform(5,"「凤舞九天」");
          return 1;
}

int help(object me)
{
    write(WHT"\n天羽奇剑之「"MAG"凤舞九天"WHT"」："NOR"\n");
         write(@HELP
	天羽奇剑之绝技凤舞九天，剑势轻灵，连攻数招，
	修行到高深之处，最多可连出七剑，所向披靡。
	并且可在其中夹带生死符，令人防不胜防。
	若机缘巧合，得窥无量玉璧之绝密，则此招将再
	次飞跃，威力更上一层楼。
  
	perform sword.fengwu
	
要求：
	八荒功的等级 450 以上;
	天羽奇剑等级 450 以上；
	基本剑法等级 450 以上；
	基本轻功等级 450 以上；
	最大内力需求 12000 以上
	当前内力需求 1000  以上
	当前精力需求 1000  以上
	激发剑法为天羽奇剑；
	激发招架为天羽奇剑；
	手持剑类武器；
	，
HELP
    );
        return 1;
}
