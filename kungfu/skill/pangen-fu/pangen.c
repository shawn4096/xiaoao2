// pangen.c 盘根错节
// cre by sohu@xojh 
#include <ansi.h>
inherit F_SSERVER;
int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, qi_wound;
        me->clean_up_enemy();
        weapon = me->query_temp("weapon");
        target = me->select_opponent();
        skill = me->query_skill("pangen-fu",1);
        if( !(me->is_fighting() ))
            return notify_fail("你只能对战斗中的对手使用「盘根式」斧法。\n");
        if ( !weapon || weapon->query("skill_type") != "axe") 
            return notify_fail("你手中没斧怎么使用「盘根错节」斧法？\n");
        if ( me->query("neili") < 500 || me->query("max_neili") < 1500 )
            return notify_fail("你的内力不够深厚，使不出「盘根式」斧法。\n");
        if( skill < 100 )
            return notify_fail("你的「盘根错节斧」等级不够, 不能使用「盘根式」斧法！\n");
		if( me->query_skill("axe",1) < 100 )
            return notify_fail("你的「基本斧法」等级不够, 不能使用「盘根式」斧法！\n");
		if( me->query_skill("qiantian-yiyang",1) < 100 )
            return notify_fail("你的乾天一阳等级不够, 不能使用「盘根式」斧法！\n");
        if( me->query_str() < 30 )
            return notify_fail("你的膂力不够，无法使用「盘根错节」斧法！\n");
        if ( me->query_skill_mapped("axe") != "pangen-fu"
            || me->query_skill_mapped("parry") != "pangen-fu")
            return notify_fail("你现在无法使用「盘根错节」斧法！\n");
        msg = HBYEL+HIW"\n$N突然大喝一声，形同发疯，手举双斧欺近$n的身前，使出三十六路「盘根错节」斧法。\n"NOR;
        message_vision(msg, me, target);
        ap = me->query("combat_exp") + skill * 400;
        dp = target->query("combat_exp") / 3;
        if( dp < 1 )
                dp = 1;
        
		if (me->query("class")!="bone")
		{
			me->add_temp("apply/damage",(int)me->query_skill("axe",1)/5);
			me->set_temp("pgf/pangen1",1);
		}
            //return notify_fail("你是出家弟子, 不能使用「盘根式」斧法！\n");
/**/
		if( random(ap) > dp )
		{
           if(userp(me))
             me->add("neili",-300);
             msg = HIR "$n只觉得眼前斧影重重，$n来不及躲避，大惊失色，躲避间身中数斧。\n"NOR;
             qi_wound = 3000;
             target->add_busy(2);
             if( qi_wound > target->query("qi") && target->query("qi") > 0 )
                qi_wound = target->query("qi")-1;
             target->receive_damage("qi", qi_wound,me);
             target->receive_wound("qi", qi_wound/3,me);
             target->add("neili", -random(400));
            
             me->start_busy(random(2));
        }
        else{
             msg = HIG "只见$n身形一闪，左右晃动，勉强躲过了$N的「盘根错节」斧法！\n"NOR;
             if(userp(me))
				me->add("neili",-100);
             me->start_busy(3);
        }
		
        message_vision(msg, me, target);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
		
		if (me->query_temp("pgf/pangen1")) {
			me->add_temp("apply/damage",-(int)me->query_skill("axe",1)/5);
			me->delete_temp("pgf/panggen1");
		}
		
		me->start_perform(3,"盘根式");
        return 1;
}

string perform_name() {return HIC"盘根式"NOR;}

int help(object me)
{
   write(WHT"\n盘根错节斧法之「"HIC"盘根式"WHT"」："NOR"\n\n");
   write(@HELP
	盘根错节斧乃是大理渔樵耕读四大护卫南山樵子古竺诚的独门武技，
	其斧法虽然招式平凡，但却在平凡的招式中蕴藏杀机。斧沉力猛，无
	论是上阵杀敌还是地下单打独斗都甚是威猛。盘根式就是奋力一招。
	砍向对方，让对方躲无所躲，防无所防。
	
	perform axe.pangen
   
要求:
	最大内力 1500 以上；
	当前内力 500  以上；
	盘根斧法 200  以上；
	基本斧法 200  以上；
	乾天一阳 200  以上；
	后天臂力 30   以上；
	激发斧法为盘根斧法；
	激发斧法为盘根斧法；
	装备斧头。

          
HELP
   );
   return 1;
}
