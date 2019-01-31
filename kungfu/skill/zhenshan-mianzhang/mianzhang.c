// mianzhang.c 武当绵掌
// By sohu#xojh

#include <ansi.h>

inherit F_SSERVER;
//int check_fight(object me);
int perform(object me, object target)
{
        int i,j,p,k,z,damage;
        if( !target ) target = offensive_target(me);
        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("绵掌劲力只能在战斗中使用。\n");       
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("先放下手中的武器再说吧！\n");
       // if( me->query_temp("mz_mian"))        
               //return notify_fail("对方已经身中你的绵掌劲力！\n");
        if((int)me->query_skill("strike", 1) < 250 )
                return notify_fail("你的基本掌法太低，无法使用绵掌之劲力。\n");  
        if((int)me->query_skill("zhenshan-mianzhang", 1) < 250 )
                return notify_fail("你的绵掌还不够娴熟，不能使出绵掌之劲力。\n");
        if (me->query_skill_prepared("strike") != "zhenshan-mianzhang"
           || me->query_skill_mapped("strike") != "zhenshan-mianzhang")
                return notify_fail("你不使用绵掌，又岂能使得绵掌之劲力？！\n");   
        if( (int)me->query("max_neili") < 3000 )
                return notify_fail("你内力修为太浅，无法运劲伤敌！\n");                
        if( (int)me->query("neili") < 1500 )
                return notify_fail("你现在真气不够，不能发出绵掌之劲力。\n");
       
        if( userp(me) && (int)me->query_skill("yinyun-ziqi", 1) < 250 )
                return notify_fail("你的氤氲紫气等级不够，不能应用绵掌之劲力。\n");
        if(userp(me) && (int)me->query_skill("taoism", 1) < 150 )
                return notify_fail("练拳先修心，你对道学心法的领悟不够，是不能领悟绵掌之劲力的。\n");
        if(userp(me) && me->query_skill_mapped("force") != "yinyun-ziqi")
                return notify_fail("你的内功心法不对，发挥不出绵掌劲力之威。\n");                                                                                     
        if (userp(me) && me->query_skill_mapped("parry") != "zhenshan-mianzhang")
                return notify_fail("你必须在激发绵掌为招架的情况下才能使用绵掌之劲力。\n");
        
        i=me->query_skill("strike",1)+me->query_skill("zhenshan-mianzhang",1)+me->query_skill("force",1);
        j=target->query_skill("parry",1)+target->query_skill("dodge",1)+target->query_skill("force",1);
        p =(me->query("combat_exp")-target->query("combat_exp"))/200000;		 
        if (!userp(target))
      		z = i/5 - j/10 + p;
		else z=i/8 - j/10 + p;
        
		if ( z < 3 ) z = 3;
        if ( z > 12 ) z = 12;
        k = random(z) + 1;
        
		me->set_temp("mz_mian", 1);
		me->add_temp("apply/attack",i/6);
		me->add_temp("apply/damage",i/8);
       
		message_vision(HIY"$N双掌由刚变柔，忽然间变得绵软无力，掌影变得飘逸不定，正以武当三十六路绵掌中的功夫，\n"+
		  HIC"$N阴柔无比地试图从$n的招式破绽中直插而进。\n"NOR,me, target);
        me->add("neili", -600);
        // 定义绵掌变量
		if (me->query_skill("zhenshan-mianzhang",1)<350)
		{
			damage=i*6;
		} else damage=i*4;
		
		if (objectp(target) 
			&& me->is_fighting(target) 
			&& random(me->query("neili"))>target->query("neili")/3)
		{	
			message_vision(HIY"\n$N双掌如游蛇，施展绵劲中的"MAG"[ 钻 ]"HIY"字诀，直击$n的丹田部位。\n"NOR,me, target);
			
			damage+=random(damage);
			
			target->receive_damage("qi",damage,me);
			target->receive_wound("qi",damage/4,me);
		    target->apply_condition("no_exert",1);
		}	
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	    
		if ( me->is_fighting(target) && me->query_skill("zhenshan-mianzhang", 1) > 250 && k > 3 )
		{
		   message_vision(MAG"\n$N心中默念“不招不架，顺势而下。”掌掌紧贴$n关节，招招锁"HIG"[ 拿 ]"MAG"对方脉门，"+
			"$n顿时被逼得手忙脚乱。\n"NOR,me, target);
	       target->add_busy(k);
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
         }
	    if ( me->is_fighting(target) 
			//&& !me->query_temp("mz_jin") 
			&& me->query_skill("zhenshan-mianzhang", 1) > 250
			&& k > 4 ){
	       message_vision(HIG"\n$N漫不经心的东击一拳，西劈一掌，$n一个身影竟被你这若有若无，似虚还实的漫天掌影所"WHT"[ 封 ]"HIG"住，"+
			   "空有一身功力也无法施展。\n"NOR,me, target);
		   
		   target->apply_condition("no_perform", 1);

           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	       
		   //target->set_temp("mz_jin",1);
           //target->start_call_out((: call_other, __FILE__, "remove_effect", target :),(int)i/6);
           //check_fight(me);
         }
	    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);

	    if ( me->is_fighting(target) && me->query_skill("zhenshan-mianzhang", 1) > 300 && k > 5 )
		{
	       message_vision(WHT"\n$N见$n斗志已失，门户大开，当下再不犹豫，双掌一合，内劲外吐，"HIR"[ 震 ]"WHT"字诀出手，"+
		      "正好三十六路绵劲堪堪收招打完，气定神闲站立当场。\n"NOR,me, target);        
           
	       damage += damage;	
		   damage = damage + random(damage);
		   if (damage>4000) damage=4000+(damage-4000)/100;
		   
		   target->receive_damage("qi", damage,me);
		   target->receive_wound("qi", damage/4,me);
		   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		   me->add("neili", -i);
		}
     
		me->start_perform(4, "绵掌");
		me->add_temp("apply/attack",-i/6);
		me->add_temp("apply/damage",-i/8);
		me->delete_temp("mz_mian");
        return 1;
}
/*
int check_fight(object me)
{
        if(!me->is_fighting(target)){
                target->clear_condition("no_perform");
		        me->delete_temp("mz_jin");
         }
        return 1;
}       
*/

void remove_effect(object target)
{
      if(!target) return;      
      target->clear_condition("no_perform");
      target->delete_temp("mz_jin");
      return 0;
}
string perform_name(){ return HIR"绵掌绝技"NOR; }
int help(object me)
{
         write(HIC"\n震山绵掌"+HIR"「绵掌绝技」"NOR"\n");
         write(@HELP
	震山绵掌乃是武当入门的初期武功，既有
	刚猛的一面，也有绵软阴柔的招式。宋青
	书在光明顶和张无忌一战，凭借花开并蒂
	一招的施展，使得镇山绵掌享誉江湖，当
	事情败露后，张三丰恨其歹毒，随手一招
	绵掌将宋的头骨震裂。但又没伤害其姓名，
	可见其招式的阴柔。绵掌绝技由此而来。
	连发数招，将对手牵制住并给与绝杀一击
	毙命。
	
	perform strike.mianzhang

要求：
	当前内力要求 1500 以上；
	最大内力要求 3000 以上；
	当前精力要求 1500 以上；
	震山绵掌等级 250 以上；
	氤氲紫气等级 250 以上；
	基本掌法等级 250 以上；
	道学心法等级 150 级别；
	激发掌法为震山绵掌；
	激发招架为震山绵掌；
	激发内功为氤氲紫气。

HELP
        );
        return 1;
}
