//yiyang-zhi's perform qianlong
//潜龙勿用
//COOL@SJ,20000401

#include <ansi.h>
inherit F_SSERVER;
void yyzql_attack(object me,object target,int count);
 
int perform(object me, object target)
{       
        string msg;
        int skill,ap,dp;
		skill=me->query_skill("yiyang-zhi",1);
        
		if( !target ) target = offensive_target(me);
		
		if( !target 
         || !target->is_character()
         || !present(target,environment(me)) )
                return notify_fail("「潜龙勿用」？\n");
        if( !living(target) )
        	return notify_fail("对方已经晕过去了。\n");
		if( !me->is_fighting(target) )
 				return notify_fail("你只能对战斗中的对手出「潜龙勿用」。\n"); 
 		//压制，虚弱
		if( target->query_temp("yyz_ql/recive") )
 			return notify_fail("这人已经承受不下你的「潜龙勿用」功力了。\n"); 
 		
            
        if( me->query_temp("weapon") )
                return notify_fail("只有空手才能施展「潜龙勿用」。\n"); 

        if( (int)me->query_skill("yiyang-zhi", 1) < 300 ||
            (int)me->query_skill("finger", 1) < 300 )
                return notify_fail("你有的功夫还不够娴熟，不会使用「潜龙勿用」。\n");

        if(!me->query_skill("kurong-changong", 1))
           	if(me->query_skill("qiantian-yiyang", 1) < 300)
                	return notify_fail("以你现在的内功修为还使不出「潜龙勿用」。\n");        
         
        if (me->query_skill_mapped("force") != "kurong-changong" )
            	if (me->query_skill_mapped("force") != "qiantian-yiyang")
                	return notify_fail("你所使用的内功不对。\n");

        if (me->query_skill_prepared("finger") != "yiyang-zhi"
			|| me->query_skill_mapped("parry") != "yiyang-zhi"
           || me->query_skill_mapped("finger") != "yiyang-zhi" )
                return notify_fail("你现在无法使出「潜龙勿用」进行攻击。\n");                                                                                 
      
        if( (int)me->query("max_neili") < 4000 )
                return notify_fail("你的最大内力修为太弱，不能使用「潜龙勿用」！\n");
		if( (int)me->query("neili") < 1000 )
                return notify_fail("你的当前内力修为太弱，不能使用「潜龙勿用」！\n");
		if( (int)me->query("jingli") < 1000 )
                return notify_fail("你的当前精力修为太弱，不能使用「潜龙勿用」！\n");
   		if (me->query_temp("yyz_ql"))
				return notify_fail("你正在使用「潜龙勿用」绝技。\n"); 
    
 		message_vision(HBGRN+HIW"\n$N体内真气流转不绝，一阳指劲力开始蓄积，正在大理一阳指绝技「潜龙勿用」的招式。\n"NOR,me);
	
        
        if ((string)me->query("class")=="bonze")
         	message_vision(WHT "\n$N忽然低唤了一声："+target->name()+WHT"`~~~~`,声音犹似在千重梦魔浮沉中气若游丝地传来。\n"NOR,me,target);    
		else message_vision(WHT "\n$N忽然大喝一声："+target->name()+WHT",声音犹似晴空霹雳，震的$n双耳”嗡嗡“做响。\n"NOR,me,target); 
     
        me->set_temp("yyz_ql",skill);
		
		me->add("neili",-100-random(1000));
        me->add("jingli",-100-random(500));
       	

		message_vision(HBWHT+HIR"$N这一指，耗尽了大量的元气，只觉的自己疲弱之极，整个人就像一株突然枯了的朽木一般。\n"NOR,me);
		
        //目标调用脱离程序。
		call_out("yyzql_attack",1,me,target,(int)skill/100);
		
		if ((int)me->query("yyz/degree")>4 && me->query_skill("yiyang-zhi",1)<450)
        {
			me->start_perform(2,"潜龙勿用");
        }
		/*else
			me->start_perform(1,"潜龙勿用");
			*/
       	
		return 1;
}
//主控制程序

