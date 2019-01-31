// beauty 美人三招
// 19991002001
// Update By lsxk@hsbbs 2007/6/5

#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return HBMAG+HIW"美人三招"NOR;}

int calc_damage(int,int,object,object);
int b_attack(object me,object target,object weapon);
int perform2(object me,object target,object weapon);
int perform3(object me,object target,object weapon); 

int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int skill,lvl,i,total; 
        skill=me->query_skill("tenglong-bifa",1);
		lvl=skill+me->query_skill("dulong-dafa",1)/4;
		weapon=me->query_temp("weapon");
        if( !target ) target = offensive_target(me);

         if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「美人三招」只能在战斗时使用！\n");

       // if(me->query("family/master_id")!="su quan")
         //       return notify_fail("「美人三招」只有拜了苏荃后才能用！\n");
		if(!me->query("quest/sld/tlbf/beauty/pass"))
                return notify_fail("「美人三招」你只是听说过，但你从尚未融会贯通！\n");

        if( !objectp(weapon) 
			|| weapon->query("skill_type")!="dagger")                    
                return notify_fail("你必须拿着匕首才能用「美人三招」！\n");
       

        
        if( (int)me->query_skill("chansi-shou", 1) < 500 )
               return notify_fail("你的金蛇缠丝手还不够熟练，不能使用「美人三招」！\n");

        if (me->query_skill_mapped("hand") != "chansi-shou")
               return notify_fail("只有使用金蛇缠丝手时才能使用「美人三招」！\n");

        if( (int)me->query_skill("shenlong-tuifa", 1) < 500 )
               return notify_fail("你的神龙腿法还不够熟练，不能使用「美人三招」！\n");

        if (me->query_skill_mapped("leg") != "shenlong-tuifa")
               return notify_fail("只有使用神龙腿法时才能使用「美人三招」！\n");

        if( (int)me->query_skill("tenglong-bifa", 1) < 500 )
                return notify_fail("你的腾龙匕法还不够熟练，不能使用「美人三招」！\n");

        if (me->query_skill_mapped("dagger") != "tenglong-bifa"
			||me->query_skill_mapped("parry") != "tenglong-bifa")
                return notify_fail("只有激发腾龙匕法时才能使用「美人三招」！\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 500 )
                return notify_fail("你的毒龙大法功力不足，不能用「美人三招」。\n");

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("你现在精力不足，不能使用「美人三招」！\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("你现在内力不足，不能使用「美人三招」！\n");      

        if(me->query("gender") == "男性" ) 
                return notify_fail("不是女人怎么能使用「美人三招」呢！\n");
        
		if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("你现在所使用的内功同毒龙大法向抵触，不能使用「美人三招」。\n");
		if (me->query_temp("tlbf/beauty"))
			return notify_fail("你现在使用「美人三招」。\n");

        me->add("jingli",-100);
        me->add("neili",-400);

        message_vision(HBMAG+HIW"$N乘$n稍稍走神之机，将苏夫人所传的招式融会贯通，以「美人三招」的方式施展出来。\n"NOR,me,target);
		message_vision(HBMAG+HIW"$N手中的"+weapon->name()+HBMAG+HIW"寒光闪闪，「贵妃回眸」、「小怜横陈」、「飞燕回翔」连贯而出！\n"NOR,me,target);
		me->set_temp("tlbf/beauty",1);
       
		if(random(me->query_skill("tenglong-bifa",1)) > target->query_skill("parry",1)/4
          || random((int)me->query("combat_exp")) > (int)target->query("combat_exp")/6
          ||(!userp(target) &&target->is_busy()) )
		{
                //me->start_busy(1);
                total = 0;
                i = calc_damage((int)me->query_skill("shenlong-tuifa",1),(int)me->query_skill("tenglong-bifa",1),me,target);
                total += i;
				if (me->query("gender")=="女性" && random(me->query_per(1))>35)
				{
					total=total+i*((int)me->query("per")/25);
					target->add_busy(2+random(2));
					message_vision(HBYEL"$N姿势优美,嫣然一笑，顿时令$n不禁神情一呆！"NOR,me,target);
				}
				message_vision(HIY "\n\n$N使出一招「"HIM"贵妃回眸"HIY"」，身子微曲，纤腰轻扭，左足反踢，向$n小腹踢去，\n"+
                          "而后顺势反身，左手搂住$n头颈，右手兵刃对准$n后心击去。\n"NOR,me,target);
               
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                
                if (userp(target))
				    if (total>5000) total=5000+(total-5000)/100;
				//else if (total>8000) total=8000+(total-8000)/100;
                
				target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"刺伤");
                result = replace_string( result, "$l", "头颈" );
                msg = result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0); 
                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ i+ WHT"点攻击伤害。\n"NOR);    
                if(target&&userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ i+ WHT"点伤害。\n"NOR); 
               
		}else{

				message_vision(" 但是$n看破了$N的企图，没有上当，急急忙忙向旁边一闪，躲了过去。\n",me,target);
				//return 1;
				me->add_busy(1);

		}
				//追加攻击。
				 		
		if (me->is_fighting()
			&&objectp(target)
			&&me->query("quest/sld/tlbf/beauty/pass"))
        {
					message_vision(HIG"$N在飞跃$n头顶之际，神龙腿法的裙底脚陡然而出，转身向$n连踢两腿，正是「"HIR"连环鸳鸯腿"HIG"」！\n"NOR,me,target);
					me->add_temp("apply/attack",skill/2);
					me->add_temp("apply/damage",skill/3);
					me->add_temp("apply/leg",skill/2);
					weapon->unequip();
					me->prepare_skill("leg", "shenlong-tuifa");
					target->add_busy(1);
					COMBAT_D->do_attack(me,target,me->query_temp("weapon"),3);
					COMBAT_D->do_attack(me,target,me->query_temp("weapon"),3);
					me->add_temp("apply/attack",-skill/2);
					me->add_temp("apply/damage",-skill/3);
					me->add_temp("apply/leg",-skill/2);
					weapon->wield();
        }
		//增加毒龙大法解开后嵌套
		if (me->query_temp("quest/sld/dldf/pass"))
		{
			me->start_perform(3,"美人三招");
		}else me->start_perform(6,"「美人三招」");

		if (me->is_fighting()&&objectp(target)&&weapon)					
			perform2(me,target,weapon);
		
		me->delete_temp("tlbf/beauty");
		return 1;
}

