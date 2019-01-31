// beiming.c
// modified by action@SJ 2009/2/5
//updated by Zmud@Sjmud 12/3/2009
//edit by sohu@xojh
	//根据解开北冥神功意味着即为逍遥派弟子
	//if (me->query("family/family_name") == "逍遥派") {
		//}
	//北冥真气第一段，解开珍珑拜入遥派弟子，但招式内功威力都一般。
	//北冥真气第二段，无量山解密
	//北冥真气第三段，李秋水+童姥的功力吸收,预留小无相接口

#include <ansi.h>
inherit F_CLEAN_UP;
void remove_effect(object me, int count);

string exert_name(){ return HIC"北溟真气"NOR; }

int exert(object me, object target)
{
	int skill;

    if( me->query("max_neili") < 10000 )
		return notify_fail("你的最大内力不够。\n");
	if( me->query("neili") < 1000 )
		return notify_fail("你的当前内力不够。\n");
	if( me->query("jingli") < 1000 )
		return notify_fail("你的当前精力不够。\n");
    if( me->query_skill("beiming-shengong", 1) < 350 )
		return notify_fail("你的北冥神功等级不够。\n");
	if( me->query_skill("force", 1) < 350 )
		return notify_fail("你的基本内功等级不够。\n");
	if( me->query_skill_mapped("force") != "beiming-shengong" )
		return notify_fail("你的内功不对。\n");

	if( me->query_temp("bmsg/bm") )
		return notify_fail("你已经在运「北溟真气」了。\n");

	skill = (int)me->query_skill("beiming-shengong", 1);

	
	message_vision(HIB "\n$N运起北冥神功口中默念"NOR"："HIB"真气经由灵台，尺泽，曲池，灵海，天宗汇入气海["HIG"北溟"HIB"]，形成一股浩荡之气。\n" NOR, me);
	

	me->set_temp("bmsg/bm", skill); 
	
	me->add_temp("apply/attack", skill/4);
	me->add_temp("apply/intelligence",skill/30);
	me->add_temp("apply/dexerity", skill/20);
	
	me->add_temp("apply/armor", skill/3); 	
	me->add_temp("apply/defense", skill/4);
	me->add_temp("apply/parry", skill/3);
	me->add_temp("apply/dodge", skill/4);

	if (me->query("quest/beiming/second/pass"))
	{
		message_vision(HBBLU+HIW "\n$N流转不息，外袍瞬间隆起，隐隐在$N周身形成一个气罩。\n" NOR, me);
		me->add_temp("apply/attack", skill/4);

		me->add_temp("apply/armor", skill/4); 	
		me->add_temp("apply/defense", skill/4);
		me->add_temp("apply/parry", skill/4);
		me->add_temp("apply/dodge", skill/4);
		me->add_temp("apply/damage",skill/5);
	}
	if (me->query("quest/beiming/third/pass"))
	{
		message_vision(HBWHT+HIG "\n$N北冥神功已臻大乘，举手投足间发出莫大的威力,北冥神功的大威力至此方显。\n" NOR, me);
		me->add_temp("apply/attack", skill/4);
		me->add_temp("apply/constitution", skill/10);
		me->add_temp("apply/strength", skill/15);
		me->add_temp("apply/damage",skill/5);
	}
	if (me->query_skill("beiming-shengong",1)<350)
		me->start_busy(random(2));
	if( me->query_skill("beiming-shengong",1)<450)
		me->start_exert(1, "北溟真气");		
	me->receive_damage("neili", -500);
	me->receive_damage("jingli", -300);

	call_out("remove_effect",60,me);

	return 1;
}

void remove_effect(object me, int count)
{
	int skill;
	write(count);
	
	if (!objectp(me)||!me->query_temp("bmsg/bm")) return;	
	
	skill=me->query_temp("bmsg/bm");	
	
	//if(count<1) 
//	{
		
		me->add_temp("apply/attack", -skill/4);
		me->add_temp("apply/intelligence",-skill/30);
		me->add_temp("apply/dexerity", -skill/20);
	
		me->add_temp("apply/armor", -skill/3); 	
		me->add_temp("apply/defense", -skill/4);
		me->add_temp("apply/parry", -skill/3);
		me->add_temp("apply/dodge", -skill/4);
		if (me->query("quest/beiming/second/pass"))
		{
			me->add_temp("apply/attack", skill/4);

			me->add_temp("apply/armor", skill/4); 	
			me->add_temp("apply/defense", skill/4);
			me->add_temp("apply/parry", skill/4);
			me->add_temp("apply/dodge", skill/4);
			me->add_temp("apply/damage",skill/5);
		}
		if (me->query("quest/beiming/third/pass"))
		{
			me->add_temp("apply/attack", skill/4);
			me->add_temp("apply/constitution", skill/10);
			me->add_temp("apply/strength", skill/15);
			me->add_temp("apply/damage",skill/5);
		}
		
		me->delete_temp("bmsg/bm");
		message_vision(HBWHT+HIG "\n$N缓缓收功，将北冥真气归入丹田气海之中。\n" NOR, me);
		return;
//	}

//	call_out("remove_effect", 1, me, count--);
}
int help(object me)
{
	write(HIW"\n北冥神功之「北溟真气」："NOR"\n\n");
        write(@HELP
	庄子‘逍遥游’有云：‘穷发之北有冥海者，天池也。有鱼焉，
	其广数千里，未有知其修也。’又云：‘且夫水之积也不厚，
	则其负大舟也无力。覆杯水于坳堂之上，则芥为之舟；置杯
	焉则胶，水浅而舟大也。’是故本派武功，以积蓄内力为第
	一要义。内力既厚，天下武功无不为我所用，犹之北冥，大
	舟小舟无不载，大鱼小鱼无不容。是故内力为本，招数为末。
	以下诸图，务须用心修习。
	
	注意：北冥神功分为三段设计规划，威力也会随之发生变化
	第一段：解开珍珑谜题，师傅会传给你北冥真气和北冥神功，
	        北冥的理解仅为皮毛。第一段体现北冥的防御特点。
	第二段：解开无量山画像谜题，获得北冥修炼方法。
			北冥真气基本大成。第二段体现北冥的攻击特点。
	第三段：解开天山童姥和李秋水的谜题，吸收二人功力，最终
			北冥真气彻底圆满。北冥彻底大成。
	
	指令：exert beiming

要求：
	最大内力  10000 以上；
	当前内力  1000  以上；
	当前精力  1000  以上；
	北冥神功  350   以上；
	基本内功  350   以上；
	
HELP
        );
        return 1;
}
