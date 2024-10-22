// huixuan.c 回旋十三式

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HIY"回旋十三式"NOR; }

int perform(object me, object target)
{
	string msg;
	object weapon;
	int times, ap, dp,i;

	if( !target ) target = offensive_target(me);

	weapon = me->query_temp("weapon");

	if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target) )
		return notify_fail("「回旋十三式」只能在战斗中使用。\n");

	if( !weapon || weapon->query("skill_type") != "whip"
	 || me->query_skill_mapped("whip") != "huifeng-bian"
	 || me->query_skill_mapped("parry") != "huifeng-bian")
		return notify_fail("你现在无法使用「回旋十三式」！\n");

//	if( target->is_busy() )
//		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

	if( (int)me->query_skill("huifeng-bian", 1) < 300 )
		return notify_fail("你的回风鞭法不够娴熟，不会使用「回旋十三式」绝技。\n");

	if( (int)me->query_skill("huntian-qigong", 1) < 300 )
		return notify_fail("你的混天气功不够深厚，不会使用「回旋十三式」。\n");

	if( (int)me->query("max_neili", 1) < 3500 )
		return notify_fail("你的内力修为不够，不能使用「回旋十三式」。\n");

	if( (int)me->query("neili") < 500 )
		return notify_fail("你现在内力太弱，不能使用「回旋十三式」。\n");

	if( me->query_skill_mapped("strike") != "lianhua-zhang" && me->query_skill_prepared("strike") != "lianhua-zhang")
		if (me->query_skill_mapped("hand") != "suohou-shou" && me->query_skill_prepared("hand") != "suohou-shou" )
		 return notify_fail("你现在激发的掌法不是莲花掌或激发的手法不是锁喉擒拿手，不能使用「回旋十三式」。\n");
 
	if( (int)me->query_temp("huixuan") )
		return notify_fail("你现在正在使用「回旋十三式」。\n");

	msg = HIY+"\n$N""突然身形如陀螺般急转数圈，手中的"+weapon->name()+HIY+"连出十三种"HIW"幻化莫测"HIY"的招式，罩向$n的周身！\n"NOR;

	ap = me->query("combat_exp", 1)/ 1000 * me->query_skill("whip");
	dp = target->query("combat_exp", 1)/ 1000 * target->query_skill("parry");

	if( random( ap + dp)  > dp ||random(me->query_int(1))>target->query_int(1)/3 ) {
		msg += HIR+"$n一个没留神，被$N变幻莫测的招式所惑，罩在幻象般的鞭影里！\n"NOR;
		me->start_perform(10 , "回旋十三式");
		times = random(me->query_skill("whip")/20) + 4;
		if( times <  6 ) times = 6;
		if( times > 13 ) times = 13;
		me->set_temp("huixuan", times);
		if( wizardp(me) ) tell_object(me, HIY"回旋十三式有 "+times+" 次。\n"NOR);
		
		message_vision(msg, me, target);
			
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	    
		me->start_busy(1+random(1));
		
		if( !userp(target) ) target->add_busy(1+random(2));
		
		call_out("huixuan", 1, me, target);
	}
	else {
		msg += CYN + "可是$n成竹在胸，抢中宫直进，从容不迫的摆脱了缠绕。\n"NOR;
		me->start_perform(3 , "回旋十三式");
		me->start_busy(random(2));
		message_vision(msg, me, target);
	}
	me->add("neili", -200);
	return 1;
}

