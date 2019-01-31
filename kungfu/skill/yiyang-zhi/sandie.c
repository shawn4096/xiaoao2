// /kungfu/skill/yiyang-zhi/sandie.c
// COOL@SJ
// Modified by snowman@SJ 05/12/2000

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>
#include <combat.h>
 
string perform_name() {return YEL"阳关三叠"NOR;}
int perform2(object me, object target);
int perform3(object me, object target);

int perform(object me, object target)
{       
        string msg;
        int damage;
        
        if( !target ) target = offensive_target(me);
 
        if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target))
                return notify_fail("「阳关三叠」只能在战斗中使用。\n");
        if( !living(target) )
        	return notify_fail("对方已经晕过去了。\n");
        	
        if( objectp( me->query_temp("weapon")) )
                return notify_fail("只有空手才能施展「阳关三叠」。\n");

        if((int)me->query_skill("yiyang-zhi", 1) < 450 
         ||(int)me->query_skill("finger", 1) < 450 
         ||(int)me->query_str() < 60)
                return notify_fail("你有的功夫还不够娴熟，不会使用「阳关三叠」。\n");

        if(me->query_skill("kurong-changong", 1)<450)
          if(me->query_skill("qiantian-yiyang", 1) <450)
                return notify_fail("以你现在的内功修为还使不出「阳关三叠」。\n");        
         
        if (me->query_skill_mapped("force") != "kurong-changong" )
        if (me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail("你所使用的内功不对。\n");

        if (me->query_skill_prepared("finger") != "yiyang-zhi" 
         || me->query_skill_mapped("finger") != "yiyang-zhi" )
                return notify_fail("你现在无法使用「阳关三叠」进行攻击。\n");
 
        if(me->query_temp("start_6mai"))
                return notify_fail("你已经在运用六脉神剑的无形剑气了！\n");

        if (me->query_skill_mapped("parry") != "kurong-changong" )
           if (me->query_skill_mapped("parry") != "yiyang-zhi")
                return notify_fail("你所使用的招架不对。\n");

        if((int)me->query("max_neili") < 5000 )
                return notify_fail("你的内力修为太弱，不能使用「阳关三叠」！\n");

        if((int)me->query("neili") < 1500 )
                return notify_fail("你的真气不够！\n");
			
		if( me->query_temp("sandie/js") || me->query_temp("sandie/jt") )
		return notify_fail("你的真气不够！\n");

	    if( me->query("env/一阳指") == "惊神" ) {
		if ( target->query_temp("sandie/jingshen")) 
			return notify_fail("你正在向对手使用着「阳关三叠之惊神」绝招！\n");
		else {
			if( me->query_temp("sandie/js") ) 
				return notify_fail("你正在使用着「阳关三叠之惊神」绝招！\n");
			else
			me->set_temp("sandie/js",1);
			perform2(me, target); 
//			call_out("perform2", 0, me, target); 
			return 1;
		}
	}
	else if( me->query("env/一阳指")=="截天" ) {
		if( target->is_busy() ) 
			return notify_fail("对方正忙着呢！\n");         
		else {
			if( me->query_temp("sandie/jt") ) 
				return notify_fail("你正在使用着「阳关三叠之截天」绝招！\n");
			me->set_temp("sandie/jt",1); 
			perform3(me, target); 
//			call_out("perform3",0,me, target); 
			return 1;
		}
	}
		
               
    
        if((string)me->query("class")=="bonze")
           	msg = WHT "\n$N双掌合什，口中低诵佛号，凝气于指，一式「破煞」点出，但听得嗤的一声轻响，一股纯阳的内力直袭$n胸口！\n" NOR;
        else if ((string)me->query("class")=="officer")
           	msg = HIY "\n$N使出「阳关三叠」绝招，须发飞舞, 威猛之极，大喝一声「破煞」,一指点出，但听得嗤嗤有声，一股纯阳的内力直袭$n胸口！\n" NOR; 


        else msg = YEL "\n$N使出「阳关三叠」绝招，大喝一声「破煞」,一指点出，但听得嗤嗤有声，一股纯阳的内力直袭$n胸口！\n" NOR; 

        
        if( random( me->query("combat_exp") ) > target->query("combat_exp")/3  
        || target->is_busy() 
		|| (me->query("env/一阳指") == "三叠" && me->query("quest/tls/yyz/sandie/pass"))
        || me->query("env/一阳指") == "破煞" )
         {

             	target->add_busy(1);
             	damage =(int)me->query_skill("kurong-changong", 1) * 3 + (int)me->query_skill("finger") * 3 + (int)me->query_skill("qiantian-yiyang", 1) * 3;
             	damage += (int)me->query_skill("yiyang-zhi", 1)*3;
        	    damage = random(damage)+damage;

             	if( me->query("neili") > target->query("neili") )
                     	damage += random(me->query("jiali"))*2;
                if (me->query("neili") > target->query("neili")*2 ) 
                       	damage *= 2;
                       	

                if(!userp(me)) damage = damage / 2;
               
            	target->receive_damage("qi", damage, me);
            	target->receive_wound("qi", damage/3, me);
				target->receive_damage("jingli",damage/4,me);
				
            	me->add("neili", -(damage/5));
            	msg += damage_msg(damage, "内伤")+"( $n"+eff_status_msg((int)target->query("qi")*100/(int)target->query("max_qi"))+" )\n"; 
            	
               if(userp(me) && me->query("env/damage"))
				   tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage+ WHT"点攻击伤害。\n"NOR); 
			   
if(userp(target)&& target->query("env/damage"))
				   tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage+ WHT"点伤害。\n"NOR);
			   if(me->query_skill("yiyang-zhi", 1) >=350)
            	{      	
				   me->start_perform(4, "三叠");
                  // call_out("perform2",1,me, target);       
                }
                else me->start_perform(5, "破煞");
	            }
        else {
		   if (me->query("env/一阳指") == "三叠" && me->query("quest/tls/yyz/sandie/pass"))
		   {
                me->start_busy(2);
                me->add("neili", -70);                
                msg += HIY"$p听得指力袭来，知道无法硬挡，一个巧云翻身，远远的躲了开去。\n"NOR;
                me->start_perform(4, "三叠");
                call_out("perform2", 1, me, target);
		   }        	    
	    }        
        message_vision(msg, me, target);
		if (objectp(target)&&objectp(me)&&me->is_fighting()&&(me->query("env/一阳指") == "三叠" && me->query("quest/tls/yyz/sandie/pass")))
		{		
			call_out("perform2", 1, me, target);
		}
		
		me->add_temp("apply/damage",me->query_skill("yiyang-zhi",1)/4);
		COMBAT_D->do_attack(me, target, 0, 3);//第一招，附带化学伤害
	    me->add_temp("apply/damage",-me->query_skill("yiyang-zhi",1)/4);
        return 1;
}

