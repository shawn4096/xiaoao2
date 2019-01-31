// fuxue.c 拈花指 「拈花拂穴
// by hunthu //99.01.03
#include <ansi.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
		int i=me->query_skill("nianhua-zhi",1)+me->query_skill("sanhua-zhang",1);
		//me->set_temp()
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
           return notify_fail("牵制攻击只能对战斗中的对手使用。\n");
        if(me->query_temp("weapon"))
      		return notify_fail("你必须空手使用「拈花指」！\n");
        if((int)me->query_con() < 25)
           return notify_fail("你根骨不够,不能使用这一绝技!\n");

        if((int)me->query_skill("yijin-jing",1) < 120)
           return notify_fail("你易筋经的功力不够不能使用拈花拂穴!\n");

        if((int)me->query_skill("nianhua-zhi",1) < 120)
           return notify_fail("你的指法修为不够,目前还不能使用拈花拂穴绝技!\n");
        if (me->query_skill_prepared("finger") != "nianhua-zhi"
        || me->query_skill_mapped("finger") != "nianhua-zhi" )
                return notify_fail("你必须用拈花指才能出此奇功。 \n");

        if( me->query_skill_mapped("force") != "yijin-jing" )
                return notify_fail("你的内功不对。\n");

        if((int)me->query("max_neili")<1500)
              return notify_fail("你的内力修为尚欠火候。\n");  
        if(target->query_temp("nhz/fuxue"))
              return notify_fail("不用浪费时间了，对方已经身重拈花指拂穴。\n");  
        if((int)me->query("neili") < 800)
           return notify_fail("你内力现在不够, 不能使用拈花拂穴! \n");

        if( target->is_busy() )
           return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧ⅵ\n");
        
         msg = HIY "$N面露慈祥微笑，手指轻轻弹出，似乎在弹落花朵上的朝露，生怕弹损花瓣一般，\n"+
                  "指力若有若无,轻柔之及。一股阴柔的内力罩住了$n的全身要穴,使$n动弹不得。\n";
        
		// me->start_perform(6,"拂穴");    
         if(random(me->query("combat_exp")) > (int)target->query("combat_exp") / 2 ||random(me->query_skill("finger")) > (int)target->query_skill("parry")/ 2){
           msg +=  HIG"结果$p被$P拂中要穴! \n" NOR;
           target->set_temp("nhz/fuxue",1);
		   target->start_busy( random((int)me->query_skill("nianhua-zhi",1) / 100 + 2));
		   target->receive_damage("qi",random(2*me->query_skill("nianhua-zhi",1)));
           target->receive_damage("jing",random(2*me->query_skill("nianhua-zhi",1)));
		   target->apply_condition("no_exert",1);
		   target->add_temp("apply/attack",-i/2);
		   target->add_temp("apply/dodge",-i/2);
		   target->add_temp("apply/parry",-i/2);

           if (random(me->query_skill("nianhua-zhi",1))>=150)
               target->apply_condition("fx_busy", random(me->query_skill("finger")/20) + 1 + target->query_condition("fx_busy"));
           me->add("neili",-300);
           me->add("jingli",-100);
		   call_out("back", 6, target,i);
        }
        else {
           msg += HIM"可是$p早有警觉，跳了开去，$P一指落空狼狈的招架着。\n" NOR;
           me->add("neili",-100);
           me->add("jingli",-50);
           me->start_busy(random(1)+1);
        }
		if (me->query_skill_mapped("finger")=="nianhua-zhi"
		&&me->query_skill_mapped("strike")=="sanhua-zhang"
		&&me->query_skill_prepared("strike")
		&&me->query_skill_prepared("finger"))
        {
			me->start_perform(2, "「拂穴」");
        }
		else me->start_perform(6, "「拂穴」");
        message_vision(msg, me, target);
        return 1;
}
void back(object target, int i)
{
        if (!target) return;
        target->add_temp("apply/attack", i/2);
        target->add_temp("apply/dodge", i/2);
        target->add_temp("apply/parry", i/2);
		target->delete_temp("nhz/fuxue");
}

int help(object me)
{
        write(HIB"\n拈花指之「拂穴」："NOR"\n");
        write(@HELP
		拈花指源于佛家“佛祖拈花，迦叶一笑”的典故，是少林七十二绝技之一。拈花指为软功外壮，
		属阴柔之劲，专练指头拈劲之一种功夫。练时内外同修阴柔兼阳刚之劲。功成之后，三指拈物，
		无论如何坚实之石，都能应指而碎。伤人于无形之中，是不可多得的防身绝技。若和散花掌相
		配合，此式虽有违佛家宗旨，不过颇受武僧喜爱，修炼者甚多。

		因为是阴柔内劲发出，所以中者往往是在不知不觉中被拂穴，当发觉时，穴道已然被点，伤势
		发作，倘若解开易筋经第四段秘密，那么拈花指的威力可以将对方的全身劲力彻底封闭。
        要求：  最大内力 1500 以上；      
                当前内力 800  以上；  
                拈花指等级 120 以上；
                易筋经等级 120 以上；
				后天根骨 25 以上；
                激发指法为拈花指；
                且手无兵器；
				如果和散花掌配合，一起施展，拈花指的威力将彻底释放。
                
                
HELP
        );
        return 1;
}