// yinfeng.c 阴风刀
// by snowman
// Modify By River@SJ 增加有9阳后的效果 2000.2.22
// Update By Lsxk@hsbbs 降低10lvl使用要求 2007/6/11
#include <ansi.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string exert_name() {return HIW"阴风刀"NOR;}

int exert(object me, object target)
{        
        object weapon;
        int damage, p, force, lvl;
        string msg;
        weapon = me->query_temp("weapon");

        if( !objectp(target)) target = offensive_target(me);
        if( !target || !me->is_fighting(target) || !living(target)
            || environment(target)!=environment(me))
                return notify_fail("阴风刀只能在战斗中对对手使用。\n");   
       
        if (me->query_skill_mapped("dagger") != "shenghuo-lingfa")
                return notify_fail("你必须先将圣火令法功和圣火神功相互配合。\n");

        if(!weapon)
                return notify_fail("你必须使用令类武器来传递阴风刀内劲！\n");   

        if( weapon->query("skill_type") != "dagger" )
                return notify_fail("你必须使用匕法传递阴风刀内劲！\n");     

        if( (int)me->query_skill("shenghuo-shengong",1) < 350 )
                return notify_fail("你的圣火神功等级不够，不能施展阴风刀内劲！\n");

        if( (int)me->query_skill("shenghuo-lingfa",1) < 350 )
                return notify_fail("你的圣火令法等级不够，不能施展阴风刀内劲！\n");

        if( (int)me->query_skill("force", 1) < 350 )
                return notify_fail("你的基本内功等级不够，不能施展阴风刀内劲！\n");

        if( (int)me->query("neili") < 5000 )
                return notify_fail("你的真气不足，不能施展阴风刀内劲！\n");

        if( (int)me->query("max_neili") < 3500 )
                return notify_fail("你的内力不足，不能施展阴风刀内劲！\n");

        if( (int)me->query("jingli") < 3000 )
                return notify_fail("你的精力不足，不能施展阴风刀内劲！\n");

       // if (me->query_skill("shenghuo-shengong",1)<450)
            me->start_exert(4, "阴风刀");

        force = me->query_skill("force",1) + me->query_skill("shenghuo-shengong", 1);
        lvl = me->query_skill("shenghuo-lingfa", 1) + me->query_skill("dagger", 1);

        tell_object(me, HIW"\n你悄悄使出"BLU"阴风刀"HIW"，运起一股无形无质的阴寒之气，直插"+target->name()+"胸口玉堂要穴！\n"NOR); 

       if( random(me->query("neili"))*(me->query_temp("yinfeng/time")+1) > target->query("neili")/2
          || random(me->query("combat_exp"))*(me->query_temp("yinfeng/time")+1) > target->query("combat_exp")/2){

              me->delete_temp("yinfeng/time");
                damage = force*me->query("jiali")/2;
                damage += random(damage);                
               
            
                if(me->query("neili")> target->query("neili")*2)
                           damage *= 2;
                else
                 if(me->query("neili")> target->query("neili"))
                           damage += random(damage/2);
                else
                 if(me->query("neili") > target->query("neili")*2 + lvl*4)
                           damage /= 2;                
               

                if (damage > 6000) damage = 6000 +(damage - 6000)/100;

                if (damage > 4000){
                           tell_object(target, HIB"\n突然之间，一股无形无质、利如钢刃的阴寒之气直插入你胸口的“玉堂穴”中！\n"+
                                               HIR"你霎时之间闭气窒息，全身动弹不得！\n"NOR);
                           target->start_busy(3+random(2));
                }
                else if(damage <= 50){
                           damage = 50;
                           tell_object(target, HIY"\n突然之间，一股利如钢刃般的阴寒之气直插你胸口的玉堂穴！\n"+
                                                  "幸好你护体神功遍护全身，这股阴风刀虽利，却也伤你不得！\n"NOR);
                           tell_object(me, HIY"你连运阴风刀的内劲，但见对方竟是毫不费力的抵挡了下来！\n"NOR);
                }
                else{
                           tell_object(target, HBBLU+HIC"\n突然之间，一股阴劲如刀、如剑、如匕、如凿，直插入你胸口的“玉堂穴”中！\n"+
                                               HIR"你霎时之间闭气窒息，全身冰冷,动弹不得！\n"NOR);
                           target->receive_wound("qi", damage/2, me);
                           target->start_busy(1+random(2));
						   target->apply_condition("no_exert",1+random(1));
						   if (me->query("mjqkdny/pass"))
					         {
							   target->apply_condition("no_perform",1+random(1));
							   target->add_busy(1+random(2));
							 }
                }
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                target->receive_damage("neili", damage); 
           
                if(userp(me) && me->query("env/damage")) 
					tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+damage+ WHT"点攻击伤害。\n"NOR); 
if(userp(target)&& target->query("env/damage"))      tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR); ;
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                tell_room(environment(target), HIR + target->name()+"突然全身猛地一震，面如金纸，震退了数步，彷佛被什么人在胸口处猛击了一下似的！\n" NOR, ({ target })); 
                msg = damage_msg(damage, "内伤");
                msg += "( $n"+eff_status_msg(p)+" )\n"; 
                message_vision(msg, me, target);          
                target->add_busy(1+random(2));
                if (me->query_skill("shenghuo-shengong",1)<450)
                    me->start_busy(1);
                me->receive_damage("neili", -damage/3);
                me->receive_damage("jingli", 70);
         }         
        else {       
                me->add_temp("yinfeng/time",1);
                if(me->query_temp("yinfeng/time")>4) me->set_temp("yinfeng/time",4);
                me->receive_damage("neili", 100);
                me->receive_damage("jingli", 15);
                tell_object(me, HIY"结果阴风刀内劲还没触到"+target->name()+"的身体便已经散了。\n"NOR);
                me->start_busy(2); 
        }
        return 1;
}
int help(object me)
{
        write(RED"\n圣火神功"+HBBLU+HIC"「阴风刀」"NOR"\n");
        write(@HELP
	该门武功源自波斯，乃教主张无忌从明教三史中所学
	领悟，待张教主将乾坤大挪移高深层次武功融汇贯通
	后，方使得明教这门以内劲激发，通过圣火令攻击对
	手的手段和方法成为明教绝技之一。注意，只能配合
	圣火令法施展本绝技。
	450级大飞，取消busy,450后解开乾坤大挪移【融合】
	谜题，彻底和乾坤大挪移融合变异，阴性阴柔的威力
	放开。
	
	指令；yun yinfeng

要求：
	当前内力需求 5000 以上；
	当前精力需求 3000 以上；
	圣火神功等级 350 以上；
	基本内功等级 350 以上；
	圣火令法等级 350 以上；
	激发内功为圣火神功。

HELP
        );
        return 1;
}