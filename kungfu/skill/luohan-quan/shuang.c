// shuang.c 双圈手
// sohu@xojh
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int remove_shuang(object me,int count);

int perform(object me, object target)
{
	int skill;
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
	if (! target || ! me->is_fighting(target))
		return notify_fail("「双圈手」只能对战斗中的对手使用。\n");

	if ((int)me->query_skill("luohan-quan", 1) < 100)
		return notify_fail("你的罗汉拳法不够娴熟，现在还无法使用「双圈手」。\n");
	if (me->query_skill("cuff", 1) < 100)
		return notify_fail("你的基本拳法不够娴熟，现在还无法使用「双圈手」。\n");
  	if (me->query_skill("force", 1) < 100)
		return notify_fail("你的基本内功不够娴熟，现在还无法使用「双圈手」。\n");  
	if (me->query_skill_mapped("force") != "hunyuan-yiqi" &&
            me->query_skill_mapped("force") != "yijinjing" &&
           // me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("你使用的非少林内功，无法施展「双圈手」！\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("你现在真气不够，无法运用「双圈手」。\n");
	if ((int)me->query("jingli") < 200)
		return notify_fail("你现在精气不够，无法运用「双圈手」。\n");			
	
	if (me->query_skill_mapped("cuff") != "luohan-quan"
		||me->query_skill_prepared("cuff") != "luohan-quan") 
		return notify_fail("你没有激发罗汉拳，无法使用双圈手绝技！\n");
	skill=me->query_skill("luohan-quan",1);

	message_vision(MAG"$N" MAG "危急之中，身腰左转成寒鸡势，双掌举过额角，左手虎口与右手虎口遥遥相对，却是罗汉拳中的一招「"HIG"双圈手"MAG"」招式！\n"
	+"这一招凝重如山，敌招不解自解。不论$n从哪一方位进袭，全在$N的「"HIG"双圈手"MAG"」笼罩之下。\n" NOR,me,target);


    me->add_temp("apply/parry",skill/4);
	me->set_temp("lhq/shuang",skill);
	//call_out("remove_shuang",1,me,(int)skill/50);
	remove_shuang(me,skill/50);
 
	me->add("neili",-100);
	me->add("jingli",-60);
	me->start_perform(2,"双圈手");
	return 1;
}
int remove_shuang(object me,int count)
{
	int skill;
	if (!me) return;
	skill=me->query_temp("lhq/shuang");
	if (me->is_busy()
		||!me->is_fighting()
		||me->query_skill_mapped("cuff")!="luohan-quan"
		||me->query_temp("weapon")
		||me->query_skill_prepared("cuff")!="luohan-quan")
	{
		message_vision(MAG"$N长吁一口气，撤去了双圈手的防御劲力！\n"NOR,me);
		me->add_temp("apply/parry",-skill/4);
		return 1;
	}
	call_out("remove_shuang",1,me,count--);
}
string perform_name(){ return HIR"双圈手"NOR; }

int help(object me)
{
        write(HIG"\n罗汉拳之"+HIR"「双圈手」："NOR"\n\n");
        write(@HELP
	少林罗汉拳是少林寺入门武技，寻常僧人皆可学的
	但因为要教授入门弟子掌握少林拳法基本原理，所
	以历代高手不断优化推陈出新，虽然招式普通，但
	其蕴含的武学原理不容小觑。练到高深处，这千锤
	百炼的寻常招式，威力也会巨大。
	双圈手是双手一横一竖，形成一个井字，将对方虚扣
	再内，对方一旦攻击，则顺势劲力翻转，是典型的
	防守反击性招式。此招易学难练，精义之处需要向
	高人请教方可领悟。
	
	指令：perform cuff.jinglan

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