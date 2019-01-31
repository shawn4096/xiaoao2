// 面无人色,wuse.c 
// cre by sohu@xojh
// 这虽是一招，其实中间变化多端.脸上喜怒哀乐，怪状百出，敌人一见，登时心神难以自制，我喜敌喜，我忧敌忧，终至听命于我
#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;
void check_fight(object me,object target,int time);

int perform(object me, object target)
{
        int lvl;

        lvl = me->query_skill("anran-zhang", 1);

        if( !target ) target = offensive_target(me);

        if( !target 
         || !me->is_fighting(target) )
                return notify_fail("「面无人色」只能在战斗中使用。\n");
        if( me->query("per")< 27 )
                return notify_fail("你长的如此极品，使用「面无人色」只能令人作呕！\n");   

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「面无人色」！\n");   

        if( (int)me->query_skill("anran-zhang", 1) < 350 )
                return notify_fail("你的黯然销魂掌还不够娴熟，使不出「面无人色」绝技。\n");
		if( (int)me->query_skill("strike", 1) < 350 )
                return notify_fail("你的基本掌法还不够娴熟，使不出「面无人色」绝技。\n");

		if( (int)me->query_skill("force", 1) < 350 )
                return notify_fail("你的基本内功还不够娴熟，使不出「面无人色」绝技。\n");

        if ( me->query_skill_mapped("strike") != "anran-zhang"
			|| me->query_skill_mapped("parry") != "anran-zhang"
			|| me->query_skill_prepared("strike") != "anran-zhang"
)
                return notify_fail("你现在无法使用「面无人色」绝技！\n");

      

        if((int)me->query("max_neili") < 5000)
                return notify_fail("你现在最大内力太弱，使不出「面无人色」。\n");      

        if((int)me->query("neili") < 1000)
                return notify_fail("你现在真气太弱，使不出「面无人色」绝技。\n");
		if (me->query("divorce"))
					return notify_fail("你如此滥情，难以使用发挥出「面无人色」绝技。\n"); 
   //     if((int)me->query("eff_qi") >= (int)me->query("max_qi"))
              //  return notify_fail("你现在心情很好，怎么使得出「面无人色」绝技。\n");
		if ((int)me->query("divorce")>0)
					return notify_fail("你如此滥情，难以使用发挥出黯然销魂意绝技。\n"); 
        if( me->query_temp("arz/wuse")) 
                return notify_fail("你现在正在使用「面无人色」绝技。\n"); 

        message_vision(BLU"却见$N使出一招"HIR"「面无人色」"BLU"这虽是一招，其实中间变化多端.脸上喜怒哀乐，怪状百出，\n"
						+"$n一见，登时心神难以自制，$N喜则$n喜，$N忧则$n忧，看起来$n完全听命于$N！ \n\n"NOR,me,target);

        me->set_temp("arz/wuse", 1);
		call_out("check_fight",1,me,target,(int)lvl/20);
   
        me->add("neili", -random(800));
        me->add("jingli", -100);
        if (me->query_skill("anran-zhang",1)<450)
			me->start_perform(2,"面无人色");

        return 1;
}

string perform_name(){ return BLU"面无人色"NOR; }

void check_fight(object me,object target,int time)
{
        int i;
		if (!me) return;
		if (me->query_temp("weapon")
         || me->query_temp("secondary_weapon")
		 || me->query_skill_mapped("strike") != "anran-zhang" 
         || me->query_skill_prepared("strike") != "anran-zhang" ){
			
			me->delete_temp("arz/wuse");
			me->start_perform(4,"面无人色");
            tell_object(me, HIR"\n你使用功夫不对，「面无人色」绝技运行完毕，气回丹田.\n" NOR);
            return;
        }
        if ( !target
			|| time < 1
			|| ! me->is_fighting(target))
		{
           
            me->delete_temp("arz/wuse");
            tell_object(me, BLU"\n你「面无人色」绝技运行完毕，气回丹田.\n" NOR);
            return;
        }
        call_out("check_fight", 1, me, target,time -1);
}


int help(object me)
{
        write(HIB"\n黯然销魂掌之"+BLU"「面无人色」"NOR"\n");
        write(@HELP

	杨过自和小龙女在绝情谷断肠崖前分手，心中日夜思念
	期盼小龙女，渐渐形销骨立，了无生趣。他在海潮之中
	苦练，终于悟出了一十七招掌法。他将这套掌法定名为
	黯然杞人忧天掌，取的是江淹「别赋」中那句黯然杞人
	忧天者，唯别而已矣之意。这掌法中逆中有正，正反相
	冲，无一不是妙到巅毫。受伤越重威力越大，实是置死
	地而得后生!
	面无人色，这虽是一招，其实中间变化多端，脸上喜怒
	哀乐，怪状百出，敌人一见，登时心神难以自制，我喜
	敌喜，我忧敌忧，终至听命于我。此乃无声无影的胜敌
	之法，比之长啸镇慑敌人又高出一筹。滥情者无法使用
	
	perform strike.wuse

要求：
	基本掌法要求 350 级以上
	黯然掌法要求 350 级以上
	基本内功要求 350 级以上
	当前内力要求 5000 以上
	当前精力要求 1000 以上
	先天容貌要求 26  以上
	空手且激发掌法和招架为黯然掌
HELP
        );
        return 1;
}
