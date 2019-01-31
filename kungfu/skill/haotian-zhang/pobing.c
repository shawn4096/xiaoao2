//cre by sohu
//履霜破冰掌
//全真教武技

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int next1(object me, object target, int i);
int next2(object me, object target, int i);


int perform(object me,object target)
{
        object weapon;
        string msg;
        int ap,dp;
        int i = me->query_skill("haotian-zhang",1) ;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("履霜破冰掌只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你的内功不是先天功，无法使用履霜破冰掌！\n");


        if( me->query_skill("xiantian-gong", 1) < 250 )
                return notify_fail("你的内功还未练成，不能使用履霜破冰掌！\n");

        if( me->query_skill("haotian-zhang", 1) < 250 )
                return notify_fail("你的昊天掌法还未练成，不能使用履霜破冰掌！\n");

        if (me->query_temp("weapon"))
               return notify_fail("你手中有兵器，无法使用履霜破冰掌！\n");
   
        if (me->query_skill_prepared("strike") != "haotian-zhang"
            || me->query_skill_mapped("strike") != "haotian-zhang")
                return notify_fail("你没有激发并使用昊天掌，现在无法使用「履霜破冰掌」进行攻击。\n");  
        if (me->query_skill_mapped("leg") != "yuanyang-lianhuantui")
                return notify_fail("你需要激发腿法为鸳鸯连环腿，方可使用「履霜破冰掌」进行攻击。\n");  

        if(me->query_skill_mapped("parry") != "haotian-zhang"
			&& me->query_skill_mapped("parry") != "kongming-quan")
                return notify_fail("你的招架功夫不对，无法使用履霜破冰掌！\n");

        if(me->query("max_neili") < 3500 )
                return notify_fail("你的内力修为不够，不能使用履霜破冰掌！\n");
        if(me->query("neili") < 1000 )
                return notify_fail("你现在真气不足，不能使用履霜破冰掌！\n");
        if(me->query("jingli") < 600 )
                return notify_fail("你现在精力不足，不能使用履霜破冰掌！\n");
        if(me->query_temp("htz/pobing"))
                return notify_fail("你正在使用履霜破冰掌！\n");

        if(me->query_skill("strike", 1) < 250 )
                return notify_fail("你的基本基本掌法不够娴熟，不能在剑招中使用履霜破冰掌。\n");


        msg = HBRED+HIW"\n$N全身真气发动，使出昊天掌绝技"NOR+HIR"「履霜破冰掌」"+HBRED+HIW"，$n只觉$N的掌力汹涌澎湃，势不可挡！\n"NOR;
        message_vision(msg, me, target);
		
		if (target->query_skill_prepared("strike")=="hanbing-shenzhang"
			||target->query_skill_prepared("strike")=="huagu-mianzhang"
			||target->query_skill_prepared("strike")=="hanbing-mianzhang"
			||target->query_skill_prepared("hand")=="songyang-shou")
		{
			if (random(me->query("combat_exp"))>target->query("combat_exp")/2)
			{
				message_vision(HIM"$N见$n施展的是阴寒掌力，先天功随心而起，昊天掌力发出，破了$n的阴寒掌力!\n"NOR,me,target);
				target->start_busy(3);
				target->apply_condition("no_perform",1);
			}
		}
            me->add_temp("apply/attack", me->query_skill("haotian-zhang") /4);

			me->add_temp("apply/damage", me->query_skill("haotian-zhang") /4);
            me->set_temp("htz/pobing", 1);
             
        //第一招攻击
        if (me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("haotian-zhang") /4);
		
me->add_temp("apply/damage", -me->query_skill("haotian-zhang") /4);

        me->add("neili", -150);
//断兵器
		weapon = target->query_temp("weapon");

		if( objectp(weapon) 
			&& me->query("env/昊天掌")=="断"
			&& me->query_temp("xtg/wuqi"))
		{
			ap =   me->query("force")/5
			+ (int)me->query("haotian-zhang")/5
			+ (int)me->query_str()
			+ (int)me->query("jiali");

			dp = (int)weapon->weight() / 500
			+ (int)target->query_str()
			+ (int)target->query("jiali")
			+ (int)target->query_skill("parry")/3;

			ap = ap/2 + random(ap/2);

			if( ap > 3 * dp ) {
				message_vision(HIY"只见$N身上的$n"+HIY+"已被一掌震断。\n"NOR, target, weapon);
				weapon->unequip();
				weapon->move(environment(target));
				weapon->set("name", "断掉的" + weapon->query("name"));
				weapon->set("value", 0);
				weapon->set("weapon_prop", 0);
				target->reset_action();
				me->add("neili", -150); // to break weapon takes more neili
			} else if( ap > 2 * dp ) {
				message_vision(HIW"$N只觉得手中" + weapon->name() + "被一掌震得把持不定，脱手飞出！\n" NOR, target);
				weapon->unequip();
				weapon->move(environment(target));
				target->reset_action();
				me->add("neili", -120); // to break weapon takes more neili
			} else if( ap > dp ) {
				message_vision("$N只觉得手中" + weapon->name() + "一震，险些脱手！\n", target);
				me->add("neili", -100); // to break weapon takes more neili
			}
		}


        if ( me->query_skill("xiantian-gong", 1) > 250)
                next1(me, target, i);
        else  me->delete_temp("htz/pobing");
        me->start_perform(3, "「履霜破冰掌」");
		return 1;
}

int next1(object me, object target, int i)

