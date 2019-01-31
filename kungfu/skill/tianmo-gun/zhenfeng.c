//zhenfeng.c 针锋相对，以硬破硬 
//cre by sohu@xojh 2014/5
//一棍一剑既针锋相对，棍硬剑柔，双方均以全力点出，则长剑非从中折断不可。
//这一招双方的后劲都是绵绵不绝，棍棒不但会乘势直点过去，而且剑上后劲会反击自身，委实无法可解。
#include <ansi.h>
#include <combat.h>
//inherit SKILL;
//#include <combat_msg.h>
inherit F_SSERVER;

int perform(object me, object target)
{
   int lvl;
   int damage;
   object weapon;
   object weapon1;
   weapon1=target->query_temp("weapon");
   lvl = (int)me->query_skill("tianmo-gun", 1);
   
   if( !target ) target = offensive_target(me);
   if( !objectp(target)
      || !me->is_fighting(target)
      || !living(target)
      || environment(target)!=environment(me))
      return notify_fail("「针锋相对」只能在战斗中对对手使用。\n");

   if (!weapon1
	   ||weapon1->query("skill_type")=="club"
       ||weapon1->query("skill_type")=="spear"
	   ||weapon1->query("skill_type")=="axe"
	   ||weapon1->query("skill_type")=="hammer")
        return notify_fail("「针锋相对」只能和轻兵器类战斗使用。\n");
   if( (int)me->query_skill("tianmo-gun", 1) < 350 )
                return notify_fail("你的天魔棍还不够娴熟，使不出「针锋相对」绝技。\n");

   if (me->query_skill_mapped("force") != "tianmo-gong" 
	   && me->query_skill_mapped("force") != "xixing-dafa" )
             return notify_fail("你所使用的特殊内功不对。\n");  

   if(me->query_skill("xixing-dafa", 1)<350)
      if(me->query_skill("tianmo-gong", 1) < 350)
         return notify_fail("以你现在的内功修为还使不出「以快破快」。\n");  

   if(  me->query_skill_mapped("club") != "tianmo-gun")
                return notify_fail("你现在无法使用「针锋相对」！\n");
   

   if (!objectp(weapon = me->query_temp("weapon")) 
          || weapon->query("skill_type") != "club"
          || me->query_skill_mapped("club") != "tianmo-gun"
          || me->query_skill_mapped("parry") != "tianmo-gun")
                 return notify_fail("你手里无棍，如何使用「针锋相对」？\n");

   if( (int)me->query("max_neili") < 4000)
                return notify_fail("你的内力太弱，使不出「针锋相对」。\n");

   if( (int)me->query("neili") < 1500 )
                return notify_fail("你现在真气太弱，使不出「针锋相对」。\n");

   if( (int)me->query("jingli") < 1500 )
           return notify_fail("你现在太累了，使不出「针锋相对」。\n");

	message_vision(HIY"\n$N随意摆出一个姿势，双手执"+weapon->query("name")+HIY"对准$n手中的"+weapon1->query("name")+HIY"迎了上去！\n"NOR,me,target);
	
	message_vision(HIY"\n双方兵器形成针锋相对局面，但$N棍硬，$n武器轻柔，双方均以全力点出，则"+weapon1->query("name")+HIY"非从中折断不可！\n"NOR,me,target);
    
	if (weapon->query("rigidity")>weapon1->query("rigidity")
		&& me->query("neili",1)>target->query("neili",1)
		&& random(me->query_str())>target->query_str()/3)
   {
	    message_vision(HIR"\n兵器接触，$n忽觉户口一热，"+weapon1->query("name")+HIR"啪得一声当即碎裂落地！\n"NOR,me,target);
		//weapon1->broken("砸断的");
		weapon1->move(environment(me));
		//target->receive_damage("qi",2000+random(5000));
    }
	//第一招
       me->add_temp("apply/attack",  lvl/3);
       me->add_temp("apply/damage",  lvl/6);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                   
       me->add_temp("apply/attack",  -lvl/3);
       me->add_temp("apply/damage",  -lvl/6);

    if (me->is_fighting(target))
    {
		message_vision(HIC"\n这一招双方的后劲都是绵绵不绝，$N棍棒乘势直点过去，"+weapon1->query("name")+HIC"上后劲顿时反击回去,顿时受伤不轻！\n"NOR,me,target);
//兵刃既断，对方棍棒疾点过来，其势只有抛去断剑，双膝跪倒，要不然身子向前一扑，才能消解棍上之势。
        target->receive_wound("qi",random(1000),me);
		if (!weapon1)
        {
		  message_vision(HIY"\n$n手中兵刃既断，$N棍棒疾点过来，其势只有抛去断剑，双膝跪倒，要不然身子向前一扑，才能消解棍上之势！\n"NOR,me,target);
          target->add_busy(2+random(2));
        }
//第二招
       me->add_temp("apply/attack",  lvl/3);
       me->add_temp("apply/damage",  lvl/5);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                   
       me->add_temp("apply/attack",  -lvl/3);
       me->add_temp("apply/damage",  -lvl/5);


    }
	
//第三招
    damage =  me->query_skill("tianmo-gun",1)*3;
    if (me->is_fighting(target)){
	   message_vision(HIB"\n$n手中兵刃既断，$N棍棒疾点过来，其势只有抛去断剑，双膝跪倒，要不然身子向前一扑，才能消解棍上之势！\n"NOR,me,target);
	   if ( damage > 4000 )
         damage = 4000 + (damage - 4000)/100;
 	   target->apply_condition("no_exert", 1+ random(2));
       target->receive_damage("qi", damage, me);
       target->receive_wound("qi", damage/3, me); 
       me->add_temp("apply/attack",  lvl/3);
       me->add_temp("apply/damage",  lvl/5);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                   
       me->add_temp("apply/attack",  -lvl/3);
       me->add_temp("apply/damage",  -lvl/5);
	}
	//参悟臂力45后,第四招
    if(me->query("str") > 45 &&me->is_fighting(target)){
         message_vision(HIR"$N见对方跌跌撞撞，破绽百出，那里还给对方机会，一招「横扫千军」，向$n当胸狂扫而去。\n"NOR,me,target);
         damage =  me->query_skill("tianmo-gun",1)*3;
         if ( damage > 5000 )
                        damage = 5000 + (damage - 5000)/100;
         target->apply_condition("no_perform", 1+ random(2));
         target->receive_damage("qi", damage, me);
         target->receive_wound("qi", damage/4, me);
 
          me->add_temp("apply/attack",  lvl/3);
          me->add_temp("apply/damage",  lvl/5);
          COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                   
          me->add_temp("apply/attack",  -lvl/3);
          me->add_temp("apply/damage",  -lvl/5);
       }
        me->add("jingli", -100);
        me->add("neili", -500);
       
        me->start_busy(1+random(2));
        me->delete_temp("tmgf/zhenfeng");
        me->start_perform(2+ random(2),"「针锋相对」");

        return 1;
}


