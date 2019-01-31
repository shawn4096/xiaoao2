// Modified by Darken@SJ
#include <ansi.h>

string exert_name() { return HIY"桃花奇门诀"NOR; }

#include <ansi.h>
int exert(object me)
{       
        int level=me->query_skill("qimen-bagua", 1);
		int i=me->query("int");
        
		if ((int)me->query_skill("qimen-bagua", 1) < 80)
                return notify_fail("你的奇门八卦修为还不够。\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不够。\n");
        if( me->query_temp("thd/is_smart")   )
                return notify_fail("你正在运用奇门心法！\n");

       
        
		//这里采用通用buff函数 
		//参数：目标 buff名 buff值 buff时间 临时标记,散功描述		
		
		if (CHAR_D->addbuff(me,"intelligence",i,level/10,"thd/is_smart",HIW"$N的思路浑浊，只好散去了「奇门」心法。"))
		 {
			
			 
			   me->add("neili", - (200+random(200)));
			   message_vision(HIW"$N仔细的思考奇门八卦之学，脑中顿时豁然开朗！\n"NOR, me);
		 }
		 
		//me->set_temp("thd/is_smart", 1);
		
        //me->add_temp("apply/intelligence",i);
       
        //me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), level );
		//call_out("remove_effect",(int)level/5,me,i);
        return 1;
}

void remove_effect(object me,int i)
{
        if( !me || !me->query_temp("thd/is_smart")) return;
        
		me->add_temp("apply/intelligence",-i);
        me->delete_temp("thd/is_smart");
        tell_object(me, HIW"你的思路浑浊，只好散去了「奇门」心法。\n"NOR);
}

int help(object me)
{
        write(HIG"\n「桃花奇门诀」："NOR"\n");
        write(@HELP

	思考奇门八卦之易理，达到暂时增加学习效率的心法诀窍。
	在作用期间，战斗中也能由特殊技巧的互相配合，激发潜
	能，领悟更深一层的武学，发挥更上一层，更加奇诡的桃
	花武功。

	指令：exert qimen

要求：
	奇门八卦等级 80 以上；
	最大内力 500 以上。
	激发内功碧海潮生功；
HELP
        );
        return 1;
}

