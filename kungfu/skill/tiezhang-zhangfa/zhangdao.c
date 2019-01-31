// 掌刀
//cre by sohu@xojh 2014/10
#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        int skill;

        if(!target ) target = offensive_target(me);
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「掌刀」！\n");       
        if((int)me->query("neili") < 1000  ) 
                return notify_fail("你的当前内力不够。\n");
        if((int)me->query_temp("tzzf/zhangdao") ) 
                return notify_fail("你已经在掌刀的运功中。\n");
        if((int)me->query_skill("tiezhang-zhangfa", 1) < 350 )
                return notify_fail("你的铁掌掌法还不够娴熟，使不出「掌刀」来。\n");
        if((int)me->query_skill("force",1) < 350 )
                return notify_fail("你的基本内功等级不够，使不出「掌刀」来。\n");
        if((int)me->query_str() < 60 )
                return notify_fail("你的膂力还不够强劲，使不出「掌刀」来。\n");
        if( (int)me->query_skill("guiyuan-tunafa", 1) < 350 )
                return notify_fail("你的归元土吐纳法等级还不够，使不出「掌刀」绝技。\n");
        if (!me->query("quest/tz/tzzf/zhangdao/pass"))
                return notify_fail("你听说过掌刀绝技，但并未领会其中奥义。\n");
        
		if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
        || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
        || me->query_skill_mapped("parry") != "tiezhang-zhangfa")
                return notify_fail("你现在无法使用「掌刀」！\n");

        skill = me->query_skill("tiezhang-zhangfa",1);
        skill = skill + me->query_skill("strike",1)/2;
        skill = skill / 6;
		
        me->add("neili", -(me->query_skill("strike",1)+100));
        me->add("jingli", -100);
        message_vision(YEL "$N猛喝一声，运劲于手，一双手掌颜色瞬间变的雪白，硬如精铁！\n" NOR, me, target);
        if (me->query("quest/hubo/pass")) {
			skill=skill+me->query_skill("force",1)/8;
			message_vision(HIC"$N将双手互博之意融入到掌刀之中，威力更甚。\n"NOR,me,target);
		}
		me->set_temp("tzzf/zhangdao", skill);
        me->add_temp("apply/attack", skill);
        me->add_temp("apply/damage", skill);
		call_out("remove_effect",1,me,skill/20);

     //   me->start_call_out( (: call_other, this_object(), "remove_effect", me, skill*3/2 :), skill/2);
        if( me->is_fighting() &&me->query_skill("tiezhang-zhangfa",1)<450) me->start_busy(1);
        return 1;

}

void remove_effect(object me, int amount)
{        
        int skill;
		if (!me) return;
	
        skill = me->query_temp("tzzf/zhangdao");
		if (!me->is_fighting()
			||amount<0)
		{
			me->add_temp("apply/attack", -skill);
			me->add_temp("apply/damage", -skill);
			me->delete_temp("tzzf/zhangdao");
			message_vision(YEL "\n$N掌刀运功完毕，双手逐渐恢复了原状。\n" NOR, me);   
			return;
		}
		call_out("remove_effect",1,me,amount--);
     
}
string perform_name(){ return HIC"掌刀"NOR; }

int help(object me)
{
        write(WHT"\n铁掌掌法之"HIC"「掌刀」："NOR"\n");
        write(@HELP
	这是裘千仞铁掌功的十三绝招之一，叫
	作「掌刀」，乃是聚数十年的内功罡气
	于掌，出招制敌时，内功附加在掌锋边
	缘宛如钢铁，这也是铁掌的由来，全凭
	一口真气支撑。运功后会大幅铁掌的攻
	击力和伤害！
	注意：解开双手互博后，此招威力提升
	
	perform strike.zhangdao
        
要求：
	当前内力要求 1000 以上；   
	铁掌掌法等级 350 以上；
	基本内功等级 350 以上；
	有效臂力要求 60  以上；
	激发掌法为铁掌掌法；
	激发招架为铁掌掌法；
	备铁掌掌法且且手无兵器。
HELP
        );
        return 1;
}

