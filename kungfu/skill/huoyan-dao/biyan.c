// zongheng.c created by sohu@xojh
//根据天龙八部鸠摩智大战天龙寺所得
inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>
#include <combat.h>
string perform_name(){ return HIG"碧烟纵横"NOR; }
//int check_fight(object me);
//int hdy_ran(object me,object target);
int perform2(object me, object target);

int perform(object me, object target)
{
    int i,y,j,c,h,l;          
      
    if( objectp(me->query_temp("weapon")) )
		return notify_fail("「碧烟纵横」只能空手使用。\n");   
  	if( !target ) target = offensive_target(me);
    if( !objectp(target)
	     || !me->is_fighting(target) )
		return notify_fail("「碧烟纵横」只能在战斗中对对手使用。\n");        
	if (!me->query("quest/dls/hyd/pass"))
		return notify_fail("你虽然听说过「碧烟纵横」绝技，但尚未领悟。\n");
	if (me->query_temp("hyd/zongheng"))
		return notify_fail("你正在施展「碧烟纵横」绝技。\n");  
	if((int)me->query_skill("huoyan-dao",1) < 500)
		return notify_fail("你的火焰刀修为不够， 目前不能使用「碧烟纵横」! \n");
  
	if((int)me->query_skill("longxiang-boruo",1) < 500)
		return notify_fail("你的龙象般若功修为不够， 目前不能使用「碧烟纵横」! \n");
		if((int)me->query_skill("force",1) < 500)
		return notify_fail("你的龙象般若功修为不够， 目前不能使用「碧烟纵横」! \n");

	if( me->query_skill_mapped("strike") != "huoyan-dao"
		||me->query_skill_prepared("strike") != "huoyan-dao"
		||me->query_skill_mapped("parry") != "huoyan-dao")
		return notify_fail("你必须使用火焰刀，才能使用「碧烟纵横」的绝技！\n");
	
	if( (int)me->query("max_neili") < 15000 )
		return notify_fail("你的最大内力修为不够！\n");
	if((int)me->query("neili")<1500)
		return notify_fail("你的当前真气不够！\n"); 
	if((int)me->query("jingli")<1000)
		return notify_fail("你的当前精力不够！\n"); 
  
	message_vision(HIC "\n\n只见$N神色肃然，捏起几支檀香扔在空中，随手一掌挥出。劲力弥漫之处，迅捷无伦地攻向$n！\n"
					+"$n定睛观瞧，见那掌风过处，檀香已被点着，却有着先后之分！只见烟气缭绕，聚而不散。\n"
					+"$N忽然$N五指微张，那团烟气一化为六，向四周徐徐散去！正是大轮寺火焰刀绝技「碧烟纵横」！\n\n"NOR,me, target);
    if (me->query("quest/dls/longxiang/pass")&&me->query_temp("xs/longxiang"))
    {
		i = (int)me->query_skill("huoyan-dao", 1)/3+(int)me->query_skill("longxiang-boruo", 1)/3;
    }else i = (int)me->query_skill("huoyan-dao", 1)/3+(int)me->query_skill("longxiang-boruo", 1)/6;
        
        //y = (int)target->query_skill("parry", 1)+(int)me->query_skill("force", 1)/3;
        me->add("neili", -400);
       
        me->set_temp("hyd/zh",i);
		// me->add_temp("apply/parry", i/5);
		me->add_temp("apply/attack", i/2);
        me->add_temp("apply/damage", i/5);
        me->set_temp("hyd/zongheng",6);
    if ( me->is_fighting(target))		
		COMBAT_D->do_attack(me, target, 0, 3);
	if ( me->is_fighting(target))		
		COMBAT_D->do_attack(me, target, 0, 3);
	if ( me->is_fighting(target))		
		COMBAT_D->do_attack(me, target, 0, 3);
	if ( me->is_fighting(target))		
		COMBAT_D->do_attack(me, target, 0, 3);
	if ( me->is_fighting(target))		
		COMBAT_D->do_attack(me, target, 0, 3);
    if ( me->is_fighting(target)){		
		COMBAT_D->do_attack(me, target, 0, 3);  
	}	
		
        me->add("jingli", -random(500));
        me->add("neili",  -random(800));
                
             
	if (objectp(target)
		&& me->is_fighting()
		&& me->query("quest/dls/longxiang/pass")
		&& me->query_temp("xs/longxiang"))
	{
		message_vision(CYN"\n$N龙象般若功流转不息，越战越勇，各种招式踏至纷来，一招「燃字决」信手而出！\n"+
					HBBLU+RED"$N将火焰刀气动念既至的意境施展出来，数股劲力随着碧烟而去，看似缓慢，但却迅捷无比!\n"NOR,me, target);
		remove_call_out("perform2");
		call_out("perform2",1,me,target);
		
	}	   
      
          me->add_temp("apply/attack", -i/2);
          me->add_temp("apply/damage", -i/5);
		//  me->add_temp("apply/parry", -i/5);
		  me->delete_temp("hyd/zongheng");
		  me->delete_temp("hyd/zh");
		  me->start_perform(6,"「碧烟纵横」");
          return 1;
                 
}

