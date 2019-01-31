#include <ansi.h>
inherit F_SSERVER;

int perform1(object me, object target, object weapon, int ap, int dp, int skill, int i);
int perform2(object me, object target, object weapon, int ap, int dp, int skill, int i);

int perform(object me, object target)
{
	string msg, dodge_skill;
	object weapon = me->query_temp("weapon");
	int ap, dp, damage, p, skill, i = 0;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("「沧澜剑式」字诀只能在战斗中对对手使用。\n");

	if( !living(target) )
		return notify_fail("「沧澜剑式」字诀只能在战斗中对对手使用。\n");

	if( !weapon || weapon->query("skill_type") != "sword" )
		return notify_fail("你手中无剑，如何使得「沧澜剑式」字诀？\n");

	if( me->query_skill_mapped("sword") != "tonggui-jian" )
		return notify_fail("你所备不是同归剑法，无法使用「沧澜剑式」字诀。\n");

	if( me->query_skill_mapped("parry") != "tonggui-jian" )
		return notify_fail("你必须以同归剑法为招架才能使用「沧澜剑式」字诀。\n");  
//增加如果解开太极神功后，则可以沧澜剑式续出
	if( me->query_temp("tgj/canglan") && !me->query("quest/wd/yyzq/taiji/pass"))
		return notify_fail("你正在使用「沧澜剑式」字诀。\n");

	//if( (int)me->query_temp("tgj/canglan") )
		//return notify_fail("你现在正在使用「沧澜剑式」字诀。\n");

	if( (int)me->query_skill("tonggui-jian", 1) <120 )
		return notify_fail("你的同归剑法修为尚不纯熟,无法使用「沧澜剑式」字诀！\n");             

	if( (int)me->query_skill("force",1) < 120 )
		return notify_fail("你的基本内功修为尚浅，不能使用「沧澜剑式」字诀！\n");

	if( (int)me->query_skill("sword",1) < 120 )
		return notify_fail("你基本剑法修为尚不纯熟,不能使用「沧澜剑式」字诀！\n");  

	if( (int)me->query("max_neili") < 1500 )
		return notify_fail("你的内力修为太弱，不能使用「沧澜剑式」字诀！\n");

	if( (int)me->query("neili") < 300 )
		return notify_fail("你的真气太少了，不能使用「沧澜剑式」字诀！\n");  

	message_vision(CYN"\n$N使出全真教的同归剑法中的"+RED+"「沧澜剑式」"+CYN+"，这套剑法取同归于尽之意，招招攻敌要害，竟不自加防守，倒与泼皮无赖街头群殴同出一理！\n"NOR,me,target);

	me->set_temp("tgj/canglan",1);

	ap = me->query("combat_exp", 1) / 1000 * me->query_int(1);
	dp = target->query("combat_exp", 1) / 1000 * target->query_int(1);

	skill = me->query_skill("tonggui-jian", 1);


	msg = YEL"\n$N全然不顾防御，猛然跨进一步，贴近$n身前，双手握剑"+weapon->name()+YEL"向下直劈而去。\n"NOR;
	me->add_temp("apply/parry",-(int)skill/2);
	me->add_temp("apply/sword",(int)skill/2);

	if ( random( ap + dp) > dp
		||random(me->query_dex(1))>target->query_dex(1)/2) 
	{
		damage = me->query_skill("sword",1)+me->query_skill("force",1)+me->query_skill("tonggui-jian",1);
		damage = to_int( damage * skill/100);
		damage = damage + random(damage);
		if (damage > 4000 ) damage = 4000 + random(damage-4000)/50;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/3, me);
		me->add("neili", -200);
		me->add("jingli", -150);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
		i = 1;
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		me->add("neili", -100);
		me->add("jingli", -50);
	}
	message_vision( msg, me, target);
	me->add_temp("apply/parry",(int)skill/2);
	me->add_temp("apply/sword",-(int)skill/2);

	me->start_perform(2, "「沧澜剑式」字诀");
	me->start_busy(random(2));
	me->delete_temp("tgj/canglan");
	if ( skill > 120 ) {
		me->set_temp("tgj/canglan", 1);
		perform1(me, target, weapon, ap, dp, skill, i);
	}
	return 1;
}

