//tuoni.c 拖泥带水 
//cre by sohu@xojh 
// 打一招，蓄势，然后连续进攻三招，后又补一招。

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int check_fight(object me,object target);

string *pictures=({
"心惊肉跳","杞人忧天","无中生有","徘徊空谷","力不从心","行尸走肉", "庸人自扰"
});
int perform(object me,object target)
{
        string picture;
        int i;       
        i = me->query_skill("anran-zhang", 1);

        picture = pictures[random(sizeof(pictures))];

        if( !target ) target = offensive_target(me);

        if( !target
         || !me->is_fighting(target) )
               return notify_fail("「拖泥带水」只能在战斗中对对手使用。\n");
        if (me->query("gender")=="无性")
               return notify_fail("你阴阳不全，使不出「黯然销魂意」绝技。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「拖泥带水」绝技！\n");   

        if( me->query_skill_prepared("strike") != "anran-zhang"
         || me->query_skill_mapped("strike") != "anran-zhang"
         || me->query_skill_mapped("parry") != "anran-zhang"
         )
               return notify_fail("你现在难以使用「拖泥带水」绝技！\n"); 

        if((int)me->query_skill("anran-zhang", 1) < 500 )
               return notify_fail("你的黯然拖泥带水掌法火候不够，使不出「拖泥带水」绝技。\n");

        if((int)me->query_skill("strike", 1) < 500 )
               return notify_fail("你的基本功还不够娴熟，使不出「拖泥带水」绝技。\n");

        if((int)me->query_skill("force",1) < 500 )
               return notify_fail("你的内功等级不够，使不出「拖泥带水」绝技。\n");

		if ((int)me->query("divorce")>0)
					return notify_fail("你如此滥情，难以使用发挥出黯然销魂意绝技。\n"); 
        if((int)me->query_str() < 80)
               return notify_fail("你的膂力还不够强劲，使不出「拖泥带水」绝技。\n");

        if((int)me->query_dex() < 30)
                return notify_fail("你的身法还不够迅猛，使不出「拖泥带水」绝技。\n");

      
        if((int)me->query("neili") < 200 )
                return notify_fail("你的内力不够。\n");

        if((int)me->query("jingli") < 100)
                return notify_fail("你的精力不够。\n");
		if(me->query_temp("arz/daishui"))
                return notify_fail("你在使用「拖泥带水」绝技。\n");
		
		if (me->query("divorce"))
					return notify_fail("你如此滥情，难以使用发挥出拖泥带水绝技。\n"); 
		
		if( me->query("eff_qi") < (int)me->query("max_qi"))
              i=(int)me->query_skill("force",1)/2;
		  else i=(int)me->query_skill("force",1)/4;
			  
		//if ((int)me->query("divorce")>1)
		//	i=i/(int)me->query("divorce");
		
		if (me->query("gender")=="女性")
			i=i/3;
		
		me->set_temp("arz/daishui",1);
        message_vision(HIC"\n$N右手云袖飘动，行云流水，轻灵飘逸，混若无物，右袖呈现北方癸水之象。\n"+
                       HIY"然后左掌却重滞之极，便似带着几千斤泥沙一般，呈中央戊土之象。正是一招"HIR"「拖泥带水」，\n"NOR,me,target);
		//阴柔,判断 int
		
		if (random(me->query_skill("force",1)*me->query_int(1))>(target->query_skill("force",1)*me->query_int(1)/3))
		{
				
			message_vision(HIB"$n一不小心为衣袖拂中顿时陷入一股阴柔的潜力之中，周身劲气汹涌，一浪高过一浪。一招"+HIR+picture+NOR,me,target);
			target->add_busy(3+random(2));
			target->apply_condition("no_exert",2);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
					
		}
		//刚猛,判断str
		if (random(me->query_str(1))>(me->query_str(1)/3))
		{
				
			message_vision(RED"$N这套掌法心使臂、臂使掌，全由心意主宰,劲气运转不绝，汹涌澎湃，携千斤巨力，左手顺势一招"+HIG+picture+RED"。\n"NOR,me,target);
			target->receive_damage("qi",1000+random(4000),me);
			target->receive_wound("qi",1000+random(1000),me);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);					
		}
		me->set_temp("arz/sanzhao",3);
		me->add_temp("apply/strike", i);
		me->add_temp("apply/attack", i);
		me->add_temp("apply/damage", i);
		message_vision(HIY"$N退步避开,闪开$n的攻击，随即连出三招，宛如大海狂涛。\n"NOR,me,target);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("arz/sanzhao",-1);
       	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("arz/sanzhao",-1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("arz/sanzhao",-1);

		me->add_temp("apply/strike", -i);
		me->add_temp("apply/attack", -i);
		me->add_temp("apply/damage", -i);
        me->add("jingli", -random(300));
        me->add("neili", -random(600));

        me->start_perform(3,"拖泥带水");
        me->delete_temp("arz/sanzhao");
        me->delete_temp("arz/daishui");

        if (me->is_fighting())
        	call_out("check_fight", 0 , me, target);
        return 1;
}
int check_fight(object me,object target)
{
		if (!target||!me||!me->is_fighting()) return 1;
		
       message_vision(HIC"$N三招踢完，跟着又是一招"HIR"「行尸走肉」"HIC"，踢出一脚。这一脚发出时恍恍惚惚，隐隐约约，若有若无。\n"

						+"这一脚如此突兀，$n那里避得过了,却听得砰的一响，正中$n的胸口。\n"NOR,me,target);
	   target->set_temp("must_be_hit",1);
	   me->add_temp("apply/damage",me->query_skill("anran-zhang",1)/5);
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	   me->add_temp("apply/damage",-me->query_skill("anran-zhang",1)/5);
	   target->delete_temp("mush_be_hit");
	   return 1;

}


string perform_name(){ return HIC"拖泥带水"NOR; }

int help(object me)
{
        write(HIB"\n黯然拖泥带水掌"+HIC"「拖泥带水」"NOR"\n");
        write(@HELP

	杨过自和小龙女在绝情谷断肠崖前分手，心中日夜思念
	期盼小龙女，渐渐形销骨立，了无生趣。他在海潮之中
	苦练，终于悟出了一十七招掌法。他将这套掌法定名为
	黯然杞人忧天掌，取的是江淹「别赋」中那句黯然杞人
	忧天者，唯别而已矣之意。这掌法中逆中有正，正反相
	冲，无一不是妙到巅毫。受伤越重威力越大，实是置死
	地而得后生!
	拖泥带水是双掌成阴阳之态，左掌中央戊己土，厚重凝
	实，右掌北方葵水之象，轻灵变动，是黯然掌的绝技。
	女性威力不及男性的三成。受伤且和你的妻子离婚一次
	的状态则威力倍增，滥情者无法使用。。
	
	perform strike.tuoni

要求：
	基本掌法要求 500 级以上
	黯然掌法要求 500 级以上
	基本内功要求 500 级以上
	当前内力要求 2000 以上
	当前精力要求 1000 以上
	当前臂力要求 80  以上
	当前身法要求 30  以上
	空手且激发掌法和招架为黯然掌
HELP
        );
        return 1;
}
