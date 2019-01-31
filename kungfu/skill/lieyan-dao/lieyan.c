// guangming.c  圣火烈焰
// By River@SJ

#include <ansi.h>
inherit F_SSERVER;
//#include <combat.h>

//#include "/kungfu/skill/eff_msg.h";
string perform_name(){ return HIC"圣火烈焰"NOR; }

string *xue_name = ({ 
"劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
"幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
}); 

string *limb=({
"颈部","后心","右腿","头部","小腹","胸口","腰间","裆部","右肩","右臂","右脚",
});

int perform(object me, object target)
{
	object weapon;
	int damage, p, ap, dp,lvl,lvl1;
	string msg,name,dodge_skill,limbs;
    weapon=me->query_temp("weapon");
	if(!target) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「圣火烈焰」只能对战斗中的对手使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	 ||(string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");
                
	if((int)me->query_skill("lieyan-dao", 1) < 100 )
		return notify_fail("你的烈焰刀法不够娴熟，不会使用「圣火烈焰」。\n");

	if ( !me->query_skill("jiuyang-shengong", 1))
	if ( me->query_skill("shenghuo-shengong", 1) < 100 )
		return notify_fail("你的圣火神功不够高，不能使用「圣火烈焰」。\n");
                        
	if((int)me->query_skill("piaoyi-shenfa", 1) < 100 )
		return notify_fail("你的飘翼身法不够高，不能使用「圣火烈焰」。\n");

	if( me->query_skill("hand",1)<100 )
		return notify_fail("你的基本手法不够高，不能使用「圣火烈焰」。\n");

	if( me->query_skill("yingzhua-shou",1)<100 )
		return notify_fail("你鹰爪擒拿手不够高，不能使用「圣火烈焰」。\n");

	if((int)me->query("jingli", 1) < 300 )
		return notify_fail("你的精力修为不够，不能使用「圣火烈焰」。\n");

	if( me->query_skill_mapped("blade") != "lieyan-dao")
		return notify_fail("你现在的状态无法使用「圣火烈焰」。\n");
    if( me->query_temp("mj/lieyan"))
		return notify_fail("你现在正在使用「圣火烈焰」绝技。\n");

	if ((int)me->query("max_neili",1) < 1400)
		return notify_fail("你的最大内力不够，无法使用「圣火烈焰」。\n");

	msg = HIC"\n$N大吼一声："HIR"为善除恶，惟光明故，喜乐悲愁，皆归尘土"HIC"。"+weapon->query("name")+HIC"和人合二为一，带着漫天杀气扑向$n。\n"NOR;
    me->set_temp("mj/lieyan",1);
	ap = me->query("combat_exp", 1) / 1000 * me->query_skill("blade");
	dp = target->query("combat_exp", 1) / 1000 * target->query_skill("parry");
	me->add_temp("apply/damage",me->query_skill("lieyan-dao",1)/6);
	if( random(ap + dp) > dp || random(me->query_str())>target->query_con()/2) {
		limbs= limb[random(sizeof(limb))];
		msg +=WHT"$n只觉得所有退路都被这逼人的杀气笼罩，避无可避，不由大惊失色，登时眼前一花，"+weapon->name()+CYN"已从其"+limbs+"洞穿而出！\n"NOR;
		//调整,调低威力
		/*if (!userp(target))
		    target->start_busy(1+random(2));*/
		damage = me->query_skill("blade",1);
		damage += me->query_skill("lieyan-dao",1);
		damage += me->query_skill("shenghuo-shengong",1);
		damage += me->query_skill("yingzhua-shou",1);
		damage *= 4;
		damage += random(damage/2);
		if (!userp(me)&& damage>3000) damage=3000; 
		
		if(damage > 4000) damage = 4000 + (damage-4000)/10;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		me->add_temp("apply/attack",damage/7);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),me->query_temp("mj/shenghuo")?3:1);
		me->add_temp("apply/attack",-damage/7);
		me->add("neili", - 150);
		me->add("jingli", - 70);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "割伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "割伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", limbs);
		
		if( me->query_skill("yingzhua-shou",1 ) > 150
	 	 && me->query_skill_mapped("hand") == "yingzhua-shou"
		 && me->query_skill_prepared("hand") == "yingzhua-shou"
		 && me->query("mjyzs/pass")
	     && objectp(target)
		 //&& !target->is_busy()
			 ){
			name = xue_name[random(sizeof(xue_name))];
			msg += HIC"\n$N紧跟着上前一步，乘对方不备之际，左手变掌为鹰爪之势，自左向右抓向$n的"+name+"。\n"NOR;
            if (me->query_skill("lieyan-dao",1)<350) ap = me->query("combat_exp", 1)/ 1000 * me->query_skill("hand")*2; //支持做到350
            else ap = me->query("combat_exp", 1)/ 1000 * me->query_skill("hand");
			dp = target->query("combat_exp", 1) / 1000 * target->query_skill("dodge");
			
			if( random(ap + dp) > dp || living(target)) {
				me->add("neili", -100);
				if (!userp(target))
				   target->add_busy( random(me->query_skill("yingzhua-shou", 1)/50)+1 );
				else target->add_busy(1+random(2));
				msg += HIW"结果$n的"+name+HIW"被抓个正着，全身不由自主的一颤，顿时不可动弹，$N看准时机又出一招。\n"NOR;
				lvl1=me->query_skill("yingzhua-shou", 1);
				weapon->unequip();
                me->add_temp("apply/hand",lvl1/5);

				target->receive_damage("qi",random(1000),me);
			    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
                me->add_temp("apply/hand",-lvl1/5);
				weapon->wield();
			 }  
		 }
		//message_vision(msg,me,target);
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
	//	message_vision(msg, me, target);
		me->add("neili", -100);
		me->start_busy(1);
	}
	//message_vision(msg, me, target);
	message_vision(msg,me,target);
	me->add_temp("apply/damage",-me->query_skill("lieyan-dao",1)/6);
	me->start_perform(4,"「圣火烈焰」");
	me->delete_temp("mj/lieyan");
	return 1;
}

int help(object me)
{
        write(HIC"\n烈焰刀法"+HIR"「圣火烈焰」"NOR"\n");
        write(@HELP
	烈焰刀乃是明教入门级的武功，源自逍遥二仙中范瑶的传授
	范右使武功极为驳杂，当初毁容而打入敌人内部，就为查找
	陷害明教的对头，以哑巴头陀的形象示人与外，实乃明教的
	大功臣。圣火烈焰是将内力逼于刀内，全力一击，将对方打
	残，同时紧跟一招鹰王的招式，极为厉害。
	
	指令：perform blade.lieyan

要求：
	最大内力要求 1400 以上；
	当前精力要求 300 以上；
	基本手法要求 100 以上；
	鹰爪擒拿要求 100 以上；
	烈焰刀法等级 100 以上；
	飘翼身法等级 100 以上；
	圣火神功等级 100 以上；
	激发刀法为烈焰刀法。
	激发手法为鹰爪擒拿手。
另外：
	圣火神功对烈焰刀有附加作用。

HELP
        );
        return 1;
}
