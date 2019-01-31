// shengyou.c 无中生有
// cre by sohu@xojh 2014
// 杨过手臂下垂，绝无半点防御姿式，待得周伯通拳招攻到近肉寸许，突然间手足齐动，左掌右袖、双足头锤、连得胸背腰腹尽皆有招式发出，无一不足以伤敌。
//周伯通虽然早防到他必有绝招，却万万料想不到他竟会【全身齐攻】，瞬息之间，【十余招数同时攻到】，说来“无中生有”只是一招，中间实蕴十余招变式后着，饶是周伯通武学深湛，也闹了个手忙脚乱。
#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;
int perform(object me, object target)
{
        int lvl, i;

        lvl = me->query_skill("anran-zhang", 1);

        if( !target ) target = offensive_target(me);

        if( !target 
         || !me->is_fighting(target) )
                return notify_fail("「无中生有」只能在战斗中使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「无中生有」！\n");   
		if (me->query("gender")=="无性")
			return notify_fail("你阴阳不调和，「无中生有」只能在战斗中使用。\n");
        
		if( (int)me->query_skill("anran-zhang", 1) < 200 )
                return notify_fail("你的黯然销魂掌还不够娴熟，使不出「无中生有」绝技。\n");
		if( (int)me->query_skill("strike", 1) < 200 )
                return notify_fail("你的基本掌法还不够娴熟，使不出「无中生有」绝技。\n");
        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("你的基本内功等级还不够，使不出「无中生有」绝技。\n");

        if ( me->query_skill_mapped("strike") != "anran-zhang"
		  || me->query_skill_mapped("parry") != "anran-zhang"
          || me->query_skill_prepared("strike") != "anran-zhang"
)
                return notify_fail("你现在无法使用「无中生有」绝技！\n");

      	if ((int)me->query("divorce")>0)
					return notify_fail("你如此滥情，难以使用发挥出黯然销魂意绝技。\n"); 

        if((int)me->query("max_neili") < 3000 )
                return notify_fail("你现在最大内力太弱，使不出「无中生有」。\n");      

        if((int)me->query("neili") < 1000 )
                return notify_fail("你现在真气太弱，使不出「无中生有」绝技。\n");
		if((int)me->query("jingli") < 500 )
                return notify_fail("你现在真气太弱，使不出「无中生有」绝技。\n");
        if((int)me->query("eff_qi") >= (int)me->query("max_qi"))
                return notify_fail("你现在心情很好，怎么使得出「无中生有」绝技。\n");

        if( me->query_temp("arz/shengyou")) 
                return notify_fail("你现在正在使用「无中生有」绝技。\n"); 
		if (me->query("divorce"))
					return notify_fail("你如此滥情，难以使用发挥出拖泥带水绝技。\n");
        if((int)me->query("qi") == 0 )
			   return notify_fail("你现在无法使用「无中生有」绝技。\n");

        
		me->set_temp("arz/shengyou", 3);
        i = (int)me->query("max_qi") / (int)me->query("eff_qi");

        if( i > 3 ) i = 3;
        if( i < 1 ) i = 1;

        if( i > 1 ){
           me->add_temp("apply/strength",lvl/3);
           me->set_temp("hurt", 1);
        } 
		message_vision(HIR"$N手臂下垂，绝无半点防御姿式，待得$n拳招攻到近肉寸许，突然间手足齐动，左掌右袖、\n"
							+"双足头锤、连得胸背腰腹尽皆有招式发出，无一不足以伤敌。正是一招"HIY"「无中生有」。\n"NOR,me,target);
        me->add_temp("apply/damage", lvl/2);
        me->add_temp("apply/strike", lvl);
		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
     
		me->add_temp("apply/damage", -lvl/2);
        me->add_temp("apply/strike", -lvl);

        if(me->query_temp("hurt")){
            me->add_temp("apply/strength",-lvl/3);
            me->delete_temp("hurt");
        }
        me->add("neili", -random(500));
        me->add("jingli", -random(200));
        me->delete_temp("arz/shengyou");
        me->start_perform(4,"无中生有");
		if (me->is_fighting())
			call_out("shengyou_attack",0,me,target);

		
		//me->start_busy(1+random(2));
        return 1;
}
// 无中生有的10招密集型攻击

int shengyou_attack(object me,object target)
{
	int count,arg,damage;
	string *limbs;
	
	if( !arrayp(limbs = target->query("limbs")) )
		limbs = ({ "上身", "下身", "身上" });
	//加个判断，否则会出错 by renlai
	//limbs = target->query("limbs");
	arg=(int)(me->query_skill("anran-zhang", 1) / 50);
	//if (arg<4) arg=4;
	damage=me->query_skill("anran-zhang",1);
	damage=damage+me->query_skill("force",1)/5;
	message_vision(CYN"\n\n$n虽然早防到$N必有绝招，却万万料想不到$N竟会全身齐攻，瞬息之间，十余招数同时攻到，\n"
					+"说来“无中生有”只是一招，中间实蕴十余招变式后着，饶是$n武学深湛，也闹了个手忙脚乱。\n\n"NOR,me,target);
	
	for(count = 0; count < arg; count++)
	{
	  message_vision(replace_string( HIW+SKILL_D("anran-zhang")->query_action(me, me->query_temp("weapon"))["action"]+NOR,	"$l", limbs[random(sizeof(limbs))]) + "！\n\n", me, target);
	}   	
	target->add_busy(1+random(3));
       
	damage = damage*arg;

	if( arg*(random(me->query("combat_exp"))) > target->query("combat_exp") )
	{
		message_vision(HIR"$n为$N这数十招迅捷的动作的所伤，哇地吐出一口鲜血。\n"NOR,me,target);
	
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		target->receive_damage("jingli", damage/10,me);

		COMBAT_D->report_status(target, 1);
		COMBAT_D->report_status(target, 0);
	}
	
	me->set_temp("arz/shengyou", 3);
	target->set_temp("must_be_hit",1);
    COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
    target->delete_temp("must_be_hit");
	me->delete_temp("arz/shengyou");
	me->start_perform(4,"无中生有");
	me->add_busy(2);
	return 1;
}

string perform_name(){ return HIG"无中生有"NOR; }
int help(object me)
{
         write(HIB"\n黯然销魂掌之「无中生有」："NOR"\n");
        write(@HELP
	杨过自和小龙女在绝情谷断肠崖前分手，心中日夜思念
	期盼小龙女，渐渐形销骨立，了无生趣。他在海潮之中
	苦练，终于悟出了一十七招掌法。他将这套掌法定名为
	黯然杞人忧天掌，取的是江淹「别赋」中那句黯然杞人
	忧天者，唯别而已矣之意。这掌法中逆中有正，正反相
	冲，无一不是妙到巅毫。受伤越重威力越大，实是置死
	地而得后生!
	无中生有是原本不动，待和对方招式发动后，由静变动
	全身无处不动，全部都是击打对象，迅捷无比，令人防
	不胜防。滥情者无法使用。
	
	perform strike.shengyou

要求：
	基本掌法要求 200 级以上
	黯然掌法要求 200 级以上
	基本内功要求 200 级以上
	最大内力要求 3000 以上
	当前内力要求 1000 以上
	当前精力要求 500 以上
	空手且激发掌法和招架为黯然掌
HELP
        );
        return 1;
}
