// xinmo.c 圣火令法--心魔
// By River@SJ 
// Update By lsxk@hsbbs change perform to exert 2007/6/11
// 修改为圣火令法的武技，非九阳

#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;

void remove_effect(object me,object weapon,int count);
int perform(object me, object target)
{
	int skill;
	object weapon;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("你只能在战斗中体验圣火令法的心魔威力。\n");

	if((int)me->query("neili") < 3500 ) 
		return notify_fail("你的内力不够。\n");

	if((int)me->query("jingli") < 3000 ) 
		return notify_fail("你的精力不够。\n");

	if((int)me->query_temp("ling")) 
		return notify_fail("你已经在运功中了。\n");

	skill = (int)me->query_skill("shenghuo-lingfa", 1);

	if(skill < 450)
		return notify_fail("你的圣火令法等级还不够。\n");

   if((int)me->query_skill("qiankun-danuoyi", 1) < 120)
		return notify_fail("你的乾坤大挪移等级还不够。\n");
/*
   if((int)me->query_skill("jiuyang-shengong", 1) < 120)
           return notify_fail("你的明教九阳功等级还不够。\n");
*/
	if( !(weapon=me->query_temp("weapon"))
	|| weapon->query("skill_type") != "dagger" )
		return notify_fail("你不用兵器怎么提高你的圣火令法的心魔威力？\n");

	if ( me->query_skill_mapped("dagger") != "shenghuo-lingfa"
	 || me->query_skill_mapped("parry") != "qiankun-danuoyi"
	 || me->query_skill_mapped("cuff") != "shenghuo-lingfa"
	 || me->query_skill_prepared("cuff") != "shenghuo-lingfa"
	 && userp(me))
		return notify_fail("你必须先将圣火令法功和乾坤大挪移相互配合。\n");

//	if(userp(me) && me->query("shen") < - 20000 && !me->query_skill("jiuyang-shengong", 1))
//		return notify_fail("你戾气太高了，提高圣火令法太过危险。\n");

	if(userp(me)){
		me->add("jingli", -80);
		me->add("neili", -300);
	}

	message_vision(HIR"\n$N此刻乍逢劲敌，将圣火令法中的精微处尽数发挥出来，心灵渐受感应，突然间哈哈哈仰天三笑，\n"+
			"声音中竟充满了邪恶奸诈之意。\n" NOR, me);
	
	skill += me->query_skill("force", 1)/3; //修改成force加成
	skill = skill/2 + random(skill/2);
	//skill =skill/2;
	//if (me->query_temp("mj/shenghuo"))
	me->add_temp("apply/dagger", skill/5);
	me->add_temp("apply/attack", skill/3);
	me->add_temp("apply/damage", skill/5);
	me->add_temp("apply/strength", skill/5);
	me->set_temp("ling", skill);

	if (me->query_skill("shenghuo-lingfa",1)<449)   //450后大飞
	 {
		me->start_busy(random(2));
	    me->start_exert(1, "心魔");
		}
	call_out("remove_effect", 1, me, weapon, skill/3);
	return 1;
}

void remove_effect(object me,object weapon, int count)
{
	if ( !me ) return;
	if (objectp(me) && me->query_temp("ling")) {
		if (count-- > 0 
		&& me->is_fighting()
		&& me->query_skill_mapped("cuff") == "shenghuo-lingfa"
		&& me->query_skill_prepared("cuff") == "shenghuo-lingfa"
		&& me->query_temp("weapon")
		&& weapon == me->query_temp("weapon")) {
			call_out("remove_effect", 1, me, weapon, count);
			return;
		}
		//if (me->query_temp("mj/shenghuo"))
	    me->add_temp("apply/dagger", -me->query_temp("ling")/5);
		me->add_temp("apply/attack", - me->query_temp("ling")/3);
		me->add_temp("apply/damage", - me->query_temp("ling")/5);
		me->add_temp("apply/strength", - me->query_temp("ling")/5);
		me->delete_temp("ling");
		tell_object(me, HIR"\n你心魔慢慢消退，圣火令法立时不能连贯，威力大减。\n"NOR);
		tell_room(environment(me), HIR+ me->name() + "心魔慢慢消退，圣火令法立时不能连贯，威力大减。\n"NOR, ({ me }));
	}
}

string perform_name(){ return HIR"心魔"NOR; }

int help(object me)
{
   write(WHT"\n明教圣火令法之「"HIR"心魔"WHT"」"NOR"\n\n");
	write(@HELP
	心魔乃是西域心法所传，乃是霍山老人至高武学，走
	诡异路线，令人往往烦不胜防，所以圣火心法乃是阴
	性内功，乃是门中长老和法王们呕心沥血的结果，和
	圣火令法相配有极佳效果。可大幅提升命中和伤害。
	
	指令：perform dagger.xinmo

要求：
	当前内力的需求 3500 以上；
	当前精力的需求 3000 以上；
	圣火令法的等级 450 以上；
	乾坤大挪移等级 450 以上：
	激发令法为圣火令法；
	激发拳法为圣火令法；
	激发招架为乾坤大挪移；
	备拳法为圣火令法；
	且手持兵器。
	450后大飞，取消busy效果。
	和圣火神功相配会有特殊杀伤力。

HELP
        );
        return 1;
}
