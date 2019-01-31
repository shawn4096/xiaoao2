// zhuan.c 打狗棒法--转字诀
// Creat by looklove@SJ 2001.4.10
// Modify by looklove 2001.5.2
// Modify by looklove 2001.5.4 青年节咯……
// Looklove modified at 2001.5.15

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int check_fight(object me,object target,int count);

string perform_name(){ return HBYEL+HIG"转字诀"NOR; }

string *zhuan_msg = ({
HIM"$n无法可施，只得向前急纵，却是避开一棒，后一棒又连环打来。\n"NOR,
HIY"眼看$n无法可施，只得向前急纵，却是避开前棒，后棒又至。\n"NOR,
HIC"大惊中$n脚下加劲，欲待得机转身，但$n纵跃愈快，$W"HIC"端来得愈急。\n"NOR,
HIG"$n绕着$N飞奔跳跃，大转圈子。$N手中$W"HIG"却一直在$n后心晃动。\n"NOR,
HIB"$N神色自若地看着$n飞奔跳跃，大转圈子。$N站在中心，举棒不离$n后心。\n"NOR,
HIR"$n绕着$N上蹿下跳，$N神色自若，$W"HIR"始终不离$n后心。\n"NOR,
HIW"$N将$W"HIW"自左手交到右手，又自右手交到左手，始终不离$n后心大穴。\n"NOR,
RED"$N手中$W"RED"划个圆圈，直点$n后心大穴，$n只得继续向前蹿跃。\n"NOR,
YEL"$n心中暗暗叫苦，却无计可施，脚下一步也不敢停顿。\n"NOR,
WHT"只见$n跑的圈子越转越大，$N手中的$W"WHT"却一直在$n后心打转。\n"NOR,
BLU"$n圈子越转越大，汗流夹背，$N手中的$W"BLU"依旧不断往$n后心招呼。\n"NOR,
MAG"$n一脸骇然，满头大汗，足下可丝毫不敢停步，一直绕着圈子躲避。\n"NOR,
CYN"一时间$n脸色大变，满头大汗，$W"CYN"不断点来，使得$n应接不暇。\n"NOR,
});

int check_fight(object me);
int halt_fight(object me);

