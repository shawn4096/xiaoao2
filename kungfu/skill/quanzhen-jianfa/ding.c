// ding. 定阳针
// Modified by action@SJ
#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

string perform_name() {return HIB"定阳针"NOR;}

int perform(object me, object target)
{        
        object weapon;
        int damage,p,force;
        string msg, *limbs;
        weapon = me->query_temp("weapon");

        if( !target) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("「定阳针」只能在战斗中对对手使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");    

        if( (int)me->query_skill("xiantian-gong",1) < 100 )
                return notify_fail("你的先天功等级不够，不能施展「定阳针」！\n");

        if( (int)me->query_skill("force", 1) < 100 )
                return notify_fail("你的基本内功等级不够，不能施展「定阳针」！\n");
                
        if ((int)me->query_skill("quanzhen-jianfa", 1) < 100)
                return notify_fail("你的全真剑法不够娴熟，不能使用「定阳针」。\n");
                
        if (me->query_skill_mapped("sword") != "quanzhen-jianfa")
                return notify_fail("你没有激发全真剑法，不能使用「定阳针」。\n");

        if( (int)me->query("neili") < 300 )
                return notify_fail("你的真气不足，不能施展「定阳针」！\n");

        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("你的内力不足，不能施展「定阳针」！\n");

        if( (int)me->query("jingli") < 600 )
                return notify_fail("你的精力不足，不能施展「定阳针」！\n");

        //if( target->is_busy()) 
                 //return notify_fail("对方正自顾不暇呢，你不忙施展「定阳针」！\n");

        me->start_perform(3, "「定阳针」");

        force = me->query_skill("force",1) + me->query_skill("xiantian-gong", 1);
        
		message_vision(HIW"$N左手捏着剑诀，右足踏开一招「"HIR"定阳针"HIW"」向上斜刺，"+weapon->query("name")+""HIW"锵然跃出，倏的化作几点星光，射向$n！\n"NOR,me,target);
		message_vision(HIC"这一招神完气足，劲、功、式、力，无不恰到好处，看来平平无奇，但却没半点瑕疵，正是正宗全真剑法。\n"NOR,me,target);
		message_vision(HIY"\n这几道星光宛如几枚银针一般扎向$n的诸身大穴！\n"NOR,me,target);
		if(random(force) > target->query_skill("force",1)
		 ||random(me->query_skill("sword",1))>target->query_skill("dodge",1)/3)
		{
           damage = force+me->query_skill("sword",1)+me->query_skill("quanzhen-jianfa",1);
           damage =2*damage;
		   damage += random(damage);
           if(target->query_skill("force",1) - 50 > force)
             damage = damage/2;
           if(target->query_skill("force",1) > (force)*2)
              damage = random(1000);
           //if((force) > target->query_skill("force",1)*2)
              damage = damage+random(damage);
           
           
		   if (wizardp(me))
           {
			   message_vision("damage="+damage+"\n",me);
           }
		   
		   if (damage>3500) damage=3500+random(100);
		   if (userp(target)&& damage > 2500) damage = 2500;

		   if(damage > 2000)
              message_vision(HIR"\n突然之间，$n胸口一痛，似乎被一枚极细的尖针刺了一下。这一下刺痛\n"+
                                     "突如其来，似有形，实无质，一股剑气突破你的护体神功，直钻入心肺！\n"NOR,me,target);            
           
		   target->receive_damage("qi", damage, me);
		   //target->apply_condition("neishang",3+random(2));
           target->receive_wound("qi", damage/5, me);
          // target->set_temp("last_damage_from", "定阳针刺死")
		   
		   me->add("neili", -damage/10);
           if (me->query("neili")<0) me->set("neili",0);
          
		   limbs = target->query("limbs");
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           tell_room(environment(target), HIR + target->name()+"忽感全身像被针刺了一样，一阵一阵的麻！\n" NOR, ({ target }));  
           msg = damage_msg(damage, "内伤");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           
		   message_vision(msg, me, target);
           
		   if(userp(me) && me->query("env/damage"))
	          tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR);
           
if(userp(target)&& target->query("env/damage"))
	         tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR);
           me->start_busy(1);
           me->add("jingli", -20);
           target->add_busy(1);
		   if (!userp(target) && me->query_temp("xtg/wuqi"))
				target->add_busy(2+random(4));		   
           
        }        
        else {
           me->add("neili", -50);
           me->add("jingli", -5);
           tell_object(me, HIY"可是"+target->query("name")+"看破了你的企图，斜跃避开了攻击。\n"NOR);

		   me->start_busy(2);         
        }
        return 1;
}

int help(object me)
{
        write(HIG"\n全真剑法之"+HIW"「定阳针」："NOR"\n\n");
        write(@HELP
	定阳针是全真剑法的厉害牵制性武技，利用深厚的内力
	凝聚成点，然后通过剑尖发出，刺中对方穴位，即可对
	对方造成一定的内伤，也可以以气打穴，控制对方的行
	动，令对手防不胜防,但需要运使先天功的五气朝元
	
	指令：perform sword.ding

要求：
	当前内力需求 300 以上；
	最大内力需求 1000 以上；
	当前精力需求 600 以上；
	全真剑法等级 100 以上；
	先天功法等级 100 以上；
	基本轻功等级 100 以上；
	激发剑法为全真剑法；
	激发招架为全真剑法或空明拳；
	激发内功为先天功。
	且全真弟子若以先天功激发，威力更甚。
HELP
        );
        return 1;
}
