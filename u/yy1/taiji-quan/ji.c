// zhen.c 太极拳「挤」字诀
// snowman
#include <ansi.h>

inherit F_SSERVER;
string *taiji_msg = ({"揽雀尾","单鞭","提手上势","白鹤亮翅","搂膝勾步","白蛇吐信","高探马",
"伏虎式","揽月势","金鸡独立","玉女穿梭","进步七星","弯弓射虎","抱虎归山",});

string perform_name(){ return HIR"挤字诀"NOR; }

int perform(object me, object target)
{
	int damage, force, ap, dp;
	string msg, *limbs;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
		return notify_fail("「挤」字诀只能对战斗中的对手使用。\n");

	if( userp(me) 
	&&( me->query_skill_mapped("parry") != "taiji-quan"
	&& me->query_skill_mapped("parry") != "taiji-jian") )
		return notify_fail("「挤字诀」必须在用太极拳或太极剑激发招架的情况下才能使用。\n");

	if( userp(me) && (me->query_skill_mapped("force") != "yinyun-ziqi"
	|| me->query_skill_prepared("cuff") != "taiji-quan") )
		return notify_fail("你的内功或拳法不对，根本不能发挥出「挤字诀」的优势。\n");  

	if( !me->query_temp("tj/太极") && me->query_skill("taiji-quan", 1) < 300 )
		return notify_fail("太极拳要旨是似松非松，你没有运用「太极」，又如何能使用「挤」字诀？\n");

	if( (int)me->query("neili", 1) < 500 )
		return notify_fail("你现在真气不够，强行使用「挤」是发挥不了它的威力的！\n");

	if( (int)me->query("jingli", 1) < 100 )
		return notify_fail("你现在精力不够，强行使用「挤」是发挥不了它的威力的！\n");                     

	if( me->query_temp("weapon"))
		return notify_fail("你先放下手中的武器再说吧？！\n");     

	limbs = target->query("limbs");

	msg = CYN "\n$N使一招太极拳「"+taiji_msg[random(sizeof(taiji_msg))]+"」，右脚实，左脚虚，运起"RED"「挤」"CYN"字诀，粘连粘随，右掌已搭住$p"+limbs[random(sizeof(limbs))]+"！\n"NOR;
        
	force = me->query_skill("force") + target->query_skill("force");

	ap = me->query("combat_exp", 1) /1000 * me->query_skill("force");
	dp = target->query("combat_exp",1 )/ 1000 * target->query_skill("parry");

	if( random(ap + dp) > dp ){
		if(!target->is_busy()) target->start_busy(random(2));
		damage = (int)me->query_skill("force");                
		if(me->query("neili") > target->query("neili")*2) 
			damage *= 2;
		else if(me->query("neili") > target->query("neili")*3/2) 
			damage += random(damage);
		else if(me->query("neili")*2 < target->query("neili")) 
			damage /= 2;
		else if(me->query("neili") < target->query("neili")) 
			damage -= random(damage/2);
		else damage = damage/2 + random(damage);
                
		if(damage> 1400) damage = 1400; 
		target->receive_damage("jingli", damage);
		target->receive_damage("neili", damage);
	      target->receive_wound("jing", me->query_int(1)*2+ me->query_con(1)*2, me);
		me->add("neili", -300);
		me->add("jingli", -100);
		msg += HIR"跟着$P横劲发出，$p给这么一挤，身子被自己的劲力带得不由主的向前一冲，跨出数步！\n"NOR;       
	}
	else{
		me->add("jingli", -25);
		me->add("neili", -100);
		msg += HIY"$p见此情景，一声惊噫，连忙收回自己的劲力，闪身避让！\n"NOR;
	}
	me->start_busy(random(2));
	me->start_perform(2, "「挤」"); 
	message_vision(msg, me, target);
	return 1;
}

int help(object me)
{
	write(WHT"\n太极「挤字诀」："NOR"\n");
	write(@HELP
	要求：	内力 500 以上；      
		精力 200 以上；      
		运用太极拳意且手无兵器。
HELP
	);
	return 1;
}