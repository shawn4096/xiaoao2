// bujue.c 绵绵不绝

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name() {return HIC"绵绵不绝"NOR;}

void attackob(object me,object target,int lvl,int hits,int);
void dohit(object,object);

int perform(object me, object target)
{
        string msg;
        int lvl,effect,i; 
        
        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「绵绵不绝」只能在战斗时用！\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能用「绵绵不绝」！\n"); 

        if( (lvl=(int)me->query_skill("huagu-mianzhang", 1)) < 400 )
                return notify_fail("你的化骨绵掌还不够熟练，不能使用！\n");

        if ( me->query_skill_prepared("strike") != "huagu-mianzhang"
        || me->query_skill_mapped("strike") != "huagu-mianzhang" 
        || me->query_skill_mapped("parry") != "huagu-mianzhang" )
                return notify_fail("你没有激发化骨绵掌，不能使用「绵绵不绝」！\n");

          if(me->query_skill("dulong-dafa",1) < 400 )
                return notify_fail("你的毒龙大法功力不足，不能用绵绵不绝。\n");

        if ( me->query_skill_mapped("force") != "dulong-dafa" )
                return notify_fail("你没有激发毒龙大法，不能使用「绵绵不绝」！\n");

        if((int)me->query("neili") < 1000)
                return notify_fail("你现在内力不足，不能用「绵绵不绝」！\n"); 

        if((int)me->query("jingli") < 1000)
                return notify_fail("你现在精力不足，不能用「绵绵不绝」！\n"); 

        if((int)me->query("jiali") < 150)
                return notify_fail("你加力太少了，不能用「绵绵不绝」！\n"); 

		//if( target->query_temp("bujue_busy") )
	 			//return notify_fail("对方已经中了「绵绵不绝」！\n"); 
	 	if( me->query_temp("hgmz/bujue") )
	 			return notify_fail("你正在施展「绵绵不绝」！\n"); 
		if(me->query("gender")=="女性") 
        	return notify_fail("你不是男人，尚不能使用绵绵不绝。\n");
		i = 3;
        
		msg = HIY"\n$N忽然猛一吸气，身形跃起，双掌一立，向$n轻轻地缓缓拍出。\n"+ 
              HIC"$N似乎出手不重，但其波浪状的掌气后浪击前浪，一浪高过一浪，连绵不尽！\n"NOR;
        message_vision(msg, me, target);
		//内功加成
		effect = SKILL_D("dulong-dafa")->force_effect(target->query_skill_mapped("force"));

        me->set_temp("hgmz/bujue",1);
		//target->add_temp("apply/defense",-lvl/5);
 
       // target->set_temp("hgmz/bujue", 1);
                me->add("jingli",-100);
                me->add("neili",-300);
        me->add_temp("apply/attack",lvl/5);
        if(i==3) 
			me->add_temp("apply/strength",lvl/20);
        COMBAT_D->do_attack(me, target,0, i);
        
		if(i==3) 
			me->add_temp("apply/strength",-lvl/20);
        COMBAT_D->do_attack(me, target,0, 3);
		//COMBAT_D->do_attack(me, target,0, 3);
        me->add_temp("apply/attack",-lvl/5);
        if(wizardp(me)) 
			write("连击回合数:"+(5-effect)*3 +"!\n");
		
		me->start_perform(4,"「绵绵不绝」");
        call_out("attackob",1, me, target,lvl,(5-effect)*3,i);
    
        return 1;       
}

void attackob(object me,object target,int lvl,int hits,int i)
{
	
   if (!me) return;
  
 /*   if( !target && me) 
   {

		message_vision(HIC"\n$N内力一顿，缓缓收回掌势！\n"NOR, me);
        me->delete_temp("sld/pfm/bujue");
		me->delete_temp("hmgz/bujue");
        me->start_perform(3,"「绵绵不绝」");
        return;
   }
  if( !me )
   {
		if(target) 
		{
				target->delete_temp("bujue_busy");
		
				target->add_temp("apply/defense",lvl/5);
				target->clear_condition("no_perform");
		}
                        
		if( userp(me) ) 
		{
				me->delete_temp("sld/pfm/bujue");
				me->delete_temp("hmgz/bujue");
		}
		return;
	}*/
    if (hits<1 
      //  || !target
        //|| !living(target)
        || me->query_temp("weapon")
        //|| target->is_ghost() 
        //|| me->is_ghost()  
        || !me->is_fighting(target) 
        || me->query("neili") < 800 
        || me->query_skill_prepared("strike") != "huagu-mianzhang" )
	{
        	message_vision(HIY"\n$N内力一顿，再也支持不住充斥这时空的内气，只能缓缓收回掌势！\n"NOR, me);
              //  target->delete_temp("bujue_busy");
              //  target->clear_condition("no_perform");
             // if( userp(me) ) {
                //me->delete_temp("sld/pfm/bujue");
				me->delete_temp("hgmz/bujue");
			  //}
            //  if( userp(me) ) 
                me->start_perform(3,"【绵绵不绝】");
		return;
	}

        if(wizardp(me)) write("连击回合数:"+hits+"!\n");
        me->add_temp("apply/attack",lvl/5);
        COMBAT_D->do_attack(me, target,0, 3);
        if(i==3) 
			me->add_temp("apply/strength",lvl/20);
        COMBAT_D->do_attack(me, target,0, 3);
		COMBAT_D->do_attack(me, target,0, 3);
        if(i==3)
			me->add_temp("apply/strength",-lvl/20);
        me->add_temp("apply/attack",-lvl/5);
        //me->start_perform(2,"「绵绵不绝」");  //取消 一开始bujue就没法halt的 问题。
        call_out("attackob", 2, me,target, lvl, --hits,i);
}

int help(object me)
{
   write(WHT"\n化骨绵掌「"HIC"绵绵不绝"WHT"」："NOR"\n");
   write(@HELP
	化骨绵掌是蛇岛独门武技，是一种极为难练的阴毒功夫，
	被化骨绵掌击中的人开始浑如不觉，但两个时辰后掌力
	发作，全身骨骼会其软如绵，处处寸断，脏腑破裂，惨
	不堪言，再无救治。
	 
	perform strike.bujue

要求：
	当前内力要求 1000 以上；
	当前精力要求 1000 以上；
	化骨绵掌等级 400 以上；
	毒龙大法等级 400 以上；
	伤敌加力需要 150 以上；
	激发且备掌法为化骨绵掌；
	激发招架为化骨绵掌；
	激发内功为毒龙大法；
	使用性别为男性；
	
HELP
   );
   return 1;
}