void yyzql_attack(object me,object target,int count)
{
	int skill,damage,ap,dp;
	if (!me) return;
	skill=me->query_skill("yiyang-zhi",1);
	damage=skill+me->query_skill("qiantian-yiyang",1)+me->query_skill("buddhism",1);
	damage=damage*2+random(damage);
	ap=me->query("combat_exp")/100000;
    //离开程序
	if (count<0
		||!objectp(target)
		|| !me->is_fighting(target)
		|| me->query_temp("weapon")
		|| me->query_skill_mapped("finger")!="yiyang-zhi")
	{	
		
		me->delete_temp("yyz_ql");
		message_vision(HIC"\n\n$N吐出一口浊气，面色呈苍白之色，显然方才这一招耗费不少精力。\n"NOR,me);
		me->add_busy(2);
		me->add("neili",-600);
		me->add("jingli",-400);
		me->start_perform(4,"潜龙勿用");
		return;
	}
	dp=target->query("combat_exp")/100000;
    
	


	
	switch (random(5))
	{
		case 0:
			//随机攻击一招
			message_vision(HIR"$N眼见$n下意识的格挡，嘿然一笑，顺手连点$n任脉，将$n前身七十二个大穴都笼罩在指风中。\n"NOR,me,target);
		    message_vision(CYN "$n受伤极重，急忙竭力抵挡，突然之间，$n眉心穴一阵滚热，自玄关热流直沉任脉，\n"
						+"而照流连接督脉，两股异流迅速周折一大周天后，在带脉合流为一，在冲脉化流为劲，\n"
						+"$N本来一招即出，竟中途易招为指“嗤”的一声，指风破空而出！\n\n"NOR, me,target);     
			target->add_busy(2);
			me->add_temp("apply/finger", skill/3);
			me->add_temp("apply/damage", skill/3 );
			target->set_temp("must_be_hit",1);
			COMBAT_D->do_target(me, target, 0, userp(me)?3:1);
			target->delete_temp("must_be_hit");
			me->add_temp("apply/finger", -skill/3);
			me->add_temp("apply/damage", -skill/3);
			break;
		case 1:
			//破防
			message_vision(HIR"$N一阳指劲气一旦接触了$n的穴位，宛如春雪化泥，立即融入到$n周身经络，游走不息。\n"NOR,me,target);
			
			if (random(me->query_int(1))>target->query_int(1)/2 && !target->query_temp("yyz_ql/recive"))
			{
				message_vision(HIY"$n中了这一指，顿觉浑身酸麻，有气无力，周身发软，气喘吁吁。\n"NOR,me,target);
				target->add_temp("apply/dodge",-skill/3);
				target->add_temp("apply/defense",-skill/3);
				target->add_temp("apply/attack",-skill/2);
				target->set_temp("yyz_ql/recive",skill);
				//不能出pfm
				target->apply_condition("no_perform",2);
				call_out("yyzql_back",skill/30,target);
			}else{
				message_vision(HIW"$n暗自咬了自己舌尖，保持清醒状态，猛然间向旁躲开。\n"NOR,me,target);

			}
			break;
		case 2:
			//破内力，内伤发作
			
			//call_out("yyzql_target2");
			message_vision(RED"$N猛喝一声，一阳指劲力汹涌澎湃，$n只觉这股劲力立即侵入到自己丹田之中。\n"NOR,me,target);
			if (random(me->query_skill("force",1))>target->query_skill("force",1)/2
				||random(me->query("neili"))>target->query("neili")/2)
			{
				message_vision(HBRED+HIW"这股怪异的内力进入$n的丹田后，仿佛被点燃了似得，$n只觉自己内力四处游走，经脉酸涨欲裂。\n"NOR,me,target);
				target->apply_condition("no_exert",1+random(3));
				target->set("jiali",0);
				if (damage>target->query("neili"))
				{
					target->add("neili",-(int)target->query("neili")/2);
				}else
					target->add("neili",-damage);
				message_vision(HIY"$n显然收了一阳指的内伤，哇的吐了一口鲜血！\n"NOR,me,target);
				target->receive_wound("qi",damage/3,me);
				target->apply_condition("yyz_hurt",2+random(2));
				
			}else {
				message_vision(HIG"$n略微受了点内伤，暗自一口真气流转，化解了$N的这招奇袭！\n"NOR,me,target);
				me->add_busy(1);

			}
			break;
		case 3:
			//破精力，伤精
			message_vision(HIW"$n只觉眉心印堂间有一股力量像要把自己的双眉撕裂一般。\n"NOR,me,target);

			message_vision(WHT "$n征了一怔，下意识间$n忽一举袖，刹那间掌心向外，拦在额前,却听见“波”的一声，$N一指击在了$n的手心。\n"NOR, me, target);

			if( random(me->query_skill("finger",1))>target->query_skill("parry",1)/2
				||random(ap)>dp/2)
			{
        		if (random(target->query("kar"))<15 && !userp(target))
				{
					message_vision(YEL"$n虽然用手掌挡住了$N的这一指，但一股热流仍自掌背迅速侵入眉心，宛如利剑，$n只觉头晕脑涨，眼前一黑。\n"NOR,me,target);
					target->unconscious();
					
				}
				
        		target->receive_damage("jingli",1000+random(3000),me);
				target->receive_damage("jing",500+random(2000),me);
				target->add_busy(2);
        		//
        		me->add("neili",-random(1000));
        		me->add("jingli",-random(500));
			}else {
				message_vision(HIY"$N这一指击中，劲力源源不断的输入，却发现$n丹田空空如也，$N大吃一惊，慌忙中止了这一式。\n"NOR,me,target);
				me->add_busy(1);
			}
			break;
		case 4:

			if(random(2))
			{
     			message_vision(HIY "\n\n$n见到$N忽然使出一招一阳指，精妙绝伦，指风本来甚为轻微，一旦遇自己的护身真气，骤改为锐劲，“波”地一声，\n"+
                "戳破而入，$n一怔之下，指风已直逼眉心，$n错手不及，被一击命中。\n"NOR, me, target);   
         		target->apply_condition("no_exert", target->query_condition("no_exert") + 5);
			} else
			{
                message_vision(WHT "\n$n见到$N忽然使出一招一阳指，精妙绝伦，指风本来甚为轻微，一旦遇自己的护身真气，骤改为锐劲，\n"+
											"“波”地一声，戳破而入，$n一怔之下，指风已直逼眉心，$n应变奇速，左掌叠在右掌之后，右掌掌心外吐\n"+
											"左掌掌背格在额前，“啪”的一声，指风射人他掌心内。$n右掌已运聚全力，抗拒指风，左掌又加以支撑，\n"
											+"但那一缕指风，连闯三关，所发的破空之声一次比一次更烈，仍然有一小部分内劲透进眉心要穴。\n"NOR, me, target);        
                target->apply_condition("no_exert", target->query_condition("no_exert") + 3);
                target->apply_condition("no_perform", target->query_condition("no_perform") + 3);
				target->receive_damage("qi",damage,me);
			}

   
			if ((int)random(me->query("neili"))>(int)target->query("neili")/2)
			{
	         	message_vision(RED "$n虽然用手掌挡住了这一指，但一股热流仍自掌背迅速侵入眉心，$n只觉头晕脑涨,一阵眩晕。\n"NOR,me,target);
        		target->receive_damage("qi",damage,me);
        		target->receive_wound("qi",damage/3,me);
   
        		message_vision( HIY"$N一指击中，劲力源源不断的输入，一波又一波的攻击袭来，汹涌澎湃。\n"NOR,me);
        		me->add("neili",-random(2000));
        		me->add("jingli",-random(1000)); 
        		
			}
	
			break;
	
	 }
	

	call_out("yyzql_attack",1,me,target,count-3);

}