int perform(object me, object target)
{
	string msg;
	object tweapon, weapon;
	int mexp, texp, mlvl, tlvl, b;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target))
		return notify_fail("「转字诀」只能对战斗中的对手使用。\n");

	weapon = me->query_temp("weapon");
	if( !weapon
	 || weapon->query("skill_type") != "stick"
	 || me->query_skill_mapped("stick") != "dagou-bang" 
	 || me->query_skill_mapped("parry") != "dagou-bang" )
		return notify_fail("你现在无法使用「转字诀」。\n");

	if( me->query_temp("dgb/zhuan") )
		return notify_fail("你正在使用「转字诀」。\n");

	if( me->query_temp("dgb/chan") )
		return notify_fail("你正在使用「缠字诀」。\n");

	if( target->is_busy() || target->query_temp("dgb/chan") )
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");


	mlvl = (int)me->query_skill("dagou-bang",1);
	tlvl = (int)target->query_skill("dodge", 1);

	b = me->query_skill("bangjue",1);

	tweapon = target->query_temp("weapon");

	if( mlvl < 500 )
		return notify_fail("你的打狗棒法还不够娴熟，不会使用「转字诀」。\n");
	if( b < 200 )
		return notify_fail("你的打狗棒诀不够娴熟，无法使出「转字诀」。\n");
	if( me->query_skill("huntian-qigong",1) < 500 )
		return notify_fail("你的混天气功根基不足，无法使出「转字诀」。\n");
	if( me->query("neili") < 1000 )
		return notify_fail("你的内力不够了。\n");
	if( me->query("jingli") <  1000 )
		return notify_fail("你的精力不足以支持你使出「转字诀」。\n");
	if( me->query("max_neili") < 8000 )
		return notify_fail("你的内力不够支持你使用「转字诀」。\n");

	me->set_temp("dgb/zhuan",1);	


	msg = HBYEL+HIR"$N使出打狗棒法"+HIC"「转字诀」"HBYEL+HIR"，只见"+weapon->name()+HBYEL+HIR"化成了一团碧影，\n"NOR;
	if (tweapon)
	{	
		msg += HBYEL+HIR"$N将手中"+weapon->query("name")+HIR"搭上$n手中的"+tweapon->query("name")+HIR",$n只觉手中兵器越来越沉。\n"NOR;
	}else 	msg += HBYEL+HIR"$N将手中"+weapon->query("name")+HIR"搭上$n的手腕,$n只觉自己身子忽然一沉。\n"NOR;

	msg += HBYEL+HIW"$N将"+HIC"「转字诀」"+HIW"圆转如意，猛点$n后心「强间」、「风府」、「大椎」、「灵台」、「悬枢」各大要穴。\n"NOR;

	
	if(random(me->query_skill("stick",1))>target->query_skill("dodge",1)/2
		||random(me->query_int(1))>target->query_int(1)/2)
	{
		msg += HIM "\n$N的棒影只在$n背后各穴上晃来晃去。点打连绵不断，一点不中，又点一穴。\n" NOR;
//破防,解开无狗后破防 
		if (me->query("quest/gb/dgb/wugou/pass")
			&&!target->query_temp("dgb/zhuan")
			&& me->query("env/打狗棒转字诀")=="破防")
		{
			
			msg += HIC "\n$n只觉身子一沉，身形立时变得迟缓起来！防御大降，破绽百出！\n" NOR;

			target->add_temp("apply/parry",-mlvl/3);
			target->add_temp("apply/dodge",-mlvl/3);
			target->add_temp("apply/defense",-mlvl/3);
			target->add_temp("apply/armor",-mlvl/3);
			target->set_temp("dgb/zhuan",mlvl);

			me->add("neili", -600);
			call_out("tremove_zhuan",(int)b/50,target);

		}
		//没开无狗就丢招和掉精
		msg += HBYEL+HIG "\n$n忽然有些头昏脑涨，陷入漫天的棍影之中，顿时失去了攻击的方向！\n" NOR;
		target->add_temp("lost_attack",b/20);
		if (objectp(target)&& me->is_fighting())
			call_out("check_fight",1,me,target,b/20);
		else call_out("remove_effect",1,me);
	}
	else {
		msg += HIW "\n$n吃了一惊，慌忙在"+weapon->name()+HIW"上一挡，阻住了$N的攻势。\n" NOR;
		me->start_busy(random(2));
		me->add("neili", -200);
	}
	if (me->query_skill("dagou-bang",1)<450)
		me->start_perform(2, "转字诀");
	message_vision(msg, me, target);
	return 1;
}

//target恢复防御
int tremove_zhuan(object target)
{
	int mlvl;
	if (!target) return 1;
	mlvl=target->query_temp("dgb/zhuan");
	target->add_temp("apply/parry",mlvl/3);
	target->add_temp("apply/dodge",mlvl/3);
	target->add_temp("apply/defense",mlvl/3);
	target->add_temp("apply/armor",mlvl/3);
	target->delete_temp("dgb/zhuan");
	message_vision("$N运功震开了被打狗棒所封住的大穴，顿时精神见长！\n",target);
	return 1;
}
//me恢复状态
int remove_effect(object me)
{
        if(!me) return 0;

        me->delete_temp("dgb/zhuan");

		message_vision(HBYEL"\n$N将手中棒子轻轻向斜上方一挑，棒影不见了，「转字诀」运行完毕，气回丹田，缓缓收功。\n"NOR, me);

        me->start_perform(2, "转字诀");
        me->start_busy(random(2));
        return 0;
}
//循环攻击