//第二招
int perform2(object me,object target,object weapon)
{
        string msg,result;
        int skill,lvl,i,total; 
        skill=me->query_skill("tenglong-bifa",1);
		lvl=skill+me->query_skill("dulong-dafa",1)/4;
		if (!objectp(target)||!objectp(weapon))
		{
			me->delete_temp("tlbf/beauty");
			return 0;
		}
		me->set_temp("tlbf/beauty",1);
		if( !target ) target = offensive_target(me);

				message_vision(HIC "\n$N身子斜倾，使出一招「"HIG"小怜横陈"HIC"」，脑袋蓦地向自己胸口钻落，顺势在地上一个斛斗，反弹而起\n"+
                         "从$n胯下钻过，握着兵器的右手成拳击向$n后心。\n"NOR,me,target);
				
                i = calc_damage((int)me->query_skill("tenglong-bifa",1),(int)me->query_skill("chansi-shou",1),me,target);
                total += i;
				if (!userp(target))
					if (total>8000) total=8000+(total-8000)/100;
		       // else if (total>6000) total=6000+(total-6000)/100;
                
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"刺伤");
                result = replace_string( result, "$l", "后心" );
                result = replace_string( result, "$w", weapon->query("name") );
                msg = result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);
				//奖励进攻
			//	if (me->is_fighting(target)&& objectp(target))
				//	COMBAT_D->do_attack(me,target,weapon,3);


                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ i+ WHT"点攻击伤害。\n"NOR);    
                if(target&&userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ i+ WHT"点伤害。\n"NOR);
				if (me->is_fighting(target)&& me->query_per()>25)
                {
					message_vision(HIR"$n见$N冲自己嫣然一笑，正自神魂颠倒之际，$N右手忽然化成金蛇缠丝手的招式，陡然戳向$n的双眸！\n"NOR,me,target);
					if (random(me->query("combat_exp"))>target->query("combat_exp")/3)
					{
						message_vision(RED"$n被$N这疾风暴雨的诡异招式吓了一身冷汗，不禁有些手忙脚乱起来。\n"NOR,me,target);
						target->add_busy(2);
						target->add_condition("no_exert",1);
					}
					me->add_temp("apply/attack",skill/2);
					me->add_temp("apply/damage",skill/4);
					me->add_temp("apply/hand",skill/2);
					weapon->unequip();
					me->prepare_skill("leg");
					me->prepare_skill("hand", "chansi-shou");
					COMBAT_D->do_attack(me,target,weapon,3);//第5招
					COMBAT_D->do_attack(me,target,weapon,3);//6
					me->add_temp("apply/attack",-skill/2);
					me->add_temp("apply/damage",-skill/4);
					me->add_temp("apply/hand",-skill/2);
					weapon->wield();
                }
				//增加毒龙大法解开后嵌套
				if (me->query_temp("quest/sld/dldf/pass"))
				{
					me->start_perform(3,"美人三招");
				}else me->start_perform(6,"「美人三招」");
				if (me->is_fighting()
					&&objectp(target)
					&&weapon)
					call_out("perform3",1,me,target,weapon);
                me->delete_temp("tlbf/beauty");
				return 1;
}
				
