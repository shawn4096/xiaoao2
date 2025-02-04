// wangu.c 万古一牛心
// Created by snowman@SJ 18/03/2001

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

int is_pfm() { return 1;}

#define PFM_NAME 	"万古一牛心"
string perform_name(){ return HIM+PFM_NAME+NOR; }

int perform(object me)
{     
      	if( (int)me->query_skill("qingyin-jian",1) < 180 )
           	return notify_fail("你的清音剑法不够娴熟，不能使用" + PFM_NAME + "！\n");
      
      	if( (int)me->query_skill("sword",1) < 180 )
           	return notify_fail("你的基本剑法等级不够，不能使用" + PFM_NAME + "！\n");  
      
      	if( (int)me->query_skill("sancheng-gong", 1) < 180 )
           	return notify_fail("你的三乘功法等级不够，不能使用" + PFM_NAME + "！\n");

      	if (me->query_skill_mapped("force") != "sancheng-gong")
           	return notify_fail("你所使用的内功不是三乘功法。\n");

      	if( (int)me->query("max_neili") < 2500 )
           	return notify_fail("你的内力太弱，不能使用" + PFM_NAME + "！\n");
      
      	if( (int)me->query("neili") < 800 )
           	return notify_fail("你的内力太少了，无法使用出" + PFM_NAME + "！\n"); 
        
        return (int)call_other( this_object(), "main", me);
}

int main(object me)
{
	object weapon;
	int i;

      	if( me->query("neili") < 800 || me->query("jingli") < 100  )
                return notify_fail("你目前无法使用「" + PFM_NAME + "」！\n");   
                	
	weapon = me->query_temp("weapon");
      	if (!weapon
       	|| weapon->query("skill_type") != "sword"
       	|| me->query_skill_mapped("sword") != "qingyin-jian" )
       		return notify_fail("你现在无法使用" + PFM_NAME + "！\n");      
       		
       	i = me->query_skill("qingyin-jian", 1) + me->query_skill("sancheng-gong", 1);
       	i = i/2 + random(i/2);
       	i /= 2;
       	
	    me->add("neili", -i);
        me->add("jingli", -50);
        message_vision(YEL "\n$N凝神而立，双手捧$n"YEL"，静如处子！但见$P任其身旁风吹呼啸而仍巍然不动，一股撼人之气立地而生！\n\n" NOR, me, weapon);
        me->start_perform(4, PFM_NAME);
        me->set_temp("pfm/wangu", i);
        me->add_temp("apply/attack", i);
        me->add_temp("apply/sword", i);
        me->add_temp("apply/damage", i/6);
        call_out("check_fight", 1 , me, i/10);
        if(me->is_fighting()) me->start_busy(1);
        return 1;
}

void check_fight(object me, int i)
{       
        int j;
        
        if( !me ) return; 
        if( !intp(j = me->query_temp("pfm/wangu")) ) return;
        
        i--;
        if( !me->is_fighting() 
	    || !me->is_living()
        ||  i < 1
        ||  !me->query_temp("weapon")
        ||  me->query_skill_mapped("sword") != "qingyin-jian"
        ||  me->query_skill_mapped("force") != "sancheng-gong") {
        	
			me->add_temp("apply/attack", -j);
        	me->add_temp("apply/sword", -j);
        	me->add_temp("apply/damage", -j/6);
        	me->delete_temp("pfm/wangu");
        	me->add("neili", -j );
        	me->start_perform(2, PFM_NAME);
        	if( living(me) )
			message_vision(YEL "\n$N张嘴呼出一口轻气，精神缓缓松弛了下来。\n" NOR, me);   
        	return;
        }
	    me->start_perform(1, PFM_NAME);
        call_out("check_fight", 1, me, i);
}


int help(object me)
{
	write(HIG"\n清音剑法「" + perform_name() + HIG"」："NOR"\n");
	write(@HELP
			双飞两虹影，万古一牛心
			
	此乃戊戍六君子之一的刘光第的联语，用传神之笔描绘出“双桥清音”的
	风韵。清音阁黑白二水冲牛心石，是峨眉山十景之一，其惊涛拍石，激起
	飞花碎玉，洒珠喷雪，水面上一派似雾非雾的水珠，飞腾于空中，跌落在
	水里。中心石黝黑光亮。凝聚着两亿多年的历史和生命，任其黑白二水汹
	涌拍击，仍巍然不动。此剑法要点在于静，静能料敌于先，静能安神定气。
	所以此式能如水中巨石一般屹立不倒，出招伤敌！
	
	要求：	
		清音剑法等级 180 以上；
		基本剑法等级 180 以上；
		三乘功法等级 180 以上；
		最大内力 2500 以上； 
		内力 800 以上。
HELP
	);
	return 1;
}

