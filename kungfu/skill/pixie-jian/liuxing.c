// hero 流星三绝招
// 19991002001
#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return HIW"流星三绝招"NOR;}

int calc_damage(int,int,object,object);

int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int i,total; 
        
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()||!me->is_fighting(target) )
                return notify_fail("「流星三绝招」只能在战斗时使用！\n");

        if(!me->query("quest/pxj/super2/pass") )
                return notify_fail("你对辟邪剑的真意尚未理解，不能使用「流星三绝招」！\n");

        //if(me->query("quest/pxj/super2/pass") )
          //      return notify_fail("你对辟邪剑的真意尚未理解，不能使用「流星三绝招」！\n");

        if( !objectp(weapon=me->query_temp("weapon")) ) {
                        
                        return notify_fail("你必须拿着武器才能用「流星三绝招」！\n");
        }
        if (weapon->query("skill_type") != "sword"
			|| me->query_skill_mapped("dodge") != "pixie-jian"
			|| me->query_skill_mapped("parry") != "pixie-jian"
			|| me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("你现在激发不对，无法使用辟邪剑。\n");
        
        if( (int)me->query_skill("pixie-jian", 1) < 350 )
                return notify_fail("你的辟邪剑还不够熟练，不能使用「流星三绝招」！\n");

		if( (int)me->query_skill("sword", 1) < 350 )
                return notify_fail("你的基本剑法还不够熟练，不能使用「流星三绝招」！\n");
      
        if((int)me->query("max_neili", 1) < 4000) 
                return notify_fail("你现在内力修为尚低，不能使用「流星三绝招」！\n"); 

        if((int)me->query("jingli", 1) < 1000)
                return notify_fail("你现在精力不足，不能使用「流星三绝招」！\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("你现在内力不足，不能使用「流星三绝招」！\n");      

        if(me->query("gender")=="男性"||me->query("gender")=="女性") 
                return notify_fail("只有懂得辟邪剑法真正美妙的人，才能使用「流星三绝招」！\n");      
      
        me->add("jingli",-200);
        me->add("neili",-400);

        message_vision(HIW"$N身形如鬼魅，滴溜溜地转到$n的身前，瞬间一个起纵，旋即到达$n的身后，几个起落间挥出一片剑影，状若流星灿烂。\n"
		+"$n觉的眼前恍如电闪雷鸣，剑光如电。\n"NOR,me,target);
		
        if(random((int)me->query_skill("pixie-jian",1))> (int)target->query_skill("parry",1)/3
          ||random((int)me->query("combat_exp")) > (int)target->query("combat_exp")/2
          ||(!userp(target)&& target->is_busy()) )
		{
                me->add("neili",- random(400)-400 );
                me->add("jingli",-random(200)- 200);
                total = 0;
				i = calc_damage((int)me->query_skill("pixie-jian",1),(int)me->query_skill("sword",1),me,target);
                total += i;
				if (me->query("gender")=="无性" && random(me->query("dex"))>45)
				{
					//参悟身法45先天后，威力增加
					if (userp(me)&&!userp(target)) total=total+i*(int)me->query("dex")/25;
				    else total=total+random(total/5);
				  
					message_vision(BYEL"$N姿势优美,手捏兰花指，对$n嫣然一笑，神情妩媚之极，顿时令$n不禁神情一呆！\n",me,target);
				}
                msg=CYN "\n$N使出一招「"HIY"流星经天"CYN"」，身子略微前倾，脚下发力，全力刺出一剑，带起一片剑光！\n"+
                           "$n本已经贴近$N的身边，剑招由飘忽变为实，令$n防不胜防。\n"NOR;
               
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",total));
                
                
                if(userp(me) && me->query("env/damage"))
				   tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ total+ WHT"点攻击伤害。\n"NOR);    
                if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ total+ WHT"点伤害。\n"NOR); 
				if (me->query("gender")!="无性") total=1000;

				target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/8 , me);
                
				result = COMBAT_D->damage_msg(i,"瘀伤");
                result = replace_string( result, "$l", "小海穴" );
                
				msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     
				//第二招

                msg =RED "\n$N使出一招「"HIW"流星如梭"RED"」，飞坠一击，身子宛如卧地，但瞬间爆发出一片灿烂的剑光\n"+
                         "全是斩向$n所没在意的一些部位，极其诡异难挡，使得$N顿时破绽百出。\n"NOR;

                i = calc_damage((int)me->query_skill("pixie-jian",1),(int)me->query_skill("force",1),me,target);
                total += i;
                //if (userp(me)&&!userp(target)) i=total;
                
                if(userp(me) && me->query("env/damage")) 
		          tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ total+ WHT"点攻击伤害。\n"NOR);    
                if(userp(target)&& target->query("env/damage"))
					tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ total+ WHT"点伤害。\n"NOR); 
      			
				if (me->query("gender")!="无性") total=1000;

                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/8 , me);
                
				result = COMBAT_D->damage_msg(i,"刺伤");
                result = replace_string( result, "$l", "小腹" );
                result = replace_string( result, "$w", weapon->query("name") );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     
				//第三招
                msg =YEL "\n$N快速急点，宛如腾空，一步一剑，围绕$n连续施展出三十六剑，正是「"HIC"流星飞雨"YEL"」的招式，\n"+
                         "剑影如电，剑尖抖动，在内力的激发下，闪烁朵朵寒光，刺向$n的身前背后诸穴。\n"NOR;

                i = calc_damage((int)me->query_skill("pixie-jian",1),(int)me->query_skill("dodge",1),me,target);
                total += i;
				//if (userp(me)&&!userp(target)) i=total;
                if (me->query("gender")!="无性") total=1000;
				if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",total));
                

                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/8 , me);
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
                me->start_perform(4,"「流星三绝招」");
        }
        else {
                msg = WHT "\n$N倏然施展这「"HIY"流星三绝招"WHT"」，$n向旁一纵身，躲开这诡异的连续三招。\n"NOR;
                
                message_vision(msg,me,target);

                me->start_busy(1);
                me->start_perform(1,"「流星三绝招」");
        }

        return 1;
}

