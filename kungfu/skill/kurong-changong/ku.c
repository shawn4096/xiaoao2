//perform ku,“枯”字大法
//cool@SJ 99529

#include <ansi.h>
void remove_effect(object me,int count);

int exert(object me)
{    
      int i=me->query_skill("kurong-changong", 1);
	  if( (int)me->query_skill("kurong-changong", 1) < 200 )
                return notify_fail("你的枯荣禅功修为不够，无法使用「枯」字大法！\n");

      if (me->query_skill_mapped("force") != "kurong-changong")
                return notify_fail("不激发枯荣禅功，无法施展「枯」字大法吗？\n");
/*
      if (me->query_skill_mapped("parry") != "kurong-changong")
                return notify_fail("你必须用枯荣禅功作为招架，才能使用「枯」字大法。\n");*/

      if( (int)me->query_con() < 35 )
                return notify_fail("你的根骨太低，根本无法使用「枯」字大法！\n");
	  if( (int)me->query_skill("force",1) < 200 )
                return notify_fail("你枯荣禅功太少了，无法使用出「枯」字大法！\n"); 
      if( (int)me->query("neili") < 500 )
                return notify_fail("你的内力太少了，无法使用出「枯」字大法！\n");   
    
      if( (int)me->query("max_neili") < 2500 )
                return notify_fail("你的内力修为这么差，还想使用「枯」字大法？\n");   
                                                                                
      if( me->query_temp("pf_ku")   )
                return notify_fail("你正在运用「枯」字大法！\n");
      if( !me->query("quest/tls/kurong/pass") && me->query_temp("pf_rong")  )
                return notify_fail("你功力尚未融会贯通，和正在运用的「荣」字大法相冲突！\n"); 
      if ( !me->is_fighting()) {
                message_vision(HBGRN+HIW"\n$N结珈而坐,双臂张开外划，缓缓收回于丹田，运起「枯」字大法，内力扩散全身，隐隐散着一股青气！\n\n" NOR, me);
                if (me->query_skill("kurong-changong",1)<350)
                {
					me->start_busy(1);
                }
                me->set_temp("pf_ku",1); 
                me->add_temp("apply/armor", i/2); 
                me->add("neili", -400);   
        } 
        else {
                message_vision(HBGRN+HIW"\n$N全力推出一掌，顺势退出三丈，急速运起「枯」字大法，内力遍布全身，隐隐笼罩着一层青气！\n\n" NOR, me);
                if (me->query_skill("kurong-changong",1)<550)
                {
					me->start_busy(1);
                }
                me->set_temp("pf_ku",1); 
                me->add_temp("apply/armor", i/2); 
                me->add("neili", -600);           
      }
	  me->set_temp("pf_ku",i);
      call_out("remove_effect", 1, me,i);
      return 1;
}

void remove_effect(object me,int count)
{
      int i;
	  if (!me) return;
	  i=me->query_temp("pf_ku");

	  if (!me->is_fighting() || count < 0)
	  {
	 	me->delete_temp("pf_ku");
		me->add_temp("apply/armor", -i/2); 
		message_vision(WHT"\n$N当即结珈而坐，长吐一口气，散去了凝聚全身内力。\n"NOR, me);
		return;
      }
	  call_out("remove_effect",1,me,count -1);
	  return ;
}

string exert_name() {return WHT"枯字诀"NOR;}

int help(object me)
{
        write(WHT"\n枯荣禅功「枯字诀」："NOR"\n");
        write(@HELP
	枯荣禅功乃是大理国护国寺院--天龙寺主持枯荣长老的内功心法
	相传佛祖涅磐是在八棵树之间。这八棵树分东西南北两棵辆棵分
	列，它们分别是一枯一荣，东西南北分别是：常与无常，乐与无
	乐，我与无我，净与无净。 讲究心中无枯无荣方是大成。枯荣
	长老心中有物，是以终其一生，只参得半枯半荣。
	
	枯字诀乃是运使枯荣禅功将浑身劲气凝与体外，强化体表，宛如
	枯木状，极大提高自身防御。

要求:
	枯荣禅功 200 级以上；
	最大内力 2500 以上；
	当前内力 500 以上；
	后天根骨 35  以上；
	需激发内功为枯荣禅功。

HELP
        );
        return 1;
}


