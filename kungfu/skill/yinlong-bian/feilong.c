
// feilong.c 九阴银龙鞭之「飞龙诀」
// Build by fengyue@CB 2008-10-20
// 参与测试 zaqz,howkjie,axj@CB


#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int lvl, skill, skill1,jiali;
	object weapon;
	string name;

	weapon = me->query_temp("weapon");
	if (weapon) name = weapon->query("name");

	if( !target ) target = offensive_target(me);
     
	if( !objectp(target)
	 || !me->is_fighting(target) )
		return notify_fail("「飞龙诀」只能在战斗中对对手使用。\n");

	if (!weapon
	 || weapon->query("skill_type") != "whip"
	 || me->query_skill_mapped("whip") != "yinlong-bian")
		return notify_fail("你不用鞭子怎么使用「飞龙诀」？\n");             

	if( (int)me->query_skill("yinlong-bian",1) < 450 )
		return notify_fail("你的九阴银龙鞭不够娴熟，不能使用「飞龙诀」！\n");
      
	if( (int)me->query_skill("whip",1) < 450 )
		return notify_fail("你的基本鞭法等级不够，不能使用「飞龙诀」！\n");  

	if( (int)me->query_skill("claw", 1) < 450 )
		return notify_fail("你的爪法等级不够，不能使用「飞龙诀」！\n");
  
	if( (int)me->query_skill("force", 1) < 450 )
		return notify_fail("你的内功等级不够，不能使用「飞龙诀」！\n");

	if( (int)me->query("max_neili") < 10000 )
		return notify_fail("你的内力太弱，不能使用「飞龙诀」！\n");

	if( (int)me->query("neili") < 500 )
		return notify_fail("你的内力太少了，无法使用出「飞龙诀」！\n");

	if( (int)me->query("jingli") < 500 )

		return notify_fail("你的精力太低了，无法使用出「飞龙诀」！\n");
/*

这段判断语句该如何写。如果jifa claw 不是 jybgz,或者不是9ysz ...
怎么执行下来都是不对的。*/
	if (me->query_skill_mapped("claw") != "jiuyin-baiguzhua"
	 && me->query_skill_mapped("claw") != "jiuyin-shenzhua")
		return notify_fail("你没有激发九阴白骨爪，现在无法使用「飞龙诀」进行攻击。\n");
		
    if (me->query_skill(me->query_skill_mapped("claw"),1)<450)
		return notify_fail("你的"+ me->query_skill_mapped("claw") +"等级太低，现在无法使用「飞龙诀」进行攻击。\n");
    		
		
	skill = me->query_skill("yinlong-bian", 1);
	skill1 = me->query_skill("claw", 1);
    lvl =  skill / 4;

	lvl += skill1 / 5;

	
	if (me->query("quest/em/zzr/pass"))
	{
		message_vision(HIC"\n$N想起周芷若的指点，右手"+name+HIW"猛的甩出，内劲奇诡莫测，软鞭便如灵蛇颤动。\n"NOR, me,target);

		lvl+=me->query_skill("jiuyin-zhengong",1);
	}
	jiali = me->query("jiali");

	message_vision(HIW"\n$N身形一闪一晃，右手"+name+HIW"猛的甩出，正如天外游龙，出手如电，矢矫而至。\n"NOR, me,target);
	message_vision(HIB"$N左手食中二指屈成爪状，向$n接连戳去，一连七爪，全是对向头脸与前胸重穴！\n"NOR, me,target);
	me->add("neili", -350); 
	me->add("jingli", -100); 

	if ( skill > 200)
		lvl = to_int((skill+skill1)/8.0* skill/200.0);

	if ( jiali > 100) {
		me->set("jiali", 100);
		me->set_temp("lyjiali", 1);
	}

	me->set_temp("feilong", 1);
	me->add_temp("apply/attack", lvl);
	me->add_temp("apply/damage", lvl/2);
	me->add_temp("apply/claw", lvl);
	me->add_temp("apply/whip", lvl);
//第一招
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

//第二招
	if ( me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);

         	weapon->unequip(); 

