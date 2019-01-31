
//taxue.c 踏雪无痕
//cre by sohu@xojh 2014 移植到轻功描述
// 定义为轻灵便捷，是后期剑法的重要法门

#include <ansi.h>
void remove_effect(object me,int count);

string perform_name() {return HIY"踏雪"NOR;}

int perform(object me,object target)
{                               
        int improve;
      
        if( !me->is_fighting() && (int)me->query_skill("xuantian-wuji",1)<450 )
                return notify_fail("你现在只能在战斗中使用「踏雪」！\n");

        if( (int)me->query_skill("xuantian-wuji",1) < 200 )
                return notify_fail("你的玄天无极功还不够娴熟，不会使用「踏雪」！\n");
		
		if( me->query_skill("taxue-wuhen",1)< 200 )
                return notify_fail("你的玄天无极功还不够娴熟，不会使用「踏雪」！\n");
        
		if (me->query_skill_mapped("force") != "xuantian-wuji")
                return notify_fail("你的内功不对，不能使用「踏雪」。\n");
      
        if((int)me->query("max_neili")<2000)
                return notify_fail("你的最大内力修为太差，多多打坐吧。\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不够。\n");

        if( me->query_temp("txwh/taxue")   )
                return notify_fail("你正在使用「踏雪」！\n");
       
      
        message_vision(HIW"$N玄天无极功流转不息，高纵上跃，矫若游龙，宛似凌空飞行，踏雪而行，飘然若仙！\n" NOR, me);
      
        improve = (int)me->query_dex();
        if (me->query_skill("xuantian-wuji",1)<350)
        {
			me->start_perform(2,"「踏雪」");
        }
        me->add_temp("apply/dodge", improve);
        me->add_temp("apply/dexerity", improve);
        me->set_temp("txwh/taxue",improve);  
        me->add("neili", -(350-(int)me->query_skill("xuantian-wuji",1)/10));            
        call_out("remove_effect", 1, me, improve);
        return 1;
}

void remove_effect(object me,int count)
{
         int improve;
         if( !me ) return;
         if( !intp(improve = me->query_temp("txwh/taxue"))) return;
         if( count < 1 || !me->is_fighting()){
          me->add_temp("apply/dodge", - improve);
          me->add_temp("apply/dexerity", -improve);
          me->delete_temp("txwh/taxue");
          tell_object(me, HIW"你散去丹田聚集的内力，立定了脚步，身法回复了正常。\n"NOR);
          tell_room(environment(me), HIW + me->name()+"气回丹田，散去了周身的功力。\n"NOR,  ({ me })); 
          return;
        }
        call_out("remove_effect", 1 , me ,count -1);
}

int help(object me)
{
        write(WHT"\n踏雪无痕之「踏雪」绝技："NOR"\n");
        write(@HELP
	踏雪无痕是昆仑重要的轻功，需要玄天无极功激发，
	此「踏雪」练成后高纵上跃，矫若游龙，在腾起之势
	将竭之时，在空中飞跃二三十丈的距离。此心法一经
	使出可大幅度提升轻功身法。350级小飞，450级大飞
	
	perform dodge.taxue

要求：
	踏雪无痕等级 200 以上；
	玄天无级等级 200 以上；
	最大内力要求 2000 以上；
	当前内力要求 500 以上；
HELP
        );
        return 1;
}
