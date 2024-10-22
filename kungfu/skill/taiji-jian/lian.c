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
		return notify_fail("「连」字诀只能在战斗中对对手使用。\n");

	if( !living(target) )
		return notify_fail("「连」字诀只能在战斗中对对手使用。\n");

	if( !weapon || weapon->query("skill_type") != "sword" )
		return notify_fail("你手中无剑，如何使得「连」字诀？\n");

	if( me->query_skill_mapped("sword") != "taiji-jian" )
		return notify_fail("你所备不是太极剑法，无法使用「连」字诀。\n");

	if( me->query_skill_mapped("parry") != "taiji-jian" )
		return notify_fail("你必须以太极剑法为招架才能使用「连」字诀。\n");  
//增加如果解开太极神功后，则可以连续出
	if( me->query_temp("tjj/chan") && !me->query("quest/wd/yyzq/taiji/pass"))
		return notify_fail("你正在使用「缠」字诀。\n");

	if( (int)me->query_temp("tjj/lian") )
		return notify_fail("你现在正在使用「连」字诀。\n");

	if( (int)me->query_skill("taiji-jian", 1) <300 )
		return notify_fail("你的太极剑法修为尚不纯熟,无法使用「连」字诀！\n");             

	if( (int)me->query_skill("yinyun-ziqi",1) < 300 )
		return notify_fail("你的氤氲紫气修为尚浅，不能使用「连」字诀！\n");

	if( (int)me->query_skill("sword",1) < 300 )
		return notify_fail("你基本剑法修为尚不纯熟,不能使用「连」字诀！\n");  

	if( (int)me->query("max_neili") < 1500 )
		return notify_fail("你的内力修为太弱，不能使用「连」字诀！\n");

	if( (int)me->query("neili") < 800 )
		return notify_fail("你的真气太少了，不能使用「连」字诀！\n");  

	message_vision(CYN"\n$N微微一笑，使出太极剑中"+RED+"「连」"+CYN+"字诀，当下身子缓缓右转,左手持剑向上提起，剑身横于胸前，\n"
			"左右掌心相对，如抱圆球，手中"+weapon->name()+CYN"未出，已然蓄势无穷。\n"NOR,me,target);

	me->set_temp("tjj/lian",1);

	ap = me->query("combat_exp", 1) / 1000 * me->query_int(1);
	dp = target->query("combat_exp", 1) / 1000 * target->query_int(1);

	skill = me->query_skill("taiji-jian", 1);

	msg = CYN"\n$N左手"+weapon->name()+CYN"缓缓向前划出，成一弧形，一股森森寒气，直逼向$n，突然之间，$N剑交右手，寒光一闪，向$n划去。\n"NOR;

	if ( random( ap + dp) > dp
		||random(me->query_dex(1))>target->query_dex(1)/2) 
	{
		damage = me->query_skill("sword") * 2;
		damage = to_int( damage * skill/100.0);
		damage = damage/2 + random(damage);
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
	me->start_perform(2, "「连」字诀");
	me->start_busy(random(2));
	me->delete_temp("tjj/lian");
	if ( skill > 150 ) {
		me->set_temp("tjj/lian", 1);
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
		me->delete_temp("tjj/lian");
		return 1;
	}

	msg =YEL"\n$N又将剑交左手，在身前划了两个圆圈，剑劲连绵护住全身，竟无半分空隙，右手捏着剑诀，\n"+
		"左手"+weapon->name()+YEL"不住的抖动，罩向$n上盘七大要穴，剑尖急颤，看不出攻向何处。\n"NOR;     

	if ( random( ap + dp) > dp ) {
		damage = me->query_skill("sword",1) +me->query_skill("taiji-jian",1)+me->query_skill("yinyun-ziqi",1);
		damage = to_int( damage * skill/150.0);
		damage = damage + random(damage);
		if (damage > 3500 ) damage = 3500 + random(damage-3500)/50;
		if ( i ) damage -= random(damage/2);
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi",damage/4, me);
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
	message_vision( msg, me, target);
	me->start_perform(3, "「连」字诀");
	me->delete_temp("tjj/lian");
	if ( skill > 200 ) {
		me->set_temp("tjj/lian", 1);
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
		me->delete_temp("tjj/lian");
		return 1;
	}

	msg = HIC"\n$N剑上所幻的"+RED+"光圈"+HIC+"越来越多，过不多时，全身已隐在无数"+RED+"光圈"+HIC+"之中，"+RED+"光圈"+HIC+"光圈一个未消，另一个再生，\n"
		"手中"+weapon->name()+HIC"虽使得极快，却丝毫听不到金刃劈风之声，足见剑劲之柔韧已达于化境。\n"
		HIC"$n凝视剑光所幻无数"+RED+"光圈"+HIC+"绞向自己，见无可退避，只得冒险一击，当下手臂一伸，向"+RED+"光圈"+HIC+"的中心挥刃直入。\n"NOR;

	if ( random( ap + dp) > dp
		||random(me->query_str())>target->query_dex()/2) {
		damage = me->query_skill("sword",1) * 4;
		damage = to_int( damage * skill/100.0);
		damage = damage + random(damage);
		if (damage > 4500 ) damage = 4500 + random(damage-4500)/100;
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
		me->start_perform(3+random(2), "「连」字诀");
	}
	else {
		dodge_skill = target->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		me->add("neili", -100);
		me->add("jingli", -50);
		me->start_perform(3, "「连」字诀");
	}

	msg += HIY"\n$N「连」字诀运行完毕，剑交左手，收剑而立，笼罩在全身上下的大小光圈随即不见踪影。\n\n"NOR;
	me->delete_temp("tjj/lian");
	message_vision( msg, me, target);
	return 1;
}

string perform_name(){ return CYN"连环诀"NOR; }

int help(object me)
{
        write(CYN"\n太极剑法之「连环诀」："NOR"\n\n");
        write(@HELP
	太极剑乃是张三丰晚年巅峰之作，开创了剑术
	以柔克刚的先河。剑势运转如滔滔大江大河，
	滔滔不绝。这连环诀就是将此剑意融合到剑法
	之中，连环不绝。
	
	perform sword.lian

要求：
	当前内力要求 800 以上;
	最大内力要求 1500 以上；
	太极剑法等级 300 以上；
	氤氲紫气等级 300 以上；
	基本剑法等级 300 以上；
	激发剑法为太极剑法；
	激发招架为太极剑法；
	激发内功为氤氲紫气。

HELP
        );
        return 1;
}
