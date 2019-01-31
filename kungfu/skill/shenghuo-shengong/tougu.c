// tougu.c 透骨针
// by snowman

#include <ansi.h>
//#include <combat.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int exert(object me, object target)
{        
        object weapon;
        int damage,p;
        string msg, *limbs;
        weapon = me->query_temp("weapon");

        if( !target) target = offensive_target(me);
        if( !target || !me->is_fighting(target) || !living(target)
            || environment(target)!=environment(me))
                return notify_fail("透骨针只能在战斗中对对手使用。\n");
        if(!weapon)
                return notify_fail("你必须使用武器来传递透骨针内劲！\n");        
       // if (me->query_temp("shenghuo/tougu"))
         //       return notify_fail("你正在施展透骨针内劲！\n");
		if( (int)me->query_skill("shenghuo-shengong",1) < 200 )
                return notify_fail("你的圣火神功等级不够，不能施展透骨针内劲！\n");
        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("你的基本内功等级不够，不能施展透骨针内劲！\n");
        if( (int)me->query("neili") < 1500 )
                return notify_fail("你的真气不足，不能施展透骨针内劲！\n");
        if( (int)me->query("max_neili") < 3500 )
                return notify_fail("你的内力不足，不能施展透骨针内劲！\n");
        if( (int)me->query("max_jingli") < 2000 )
                return notify_fail("你的精力不足，不能施展透骨针内劲！\n");
        //if( target->is_busy()) 
                //return notify_fail("对方正自顾不暇呢，你不忙施展透骨针内劲！\n");
        me->start_exert(4,"透骨针");         
        message_vision(HIW"$N悄悄运起"+HIB+"透骨针"+HIW+"，将一股极阴寒的内力积贮于一点，从"+weapon->query("name")+HIW"上传出，直刺"+target->name()+HIW"！\n"NOR,me,target);       
        //me->set_temp("shenghuo/tougu",1); 
		if(random(me->query_skill("force",1)) > target->query_skill("force",1)/3){           
           damage = me->query_skill("force",1)+me->query_skill("shenghuo-shengong",1);
           damage = damage*2 + random(damage);
		 
        if(target->query("neili") > me->query("neili")*2)
             damage = random(10);
		if(target->query("neili")< me->query("neili")/2)
             damage =damage+ me->query("neili")-target->query("neili");        
       
        if (me->query("mjqkdny/pass"))
             damage=damage*2;
		if(damage > 3000){
		   damage=3000+(damage-3000)/10;
           tell_object(target,HBRED"\n突然之间，你胸口一痛，似乎被一枚极细的尖针刺了一下。这一下刺痛\n"+
		   "突如其来，似有形，实无质，一股寒气突破你的护体真气，直入心肺，痛彻入骨！\n"NOR);
		}
        else if(damage <= 1000){
              damage = 1000;
              tell_object(target, HIY"\n突然之间，你胸口一痛，似乎被一枚极细的尖针刺了一下。幸好你护体神功遍\n"+
"护全身，这阴劲虽是凝聚如丝发之细，倏钻陡戳，难防难当，却也伤你不得！\n"NOR);
              tell_object(me, HIY"你连运“透骨针”的内劲，但见对方竟是毫不费力的抵挡了下来！\n"NOR);
              }
        else tell_object(target, HIB"\n突然之间，你胸口被尖针刺了一下。刺痛似有形，实无质，一股寒气突破你的\n"+
"护体神功，直侵内脏！阴劲入体，立即消失，但这一刺可当真疼痛入骨！\n"NOR);
           target->receive_damage("qi", damage,me);
          // target->receive_wound("qi", damage/2);
           target->receive_damage("neili", damage); 
		   if (target->query("neili")<0) target->set("neili",1);
		 
           limbs = target->query("limbs");
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           tell_room(environment(target), HIR + target->name()+"突然全身一颤，如同被尖针刺了一下！\n" NOR, ({ target }));  
           msg = damage_msg(damage, "内伤");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           message_vision(msg, me, target);
           if(userp(me) && me->query("env/damage")) 
			   tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+damage+ WHT"点攻击伤害。\n"NOR);
		   
if(userp(target)&& target->query("env/damage"))
			   tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR);
		   me->start_busy(1);
           me->add("neili", -150);
           me->add("jingli", -20);
		   if (me->query("mjqkdny/pass")&&objectp(target))
		   {
			   target->apply_condition("no_exert",1);
			   target->add("max_neili",-1-random(5));
		   }
           target->add_busy(1);
           return 1;
       } else {
          me->add("neili", -50);
          me->add("jingli", -5);
          tell_object(me, HIY"结果透骨针内劲很弱，还没触到"+target->name()+"便已经散了。\n"NOR);
          me->start_busy(1);         
          }
        // me->delete_temp("shenghuo/tougu");  
         
		 return 1;   
}
string exert_name(){ return BLU"「透骨针」"NOR; }

int help(object me)
{
        write(RED"\n圣火神功"+BLU"「透骨针」"NOR"\n");
        write(@HELP
	传自西域霍山老人的绝技透骨针，通过内力激发，聚集
	在兵器上并通过兵器透发，阴损毒辣，令人防不胜防，
	该技能若解开乾坤大挪移秘籍与之融合后，透骨针威力
	倍增，对敌人造成严重伤害。
	另外：解开乾坤大挪移【融合】谜题，将彻底和乾坤大
	挪移融合变异，阴性阴柔的威力放开,起到很重要的辅助
	功效。
	
	指令;exert tougu

要求：
	当前内力 3500 以上；
	最大精力 2000 以上；
	圣火神功等级 200 以上；
	激发内功为圣火神功。        

HELP
        );
        return 1;
}