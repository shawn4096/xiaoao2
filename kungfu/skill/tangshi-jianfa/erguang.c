//erguang.c 耳光式
// By Spiderii
// add shenzhao 3 by sohu
#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
	int j, lvl = me->query_skill("tangshi-jianfa", 1);
    if (me->query_skill("shenzhao-jing",1)>349)
       lvl = me->query_skill("tangshi-jianfa", 1)+me->query_skill("shenzhao-jing", 1);
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("「耳光式」只能对战斗中的对手使用。\n");

	
   if( (int)me->query_skill("tangshi-jianfa", 1) < 250 )
		return notify_fail("你的躺尸剑法功力太浅，别做梦了。\n");

   if( (int)me->query_skill("sword", 1) < 250 )
		return notify_fail("你的基本剑法功力太浅，别做梦了。\n");


   if( (int)me->query("max_neili") < 3500 )
		return notify_fail("你的内力太浅，别做梦了。\n");

	if( (int)me->query("neili") < 1000 )
		return notify_fail("你的真气不够，别做梦了。\n");
	
	if( target->is_busy() )
		return notify_fail("对方已经手忙脚乱了，赶紧进攻吧。\n");

	
	if( !objectp(weapon = me->query_temp("weapon"))
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("sword") != "tangshi-jianfa" )
		return notify_fail("你使得了「耳光式」么?\n");
    
	me->set_temp("tangshi/erguang",1);
	j = lvl/3;

	if ( lvl > 349 )
		j = to_int(lvl/3.0 * lvl/200.0);
    //msg = HIY "只见$N手中兵器由右手快速交换到左手，右手以意想不到的方位挥向$n的脸颊。\n"NOR;
    message_vision(HIY "只见$N手中兵器由右手快速交换到左手，右手以意想不到的方位挥向$n的脸颊。\n"NOR, me, target);
    if (random(me->query("combat_exp")) > target->query("combat_exp")/3
		||random(me->query_skill("sword",1))>target->query_skill("parry",1)/2 )
	 {
        message_vision(CYN"$n只觉得脸上一阵火辣辣的生痛，已被$N响亮的打了一耳光！\n"NOR, me, target);
		if( !target->is_busy() ) target->start_busy( (int)me->query_skill("tangshi-jianfa") / 100 );
        else target->add_busy( (int)me->query_skill("tangshi-jianfa") / 100 );
		damage = (int)me->query_skill("tangshi-jianfa", 1);
		damage = damage +  (int)me->query_skill("tangshi-jianfa", 1);
		damage = damage +  (int)me->query_skill("sword", 1);
		damage = damage*2+random(damage);
		if (me->query("quest/shenzhao/laozu")) damage = damage + 2*me->query_skill("shenzhao-jing",1);
		if (damage>5000) damage=damage+(damage-5000)/100;
		target->receive_damage("qi", damage/2,me);
		target->receive_damage("jing",random(1000),me);
		target->receive_wound("qi", damage/50,me);
		target->apply_condition("neishang",2);
		me->add("neili", -100);
		//msg = CYN"$n只觉只觉得脸上一正火辣辣的生痛，已被$N响亮的打了一耳光！\n"NOR;		
		target->add_busy(2);
		if (me->query_skill("tangshi-jianfa",1)>450) target->add_busy(1);
        if (me->query("quest/shenzhao/diyun")) target->add_busy(1+random(1));
		if (me->query("quest/shenzhao/laozu")) target->add_busy(2+random(1));
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		//if (me->query_skill("tangshi-jianfa",1)<450) me->start_busy(2);
	} else 
	{
		//msg = CYN"可是$p身形一侧,躲过了$P的掌风。\n"NOR;
		message_vision(CYN"可是$p身形一侧,躲过了$P的掌风。\n"NOR, me, target);
		me->add("neili", -100);
		me->start_busy(2);
	}
	me->delete_temp("tangshi/erguang");	
	if (me->query_skill("tangshi-jianfa",1)<450)
	{
		me->start_busy(1+random(2));
	}
	me->add("neili", -300);
	me->add("jingli", -100);
	if (!me->query("quest/shenzhao/diyun")) me->start_perform(2, "「耳光式」");
	// 解开神照2，大飞
	return 1;
	
}

string perform_name(){ return HIR"耳光式"NOR; }

int help(object me)
{
        write(HIC"\n躺尸剑法之「耳光式」："NOR"\n\n");
        write(@HELP
	“躺尸剑法”乃是金庸十四部武侠巨著中《连城诀》的著名武功
	主要是由反面角色“铁索横江”戚长发精研的一种剑术，他为了
	掩人耳目，把《唐诗剑法》蓄意讹传为“躺尸剑法”，其中的种
	种招数名称也改成谐音字或同声异形字，他曾把该剑术传给小
	说的主人公狄云。由此，以讹传讹,实乃滑天下之大稽。
	耳光式乃是源自言达平指导狄云中极为精妙的一招，借用剑光
	影响，以迅雷不及掩耳之式打对方一个耳光，使得对手陷入忙
	乱之中。解开神照经第二段后此招大飞。
	
	指令：perform sword.erguang

要求：　
	当前内力 1000 以上；
	最大内力 3500 以上；
	躺尸剑法等级 250 以上；
	基本剑法等级 250 以上；
	激发剑法为躺尸剑法。

HELP
        );
        return 1;
}
