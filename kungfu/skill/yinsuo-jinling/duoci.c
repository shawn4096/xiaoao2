// juanduo.c 银索金铃 卷夺字诀
// cre by sohu@xojh 2014/9
// 源自李莫愁的拂尘技法
#include <ansi.h>


//李莫愁拂尘微挥，银丝倒转，已卷住了铁杖头，叫一声：“撒手！”借力使力，拂尘上的千万缕银丝将铁杖之力尽数借了过来。外加2掌赤练神掌。
//那老者双臂剧震，险些把持不住，危急中乘势跃起，身子在空中斜斜窜过，才将她一拂的巧劲卸开
//拂尘一扬，银丝鼓劲挺直，就似一柄花枪般向柯镇恶当胸剌去。这拂尘丝虽是柔软之物，但藉着一股巧劲，所指处又是要害大穴，这一剌之势却也颇为厉害。
//李莫愁侧身避过铁杖，拂尘扬出，银丝早将武三娘长剑卷住。两股劲力自拂尘传出，一收一放，喀的一响，长剑断为两截，剑尖刺向武三娘，剑柄却向柯镇恶脸上激射过去。
inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon;
	object ob;		
	string msg;
	int i;
	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("「横扫」只能对战斗中的对手使用。\n");
	if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "whip")
			return notify_fail("你使用的武器不对。\n");
	ob = target->query_temp("weapon");
	i=me->query_skill("yinsuo-jinling",1);
	if (me->query_skill_mapped("force")=="yunu-xinjing"&&me->query("gender")=="女性")
		i=i+me->query_skill("yunu-xinjing",1)/5;
	if (userp(target))
		i=i+me->query_skill("strike",1)/5;

	if (me->query_skill_mapped("force")!="yunu-xinjing")
		return notify_fail("你激发的内功不对，无法施展「夺刺诀」。\n");
	if (me->query_skill_mapped("whip")!="yinsuo-jinling"
		||me->query_skill_mapped("parry")!="yinsuo-jinling")
		return notify_fail("你激发的武技不对,无法施展「夺刺诀」。\n");
	if (me->query_skill_mapped("strike")!="wudu-shenzhang"
		||me->query_skill_prepared("strike")!="wudu-shenzhang")
		return notify_fail("你激发的掌法非五毒神掌,无法施展「夺刺诀」。\n");
	if( (int)me->query_skill("yinsuo-jinling", 1) < 250 )
		return notify_fail("你的银索金铃不够纯熟，还不能「夺刺诀」\n");
	if( (int)me->query_skill("whip", 1) < 250 )
		return notify_fail("你的基本鞭法不够纯熟，还不能「夺刺诀」\n");
	if(me->query_dex() < 50 )
		return notify_fail("你的后天身法不够，还不能「夺刺诀」\n");
	if( (int)me->query_skill("yunu-xinjing",1)< 250)
		return notify_fail("你的内功修为太差，劲力无法封闭穴道\n");
	if( (int)me->query_temp("ysjl/duoci"))
		return notify_fail("你的正在使用银索金铃「夺刺诀」。\n");
	if( (int)me->query("max_neili")<2500)
		return notify_fail("你的内力不足以施展「夺刺诀」功夫.\n");
	if ( (int)me->query("jingli") < 500 )
		return notify_fail("你的内力不够施展「夺刺诀」。\n");		
	if ( (int)me->query("neili") < 500 )
		return notify_fail("你的内力不够施展「夺刺诀」。\n");
	me->add("neili", - 300);
	me->add("jingli", - 100);
	if (ob)
	    message_vision(HIC"$N手中"+weapon->query("name")+HIC"微挥，鞭影倒转，已卷住了$n手中的"+ob->query("name")+HIC"，大叫一声：“撒手！”\n"+
					"然后借力使力，"+weapon->query("name")+HIC"上的柔软的鞭子将"+ob->query("name")+HIC"之力尽数借了过来。\n"NOR,me,target);
	else message_vision(HIC"$N手中"+weapon->query("name")+HIC"微挥，鞭影倒转，已卷住了$n的上臂，大叫一声：“着！”\n"NOR,me,target);
	me->set_temp("ysjl/duoci",1);
    //卷,第一招
		me->add_temp("apply/attack",i/5);
		me->add_temp("apply/damage",i/5);
		me->add_temp("apply/whip",i/5);
	
	if( random( me->query_skill("whip",1)) > target->query_skill("parry",1 )/2
		||random(me->query_dex(1))>target->query_dex(1)/2)
	{
		if (ob)
		{
			message_vision(HIY"\n\n$n只觉一股大力要将他"+ob->query("name")+HIY"夺出手去，忙运劲回夺，那知劲力刚透\n"+
							"突然$N相夺之力已不知到了何处，这一瞬间，但觉四肢百骸都是空空荡荡的无所着力。\n"NOR,me,target);
			ob->unequip();
			ob->move(environment(target));

		}
		else {
			message_vision(HIY"$n顿时为"+weapon->query("name")+HIY"缠住，身形顿时受制。\n"NOR,me,target);
			target->add_busy(2);
		}
	
	}else {
			message_vision(HIY"$n危急中乘势跃起，身子在空中斜斜窜过，才将$N一拂的巧劲卸开。\n"NOR,me,target);
			me->add_busy(1);
	}
	//第一招
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);   
	 
	 //第二招，刺
	
	 if (random( me->query_skill("whip",1)) >  target->query_skill("parry",1 )/2
		||random(me->query_dex(1))>target->query_dex(1)/2)
	 {
		 message_vision(HIR"$N"+weapon->query("name")+HIR"一扬，银丝鼓劲挺直，就似一柄花枪般向$n当胸剌去。这鞭子虽是柔软之物，\n"
						+"但藉着一股巧劲，所指处又是要害大穴，这一剌之势却也颇为厉害。\n"NOR,me,target);
		 target->receive_damage("qi",random(4000),me);
		 target->receive_wound("qi",random(1000),me);
	 }
	
	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	//第三，四招，补上2掌
	 message_vision(HIB"$N对$n轻声浅笑道，“赤练神掌拍到你胸口啦”,随后双手晃动，连续攻出两掌!\n"NOR,me,target);
	 weapon->unequip();
	 me->add_temp("apply/strike",i/4);
	 me->add_temp("apply/damage",i/6);
	 me->set_temp("wdsz/duoci",2);
	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
	 me->delete_temp("wdsz/duoci");
	 me->add_temp("apply/damage",-i/6);
	 me->add_temp("apply/strike",-i/4);
		
	 weapon->wield();
	 me->add_temp("apply/attack",-i/5);
	 me->add_temp("apply/damage",-i/5);
	 me->add_temp("apply/whip",-i/5);
	
	 me->delete_temp("ysjl/duoci");
	 me->start_perform(4,"夺刺诀");
	 me->add_busy(2);
	 return 1;
}
string perform_name(){ return HBYEL+HIR"夺刺诀"NOR; }

int help(object me)
{
	write(WHT"\n银索金铃之"HBYEL+HIR"「夺刺诀」："NOR"\n");
	write(@HELP
	银索金铃是古墓派小龙女的独门武技，乃是武功至柔
	的体现，以金铃索施展，招式精妙，变幻莫测，以攻
	敌穴道为主，索式夭矫似灵蛇，圆转如意。
	夺刺诀，乃是源自李莫愁的拂尘技法，以软鞭缠绕对
	方兵器，夺取并震段。随后，化软鞭为刺字诀，刺中
	对方。最后趁敌人手忙脚乱之际，连出两招五毒神掌
	
	perform whip.duoci
	
要求：
	当前内力要求 500 以上；
	当前精力要求 500 以上；
	最大内力要求 2500 以上
	银索金铃等级 250 以上；
	玉女心经等级 250 以上；
	基本鞭法等级 250 以上；
	有效身法等级 50  以上；
	激发鞭法为银索金铃；
	激发招架为银索金铃；
	激发掌法为五毒神掌；
	且备掌法为五毒神掌；
	手持鞭子类兵器。
HELP
	);
	return 1;
}