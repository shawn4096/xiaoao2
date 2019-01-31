// chan.c 打狗棒法--封字诀
// Modify by looklove@SJ 3/16/2001
// Update by lsxk@hsbbs 2007/7/2
// 定位成防守武技，防御力大升的武技

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HBMAG+HIW"封字诀"NOR; }
int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int mexp, texp, mlvl, tlvl, b;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「封字诀」只能对战斗中的对手使用。\n");

	weapon = me->query_temp("weapon");
	tweapon = target->query_temp("weapon");

	if( !objectp(weapon)
	 || weapon->query("skill_type") != "stick"
	 || me->query_skill_mapped("parry") != "dagou-bang"
	 || me->query_skill_mapped("stick") != "dagou-bang" )
		return notify_fail("你现在无法使用打狗棒「封字诀」。\n");

	mexp = (int)me->query("combat_exp")/100000;
	texp = (int)target->query("combat_exp")/100000;
	mlvl = (int)me->query_skill("dagou-bang",1);
	tlvl = (int)target->query_skill("dodge",1);

	b = me->query_skill("bangjue",1);

	if( mlvl < 400 )
		return notify_fail("你的打狗棒法还不够娴熟，不会使用「封字诀」。\n");
	if( b < 150 )
		return notify_fail("你的打狗棒诀不够娴熟，无法使出「封字诀」。\n");

	if( (int)me->query_skill("huntian-qigong", 1) < 400 )
		return notify_fail("你的混天气功根基不足，无法使出「封字诀」。\n");

	if( (int)me->query("neili") < 500 )
		return notify_fail("你的内力不够，无法使出「封字诀」。\n");

	if( (int)me->query("jingli") < 500 )
		return notify_fail("你的精力不足以让你使出「封字诀」。\n");

	if( (int)me->query("max_neili") < 2000 )
		return notify_fail("你的内力不够支持你使用「封字诀」。\n");

	if( me->query_temp("dgb/feng") )
		return notify_fail("你正在施展「封字诀」。\n");	
	if( me->query_condition("no_perform") )
		return notify_fail("你的对手已经为你「封字诀」所封住了招式，放胆进攻吧。\n");	


	message_vision( HBYEL"$N使出打狗棒法的「封字诀」，手中"+weapon->query("name")+HBYEL"舞成一团棒影，紧紧守住门户。\n"NOR,me);
	
	if( tweapon )
		message_vision(HBGRN"\n只见$n的"+tweapon->query("name")+HBGRN"挥到东，"+weapon->query("name")+HBGRN"就跟向东，"+tweapon->query("name")+HBGRN"打到西，"+weapon->query("name")+HBGRN"随到西。\n"NOR,me,target);
	else
		message_vision(HBGRN"\n只见"+weapon->query("name")+HBGRN"如影随形，招招不离$n周身大穴，$n感受到巨大的威胁，打狗棒当真精妙无比。\n"NOR,me,target);
	
	//message("wizard", HIG"封字诀：busy回合数"+busy+"，使用者EXP"+mexp+"，对手EXP"+texp+", "+x+","+y+"。\n"NOR, environment(me), me);
	
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

