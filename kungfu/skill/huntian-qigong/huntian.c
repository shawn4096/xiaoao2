// huntian.c 混天气功加力
// Change Powerup to huntian by Looklove 2001.5.3

#include <ansi.h>
inherit F_CLEAN_UP;

string exert_name(){ return HIR"混天"NOR; }

int exert(object me, object target)
{
	int skill;

	if( me->query("neili") < 500 )
		return notify_fail("你的内力不够。\n");

	if( me->query_skill("huntian-qigong", 1) < 100 )
		return notify_fail("你的混天气功等级不够。\n");

	if( me->query_skill_mapped("force") != "huntian-qigong" )
		return notify_fail("你的内功不对。\n");

	if( me->query_temp("htqg/powerup") )
		return notify_fail("你已经在运功中了。\n");

	skill = me->query_skill("huntian-qigong",1);
	//if( skill > 150 ) skill = 150;

	me->receive_damage("neili", -300);
	message_vision(HIR "$N微一凝神，运起「混天」神功，全身骨节发出一阵爆豆般的声响。\n" NOR, me);
//丐帮强调的是攻击,命中较大，伤害增加
	
	me->delete_temp("apply/dodge");	
   	me->delete_temp("apply/attack");
	me->delete_temp("apply/damage");	
	
	me->add_temp("apply/dodge", skill/6);	
   	me->add_temp("apply/attack", skill/2);
	me->add_temp("apply/damage", skill/6);
	//me->add_temp("apply/strength", skill/10);
	me->set_temp("htqg/powerup", skill);
	me->delete_temp("htqg/shougong");

	call_out("remove_effect", 1, me, skill);
	if (me->query_skill("huntian-qigong",1)<450)
	{
		me->start_exert(1, "混天气功");
	}
	if( me->is_fighting()&& me->query_skill("huntian-qigong",1)<450 )
		me->start_busy(1+random(1));
	return 1;
}

void remove_effect(object me, int count)
{
	int amount;
	if(!me) return;
	if(me->query_temp("htqg/powerup")){
	if( count-- > 0 && !me->query_temp("htqg/shougong") ) {
			call_out("remove_effect", 1, me, count);
			return;
		}	
		amount = me->query_temp("htqg/powerup");		
		me->add_temp("apply/dodge", - amount/6);	
     	me->add_temp("apply/attack",- amount/2);
	    me->add_temp("apply/damage",- amount/6);
	    //me->add_temp("apply/strength",- amount/10);
		me->delete_temp("htqg/powerup");
		me->delete_temp("htqg/shougong");
		tell_object(me, HIR"你的混天气功运行完毕，将内力收回丹田。\n"NOR);
	   return;
	   }
}

int help(object me)
{
        write(HIR"\n混天气功之「混天」："NOR"\n");
        write(@HELP
	混天气功乃是丐帮重要的内功技能，对于丐帮的绝技有特殊的加成作用。
	其特点也是极具特色，遇敌越强，反击越强。江湖中传言只有九指神丐
	的独家武功，其内劲和别的帮派不同，遇到对手的打击若抵抗不住，一
	般化解方法是向倒下，而混天内劲的作用却是向前俯跌。只因他的武功
	刚猛绝伦，遇强愈强，决不随势屈服，就算跌倒，也要跌得与敌人用力
	的方向相反。
	「混天决」为混天气功重要技能之一。通过运功可以将自身命中和防御
	大幅提升。450级后取消busy。
	要求：
		混天气功等级　100 以上；
		当前内力  500 以上。
	set 混天气功 神罡 有防御特效
HELP
        );
        return 1;
}