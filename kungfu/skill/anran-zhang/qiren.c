// cre by sohu@xojh 杞人忧天
// 比拼对方内力，造成受伤、闭气、打消内力等状况。
// qiren.c 
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me,object target)
{
        int i;       
        i = me->query_skill("anran-zhang", 1);

        if( !target ) target = offensive_target(me);

        if( !target
         || !me->is_fighting(target) )
               return notify_fail("「杞人忧天」只能在战斗中对对手使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「杞人忧天」绝技！\n");   

        if( me->query_skill_prepared("strike") != "anran-zhang"
         || me->query_skill_mapped("strike") != "anran-zhang"
         || me->query_skill_mapped("parry") != "anran-zhang"
         )
               return notify_fail("你现在难以使用「杞人忧天」绝技！\n"); 

        if((int)me->query_skill("anran-zhang", 1) < 300 )
               return notify_fail("你的黯然杞人忧天掌法火候不够，使不出「杞人忧天」绝技。\n");

        if((int)me->query_skill("strike", 1) < 300 )
               return notify_fail("你的基本功还不够娴熟，使不出「杞人忧天」绝技。\n");

        if((int)me->query_skill("force",1) < 300 )
               return notify_fail("你的内功等级不够，使不出「杞人忧天」绝技。\n");

        if (me->query("gender")=="无性")
               return notify_fail("你阴阳不全，使不出「黯然销魂意」绝技。\n");

		if ((int)me->query("divorce")>0)
					return notify_fail("你如此滥情，难以使用发挥出黯然销魂意绝技。\n"); 
        if((int)me->query_str() < 60)
               return notify_fail("你的膂力还不够强劲(60)，使不出「杞人忧天」绝技。\n");

        if((int)me->query_dex() < 30)
                return notify_fail("你的身法还不够迅猛(30)，使不出「杞人忧天」绝技。\n");

       
        if((int)me->query_temp("arz/qiren")) 
                return notify_fail("你现在正在使用「杞人忧天」绝技。\n"); 
		if (me->query("divorce"))
					return notify_fail("你如此滥情，难以使用发挥出拖泥带水绝技。\n");
      /*  if((int)me->query("max_qi") <= (int)me->query("eff_qi"))
                return notify_fail("以你现在的心境难以使用发挥出消魂绝技。\n"); */

        if((int)me->query("neili") < 2000 )
                return notify_fail("你的当前内力不够。\n");

        if((int)me->query("jingli") < 1000)
                return notify_fail("你的当前精力不够。\n");
		
		message_vision(WHT"\n$N用左臂挥平而上，抬头向天，浑若不见，呼的一掌向自己头顶空空拍出，然后手掌斜下，掌力化成弧形，\n"+
                          "四散落下，正是一招「杞人忧天」！这一掌力似穹庐，圆转广被，实是无可躲闪，\n"NOR,me,target);
		me->set_temp("arz/qiren",1);
		if (random(me->query_skill("force",1)*me->query("neili"))>target->query_skill("force",1)*me->query("neili")/2
			|| random(me->query_str())>target->query_str()/2)
		{
			 message_vision(HIG"\n\n$n当下举掌相迎，拍的一下，双掌相交。$n不由得身子一晃，都只为$n过于托大，\n"+
                          "殊不知$n武功虽然决不弱于$N，但一掌对一掌，却远不及$N掌力的厚实雄浑。\n"NOR,me,target);			
			 if (me->query("neili")>target->query("neili"))
			 {
				 message_vision(HIR"\n\n$n正值内力急剧消耗之际，旧力耗尽，新力未生之际，那里还能招架得住，顿时一口鲜血喷出。\n"NOR,me,target);
				 target->receive_damage("qi",me->query("neili")/5,me);				 
				 target->receive_wound("qi",me->query("neili")/20,me);
				 target->add("neili",-(int)target->query("max_neili")/4);
				 target->apply_condition("no_exert",1);
				 target->start_busy(2+random(3));
				 me->add("neili",-(int)me->query("neili")/10);
				 me->add_temp("apply/damage",i/5);
				 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				 me->add_temp("apply/damage",-i/5);
			 }
			 else 
			  {
				 message_vision(HIY"\n\n$n此时内力消耗甚大，为$N掌力所压迫，气息不禁为之一滞，身形顿时受制。\n"NOR,me,target);
				 target->receive_damage("qi",me->query("neili")/10,me);				 
				 target->receive_wound("qi",me->query("neili")/30,me);
				 target->add("neili",-(int)target->query("neili")/6);
				 me->add("neili",-(int)me->query("neili")/2);
			  }
		}
		else 
			message_vision(WHT"$n吐出胸中一口浊气，喝彩道：“好！这难道就是传说中的‘杞人忧天'？\n"NOR,me,target);
       
        me->add("jingli", -i/5);
       
        me->start_perform(3,"杞人忧天");
        me->delete_temp("arz/qiren");
		me->add_busy(1);
        return 1;
}

string perform_name(){ return HIW"杞人忧天"NOR; }
int help(object me)
{
        write(HIB"\n黯然销魂掌"+WHT"「杞人忧天」"NOR"\n");
        write(@HELP

	杨过自和小龙女在绝情谷断肠崖前分手，心中日夜思念
	期盼小龙女，渐渐形销骨立，了无生趣。他在海潮之中
	苦练，终于悟出了一十七招掌法。他将这套掌法定名为
	黯然杞人忧天掌，取的是江淹「别赋」中那句黯然杞人
	忧天者，唯别而已矣之意。这掌法中逆中有正，正反相
	冲，无一不是妙到巅毫。受伤越重威力越大，实是置死
	地而得后生!
	杞人忧天乃是凭借强大的功力以单掌和对方对抗，若对
	方功力不及，或臂力偏低，那么受到这招后，会内力被
	极大损耗，且陷入手忙脚乱状态。滥情者无法使用。


要求：
	基本掌法要求 300 级以上
	黯然掌法要求 300 级以上
	基本内功要求 300 级以上
	当前内力要求 2000 以上
	当前精力要求 1000 以上
	当前臂力要求 60  以上
	当前身法要求 30  以上
	空手且激发掌法和招架为黯然掌
HELP
        );
        return 1;
}