string perform_name(){ return HIR"针锋相对"NOR; }

int help(object me)
{
        write(HIR"\n天魔棍之「针锋相对」："NOR"\n\n");
        write(@HELP
	天魔棍乃是日月神教十大神魔之”金猿神魔“张乘风和”白猴神魔“张乘云
	兄弟二人所创棍法，威震江湖。后来十长老围攻华山后下落不明，使得
	这门绝技从此失传。不过有人听说在华山后山石洞发现过天魔棍招式。
	具体情况有待于玩家自己探索。
	针锋相对乃是以拙破巧的绝技，对于轻兵器有特殊的破解功效，通过自
	身深厚的功力和武器的硬度可以有效克制除了[棍法]、[斧法]、[枪法]、
	[锤法]外的所有武器，另外，对付空手玩家无效，请玩家慎重使用。也
	就是说这门武功是克制五岳剑派的独特武技。
	
	指令：perform club.zhengfeng

要求：
	最大内力 4000 以上；
	当前内力 1500  以上；
	当前精力 1500  以上；
	天魔棍法等级 350 以上；
	特殊内功等级 350 以上；
	基本棍法等级 350 以上；
	激发招架为天魔棍：
	激发内功为天魔功或吸星大法
	先天臂力大于45，威力大幅增加；
               

HELP
        );
        return 1;
}
