//pojian.c 无招胜有招;
//谁能死守着9j不出questskills;
// poqi伤害毕竟还是太低了。;
//限制激发条件，避免quest类dodge或者exert带来的效果。
//重新装修 by sohu@xojh 2014.1 梳理成第一类武技
//破气定位成气血杀伤，闭气不封招、破招压制打兵器，伤害；总决为辅助进攻，压制；无招终极融合所有
#include <ansi.h>
 
inherit F_SSERVER;
 
string perform_name() {return HBBLU+HIW"无招胜有招"NOR;}

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, p, force, neili_wound, qi_wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("dugu-jiujian",1)  ;
        
        if( !me->query("quest/hs/dgjj/wuzhao/pass"))
                return notify_fail("「无招胜有招」你只是听风老前辈说过，但并没有领悟。\n");
        if( !me->is_fighting()||!living(target))
                return notify_fail("「无招胜有招」只能对战斗中的对手使用。\n");
 
        if (!objectp(weapon = me->query_temp("weapon"))
            || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

	    if((string)me->query_skill_mapped("sword") != "dugu-jiujian" && userp(me))
		     return notify_fail("你现在无法使用「无招胜有招」！\n");

	    if((string)me->query_skill_mapped("parry") != "dugu-jiujian" && userp(me))
		     return notify_fail("你现在无法使用「无招胜有招」！\n");

        if( me->query("int",1) < 45 )
		 
			return notify_fail("你先天悟性不够45，无法使用「无招胜有招」！\n");

        if( skill < 500)
                return notify_fail("你的独孤九剑等级不够, 不能使用「无招胜有招」！\n");

        if( me->query("neili") < 2500 )
                return notify_fail("你的内力不够，无法运用「无招胜有招」！\n");
 
        msg = HIM"\n$N谨遵风清扬所授独孤九剑“以无招胜有招”的要旨，任意变幻。遇强越强，一经$n的激发，“独孤九剑”\n"
		          +
"中种种奥妙精微之处，发挥得淋漓尽致。“无招胜有招”看似随意出招，但其中于天下各门各派招法要义兼\n"
				  +"收并蓄，虽说“无招”，却是以普天下剑法之招数为根基。招数之奇妙，实是匪夷所思，料敌机先，招招致命。\n"NOR;
       if(!userp(me)) skill = skill / 2;

        me->add_temp("apply/attack", skill/2);
        me->add_temp("apply/damage", skill/3);
        me->add_temp("apply/sword",  skill/3);
        ap = me->query_skill("sword",1) + skill;
        dp = target->query_skill("force",1)/2;
       if( dp < 1 ) dp = 1;


       if( random(ap ) > dp 
		   ||( me->query("int")>=45 && random( me->query_int(1)) > target->query_int(1)/3 )  ){

		   if(userp(me))
                me->add("neili",-(500+random(500)));
           msg += YEL"\n$n见$N剑招层出不穷，每一变化均是从所未见，当下提起内力，接连变招。\n"+
                     "有的攻势凌厉，有的招数连绵，有的小巧迅捷，有的威猛沉稳。但不论$n招数如何精妙，\n"+
                     "内力如何深厚，到了“独孤九剑”精微的剑法之下，尽数落空。\n" NOR;

           p = (int)me->query_skill("force") + random(me->query_skill("force")*3);
   
           force = target->query_skill_mapped("force");
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
              if (target->query("family/family_name") == "逍遥派") {
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
           }
	             qi_wound = ap  +random(ap*2) ;
                 neili_wound = random(qi_wound/2)* 5;
                
                if(neili_wound > target->query("neili"))
                   neili_wound = target->query("neili");

                if(qi_wound > target->query("qi"))
                   qi_wound = target->query("qi");
                //if(random(2)== 1)
                target->apply_condition("no_perform", 2+ random(1));
				target->apply_condition("no_exert", 2+ random(2));
                target->add("neili", -neili_wound);
                target->add("qi", -qi_wound);
                target->add("eff_qi", -qi_wound*2/3);
                if (userp(target)) target->add_busy(3);
				else target->add_busy(3+random(3));
    
              message_vision(msg, me, target);
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);      
	          if ( me->is_fighting(target))
		        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);       
                me->start_perform(2,"无招胜有招");
			} else
              { 

              message_vision(msg, me, target);

              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
   
  	        if ( me->is_fighting(target))
		        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
       
                me->start_perform(4,"无招胜有招");
         }

        me->add_temp("apply/attack", -skill/2);
        me->add_temp("apply/damage", -skill/3);
        me->add_temp("apply/sword",  -skill/3);
        return 1;

}
int help(object me)
{
	write(HIC"\n独孤九剑「无招胜有招」："NOR"\n");
	write(@HELP
 
	独孤九剑「无招胜有招」

	依据：令狐冲谨依风清扬所授“以无招胜有招”的要旨，任意变幻。
	那“独孤九剑”中的“破剑式”虽只一式，但其中于天下各门各派
	剑法要义兼收并蓄，虽说“无招”，却是以普天下剑法之招数为根
	基。无招乃是独孤九剑的大成之招式，九剑一出，天下英雄束手，
	不论敌手的内力如何深厚，到了“独孤九剑”精微的剑法之下，尽
	数落空。“独孤九剑”是敌强愈强，没有防守，唯有进攻，进攻就
	是最好的防守。料敌机先，无有不破。“独孤九剑”除了精熟剑诀
	剑术之外，有极大一部分依赖使剑者的灵悟，使剑者聪明智慧越
	高，剑法也就越威猛。     

要求：
	当前内力 2500 以上；
	独孤九剑等级 500 lv以上；      
	激发剑法独孤九剑；
	激发招架独孤九剑；
	先天悟性不小于 45 方可使用；
	手持兵器。
	极高的悟性对战斗有额外的效果。 

HELP
	);
	return 1;
}
