// hero 英雄三招
// 19991002001
#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return HIR"英雄三招"NOR;}

int calc_damage(int,int,object,object);
int perform1(object me,object target,object weapon);
int perform2(object me,object target,object weapon);
int perform3(object me,object target,object weapon);


int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int i,total,skill; 
        skill=me->query_skill("canglang-goufa",1);
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()||!me->is_fighting(target) )
                return notify_fail("「英雄三招」只能在战斗时使用！\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("「英雄三招」只有拜了教主后才能用！\n");

        if( !objectp(weapon=me->query_temp("weapon"))||weapon->query("skill_type")!="hook" ) {
                          
                return notify_fail("你必须拿着钩型武器才能用「英雄三招」！\n");
        }
     
        
        if( (int)me->query_skill("huagu-mianzhang", 1) < 500 )
                return notify_fail("你的化骨绵掌还不够熟练，不能使用「英雄三招」！\n");

        if (me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("只有使用化骨绵掌时才能使用「英雄三招」！\n");

        if( (int)me->query_skill("shenlong-tuifa", 1) < 500 )
                return notify_fail("你的神龙腿法还不够熟练，不能使用「英雄三招」！\n");

        if (me->query_skill_mapped("leg") != "shenlong-tuifa")
                return notify_fail("只有使用神龙腿法时才能使用「英雄三招」！\n");

        if( (int)me->query_skill("canglang-goufa", 1) < 500 )
                return notify_fail("你的沧浪钩法还不够熟练，不能使用「英雄三招」！\n");

        if (me->query_skill_mapped("hook") != "canglang-goufa")
                return notify_fail("只有使用沧浪钩法时才能使用「英雄三招」！\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 500 )
                return notify_fail("你的毒龙大法功力不足，不能用「英雄三招」。\n");

       
        if((int)me->query("max_neili", 1) < 4000) 
                return notify_fail("你现在内力修为尚低，不能使用「英雄三招」！\n"); 

        if((int)me->query("eff_jingli", 1) < 2500) 
                return notify_fail("你现在精力修为尚低，不能使用「英雄三招」！\n"); 

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("你现在精力不足，不能使用「英雄三招」！\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("你现在内力不足，不能使用「英雄三招」！\n");      

        if(me->query("gender")!= "男性") 
                return notify_fail("只有男人才能使用「英雄三招」！\n");      

        if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("你现在所使用的内功同毒龙大法向抵触，不能使用「英雄三招」。\n");

        me->add("jingli",-100);
        me->add("neili",-200);

        msg = HIR"$N乘$n稍稍走神之机，拼尽全力使出洪教主不传之绝技－－「英雄三招」\n"NOR;
		msg += HIR"\n$N双手舞动"+weapon->query("name")+HIR",密不透风，瞬间使出「狄青降龙」、「鲁达拔柳」、「子胥举鼎」连贯而出。\n"NOR;
    
		if(random((int)me->query_skill("canglang-goufa",1))*8/5 > (int)target->query_skill("parry",1)
          ||random((int)me->query("combat_exp"))*8/5 > (int)target->query("combat_exp")
          ||(!userp(target)&& target->is_busy()) )
		{
                me->start_busy(1);
                me->add("neili",- random(400)-400 );
                me->add("jingli",-random(200)- 200);
                total = 0;
				i = calc_damage((int)me->query_skill("huagu-mianzhang",1),(int)me->query_skill("canglang-goufa",1),me,target);
                total += i;
				if (me->query("gender")=="男性" && random(me->query("str"))>35)
				{
					
					if (userp(me)&&!userp(target)) total=total+i*(int)me->query("str")/35;
				    else total=total+random(total/2);
				  
					//message_vision(BYEL"$N姿势优美,嫣然一笑，顿时令$n不禁神情一呆！",me,target);
				}
                msg += HIR "\n$N使出一招「"HIY"子胥举鼎"HIR"」，一手轻搔$n腋底极泉穴，乘其慌张之际，另一手同\n"+
                           "时拿向$n肘后小海穴，将其摔向地上。\n"NOR;
               
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                
                if (total>6000) total=6000+random(1000);
               
                if(userp(me) && me->query("env/damage"))
				   tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ i+ WHT"点攻击伤害。\n"NOR);    
                if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ i+ WHT"点伤害。\n"NOR); 
                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/4 , me);
                result = COMBAT_D->damage_msg(i,"瘀伤");
                result = replace_string( result, "$l", "小海穴" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);
				COMBAT_D->do_attack(me,target,weapon,3);
		}
		//绝世增加进攻		
		if (me->query_skill_mapped("strike")=="huagu-mianzhang"
			&& me->is_fighting(target)
			&& me->query("quest/sld/clgf/canglang/pass"))
		{

			
					message_vision(YEL"$N将兵器交与左手，转身向$n拍出一掌阴柔劲，正是「"HIR"化骨绵掌"YEL"」的招式！\n"NOR,me,target);
					message_vision(YEL"$n直觉一股阴柔的劲气拂面而过，隐约间有股幽香传来！\n"NOR,me,target);

					me->add_temp("apply/attack",skill/2);
					me->add_temp("apply/damage",skill/4);
					me->add_temp("apply/strike",skill/4);
					weapon->unequip();

					me->prepare_skill("strike", "huagu-mianzhang");
					COMBAT_D->do_attack(me,target,weapon,3);//第二招
					
					me->add_temp("apply/attack",-skill/2);
					me->add_temp("apply/damage",-skill/4);
					me->add_temp("apply/strike",-skill/4);
					weapon->wield();
                
		}	
				
				
		if (me->is_fighting()&& objectp(target))
			perform1(me,target,weapon);
		return 1;

}
//no 2招式