int calc_damage(int skill,int skill2,object me,object target)
{
        int i;

            i = (random(skill+skill2)*2-(int)target->query_skill("parry",1))*6;
            if (i<0) i = -i;
            
			i += random(i*1/5);
            if( i < (skill2*5)) i = (int)target->query("max_qi",1)/3;
            
			if (userp(me)&&!userp(target))
				i=i;
				//i=i*1.2;
            if(userp(target)) i = i/2;         
            if (me->query("gender")!="无性") i=i/10;
           
            return i;
}

int help(object me)
{
   write(WHT"\n辟邪剑法之「"HIR"流星三绝招"WHT"」："NOR"\n");
   write(@HELP
	日月神教乃江湖中重要的一大邪派组织，做事全凭个人好恶
	教中长老武技各有所长，这辟邪剑法乃是现任教主东方不败
	的绝技，后来江湖流传各种版本，但正宗辟邪剑法以轻巧、
	灵活、多变而著称。
	「流星三绝招」乃是利用辟邪剑诡异的身法，贴身对方快速
	攻击对方，剑势如虹，流星灿烂，乃是一招出其不意的狠招！
    此招需自宫后方可发挥最大威力。参悟先天身法45后，威力
	再次提升。

	指令：perform sword.liuxing

要求：
	当前内力 1800 以上；
	最大内力 4000 以上
	当前精力 1000 以上
	辟邪剑法 350 以上；
	基本剑法 350 以上；
	基本轻功 350 以上；
	后天身法 60  以上；
	激发轻功辟邪剑法
	激发招架辟邪剑法；
	激发剑法辟邪剑法；
	需手持剑类武器;

HELP
   );
   return 1;
}
