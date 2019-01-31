// huan.c
// by sohu@xojh

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";


int perform(object me, object target)
{
      string msg, dodge_skill;                                   
      int ap, dp,p,d;
      
      if( !target ) target = offensive_target(me);
     
      if( !objectp(target) || !me->is_fighting(target) || !living(target)
      || environment(target)!=environment(me))
                return notify_fail("「幻字诀」只能在战斗中对对手使用。\n");
             
      if( target->query("combat_exp") < 80000 )
                return notify_fail("杀鸡焉用牛刀？对"+target->name()+"你没必要使用幻字诀吧。\n");
      if( me->query_temp("weapon") )
                return notify_fail("你必须空手使用「幻字诀」！\n");
      
      if( (int)me->query_skill("huanyin-zhi",1) < 350 )
                return notify_fail("你的幻阴指不够娴熟，不会使用「幻字诀」！\n");
      
      if( (int)me->query_skill("shenghuo-shengong",1) < 350 )
                return notify_fail("「幻字诀」需要雄厚的易筋经内功为基础。\n");
                  
      if (me->query_skill_mapped("force") != "shenghuo-shengong")
                return notify_fail("你所使用的内功不对。\n");
                
      if( target->query_condition("yzc_qiankun"))
                return notify_fail("对方已经身中「幻字诀」，你不用再费力气了。\n");
      
      if( (int)me->query("max_neili") < 3500 )
                return notify_fail("你的内力修为太次，不能使用「幻字诀」！\n");
      
      if( (int)me->query("neili") < 1500 )
                return notify_fail("你的内力太少了，无法使用出「幻字诀」！\n");   
            
      if( (int)me->query("jingli") < 500 )
                return notify_fail("你的精力太少了，无法使用出「幻字诀」！\n");   
                  
      if( (int)me->query_temp("hyz/huan"))
                return notify_fail("你刚刚用了一次「幻字诀」，先调息调息一下吧！\n");   
      if(target->query_temp("hyz/huan"))
                return notify_fail("对方已经中了你的「幻字诀」！\n");                                                            
      if (me->query_skill_prepared("finger") != "huanyin-zhi"
          || me->query_skill_mapped("finger") != "huanyin-zhi")
                return notify_fail("你现在无法使用「幻字诀」进行攻击。\n");                                                                                 
       
     message_vision(HIB "$N" HIB "深深的吸了一口气，缓缓的刺出一指，举重若轻，挟待一股寒气逼向$n" HIB "。\n" NOR,me,target);
                                         
      ap = me->query_skill("finger",1);
      dp = me->query_skill("dodge",1) ;   
      ap *= me->query("combat_exp")/100000;
      dp *= target->query("combat_exp")/100000;       
      d=ap*(me->query_skill("force",1)-target->query_skill("force",1))/1000;
	  me->set_temp("hyz/huan", 1);
      if( random(ap) > dp/2)
	  {
                message_vision(HIG "$p" HIG "急忙后退，然而这指何等玄妙，正好点中$p" HIG "胸前，$p" HIG "不禁打了一个冷战。\n" NOR,me,target);
                tell_object(target, HIC"你感觉这指劲化作一道阴寒内力附着在你体内，而且会游走在你四肢百骸扰得你浑身发软！\n"NOR);
                target->receive_damage("jingli", d/2, me);
				target->receive_damage("neili", d, me);
                target->receive_wound("qi",d/3, me);
				target->set("jiali",0);
				//增加buff,打散内力，且no_exert
				target->apply_condition("no_exert",3);
				target->apply_condition("no_perform",3);
				target->add_temp("apply/attack",-ap/2);
				target->add_temp("apply/damage",-ap/4);
				target->set_temp("hyz/huan",1);
				call_out("remove_effect",15,target,ap);
              
                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+d+ WHT"点攻击伤害。\n"NOR);
				
if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+d+ WHT"点伤害。\n"NOR);
   
					 /**/
                target->apply_condition("huanyin_poison", 5+random(3));                                                   
                }
     else {
                me->start_busy(2);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
				message_vision(msg, me, target);   

      }                
      if (me->query_skill("huanyin-zhi",1)<450)
      {
		   me->start_perform(2,"幻字诀");
      } 
	  else  me->start_perform(1,"幻字诀");
      me->delete_temp("hyz/huan");

    
      return 1;
}

int remove_effect(object target,int ap)
{
	if (objectp(target)) return 0;
	target->add_temp("apply/attack",ap/2);
	target->add_temp("apply/damage",ap/4);
	target->delete_temp("hyz/huan");
	message_vision(HIC"$N长出一口气，将这股阴寒无比的劲气缓缓化掉。\n"NOR,target);
	return 1;
}
string perform_name(){ return HIM"幻字诀"NOR; }

int help(object me)
{
        write(HIB"\n幻阴指之「幻字诀」："NOR"\n");
        write(@HELP
	幻阴指是成昆独门武功，当初以此技能在明教光明顶一战而差点
	灭了明教的圣火，这幻阴指就是其成名绝技，最大特点是一旦中
	了，则浑身无力，攻击力将会大大受到削弱。

	指令；perform finger.huan

要求：
	最大内力 3500 以上；      
	当前内力 1500  以上；  
	幻阴指等级 350 以上；
	易筋经等级 350 以上；
	激发指法为幻阴指；               
	且手无兵器,450后飞跃，缩短后续pfm发出时间；
                               
HELP
        );
        return 1;
}
