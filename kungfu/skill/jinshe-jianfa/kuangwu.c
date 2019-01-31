//rebuild by jpei 2010
//原来的思路有些乱
 
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

 int perform(object me, object target)
 {
         string msg;
         object weapon;
         int jf,zf,sf,lvl,i,j;
         jf = me->query_skill("jinshe-jianfa", 1);
         zf = me->query_skill("jinshe-zhang", 1);
         sf = me->query_skill("wudu-yanluobu", 1);
         lvl=( jf + zf +sf ) /3;        
         weapon = me->query_temp("weapon");
 
         if( !target ) target = offensive_target(me);
        if( !target ) target = offensive_target(me);

        if( !target 
          || !me->is_fighting(target)
          || !objectp(target)
          || environment(target)!= environment(me))
                return notify_fail("「金蛇狂舞」只能在战斗中对对手使用。\n");
 
 
        if (!weapon || weapon->query("skill_type") != "sword"
            || me->query_skill_mapped("sword") != "jinshe-jianfa")
                 return notify_fail("你必须在使用剑时才能使出「金蛇狂舞」！\n");
 
        if(me->query_skill("jinshe-jianfa", 1) < 450 )
                 return notify_fail("你的金蛇剑法还不够娴熟，使不出「金蛇狂舞」绝技。\n");
		if(me->query_skill("jinshe-zhangfa", 1) < 450 )
                 return notify_fail("你的金蛇掌法还不够娴熟，使不出「金蛇狂舞」绝技。\n");
        if( (int)me->query_skill("force",1) < 450 )
                 return notify_fail("你的基本内功等级不够，使不出「金蛇狂舞」绝技。\n");
 
         if( (int)me->query_str() < 37)
                 return notify_fail("你的膂力还不够强劲，使不出「金蛇狂舞」绝技。\n");
 
         if( (int)me->query_dex() < 37)
                 return notify_fail("你的身法还不够迅猛，使不出「金蛇狂舞」绝技。\n");

         if( (int)me->query("dex") < 20 ||(int)me->query("str") < 20 || (int)me->query("int") < 20)
                 return notify_fail(HIG"你傻头傻脑,笨手笨脚的,乱舞个什么劲.\n"NOR);
              
         if( (int)me->query("max_neili") < 5000 )
                 return notify_fail("你现在内力太弱，使不出「金蛇狂舞」。\n");      
 
         if( (int)me->query("neili") < 500 )
                 return notify_fail("你现在真气不足，使不出「金蛇狂舞」。\n");

		 if (me->query("quest/金蛇剑法/pass"))
		 {
			 i=3;
		 }else if (me->query("quest/jinshe2/pass"))
		 {
			 i=2;
		 }else i=1;
		 //weapon = me->query_temp("weapon");

//判断武器是不是金蛇剑或者银蛇,并消除bug
         if((weapon->query("id") == "jinshe sword" && weapon->query("owner")=="夏雪宜")
		   ||(weapon->query("id") == "yinshe sword" && weapon->query("spec"))
		   || !userp(me))
			   me->set_temp("jsjf/shejian", 1); 
   //五毒阎罗步奖励
         if( me->query_skill("wudu-yanluobu", 1) > 450
			 && me->query_skill_mapped("dodge") == "wudu-yanluobu")
           {     
			 
			 me->add_temp("apply/dexerity",sf /10);
             me->add_temp("apply/attack",sf /4); 
             me->set_temp("jsjf/sfup",1); 
           }
//金蛇掌法奖励
         if( me->query_skill("jinshe-zhangfa", 1) > 450
			 && me->query_skill_mapped("strike") == "jinshe-zhangfa"
		     && me->query_skill_prepared("strike") == "jinshe-zhangfa")
           {          
		     me->add_temp("apply/strength", zf/10);
             me->add_temp("apply/damage", zf/6);
             me->set_temp("jsjf/zfup",1);
           }       

		
         message_vision(HIC"\n$N一摆手中"+weapon->name()+HIC"使出金蛇剑法不传之秘，第"HIY+chinese_number(i)+HIC"重金蛇狂舞之"HIY"金蛇狂舞"HIC"，身法骤然加快了速倍。\n"NOR,me);
         //普通攻击
		 me->add_temp("apply/damage", lvl /6);
         me->add_temp("apply/attack", lvl /4);
         me->add_temp("apply/dexerity",sf /10);
		 me->add("neili",-800);
		 me->add("jingli",-500);
//普通兵器狂舞
         if (!me->query_temp("jsjf/shejian"))
         {
			 for (j=0;j>5 ;j++ )
			 {
				if (objectp(target)&&me->is_fighting())
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			 }
			 me->add_temp("apply/damage", -lvl /6);
			 me->add_temp("apply/attack", -lvl /4);
			 me->add_temp("apply/dexerity",-sf /10);
			 me->add_busy(2);
			 me->start_perform(5,"金蛇狂舞");

			 return 1;

         }
//特殊蛇形兵器狂舞

         if(me->query_temp("jsjf/sfup"))
         {      
            message_vision(HIY"\n\n$N手中"+weapon->name()+HIY"连划数剑，逼出道道金光，剑光中$N化身为"HIR+chinese_number(i)+HIY"，身形宛如蛇形，围绕$n快速旋转！。\n"NOR,me,target);
            message_vision(HIR"$N身法变得邪异无比,$n顿时觉得眼花缭乱,被$N攻了个措手不及！\n"NOR,me,target);                     
            if(!userp(target)) target->add_busy( sf/100 + random(2));
		 }


         if(me->query_temp("jsjf/shejian") )
		 {  
			    //金蛇剑法奖励                                                             
			 if( me->query_skill("jinshe-jianfa",  1) > 450
				 && me->query_skill_mapped("sword") == "jinshe-jianfa")
			  {     
				 	message_vision(MAG"$N手持"+weapon->name()+MAG",金蛇剑法在怪异武器配合下，威力顿时倍增！\n"NOR,me);
					me->add_temp("apply/sword", lvl /4);
					me->add_temp("apply/parry", lvl /4);
					me->add_temp("apply/damage", lvl/6);
					me->set_temp("jsjf/jfup",1);
			  }        


			if (me->is_fighting(target)) 
				  COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
							  message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       
							  message_vision(HIY"                                                                     ※※  金  ※※\n"NOR,me);
							  message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       
	   
			if (me->is_fighting(target)) 
				  COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
							  message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       
							  message_vision(HIY"                                                                     ※※  蛇  ※※\n"NOR,me);       
							  message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       

			if (me->is_fighting(target))
				  COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
							  message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       
							  message_vision(HIY"                                                                     ※※  狂  ※※\n"NOR,me);       
							  message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       
			if (me->is_fighting(target))
				  COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
							  message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       
							  message_vision(HIY"                                                                     ※※  舞  ※※\n"NOR,me);       
							  message_vision(HIY"                                                                     ※※※※※※※\n"NOR,me);       
		 	
			if (objectp(target)&&me->is_fighting())
			{
				weapon->unequip(); 
				message_vision(HIB"$N剑猛然一收，在奔跑过程中顺势拍出一掌！\n"NOR,me,target);
				me->add_temp("apply/strike",lvl/4);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				me->add_temp("apply/strike",-lvl/4);
				weapon->wield();
			}

		 } 
		 else if( objectp(target)
				&& me->query_temp("jsjf/zfup"))
		 {
			  message_vision(HIC"\n突然$N绕着$n快速奔走，猛然击出一剑两掌！\n"NOR,me,target);
			  me->start_perform(4,"「金蛇狂舞」");
				  if (objectp(target)&&me->is_fighting())
					  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				
				  if (objectp(target)&&me->is_fighting()) 
				  {
					 weapon->unequip(); 
					 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
					 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
					 weapon->wield();
				  }
		}       

       if (me->query_temp("jsjf/sfup"))
	   {
                me->add_temp("apply/dexerity",-sf /10);      
                me->add_temp("apply/attack",   -sf /4); 
				me->delete_temp("jsjf/sfup");
       }
       if (me->query_temp("zfup"))
	   {  
                me->add_temp("apply/strength", -zf/10);
                me->add_temp("apply/damage", -zf/ 6);
				me->delete_temp("jsjf/zfup");
       }
       if( me->query_temp("jsjf/jfup"))
	   {
                me->add_temp("apply/sword",     - lvl/4);
                me->add_temp("apply/parry",      - lvl/4);
                me->add_temp("apply/damage",  - lvl/6);
				me->delete_temp("jsjf/zfup");
       }
		
       me->delete_temp("jsjf/shejian");

       me->add_temp("apply/damage", -lvl /6);
       me->add_temp("apply/attack", -lvl /4);
       me->add_temp("apply/dexerity",-sf /10);  
       me->start_busy(1+random(2));
       target->start_busy(1);
       me->start_perform(6,"「金蛇狂舞」");

       return 1;
 }


