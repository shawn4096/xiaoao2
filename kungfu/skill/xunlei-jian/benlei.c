// benlei.c 奔雷剑诀
#include <ansi.h>
//改名叫奔雷诀---by daidai 2007-06-26
inherit F_SSERVER;
void remove_effect(object me, int count);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, attack_time, lvl;
        if( !target ) target = offensive_target(me);
        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
            return notify_fail("「奔雷诀」只能对战斗中的对手使用。\n");
        if (!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "sword")
            return notify_fail("你使用的武器不对。\n");
        if( me->query_skill("xunlei-jian",1) < 200 )
            return notify_fail("你的迅雷剑法还不够火候，使不出「奔雷诀」。\n");
        if( me->query_skill("force",1) < 200 )
            return notify_fail("你的基本内功还不够火候，使不出「奔雷诀」。\n");
        if( me->query_skill_mapped("sword") != "xunlei-jian")
		//	||me->query_skill_mapped("parry") != "xunlei-jian" )
          return notify_fail("你现在没激发迅雷剑，无法使用这个绝招！\n");
        if( me->query_skill("xuantian-wuji",1) <200)
            return notify_fail("你不用玄天无级内功支持是无法使用这个绝招的！\n");
        
        if( me->query_temp("xlj/benlei") )
               return notify_fail("你现在已经在向对手使用「奔雷诀」了。\n");
       
        if( me->query("max_neili", 1) < 3000 )
               return notify_fail("你的最大内力修为不够使用「奔雷诀」！\n");
        if( me->query("jingli") < 500 )
			return notify_fail("你的精力修为不够使用「奔雷诀」！\n");
	 	if( me->query_dex() < 40 )
			return notify_fail("你的后天有效身法修为不够使用「奔雷诀」！\n");
        if( me->query("neili")<500)
            return notify_fail("你的真气不够！\n"); 
   
		msg = HBMAG "$N手中"+weapon->name()+HBMAG"呜呜做响，剑尖指天，突然身形拔高，不待$n反应过来又连续向$n攻去！\n"NOR;
        message_vision(msg, me, target);
        if (me->query("quest/kl/xlj/wuxue/pass"))
        	lvl = me->query_skill("xunlei-jian", 1) + me->query_skill("xuantian-wuji", 1)/ 6;
        else lvl=me->query_skill("xunlei-jian", 1);

		lvl = lvl/8;
		me->set_temp("xlj/benlei", lvl);
        
		me->add_temp("apply/damage", lvl/3);
        me->add_temp("apply/sword", lvl);
        me->add_temp("apply/attack", lvl);
        
        if (me->query_skill("xunlei-jian",1)<300)
			me->start_perfrom(2,"「奔雷诀」");
        me->add("neili", -300);
        me->add("jingli", -80);
       
        call_out("remove_effect",0,me,(int)lvl/10);
        return 1;
}

void remove_effect(object me,int count)
{
        int lvl;
		object weapon;
		if (!me) return;
		lvl =(int)me->query_temp("xlj/benlei");
		weapon=me->query_temp("weapon");

        if (count < 0 
			|| !me->is_fighting()
			|| !weapon
			|| weapon->query("skill_type")!="sword"
			|| me->query_skill_mapped("parry")!="xunlei-jian"
			|| me->query_skill_mapped("sword")!="xunlei-jian")
        {      
			me->add_temp("apply/damage", -lvl/3);
			me->add_temp("apply/sword", -lvl);
			me->add_temp("apply/attack", -lvl);
			me->delete_temp("xlj/benlei");

			message_vision(MAG"$N的奔雷攻势渐渐慢了下来，缓缓呼出一口浊气。\n"NOR,me);
			return;
		}
		call_out("remove_effect",1,me,count -2);
		return;

}
string perform_name() {return HIW"奔雷诀"NOR;}

int help(object me)
{
    write(HIY"\n迅雷剑法「"HIW"奔雷诀"WHT"」："NOR"\n");
    write(@HELP
	迅雷剑乃是昆仑的初级剑法，由何足道观悟天地变化所得。
	因昆仑山天高地寒，雷暴天气颇多，由此领悟剑法的快捷
	本意，需要高深的身法支持。
	迅雷诀是迅雷剑法中重要的辅助进攻武技，玩家可以自己
	需要仔细体会,300级后小飞，取消busy。

	指令：perform benlei
	
要求：
	基本内功等级 200 级以上；
	迅雷剑法等级 200 级以上；
	有效身法等级 40    以上；
	基本剑法等级 200 级以上，
	最大内力要求 3000 以上，
	当前内力要求 1000 以上，
	当前精力要求 1000 以上，
	激发剑法迅雷剑；
	内功不限；
	需手持剑类武器。    

HELP
	);
	return 1;
}

