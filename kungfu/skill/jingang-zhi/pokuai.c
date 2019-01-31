//pokuai.c 以快破快
// 破了对方的龙爪手

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;
string perform_name(){ return RED"以快破快"NOR; }

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
                return notify_fail("大力金刚指「以快破快」只能在战斗中使用。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「以快破快」！\n");   
        if( (int)me->query_skill("jingang-zhi", 1) < 500 )
                return notify_fail("你的大力金刚指还不够娴熟，使不出「以快破快」绝技。\n");
        if (me->query_skill_prepared("finger") != "jingang-zhi"
        || me->query_skill_mapped("finger") != "jingang-zhi")
                return notify_fail("你现在无法使用「以快破快」进行攻击。\n");  
 
        if( (int)me->query_skill("force", 1) < 500 )
                return notify_fail("你的基本内功等级还不够，使不出「以快破快」绝技。\n");
        if (me->query("class") && me->query("class") == "bonze")
		            return notify_fail("你乃禅宗弟子和大力金刚指的凶历之气相悖，不能使用「以快破快」。\n");
        if( me->query("max_neili") < 15000 )
                return notify_fail("你现在内力太弱，使不出「以快破快」。\n");      
        if( (int)me->query("neili") <2000 )
                return notify_fail("你现在真气太弱，使不出「以快破快」。\n");
      
       
        lv = me->query_skill("jingang-zhi",1);
		lvf=me->query_skill("force",1)/2;
        hit = (lv/50);
        if(hit > 8) hit = 8;
        if(hit <3) hit = 3;
        lv += lvf;
		if (target->is_busy())
		{
			message_vision(HIY"$N见$n正处于忙乱之中，自顾不暇，劲力弥漫，大力金刚指威力顿时增加不少。\n"NOR,me,target);
			lv+=lv/4;
		}
        me->add_temp("apply/attack", lv/3);
		me->add_temp("apply/finger", lv/3);
        me->add_temp("apply/damage", lv/5);
       // me->add_temp("apply/parry", -lv/5);
        lzg_msg = HIR"\n$N踏上一步，呼的一拳，便往$n胸口打到，这一招神速如电，拳到中途，左手拳更加迅捷的抢上，后发先至，撞击$n面门。 \n";

      //  if(hit >= 2)lzg_msg += "「捕风式」、「捉影式」";
     //   if(hit >= 4)lzg_msg += "、「抚琴式」、「鼓瑟式」";
      //  if(hit >= 6)lzg_msg += "、「批亢式」、「捣虚式」";
     //   if(hit >= 8)lzg_msg += "、「抱残式」、「守缺式」";
        
        lzg_msg += "\n\n随即脸色自红转青，怒吼一声，纵身扑上，左手或拳或掌，变幻莫测，右手却纯是手指的功夫，拿抓点戳、勾挖拂挑，\n五根手指如判官笔，如点穴撅，如刀如剑，如枪如戟，攻势凌厉之极！\n"NOR;

        message_vision(lzg_msg, me, target);
        me->set_temp("lzg_times",hit);
        me->set_temp("lzg_effect",1);
        me->add_temp("jgz/pokuai", 1);
        me->set_temp("action_flag", member_array("finger", keys(me->query_skill_prepare())));
        //me->set_temp("baocan",hit);
		
        for( i=0; i < hit; i++ )
        {
                
				//me->add_temp("jgz/pokuai", 1);
                COMBAT_D->do_attack(me, target, weapon, 3);
        }


       message_vision(RED"\n这"+chinese_number(hit)+"式指法，如狂风暴雨，以快破快，绵绵不绝，快捷无比！\n"NOR, me);

        me->add("neili", -hit*20+20);
        me->add("jing", -hit*5);
        me->start_perform(5,"「以快破快」");
        me->start_busy(1+random(2));
        me->delete_temp("jgz/pokuai");
        me->delete_temp("lzg_times");
        me->add_temp("apply/attack", -lv/3);
        me->add_temp("apply/damage", -lv/5);
		me->add_temp("apply/finger", -lv/3);
       // me->add_temp("apply/parry", lv/5);
        return 1;
}


int help(object me)
{
        write(HIR"\n大力金刚指之「以快破快」："NOR"\n");
        write(@HELP
	大力金刚指为少林七十二绝技之一，乃是练习擒拿所需指力
	的重要功夫，其又称擒拿手。为软硬相兼之功，刚柔并济之
	劲，阴阳相合之力。练至能气随意注，力随指行方为大成。
	此「以快破快」一经使出，犹如狂风骤雨，连环戳出，凌厉
	狠辣，威猛无比。此式虽有违佛家宗旨，不过颇受俗家弟子
	喜爱，修炼者甚多。
	
	指令;perform finger.pokuai

要求：
	最大内力的需求 3500 以上；      
	当前内力的需求 1500  以上；  
	大力金刚指等级 500 以上；
	基本内功的等级 500 以上；
	激发指法为大力金刚指；
	激发招架为大力金刚指；
	且手无兵器；
	大力金刚指每提升等级 100 lv；
	可追加2 hit 攻击；
	最高可至 8 hit 连击。
	若和大力般若掌互备有特殊功效。
                
HELP
        );
        return 1;
}


