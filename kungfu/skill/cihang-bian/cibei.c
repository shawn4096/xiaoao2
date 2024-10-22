// 调整 by lane 2004.12.13 
#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int extra,skill,at,df,i,lmt,damage,p;
	object weapon;
	extra = me->query_skill("cihang-bian", 1);

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「慈悲字诀」只能对战斗中的对手使用。\n");

	if( extra < 160 )
		return notify_fail("你的慈行鞭法修为太差,还不能使用「慈悲字诀」！\n");

	skill = me->query_skill("buddhism", 1); 

	if( skill < 180 )
		return notify_fail("你的禅宗心法等级不够，怎能支持「慈悲字诀」？ \n");

	if( userp(me) && me->query("class") != "bonze" )
		return notify_fail("「慈悲字诀」只有出家人才能使用。\n");

	if( me->query_temp("chb") )
		return notify_fail("你正在使用「慈悲字诀」。\n");

	if( me->query("shen") < 100000 )
		return notify_fail("「慈悲字诀」需以无边正气为辅，大师还是多行善事吧! \n");

	if( me->query_skill("kurong-changong", 1) < 160 )
		return notify_fail("你的枯荣禅功修为太差，还不能使用「慈悲字诀」！\n");

	if( me->query("max_neili") < 2000 )
		return notify_fail("你的内力修为不够辅助慈悲字诀。\n");

	if( me->query("neili") < 2000 )
		return notify_fail("你现在内力不足，不够辅助慈悲字诀。\n");

	if( me->query("jingli") < 1200 )
		return notify_fail("你的精力修为不够辅助慈悲字诀。\n");

	weapon = me->query_temp("weapon"); 

	if( me->query_skill_mapped("whip") != "cihang-bian" && userp(me) )
		return notify_fail("你现在无法使用「慈悲字诀」！\n");

	if( me->query_skill_mapped("parry") != "cihang-bian" && userp(me) )
		return notify_fail("你现在无法使用「慈悲字诀」！\n");

	if( !weapon || weapon->query("skill_type") != "whip" )
		return notify_fail("你手中没有兵器如何使用「慈悲字诀」。\n");

        msg=HIC"$N口中高宣佛号，使出慈航鞭中「慈悲」绝技，手中长索滚动飞舞，\n";
        msg+="宛若念珠乱颤，自上而下劈向$n,接着$N手腕一抖，便如如来降魔\n";
        msg+="似，急升而上，又往$n扑到。\n"NOR;


	message_vision(msg, me, target);

	at = me->query("combat_exp",1)/1000 * me->query_skill("cihang-bian", 1);
	df = target->query("combat_exp", 1)/1000 * target->query_skill("dodge", 1);

	me->set_temp("chb", 3);

//	增加内力损失，和 buddhism 挂钩 
	me->add("neili", -(800-skill) );
	me->add("jingli", -150);
	lmt = extra/4;
	//下面两处由250调成350，弱化鞭子威力
	if( extra > 350 )
		lmt = to_int( extra / 4.0 * extra / 350.0); 

	me->add_temp("apply/attack", lmt);
	me->add_temp("apply/whip", lmt);
	me->add_temp("apply/damage", lmt);
	me->add_temp("apply/dodge", lmt);


	for(i=1;i <= 3; i++)
		COMBAT_D->do_attack(me,target, me->query_temp("weapon"), random(2)?1:3);

	me->add_temp("apply/attack",-lmt);
	me->add_temp("apply/whip",-lmt);
	me->add_temp("apply/damage", -lmt);
	me->add_temp("apply/dodge", -lmt);

	me->delete_temp("chb");
	me->start_perform(4,"「慈悲字诀」");

	if( me->query_skill("cihang-bian", 1) >= 200 ) {
		if( random(at + df) > df ) {
			damage = me->query("shen")/1000;

//			增加判断，佛法对正神对手伤害减少
			if( target->query("shen") > 0 )
				damage = damage + skill - target->query("shen")/5000;
			if( damage < 100 ) damage = 50 + random(50);

			if( damage > 2000 ) damage = 2000;
			msg = CYN"\n$n不禁被$N的无边佛法打动，猛的后退，脸上没有一丝血色...\n"NOR;
			target->add("neili", -damage/2 );
			target->receive_damage("qi", damage, me);
			target->receive_wound("qi", damage/3, me); 
			p = (int)target->query("qi")*100/(int)target->query("max_qi");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n"; 
            if(userp(me) && me->query("env/damage"))
				tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR);
			
if(userp(target)&& target->query("env/damage"))
				tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR);
				weapon = me->query_temp("weapon");        
			message_vision(msg, me, target);
			me->add("neili", -300);
			me->add("jingli", -100);

//			考虑到做 job 1 pfm 不够，改成 1k 差不多
			me->add("shen", -1000);
			me->start_perform(4,"「慈悲字诀」");
		}
		else {
			me->add("neili",-200);
			me->add("jingli",-50);
		}
	}
	me->start_busy(random(2));
	return 1;
}

string perform_name(){ return HIY"慈悲字诀"NOR; } 

int help(object me)
{
	write(HIY"\n慈航鞭之「慈悲字诀」："NOR"\n\n");
	write(@HELP
   要求：  当前内力 1500 以上；
           当前精力 1200 以上；
           慈航鞭等级 160 以上；
           枯荣禅功等级 160 以上；
           禅宗心法等级 180 以上：
           正神 500000 以上；
           激发鞭法为慈航鞭；
           激发招架为慈航鞭；
           必须出家且手持兵器。

HELP
        );
	return 1;
}