//增加自身攻防
	
	if (random(mlvl)>tlvl/2
		||random(me->query_int(1))>target->query_int(1)/2)
	{
	
		if (me->query("env/打狗棒封字诀")=="防守")
		{
			if (!me->query_temp("dgb/feng"))
			{
				message_vision(HIG "\n\n$N施展的打狗棒法精妙为主，一根轻轻巧巧的"+weapon->query("name")+HIG"自可使得圆转自如。$n一时竟然难以攻入。\n" NOR,me,target);

				me->add_temp("apply/parry",mlvl/3);
				me->add_temp("apply/defense",mlvl/3);
				me->add_temp("apply/dodge",mlvl/3);
				me->add_temp("apply/armor",mlvl/3);
				me->set_temp("dgb/feng",mlvl);
				call_out("check_fight",1,me,mlvl/20);
			}

		}
		if (me->query("env/打狗棒封字诀")=="反击"
			&&me->query("quest/gb/dgb/wugou/pass"))
		{
		
			if (!me->query_temp("dgb/feng"))
			{
				message_vision(HIM "\n\n$n想运劲震断$N手中的"+weapon->query("name")+HIM"哪知$N这一招使的是“打狗棒法”中的“封”字诀，棒法全是横使。\n"+
				"并不攻击敌身，一条"+weapon->query("name")+HIM"化成一片碧墙，挡在面门，只要敌人不踏上一步，那就无碍，若施攻击，立受反打。\n"NOR,me,target);

				if (me->is_fighting()
					&&objectp(target))
				{
					message_vision(HIW "$N使个“封”字诀，棒影飘飘，皆都指向$n周身要穴，登时将$n身前数尺之地尽数封住了。\n" NOR,me,target);
					if (userp(target)) target->add_condition("no_perform",b/100);
					else target->add_condition("no_perform",b/50);
					//target->set_temp("dgb/feng",mlvl);
				}
			}

		}

	}		
	else {
		message_vision(HIW "$n镇定自若，信手在"+weapon->query("name")+HIW"上一推，封字诀瞬间瓦解。\n" NOR,me,target);
		me->start_busy(1+random(2));
	}
	if (me->query_skill("dagou-bang",1)>550 && !me->query("quest/gb/dgb/bangjue/pass"))
		me->start_perform(1, "封字诀");

	me->add("neili", -200);
	me->add("jingli", -60);
	return 1;
}

void check_fight(object me,int count)
{
	object weapon;
	int mlvl;
	if (!me) return;	
	if (!me->query_temp("dgb/feng")) return;
	mlvl=me->query_temp("dgb/feng");
	weapon=me->query_temp("weapon");
	if( !me->is_fighting()
	 || !weapon
	 || weapon->query("skill_type")!="stick"
	 || count<0
	 || me->query_skill_mapped("parry") != "dagou-bang"
	 || me->query_skill_mapped("stick") != "dagou-bang")
	{      
	        
			me->add_temp("apply/parry",-mlvl/3);
			me->add_temp("apply/defense",-mlvl/3);
			me->add_temp("apply/dodge",-mlvl/3);
			me->add_temp("apply/armor",-mlvl/3);
			me->delete_temp("dgb/feng");
			
			message_vision(HBYEL "$N长吁一口浊气，停止了打狗棒法「封字诀」，漫天弥漫的棒影逐渐消失。\n" NOR,me);
			if (me->query_skill("dagou-bang",1)<450) me->start_perform(1, "封字诀");

			return;
	}

	call_out("check_fight", 1, me,count--);
}
int help(object me)
{
	write(HBMAG"\n打狗棒「封字诀」："NOR"\n");
	write(@HELP
	昔年洪七公以打狗棒之轻灵奇巧，跻身当世五大高手
	为丐帮不传之秘，这打狗棒「封字诀」，正是洪七公
	当年惯使的一招成名绝技。一旦施展出，立即将周身
	空门封住，使得对方招式难以攻入，对方若强行攻入
	随时面临打狗棒的反击，是以静制动的不二法门。
	本门武功和双方经验、武技等级、双方悟性具有关联
	一旦对方被封，将会降低相应的攻防。550级后大飞
	
	注意：封字诀有两种功效，防守和反击，可以通过有
		效的设置完成封字诀的使用。防守是大幅提升自
		己防御能力，反击是对对方进行封招功效，反击
		的效果是解开打狗棒第三段，即招式和口诀融合
		后方可使用。
		
		set 打狗棒封字诀 防守
		set 打狗棒封字诀 反击 
			
	指令：perform stick.feng
	
要求：
	最大内力需求 2000 以上；
	当前内力需求 500 以上；
	当前精力需求 500 以上；
	打狗棒法等级 400 以上；
	混天气功等级 400 以上；
	打狗棒诀等级 150 以上：
	激发招架为打狗棒。
HELP
	);
	return 1;
}