//潜龙恢复防御
void yyzql_back(object target)
{
	int skill;
	if (!target) return;
	skill=target->query_temp("yyz_ql/recive");
	
	message_vision(WHT"$N长吁一口气，体内不断蓄积的那股一阳指气流满满消散了！\n"NOR,target);
	target->add_temp("apply/dodge",skill/3);
	target->add_temp("apply/defense",skill/3);
	target->add_temp("apply/attack",skill/2);
	target->delete_temp("yyz_ql/recive");
	return;
}
string perform_name() {return HIC"潜龙勿用"NOR;}

int help(object me)
{
   write(HIY"\n一阳指之「"HIC"潜龙勿用"WHT"」："NOR"\n\n");
   write(@HELP
	
	潜龙勿用，乃是大理国一阳指绝技，施展一阳指劲力后，若打中对
	则对方初时感觉不到，但当一阳指劲力在对方体内释放后，对方会
	短时间内流失大量内力和精力，不过因为此功法属于内功克敌的招
	式，因此自己也损耗大量内力，对方若是功力太弱，若中可能出现
	立即昏迷的现象。慎之慎之。一阳指修炼到四品后大飞。

	指令：perform finger.qianlong

要求: 
	最大内力需求 4000 点以上；
	当前内力需求 1000 点以上；
	当前精力需求 1000 点以上；
	一阳指的等级 300 以上；
	基本内功等级 300 以上；
	特殊内功等级 300 以上；
	激发指法为一阳指；
	空手，备一阳指。

HELP
   );
   return 1;
}
