#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me,int skill);

int exert(object me, object target)
{
        int skill;
        string fam;
        fam = me->query("family/family_name");

        // 和尚尼姑玩家增加威力
        if (userp(me)
         //  && fam != "少林派"
         //  && fam != "天龙寺"
         //  && fam != "峨嵋派"
           && ! me->query("quest/摩天崖/luohan")
            )
                return notify_fail("你所学的内功中没有这种功能。\n");

        if (target != me)
                return notify_fail("你只能用罗汉伏魔神功来提升自己的战斗力。\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_temp("powerup"))
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        me->add("neili", -100);
        me->receive_damage("qi", 0);
        
         //修改为这里增加和尚尼姑的特殊表述效果一样
        if ((int)me->query_skill("dacheng-fofa", 1) > 100
           ||(int)me->query_skill("buddhism", 1) > 100
           || (int)me->query_skill("huanxi-chan", 1) > 100)
	        message_vision(HBMAG HIY "$N" HIY "高呼一声佛号，运起罗汉伏魔神"
                                "功，全身皮肤一会呈现" NOR + HBMAG HIY"紫金" HIY
                                "色，一会又呈现出一道道" HIY "金光" HIY "。\n"
                                NOR, me); 
           
                             
  /*      else

        if (fam == "少林派")
	        message_vision(HIY "$N" HIY "高呼一声佛号，运起罗汉伏魔神"
                                "功，全身真气澎湃，衣衫随之鼓胀。\n"
                                NOR, me);
*/
        else 
	        message_vision(HIY "$N" HIY "微一凝神，运起罗汉伏魔神功，"
                                "全身肌肤竟交替呈现出" NOR + HIB "靛青" HIY
                                "与" HIR "血红" HIY "两色。\n" NOR, me);

 
        me->add_temp("apply/attack", me->query_skill("luohan-fumogong", 1)/2);
        me->add_temp("apply/damage", me->query_skill("luohan-fumogong", 1)/3);
        me->add_temp("apply/parry", - me->query_skill("luohan-fumogong", 1)/3);
        me->set_temp("luohan_power",1);
        me->set_temp("powerup", 1);
       

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill / 3 :), skill);

        if (me->is_fighting())
                me->start_busy(0);
        return 1;
}
void remove_effect(object me, int skill)
{
	
	 if (objectp(me)) {
                if (me->is_fighting()) {
                        call_out("remove_effect", 1, me, skill);
                        return;
                }

           me->delete_temp("powerup");
	    
           me->add_temp("apply/attack", -me->query_skill("luohan-fumogong", 1)/2);
           me->add_temp("apply/damage", -me->query_skill("luohan-fumogong", 1)/3);
           me->add_temp("apply/parry", me->query_skill("luohan-fumogong", 1)/3);

	    message_vision(HIR"\n$N的罗汉伏魔神功运行完毕，将内力收回丹田。\n"NOR, me);
	    return;

	}
}

string exert_name() { return HIY"伏魔决"NOR; }
int help(object me)
{
        write(HIY"\n「罗汉伏魔」："NOR"\n");
        write(@HELP

        罗汉伏魔神功之伏魔诀，此招术威力非同小可。
        当运用罗汉诀时，可提升自我的攻击力、命中、
        但是降低招架。如果是佛门弟子使用效果更好。

        要求：  罗汉伏魔功等级 100 以上；
                基本内功等级 100 以上；
                set 罗汉伏魔 伏魔
                可在攻击型武功中增加伏魔内伤效果；
                              
                
HELP
        );
        return 1;
}


