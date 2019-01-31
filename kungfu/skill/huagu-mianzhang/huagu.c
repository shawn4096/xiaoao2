// huagu.c 化骨

#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return HIG"化骨诀"NOR;}

int perform(object me, object target)
{
        string msg;
		int count;
        int skill,damage;

       	if( !target ) 
       		target = offensive_target(me);
		
		skill=me->query_skill("huagu-mianzhang",1);
		skill=skill+me->query_skill("dulong-dafa",1)/5;
		damage=me->query_skill("huagu-mianzhang",1)*me->query_str(1)/10;
		count=(int)skill/50;
        if( !target || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me) 
        || target == me
        || !target->is_character())
        	return notify_fail("你想化谁的骨？\n");

        if(target->query("combat_exp") < 80000)
           	return notify_fail("杀鸡焉用牛刀？没必要使用化骨吧。\n");

        if(me->query("age") < 16) 
        	return notify_fail("你现在年龄太小，尚不能使用化骨。\n");
		if(me->query("gender")=="女性") 
        	return notify_fail("你不是男人，尚不能使用化骨诀。\n");

        if(userp(me) 
        && userp(target) 
        && target->query("age") < 17)
                return notify_fail("你的心肠太黑了, 对手无缚鸡之力的玩家也下得了手。\n"); 

        if(userp(me) 
        && userp(target) 
        && target->query("combat_exp") < me->query("combat_exp")/10)
                return notify_fail("你的心肠太黑了, 对手无缚鸡之力的玩家也下得了手。\n");
		
		if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能化骨！\n");

        if((int)me->query_skill("huagu-mianzhang",1)<350)
                return notify_fail("你的化骨绵掌还不够熟练，不能使用！\n");
		
		if(!me->query("quest/sld/hgmz/pass"))
                return notify_fail("你只是听说过的化骨绵掌的威力，但不能使用！\n");
        if( (int)me->query("neili") < 2000 )
                return notify_fail("你现在内力不足，不能化骨！\n");     

        if( (int)me->query("jingli") < 1500 )
                return notify_fail("你现在精力不足，不能化骨！\n");     

        if( (int)me->query_skill("dulong-dafa", 1) < 350 )
                return notify_fail("你的毒龙大法功力不足，不能化骨。\n");
		if( (int)me->query_skill("poison", 1) < 150 )
                return notify_fail("你的毒计功力不足，不能化骨。\n");
		if( (int)me->query_skill("shenlong-yaoli", 1) < 200 )
                return notify_fail("你的神龙药理功力不足，不能化骨。\n");
		if (me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("没有毒龙大法作为根基，是无法使出「化骨」绝技的！\n"); 
		
		if (me->query_skill_mapped("strike") != "huagu-mianzhang"
			||me->query_skill_prepared("strike") != "huagu-mianzhang"
			||me->query_skill_mapped("parry") != "huagu-mianzhang")
                return notify_fail("没有激发化骨绵掌，是无法使出「化骨」绝技的！\n"); 
    	if (me->query_temp("hgmz/huagu"))
                return notify_fail("你正在使用化骨诀！\n"); 
		
        msg = HBYEL+HIW "\n$N忽然脸带诡笑，冷笑几声，双掌不带一点劲气，遥遥地向$p轻轻地拍了一掌！\n"NOR;		

        if( random(me->query_skill("huagu-mianzhang",1)) > (int)target->query_skill("parry",1)/2
			||random(me->query_str(1))>target->query_str(1)/2)
        {
                //tneili = target->query("max_neili");
                //mneili = me->query("max_neili");
         	    msg+=HIR"$n忽觉一股暗劲猛然间拍到心胸当中，一股若有若无的香甜气息顿时袭来！\n"NOR;
        		
				
				target->receive_damage("qi",random(1000),me);
				target->receive_damage("jingli",random(1000),me);
				if (target->query("neili")>1000)
					target->add("neili",-random(1000));

				target->apply_condition("huagu_poison",2);
               	me->add("neili",-300);
				me->add("huagu",-200);
       	} 
        else {
                msg += "$p往旁边一闪身，躲过了这招。\n"NOR;
                //me->start_busy(1);
        }
        message_vision(msg, me, target);
		if (!me->query_temp("hgmz/huagu"))
		{
			message_vision(HIB"$N双手忽然变得绵软无比，施展出化骨绵掌绝技「"+HIW"化骨"+HIB"」!\n"NOR,me);
			me->add_temp("apply/attack",skill/3);
			me->add_temp("apply/damage",skill/6);
			me->add_temp("apply/strike",skill/6);
			me->set_temp("hgmz/huagu",skill);
			if (objectp(target)&&!target->query_condition("huagu_poison"))
			{
				target->apply_condition("huagu_poison",2);
			}
			call_out("remove_effect",1,me,target,count);	
		}
		
		me->add("jingli",-200);
		me->add("neili",-300);
        //me->kill_ob(target);
        if (objectp(target)&&userp(target))
			target->kill_ob(me);
        return 1;     
}

