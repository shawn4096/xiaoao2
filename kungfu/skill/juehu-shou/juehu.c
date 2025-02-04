#include <ansi.h>
#include <combat.h>

#define JUEHU "「" HIR "绝户手" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        
        object weapon;
        int ap, dp;
        string wn, msg;
	    int extra;
	    int i,a;
        if (! target) target = offensive_target(me);


        if (! target || ! me->is_fighting(target))
                return notify_fail(JUEHU "只能在战斗中对对手使用。\n");
        if (!me->query("quest/wudang/juehu"))
                return notify_fail("你需要得到俞二侠的指点方能使用此招绝户手绝技。\n");
        if (objectp(me->query_temp("weapon")))
                return notify_fail("你必须空手才能使用绝户手绝技。\n");
        if( (int)me->query_skill("force", 1) < 300 )
                return notify_fail("你的基本内功功力太浅了。\n");
        if( (int)me->query_skill("hand", 1) < 300 )
                return notify_fail("你的基本手法太浅了。\n");
		if( (int)me->query("max_neili", 1) < 3500 )
                return notify_fail("你的功力太浅了。\n");
        if( (int)me->query("neili", 1) < 1500 )
                return notify_fail("你的功力不够施展此项武技。\n");
		if( (int)me->query("max_jingli", 1) < 1500 )
                return notify_fail("你的功力太浅了。\n");
       // if (userp(me) && me->query("shen") < 10000)
         //       return notify_fail(HIC "\n你恶念顿生，刚想施展毒招，可突然想到当初俞莲舟"
             //                      "的一番告诫，不得不中途放弃了攻击。\n" NOR);

        if ((int)me->query_skill("juehu-shou", 1) < 300)
                return notify_fail("你的虎爪绝户手不够娴熟，难以施展绝户手绝技。\n");

        if (me->query_skill_mapped("hand") != "juehu-shou")
                return notify_fail("你没有激发虎爪绝户手，难以施展绝户手绝技。\n");
        if (me->query_skill_prepared("hand") != "juehu-shou")
                return notify_fail("你没有激发虎爪绝户手，难以施展绝户手绝技。\n");
       // if (me->query_skill_mapped("parry") != "juehu-shou")
      //          return notify_fail("你没有准备使用虎爪绝户手，无法使用" JUEHU "。\n");

        if (me->query("neili") < 1500)
                return notify_fail("你现在真气不够，难以施展绝户手绝技。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
	       extra = me->query_skill("juehu-shou",1) / 4;
	       extra += me->query_skill("yinyun-ziqi",1) / 6;
		   a=me->query_skill("juehu-shou",1)/100;
           if (a> 5) a=5;
	       me->add_temp("apply/attack", extra*3/2);	
	       me->add_temp("apply/damage", extra);
           me->add_temp("apply/hand", extra);
		   me->set_temp("wudang/juehu",1);
	       message_vision(HBMAG "$N大喝一声，变掌为爪，双爪化出漫天爪影，如狂风骤雨一般向$n抓去！\n"NOR,me, target);
		   msg = HIR "$N双手化出漫天手影，向$n的要害抓去第一爪！\n"NOR;
		   message_vision(msg,me,target);
		  // if (me->is_fighting()&&objectp(target)
			     COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
	       if (me->is_fighting()&&objectp(target))
			  {
			   message_vision(HIR"$N双手化出漫天手影，向$n的要害抓去第二爪！\n"NOR,me,target);
			   COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			   }
	        if (me->is_fighting()&&objectp(target))
			  {
			   message_vision(HIR"$N双手化出漫天手影，向$n的要害抓去第三爪！\n"NOR,me,target);
			   COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			   }
	       if (me->is_fighting()&&objectp(target)&& a>=4)
			  {
			   message_vision(HIR"$N双手化出漫天手影，向$n的要害抓去第四爪！\n"NOR,me,target);
			   COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			   }

		   if (me->is_fighting()&&objectp(target)&& a>=5)
			  {
			   message_vision(HIR"$N双手化出漫天手影，向$n的要害抓去第五爪！\n"NOR,me,target);
			   COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			   }
	/*		if (me->is_fighting()&&living(target)&& a>=6)
			  {
			   message_vision(HIR"$N双手化出漫天手影，向$n的要害抓去第六爪！\n"NOR,me,target);
			   COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			   }*/
	        me->add_temp("apply/attack", -extra*3/2);
	        me->add_temp("apply/damage", -extra);
	        me->add_temp("apply/hand", -extra);
	        me->delete_temp("wudang/juehu",1);
            me->add("neili", - 50 * a);      
        
          if (random(me->query_skill("hand",1)) > target->query_skill("parry",1) / 2&&me->query_skill("juehu-shou",1)>350) {
                //me->start_busy(2);
                damage = me->query_skill("juehu-shou", 1);
                damage = damage * 3 + random(damage)* 6;
                target->receive_damge("qi",damage,me);
                target->receive_wound("qi",damage/3,me);
				target->receive_wound("jing",damage/8,me);
                msg =  "\n"NOR;
	            msg += RED HIR "结果$p" HIR "一声惨嚎，没能招架住$P"+HIR "凌厉的攻势，被抓得皮肉分离，鲜血飞溅！\n" NOR;

                message_vision(msg,me,target);
               if (random(6)>3 && target->query("gender")=="男性"
			       && damage>5000
                   && me->query_skill("juehu-shou",1)> 350)
                  {
                    message_vision(HIY"\n$n要害处尽然硬生生被$N撕了下来！真是皮肉分离，鲜血飞溅\n" NOR, me,target);
                    //target->set("gender","无性");
					target->apply_condition("no_exert",1);                    
					target->add_busy(3);
					target->apply_condition("jueshu_hurt",1+random(2));
                  }				
                me->add("neili", -400);               
         } else
          {
                me->start_busy(3);
	            me->add("neili", -400);
                if ((int)me->query("shen") > 0)
                	me->add("shen",  -random(100));
                    msg += CYN "可是$p" CYN "看破了$N"
                       CYN "的企图，躲开了这招杀着。\n" NOR;
        }
        message_combatd(msg, me, target);
        me->start_perform(5, "「绝户手」");
        return 1;
}

string perform_name(){ return HIR"绝户"NOR; }

int help(object me)
{
        write(HIC"\n虎爪绝户手之"+HIR"「绝户」"NOR"\n\n");
        write(@HELP
	说明：绝户手乃是武当二侠俞莲舟早期修炼的武技，初创之时为师傅张三丰真人所见到，
	真人为此不断摇头，后来俞莲舟以为自己这招仍然杀伤力不足，就又再次闭关，直到
	创出这一六式连环的绝户手招式。谁知，张真人却为此大为恼怒，批评了俞莲舟，说
	此门武学招招狠毒，专门拿人腰眼，使人断子绝孙，实乃江湖不齿之行径。俞莲舟听
	后甚是惶恐，决定封藏此招。以至于后来众人围攻武当山时，为了挽救武当安危，俞
	二侠又再次将该武技传授给同门师弟。可见其杀伤力的厉害，但因为本武功和武当后
	期大成武功的机理相违背，所以只能是初期中期的武技。机缘巧合之下，当可向俞二
	侠请教。需要注意的是，学了此招，在拜师之前不能大于150级，否则，张真人会很生
	气，取消该技能，后果很严重。
	
	指令;perform hand.juehu

要求：
	当前内力要求 1500 以上；
	最大内力要求 3500 以上；
	当前精力要求 1500 以上；
	绝户手法等级 300 以上；
	基本内功等级 300 以上。
	激发手法为虎爪绝户手；		            

HELP
        );
        return 1;
}
                                                         