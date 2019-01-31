//sanxian 华岳三神峰
//by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>
void next1(object me, object target);
void next2(object me, object target);

int perform(object me,object target)
{
	int i;
	string msg;
    object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("华岳三神峰只能对战斗中的对手使用。\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("你的内力不够使用华岳三神峰！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力不够使用华岳三神峰！\n");

        if (!weapon ||weapon->query("skill_type")!="blade")
                return notify_fail("你手中无刀怎能使用华岳三神峰？！\n");
		if (me->query_skill("blade",1)<350)
                return notify_fail("你的基本刀法不足350，怎能使用华岳三神峰？！\n");
		if (me->query_skill("force",1)<350)
                return notify_fail("你的基本内功不足350，怎能使用华岳三神峰？！\n");
		
		if (me->query_skill("fanliangyi-dao",1)<350)
                return notify_fail("你的反两仪刀法不足350，怎能使用华岳三神峰？！\n");

        if ( me->query_skill_mapped("blade") != "fanliangyi-dao"
			|| me->query_skill_mapped("blade") != "fanliangyi-dao" )
             	return notify_fail("你必须先激发刀法和招架为反两仪刀法。\n");
      //  if (me->query_temp("flyd/sanshenfeng"))
				// return notify_fail("你正在施展反两仪刀法中的华岳三神峰。\n");
		if (userp(me)&&!me->query("quest/hs/flyd/sanshenfeng/pass"))
             	return notify_fail("你必须先解开这门武技才能施展反两仪刀法。\n");

	message_vision( HIR"$N手中"+weapon->query("name")+HIR"幻起一片刀影，招式却和两仪诀方向完全想反!\n"+
		"$N挥舞起这片刀光却将$n笼罩，令$n感觉前后左右均为刀光所控。\n"NOR,me,target);
	
	me->start_perform(5,"「华岳三神峰」");
	//me->set_temp("flyd/sanshenfeng",1);
	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
	   || random(me->query_int())>target->query_int()/2)
	{
		
		msg = HIC "\n\n$n发现无论如何躲闪都没法避开这招，顿时有些慌乱。\n" NOR;
		target->add_busy(2);
	}
	else {
		msg = HIW "可是$n看破了$N的企图，飞快的向后退去。\n" NOR;
		me->start_busy(1);
	}
	message_vision(msg, me, target);
	if (objectp(target)&&me->is_fighting())
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);

	if (objectp(target)&&me->is_fighting())
		next1(me, target);
	return 1;
}

void next1(object me, object target)
{
	string msg;
	int damage,damage2;
	object weapon;

	if (!me) return ;
		weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("flyd/sanshenfeng");
		return ;
	}

	msg = YEL"\n$N向左转身，身体忽然倒行，从不可思议的角度反手出刀，一刀劈向$n的前胸，端的是凶险万分。\n"NOR;

	if(random(me->query("combat_exp"))>target->query("combat_exp")/2
		||random(me->query_skill("fanliangyi-dao",1))> target->query_skill("dodge",1)/2 )
	{
		msg = msg + HIR"$n躲闪不及，为$N一刀劈中，顿时鲜血四溅。\n"NOR;
		damage = me->query_skill("fanliangyi-dao",1)+me->query_skill("force",1);
		damage += me->query_skill("blade",1);
		damage=damage*me->query_str()/50;
		damage += random(damage);
		
		target->add("neili",-(1000+random(500)));
		if (target->query("neili")<0) target->set("neili",10);
		
		//这里改成统一化学伤害函数 by renlai
		
		//参数1是扣气血
		damage2=COMBAT_D->do_chemis_attack(me,target,1,damage);		
		
		if (wizardp(me)) write("damage2="+damage2);	    
		msg += damage_msg(damage2, "震伤");
		msg = replace_string(msg, "$w", weapon->query("name"));
		msg = replace_string(msg, "$l", "手臂");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-350);
		//me->add("jingli",-100); 公共函数里已经扣除精力
		
	} else {
		msg  =  msg + CYN"$n凭借灵巧的身法躲开了这一招。\n"NOR;
		message_vision(msg, me, target);
		me->start_busy(1+random(2));
		target->start_busy(1+random(2));
	}
	me->start_perform(5,"华岳三神峰");

	if (objectp(target)&&me->is_fighting())
		next2(me, target);
	return;

}

void next2(object me, object target)
{
	string msg;
	int damage,damage2;
	object weapon;

	if( !me) return ;

	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("flyd/sanshenfeng");
		return ;
	}

	msg = HIG "\n$N身子飘忽，闪烁不定，刀法忽起忽落，"+weapon->query("name")+HIG"横削切磨的招式不断罩向$n。\n"NOR;

	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
		||random(me->query_str()) >target->query_dex()/3)
	{
		msg = msg + HIC "$n这"+weapon->query("name")+HIC"前后左右笼罩$n，顿时为刀光所困住！\n"NOR;
		damage = me->query_skill("fanliangyi-dao",1)+me->query_skill("force",1);
		damage += me->query_skill("blade",1);
		damage=damage*me->query_str()/50;
		damage += random(damage);
		
		//if (!target->is_busy()) target->start_busy(damage/500);
		
		target->add_temp("apply/attack", -200);
		target->add_temp("apply/dodge", -200);
		target->add_temp("apply/parry", -200);
		//target->receive_damage("qi", damage,me);
		//target->receive_wound("qi", damage/3,me);
		//化学伤害
		damage2=COMBAT_D->do_chemis_attack(me,target,1,damage);		
				if (wizardp(me)) write("damage3="+damage2);

		msg += damage_msg(damage, "砍伤");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "手臂");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-350);
		//me->add("jingli",-150);
		if (objectp(target))
			call_out("back", 5+random(5), target);
	} else {
		msg = msg + HIW "$n运起轻功，向前一跃，躲开一旁。\n" NOR;
		message_vision(msg, me, target);
		me->start_busy(1 + random(2));
		target->start_busy(1+random(2));
	}
	me->delete_temp("flyd/sanshenfeng");
	me->start_perform(4,"华岳三神峰");
	return;
}

void back(object target)
{
	if (!target) return;
	target->add_temp("apply/attack", 200);
	target->add_temp("apply/dodge", 200);
	target->add_temp("apply/parry", 200);
}
string perform_name(){ return RED"华岳"MAG"三"HIC"神峰"NOR; }

int help(object me)
{
   write(WHT"\n反两仪刀法之「"HIG"华岳三神峰"WHT"」："NOR"\n");
   write(@HELP
	此套刀法的步法招数与「昆仑派」的「正两仪剑法」一样，
	均从四象八卦中变化而出，都有八八六十四般变化。当初
	华山高矮二长老在光明顶一战，世人方知道这反两仪刀也
	是了不得的绝学。
	华岳三神峰乃是反两仪刀绝学，施展后会三招刀法连续出
	威力巨大。

	指令：perform blade.sanshenfeng

要求：
	当前内力 1000 以上；
	当前精力 1000 以上；
	反两仪刀法 350 以上；
	基本刀法 350 以上；
	基本内功 350 以上；
	激发刀法为反两仪刀法；
	手中持刀；

HELP
   );
   return 1;
}
