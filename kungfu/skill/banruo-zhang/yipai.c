//banruo-zhang's perform yipai(一拍两散)
//cool 981226

#include <ansi.h>

inherit F_SSERVER;
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";
int next1(object me, object target, int i);
int perform(object me, object target)
{
        int damage, i,lvl;
        mapping pre;
        string *skill, a, b;
        lvl=me->query_skill("banruo-zhang",1)+me->query_skill("yijin-jing",1)/2;
        if( !objectp(target) ) target = offensive_target(me);
        
        if( !target
         || !target->is_character()
         || !me->is_fighting(target) || !living(target) 
         || environment(target)!=environment(me))
                return notify_fail("一拍两散绝招只能对战斗中的对手使用。\n");      

        if((int)me->query_skill("banruo-zhang", 1) < 500 )
                return notify_fail("你的般若掌还不够熟练，不能使用一拍两散绝招对敌！\n");
		if((int)me->query_skill("yijin-jing", 1) < 500 )
			if((int)me->query_skill("hunyuan-yiqi", 1) < 500 )
                return notify_fail("你的易筋经功还不够熟练，不能使用一拍两散绝招对敌！\n");
 
        if((int)me->query_skill("strike", 1) < 500 )
                return notify_fail("你的掌法不够娴熟，使不出般若掌的绝招！\n");
                
        if(objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「一拍两散」！\n");
        
        if (me->query_skill_prepared("strike") != "banruo-zhang"
         || me->query_skill_mapped("strike") != "banruo-zhang"
		 || me->query_skill_mapped("parry") != "banruo-zhang")
                return notify_fail("你必须先将般若掌运用于掌法和招架之中才行。\n");

        if(me->query_skill_mapped("parry") != "banruo-zhang")
                return notify_fail("你必须先将般若掌运用于招架之中才行。\n");
        if((int)me->query("neili") < 5000 )
                return notify_fail("你当前内力修为不足，使不出般若掌的绝招！\n");  
        if((int)me->query("max_neili") < 15000 )
                return notify_fail("你最大内力修为不足，使不出般若掌的绝招！\n");     
        if((int)me->query("jingli") < 5000 )
                return notify_fail("你当前精力修为不足，使不出般若掌的绝招！\n");  
        if( (int)me->query("neili") < (int)me->query("max_neili")*2/3 )
                return notify_fail("你现在内力不足，使不出般若掌的绝招！\n");     

        if( (int)me->query("jingli") < me->query("eff_jingli")/2 )
                return notify_fail("你现在精力不足，使不出般若掌的绝招！\n");   
                
//        me->start_perform(15, "一拍两散");

        message_vision(HIR"\n$N口诵佛号，凝聚全身功力，孤注一掷，汇于双掌之内连续拍出，带动空气隐约有“啪”的一声暗响！\n" NOR, me,target);
 
        pre = me->query_skill_prepare();
        skill = keys(pre);     
        for (i=0; i<sizeof(skill); i++){
                if(skill[i]=="strike") continue; 
                a = skill[i];
                b = pre[skill[i]];
                me->prepare_skill(skill[i]);
        }         
        if ( (int)me->query("combat_exp",1) < (int)target->query("combat_exp",1) )
                damage = me->query("neili")/10;
        else    damage = me->query("neili")/3;
        
		me->set_temp("brz_yipai", 1);
        me->set("jiali", damage);
        
        if(wizardp(me))  tell_object(me, "Jiali = "+damage+"。");

       if(random(me->query_skill("banruo-zhang",1))>target->query_skill("parry",1)/2
		   ||random(me->query("combat_exp"))>target->query("combat_exp")/2 
		   ||(random(me->query_str())>target->query_dex()/2 && me->query_temp("yjj/powerup")))
	   {
                me->add_temp("apply/attack",lvl/2);
				me->add_temp("apply/strike",lvl/3);
				message_vision(HIW"$N第一掌向前虚按，「"HIR"一拍"HIW"」而出，$n为其劲力所压迫，顿觉胸前一阵窒息。\n"NOR,me,target);
				  //if(random(3))
			    target->add_condition("no_exert", 1);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3); 
                me->add_temp("apply/attack", -lvl/2);
				me->add_temp("apply/strike",-lvl/3);
				if (objectp(target)&&me->is_fighting())
					call_out("next1",1,me,target,i);
					//next1(me, target, i);
         }
        else {
			message_vision(HIC"$N神情一凛，意识到这招的威力绝非强抗能解，于是一个懒驴打滚躲过，但浑身已然是见汗。\n"NOR,me,target);
            target->add_busy(3);

		}
        me->prepare_skill(a,b);
        if (me->query("yjj/powerup")!="pass")
        {
			message_vision(RED"$N因功力不纯这一掌耗尽了自己全身的气劲和精力！不由地大口大口喘气！\n"NOR,me);
       		me->set("jingli",100);
			me->set("neili", 100);
			me->delete("jiali");
		}else{
			message_vision(HBRED+HIW"$N易筋经神功流转不息，透出一口浊气，缓缓恢复些许功力！\n"NOR,me);
			me->add("neili",-3000-random(1000));
			me->add("jingli",-2000-random(1000));
		}
        //me->set("qi",10);
//        me->set("eff_qi";10);
//        me->set("jingli",0);
        //me->set("jingli",10);     
       // me->delete("jiali");
        //me->set("jingli", me->query("eff_jingli")/2);
        
        if(!target->is_killing(me->query("id"))) 
                target->kill_ob(me); 
        me->start_busy(3);
		me->start_perform(4,"一拍两散");
        if(!target->is_busy())
                target->start_busy(2); 
        return 1; 
}

