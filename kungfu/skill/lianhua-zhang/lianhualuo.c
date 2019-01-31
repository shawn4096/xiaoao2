// lianhualuo.c 莲花落 by sohu@xojh 2014 
// 定位：丐帮弟子吟唱莲花落，依靠高明的步法和口中念念有词，牵制对手
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name(){ return HIM"莲花落"NOR; }

string *color = ({ RED+"",GRN+"",YEL+"",BLU+"",MAG+"",CYN+"",
HIR+"",HIG+"",HIY+"",HIB+"",HIM+"",});

int perform(object me, object target)
{
	int tbusy, i, j;
	string msg;
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 ||!target->is_character()
	 ||!me->is_fighting(target) )
		return notify_fail("「莲花落」只能对战斗中的对手使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("「莲花落」只能空手使用。\n");

	if( me->query_skill_prepared("strike") != "lianhua-zhang"
	 || me->query_skill_mapped("strike") != "lianhua-zhang"
	 || me->query_skill_mapped("parry") != "lianhua-zhang" )
		return notify_fail("你必须用莲花掌才能出此奇功。 \n");

	if( me->query_skill("huntian-qigong",1) < 260 )
		return notify_fail("你的混天气功功力还不足以使用「莲花落」!\n");

	if( me->query_skill("lianhua-zhang",1) < 260 )
		return notify_fail("你的莲花掌修为不够，还不能使出「莲花落」绝技!\n");

	if( me->query_skill_mapped("force") != "huntian-qigong" )
		return notify_fail("你的内功不对。\n");

	if( me->query("max_neili") < 1800 )
		return notify_fail("你的内力修为尚欠火候。\n");
    
	if( me->query_skill_mapped("dodge") !="xiaoyaoyou" )
		return notify_fail("你尚未激发逍遥游，使用不出「莲花落」。\n");
	if( me->query("neili") < 500 )
		return notify_fail("你现在内力不够, 不能使用「莲花落」! \n");

	if( me->query("jingli") < 500 )
		return notify_fail("你现在精力不够, 不能使用「莲花落」! \n");

	if( target->is_busy())
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

	if( me->query_temp("lhz/lhl") )
		return notify_fail("你现在正在使用「莲花落」绝技，当下气血翻涌，现在还不能使用「莲花落」! \n");
	
	message_vision(HIG"\n$N悄然运起逍遥游，脚下顿时变得迅捷无比起来，衣袂飘飘，行动如风。\n"
                       +"$n一时不察，$N双掌在胸前一并，然后双腕外翻，又划了两个圆圈后突然分袭向$n。\n"NOR,me,target);
	

	//me->start_perform(3, "莲花落");
	me->set_temp("lhz/lhl",1);
	tbusy = (int)me->query_skill("lianhua-zhang",1) / 100 ;
	if( tbusy < 2 ) tbusy = 2;
	if( tbusy > 3 ) tbusy = 3+random(2);


	i= me->query("combat_exp")/100000;
	j=target->query("combat_exp")/100000;
	if( random(i + j) > j 
		||random(me->query_dex(1))>target->query_dex(1)/2)
	{

		if( !userp(target) ) target->add_busy(tbusy);
		else target->add_busy(1+random(2));
		
		message_vision(HIM "但见$N脚下后退一步，左手一记“千叶莲花”，朝前劈出，在$n身前像火树银花般爆发开来，\n"+
		"同时，$N一阵阵的不断吟唱，“竹龙又替水龙船，斗巧争奇色色鲜，笑煞城东王老爷，听人齐唱落离莲。”\n"+
		"$n一时不察，受$N吟唱影响，一阵心浮气躁，身形立时为其掌法受制。\n"NOR,me,target);
		me->add("neili",-200);
		me->add("jingli",-50);
		//me->start_perform(2, "莲花落");
		target->receive_damage("jing",100+random(1000),me);
		me->delete_temp("lhz/lhl");
		return 1;
	}
	else {
		message_vision(HIM"$n虽被这精妙的一招震得连退了数步，但招式章法却丝毫不乱，竟也勉强接了下来。\n" NOR,me,target);
		if( me->is_fighting(target) && random(i) > j/3
			||random(me->query_int(1))>target->query_int(1)/2 ) {
			message_vision(HIG"只是被莲花掌风所伤，$N立即一吸真气，朝前逼进，右手起处连劈两掌………\n" NOR,me,target);
			//message_vision(msg, me, target);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query("gender")=="女性"?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query("gender")=="女性"?3:1);
			me->start_busy(random(2));
			me->start_perform(3, "莲花落");
		}
		else if( me->is_fighting(target) && random(i) > random(j)/3 ) {
			message_vision(HIB"只是被莲花掌风扫到了下盘，$n便略见窒碍，守护也立见松懈。\n" NOR,me,target);
			
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query("gender")=="女性"?3:1);
			me->start_busy(random(2));
			me->start_perform(2+random(2), "莲花落");
		}
	//    message_vision(msg, me, target);
		me->add("neili",-250);
		me->add("jingli",-150);
	}
	me->delete_temp("lhz/lhl");
	return 1;
}

int help(object me)
{
        write(HIM"\n莲花掌法之「莲花落」："NOR"\n");
        write(@HELP
	莲花落为莲花掌绝技之一。功力达到者可借助逍遥游的武技，施展
	莲花落绝技。莲花落一方面为牵制敌人，利用身法的优势边走边唱
	干扰对方的心神，在对方忙乱之际，陡然发出莲花状的掌锋。防不
	胜防。此招除了自身武技有关外，还与身法和悟性有关系。
	此门武功乃是帮中长老所创，需激发混天气功。

	指令：perform strike.lianhualuo

要求：  
	最大内力 1800 以上；
	当前内力 500 以上；
	当前精力 500 以上；
	莲花掌等级 260 以上；
	混天气功等级 260 以上；
	激发招架为莲花掌。
HELP
        );
        return 1;
}
