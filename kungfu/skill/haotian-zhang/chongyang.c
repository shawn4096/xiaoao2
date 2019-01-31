//sohu@xojh
//重阳连环掌


#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
#include <combat_msg.h>

string *xing=({"「"HIR"天璇星"NOR"」","「"HIG"天枢星"NOR"」","「"HIY"天玑星"NOR"」","「"HIB"天权星"NOR"」","「"HIM"玉衡星"NOR"」","、「"HIC"开阳星"NOR"」","、「"HIW"摇光星"NOR"」"});
int next1(object me, object target);

int next(object me, object target);

int perform(object me, object target)
{
	int skill;
	string weapon;
	int damage;
	string *limbs,str,type, limb,qxing;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("重阳连环掌只能对战斗中的对手使用。\n");
	

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("重阳连环掌需空手才能施展！\n");

	if( me->query_skill_mapped("strike") != "haotian-zhang" )
		return notify_fail("你所用的并非重阳神掌，不能施展重阳连环掌！\n");

	if( me->query_skill_prepared("strike") != "haotian-zhang" )
		return notify_fail("你所备的并非重阳神掌，不能施展重阳连环掌！\n");

	if( me->query_skill_mapped("force") != "xiantian-gong" )
		return notify_fail("你所用的并非玄门先天功，施展不出重阳连环掌！\n");
	
	if( me->query_skill_mapped("parry") != "haotian-zhang"
		&& me->query_skill_mapped("parry") != "kongming-quan")
		return notify_fail("你所用的招架并非昊天掌或空明拳，不能施展重阳连环掌！\n");
	
	if( !me->query("quest/qz/htz/chongyang/pass"))
		return notify_fail("你尚未习得该项神功，施展不出重阳连环掌！\n");

	if( me->query_skill("force",1) < 500 )
		return notify_fail("你的基本功火候未到，无法施展重阳连环掌！\n");
	if( me->query_skill("xiantian-gong",1) < 500 )
		return notify_fail("你的先天功火候未到，无法施展重阳连环掌！\n");
	if( me->query_skill("haotian-zhang",1) < 500 )
		return notify_fail("你的昊天掌火候未到，无法施展重阳连环掌！\n");
	
	if( me->query_skill("yuanyang-lianhuantui",1) < 500 )
		return notify_fail("你的鸳鸯连环腿法火候未到，无法施展重阳连环掌！\n");

	if( me->query_skill("strike",1) < 500 )
		return notify_fail("重阳连环掌需要精湛的重阳神掌方能有效施展！\n");

	if( me->query("neili") <= 3000 )
		return notify_fail("你的内力不够3000,无法使用重阳连环掌！\n");

	message_vision(HIC "$N默运先天功，但见天空北斗七星蓦然闪烁，这昊天掌果然威力绝大，竟然能引动星斗之力！\n"
	+"$N"HIC"将蓄积已久的真气豁然迸发，大喝一声，三招连出，施展出昊天掌绝技重阳连环掌！\n\n" NOR, me, target);

	skill = me->query_skill("haotian-zhang",1)+ me->query_skill("xiantian-gong",1) / 6;
	
	me->add_temp("apply/attack",skill/5);
	me->add_temp("apply/damage",skill/5);

	me->set_temp("htz/chongyang",1);
	qxing=xing[random(sizeof(xing))];

	message_vision(qxing +HIY"一晃，夹杂星斗之力，昊天掌力呼啸而来！\n\n" NOR, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

	message_vision(qxing +HIC"一晃，第二道掌力又转迅而至！\n\n" NOR, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

	message_vision(qxing +HIG"一晃，第三道掌力如影随形！\n\n" NOR, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	


	if (me->query("env/重阳连环掌")=="三花聚顶"&&me->query_temp("htz/sanhua")>0 && me->query_skill("haotian-zhang",1)>500)
	{
		me->add_temp("htz/sanhua",-1);
		message_vision(HIR "$N将方才蓄积在头顶的一股真气小周天运转，回灌在双手，两股劲力叠加在一起，猛然向外一推！\n\n" NOR, me, target);
		me->add_temp("apply/strike",skill/6);
		me->add_temp("apply/damage",skill/6);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		me->add_temp("apply/strike",-skill/6);
		me->add_temp("apply/damage",-skill/6);
		me->add("neili",-1000);
		me->add("jingli",-600);
	}
	if (me->query("env/重阳连环掌")=="三花聚顶"&&me->query_temp("htz/sanhua")>0 && me->query_skill("haotian-zhang",1)>550)
	{
		me->add_temp("htz/sanhua",-1);
		message_vision(HIY "$N三花聚顶功力凝而不散，头顶的第二股真气又引导灌向双掌，劲力外吐！\n\n" NOR, me, target);
		me->add_temp("apply/strike",skill/5);
		me->add_temp("apply/damage",skill/5);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		me->add_temp("apply/strike",-skill/5);
		me->add_temp("apply/damage",-skill/5);
		me->add("neili",-1200);
		me->add("jingli",-700);

	}
	if (me->query("env/重阳连环掌")=="三花聚顶"&&me->query_temp("htz/sanhua")>0 && me->query_skill("haotian-zhang",1)>600)
	{
		me->add_temp("htz/sanhua",-1);
		message_vision(HIM "$N将最后头顶一朵莲花融入掌法中，三股劲力叠加，掌法变得凶猛异常！\n\n" NOR, me, target);
		me->add_temp("apply/strike",skill/5);
		me->add_temp("apply/damage",skill/5);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		me->add_temp("apply/strike",-skill/5);
		me->add_temp("apply/damage",-skill/5);
		me->add("neili",-1200);
		me->add("jingli",-700);

	}

	message_vision( HIY "\n紧跟着$N突然腾空飞起，使出一招鸳鸯连环腿，两腿风驰电掣连环踢向$n\n" NOR,me,target);
	if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/2)
	{
		if( ( target->query_skill("dodge")+target->query_skill("parry") ) < random((me->query_skill("strike") + me->query_skill("force"))*2/3) )
		{
			message_vision(HIR"只听$N一声惨叫，这连环二腿正中心口。但见$n一个身躯突然平平飞出，腾的一响，尘土飞扬，跌在丈许之外，直挺挺的躺在地下，再也不动。\n\n"NOR, target,target );
                        damage = (int)target->query("eff_qi");
                        target->receive_wound("qi", (damage>0?damage:-damage), me);
                        damage = (int)target->query("qi");
                        target->receive_wound("qi", (damage>0?damage+1:1-damage), me);
			me->add("neili", -me->query("jiali"));
		}
		else
		{
			damage = random((int)me->query_skill("strike")+me->query("jiali")) ;
			if(damage > 5000) damage = 5000;
			//if(damage < 1000) damage = 1000;
			me->add("neili", -me->query("jiali"));

			target->receive_damage("qi", damage,  me);
			target->receive_wound("qi", damage/3, me);

			limb = target->query("limbs");
			type = "瘀伤";
			message_vision("只听$N一声惨叫，这连环二腿正中$P"+limb[random(sizeof(limb))]+"，结果把$P踢摔了个跟头。\n",target);

			str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
			message_vision("($N"+str+")\n", target);
		}
		me->start_busy(1+random(2));
	}
	else if( ( random( target->query_skill("dodge") ) >  me->query_skill("strike")*2/3) && random(5) == 1 )
	{
		message_vision(HIR"$N猛觉得劲风罩来，心知不妙，慌忙闪开，结果$n踢了个空，白白自己重重跌了一跤。\n\n"NOR, target,me );
		me->receive_wound("qi", 30+random(50),  me);
		me->start_busy(2+random(2));
		str = COMBAT_D->status_msg((int)me->query("qi") * 100 /(int)me->query("max_qi"));
		message_vision("($N"+str+")\n", me);
	}
	else
	{
		message_vision( "$N眼见这一腿来势凶猛，当下双足一点，跃高四尺，躲开了$n这一招，不过也出了一身冷汗。\n\n" NOR,  target,me);
		me->start_busy(2);
	}
	//履霜破冰掌
	if (objectp(target)&&me->is_fighting())
	{
		next(me,target);
		//return 1;
	}
	me->add_temp("apply/attack",-skill/5);
	me->add_temp("apply/damage",-skill/5);
	me->add("neili", -random(me->query_skill("strike",1)/4) -100 );
	me->start_busy( 2+random(2) );
	me->start_peform(6,"重阳连环掌");
	return 1;
}


int next(object me, object target)
{
        string msg;
        int damage, ap, dp;
        object weapon;
        if( !me ) return 0;
        weapon = me->query_temp("weapon");
        if (weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("htz/lianhuan");
                return 0;
        }
		if (me->query_skill_mapped("strike")!="haotian-zhang"
		||me->query_skill_prepared("strike")!="haotian-zhang") return 0;
		
        msg = HIG"\n$N长吸一口真气，施展出昊天掌"HBCYN+HIG"「履霜破冰掌」"NOR+HIG"绝技！\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1)/100000;
        dp = target->query("combat_exp", 1) * target->query_str(1)/100000;
		//100000降低ap,dp，以防溢出 by sohu@xojh
       if(objectp(target)&&((userp(target)&& random(ap + dp) > dp) || !userp(target)))
	   {

                    damage = me->query_skill("haotian-zhang",1)*3;

					damage += me->query_skill("strike",1)*3;

					damage += random(damage);
                if ( damage > 6000 )
					damage = 6000 + (damage - 1000)/100;
				//if( damage>= target->query("qi",1)) damage= target->query("qi",1)-1;
                
				target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                
				msg += damage_msg(damage, "瘀伤");
                message_vision(msg, me, target);

				if(objectp(target) && me->query("env/damage"))
					tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage+ WHT"点攻击伤害。\n"NOR);
				//
				if(userp(target)&& target->query("env/damage"))
									//tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage+ WHT"点伤害。\n"NOR);
								
				COMBAT_D->report_status(target, random(2));

				me->add_temp("apply/attack", (int)me->query_skill("xiantian-gong") /4);
				me->add_temp("apply/damage", (int)me->query_skill("xiantian-gong") /4);
				if (me->is_fighting(target))
						COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

				me->add_temp("apply/attack", -(int)me->query_skill("xiantian-gong") /4);

				me->add_temp("apply/damage", -(int)me->query_skill("xiantian-gong") /4);
                me->add("neili",- 150);
                me->add("jingli",-80);
                me->start_perform(3 + random(2),"「重阳连环掌」");
        } 
        else {
                msg = msg + HIW "$n一个旱地拔葱，跃起数丈，堪堪避过。\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
        me->delete_temp("htz/lianhuan");
		me->start_perform(6,"重阳连环掌");
        return 1;
}


string perform_name(){ return HIR"重阳连环掌"NOR; }
int help(object me)
{
        write(HIC"\n昊天掌之「重阳连环掌」："NOR"\n");
        write(@HELP
	重阳连环掌是祖师王重阳仰观北斗七星，领悟其中连环不绝
	之意所创的掌法。此招招式精奇，修炼到高深境界会和天空
	北斗七星暗合，遥相呼应，威力倍增。修炼到重阳境界全真
	空手已然大乘，功力越是深厚，此招威力越大。
	
	注意：set 重阳连环掌 三花聚顶 效果：会释放头顶蓄积的
	三花劲气，颇为耗费内力，但威力巨大，功力不高者慎用。

	指令：perform strike.chongyang

要求：
	先天功法的等级 500  以上；
	鸳鸯连环腿等级 500  以上；
	基本腿法的等级 500  以上；
	昊天掌发的等级 500  以上
	基本掌法的等级 500  以上
	基本内功的等级 500  以上
	当前内力的要求 3000  以上；
	激发且备掌法为昊天掌；
	激发腿法为鸳鸯连环腿；
	激发内功为先天功；
	空手且备掌法为昊天掌。
HELP
        );
        return 1;
}
