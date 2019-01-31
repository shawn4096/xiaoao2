//tangshi.c  正宗唐诗剑法
//by sohu@xojh参照连城诀编写


#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon, weapon2;
	int i,j,l, lvl = me->query_skill("tangshi-jianfa", 1);
    if (me->query_skill("shenzhao-jing",1)>349)
    lvl = me->query_skill("tangshi-jianfa", 1)+me->query_skill("shenzhao-jing", 1)/2;
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("「唐诗剑法」只能对战斗中的对手使用。\n");
    if(me->query("tangshi/ts")!="pass") 
                return notify_fail("你对唐诗剑法的奥秘一窍不通，尚使用不了唐诗剑法！\n");
	
    if( (int)me->query_skill("tangshi-jianfa", 1) < 350 ) 
                return notify_fail("你的唐诗剑法还未练成，无法使用「去肩」字诀！\n");

    if((int)me->query_skill("sword", 1) < 350 )
                return notify_fail("你的基本剑法不够娴熟，不能使用「去肩」字诀！\n");

    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "tangshi-jianfa")
                return notify_fail("你必须使用剑器，才能使出「唐诗剑法」!\n");
  
   if(me->query_skill_mapped("parry") != "tangshi-jianfa")
           return notify_fail("「唐诗剑法」需要使用唐诗剑法招架一切敌方攻击。\n"); 

   if((int)me->query("max_neili") < 5000 )
           return notify_fail("你内力修为尚浅，使不出「唐诗剑法」字诀。\n");  

   if( (int)me->query("neili") < 1500 )
           return notify_fail("你现在真气太弱，使不出「唐诗剑法」字诀。\n");

       l=(int)me->query("int")/10+(int)me->query_skill("literate",1)/60;
	   
	   if (l>6) l=6;
	
	   j = lvl/2;
	   me->set_temp("tangshi/shiyin",1);
       message_vision(HIC"$N的剑势忽然一变，浩荡飘渺，古意盎然，大开大合，正是连城诀中正宗的「唐诗剑法」绝技!\n"NOR,me,target);
	   me->add_temp("apply/sword", j);
       me->add_temp("apply/attack", j);
       me->add_temp("apply/damage", j/2);
	
	for( i = 0; i <=l; i ++ ) 
	  {
       
            // me->add_temp("apply/damage",(int)me->query_skill("tangshi-jianfa",1)/4);
			 if (objectp(target)&& me->is_fighting(target))
                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            // me->add_temp("apply/damage",-(int)me->query_skill("tangshi-jianfa",1)/4);
      }
    
	me->add_temp("apply/sword", -j);
    me->add_temp("apply/attack", -j);
	me->add_temp("apply/damage", -j/2);
    //call_out("check",1,me);
	me->delete_temp("tangshi/shiyin");

	me->start_busy(random(2));
	me->add("neili", -300);
	me->add("jingli", -100);
	me->start_perform(5, "「唐诗剑法」");
	return 1;
}

string perform_name(){ return HIG"唐诗剑法"NOR; }

int help(object me)
{
        write(HIC"\n躺尸剑法之「唐诗剑法」："NOR"\n\n");
        write(@HELP
	 “躺尸剑法”乃是金庸十四部武侠巨著中《连城诀》的著名武功
	主要是由反面角色“铁索横江”戚长发精研的一种剑术，他为了
	掩人耳目，把《唐诗剑法》蓄意讹传为“躺尸剑法”，其中的种
	种招数名称也改成谐音字或同声异形字，他曾把该剑术传给小
	说的主人公狄云。由此，以讹传讹,实乃滑天下之大稽。
	唐诗剑法绝技是还原真实的唐诗剑法招式，堂堂正正，大开大
	合，乃是极为厉害的一门武技。
	
	指令：perform sword.tangshi
			
要求：　
	当前内力 5000 以上；
	最大内力 1500 以上；
	躺尸剑法等级 350 以上；
	基本剑法等级 350 以上；
	激发招架为唐诗剑法。

HELP
        );
        return 1;
}
