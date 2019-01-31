// piaoxue.c by sohu@xojh


#include <ansi.h>

inherit F_SSERVER;


int calc_damage(int,int,object,object);

int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int i,total; 
       
        if( !target ) target = offensive_target(me);

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「飘雪穿云」只能在战斗时使用！\n");
         
        if( objectp(weapon=me->query_temp("weapon")) )                              
                return notify_fail("你手里拿着武器，无法施展「飘雪穿云」！\n");               
        
        if( (int)me->query_skill("sixiang-zhang", 1) < 100 )
                return notify_fail("你的四象掌还不够熟练，不能使用「飘雪穿云」！\n");

        if (me->query_skill_mapped("strike") != "sixiang-zhang")
                return notify_fail("只有使用四象掌时才能使用「飘雪穿云」！\n");
	//	if (me->query_skill_mapped("parry") != "sixiang-zhang")
             //   return notify_fail("只有使用四象掌招架时才能使用「飘雪穿云」！\n");

        if( (int)me->query_skill("linji-zhuang", 1) < 100 )
                return notify_fail("你的临济庄还不够熟练，不能使用「飘雪穿云」！\n");       

        if((int)me->query("max_jingli", 1) < 1000 )
                return notify_fail("你的最大精力不足，不能使用「飘雪穿云」！\n");       

        if((int)me->query("max_neili", 1) < 1200) 
                return notify_fail("你的最大内力不足，不能使用「飘雪穿云」！\n");      		
        if((int)me->query("neili", 1) < 500) 
                return notify_fail("你的当前内力不足，不能使用「飘雪穿云」！\n");      		
        if( me->query_skill_mapped("force") != "linji-zhuang")
                return notify_fail("你现在所使用的内功同临济庄相抵触，不能使用「飘雪穿云」。\n");
        me->add("jingli",-100);
        me->add("neili",-400);
        
        msg = HIW"$N轻身前纵，左手向左划了半圆，右手成掌，向前急速推出，施展出峨嵋派「飘雪穿云」绝技。\n"NOR;
        if(random((int)me->query_skill("sixiang-zhang",1))> (int)target->query_skill("parry",1)/2
          ||random((int)me->query("combat_exp")) > (int)target->query("combat_exp")/2
          ||target->is_busy() ){
                me->start_busy(1);
                total = 0;
                msg +=CYN "\n$N使出一招「"HIW"飘雪"CYN"」，双掌飞舞，出掌飘逸，两畔生风，夹杂着令人窒息的劲气击向$n。\n"NOR;
                i = calc_damage((int)me->query_skill("sixiang-zhang",1),(int)me->query_skill("linji-zhuang",1),me,target);
				if (me->query("class")=="bonze") i=i+me->query_skill("dacheng-fofa",1);
                total += i;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"瘀伤");
                result = replace_string( result, "$l", "腹部" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0); 

                msg =HIC "\n$N使出一招「"WHT"穿云"HIC"」，单掌直逼$n中宫，柔中带刚，进发出凛然的掌风，拍向$n的面部，\n"NOR;

                //i = calc_damage((int)me->query_skill("meinu-qunfa",1),(int)me->query_skill("linji-zhuang",1),me,target);
				if (me->query("class")=="bonze") i=i+me->query_skill("dacheng-fofa",1);
                total += i/5;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"瘀伤");
                result = replace_string( result, "$l", "面部" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     
               if (me->query("emjy/pass")				   
				   &&me->query_skill_mapped("hand")=="jieshou-jiushi"
			       &&me->query_skill_mapped("strike")=="sixiang-zhang"
				   &&me->query_skill_prepared("hand")=="jieshou-jiushi"
				   &&me->query_skill_prepared("strike")=="sixiang-zhang")
               {
                 msg =HIY "\n$N使出一招「"HIB"佛光普照"HIY"」，一招拍出，击向敌人胸口也好，背心也好，肩头也好，面门也好，招式平平淡淡。\n"+
                         "一成不变，其威力之生，全在于以峨嵋派九阳功作为根基。\n"NOR;

               // i = calc_damage((int)me->query_skill("sixiang-zhang",1),(int)me->query_skill("linji-zhuang",1),me,target);
			    if (me->query("class")=="bonze") i=i+me->query_skill("dacheng-fofa",1);
                total += i/6;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"内伤");
                result = replace_string( result, "$l", "胸口" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);
				}
                if(wizardp(me)) tell_object(me,sprintf("Total damage: %d \n",total));
                me->start_perform(3,"「飘雪穿云」");
        }
        else {
                msg +=CYN "\n$N使出一招「"HIW"飘雪"CYN"」，双掌飞舞，出掌飘逸，两畔生风，夹杂着令人窒息的劲气击向$n。\n"NOR;
                msg += "但是$n看破了$N的企图，没有上当，急急忙忙向旁边一闪，躲了过去。\n";
                msg =HIC "\n$N使出一招「"WHT"穿云"HIC"」，单掌直逼$n中宫，柔中带刚，进发出凛然的掌风，拍向$n的面部，\n"NOR;
                         "还没待$n反应过来，身子一转，正好转到$n的右侧，这一指却是指向了$n的太阳穴。\n"NOR;
                msg += "$n吃了一惊，但随即冷静下来，在空中猛一蹬腿踢向$N面门，$N只得松开了手。\n";
               // msg =HIY "\n$N使出一招「"HIB"佛光普照"HIY"」，一招拍出，击向敌人胸口也好，背心也好，肩头也好，面门也好，招式平平淡淡。\n"+
                 //        "一成不变，其威力之生，全在于以峨嵋派九阳功作为根基。\n"NOR;
                //msg += "$n被$N制住，但临危不乱，以内力护住要害，同时高高跃起，翻身以头撞地，把$N撞了出去！\n";
                message_vision(msg,me,target);
                me->start_busy(1+random(2));
                me->start_perform(4,"「飘雪穿云」");
        }
        return 1;
}

int calc_damage(int skill,int skill2,object me,object target)
{
			int i;

            i = (random(skill+skill2)*2-(int)target->query_skill("parry",1))*10;
            if (i<0) i = -i;
            i += random(i*2/5);            
            if(!userp(me)) i = i/2;
            return i; 
}
string perform_name(){ return HIW"飘雪穿云"NOR; }

int help(object me)
{
   write(HIC"\n四象掌「"HIW"飘雪穿云"HIC"」："NOR"\n");
   write(@HELP
	四象掌绝学是峨嵋重要的空手武技，和雁行刀法配合有不弱
	的表现，当和峨嵋的另外一项空手武技截手九式互备后，会
	产生一定程度的飞跃。当解开峨嵋九阳谜题后，四象掌会出
	第三招【佛光普照】，实现飞跃。
	
指令: perform strike.piaoxue
	
要求：
	最大内力需求 1200 以上；
	最大精力需求 1000 以上；
	当前内力需求 500 以上；
	四象掌法等级 100 以上；
	基本掌法等级 100 以上；
	临济十二桩等级 100 以上；
	出家人因大乘佛法原因，有略微优势。
		
HELP
   );
   return 1;
}
