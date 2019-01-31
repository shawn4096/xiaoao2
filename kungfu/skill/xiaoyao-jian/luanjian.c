// luanjian.c 逍遥剑法之 乱披风，源自苦头陀
// By sohu@xojh

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int i,j,damage,count,skill;
		object weapon,tweapon;
		weapon=me->query_temp("weapon");
		//weapon2=present("sword",me);
		skill=me->query_skill("xiaoyao-jian",1);
        
	
        if( !target ) target = offensive_target(me);
        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("「乱剑诀」只能在战斗中使用。\n");       
        if( !objectp(me->query_temp("weapon")) )
               return notify_fail("手中无武器，如何能施展「乱剑诀」！\n");
        if (!me->query("quest/mj/xyj/luanjian/pass"))
                return notify_fail("你虽听说过「乱剑诀」但尚未得到范瑶的传授！\n");
		if (!weapon||weapon->query("skill_type")!="sword")
				return notify_fail("你的武器不对！\n");
        if((int)me->query_skill("sword", 1) < 400 )
                return notify_fail("你的基本剑法太低，无法使用「乱剑诀」。\n");  
        if((int)me->query_skill("xiaoyao-jian", 1) < 400 )
                return notify_fail("你的逍遥剑还不够娴熟，不能使出「乱剑诀」。\n");
        if (me->query_skill_mapped("parry") != "xiaoyao-jian"
           && me->query_skill_mapped("parry") != "qiankun-danuoyi")
                return notify_fail("你的招架不对，又岂能使得「乱剑诀」？！\n");   
        if (me->query_skill_mapped("sword") != "xiaoyao-jian")
                return notify_fail("你的剑法不对，又岂能使得「乱剑诀」？！\n");   
	    if ( me->query("max_neili") < 3500 )
                return notify_fail("你内力修为太浅，无法使得「乱剑诀」！\n");                
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在真气不够，不能发出「乱剑诀」。\n");   
		if( (int)me->query("jingli") < 1000 )
                return notify_fail("你现在精力不够，不能发出「乱剑诀」。\n");       
        if( (int)me->query_con() < 65 )
                return notify_fail("你现在后天根骨不够，不能发出「乱剑诀」。\n");       

        if((int)me->query_skill("force", 1) < 400 )
                return notify_fail("你的基本内功等级不够，不能应用「乱剑诀」。\n");       
    
        if (me->query_temp("xyj/luanjian"))
                return notify_fail("你正在施展「乱剑诀」。\n");       


        message_vision(WHT"$N刷的一剑，斜刺而至，剑招忽快忽慢，处处暗藏机锋。$n一加拆解，$N立即撤回，另使新招，几乎没一招是使得到底了的。\n"NOR,me, target);
        message_vision(WHT"$N手中"+weapon->query("name")+WHT"挥舞，使出「"HIR"乱剑诀"WHT"」中的“乱披风”势来，白刃映日，有如万道金蛇乱钻乱窜！\n"NOR,me,target);
		me->add("neili", -600);
	 	
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/damage",skill/10);
		me->add_temp("apply/sword",skill/6);
		me->set_temp("xyj/luanjian",skill);
		call_out("remove_effect",1,me,(int)skill/50);
		
		
        return 1;

}
void remove_effect(object me,int count)
{
	int skill;
	object weapon;
	if (!me) return;
	skill=me->query_temp("xyj/luanjian");
	weapon=me->query_temp("weapon");
	if (!me->is_fighting()
		||count<0
		||!weapon
		|| weapon->query("skill_style")!="sword"
		||me->query_skill_mapped("sword")!="xiaoyao-jian")
	{
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/damage",-skill/10);
		me->add_temp("apply/sword",-skill/6);
		me->delete_temp("xyj/luanjian");
		//me->start_perform(5, "「乱剑诀」");  
		message_vision(WHT"$N蓦地里倒过剑鞘，刷的一声，剑鞘已套上了剑刃，双手环抱一搭。\n"NOR,me);
		return;
	}
	call_out("remove_effect",1,me,count--);

}

string perform_name(){ return HIY"乱"+HIC+"剑"+WHT+"诀"NOR; }
int help(object me)
{
        write(HIG"\n逍遥剑法之"+HIC"「乱剑诀」"NOR"\n");
        write(@HELP
	杨逍乃是明教光明左使，与范遥合称”逍遥二仙“。一身武功极其驳杂，
	最具代表性的即为这逍遥剑法，当年少林寺一战，杨逍以资深武功和
	少林三老一番大战，其武功之庞杂与怪异表现的淋漓尽致，连平素一
	项都不服气的范遥都深为叹服。
	光明右使范瑶当初以苦头陀的身份卧底蒙古，后来在和张无忌一战中
	剑法极其杂驳，尤其是使出这乱剑诀后，连张无忌都认为范瑶的剑法
	超过八臂神魔方东白的剑法。
	「乱剑诀」乃是逍遥二仙范瑶的绝技，一身功夫全靠博杂。可以手持剑类
	武器来施展此招，凭空增加不少威力。
	
	指令;perform sword.luanjian

要求：  
	当前内力要求 1000 以上；
	最大内力要求 3500 以上；
	当前精力要求 1000 以上；
	逍遥剑法等级 400 以上；
	圣火神功等级 400 以上；
	基本剑法等级 400 以上；
	基本内功等级 400 以上；
	后天根骨需求 65  以上;
	激发剑法为逍遥剑法；
	激发招架为逍遥剑法或乾坤大挪移；
	激发内功不限。
HELP
        );
        return 1;
}