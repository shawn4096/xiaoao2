// Code of xojh
//dianxue.c 劲气注入武器，以剑尖点穴
//sohu@xojh 重新定位段家剑法为王爷招式

#include <ansi.h>

inherit F_SSERVER;

void checking(object me,object target,int count);

int perform(object me, object target)
{
        object weapon;
        int skill, skill1, damage;

        if (me->query_skill_mapped("force") != "qiantian-yiyang")
                return notify_fail("你所用得内功心法不对，无法运用一阳指。\n");

        if (!me->query("quest/dl/djjf/yiyang/pass"))
                return notify_fail("你只是知道这门绝技的厉害，但并未融汇贯通！\n");
        
		if (me->query_skill("force",1)<350
                || me->query_skill("qiantian-yiyang",1)<350
                || me->query_skill("duanjia-jian",1)<350 )
                return notify_fail("你的功力不够，无法运用这门心法！\n");

        if (!objectp(weapon = me->query_temp("weapon")) 
			|| weapon->query("skill_type")!="sword")
                return notify_fail("你没有使用正确的武器，无法运一阳指力于其上。\n");

       if (me->query_skill("jingmai-xue",1)<200)
               return notify_fail("你的经脉学等级不够，无法施展！\n");
        if (me->query_skill_mapped("sword") != "duanjia-jianfa" &&
            me->query_skill_mapped("parry") != "duanjia-jianfa")
                return notify_fail("你激发的剑招不对，无法使用一阳指力于兵器上。\n");

        if (me->query("neili") <= 1000)
                return notify_fail("你当前的内力不够运一阳指力！\n");

        if (me->query("jingli") <= 1000)
                return notify_fail("你当前的精力不够运一阳指力！\n");

        if (me->query_temp("djjf/yiyang"))
                return notify_fail("你已运一阳指指力于武器上了！\n");

        message("vision", HIY "\n"+me->query("name")+"紧握"+weapon->query("name")+"凝神运气,片刻脸上一片潮红。\n\n" NOR, environment(me), me);
        
		tell_object(me, HIY "\n你凝神运气，把一阳指劲力灌注到"+weapon->query("name")+"上。\n\n" NOR);



        skill = me->query_skill("qiantian-yiyang",1);
		
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/sword",skill/6);
		me->add_temp("apply/damage",skill/6);

		me->set_temp("djjf/yiyang",skill);
		if (me&&target)
			checking(me,target,skill/35);
        me->add("neili", -300);
        me->add("jingli", -250);

        return 1;
}

void checking(object me,object target,int count)
{
	int skill;
	object weapon;
	if (!me) return 0;
	skill=me->query_skill("duanjia-jianfa");
	if (count<0
		||!objectp(target)
		||me->query_skill("sword")!="duanjia-jianfa"
		||me->query_skill("parry")!="duanjia-jianfa"
		||!me->is_fighting())
	{
		message_vision(YEL"$N将一阳指力缓缓收功，剑法威力顿减！\n"NOR,me);
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/sword",-skill/6);
		me->add_temp("apply/damage",-skill/6);
		return;
	}
	if (random(10)>7)
	{
		switch (random(3))
		{
			case 0:
				message_vision(HIR"$N将一阳指力凝聚与剑尖，一股劲气直透而出，点中$n的大椎穴！\n"NOR,me,target);
				target->add_busy(1);
				break;
			case 1:
				message_vision(MAG"$N面色瞬间潮红，剑尖嗤嗤作响，笼罩$n的周身大穴，隐约剑气刺中$n的胸口！\n"NOR,me,target);
				target->apply_condition("no_exert",1);
				target->receive_wound("qi",1000+random(1000),me);
				break;
			case 2:
				message_vision(HIC"$N身形倒退，但转身之际突然跃起，反手以剑尖连续点中$n的寸关诸穴！\n"NOR,me,target);
				if (objectp(weapon=target->query_temp("weapon")))
				{
					weapon->move(environment(target));
					message_vision(CYN"$n一时不查，手中的"+weapon->query("name")+CYN"掉落在地！\n"NOR,me,target);
					
				}
				break;
		}
	}
	call_out("checking",1,me,count--);
     
}       
string perform_name() {return HIY"以剑点穴"NOR;}

int help(object me)
{
        write(HIR"\n段家剑法之「以剑点穴」："NOR"\n\n");
        write(@HELP
	段家剑法乃是大理段家剑法的精粹，大理乃皇族，同时
	也是武林人士，除了大理一阳指绝世武功外，还有其他
	武技享誉江湖。以剑点穴乃是将一阳指劲气融入到剑法
	之中，以剑尖点住对方。学解密方可修习。
	
	perform sword.dianxue

要求：
	当前内力需求 1000 以上；
	当前精力需求 1000 以上；
	基本剑法等级 350  级；
	基本内功等级 350  级；
	段家剑法等级 350  级；
	乾天一阳等级 350  级；
	经脉学的等级 200  级；
	激发剑法为段家剑法；
	激发招架为段家剑法；
	激发内功为乾天一阳；
	且手持剑类兵器。

HELP
        );
        return 1;
}
