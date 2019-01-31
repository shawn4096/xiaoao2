// By Spiderii 更新效果

#include <ansi.h>

inherit F_SSERVER;
string perform_name() {return HBYEL"诸天化身步"NOR;}
int perform(object me, object target)
{
        string msg;
        int i;
        
        if (! me->is_fighting())
                return notify_fail("你只能在战斗种使用诸天化身步。\n");

        if ((int)me->query_skill("linji-zhuang", 1) < 100)
                return notify_fail("你的临济十二庄还不够火候，使不出诸天化身步。\n");  

        if ((int)me->query_skill("anying-fuxiang", 1) < 100)
                return notify_fail("你的暗影浮香还不够火候，使不出诸天化身步。\n");  

        if ((int)me->query("jing", 1) < 500)
                return notify_fail("你现在精不够。\n");

        if ((int)me->query("neili", 1) < 500)
                return notify_fail("你现在内力不够。\n");

        if (me->query_temp("emei/parry"))
                return notify_fail("你正在使用诸天化身步。\n");

        msg = HBYEL "你使出暗影浮香的诸天化身步，身手登时更加灵巧！\n\n" NOR; 

        me->add("neili", -200 + random(100));
        me->recieve_damage("jing", 50);        
        tell_object(me,msg);
        
        i = me->query_skill("linji-zhuang", 1) / 5;
		
	CHAR_D->addfightbuff(me,"dodge|parry",i,i,"anying-fuxiang|dodge","emei/parry",HBYEL"$N心力一阵不济，「诸天化身步」无法持续了。");
		
		
       // me->set_temp("emei/parry", i);
       // me->add_temp("apply/dodge", i);
       // me->add_temp("apply/parry", i);
        
		
        
        //remove_call_out("remove_effect");
       // call_out("remove_effect", 1, me, (int)me->query_skill("force",1) / 3);
        return 1;
}

void remove_effect(object me, int count)
{
        int i;
        
        if (!me) return;
		i = me->query_temp("emei/parry");

        if (!me->is_fighting()
			||me->query_skill_mapped("dodge") != "anying-fuxiang" 
			||count < 1)
        {
                me->add_temp("apply/dodge", - i);
                me->add_temp("apply/parry", - i);
                me->delete_temp("emei/parry");
                tell_object(me, HIW "你停止了诸天化身步，深深的吸了口气。\n" NOR);
                return;
       }
       call_out("remove_effect", 1 ,me ,count -1);
}


int help(object me)
{
        write(HIB"\n暗影浮香之"+BLU"「诸天化身步」"NOR"\n");
        write(@HELP

	郭襄自和杨过分别后，心中日夜思念期盼杨过，渐渐形
	销骨立，了无生趣。她在百花谷中苦练，终于悟出了一
	套轻身功法。她将这套功法定名为暗影浮香步。
	
	perform dodge.huashen

要求：
	临济十二庄要求 100 级以上
	暗影浮香要求 100 级以上	
	当前内力要求 500 以上
	当前精力要求 500 以上	
HELP
        );
        return 1;
}


