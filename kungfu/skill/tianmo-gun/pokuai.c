// pokuai.c 连续五击 ，以快破快
// cre by sohu@xojh
// dueto 但一看使棍人形的姿式，便即明白：“这不是五条棍子，是他在一刹那间连续击出五棍，分取对方下盘五处。

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HIW"以快破快"NOR; }
int perform(object me,object target)
{
    object weapon;
    int i,j,lev,jiali;
    
    if( !target ) target = offensive_target(me);
     
    if( !userp(me) && userp(target) )
                return notify_fail("「以快破快」只能由玩家使用。\n");
    if (me->query("quest/hmy/tmgf/jueji")!="pass")
	            return notify_fail("你尚未融会贯通，不能使用以天魔棍法之快破快绝技！\n");
    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("「以快破快」只能对战斗中的对手使用。\n");

     if (me->query_skill_mapped("force") != "tianmo-gong" && me->query_skill_mapped("force") != "xixing-dafa" )
             return notify_fail("你所使用的特殊内功不对。\n");  

     if(me->query_skill("xixing-dafa", 1)<450)
          if(me->query_skill("tianmo-gong", 1) < 450)
                return notify_fail("以你现在的内功修为还使不出「以快破快」。\n");  

    if( (int)me->query_skill("tianmo-gun", 1) < 450 ) 
                return notify_fail("你的日月天魔棍还未练成，无法使用「以快破快」！\n");

    if((int)me->query_skill("club", 1) < 450 )
                return notify_fail("你的基本棍法不够娴熟，不能使用「以快破快」！\n");

    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "club"
        || me->query_skill_mapped("club") != "tianmo-gun")
                return notify_fail("你必须使用棍法，才能使出「以快破快」!\n");
                
   if((int)me->query_str() < 60)
           return notify_fail("你的膂力还不够强劲，使不出「以快破快」绝技。\n");

   if(me->query_skill_mapped("parry") != "tianmo-gun")
           return notify_fail("「以快破快」需要使用天魔棍招架。\n"); 

   if((int)me->query("max_neili") < 10000 )
           return notify_fail("你内力修为尚浅，使不出「以快破快」。\n");  

   if( (int)me->query("neili") < 6000 )
           return notify_fail("你现在真气太弱，使不出「以快破快」。\n");

    message_vision(HIW"\n$N将手中"+weapon->name()+HIW+"急速挥舞，形成五条棍影，连续五击，分击$n下盘五个不同部位，\n"+
	   "$n只觉"+weapon->name()+HIW+"棍风凛冽，劲气弥漫，正是天魔棍以快破快的法门。\n"NOR, me, target);

    lev = (int)me->query_skill("tianmo-gun",1);
//注意和吸星大法配合
    if( me->query_temp("xxdf/powerup") ) {           
           lev += (int)me->query_skill("xixing-dafa",1)/2;
    }     
   
        me->set_temp("tmgf/pokuai", 1);
        jiali = ((int)me->query("str",1)/2 + (int)me->query("con",1))/2 + (int)me->query("jiali")/20 ;
        
		me->add_temp("apply/damage",  lev/5);
        me->add_temp("apply/attack",  lev/3);
        me->add_temp("apply/strength", jiali);
       
		message_vision(HIC"$N这五招专攻$n的下盘，都是攻向$n所必救的方位，而$N均以巧妙无伦、狠辣之极的招数破去，$n越看越心惊。\n"NOR,me,target);
		target->add_busy(1+random(2));
        
		for (i=0;i<6;i++){
          j = i;
          if (i<1) j = 1;
          if (i>1) j = 3;
		  if (!random(4)&&me->is_fighting(target)){
		       message_vision(HIY"$n面对$N狂风暴雨般的进攻，宛如陷入泥潭般的难以自拔,胸口如压重石，气机运行滞缓。\n"NOR,me,target);
			   target->apply_condition("no_exert",1);
		  }
		  if (me->is_fighting(target))
		      COMBAT_D->do_attack(me, target, me->query_temp("weapon"),j);
          me->add("neili", -100);  
        }
   
        me->add("neili", -200);
        me->add_temp("apply/damage",  -lev/5);
        me->add_temp("apply/attack",  -lev/3);
        me->add_temp("apply/strength", -jiali);

        me->delete_temp("tmgf/pokuai");
		me->start_perform(4,"「以快破快」");
        return 1;
}

int help(object me)
{
	write(HIW"\n天魔棍法之「以快破快」："NOR"\n");
	write(@HELP
	天魔棍乃是日月神教十大神魔之”金猿神魔“张乘风和”白猴神魔“张乘云
	兄弟二人所创棍法，威震江湖。后来十长老围攻华山后下落不明，使得
	这门绝技从此失传。不过有人听说在华山后山石洞发现过天魔棍招式。
	具体情况有待于玩家自己探索。
	天下武功，唯快不破，以快破快正是天魔棍法克制轻兵器的不二法门。
	尤其是针对剑法有额外的克制功效。
	
	指令：perform club.pokuai

要求：
	最大内力 10000 以上；
	当前内力 6000 以上；
	日月天魔棍等级 450 以上；
	天魔功或吸星大法等级 450 以上；
	最小臂力不小于60；
	激发招架为日月天魔棍；
HELP
	);
	return 1;
}