int perform1(object me,object target,object weapon)
{
	string msg,result;
	int i,total,skill;
        skill=me->query_skill("canglang-goufa",1);

	
			

                msg =HIR "\n$N使出一招「"HIW"鲁达拔柳"HIR"」，缩腿假装向$n叩头，突然一个斛斗，似欲向$n胯下\n"+
                         "钻过，但只一作势，左手抓向$n右脚足踝，右手兵器虚点向$n小腹，一用力，把$n头下脚上，\n"+
                         "倒提起来。\n"NOR;

                i = calc_damage((int)me->query_skill("shenlong-tuifa",1),(int)me->query_skill("canglang-goufa",1),me,target);
                total += i;
                //if (userp(me)&&!userp(target)) i=total;
                if (random(me->query_str())>target->query_str()/2)
                {
					message_vision(HIC"$n一不小心为这招所制住，手脚不能动弹，呼吸困难。\n"NOR,me,target);
					target->apply_condition("no_force",2);
					target->add_busy(2);
                }
                if(userp(me) && me->query("env/damage")) 
		          tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ i+ WHT"点攻击伤害。\n"NOR);    
                if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ i+ WHT"点伤害。\n"NOR); 
                
				if (total>7000) total=7000+random(1000);

                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"刺伤");
                result = replace_string( result, "$l", "小腹" );
                result = replace_string( result, "$w", weapon->query("name") );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     
				
				if (me->query_skill_mapped("leg")=="shenlong-tuifa" 
					&& me->is_fighting(target)
					&& me->query("quest/sld/clgf/canglang/pass"))
                {
					message_vision(HIG"$N在飞跃$n头顶之际，神龙腿法陡然而出，转身向$n小腿部位猛然扫去，正是「"HIR"铁扫帚功"HIG"」绝技！\n"NOR,me,target);
					message_vision(YEL"这腿法招式只有一招，但却是威力极大,势不可挡！\n"NOR,me,target);

					me->add_temp("apply/attack",skill/2);
					me->add_temp("apply/damage",skill/4);
					me->add_temp("apply/leg",skill/4);
					weapon->unequip();
					me->prepare_skill("strike");
					me->prepare_skill("leg", "shenlong-tuifa");
					COMBAT_D->do_attack(me,target,weapon,3);//第二招
				//	COMBAT_D->do_attack(me,target,weapon,3);//3
					me->add_temp("apply/attack",-skill/2);
					me->add_temp("apply/damage",-skill/4);
					me->add_temp("apply/leg",-skill/4);
					me->prepare_skill("leg");
					me->prepare_skill("strike", "huagu-mianzhang");
					weapon->wield();
                }
		if (me->is_fighting()&& objectp(target))
			 perform2(me,target,weapon);
		return 1;


}

