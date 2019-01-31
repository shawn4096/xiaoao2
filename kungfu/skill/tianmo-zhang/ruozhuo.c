// ruozhuo.c 若拙实巧
// Cre by sohu@xojh 2014/6

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>


int perform(object me,object target)
{     
      	
		if( (int)me->query_skill("tianmo-zhang",1) < 350 )
           	return notify_fail("你的天魔掌不够娴熟，不能使用「若拙实巧」绝技！\n");
      
      	if( (int)me->query_skill("strike",1) < 350 )
           	return notify_fail("你的基本掌法等级不够，不能使用「若拙实巧」！\n");  
      
      	if( (int)me->query_skill("tianmo-gong", 1) < 350 )
           	return notify_fail("你的天魔功法等级不够，不能使用「若拙实巧」！\n");
        if ( !me->query("quest/hmy/tmzf/ruozhuo/pass"))
            return notify_fail("你尚未理解天魔掌诀窍，不能使用「若拙实巧」！\n");
      	if (me->query_skill_mapped("force") != "tianmo-gong")
			if (me->query_skill_mapped("force") != "xixing-dafa")
           	return notify_fail("你所使用的内功不是日月派功法。\n");
        if( objectp(me->query_temp("weapon")) )
            return notify_fail("你必须空手才能使用「若拙实巧」！\n");
      	if( (int)me->query("max_neili") < 3500 )
           	return notify_fail("你的内力太弱，不能使用「若拙实巧」！\n");
       	if( (int)me->query_temp("tmzf/ruozhuo"))
           	return notify_fail("你正在使用「若拙实巧」！\n"); 
      	if( (int)me->query("neili") < 2000 )
           	return notify_fail("你的内力太少了，无法使用出「若拙实巧」！\n"); 
        
        return (int)call_other( this_object(), "main", me,target);
}

int main(object me,object target)
{
	    object tweapon;
	    int skill;
  	    int i;
        tweapon=target->query_temp("weapon");
      	if( me->query("neili") < 800 || me->query("jingli") < 100  )
                return notify_fail("你目前无法使用「若拙实巧」！\n");   
        i=me->query_skill("tianmo-zhang", 1);       	
	    if (me->query_skill_mapped("force")=="tianmo-gong") 
			i = me->query_skill("tianmo-zhang", 1) + me->query_skill("tianmo-gong", 1)/4;
        if (me->query_skill_mapped("force")=="xixing-dafa")
			i = me->query_skill("tianmo-zhang", 1) + me->query_skill("xixing-dafa", 1)/2;
	        		
       	i = i + random(i);
       	i /= 2;

	    me->add("neili", -i);
        me->add("jingli", -50);
        message_vision(YEL"\n$N凝神而立，招式极其简单，但却显露朴实无华之意，看似笨拙实难招架！正是天魔掌法精华绝技「若拙实巧」。\n" NOR,me);
       
        me->set_temp("tmzf/ruozhuo", i);
    
       if (me->query("env/天魔掌")=="若拙"&&objectp(target)&&me->is_fighting(target))
        {
			message_vision(HIC"$N天魔掌越来越慢，但其掌力却更见浑厚，迫使$n难于进攻。\n"NOR,me,target);
			if (random(me->query_skill("strike",1))>target->query_skill("parry",1)/3)
			{
				message_vision(HIY"$N掌风凌冽，$n一不小心为掌风所带动，身形顿时滞缓。\n"NOR,me,target);
				target->add_busy(2+random(2));
			}else 
				message_vision(YEL"$n经验非常丰富，伸手格挡后随即后撤，躲开了$N的攻击。\n"NOR,me,target);
            //克制千叶
			if (target->query_skill_prepared("hand")=="qianye-shou"&& random(me->query_skill("tianmo-zhang",1))>target->query_skill("qianye-shou",1)/2)
            {
				message_vision(HIY"$N见$n招式越来越快，正是少林绝技千叶手，不敢怠慢，将招式使得越来越慢，正应了若拙实巧的要义。\n"NOR,me,target);
				tell_object(target,HIC"你觉得对方的慢招正好克制自己的招式，不由得一慌。\n"NOR);
				target->apply_condition("no_perform",2);
				target->add_busy(2+random(3));

            }
			if (!tweapon)
			{
				//message_vision(HIG"$N见$n招式越来越快，心中极为谨慎，将天魔掌的若拙实巧的要以发挥的淋漓精致。\n"NOR,me,target);
				target->add_temp("apply/attack",-i);
				target->add_temp("apply/damage",-i/4);
				target->add_temp("apply/dodge",-i/4);
				message_vision(HIC"$n忽然感觉对方这极慢的招式似乎一堵墙一样向自己压了过来，身形滞缓。\n"NOR,me,target);
				target->set_temp("tmzf/ruozhuo",i);
				
				call_out("tmzf_effect",(int)i/20,target);
			}

        }      

		me->add_temp("apply/attack", i);
        me->add_temp("apply/strike", i);
        me->add_temp("apply/damage", i/6);
		//message_vision("i=="+i,me,target);
		//if (objectp(target)&&me->is_fighting())
			call_out("check_fight", 2 , me,i/4);
        
		if(me->query_skill("tianmo-zhang",1)<350) me->start_busy(1);

        return 1;
}

