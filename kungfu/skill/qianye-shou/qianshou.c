// qianshou 千手如来
// bren

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
void remove_effect(object target, int skill);
void check_fight(object me,object target,int improve);
int perform(object me, object target)
{
        string msg;
        int skill,ap,dp,i;
        skill = (int)me->query_skill("qianye-shou", 1)+(int)me->query_skill("yijin-jing", 1)/2;                

       if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("「千手如来」只能在战斗中对对手使用。\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("使用「千手如来」时双手必须空着！\n");

        if( (int)me->query_skill("qianye-shou", 1) < 350 )
                return notify_fail("你的如来千叶手不够娴熟，不会使用「千手如来」。\n");

        if( (int)me->query_skill("yijin-jing", 1) < 350 )
                return notify_fail("你的易筋经内功等级不够，不能使用「千手如来」。\n");

        if( (int)me->query_dex() < 27 )
                return notify_fail("你的身法不够强，不能使用「千手如来」。\n");

        if (me->query_skill_prepared("hand") != "qianye-shou"
        || me->query_skill_mapped("hand") != "qianye-shou")
                return notify_fail("你现在无法使用「千手如来」进行攻击。\n");
        if( (int)me->query("max_neili") < 3500 )
                return notify_fail("你现在内力太弱，不能使用「千手如来」。\n");
        if( (int)me->query("neili") < 1500 )
                return notify_fail("你现在内力太弱，不能使用「千手如来」。\n");
		if( me->query_temp("fumo"))
				return notify_fail("你正在使用大金刚拳的特殊攻击「金刚伏魔」！\n");

        if( target->query_temp("qianshou")   )
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。！\n");

// 42          me->start_perform(2,"如来千叶手")
        msg = HIY "$N双手合十互击，陡然向外一分，双掌顿时变得轻灵飘逸，灵动异常，正是少林绝技之一「千手如来」\n" NOR;
		msg += HIW "$N掌势一起，一分二，二分四，渐至无穷之势，霎时幻起漫天的掌影。。\n" NOR;
        message_vision(msg, me, target);
		ap=me->query("combat_exp")/10000;
		dp=target->query("combat_exp")/10000;
		i=2;
		if (me->query("quest/sl/qys/pass"))
		{
			message_vision(HBYEL+HIW"$N的千叶手功力已然大乘，双手一分招式更见凌厉！\n"NOR,me);
			i=3;
			skill=skill+me->query_skill("hand",1)/3;
		}
        if (random(ap) > dp/i
			||random(me->query_skill("hand",1))>target->query_skill("parry",1)/i)
		{
          msg = HIR "$n只觉得四周都是$N的身影，不由得慌乱起来。\n" NOR;
          message_vision(msg, me, target);
          target->add_temp("apply/attack", -skill/3);
          target->add_temp("apply/dodge", -skill/3);
          target->add_temp("apply/parry", -skill/3); 
          target->set_temp("qianshou",skill);   
          me->add("neili", -400);
          me->add("jingli",-150);
          me->start_call_out( (: call_other, this_object(), "check_fight",  me, target, skill :), 1);                             
          return 1;
        }
        message_vision(HIC"$N慌乱中镇定心神，仔细看清了$n的身影。\n"NOR,target,me);
        if (me->query_skill("qianye-shou",1)<449)
        {
			me->start_busy(1);
			me->start_perform(2,"「千手如来」");
        } 
		if (me->query_skill_mapped("leg")!="ruying-suixingtui"
			||me->query_skill_prepared("leg")!="ruying-suixingtui")
        {
			me->start_perform(1,"「千手如来」");
        }
        me->add("neili", -100);
        me->add("jingli", -100);
        return 1;
}

void check_fight(object me, object target, int improve) 
{ 
       object weapon;     

       if (!target) return;
       if( !me) {
          remove_effect(target,improve);
       }
       else 
       if(target->query_temp("qianshou") && !me->is_fighting(target))
	   {
          remove_effect(target, improve);
       }
       else if( (target->query_temp("qianshou")) 
        && (!target->is_fighting() 
        || !me->is_fighting() 
        || !living(me) 
        || target->is_ghost() 
        || me->is_ghost() )){
               remove_effect(target, improve);
        }
        else if((target->query_temp("qianshou"))
         && objectp(weapon = me->query_temp("weapon"))){
                remove_effect(target, improve);
        }
        else{
//            target->apply_condition("no_perform",1);
			if (random(10)>6&&me->query("quest/sl/qys/pass")&&objectp(target)&&me->is_fighting())
			{
				message_vision(HIY"$N口诵佛号，难无阿弥陀佛！千叶手又是一分，呈千手观音状，招式陡然加快！\n"NOR,me,target);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_RIPOSTE);

			}
            call_out("check_fight", 1, me, target, improve); 
            return;
        }
}

void remove_effect(object target, int skill)
{
        if (!target) return;
        
		target->add_temp("apply/attack", skill/3);
        target->add_temp("apply/dodge", skill/3);
        target->add_temp("apply/parry", skill/3);
        target->delete_temp("qianshou");
        tell_object(target, HIB"你渐渐适应了这种变化，状态又恢复如常。\n"NOR);
}

string perform_name(){ return HIY"千手如来"NOR; }
int help(object me)
{
        write(HIB"\n如来千叶手之「千手如来」："NOR"\n");
        write(@HELP
	如来千叶手为少林七十二绝技之一，乃是少林一种重要的手法绝技。
	一招既出，不断演化，一分二，二为四，四成八，渐渐至于无穷。但
	人的功力终究是有限的，其要诀在于一个快字。一招既出，还没等对
	方变招，下一招已经发出。遥想当初少林方证大师以此绝技和魔教任
	我行一场拼斗，其招式变化之快，竟然令任我行这个笑傲江湖的大魔
	头不得不以其绝学“古拙掌法”相抗衡。需要注意的是如来千叶手需要
	少林内功支持。
		
	注意：「千手如来」绝技最大的功效是降低对方的攻防。解开千叶手
		谜题后，千手如来招式加快！只有和互备武功组合方可大威力

	指令：perform hand.qianshou

要求：  
	最大内力 3500 以上；      
	当前内力 1500  以上；  
	千叶手等级 350 以上；
	易筋经等级 350 以上；
	激发手法为如来千叶手；
	激发招架为如来千叶手；
	且手无兵器,450后飞跃；
	若佛法大于180，会有特殊效果出现。
	若和如影随形腿互备有特殊功效。
                
HELP
        );
        return 1;
}