// 第一种情况，判断9ybgz，并且判断有没有9yzg支持。为了防止玩家激发别的空手。

	if( me->is_fighting(target) 
		&& me->query_skill_prepared("claw") == "jiuyin-baiguzhua" 
		&& me->query_skill_mapped("claw") == "jiuyin-baiguzhua" )
	{
		
		if (me->query("quest/jiuyin2/jybgz/pass"))
			 {
				 message_vision(HIR"\n$N运使九阴白骨爪，指爪挥动间暗光流动，显然已得梅超风独门真传，招数诡异狠辣，威力无比！\n"NOR, me,target);
                target->set_temp("must_be_hit",1);
                target->add_busy(4);
                COMBAT_D->do_attack(me, target, 0, 3);
				COMBAT_D->do_attack(me, target, 0, 3);
                message_vision(HIR"\n$N左手跟着前探，九阴白骨爪五指便抓向$n头顶,眼见这一抓之下，立时便是头骨破碎之灾！\n"NOR, me,target);    				
               	              
                COMBAT_D->do_attack(me, target, 0, 3);
                target->delete_temp("must_be_hit",1) ; 				 
			 }		
         else if(me->query_skill("jiuyin-zhengong",1) >= 120)
         {
			 
		    	message_vision(HIM"\n$N运使九阴白骨爪，指爪挥动间九阴真气嘶嘶作响，威力大增，招数诡异狠辣，威力无比！\n"NOR, me,target);
                target->set_temp("must_be_hit",1);
                target->add_busy(3);
                COMBAT_D->do_attack(me, target, 0, random(2)?1:3);
				//COMBAT_D->do_attack(me, target, 0, random(2)?1:3);                      
               	message_vision(HIM"\n$N左手跟着前探，九阴白骨爪五指便抓向$n胸口,眼见这一抓之下，立时便是开膛破胸之祸！\n"NOR, me,target);         
                COMBAT_D->do_attack(me, target, 0, random(2)?1:3);
                target->delete_temp("must_be_hit",1) ; 		
         }		 
		  
		  COMBAT_D->do_attack(me, target, 0, random(2)?1:3); 
          COMBAT_D->do_attack(me, target, 0, random(2)?1:3); 

}
// 第2种情况，判断激发9阴神爪和九阴真功。

	if( me->is_fighting(target) 
		&& me->query_skill_prepared("claw") == "jiuyin-shenzhua" 
		&& me->query_skill_mapped("claw") == "jiuyin-shenzhua" )
	{
         if( me->query_skill("jiuyin-zhengong",1) >= 120 )
              {
              		if (me->is_fighting(target)&& objectp(target))
					{
						
						message_vision(HIM"\n$N爪法得九阴真气支持，威力远非九阴白骨爪可比，招数精奇绝伦，威力无比！\n"NOR, me,target);
                        target->set_temp("must_be_hit",1);
                        target->add_busy(5);
                        COMBAT_D->do_attack(me, target, 0, 3);
					}
					if (me->is_fighting(target)&& objectp(target))
					{
               			message_vision(HIM"\n$N左手跟着前探，九阴神爪发动，便抓向$n胸口,眼见这一抓到来，立时便是开膛破胸之祸！\n"NOR, me,target);
                        target->set_temp("must_be_hit",1);
                        COMBAT_D->do_attack(me, target, 0, 3);
                        target->delete_temp("must_be_hit",1) ; 
					}
               }
			   COMBAT_D->do_attack(me, target, 0, random(2)?1:3);  
			if (me->is_fighting(target)&& objectp(target))
				COMBAT_D->do_attack(me, target, 0,3); 
            if (me->is_fighting(target)&& objectp(target))
				COMBAT_D->do_attack(me, target, 0, 3); 
			           
	}
    weapon->wield();

	if ( me->query_temp("lyjiali"))
	{
 		me->set("jiali", jiali);
		me->delete_temp("lyjiali");
	}

	me->add_temp("apply/attack", -lvl);
	me->add_temp("apply/whip", -lvl);
	me->add_temp("apply/damage", -lvl/2);
	me->add_temp("apply/claw", -lvl);
        me->start_busy(1);
	me->delete_temp("feilong");
	me->start_perform(5, "「飞龙诀」");
	return 1;
}

string perform_name(){ return HIW"飞龙诀"NOR; }

int help(object me)
{
	write(HIW"\n九阴银龙鞭之「飞龙诀」："NOR"\n\n");
	write(@HELP
	九阴银龙鞭是九阴真经下卷中著名的武功，和摧心掌、九阴白骨抓
	齐名，这鞭法施展不靠内力，只需要足够的技巧就能施展攻敌不备
	而且防御起来也是风雨不透，甚是严密。
	飞龙诀是运使银龙鞭和九阴真经下卷的武功配合，一连几招，诡异
	莫测，鞭中夹杂爪法，爪子中蕴含鞭子。远近攻击，兔起鹘落，防
	不胜防。峨眉弟子若解开周芷若谜题，则本招会飞跃。
	倘若九阴白骨爪能得梅超风告知真谛，威力可媲美九阴神爪。

指令：perform whip.feilong

要求：
	当前内力需求 500 以上；
	最大内力需求 10000 以上；
	当前精力需求 500 以上；
	九阴银龙鞭等级 450 以上；
	九阴神(白骨爪)爪 450 以上；	
	基本内功需求 450 以上；	
	激发鞭法,招架为九阴银龙鞭；
	且手持兵器。

注意：如果搭配以下技能，更有意想不到的效果效果        
	激发爪法为九阴白骨爪或九阴神爪并且备爪法；
	九阴真功等级 120 以上(无需激发)；		

		

HELP
        );
        return 1;
}
