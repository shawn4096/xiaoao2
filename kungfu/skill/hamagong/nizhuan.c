
// nizhuan.c 逆转九阴
// by snowman@SJ
// edit by sohu@xojh 增加蛤蟆3威力

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me);

string exert_name()
{
        return HBWHT+HIB"逆转九阴"NOR;
}

int exert(object me, object target)
{
        int skill,sk;

        if( !target )
                target = me;

        if(!(int)me->query_skill("hamagong", 1) )
                return 0;
        if( me->query("oyf/hamagong") < 2 )
                return notify_fail("你尚未得到欧阳锋逆转心法，无法逆运蛤蟆功使经脉倒转！\n");
        if((int)me->query("neili") < 3000  )
                return notify_fail("你的内力不够。\n");
        if((int)me->query("jingli") < 2000  )
                return notify_fail("你的精力不够。\n");
		if (me->query_skill("hamagong",1)<500)
				return notify_fail("你的蛤蟆功不足500级，尚未融会贯通，无法运使。\n");
        if((int)me->query_temp("hmg_nizhuan") )
                return notify_fail("你已经用九阴心法逆运了蛤蟆功。\n");

     
       skill = me->query_skill("force",1) + me->query_skill("hamagong", 1);
	   sk=skill/2;
       me->add("neili", -200);
       me->add("jingli", -20);


      message_vision(HIW "\n$N双手撑地，口中发出一连窜低喉声，一股股内劲勃发使$N双足离地，呈头下足上之势。\n" NOR, me);
	  message_vision(HIC"$N口中大声念叨“斯里星，昂依纳得，斯热确虚，哈虎文钵英”,状若疯狂，但出招的威力却巨大！\n"NOR,me);
      tell_object(me, HIR "你体内蛤蟆功劲力逆转，好像有股巨大的力量要崩发出来一样。\n" NOR);
	  
	  if( me->query("quest/hama/nizhuan/pass")) {
         message_vision(HBMAG+HIW"$N忆起欧阳锋传授的逆转诀窍，蛤蟆功的大威力至此方显，全身劲力汹涌澎湃，势不可挡！\n"NOR,me);
		 me->add_temp("apply/strength",skill/5);
		 me->add_temp("apply/armor",skill/5);
		 me->add_temp("apply/defense",skill/5);
		 me->add_temp("apply/parry", skill/4);
         me->add_temp("apply/dodge", skill/4);
		}
		else
		{
     // me->start_call_out( (: call_other, this_object(), "remove_effect", me :), skill);
     
          if (me->query_skill("hamagong", 1) > 450)
            {
                me->add_temp("apply/parry", skill/4);
                me->add_temp("apply/dodge", skill/4);
            }
       if (userp(me))
       {
		   me->add_temp("apply/strength", skill/6);
		   me->add_temp("apply/damage", skill/10); 
		   me->add_temp("apply/cuff", skill/10);
		   me->add_temp("apply/staff", skill/10);
       }
		}
        me->add_temp("apply/dexerity", skill/10);
        me->add_temp("apply/attack", skill/10);
		me->add_temp("apply/strike", skill/10);
		
		
  
        me->set_temp("hmg_nizhuan", skill);
		
		call_out("remove_effect",60,me); //之前那个完全不会消除效果 by renlai
        
        if( me->is_fighting() ) me->start_busy(1);

        return 1;
}

void remove_effect(object me)
{
        int amount;
        if(!me) return;

        if( !intp(amount = me->query_temp("hmg_nizhuan")) )
                return;

			
			
	 if( me->query("quest/hama/nizhuan/pass") ) {
			me->add_temp("apply/strength",-amount/5);
			me->add_temp("apply/armor",-amount/5);
			me->add_temp("apply/defense",-amount/5);
			me->add_temp("apply/parry", -amount/4);
            me->add_temp("apply/dodge", -amount/4);
		}
		else
		{
        if (me->query_skill("hamagong", 1) > 450)
        {
                me->add_temp("apply/parry", -amount/4);
                me->add_temp("apply/dodge", -amount/4);
        }
        if (userp(me))
        {
		   me->add_temp("apply/strength", -amount/6);
		   me->add_temp("apply/damage", -amount/10); 
		   me->add_temp("apply/cuff", -amount/10);
		   me->add_temp("apply/staff", -amount/10);
        }
		}
		
        me->add_temp("apply/dexerity", - amount/10);
        me->add_temp("apply/attack", - amount/10);
		me->add_temp("apply/strike", - amount/10);
		
        me->delete_temp("hmg_nizhuan");
        tell_object(me, HIW "你蛤蟆功逆运过久，神智渐渐不清，只好中止了逆转。\n" NOR);      
}

int help(object me)
{
write(WHT"\n蛤蟆功「逆转九阴」："NOR"\n");
write(@HELP
	欧阳锋的独门绝技蛤蟆功乃是天下武学中的绝顶功夫。
	自从他逆练九阴成疯而又夺得天下第一的称号后，这
	蛤蟆功更大逆寻常武功，更加怪异无伦。这逆转九阴
	之法，便是当年他传与杨过的绝技！
	逆转功效可以有效消除身体异常，且不易为对方打中
	在大幅度提升攻击方面具有特效。解开蛤蟆功第三段
	威力全部释放

	指令：exert nizhuan

要求：
	当前内力 3000 以上；
	当前精力 2000 以上；
	蛤蟆功法 500  级以上
	解开蛤蟆功秘题二；
	可以施展逆转九阴；
	解开蛤蟆功秘题三；
	可以释放逆转九阴真正威力。
HELP
);
return 1;

}
