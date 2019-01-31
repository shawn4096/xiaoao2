// by darken@SJ
// Modify By River@SJ 2001.6.18

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
int mulan_attack(object me,object target);

string perform_name(){ return HIC"玉女剑"NOR; }

//抚琴按萧扫雪烹茶松下对弈池边调鹤西窗夜话柳荫联句竹帘临池锦笔生花
int perform(object me, object target)
{
        string msg;
		int skill = me->query_skill("yunu-jianfa", 1);
        object weapon = me->query_temp("weapon");  
        

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「玉女剑」只能对战斗中的对手使用。\n");

        if( me->query_skill("force", 1) < 300 )
                return notify_fail("你的内功火候未到，无法施展「玉女剑」！\n");
		if( me->query_skill("yunu-xinjing", 1) < 300 )
                return notify_fail("你的玉女心经火候未到，无法施展「玉女剑」！\n");

        if( me->query_skill("dodge",1) < 300 )
                return notify_fail("「玉女剑」需轻功配合，方能施展！\n");

        if( me->query_skill("sword",1) < 300 )
                return notify_fail("你基本剑法火候未足，无法使用「玉女剑」！\n");

        if( me->query("neili") < 1000 )
                return notify_fail("你的内力不够使用「玉女剑」！\n");
		if( me->query("gender") =="无性" )
                return notify_fail("你阴阳不调，无法施展使用「玉女剑」！\n");
        if( me->query("jingli") < 500 )
                return notify_fail("你的精力不够使用「玉女剑」！\n");
        if (me->query_temp("ynjf/yunu"))
        		return notify_fail("你正在使用「玉女剑」！\n");
        
		if( me->query_skill_mapped("force") !="yunu-xinjing")
                return notify_fail("你激发的内功不对，无法使用「玉女剑」绝技。\n"); 

        if (!weapon 
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "yunu-jianfa"
		 || me->query_skill_mapped("parry") != "yunu-jianfa" )
                return notify_fail("你手中无剑怎能使用「玉女剑」？！\n");

        msg = HIW"\n$N手中剑略前挺，剑尖颤动，似左实右刺敌,随后一声清啸，使出「玉女剑势」，剑尖分成数点，刺向$n！\n" NOR;
       		
		if (me->query("family/family_name")=="古墓派" 
			&& me->query_per()>28 
			&& me->query_skill("yunu-jianfa",1)>350
			&& me->query("gender")=="女性")
		{
			 msg += HIM"\n$N剑招精妙凌厉,剑式轻柔灵动,使用时身形清雅潇洒,姿态飘飘若仙,三分飘逸风姿,韵姿佳妙之态！\n" NOR;
			 if (userp(target))
				target->add_busy(1+random(3));
			 else target->add_busy(3+random(1));
			 skill=skill+me->query_skill("yunu-xinjing",1)/4;
		}
		message_vision(msg , me, target);
        
		me->set_temp("ynjf/yunu",4);

		me->add_temp("apply/attack", skill/3 );
        me->add_temp("apply/damage", skill/4 );
        me->add_temp("apply/sword", skill/5 );
		me->add("neili", -300);
        me->add("jingli", -100);
		
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		me->add_temp("ynjf/yunu",-1);
        if (me->is_fighting() && objectp(target))
		{
      		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			me->add_temp("ynjf/yunu",-1);
			//解开木兰组合，则会趁对方busy反击
			if ( me->query("quest/gumu/ynjf/mulan/pass")
				&& me->query_skill("yunu-jianfa",1)>400
				&& me->query_skill_mapped("dodge")=="yunu-shenfa")
			{
				message_vision(YEL"$N玉女身法运使如行云流水，在辗转腾挪之际，见$n恰处于手忙脚乱状态有机可乘。\n"
				+"趁机向前急纵，暗自准备「木兰回射」的招式。\n"NOR,me,target);
				call_out("mulan_attack",1,me,target);
			}
		}
		if (me->is_fighting() && objectp(target))
		{
      		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
			me->add_temp("ynjf/yunu",-1);
		}
		if (me->is_fighting() && objectp(target))
		{
      		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
			me->add_temp("ynjf/yunu",-1);
		}
        me->delete_temp("ynjf/yunu");
		me->add_temp("apply/attack", -skill/3 );
        me->add_temp("apply/damage", -skill/4 );
		me->add_temp("apply/sword", -skill/5 );
		me->start_perform(4,"「玉女剑」");

        return 1; 
}

int mulan_attack(object me,object target)
{
	object weapon;
	int i,damage;
	if (!me||!objectp(target)) return 0;
	weapon=me->query_temp("weapon");
	if (!weapon) return 0;

	i=(int)me->query_skill("yunu-jianfa",1);
	damage=(i*5+me->query_skill("sword",1))*me->query_per();

	message_vision(HIR"\n$N纵身前跃，奔跑之际，将手中的"+weapon->query("name")+HIR"突然挺剑向背后刺出攻向$n的胸口！\n"NOR, me,target);
    message_vision(HIR"\n正是玉女剑法中一招"HIC"「木兰回射」"HIR"绝技！\n"NOR, me,target);
	me->add("neili", -100);
    me->add("jingli",-50);
	
	if (random(me->query("combat_exp"))>target->query("combat_exp")/2
		|| random(me->query_dex(1))>target->query_dex(1)/2)
    {  
	    message_vision(HIY"\n\n$n正追赶之际，被$N这招「木兰回射」一剑刺中胸口，鲜血迸溅！\n"NOR,me,target);
		if (userp(target))
		{		
			target->receive_damage("qi",3000+random(1000),me);
			target->receive_wound("qi",1000+random(500),me);
		}
		else {
			target->receive_damage("qi",4000+random(2000),me);
			target->receive_wound("qi",2000+random(1000),me);
		}
		target->apply_condition("no_exert",1);
		if (!userp(target)) target->add_busy(2);
		
		me->add_temp("apply/damage",i);
		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if (me->query_skill("yunu-jianfa",1)>200 && me->is_fighting())
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/damage",-i);
	            	
    }else
	{
		message_vision(HIC"\n\n$n脚下急忙后退，堪堪躲过此招，吓了一声冷汗。\n"NOR,me,target);
		me->add_busy(1);
	}
	return 1;	

}

int help(object me)
{
        write(HIG"\n玉女剑法之"+HIW"「玉女剑」："NOR"\n\n");
        write(@HELP
	玉女剑法乃是古墓派绝技剑法,剑招精妙凌厉,剑式轻柔灵动,
	使用时身形清雅潇洒,姿态飘飘若仙,带著三分飘逸风姿,以韵
	姿佳妙取胜.
	玉女剑是将剑法中较为突出的四招集中起来，供古墓弟子使用
	是初期重要的入门武技。女性使用比男性有明显的优势。
	提示：若机缘巧合且悟性较高，可以将此招和木兰回射有效组
	合，形成更强的攻击效果,玉女剑法需400级以上。
	玉女身法对此招有极大辅助作用，古墓弟子切记。
	
	perform sword.yunu

要求：
	当前内力要求 1000 以上；
	当前精力要求 500 以上；
	玉女剑法等级 300 以上；
	玉女心经等级 300 以上；
	基本剑法等级 300 以上；
	基本轻功等级 300 以上；
	激发剑法为玉女剑法；
	激发招架为玉女剑法；
	激发内功为玉女心经。
	需手持剑类武器。
HELP
        );
        return 1;
}
