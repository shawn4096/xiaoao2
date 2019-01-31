// chuang.c 闯少林
// sohu@xojh
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int damage;
	string msg;
        int ap, dp;

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
	if (! target || ! me->is_fighting(target))
		return notify_fail("「闯少林」只能对战斗中的对手使用。\n");

	if ((int)me->query_skill("luohan-quan", 1) < 100)
		return notify_fail("你的罗汉拳法不够娴熟，现在还无法使用「闯少林」。\n");
	if (me->query_skill("cuff", 1) < 100)
		return notify_fail("你的基本拳法不够娴熟，现在还无法使用「闯少林」。\n");
  	if (me->query_skill("force", 1) < 100)
		return notify_fail("你的基本内功不够娴熟，现在还无法使用「闯少林」。\n");  
	if (me->query_skill_mapped("force") != "hunyuan-yiqi" &&
            me->query_skill_mapped("force") != "yijinjing" &&
           // me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("你使用的非少林内功，无法施展「闯少林」！\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("你现在真气不够，无法运用「闯少林」。\n");
	if ((int)me->query("jingli") < 200)
		return notify_fail("你现在精气不够，无法运用「闯少林」。\n");			
	
	if (me->query_skill_mapped("cuff") != "luohan-quan"
		||me->query_skill_prepared("cuff") != "luohan-quan") 
		return notify_fail("你没有激发罗汉拳，无法使用闯少林绝技！\n");

	message_vision(HIY "$N" HIY "双拳紧握，站成弓步马的姿势，大吼一声，双拳迅速连出一十三招，拳风呼啸，正是罗汉拳中「闯少林」的招式。\n" NOR,me,target);

        ap = me->query_skill("cuff",1);
        dp = target->query_skill("parry",1);
    if (ap / 2 + random(ap) > dp || !living(target))
	{
		damage = me->query_skill("luohan-quan",1)*me->query_str(1)/10;
		damage=damage+random(damage);
		//COMBAT_D->do_chemis_attack(me,ob,1,damage);
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/5,me);
		me->add("neili", -30);
		message_vision(HIR"只见$n" HIR "一个招架失误，登时被这拳打了个正着，闷哼一声，退了数步。\n" NOR,me,target);
		target->add_busy(2);
	} else 
	{
		message_vision(CYN "可是$p" CYN "轻轻一格，架住了$P"
                       CYN "的来拳。\n" NOR,me,target);
		me->add("neili", -10);
		me->start_busy(1);
	}
	me->add("neili",-100);
	me->add("jingli",-60);
	me->start_perform(2,"闯少林");
	return 1;
}
string perform_name(){ return HIC"闯少林"NOR; }

int help(object me)
{
        write(HIG"\n罗汉拳之"+HIC"「闯少林」："NOR"\n\n");
        write(@HELP
	少林罗汉拳是少林寺入门武技，寻常僧人皆可学的
	但因为要教授入门弟子掌握少林拳法基本原理，所
	以历代高手不断优化推陈出新，虽然招式普通，但
	其蕴含的武学原理不容小觑。练到高深处，这千锤
	百炼的寻常招式，威力也会巨大。
	
	指令：perform cuff.chuang

要求：
	当前内力需求 200 以上；
	最大内力需求 1500 以上；
	当前精力需求 200 以上；
	基本拳法等级 100 以上；
	基本内功等级 100 以上；
	罗汉拳法等级 100 以上；
	激发拳法且备罗汉拳；
	激发少林内功；
HELP
        );
        return 1;
}