//lanhua.c 兰花手三式
//by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>
void next1(object me, object target, int i);
void next2(object me, object target, int i);

int perform(object me,object target)
{
	int i;
	string msg;
	object weapon,tweapon;
    weapon = me->query_temp("weapon");  
        
		if( !target ) target = offensive_target(me);
		
		tweapon = target->query_temp("weapon");  

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「兰花三式」只能对战斗中的对手使用。\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("你的内力不够使用「兰花三式」！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力不够使用「兰花三式」！\n");

        if (weapon)
                return notify_fail("你手中拿兵器，怎能使用「兰花三式」？！\n");
		//这里是兰花手技能
		if (!me->query("thd/wuji/lhs"))
				return notify_fail("你从何处偷学来的兰花手」？！\n");
	    //这里是pfm技能
     	if (!me->query("quest/thd/lhs/lanhua/pass"))
				return notify_fail("你虽然听说过，但尚未学会，怎能使用「兰花三式」？！\n");

		if (me->query_skill("hand",1)<300)
                return notify_fail("你的基本手法不足300，怎能使用「兰花三式」？！\n");
		if (me->query_skill("force",1)<300)
                return notify_fail("你的基本内功不足300，怎能使用「兰花三式」？！\n");
		if (me->query_skill("bihai-chaosheng",1)<300)
                return notify_fail("你的碧海潮生功不足300，怎能使用「兰花三式」？！\n");

		if (me->query_skill("lanhua-shou",1)<300)
                return notify_fail("你的兰花手等级不足300，怎能使用「兰花三式」？！\n");

        if ( me->query_skill_mapped("hand") != "lanhua-shou" )
             	return notify_fail("你必须先激发手法为兰花手。\n");

      //  if (me->query_temp("lhs/lanhua"))
				//return notify_fail("你正在施展兰花手中的「兰花三式」。\n");
	
	message_vision( HIG"$N将拇指与食指扣起，余下三指略张，手指如一枝兰花般伸出，姿势美妙已极，已将$n身前大穴罩住，\n"+
		"$n只觉眼前手影绚烂，正是兰花手绝技「"+HIY"兰花手落叶式"+HIG"」。\n"NOR,me,target);

	me->start_perform(4,"「兰花三式」");
	//me->set_temp("lhs/lanhua",1);
	
	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
	   || random(me->query_int())>target->query_int()/2)
	{
		
		message_vision( HIR "\n\n$n只觉一股轻柔的触摸传来，寸关穴一麻，被「"+HIY"兰花手落叶式"+CYN"」拂中。\n" NOR,me,target);
		if (tweapon)
		{
			message_vision(CYN"$n手中的"+tweapon->query("name")+CYN"把持不住，掉在地上。\n"NOR,me,target);
			tweapon->move(environment(target));
		}
		target->add_busy(1);
	}
	else {
		msg = HIW "可是$n看破了$N的企图，飞快的向后退去。\n" NOR;
		me->start_busy(1);
	}
	//落叶缤纷
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
	if (me->is_fighting()&&objectp(target))
		next1(me, target, i);
	return 1;
}

void next1(object me, object target, int i)
{
	string msg;
	int damage,lvl;
	object weapon;

	if (!me) return ;
	weapon = me->query_temp("weapon");
	if (weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("lhs/lanhua");
		return ;
	}
	message_vision( YEL"\n$N将姆指、食指、无名指，弯弯地朝上翘着，一抬一式，无不清雅曼妙,倏然间转向$n的身后！\n"+
		"正是桃花岛绝技「"+HIM"兰花手蝶舞式"+YEL"」!\n" NOR,me,target);
	if(random(me->query("combat_exp"))>target->query("combat_exp")/2
		||random(me->query_skill("lanhua-shou",1))> target->query_skill("dodge",1)/2 )
	{
		message_vision(RED"$n被「"+HIM"兰花手蝶舞式"+RED"」连续拂中了$n身后督脉诸穴，战力大减！。\n"NOR,me,target);
		damage = me->query_skill("lanhua-shou",1)+me->query_skill("force",1);
		damage += me->query_skill("hand",1);
		damage=damage*me->query_dex()/20;
		damage += random(damage);
		
		target->add("neili",-(1000+random(500)));
		if (target->query("neili")<0) target->set("neili",0);
		
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		if (wizardp(me)) write("damage2="+damage);
	    
		msg = damage_msg(damage, "震伤");
		//msg = replace_string(msg, "$w", weapon->query("name"));
		msg = replace_string(msg, "$l", "前胸");
		
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-300);
		me->add("jingli",-100);
		//虚弱
		lvl=me->query_skill("lanhua-shou",1);
		if (!target->query_temp("lhs/diewu"))
		{
		
			target->set_temp("lhs/diewu",lvl);
			target->add_temp("apply/dexerity",-lvl/20);
			target->add_temp("apply/strength",-lvl/20);
			target->add_temp("apply/constitution",-lvl/20);
			target->add_temp("apply/intelligence",-lvl/20);
			if (objectp(target))
				call_out("remove_diewu",(int)lvl/30,target);
		}
	} else {
		msg  =  CYN"$n凭借灵巧的身法躲开了这一招。\n"NOR;
		message_vision(msg, me, target);
		me->start_busy(1+random(2));
		target->start_busy(1+random(2));
	}
	if (me->is_fighting()&&objectp(target))
		next2(me, target, i);
	return;

}

