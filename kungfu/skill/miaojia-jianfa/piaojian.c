// piaojian.c 飘剑诀
// Created by sohu@xojh 2015 

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me);

int perform(object me, object target)
{
	object weapon;
	int focus;
	int j,ap,dp,damage,p;
	string msg;
	if (me->query_skill_mapped("force") == "lengquan-shengong")
		focus =me->query_skill("force",1)+ me->query_skill("lengquan-shengong",1);
	else focus =me->query_skill("force",1);
	
	        
	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("「飘剑诀」只能在战斗中使用。\n");
        
	if( (int)me->query_skill("miaojia-jianfa", 1) < 400 )
		return notify_fail("你的苗家剑法还不够娴熟，无法使出「飘剑诀」。\n");

	if( (int)me->query_skill("force", 1) < 400 )
		return notify_fail("你的基本内功等级还不够，无法使出「飘剑诀」。\n");
	if( (int)me->query_skill("sword", 1) < 400 )
		return notify_fail("你的基本剑法等级还不够，无法使出「飘剑诀」。\n");
	

	if (!objectp(weapon = me->query_temp("weapon"))
	|| weapon->query("skill_type") != "sword"
	|| me->query_skill_mapped("parry") != "miaojia-jianfa"
	|| me->query_skill_mapped("sword") != "miaojia-jianfa" )
		return notify_fail("你无法使出「飘剑诀」。\n");

	if (me->query_temp("mjjf/piaojian"))
		return notify_fail("你正在使用「飘剑诀」，休息一下吧。\n"); 
    //if (target->is_busy())
	//	return notify_fail("对方已经手忙脚乱了，无需使用这招「飘剑诀」。\n"); 
           
	if( (int)me->query("max_neili") < 5000)
		return notify_fail("你的内力修为太差，无法使出「飘剑诀」。\n");
                
	if( (int)me->query("neili") < 1000)
		return notify_fail("你现在真气太弱，使不出「飘剑诀」。\n");
	if( (int)me->query("jingli") < 1000)
		return notify_fail("你现在精力太弱，使不出「飘剑诀」。\n");

	j = me->query_skill("miaojia-jianfa", 1);
			
	

	message_vision(HIW"突然之间，$N忽然施展出苗家剑法中「"HIC"提撩剑白鹤舒翅"HIW"」招式，身形如雁，宛如白鹤展翅翱翔。\n"NOR,me);
			
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER );
	
	

		
	message_vision(HIW"\n$n哪知$N的武功如此玄妙，愕然之间为$N突发的这招所迷惑，顿时有些手足失措。\n"
	                  +"$N的这招展开后，剑势绵绵不绝，几乎毫无破绽，真是苗家剑法中"HIG"「飘剑诀」"HIW"的绝技！\n"NOR,me,target);

	me->set_temp("mjjf/piaojian",j);
	
	me->add_temp("apply/attack",j/4);
	me->add_temp("apply/parry", j/4);
	me->add_temp("apply/dodge", j/4);
	me->add_temp("apply/dexerity", j/10);

	call_out("effect_check",1,me,(int)j/25);

	me->add("neili", -400-random(200));
	me->add("jingli", -300-random(100));
    if (me->query_skill("miaojia-jianfa",1)<450)
		me->start_perform(1, "飘剑诀");
	
    return 1; 
}

int effect_check(object me,int count)
{
	int j;
	object weapon;
	//j=me->query_temp("mjjf/piaojian");
	
	if (!me) return 0;
	j=me->query_skill("miaojia-jianfa",1);

	weapon=me->query_temp("weapon");
	//write("j="+j);
	if (!me->is_fighting()
		||me->query_skill_mapped("sword")!="miaojia-jianfa"
		||!objectp(weapon)
		||weapon->query("skill_type")!="sword"
		||count< 1)
	{
		me->add_temp("apply/attack",-j/4);
		me->add_temp("apply/parry", -j/4);
		me->add_temp("apply/dodge", -j/4);
		me->add_temp("apply/dexerity", -j/10);
		me->delete_temp("mjjf/piaojian");

		//write("j1="+j/3);
		message_vision(HIW"$N剑法一滞，身形顿时迟缓，将「飘剑诀」缓缓收招。\n"NOR,me);
		return 1;
	}
	call_out("effect_check",2,me,count--);
	//return 1;
}
string perform_name(){ return HIW"飘剑诀"NOR; }

int help(object me)
{
        write(YEL"\n苗家剑法之「飘剑诀」："NOR"\n\n");
        write(@HELP
	苗家剑法乃是打遍天下无敌手的苗人凤家传绝技
	该剑法胜在灵活多变，狠辣异常，几乎没有破绽
	实乃武林中不可多得的一门武技。
	「飘剑诀」是利用自身高超的轻功优势，将剑势
	和身法融合在一起，借用身形飘逸之势，提升自
	身的防御和躲避，功力高深式可获得一定的躲避
	伤害功效。
	注意：需要激发自身的招架方可使用
	
	指令:perform sword.piaojian

要求：
	当前内力需求 1000 以上；
	最大内力需求 5000 以上；
	当前精力需求 1000 以上；
	苗家剑法等级 400 以上；
	基本内功等级 400 以上；
	基本剑法等级 400 以上；
	激发剑法为苗家剑法；
	激发招架为苗家剑法；
	且手持兵器。

HELP
        );
        return 1;
}
