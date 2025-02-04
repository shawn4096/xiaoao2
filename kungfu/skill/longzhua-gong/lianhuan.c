// lianhuan.c 龙爪功连环八式
// By Spiderii 变态修改。。。。设定为高攻击，高伤害！代价是降低自身防御
/*
    空性突然间大喝一声，纵身而上，双手犹如狂风骤雨，「捕风式」、「捉影式」、「抚琴式」、「鼓瑟式」、「批亢式」、「捣虚式」、「抱残式」、「守缺式」，八式连环，疾攻而至。张无忌神定气闲，依式而为，捕风捉影、抚琴鼓瑟、批亢捣虚、抱残守缺，接连八招，招招后发而先至。
    空性神僧这八式连环的龙爪手绵绵不绝，便如是一招中的八个变化一般，快捷无比，
*/

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
string perform_name(){ return RED"连环八式"NOR; }

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lv,lvf, i, hit;
         string weapon, lzg_msg;

        if( !target ) target = offensive_target(me);
        
		if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
                return notify_fail("龙爪功「连环八式」只能在战斗中使用。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「连环八式」！\n");   
        if( (int)me->query_skill("longzhua-gong", 1) < 250 )
                return notify_fail("你的龙爪功还不够娴熟，使不出「连环八式」绝技。\n");
        if (me->query_skill_prepared("claw") != "longzhua-gong"
        || me->query_skill_mapped("claw") != "longzhua-gong")
                return notify_fail("你现在无法使用「连环八式」进行攻击。\n");  

	    if( me->query_skill_mapped("force") != "yijin-jing" )
		        return notify_fail("你现在使用的内功，不能使用「连环八式」。\n");
        if( (int)me->query_skill("yijin-jing", 1) < 250 )
                return notify_fail("你的易筋经等级还不够，使不出「连环八式」绝技。\n");
        if (me->query("class") && me->query("class") != "bonze")
		            return notify_fail("你非禅宗弟子，不能使用「连环八式」。\n");
        if( me->query("max_neili") < 3500 )
                return notify_fail("你现在内力太弱，使不出「连环八式」。\n");      
        if( (int)me->query("neili") <1500 )
                return notify_fail("你现在真气太弱，使不出「连环八式」。\n");
      
        
        lv = me->query_skill("longzhua-gong",1);
		lvf=me->query_skill("yijin-jing",1)/2;
        hit = (lv/50);
        if(hit > 8) hit = 8;
        if(hit <2) hit = 2;
        lv += lvf;
		if (target->is_busy())
		{
			message_vision(HIY"$N见$n正处于忙乱之中，自顾不暇，易筋经运于爪中，龙爪功威力顿时增加不少。\n"NOR,me,target);
			lv+=lv/4;
		}
        me->add_temp("apply/attack", lv/3);
		me->add_temp("apply/claw", lv/3);
        me->add_temp("apply/damage", lv/5);
       // me->add_temp("apply/parry", -lv/5);
        lzg_msg = HIR"\n$N突然间大喝一声，纵身而上，双手犹如狂风骤雨: \n";

        if(hit >= 2)lzg_msg += "「捕风式」、「捉影式」";
        if(hit >= 4)lzg_msg += "、「抚琴式」、「鼓瑟式」";
        if(hit >= 6)lzg_msg += "、「批亢式」、「捣虚式」";
        if(hit >= 8)lzg_msg += "、「抱残式」、「守缺式」";
        
        lzg_msg += "，\n"+chinese_number(hit)+"式连环，疾攻而至！\n"NOR;

        message_vision(lzg_msg, me, target);
        me->set_temp("lzg_times",hit);
        me->set_temp("lzg_effect",1);
        me->add_temp("lzg/lianhuan", 3);
        me->set_temp("action_flag", member_array("claw", keys(me->query_skill_prepare())));
        //me->set_temp("baocan",hit);
		
        for( i=0; i < hit; i++ )
        {
                
				me->add_temp("lzg/lianhuan", 1);
                COMBAT_D->do_attack(me, target, weapon, random(2)?3:1);
        }


       message_vision(HIY"\n这"+chinese_number(hit)+"式连环的龙爪手绵绵不绝，便如是一招中的"+chinese_number(hit)+"个变化一般，快捷无比！\n"NOR, me);

        me->add("neili", -hit*20+20);
        me->add("jing", -hit*5);
        me->start_perform(3,"「连环八式」");
        me->start_busy(1+random(2));
        me->delete_temp("lzg/lianhuan");
        me->delete_temp("lzg_times");
        me->add_temp("apply/attack", -lv/3);
        me->add_temp("apply/damage", -lv/5);
		me->add_temp("apply/claw", -lv/3);
       // me->add_temp("apply/parry", lv/5);
        return 1;
}


int help(object me)
{
        write(HIR"\n龙爪功之「连环八式」："NOR"\n");
        write(@HELP
        龙爪功为少林七十二绝技之一，乃是练习擒拿所需指力的重要功夫，其又称擒拿手。
        为软硬相兼之功，刚柔并济之劲，阴阳相合之力。练至能气随意注，力随指行方为
        大成。此「连环八式」一经使出，犹如狂风骤雨，连环抓出，凌厉狠辣，威猛无比。
        此式虽有违佛家宗旨，不过颇受武僧喜爱，修炼者甚多。

        要求：  最大内力 3500 以上；      
                当前内力 1500  以上；  
                龙爪功等级 250 以上；
                易筋经等级 250 以上；
                激发爪法为龙爪功；
                激发招架为龙爪功；
                且手无兵器；
                龙爪功每提升等级 100 lv；
                可追加2 hit 攻击；
                最高可至 8 hit 连击。
				若和一指禅互备有特殊功效。
                
HELP
        );
        return 1;
}


