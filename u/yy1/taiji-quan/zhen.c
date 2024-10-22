// zhen.c 太极拳「震」字诀
// snowman
#include <ansi.h>

inherit F_SSERVER;

string *taiji_msg = ({"十字手","如封似闭","搬拦捶","野马分鬃","斜飞势","云手","马步靠","闪通臂"});

string perform_name(){ return HIR"震字诀"NOR; }

int perform(object me, object target)
{
	int damage, p, m, force, ap ,dp;
	float at;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target) )
		return notify_fail("神功震敌只能对战斗中的对手使用。\n");

	if( userp(me) && !me->query_temp("tj/太极") && me->query_skill("taiji-quan", 1) < 300 )
		return notify_fail("太极拳讲究劲断意不断，你没有运用「太极」，又如何能使用「震」字诀？\n");

	if( userp(me) && (me->query_skill_mapped("force") != "yinyun-ziqi"
	 || me->query_skill_prepared("cuff") != "taiji-quan") )
		return notify_fail("你的内功或拳法不对，又如何能使用「震」字诀？\n");

	if( (int)me->query("neili", 1) < 1000 )
		return notify_fail("你现在真气不够，强迫使用「震」字诀只会伤到你自己！\n");

	if( me->query_temp("weapon") )
		return notify_fail("你先放下手中的武器再说吧？！\n");

	msg = CYN "\n突然，$N一招「"+taiji_msg[random(sizeof(taiji_msg))]+"」，双手左右连画，一个圆圈已将$n套住，太极拳的"RED"「震」"CYN"字诀随即使出！\n"NOR;

	force = me->query_skill("force") + target->query_skill("force");

	ap = me->query("combat_exp", 1)/ 1000 * me->query_skill("force");
	dp = target->query("combat_exp", 1)/1000 * target->query_skill("force");

	if( random( ap + dp) > dp ){
			if( me->query("neili") < target->query("neili")*3/2 ) {
				me->start_busy(2);
				target->add_busy(2);
				me->add("jingli", -force/10);
				me->add("neili", -force/2);
                       	target->add("jingli", -force/10);
                       	target->add("neili", -force/2);
				msg += HIY"只听「啪」的一声，$p和$P两人内力相拼相碰，各自退了几步。\n"NOR;
				me->start_perform(2, "「震」");
				message_vision(msg, me, target);
				return 1;
			}
			me->start_busy(random(2));

			damage = (int)me->query_skill("force") * 4;
			at = me->query("neili") / (target->query("neili")+1);
                
			if( at < 1 ) {
				if(at < 0.5) damage /= 2;
				damage /= 2;
			}
			else damage = to_int(damage * at);

			if( me->query_skill("taiji-quan", 1) > 300 ) 
			m = 4000 + ( me->query_skill("taiji-quan", 1) - 300 ) * 10 + random(200);
			else m = 4000;

			if( !userp(me) ) m = 4000;

			if( damage > m ) damage = m + (damage-m)/20;
			if( damage > 8000 ) damage = 10000 + (p-8000)/50;
			if( wizardp(me) ) tell_object(me, "你的「"RED"震字诀"NOR"」威力为： "+damage+"。\n"NOR);

			if( wizardp(me) && (string)me->query("env/combat")=="verbose")
			tell_object(me, "M_neili = "+me->query("neili")+ " T_neili = "+target->query("neili")+" Damage = "+damage+"\n");

			target->receive_damage("qi", damage, me);
			target->receive_wound("qi", damage/(2+random(2)), me);
			target->receive_damage("neili", damage/(2+random(2)), me);
                    target->add("jing",-(me->query_int(1)+ me->query_con(1))* 3 );

			me->add("neili", -400);
			me->add("jingli", -150);
			me->start_perform(3, "「震」");

			if( damage >= me->query_skill("taiji-quan", 1) * 10 )
				msg += "太极之意连绵不断，有如自去行空，一个圆圈未完，第二个圆圈已生，喀喇一响，$p一处骨头被绞断！\n";
			if( damage >= me->query_skill("taiji-quan", 1) * 12 ){
				msg += "$N恨他歹毒，「震」字诀使出时连绵不断，跟着喀喀喀几声，$p全身各处骨头也被一一绞断！\n";
			       target->receive_wound("jing", damage/(2+random(2)), me);}
			p = (int)target->query("eff_qi")*100/(int)target->query("max_qi");

			msg += COMBAT_D->damage_msg(damage, "震伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
	else{
		msg += HIY"$p一看不对，马上一阵急攻，$P登时手忙脚乱，再也来不及出招！\n"NOR;
		me->start_busy(random(2));
		me->add("jingli", -50);
		me->add("neili", -150);
		me->start_perform(2, "「震」");
	}
	message_vision(msg, me, target);
	return 1;
}

int help(object me)
{
	write(WHT"\n太极「震字诀」："NOR"\n");
	write(@HELP
	要求：	内力 1000 以上；      
		精力 200 以上；      
		运用太极拳意且手无兵器。
HELP
	);
	return 1;
}
