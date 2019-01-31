// tiezhou.c 铁帚腿法腿
// by sohu@xojh

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	mapping pre;
	string *skill, a, b;
	int i;

	if( !target ) target = offensive_target(me);

     if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
		return notify_fail("「铁帚腿」只能在战斗中对对手使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("使用「铁帚腿」时双手必须空着！\n");
	if( !me->query("quest/sl/rysxt/tiezhou/pass"))
		 return notify_fail("你尚未修习成功「铁帚腿」神功！\n");
	if( (int)me->query_skill("ruying-suixingtui", 1) < 500 )
		return notify_fail("你的铁帚腿腿不够娴熟，不会使用「铁帚腿」。\n");

	if( (int)me->query_skill("yijin-jing", 1) < 500 )
		return notify_fail("你的易筋经等级不够，不能使用「铁帚腿」。\n");
	if( me->query_temp("fumo"))
		 return notify_fail("你正在使用大金刚拳的特殊攻击「金刚伏魔」！\n");

	if (me->query_skill_mapped("force") != "yijin-jing")
		return notify_fail("你目前的内功无法支持你使用「铁帚腿」进行攻击。\n");  
	if( me->query_temp("fumo"))
		 return notify_fail("你正在使用大金刚拳的特殊攻击「金刚伏魔」！\n");

	if( (int)me->query_dex() < 60 )
		return notify_fail("你的身法不够强，不能使用「铁帚腿」。\n");

	if (me->query_skill_prepared("leg") != "ruying-suixingtui"
	|| me->query_skill_mapped("leg") != "ruying-suixingtui")
		return notify_fail("你现在无法使用「铁帚腿」进行攻击。\n");  
											       
	if( (int)me->query("max_neili") < 15000 )
		return notify_fail("你现在内力修为太弱，不能使用「铁帚腿」。\n");
	if( (int)me->query("neili") < 1500 )
		return notify_fail("你目前内力太少，不能使用「铁帚腿」。\n");

	if( (int)me->query("jingli") < 500 )
		return notify_fail("你现在精力太少，不能使用「铁帚腿」。\n");
	if( me->query_temp("rysxt/tiezhou"))
		return notify_fail("你正在施展「铁帚腿」神功。\n");

	message_vision(HBYEL+HIW"\n$N双脚丁字步站立，气沉丹田，将毕生修习的浑身功力凝于双腿，宛如"HIR"铁帚！\n" NOR,me, target);
 	
	i = (int)me->query_skill("ruying-suixingtui", 1);

    me->add_temp("apply/attack", i/5);
    me->add_temp("apply/strength", i/20);
    me->add_temp("apply/leg",i/5);
	me->add_temp("apply/damage",i/5);
    me->add_temp("apply/parry", i/5);

	me->set_temp("rysxt/tiezhou", i);
	if (me->query_skill("ruying-suixingtui",1)<550)
	{
		me->start_perform(1,"铁帚腿");
	}
	call_out("remove_effect",1,me,(int)i/30);

	return 1;
}

int remove_effect(object me,int count)
{
	int i;
	if (!me) return;
	i=me->query_skill("ruying-suixingtui",1);
	if (count<0
		||!me->is_fighting()
		||me->query_skill_prepared("leg")!="ruying-suixingtui"
		||me->query_skill_mapped("leg")!="ruying-suixingtui")
	{
		me->add_temp("apply/attack", -i/5);
		me->add_temp("apply/strength", -i/20);
		me->add_temp("apply/leg",-i/5);
		me->add_temp("apply/parry", -i/5);
		me->add_temp("apply/damage",-i/5);
		me->delete_temp("rysxt/tiezhou");
		message_vision(YEL "\n$N身子落地，脸憋得通红，呼出一口浊气，缓缓将凝聚于双腿的铁帚功散去。\n" NOR,me);
		return 1;

	}
	call_out("remove_effect",1,me,count--);	
	
}

string perform_name(){ return HBYEL+HIW"铁帚腿"NOR; }
int help(object me)
{
        write(HBYEL"\n铁帚腿腿之「铁帚腿」："NOR"\n");
        write(@HELP
	如影随形为少林七十二绝技之一，乃是少林绝技中腿法的极致。
	利用坚实的腿功和强大的内力，身子纵起空中，双腿不断连环
	踢出，令对手防不胜防，躲无可躲，端的是厉害非常。当初大
	轮寺鸠摩智一代圣僧，将偷学到的如影随形腿利用小无相功施
	展出来，虽然功力并不如易筋经激发的效果好，但其招式之精
	妙以及气势之雄浑，却是模仿的淋漓极致。
	铁帚腿神功乃是将浑身气血打熬的功夫运于双腿，坚如磐石，
	硬如铁帚，乃是少林腿法中修炼到极致的体现。550后大飞
		
	指令：perform leg.tiezhou

要求：  
	最大内力 15000 以上；      
	当前内力 1500  以上；  
	如影随行腿 500 以上；
	易筋经等级 500 以上；
	激发腿法为如影随行腿；
	激发招架为如影随行腿；
	且手无兵器；
	有效身法不得小于60。
	需和如来千叶手互备有特殊功效。
                
HELP
        );
        return 1;
}
