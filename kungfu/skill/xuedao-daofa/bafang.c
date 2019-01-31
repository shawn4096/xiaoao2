//bafang.c  夜战八方式
//by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>
void next1(object me, object target);
void next2(object me, object target);

int perform(object me,object target)
{
		int damage,skill;
		string msg;
		object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);
		
		skill=me->query_skill("xuedao-daofa",1);
        
		if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「夜战八方式」只能对战斗中的对手使用。\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("你的内力不够使用「夜战八方式」！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力不够使用「夜战八方式」！\n");

        if (!weapon ||weapon->query("skill_type")!="blade")
                return notify_fail("你手中无刀怎能使用「夜战八方式」？！\n");
		if (me->query_skill("blade",1)<220)
                return notify_fail("你的基本刀法不足220，怎能使用「夜战八方式」？！\n");
		if (me->query_skill("force",1)<220)
                return notify_fail("你的基本内功不足220，怎能使用「夜战八方式」？！\n");

		if (me->query_skill("xuedao-daofa",1)<220)
                return notify_fail("你的血刀刀法不足220，怎能使用「夜战八方式」？！\n");

        if ( me->query_skill_mapped("blade") != "xuedao-daofa" )
             	return notify_fail("你必须先激发刀法为血刀刀法。\n");
		if ( me->query_skill_mapped("parry") != "xuedao-daofa" && me->query_skill_mapped("parry") != "jingang-liantishu")
             	return notify_fail("你的招架不对，必须激发刀法为血刀刀法或金刚炼体术。\n");
		if ( me->query_skill_mapped("force") != "xuedao-jing" )
			if ( me->query_skill_mapped("force") != "shenzhao-jing" )
             	return notify_fail("你激发的内功和刀法不符。\n");

        if (me->query_temp("xddf/bafang"))
				return notify_fail("你正在施展血刀刀法中的「夜战八方式」。\n");
		message_vision( HIY"$N手中"NOR+weapon->query("name")+HIY"连砍十五六刀，四面八方都砍遍了，正是血刀经中的“夜战八方式”\n"+
		"同时飞起一足，向$n下盘踢去，随即$N挥刀砍落，四面八方都笼罩住，令$n绝无闪避躲让之处。\n"NOR,me,target);

		me->start_perform(4,"「夜战八方式」");
		me->set_temp("xddf/bafang",1);
		damage=skill+me->query_skill("jingang-liantishu",1)+me->query_skill("xuedao-jing",1);
		damage=damage*me->query_str(1)/15+random(damage);
		//第一招看悟性判断
		if(random(me->query("combat_exp")) > target->query("combat_exp")/2
		   || random(me->query_int())>target->query_int()/2)
		{
			
			msg = HIR "\n\n$n拍的一声轻响，混有骨骼碎裂之声，已砍中了$n的前胸。\n" NOR;
			target->receive_damage("qi",damage,me);
			target->receive_damage("qi",damage/3,me);
			if(userp(me) && me->query("env/damage"))
				   tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage*5/4+ WHT"点攻击伤害。\n"NOR); 

		}
		else {
			msg = HIC "可是$n看破了$N的企图，飞快的向后退去。\n" NOR;
			me->start_busy(1);
		}
		message_vision(msg, me, target);
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/damage",skill/4);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/damage",-skill/4);

		if (objectp(target)&&me->is_fighting())
			next1(me, target);
		else me->delete_temp("xddf/bafang");
		return 1;
}

void next1(object me, object target)
{
	string msg;
	int damage;
	object weapon;

	if (!me) return ;
	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target))
	{
		me->delete_temp("xddf/bafang");
		return ;
	}

	message_vision(HIR"\n$N刀法忽变，连续攻击三十六刀，一刀快似一刀，一口气之数尽快向外劈去，电闪雷鸣，目不暇接。\n"+
		"只要$n撞上了，不死也得重伤，便算不撞上，只要一架一闪，立时便会被陷入刀影中。\n"NOR,me,target);
	
//第二招判断身法和基本武技
	if(random(me->query("dex"))>target->query("dex")/2
		||random(me->query_skill("xuedao-daofa",1))> target->query_skill("dodge",1)/2 )
	{
		msg =  HIY"$n双臂酸麻更甚，只要再给$N这般砍上几刀，$n手臂上的筋络也要给震伤。\n"NOR;
		damage = me->query_skill("xuedao-daofa",1)+me->query_skill("force",1);
		damage += me->query_skill("blade",1);
		damage=damage*me->query_str()/20;
		damage += random(damage);
		
		target->add("neili",-(1000+random(500)));
		if (target->query("neili")<0) target->set("neili",10);
		
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		if (wizardp(me)) write("damage2="+damage);
	    
		msg += damage_msg(damage, "震伤");
		msg = replace_string(msg, "$w", weapon->query("name"));
		msg = replace_string(msg, "$l", "手臂");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		if(userp(me) && me->query("env/damage"))
			   tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage*4/3+ WHT"点攻击伤害。\n"NOR); 

		me->add("neili",-300);
		me->add("jingli",-100);
	} else {
		message_vision(CYN"$n凭借灵巧的身法躲开了这一招。\n"NOR,me, target);
		me->start_busy(1+random(2));
		target->start_busy(1+random(2));
	}
	//me->start_perform(4,"「夜战八方式」");

	if (objectp(target) && me->is_fighting() && me->query_skill("xuedao-daofa",1)>=350)
		next2(me, target);
	else me->delete_temp("xddf/bafang");

	return;

}

