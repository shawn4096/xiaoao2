// sohu@xojh
//一气劲 yiqijin.c
//少林空手增幅武技

#include <ansi.h>
void remove_effect(object me,string ks);

int exert(object me)
{    
      int skill;
	  string ks,ksc;
	 
	  skill=me->query_skill("hunyuan-yiqi",1);
	  if ( !me->is_fighting())
                return notify_fail("你只能在战斗中使用「一气劲」！\n");
	  if(!me->query("quest/sl/hyyq/yiqijin/pass"))
                return notify_fail("你只是听说过这门功夫，但根本无法使用「一气劲」！\n");
      if( (int)me->query_skill("hunyuan-yiqi", 1) < 450 )
                return notify_fail("你的易筋经内功修为不够，无法使用「一气劲」！\n");
      if( (int)me->query_skill("force", 1) < 450 )
                return notify_fail("你的基本内功修为不够，无法使用「一气劲」！\n");
 

      if (me->query_skill_mapped("force") != "hunyuan-yiqi")
                return notify_fail("其它内功有「一气劲」吗？\n");

      if( (int)me->query_con() < 50 )
                return notify_fail("你的后天根骨太低，根本无法使用「一气劲」！\n");
 
      if( (int)me->query("neili") < 2000 )
                return notify_fail("你目前的内力太少了，无法使用「一气劲」！\n");   
    
      if( (int)me->query("jingli") < 1000 )
                return notify_fail("你的精力不够，还想使用「一气劲」？\n");   
      
	  if( me->query_temp("hyyq/yiqijin"))
                return notify_fail("你正在运用「一气劲」！\n");
     
	  ks=me->query("env/混元一气劲");  																			   
	  if (!ks)
				return notify_fail("你要将一气劲运使在哪项空手功夫上？\n");
	   if ((int)me->query_skill(ks,1)<450)
				return notify_fail("你此门基本武技不足450级，威力不显？\n");
	 
	/*  skills=me->qury_skill();
	  for (i=0;i<sizeof(skills);i++ )
	  {
		  if (ks==skills[i]) break;
		  else return notify_fail("你根本没有学这门功夫，如何使用一气劲？\n");
	  }*/
	  ksc=to_chinese(ks);					   
      
	 
	  message_vision(HBYEL"\n$N长吸一口真气，混元一气劲流转不息，将「一气劲」的暗劲运使在"+ksc+HBYEL"中，周身隐隐有噼里啪啦的声响！\n\n" NOR, me);
    
      me->set_temp("hyyq/yiqijin",skill);
	  
	  me->add_temp("apply/"+ks, skill/3);		

      me->add("neili", -500);  
	  me->add("jingli", -300);  

      call_out("remove_effect", (int)me->query_skill("hunyuan-yiqi", 1)/40, me,ks);
      
	  me->start_exert(2,"混元一气劲");
      return 1;
}

void remove_effect(object me,string ks)
{
        int skill;
		if( !me||!me->query_temp("hyyq/yiqijin")) return;
		skill=me->query_temp("hyyq/yiqijin");
 	    me->add_temp("apply/"+ks, -skill/3);	
		me->delete_temp("hyyq/yiqijin");
		message_vision(HIR"\n$N呼出一口浊气，将「一气劲」缓缓散功。\n"NOR, me);    
	    return;
}
string exert_name(){ return HIR"一气劲"NOR; }

int help(object me)
{
        write(HIY"\n混元一气功之「一气劲」："NOR"\n");
        write(@HELP
	少林混元一气功是少林寺基础心法，凝聚混元一气劲
	既可以修炼一气劲，也可以增加手头上功夫，练到高
	深处，虽然不如本门第一神功易筋经的威力，但因其
	脱胎于易筋经心法，也是不俗的内功心法。
	一气劲全凭一口真气，将少林的辛苦修炼的硬功夫施
	展出来，在短期内增加其威力，仅对空手有效。需要
	解密方可使用。

	注意；set 混元一气劲 xx [leg,strike,claw,hand
	finger,cuff 基本武功英文]

	指令：exert yiqijin

要求：  
	混元一气功等级 450  以上；
	基本内功的等级 450  以上；
	后天根骨的需求 50   以上；
	当前的内力需求 2000 以上；
	当前的精力需求 1000  以上。

HELP
        );
        return 1;
}
