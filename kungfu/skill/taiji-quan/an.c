// an.c 太极拳「按字诀」诀
// by snowman@SJ 06/06/2000

inherit F_SSERVER;

#include <ansi.h>
#include <combat_msg.h>

#define TAIJI                "/kungfu/skill/yinyun-ziqi/taiji"

int is_pfm() {       return 1;}

string perform_name(){ return HIB"按字诀"NOR; }

int perform(object me, object target)
{ 
	object ob;
	if( !target ) target = offensive_target(me);

	if( !objectp(target) 
	|| !target->is_character() 
	|| !me->is_fighting(target) 
	|| !living(target))
		return notify_fail("「按字诀」只能对战斗中的对手使用。\n");

	if( userp(me) 
	&&( me->query_skill_mapped("parry") != "taiji-quan"
	&& me->query_skill_mapped("parry") != "taiji-jian") )
		return notify_fail("「按字诀」必须在用太极拳或太极剑激发招架的情况下才能使用。\n");

	if( userp(me) && (me->query_skill_mapped("force") != "yinyun-ziqi"
	|| me->query_skill_prepared("cuff") != "taiji-quan") )
		return notify_fail("你的内功或拳法不对，根本不能发挥出「按字诀」的优势。\n");  

	if( me->query_skill_prepared("cuff") != "taiji-quan"
	|| me->query_skill_mapped("cuff") != "taiji-quan")
		return notify_fail("你必须懂得太极拳，才能施展「按字诀」。\n");  

	if( me->query_skill("taiji-quan", 1) < 450 )
		return notify_fail("你的太极拳不够娴熟，还不能领会「按字诀」之诀窍！\n");
    if( me->query_skill("yinyun-ziqi", 1) < 450 )
		return notify_fail("你的氤氲紫气不够娴熟，还不能领会「按字诀」之诀窍！\n");
	if( (int)me->query("neili", 1) < 5000 )
		return notify_fail("你现在真气不够，强行使用「按字诀」是发挥不了它的威力的！\n");    
	if( (int)me->query("jingli", 1) < 3000 )
		return notify_fail("你现在真气不够，强行使用「按字诀」是发挥不了它的威力的！\n");    

	if( me->query_temp("weapon"))
		return notify_fail("你先放下手中的武器再说吧？！\n");     

	if( me->query_int(1) < target->query_int(1)/3*2 )
		return notify_fail("你这诱敌的招数，怕对这么聪明的对手不适合吧？！\n");     

	if( target->is_busy())
		return notify_fail("对方正自顾不暇呢，你不忙使用「按字诀」。\n");

	if( objectp(ob = me->query_temp("tjq/an")) ) {
		if( ob->is_fighting(me) || me->is_fighting(ob))
			return notify_fail("你已经准备随时对此对手使用「按字诀」了。\n");
		else me->delete_temp("tjq/an");
	}
	return (int)call_other( this_object(), "main", me, target);
}

int main(object me, object target)
{
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target) 
	|| me->query("neili") < 1500 || me->query("jingli") < 300 || me->query_temp("weapon")
	|| me->query_skill("taiji-quan", 1) < 350 )
		return 0;     
                
	if(intp(me->query_temp("tjq/"+target->query("id")) > 7))
		me->add_temp("tjq/"+target->query("id"), -7);
	else me->delete_temp("tjq/"+target->query("id"));
       
	msg = HIB"\n你双臂陡然圈转，似是只守不攻，无声无息的运起太极拳中"RED"「按字诀」，"HIB;
        
	if(me->query_skill_mapped("force") != "yinyun-ziqi"
	|| me->query_skill("yinyun-ziqi", 1) < 100){
		msg += "双臂聚力，紧视$n！\n"NOR;
	}        
        
	else msg += "双臂凝聚太极六合内劲，气守丹田，蓄势待发！\n"NOR;
 
	tell_object(me, msg);
	if (me->query_skill("taiji-quan",1)<550)
	{
		me->start_perform(2, "「按字诀」");
	}
	me->set_temp("tjq/an", target);
	me->add("neili", -150);
	//me->start_busy(random(1)); 有了pfmbusy就可以了
	me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), me->query_int()/2);      
	return 1;
}

void remove_effect(object me)
{
	if( !me ) return;
	if( !me->query_temp("tjq/an") ) return;
	
	me->delete_temp("tjq/an");
	if( me->is_fighting() ){
		tell_object(me, HIB"\n你聚力过久，无法支撑，只好散去「按字诀」的劲力。\n"NOR, me);
		if( !me->query_perform() )
			me->start_perform(1);
	}
}

int help(object me)
{
	write(WHT"\n太极拳法之"HIB"「按字诀」："NOR"\n");
	write(@HELP
	太极拳乃是虽变化万端，而理为一贯。由招熟而渐悟懂劲，由懂劲而阶及神明。
	「按字诀」的要点在于压敌，制敌用困，而后以泰山压顶之势胜出。此招集
	神、气、精、力、巧为一体，乃太极拳之精华！
	太极拳法之「按字诀」乃太极拳重要的辅助进攻武技，550级后大飞。
	要求：	
		当前内力 5000 以上；      
		当前精力 3000 以上；  
		太极拳等级 450 以上；
		氤氲紫气需 450 以上；
		运用太极拳且手无兵器。
HELP
	);
	return 1;
}
