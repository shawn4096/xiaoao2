// fanliangyi.c 反两仪
// 正招反出
// by sohu
// 通过effect 控制
#include <ansi.h>

inherit F_SSERVER;


int perform(object me, object target)
{
        int lvl;
        object weapon = me->query_temp("weapon");
        lvl =  (int)me->query_skill("fanliangyi-dao", 1);

        if( !target ) target = offensive_target(me);
     
        if( !target || !me->is_fighting(target) )
                return notify_fail("「反两仪决」只能在战斗中对对手使用。\n");

        if (!weapon || weapon->query("skill_type") != "blade"
			|| me->query_skill_mapped("blade") != "fanliangyi-dao")
                return notify_fail("你手里没有刀，无法使用「反两仪决」！\n");             

        if( (int)me->query_skill("fanliangyi-dao",1) < 450 )
                return notify_fail("你的反两仪刀不够娴熟，不能使用「反两仪决」！\n");
      
        if( (int)me->query_skill("blade",1) < 450 )
                return notify_fail("你的基本刀法等级不够，不能使用「反两仪决」！\n");  

        if( (int)me->query_skill("poyu-quan", 1) < 450 )
                return notify_fail("你的破玉拳法等级不够，不能使用「反两仪决」！\n");
      
        if( (int)me->query_skill("hushan-qigong", 1) < 450 )
                return notify_fail("你的华山气功等级不够，不能使用「反两仪决」！\n");


      
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你的当前内力太少了，无法使用出「反两仪决」！\n");   
        if( (int)me->query("jingli") < 1000 )
                return notify_fail("你的当前精力太少了，无法使用出「反两仪决」！\n");                                                                                   
        if (me->query_skill_prepared("cuff") != "poyu-quan"
          || me->query_skill_mapped("cuff") != "poyu-quan")
                return notify_fail("你现在无法使用「反两仪决」进行攻击。\n");
		if (me->query_temp("flyd/flyj"))
                return notify_fail("你正在施展「反两仪决」！\n");   

        message_vision(HIC"\n$N刀法忽变，施展出和先前完全不同的招式套路，真是反两仪刀法中的「反两仪决」刀法威力顿时变得捉摸不定！\n"NOR, me,target);
        me->add("neili", -(300+random(100))); 
        me->add("jingli", -100);      
        me->add_temp("apply/attack", lvl/4);
		me->add_temp("apply/blade", lvl/5);
		me->add_temp("apply/damage", lvl/5);
		me->add_temp("apply/parry", lvl/4);
		me->add_temp("apply/dodge", lvl/4);

		me->set_temp("flyd/flyj",lvl);

		call_out("remove_effect",0,me,(int)lvl/20);
		//me->start_perform(4 , "「反两仪决」");
        return 1;
}

int remove_effect(object me,int count)
{
	int lvl;
	object weapon;
	if (!me) return 0;
	lvl=me->query_temp("flyd/flyj");
	weapon=me->query_temp("weapon");
	if (count<0
		||!me->is_fighting()
		||me->query_skill_mapped("blade")!="fanliangyi-dao"
		||me->query_skill_mapped("parry")!="fanliangyi-dao"
		||!weapon
		||weapon->query("skill_type")!="blade")
	{
        me->add_temp("apply/attack", -lvl/4);
		me->add_temp("apply/blade", -lvl/5);
		me->add_temp("apply/damage", -lvl/5);
		me->add_temp("apply/parry", -lvl/4);
		me->add_temp("apply/dodge", -lvl/4);

		me->delete_temp("flyd/flyj");
		message_vision(HIC"$N引刀入鞘，反两仪决的威力缓缓收功！\n"NOR,me);
		return 1;
	}
	call_out("remove_effect",1,me,count--);

}
string perform_name(){ return HBWHT+HIB"反两仪诀"NOR; }
int help(object me)
{
        write(HIC"\n反两仪刀之「反两仪诀」："NOR"\n");
        write(@HELP
	此套刀法的步法招数与「昆仑派」的「正两仪剑法」一样，
	均从四象八卦中变化而出，都有八八六十四般变化。当初
	华山高矮二长老在光明顶一战，世人方知道这反两仪刀也
	是了不得的绝学。
	反两仪决乃是反两仪刀绝学，施展后会短期内增加刀法威
	力和提高部分防御。

	指令：perform blade.fanliangyi

要求：
	华山气功（紫霞功）的等级 450  以上；
	反两仪刀的等级 450  以上；
	基本刀法的等级 450  以上；
	破玉拳法的等级 450  以上；
	奇门八卦的等级 200  以上
	当前内力的要求 1000  以上；
	当前精力的要求 1000  以上；
	激发刀法为反两仪刀；
	激发招架为反两仪刀；
	激发内功不限；
	手持刀。
HELP
        );
        return 1;
}
