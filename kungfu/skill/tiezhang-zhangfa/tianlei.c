// tianlei.c 铁掌--天雷气
// rewrite by snowman@SJ 19/12/2000

#include <ansi.h>

inherit F_SSERVER;

#include <combat_msg.h>

string perform_name(){ return HBWHT+HIW"天雷气"NOR; }
int perform(object me, object target)
{
        if( !target ) target = offensive_target(me);

        if( !target 
          || !me->is_fighting(target)
          || !objectp(target)
          || !living(target)
          || environment(target)!= environment(me))
                return notify_fail("天雷气只能对战斗中的对手使用。\n");


        if( me->query_temp("weapon") )
                return notify_fail("你必须空手才能使用天雷气！\n");

        if((int)me->query_skill("guiyuan-tunafa", 1) < 350 )
                return notify_fail("你的天雷气还未练成，不能使用！\n");
               
        if((int)me->query("neili", 1) < 1000 )
                return notify_fail("你现在内力不足，不能使用天雷气！\n");       

        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
        || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
        || me->query_skill_mapped("parry") != "tiezhang-zhangfa")
                return notify_fail("你现在无法使用「天雷气」！\n");                                                                                 

        if( me->query_skill_mapped("force") != "guiyuan-tunafa")
                return notify_fail("你现在的内功用不了「天雷气」！\n");   
               
      //  if(me->query_temp("tzzf/zhangdao"))
              //  return notify_fail("你正在使用掌刀。\n");
		if(me->query_temp("tzzf/tianlei"))
                return notify_fail("你正在使用天雷气绝技。\n");
        if((int)me->query_skill("tiezhang-zhangfa", 1) < 350 )
                return notify_fail("你的铁掌掌法不够娴熟，不能使用天雷气。\n");

        tell_object(me, HIW"\n你深吸了一口气，暗暗施展出铁掌掌法的秘传“天雷气”凝聚到双掌之中,蓄势待发！\n"NOR);
        //me->start_perform(3, "天雷气");
        me->set_temp("tzzf/tianlei",1);
		me->start_call_out( (: call_other, __FILE__, "tianlei_hit", me, 1 :), 1+ random(4) );
        return 1;
}