int help(object me)
{
        write(HIY"\n金蛇剑法之「金蛇狂舞」："NOR"\n\n");
        write(@HELP
	金蛇郎君夏雪宜所流传下来的的绝世武功. 可惜在争夺中
	金蛇秘籍被分割成好几部分, 金蛇狂舞的威力也大不如前. 
	相传在凑齐金蛇秘籍中的剑法, 身法, 掌法后才能发挥金
	狂舞真正的威力. 如果有幸可以获得金蛇剑, 可使其威力
	更上层楼。

	指令：perform sword.kuangwu

要求：
	当前内力 500 以上;
	最大内力 5000 以上；
	金蛇剑法 450 以上；
	金蛇掌法 450 以上；
	基本内功 450 以上；
	先天身法,悟性不能小于20,
	先天臂力不能小于20,
	后天身法、臂力大于37
	第一阶段：金蛇剑法等级 450 以上；基本内功等级 450 以上；
	激发剑法为金蛇剑法；
	第二阶段：金蛇掌法等级 450 以上；激发准备掌法为金蛇掌法；
	第三阶段：五毒阎罗步等级 450 以上；激发轻功为五毒阎罗步；
                
    另外，如果装备了金蛇剑或者银蛇剑，威力可更上一层楼．

HELP
        );
        return 1;
}

string perform_name(){ return HBYEL+HIR"金蛇狂舞"NOR; }
