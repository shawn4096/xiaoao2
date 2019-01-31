//xiao, cred by sohu@sojh yangxiao 的武技演化而来

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int next1(object me, object target, int skill);
int next2(object me, object target);

int perform(object me,object target)
{
        object weapon1,tweapon;
        string msg;
		int ap,dp,dam;
        int skill = me->query_skill("xiaoyao-jian",1);
        
        weapon1=me->query_temp("weapon");
        tweapon=target->query_temp("weapon");
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("「啸字诀」只能对战斗中的对手使用。\n");
      

        if( me->query_skill("shenghuo-shengong", 1) < 300 )
                return notify_fail("你的内功还未练成，不能使用「啸字诀」！\n");

        if( me->query_skill("xiaoyao-jian", 1) < 300 )
                return notify_fail("你的逍遥剑法还未练成，不能使用「啸字诀」！\n");

        if (!objectp(weapon1 = me->query_temp("weapon")) 
        || weapon1->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "xiaoyao-jian")
                return notify_fail("你手里没有剑，无法使用「啸字诀」！\n");

        if(me->query_skill_mapped("parry") != "xiaoyao-jian"
        && me->query_skill_mapped("parry") != "qiankun-danuoyi")
                return notify_fail("你的招架功夫不对，无法使用「啸字诀」！\n");
        if(me->query("max_neili") < 3000 )
                return notify_fail("你的最大内力修为不够，不能使用「啸字诀」！\n");
        if(me->query("neili") < 500 )
                return notify_fail("你现在真气不足，不能使用「啸字诀」！\n");
        if(me->query("jingli") < 600 )
                return notify_fail("你现在精力不足，不能使用「啸字诀」！\n");
       // if(me->query_temp("xyjf/xiao"))
             //   return notify_fail("你正在使用「啸字诀」！\n");

        if(me->query_skill("sword", 1) < 300 )
                return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用「啸字诀」。\n");

       // if( target->is_busy() )
         //       return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        msg = HIW"\n$N仰天长啸，使出逍遥剑法「啸字诀」。只震得四下里木叶簌簌乱落。配合$N的一袭白衫，当真潇洒无比。\n"NOR;
        me->start_perform(4, "「啸字诀」");
		//第一招判断 exp int
        ap = me->query("combat_exp") /1000;
        dp = target->query("combat_exp")/1000;
       // me->set_temp("xyjf/xiao", 1);
        if( random(ap + dp ) > dp||random(me->query_con())> target->query_con()/2) {
                msg += MAG "为$N的长啸之声所影响，身形顿时不由地一滞。\n" NOR;
                target->add_busy(1); 
				if (!userp(target))
					target->add_busy(2+random(2));
                me->add("neili", -150);
				message_vision(msg, me, target);
		
        }
        else {
                me->add("neili", -80);
                msg += MAG "可是$n战斗经验异常丰富，运功于耳，并没有受到丝毫影响。\n" NOR;
                me->start_busy(random(2));
				message_vision(msg, me, target);				
        }
           //message_vision(msg, me, target);
               me->add_temp("apply/attack", (int)me->query_skill("xiaoyao-jian") /4);
		        me->add_temp("apply/damage", (int)me->query_skill("xiaoyao-jian") /4);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
                me->add_temp("apply/attack", -(int)me->query_skill("xiaoyao-jian") /4);
	            me->add_temp("apply/damage", -(int)me->query_skill("xiaoyao-jian") /4);

		if (me->is_fighting(target))
                next1(me,target,skill);
		else  me->delete_temp("xyjf/xiao");
		
        //me->start_perform(1,"啸字诀");
        return 1;
}

int next1(object me, object target, int skill)
{
        string msg;
        int damage, ap,dp;
		object weapon1,tweapon;
        weapon1=me->query_temp("weapon");
        tweapon=target->query_temp("weapon");
        if (!me) return 0;
    
        if (!weapon1 || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("xyjf/xiao");
                return 0;
        }
		if (objectp(tweapon))
		{
			message_vision(HIY"$N趁$n身形一滞的当下，不见$N提足抬腿，突然之间倒退丈余，一转身，又已在$n周身咫尺。\n"+
					HIG"$N伸手向$n手中的"+tweapon->query("name")+HIG"抓去。\n"NOR,me,target);
            if (random(me->query("combat_exp") )>target->query("combat_exp")/3)
            {
				message_vision(HIC"$n冷不防为$N夺下手中的"+tweapon->query("name")+",却见$N随手投掷与地，不管不问，竟然扬长而去。\n"+
					"$n顿时为之气结，愣在当场气的说不出话来。\n"NOR,me,target);
				tweapon->move(environment(me));
				target->add_busy(1+random(2));           
			}
			else message_vision(HIC"$n见$N如此轻视自己，心情大怒，但仍然保持冷静的头脑。\n"NOR,me,target);
		}
		damage = skill*4+me->query_skill("force",1);
        damage += me->query_skill("sword",1);
        damage += 2*damage+random(damage);
        if ( damage > 4000 )
                        damage = 4000 + (damage - 4000)/10;
        
		msg = HIR"\n紧跟着$N剑锋一转，欺身近前，挥剑如电，反手便刺伤$n的左肋。\n"NOR;
        ap = me->query("combat_exp", 1) /10000;
        dp = target->query("combat_exp", 1) /10000;
        if( random(ap + dp) > dp ||random(me->query_str(1))>target->query_con(1)/3){
                msg += RED"$n只觉左肋一痛，鲜血狂泻而出。\n"NOR;
              
                target->add("neili",-(300+random(150)));
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/3,me);
                msg += damage_msg(damage, "刺伤");
                msg = replace_string(msg, "$w", weapon1->name());
                msg = replace_string(msg, "$l", "「期门穴」");
                message_vision(msg, me, target);
                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+damage+ WHT"点攻击伤害。\n"NOR);
				