int perform1(object me, object target, object weapon, int ap, int dp, int skill,int i)
{
	string msg, dodge_skill;
	int damage, p;

	if ( !me) return 1;
	if( !weapon || !objectp(target)) {
		me->delete_temp("tgj/canglan");
		return 1;
	}

	msg =RED"\n$N向左跨出，贴身跟上，"+weapon->name()+RED"不住的抖动，罩向$n上盘七大要穴，向左斜下方全力连出三招，招招刺向$n的要害。\n"NOR;     
	
	me->add_temp("apply/parry",-(int)skill/2);
	me->add_temp("apply/sword",(int)skill/2);

	if ( random( ap + dp) > dp ) {
		damage = me->query_skill("sword",1) +me->query_skill("tonggui-jian",1)+me->query_skill("force",1);
		damage = to_int( damage * skill/50.0);
		damage = damage + random(damage);
		if (damage > 5000 ) damage = 5000 + random(damage-5000)/50;
		if ( i ) damage -= random(damage/2);
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi",damage/2, me);
		me->add("neili", -250);
		me->add("jingli", -150);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		i = 0;
		me->add("neili", -100);
		me->add("jingli", -50);
	}
	me->add_temp("apply/parry",(int)skill/2);
	me->add_temp("apply/sword",-(int)skill/2);

	message_vision( msg, me, target);
	me->start_perform(3, "「沧澜剑式」字诀");
	me->delete_temp("tgj/canglan");
	if ( skill > 160 ) {
		me->set_temp("tgj/canglan", 1);
		perform2(me, target, weapon, ap, dp, skill, i);
	}
	return 1;
}

int perform2(object me, object target,object weapon, int ap, int dp, int skill, int i)
{
	string msg, dodge_skill;
	int damage, p;

	if ( !me) return 1;
	if( !weapon || !objectp(target)) {
		me->delete_temp("tgj/canglan");
		return 1;
	}

	msg = MAG"\n$N手中"+weapon->name()+MAG"连续抖出数多剑光，招式暴烈，全然不要命的打法，大开大合，挥刃直入。\n"NOR;
	me->add_temp("apply/parry",-(int)skill/2);
	me->add_temp("apply/sword",(int)skill/2);

	if ( random( ap + dp) > dp
		||random(me->query_str())>target->query_dex()/2) {
		damage = me->query_skill("sword",1) * 4;
		damage = to_int( damage * skill/100.0);
		damage = damage + random(damage);
		if (damage > 6000 ) damage = 6000 + random(damage-6000)/100;
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage/2+random(damage/2), me);
		me->add("neili", -300);
		me->add("jingli", -150);
		if (random(2)) {
			p = (target->query("eff_qi")+target->query_temp("apply/qi"))*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "刺伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
		msg = replace_string( msg, "$w", weapon->name());
		msg = replace_string( msg, "$l", "手臂");
		me->start_perform(3+random(2), "「沧澜剑式」字诀");
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
	}

	msg += WHT"\n$N「沧澜剑式」运行完毕，剑交左手，收剑而立，笼罩在全身上下的大小光圈随即不见踪影。\n\n"NOR;
	me->add_temp("apply/parry",(int)skill/2);
	me->add_temp("apply/sword",-(int)skill/2);

	me->delete_temp("tgj/canglan");
	message_vision( msg, me, target);
	me->add("neili", -100);
	me->add("jingli", -50);
	me->start_perform(3, "「沧澜剑式」字诀");

	return 1;
}

string perform_name(){ return WHT"沧澜剑式"NOR; }

int help(object me)
{
        write(CYN"\n同归剑法之「沧澜剑式」："NOR"\n\n");
        write(@HELP
	同归剑法为全真七子所创。全套剑法只攻不守，招招猛攻敌人要害
	力求与敌同归于尽，故得此名。全真七子忌惮欧阳锋武功高强，怕
	欧阳锋重回中原时全真教有覆灭之虞，为避免七人落单时不敌其武
	功而创出，意在牺牲一人而保全同门。丘处机与江南七怪及焦木大
	师交手时首次使出。
	沧澜剑式是同归剑法牺牲自身防御，全力进攻的典型打法，招式娴
	熟后，连续三招，招招不要命，极为狠辣。但缺点是自身防御会大
	幅下降，很容易为对方反击，切记。

	指令：perform sword.canglan

要求：
	当前内力要求 800 以上;
	最大内力要求 1500 以上；
	同归剑法等级 120 以上；
	基本内功等级 120 以上；
	基本剑法等级 120 以上；
	激发剑法为同归剑法；
	激发招架为同归剑法；
	激发内功不限。

HELP
        );
        return 1;
}
