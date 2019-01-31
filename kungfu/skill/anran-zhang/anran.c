// cre by sohu@xojh 2014
// anran.c 黯然销魂意
// 定位成重要的辅助功能

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string *pictures=({
"心惊肉跳","杞人忧天","无中生有","拖泥带水","徘徊空谷","力不从心","行尸走肉", "庸人自扰"
});
void check_fight(object me,object target,int time);

int perform(object me,object target)
{

		string picture;
        int i,j;       
        i = me->query_skill("anran-zhang", 1);
        if( me->query("eff_qi") > 0)
			j = me->query("max_qi") / me->query("eff_qi");
        else j = 0;
        picture = pictures[random(sizeof(pictures))];

        if( !target ) target = offensive_target(me);
        if( !target
         || !me->is_fighting(target) )
               return notify_fail("「黯然销魂意」只能在战斗中对对手使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「黯然销魂意」绝技！\n");   

        if( me->query_skill_prepared("strike") != "anran-zhang"
         || me->query_skill_mapped("strike") != "anran-zhang"
         || me->query_skill_mapped("parry") != "anran-zhang"
        )
               return notify_fail("你现在难以使用「黯然销魂意」绝技！\n"); 

        if((int)me->query_skill("anran-zhang", 1) < 450 )
               return notify_fail("你的黯然黯然销魂意掌法火候不够，使不出「黯然销魂意」绝技。\n");

        if((int)me->query_skill("strike", 1) < 450 )
               return notify_fail("你的基本功还不够娴熟，使不出「黯然销魂意」绝技。\n");

        if((int)me->query_skill("force",1) < 450 )
               return notify_fail("你的内功等级不够，使不出「黯然销魂意」绝技。\n");
        if (me->query("gender")=="无性")
                    return notify_fail("你阴阳不全，使不出「黯然销魂意」绝技。\n");
 
       if (me->query("gender")!="男性")
                    return notify_fail("你阳气不足，使不出「黯然销魂意」绝技。\n");
        if((int)me->query_str() < 70)
               return notify_fail("你的膂力还不够强劲，使不出「黯然销魂意」绝技。\n");

        if((int)me->query_dex() < 30)
                return notify_fail("你的身法还不够迅猛，使不出「黯然销魂意」绝技。\n");

   
        if((int)me->query_temp("arz/anran")) 
                return notify_fail("你现在正在使用「黯然销魂意」绝技。\n"); 

        if((int)me->query("max_qi") <= (int)me->query("eff_qi"))
                return notify_fail("以你现在的心境难以使用发挥出黯然销魂意绝技。\n"); 
		if (me->query("divorce"))
					return notify_fail("你如此滥情，难以使用发挥出黯然销魂意绝技。\n"); 
		
		if((int)me->query("neili") < 2000 )
                return notify_fail("你的内力不够。\n");

        if((int)me->query("jingli") < 1000)
                return notify_fail("你的精力不够。\n");

        message_vision(HBRED+HIY"\n$N心想今日身陷绝境，不由万念俱灰，凄然之意自心而升，没精打采的拍出一掌"HIG"「"+picture+"」，\n"+
                          HBRED+HIY"但见掌风激荡，恍恍惚惚，隐隐约约！刹时黯然黯然销魂意掌威力顿增，势不可挡。\n"NOR,me,target);

        if (me->query("gender")=="男性")
			i=i/2;
		else i=i/6;

		if (me->is_busy())
		{
			message_vision(HIG"$N反手一招拍向$n肩头,中掌后$n只觉震得胸口剧痛，身子一晃，惊怒交集﹐立即和身扑上。\n"NOR,me,target);
			me->start_busy(-1);
			target->receive_damage("qi",1000+random(3000),me);
		}
        me->add("neili", -random(1500));
        me->add("jingli", -random(600));
		
		me->set_temp("arz/anran", i);

        me->add_temp("apply/attack", i);
        me->add_temp("apply/damage", i/4);
		me->add_temp("apply/strike", i/4);
		if (me->query("marry"))
		{
			message_vision(HIM"$N忆起自己和爱妻"+me->query("name")+"间的悲欢离合，神情萧然，无意中暗合这黯然销魂的意境，威力大增！\n"NOR,me);
			me->add_temp("apply/strength",i/8);
			me->add_temp("apply/damage", i/4);
			me->add_temp("apply/strike", i/4);

		}

		if (me->query_skill("anran-zhang",1)<550)
			me->start_perform(1,"黯然销魂意");
		else if (me->query_skill("anran-zhang",1)<500)
			me->start_perform(2,"黯然销魂意");
		
        call_out("check_fight", 1 , me,target,(int)i/5);
        return 1;
}

