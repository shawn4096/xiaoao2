//dingyang.c 定阳针;
//Modify By jpei
//自一灯处学得定阳针后，需要反复练习才能豁然贯通
//起初标记为try,威力减半
 
#include <ansi.h>
inherit F_SSERVER;
 
string exert_name() {return HBWHT+HIR"定阳针"NOR;}

int exert(object me)
{
        string msg;
        object target;
        int skill, ap, dp, p, force, neili_wound, qi_wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("xiantian-gong",1);
		//count=skill/2;
        if( !(me->is_fighting() ))
                return notify_fail("「定阳针」只能对战斗中的对手使用。\n");

        if((string)me->query_skill_mapped("force") != "xiantian-gong" )
		  return notify_fail("「定阳神针」乃是道家先天功的绝学！\n");

        if( skill < 450)
                return notify_fail("你的先天功修炼不够, 不能使用「定阳针」！\n");

        if( me->query("neili") < 2000 )
                return notify_fail("你的内力不够，无法运用「定阳针」！\n");
		//破了童子身，无法运使定阳针
		if( me->query("marry"))
                return notify_fail("你已经破了童子身，无法运用先天功绝技「定阳针」！\n");
       if( !me->query("quanzhen/force")  )
                return notify_fail("你虽然听说过「定阳针」，但是不知道如何运用。\n");     

       if( me->query("max_neili") < 15000 )
                return notify_fail("你的内力不够，无法运用「定阳针」！\n");
 
       msg = HIY"\n$N默运先天功，以先天真气运用一阳指指法，迎面一指，径直点向$n眉心，正是当年一指点破蛤蟆功的重阳绝技「"HIR"定阳针"HIY"」！。\n"NOR;

         ap = me->query_skill("force",1) + skill;
         dp = target->query_skill("force",1)+ target->query_skill("parry",1);

	   if( dp < 1 ) dp = 1;
  	
       if( me->query("quanzhen/force")=="try" )
        {        ap = ap/4;
    	         msg += HIY"只是$N初学乍练之下，并不能很好的发挥定阳针的威力！\n"NOR;

         if( me->query("kar")<31 && random(me->query("kar"))>28 && random(50)==5 && me->query_skill("xiantian-gong",1)>=450 ){

		      	msg += HBBLU"$N忽然福至心灵，先天功真气由膻中，入缺盆，过阳池外关，交与三焦手少阳之脉，激射而出，豁然贯通！\n"NOR;	     
	           me->set("quanzhen/force","pass");
	          }

        }         
       message_vision(msg, me, target);
      //||random( me->query_skill("force",1)) > target->query_skill("dodge",1)/2 
       if((random(ap) >dp/2)		    
		   ||( me->query("str")>40 && random( me->query("combat_exp",1)) > target->query("combat_exp",1)/2 ) 
		   ||(!userp(target) && me->query("str") >=45) 
		   )
		{

		  if(userp(me))
              me->add("neili",-(500+random(500)));
           msg = HIM"\n$n不及躲闪，被$N一指点中！只觉得先天真气透体而入，沛然浩瀚，莫与之敌。全身功力当即被封，当下骇的魂飞魄散！\n" NOR;   
           message_vision(msg, me, target);
      
           p = (int)me->query_skill("force") + random(me->query_skill("force")*3);
   
           force = target->query_skill_mapped("force");
 	     switch(force) {
		    case "huntian-qigong":
			if( intp(p = target->query_temp("htqg/powerup")) ){
				target->add_temp("apply/armor", - p*2);
				target->add_temp("apply/dodge", - p);
				target->delete_temp("htqg/powerup");
				tell_object(target, HIR"你被定阳针指力点中，护体神功被点破，混天气功的效果自然消失了！\n"NOR);
				break;
			}
		case "xixing-dafa":
			if( intp(p = target->query_temp("xxdf/xixing")) ){
				target->add_temp("apply/attack", - p);
				target->add_temp("apply/dexerity", - p/10);
				target->delete_temp("xxdf/xixing");
				tell_object(target, HIR"你被定阳针指力点中，护体神功被点破，吸星大法的效果自然消失了！\n"NOR);
				break;
			}

		case "xiantian-gong":
			if( intp(p = target->query_temp("xtg/wuqi")) ){
				target->add_temp("apply/armor", - p/5);
				target->add_temp("apply/strike", - p/10);
                                target->add_temp("apply/attack", - p /10);
				target->delete_temp("xtg/wuqi");
				tell_object(target, HIR"你被定阳针指力点中，护体神功被点破，五气朝元的效果自然消失了！\n"NOR);
				break;
			}
		case "bahuang-gong":
			if( intp(p = target->query_temp("bhg/duzun")) ){
				target->add_temp("apply/armor", - p/5);
				target->add_temp("apply/hand", - p/10);
				target->add_temp("apply/attack", - p*5 /10);
				target->delete_temp("bhg/duzun");
				tell_object(target, HIR"你被定阳针指力点中，护体神功被点破，八荒功唯我独尊效果自然消失了！\n"NOR);
				break;
			}
		case "beiming-shengong":
			if( intp(p = target->query_temp("bmsg/bm")) ){
				target->add_temp("apply/armor", - p/5);
				target->add_temp("apply/attack", - p/5);
				target->add_temp("apply/intelligence", - p/10);
				target->add_temp("apply/dexerity", - p /10);
				target->delete_temp("bmsg/bm");
				tell_object(target, HIR"你被定阳针指力点中，护体神功被点破，北冥真气的效果自然消失了！\n"NOR);
				break;
			}
		case "huashan-qigong":
			if( intp(p = target->query_temp("hsqg/yjs")) ){
				target->add_temp("apply/attack", - p/2);
				target->delete_temp("double_attack");
				target->delete_temp("hsqg/yjs");
				tell_object(target, HIR"你被定阳针指力点中，护体神功被点破，真气不足，驭剑式效果自然消失了！\n"NOR);
				break;
			}
		case "zixia-gong":
			if( target->query_temp("zxg/zixia") ){
				target->delete_temp("double_attack");
				target->delete_temp("zxg/zixia");
				tell_object(target, HIR"你被定阳针指力点中，护体神功被点破，真气不足，紫霞聚力效果消失了！\n"NOR);
				break;
			}

		case "yijin-jing":
			if( intp(p = target->query_temp("fanzhen")) ){
				target->add_temp("apply/armor", - p);
				target->add_temp("apply/parry", - p);
				target->add_temp("apply/attack", - p);
				target->delete_temp("fanzhen");
				target->delete_temp("no_skill_hit_ob");
				                                                      target->add("neili", -p*100);
				tell_object(target, HIR"你被定阳针指力点中，护体神功被点破,「金刚不坏体神功」的效应也相应地消失了！\n"NOR);
				break;
			}
		case "jiuyang-gong":
			if( intp(p = target->query_temp("jiuyang/powerup")) ){
	                                        target->add_temp("apply/attack", - p);
	                                        target->add_temp("apply/dexerity", - p/10);
                                                      target->add_temp("apply/armor", - p/4);
                                                      target->delete_temp("fanzhen");  
                                                      target->add("neili", -p*100);
	                                        target->delete_temp("jiuyang/powerup");
				tell_object(target, HIR"你被定阳针指力点中，护体神功被点破,「九阳神功」的效应也相应地消失了！\n"NOR);
				break;
			}
		case "linji-zhuang":
			if( target->query_temp("ljz/riyue") ){
				target->delete_temp("ljz/riyue");
				tell_object(target, HIR"你被定阳针指力点中，护体神功被点破,「日月」庄所聚天地之精气已散回日月之间！\n"NOR);
				break;
			}
			if( intp(p = target->query_temp("ljz/yinyang")) ){
				target->add("max_qi", - p);
				target->receive_wound("qi", p, "「阴阳」庄被破，脱力而");
				target->delete_temp("ljz/yinyang");
				tell_object(target, HIR"你被定阳针指力点中，护体神功被点破,「阴阳」庄提升的效应也消失了！\n"NOR);
				break;
			}
			if( intp(p = target->query_temp("ljz/fengyun")) ){
				target->add_temp("apply/dexerity", - p);        
				target->delete_temp("ljz/fengyun");
				tell_object(target, HIR"你被定阳针指力点中，护体神功被点破,「风云」庄效果消失，略觉步履沉重了一些。\n"NOR);
				break;
			}
			if( target->query_temp("ljz/wuwo")){
				target->delete_temp("ljz/wuwo");
				tell_object(target, HIR"你被定阳针指力点中，护体神功被点破,「无我」心法被破，又恢复了原来的你！\n"NOR);
				break;
			}
		case "yinyun-ziqi":
			if( target->query_temp("tj/太极") ){
				target->delete_temp("tj/太极");
				tell_object(target, HIR"你被定阳针指力点中，护体神功被点破,慌忙之中，太极不能连贯而行，效应也消失了！\n"NOR);
				break;
			}
		case "dulong-dafa":
			if( intp(p = target->query_temp("sld/wudi2") ) ){
				target->add_temp("apply/strength", -p/20);  
				target->add_temp("apply/attack", -p/3);
				target->delete_temp("double_attack");
				target->delete_temp("sld/wudi2");
				if(target->query("eff_qi") > target->query("max_qi")) 
					target->set("eff_qi", target->query("max_qi"));
				tell_object(target, HIR"你心神一松，再也支持不住了！！\n"NOR);
				break;
			}
		           if( intp(p = target->query_temp("sld/wudi1")) ){
				target->add_temp("apply/strength", -p/20);
				target->add_temp("apply/attack", -p/4);
				target->delete_temp("sld/wudi");
				target->delete_temp("sld/wudi1");
				if(target->query("eff_qi") > target->query("max_qi")) 
					target->set("eff_qi",target->query("max_qi"));
				tell_object(target, HIR"你心神一松，好象虚脱了一样，突然垮了下来！！\n"NOR);
				break;
			}
		case "hanbing-zhenqi":
			if ( intp(p = target->query_temp("hbzq/huti")) ){
				target->add_temp("apply/parry", -p);
				target->add_temp("apply/dodge", -p);
				target->delete_temp("hbzq/huti");
				tell_object(target, HIR"你周身的寒气散尽，不再能起到保护的作用了。\n"NOR);
				break;
			}
			if( target->query_temp("ss/focus")){
				target->delete_temp("ss/focus");
				tell_object(target, HIR"你护体真气被定阳针点破，周身的寒气渐渐的散去了。\n"NOR);
				break;
			}
			if( target->query_temp("ss/hb")){
				target->delete_temp("ss/hb");
				tell_object(target, HIR"你护体真气被定阳针点破，手上的寒气渐渐的散去了。\n"NOR);
				break;
			}
		case "huagong-dafa":
			if( intp(p = target->query_temp("hgdf/judu")) ){
				target->add_temp("apply/armor", -p);
				target->delete_temp("hgdf/judu");
				tell_object(target, HIR"你护体真气被定阳针点破，心神一松，所聚毒素全都垮了！！\n"NOR);
				break;
			}
			else if( intp(p = target->query_temp("hgdf/huadu")) ){
				target->add_temp("apply/dodge", -p); 
				target->add_temp("apply/armor_vs_force", -p/2);           
				target->delete_temp("hgdf/huadu");
				tell_object(target, HIR"你护体真气被定阳针点破，心神一松，化毒所聚毒素全都垮了！！\n"NOR);
				break;
			}
		case "yunu-xinjing":
			if( target->query_temp("gm/xinjing") ){
				p  = target->query_temp("gm/xinjing");
				target->add_temp("apply/intelligence", -p/10);
				target->add_temp("apply/dexerity", -p/10);
				if ( target->query_skill("yunu-xinjing", 1) > 200 ){
					target->add_temp("apply/attack", -p/5);
                                                                      target->add_temp("apply/damage", -p/8);
					if ( target->query("gender") == "女性") {
						target->add_temp("apply/dodge", -p/10);
						target->add_temp("apply/parry", -p/10);
						target->add_temp("apply/armor", -p/10);
					}
					if ( target->query("gender") == "男性") {
						target->add_temp("apply/strike", -p/10);
						target->add_temp("apply/parry", -p/10);
						target->add_temp("apply/armor", -p/10);
					}
				}
				target->delete_temp("gm/xinjing");
				tell_object(target, HIR"你被定阳针指力点中，护体神功被点破,「心经」字决效应也消失了！\n"NOR);
				break;
			}
		case "shenyuan-gong":
			if ( intp(p = target->query_temp("shenyuan")) ){
				target->add_temp("apply/parry", -p/3);
				target->add_temp("apply/dexerity", -p/20);
				target->delete_temp("shenyuan");
				tell_object(target, HIR"你护体真气被定阳针点破，防守招式已经减弱了。\n"NOR);
				break;
			}
		case "xuantian-wuji":
			if ( intp(p = target->query_temp("kl/riyue")) ){
				target->add_temp("apply/parry", -p/2);
				target->add_temp("apply/armor", -p/2);
				target->delete_temp("kl/riyue");
				tell_object(target, HIR"你护体真气被定阳针点破，无极真气无法起到保护作用了。\n"NOR);
				break;
			}
			if ( intp( p = target->query_temp("kl/taxue")) ) {
				target->add_temp("apply/dodge", -p);
                                                        target->add_temp("apply/dexerity", -p);
				target->delete_temp("kl/taxue");
				tell_object(target, HIR"立定了脚步，身法回复了正常！\n"NOR);
				break;
			}
		case "longxiang-boruo":
			if ( intp(p = target->query_temp("xs/shield")) ) {
				target->add_temp("apply/dodge", -p);
				target->add_temp("apply/armor", -p*2);
				target->delete_temp("xs/shield");
				tell_object(target, HIR"你护体真气被定阳针点破，脸上红光一闪，骨节啪啪轻响几声，散去了护体真气。\n" NOR);
				break;
			}
			if ( intp(p = target->query_temp("xs/longxiang")) ) {
				target->add_temp("apply/attack", -p);
				target->delete_temp("xs/longxiang");
				tell_object(target, HIR"你护体真气被定阳针点破，脸上紫气一闪，又恢复如常。\n" NOR);
				break;
			}
		case "qiantian-yiyang":
			if( intp(p = target->query_temp("dali_jing")) ){
				target->add_temp("apply/intelligence", -p);
				target->delete_temp("dali_jing");
				tell_object(target, HIR"你护体真气被定阳针点破，无法继续潜修了。\n" NOR);
				break;
			}
		case "guiyuan-tunafa":
			if ( intp(p = target->query_temp("tz/focus")) ){
				target->add_temp("apply/attack", p);
				target->add_temp("apply/strength", p);
				target->delete_temp("tz/focus");
				tell_object(target, HIR"你护体真气被定阳针点破，精神有些委顿，力道随即恢复常态。\n"NOR);
				break;
			}
		case "kurong-changong":
			if( intp(p = target->query_temp("krcg_kurong")) ){
				target->delete_temp("krcg_kurong");
				target->add_temp("apply/armor", -p);
				target->add_temp("apply/parry", -p);
				tell_object(target, HIR"你护体真气被定阳针点破，「枯荣」大法立刻消散了！\n" NOR);
				break;
			}	

			case "hamagong":
             if( intp(p = target->query_skill("hamagong",1)) && target->query("oyf/hamagong",1)<3 ){

				target->start_busy(p/10);
				target->add_temp("apply/force", -p);
				target->add_temp("apply/damage", -p);
								target->add_temp("apply/attack", -p);
								target->add_temp("apply/dodge", -p);
								target->add_temp("apply/parry", -p);
							   target->add("neili", -p*200);
				tell_object(target, HIR"定阳针乃蛤蟆功克星，你全身功力顿时尽失！\n" NOR);
				break;
		      }
              if( target->query_temp("hmg_nizhuan") && target->query("oyf/hamagong",1)==3 ){

                 message_vision(HIW "\n$n已然将九阴真经逆练成功，全身经脉逆转，杂乱无序，$N一指点去，只觉得如中败革，\n"
				  +"点中的位置正确，但因$n经脉错乱，先天真力如泥牛入海，丝毫不起作用。\n" NOR, me,target);
				break;
		       	}
				
		case "bihai-chaosheng":
			if( intp(p = target->query_temp("thd/maze")) ){
				target->delete_temp("thd/maze");
				target->add_temp("apply/dexerity", -p/10);
				target->add_temp("apply/parry", -p /2);
				target->add_temp("apply/dodge", -p /2);

              target->delete_temp("thd/mazed");
				tell_object(target, HIR"你护体真气被定阳针点破，无暇顾及所布迷阵，结果三下两下就被打散了！\n" NOR);
				break;
			}
          }
                
				qi_wound = ap * 4 +random(ap*2) ;

				neili_wound = ap * 3 +random(ap*3);
                
                if(neili_wound > target->query("neili"))
                   neili_wound = target->query("neili");

                if(qi_wound > target->query("qi"))
                   qi_wound = target->query("qi");
                //蛤蟆功3失效
				if( target->query_temp("hmg_nizhuan") && target->query("oyf/hamagong",1)==3 ){
                    target->add_busy(2+random(1));
					return 1;
				}
        	                       
                else if(random(3)== 1){
                    target->apply_condition("no_perform", 3+ random(3));
					target->apply_condition("no_force", 3+ random(3));
				}
				message_vision(WHT"$n只觉一口真气被$N的先天真气一股脑破掉，全身剧痛，真气乱窜，无法调息！\n"NOR,me,target);
				target->apply_condition("no_exert", 3+ random(3));

                target->set("neili", 0);
                target->add("qi", -qi_wound);
                target->add("eff_qi", -qi_wound*2/3);
                
				message_vision(HIR"定阳针所施展的真气游走在$n的奇经八脉,均处于极度混乱状态，浑身酸痛无比，丝毫动弹不得！\n"NOR,me,target);

				if (!userp(target)) target->add_busy(skill/50);
                else target->add_busy(skill/100);
				//破防御
				message_vision(HBYEL+HIR"$n觉得快要死了般的极度虚弱，大口地喘气！\n"NOR,me,target);

				target->set_temp("xtg/dingyang",skill);
				target->add_temp("apply/attack",-skill);
				target->add_temp("apply/parry",-skill);
				target->add_temp("apply/dodge",-skill);
				target->add_temp("apply/defense",-skill);
				call_out("dy_recover",(int)skill/10,me,target);
                
				me->start_exert(5,"定阳针");
				//me->start_perform(1,"定阳针");

		   } else
              { 
                msg = YEL"\n$n只觉得$N指力透体而入，先天真气沛然浩瀚，莫与之敌。当下只得飞身后退！\n" NOR;
                message_vision(msg, me, target);
                if (me->query("quanzhen/force") =="pass" )
			       target->add_busy(2);
		        me->add_busy(1);
		        me->start_exert(3+random(2),"定阳针");

			 }

        return 1;

}
int dy_recover(object me,object target)
{
	int skill;
	if (!target) return 0;
	//if (!me) return 0;
	skill=target->query_temp("xtg/dingyang");
	
	target->add_temp("apply/attack",skill);
	target->add_temp("apply/parry",skill);
	target->add_temp("apply/dodge",skill);
	target->add_temp("apply/defense",skill);
	return 1;
}
int help(object me)
{
	write(HIC"\n先天功之「定阳针」绝技："NOR"\n");
	write(@HELP
	先天真气之「定阳针」绝技：
	全真教王重阳号称五绝中【中神通】，一身功力以至化境，
	凭借的就是两大绝技，其一为全镇七星剑法，其二为先天
	功。甚至先天功的威力能起到决定性的作用，五绝华山论
	剑，东邪、西毒、南帝、北丐都对王重阳的先天功佩服的
	五体投地。尤其是对于西毒欧阳锋的蛤蟆功更是有明显的
	克制功效。定阳针乃当年一指点破西毒欧阳锋蛤蟆功的重
	阳绝技，以先天真气驱动一阳指指力，点破敌人护体真气。
	端的是厉害非常，号称克制天下所有内功。不过当后来欧
	阳锋逆练九阴真经，先天功的克制作用才逐渐失效。

	注意：先天功「定阳针」绝技需童子之身方可修习。

	指令：exert dingyang
	
要求：	
	当前内力需求 2000  以上；
	最大内力需求 15000 以上；
	先天功的等级 450   以上；
	得到王重阳先天功真传的弟子可以使用。
	必要条件需童子之身。
	高的臂力和内功等级有额外的效果。 

HELP
	);
	return 1;
}

