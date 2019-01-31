//cijian.c
//by spiderii@ty参照SJ编写

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
	int j, lvl = me->query_skill("tangshi-jianfa", 1);
    if (me->query_skill("shenzhao-jing",1)>349)
       lvl = me->query_skill("tangshi-jianfa", 1)+me->query_skill("shenzhao-jing", 1)/2;
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("「刺肩式」只能对战斗中的对手使用。\n");

	
    if( (int)me->query_skill("tangshi-jianfa", 1) < 180 ) 
                return notify_fail("你的躺尸剑法还未练成，无法使用「刺肩」字诀！\n");

    if((int)me->query_skill("sword", 1) < 180 )
                return notify_fail("你的基本剑法不够娴熟，不能使用「刺肩」字诀！\n");

    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "tangshi-jianfa")
                return notify_fail("你必须使用剑法，才能使出「刺肩」字诀!\n");

  // if(me->query_skill_mapped("parry") != "tangshi-jianfa")
    //       return notify_fail("「刺肩」字诀需要使用躺尸剑法招架一切敌方攻击。\n"); 

   if((int)me->query("max_neili") < 3000 )
           return notify_fail("你内力修为尚浅，使不出「刺肩」字诀。\n");  

   if( (int)me->query("neili") < 1000 )
           return notify_fail("你现在真气太弱，使不出「刺肩」字诀。\n");
	
   message_vision(HIY"\n$N轻轻念道：“左肩，右肩，左肩，右肩...”,剑光飘忽，在$n双肩方位不断闪烁！\n"NOR, me,target);
  
   j=lvl+random(lvl);
   if (me->query("quest/shenzhao/diyun") && me->query_temp("szj_power"))
	{
     message_vision(HIM"\n$N按照从狄云处领悟的神照经要领，运用到躺尸剑法之上，威力倍增。\n"NOR, me,target);
	 j=lvl+2*lvl;
	}
   if (!userp(me)) j=lvl/3;
     damage=j;
  
   if (random(me->query("combat_exp")) > target->query("combat_exp")/3 )
	{
        		   
		   target->receive_damage("qi",j,me);
		   target->receive_wound("qi", j/2,me);
		   target->receive_damage("jing", j/10,me);
		   me->add("neili", -100);
		message_vision(HIR"$n只觉"+random(2)?HIG"左肩"NOR:HIY"右肩"NOR+HIR"一阵剧烈刺痛，鲜血飞溅，身形不由得为之一慢！\n"NOR,me,target);  
		if( !target->is_busy()&& !random(2) ) target->start_busy(2);
        if (me->query("quest/shenzhao/laozu"))
        {
			target->apply_condition("no_perform",1);
        }
		//message_vision(msg, me, target);
   	    me->set_temp("tangshi/cijian",3);
        me->add_temp("apply/attack", j);
        me->add_temp("apply/damage", j);
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		//COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        me->add_temp("apply/attack", -j);
	    me->add_temp("apply/damage", -j);
	} else 
	{
		//msg = CYN"可是$n身形一侧,躲过了$N的攻击。\n"NOR;
		message_vision(CYN"可是$n身形一侧,躲过了$N的攻击。\n"NOR, me, target);
		me->add("neili", -100);
		me->start_busy(3);
	}
	
    me->delete_temp("tangshi/cijian");
	me->start_busy(random(2));
	me->add("neili", -300);
	me->add("jingli", -100);
	me->start_perform(2, "「刺肩式」");
	return 1;
}

string perform_name(){ return HIW"刺肩式"NOR; }

int help(object me)
{
        write(HIC"\n躺尸剑法之「刺肩式」："NOR"\n\n");
        write(@HELP
	“躺尸剑法”乃是金庸十四部武侠巨著中《连城诀》的著名武功
	主要是由反面角色“铁索横江”戚长发精研的一种剑术，他为了
	掩人耳目，把《唐诗剑法》蓄意讹传为“躺尸剑法”，其中的种
	种招数名称也改成谐音字或同声异形字，他曾把该剑术传给小
	说的主人公狄云。由此，以讹传讹,实乃滑天下之大稽。
	刺肩式乃是源自言达平指导狄云中极为精妙的一招，借用剑光
	影响，以迅雷不及掩耳之式刺中对方的肩部，对对方形成强大
	杀伤。解开神照经第二段后此招大飞。
	
	指令：perform sword.cijian

要求：　
	当前内力 3000 以上；
	最大内力 1000 以上；
	躺尸剑法等级 180 以上；
	基本剑法等级 180 以上；
	激发招架为躺尸剑法。

HELP
        );
        return 1;
}