int perform2(object me, object target)
{  

		int damage;
		string msg;
		
		if (!me->is_fighting()) return 0;
		if( !target ) target = offensive_target(me);
		
		if (random((int)me->query("neili"))>(int)target->query("neili")/2
			|| random(me->query_skill("strike",1))>target->query_skill("parry",1)/2)
        { 
           message_vision(RED "$N暴喝一声，聚集的真气汹涌而出，带着热浪的真气如排山倒海般冲击$n\n"+
           HIW "$n不停的痛苦挣扎着，但是$N已臻大成的"HIY"龙象般若功"HIW"一阵接着一阵，一个不慎，内息大乱！\n"NOR,me,target);
           damage =  8 * (int)me->query_skill("huoyan-dao", 1);
           damage = damage  + random(damage);
		   //if (damage>6000) damage=6000+(damage-6000)/10;
		   if(userp(me) && me->query("env/damage")) 
	             tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR);
           me->add("neili", -300);
           me->add("jingli",-100);
		    
           target->receive_damage("qi", damage,me);
           target->receive_wound("qi", damage/4,me);
		   target->apply_condition("no_exert",1);
		   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query_temp("xs/longxiang")?3:1);
           
        }
        else if(random(me->query_skill("force",1)) >  target->query_skill("force",1)/3){
                message_vision(RED "$n为$N龙象波若功的强大内功所迫，当即中招，只觉得全身燥热，内息顿时乱冲！\n"NOR,me,target);
                target->receive_damge("qi",damage/4,me);
                target->add("neili", -random(2000));
				target->apply_condition("no_exert",1);
			    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query_temp("xs/longxiang")?3:1);
                target->start_busy(2);
                me->add("neili",-400);
        } 
        else {
                message_vision(HIY "$n内功亦是极为了得，运起全身功力，硬是将此股热气反击回来。\n" NOR,me,target);
                message_vision(HIR "$N只觉得全身燥热，内息乱冲！"NOR,me,target);
                me->receive_damage("qi", damage/4,target);
                me->add("neili",-random(1000));
				me->add_busy(2);
                target->add("neili",-500);
                
        }
		//message_vision(msg,me,target);
		return 1;

}
/*
int check_fight(object me)
{
      int j;
      if ( !me || !me->query_temp("honglian/lianxu")) return;
      if (me->query_temp("weapon")
       || me->query_temp("secondary_weapon")
       || me->query_skill_prepared("strike") !="huoyan-dao"
       &&me->query_temp("honglian/lianxu")){
        me->delete_temp("honglian/lianxu");
        tell_object(me, HIB"「火焰刀气」散尽，你的后续招式无法继续了。\n"NOR);
        return;
      }
      if (!me->is_fighting()&&me->query_temp("honglian/lianxu")) {
        me->delete_temp("honglian/lianxu");
        tell_object(me, HIB"「火焰刀气」散尽，你的后续招式无法继续了。\n"NOR);
        return;
      }
      else {

        call_out("check_fight", 1, me);
      }
}*/

int help(object me)
{
	write(HIR"\n雪山秘技「碧烟纵横」："NOR"\n");
	write(@HELP
	火焰刀碧烟纵横绝技,乃是大轮寺不传之秘，大轮明王鸠摩智
	曾经以此武技在天龙寺中力战六大高手而不败，可见此武功的
	高深莫测。解密后方可使用，乃大轮寺绝世武技。
要求：
	最大内力 15000 以上；
	当前内力 1500  以上；
	当前精力 1000  以上；
	龙象般若功等级 500 以上；
	火  焰  刀等级 500 以上；
	基本内功等级   500 以上；    
HELP
	);
	return 1;
 }


