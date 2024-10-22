// poqi.c 破气式
// 继续完善门派的exert种类 By Jpei
// 谁有空帮我完善下
 
#include <ansi.h>
 
inherit F_SSERVER;
 
string perform_name() {return HIC"破气式"NOR;}

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, p, force, neili_wound, qi_wound,i;

        me->clean_up_enemy();
        target = me->select_opponent();
        
        skill = me->query_skill("dugu-jiujian",1);
        i=skill/50;
        if( !(me->is_fighting() ))
                return notify_fail("「破气式」只能对战斗中的对手使用。\n");
		if( !userp(me))
                return notify_fail("「破气式」只能玩家使用，NPC无效。\n");
 
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if( skill < 350)
                return notify_fail("你的独孤九剑等级不够, 不能使用「破气式」！\n");

        if( me->query("neili") < 1000 )
                return notify_fail("你的内力不够，无法运用「破气式」！\n");
		if (target->query_condition("dgjj_poqi"))
			return notify_fail("对方已经中了你的「破气式」！放胆进攻吧\n");
        msg = HIC "$N潜运独孤九剑「"HIG"破气式"HIC"」，运气贯剑使其由利返钝，毫无花俏地直刺$n的丹田。\n"NOR;
        ap = me->query_skill("sword",1) + skill;
        dp = target->query_skill("force",1)/2;
        if( dp < 1 )
                dp = 1;
        if( random(ap + 20) > dp ||random(me->query_int(1)) > target->query_int(1)/2 )
		{
           if(userp(me))
               me->add("neili",-(200+random(200)));
           msg += HBYEL+HIR"$N运起「破气式」, $n顿时觉得眼前一花，气海穴上微微一痛，全身真气狂泄而出！\n" NOR;

           p = (int)me->query_skill("force") + random(me->query_skill("force")*2);
   
           force = target->query_skill_mapped("force");
/*
	switch(force) {
		case "huntian-qigong":
			if( intp(p = target->query_temp("htqg/powerup")) ){
				target->add_temp("apply/armor", - p*2);
				target->add_temp("apply/dodge", - p);
				target->delete_temp("htqg/powerup");
				tell_object(target, HIR"你的丹田要穴被伤，混天气功的效果自然消失了！\n"NOR);
				break;
			}
		case "xixing-dafa":
			if( intp(p = target->query_temp("xxdf/xixing")) ){
				target->add_temp("apply/attack", - p);
				target->add_temp("apply/dexerity", - p/10);
				target->delete_temp("xxdf/xixing");
				tell_object(target, HIR"你的丹田要穴被伤，吸星大法的效果自然消失了！\n"NOR);
				break;
			}

		case "xiantian-gong":
			if( intp(p = target->query_temp("xtg/wuqi")) ){
				target->add_temp("apply/armor", - p/5);
				target->add_temp("apply/strike", - p/10);
				target->add_temp("apply/attack", - p*4 /10);
				target->delete_temp("xtg/wuqi");
				tell_object(target, HIR"你的丹田要穴被伤，五气朝元的效果自然消失了！\n"NOR);
				break;
			}
		case "bahuang-gong":
			if( intp(p = target->query_temp("bhg/duzun")) ){
				target->add_temp("apply/armor", - p/5);
				target->add_temp("apply/hand", - p/10);
				target->add_temp("apply/attack", - p*5 /10);
				target->delete_temp("bhg/duzun");
				tell_object(target, HIR"你的丹田要穴被伤，八荒功唯我独尊效果自然消失了！\n"NOR);
				break;
			}
		case "beiming-shengong":
			if( intp(p = target->query_temp("bmsg/bm")) ){
				target->add_temp("apply/armor", - p/4);
				if(target->query("family/family_name") == "逍遥派") {
				    target->add_temp("apply/attack", - p/6);
			       target->add_temp("apply/intelligence", - p/30);
			       target->add_temp("apply/dexerity", - p /20);
			           }
				target->delete_temp("bmsg/bm");
				tell_object(target, HIR"你的丹田要穴被伤，北冥真气的效果自然消失了！\n"NOR);
				break;
			}
		case "huashan-qigong":
			if( intp(p = target->query_temp("hsqg/yjs")) ){
				target->add_temp("apply/attack", - p/2);
				target->delete_temp("double_attack");
				target->delete_temp("hsqg/yjs");
				tell_object(target, HIR"你的丹田要穴被伤，真气不足，驭剑式效果自然消失了！\n"NOR);
				break;
			}
		case "zixia-gong":
			if( target->query_temp("zxg/zixia") ){
				target->delete_temp("double_attack");
				target->delete_temp("zxg/zixia");
				tell_object(target, HIR"你的丹田要穴被伤，真气不足，紫霞聚力效果消失了！\n"NOR);
				break;
			}

		case "yijin-jing":
			if( intp(p = target->query_temp("fanzhen")) ){
				target->add_temp("apply/armor", - p);
				target->add_temp("apply/parry", - p);
				target->add_temp("apply/attack", - p);
				target->delete_temp("fanzhen");
				target->delete_temp("no_skill_hit_ob");
				tell_object(target, HIR"你的丹田要穴被伤,「金刚不坏体神功」的效应也相应地消失了！\n"NOR);
				break;
			}
		case "jiuyang-shengong":
			if( intp(p = target->query_temp("jiuyang/powerup")) ){
	                                        target->add_temp("apply/attack", - p);
	                                        target->add_temp("apply/dexerity", - p/10);
                                                      target->add_temp("apply/armor", - p/4);
                                                      target->delete_temp("fanzhen");  
	                                        target->delete_temp("jiuyang/powerup");
				tell_object(target, HIR"你的丹田要穴被伤,「九阳神功」的效应也相应地消失了！\n"NOR);
				break;
			}
		case "linji-zhuang":
			if( target->query_temp("ljz/riyue") ){
				target->delete_temp("ljz/riyue");
				tell_object(target, HIR"你的丹田要穴被伤,「日月」庄所聚天地之精气已散回日月之间！\n"NOR);
				break;
			}
			if( intp(p = target->query_temp("ljz/yinyang")) ){
				target->add("max_qi", - p);
				target->receive_wound("qi", p, "「阴阳」庄被破，脱力而");
				target->delete_temp("ljz/yinyang");
				tell_object(target, HIR"你的丹田要穴被伤,「阴阳」庄提升的效应也消失了！\n"NOR);
				break;
			}
			if( intp(p = target->query_temp("ljz/fengyun")) ){
				target->add_temp("apply/dexerity", - p);        
				target->delete_temp("ljz/fengyun");
				tell_object(target, HIR"你的丹田要穴被伤,「风云」庄效果消失，略觉步履沉重了一些。\n"NOR);
				break;
			}
			if( target->query_temp("ljz/wuwo")){
				target->delete_temp("ljz/wuwo");
				tell_object(target, HIR"你的丹田要穴被伤,「无我」心法被破，又恢复了原来的你！\n"NOR);
				break;
			}
		case "yinyun-ziqi":
			if( target->query_temp("tj/太极") ){
				target->delete_temp("tj/太极");
				tell_object(target, HIR"你的丹田要穴被伤,慌忙之中，太极不能连贯而行，效应也消失了！\n"NOR);
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
				tell_object(target, HIR"你丹田要穴被伤，心神一松，再也支持不住了！！\n"NOR);
				break;
			}
		           if( intp(p = target->query_temp("sld/wudi1")) ){
				target->add_temp("apply/strength", -p/20);
				target->add_temp("apply/attack", -p/4);
				target->delete_temp("sld/wudi");
				target->delete_temp("sld/wudi1");
				if(target->query("eff_qi") > target->query("max_qi")) 
					target->set("eff_qi",target->query("max_qi"));
				tell_object(target, HIR"你丹田要穴被伤，心神一松，好象虚脱了一样，突然垮了下来！！\n"NOR);
				break;
			}
		case "hanbing-zhenqi":
			if ( intp(p = target->query_temp("hbzq/huti")) ){
				target->add_temp("apply/parry", -p);
				target->add_temp("apply/dodge", -p);
				target->delete_temp("hbzq/huti");
				tell_object(target, HIR"你丹田要穴被伤，周身的寒气散尽，不再能起到保护的作用了。\n"NOR);
				break;
			}
			if( target->query_temp("ss/focus")){
				target->delete_temp("ss/focus");
				tell_object(target, HIR"你丹田要穴被伤，周身的寒气渐渐的散去了。\n"NOR);
				break;
			}
			if( target->query_temp("ss/hb")){
				target->delete_temp("ss/hb");
				tell_object(target, HIR"你丹田要穴被伤，手上的寒气渐渐的散去了。\n"NOR);
				break;
			}
		case "huagong-dafa":
			if( intp(p = target->query_temp("hgdf/judu")) ){
				target->add_temp("apply/armor", -p);
				target->delete_temp("hgdf/judu");
				tell_object(target, HIR"你丹田要穴被伤，心神一松，所聚毒素全都垮了！！\n"NOR);
				break;
			}
			else if( intp(p = target->query_temp("hgdf/huadu")) ){
				target->add_temp("apply/dodge", -p); 
				target->add_temp("apply/armor_vs_force", -p/2);           
				target->delete_temp("hgdf/huadu");
				tell_object(target, HIR"你丹田要穴被伤，心神一松，化毒所聚毒素全都垮了！！\n"NOR);
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
				tell_object(target, HIR"你的丹田要穴被伤,「心经」字决效应也消失了！\n"NOR);
				break;
			}
		case "shenyuan-gong":
			if ( intp(p = target->query_temp("shenyuan")) ){
				target->add_temp("apply/parry", -p/3);
				target->add_temp("apply/dexerity", -p/20);
				target->delete_temp("shenyuan");
				tell_object(target, HIR"你丹田要穴被伤，防守招式已经减弱了。\n"NOR);
				break;
			}
		case "xuantian-wuji":
			if ( intp(p = target->query_temp("kl/riyue")) ){
				target->add_temp("apply/parry", -p/2);
				target->add_temp("apply/armor", -p/2);
				target->delete_temp("kl/riyue");
				tell_object(target, HIR"你丹田要穴被伤，无极真气无法起到保护作用了。\n"NOR);
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
				tell_object(target, HIR"你丹田要穴被伤，脸上红光一闪，骨节啪啪轻响几声，散去了护体真气。\n" NOR);
				break;
			}
			if ( intp(p = target->query_temp("xs/longxiang")) ) {
				target->add_temp("apply/attack", -p);
				target->delete_temp("xs/longxiang");
				tell_object(target, HIR"你丹田要穴被伤，脸上紫气一闪，又恢复如常。\n" NOR);
				break;
			}
		case "qiantian-yiyang":
			if( intp(p = target->query_temp("dali_jing")) ){
				target->add_temp("apply/intelligence", -p);
				target->delete_temp("dali_jing");
				tell_object(target, HIR"你丹田要穴被伤，无法继续潜修了。\n" NOR);
				break;
			}
		case "guiyuan-tunafa":
			if ( intp(p = target->query_temp("tz/focus")) ){
				target->add_temp("apply/attack", p);
				target->add_temp("apply/strength", p);
				target->delete_temp("tz/focus");
				tell_object(target, HIR"你丹田要穴被伤，精神有些委顿，力道随即恢复常态。\n"NOR);
				break;
			}
		case "kurong-changong":
			if( intp(p = target->query_temp("krcg_kurong")) ){
				target->delete_temp("krcg_kurong");
				target->add_temp("apply/armor", -p);
				target->add_temp("apply/parry", -p);
				tell_object(target, HIR"你丹田要穴被伤，「枯荣」大法立刻消散了！\n" NOR);
				break;
			}
			
		case "bihai-chaosheng":
			if( intp(p = target->query_temp("thd/maze")) ){
				target->delete_temp("thd/maze");
				target->add_temp("apply/dexerity", -p/10);
				target->add_temp("apply/parry", -p /2);
				target->add_temp("apply/dodge", -p /2);
			         if( me->query_temp("thd/mazed") ){ 
                                                        me->add_temp("apply/dexerity", p/10);
				me->add_temp("apply/damage", p/2);
				me->add_temp("apply/dodge", p /2);
				me->add_temp("apply/parry", p /2);
                                                        me->delete_temp("thd/mazed");
                                                         }
				tell_object(target, HIR"你丹田要穴被伤，无暇顾及所布迷阵，结果三下两下就被打散了！\n" NOR);
				break;
			}
           }*/
	            qi_wound = ap*3+random(ap) ;
                neili_wound = random(qi_wound);
                
				if(neili_wound > target->query("neili"))
                        neili_wound = target->query("neili");

                if(qi_wound > target->query("qi"))
                       qi_wound = target->query("qi");
                if(random(2)== 1)                
					target->apply_condition("no_exert", 1+ random(2));
				

                target->add("neili", -neili_wound);
				if (target->query("neili")<0) target->set("neili",0);
				
				if (userp(target))
					qi_wound=(int)target->query("qi")/4;
                
				target->receive_damage("qi", -qi_wound,me);
                target->receive_wound("qi", -qi_wound/3,me);

				target->set("jiali",0);
				//target->add("eff_qi", -qi_wound);
				//闭气效果
				target->apply_condition("no_exert",1+random(2));
				//中了后不断泄气
                target->apply_condition("dgjj_poqi",5+random(5));
				//target->set_temp("");
				
				if (userp(target)) target->add_busy(2+random(2));
                else target->add_busy(i);
				
				target->set_temp("faint_by",me);//增加一个标记，避免莫名其妙死亡 by renlai
				//target->set_temp("last_damage_from", "被"+me->query("name")+"所使独孤九剑绝技击杀");

               
        }
        else
        {
                if(userp(me))
                        me->add("neili",-200);
                msg += "可是$n看破了$N的企图，立刻守紧门户，几经艰难终于还招挡开。\n"NOR;
                
				me->add_busy(2);
                //me->start_perform(3,"破气式");
        }
        message_vision(msg, me, target);
		me->add_busy(1+random(1));
        me->start_perform(3,"破气式");
        return 1;
}
int help(object me)
{
	write(HIC"\n独孤九剑「破气式」："NOR"\n");
	write(@HELP
	独孤九剑乃是一代大侠独孤求败所传剑法，是剑法
	中变化多端、快速进攻有进无退的高明剑术。后经
	过风清扬所传，传给华山大弟子令狐冲。令狐持之
	横行江湖。破气式乃是运独孤九剑剑意，破敌之真
	气，制敌之先机。使得对手真气收到影响，从而无
	法运用真气来加成。独孤九剑号称破天下所有内功
	注意：450后大飞
	
	指令：perform sword.poqi
	
要求：	
	当前内力需求 1000 以上；      
	独孤九剑等级 350 以上；
	基本剑法等级 350 以上；
	基本内力等级 350 以上；
	手持剑类兵器。
HELP
	);
	return 1;
}

