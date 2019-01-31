//风雷 fenglei.c 

#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return HIC"风雷轻烟"NOR;}

int perform(object me, object target)
{
        object weapon;
        int i,a;

        weapon = me->query_temp("weapon");
       
        if( !target ) target = offensive_target(me);
         if( !objectp(target)) return notify_fail("你要对谁攻击？\n");

        if( !me->is_fighting() )
                return notify_fail("「风雷轻烟」只能在战斗中使用。\n");
 
        weapon = me->query_temp("weapon");
        if (!weapon || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "duanjia-jianfa")
                return notify_fail("手中无剑,你怎么使得出「风雷轻烟」！\n");

        if( (int)me->query("max_neili") < 1300 )
                return notify_fail("你的最大内力不够！\n");
		if( (int)me->query("max_jingli") < 900 )
                return notify_fail("你的最大精力不够！\n");
                
        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不够！\n");

        if( (int)me->query("jingli") < 300 )
                return notify_fail("你的精力不够！\n");

        if( (int)me->query_str() < 25 )
                return notify_fail("你的臂力不够！\n");

        if( (int)me->query_skill("duanjia-jianfa",1) < 100 )
                return notify_fail("你的段家剑法等级不够！\n");
        if( (int)me->query_skill("qingyan-zhang",1) < 100 )
                return notify_fail("你的五罗轻烟掌等级不够！\n");
        if(!me->query_skill("kurong-changong", 1))
          if(me->query_skill("qiantian-yiyang", 1) < 100)
                return notify_fail("以你现在的内功修为还使不出「风雷轻烟」。\n");        
         
        if (me->query_skill_mapped("force") != "kurong-changong" )
          if(me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail("你所使用的内功不对。\n");

        if( (int)me->query_skill("duanjia-jianfa",1) < 100 )
                return notify_fail("你的段家剑法还不到家，无法使用「风雷轻烟」绝技！\n");

        if( (int)me->query_skill("sword",1) < 100 )
                return notify_fail("你的剑法造诣不够，无法使用如此高深的「风雷轻烟」绝技！\n");

        if( (int)me->query_skill("qingyan-zhang",1) < 100 ||
            me->query_skill_mapped("strike") != "qingyan-zhang")
                return notify_fail("你的五罗轻烟掌还不到家，无法使用「风雷轻烟」绝技！\n");

        if( (int)me->query_skill("strike",1) < 100 )
                return notify_fail("你的掌法造诣不够，无法使用如此高深的「风雷轻烟」绝技！\n");

        if (me->query_skill_prepared("strike") != "qingyan-zhang"
		    || me->query_skill_mapped("strike") != "qingyan-zhang")
                return notify_fail("你激发的掌法不对，无法使用「风雷轻烟」进行攻击。\n");
        if (me->query_skill_mapped("sword") != "duanjia-jianfa"
			 || me->query_skill_mapped("parry") != "duanjia-jianfa")
                return notify_fail("你激发的剑法不对，无法使用「风雷轻烟」进行攻击。\n");

        if( (int)me->query_skill("tianlong-xiang",1) < 100 )
                return notify_fail("你的天龙翔还不到家，无法使用「风雷轻烟」绝技！\n");
        
        i = (int)(me->query_skill("duanjia-jianfa",1)+me->query_skill("qingyan-zhang",1))/5;
        if (i < 250) target->start_busy(1+random(2));
        message_vision(BLU"\n$N蹂身而上，左手"HIM"五罗轻烟掌"BLU"，右手"HIW"段家剑法"BLU"，施展绝招「"HIR"风雷轻烟"BLU"」！\n"NOR, me,target);

		if(me->query("quest/tls/ailao/pass")){
		   message_vision(HIC"$N将自己所领悟的"+HIR+"哀牢山剑意"+HIC+"运用在段家剑法中，剑气纵横，威力陡增！\n"NOR,me);
		   //俗家有优势
		   i=i+me->query_skill("qiantian-yiyang",1)/10;
		}
		if (i > 150) i=150;

        me->add("neili",-(150+random(50))); 
        me->add("jingli",-50); 
		me->set_temp("fenglei",4);
		for(a=0;a<4;a++)
        {
		    if(me->query("quest/tls/ailao/pass"))
		     {
                     //    message_vision(HIC"$N将自己所领悟的"+HIR+"哀牢山剑意"+HIC+"运用在段家剑法中，威力陡增！\n"NOR,me);
						 		
						if(objectp(target)) target->add_busy(1);

						 me->add_temp("apply/attack", i/3 );                        
                         me->add_temp("apply/damage", i/5   );
                         me->add_temp("apply/sword", i /5  );                         
		                 switch(random(2))
						 {
							case 0:
						      if(me->is_fighting(target))
		                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3); 
							  break;
							case 1:
						      weapon->unequip();
                             // if(me->is_fighting(target))
								me->add_temp("apply/strike", i /4  );
		                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3); 
								me->add_temp("apply/strike", -i /4);
							  weapon->wield();
							  break;
					     }
                         me->add_temp("apply/sword", -i /5);                      
                         me->add_temp("apply/damage", -i/5 );
                         me->add_temp("apply/attack", -i/3 );
              } else {
		                 me->add_temp("apply/attack", i /4 );                         
                         me->add_temp("apply/sword", i /6 );
                         me->add_temp("apply/damage", i /6 );
                         switch(random(2))
						{
							case 0:
						      if(me->is_fighting(target))
		                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1); 
							  break;
							case 1:
						      weapon->unequip();
                             // if(me->is_fighting(target))
								me->add_temp("apply/strike", i /4  );
		                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1); 
							  me->add_temp("apply/strike", -i /4);
							  weapon->wield();
							  break;
					     }
						 me->add_temp("apply/damage", - i/6  );
                         me->add_temp("apply/sword", - i /6 );
                        // me->add_temp("apply/strike", - i /4 );
                         me->add_temp("apply/attack", - i /4 );
			}
        }
        
		me->delete_temp("fenglei");
		//me->delete_temp("fl_sword");
        me->start_perform( 4 + random(2), "「风雷轻烟」");
		
me->start_busy(2);
        return 1;
}

int help(object me)
{
        write(HIR"\n段家剑法之「风雷轻烟」："NOR"\n\n");
        write(@HELP
	风雷轻烟乃是大理段家剑法的精粹，大理乃皇族，同时
	也是武林人士，除了大理一阳指绝世武功外，还有其他
	武技享誉江湖。风雷四击乃是快速连出四招，夹杂着轻
	烟掌的招式。解开风雷轻烟谜题剑法飞跃。
	
	perform sword.fenglei

要求：
	当前内力 500 以上；
	最大内力 1300 以上；
	最大精力 900 以上；
	基本掌法 100 级；
	五罗轻烟掌 100级；
	段家剑法 100级；
	乾天一阳 100 级；
	臂力要求 25 以上；
	激发掌法为轻烟掌
	激发剑法为段家剑法；
	激发招架为段家剑法；
	备掌法为五罗轻烟掌；
	且手持兵器。

HELP
        );
        return 1;
}
