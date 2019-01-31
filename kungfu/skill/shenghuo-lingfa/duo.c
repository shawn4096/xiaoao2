// duo.c 圣火令法「夺」字诀
// By Spiderii@ty 更新

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return BCYN"夺字诀"NOR; }
int perform(object me, object target)
{
	string msg;
	object tweapon, weapon,weapon2,*inv;
	int ap, dp,count,i;

	me->clean_up_enemy();
	target = me->select_opponent();

    inv = all_inventory(me);
    for(count=0, i=0; i<sizeof(inv); i++) {
           if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
           if( inv[i]->query("skill_type") == "dagger" ) 
		   {
			   weapon2 = inv[i];
			   break;
		   }
     }

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「夺字诀」只能对战斗中的对手使用。\n");

	weapon = me->query_temp("weapon");
	tweapon = target->query_temp("weapon");

	if( !weapon||!weapon2
	 || weapon->query("skill_type") != "dagger"
	 || me->query_skill_mapped("dagger") != "shenghuo-lingfa" )
		return notify_fail("你现在无法使用夺字诀。\n");

	if( !tweapon )
		return notify_fail("对方没有使用任何兵器，你无法使用「夺字诀」。\n");

	if((int)me->query_skill("shenghuo-lingfa", 1) < 350 )
		return notify_fail("你的圣火令法还不够娴熟，不会使用「夺」字诀。\n");

	//if( me->query_temp("qkdny/yin") )
	//	return notify_fail("你正在施展乾坤大挪移「引」字诀呢！\n");

	//if( me->query_temp("qkdny/hua") )
		//return notify_fail("你正在施展乾坤大挪移「化」字诀呢！\n");

	if((int)me->query("neili") < 3000 )
		return notify_fail("你的内力不够！\n");

	if( (int)me->query_str() < 65 )
		return notify_fail("「夺」字诀需要很高的臂力，才能出奇不异的把对方的兵器夺下来，你的条件好象还不够。\n");

	if( me->query_skill_mapped("parry") != "shenghuo-lingfa"
	&& me->query_skill_mapped("parry") != "qiankun-danuoyi" )
                return notify_fail("你需要激发招架为圣火令法，方能使用「夺」字诀。\n");

	if ( weapon && weapon2)
		msg = BCYN"$N举起"+weapon->query("name")+BCYN"，双手一振，令牌已搭在$n的"+tweapon->query("name")+BCYN"上，企图以圣火令法「夺」字诀把$n的兵器夺下。\n"NOR;
	if (me->query_skill("shenghuo-shengong",1)>349&&me->query_temp("mj/shenghuo")) 
		me->start_perform(1, "夺字诀");
	else me->start_perform(3, "「夺」字诀"); //提高buff能力	me->start_perform(3, "夺字诀");

	ap = me->query("combat_exp")/1000 * me->query_str(1);
	dp = target->query("combat_exp")/1000 * target->query_dex(1);

	if( random(ap + dp) > dp ) {
		int move_flag = 0;
		if(tweapon->is_owner(target)) move_flag=1;
		msg += HIY"$n只感"+tweapon->name()+HIY"似欲脱手飞出，一个把握不住，手中兵器被夺飞了出去。\n"NOR;
		target->add_busy(1+random(2));
		me->add("neili",-300);

		if (move_flag==0 && random(2)!=1 && tweapon->query("imbued") < 3 && tweapon->move(me)){
			msg += HIY"$n的兵器被$N的令牌一压一带，刹那间"+tweapon->name()+HIY"已被$N夺下。\n"NOR;
			target->add_busy(1+random(2));
                    tweapon->move(environment(me));
}

		else {
			msg += HIY"$n被$N手中"+weapon->name()+HIY"一番疾攻。不由的闪身急躲,只能任"+tweapon->name()+HIY"落在一边。\n"NOR;
			tweapon->move(environment(me));
		}
	}
	else {
		me->add("neili",-200);
              msg += CYN"$n见势不妙，右手"+weapon->name()+CYN"奋力挣脱，慌乱中总算脱离了$N的攻击！\n"NOR;

	}
	if (me->query_skill("shenghuo-shengong",1)<349 || !me->query_temp("mj/shenghuo"))me->start_busy(random(2));
	 //提高buff能力	me->start_perform(3, "夺字诀");
	
	message_vision(msg, me, target);
	return 1;
}

int help(object me)
{
	write(CYN"\n圣火令法之「夺字诀」："NOR"\n\n");
	write(@HELP
	夺取对方手中兵器，用两个圣火令夹住对方兵器，向自己怀里夺去。
	需手持两块令类型的武器，并需要高臂力配合。
	
	指令：perform dagger.duo

要求：
	当前内力需求 3000 以上；
	圣火令法等级 350 以上；
	后天臂力 65；
	激发招架为圣火令法或乾坤大挪移；
	且手持兵器。
	350小飞。
		

HELP
        );
        return 1;
}

