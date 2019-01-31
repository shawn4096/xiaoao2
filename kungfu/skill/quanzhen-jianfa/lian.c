// modified by snowman@SJ 05/12/2000
// Modify By River@Sj
// Modify By jpei


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
        int i = me->query_skill("haotian-zhang",1) / 2 + me->query_skill("quanzhen-jianfa",1) /2 ;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("三连环只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你的内功不是先天功，无法使用三连环！\n");

        if(me->query("quest/quanzhen/sword/lianhuan")!=1)
                return notify_fail("你虽然听说过三连环绝技，但是一直没有领悟其中诀窍，还不会运用！\n");

        if( me->query_skill("xiantian-gong", 1) < 400 )
                return notify_fail("你的内功还未练成，不能使用三连环！\n");

        if( me->query_skill("quanzhen-jianfa", 1) < 400 )
                return notify_fail("你的剑法还未练成，不能使用三连环！\n");
        if( me->query_skill("sword", 1) < 400 )
                return notify_fail("你的基本剑法还未练成，不能使用三连环！\n");

        if (!objectp(weapon = me->query_temp("weapon")) 
        || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "quanzhen-jianfa")
                return notify_fail("你手里没有剑，无法使用三连环！\n");
   
        if (me->query_skill_prepared("strike") != "haotian-zhang"
            || me->query_skill_mapped("strike") != "haotian-zhang")
                return notify_fail("你没有激发并使用昊天掌，现在无法使用「三连环」进行攻击。\n");  

        if(me->query_skill_mapped("parry") != "quanzhen-jianfa"
        && me->query_skill_mapped("parry") != "kongming-quan")
                return notify_fail("你的招架功夫不对，无法使用三连环！\n");

        if(me->query("max_neili") < 3500 )
                return notify_fail("你的内力修为不够，不能使用三连环！\n");
        if(me->query("neili") < 1000 )
                return notify_fail("你现在真气不足，不能使用三连环！\n");
        if(me->query("jingli") < 600 )
                return notify_fail("你现在精力不足，不能使用三连环！\n");
        if(me->query_temp("qzjf/lian"))
                return notify_fail("你正在使用三连环！\n");

        if(me->query_skill("sword", 1) < 250 )
                return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用三连环。\n");


        msg = HBRED"\n$N使出全真剑法「三连环」绝招，忽然剑交左手，举剑平刺，迅捷无比，当真是星芒电闪，去势绝快！\n"NOR;
              message_vision(msg, me, target);

            me->start_perform(3, "「三连环」");
            me->add_temp("apply/attack", me->query_skill("quanzhen-jianfa") /4);

			me->add_temp("apply/damage", me->query_skill("quanzhen-jianfa") /4);
            me->set_temp("qzjf/lian", 1);
             
        //第一招攻击
        if (me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("quanzhen-jianfa") /4);
		
me->add_temp("apply/damage", -me->query_skill("quanzhen-jianfa") /4);

        me->add("neili", -150);

        if ( me->query_skill("xiantian-gong", 1) > 250)
                next1(me, target, i);
        else 
                me->delete_temp("qzjf/lian");
        return 1;
}

int next1(object me, object target, int i)

{
        string msg;
        int damage, ap,dp;
        object weapon;

        if (!me) return 0;

        weapon = me->query_temp("weapon");
        if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("qzjf/lian");
                return 0;
        }
        msg = HIR"\n紧跟着$N欺身近前，一掌印在$n胸前，昊天掌掌力急吐。\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_con(1)/10000;
        dp = target->query("combat_exp", 1) * target->query_con(1)/10000;
        if((userp(target)&& random(ap + dp) > dp )|| !userp(target))
		{
                msg += HBRED+HIW"$n只觉腾的一阵大力撞来，直撞的自己眼冒金星。\n"NOR;
                damage = me->query_skill("quanzhen-jianfa",1)*3;

				damage += me->query_skill("sword",1)*3;
				damage+=me->query_skill("xiantian-gong",1)*3;
				
damage += random(damage);
			if ( damage > 5000 )
				damage = 5000 + (damage - 5000)/100;

		
			if(damage>= target->query("qi")) damage= target->query("qi")-1;

                target->add("neili",-(300+random(150)));
                target->receive_damage("qi", damage, me);
			if(userp(me) && me->query("env/damage"))
				tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage+ WHT"点攻击伤害。\n"NOR);
			