if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+damage+ WHT"点伤害。\n"NOR);

				COMBAT_D->report_status(target, random(2));
				if (!userp(target))
			    {        
					me->add_temp("apply/attack", (int)me->query_skill("xiaoyao-jian") /3);
					me->add_temp("apply/damage", (int)me->query_skill("xiaoyao-jian") /4);
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(2)?3:1);
					me->add_temp("apply/attack", -(int)me->query_skill("xiaoyao-jian") /3);
					me->add_temp("apply/damage", -(int)me->query_skill("xiaoyao-jian") /4);
				}
				me->add("neili",-200);
                me->add("jingli",-80);
                me->start_perform(2, "「啸字诀」");
        }
		
        else {
                msg  += CYN"$n意识到危险，危急反向转身，躲过这猝然一击。\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                me->add_busy(random(2));
        }
        if (me->is_fighting(target))
               next2(me, target);
        else 
            me->delete_temp("xyjf/xiao");
        return 1;
}

int next2(object me, object target)
{
        string msg;
        int ap, dp,damage,skill;
		object weapon1,tweapon;
        weapon1=me->query_temp("weapon");
        tweapon=target->query_temp("weapon");
		
		skill=me->query_skill("xiaoyao-jian",1);
        
		if( !me ) return 0;
        if (!weapon1 || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("xyjf/xiao");
                return 0;
        }

        msg = HIR"\n就在$n为$N凌厉的招式袭击而疲于防守之际，$N又运起内劲，啸声激荡，风驰电掣地刺出一剑。\n"NOR;
        ap = me->query("combat_exp")/1000;
        dp = target->query("combat_exp")/1000;
        if( random(ap + dp) > dp ||random(me->query_str())>target->query_dex()/3) {
                msg += HIW "$N手中的"+weapon1->query("name")+HIW+"神出鬼没，突然一剑正刺中$n的" +HIC"「关元穴」"+HIW + "。\n"NOR;
                
				damage = skill*4+me->query_skill("force",1);
				damage += me->query_skill("sword",1);
				damage += 2*damage+random(damage);
				damage+=me->query_skill("qiankun-danuoyi",1);
				damage *=4;
                damage += random(damage);
                if ( damage > 5000 )
                        damage = 5000 + (damage - 5000)/10;
               
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
				target->add_busy(1);
                msg += damage_msg(damage, "刺伤");
                msg = replace_string(msg, "$w", weapon1->name());
                msg = replace_string(msg, "$l", "「关元穴」");
                message_vision(msg, me, target);
                COMBAT_D->report_status(target, random(2));
			    
				if (!userp(target))
			    {
			    
					me->add_temp("apply/attack",(int)me->query_skill("xiaoyao-jian") /2);
					me->add_temp("apply/damage", (int)me->query_skill("xiaoyao-jian") /4);
					
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
					me->add_temp("apply/attack", -(int)me->query_skill("xiaoyao-jian") /2);
					me->add_temp("apply/damage", -(int)me->query_skill("xiaoyao-jian") /4);
					me->add("neili",- 150);
					me->add("jingli",-80);
				}
                //me->start_perform(3 + random(2),"「啸字诀」");
                //call_out("back", 5 + random(me->query("jiali") / 20), target);
        } 
         else {
                msg = msg + HIW "$n不为所动，游刃有余，胜似闲庭信步，轻轻避过这招。\n" NOR;
                message_vision(msg, me, target);
                me->add("neili", -70);
                me->add_busy(random(2));
				//me->start_perform(2 + random(2),"「啸字诀」");
        }
        me->delete_temp("xyjf/xiao");
		me->start_perform(3 + random(2),"「啸字诀」");
        return 1;
}


string perform_name(){ return HIR"啸字诀"NOR; }
int help(object me)
{
        write(HIG"\n逍遥剑法之"+HIR"「啸字诀」"NOR"\n\n");
        write(@HELP
	杨逍乃是明教光明左使，与范遥合称”逍遥二仙“。一身武功极其驳杂，
	最具代表性的即为这逍遥剑法，当年少林寺一战，杨逍以资深武功和
	少林三老一番大战，其武功之庞杂与怪异表现的淋漓尽致，连平素一
	项都不服气的范遥都深为叹服。
	
	指令：perform sword.xiao

要求：
	当前内力要求 500 以上；
	最大内力要求 3000 以上；
	当前精力要求 600 以上；
	逍遥剑法等级 300 以上；
	圣火神功等级 300 以上；
	基本剑法等级 300 以上；
	激发剑法为逍遥剑法；
	激发招架为逍遥剑法或乾坤大挪移；
	激发内功不限。
HELP
        );
        return 1;
}
