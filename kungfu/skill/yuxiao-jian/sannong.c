//sannong 梅花三弄
//
//by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>
void next1(object me, object target, int i);
void next2(object me, object target, int i);

int perform(object me,object target)
{
	int i;
	string msg;
    object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("梅花三弄只能对战斗中的对手使用。\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("你的内力不够使用梅花三弄！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力不够使用梅花三弄！\n");

        if (!weapon || !(weapon->id("xiao")))
                return notify_fail("你手中无萧怎能使用梅花三弄？！\n");
		if (me->query_skill("sword",1)<300)
                return notify_fail("你的基本剑法不足300，怎能使用梅花三弄？！\n");
		if (me->query_skill("force",1)<300)
                return notify_fail("你的基本内功不足300，怎能使用梅花三弄？！\n");

		if (me->query_skill("yuxiao-jian",1)<300)
                return notify_fail("你的玉箫剑法不足300，怎能使用梅花三弄？！\n");
       // if (!me->query_temp("yuxiao-jian/luanren",1)||!me->query_temp("yuxiao-jian/nizhuan",1))
               // return notify_fail("你不使用“阴阳(perform yinyang)倒乱(perform nizhuan)刃法”怎么能用梅花三弄封住敌人行动！\n");

        if ( me->query_skill_mapped("sword") != "yuxiao-jian" )
             	return notify_fail("你必须先激发剑法为玉箫剑法。\n");
        if (me->query_temp("yxj/sannong"))
				return notify_fail("你正在施展玉箫剑法中的梅花三弄。\n");
	
	message_vision( MAG"$N手中"+weapon->query("name")+MAG"以音乐上弄手法吹奏，语调清幽，宛如早上的梅花含苞欲放，晶莹洁白\n"+
		"$n仿佛幽香在自己周身阵阵而起，感觉徜徉在漫无边际的花海一般,不自觉间有些发怔。\n"NOR,me,target);
	
	me->start_perform(4,"「梅花三弄」");
	me->set_temp("yxj/sannong",1);
	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
	   || random(me->query_int())>target->query_int()/2)
	{
		
		msg = HBYEL+HIR "\n\n$n只觉大脑昏昏欲睡，手脚似乎不受自己控制。\n" NOR;
		target->add_busy(2);
	}
	else {
		msg = HIY "可是$n看破了$N的企图，急忙咬住自己舌尖，保持清醒。\n" NOR;
		me->start_busy(1);
	}
	message_vision(msg, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);

	if (me->is_fighting()&&objectp(target))
		next1(me, target, i);
	else call_out("remove_effect",4,me);
	return 1;
}

void next1(object me, object target, int i)
{
	string msg;
	int damage;
	object weapon;

	if (!me) return ;
	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("yxj/sannong");
		return ;
	}

	msg = MAG"\n$N箫声幽幽，音调陡然拔高，宛如梅花大片绽放，满树飘白，落花如雨。\n"+
		"$n觉得自己眼前梅花繁华盛开，灿烂芬芳，笑脸迎人，忍不住伸手要去摘取这绚烂的梅花。\n"NOR;

	if(random(me->query("combat_exp"))>target->query("combat_exp")/2
		||random(me->query_skill("yuxiao-jian",1))> target->query_skill("dodge",1)/2 )
	{
		msg = msg + HIR"$n忽觉一阵剧痛，方才失神之际为$N所乘，受到刺伤！\n"NOR;
		damage = me->query_skill("yuxiao-jian",1)+me->query_skill("force",1);
		damage += me->query_skill("sword",1);
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
		me->add("neili",-300);
		me->add("jingli",-100);
	} else {
		msg  =  msg + CYN"$n凭借灵巧的身法躲开了这一招。\n"NOR;
		message_vision(msg, me, target);
		me->start_busy(1+random(2));
		target->start_busy(1+random(2));
	}
	if (me->is_fighting()&&objectp(target))
		next2(me, target, i);
	else call_out("remove_effect",4,me);
	return;

}

void next2(object me, object target, int i)
{
	string msg;
	int damage,lvl;
	object weapon;

	if( !me ) return ;

	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->delete_temp("yxj/sannong");
		return ;
	}

	msg = HIW "\n$N脚踩奇门五转步伐，面色有些潮红，功力尽展，将"+weapon->query("name")+HIW"施展宛如落英缤纷，煞是好看。\n"NOR;
	msg += HIW "\n$N施展出玉箫剑法梅花三弄，$n但觉周身梅花凌霜傲寒，高洁不屈的节操与气质表现无遗！\n"NOR;
	
	if(random(me->query("combat_exp")) > target->query("combat_exp")/2
		||random(me->query_str()) >target->query_dex()/3)
	{
		msg = msg + HIC "$n这"+weapon->query("name")+HIC"的音调攻击如长枪大戟，汹涌澎湃，$n面色大变！\n"NOR;
		damage = me->query_skill("yuxiao-jian",1)+me->query_skill("force",1);
		damage += me->query_skill("blade",1);
		damage=damage*me->query_str()/20;
		damage += random(damage);
		
		//if (!target->is_busy()) target->start_busy(damage/500);
		lvl=me->query_skill("yuxiao-jian",1)+me->query_skill("qimen-bagua",1);
		target->apply_condition("no_exert",2);

		target->add_temp("apply/attack", -lvl/3);
		target->add_temp("apply/dodge", -lvl/5);
		target->add_temp("apply/parry", -lvl/5);
		target->add_temp("yxj/sannong",lvl);
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
				if (wizardp(me)) write("damage3="+damage);

		msg += damage_msg(damage, "砍伤");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "手臂");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-300);
		me->add("jingli",-150);
		if (objectp(target))
			call_out("back", 5+random(5), target);
	} else {
		msg = msg + HIW "$n运起内功，闭塞听觉，抵抗这闻名江湖的梅花三弄绝技。\n" NOR;
		message_vision(msg, me, target);
		me->start_busy(1 + random(2));
		target->start_busy(1+random(2));
	}
	me->delete_temp("yxj/sannong");
	me->start_perform(3,"梅花三弄");
	return;
}

void back(object target)
{
	int lvl;
	if (!target) return;
	lvl=target->query_temp("yxj/sannong");
	target->add_temp("apply/attack", lvl/3);
	target->add_temp("apply/dodge", lvl/5);
	target->add_temp("apply/parry", lvl/5);
}
void remove_effect(object me)
{
	if (!me) return;
	me->delete_temp("yxj/sannong");
	message_vision(HIM"$N将梅花三弄绝技，缓缓收功。\n"NOR,me);
	return;
}
string perform_name(){ return MAG"梅花三弄"NOR; }

int help(object me)
{
   write(WHT"\n玉箫剑法之「"MAG"梅花三弄"WHT"」："NOR"\n");
   write(@HELP
	此「梅花三弄」乃巧用内劲和身法配合，以玉箫剑法中
	精奇的招式配合箫声攻击对方，防不胜防。此招乃需要
	依靠丰富的战斗经验和相应的奇门造诣与悟性。若对方
	为你所打中，则会出现一定程度的虚弱和忙碌状态。

	指令：perform sword.sannong

要求：
	当前内力 1000 以上；
	当前精力 1000 以上；
	玉箫剑法 300 以上；
	基本剑法 300 以上；
	基本内功 300 以上；
	激发剑法为玉箫剑法；
	手中持箫；

HELP
   );
   return 1;
}