int perform2(object me,object target,object weapon)
{
	string msg,result;
	int i,total,skill;
        skill=me->query_skill("canglang-goufa",1);



                msg =HIR "\n$N使出一招「"HIC"狄青降龙"HIR"」，背脊后撞，十指向$n胸口虚抓，乘其避让之际，\n"+
                         "突然一个倒翻斛斗，身子跃起，双腿一分，跨坐在$n肩头，同时双手拇指压住$n\n"+
                         "太阳穴，食指按眉，中指按眼。\n"NOR;

                i = calc_damage((int)me->query_skill("shenlong-tuifa",1),(int)me->query_skill("canglang-goufa",1),me,target);
                total += i;
				//if (userp(me)&&!userp(target)) i=total;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                
                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ i+ WHT"点攻击伤害。\n"NOR);    
                if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ i+ WHT"点伤害。\n"NOR); 
               
				if (total>8000) total=8000+random(1000);

                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"内伤");
                result = replace_string( result, "$l", "头部" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);
                
               
                if(userp(me) && me->query("env/damage"))
					tell_object(me,WHT"你对"+ target->query("name") +"总共造成了"RED+ total+ WHT"点攻击伤害。\n"NOR);    
                if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"的攻击对你总共造成了"RED+ total+ WHT"点伤害。\n"NOR);  
                if(wizardp(me)) tell_object(me,sprintf("Total damage: %d \n",total));               
				//引出第三招
				if (me->is_fighting()&& objectp(target)&& me->query("quest/sld/clgf/canglang/pass"))
					perform3(me,target,weapon);
      
				me->start_perform(5,"「英雄三招」");
                me->start_busy(1+random(3));                    

        return 1;
}

int perform3(object me,object target,object weapon)
{
		
		int skill;
        skill=me->query_skill("canglang-goufa",1);
        if (!objectp(weapon))
			return 1;    
		message_vision(HIW"$N英雄三招使完，沧浪意境犹在，憋在心胸难以舒展，忍不住长啸一声！\n手中"+weapon->query("name")+HIW"顺势连续幻出一股苍凉古意，招式顿时变得玄奥无比。\n"NOR,me,target);
		me->add_temp("apply/attack",skill/2);
		me->add_temp("apply/damage",skill/4);
		me->add_temp("apply/hook",skill/4);
				//	message_vision(HIC"第一招，"NOR,me,target);
		COMBAT_D->do_attack(me,target,weapon,3);//第二招
		if (me->query("str")>34 && me->query_temp("sld/wudi2")) 
		{
			message_vision(HIR"$N毒龙大法发动，多年辛苦修炼的劲力勃发，招式威力顿时大增。\n"NOR,me,target);

			target->set_temp("must_be_hit",1);
			me->add_temp("apply/damage",skill/5);
			
			COMBAT_D->do_attack(me,target,weapon,3);
			COMBAT_D->do_attack(me,target,weapon,3);
			me->add_temp("apply/damage",-skill/5);

			target->delete_temp("must_be_hit");

		}
		me->add_temp("apply/attack",-skill/2);
		me->add_temp("apply/damage",-skill/4);
		me->add_temp("apply/hook",-skill/4);
				
				
		return 1;
}

int calc_damage(int skill,int skill2,object me,object target)
{
        int i;

            i = (random(skill+skill2)*2-(int)target->query_skill("parry",1))*10;
            if (i<0) i = -i;
            i += random(i*2/5);
            if( i < (skill2*5)) i = (int)target->query("max_qi",1)/3;
            if (userp(me))
				i=i*1.5;
            if(userp(target)) i = i* 2/5;         
            
            return i;
}
int help(object me)
{
   write(WHT"\n沧浪钩法「"HIR"英雄三招"WHT"」："NOR"\n");
   write(@HELP
	沧浪钩法乃是神龙岛主晚年后整理自己的所学武技
	后总体提炼出的一套钩法武技，去繁就简，诡异犀
	利，防不胜防，尤其对于臂力较大男弟子而言，更
	是非常实战的功夫。其中英雄三招乃是典型的进攻
	武技，利用自己高的臂力和丰富的战斗经验，对敌
	人实施三招典型的打击。
	注意：先天臂力参悟35后，威力再次增加。

	指令：perform hook.hero
	
要求：
	最大内力要求 4000 以上；
	最大精力要求 2500 以上；
	当前内力要求 1500 以上；
	当前精力要求 800 以上；
	化骨绵掌等级 500 以上；
	神龙腿法等级 500 以上；
	沧浪钩法等级 500 以上；
	毒龙大法等级 500 以上；
	基本钩法等级 500 以上；
	激发且备掌法为化骨绵掌；
	激发腿法为神龙腿法；
	激发钩法为沧浪钩法；
	激发内功为毒龙大法；
	手持钩类武器；
	性别需求 男性。
HELP
   );
   return 1;
}
