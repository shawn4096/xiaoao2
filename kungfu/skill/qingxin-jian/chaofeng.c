// chaofeng.c 百鸟朝凤
// cck 13/6/97
//edit by sohu
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon,tweapon;
        string msg;
        string msg1;
	
		int skill;
		skill=me->query_skill("qingxin-jian",1);

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「百鸟朝凤」只能在战斗中对对手使用。\n");
		tweapon=target->query_temp("weapon");
        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if( (int)me->query_skill("qingxin-jian", 1) < 100 )
                return notify_fail("你的清心普善剑不够娴熟，不会使用「百鸟朝凤」。\n");

        if( (int)me->query_skill("tianmo-gong", 1) < 100 )
                return notify_fail("你的天魔功等级不够，不能使用「百鸟朝凤」。\n");
		if( me->query_skill_mapped("sword")!="qingxin-jian" 
			||me->query_skill_mapped("parry")!="qingxin-jian" )
                return notify_fail("你没能激发清心普善剑，不能使用「百鸟朝凤」。\n");
		if( (int)me->query_dex() < 30 )
                return notify_fail("「百鸟朝凤」需要高臂力，你的后天身法不够30，不能使用「百鸟朝凤」。\n");

        if( (int)me->query("neili", 1) < 250 )
                return notify_fail("你现在内力太弱，不能使用「百鸟朝凤」。\n");
        if( (int)me->query("jingli", 1) < 200 )
                return notify_fail("你现在精力太弱，不能使用「百鸟朝凤」。\n");         
             
		if( me->query_temp("qxj/chaofeng") )
                return notify_fail("你正在使用「百鸟朝凤」。\n");
        
		message_vision(HIM "$N说打便打，事先更没半点征兆，出手如电，一剑「百鸟朝凤」便刺了过来,$n招架不及，只得躲闪开去！\n" NOR,me,target);
       // msg1 = BBLU+HIY "$N长啸一声，剑锋回指,姿势怪异但却潇洒无比。\n" NOR;

     //   message_vision(msg, me, target);
		//强化下对npc的攻击
		if (!userp(target)) {
			skill=skill+me->query_skill("qingxin-jian",1)/6;
			target->start_busy(1);
			
		}
		if (me->query_temp("qxj/qingxin"))
		{
			message_vision(HIR"$n闻听清心普善咒的清音，不觉着迷，手势减缓，顿时为$N所乘，数招连出！\n"NOR,me,target);
			target->start_busy(1);

		}
		if (me->query("env/清心剑")=="夺兵")
			if (objectp(tweapon)&&(random(me->query_skill("qingxin-jian",1))>target->query_skill("parry",1)/2
			||random(me->query_dex(1))>target->query_dex(1)/2))
		{
						
			message_vision(HIW"$n更没料到$N这一招乃是虚招，身子略转之际，右手一松，"+tweapon->query("name")+"给$N夺了过去。\n"NOR,me,target);
			tweapon->move(environment(target));

		}
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/sword",skill/5);
		me->add_temp("apply/damage",skill/5);
		me->set_temp("qxj/chaofeng",1);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	
		
		if (me->query_temp("qxj/qingxin")&&objectp(me)&&objectp(target)) {
			message_vision(HIC"$N身子不停，见$n身形迟缓，又瞬间连刺二剑，所合身法剑招，一模一样！\n"NOR,me,target);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?3:1);
		}
		
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/sword",-skill/5);
		me->add_temp("apply/damage",-skill/5);
        me->add("neili", -150);
		me->delete_temp("qxj/chaofeng");

		me->start_perform(3,"「百鸟朝凤」");   
	    return 1;
}

string perform_name() {return HIC"百"HIR"鸟"HIW"朝"HIM"凤"NOR;}

int help(object me)
{
    write(HIY"\n清心普善剑「百鸟朝凤」："NOR"\n");
    write(@HELP
	清心普善剑是源自任盈盈的武学所演化，招式
	大都采集笑傲江语原著，名字不可靠，但为了
	纪念这位聪明睿智，心狠手辣的小魔女同时兼
	顾日月女性玩家的癖好以及特点归纳而成。
	清心剑乃初级武功，为以后剑法线路的七弦无
	形剑做准备。不限内功。
	百鸟朝凤，是演化自盈盈大战嵩山派所用武功
	连续三招，若解开盈盈小谜题且使用清心普善
	咒的条件下，会再出两招后招。
	注意，此招如果身法高，则会自动出迅捷夺兵
	效果，反应其轻灵特效: set 清心剑 夺兵
    
	指令：perform sword.chaofeng
	
要求：
	清心普善剑等级 100 级以上；
	基本剑法等级 100 级以上，
	当前内力要求 250 以上，
	当前精力要求 200 以上，
	当前有效身法 30 以上；
	激发剑法清心普善剑；
	激发招架清心普善剑；
	需手持剑类武器。    

HELP
	);
	return 1;
}

