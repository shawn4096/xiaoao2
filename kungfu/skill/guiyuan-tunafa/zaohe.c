// tu.c creat by sohu@xojh 
// 源自裘千尺的枣核暗器
// 
#include <ansi.h>
inherit F_SSERVER;
inherit F_CLEAN_UP;
#include "/kungfu/skill/eff_msg.h"

string exert_name(){ return HIY"吐字诀"NOR; }

int exert(object me, object target)
{
	int skill,num,damage,p;
	string msg;
	object zaohe;
	zaohe=present("zaohe",me);
	skill =  me->query_skill("guiyuan-tunafa", 1);
    if(!target) target = offensive_target(me);
    if( !target || !me->is_fighting(target) || !living(target)
            || environment(target)!=environment(me))
                return notify_fail("吐字诀只能在战斗中对对手使用。\n");
	
	if( me->query("max_neili") < 3000 )
		return notify_fail("你的最大内力不够。\n");
	if( me->query("neili") < 1200 )
		return notify_fail("你的当前内力不够，无法施展吐字诀。\n");
    if( me->query("jingli") < 1000 )
		return notify_fail("你的当前精力不够。\n");

	if( me->query_skill("guiyuan-tunafa", 1) < 300 )
		return notify_fail("你的归元吐纳法等级不够。\n");

	if( me->query_skill_mapped("force") != "guiyuan-tunafa" )
		return notify_fail("你的内功不对。\n");
    
	if (!me->query("quest/tiezhang/gytnf/pass"))
        return notify_fail("你听过说有此绝技，但并不知道如何使用。\n");
	
	if( me->query_temp("gytnf/tu") )
		return notify_fail("你已经在运使「归元吐纳法」吐字诀了。\n");

	
	if (!objectp(zaohe))
             return notify_fail("你忽然发现身上的枣核不够，无法使出这吐字诀。\n");   
	
	if (userp(target)&&damage>4000) damage=4000+(damage-4000)/100;
	
	me->receive_damage("neili", -random(100)*num);
	me->receive_damage("jingli", -random(50)*num);
	
	message_vision(HBYEL+HIW "$N猛然间张口，将丹田中的真气，一口喷出，夹裹着口中的枣核射向$n的面门！\n" NOR, me,target);
	
	me->set_temp("gytnf/tu",1);
	zaohe->add_amount(-1);
	//move(environment(me));
	me->add("jingli",-random(200));
	me->add("neili",-random(500));
    if (random(me->query("neili"))>target->query("neili")/2
		||random(me->query_dex(1))>target->query_dex(1)/2)
    {    
	  damage=me->query_skill("guiyuan-tunafa",1)+me->query_skill("force",1);
	  damage=damage*2+random(damage);
	  damage=damage*num;
	  if (damage>target->query("qi",1))
	     damage=target->query("qi")-1;
	  target->receive_damage("qi",damage,me);
	  //target->receive_wound("qi",damage/5,me);
      p = (int)target->query("qi")*100/(int)target->query("max_qi");
      tell_room(environment(target), HIR + target->name()+"冷不防为这枚枣核射中，突然顿时为之一滞，显然穴道被打中！\n" NOR, ({ target }));  
           msg = damage_msg(damage, "内伤");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           message_vision(msg, me, target);
      target->add_busy(2+random(1));
	  if (!userp(target))
	  {
		  target->add_busy(1);
	  }
	}
	else {
     message_vision(CYN"$n轻轻向旁闪身，躲过了这数道袭击，不由地吓了一身冷汗。\n"NOR,me,target);
	 me->add_busy(1+random(1)); 
	}
	if (zaohe->query_amount()<2)
	{
		zaohe->move(environment(me));
		tell_object(me, "\n你的" + zaohe->query("name") + "快用完了！\n");
	}
	me->delete_temp("gytnf/tu");
	//if (me->query_skill("guiyuan-tunafa",1)<450)
	me->start_exert(3, "吐字诀");
	
	me->start_busy(1);
	return 1;
}



int help(object me)
{
	write(HIW"\n归元吐纳法之「吐字诀」："NOR"\n\n");
        write(@HELP
	裘千尺是铁掌裘千仞的亲妹子，一身功夫
	甚是了得，后来遭受丈夫公孙芷抛弃，丢
	入万丈深渊。依靠几枚野生枣得意存活，
	同时不经意间将内功化为内劲夹裹枣核吐
	出伤人的绝技，令人防不胜防。
	注意：需身带几枚大枣方可使用。

	指令：yun zaohe

要求：
	最大内力要求  3000 以上；
	当前内力要求  1200  以上；
	当前精力要求  1000  以上；
	归元吐纳法  300  级以上；
HELP
        );
        return 1;
}