int perform2(object me, object target)
{
        int f,i,damage;
        string msg;
        
		if (!me ) return 0;        
        
        if( !living(me) ) return 0;
        
		me->delete_temp("sandie/js");   
        if(!target
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) )
               return notify_fail("你正要发一招，却见对手已经不用打了。\n");;

        if((int)me->query("neili", 1) < 400 )
               return notify_fail("你待要发出一指，却发现自己的内力不够了！\n");;    

        if( (int)me->query_skill("yiyang-zhi", 1) < 140)               
               return notify_fail("你的一阳指修为不够，无发使出「阳关三叠 」之 惊神。\n");;
     
        damage =(int)me->query_skill("kurong-changong", 1)  + (int)me->query_skill("finger") + (int)me->query_skill("qiantian-yiyang", 1);
        damage += (int)me->query_skill("yiyang-zhi", 1)*3;
        damage = random(damage)+damage*2;
 
        f = (int)me->query_skill("yiyang-zhi",1);

        me->start_perform(4, "惊神");             
        
        if( target->is_busy() ){
          	msg = YEL "\n紧跟着$N一阳指第二次点出，反手一指，一式「惊神」点出，但听得嗤的一声轻响，一股纯阳的指力透入$n体内任脉紫宫穴！\n" NOR;
          	i = 2+random(2);
        }
        else {
          	msg = YEL "\n紧跟着$N一阳指第二次点出，以纯阳内力，同时透入$n体内任脉紫宫穴、阴维脉大横穴、冲脉幽门穴、带脉章门穴和阴跤脉晴明穴！\n"NOR;        
          	i = 2;
        }


		if( random(me->query_skill("force",1)) > target->query_skill("force",1)/i
			|| (me->query("env/一阳指") == "三叠" && me->query("quest/tls/yyz/sandie/pass"))
			|| me->query("env/一阳指") =="惊神" )
         {
        	
                me->add("neili", -f*2);
                msg += HIR "$n只觉一股灼热之气侵入体内奇经八脉,全身上下暖洋洋的，极为虚弱，竟然提不起一丝力气！\n" NOR;
                target->add_temp("apply/attack", -f/4);
                target->add_temp("apply/dodge", -f/4);
                target->add_temp("apply/parry", -f/4); 
                target->add_temp("apply/strength", -f/4); 
                
				
				target->receive_damage("qi", damage, me);
            	target->receive_wound("qi", damage/3, me);
				target->receive_damage("jingli",damage/4,me);

               
			    if(userp(me) && me->query("env/damage"))
				   tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+ damage+ WHT"点攻击伤害。\n"NOR); 
			   
				if(userp(target)&& target->query("env/damage"))
				   tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+ damage+ WHT"点伤害。\n"NOR);


				if( random(2) ) 
                 	target->apply_condition("no_exert", 2);
                else  
                 	target->apply_condition("no_perform", 2);
                 	
                target->set_temp("sandie/jingshen",f/4);

                call_out("sandie_back", 5+random(20), target, f/4);

                if((int)me->query_skill("yiyang-zhi", 1) >= 180 && (me->query("env/一阳指") == "三叠" && me->query("quest/tls/yyz/sandie/pass")))
                {
                 	remove_call_out("perform3");
                 	call_out("perform3", 1, me, target);
                }
           }
        else{
   
               me->add("neili", - 100);
                msg += HIY"\n两人身形一合瞬间分开,却见$p运起独门内功，消去了攻入体内的一阳指劲。\n" NOR;
                if((int)me->query_skill("yiyang-zhi", 1) >= 180 && (me->query("env/一阳指") == "三叠" && me->query("quest/tls/yyz/sandie/pass")))
                {
                  	call_out("perform3", 1, me, target);
                 }
        }
        message_vision(msg, me, target);
		if (objectp(target)&&objectp(me)&&me->is_fighting() && (me->query("env/一阳指") == "三叠" && me->query("quest/tls/yyz/sandie/pass")))
		{		
			call_out("perform3", 1, me, target);
		}
		
		me->add_temp("apply/damage",me->query_skill("yiyang-zhi",1)/4);
		COMBAT_D->do_attack(me, target, 0, 3);//第二招，附带破防效果
	    me->add_temp("apply/damage",-me->query_skill("yiyang-zhi",1)/4);
		
        return 1;
}

