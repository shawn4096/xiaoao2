// fenmo.c 焚魔决
// by sohu@xojh 

#include <ansi.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int i,ap,dp;
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「焚魔决」攻击只能对战斗中的对手使用。\n");

        if (!weapon || weapon->query("skill_type") != "blade"
           || me->query_skill_mapped("blade") != "ranmu-daofa")
                return notify_fail("你现在无法使出「焚魔决」绝技！\n");

        if (weapon->query("sharpness") > 3)
                return notify_fail("你手中之刀已是锋利之极，使用「焚魔决」绝技没有什么作用！\n");

        if (weapon->query("unique"))
                return notify_fail("你手中之刀已是锋利之极，使用「焚魔决」绝技没有什么作用！\n");
                
        if(me->query_skill("ranmu-daofa", 1) < 400 )
                return notify_fail("你的燃木刀法火候不够，使不出「焚魔决」绝技。\n");

        if(me->query_skill("blade", 1) < 400 )
                return notify_fail("你的基本功还不够娴熟，使不出「焚魔决」绝技。\n");
	   if (me->query_skill_mapped("parry")!="ranmu-daofa"&&me->query_skill_mapped("parry")!="cibei-dao")
                return notify_fail("你的招架不对，无法使用「焚魔决」绝技。\n");  

        if( (int)me->query_skill("yijin-jing", 1) < 400 )
                return notify_fail("你的易筋经等级不够，使不出「焚魔决」绝技。\n");

        if( (int)me->query_str() < 65)
                return notify_fail("你的膂力还不够强劲，不足65，使不出「焚魔决」绝技。\n");

        if( (int)me->query_int() < 30)
                return notify_fail("没有大智慧大般若，是使不出「焚魔决」绝技的。\n");
 
        if ( me->query_skill_mapped("force") != "yijin-jing")
                return notify_fail("没有易筋经作为根基，是无法使出「焚魔决」绝技的！\n"); 

        if(me->query_temp("rmdf/fenmo")) 
                return notify_fail("你现在正在使用「焚魔决」绝技。\n"); 

        if (me->query_temp("jgq/fumo"))
                return notify_fail("你现在正在使用「金刚伏魔」神功。\n"); 

        if (me->query("max_neili") < 1000)
                return notify_fail("你的内力修为不够。\n");

        if (me->query("neili") < 650)
                return notify_fail("你的内力不够。\n");

        if (me->query("jingli") < 200)
                return notify_fail("你的精力不够。\n");

        me->add("neili", -600);
        me->add("jingli", -150);        

		//fenwo's damage depends on how many times u pfmd       

        i = me->query("rmdf/fenmo");
        if (i > me->query_skill("blade",1)) 
			i = me->query_skill("blade",1);
        ap = me->query_dex(1);
	    dp = target->query_dex(1);
	
//and it will not be over ur enable blade skill

		me->add_temp("apply/damage",i);
		me->add_temp("apply/attack",i/2);//原来是/2
        
		me->set_temp("rmdf/fenmo", i);
        
		message_vision(HIY"\n$N连续向空气中劈出数刀，刀和空气燃烧发出噼啪作响声音，空气宛如燃烧一样，夹裹一股热浪直劈$n面门而去！\n"NOR,me,target);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);   
    /*    	
        if(random( ap + dp ) > dp&&me->is_fighting()) 
		{ 
        	message_vision(HIC"\n$N身法极强，又趁对方无缓息之际，又使出一刀，带着灼热之气，向$n后背直劈过去！\n"NOR,me,target);
        	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        }
        if(me->is_fighting()) 
		{ 
        	message_vision(HIR"\n$N心中默念佛法，心中恒定如石，誓灭天下邪魔外道，刀身被劲气催红，喝道，「焚魔天下」！\n"NOR,me,target);
        	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        }
*/
        weapon->add("fenmo", 1);
        
		if (weapon 
        && !weapon->query("unique")
		&& me->query("yjj/powerup")!="pass"
        && weapon->query("rigidity") < 2
        && weapon->query("fenmo") >= (3+weapon->query("rigidity"))) 
		{
           	message_vision(HIY"\n只听“咔咔”几声，$N手中的$n"HIY"在熊熊火焰中裂成了碎片！\n"NOR,me,weapon);
           	weapon->unequip();
           	weapon->move(environment(me));
           	weapon->set("name", "碎裂的" + weapon->query("name"));
           	weapon->set("value", 49);
           	weapon->set("weapon_prop", 0);
           	me->reset_action();
        }
        me->add_temp("apply/damage", -i);
        me->add_temp("apply/attack", -i/2);//原来是/2
        me->delete_temp("rmdf/fenmo");
        me->start_busy(1);
        me->start_perform(3,"焚魔决");
        me->add("fenmo", 1);
        return 1;
}
string perform_name(){ return HBWHT+HIR"焚魔决"NOR; }
int help(object me)
{
        write(HIY"\n燃木刀法之「焚魔诀」："NOR"\n\n");
        write(@HELP
	燃木刀法乃是少林三大终极兵器之一，是刀法的集大成武技
	此招乃是少林七十二绝技中不传之秘，武功练到高深处后，
	凭借深厚内力，可以做到以掌化刀，厉害无比。此门武功由
	少林玄苦大师修习，自玄苦大师圆寂后，此武技无人修成，
	当一代高僧鸠摩智凭借小无相神功演化燃木刀法大战少林寺
	时，使得此门武技名扬天下。同时，开了易筋经绝世内功，
	则内力控制自如，刀将不碎。
	焚魔决虽然是一招，但和熟练度相关，练习燃木刀越熟练则
	此招越是犀利，实乃燃木刀法一大杀招！

	指令：perform blade.fenmo 

要求：  
	当前内力需求 1000 以上；
	最大内力需求 10000 以上；
	当前精力需求 800 以上；
	燃木刀法等级 400 以上；
	易筋经功等级 400 以上；
	基本刀法等级 400 以上；
	激发刀法为燃木刀法；
	激发内功为易筋经神功；
	且手持木刀。

HELP
        );
        return 1;
}