int huixuan(object me, object target)
{
	int lvl, ap, dp, times,i;
	object weapon;

	if( !me ) return 0;

	weapon = me->query_temp("weapon");

	if( !objectp(target) ) {
		message_vision(HIY+"\n$N"+HIY+"内力已尽，"+weapon->query("name")+HIY+"软绵绵的垂将下来。\n"NOR,me);
		me->start_perform(1 , "回旋十三式");
		me->delete_temp("huixuan");
		me->delete_temp("hfb/budai");
		return 1;
	}

	if( !objectp(me)&&!me->is_fighting() ) {
		message_vision(HIY+"\n$N"+HIY+"内力已尽，"+weapon->query("name")+HIY+"软绵绵的垂将下来。\n"NOR,me);
		me->start_perform(1 , "回旋十三式");
		me->delete_temp("huixuan");
		me->delete_temp("hfb/budai");
		return 1;
	}

	if( !living(me) || me->is_ghost() ) {
		me->start_perform(1 , "回旋十三式");
		me->delete_temp("huixuan");
		me->delete_temp("hfb/budai");
		return 1;
	}

	if( !weapon || weapon->query("skill_type") != "whip"
	 || me->query_skill_mapped("whip") != "huifeng-bian"
	 || me->query_skill_mapped("parry") != "huifeng-bian" ) {
		me->start_perform(1 , "回旋十三式");
		me->delete_temp("huixuan");
		me->delete_temp("hfb/budai");
		return 1;
	}

	if( me->query_temp("huixuan") < 1 ) {
		message_vision(HIY+"\n$N"+HIY+"内力已尽，"+weapon->query("name")+HIY+"软绵绵的垂将下来。\n"NOR,me);
		me->start_perform(1 , "回旋十三式");
		me->delete_temp("huixuan");
		me->delete_temp("hfb/budai");
		return 1;
	}
/*
	if( me->is_busy() ) {
		call_out("huixuan", 1, me, target);
		return 1;
	}*/

	lvl = me->query_skill("huifeng-bian", 1);

	ap = me->query("combat_exp")/ 100000 * me->query_skill("whip",1);
	dp = target->query("combat_exp")/ 100000 * target->query_skill("dodge",1);

	me->start_perform(10 , "回旋十三式");

	if( random(ap + dp)  > dp/3 ) {
		if( weapon->query("id") == "po budai" ) {
			message_vision( HIR+me->query("name")+"将手中的"+weapon->query("name")+HIR"向$n头上一罩。\n"NOR, me, target);
			tell_object(target,BLU"你觉得脸上一阵剧痛，啊！！！你被蝎子咬了。\n"NOR);
			if (!target->is_busy()) target->start_busy(1+random(3));
			else target->add_busy(1+random(3));
			target->receive_wound("qi", me->query_skill("whip",1)/3, me);
			target->receive_wound("jing", me->query_skill("whip",1)/3, me);
			target->add_condition("scorpion_poison", 5+random(2));
			target->set_temp("hfb/budai",1);
		}
		message_vision(HIR"\n$n被眼前"+weapon->query("name")+HIR"所幻化出的重重"HIW"鞭影"HIR"完全迷惑住了，$N乘此良机连连出招！"NOR, me, target);
		if( !userp(target) ) 
		   target->add_busy(2+random(2));			
	    else 
			lvl=lvl/3;
        if (me->query("gender")!="女性")
			lvl=lvl/2;
		//连击术
		me->add_temp("apply/whip", lvl/3);
		me->add_temp("apply/attack", lvl/3);
		me->add_temp("apply/damage", lvl/6);
		target->add_temp("apply/dodge", - me->query_skill("whip", 1)/4);
		//times=me->query_temp("huixuan");
	
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		me->add_temp("huixuan", -1);

		if( me->is_fighting(target) ) {
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
			me->add_temp("huixuan", -1);
		}
		if (me->query_skill_prepared("strike")=="lianhua-zhang"&&me->is_fighting()&&objectp(target)&&me->query("gender")=="女性")
		{
			weapon->unequip();
            me->add_temp("apply/strike",lvl/4);
			message_vision(HIM"$N放下手中的"+weapon->query("name")+HIW"使出丐帮绝技莲花掌，正是闻名江湖的花开并蒂。\n"NOR,me,target);
		    COMBAT_D->do_attack(me, target,0, userp(me)?3:1);
            COMBAT_D->do_attack(me, target,0, userp(me)?3:1);
            me->add_temp("apply/strike",-lvl/4);
			weapon->wield();

		}else if (me->query_skill_prepared("hand")=="suohou-shou"&&me->is_fighting()&&objectp(target)&&me->query("gender")=="男性")
		{
			weapon->unequip();
            me->add_temp("apply/hand",lvl/4);
			message_vision(HIW"$N放下手中的"+weapon->query("name")+HIW"使出丐帮绝技锁喉擒拿手，瞬间拿住对方的周身大穴。\n"NOR,me,target);
			message_vision(HIC"紧接着又施展出锁喉绝技，手呈鹰抓状捏住了$n的咽喉。\n"NOR,me,target);
			target->add_busy(2+random(2));
		    COMBAT_D->do_attack(me, target,0, userp(me)?3:1);            
            me->add_temp("apply/hand",-lvl/4);
			weapon->wield();
		}
		me->add_temp("apply/whip", -lvl/3);
		me->add_temp("apply/attack", -lvl/3);
		me->add_temp("apply/damage", -lvl/6);
		target->add_temp("apply/dodge", me->query_skill("whip", 1)/4);
	}

	times = me->query_temp("huixuan");
	times=times-1;
	if (objectp(target)&&me->is_fighting())
				call_out("huixuan", 1, me, target);
	else call_out("remove_effect",0,me);
	
	if( wizardp(me) ) tell_object(me, HIY"回旋十三式被破解，还有 "+times+" 次。\n"NOR);
	return 1;
}

int remove_effect(object me)
{
		if (!objectp(me)) return 1;
		me->delete_temp("huixuan");
		me->delete_temp("hfb/budai");
		message_vision(HIY"$N的回风鞭蓦然收回，缓缓停了下来。\n"NOR,me);
		return 1;

}

int help(object me)
{
	write(HIY"\n回风鞭法「回旋十三式」："NOR"\n");
        write(@HELP
	回风鞭法乃是丐帮陈长老成名绝技，施展起来，劲气纵横，乃是丐帮一门
	非常奇特的外门武技。丐帮因抗辽抗金，侠名远播，使得无数英雄慕名而
	来，这门鞭法若和莲花掌或锁喉擒拿手配合，有出其不意的效果。特别说
	明，丐帮的陈长老因为抓蛇而名闻天下，手中的破布袋乃是一门非常奇特
	的外门兵器。若使用得当，会产生出奇不意的效果。
	注意：男性备锁喉手和女性备莲花掌各有特效,本门武功女性有优势

	指令：perform whip.huixuan
	
要求：
	最大内力  3500 以上；
	当前内力  500 以上；
	回风鞭法等级 300 以上；
	混天气功等级 300 以上；
	需激发莲花掌或锁喉擒拿手。
HELP
        );
        return 1;
}