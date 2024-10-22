// write by snowman@SJ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
int check_pfm(object me, object target,object ob);
int remove_effect(object me);

int perform(object me, object target)
{
      	object ob;
		int skill;
        if( !target ) target = offensive_target(me);
		skill=me->query_skill("chousui-zhang",1);
        if( !objectp(target)
        || !target->is_character()
        || !me->is_fighting(target)
        || !necessary(target) )
                return notify_fail("「火球」攻击只能对战斗中的对手使用。\n");
      
      	if( (int)me->query("max_neili") < 2500 ) 
                return notify_fail("你发现自己内力太弱，无法驱动「火球」进行攻击。\n");
		if( (int)me->query("neili") < 1200 ) 
                return notify_fail("你发现自己内力不足以驱动「火球」进行攻击。\n");
        if( (int)me->query_skill("huagong-dafa",1) < 250 )
                return notify_fail("你发现自己的化功大法修为不够，无法使用「火球」进行攻击。\n");
        if( (int)me->query_skill("poison",1) < 150 )
                return notify_fail("你发现自己体内聚毒不够，无法使用「火球」进行攻击。\n");
        if( (int)me->query_skill("chousui-zhang", 1) < 250 )
                return notify_fail("你发现自己的星宿毒掌还不够娴熟，无法使用「火球」进行攻击。\n");
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能使用「火球」！\n");        
        if( !objectp(ob = present("huo yan", environment(me))) )
                return notify_fail("没有火堆怎么驱动「火球」进行攻击？\n");
        if( me->query_temp("csz/huoqiu") )
                return notify_fail("你正在驱动火堆进行攻击！\n");
		if(me->query_temp("csz/yinhuo"))
                return notify_fail("你正在驱动「银火」进行攻击！\n");
		if(me->query_temp("csz/huoqiang"))
                return notify_fail("你正在驱动「火墙」进行攻击！\n");

       message_vision(CYN"\n$N厉声大喝，掌力加盛，火焰中突然生出一个斗大的"HIR"火球"CYN"，在空中骨碌碌的迅速转动！\n\n"NOR,me);
      
        me->start_busy(2);
       me->set_temp("csz/huoqiu", 1);
	   me->add("neili",-200);
	   if (objectp(target)&&me->is_fighting()) {
		    message_vision(CYN"\n$N劲气汹涌，以内力御使这个"HIR"火球"CYN"向$n飞速攻去！\n\n"NOR,me,target);		    
	       call_out("check_pfm", 2, me, target, ob);
	   }
       else remove_effect(me);
	   return 1;
}
int remove_effect(object me)
{
           	message_vision(HIY"$N衣袖再拂，将升起的"RED"火球"HIY"压回火焰之中。\n"NOR,me);
			me->delete_temp("csz/huoqiu");
           	return 1;

}

