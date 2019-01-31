// shu.c 日月鞭法「束缚诀」
// 
#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	string msg;
	object weapon = me->query_temp("weapon");
	int busy,skill;
	skill=me->query_skill("riyue-bian",1);
	if( !target ) target = offensive_target(me);

        if( !objectp(target)
	  ||!target->is_character()
	  ||!me->is_fighting(target) )
		return notify_fail("牵制攻击只能对战斗中的对手使用。\n");

	if( (int)me->query_skill("yijin-jing", 1) < 250 )
		return notify_fail("你的易筋经内功等级不够，不能使用「束缚诀」诀。\n");

	if( (int)me->query_skill("riyue-bian", 1) < 250 )
		return notify_fail("你的日月鞭法不够娴熟，不会使用「束缚诀」诀。\n");

	if (!weapon
	 || weapon->query("skill_type") != "whip"
	 || me->query_skill_mapped("whip") != "riyue-bian"
	 || me->query_skill_mapped("parry") != "riyue-bian")
		return notify_fail("你现在无法使用牵制攻击。\n");

	if( (int)me->query("neili") < 500 )
		return notify_fail("你现在内力太弱，不能使用「束缚诀」诀。\n");

	if( target->is_busy())
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

	//me->start_perform(4, "「束缚诀」"); 

	message_vision(HIY"$N使出日月鞭法「束缚诀」，连挥数鞭，散下满天鞭网，企图把$n的全身缠绕起来。\n"NOR,me,target);
	message_vision(HIY "$N手中"+weapon->query("name")+"似缓实急，却又无半点风声，如鬼似魅，说不尽的诡异。\n"NOR,me,target);

	me->add("neili", -350);
	me->add("jingli", -250);

	if(random(me->query("combat_exp")) >  target->query("combat_exp")/2
		||random(me->query_int(1))>target->query_int(1)/2)
	{
		message_vision(YEL"结果$n被$N攻了个措手不及！\n" NOR,me,target);
		target->receive_damage("qi",2000+random(1000),me);
		target->add_busy(skill/100);
		me->set_temp("ryb/shu",1);
		//call_out("check_fight", 1, me, target, weapon, 7); 
	}else {
		message_vision(CYN"可是$n看破了$N的企图，并没有上当。\n" NOR,me,target);
		me->start_busy(1);
	}
	//解密后束缚诀增加连续动作
	if (objectp(me)
		&&objectp(target)
		&&me->is_fighting()
		&&me->query("quest/sl/ryb/shu/pass"))
	{
		call_out("check_fight",1,me,target,skill/20);
	}
	return 1;
}

void check_fight(object me,object target,int count)
{
	object weapon;
	if (!me||!target) return;
	if (!objectp(weapon=me->query_temp("weapon"))||weapon->query("skill_type")!="whip") return;
	if (me->query_skill("whip")!="riyue-bian"||count<0) return;
	
	
	if (random(me->query_skill("whip",1))>target->query_skill("parry",1)/2)
	{
		message_vision(YEL"$n不提防一根长索从脑后无声无息的圈到，绕住了$n的腰间，$N瞬间一抖，将$n抛了起来！\n" NOR,me,target);
		target->receive_damage("qi",3000,me);
		target->receive_wound("qi",1000,me);
		target->apply_condition("no_exert",1);
		target->add_busy(1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	}else if (random(me->query_skill("force",1))>target->query_skill("force",1)/2)
	{
		message_vision(RED"$n左手一翻，试图抓住当胸点来的那条黑索，正想从旁甩去，突觉那条长索一抖，一股排山倒海的内劲向胸口撞到，\n"
						+"这内劲只要中得实了，当场便得肋骨断折，五脏齐碎！\n" NOR,me,target);
		target->receive_damage("qi",3000,me);
		target->receive_wound("qi",1000,me);
		target->apply_condition("neishang",2);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	}else if (random(me->query_skill("riyue-bian",1))>target->query_skill("dodge",1)/2)
	{
		message_vision(YEL"$n突觉身周气流略有异状，这一下袭击事先竟无半点朕兆，一惊之下，立即着地滚开，只觉一条长物从脸上横掠而过，\n"
						+"相距不逾半尺，去势奇急，却是绝无劲风，\n" NOR,me,target);
		message_vision(HIR"$n立即感觉自己被$N的长鞭所束缚，越收越紧，精力在不断流逝！\n"NOR,me,target);
		target->receive_damage("jingli",1000+random(2000),me);
		//target->receive_wound("jingli",1000,me);
		target->apply_condition("no_perform",2);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

	}
    call_out("check_fight", 1, me,target,count -1);/**/
}
string perform_name(){ return HIY"束缚诀"NOR; }
int help(object me)
{
	write(HIC"\n日月鞭「束缚诀」："NOR"\n");
	write(@HELP
	日月鞭是少林三大武器之一，乃是修炼到极高阳刚之意后的由刚化柔的武功
	此时少林内功以达内力返照空明，功力精纯，不露棱角的境界。越长越是灵
	动，越短功力越强。长短收缩，自由收发于心。张无忌救谢逊，孤身犯险，
	以一抵抗三大神僧，那一战固然成就了张无忌的威名，但同时，少林三老的
	日月鞭也名扬天下。
	束缚诀，是将日月鞭阴柔之劲发挥至极致，利用鞭子抖动之际，将对方束缚
	刺穿、破其体力等效果，使得对方在短时间内无法动弹且被压制。
	
	指令：perform whip.shu

要求：	
	当前内力 500 以上； 
	当前精力 500 以上； 
	易筋经等级 250 以上；
	日月鞭法等级 250 以上；
	禅宗心法等级 250 以上；
	激发日月鞭法为招架；
	激发易筋经为内功；
	装备长鞭类兵器。     
HELP
	);
	return 1;
}