void next2(object me, object target, int i)
{
	string msg;
	int damage;
	object weapon;

	if( !me ) return ;

	weapon = me->query_temp("weapon");
	if (weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("lhs/lanhua");
		return ;
	}
	message_vision(HBCYN "\n$N的小指就可以对准敌人的合谷穴，无名指对准阳池穴，中指对准阳谷穴，食指对准腕骨穴，姆指对准内关穴肩。\n"+
	"正是桃花岛绝技「"+HIR"兰花手擒拿式"+HBCYN"」\n"NOR,me,target);

	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
		||random(me->query_str()) >target->query_dex()/3)
	{
		message_vision(HIC"$n被「"+HIR"兰花手擒拿式"+CYN"」拂中了「"HIR+"合谷穴"+HIC+"」，$n全身酸麻，武功的特殊威力无法施展出来。\n" NOR,me,target);

		damage = me->query_skill("lanhua-shou",1)+me->query_skill("force",1);
		damage += me->query_skill("hand",1);
		damage=damage*me->query_str()/20;
		damage += random(damage);
		
		if (!target->query_temp("lhs/qinna"))
		{
			target->add_temp("apply/attack", -200);
			target->add_temp("apply/dodge", -200);
			target->add_temp("apply/parry", -200);
			target->set_temp("lhs/qinna",1);
			if (objectp(target))
				call_out("back", 5+random(5), target);

		}
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		target->receive_wound("jing",damage/6,me);
		
		if (wizardp(me)) write("damage3="+damage);

		msg = damage_msg(damage, "内伤");
		//msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "手臂");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-300);
		me->add("jingli",-150);
	} else {
		msg = msg + HIW "$n运起轻功，向前一跃，躲开一旁。\n" NOR;
		message_vision(msg, me, target);
		me->start_busy(1 + random(2));
		target->start_busy(1+random(2));
	}
	me->delete_temp("lhs/lanhua");
	me->start_perform(4,"「兰花三式」");
	return;
}
/*
//蝶舞恢复
void remove_diewu(object target)
{
	int lvl;
	if (!target) return;
	lvl=target->query_temp("lhs/diewu");
	target->add_temp("apply/dexerity",-lvl/20);
    target->add_temp("apply/strength",-lvl/20);
    target->add_temp("apply/constitution",-lvl/20);
    target->add_temp("apply/intelligence",-lvl/20);
	target->delete_temp("lhs/diewu");
	return;
}
//擒拿恢复

void back(object target)
{
	if (!target) return;
	target->add_temp("apply/attack", 200);
	target->add_temp("apply/dodge", 200);
	target->add_temp("apply/parry", 200);
	target->delete_temp("lhs/qinna");
	return;
}
*/
string perform_name(){ return HBCYN+HIG"兰花三式"NOR; }

int help(object me)
{
   write(WHT"\n兰花手之「"HBCYN+HIG"兰花三式"WHT"」："NOR"\n");
   write(@HELP
	兰花三式是将桃花岛家传武学兰花手的精要武学「落叶式」
	「蝶舞式」、「擒拿式」三式集中一起施展，乃是兰花手的
	的最大威力集成招式。反馈了兰花手“快、准、奇、清”的特
	点。实乃桃花岛武学的精粹，女性玩家有优势。
	
	落叶式：以手法伤敌，打掉对方兵器
	蝶舞式：虚弱对方先天属性，极为阴险毒辣
	擒拿式：专门选择对方的麻穴下手，破对方防御	

指令：perform hand.lanhua

要求：
	当前内力 1000 以上；
	当前精力 1000 以上；
	兰花手法 300 以上；
	基本手法 300 以上；
	基本内功 300 以上；
	碧海潮生 300 以上；
	激发手法为兰花手；
	激发招架为兰花手或弹指神通
	空手不能持有武器；

HELP
   );
   return 1;
}
