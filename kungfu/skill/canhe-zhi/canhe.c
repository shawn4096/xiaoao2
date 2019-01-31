// canhe.c 参合诀
// cre by sohu@xojh

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string *xue1 = ({ 
        "大锥穴",
        "百会穴",
        "志室穴",
        "肩井穴",
        "劳宫穴",
        "内关穴",
        "外关穴",
        "会宗穴",
});



int perform(object me, object target)
{
	string msg,xuename;
	int i,skill;
	skill=me->query_skill("canhe-zhi",1);
	i=skill/100;
	xuename=xue1[random(sizeof(xue1))];
	if( !target ) target = offensive_target(me);

    if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
		return notify_fail("「参合诀」只能在战斗中使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("你必须空手使用「参合诀」！\n");

	if( (int)me->query_skill("canhe-zhi",1) < 400 )
		return notify_fail("你的参合指不够娴熟，不会使用「参合诀」！\n");

	if( (int)me->query_skill("shenyuan-gong",1) < 400 )
		return notify_fail("你的神元功等级不够，不能使用「参合诀」！\n");

	if( (int)me->query_str(1) < 50 )
		return notify_fail("你的臂力不够强，不能使用「参合诀」！\n");

	if( (int)me->query("max_neili") < 8000 )
		return notify_fail("你的内力太弱，不能使用「参合诀」！\n");

	if( (int)me->query("neili") < 1000 )
		return notify_fail("你的内力太少了，无法使用出「参合诀」！\n");

	if (me->query_skill_prepared("finger") != "canhe-zhi"
	|| me->query_skill_mapped("finger") != "canhe-zhi")
		return notify_fail("你现在无法使用「参合诀」进行攻击。\n");

    if ( me->query_skill_mapped("force") != "shenyuan-gong")
        return notify_fail("没有神元功支持如何使用「参合诀」！\n");
	if ( me->query_skill_mapped("parry") != "canhe-zhi"
	&& me->query_skill_mapped("parry") != "douzhuan-xingyi")
		return notify_fail("你现在无法使用「参合诀」进行攻击。\n");

	if( me->query_temp("chz/canhe"))
		return notify_fail("你正在使用参合指的特殊攻击「参合诀」！\n");
	//if( me->query_temp("chz/ci"))
		//return notify_fail("你正在使用参合指的特殊攻击「参合诀」！\n");
	msg = HIC"\n$N默念参合指的正诀「"HIR"参"HIC"」，和反诀「"HIB"商"HIC"」，内力正反颠倒运行反复"+chinese_number(i)+"次。\n"+
		"内力由丹田上升，往返奔流，最后经由经络蓄积在「"HIY+xuename+HIC"」，蓄势待发。\n" NOR;
	message_vision(msg, me);

	me->set_temp("chz/canhe", skill);
	me->set_temp("chz/xuewei",xuename);
	
	me->add_temp("apply/attack",skill/5);
	me->add_temp("apply/finger",skill/5);
	me->add_temp("apply/damage",skill/5);
	call_out("check_fight",1,me,(int)skill/20,xuename);
	
	return 1;
}

void check_fight(object me, int count,string xuename)
{
	int skill;
	if(!me) return;
	
	skill=me->query_temp("chz/canhe");
	
	if(!me->is_fighting()
	|| me->query_skill_mapped("finger") != "canhe-zhi"
	|| me->query_skill_prepared("finger") != "canhe-zhi"
	|| me->query_temp("weapon")
	|| count < 0 )
	{
	
		me->add_temp("apply/attack",-skill/5);
		me->add_temp("apply/finger",-skill/5);
		me->add_temp("apply/damage",-skill/5);
		me->delete_temp("chz/canhe");
		message_vision(HIC"$N将蓄积在"HIY+xuename+HIC"处的真气缓缓释放，回归丹田！\n"NOR,me);
		me->add_busy(2);
		me->start_perform(3, "「参合诀」");
		return;
	}
	call_out("check_fight", 1, me, count--,xuename);
}

string perform_name(){ return HBCYN+HIR"参合诀"NOR; }

int help(object me)
{
        write(HIC"\n参合指之「参合诀」"NOR"\n\n");
        write(@HELP
	参合指是南慕容氏的绝学，参商相隔，斗转星移，是南慕容
	家传的绝世武技，参合指以强大的内力将内力激发出来，和
	对方搏斗，若习得参合指的绝世秘籍，并不弱与天下其他门
	派的指法绝技。
	参合诀是将慕容氏独特的内力蓄积起来，寻找对方的破绽，
	以强大而独特的内力激发指力，给敌人以重创！

指令：perform finger.canhe

要求：
	当前内力 1000 以上；
	最大内力 8000 以上；
	参合指等级 400 以上；
	神元功等级 400 以上；
	激发指法为参合指；
	招架为参合指或斗转星移
	备指法为参合指；
	当前臂力不小于50。
	且手无兵器,

HELP
        );
        return 1;
}
                                
