// honglian.c  火焰刀 [红莲火]
//2006年12月24日KinGSo新编辑,添加HELP

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string perform_name(){ return HBYEL+HIR"红莲火"NOR; }
int check_fight(object me);

int perform(object me, object target)
{
    int i,y,j,c;
          
      
    if( objectp(me->query_temp("weapon")) )
		return notify_fail("「红莲火」只能空手使用。\n");
     
	if( !target ) target = offensive_target(me);

    if( !target 
         || !me->is_fighting(target)
         || !objectp(target)
         || environment(target)!= environment(me))
		return notify_fail("「红莲火」只能在战斗中对对手使用。\n");
        
	if((int)me->query_skill("huoyan-dao",1) < 450)
		return notify_fail("你的火焰刀修为不够， 目前不能使用「「红莲火」」! \n");

	if((int)me->query_skill("longxiang-boruo",1) < 450)
		return notify_fail("你的龙象般若功修为不够， 目前不能使用「红莲火」! \n");
	if((int)me->query_skill("force",1) < 450)
		return notify_fail("你的龙象般若功修为不够， 目前不能使用「红莲火」! \n");

	if( me->query_skill_mapped("strike") != "huoyan-dao")
		return notify_fail("你必须使用火焰刀，才能使用「红莲火」的绝技！\n");

	
	if( (int)me->query("max_neili") < 9000 )
		return notify_fail("你的内力修为不够！\n");
	if((int)me->query("neili")<2500)
		return notify_fail("你的真气不够！\n"); 
	if((int)me->query("jingli")<1000)
		return notify_fail("你的精力不够！\n"); 

    message_vision(RED "只见$N神色肃然，手结"HIW"莲花合掌印"RED"，突然一招"HIR"「红莲火」"RED"迅捷无比地攻向$n！\n"NOR,me, target);
    i = (int)me->query_skill("huoyan-dao", 1);
    y = (int)target->query_skill("parry", 1);
    
    //me->add_temp("apply/strength", i/20);
    me->add_temp("apply/attack", i/2);
    me->add_temp("apply/damage", i/5);
	me->set_temp("hyd/honglian/power",4);
	//若有刀气，则威力增加
    if(me->query_temp("hyd/power"))
	{
       message_vision(HIM "$N猛喝一声,结合刀气绝技将"HIR"「红莲火」"HIM"威力施展到极致，$n完全被$N的刀气所摄！\n"NOR,me, target); 
       me->set_temp("hyd/honglian/power",3);
       target->start_busy(1+random(2));
    }
    
	COMBAT_D->do_attack(me, target, 0, random(2)?1:3); //第一招

	if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, i>350?3:1); //第二招

	if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, i>450?3:1); //第三招

	if ( me->is_fighting(target) &&me->query_temp("hyd/power")&& me->query_skill("huoyan-dao",1)>449)
	{
           me->add_temp("apply/attack",i/3);
		   me->add_temp("apply/damage",i/5);
		   COMBAT_D->do_attack(me, target, 0, 3); //第四招,和踢沙相当
		   me->add_temp("apply/attack",-i/3);
		   me->add_temp("apply/damage",-i/5);
	}
/*
	if ( me->is_fighting(target) &&me->query_temp("hyd/power") && me->query_skill("huoyan-dao",1)>449 )
           COMBAT_D->do_attack(me, target,0, 3); //第五招
    if ( me->is_fighting(target) &&me->query_temp("hyd/power") 
    && me->query_skill("huoyan-dao",1) >549 
    && me->query_skill("longxiang-boruo",1) >549
    && me->query_temp("xs/longxiang"))
           COMBAT_D->do_attack(me, target,0, 3); //第六招，550级后大飞*/
                    
     me->delete_temp("hyd/honglian/power");
     me->add("jingli", -100*(1+random(2)));
     me->add("neili", -100*(2+random(2)));
     
    // me->add_temp("apply/strength", -i/20);
     me->add_temp("apply/attack", -i/2);
     me->add_temp("apply/damage", -i/5);
     me->start_perform(4,"「红莲火」");         
     return 1;
                 
}

int help(object me)
{
	write(HIR"\n火焰刀秘技「红莲火」："NOR"\n");
	write(@HELP
	火焰刀红莲火绝技,能在战斗中能够迅捷的连击对方。
	如能配合绝招刀气施展，威力将得到倍增，从而克敌制胜，
	到龙象般若功达致大成，在战斗中运用龙象之力更是能够
	君临天下无往不利。350级有飞跃,450级再次飞跃。
	
	指令：perform strike.honglian

要求：
	最大内力要求 9000 以上；
	当前内力要求 2500 以上；
	当前精力要求 1000 以上；
	龙象般若功   450 以上；
	火焰刀等级   450 以上；
	基本内功等级 450 以上；    
HELP
	);
	return 1;
 }


