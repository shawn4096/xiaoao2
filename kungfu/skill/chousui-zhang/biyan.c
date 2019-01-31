#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
      object ob;
      string msg, *limbs;
      int i, neili, ap, dp, damage, p;
        
      i = (int)me->query_skill("chousui-zhang", 1);
      neili = (int)me->query("neili");   
        if( !target ) target = offensive_target(me);
    if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) 
        || !living(target)
        || environment(me)!=environment(target) )
                return notify_fail("「碧焰」攻击只能对战斗中的对手使用。\n");
      
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「碧焰」！\n");        
        if(!objectp(ob = present("huo yan", environment(me))))
                return notify_fail("没有火堆怎么驱动「碧焰」进行攻击？\n");
        if(me->query_temp("pfm_chousui"))
                return notify_fail("你正在驱动火堆进行攻击！\n");
        if( i < 350 )
                return notify_fail("你发现自己的星宿毒掌还不够娴熟，无法使用「碧焰」进行攻击。\n");

        if( (int)me->query_skill("huagong-dafa",1) < 350 )
                return notify_fail("你发现自己的化功大法修为不够，无法使用「碧焰」进行攻击。\n");
        
		if( (int)me->query_skill("force",1) < 350 )
                return notify_fail("你发现自己的基本内功修为不够，无法使用「碧焰」进行攻击。\n");
		if( (int)me->query_skill("strike",1) < 350 )
                return notify_fail("你发现自己的基本掌法修为不够，无法使用「碧焰」进行攻击。\n");
        if((int)me->query_skill("poison",1) < 180)
                return notify_fail("你发现自己体内聚毒不够，无法使用「碧焰」进行攻击。\n");         

        if (me->query_skill_prepared("strike") != "chousui-zhang"
        || me->query_skill_mapped("strike") != "chousui-zhang"
        || me->query_skill_mapped("parry") != "chousui-zhang")
                return notify_fail("你必须用抽髓掌才能使用「碧焰」进行攻击。\n"); 
                                                                              
        if( me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("你发现自己所用的内功无法进行「碧焰」攻击。\n");

        if( (int)me->query("max_neili") < 5000) 
                return notify_fail("你发现自己内力太弱，无法驱动「碧焰」进行攻击。\n");

        if(neili < 2500)
                return notify_fail("你发现自己现在真气太弱，使不出「碧焰」进行攻击。\n");           
    
        if(target->query_condition("xx_poison") > 200)
                return notify_fail("对方已经身中无数剧毒，你不用再进行「碧焰」攻击了。\n");           

        message_vision(HIC"\n$N右手指向"HIR"火堆"HIC"，默不作声的注视着火焰，左掌按胸，口中喃喃的不知说些什么。\n"NOR,me);
                 
        ap = me->query("combat_exp")/100000 * me->query_str();
        dp = target->query("combat_exp")/100000 * target->query_dex();
        if (ap < 1) ap = 1;
        if (dp < 1) dp = 1;
        me->add("neili", -100);
        me->add("jingli", -25);
        
		message_vision(HIG"\n$N突然在自己舌尖狠命一咬,喷出数口精血，喷在"RED"火焰"HIG"之上，顿时只见空气中血雾弥漫，腥臭无比！\n"NOR,me);  
		me->receive_damage("qi",random(200),me);
		if (!me->query_temp("csz/biyan"))
		{
			message_vision(HBWHT+HIB"$N这几口精血蕴含剧毒，在火焰中顿生一股妖异的"HIG"碧焰"HBWHT+HIB"！，使得抽髓掌威力陡增！\n"NOR,me);  
		
			
			me->add_temp("apply/attack",i/4);
			me->add_temp("apply/strike",i/6);
			me->add_temp("apply/damage",i/6);
			me->set_temp("csz/biyan",i);
			call_out("remove_effect",1,me,i/50);
		}
		
        
		message_vision(HIG"\n然后$N突然双掌向前平平推出，但见"RED"火焰"HIG"微微颤动了两下，喷出一道"GRN"碧焰"HIG"，射向$n！\n"NOR,me,target);        

		
		if(random(ap+dp) > dp
			||random(me->query_skill("chousui-zhang",1))>target->query_skill("parry",1)/2)
		{
        	damage = (i+me->query("jiali"))*4;
          	if(neili > target->query("neili")*2) damage *= 2;
            if( damage > 6500) damage = 6500+random(damage-6500)/10;
          	
			target->receive_damage("qi", damage, me);
          	target->receive_wound("qi", random(damage), me);
          	
			target->apply_condition("xx_poison",  1+random(2));
		    
			if (userp(me) && userp(target) && me->query_condition("killer") < 15)
				me->apply_condition("killer", 15);
          	p = (int)target->query("qi")*100/(int)target->query("max_qi");
          	msg = damage_msg(damage, "内伤");
          	msg += "( $n"+eff_status_msg(p)+" )\n";
            if(userp(me) && me->query("env/damage"))
				tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR);
			
			if(userp(target)&& target->query("env/damage"))
				tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR);
			
			if (me->query_skill("chousui-zhang",1)<350)
			   me->start_busy(1);
          	if(!target->is_busy())
          		target->start_busy(3);
			message_vision(msg, me, target);

        }
        else{
          	if (!me->query("hgdf/powerup"))
				me->start_busy(1);
          	message_vision( HIY"\n$p全力向后一纵一闪，凶险万分地避开了那急速而来的碧焰！\n" NOR,me,target);
        }  
             
      // limbs = target->query("limbs");
    //   msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
    //   msg = replace_string(msg, "$w", GRN"碧焰"NOR);
   //    message_vision(msg, me, target);
       if (me->query_skill("chousui-zhang",1)<450)
       {
		   me->start_perform(2,"碧焰");
       }
       return 1;
}

int remove_effect(object me,int count)
{
	int i;
	if (!me) return 0;
	i=me->query_temp("csz/biyan");
	
	if (!me->is_fighting()
		||count<0
		||me->query_skill_mapped("strike")!="chousui-zhang"
		||me->query_skill_mapped("parry")!="chousui-zhang"
		||me->query_skill_prepared("strike")!="chousui-zhang")
	{
		
			me->add_temp("apply/attack",-i/4);
			me->add_temp("apply/strike",-i/6);
			me->add_temp("apply/damage",-i/6);
			me->delete_temp("csz/biyan");
			message_vision(WHT"$N长长吐出一口浊气，面色有些灰暗，疲态顿显，显然方才消耗不少精气！\n"NOR,me);  
			return 1;

	}
	call_out("remove_effect",1,me,count--);

}
string perform_name(){ return HIC"碧焰"NOR; }
int help(object me)
{
        write(HIB"\n抽髓掌之「碧焰」："NOR"\n\n");
        write(@HELP
	星宿派的功夫主要是在<毒>字上下功夫，深的阴损毒辣其中三味
	抽髓掌乃是在战斗中，凭借深厚内功把体内存毒逼出借以伤敌的
	一门功夫。「碧焰」一式乃是通过雄浑内功将毒火推动攻向对手，
	后来者门功夫经过星宿老仙不断优化和推演，逐渐凝练，攻击和
	对抽髓掌的辅助进攻更是强大，450级后彻底大飞。
	
	指令：perform strike.biyan

要求：
	当前内力需求 2500 以上;
	最大内力需求 5000 以上；
	抽髓掌法等级 350 以上；
	化功大法等级 350 以上；
	基本掌法等级 350 以上；
	基本内功等级 350 以上;
	基本毒计等级 180 以上；
	且手中无兵器。

        
HELP
        );
        return 1;
}

