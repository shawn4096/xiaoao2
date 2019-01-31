// sohu@xojh
//金钟罩 zhao.c
//少林初期防身功夫

#include <ansi.h>
void remove_effect(object me,int count);

int exert(object me)
{    
      int skill;
	  skill=me->query_skill("hunyuan-yiqi",1);
	  if ( !me->is_fighting())
                return notify_fail("你只能在战斗中使用「金钟罩」！\n");
	
      if( (int)me->query_skill("hunyuan-yiqi", 1) < 350 )
                return notify_fail("你的易筋经内功修为不够，无法使用「金钟罩」！\n");
      if( (int)me->query_skill("force", 1) < 350 )
                return notify_fail("你的基本内功修为不够，无法使用「金钟罩」！\n");
 

      if (me->query_skill_mapped("force") != "hunyuan-yiqi")
                return notify_fail("其它内功有「金钟罩」吗？\n");

      if( (int)me->query_con() < 50 )
                return notify_fail("你的后天根骨太低，根本无法使用「金钟罩」！\n");
 
      if( (int)me->query("neili") < 1000 )
                return notify_fail("你目前的内力太少了，无法使用「金钟罩」！\n");   
    
      if( (int)me->query("jingli") < 800 )
                return notify_fail("你的精力不够，还想使用「金钟罩」？\n");   
      if( me->query_temp("hyyq/zhao"))
                return notify_fail("你正在运用「金钟罩」！\n");
                                                                                 
      message_vision(HIY"\n$N混元一气劲发动，内力运转周身，隐隐在周身形成一股薄薄的气劲，宛如倒扣的金钟，正是少林「金钟罩」的功夫！\n\n" NOR, me);
    
      me->set_temp("hyyq/zhao",skill);
	  
	  me->add_temp("apply/armor", skill/5);		
      me->add_temp("apply/parry", skill/5);
	  //me->add_temp("apply/dodge", skill/5);
	  me->add_temp("apply/defense", skill/5);

      me->add("neili", -200);  
	  me->add("jingli", -100);  

      call_out("remove_effect", 1, me, (int)me->query_skill("hunyuan-yiqi", 1)/40);
      if (me->query_skill("hunyuan-yiqi",1)<350)
      {
		  me->start_exert(2,"「金钟罩」");
      }
      return 1;
}

void remove_effect(object me,int count)
{
        int skill;
		if( !me||!me->query_temp("hyyq/zhao")) return;
		skill=me->query_temp("hyyq/zhao");
        if( count < 1
			||!me->is_fighting())
	   {
			  
		  me->add_temp("apply/armor", -skill/5);		
		  me->add_temp("apply/parry", -skill/5);
		  //me->add_temp("apply/dodge", -skill/5);
		  me->add_temp("apply/defense", -skill/5);
		  me->delete_temp("hyyq/zhao");
		  message_vision(HIR"\n$N默念佛号，散去了凝聚于全身上下的「金钟罩」劲气。\n"NOR, me);    
		  return;
		}
     
        call_out("remove_effect", 1, me,count -1);
		return;
}
string exert_name(){ return HIY"金钟罩"NOR; }

int help(object me)
{
        write(HIY"\n混元一气功之「金钟罩」："NOR"\n");
        write(@HELP
	少林混元一气功是少林寺基础心法，凝聚混元一气劲
	既可以修炼金钟罩，也可以增加手头上功夫，练到高
	深处，虽然不如本门第一神功易筋经的威力，但因其
	脱胎于易筋经心法，也是不俗的内功心法。
	金钟罩是凭借一口真气流转，在周身形成薄薄的气劲
	短时间内提升自身有效防御。
	
	指令：exert zhao

要求：  
	混元一气功等级 350  以上；
	基本内功的等级 350  以上；
	后天根骨的需求 50   以上；
	当前的内力需求 1000 以上；
	当前的精力需求 800  以上。

HELP
        );
        return 1;
}
