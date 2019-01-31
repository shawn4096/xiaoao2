//updata by Jpei 2010 
//增加有效死亡次数death_times的威力。

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name(){ return HIB"天下无狗"NOR; }

int perform(object me,object target)
{
    object weapon;
    int i,j;
    
    if( !target ) target = offensive_target(me);
     
    if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("天下无狗只能对战斗中的对手使用。\n");
	if (!me->query("quest/gb/dgb/wugou/pass"))
		return notify_fail("你没有将招式和棒诀融合贯通，无法使用天下无狗！\n");
    if(me->query_skill_mapped("force") != "huntian-qigong")
                return notify_fail("你的内功不是混天气功，无法使用天下无狗！\n");
    if( (int)me->query_skill("huntian-qigong", 1) < 500 )
                return notify_fail("你的内功还未练成，不能使用天下无狗！\n");
    if( (int)me->query_skill("dagou-bang", 1) < 500 ) 
                return notify_fail("你的打狗棒法还未练成，不能使用天下无狗！\n");
    if((int)me->query_skill("stick", 1) < 500 )
                return notify_fail("你的基本棒法不够娴熟，不能在使用天下无狗。\n");
    if((int)me->query_skill("bangjue", 1) < 200 )
                return notify_fail("你的打狗棒诀不够娴熟，不能在使用天下无狗。\n");
    if((int)me->query_con(1) < 70 )
                return notify_fail("你的身体不够强壮，不能使用天下无狗。\n");
    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "stick"
        || me->query_skill_mapped("stick") != "dagou-bang"
        || me->query_skill_mapped("parry") != "dagou-bang")
                return notify_fail("你现在使得了天下无狗么？\n");
                
    if((int)me->query("max_neili") < 15000 )
                return notify_fail("你的内力修为不够，不能使用天下无狗！\n");
    if((int)me->query("neili") < 2000 )
                return notify_fail("你现在真气不足，不能使用天下无狗！\n");

        message_vision(HIW"\n$N竹棒抖动，将一路“打狗棒法”使得变化万方，但见棒去如神龙夭矫，棒来又似灵蛇盘舞，奥妙招式,信手拈来！\n",me);
        message_vision(HIG"这正是打狗棒法的绝招「天下无狗」,据说共六种变化，一招使出,劲力所至,四面八方全是棒影，\n",me);
        message_vision(HIG"此时纵是有几十条恶犬也可一并打死了，所谓“天下无狗”便是此意，棒法之精妙绝伦，已臻武学中的绝诣!\n"NOR,me);
        message_vision(HBRED"$N已得「天下无狗」六变之精要，出招行云流水，刹那间漫天的棒影挥向$n!\n"NOR,me,target);

    me->start_perform(2+random(2),"「天下无狗」");
    i = (int)me->query_skill("dagou-bang",1);
    j= me->query_skill("bangjue",1);
    // if(j>500) j = 500;

    me->add("neili", -500);
	me->add("jingli", -500);
        me->add_temp("apply/attack",  i/2);
        me->add_temp("apply/damage",  i/4);
	
	if (weapon->query("material")=="bamboo"
		||weapon->query("material")=="wood"
		|| weapon->query("id") == "yuzhu bang"
		|| weapon->query("material") == "paper" 
		|| weapon->query("weapon_prop/damage") < 20 )
	{
		if (!me->query_temp("dgb/zhubang")) 
		{
			message_vision(HBYEL+HIW"\n\n$N已经深得打狗棒「轻灵奇巧」的绝旨，手中的"+weapon->query("name")+HBYEL+HIW"在$N内力灌注下，更加灵活多变！\n"NOR,me);
			me->add_temp("apply/stick",  i/2);
			me->add_temp("apply/strength",  i /10);
			me->add_temp("apply/attack",  i/2);
			me->add_temp("apply/damage",  i/4);
			me->set_temp("dgb/zhubang",i);
		}
		
	}
		me->set_temp("dgb/wugou",6);


        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        

    if( j>200 && me->is_fighting(target)&& userp(target) ) 
	   target->add_busy(j/50);
   
        
 
      if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
     if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
     if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
       
	   	me->add_temp("apply/attack",  -i/2);
        me->add_temp("apply/damage",  -i/4);
	if (me->query_temp("dgb/zhubang"))
	{
        me->add_temp("apply/stick", - i/2 );
        me->add_temp("apply/strength",  - i /10 );
        me->add_temp("apply/attack",  -i/2 );
        me->add_temp("apply/damage",  -i/4);
		me->delete_temp("dgb/zhubang");
	}
    
	if (me->query("gender")=="女性") me->start_perform(5,"「天下无狗」");
	else me->start_perform(6,"「天下无狗」");
	
	me->delete_temp("dgb/wugou");
    me->start_busy(2);
    return 1;
}

int help(object me)
{
   write(HIB"\n打狗棒「天下无狗」："NOR"\n");
   write(@HELP
	此招共有六变，为打狗棒最终极的绝招，虽江湖上盛传丐帮
	弟子中，年轻有为者，已然学会该绝技，但只仅仅是招式而
	已，若能有幸得丐帮帮主洪老爷子亲口传授该绝技，领会该
	「天下无狗」之妙处，则使将出来乃威力无穷！天下无狗乃
	是打狗棒法的终极武技，这一招使将出来，四面八方是棒，
	劲力所至，便有几十条恶犬也一齐打死了，所谓「天下无狗」
	便是此义，棒法之精妙，已臻武学绝诣。
	
	指令：perform stick.wugou

要求：
	最大内力需求 15000 以上；
	当前内力需求 2000 以上；
	打狗棒法等级 500 以上；
	混天气功等级 500 以上；
	后天根骨需要 70  以上；
	打狗棒诀等级 200 以上；
	激发招架为打狗棒；
HELP
   );
   return 1;
}
