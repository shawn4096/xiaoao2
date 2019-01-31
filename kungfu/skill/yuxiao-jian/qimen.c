// By Darken@SJ
// BY SOHU@XOJH
#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HIG"奇门诀"NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, attack_time, lvl,b;
        if( !target ) target = offensive_target(me);
        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                 return notify_fail("「奇门诀」只能对战斗中的对手使用。\n");
        if (!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "sword")
                 return notify_fail("你使用的武器不对。\n");
		if (!weapon->id("xiao"))
		         return notify_fail("你手里没有拿箫，无法施展出「奇门诀」。\n");
        if (!me->query("thd/wuji/yuxiao"))
				 return notify_fail("你尚未领悟“碧海涛声按玉箫”的真谛，无法施展出「奇门诀」。\n");
		if((int)me->query_skill("yuxiao-jian",1) < 100 )
                 return notify_fail("你的玉箫剑法还不够火候，使不出「奇门诀」。\n");
        if((int)me->query_skill("qimen-bagua",1) < 100 )
                 return notify_fail("你的奇门八卦还不够火候，使不出「奇门诀」。\n");
        if((string)me->query_skill_mapped("sword") != "yuxiao-jian" && userp(me))
                   return notify_fail("你现在无法使用「奇门诀」！\n");
        if((string)me->query_skill_mapped("parry") != "yuxiao-jian" && (string)me->query_skill_mapped("parry") != "tanzhi-shentong"&&userp(me))
                   return notify_fail("你现在无法使用「奇门诀」！\n");
        if((int)me->query_temp("yuxiao_lian") )
                return notify_fail("你现在已经在向对手使用「奇门诀」了。\n");
        if((int)me->query("max_neili", 1) < 1000 )
                 return notify_fail("你的内力修为不够使用「奇门诀」！\n");
        if((int)me->query("max_jingli") < 500 )
                 return notify_fail("你的精力修为不够使用「奇门诀」！\n");
        if((int)me->query("neili")<500)
                 return notify_fail("你的真气不够！\n"); 
        
        attack_time = me->query_skill("yuxiao-jian",1) / 2;

        if (attack_time < 2)  attack_time = 2;
        if (attack_time > 4)  attack_time = 4;
        if (me->query_temp("thd/is_fast")) attack_time += 2;

        msg = HIG "$N手中"+weapon->name()+HIG"连刺，潇洒自如，招招都是攻势，一招不待$n化解开去，剑招已连绵而至！\n"+
                 "$N东刺一剑，西削一招，连出"+chinese_number(attack_time)+"招，与武学常理完全相反。\n"+
                 "$n愈斗愈惊，周身要害似已全在"+weapon->name()+HIG"笼罩之下！\n"NOR;
		if (random(me->query_skill("qimen-bagua",1) > target->query_skill("qimen-bagua",1)/2)&& weapon->query("skill_tyle")=="xiao")
		{
		   message_vision(HIC"\n$n耳畔忽闻一阵婉转悠扬的箫声传来，$n大脑一片空白，似乎忘记了招架一般。\n"NOR,);
		   b=random(me->query_skill("qimen-bagua",1)/100);
		   target->add_busy(1+b);
		}
        message_vision(msg, me, target);
        lvl = me->query_skill("yuxiao-jian", 1) /10 + me->query_skill("qimen-bagua", 1)/ 2;
        me->add_temp("apply/attack", lvl);
        me->add_temp("apply/damage", lvl);
        me->add_temp("apply/sword", lvl);
        me->add("neili", -300);
        me->add("jingli", -80);
        /*
		for(i = 0; i < attack_time; i++)
                if (me->is_fighting(target))
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);*/
        //me->start_perform(4,"「奇门诀」");
        me->set_temp("yuxiao_lian", lvl);
		call_out("remove_effect",1,me,(int)lvl/10);
        //me->start_call_out( (: call_other, __FILE__, "remove_effect", me, target, lvl :), random(attack_time)+4);
        return 1;
}

void remove_effect(object me, int count)
{
        object weapon;
		int lvl;

		if (!me) return;
		lvl=me->query_temp("yuxiao_lian");
		weapon=me->query_temp("weapon");
		if (count<1
			|| !me->is_fighting()
			|| !weapon
			|| !weapon->id("xiao")
			|| me->query_skill("sword")!="yuxiao-jian"
			|| weapon->query("skill_type") != "xiao")
		{

			me->delete_temp("yuxiao_lian"); 
			me->add_temp("apply/attack", -lvl);
			me->add_temp("apply/damage", -lvl);
			me->add_temp("apply/sword", -lvl);
            if (weapon)
				message_vision(HIC"$N信手将手中的"+weapon->query("name")+HIC"挽了个花，从容不迫，状极潇洒。\n"NOR,me);
			else message_vision(HIC"$N信手挽了个花，从容不迫，状极潇洒。\n"NOR,me);
			return;
		}
		call_out("remove_effect",1,me,count--);
}

int help(object me)
{
        write(HIG"\n「奇门诀」："NOR"\n");
        write(@HELP
	奇门诀是桃花岛独特的一门武技，脚踩奇门八卦方位
	手中剑术采取特殊攻势，向对手快速攻击之余且能迷
	惑对手。短时期内会提升自身的剑法攻击。
	
	指令：perform sword.qimen

要求：
	碧海潮声等级 100 以上；
	玉箫剑法等级 100 以上；
	奇门八卦等级 100 以上；
	配合奇门八卦且手中持萧
HELP
        );
        return 1;
}



