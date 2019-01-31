// kunlun-zhang.pfm 乱七八糟
// By jpei
//edit by sohu
#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HIW"昆仑叠掌"NOR; }


int perform(object me, object target)
{
        int i,damage;

        if( !target ) target = offensive_target(me);
        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("昆仑叠掌劲力只能在战斗中使用。\n");       
        if( objectp(me->query_temp("weapon")) )
               return notify_fail("先放下手中的武器再说吧！\n");
        if((int)me->query_skill("strike", 1) < 450 )
                return notify_fail("你的基本掌法太低，无法使用昆仑叠掌之劲力。\n");  
        if((int)me->query_skill("kunlun-zhang", 1) < 450 )
                return notify_fail("你的昆仑叠掌还不够娴熟，不能使出昆仑叠掌之劲力。\n");
        if (me->query_skill_prepared("strike") != "kunlun-zhang"
		   || me->query_skill_mapped("parry") != "kunlun-zhang"
           || me->query_skill_mapped("strike") != "kunlun-zhang")
                return notify_fail("你不使用昆仑叠掌，又岂能使得昆仑叠掌之劲力？！\n");   
        
		if( (int)me->query("max_neili", 1) < 12000 )
                return notify_fail("你内力修为太浅，无法运劲伤敌！\n");                
        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("你现在真气不够，不能发出昆仑叠掌之劲力。\n");
        if(!me->query("quest/kl/klz/diezhang/pass"))
                return notify_fail("你没有学会此招，不能发出昆仑叠掌之劲力。\n");

		if(userp(me) && (int)me->query_skill("xuantian-wuji", 1) < 450 )
                return notify_fail("你的特殊内功等级不够，不能应用昆仑叠掌之劲力。\n");
        if(userp(me) && me->query_skill_mapped("force") != "xuantian-wuji")
                return notify_fail("你的内功心法不对，发挥不出昆仑叠掌劲力之威。\n");                                                                                     
        if (userp(me) && me->query_skill_mapped("parry") != "kunlun-zhang")
                return notify_fail("你目前无法使用昆仑叠掌掌力。\n");

        if( me->query_str(1) < 75 )
                return notify_fail("你的后天臂力不足75，无法使用昆仑叠掌。\n");  

		
		if (me->query("gender")=="男性")
		{
			i=me->query_skill("strike",1)/3  + me->query_skill("kunlun-zhang",1)/3 + me->query_skill("force",1)/3 ;
		}else
			i=me->query_skill("strike",1)/4  + me->query_skill("kunlun-zhang",1)/4 ;



		i = i /4;
		damage=me->query_str()*i;

		if(!userp(me))  i = i / 3;               //npc释放威力降低为1/3^M
 
		
		me->add_temp("apply/strength", i /10);
        me->add_temp("apply/strike", i/2);
        me->add_temp("apply/damage", i/2);
        me->add_temp("apply/attack",i);


		message_vision(HIY"$N运足内力，左手反击一掌，以硬功对硬功，只听得“砰”的一声，硬碰硬的以力对力，力弱者伤，中间实无丝毫回旋余地！\n"NOR,me, target);
        me->add("neili", -300);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

        if ( me->is_fighting(target) ){
			message_vision(MAG"$N跟着双掌齐出，交叉着左掌和$n左掌相接，但掌力之中却分出了一刚一柔之力。\n"NOR,me, target);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query("gender")=="男性"?3:1);
       }

	
        if ( me->is_fighting(target)){
			message_vision(HIG"$n只觉击向对方小腹的一招如打在空处，击$N面门的一招却似碰到了铜墙铁壁。\n"NOR,me, target);
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"),me->query("gender")=="男性"?3:1);
	    }
        if ( me->is_fighting(target)){
			message_vision(HIW"$N使出一招千岩竞秀，连出数招拍向$n的前胸，掌风凌冽之极。\n"NOR,me, target);
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"),me->query("gender")=="男性"?3:1);
	    }

       if ( me->is_fighting(target) && me->query_skill("kunlun-zhang", 1) > 220 )
       {
			message_vision(WHT"猛地里一股巨力撞来，$n自己的劲力反击回来，再加上$N的掌力，直迫得$n口喷鲜血\n"NOR,me, target);        
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), me->query("gender")=="男性"?3:1);
            if (me->query_temp("xtwj/riyue")&&me->query("jiali")>50 && me->query("quest/kl/klz/diezhang/pass"))
		   {
				
           		COMBAT_D->do_attack(target, target, me->query_temp("weapon"), me->query("gender")=="男性"?3:1);
		   }
		   target->apply_condition("neishang",1);
            
			damage = i * 2 ;               
            damage = damage  + random(damage);
			if (damage > 5000 ) damage = 4500+random(1000);
			if( me->query("max_neili") /2 > target->query("neili")  )
            {          
              target->receive_damage("qi", damage,me);
              target->receive_wound("qi", damage/3,me);
            }
			if(userp(me) && me->query("env/damage")) 
				tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR); 
			if(userp(target)&& target->query("env/damage")) 
				tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR);

       }

		me->add_temp("apply/strength",- i /10);
		me->add_temp("apply/strike", -i/2);
		me->add_temp("apply/damage",- i/2);
		me->add_temp("apply/attack",-i);


        me->add("neili", -(200+random(100)));
        me->start_perform(4, "昆仑叠掌");
        return 1;
}



int help(object me)
{
	write(WHT"\n昆仑掌法之「"HIG"昆仑叠掌"WHT"」："NOR"\n");
	write(@HELP
	何足道大战卫天望时见他以少林硬功来战，于是也以
	昆仑掌法来和他对抗，昆仑掌法刚柔相济，厉害无比
	虽然不及降龙十八掌刚猛，但也有其独到之处。
	若运使玄天无极功并加力大于50以上，会有适当的反
	击效果，此招需向何足道请教。
	此招以硬碰硬，纯粹硬功夫，男性有优势。
	
	指令：perform strike.diezhang

要求：
	昆仑掌法等级 450 以上；
	玄天无极等级 450 以上
	基本掌法等级 450 以上
	当前内力要求 1000 以上，
	最大内力要求 12000 以上。
	后天臂力需求 75 以上；
	激发掌法为昆仑掌；
	激发招架为昆仑掌；
	激发内功为玄天无极功；
	空手且备掌法为昆仑掌；
HELP
	);
	return 1;
}
