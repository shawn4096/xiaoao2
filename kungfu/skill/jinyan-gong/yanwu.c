// Modified by action@SJ 2008/09/15

#include <ansi.h>

inherit F_SSERVER;
void remove_effect(object me,int count);

string perform_name() {return HIR"鹰"HIC"飞"HIW"雁"HIM"舞"NOR;}
int perform(object me, object target)
{
        string msg;
        int i;
        
        if (!me->is_fighting())
                return notify_fail("你只能在战斗种使用「鹰飞雁舞」。\n");
        
	//	if( !target ) target = offensive_target(me);
	//	if (target!=me)
	//	{
		//	return notify_fail("你只能在战斗对自己使用「鹰飞雁舞」。\n");
	//	}
        if ((int)me->query_skill("xiantian-gong", 1) < 300)
                return notify_fail("你的先天功还不够火候，使不出「鹰飞雁舞」。\n");  

        if ((int)me->query_skill("jinyan-gong", 1) < 300)
                return notify_fail("你的金雁功还不够火候，使不出「鹰飞雁舞」。\n");  

        if ((int)me->query_skill("dodge", 1) < 300)
                return notify_fail("你的基本轻功还不够火候，使不出「鹰飞雁舞」。\n");  

        if ((int)me->query("jing", 1) < 500)
                return notify_fail("你现在精不够。\n");

        if ((int)me->query("neili", 1) < 500)
                return notify_fail("你现在内力不够。\n");

        if (me->query_temp("jyg/yanwu"))
                return notify_fail("你正在使用「鹰飞雁舞」。\n");

        msg = HIW "你长啸一声，身法陡然加快，犹如鹰击长空、又如群雁飞舞，令人眼花撩乱，煞是好看。\n\n" NOR; 

        me->add("neili", -200 + random(100));
        me->recieve_damage("jingli", 50);
        
        
        i = me->query_skill("xiantian-gong", 1) / 5;

        me->add_temp("apply/dodge", i);
        if (me->query("quest/qz/jyg/shangtianti/pass"))
        {
			me->add_temp("apply/parry", i);
			me->add_temp("apply/dexerity", i/10);
			msg += HIY "你将所领悟"HIR"「上天梯」"HIY"的功夫施展出来，在悬崖辛苦修炼的功夫这时显现出来，起落间身轻如燕。\n\n" NOR; 

        }
		
        me->set_temp("jyg/yanwu", i);
        
		tell_object(me,msg);
  
      //  remove_call_out("remove_effect");
        call_out("remove_effect", 1, me, (int)me->query_skill("dodge",1) / 10);
        return 1;
}

void remove_effect(object me,object target, int count)
{
	   int i;
	   if(!me || !me->query_temp("jyg/yanwu")) return;
	   i=me->query_temp("jyg/yanwu");
	   
	   if (!me->is_fighting()
		   ||count<0
		   ||me->query_skill_mapped("dodge")!="jinyan-gong")
	   {
         me->add_temp("apply/dodge", - i);
		 if (me->query("quest/qz/jyg/shangtianti/pass"))
         {
			 me->add_temp("apply/parry", - i);
			 me->add_temp("apply/dexerity", - i/10);
		 }
		 me->delete_temp("jyg/yanwu");
         tell_object(me, HIW "你身形渐停，深吸一口气，收回了「鹰飞雁舞」轻功绝技。\n" NOR);
         return;
	   }
	   //上天梯绝技
	   
	   if (me->is_busy()
		   && me->query("neili")>1500
		   && me->query("env/金雁功")=="上天梯"
		   && random(me->query_skill("jinyan-gong",1))>(me->query_skill("jinyan-gong",1)/2)
		   && me->query("quest/qz/jyg/shangtianti/pass"))
	   {
			if (!me->query("quest/qz/xtg/daojue/pass"))
				me->add("max_neili",-1-random(2));	
			tell_object(me, HIR "你眼见情形危机，当下奋起全身功力向上一纵，施展出「上天梯」的绝技。\n" NOR);
			tell_object(me, HIY "瞬间摆脱了自己忙碌的状态！\n" NOR);
			me->start_busy(-1);
			
			//me->clear_codition("no_perform");
			me->add("neili",-1000-random(500));
	   }
	   else if (me->query_condition("no_perform")
		   && me->query("neili")>1500
		   && me->query("env/金雁功")=="上天梯"
		   && random(me->query_skill("jinyan-gong",1)>me->query_skill("force",1)/2)
		   && me->query("quest/qz/jyg/shangtianti/pass"))
	   {
			if (!me->query("quest/qz/xtg/daojue/pass"))
				me->add("max_neili",-1-random(2));	
			tell_object(me, HIM "你眼见情形危机，当下奋起全身功力向上一纵，施展出「上天梯」的绝技。\n" NOR);
			tell_object(me, HIY "瞬间摆脱了自己无法出招的窘况！\n" NOR);
			//me->start_busy(-1);
			
			me->clear_codition("no_perform");
			me->add("neili",-1000-random(500));
	   }
       call_out("remove_effect", 2, me,count--);
       return;
                                     
}

int help(object me)
{
        write("\n金雁功之"+HIC"「鹰飞雁舞」："NOR"\n\n");
        write(@HELP
	金雁功是全真教重要的轻功身法，修炼到高深境界
	身轻如燕不说，对于内功的修炼都有裨益，是一门
	典型的内外兼修的功法。
	金雁功越到后期功力越是深厚，所体现出来的效果
	越是明显，其中门派中重要的轻功绝技「上天梯」
	若得到高人相授则，可在危难之际，脱离对方的袭
	扰，成功救你一命。
	设置；set 金雁功 上天梯(需要解密)

	指令：perform dodge.yanwu

要求：
	当前内力需求 500 以上；
	当前精力需求 500 以上；
	金雁功法等级 300 以上；
	先天功法等级 300 以上；
	基本轻功等级 300 以上；
	激发轻功为金雁功；

HELP
        );
        return 1;
}