int perform3(object me, object target)
{
       
    int i;
 	string msg;
	if( !me ) return 0;

	if( !living(me) ) return 0;
	me->delete_temp("sandie/jt");
	me->delete_temp("yyz/sd");
	if(!target
        || !target->is_character()
        || !me->is_fighting(target) 
        || !living(target) )
               return notify_fail("你正要发一招，却见对手已经不用打了。\n");

        if((int)me->query("neili", 1) < 300 )
				return notify_fail("你待要发出一指，却发现自己的内力不够了！\n");
		
		if( (int)me->query_skill("yiyang-zhi", 1) < 180)			
               return notify_fail("你的一阳指修为不够，无发使出「阳关三叠 之 惊神」。\n");

        if (target->is_busy()) return notify_fail("对方正自顾不暇，放胆攻击吧！\n");
        
        i = me->query_skill("yiyang-zhi") /35;
     
        if(i>10) i=10; 
   
	     me->start_perform(4, "截天");

         msg = YEL"\n接着$N踏前一步，出第三指「截天」隔空点向$n胸前“玉堂穴”，认穴竟无厘毫之差！\n"NOR;

        if( random(me->query_skill("finger",1)) > target->query_skill("parry",1)/3 
			 || (me->query("env/一阳指") == "三叠" && me->query("quest/tls/yyz/sandie/pass"))
             || me->query("env/一阳指") =="截天" ){
              msg += HIR "结果一指点中，$n只觉得气脉通道阻塞，真气立受干挠，身形顿时变得迟缓起来！\n"NOR;
                target->add_busy( i );
                target->add("neili", -me->query_skill("force",1)*4);
                me->add("neili", -(me->query_skill("force",1)/3));
				if (me->query("yideng/ronghe")=="pass" && (me->query("env/一阳指") == "三叠" && me->query("quest/tls/yyz/sandie/pass")))
				{
					msg += HIY"\n$N将先天功和乾天一阳融合后内劲以一阳指施展出来，一阳指威力更甚！\n"NOR;
					me->start_call_out( (: call_other, __DIR__"yizhisanmai", "yzsm_attack", me, 2 :), 1 );
				}
				else if( (i =10  && userp(me) && (me->query("env/一阳指") == "三叠" && me->query("quest/tls/yyz/sandie/pass"))) || ( random(10)> 4 && me->query("env/一阳指") =="三叠"))
                {
          	        msg += HIM"\n$N潜运内力，面色波澜不惊，但手指上的劲气却是越来越强！\n"NOR;
                    me->start_call_out( (: call_other, __DIR__"yizhisanmai", "yzsm_attack", me, 1 :), 1 );
                }

           }
      
         else {
               	me->start_busy(1+random(2));
                me->add("neili", -200);
                target->add("neili", -random(100));
                msg += HIY"\n$p听得指力袭来，知道无法硬挡，便也隔空一击，两股力道相碰，$p顺势跳了开去。\n" NOR;
               }

        message_vision(msg, me, target);

		me->add_temp("apply/damage",me->query_skill("yiyang-zhi",1)/4);
		COMBAT_D->do_attack(me, target, 0, 3);//第三招，附带busy效果
	    me->add_temp("apply/damage",-me->query_skill("yiyang-zhi",1)/4);


        return 1;
}
void sandie_back(object target, int i)
{        
        if( !target ) return;
        target->add_temp("apply/attack", i);
        target->add_temp("apply/dodge", i);
        target->add_temp("apply/parry", i); 
        target->add_temp("apply/strength", i); 
        target->delete_temp("sandie/jingshen");
}



