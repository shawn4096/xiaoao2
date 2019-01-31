//tulong.c 屠龙
// By Spiderii@ty
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
 
string perform_name() {return HIR"倚天屠龙诀"NOR;}

int perform(object me, object target)
{
        object weapon;
        int skill;

        if( !target ) target = offensive_target(me);
	
        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("屠龙诀只能对战斗中的对手使用。\n");
    
         weapon =  me->query_temp("weapon");

		if((int)me->query_skill("yitian-tulong",1) < 250 )
         return notify_fail("你的倚天屠龙功还不够熟练，使不出屠龙诀！\n");
      
      if((int)me->query_skill("literate",1) < 250 )
         return notify_fail("你的读书写字等级不够，使不出屠龙诀！\n");  

      if((int)me->query_skill("sword",1) < 250 )
         return notify_fail("你的基本剑法还不够熟练！\n");

        if( me->query("neili") <= 3000 )
                return notify_fail("你的内力不够使用屠龙诀！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力不够使用屠龙诀！\n");

        if( me->query_temp("yttlg/tulong"))
                return notify_fail("你正在运用屠龙诀！\n");

        if( !me->query_temp("weapon") || (me->query_temp("weapon"))->query("skill_type") != "sword" )
                return notify_fail("你手中无剑怎能使用屠龙诀？！\n");
                
	
        if (me->query_skill_mapped("sword") != "yitian-tulong")
				return notify_fail("你没有激发倚天屠龙功，如何使得出屠龙诀！\n");

		message_vision(HIY "\n$N以手中" + weapon->query("name") + HIY"做笔，在空中写起字来，每一字包含数招，便有数般变化。\n" +
        "但见剑招开合，俊逸处如风飘雪舞，厚重处如虎蹲象步，当真是雄浑刚健，淋漓酣畅。\n" NOR, me, target);

        skill = me->query_skill("yitian-tulong",1);
        if (me->query_skill_mapped("force")=="yinyun-ziqi"
			&& me->query_skill("yinyun-ziqi",1)>350)
			skill += me->query_skill("yinyun-ziqi",1)/5;
        
		me->set_temp("yttlg/tulong",skill);
        me->add_temp("apply/attack", skill/3);
        me->add_temp("apply/damage", skill/5);
        me->add_temp("apply/parry",skill/10);        
        me->add_temp("apply/dodge", skill/10);
       
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
       
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
       
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
       
	   COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);

       me->add("neili", -me->query_skill("force",1));
       me->add("jingli", - 100);
       me->start_perform(5, "屠龙诀");
	   
	   me->add_temp("apply/attack", -skill/3);
       me->add_temp("apply/damage", -skill/5);
       me->add_temp("apply/parry", -skill/10);        
       me->add_temp("apply/dodge",-skill/10);
       me->delete_temp("yttlg/tulong");
       message_vision(HIG "\n$N以剑代笔，二十四个字一遍又一遍的反复施展，良久始罢！\n\n" NOR, me);

       return 1;
}

int help(object me)
{
   write(HIG"\n倚天屠龙功之「"HIW"倚天屠龙诀"HIG"」："NOR"\n");
	write(@HELP   
	起因于“武林至尊，宝刀屠龙。号令天下，莫
	敢不从。倚天不出，谁与争锋。”的故事传说。
	后来当张三丰寿诞之日,武当遭逢遭逢大变,俞
	岱岩为人所伤，遭人荼毒，张三丰神情郁郁，
	情之所至，信手挥洒，将这二十四个字演为一
	套独步武林的特殊武功，后传于武当张翠山
	
	张翠山因江湖号称铁钩银划，在书法造诣极深，
	因此而享誉江湖。倚天屠龙诀，乃是将铁钩银
	划的意境融入武功招式之中，点穴、连击、招
	架都将极为迅猛。

	指令：perform sword.yttl

要求：
	基本剑法为 250 级
	读书写字为 250 级
	倚天屠龙功 250 级
	当前内力   3000 以上，
	当前精力   1000 以上，
	手中持有剑类武器。           
	说明：倚天屠龙功乃是由铁钩银
	划以及书法演变而来。要求绝高
	的书法造诣，领悟之后，不判断
	招架激发。
HELP
	);
	return 1;
}