void remove_effect(object me,object target,int count)
{
	int skill;
	
	if (!me) return 0;
	skill=me->query_temp("hgmz/huagu");

	if (count<0 
		||!objectp(target)
		|| !me->is_fighting()
		|| me->query_skill_mapped("strike")!="huagu-mianzhang")
	{
		me->add_temp("apply/attack",-skill/3);
		me->add_temp("apply/damage",-skill/6);
		me->add_temp("apply/strike",-skill/6);
		message_vision(HIG"$N长吁一口气，将暗运的化骨诀暗劲收回丹田。\n"NOR,me);
		me->delete_temp("hgmz/huagu");
		return;
	}
	if (objectp(target)&&random(10)>7)
	{
	
		if (random(me->query("neili"))>target->query("neili")/2 && !random(2))
		{
			message_vision(HBGRN+HIW"$N将毒龙大法的劲气运与掌中，毒气弥漫，$n一不小心中了化骨毒。\n"NOR,me,target);
			target->add_condition("huagu_poison",1);

		}
	}
	if (objectp(target)&&!random(4))
	{
		if (random(me->query("combat_exp"))>target->query("combat_exp")/2 && !random(3))
		{
			message_vision(HBGRN+HIW"$N“嘿”的低喝一声，化骨绵掌劲力发动，一股暗劲顺势拍到$n身上。\n"NOR,me,target);
			target->add_condition("neishang",1);
		}
	}
	
	call_out("remove_effect",2,me,target,count-1);
	return;

}
int help(object me)
{
   write(WHT"\n化骨绵掌「"HIG"化骨诀"NOR"」："NOR"\n");
   write(@HELP
	化骨绵掌是蛇岛独门武技，是一种极为难练的阴毒功夫，
	被化骨绵掌击中的人开始浑如不觉，但两个时辰后掌力
	发作，全身骨骼会其软如绵，处处寸断，脏腑破裂，惨
	不堪言，再无救治。
	化骨绵掌中「化骨诀」绝技主要以阴柔之内劲伤敌，并
	短时间内提升化骨绵掌的威力，同时有概率增加对方附
	加内伤效果，并有概率被化骨毒所伤。因此招过于歹毒
	所以容易引起对方的仇杀。为重要的辅助进攻武技。
	
	注意：化骨绵掌是神龙岛重要武技，相对比较负责，不
	同的设置会产生不同的影响。
	设置：set 化骨绵掌 <内容>
	set 化骨绵掌 擒拿
	效果；能有概率夺取对方兵器，并是对方攻击失效
	set 化骨绵掌 点穴
	效果：能有概率使得对方点中穴道，封招、闭气、忙碌
	set 化骨绵掌 掌力散毒
	效果：通过毒龙大法将体内毒素散发出去，随机性产生
	千里香迷药、七色七重花毒、化骨毒、蛇毒功效。
	set 散毒 <千里香>/<腐骨毒>/<软筋散> 则会小概率让
	对方中毒事件，默认值为蛇毒。
	同时，因为化骨绵掌具有独特特点，是神龙岛最具特色
	的武技，所以，功效将全面提升。请玩家自己尝试。
	 
	指令：perform strike.huagu

要求：
	最大内力要求 3000 以上；
	当前内力要求 1500 以上；
	化骨绵掌等级 350 以上；
	毒龙大法等级 350 以上；
	伤敌加力要求 100 以上。
	神龙药理要求 200 以上；
	毒计等级要求 150 以上；
	激发掌法为化骨绵掌；
	且备掌法为化骨绵掌；	
	激发招架为化骨绵掌；
	激发内功为毒龙大法；
	男性玩家使用；
HELP
   );
   return 1;
}

