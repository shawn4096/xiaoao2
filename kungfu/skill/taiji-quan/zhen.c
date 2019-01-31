// zhen.c 太极拳「震」字诀
// snowman
#include <ansi.h>

inherit F_SSERVER;

string *taiji_msg = ({"十字手","如封似闭","搬拦捶","野马分鬃","斜飞势","云手","马步靠","闪通臂"});

string perform_name(){ return HBRED+HIY"震字诀"NOR; }

int perform(object me, object target)
{
	int damage, p, m, force, ap ,dp;
	int tnl,snl;
	float at;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target) )
		return notify_fail("神功震敌只能对战斗中的对手使用。\n");

	if( me->query_skill("taiji-quan", 1) < 450 )
		return notify_fail("太极拳讲究劲断意不断，你太极拳功力不到，又如何能使用「震」字诀？\n");

	if( userp(me) && (me->query_skill_mapped("force") != "yinyun-ziqi"
	 || me->query_skill_prepared("cuff") != "taiji-quan") )
		return notify_fail("你的内功或拳法不对，又如何能使用「震」字诀？\n");

	if( (int)me->query("neili", 1) < 5000 )
		return notify_fail("你现在真气不够，强迫使用「震」字诀只会伤到你自己！\n");

	if( me->query_temp("weapon") )
		return notify_fail("你先放下手中的武器再说吧？！\n");

	msg = CYN "\n突然，$N一招「"+taiji_msg[random(sizeof(taiji_msg))]+"」，双手左右连画，一个圆圈已将$n套住，太极拳的"RED"「震」"CYN"字诀随即使出！\n"NOR;

	force = me->query_skill("force",1) + target->query_skill("yinyuan-ziqi",1);

	ap = me->query("combat_exp", 1)/ 100000 * me->query_skill("force",1);
	dp = target->query("combat_exp", 1)/100000 * target->query_skill("force",1);

	if( random( ap + dp) > dp 
		|| random(me->query_int(1))>target->query_int(1)/3 )
	{
			if( me->query("neili") < target->query("neili")*3/2 ) 
			{
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

			damage = (int)me->query_skill("taiji-quan",1) * 4+force;
			//防止除0 by renlai
			if (target->query("neili")>0) tnl=target->query("neili");
				else tnl=1;
			if (me->query("neili")>0) snl=me->query("neili");
			else snl=0;
			at = snl / tnl;
                
			if( at < 1 ) {
				if(at < 0.5) damage /= 2;
				damage /= 2;
			}
			else damage = to_int(damage * at);

			if( me->query_skill("taiji-quan", 1) > 450 ) 
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
			target->receive_damage("neili", damage/2);
            target->receive_damage("jing",-(me->query_int(1)+ me->query_con(1))* 3,me );

			me->add("neili", -400);
			me->add("jingli", -150);
			me->start_perform(2, "「震」");

			if( damage >= me->query_skill("taiji-quan", 1) * 8 )
				msg += "太极之意连绵不断，有如自去行空，一个圆圈未完，第二个圆圈已生，喀喇一响，$p一处骨头被绞断！\n";
			if( damage >= me->query_skill("taiji-quan", 1) * 10 ){
				msg += "$N恨他歹毒，「震」字诀使出时连绵不断，跟着喀喀喀几声，$p全身各处骨头也被一一绞断！\n";
			target->receive_wound("jing", damage/(2+random(2)), me);
			}
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
	if (me->query("taiji/pass"))
	{
		target->set_temp("must_be_hit",1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		target->delete_temp("must_be_hit");
	}
	
	return 1;
}

int help(object me)
{
	write(WHT"\n太极拳法之"HBRED+HIY"「震字诀」："NOR"\n");
	write(@HELP
	太极拳法之「震字诀」乃是将太极拳和氤氲紫气融合后的
	一种攻击武技。其特点是，通过太极拳的内劲迸发，将太极
	劲气陡然发出来，对对方的内功和精力以及气血都造成极大
	伤害。注意，和臂力，内功，经验值以及悟性具有关系。
	
	指令：perform cuff.zhen

要求：	
	当前内力 5000 以上；      
	当前精力 2000 以上；
	太极拳法 450  以上；
	氤氲紫气 450  以上；
	运用太极拳且手无兵器。
HELP
	);
	return 1;
}
