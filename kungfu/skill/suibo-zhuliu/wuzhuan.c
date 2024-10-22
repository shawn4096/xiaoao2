// By Darken@SJ

#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;

string perform_name() { return HIG"奇门五转"NOR; }

int perform(object me)
{
       string msg;
       int i;

       if( !me->is_fighting() && (me->query_skill("suibo-zhuliu",1) < 400 ))
                return notify_fail("奇门五转只能在战斗中使用。\n");
       if( (int)me->query_skill("bihai-chaosheng",1) < 150 )
                return notify_fail("你的碧海潮生功还不够火候，使不出奇门五转。\n");  
       if( (int)me->query_skill("suibo-zhuliu",1) < 150 )
                return notify_fail("你的随波逐流还不够火候，使不出奇门五转。\n");  
       if( (int)me->query_skill("qimen-bagua",1) < 150 )
                return notify_fail("你的奇门八卦还不够火候，使不出奇门五转。\n");  
       if( (int)me->query("jingli", 1) < 500 )
                return notify_fail("你现在精力不够。\n");
       if( (int)me->query("neili", 1) < 200 )
                return notify_fail("你现在内力不够。\n");
       if (me->query_temp("thd/is_fast"))
                return notify_fail("你正在使用奇门五转。\n");

      
       i = me->query_skill("qimen-bagua", 1)/10 + me->query_skill("qimen_baguazhen",1)/20 + me->query_skill("dodge",1)/10;
 
 //这里测试战斗buff
   //me, buffname,buffvalue,cout,skillslist,tempmark,msg
   if(CHAR_D->addfightbuff(me,"dexerity",i,i,"suibo-zhuliu|dodge","thd/is_fast",HIW"$N内力不济，身法慢了下来。"))
   {
	    me->set_temp("double_attack", 1);
	    msg = HIW "$N一声清啸，使出桃花岛的绝学奇门五转，脚踏着八卦方位，步法虚虚实实，行若鬼魅，身法陡然加快！\n\n"NOR; 

       me->add("neili", -(200+random(300)));
       me->add("jingli", -(100+random(50)));
       message_vision(msg, me);
	   if (me->query_skill("suibo-zhuliu",1) < 400) me->start_perform(1, "奇门五转");
   }


	 // me->add_temp("apply/dexerity", i);
     //  me->set_temp("thd/is_fast", i);
    //   me->set_temp("double_attack", 1);
    //   if (me->query_skill("suibo-zhuliu",1) < 400) me->start_perform(1, "奇门五转");
   //    call_out("remove_effect", 1, me, i, i);
       return 1;
}
void remove_effect(object me, int count, int dex)
{
        if (!me) return;
        if( me->query_skill_mapped("dodge") != "suibo-zhuliu" 
         || (!me->is_fighting() && (me->query_skill("suibo-zhuliu",1) < 400 ))
         || me->query("neili") < 100
         || count < 1){
                me->add("neili", - (100 + random(100)));
                me->add_temp("apply/dexerity", -dex);
                me->delete_temp("thd/is_fast");
                me->delete_temp("double_attack");
                message_vision(HIW"$N内力不济，身法慢了下来。\n"NOR, me);
                return;
        }
        call_out("remove_effect", 1 , me, count -1, dex);
}

int help(object me)
{
        write(HIG"\n「奇门五转」："NOR"\n");
        write(@HELP

	黄药师所创之诡异身法。使用奇门八卦配合随波逐流
	步法，使行动令对手出乎意料，无法预测，因而提升
	闪躲以及命中的机率，同时也加快攻击的速度使对手
	防不胜防。配合其他桃花岛特殊技巧，更能事半功倍。
	
	指令：perform dodge.wuzhuan

要求：  
	碧海潮声等级 150 以上；
	奇门八卦等级 150 以上；
	随波逐流等级 150 以上；
	每回合消耗内力；	
	随波逐流等级 400 以上使用时减少收招时间。
HELP
        );
        return 1;
}

