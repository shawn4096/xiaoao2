

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;


int perform(object me, object target)
{
        int lv,lvf, i, hit;
         string weapon, lzg_msg;

        if( !target ) target = offensive_target(me);
        
		if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("凝血神抓「连环神抓诀」只能在战斗中使用。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「连环神抓诀」！\n");   
        if( (int)me->query_skill("ningxue-shenzhua", 1) < 500 )
                return notify_fail("你的凝血神抓还不够娴熟，使不出「连环神抓诀」绝技。\n");
        if (me->query_skill_prepared("claw") != "ningxue-shenzhua"
        || me->query_skill_mapped("claw") != "ningxue-shenzhua")
                return notify_fail("你现在无法使用「连环神抓诀」进行攻击。\n");  
        if( (int)me->query_str() < 60 )
                return notify_fail("你在臂力不足60，无法使用「凝血诀」绝技!\n");

	    if( me->query_skill("force",1)<500 )
		        return notify_fail("你现在的基本内功等级不够，不能使用「连环神抓诀」。\n");
        if( (int)me->query_skill("claw", 1) < 500 )
                return notify_fail("你的基本爪法等级还不够，使不出「连环神抓诀」绝技。\n");
        if( me->query("max_neili") < 15000 )
                return notify_fail("你现在内力太弱，使不出「连环神抓诀」。\n");      
        if( (int)me->query("neili") <1500 )
                return notify_fail("你现在真气太弱，使不出「连环神抓诀」。\n");
      
        
        lv = me->query_skill("ningxue-shenzhua",1);
        hit = (lv/70);
        
		if(hit > 8) hit = 8;
        if(hit <3) hit = 3;
		
		if (target->is_busy())
		{
			message_vision(HIY"$N见$n已经自顾不暇，冷哼一声，凝血劲暗自运于爪中，凝血神抓威力顿时增加不少。\n"NOR,me,target);
			target->add_condition("nxsz_hurt",1);
			lv+=lv/4;
		}
        me->add_temp("apply/attack", lv/4);
		me->add_temp("apply/claw", lv/6);
        me->add_temp("apply/damage", lv/6);
       
		lzg_msg = HIR"\n$N默不作声，脸上一片红晕，暗暗运气于双手，悄然向$n攻出数招，正是凝血神抓绝技「连环神抓诀」:顿时 \n";
/*
        if(hit >= 2)lzg_msg += HIG"「凝字诀」、「定字诀」"NOR;
        if(hit >= 4)lzg_msg += HIY"、「拍字诀」、「擒字诀」"NOR;
        if(hit >= 6)lzg_msg += HIM"、「拿字诀」、「抓字诀」"NOR;
        if(hit >= 8)lzg_msg += HIC"、「明字诀」、「控字诀」"NOR;
 */       
        lzg_msg += "，\n"+chinese_number(hit)+"式连环，漫天抓影，向$n疾攻而至！\n"NOR;

        message_vision(lzg_msg, me, target);
        
		me->set_temp("lzg_times",hit);
        //me->set_temp("nxsz/shenzhua",0);
        
		me->set_temp("action_flag", member_array("claw", keys(me->query_skill_prepare())));
        //me->set_temp("baocan",hit);
		
		if (hit>7)
		{
			   
                COMBAT_D->do_attack(me, target, weapon, 3);
				COMBAT_D->do_attack(me, target, weapon, 3);
				COMBAT_D->do_attack(me, target, weapon, 3);
				COMBAT_D->do_attack(me, target, weapon, 3);
				COMBAT_D->do_attack(me, target, weapon, 3);
				COMBAT_D->do_attack(me, target, weapon, 3);
				COMBAT_D->do_attack(me, target, weapon, 3);
				COMBAT_D->do_attack(me, target, weapon, 3);
				 me->set_temp("nxsz/shenzhua",8);
		}
			
		else{
        for( i=0; i < hit; i++ )
        {
                
				me->add_temp("nxsz/shenzhua", 1);
                COMBAT_D->do_attack(me, target, weapon, 3);
        }
		}


       message_vision(HIR"\n这"+chinese_number(hit)+"式连环绵绵不绝，"+chinese_number(hit)+"个变化融合为一，快捷无比！\n"NOR, me);

        me->add("neili", -hit*50+20);
        me->add("jing", -hit*50);
        me->add_temp("apply/attack", -lv/4);
        me->add_temp("apply/damage", -lv/6);
		me->add_temp("apply/claw", -lv/6);
       // me->add_temp("apply/parry", lv/5);
	    me->start_perform(6,"「连环神抓诀」");
        me->start_busy(1+random(2));
        me->delete_temp("nxsz/shenzhua");
        
        return 1;
}

string perform_name(){ return HBRED+HIY"连环神抓诀"NOR; }

int help(object me)
{
   write(WHT"\n凝血神爪「"HBRED+HIY"连环神抓诀"WHT"」："NOR"\n");
   write(@HELP
	「凝血神爪」是天地会总舵主陈近南最得意的成名武艺。传言中，
	凡中此神爪之人，三天后全身血液会慢慢凝结变成浆糊一般，无药
	可治。连环神抓诀是在瞬间连出数招，招招抓向对方要害。是凝血
	神抓的终极绝技。
	
	指令：perform claw.shenzhua

要求：
	当前内力 1500 以上；
	最大内力 15000 以上； 
	后天臂力 60 以上； 
	凝血神爪等级 500 以上；
	基本爪法等级 500 以上；
	基本内功等级 500 以上；
	激发爪法为凝血神爪；
	激发招架为凝血神爪；
	备爪法且手无兵器。

HELP
   );
   return 1;
}