void next2(object me, object target)
{
	string msg;
	int damage,skill;
	object weapon;

	if( !me ) return ;

	weapon = me->query_temp("weapon");
	skill=me->query_skill("xuedao-daofa",1);
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("xddf/bafang");
		return ;
	}

	message_vision(HIC "\n$N歪头一阵淫笑不断，手中"NOR+weapon->query("name")+HIC"忽然弯曲如蛇，蜿蜒前行，甚是诡异，蓦然间已刺中$n的右胸口。\n"NOR,me,target);
//第三招和臂力有关
	if(random(me->query("str")) > target->query("str")/2
		||random(me->query_skill("blade",1)) >target->query_skill("parry",1)/3)
	{
		msg = HIC "$n这"NOR+weapon->query("name")+HIC"的一击差点刺中心脏，$n面色大变！\n"NOR;
		damage = me->query_skill("xuedao-daofa",1)+me->query_skill("force",1);
		damage += me->query_skill("blade",1);
		damage=damage*me->query_str()/15;
		damage += random(damage);
		
		//if (!target->is_busy()) target->start_busy(damage/500);
		target->add_temp("apply/attack", -200);
		target->add_temp("apply/dodge", -200);
		target->add_temp("apply/parry", -200);
		
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		
	//	if (wizardp(me)) write("damage3="+damage);

		msg += damage_msg(damage, "砍伤");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "手臂");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		if(userp(me) && me->query("env/damage"))
			   tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage*4/3+ WHT"点攻击伤害。\n"NOR); 

		me->add("neili",-300);
		me->add("jingli",-150);
		if (objectp(target))
			call_out("back", 5+random(5), target);
	} else {
		msg = HIW "$n运起轻功，向前一跃，躲开一旁。\n" NOR;
		message_vision(msg, me, target);
		me->start_busy(1 + random(2));
		target->start_busy(1+random(2));
	}
	me->add_temp("apply/attack",skill/4);
	me->add_temp("apply/damage",skill/4);
	
	me->set_temp("xddf/bafang",1);

    if (me->query_skill("xuedao-daofa",1)>400
	    &&objectp(target)
		&&me->is_fighting())
    {
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

    }
	if (me->query_skill("xuedao-daofa",1)>450
	    &&objectp(target)
		&&me->is_fighting())
    {
		message_vision(HIR"$N须发皆张，呈「怒目金刚相」施展出夜战八方式最后一招,已经呈由魔入佛的境界！\n"NOR,me);
		me->add_temp("apply/blade",skill/4);
		me->add_temp("apply/damage",skill/5);
		me->set_temp("xddf/jingang",1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->delete_temp("xddf/jingang");
		me->add_temp("apply/blade",-skill/4);
		me->add_temp("apply/damage",-skill/5);

    }

	me->add_temp("apply/attack",-skill/4);
	me->add_temp("apply/damage",-skill/4);

	me->delete_temp("xddf/bafang");
	//me->start_perform(4,"「夜战八方式」");
	return;
}




void back(object target)
{
	if (!target) return;
	target->add_temp("apply/attack", 200);
	target->add_temp("apply/dodge", 200);
	target->add_temp("apply/parry", 200);
	return;
}
string perform_name(){ return HIY"夜战八方式"NOR; }

int help(object me)
{
   write(WHT"\n血刀刀法之「"HIY"「夜战八方式」"WHT"」："NOR"\n");
   write(@HELP
	此「夜战八方式」乃巧用血刀经中内劲功夫和身体配合
	连续施展血刀刀法中诡异的招式，以冷不防著称。第一
	招凭借深厚经验和悟性出手，第二招依靠的是身法优势
	如果招式过了350级，可以凭借武技优势或臂力优势出第
	三招来迎战对方。
	注意：第三招极为重要，若对方为你所打中，则会出现
	一定程度的虚弱和忙碌状态。

	指令：perform blade.bafang

要求：
	当前内力 1000 以上；
	当前精力 1000 以上；
	血刀刀法 220 以上；
	基本刀法 220 以上；
	基本内功 220 以上；
	血刀经功 220 以上
	激发刀法为血刀刀法；
	激发内功为血刀经
	激发招架为血刀刀法或金刚护体术；
	手中持刀；

HELP
   );
   return 1;
}