{
        string msg;
        int damage, ap,dp;
        object weapon;

        if (!me) return 0;

        weapon = me->query_temp("weapon");
        if (weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("htz/pobing");
                return 0;
        }
        msg = HIY"\n一步越出，后续步伐紧跟，靠近$N近前，双掌外推，印向$n的胸前，昊天掌掌力如潮水般涌向$n。\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1)/10000;
        dp = target->query("combat_exp", 1) * target->query_str(1)/10000;
        if((userp(target)&& random(ap + dp) > dp )|| !userp(target)){
                msg += HIR"$n只觉的一阵大力撞来汹涌澎湃，直撞的自己眼前星光灿烂。\n"NOR;
                damage = me->query_skill("haotian-zhang",1)*3;

				damage += me->query_skill("strike")*3;
				
damage += random(damage);
        if ( damage > 3000 )
				damage = 3000 + (damage - 1000)/10;

		if(damage>= target->query("qi")) damage= target->query("qi")-1;

                target->add("neili",-(300+random(150)));
                target->receive_damage("qi", damage, me);
        if(userp(me) && me->query("env/damage"))
        	tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage+ WHT"点攻击伤害。\n"NOR);
		
if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage+ WHT"点伤害。\n"NOR);
		
        target->receive_wound("qi", damage/2, me);
                msg += damage_msg(damage, "内伤");
                message_vision(msg, me, target);
                COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", me->query_skill("haotian-zhang") /4);

		me->add_temp("apply/damage", me->query_skill("haotian-zhang") /4);

        if(!random(5))
			target->add_condition("no_perform", 1);
        if(!random(5))
			target->add_condition("no_exert", 1);
        if(!userp(target))    target->add_busy(2);
        if (me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        me->add_temp("apply/attack", -me->query_skill("haotian-zhang") /4);

		me->add_temp("apply/damage", -me->query_skill("haotian-zhang") /4);

                me->add("neili",-200);
                me->add("jingli",-80);
                me->start_perform(3, "「履霜破冰掌」");
        }
        else {
                msg  += CYN"\n$n一个纵跳起跃，危急之中躲过致命一击。\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                me->add_busy(random(2));
        }
        if (me->query_skill("haotian-zhang", 1) > 250)
                next2(me, target, i);
        else
                me->delete_temp("htz/pobing");
        return 1;
}

int next2(object me, object target, int i)
{
        string msg;
        int damage, ap, dp;
        object weapon;
        if( !me ) return 0;
        weapon = me->query_temp("weapon");
        if (weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("htz/pobing");
                return 0;
        }
		if (me->query_skill_mapped("leg")!="yuanyang-lianhuantui") return 0;
		
        msg = HIG"\n$n只觉对方劲气绵长不绝，内功着实了得，只得疲于防守，此时$N瞬间收掌，下盘却是一记鸳鸯腿的招式，一腿扫出！\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1)/100000;
        dp = target->query("combat_exp", 1) * target->query_str(1)/100000;
		//100000降低ap,dp，以防溢出 by sohu@xojh
       if(objectp(target)&&((userp(target)&& random(ap + dp) > dp) || !userp(target)))
	   {

                    damage = me->query_skill("haotian-zhang",1)*3;

					damage += me->query_skill("strike",1)*3;

					damage += random(damage);
                if ( damage > 4000 )
					damage = 4000 + (damage - 1000)/100;
				//if( damage>= target->query("qi",1)) damage= target->query("qi",1)-1;

                target->add_temp("apply/attack", -180);
                target->add_temp("apply/dodge", -180);
                target->add_temp("apply/parry", -180);
                target->set_temp("htz/pobing",1);

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
                me->start_perform(3 + random(2),"「履霜破冰掌」");
				if (objectp(target))
				    call_out("back", 5 + random(me->query("jiali") / 20), target);
        } 
        else {
                msg = msg + HIW "$n一个旱地拔葱，跃起数丈，堪堪避过。\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
        me->delete_temp("htz/pobing");
		me->start_perform(3,"履霜破冰掌");
        return 1;
}

void back(object target)
{
        if (!target) return;
        target->add_temp("apply/attack", 180);
        target->add_temp("apply/dodge", 180);
        target->add_temp("apply/parry", 180);
		target->delete_temp("htz/pobing");
		return;
}

string perform_name(){ return HIG"履霜破冰掌"NOR; }
int help(object me)
{
        write(HIC"\n昊天掌之"+RED"「履霜破冰掌」："NOR"\n\n");
        write(@HELP
	昊天掌是王重阳所创全真教的高级掌法，大道初修通九窍，
	又窍原在尾闾穴。先从涌泉脚底冲，涌泉冲起渐至膝。过膝
	徐徐至尾闾，泥丸顶上回旋急。金锁关穿下鹊桥，重楼十二
	降宫室。变化精微，与全真教的全真心法相得益彰。连续使
	出三招，乃是当初马钰纵横江湖的厉害招式。
	注：履霜破冰掌对于阴寒属性掌法有一定克制作用。

	注意：set 昊天掌 断 其功效为打断对方兵器
			
	指令：perform strike.pobing

要求：
	当前内力需求 1000 以上；
	最大内力需求 3500 以上；
	当前精力需求 600 以上；
	基本掌法等级 250 以上；
	先天功的等级 250 以上；
	基本掌法等级 250 以上；
	基本腿法等级 250 以上；
	激发掌法为昊天掌法；
	激发招架为昊天掌或空明拳；
	激发腿法为鸳鸯连环腿；
	激发内功为先天功，
	准备掌法为昊天掌。
HELP
        );
        return 1;
}
