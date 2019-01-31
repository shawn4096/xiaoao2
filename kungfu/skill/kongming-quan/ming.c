// ming.c  
// by tiantian@sj 2000.6.19

#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return HIC"明"NOR; }

int perform(object me,object target)
{
    int lvl=me->query_skill("kongming-quan",1)+me->query_skill("xiantian-gong",1);
	
	if (!target) target = offensive_target(me);
	if (!target || !me->is_fighting(target))
		return notify_fail("“明”字诀只能在战斗中使用。\n");                
    if (me->query_temp("weapon"))
		return notify_fail("你手持兵器，不能使用“明”字诀。\n");   
	if (me->query_skill("kongming-quan", 1) < 300)
		return notify_fail("你的空明拳尚不纯熟，还不能使用“明”字诀。\n");        
	if (me->query("neili") < 2000)
		return notify_fail("你现在内力不足，不能使用“明”字诀！\n");
//	if (me->query_temp("kongming/kong"))
//		return notify_fail("你正在使用“空”字诀！\n");      
    if (!me->query("quest/jiebai/pass"))
        return notify_fail("你没有和周伯通结义，不能使用“明”字诀。\n");
	if (me->query_temp("kongming/ming"))
		return notify_fail("你正在使用“明”字诀！\n");      
	message_vision(HIC"\n$N长啸一声，拳法陡然加快，双手拳招源源而出。拳风舞动如云如雾，将周身防御的水泄不通。\n"NOR, me);
	me->add("neili", -300); 
	if (!me->query("quest/hubo/pass") )
		me->start_perform(2,"明字诀");
	me->set_temp("kongming/ming", lvl);
	me->add_temp("apply/armor",lvl/3);
	me->add_temp("apply/parry",lvl/3);
	call_out("remove_effect", 1, me,(int)me->query_skill("kongming-quan")/10);
	return 1;
}

void remove_effect(object me,int count)
{
	
	int lvl;
	if (!me) return;
	lvl	=me->query_temp("kongming/ming");

	if (!me->is_fighting()
		||me->query_skill_mapped("cuff")!="kongming-quan"
		||count<0)
	{
		me->delete_temp("kongming/ming");
		me->add_temp("apply/armor",-lvl/3);
	    me->add_temp("apply/parry",-lvl/3);
		tell_object(me, HIC"\n你拳法一窒，全身劲气一震，出手不由得慢了下来。\n"NOR);
		return;

	}
	call_out("remove_effect",2,me,count--);
	//return;
	
}
int help(object me)
{
	write(HIY"\n空明拳之「明字诀」："NOR"\n\n");
	write(@HELP
	空明拳是天下至柔的拳术，是周伯通从《道德经》中化
	出来的，《道德经》中有言道：“兵强则灭，木强则折。
	坚强处下，柔弱处上。”又云：“天下莫柔弱于水，而攻
	坚强者莫之能胜，其无以易之。弱之胜强，柔之胜刚，
	天下莫不知，莫能行。那降龙十八掌却是武学中至刚至
	坚的拳术。空明拳之空字诀，看似是空，实际是以虚化
	实的高明口诀，阴柔无比。攻击性不强，但反击力度靠
	自身的实力。
	「明字诀」乃是以极高明的招式来增强自身的防御效果
	以道家圆融汇通，冲虚圆润的道理为根基，将对方功力
	化解，真是未学会打人先要学会挨打的本意。

	指令：perform cuff.ming

要求：	
	最大内力 3000 以上；
	当前内力 1500  以上；
	当前精力 1500  以上；
	空明拳等级 300 以上；
	激发拳法招架为空明拳；
	备拳法为空明拳且空手。
	解开双手互博后可以自由使用。

HELP
	);
	return 1;
}