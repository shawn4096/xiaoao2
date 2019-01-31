//kungfu/skill/liuyang-zhang/baihong.c 白虹
// modified by action@SJ 2009/2/5
//updated By action@sjmud 2009/5/21
//modified by zhuifeng@SJFY 2010/07/17

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
string perform_name(){ return HIR"白虹"NOR; }

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lv, a;

        if( !target ) target = offensive_target(me);

         if( !objectp(target) || !me->is_fighting(target) )
                return notify_fail("「白虹」绝招只能在战斗中使用。\n");
                
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「白虹」绝招！\n");   
                
        if( (int)me->query_skill("liuyang-zhang", 1) < 450 )
                return notify_fail("你的天山六阳掌还不够娴熟，使不出「白虹」绝招。\n");
                
        if (me->query_skill_prepared("strike") != "liuyang-zhang"
            || me->query_skill_mapped("strike") != "liuyang-zhang"
            //|| me->query_skill_mapped("parry") != "liuyang-zhang"
			)
                return notify_fail("你现在无法使用「白虹」进行攻击。\n");  
/*
        if( (int)me->query_skill("bahuang-gong", 1) < 180 )
        if( (int)me->query_skill("beiming-shengong", 1) < 180 )
                return notify_fail("你的内功等级还不够，使不出「白虹」绝招。\n");
                
        if (me->query_skill_mapped("force") != "bahuang-gong")
        if (me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("你的内功有误，无法使用「白虹」绝招。\n");    */           
		            
      if( me->query("max_neili") < 2500 )
                return notify_fail("你现在内力太弱，使不出「白虹」绝招。\n"); 
                     
        if( (int)me->query("neili") < 1500 )
                return notify_fail("你现在真气太弱，使不出「白虹」绝招。\n");
                
        if( (int)me->query("jingli") < 1000 )
                return notify_fail("你现在精力不足太弱，使不出「白虹」绝招。\n");
                
       message_vision(HBMAG+HIW "\n$N左掌拍出，右掌一带，左掌之力吞吐不定。这门功夫乃是天山\n"
                HBMAG"六阳掌法中的"+ HIW +"‘白虹掌力’"+ NOR + WHT +HBMAG+"，此刻$N掌力曲直如意，当真了得！\n"NOR, me); 
       //北冥神功有优势
	   
	   if (me->query_skill("bahuang-gong", 1)) 
		lv = me->query_skill("liuyang-zhang",1)+me->query_skill("bahuang-gong",1) /2;
	   else   
        lv = me->query_skill("liuyang-zhang",1)+me->query_skill("beiming-shengong",1) /2;
       
        me->set_temp("baihong",6);
        
		if (me->query("family/family_name") == "逍遥派"
		||me->query("family/family_name") == "灵鹫宫"
		||me->query_skill_mapped("force")=="beiming-shengong") 
		{
            me->add_temp("apply/attack", lv / 3);
            me->add_temp("apply/damage", lv / 3);
            me->add_temp("apply/strike", lv / 5);
			me->set_temp("lyz/bhaddtemp",lv);
        }

        me->add_temp("apply/strike", lv / 5);
        me->add_temp("apply/attack", lv  /3);
        me->add_temp("apply/strength", lv / 10);

		//me->set_temp("lyz/baihong",1);
        
		for(a=0;a<6;a++)
        {
		     if(random(2)) me->set_temp("lyz/baihong",1);

		     if (me->query_temp("lyz/baihong"))
		   {
		         if(me->is_fighting(target))
		         	me->prepare_skill("strike", "liuyang-zhang");
		         	me->prepare_skill("hand", "none");
		         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3); 
                } else {
                 if(me->is_fighting(target))
                 	me->prepare_skill("strike", "liuyang-zhang");
                 	me->prepare_skill("hand", "none");
		         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3); 
           }
        me->delete_temp("lyz/baihong");
        }
		    me->delete_temp("baihong");
		    me->delete_temp("lyz/baihong");
     //   if (me->query("family/family_name") == "逍遥派"
		//||me->query("family/family_name") == "灵鹫宫")
		if (me->query_temp("lyz/bhaddtemp"))
		{
			me->add_temp("apply/attack", -lv / 3);
			me->add_temp("apply/damage",- lv / 3);
			me->add_temp("apply/strike",- lv / 5);
			me->delete_temp("lyz/bhaddtemp");
		}

        me->add_temp("apply/attack", -lv / 3);
        me->add_temp("apply/strike",- lv / 5);
        me->add_temp("apply/strength", -lv / 10);

		me->start_perform(2 + random(2), "「白虹」");
  
        return 1; 
}


int help(object me)
{
        write(HIR"\n天山六阳掌之「白虹」："NOR"\n");
        write(@HELP
	天山六阳掌在逍遥派武技中属于高深武学，威力巨大。
	一旦施展后，若内功为逍遥北冥神功、八荒功或小无相
	则同时可以附带生死符攻击，端的是厉害无比。逍遥派
	武功讲究轻灵飘逸，闲雅清隽，一旦施展在白衣飘飘中
	暗藏杀机。其中，天山六阳掌之「白虹」绝招为逍遥派
	无崖子绝学，连续攻击六招厉害无比。天山六阳掌若为
	身负北冥神功者修习，威力远高于其他门派。
	
	指令: perform strike.baihong

要求：  
	最大内力 2500 以上；      
	当前内力 1500  以上；  
	天山六阳掌等级 450 以上；
	激发掌法为天山六阳掌；
	备掌法为天山六阳掌；
	且手无兵器；                               
HELP
        );
        return 1;
}


