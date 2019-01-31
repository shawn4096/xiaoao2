// focus.c, 聚力 by darken@SJ
// By Spiderii@ty更新效果
#include <ansi.h>

inherit F_CLEAN_UP;
void remove_effect(object me,int count);
string exert_name(){ return HBBLU"归元聚力"NOR; }

int exert(object me)
{      
       int skill;
       skill = me->query_skill("guiyuan-tunafa",1);
       if( !me->is_fighting() && (int)me->query_skill("guiyuan-tunafa",1)<350 )
                return notify_fail("你只能在战斗中使用「归元聚力」！\n");

        if( (int)me->query_skill("guiyuan-tunafa", 1) < 100 )
                return notify_fail("你的归元吐纳法法修为还不够！\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不够。\n");

        if(me->query_temp("tz/focus"))
                return notify_fail("你已经在使用了。\n");

        message_vision(HBBLU"$N微微一凝神，归元一气劲凝聚于双手，力道似乎增强了不少。\n" NOR, me);
        if (me->query_skill("guiyuan-tunafa",1)<350)
        {
			me->start_busy(1);
        }
        me->add_temp("apply/strength", me->query_skill("guiyuan-tunafa", 1)/15);

		me->add_temp("apply/attack", me->query_skill("guiyuan-tunafa", 1)/10);
		me->add_temp("apply/strike", me->query_skill("guiyuan-tunafa", 1)/10);
        me->add("neili", -400);
        me->set_temp("tz/focus",skill /10);
        call_out("remove_effect", 1, me, skill/10);
        if (me->query_skill("guiyuan-tunafa",1)<350) me->start_exert(1, "「归元聚力」");
        return 1;
}
void remove_effect(object me, int count)
{
       if (!me) return;
       if( count < 1){
		   
           me->add_temp("apply/strength", -(me->query_skill("guiyuan-tunafa", 1)/15));

		   me->add_temp("apply/attack", -(me->query_skill("guiyuan-tunafa", 1)/10));
           me->add_temp("apply/strike", -(me->query_skill("guiyuan-tunafa", 1)/10));
		   message_vision(HIW"$N运功完毕，手上力道渐渐恢复如常。\n"NOR, me);
		   me->delete_temp("tz/focus");
           return;
        }
        call_out("remove_effect", 1 , me ,count -1);
}

int help(object me)
{
        write(HIR"\n归元吐纳法之「归元聚力」："NOR"\n\n");
        write(@HELP 
	铁掌水上漂裘千仞以铁掌掌法和水上漂绝技
	享誉江湖，归元吐纳法为铁掌帮内传承的内
	功心法。因为历代帮主都是精忠报国之辈，
	大都为国事奔波，无暇参悟本门内功，因此
	归元吐纳法一直在江湖名声不显。倘若门下
	弟子机缘巧合得到武林心法，那么铁掌武学
	必将又升上一个新台阶。
        
	yun guiyuan

要求：
	当前内力要求 500 以上；
	最大内力要求 1500 以上；
	当前精力要求 500 以上；
	基本内功等级 100 以上；
	激发内功为归元吐纳法；                              
HELP
        );
        return 1;
}