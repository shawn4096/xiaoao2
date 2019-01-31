// bizhen.c  碧针清掌 碧针
// sohu@xojh
 
#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

int effect_back(object me, int count);

string perform_name() {return HBBLU HIG"碧针"NOR;}

int perform(object me, object target)
{
        int lev;
        
        if( !target ) target = offensive_target(me);

         if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) 
         || !living(target) )
                return notify_fail("「碧针」只能在战斗中使用。\n");

        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用「碧针」！\n");   

        if( (int)me->query_skill("bizhen-qingzhang", 1) < 350 )
                return notify_fail("你的掌法还不够娴熟，使不出「碧针」绝技。\n");

        if((int)me->query_skill("force",1) < 350 ) 
                return notify_fail("你的内功修为还不够，使不出「碧针」绝技。\n");
             

        if (me->query_skill_prepared("strike") != "bizhen-qingzhang" 
         || me->query_skill_mapped("strike") != "bizhen-qingzhang" )
                return notify_fail("你现在无法使用「碧针」！\n");    
 

        if( (int)me->query("neili") < 1000)
                return notify_fail("你现在真气太弱，使不出「碧针」。\n");

        if( (int)me->query("jingli") < 400 )
                return notify_fail("你现在精力太少，使不出「碧针」。\n");
        if( me->query_temp("bzqz/bizhen") )
                return notify_fail("你正在施展「碧针」绝技。\n");
 
        lev = (int)me->query_skill("bizhen-qingzhang", 1); 
       
		message_vision(HIG "$N展开掌法，将成千成万枚松针反击上天，浑身劲气汹涌澎湃，力透双掌，凝气如丝，瞬间向外释放！\n" NOR, me);
		message_vision(HIG "$N内力虽非有形有质，却也已隐隐有凝聚！千千万万枚松针化成一团绿影，将他一个盘旋飞舞的人影裹在其中\n" NOR, me);

        me->add_temp("apply/damage", lev/10);
        me->add_temp("apply/attack", lev/5);       
        me->add_temp("apply/strike", lev/5);
		me->add_temp("apply/dodge", lev/4);

		if (random(me->query_skill("force",1))>target->query_skill("dodge",1)/2
			||random(me->query_dex(1))>target->query_dex(1)/2)
		{
			message_vision(RED"$n一时疏忽，为$N碧针绝技所封住穴道，顿时一阵气血汹涌！\n" NOR, me,target);
			target->apply_condition("no_exert",2);
			target->add_busy(2);
		}
		me->set_temp("bzqz/bizhen",lev);
        
        me->add("neili", -400);
        me->add("jingli", -100);
		effect_back(me,(int)lev/20);
		//call_out("effect_back",1,me,(int)lev/20);
        return 1 ;
}

int effect_back(object me,int count)
{
	int lev;
	if (!me||!me->query_temp("bzqz/bizhen")) return 0;
	lev=me->query_temp("bzqz/bizhen");
	if (count--<0
		||me->query_skill_mapped("strike")!="bizhen-qingzhang"
		||me->query_skill_prepared("strike")!="bizhen-qingzhang"
		||!me->is_fighting())
	{
        me->add_temp("apply/damage", -lev/10);
        me->add_temp("apply/attack", -lev/5);       
        me->add_temp("apply/strike",-lev/5);
		me->add_temp("apply/dodge", -lev/4);

		me->delete_temp("bzqz/bizhen");

		message_vision(HIG "$N所施展的「碧针」绝技缓缓收功！\n" NOR, me);
		return 1;
	}
	call_out("effect_back",1,me,count--);
}
int help(object me)
{
   write(HIC"\n碧针清掌「" HIG"碧针"HIC"」："NOR"\n\n");
   write(@HELP
	碧针清掌是摩天居士谢烟客的独门秘籍，一旦施展
	宛如巨浪排空，劲气极为汹涌，属于掌法中异常独
	特的一种功法。碧针绝技的最大功效是凝气成针向
	外涌去，宛如巨浪，对手会受到劲气的封穴效果
	
	指令：perform strike.bizhen

要求: 
	当前内力 1000 以上；
	当前精力 400 以上；
	碧针清掌等级 350 以上；
    基本内功等级 350 以上；
	激发掌法为碧针清掌；
	内功不限；
	空手，备碧针清掌。

HELP
   );
   return 1;
}

