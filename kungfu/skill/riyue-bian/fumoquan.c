#include <ansi.h>

inherit F_SSERVER;
private int remove_effect(object me, int amount);
int perform(object me,object target)
{
        object weapon,wp2;
        int skill;
     	if( !target ) target = offensive_target(me);
        if(!me->is_fighting() )
                return notify_fail("「金刚伏魔圈」只能在战斗中使用。\n");

        if((int)me->query_skill("yijin-jing", 1) < 350 )
                return notify_fail("你的内功等级不够，不能使用「金刚伏魔圈」。\n");
    
        if ((int)me->query_skill("riyue-bian", 1) < 350 )
                return notify_fail("你的日月鞭法不够娴熟，不能真正发挥「金刚伏魔圈」。\n");
        weapon= me->query_temp("weapon");
		wp2=target->query_temp("weapon");  
		if (!me->query("quest/sl/ryb/fumoquan/pass"))
	            return notify_fail("你虽然听说过伏魔圈威力，但尚未领悟真意，无法发挥「金刚伏魔圈」。\n");

        if (!weapon 
         || weapon->query("skill_type") != "whip"
         || me->query_skill_mapped("whip") != "riyue-bian")
                return notify_fail("你现在无法使用「金刚伏魔圈」来提高防御力。\n");
    
        if ((int)me->query("neili") < 1500 )
                return notify_fail("你现在内力太弱，不能使用「金刚伏魔圈」。\n");

        if ((int)me->query("jingli") < 500 )
                return notify_fail("你现在精力太少，不能使用「金刚伏魔圈」。\n");


        if( me->query_temp("jgq/fumo"))
                return notify_fail("你正在使用大金刚拳的特殊攻击「金刚伏魔」！\n");
		if ( me->query("class")!="bonze" ) 
                return notify_fail("你非僧人，俗世凡心太重，无法运使「金刚伏魔圈」。\n");
        if ( (int)me->query_temp("ryb/fumoquan") ) 
                return notify_fail("你正在使用「金刚伏魔圈」。\n");

  
        if (me->query_skill_mapped("force") != "yijin-jing")
                return notify_fail("你的内功有误，无法使用「金刚伏魔圈」。\n");
 
        message_vision(RED "$N口诵佛号“"HIY"我佛慈悲！”"RED"脸上殷红如血，僧袍都鼓了起来，手中"+weapon->name()+RED"急速转动，渐渐收短，\n"+
                           "守御相当严密。"+weapon->name()+RED"似有无穷弹力，似真似幻，无论敌人怎么变招抢攻，总是被弹了出去。\n"NOR, me); 
 
       if (me->query_skill("riyue-bian",1)<450)
        {		
			me->start_busy(1);
			me->start_perform(1,"「金刚伏魔圈」");

        }
        me->add("neili", -400);          
        me->add("jingli", -300);
		
        skill = me->query_skill("riyue-bian", 1);
		
		if (target->query("shen")<-10000
			||(target->query_skill_mapped("dagger")=="shenghuo-lingfa" && objectp(wp2)&&wp2->query("skill_type")=="dagger"))
		{
			skill=skill+me->query_temp("yijin-jing",1)/4;
			
			message_vision(YEL"$N施展的是正宗的佛门功法,正好克制了$n的功法，$n顿觉压力陡增！\n"NOR,me,target);
		}
        me->add_temp("apply/armor",  skill/4);
        me->add_temp("apply/parry",  skill/3);
        me->add_temp("apply/dodge",  skill/3);
		me->add_temp("apply/whip", skill/2);
        me->add_temp("apply/strength",  skill/8);
        me->set_temp("ryb/fumoquan", skill);
		call_out("check_fight",1,me,(int)skill/30);
        return 1; 
}

void check_fight(object me, int amount)
{  
        object wep;
		int skill;
        if (!me) return;
		skill=me->query_temp("ryb/fumoquan");
        wep = me->query_temp("weapon");  
        if(!me->is_fighting()
         || !wep
		 || amount<0
		 || wep->query("skill_type")!="whip" )
	{
			me->add_temp("apply/armor",  -skill/4);
			me->add_temp("apply/parry",  -skill/3);
			me->add_temp("apply/dodge",  -skill/3);
			me->add_temp("apply/whip", -skill/2);
			me->add_temp("apply/strength",  -skill/8);
			me->delete_temp("ryb/fumoquan");

			if(living(me) && !me->is_ghost())
				message_vision(RED"良久，$N所使金刚伏魔圈的威力渐渐平息，一切又恢复了原状。\n"NOR, me);
			return;
	}
       call_out("check_fight", 1, me, amount--);
}
//是否考虑伏魔圈增加增加连环攻击效果？
string perform_name(){ return HBYEL+HIR"金刚伏魔圈"NOR; }

int help(object me)
{
	write(HIC"\n日月鞭「金刚伏魔圈」："NOR"\n");
	write(@HELP
	日月鞭是少林三大武器之一，乃是修炼到极高阳刚之意后的由刚化柔的武功
	此时少林内功以达内力返照空明，功力精纯，不露棱角的境界。越长越是灵
	动，越短功力越强。长短收缩，自由收发于心。张无忌救谢逊，孤身犯险，
	以一抵抗三大神僧，那一战固然成就了张无忌的威名，但同时，少林三老的
	日月鞭也名扬天下。
	金刚伏魔圈是以高深的佛法，以金刚无相之意融入到鞭法之中，不仅提高自
	身的防御，同时增加日月鞭的攻击威力。对于戾气较重者或西域武技有一定
	克制功效。450后小飞。
	
	指令：perform whip.fumoquan

要求：	
	当前内力 1500 以上； 
	当前精力 500 以上； 
	易筋经等级 350 以上；
	日月鞭法等级 350 以上；
	禅宗心法等级 200 以上；
	激发鞭法为日月鞭法；
	激发日月鞭法为招架；
	激发易筋经为内功；
	装备长鞭类兵器。     
HELP
	);
	return 1;
}
