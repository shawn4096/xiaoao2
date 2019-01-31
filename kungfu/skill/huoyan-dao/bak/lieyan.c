//2006年12月24日KinGSo新编辑,添加HELP
// lieyan.c  火焰刀 [烈焰]
// 修改by hongba kingso的理念太流氓，我cut一点威力，降低一点难度
inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>
string perform_name(){ return HBRED HIR "烈焰"NOR; }
int perform(object me, object target)
{
        int damage, p;
        int lieyan;
        string msg;
        
        if( !target ) target = offensive_target(me);

        
        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「烈焰」只能对战斗中的对手使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器！\n");   
        if( (int)me->query_skill("huoyan-dao",1) < 250 )
                return notify_fail("你的掌法修为不足，使不出烈焰。\n");
        if( (int)me->query("neili") < 2000 )
                return notify_fail("你现在内力太弱，不能打出烈焰。\n");
        if( (int)me->query("max_neili") < 4000 )
                return notify_fail("你现在内力修为太弱，不能打出烈焰。\n");

        if( (int)me->query("jiali") < 50 )
                return notify_fail("你现在加力这么弱，怎么使用烈焰。\n");
        if (me->query_skill_prepared("strike") != "huoyan-dao"
            || me->query_skill_mapped("strike") != "huoyan-dao")
                return notify_fail("你现在无法使用烈焰！\n");
                
        
        msg = HBRED HIR "只见$N双手合于胸前，手中抱起一团炙热的真气犹如一团"HIY"燃烧的烈焰"HIR",凝视着$n。\n"
                        "突然，$N双掌平推，将这团高密度的炙热真气朝着$n轰了过去。\n"NOR;
                       
        if (me->query_skill("strike")  > target->query_skill("strike")*3/4)
                   {
                me->start_busy(1);
              //  lieyan = (int)me->query_skill("strike") /60; 这句没明白
              // damage = (int)me->query_skill("strike"); 这个太狠了
                 damage = (int)me->query_skill("strike"); 
                damage += random(me->query("jiali") * 100);
                damage *= 3;
                if(target->query("neili") < me->query("neili")) damage *= 2;
             //   if (damage>8500) damage=7000+random(9000);  这也够狠啊
               if (damage>2500) damage=2500;  
                
                me->add("neili", -1500);
                if (me->query("neili") < 0)
                      me->set("neili",0);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += HBRED HIY "只听见轰隆一声巨响，$n被烈焰气团轰了个正着，震得$n离地飞起,眼耳口鼻全渗出鲜血,神情可怖。\n"NOR;
                if(damage>= target->query("qi",1)) damage= target->query("qi",1)-1;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                target->start_busy(1);
                msg += "( $n"+eff_status_msg(p)+" )\n"; 
                if(me->query_skill("strike")*2 > target->query_skill("strike")*3 /2)
                call_out("perform2", 1, me, target, p, damage); 
                
        }
else {
                me->start_busy(2);
                msg += HIW"$n见这团"HBRED ""HIR"烈焰"NOR""HIW"，来势如此凶猛，硬拼肯定是两败俱亡的结局，于是一个翻跃躲开了这招。\n"NOR;

                      }

        message_vision(msg, me, target);
        me->start_perform(3,"烈焰"); // busy 短一点
        return 1;
}

int perform2(object me, object target)
{  
       string msg, dodge_skill;
       int lev;
       int damage;
       int p;
       lev = me->query_skill("huoyan-dao", 1);
       
       p = (int)target->query("qi")*100/(int)target->query("max_qi");
       damage = (int)me->query_skill("strike"); 
        if( !target || !me || !living(me)
           || !me->is_fighting(target) 
           || environment(target)!=environment(me) || !living(target)
           || (int)me->query("neili") < 500)
                return 0;

       
         message_vision(HBRED HIW "$N趁着$n血气翻腾,新力不济之时,身法突然加速，绕到$n背后空门处，痛下杀手，连击数掌！\n"NOR,me, target);
    
         // 不能加must be hit，连击放这里   
// target->start_busy(1);
                
               
           if (me->query_dex() > target->query_dex())
target->set_temp("must_be_hit",1);

                 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                   if ( me->is_fighting(target) )
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                 if ( me->is_fighting(target) )
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                  if ( me->is_fighting(target) )
		   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                  if ( me->is_fighting(target) )
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

         
         if (random(me->query_skill("strike")*4) > target->query_skill("dodge"))
        
           {

               me->add_temp("apply/strike", lev/4);
                 me->add_temp("apply/attack", lev*10);
                  me->add_temp("apply/damage", lev*5);
                  me->add_temp("apply/strength", lev/4);
                target->delete_temp("must_be_hit",1);

                msg = HBRED HIY "砰砰砰砰’！劲气爆破之声不断响起，$N连续数掌闪电般迅快地拍在$n背上，每一掌均令$n喷出一蓬鲜血。\n"NOR;
               msg += "( $n"+eff_status_msg(p)+" )\n"; 
            // 去掉那个什么内伤的描述
               
                

                me->add("neili", -500);
                me->add("jingli", -200);   
          
               me->add_temp("apply/strength", -lev/4);
                me->add_temp("apply/strike", -lev/4);
                me->add_temp("apply/attack", -lev*10);
                me->add_temp("apply/damage", -lev*5);

                target->start_busy(1);
                target->apply_condition("hyd_condition",8); // 加入火焰刀内伤
                 me->start_busy(2);
                   if (me->query("neili") < 0)
                      me->set("neili",0);
                 
               me->add("neili", -1500);
                me->add("jingli", -200);  
                
         
            } 
        else 
        {
         
                msg = HIY "$n" HIY "见对方留有如此后着，心想如闪避不急，恐难保命。"
                      "于是强提一口真气，如滚地葫芦般，狼狈的躲了开去，但已大伤真元。\n" NOR; 
        
               me->add("neili", -500);
                me->add("jingli", -200);  
                target->add("max_neili", -random(500));                            
                target->start_busy(2);
                target->add("neili", -random(5000));

                 me->start_busy(3);
                if (me->query("neili") < 0)
                      me->set("neili",0);
                if (target->query("neili") < 0)
                      target->set("neili",0);


        }
        message_vision(msg, me, target); 
me->start_perform(5, "「烈焰」");  // busy短一点，原来是8啊

        return 1;
}

int help(object me)
{
	write(HIR"\n雪山秘技「烈焰」："NOR"\n");
	write(@HELP
	火焰刀烈焰绝技，此技能为火焰刀终极奥义。
       据传此招一出，没有人还能站着。
       

	要求：	最大内力 4000 以上；
		内力     2000  以上；
              火焰刀   等级 250 以上；
		
HELP
	);
	return 1;
 }
