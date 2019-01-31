//蛇形脚,作为过渡用
////2014-08-07
//by sohu
#include <ansi.h>
#include <combat.h>

 inherit F_SSERVER;

 string perform_name() {return HIB"蛇形脚"NOR;}
int sltf_shexing(object me,int count);


 int perform(object me, object target)
 {
	 //对象定义
        object weapon;
        string msg,result;
        int skill; 
	//使用条件判断
		if( !target ) target = offensive_target(me);

		if( !objectp(target) || !target->is_character() || !me->is_fighting(target) )
                 return notify_fail("蛇形脚只能对战斗中的对手使用。\n");

		if (me->query_skill_prepared("leg") != "shenlong-tuifa"
            || me->query_skill_mapped("leg") != "shenlong-tuifa"
			|| me->query_skill_mapped("parry") != "shenlong-tuifa" )
                return notify_fail("你现在无法使用蛇形脚进行攻击。\n");  

         if((int)me->query_skill("shenlong-tuifa", 1) < 220 )
                 return notify_fail("你的神龙腿法不够娴熟，不能使用蛇形脚。\n");

		 if((int)me->query_skill("leg", 1) < 220 )
                 return notify_fail("你的基本腿法不够娴熟，不能使用蛇形脚。\n");

         if((int)me->query_skill("dulong-dafa", 1) < 220 )
                 return notify_fail("你的毒龙大法不够深厚，不能使用蛇形脚。\n");

         if((int)me->query("max_neili") < 1000)
                 return notify_fail("你最大内力太弱，不能使用蛇形脚。\n");
		  if((int)me->query("max_neili") < 500)
                 return notify_fail("你当前内力太弱，不能使用蛇形脚。\n");


         if((int)me->query("jingli") < 500)
                 return notify_fail("你现在精力太弱，不能使用蛇形脚。\n");

         if( me->query_temp("weapon")) 
                 return notify_fail("你拿着兵器无法使用蛇形脚。\n");

        if (me->query_skill_mapped("parry") != "shenlong-tuifa")
                return notify_fail("你没有激发神龙腿法为招架！\n");

		if( me->query_skill_prepared("leg") != "shenlong-tuifa")
				return notify_fail("你没有激活腿法为当前武功招式！\n");

         if(me->query_skill_mapped("force") != "dulong-dafa")
                 return notify_fail("你现在所使用的内功同毒龙大法向抵触，不能使用蛇形脚。\n");
         if(me->query_temp("sltf/shexing"))
                 return notify_fail("你现在正在使用蛇形脚绝技。\n");

	//起式描述
	message_vision(BLU"$N双腿如蛇形之状，忽东忽西，蜿蜒前行，和以往武技大不相同，正是「"HIC"蛇形脚"BLU"」绝技。\n\n"NOR,me,target);
	// 第1hit
	
	  skill=me->query_skill("shenlong-tuifa",1);
	  if (me->query("gender")=="男性")
	  {
		skill+=me->query_skill("xunsheshu",1);
		message_vision(HIG"$N将在训蛇的经验融会贯通，灵光一闪间，运用此绝技更是得心应手，有如神助。\n\n"NOR,me);

	  }
	  //收招描述
	 me->add_temp("apply/attack",skill/8);
	 if (me->query("gender")=="男性") me->add_temp("apply/damage",skill/8);
	 me->add_temp("apply/leg",skill/6);
	 me->set_temp("sltf/shexing",skill);
	 call_out("sltf_shexing",1,me,skill/40);
	 message_vision(BLU"$N一旦触到$n的身前，左脚忽然施展出「"HIR"盘字诀"BLU"」勾住$n的脖子，右脚随即登了上去！\n\n"NOR,me,target);

	 if (random(me->query_dex(1))>target->query_dex(1)/2)
	 {
		message_vision(BLU"$n被这一脚踢中，顿时有些头重脚轻，嗡嗡作响！\n\n"NOR,me,target);
		target->add_bus(1);
	 }
	  me->add("neili",-100-random(200));
	  me->add("jingli",-100-random(100));
	return 1;
	
 }

//伤害计算函数
int sltf_shexing(object me,int count)
{
        int skill;
		if (!me) return 1;
		skill=me->query_temp("sltf/shexing");
		if (!me->is_fighting()
			|| me->query_temp("weapon")
			|| me->query_skill_prepared("leg")!="shenlong-tuifa"
			|| me->query_skill_mapped("leg")!="shenlong-tuifa"
			|| count<0)
		{
			 me->add_temp("apply/attack",-skill/8);
			 me->add_temp("apply/leg",-skill/6);
			 if (me->query("gender")=="男性") me->add_temp("apply/damage",-skill/8);
			 me->delete_temp("sltf/shexing");
			 message_vision(BLU"$N双脚变回原样，长吁一口真气！\n\n"NOR,me);
			 return 1;
		}
		call_out("sltf_shexing",1,me,count--);

}


//帮助
int help(object me)
{
   write(WHT"\n神龙腿法之「"BLU"蛇形脚"WHT"」："NOR"\n");
   write(@HELP
	神龙腿法为神龙岛初级入门技能，模仿神龙
	之态，凌空而起，连续蹬出几脚，令对手防
	不胜防。
	蛇形脚是模仿蛇形之状，一脚勾住对方脖子
	另外一脚随机踢中对方脖颈，力大者可以使
	对方直接当场昏迷。施展后会小幅提升腿法
	命中和腿法威力。男性若修习训蛇术威力提
	升，女性稍差。
	
	指令：perform leg.shexing
	
要求：
	最大内力要求 1000 以上；
	当前内力要求 500 以上
	当前精力要求 500 以上；
	神龙腿法等级 220 以上；
	基本腿法等级 220 以上；
	毒龙大法等级 220 以上；
	需激发腿法神龙腿法；
	需备腿法为神龙腿法
	需激发内功为毒龙大法；
HELP
      );
   return 1;
}
