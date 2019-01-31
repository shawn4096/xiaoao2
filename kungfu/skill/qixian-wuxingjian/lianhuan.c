//lianhuan.c 七弦连环诛
//cre by sohu@xojh 2014/6/6
// 

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
       object weapon;
	   int i, a,skill;

  	   if( !target ) target = offensive_target(me);
         skill=me->query_skill("qixian-wuxingjian",1);
	   if( !objectp(target)
	    || !target->is_character()
	    || !me->is_fighting(target)
	    || !living(target) )
		return notify_fail("「七弦连环诛」只能对战斗中的对手使用。\n");


 
        if( (int)me->query_skill("qixian-wuxingjian", 1) < 450 )
		   return notify_fail("你的七弦无形剑等级不足，无法使出「七弦连环诛」。\n");
 
        if( (int)me->query_skill("sword", 1) < 450 )
		   return notify_fail("你的基本剑法等级不足，无法使出「七弦连环诛」。\n");


        if( (int)me->query_skill("force", 1) < 450 )
		    return notify_fail("你的基本内功等级不足，无法使出「七弦连环诛」。\n");

        if( (int)me->query("max_neili") < 9500 )
		   return notify_fail("你的内力修为太浅，无法使出「七弦连环诛」。\n");

	    if( (int)me->query("neili") < 3000 )
		   return notify_fail("你的真气不足，无法使出「七弦连环诛」。\n");
		
		if( (int)me->query("jingli") < 2000 )
		   return notify_fail("你的精力不足，无法使出「七弦连环诛」。\n");

	    //if( me->query_skill_mapped("force") != "xixing-dafa" )
		  // return notify_fail("你没有使用吸星大法，无法使出「七弦连环诛」?\n");
         //增加使用限制，必须是琴
	    if( !objectp(weapon = me->query_temp("weapon"))
	     || weapon->query("skill_type") != "sword"
		 || !weapon->query("qinjian")
	     || me->query_skill_mapped("sword") != "qixian-wuxingjian" )
	    	return notify_fail("你使得了「七弦连环诛」么?\n");
        
		if( me->query_temp("qxwxj/lianhuan") )
		    return notify_fail("你正在使用「七弦连环诛」。\n");
		//吸星大法有额外加成
        skill = (int)me->query_skill("qixian-wuxingjian",1) +(int)me->query_skill("xixing-dafa",1) /4;
  	      
        me->add("neili",-(150+random(50))); 
        me->add("jingli",-50); 
		me->set_temp("qxwxj/lianhuan",6);
		
		me->add_temp("apply/attack",skill/4);
        me->add_temp("apply/damage",skill/6);
		if (weapon->query("qinjian"))
		{
			message_vision(HIG"$N身形暴退数丈，从行囊种掏出一张"+weapon->query("name")+HIG",看着$n，悠悠一叹！\n"NOR,me,target);
			//琴类武器增加威力
			me->add_temp("apply/damage",skill/4);
			me->add_temp("apply/attack",skill/4);
			me->set_temp("qxwxj/lhqj",1);
		}
		
		
		message_vision(HIB"\n$N屏气凝神，双手起伏不定，按在"+weapon->query("name")+HIB"上，琴声时缓时急，忽尔悄然无声，忽尔铮然大响。\n"+
			               "过了一会，琴声越弹越急,偶而琴音高亢,忽然间琴音铮铮大响，琴音响一声，$n便退出一步，琴音连响五下，\n"+
			               "$n便不由自主的退了五步，$N施展出的正是七弦无形剑的绝技「七弦连环诛」！\n"NOR,me,target);
      
        for(a=0;a<=7;a++)
        {		     
		     if (me->is_fighting())
		      {		      
		         
				 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);				
			   }
			
        }

		if (me->is_fighting(target)
			&&random(me->query("neili",1))>target->query("neili",1)/3
			//&&me->query("hmy/qxwxj/lianhuan")=="pass"
		) 
	    {
			message_vision(HIR"$N手中"+weapon->query("name")+HIR"连发六音，这六音连续狠打猛击，那$n如何能抵受得了?\n"NOR,me,target);
            message_vision(HIW "只见$N" HIW "双目微闭，单手在" + weapon->query("name") +HIW "上轻轻拨动，顿时只听“啵啵啵”破空之声连续不断，\n"+
								"数股凝聚成一股破体无形剑气激射而出，直奔$n" HIW "而去，正是「七弦连环诛」最后一击「黄龙闪」。\n" NOR,me,target);
            target->add("neili",-2000-random(5000));
			target->apply_condition("no_exert",2+random(3));
			target->apply_condition("neishang",2);
			message_vision(HIY"$n只觉自己内力翻腾不已，面色惨白，显然为$N的琴音所伤。\n"NOR,me,target);
			me->add_temp("apply/sword",skill/4);
            me->add_temp("apply/damage",skill/4);
			me->set_temp("must_be_hit",1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            me->add_temp("apply/sword",-skill/4);
			me->add_temp("apply/damage",-skill/4);
			me->delete_temp("must_be_hit");

    	}
		if (me->query_temp("qxwxj/lhqj"))
		{
			me->add_temp("apply/damage",-skill/4);
			me->add_temp("apply/attack",-skill/4);
			me->delete_temp("qxwxj/lhqj");

		}
		me->add_temp("apply/attack",-skill/4);
        me->add_temp("apply/damage",-skill/6);
		me->delete_temp("qxwxj/lianhuan");
        me->start_perform( 5 + random(2), "「七弦连环诛」");
        me->start_busy(2);
        return 1;
}


string perform_name(){ return HIR"七弦连环诛"NOR; }
int help(object me)
{
        write(HIY"\n七弦无形剑"+HIR"「七弦连环诛」"NOR"\n");
        write(@HELP
	“七弦无形剑”只是琴音，声音本身自不能伤敌，效用全在激发敌人
	内力，扰乱敌招，对手内力越强，对琴音所起感应也越加厉害。其
	中最厉害的招数是“六丁开山”神技，施展时通过六次拨弦，不断催
	加内力，最后七弦同响，内力催到顶峰，是黄钟公武功中的登峰造
	极之作。
	「七弦连环诛」乃是传自梅庄四友的黄钟公，他乃是江南四友老大。
	一身武功深不可测，内功更是极其深厚，他的七弦五形剑乃是当世
	一绝，连任我行都不禁极为佩服，七弦无形剑乃是以音攻击对方，若
	对方内功越是深厚，所受伤害越大，令人防不胜防。
	
	指令;perform sword.lianhuan

要求：
	基本内功等级 450 以上；
	基本剑法等级 450 以上；
	七弦无形剑   450 以上；
	所需最大内力 9500；
	所需当前内力 3000；
	所需当前精力 2000；
	无需特定门派内功支持，
	吸星大法有额外加成。

HELP
        );
        return 1;
}