if(userp(target)&& target->query("env/damage"))
				tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage+ WHT"点伤害。\n"NOR);
			
        target->receive_wound("qi", damage/3, me);
					msg += damage_msg(damage, "内伤");
					message_vision(msg, me, target);
					COMBAT_D->report_status(target, random(2));


                me->add("neili",-200);
                me->add("jingli",-80);
                me->start_perform(3, "「三连环」");
        }
        else {
                msg  += CYN"\n$n一个懒驴打滚，危急之中躲过致命一击。\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                me->add_busy(random(2));
        }
		//剑招

		me->add_temp("apply/attack", me->query_skill("haotian-zhang") /4);
		me->add_temp("apply/damage", me->query_skill("haotian-zhang") /4);

			if(!random(4))
				target->add_condition("no_perform", 1);
			if(!random(4))
				target->add_condition("no_exert", 1);
			if(!userp(target))    target->add_busy(2);
		   
			message_vision(HIC"$N手中"+weapon->query("name")+"挽了个剑花，剑指天南，瞬间回旋连抖三下急刺$n！\n"NOR,me,target);
			if (me->is_fighting(target))
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
			me->add_temp("apply/attack", -me->query_skill("haotian-zhang") /4);

			me->add_temp("apply/damage", -me->query_skill("haotian-zhang") /4);

        if (me->query_skill("quanzhen-jianfa", 1) > 250)
                next2(me, target, i);
        else
                me->delete_temp("qzjf/lian");
        return 1;
}

int next2(object me, object target, int i)
{
        string msg;
        int damage, ap, dp;
        object weapon;
        if( !me ) return 0;
        weapon = me->query_temp("weapon");
        if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("qzjf/lian");
                return 0;
        }

        msg = HIC"\n就在$n疲于防守之际，$N手中长剑做势欲刺，当下却是一腿扫出！\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_str(1)/100000;
        dp = target->query("combat_exp", 1) * target->query_str(1)/100000;
		//100000降低ap,dp，以防溢出 by sohu@xojh
       if(objectp(target)&&((userp(target)&& random(ap + dp) > dp) || !userp(target)))
	   {

                    damage = me->query_skill("quanzhen-jianfa",1)*3;

					damage += me->query_skill("sword",1)*3;

					
					damage+=me->query_skill("xiantian-gong",1)*3;
					damage += random(damage);
                if ( damage > 6000 )
					damage = 6000 + (damage - 6000)/100;
				//if( damage>= target->query("qi",1)) damage= target->query("qi",1)-1;
				if (!target->query_temp("qzjf/lian"))
				{
					target->add_temp("apply/attack", -80);
					target->add_temp("apply/dodge", -80);
					target->add_temp("apply/parry", -80);
					target->set_temp("qzjf/lian",80);
					if (objectp(target))
						call_out("back", 5 + random(me->query("jiali") / 20), target);

				}

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                
				msg += damage_msg(damage, "瘀伤");
                message_vision(msg, me, target);

        if(objectp(target) && me->query("env/damage"))
			tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage+ WHT"点攻击伤害。\n"NOR);
		//
if(userp(target)&& target->query("env/damage"))
			//tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage+ WHT"点伤害。\n"NOR);
		
COMBAT_D->report_status(target, random(2));

                me->add("neili",- 150);
                me->add("jingli",-80);
                me->start_perform(3 + random(2),"「三连环」");
        } 
        else {
                msg = msg + HIW "$n一个旱地拔葱，跃起数丈，堪堪避过。\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
        }
		me->add_temp("apply/attack", (int)me->query_skill("xiantian-gong") /4);

		me->add_temp("apply/damage", (int)me->query_skill("xiantian-gong") /4);
        message_vision(RED"$N剑尖一阵晃动，顺手点出一片寒星！将$n笼罩在一片剑光中！\n"NOR,me,target);
		if (me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -(int)me->query_skill("xiantian-gong") /4);

	    me->add_temp("apply/damage", -(int)me->query_skill("xiantian-gong") /4);

        me->delete_temp("qzjf/lian");
        return 1;
}

void back(object target)
{
        if (!target||!target->query_temp("qzjf/lian")) return;
		target->delete_temp("qzjf/lian");
        target->add_temp("apply/attack", 80);
        target->add_temp("apply/dodge", 80);
        target->add_temp("apply/parry", 80);
		tell_object(target,HIC"你周身真气一震，经脉豁然贯通，将全真剑法连环诀的虚弱卸掉！\n"NOR);
		return;
}

string perform_name(){ return HIG"三连环"NOR; }
int help(object me)
{
        write(HIG"\n全真剑法之"+RED"「三连环」："NOR"\n\n");
        write(@HELP
	全真剑法是王重阳所创全真教的入门剑法，大道初修通九窍，
	又窍原在尾闾穴。先从涌泉脚底冲，涌泉冲起渐至膝。过膝
	徐徐至尾闾，泥丸顶上回旋急。金锁关穿下鹊桥，重楼十二
	降宫室。变化精微，与全真教的全真心法相得益彰。
	连续使出三招，乃是当初丘处机纵横江湖的厉害招式，若机
	缘巧合，解开此项绝技，则全真剑法的威力非凡。
	
	指令：perform sword.lian

要求：
	当前内力需求 1000 以上；
	最大内力需求 3500 以上；
	当前精力需求 600 以上；
	全真剑法等级 400 以上；
	先天功法等级 400 以上；
	基本剑法等级 400 以上；
	激发剑法为全真剑法；
	激发招架为全真剑法或空明拳；
	激发内功为先天功，
	激发掌法为昊天掌并准备。
HELP
        );
        return 1;
}