void check_fight(object me,object target,int time)
{
        int i;
		if (!me) return;
        time = me->query_skill("anran-zhang",1)/5; 
        i=me->query_temp("arz/anran");
		if (me->query_temp("weapon")
			|| me->query_temp("secondary_weapon")
			|| me->query_skill_mapped("strike") != "anran-zhang"
			|| me->query_skill_prepared("strike") != "anran-zhang" ){
					me->add_temp("apply/attack", -i);
					me->add_temp("apply/damage", -i/4);
					me->add_temp("apply/strike", -i/4); 
					if (me->query("marry"))
					{						
						me->add_temp("apply/strength",-i/8);
						me->add_temp("apply/damage", -i/4);
						me->add_temp("apply/strike", -i/4); 
					}
					me->delete_temp("arz/anran");
					tell_object(me, HIR"\n你使用功夫不对，「黯然销魂意」绝技运行完毕，气回丹田.\n" NOR);
					return;
        }
        if ( !target
         || time < 1
         || !me->is_fighting())
		{
					me->add_temp("apply/attack", -i);
					me->add_temp("apply/damage", -i/4);
					me->add_temp("apply/strike", -i/4); 
					if (me->query("marry"))
					{						
						me->add_temp("apply/strength",-i/8);
						me->add_temp("apply/damage", -i/4);
						me->add_temp("apply/strike", -i/4); 
					}            
					me->delete_temp("arz/anran");
					tell_object(me, HIR"\n你「黯然销魂意」绝技运行完毕，缓缓收功，气回丹田.\n" NOR);
					return;
        }
        call_out("check_fight", 1, me, target,time -1);
}
string perform_name(){ return HBBLU+HIW"黯然销魂意"NOR; }
int help(object me)
{
        write(HIB"\n黯然黯然销魂意掌「"WHT"黯然销魂意"NOR"」：\n");
        write(@HELP
	
	杨过自和小龙女在绝情谷断肠崖前分手，心中日夜思念
	期盼小龙女，渐渐形销骨立，了无生趣。他在海潮之中
	苦练，终于悟出了一十七招掌法。他将这套掌法定名为
	黯然杞人忧天掌，取的是江淹「别赋」中那句黯然杞人
	忧天者，唯别而已矣之意。这掌法中逆中有正，正反相
	冲，无一不是妙到巅毫。受伤越重威力越大，实是置死
	地而得后生!
	
	黯然销魂意，乃是杨过在思念不得的心境下，心灰意冷
	黯然伤神。以至于功夫的最大威力方能发挥出来。黯然
	销魂实乃黯然销魂掌的最高绝技。
	
	注意：受伤后方能使用。不受伤无法使用。受伤害越大
	黯然销魂掌威力越大，550级后大飞。女性威力不及男性
	的三成。

	perform strike.anran

要求：
	基本掌法要求 450 级以上
	黯然掌法要求 450 级以上
	基本内功要求 450 级以上
	当前内力要求 2000 以上
	当前精力要求 1000 以上
	当前臂力要求 70  以上
	当前身法要求 30  以上
	空手且激发掌法和招架为黯然掌
HELP
        );
        return 1;
}
