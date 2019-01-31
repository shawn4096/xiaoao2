// dulong.c 
// by sohu@xojh
//
#include <ansi.h>
inherit F_CLEAN_UP;

string exert_name() {return HBWHT+HIB"毒龙诀"NOR;}

void remove_effect(object me, int amount);
void remove_effect2(object me, int amount);

int exert(object me)
{
        int i;
		if (!me->is_fighting())
			return notify_fail("毒龙诀只能战斗中施展，无法施用「毒龙诀」。\n");
        if(!me->query("quest/sld/dldf/dulong/pass"))
               return notify_fail("你尚未解开毒龙诀，无法运使。\n");
        if((int)me->query_skill("dulong-dafa",1) < 350  )
                return notify_fail("你的毒龙大法功力不够，无法施用「毒龙诀」。\n");
        if((int)me->query_skill("force",1) < 350  )
                return notify_fail("你的基本内功功力不够，无法施用「毒龙诀」。\n");
		if((int)me->query_skill("shenlong-yaoli",1) < 200  )
                return notify_fail("你的神龙药理功力不够，无法施用「毒龙诀」。\n");
        if((int)me->query("max_neili") < 3500 )
                return notify_fail("你的最大内力不够，无法使用「毒龙诀」。\n");
		if((int)me->query("neili") < 1500 )
                return notify_fail("你的当前内力不够，无法使用「毒龙诀」。\n");
        if(me->query_skill("poison",1)<180 )
				return notify_fail("你现在毒计不够，不能使用「毒龙诀」。\n");
        if(me->query_skill("qusheshu",1)<200 )
				return notify_fail("你现在毒计不够，不能使用「毒龙诀」。\n");


    

        if((int)me->query("jingli") < 1000  )
				return notify_fail("你的精气不够，无法使用「毒龙诀」。\n");
        
		i = me->query_skill("dulong-dafa", 1);
	

		message_vision(HBBLU+HIG"$N仰头长吸一口真气，运起「毒龙诀」，长啸之声音暗哑，宛如毒蛇嘶嘶有声，口中念念有词，毒龙大法威力大增!\n"NOR,me);
		
		me->set_temp("dldf/dulong",i);
		me->add_temp("apply/attack",i/5);
		if (me->query("gender")=="男性")
		{
				me->add_temp("apply/strike",i/5);
				me->add_temp("apply/hook",i/5);
		}
		if (me->query("gender")=="女性")
		{
				me->add_temp("apply/hand",i/5);
				me->add_temp("apply/dagger",i/5);
				me->add_temp("apply/whip",i/5);
		}
		me->add_temp("apply/dodge",i/6);
		
		if (me->query_skill("dulong-dafa",1)<450)
		    me->start_exert(1,"「毒龙诀」");
		me->add("neili",-200);
		me->add("jingli",-150);
		//if (objectp(me))
			call_out("remove_dulong",1,me,(int)i/15);
		return 1;
 }      
		

void remove_dulong(object me, int count)
{
        int i;
		object target,ob;
		if (!me||!me->query_temp("dldf/dulong")) return;
		
		i=me->query_temp("dldf/dulong");
        if( count-- < 0
			||!me->is_fight())
		{ 
            me->add_temp("apply/attack",-i/5);
			if (me->query("gender")=="男性")
			{
					me->add_temp("apply/strike",-i/5);
					me->add_temp("apply/hook",-i/5);
			}
			if (me->query("gender")=="女性")
			{
					me->add_temp("apply/hand",-i/5);
					me->add_temp("apply/dagger",-i/5);
					me->add_temp("apply/whip",-i/5);
			}
			me->add_temp("apply/dodge",-i/6);
			me->delete_temp("dldf/dulong");

			message_vision(HBBLU+HIG"$N毒龙诀运转完毕，长长地吐出一口灰色的浊气，显然带有剧毒！\n"NOR,me);
            return;
        }
		
		if (objectp(ob=present("jin she",me))
			&&random(10)>5)
		{
			if (me->query("env/神龙")=="攻击")
			{		
					message_vision(HIY"$N运起毒龙大法毒龙诀驱使自己的小金龙向敌人指了指！\n"NOR,me);
					ob->gongji();
				
			}else if (me->query("env/神龙")=="防御")
			{				
					message_vision(HIY"$N运起毒龙大法毒龙诀驱使自己的小金龙向自己指了指！\n"NOR,me);
					ob->huti();
			}
		}
		call_out("remove_dulong", 1, me, count);
}

int help(object me)
{
        write(WHT"\n毒龙大法之"+HIR"「毒龙诀」"WHT"：\n\n"NOR);
        write(@HELP
	毒龙大法乃是神龙岛内功绝技，乃是开山祖师
	洪教主根据门派独特心法所创立。既有其蛇毒
	的特性，又有其强悍的一面。
	「毒龙诀」绝技乃是利用毒龙大法的独门心法
	与各种毒药相结合后融合而成的一口心法，可
	以在短时间内增加自己的功力。
	男性侧重于掌法钩法，女性则在手法鞭法匕法
	上各自有独到增强。需解密方可施展。
	
	注意：set 神龙 <攻击|防御>

	攻击是指可以指示自己驯养的神龙协助自己去
	攻击敌人，而防御则是设定自己神龙为自己主
	动防御。注意，若自己驯养神龙死亡需要再去
	驯养一条。

	使用指令：yun dulong
		
要求：
	当前内力要求 2000 以上；
	最大内力要求 3500 以上；
	当前精力要求 1000 以上；
	基本内功等级 350  以上；
	毒龙大法等级 350 以上；
	神龙药理等级 200 以上；
	毒    计等级 180 以上；
	驱 蛇 术等级 200 以上
	激发内功为毒龙大法；
	450级后busy取消，飞跃。
HELP
        );
        return 1;
}