int check_pfm(object me, object target,object ob)
{
        string msg, *limbs;
        int i, neili, ap, dp, damage, p;
        object *inv;
        

        //me->delete_temp("pfm_chousui");
        if (!living(me) )
        {
           	message_vision(HIY"$N一跤跌倒，昏迷不醒，将升起的"RED"火球"HIY"压在身下。\n"NOR,me);
			me->delete_temp("csz/huoqiu");
			return 1;
        }
        if( me->is_ghost()||!me ) return 0;
        
        if(!target 
        //|| !living(target) 
        || !me->is_fighting()
        || environment(me)!=environment(target)){
           	message_vision(HIY"$N衣袖再拂，将升起的"RED"火球"HIY"压回火焰之中。\n"NOR,me);
			me->delete_temp("csz/huoqiu");
           	return 1;
        }  
        
        i = (int)me->query_skill("chousui-zhang", 1);
        neili = (int)me->query("neili");
        //me->start_busy(2+random(2));
        
        if(!objectp(present(ob, environment(me)))){
           	message_vision(HIY"$N眼看火堆熄灭，散开内息，放下举起的双手。\n"NOR,me);
			me->delete_temp("csz/huoqiu");
           	return 1;
        }
        if (me->query_skill_prepared("strike") != "chousui-zhang"
        || me->query_skill_mapped("strike") != "chousui-zhang"
        || me->query_skill_mapped("parry") != "chousui-zhang"){
                tell_object(me,"你必须用抽髓掌才能使用「火球」进行攻击。\n"); 
				me->delete_temp("csz/huoqiu");
                return 1;
        }                                                                                
        if( me->query_skill_mapped("force") != "huagong-dafa"){
                tell_object(me,"你发现自己所用的内功无法进行「火球」攻击。\n");
				me->delete_temp("csz/huoqiu");
                return 1;
        }
        if(neili < 1000){
                tell_object(me,"你发现自己现在真气太弱，使不出「火球」进行攻击。\n");
				me->delete_temp("csz/huoqiu");
                return 1;
        }           
              
       
		ap = me->query_skill("chousui-zhang",1);
		dp = me->query_skill("parry",1);
        
		if(objectp(target)&&!userp(target))
        	dp /= 3;
        if (ap < 1) ap = 1;
        if (dp < 1) dp = 1;
        me->add("neili", -600);
        me->add("jingli", -100);
		damage = ( i + me->query("jiali") ) * 15;
		if(userp(target)) damage = damage*2/3;
		if( ap < dp ) damage -= random(damage/3);
		if( ap > dp ) damage += random(damage/3);
	
        msg = WHT"\n此时$N脸上已无半点血色，一口口鲜血不住向"RED"火球"WHT"中吐去!\n"HIR"刹那间,火势一盛，嗤嗤两声轻响，"
"爆出几朵火花，"RED"火球"WHT"陡然变大向$n疾冲过来！\n"NOR;

       
        if(random(ap+dp) > dp*4/5
			||random(me->query_str())>target->query_str()/2)
		{
       		target->add_condition("xx_poison", 3);
			if (userp(me) && userp(target) && me->query_condition("killer") < 15)
				me->apply_condition("killer", 15);
			if(!target->is_busy())
                target->add_busy(1);
          	//inv = check_armor(all_inventory(target));
          	inv = filter_array(all_inventory(target),(:$1->query("equipped")=="worn":));
			inv -= ({0});
          	//破甲
			if( sizeof(inv) >= 1 ){     
            		if( neili > random(target->query("neili"))*2){
               			if( me->query_str()/3*2 > random(target->query_str()) ){
                  			msg += HIY"猛烈间火球温度飙升，火花迸射，炸开了$p的护具！\n" NOR;
                  			damage += random(damage)*2;
                  			damage -= target->query_temp("apply/armor");
                  			for(i=0; i<sizeof(inv); i++){
                     				inv[i]->unequip();
                         			inv[i]->move(environment(target));
                         			inv[i]->set("name", "粉碎的" + inv[i]->query("name"));
                         			inv[i]->delete("value");
                         			inv[i]->set("armor_prop", 0);
                         		}     
                  		}                   
            			else {
                  			msg += HIY"只见火球猛然升温，火花四溅，热力直透$p的护具！\n" NOR;
                  			damage += random(damage);
                  			damage -= target->query_temp("apply/armor");
                  			for(i=0; i<sizeof(inv); i++){
                     				inv[i]->set("name", "碎裂的" + inv[i]->query("name"));
                        			inv[i]->set("value", 49);
                         			if(inv[i]->query("armor_prop/armor"))
                             				inv[i]->set("armor_prop/armor", inv[i]->query("armor_prop/armor")/2);
                        		}
                  		}
                  		target->reset_action();     
               		}
          			else {
                  		msg += HIY"火球急速滚动，火光四溅，掀起阵阵火焰撞向$p怀里！\n" NOR;
                  	}
				//破甲后顺带破气
                  	target->receive_damage("qi", damage, me);   
                  	target->receive_wound("qi", damage/3, me);  
				if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR);
			
	if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR); 
			}            	
        	else{
                //target has no armor, so, hehe...
                	if( neili > target->query("neili")/2*3 )
                		damage += random(damage);
                	else if( neili < target->query("neili")/3*2 )
                		damage -= random(damage/2);
                	else if( neili > target->query("neili")*2 ) 
                		damage *= 3;
                	damage += random(damage);
                	target->receive_damage("qi", damage, me);   
                	target->receive_wound("qi", damage/3, me);
                    if(userp(me) && me->query("env/damage"))
						tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR);
					
if(userp(target)&& target->query("env/damage"))
						tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR);           }
                p = (int)target->query("qi")*100 / (int)target->query("max_qi");
                msg += damage_msg(damage, "砸伤");
               	msg += "( $n"+eff_status_msg(p)+" )\n";
               	limbs = target->query("limbs");
       		    msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
       		    msg = replace_string(msg, "$w", RED"火球"NOR);   
        }        
    	else{
    		if(!target->is_busy())
        		target->start_busy(1);
        	msg += HIY"\n$p眼看就要被打中，冒死一个“铁板桥”，全身自膝盖处向后倒去，堪堪避过火球"HIY"！\n" NOR;
        }
            
       	message_vision(msg, me, target);
       	if( userp(target)&&!target->is_killing(me->query("id")) ) target->kill_ob(me);
		me->delete_temp("csz/huoqiu");
		me->start_perform(3,"火球");
       	return 1;
} 


string perform_name(){ return HIR"火球"NOR; }
int help(object me)
{
        write(HBBLU"\n抽髓掌之「火球」："NOR"\n\n");
        write(@HELP
	星宿派的功夫主要是在<毒>字上下功夫，深的阴损毒辣其中三味
	抽髓掌乃是在战斗中，凭借深厚内功把体内存毒逼出借以伤敌的
	一门功夫。「火球」绝技专破对方防具，顺带伤气，甚难防御！
	
	指令：perform strike.huoqiu

要求：  
	当前内力需求 1000 以上;
	最大内力需求 2500 以上；
	抽髓掌法等级 250 以上；
	化功大法等级 250 以上；
	基本掌法等级 250 以上；
	基本内功等级 250 以上;
	且手中无兵器。        
HELP
        );
        return 1;
}
