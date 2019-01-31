// qiankun.c
// by snowman@SJ 22/06/99

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

void remove_effect(object me);
int perform(object me, object target)
{
      string msg, dodge_skill;                                   
      int ap, dp;
      
      if( !target ) target = offensive_target(me);
     
      if( !objectp(target) || !me->is_fighting(target) || !living(target)
      || environment(target)!=environment(me))
                return notify_fail("「一指乾坤」只能在战斗中对对手使用。\n");
             
      if( target->query("combat_exp") < 80000 )
                return notify_fail("杀鸡焉用牛刀？对"+target->name()+"你没必要使用一指乾坤吧。\n");
      if( me->query_temp("weapon") )
                return notify_fail("你必须空手使用「一指乾坤」！\n");
      
      if( (int)me->query_skill("yizhi-chan",1) < 350 )
                return notify_fail("你的一指禅不够娴熟，不会使用「一指乾坤」！\n");
      
      if( (int)me->query_skill("yijin-jing",1) < 350 )
                return notify_fail("「一指乾坤」需要雄厚的易筋经内功为基础。\n");
                  
      if (me->query_skill_mapped("force") != "yijin-jing")
                return notify_fail("你所使用的内功不对。\n");
                
      if( target->query_condition("yzc_qiankun"))
                return notify_fail("对方已经身中「一指乾坤」，你不用再费力气了。\n");
      
      if( (int)me->query("max_neili") < 3500 )
                return notify_fail("你的内力修为太次，不能使用「一指乾坤」！\n");
      
      if( (int)me->query("neili") < 1500 )
                return notify_fail("你的内力太少了，无法使用出「一指乾坤」！\n");   
            
      if( (int)me->query("jingli") < 500 )
                return notify_fail("你的精力太少了，无法使用出「一指乾坤」！\n");   
                  
      if( (int)me->query_temp("yzc/qiankun"))
                return notify_fail("你刚刚用了一次「一指乾坤」，先调息调息一下吧！\n");   
                                                               
      if (me->query_skill_prepared("finger") != "yizhi-chan"
          || me->query_skill_mapped("finger") != "yizhi-chan")
                return notify_fail("你现在无法使用「一指乾坤」进行攻击。\n");                                                                                 
       
      msg = HIC"\n$N面露微笑，曲指对着$n轻轻一弹，只听嗤的一声一股劲气从$P手指激射而出，窜向$p丹田！\n" NOR;
                                           
      ap = me->query_skill("force") + me->query_skill("finger") + me->query_kar();
      dp = me->query_skill("force") + me->query_skill("dodge") + target->query_kar();   
      ap *= me->query("combat_exp")/1000;
      dp *= target->query("combat_exp")/1000;       
                      
      me->receive_damage("neili", me->query_skill("force") + me->query_skill("finger"));
//     me->start_perform(5,"一指乾坤");
      
      if( random(ap) > dp/3) {
                msg += HIW"结果$n一个不小心，被指劲点在丹田之上，顿时丹气混乱，脸色发白！\n"NOR;
                tell_object(target, "你感觉这指劲在丹田里乱窜，扰得你浑身发软，身不由己！\n");
                target->receive_damage("qi", me->query_skill("yizhi-chan"), me);
				target->add("neili",-me->query_skill("yizhi-chan"));
                target->receive_wound("qi", me->query_skill("yizhi-chan"), me);
				target->set("jiali",0);
				//增加buff,打散内力，且no_exert

                ap = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += damage_msg(me->query_skill("finger"), "内伤");
                msg += "( $n"+eff_status_msg(ap)+" )\n";
                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+me->query_skill("finger")+ WHT"点攻击伤害。\n"NOR); 
if(userp(target)&& target->query("env/damage"))      tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+me->query_skill("finger")+ WHT"点伤害。\n"NOR);
                
                target->apply_condition("yzc_qiankun", 2+me->query_kar()/5);                                                    
                }
      else {
                me->start_busy(2);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                }                    
      if (me->query_skill("nianhua-zhi",1)<450)
      {
		   me->start_perform(5,"一指乾坤");
      } 
	  else  me->start_perform(2,"一指乾坤");
      message_vision(msg, me, target);   
      me->set_temp("yzc/qiankun", 1);
      me->start_call_out( (: call_other, __FILE__, "remove_effect", me:), 15);
      return 1;
}

void remove_effect(object me)
{
        if(!me) return;
        me->delete_temp("yzc/qiankun"); 
}

string perform_name(){ return HIC"一指乾坤"NOR; }
//举起一指的意思是万法归一，千差万别归于平等，所以在天龙竖起的一指上，包摄了气象万千的世界。

int help(object me)
{
        write(HIB"\n一指禅之「一指乾坤」："NOR"\n");
        write(@HELP
		少林内劲一指禅功为少林七十二艺之一，乃众多少林先辈心血的结晶，
		其功法特点是：将全身劲力集于一指，攻敌之身达到“打其表面伤其内，
		击中前心震后心”之目的。这一指乾坤蕴含大千世界，万法归一的意境，
		当功力达到高深境界时，内力劲气，可将对手全身穴道笼罩，一旦被
		点中会随机让对方封招、闭气功效。一指禅功，全凭易筋经深厚的功
		力支撑，功力越强，威力越大。为少林中后期的秘传武功。

        要求：  最大内力 3500 以上；      
                当前内力 1500  以上；  
                一指禅等级 350 以上；
                易筋经等级 350 以上；
                激发指法为一指禅；               
                且手无兵器,450后飞跃，
				缩短后续pfm发出时间；
                               
HELP
        );
        return 1;
}
