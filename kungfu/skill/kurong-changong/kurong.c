// By Spiderii 合并同类项 kurong.c
// By Spiderii 鉴于空手门派，提高防御
// by sohu：增加枯荣禅功实际效果威力为7

#include <ansi.h>
void remove_effect(object me,int skill);


string exert_name() {return HIW"枯"HIG"荣"HIC"诀"NOR;}

int exert(object me)
{      
   int skill;
       skill = me->query_skill("kurong-changong",1);
	   skill=skill+me->query_skill("yiyang-zhi",1)/3;
	   skill=skill/3;
	if ( !me->is_fighting())
		return notify_fail("你只能在战斗中使用「枯荣」！\n");

	if( (int)me->query_skill("kurong-changong", 1) < 350 )
		return notify_fail("你的枯荣禅功修为不够，无法使用「枯荣」！\n");

	if (me->query_skill_mapped("force") != "kurong-changong")
		return notify_fail("其它内功有「枯荣」吗？\n");

	if( (int)me->query("neili") < 15000 )
		return notify_fail("你目前的内力太少了，无法使用「枯荣」！\n");

	if( (int)me->query("max_neili") < 2000 )
		return notify_fail("你的内力修为这么差，还想使用「枯荣」？\n");

	if( me->query_temp("krcg_kurong"))
		return notify_fail("你正在运用「枯荣」！\n");

        // 亦枯亦荣,彻底大成
    if ((int)me->query_skill("kurong-changong", 1) > 550 && me->query("quest/tls/kurong/pass"))
	{
			message_vision(HIY "$N" HIY "运起枯荣禅功，全身皮肤竟变得一半犹"
                                "如婴儿，另一半却似干皱的树皮。正是枯荣禅功的"HIW"「亦枯"HIG"亦荣」"HIY"境界。\n" NOR, me);
            me->add_temp("apply/damage", skill/5);
			me->add_temp("apply/finger", skill/2);
			me->add_temp("apply/strength", skill/20);
            me->add_temp("apply/attack", skill/2);
			me->add_temp("apply/armor", skill/2);
	   	    me->add_temp("apply/parry", skill/2);
			me->add_temp("apply/dodge", skill/2);

	 }
        // 全荣，增加命中
	else if ((int)me->query_skill("kurong-changong", 1) > 500 )
	{
	        message_vision(HIG "$N" HIG "暗自凝神，运起枯荣禅功，全身皮肤竟"
                                "变得犹如婴儿般光滑亮泽。正是枯荣禅功的"HBGRN+HIW"「全荣境界」。\n" NOR, me);
		    me->add_temp("apply/attack", skill/2);
			me->add_temp("apply/armor", skill/2);
		    me->add_temp("apply/parry", skill/2);
			me->add_temp("apply/dodge", skill/2);

     }
		// 全枯，增加防御
    else if ((int)me->query_skill("kurong-changong", 1) > 450)
	{
	       message_vision(YEL "$N" HIW "暗自凝神，运起枯荣禅功，全身皮肤竟"
                                "变得犹如树皮般干皱苍老。正是枯荣禅功之"HIC"“全枯境界”。\n" NOR, me);
		   me->add_temp("apply/armor", skill/2);
		   me->add_temp("apply/parry", skill/2);
		   me->add_temp("apply/dodge", skill/2);
    }
		// 半枯半荣，增加parry
    else if ((int)me->query_skill("kurong-changong", 1) > 350){
		   me->add_temp("apply/parry", skill/2);
		   me->add_temp("apply/dodge", skill/2);
	        message_vision(WHT "$N" WHT "暗自凝神，运起枯荣禅功，真气顿时游"
                                "遍全身，正是枯荣禅功之"YEL"“半枯半荣”境界。\n" NOR, me);
	}else {
		me->add_temp("apply/parry", skill/2);
		message_vision(WHT "$N" WHT "暗自凝神，运起枯荣禅功，真气顿时游遍全身，正是枯荣禅功!\n" NOR, me);
	}
       if (me->query_skill("kurong-changong",1)<350)      
          me->start_busy(1); 
      
	   if (me->query_skill("kurong-changong",1)<450)
      	  me->start_exert(2, "「枯荣」");     
      
		me->add("neili", -400);
		me->set_temp("krcg_kurong",skill);
		call_out("remove_effect", 1, me, skill);
		return 1;
}

void remove_effect(object me, int skill)
{
	
	 if (!me) return;
	 skill=me->query_temp("krcg_kurong");
	 
	 if (objectp(me)) {
                if (me->is_fighting()) {
					   if (me->query("quest/tls/kurong/pass"))
					    {
							me->receive_curing("qi",random(1000));
							message_vision(HIC"$N枯荣禅功已经登峰造极，真气流转之际，身形忽然为枯，忽然为荣，所受伤势得到极大好转。\n"NOR,me);
					    }
                        call_out("remove_effect", 1, me, skill);
                        return;
      }

        me->delete_temp("krcg_kurong");
	    if ((int)me->query_skill("kurong-changong", 1) > 550 && me->query("quest/tls/kurong/pass"))
	    {
			me->add_temp("apply/damage", -skill/5);
			me->add_temp("apply/finger", -skill/2);
			me->add_temp("apply/strength",-skill/20);
			me->add_temp("apply/attack", -skill/2);
			me->add_temp("apply/armor", -skill/2);
			me->add_temp("apply/parry", -skill/2);
		    me->add_temp("apply/dodge", -skill/2);
	     }
        else if ((int)me->query_skill("kurong-changong", 1) > 500){
	       me->add_temp("apply/attack", -skill/2);
		   me->add_temp("apply/armor", -skill/2);
		   me->add_temp("apply/parry", -skill/2);
		   me->add_temp("apply/dodge", -skill/2);
        }
        else if ((int)me->query_skill("kurong-changong", 1) > 450){
		   me->add_temp("apply/armor", -skill/2);
		   me->add_temp("apply/parry", -skill/2);
		   me->add_temp("apply/dodge", -skill/2);
        }
		else if ((int)me->query_skill("kurong-changong", 1) > 350){
		   me->add_temp("apply/parry", -skill/2);
		   me->add_temp("apply/dodge", -skill/2);
        }
        else 
		   me->add_temp("apply/parry", -skill/2);
           message_vision(HIW"\n$N的枯荣禅功运行完毕，将内力收回丹田。\n"NOR, me);
		   
	    return;

	}
}


int help(object me)
{
        write(WHT"\n枯荣禅功之「"HIW"枯"HIG"荣"HIY"诀"WHT"」："NOR"\n");
        write(@HELP
	枯荣禅功乃是大理国护国寺院--天龙寺主持枯荣长老的内功心法
	相传佛祖涅磐是在八棵树之间。这八棵树分东西南北两棵辆棵分
	列，它们分别是一枯一荣，东西南北分别是：常与无常，乐与无
	乐，我与无我，净与无净。 讲究心中无枯无荣方是大成。枯荣
	长老心中有物，是以终其一生，只参得半枯半荣。
	此枯荣一诀能使玩家大幅度提高自身的防御与招架，并且有一定
	几率使对方攻击无效！
	
	指令：yun kurong

要求:
	枯荣禅功 200 级以上；
	最大内力 2000 点；
	当前内力 1500 点；
	需激发内功为枯荣禅功。
              
HELP
        );
        return 1;
}