int perform3(object me,object target,object weapon) 
{
	 string msg,result;
     int skill,lvl,i,total; 
     skill=me->query_skill("tenglong-bifa",1);
	 lvl=skill+me->query_skill("dulong-dafa",1)/4;
	 
		if (!objectp(target)||!objectp(weapon))
		{
			me->delete_temp("tlbf/beauty");
			return 0;
		}
		me->set_temp("tlbf/beauty",1);
				message_vision(MAG "\n$N使出一招「"HIR"飞燕回翔"MAG"」，右足顺势一勾，在兵器上一点，兵器陡地向$N咽喉\n"+
                         "射过去，$N身子向下一缩，那兵器急射$n胸口。\n"NOR,me,target);
				//if (objectp(target))
			    i = calc_damage((int)me->query_skill("tenglong-bifa",1),(int)me->query_skill("dulong-dafa",1),me,target);
                total += i;
				
				if (!userp(target))
					if (total>10000) total=10000+(total-10000)/100;
		      //  else if (total>7000) total=7000+(total-7000)/100;
                
				if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                

                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(total,"刺伤");
                result = replace_string( result, "$l", "胸口" );
                msg = result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);  
				//奖励攻击			
				//附加攻击
				if (me->is_fighting()
					&& objectp(weapon)
					&& objectp(target)
					&& me->query("quest/sld/tlbf/beauty/pass"))
				{
					b_attack(me,target,weapon);	
				}
				//call_out("b_attack",1,me,target,weapon);
			

     
				if(userp(me) && me->query("env/damage"))
				{
					tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ i+ WHT"点攻击伤害。\n"NOR);  
					tell_object(me,WHT"你的”美女三招“对"+ target->query("name") +"总共造成了"RED+ total+ WHT"点攻击伤害。\n"NOR);    
				}
         
				if(target&&userp(target)&& target->query("env/damage"))     { 
					tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ i+ WHT"点伤害。\n"NOR); 
					tell_object(target,WHT""+ me->query("name") +"的”美女三招“对你总共造成了"RED+ total+ WHT"点伤害。\n"NOR);          
				}
                
                if(wizardp(me)) tell_object(me,sprintf("Total damage: %d \n",total));
                
				//增加毒龙大法解开后嵌套
				if (me->query_temp("quest/sld/dldf/pass"))
				{
					me->start_perform(3,"美人三招");
				}else me->start_perform(6,"「美人三招」");
				me->delete_temp("tlbf/beauty");
				return 1;
}

int b_attack(object me,object target,object weapon)
{
		
		
		int skill;
		if (!me||!target||!weapon) return 0;
		skill=me->query_skill("tenglong-bifa",1);

		message_vision(HBRED"$n忽然见$N的匕首已然面临胸前，当真神出鬼没，$N掩嘴轻笑，手上又是连续三招，招招致命！\n"NOR,me,target);
		message_vision(HIW"$n忍不住对$N喝道，“美人，你真当得起，艳若桃李，心似蛇蝎”，下手居然如此狠毒！\n"NOR,me,target);

		me->set_temp("tlbf/beautya",1);
		me->add_temp("apply/attack",skill/2);
		me->add_temp("apply/damage",skill/4);
		if (me->is_fighting(target)&& objectp(target))
			COMBAT_D->do_attack(me,target,weapon,3);
		if (me->is_fighting(target)&& objectp(target))
			COMBAT_D->do_attack(me,target,weapon,3);
		if (me->is_fighting(target)&& objectp(target))
			COMBAT_D->do_attack(me,target,weapon,3);
		me->delete_temp("tlbf/beautya");

		me->add_temp("apply/attack",-skill/2);
		me->add_temp("apply/damage",-skill/4);        
		me->start_perform(6,"「美人三招」");

		return 1;

}

int calc_damage(int skill,int skill2,object me,object target)
{
			int i;
			if (!me||!objectp(target)) return 0;
		
            i = ( (skill+skill2)*2 - (int)target->query_skill("parry",1) )*10;
            if (i<0) i = -i;
               i += random(i*2/5);
            if( i < (skill2*5)) i = (int)target->query("qi",1)/2;   

            if(userp(target)) return  i/3;


			return i*3/5;
}

int help(object me)
{
   write(WHT"\n腾龙匕法之「"HBMAG+HIW"美人三招"WHT"」："NOR"\n");
   write(@HELP
	腾龙匕法乃是神龙岛主夫人苏荃的不传之谜
	变化多端，防不胜防。可谓将女人的优势发
	挥的淋漓尽致。
	美人三招是将神龙岛女性阴柔武技之大成，
	既有腿法，又有缠丝手夹杂在匕首之中，战
	斗期间，神鬼难测，防不胜防。
	注意：容貌和身法是命中和伤害的基础。
	
	perform dagger.beauty

要求：
	当前内力的要求 1500 以上；
	当前精力的要求 1000 以上；
	金蛇缠丝手等级 500 以上；
	神龙腿法的等级 500 以上；
	基本匕法的等级 500 以上；
	毒龙大法的等级 500 以上；
	激发内功为毒龙大法；
	激发匕法为腾龙匕法
	激发招架为腾龙匕法；
	激发腿法为神龙腿法；
	激发手法为金蛇缠丝手；
	性别需求 女性
HELP
   );
   return 1;
}
