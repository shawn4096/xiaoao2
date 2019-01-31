// By sohu@xojh 更新
#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
       	string msg;
       	int i;
		object target;
	
		if(!target)
			target = offensive_target(me);
		if( (int)me->query_skill("force",1) < 350 )
                return notify_fail("你的内功还不够火候，不足350,使不出洛神。\n");  
       	if( (int)me->query_skill("lingbo-weibu",1) < 350 )
                return notify_fail("你的凌波微步还不够火候，使不出洛神。\n");  
       	if( (int)me->query("max_neili",1) < 5000 )
                return notify_fail("你的内力修为还不够火候，使不出洛神。\n");  
       	if( (int)me->query("jingli", 1) < 1500 )
                return notify_fail("你现在精力不够。\n");
       	if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("你现在内力不够。\n");
       	if (me->query_temp("lbwb/ls"))
                return notify_fail("你正在使用洛神。\n");
	     if (!me->query("quest/天龙八部/武功/pass"))
			 return notify_fail("你尚未得到凌波微步的真谛。\n");
			    

       	message_vision(HIC "$N越走越快，每一步踏出都暗合四相八卦之势,内息随着步法不住运转,转眼间犹如雾一样！\n\n"NOR,me);
		if (me->query("gender")=="男性")
		{
       		message_vision(HIW"$N身形潇洒，行走间大袖飘飘，端的是神态清逸！宛如神仙!\n\n"NOR,me);
		}else
			message_vision(HIW"$N容貌秀丽，休迅飞凫，飘忽若神，凌波微步，罗袜生尘，一番清丽脱俗之态！\n\n"NOR,me);
		
		if (objectp(target)
			&&me->query_skill("qimen-bagua",1)>=200 
			&&(random(me->query_int(1))>target->query_int()/2 || random(me->query_skill("dodge",1))>target->query_skill("dodge",1)/3))
		{
			message_vision(HIR"\n$N按照易经六十四卦的要求，踏着卦象方位行进，瞬间从第一步到最后一步正好行走一个大圈！\n\n"NOR,me);
			if (me->is_fighting() && objectp(target))
			{
				message_vision(HBBLU+HIW"$n一不小心为$N快速转动的身法所迷惑，刹那间有些失神！\n\n"NOR,me,target);
				target->add_busy(3+random(2));
			}
		}
       	me->add("neili", -(200+random(300)));
       	me->add("jingli", -(100+random(50)));
       	
		i = me->query_skill("lingbo-weibu", 1)/5 + me->query_int()+me->query_skill("qimen-bagua",1)/10;
       // i = i - random(i/6);
       	if (me->query_skill("lingbo-weibu", 1) < 350)
                i = i/3;
		else if (me->query_skill("lingbo-weibu", 1) < 450)
			 i = i/2;
		
       	me->add_temp("apply/dexerity", i);
       	me->add_temp("apply/dodge", i*2);
		me->add_temp("apply/parry", i);
       	me->add_temp("apply/armor", i);
		me->add_temp("apply/defense", i);

		me->set_temp("lbwb/ls", i);
       	if (me->query_skill("lingbo-weibu",1)<450)
			me->start_perform(1, "洛神");
		
       	call_out("remove_effect", 1, me, i, i);
       	return 1;
}

void remove_effect(object me, int count,int dex)
{
        if (!me) 
        	return;
        if( me->query_skill_mapped("dodge") != "lingbo-weibu" 
        || me->query("neili") < 100
        || count < 1)
        {
           	me->add_temp("apply/dexerity", -dex);
            me->add_temp("apply/dodge", -dex*2);
			me->add_temp("apply/parry", -dex);
       		me->add_temp("apply/armor", -dex);
			me->add_temp("apply/defense", -dex);
           	
			me->delete_temp("lbwb/ls");
           	message_vision(HIW"$N长吁一口浊气，凌波微步身法逐渐慢了下来。\n"NOR, me);
           	return;
        }
 		call_out("remove_effect", 1 , me, count -1,dex);
}
string perform_name(){ return HBBLU+HIG"洛神"NOR; }

int help(object me)
{
	write(HIW"\n凌波微步之「洛神」："NOR"\n\n");
	write(@HELP
	凌波微步是逍遥派的独门轻功步法，以易经八八六十四卦
	为基础，使用者按特定顺序踏着卦象方位行进，从第一步
	到最后一步正好行走一个大圈。此步法精妙异常，习者可
	以用来躲避众多敌人的进攻。
	凌波微步乃书剑中第一轻功，具有极强的躲避功能，且若
	深悟奇门八卦精要，则该武功威力又将产生飞跃。
	
	指令：perform dodge.luoshen

要求：
	当前内力要求 1500 以上；
	最大内力要求 5000 以上；
	当前精力需求 1000 以上；
	凌波微步等级 350 以上；
	基本轻功等级 350 以上；
	激发轻功为凌波微步；    
	注意：set 凌波微步 洛神 会有轻功的特殊防御效果
             

HELP
        );
        return 1;
}