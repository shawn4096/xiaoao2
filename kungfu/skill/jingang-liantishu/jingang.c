//jingang cred by sohu@xojh 金刚体魄
//主要是起到增加体力效果，增加自己根骨
//激发到cuff,strike,leg方面

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
  int lvl,i,j;
  string msg;
  lvl = (int)me->query_skill("jingang-liantishu", 1);
 // if (me->query("max_pot") >= 350 ) lvl = lvl /4 ;//250后衰弱
  
  if( !target ) target = offensive_target(me);
  /*
  if( !objectp(target)
	 || !me->is_fighting(target)
	 || !living(target)
	 || environment(target)!=environment(me))
		return notify_fail("「金刚体魄」只能在战斗中对对手使用。\n");*/

  // if( objectp(me->query_temp("weapon")))
	//	return notify_fail("你必须空手才能使用「金刚体魄」！\n");

   if( (int)me->query_skill("jingang-liantishu", 1) < 100 )
		return notify_fail("你的金刚炼体术还不够娴熟，使不出「金刚体魄」绝技。\n");
   if( (int)me->query_skill("xuedao-jing", 1) < 100 )
		return notify_fail("你的血刀经还不够娴熟，使不出「金刚体魄」绝技。\n");

   if(me->query_skill("force", 1) <100)   
       return notify_fail("你的基础技能等级还不够，使不出「金刚体魄」绝技。\n");

   if( (int)me->query_skill("cuff",1) < 100 )
		return notify_fail("你的基本拳法等级不够，不能使用「金刚体魄」。\n");
   if( (int)me->query_skill("strike",1) < 100 )
		return notify_fail("你的基本掌法等级不够，不能使用「金刚体魄」。\n");
   if( (int)me->query_skill("leg",1) < 100 )
		return notify_fail("你的基本腿法等级不够，不能使用「金刚体魄」。\n");
   
   if(!me->query("quest/xd/jglts/jingang/pass"))
		return notify_fail("你尚未得到金刚炼体术真传，不能使用「金刚体魄」。\n");


   if( me->query_skill_mapped("strike") != "jingang-liantishu"
	 || me->query_skill_mapped("leg") != "jingang-liantishu"
	 || me->query_skill_mapped("cuff") != "jingang-liantishu")
		return notify_fail("你现在没有激发武技，无法使用「金刚体魄」！\n");


   if( me->query_skill_mapped("parry") != "jingang-liantishu")
		return notify_fail("你需要激发招架为金刚炼体术，方能使用「金刚体魄」。\n");

   if( me->query_skill_mapped("force") != "xuedao-jing")
		return notify_fail("你需要激发内功为血刀经，方能使用「金刚体魄」。\n");


   if( (int)me->query("max_neili") < 1300)
		return notify_fail("你的内力太弱，使不出「金刚体魄」。\n");

   if( (int)me->query("neili") < 500 )
		return notify_fail("你现在真气太弱，使不出「金刚体魄」。\n");

   if( (int)me->query("jingli") < 500 )
           return notify_fail("你现在太累了，使不出「金刚体魄」。\n");
   
   if (me->query_temp("jglts/jingang"))
   {
           return notify_fail("你正处于「金刚体魄」状态。\n");

   }
    message_vision(HIY"\n$N将寻常辛苦修炼的金刚炼体术施展出来，形成短时间的「金刚体魄」状态！\n"
						"$N只觉得浑身精力转化为充沛的力量，身体明显健壮不少！\n"NOR,me);


	me->add_temp("apply/constitution", lvl/25);
	me->add_temp("apply/strength", lvl/30);
    me->add("jingli", -100);
    me->add("neili", -200);
	me->set_temp("jglts/jingang",lvl);
	call_out("remove_jingang",3+lvl/100,me);
  
	return 1;
}
int remove_jingang(object me)
{
	int lvl;
	if (!me||!me->query_temp("jglts/jingang")) return;
	lvl=me->query_temp("jglts/jingang");
	me->add_temp("apply/constitution", -lvl/25);
	me->add_temp("apply/strength", -lvl/30);
	me->delete_temp("jglts/jingang");
	message_vision(HIY"$N呼出一口淡红色的浊气，金刚体魄缓缓收功！\n"NOR,me);
	return;

}


string perform_name(){ return HIR"金刚体魄"NOR; }

int help(object me)
{
	write(HIR"\n金刚炼体术之"+HIY"「金刚体魄」"NOR"\n\n");
	write(@HELP
	金刚炼体术是血刀门的入门武功，将招式和心法
	修炼融合在一起的武学。这门武功修炼神速，乃
	血刀门秘不外传的武技。运使后会短时期内大幅
	增加自己的体格状态，加成状态和金刚炼体术等
	级有关联，等级越高，金刚体魄持续的时间越长
	
	此门武功乃是血刀门弟子在雪地中辛苦修炼打熬
	所成，是血刀门非核心弟子不传的修炼法门。
	此门武功强调的是拳法、掌法、腿法的修炼，对
	此三门基本武功均需要修炼。同时注重协调发展
	因此，意志不坚定者慎重考虑修习。
	此招式需得到真传方可使用，否则不得其门而入
	激发招架后虽没有内功的反弹功效，但体格健壮
	和抗打击能力显然增强不少。

	指令：perform jingang

要求：
	最大内力 1300 以上；
	当前内力 500  以上；
	当前精力 500  以上；
	金刚炼体术等级 100 以上；
	血刀经内功等级 100 以上；
	基本内功、轻功、招架、拳法、掌法、腿法等级 100 以上；
	激发拳法为金刚炼体术；
	激发腿法为金刚炼体术；
	激发拳法为金刚炼体术；
	激发招架为金刚炼体术：
	激发内功血刀经；
	备拳法为金刚炼体术且空手。

HELP
	);
	return 1;
}
