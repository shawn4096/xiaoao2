//yusui.c 玉碎刀光
//cre by sohu@xojh

#include <ansi.h>
inherit F_SSERVER;
int perform(object me,object target)
{
        int skill;
        object weapon = me->query_temp("weapon");
        skill = me->query_skill("murong-daofa",1);
        
		if (!me->query("quest/mr/mrdf/yusui/pass"))
			return notify_fail("你只是听说过玉碎刀光绝技，但却不知道该如何使用。\n");                

		
        if( !target ) target = offensive_target(me);

        if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))               
                return notify_fail("玉碎刀光只能对战斗中的对手使用。\n");                

        if( (int)me->query_skill("murong-daofa", 1) < 250 )
                return notify_fail("你的刀法还未练成，不能使用玉碎刀光！\n");        

        if (!weapon
         || weapon->query("skill_type") != "blade"
         || me->query_skill_mapped("blade") != "murong-daofa")
                return notify_fail("你手里没有刀，无法使用玉碎刀光！\n");




        if(me->query_skill_mapped("parry") != "xingyi-zhang")
		if(me->query_skill_mapped("parry") != "douzhuan-xingyi")

			if(me->query_skill_mapped("parry") != "murong-daofa")
                return notify_fail("你的招架功夫不对，无法使用玉碎刀光！\n");

        if((int)me->query("max_neili") < 3000 )
                return notify_fail("你现在内力修为不够，不能使用玉碎刀光！\n");      

        if((int)me->query("neili") < 500 )
                return notify_fail("你现在内力不足，不能使用玉碎刀光！\n");      

        if((int)me->query_skill("blade", 1) < 250 )
                return notify_fail("你的基本刀法不够娴熟，不能在刀招中夹杂使用玉碎刀光。\n");
        if((int)me->query_skill("murong-daofa", 1) < 250 )
                return notify_fail("你的慕容刀法不够娴熟，不能在刀招中夹杂使用玉碎刀光。\n");

        if(me->query_temp("mrdf/yusui"))
                return notify_fail("你正在施展玉碎刀光绝技。\n");

        message_vision(CYN"\n$N将手中的"+weapon->query("name")+CYN"一抖，内力激发下，顿时幻起片片刀光，宛如玉珠崩盘！\n"+
			"$N施展的正是慕容刀法绝技"HIW"「玉碎刀光」"CYN"$n只觉眼前一片刀光，在阳光反射下极为耀眼！\n"NOR, me,target);
        me->add("neili", -200); 
        me->add("jingli", -150);
        

        me->add_temp("apply/attack", skill/8); 
        me->add_temp("apply/blade",skill/5);
		me->add_temp("apply/damage",skill/8);
		
		me->set_temp("mrdf/yusui",skill); 
		me->set("mrdf/yusui",skill);//不用临时变量，以免退出后无值
        call_out("xs_attack",1,me,(int)skill/20);
			
		return 1;
}

int xs_attack(object me,int count)
{
	object weapon;
	
	int skill;
	
	if (!me) return 1;

	skill=me->query("mrdf/yusui");
	weapon=me->query_temp("weapon");
	if (count<0
		|| !me->is_fighting()
		|| me->query_skill_mapped("blade")!="murong-daofa"
		|| !weapon
		|| weapon->query("skill_type")!="blade")
	{
		me->add_temp("apply/attack", -skill/8); 
        me->add_temp("apply/blade",-skill/5);
		me->add_temp("apply/damage",-skill/8);
		me->delete_temp("mrdf/yusui");
		me->delete("mrdf/yusui");
		message_vision(CYN"\n$N缓缓收功，长出一口气,将慕容刀法「玉碎刀光」停了下来！\n"NOR, me);

		me->start_perform(4,"玉碎刀光");

		return 1;

	}   
	 
     call_out("xs_attack",1,me,count--);
}

string perform_name(){ return HIW"玉碎刀光"NOR; }

int help(object me)
{
        write(HIC"\n慕容刀法之"+HIW+"「玉碎刀光」"NOR"\n\n");
        write(@HELP
	慕容刀法乃是慕容家族中传给家臣们的重要刀法武技，慕容氏
	早期乃是大燕国后裔，自慕容垂开始。崛起于军旅之间，刀法
	历经实战的演练，已经融合不少其他门派的刀法绝技，一刀既
	出，刀中夹掌。端的是厉害无比，防不胜防，因为是为家臣所
	用，所以内功不做特殊要求，若臂力越大，威力将增强。
	
	注意：该招为慕容刀法精髓所在，起于军旅中宁为玉碎不为瓦
		全的血气之勇，可向包不同询问解密事由。
	
指令：perform blade.yusui

要求：
	当前内力要求 500 以上；
	最大内力要求 3000 以上；
	当前精力要求 1000 以上；
	慕容刀法等级 250 以上；
	基本刀法等级 250 以上；
	激发招架为慕容刀法或斗转星移；
	手中持刀
                
HELP
        );
        return 1;
}
