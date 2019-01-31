// wugu.c 灵蛇拳法之「柔若无骨」
// Modified by sohu@xojh

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

string perform_name(){ return HIG"灵蛇无骨"NOR; }

int perform(object me, object target)
{
	int skill;
	skill=me->query_skill("lingshe-quanfa",1);        
        if( !target ) target = offensive_target(me);

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「灵蛇无骨」只能对战斗中的对手使用。\n");


	if( userp(me)&&( me->query_skill_mapped("force") != "hamagong"
        && me->query_skill_mapped("cuff") != "lingshe-quanfa") )
                return notify_fail("「灵蛇无骨」必须用灵蛇拳法配合蛤蟆功才能使用。\n");

        if( me->query_skill_prepared("cuff") != "lingshe-quanfa")
                return notify_fail("你的拳法不对，根本不能用出「灵蛇无骨」。\n");  

        if( me->query_skill("lingshe-quanfa", 1) < 350 )
                return notify_fail("你的拳法修为还不够！\n");

        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("你的真气不够，发挥不了威力！\n");                   
        if( me->query_temp("weapon"))
                return notify_fail("你先放下手中的武器再说吧？！\n");     
	if (me->query_temp("lsqf/wugu"))
			return notify_fail("你正在施展「灵蛇无骨」？！\n");  
    message_vision(BLU"\n$N默念灵蛇拳"HIR"「灵蛇无骨」"BLU"要诀，瞬间融汇贯通了拳法中的“柔”、“快”、“奇”、“诡”意境，灵蛇拳法威力大增！！\n"NOR,me);


	me->add_temp("apply/cuff",skill/6);
    me->add_temp("apply/attack",skill/4);
	me->add_temp("apply/damage",skill/8);

	if (me->query_temp("hmg_nizhuan"))
	{
	
		message_vision(HIC"$N握拳之手，突然伸出两指，犹如灵蛇吐信，一曲一伸，数道蛤蟆功劲力从指间弹出，$n顿时全身发麻，气息不畅！\n"NOR,me,target);
		target->apply_condition("no_exert",2);
		target->add_busy(3+random(2));
	}

	me->set_temp("lsqf/wugu",skill);
 
	me->add("neili", -450);
	me->add("jingli", -250);
	call_out("lingshe_auto",1,me,(int)skill/50);
	return 1;
}

int lingshe_auto(object me,int count)
{
	int skill;
	
	if (!me) return;
	skill=me->query_temp("lsqf/wugu");
	if (count<0
		||!me->is_fighting()
		||me->query_skill_mapped("cuff")!="lingshe-quanfa"
		||me->query_skill_prepared("cuff")!="lingshe-quanfa")
	{
		me->add_temp("apply/cuff",-skill/6);
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/damage",-skill/8);
		me->delete_temp("lsqf/wugu");
		message_vision(BLU"$N灵蛇劲力一松，「灵蛇无骨」的招式一停，缓缓收功。\n"NOR,me);
		return 1;
	}
	call_out("lingshe_auto",1,me,count--);
	
}
int help(object me)
{
   write(HIB"\n灵蛇拳法之「"HIG"灵蛇无骨"HIB"」："NOR"\n");
   write(@HELP
	为西毒欧阳锋之绝学，乃是他在第一次华山论剑落败后，为
	在下回论剑时出奇制胜，参考毒蛇动作而创出的拳技。施展
	时自身手臂灵动如蛇，宛若无骨；要旨在于手臂似乎能于无
	法弯曲处弯曲，使敌人以为已将自身来拳架开，使出拳的方
	位显得匪夷所思，自身却又在离敌最近之处突然变换方向攻
	击敌人，使敌人大感窘迫而失了先机。
	
	指令：perform cuff.wugu

要求：
	当前内力 1000 以上；
	当前精力 1000 以上；
	灵蛇拳法 350 以上；
	基本拳法 350 以上；
	基本内功 350 以上；
	蛤蟆功   350 以上；
	激发拳法为灵蛇拳法；
	激发招架为灵蛇拳法
	空手不能持有武器；

HELP
   );
   return 1;
}
