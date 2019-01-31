// hengsao cred by sohu@xojh 太祖拳横扫千军


#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
  int lvl,i,j;
  string msg;
  lvl = (int)me->query_skill("taizu-quan", 1);
  if (me->query("max_pot") >= 350 ) lvl = lvl /4 ;//250后衰弱
  
  if( !target ) target = offensive_target(me);
  if( !objectp(target)
	 || !me->is_fighting(target)
	 || !living(target)
	 || environment(target)!=environment(me))
		return notify_fail("「横扫千军」只能在战斗中对对手使用。\n");

   if( objectp(me->query_temp("weapon")))
		return notify_fail("你必须空手才能使用「横扫千军」！\n");

   if( (int)me->query_skill("taizu-quan", 1) < 100 )
		return notify_fail("你的太祖拳还不够娴熟，使不出「横扫千军」绝技。\n");

   if(!me->query_skill("force", 1) || (int)me->query_skill("cuff",1)<100)
   if( (int)me->query_skill("parry", 1) < 100 )
           return notify_fail("你的基础技能等级还不够，使不出「横扫千军」绝技。\n");

   if( (int)me->query_skill("dodge",1) < 100 )
		return notify_fail("你的轻功等级不够，不能使用「横扫千军」。\n");


   if( me->query_skill_prepared("cuff") != "taizu-quan"
	 || me->query_skill_mapped("cuff") != "taizu-quan")
		return notify_fail("你现在无法使用「横扫千军」！\n");


   if( me->query_skill_mapped("parry") != "taizu-quan")
		return notify_fail("你需要激发招架为太祖拳，方能使用「横扫千军」。\n");


   if( (int)me->query("max_neili") < 1300)
		return notify_fail("你的内力太弱，使不出「横扫千军」。\n");

   if( (int)me->query("neili") < 500 )
		return notify_fail("你现在真气太弱，使不出「横扫千军」。\n");

   if( (int)me->query("jingli") < 500 )
           return notify_fail("你现在太累了，使不出「横扫千军」。\n");
   if (me->query("family/family_name")=="普通百姓")
	{
	   i=3;
       j=1;
	}
   else 
	{
	   i=1;
       j=6;
	}

   message_vision(HIC"\n$N将左手向右前方轻挽并向内扣，右脚为支点，快速下盘，随即欺身向前，旋转而出。连出数招！\n"NOR,me);

   //if(!userp(target) && me->query("max_pot") <= 350)  target->set_temp("must_be_hit",1);

	me->add_temp("apply/attack", lvl/j);
	me->add_temp("apply/damage", lvl/j);
	me->add_temp("apply/cuff", lvl/j);
	me->add_temp("apply/strength", lvl/3);
    me->set_temp("tzq/hengsao",1);
      COMBAT_D->do_attack(me, target, 0, i);

	if (objectp(target) && me->is_fighting(target))
       COMBAT_D->do_attack(me, target, 0, i);

	if (objectp(target) && me->is_fighting(target))
       COMBAT_D->do_attack(me, target, 0, i);

   //等待解密后开
	if ( objectp(target) && me->is_fighting(target)&&me->query("quest/天龙八部/武功/quanli")){
	   message_vision(HIR"$N已然将萧峰处所悟拳理和太祖拳融会贯通，招式虽然简单，但每一招发出来却威力大增。\n"NOR,me,target);
       target->add_temp("must_be_hit",1);
	   me->add_temp("apply/damage",lvl/5);
       COMBAT_D->do_attack(me, target, 0, 3);	  
	   target->delete_temp("must_be_hit");
	   me->add_temp("apply/damage",-lvl/5);
	}
	
	if (objectp(target) && me->is_fighting(target) && me->query("quest/baduanjin/pass2"))
	{
		message_vision(HIB"$N已然将赵宋皇室心法与太祖拳融会贯通，每一招发出来皆有莫大威能。\n"NOR,me,target);
		target->add_temp("must_be_hit",1);
	   me->add_temp("apply/damage",lvl/2);
       COMBAT_D->do_attack(me, target, 0, 3);
	   COMBAT_D->do_attack(me, target, 0, 3);	   
	   target->delete_temp("must_be_hit");
	   me->add_temp("apply/damage",-lvl/2);		
	}

	
	me->add_temp("apply/attack",- lvl/j);
	me->add_temp("apply/damage", -lvl/j);
	me->add_temp("apply/cuff", -lvl/j);
	me->add_temp("apply/strength",- lvl / 3);
    me->add("jingli", -100);
    me->add("neili", -200);
	me->delete_temp("tzq/hengsao");
    me->start_busy(random(2));

	if (!me->query("quest/baduanjin/pass2")) me->start_perform(2+ random(2),"「横扫千军」");
	else
		me->start_perform(2,"「横扫千军」");

	return 1;
}


string perform_name(){ return HIR"横扫千军"NOR; }

int help(object me)
{
	write(HIR"\n太祖拳之"+HIY"「横扫千军」"NOR"\n\n");
	write(@HELP
	相传为宋太祖赵匡胤所传，故称太祖拳。太祖拳法讲究实战，攻防格斗，
	起如风，击如电，前手领，后手追，两手互换一气摧。特点为套路严谨，
	动作舒展，招式鲜明，步法灵活，刚柔相济，虚实并兼，行拳过步，长
	打短靠，爆发力强。其劲力发挥于撑、拦、斩、卡、撩、崩、塞中，“囚
	身似猫，抖身如虎，行似游龙，动如闪电”。
	
	注意：250级后效果开始衰弱，若解开天龙八部谜题并获得萧峰指点，
	则该招将再次飞跃，本招仅为普通百姓方可修得。
	要求：
		最大内力 1300 以上；
		当前内力 500  以上；
		当前精力 500  以上；
		太祖拳等级 100 以上；
		基本内功 轻功 招架 拳法 等级 100 以上；
		激发拳法为太祖拳；
		激发招架为太祖拳：
		备拳法为太祖拳且空手。

HELP
	);
	return 1;
}
