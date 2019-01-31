// Created by Numa 2000.1.25
// Modified by darken@SJ

#include <ansi.h>
#include <combat.h> 
#include "/kungfu/skill/eff_msg.h"
inherit F_SSERVER;

void remove_tuota(object me, int count);

string perform_name() {return HBYEL+HIW"托塔手"NOR;}

int perform(object me, object target)
{
		int i, j, damage, num, p, win=0;
		int tmp,focus,skill;
		string msg;
		focus = me->query_temp("ss/focus");
		skill = me->query_skill("songyang-shou", 1);
		if( !target ) target = offensive_target(me);
		
		if( !target
		|| !target->is_character()
		|| !me->is_fighting(target) 
		|| !living(target))
			return notify_fail("托塔手绝技只能对战斗中的对手使用。\n");

		if( (int)me->query_skill("songyang-shou", 1) < 250 )
			return notify_fail("你的大嵩阳手火候不够。\n");

		if( (int)me->query_skill("parry", 1) < 250 )
			return notify_fail("你的基本招架火候不够。\n");

		if( (int)me->query_skill("hanbing-zhenqi", 1) < 250 )
			return notify_fail("你的基本内功火候不够。\n");

		if( (int)me->query("max_neili") < 3500 )
			return notify_fail("你的内力修为不够。\n");

		if( (int)me->query("neili") < 800 )
			return notify_fail("你的真气不够。\n");

		if( (int)me->query("jingli") < 500 )
			return notify_fail("你的精力不够。\n");

		if (userp(me)&&!me->query("quest/ss/sys/tuota/pass"))
			return notify_fail("你不会托塔手绝技。\n");
		if (me->query_temp("sys/tuota"))
			return notify_fail("你正在施展托塔手绝技。\n");
		
		if (me->query_skill_mapped("force") != "hanbing-zhenqi")
			if (me->query_skill_mapped("force") != "lengquan-shengong")
			return notify_fail("你内功属性和托塔手绝技不符合?\n");

		if (me->query_skill_prepared("hand") != "songyang-shou"
		|| me->query_skill_mapped("parry") != "songyang-shou"
		|| me->query_skill_mapped("hand") != "songyang-shou")
			return notify_fail("你现在无法使用嵩阳手。\n");

		if (me->query_temp("weapon"))
			return notify_fail("托塔手绝技只能空手使用！\n");

		if( me->query_temp("sys/tuota"))
			return notify_fail("你正在使用托塔手绝技。\n");

		me->add("neili", -200);
		me->add("jingli", -50);
		message_vision(HIY "\n$N双腿微微屈，扎好马步，猛然大喝一声，双手上托，宛如托起千斤重塔，声势雄壮，手上的劲力显然增加不少！\n" NOR,me);

		me->add_temp("apply/attack", skill/3);
		me->add_temp("apply/damage", skill/6);
		me->add_temp("apply/hand", skill/5);

		me->set_temp("sys/tuota", skill);
		
		remove_tuota(me,skill/30);

        return 1;
}


void remove_tuota(object me, int count)
{
		int skill;
		if (!me) return;
		skill=me->query_temp("sys/tuota");
		if(!me->is_fighting()
		|| me->query_temp("weapon")
		|| me->query_skill_prepared("hand") != "songyang-shou"
		|| me->query_skill_mapped("hand") != "songyang-shou"
		|| count < 1 )
		{
			me->add_temp("apply/attack", -skill/3);
			me->add_temp("apply/damage", -skill/6);
			me->add_temp("apply/hand", -skill/5);

			message_vision(HIY "\n$N缓缓释放托塔手所蓄积的浊气！\n" NOR,me);
			me->delete_temp("sys/tuota");
			return;
		}
		call_out("remove_tuota", 1, me, count - 1);
}

int help(object me)
{
	write(HIW"\n大嵩阳手之"+HIY"「托塔手」："NOR"\n\n");
        write(@HELP
	大嵩阳手乃是嵩山弟子入门武技，但这门武功中蕴含
	的意境去不容小觑。这招的特点是依靠自己强大内力
	灌注于双手，所以若功力高深者，运用此招，再辅助
	以独门内劲寒冰真气，威力独具特色。
	托塔手是嵩山十三太保之首的丁勉绝技，一手大嵩阳
	手出神入化，冠绝江湖。

	指令：perform hand.tuota

要求：
	最大内力  3500 以上；
	当前内力  800  以上；
	当前精力  500  以上；
	寒冰真气  250  级以上；
	大嵩阳手  250  级以上；
	激发手法为嵩阳手；
	激发招架为嵩阳手
	激发内功为寒冰真气或阴性内功;
	备手法为嵩阳手；
	空手；
HELP
        );
        return 1;
}