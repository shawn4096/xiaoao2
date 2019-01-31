// fentian.c 举火焚天
// by hunthu

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int skill, damage,p;
        weapon = me->query_temp("weapon");  
        skill= me->query_skill("ranmu-daofa",1);

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「举火焚天」只能对战斗中的对手使用。\n");        

        if (!weapon || weapon->query("skill_type") != "blade"
                        || me->query_skill_mapped("blade") != "ranmu-daofa")
                return notify_fail("你现在无法使出「举火焚天」之技！\n");

        if (weapon->query("unique"))
                return notify_fail("你手中之刀过于锋利，影响你燃刀绝技施展！\n");

        if((int)me->query_skill("ranmu-daofa", 1) < 300 )
                return notify_fail("你的燃木刀法火候不够，无法「举火焚天」。\n");

        if((int)me->query_skill("blade", 1) < 300 )
                return notify_fail("你的基本刀法还不够娴熟，使不出「举火焚天」绝技。\n");

        if( (int)me->query_skill("yijin-jing", 1) < 300 )
                return notify_fail("你的易筋经修为不够，使不出「举火焚天」绝技。\n");

        //if ((int)me->query_skill("strike",1) < 300)
          //      return notify_fail("你的掌法修为太差，无法使出「举火焚天」绝技。\n");

        if (me->query_skill_mapped("force") != "yijin-jing")
                return notify_fail("没有易筋经作为根基，是无法使出「举火焚天」绝技的！\n"); 
	    
		if (me->query_skill_mapped("parry")!="ranmu-daofa"&&me->query_skill_mapped("parry")!="cibei-dao")
                return notify_fail("你的招架不对，无法使用「燃木诀」绝技。\n");  

        if (me->query_temp("jgq/fumo"))
                return notify_fail("你现在正在使用「金刚伏魔」神功。\n"); 


        if (me->query_temp("rmdf/fentian"))
                return notify_fail("你正在使用「举火焚天」绝技！");

        if (me->query("max_neili") < 5000)
                return notify_fail("你的内力修为不够。\n");

        if (me->query("neili") < 500)
                return notify_fail("你的内力不够。\n");

        if (me->query("jingli") < 200)
                return notify_fail("你的精力不够。\n");

        me->set_temp("rmdf/fentian",1);
        me->start_busy(2);
        me->add("neili", -800);
        me->add("jingli", -200);        
        msg =HIR"\n$N猛然一声大喝，手中的"+weapon->query("name")+HIR"如一道流星腾空而起，一阵筚拨之声，洒下漫天火焰，\n"+
                "刀头指处，一股烈焰熊熊而出。$N聚气于刀身，在间不容发之际，往空虚连劈数刀。\n"NOR;

        if(random(me->query("combat_exp",1)) > target->query("combat_exp",1)/2
         ||((me->query_skill("blade",1))+ me->query_skill("strike",1))/2 > random(target->query_skill("dodge",1)))
		{
          skill= me->query_skill("ranmu-daofa",1)+me->query_skill("blade",1)+me->query_skill("buddhism",1);
          damage= skill*2;
          msg += HIR"\n$n见火焰扑面卷来，不免大惊失色，但躲闪无及，被熊熊大火围在当中。\n"NOR;
          damage = damage+random(damage/2);

          if (damage > 3000) damage = 3000;
          target->receive_damage("qi", damage*4,me);
          target->receive_wound("qi", damage*2,me);
          
		  p = (int)target->query("qi")*100/(int)target->query("max_qi");
          msg += "( $n"+eff_status_msg(p)+" )\n";
          
          
		  me->start_perform((1+random(4)), "举火焚天");
          me->start_busy(2+random(2));
          
          
		  message_vision(msg, me, target);
		  
		  if(userp(me) && me->query("env/damage"))
			  tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR); 
		  
if(userp(target)&& target->query("env/damage"))
			  tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR); 
		  
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
          me->start_perform(2, "举火焚天");
          me->delete_temp("rmdf/fentian");

		  return 1;
        }
        if(random(me->query("combat_exp",1)) > (target->query("combat_exp",1)/3))
		{
          message_vision(HIR"\n$n虽早有防备，但乍见火光耀眼也不禁大吃一惊，急忙跃开规避，也已大是狼狈。\n"NOR,me,target);
          target->start_busy(3+random(2));
        
          me->start_perform(2, "举火焚天");
		 
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		  me->delete_temp("rmdf/fentian");

          return 1;
        }
        msg += HIR"\n$n成竹在胸，长袖拂出，一股劲气扑出，瞬间漫天火光顿时凝聚成一个火柱，倒卷向$N。\n"NOR;
        damage = skill*5;
        me->receive_damage("qi", damage,"举火焚天而");
        me->receive_wound("qi", damage,"举火焚天而");
        p = (int)me->query("qi")*100/(int)me->query("max_qi");
        msg += "( $N"+eff_status_msg(p)+" )\n";
        message_vision(msg, me, target);
		me->start_perform(2, "举火焚天");

        me->delete_temp("rmdf/fentian");
        return 1;
}



string perform_name(){ return HBYEL+HIW"举火焚天"NOR; }

int help(object me)
{
        write(HIY"\n燃木刀法之「举火焚天」："NOR"\n\n");
        write(@HELP
	燃木刀法乃是少林三大终极兵器之一，是刀法的集大成武技
	此招乃是少林七十二绝技中不传之秘，武功练到高深处后，
	凭借深厚内力，可以做到以掌化刀，厉害无比。此门武功由
	少林玄苦大师修习，自玄苦大师圆寂后，此武技无人修成，
	当一代高僧鸠摩智凭借小无相神功演化燃木刀法大战少林寺
	时，使得此门武技名扬天下。
	
	注意：修习手刀绝技需要身兼少林基础刀法修罗刀的杀意和
		慈悲刀的慈悲之意，在杀伐和慈悲的融合中懂得手刀的
		精髓。切记，切记！
	
	指令：perform blade.fentian 

要求：  
	当前内力需求 1000 以上；
	最大内力需求 10000 以上；
	当前精力需求 800 以上；
	燃木刀法等级 300 以上；
	易筋经功等级 300 以上；
	基本刀法等级 300 以上；
	激发刀法为燃木刀法；
	激发招架为燃木刀法或慈悲刀;
	激发内功为易筋经神功；
	且手持木刀。

HELP
        );
        return 1;
}
/**/
