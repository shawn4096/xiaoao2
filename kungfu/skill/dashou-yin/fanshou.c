//fanshou.c  反手勾腕
//By sohu@xojh 反手勾腕
// 灵智上人忽道：“道长功力精奥，令人拜服之至。”双手合十，施了一礼，突然双掌提起，一股劲风猛然扑出。
//王处一举手回礼，也是运力于掌，要以数十年修习的内功相抵。两股劲风刚触到，
//灵智上人突变内力为外功，右掌斗然探出，来抓王处一手腕。这一下迅捷之至，王处一变招却也甚是灵动。反手勾腕，强对强，硬碰硬，两人手腕一搭上，立即分开。
#include <ansi.h>
string perform_name(){ return HIC"反手勾腕"NOR; }
inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        if( !target )
             target = offensive_target(me);
        if( !target 
          || !me->is_fighting(target)
          || !objectp(target)
          || !living(target)
          || environment(target)!= environment(me))
		return notify_fail("「反手勾腕」只能在战斗中使用。\n");
          
		  weapon = target->query_temp("weapon");

        if( userp(me) 
        &&( me->query_skill_mapped("parry") != "dashou-yin"))
                return notify_fail("「反手勾腕」必须在用大手印激发招架的情况下才能使用。\n");

        if( userp(me) && (me->query_skill_mapped("force") != "longxiang-boruo"
        || me->query_skill_prepared("hand") != "dashou-yin") )
                return notify_fail("你的内功或手法不对，根本不能发挥出「反手勾腕」的优势。\n");  
		
        if((int)me->query_skill("longxiang-boruo", 1)  < 180 )
             return notify_fail("你的龙象波若功等级还不够，使不出「反手勾腕」。\n");

        if((int)me->query_skill("dashou-yin",1) < 180 ) 
             return notify_fail("你的大手印等级不够，不会使用「反手勾腕」。\n");

		if (!me->query("quest/dls/dsy/tianyin/pass"))
			 return notify_fail("大手印乃是大轮寺不传之秘，请先跟灵智上人请教「反手勾腕」。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你先放下手中的武器再说吧？！\n");     

		if( target->is_busy())
                return notify_fail("对方已经忙碌不堪了，放胆进攻吧？！\n");     

        if((int)me->query("neili") < 1500)
             return notify_fail("你的内力不够用来「反手勾腕」。\n");

        if((int)me->query("jingli") < 500)
             return notify_fail("你的精力不够用来「反手勾腕」。\n");
      
        message_vision(RED"\n$N双手合十，施了一礼，突然双掌提起，一股劲风猛然扑出。$n刚要举手回礼，以内功相抗，突然意识到不妙！\n" NOR, me, target);
		message_vision(HIC"\n此时$N突变内力为外功，右掌斗然探出，来抓$n手腕。这一下迅捷之至。而$n立即反手勾腕，强对强，硬碰硬，\n"
							+"当两人手腕一搭上，“啪”的一声轻响，立即分开。\n"NOR,me,target);
	
        if (random(me->query_str(1)) > target->query_dex(1)/2 
			||random(me->query("combat_exp"))>target->query("combat_exp")/2){
              message_vision(HIR"\n$n闪身急避，怎料$N双手犹如附骨之蛆一般，一时不察，脉门要穴已被$N死死抓住。\n"NOR, me, target);
              target->add_busy(1+random(2));
			  //不能加力
			  target->set("jiali",0);
			  target->receive_damage("qi",500+random(1000),me);
		      target->apply_condition("no_force",1+random(1));
              //me->start_perform(5,"「反手勾腕」");
           }
           else{
              message_vision( HIM"\n$n早已听说大手印中阴招反手勾腕的厉害之处，心中已有防备，猛地里身形急转，后退数步。\n"NOR, me, target);
              me->start_busy(1);
              me->start_perform(2,"「反手勾腕」");
           }
		me->add("neili",-230);
		me->add("jingli",-150);
        if (me->query_skill("dashou-yin",1)<250)
        {
			me->start_perform(1,"反手勾腕");
        }
		return 1;

}

int help(object me)
{
        write(HIC"\n大手印之「反手勾腕」："NOR"\n\n");
        write(@HELP 
	反手勾腕绝技，是大轮寺灵智上人的成名绝技，
	是将密宗日常修持的修行之举耳濡目染中自然
	融入到武技之中，由端庄变灵动，由浩然变诡
	异，短时间之内令对手防不胜防，不少武林中
	人都栽在灵智上人这招之下。
	注意：250级后小飞
	
	指令;perform hand.fanshou
				
要求：
	当前内力需求 1500 以上；
	当前精力需求 500 以上；
	大手印的等级 180 以上；
	基本内功等级 180 以上；
	基本掌法等级 180 以上；
	激发掌法为大手印；
	激发招架为大手印；
	激发内功为龙象般若功。
HELP
        );
        return 1;
}