void check_fight(object me,int i)
{       
        int j;
		object weapon;
        if( !me ) return; 
        if( !intp(j = me->query_temp("tmzf/ruozhuo")) ) return;

        weapon=me->query_temp("weapon");

        if( !me->is_fighting() 
	    ||  i < 1
        ||  weapon
        ||  me->query_skill_mapped("strike") != "tianmo-zhang"
        ||  me->query_skill_prepared("strike") != "tianmo-zhang")
		{
        	
			me->add_temp("apply/attack", -j);
        	me->add_temp("apply/strike", -j);
        	me->add_temp("apply/damage", -j/6);
        	me->delete_temp("tmzf/ruozhuo");
        	me->add("neili", -j );
        	me->start_perform(3, "若拙实巧");
			//若中了若拙，清除掉
		
        	//if( living(me))
			   message_vision(YEL "\n$N张嘴呼出一口轻气，精神缓缓松弛了下来。\n" NOR, me);   
        	return;
        }
	    if (me->query_skill("tianmo-zhang",1)<450)
	       me->start_perform(2, "若拙实巧");
        call_out("check_fight", 1, me,i--);
}
int tmzf_effect(object target)
{
	int i;
	if (!target) return 0;
	i=target->query_temp("tmzf/ruozhuo");
	
	target->add_temp("apply/attack",i);
	target->add_temp("apply/damage",i/4);
	target->add_temp("apply/dodge",i/4);
	target->delete_temp("tmzf/ruozhuo");

	message_vision(HIC"$N长吁一口真气，将天魔掌所造成的压力缓缓释放。\n"NOR,target);
	return 1;
}

string perform_name(){ return HIC"若拙实巧"NOR; }
int help(object me)
{
	write(HIG"\n天魔掌「若拙实巧」：\n"NOR);
	write(@HELP
	天魔掌乃是日月神教历代高手千锤百炼的空手武技，乃是门下弟子
	习练的主要空手武技。后来任我行在少林与方证大师一战，天魔掌
	的奥妙方为人所知。这招若拙实巧就是任我行所授的绝学。看似出
	招缓慢，其实威力奇大。对少林千叶手有一定的克制效果。对空手
	连击武技有一定约束效果。需向任我行请教方可习得。
	注意：吸星大法有特殊效果，此武技350级小飞，450级后大飞。
	
	注意：set 天魔掌 若拙

	指令：perform strike.ruozhuo

要求：	
	天魔掌法等级 350 以上；
	基本掌法等级 350 以上；
	天魔功法等级 350 以上（或吸星大法）；
	最大内力需求 3500 以上； 
	当前内力需求 2000 以上。
HELP
	);
	return 1;
}

