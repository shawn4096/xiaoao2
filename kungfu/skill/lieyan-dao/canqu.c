//canqu.c 焚躯
// by sohu
#include <ansi.h>

inherit F_SSERVER;


int lydremove_effect(object target);

string perform_name() {return RED"焚我残躯"NOR;}

int perform(object me, object target)
{
        int lvl,i;
        object weapon = me->query_temp("weapon");
        lvl =  (int)me->query_skill("lieyan-dao", 1)/4 ;

        if( !target ) target = offensive_target(me);
     
        if( !target || !me->is_fighting(target) )
                return notify_fail("「焚我残躯」只能在战斗中对对手使用。\n");

        if (!weapon || weapon->query("skill_type") != "blade"
        || me->query_skill_mapped("blade") != "lieyan-dao")
                return notify_fail("你手里没有刀，无法使用「焚我残躯」！\n");             

        if( (int)me->query_skill("lieyan-dao",1) < 150 )
                return notify_fail("你的烈焰刀不够娴熟，不能使用「焚我残躯」！\n");
      
        if( (int)me->query_skill("blade",1) < 150 )
                return notify_fail("你的基本刀法等级不够，不能使用「焚我残躯」！\n");  

        if( !me->query("quest/mj/lyd/canqu/pass") )
                return notify_fail("你的尚未得到周颠指点，不能使用「焚我残躯」！\n");  

        if( (int)me->query_skill("shenghuo-shengong", 1) < 150 )
                return notify_fail("你的圣火神功等级不够，不能使用「焚我残躯」！\n");

        if( (int)me->query("max_neili") < 1500 )
                return notify_fail("你的最大内力太弱，不能使用「焚我残躯」！\n");
      
        if( (int)me->query("neili") < 400 )
                return notify_fail("你的当前内力太少了，无法使用出「焚我残躯」！\n");   
        if( (int)me->query("jingli") < 300 )
                return notify_fail("你的当前精力太少了，无法使用出「焚我残躯」！\n");   
        if( (int)target->query_temp("lyd/canqu"))
                return notify_fail("对方已经为你「焚我残躯」受到惊吓！\n");   
                                                                        
        message_vision(HIC"\n$N忽然间手舞足蹈，大叫大嚷，右手一翻，从怀中取出一柄"+weapon->query("name")+HIC"随身攻上。\n"
		+"同时叫道：“你不领情吃我的狗腿，老子今日跟你拚了。”一刀在自己脸上一划，登时鲜血淋漓！\n"NOR, me,target);
       // me->add("neili", -(300+random(100))); 
        me->add("jingli", -50);      
      
		me->receive_damage("qi",100+random(100),me);
		if (me->query_per()>20)
		{
			i=me->query_per()-20;
			i=i/2;
		}else i=1;
		if (random(me->query_skill("blade",1))>target->query_parry("parry",1)/2
			||random(me->query_per())>target->query_con()/4)
		{
			message_vision(HIY"$n眼见$N这一刀居然在其脸上划了深可见骨的刀痕，鲜血淋漓，狰狞恐怖，心中大惊！\n"NOR,me,target);
			target->add_busy(i);
			target->apply_condition("no_exert",i);
			target->apply_condition("jiali",0);
			target->add_temp("apply/attack",-lvl);
			target->add_temp("apply/damage",-lvl);
			target->set_temp("lyd/canqu",lvl);
			
			if (objectp(target))
				call_out("lydremove_effect",lvl/30,target);

		}else {
			message_vision(YEL"$N眼见$n不为所动，心中冷笑一声，随手递出数招！\n"NOR,me,target);
			me->set_temp("lyd/canqu",1);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			if(random(3)>0 && me->is_fighting(target))
				  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
			if(random(3)>1 && me->is_fighting(target))
				  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
			me->delete_temp("lyd/canqu");
			me->add_busy(1);
			me->start_perform(3 , "「焚我残躯」");
        }
		return 1;
}

int lydremove_effect(object target)
{
	int lvl;
	if (!target) return 1;
	lvl=target->query_temp("lieyandao/canqu");
	
		message_vision(HIC"$N长吁了一口气，心中终于摆脱了方才的惊恐！\n"NOR,target);
		target->delete_temp("lieyandao/canqu");
		target->add_temp("apply/attack",lvl);
		target->add_temp("apply/damage",lvl);
		return 1;
	

}


int help(object me)
{
        write(HIC"\n烈焰刀法"+HIR"「焚我残躯」"NOR"\n");
        write(@HELP
	烈焰刀乃是明教入门级的武功，源自逍遥二仙中范瑶的传授
	范右使武功极为驳杂，当初毁容而打入敌人内部，就为查找
	陷害明教的对头，以哑巴头陀的形象示人与外，实乃明教的
	大功臣。
	熊熊烈火，焚我残躯是大光明教的教旨，该招取自周颠在少
	林寺大战中以刀割自己脸颊来影响对方的招式，让对方攻击
	力和杀伤力均受到虚弱影响并同时产生一定的惊慌忙乱。如
	若不中会随机带来数招攻击。
	该招的命中和容貌相关，容貌越高带来的惊恐效果越强。需
	向周颠请教方可修习。
	
	指令：perform blade.canqu

要求：
	最大内力要求 1500 以上；
	当前内力要求 400 以上；
	当前精力要求 300 以上；
	烈焰刀法等级 150 以上；
	飘翼身法等级 150 以上；
	圣火神功等级 150 以上；
	激发刀法为烈焰刀法。
	手持刀类武器。

HELP
        );
        return 1;
}
