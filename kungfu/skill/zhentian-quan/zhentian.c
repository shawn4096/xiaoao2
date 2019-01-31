// zhentian.c 震天拳-震天绝技

#include <ansi.h>
#include <combat.h>
inherit SKILL;
inherit F_SSERVER;

string perform_name(){ return HIC"震天绝技"NOR; }

void remove_effect(object target);
void check_fight(object me,object target);

int perform(object me, object target)
{
    int lvl;
    lvl = (int)me->query_skill("zhentian-quan", 1);
   
    if( !target ) target = offensive_target(me);
    
    if( !target || !me->is_fighting(target) )
      return notify_fail("「震天绝技」只能在战斗中对对手使用。\n");

    if (me->query_skill_prepared("cuff") != "zhentian-quan"
      || me->query_skill_mapped("cuff") != "zhentian-quan")
      return notify_fail("你现在无法使用「震天绝技」进行攻击。\n");      

    if( (int)me->query_skill("zhentian-quan",1) < 100 )
      return notify_fail("你的震天拳不够娴熟，不能使用「震天绝技」！\n");
    
    if( (int)me->query_skill("cuff",1) < 100 )
      return notify_fail("你的基本拳法等级不够，不能使用「震天绝技」！\n");  
    
    if( (int)me->query_skill("xuantian-wuji", 1) < 100 )
      return notify_fail("你的玄天无极功等级不够，不能使用「震天绝技」！\n");

    if( (int)me->query("max_neili") < 1400 )
      return notify_fail("你的功力太弱，不能使用「震天绝技」！\n");
    
    if( (int)me->query("neili") < 800)
      return notify_fail("你的内力太少了，无法使用出「震天绝技」！\n");   
    
    if( (int)me->query("jingli") < 200 )
      return notify_fail("你现在精力太少，不能使用「震天绝技」。\n");
  
    if(me->query_temp("klpfm/zhentian"))
      return notify_fail("你暂时不能使用「震天绝技」了。\n");  
                                                                               
    message_vision(HIC"\n$N施展出震天拳的「震天绝技」，自巧转拙，却是去势奇快，拳风凌厉，如雨点般向$n打去！\n"NOR, me,target);
    message_vision(HIW"\n$N的拳风呼啸，劲气汹涌，空气跌宕起伏形成嗡嗡的震动之声！\n"NOR, me,target);

    me->add("neili", - 150);
    me->add("jingli", -100);      
    
    if( random(lvl) > (int)target->query_skill("parry",1)/2
	  ||random(me->query_str(1))>target->query_dex(1)/2)
	{
	  message_vision(HIY"\n$n一时不察，顿时被$N的漫天震动之声所影响，宛如陷入泥潭沼泽之中。\n"NOR, me,target);
	  target->add_busy(1);
		if( !target->query_temp("kl_zhentian")   ) {
		  target->add_temp("apply/attack", -lvl/6);
		  target->add_temp("apply/dodge", -lvl/6);
		  target->add_temp("apply/parry", -lvl/6); 
		  target->set_temp("kl_zhentian",lvl); 
		  if (objectp(target))
			  call_out("zhentian",lvl/20,me,target); 
		}  
    }
    else {
	  message_vision(YEL"\n$n轻功绝顶，顿时发现$N攻势中的破绽，冲出重围。\n"NOR, me,target);
    }
    
	me->add_temp("apply/attack", lvl/5 );
	me->add_temp("apply/damage", lvl/6 );
	me->add_temp("apply/cuff", lvl/6 ); 

	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (me->query("gender")=="男性")?3:1);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), (me->query("gender")=="男性")?3:1);
	   
	   if(me->query("gender")=="男性"&& me->is_fighting()) 
	   {
			me->add_temp("apply/attack", lvl/5 );
			me->add_temp("apply/damage", lvl/6 );
		    message_vision(HIW"\n$N身高力猛，震天拳法施展到极致，一掌拍出，空气被震动的轰的一声巨响。\n"NOR, me,target);
			me->add("neili", - 100);
			me->add("jingli", -50);   

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			me->add_temp("apply/attack", -lvl/5 );
			me->add_temp("apply/damage", -lvl/6 );				
		}
	me->add_temp("apply/attack", -lvl/5 );
	me->add_temp("apply/damage", -lvl/6  );
	me->add_temp("apply/cuff",-lvl/6 ); 
	
	me->delete_temp("klpfm/zhentian");
	me->start_busy(2);
	me->start_perform(4,"「震天绝技」");
    return 1; 
}

void zhentian(object target)
{
    int lvl;
	if (!objectp(target)) return;
	lvl=target->query_temp("kl_zhentian");
	target->add_temp("apply/attack", lvl/6);
    target->add_temp("apply/dodge", lvl/6);
    target->add_temp("apply/parry", lvl/6);
    target->delete_temp("kl_zhentian");
    tell_object(target, HIB"你渐渐冷静下来，震天拳所造成的虚弱状态又恢复如常。\n"NOR);
	return;
}

int help(object me)
{
write(HIC"\n震天拳之「震天绝技」："NOR"\n\n");
write(@HELP
	震天拳是昆仑派门下弟子入门武技，凭借深厚的内力
	以快速出拳，和空气剧烈摩擦后形成的嗡嗡之声，功
	力越高，这种效果越强，宛如震天之意。震天绝技正
	是利用此项绝技来影响并虚弱对手。连出二招，威力
	极大。男性玩家因臂力强大此招有优势并多出一招。
	此招威力奇妙，命中判断武技或臂力效果。
	
	指令；perform cuff.zhentian
要求：
	最大内力 1400 以上，
	当前内力 800 以上，
	当前精力 200 以上；
	玄天无极 100 以上；
	震天拳法 100 以上；
	基本拳法 100 以上；
	激发并且备有震天拳。
	初期的招式，可造成敌人busy且攻防下降，

HELP
);
return 1;
}