int next1(object me, object target, int i)

{
      string msg;
        int damage, ap,dp;
        object weapon;

        if (!me) return 0;

        weapon = me->query_temp("weapon");
        if (weapon || !target || !living(me) || !me->is_fighting(target)) {
                me->delete_temp("brz_yipai");
                return 0;
        }
        msg = HBRED"\n紧跟着$N左脚向前跨越半步，右脚略微外倾，双掌同时向前先后拍出，一股汹涌至极的掌力将$n笼罩在内！\n"NOR;
        ap = me->query("combat_exp", 1) * me->query_con(1)/10000;
        dp = target->query("combat_exp", 1) * target->query_con(1)/10000;
        if((userp(target)&& random(ap + dp) > dp )|| !userp(target)){
                msg += YEL"$n赫然一惊，见$N这两掌招式中蕴含排山倒海般劲力，正是般若掌中极为难练的「"HIR"一拍两散"YEL"」绝技！\n"NOR;
                damage = me->query_skill("banruo-zhang",1)*3;

				damage += me->query_skill("strike")*3;
				
                damage += random(damage);
        if ( damage > 8000 )
				damage = 8000 + (damage-1000) /100;

		if(damage>= target->query("qi",1)) damage= target->query("qi",1)-1;

                target->add("neili",-(800+random(400)));
                target->receive_damage("qi", damage, me);
        if(userp(me) && me->query("env/damage"))
        	tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage+ WHT"点攻击伤害。\n"NOR);
		
        if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage+ WHT"点伤害。\n"NOR);
		
                target->receive_wound("qi", damage/3, me);
                msg += damage_msg(damage, "内伤");
                message_vision(msg, me, target);
                COMBAT_D->report_status(target, random(2));

        me->add_temp("apply/attack", me->query_skill("banruo-zhang") /3);

		me->add_temp("apply/damage", me->query_skill("banruo-zhang") /3);

        //if(random(3))
			//target->add_condition("no_perform", 1);
        //if(random(3))
			//target->add_condition("no_exert", 1);
        if(!userp(target))    target->add_busy(2);
        
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add_temp("apply/attack", -me->query_skill("banruo-zhang") /3);

		me->add_temp("apply/damage", -me->query_skill("banruo-zhang") /3);

                me->add("neili",-200);
                me->add("jingli",-80);
                me->start_perform(3, "「一拍两散」");
        }
        else {
                msg  += CYN"\n$n急忙退后逃避，危急之中躲过这致命一击。\n"NOR;
                message_vision(msg, me, target);
                me->add("neili", -80);
                me->add_busy(random(2));
        }
	    me->delete_temp("brz/yipai");
        return 1;
}



string perform_name(){ return HBRED+HIW"一拍两散"NOR; }

int help(object me)
{
        write(HIB"\n般若掌之「一拍两散」："NOR"\n");
        write(@HELP
	般若掌是少林七十二绝技中高深武技，掌法中的极致
	其一拍两散绝技实是毕生功力之所聚，所谓“ 两散 ”
	是指拍在石上，石屑四“散”、拍在人身，魂飞魄“散”
	这路掌法就只这么一招，只因掌力太过雄浑，临敌时
	用不着使第二招，敌人便已毙命，而这一掌以如此排
	山倒海般的内力为根基，要想变招换式，亦非人力之
	所能。
		
	定位：空手绝杀技能之一，但因为需要强大功力，所
	以内力越高威力越大，同时因为耗尽功力，若对方功
	力太高容易造成对方的反击，胆小者慎用。命中和臂
	力与经验值相关。

	说明：该绝技若解开易筋经，则功力会凝而不散，功
	力和精力并不会见底。
	
	指令：perform strike.yipai

要求：  
	最大内力需求 15000 以上；      
	当前内力需求 5000  以上；  
	般若掌法等级 500 以上；
	易筋经的等级 500 以上；
	基本掌法等级 500 以上；
	激发掌法为般若掌；
	激发招架为般若掌；
	且手无兵器；
	注意：般若掌若运用得当，激发的话，有一定的反击功效。
                
HELP
        );
        return 1;
}