int help(object me)
{
   write(HIY"\n一阳指之「阳关三叠」："NOR"\n\n");
   write(@HELP
	渭城朝雨，一霎挹轻尘。
	更洒遍客舍青青，弄柔凝，千缕柳色新。 
	更洒遍客舍青青，千缕柳色新。
	休烦恼，劝君更尽一杯酒，
	人生会少，自古富贵功名有定分，莫遣容仪瘦损。
	休烦恼，劝君更尽一杯酒，
	只恐怕西出阳关，旧游如梦，眼前无故人

	取阳关三叠反复咏叹之意思，连出三指。以破煞
	伤敌气血，以惊神将一阳指指力送入，敌人体内
	造成内伤并封招闭气，削弱敌人防御和招架，降
	低敌人命中。最后以截天指力点穴使之忙乱。出
	招虽然缓慢，但是一阳指当世无双，威力无比。
	
	perform finger.sandie
	
基本要求：
	一阳指的等级 450  级以上；
	基本指法等级 450  级以上。
	乾天一阳等级 450  级以上，或(枯荣禅功)
	后天臂力要求 60   以上；
	最大内力要求 5000 以上，
	当前内力要求 1500 以上。
	备指法和招架为一阳指。
	
设置内容： 
	set    一阳指   xxxx 
	破煞   效果为提高破煞命中，破煞功效为伤气
	惊神   效果为提高惊神命中，惊神功效为封招闭气
	截天   效果为提高截天命中，截天功效为打内力且让对方busy
	三叠   效果为提高后招一指三脉的几率，相当于三个设置融合
	

HELP
   );
   return 1;
}