int tianlei_hit(object me, int flag)
{
        object target, weapon;
        int i, damage;
        string *limbs, msg, dodge_skill;
        
        if( !me||me->is_ghost() ) return 0;
        //昏迷如何处理？
		if (!living(me) )
		{
			write(HIW"你现在是昏迷状态，蓄积的天雷气顿时失效！\n"NOR);
			me->delete_temp("tzzf/tianlei");
			return 1;
		}
        if( !me->is_fighting() ){
                write("天雷气只能在战斗中使用。\n");
				me->delete_temp("tzzf/tianlei");

                return 0;
        }
        i = 5;
        target = offensive_target(me);
        
		if( !target
        || !target->is_character()
        || !me->is_fighting(target)
        || !living(target)
        || environment(target) != environment(me) ){
                write("天雷气只能对战斗中的对手使用。\n");
       			me->delete_temp("tzzf/tianlei");

				return 0;
        }
        
        if( me->query_temp("weapon")
        && !me->query_temp("tzzf") ){
                write("你必须空手才能使用天雷气！\n");
				me->delete_temp("tzzf/tianlei");

                return 0;
        }
        if( (int)me->query("neili", 1) < 600 ){
                write("你现在内力不足，不能使用天雷气！\n"); 
				me->delete_temp("tzzf/tianlei");

                return 0;
        }
        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
        || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
        || me->query_skill_mapped("parry") != "tiezhang-zhangfa"){
                write("你现在无法使用「天雷气」！\n");
				me->delete_temp("tzzf/tianlei");

                return 0;
        }
        
        me->start_perform(3 + random(2), "天雷气");
        dodge_skill = (flag == 1)?"天 …… 雷 …… 气":"天 …… 雷 …… 合 …… 一";
        
        msg = HIY "\n$N忽然仰天大喝一声“"HIW + dodge_skill + HIY"”，一双手掌刹那间变得雪白！掌劲之下，一阵炙热的罡气随掌势狂飙而出，势不可挡！\n"NOR;

        if( me->query_temp("tzzf/zhangdao") ) flag=3;
        
		if( random((int)me->query("combat_exp", 1) * (flag+1) ) < (int)target->query("combat_exp", 1)/3
        || me->query("combat_exp") < target->query("combat_exp")/2 ){
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += "\n" + SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                limbs = target->query("limbs");
                msg = replace_string( msg, "$l", limbs[random(sizeof(limbs))]);
                msg += HIY"$p在危急中避过了这致命一击，已吓得脸色苍白！\n" NOR;
                message_vision(msg, me, target);
                if( !target->is_busy() ) target->start_busy(1);
				//要取消天雷气设置
				me->delete_temp("tzzf/tianlei");
                return 1;
        }
       
        damage = me->query_skill("tiezhang-zhangfa", 1) + me->query_skill("guiyuan-tunafa", 1) + me->query("jiali") * 4;
        damage = damage / 2 + random(damage / 2);
        damage *= 2;
        
		
        if( target->query("neili") < 10 || target->query("qi") <= 100 ) 
                damage = target->query("qi") + 10;
        else {
                if( me->query("neili") > target->query("neili") * 2 )
                        damage *= 2;
                else if( me->query("neili") > target->query("neili") /3*2 )
                        damage += random(damage);
                else if( me->query("neili") > target->query("neili") )
                        damage += random(damage/2);             
                else if( me->query("neili") < target->query("neili") / 2 )
                        damage /= 2;    
                else if( me->query("neili") < target->query("neili") /3*2 )
                        damage -= random(damage/2);
                damage *= flag; // call by other combo pfm...add damage rate;
        }
		
        
        msg += "$n避无可避，这一掌已经印到了前胸！\n";
        if( objectp(weapon = target->query_temp("weapon")) ){
                if( random(me->query_str()) > (int)target->query_str()/3
                && damage > 1000 ) { 
                        msg += HIM"$p只觉得浑身一热，手掌虎口巨痛，手中"+weapon->query("name")+HIM"脱手而出。\n" NOR;
                        weapon->unequip();
                        weapon->move(environment(target));
                }
                else if( target->query_str()/2 > random(me->query_str()) ){
                        msg += "$p眼见情况危激，慌忙把"+weapon->query("name")+"在身前一挡，只听“当”的一声，倒是抵销了一些掌力！\n" NOR;
                        damage -= random(damage/2);
                }
        }
        if( wizardp(me) ) tell_object(me, "Damage = "+damage+"\n");
        
        if( !me->is_busy() ) me->add_busy(1);
        if( !target->is_busy() ) target->add_busy(1);
          target->receive_damage("qi", damage, me);
        if (me->query_temp("tzzf")) target->receive_wound("qi", damage *3/4, me);
        else target->receive_wound("qi", damage /3, me);
          target->receive_wound("qi", damage *3/4, me);
        i = (int)target->query("qi")*100/(int)target->query("max_qi");
        msg += damage_msg(damage, "瘀伤")+"( $n"+eff_status_msg(i)+" )\n"; 
        message_vision(msg, me, target);
        if( flag < 2 )
                me->add("neili", -400);
        me->delete_temp("tzzf/tianlei");
		me->start_perform(3,"天雷气绝技");
        return 1;
}
int help(object me)
{
        write(WHT"\n铁掌掌法「天雷气」："NOR"\n");
        write(@HELP
	这是裘千仞铁掌功的十三绝招之一，叫作「天雷气」，
	乃是聚数十年的内功罡气于掌，出招制敌。是江湖上有
	名的杀招之一！
	
	perform strike.tianlei
	
要求：
	当前内力要求 1000 以上；   
	铁掌掌法等级 350 以上；
	基本内功等级 350 以上；
	有效臂力要求 60  以上；
	激发掌法为铁掌掌法；
	激发招架为铁掌掌法；
	备铁掌掌法且且手无兵器。
HELP
        );
        return 1;
}

