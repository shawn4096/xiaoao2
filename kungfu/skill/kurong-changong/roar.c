// roar.c 天龙吟
// by sohu@xojh 2014
//猛听得“呜哗－－”一声大喝，各人耳中均震得嗡嗡作响。保定帝知道这是佛门中一门极上乘的功夫，
//叫作‘狮子吼’，一声断喝中蕴蓄深厚内力，大有慑敌警友之效。

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        string force;
        mapping msg;
        object *ob;
        
        int i, skill, damage;

		if( (int)me->query("max_neili") < 5000 )
                return notify_fail("你的最大内力不够。\n");
        if( (int)me->query("neili") < 2000 )
                return notify_fail("你的当前内力不够。\n");
		if( (int)me->query("jingli") < 2000 )
                return notify_fail("天龙梵唱极为消耗精力，你的当前内力不够。\n");
        
		if (me->query_skill_mapped("force") != "kurong-changong" )
                return notify_fail("你现在的内功没有这项功能。\n");     

        if( environment(me)->query("no_fight") )
             return notify_fail("这里不能战斗。\n");
        if( (int)me->query_skill("force",1) < 250 )
                return notify_fail("你的基本内功等级修为不够。\n");
		if( (int)me->query_skill("kurong-changong",1) < 250 )
                return notify_fail("你的枯荣禅功等级修为不够。\n");
                
        if( (int)me->query_skill("buddhism",1) < 150 )
                return notify_fail("你的佛法禅定功夫不够。\n");
        
        if( (int)me->query("jingli") < 150 )
                return notify_fail("你太累了，还是休息一下吧。\n");      
        skill =me->query_skill("kurong-changong",1)+me->query_skill("buddhism",1);
		//skill =skill+random(skill);
        me->add("neili", -random(2000));
        me->receive_damage("jingli", random(1000));

        

        message_vision(HBRED+HIY "猛听得$N“呜哗--”一声大喝，各人耳中均震得嗡嗡作响。$N使出佛门中一门极上乘的功夫，\n"
								+"叫作‘天龙吟’，一声断喝中蕴蓄深厚内力，大有慑敌警友之效。\n\n" NOR, me);

        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
                if( wizardp(ob[i])||!living(ob[i]) || ob[i]==me ) continue;
                if( random(skill) < (int)ob[i]->query_skill("force",1)) continue;
                
                damage = skill;
                damage += damage;
                tell_object(ob[i], "你被这巨吼震的眼前发晕，脑中一片空白，不由一阵恍惚。\n");
                //逃跑救命战术啊
				if (ob[i]->is_fighting()) 
                {
					ob[i]->remove_all_enemy();
					message_vision("\n$N身体一缓，停止了战斗。\n", ob[i]); 
                }
                else if ((int)ob[i]->query_temp("pending/exercise")) 
                {
					force = ob[i]->query_skill_mapped("force");
					if (force) msg = SKILL_D(force)->exercise_msg(ob[i]);
					if (!msg || undefinedp(msg["halt_msg"]))
						message_vision("$N你只觉气息不顺，站了起来。\n", ob[i]);
					else
						message_vision("$N只觉气息不顺,"+msg["halt_msg"], ob[i]);
                }
                else if ((int)me->query_temp("pending/respirate") != 0) 
                message_vision("$N只觉气息不顺，猛吸几口大气，站了起来。\n", me);
                
				ob[i]->interrupt_me();
                        
                if( damage > 0 ) {
                        if (ob[i]->query("jing")>=damage)
							ob[i]->receive_damage("jing", damage, me);
                        else ob[i]->unconcious();
                        
                }
                if(living(ob[i]) && (random(me->query("combat_exp",1)) > ob[i]->query("combat_exp") / 2)){
					message_vision(HIY"$N一阵恍惚后，似乎反映有些迟钝。\n"NOR,ob[i]);
					ob[i]->add_busy(random(skill/100) +1);
				}
        }
		me->start_busy(2);
		//if (me->query_skill("kurong-changong",1)<450)
		//{
		me->start_exert(4,"天龙吟");
		//}
        return 1;
}

string exert_name() {return HIY"天龙吟"NOR;}


int help(object me)
{
        write(WHT"\n枯荣禅功「天龙吟」："NOR"\n");
        write(@HELP
	枯荣禅功乃是大理国护国寺院--天龙寺主持枯荣长老的内功心法
	相传佛祖涅磐是在八棵树之间。这八棵树分东西南北两棵辆棵分
	列，它们分别是一枯一荣，东西南北分别是：常与无常，乐与无
	乐，我与无我，净与无净。 讲究心中无枯无荣方是大成。枯荣
	长老心中有物，是以终其一生，只参得半枯半荣。
	
	此天龙吟能使玩家凭借雄厚内功以佛门狮子吼发出“呜哗－－”
	猛听得一声大喝，各人耳中均震得嗡嗡作响。并且有一定，一声
	断喝中蕴蓄深厚内力，大有慑敌警友之功效。

要求:
	枯荣禅功 200 级以上；
	最大内力 2000 点；
	当前内力 1500 点；
	需激发内功为枯荣禅功。

HELP
        );
        return 1;
}


