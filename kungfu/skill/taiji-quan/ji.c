// zhen.c 太极拳「挤」字诀
// snowman
#include <ansi.h>

inherit F_SSERVER;
string *taiji_msg = ({"揽雀尾","单鞭","提手上势","白鹤亮翅","搂膝勾步","白蛇吐信","高探马",
"伏虎式","揽月势","金鸡独立","玉女穿梭","进步七星","弯弓射虎","抱虎归山",});

string perform_name(){ return HIG"挤字诀"NOR; }

int perform(object me, object target)
{
	int damage, force, ap, dp,skill;
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

	if( me->query_skill("taiji-quan", 1) < 350 )
		return notify_fail("太极拳要旨是似松非松，你太极拳等级太低，又如何能使用「挤」字诀？\n");
    if( me->query_skill("yinyun-ziqi", 1) < 350 )
		return notify_fail("太极拳需要和氤氲紫气相配合，没有强大的内功又如何能使用「挤」字诀？\n");
     if( (int)me->query("max_neili", 1) < 5000 )
		return notify_fail("你现在最大内力不够，强行使用「挤」是发挥不了它的威力的！\n");
	if( (int)me->query("neili", 1) < 1500 )
		return notify_fail("你现在真气不够，强行使用「挤」是发挥不了它的威力的！\n");

	if( (int)me->query("jingli", 1) < 1000 )
		return notify_fail("你现在精力不够，强行使用「挤」是发挥不了它的威力的！\n");                     

	if( me->query_temp("weapon"))
		return notify_fail("你先放下手中的武器再说吧？！\n");     

	limbs = target->query("limbs");
	skill=me->query_skill("taiji-quan",1);
	msg = WHT "\n$N"WHT"使一招太极拳「"+taiji_msg[random(sizeof(taiji_msg))]+WHT"」，右脚实，左脚虚，运起"RED"「挤」"WHT"字诀，粘连粘随，右掌已搭住$p"+limbs[random(sizeof(limbs))]+"！\n"NOR;
        
	force = me->query_skill("force",1) + target->query_skill("force",1);

	ap = me->query("combat_exp") /100000 * me->query_skill("force",1);
	dp = target->query("combat_exp")/ 100000 * target->query_skill("parry",1);
    if (me->query("yyzq/taiji"))
      ap+=ap/2;
	
	me->add_temp("apply/attack",skill/4);		
	me->add_temp("apply/damage",skill/8);

	if( random(ap + dp) > dp 
		||random(me->query_int(1))>target->query_int(1)/3)
	{
		target->add_busy(2+random(3));
		damage = (int)me->query_skill("force",1)+(int)me->query_skill("yinyun-ziqi",1);                
		damage=damage+random(damage);

		if(me->query("neili") > target->query("neili")*2/3) 
			damage *= 2;
		else if(me->query("neili") > target->query("neili")) 
			damage += random(damage);
		else if(me->query("neili")*1.5 < target->query("neili")) 
			damage /= 2;
		else if(me->query("neili") < target->query("neili")) 
			damage -= random(damage/2);
		else damage = damage/2 + random(damage);
                
		if(damage> 4000) damage = 4000+(damage-4000)/10; 
		target->receive_damage("jingli", damage,me);
		target->receive_damage("neili", damage/2);
	    target->receive_wound("jing", me->query_int(1)*2+ me->query_con(1)*2, me);
		me->add("neili", -300);
		me->add("jingli", -100);
		msg += HIR"跟着$P横劲发出，$p给这么一挤，身子被自己的劲力带得不由主的向前一冲，跨出数步！\n"NOR;
		message_vision(msg, me, target);
		if (!userp(target)) {
			me->set_temp("tjq/jiadd",skill);
			me->add_temp("apply/damage",skill/8);
		}

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		

		if (me->query_temp("tjq/jiadd"))
		{
			me->delete_temp("tjq/jiadd");
			me->add_temp("apply/damage",-skill/4);		
		}
	}
	else{
		me->add("jingli", -25);
		me->add("neili", -100);
		msg += HIY"$p见此情景，一声惊噫，连忙收回自己的劲力，闪身避让，随后连攻一招！\n"NOR;
		message_vision(msg, me, target);
		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
	}
	

	me->add_temp("apply/attack",-skill/4);		
	me->add_temp("apply/damage",-skill/8);

	me->start_busy(1+random(1));
	me->start_perform(3, "「挤」"); 
	
	return 1;
}

int help(object me)
{
	write(WHT"\n太极拳法之"HIG"「挤字诀」："NOR"\n");
	write(@HELP
	太极拳乃是武当开山鼻祖张三丰真人在晚年所创立的一门功法，讲究的是
	以慢打快，后发先至，借力打力的高明武学，这门拳术的创立可谓开天辟
	地的大事，改变了整个武林的武学体系，可谓前无古人后来者，太极拳的
	挤字诀乃是太极拳中极为高明的心法，对手一旦落入当中，自身中心立失
	从而形成被动挨打的局面。高的内功和高悟性对敌人的精有额外的伤害；
	
	指令：perform cuff.ji

要求：	
	当前内力 1500 以上；
	当前精力 1500 以上；
	最大内力 5000 以上；
	氤氲紫气 350  以上；
	太极拳需 350  以上；		
	激发太极拳且手无兵器。
HELP
	);
	return 1;
}