int check_fight(object me,object target,int count)
{
	object wp;
	int n;
	string msg;
	
	//target = offensive_target(me);

	
	if (!me) return 1;
	n=me->query_skill("dagou-bang",1)+me->query_skill("bangjue",1);
	n=n+random(n);

	if( target->is_ghost()||!objectp(target))
	{
			msg = HBYEL"$N将"+wp->name()+HBYEL"向后一摆，收回了招式。\n"NOR;
			message_vision(msg, me);
			return remove_effect(me);
	}
	else if(!objectp(wp = me->query_temp("weapon"))
		||wp->query("skill_type")!="stick")
	{
		msg = HIG"$N手中武器既失，转字诀也随之停了下来。\n"NOR;
	
		message_vision(msg, me);
		return remove_effect(me);
	}	
	else if(!living(target))
	{
		msg = HIW"$N不屑地看了$n一眼，神色自若地将"+wp->name()+HIW"收了回来。\n"NOR;
		message_vision(msg, me,target);
		return remove_effect(me);
	}

	else if(!me->is_fighting() || !living(me)||count<0)
	{
			msg = HBYEL"$N将手中"+wp->name()+HBYEL"一收，脚步停了下来。\n"NOR;
			message_vision(msg, me);
			return remove_effect(me);

	}
	else if( me->query_skill_mapped("stick") != "dagou-bang"||me->query_skill_mapped("parry") != "dagou-bang")
	{
			msg = HBYEL"$N招数一变，使出另一路棒法来。\n"NOR;
			message_vision(msg, me);
			return remove_effect(me);
	}
	else if( me->query("jingli") <= 300 )
	{
			msg = HBYEL"$N棒招渐缓，原来是精力不足了。\n"NOR;
			message_vision(msg, me);
			return remove_effect(me);
	}
	else if( random((int)me->query_int()) < target->query_int()/4)
	{
			msg = HIW"$n奋力跳起，回身在"+wp->name()+HIW"上一拨，$N始料不及，急忙收招。\n"NOR;
			message_vision(msg, me,target);
			return remove_effect(me);
	}
		
	//开始掉精
	msg = zhuan_msg[random(sizeof(zhuan_msg))];
	msg = replace_string(msg, "$W", wp->name());
	msg += "\n"NOR;
	message_vision(msg, me, target);
	
	
	//每回合都掉精
	me->receive_damage("neili",100);
	target->receive_damage("jingli", n, me);
	target->receive_damage("jing", n, me);
	if((int)target->query("jingli")< 0) target->set("jingli",0);
	message_vision(MAG"$n感觉自己左冲右突，不得其法，烦躁不堪，精力精气都大为损耗！\n"NOR,me,target);
	
	call_out("check_fight",1,me,target,count--);
}
int help(object me)
{
	write(HBYEL"\n打狗棒「转字诀」："NOR"\n");
	write(@HELP
	「转字诀」将打狗棒“轻”“灵”“奇”“巧”的特点发挥得淋
	漓尽致，以专攻对手的后心几大要穴为主，一旦施展开
	来，将会迫使对手不停地象螺砣般旋转，以趋避点打。
	结果是愈逃棒越急，对手纵使暗暗叫苦却也无计可施，
	最后因耗尽体力和精力而败下阵去。
	
	解开天下无狗，能棒诀和招式融合之后，方可使用本招
	本招的主要功效为破防和回合中消耗对方精力精气，堪
	为打狗棒高深的功夫。和缠字诀不能组合攻击
	
	注意：有效设置打狗棒转字诀会产生特效
	
	set 打狗棒转字诀 破防
	
	指令：perform stick.zhuan

要求：
	最大内力 2000 以上；
	当前内力 800 以上；
	当前精力 800 以上；
	打狗棒等级 180 以上；
	混天气功等级 180 以上；
	打狗棒诀等级 180 以上：
	激发招架为打狗棒。
HELP
	);
	return 1;
}
