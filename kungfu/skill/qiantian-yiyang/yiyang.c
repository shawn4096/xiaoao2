// yiyang.c 一阳功
// by sohu@xojh  2014

#include <ansi.h>

int exert(object me)
{
	int i;
	
	i = me->query_skill("qiantian-yiyang",1);

	/*
    if(me->query("class") == "bonze" )
	      return notify_fail("你已经出家，此俗家武功已经不适合于你！\n");
	if ( me->query("family/master_name") != "一灯大师" )
		return notify_fail("你非一灯弟子，无法了解这乾天一阳。\n");
*/
	if (me->query_skill("qiantian-yiyang",1) < 300 )
		return notify_fail("你的乾天一阳功不够娴熟，无法运使「一阳功」。\n");

	if( me->query_skill_mapped("force") != "qiantian-yiyang" )
		return notify_fail("你所使用的内功不对。\n");
/*
	if ( me->query_skill("yiyang-zhi", 1) < 300 )
		return notify_fail("你的一阳指等级不够，无法「一阳功」。\n");

	if ( me->query_skill_mapped("finger") != "yiyang-zhi"
	|| me->query_skill_prepared("finger") != "yiyang-zhi") 
		return notify_fail("你必须结合一阳指使用「一阳功」。\n");
*/
	if (me->query("max_neili") < 5000  )
		return notify_fail("你的内劲修为不够。\n");

	if (me->query("neili") < 1000  )
		return notify_fail("你的内力不够。\n");
	
	if (me->query("jingli") < i  )
		return notify_fail("你的精力不够。\n");

	if (me->query("max_jing") < 2000  )
		return notify_fail("你的最大精血不足。\n");

	if (me->query("jing") < 1000  )
		return notify_fail("你的精血不足。\n");

	if (me->query_temp("qtyy/yiyang"))
		return notify_fail("你已经使用「一阳功」了。\n");

	message_vision(HIY"\n$N凝神聚气，脸色数变，肤色红润了许多,将浑身功力凝聚于手指，蓄势待发。\n"NOR, me);

	

	me->add("neili", -i);
	me->add("jingli",-i);
	if (me->query("class") == "bonze")
		i=i/2;
	
    me->add_temp("apply/attack",i/8);
	me->add_temp("apply/damage",i/10);
	me->add_temp("apply/finger",i/10);
	
	if (me->query_skill("qiantian-yiyang",1)>450)
	{     
       me->add_temp("apply/attack",i/6);	  
	  if (me->query("yideng/ronghe")=="pass")
	  {
		  message_vision(HIC"\n$N将领悟到「先天功」的奥义与乾天一阳功彼此融合，威力陡增。\n"NOR, me);
	      me->add_temp("apply/damage",i/5);
		  
	  } else 
		  me->add_temp("apply/damage",i/10);	
	}
   
	me->set_temp("qtyy/yiyang", i);
	
	if (me->query_skill("qiantian-yiyang",1)<450)
	{
	   if( me->is_fighting() ) 
		   me->start_busy(random(2));
	   me->start_exert(2, "一阳功");
	}	
	call_out("remove_effect", 1, me, 3+me->query_skill("qiantian-yiyang", 1)/50);
	return 1;
}

void remove_effect(object me, int tick)
{
	int i;
	if(!me) return;
	i=me->query_temp("qtyy/yiyang");

	if( me->query_skill_mapped("force")!="qiantian-yiyang" 
		|| tick<0 ) 
	{
		tell_object(me, HIY"\n你功力运转不止，这一阳指力最耗内力，终于感觉支持不住，长长地吐出一口浊气。\n" NOR);
		me->add_temp("apply/attack",-i/8);
	    me->add_temp("apply/damage",-i/10);
	    me->add_temp("apply/finger",-i/10);
        if (me->query_skill("qiantian-yiyang",1)>450)
	    {
		   me->add_temp("apply/attack",-i/6);
	       if (me->query("yideng/ronghe")=="pass")
		      me->add_temp("apply/damage",-i/5);
	       else
	          me->add_temp("apply/damage",-i/10);
		 }

		me->delete_temp("qtyy/yiyang");
		return;
	}
	call_out("remove_effect", 1, me, tick-1);
}

string exert_name(){ return HIY"一阳功"NOR; }

int help(object me)
{
	write(HIY"\n乾天一阳功之「一阳功」："NOR"\n\n");
        write(@HELP
	一阳功是大理乾天一阳秘传功法，非核心弟子不传
	最适合和一阳指运使，但因为南帝一灯大师曾经从
	中神通王重阳所授之先天功的精要，所以一灯大师
	对于一阳功的运使更上一层楼。获得一灯大师指点
	后，受先天功激发，一阳功将发生飞跃，刚柔并济
	注意：出家弟子使用威力不及俗家弟子的一半。	
    
指令：exert yiyang
	
要求：
	当前内力 1000 以上；
	当前精力 1000 以上；
	最大内力 5000 以上；
	最大精力 2000 以上；
	乾天一阳功 300 以上；
		
		
HELP
        );
        return 1;
}
