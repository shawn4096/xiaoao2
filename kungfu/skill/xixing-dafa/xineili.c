// xineili.c for xixin-dafa

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;


int exert(object me, object target)
{
        int sp, dp;
        int skill=me->query_skill("xixing-dafa",1);
        if( !target ) target = offensive_target(me);
     
        if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("吸星大法【吸功诀】只能对战斗中的对手使用。\n");

        if (me->query_skill_mapped("force") != "xixing-dafa" )
             return notify_fail("你所使用的特殊内功不对，无法实现【吸功诀】。\n");  
		
		if( !objectp(target) || target->query("id") == "mu ren" )
                return notify_fail("你要吸取谁的内力？\n");
        if ( me->query("quest/xxdf/pass")<2 )
                return notify_fail("你听说过吸星大法有这功能，但你却未得任我行的传授，不会使用！\n");
        if ( me->query_temp("xixing/suckneili") )
                return notify_fail("你正在吸取内力！\n");
      
        if( (int)me->query_skill("xixing-dafa",1) < 400 )
                return notify_fail("你的吸星大法功力不够，不能吸取对方的内力！\n");

        if( (int)me->query("neili",1) < 5000 )
                return notify_fail("你的内力不够，不能使用吸星大法。\n");

        if( (int)target->query("max_neili") <= 0 )
                return notify_fail( target->name() +"没有任何内力！\n");
        if( (int)target->query("neili") < (int)target->query("max_neili") / 10)
                return notify_fail( target->name() +
                        "已经内力涣散，你已经无法从他体内吸取任何内力了！\n");

        message_vision(
                HIR "$N脸色一变，右掌突然伸出，猛地对准$n的膻中大穴按了上去！\n\n" NOR,
                me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

        sp =( me->query_skill("force",1) + me->query_skill("dodge",1))*me->query("str")/100;
        dp = (target->query_skill("force",1) + target->query_skill("parry",1) )*me->query("con")/100;
        //设定标记
        me->set_temp("xixing/suckneili", 1);              

        if( random(sp+dp) > dp )
        {
                tell_object(target, HIR "你顿觉膻中微痛，如同被尖针刺了个小孔，全身内力如水银般循孔飞泄而出！\n "+HIY"你心中大吃一惊！竟然吓得呆立当场。" NOR);
                tell_object(me, HIG "你觉得" + target->name() + "的内力自劳宫穴源源不绝地流了进来。\n" NOR);

                target->add("neili", -2*skill );
                me->add("neili", skill);
                me->add_busy(2+random(1));
                target->add_busy(2+random(1));
				target->apply_condition("no_exert",2);
                me->add("neili", -100);
                call_out("del_sucked", 1, me,target);
        }
        else
        {       
                message_vision(HIY "可是$p看破了$P的企图，机灵地闪了开去。\n" NOR, me, target);
                me->start_busy(2+random(1));
                call_out("del_sucked", 2, me,target);
        }
     
        return 1;
}

void del_sucked(object me,object target)
{
       int sp,dp,skill;
		sp =(int)((me->query_skill("force",1) + me->query_skill("dodge",1))*me->query("str")/100);
        dp = (int)(1+(target->query_skill("force",1) + target->query_skill("parry",1))*(target->query("con")+1)/100);
		skill=me->query_skill("xixing-dafa",1)+me->query_skill("force",1);
	   if( random(sp+dp) > dp && me->is_fighting(target))
       {
               tell_object(target, HIR "你猛觉额角两侧如针刺般剧痛，显然受到对方吸星大法的影响。\n" NOR);
               tell_object(me, HIG "你觉得" + target->name() + "的内力自你的手掌源源不绝地流了进来。\n" NOR);

               target->add("neili",-skill*3);
               me->add("neili",skill);            
               if (!random(3)) target->add("max_neili",-random(10));
               
               me->start_busy(1+random(2));
               target->start_busy(2+random(3));
			   target->kill_ob(me); 
               me->add("neili", -100);
			   //remove_call_out("del_sucked");
               call_out("del_sucked", 1, me,target);
        }
		else {
          message_vision(HIC "$n轻轻向旁边一闪身，终于躲开了$N的吸星大法的影响。\n" NOR,me,target);
          target->kill_ob(me);  
		  //if ( me->query_temp("xixing/suckneili") )
          me->delete_temp("xixing/suckneili");
		  me->add_busy(2);
		  return;
		}

}
string exert_name(){ return HIG"「吸功诀」"NOR; }
int help(object me)
{
        write(HIR"\n吸星大法"+HIG"「吸功诀」"NOR"\n");
        write(@HELP
		吸星大法乃是日月神教前教主任我行的秘传武技，想当初日月神教有两大神技，
		其一为葵花宝典，其二为吸星大法，前人教主任我行在位时选择修习吸星大法。
		固然有其陷害东方不败的嫌疑，但吸星大法的诡异和强横也是他选择的主要原因
		以至于，江湖中为之谈虎色变。后来任我行在少林一战，以吸星大法重出江湖
		可见其威力无铸。
		金庸老先生在重新修订的笑傲江湖中将吸星大法归因于北冥神功，所以在本站
		的吸星大法中，更加强调吸星的特点。本站吸星大法总共分为二段来解。		
		吸功诀，主要是吸取对方的内力，非功力高深者不得施展。
		要求：
			基本内功等级 400 以上；
			吸星大法等级 400 以上；
			当前内力     5000 以上。

HELP
        );
        return 1;
}
