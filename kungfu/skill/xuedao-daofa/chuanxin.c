// chuanxin.c 穿心刀
// edit by sohu@xojh 2015

#include <ansi.h>
//#include <skill.h>
//#include <combat.h>
//#include <weapon.h>
//inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
 
string perform_name(){ return HIC"穿心刀"NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg, weaname;
        int lvl,damage,p;


        lvl = (int)me->query_skill("xuedao-daofa",1);
        
        
		target = me->select_opponent();

        if( !me->is_fighting() )
                return notify_fail("「穿心刀」只能在战斗中使用。\n");

        if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");

        if((int)me->query_dex() < 28)
                return notify_fail("你的身法不够, 目前还不能使用这项绝技! \n");

        if((int)me->query_skill("dodge",1) < 100)
                return notify_fail("你的轻功修为不够, 不能使用「穿心刀」！\n");
 
        if((int)me->query_skill("xuedao-jing",1) < 100)
                return notify_fail("你的刀法修为不够， 目前不能使用「穿心刀」! \n");

        if((int)me->query_skill("xuedao-daofa",1) < 100)
                return notify_fail("你的血刀刀法修为不够， 目前不能使用「穿心刀」! \n");

        if( me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("你必须使用血刀刀法，才能使用「穿心刀」的绝技！\n");
		
		if ( me->query_skill_mapped("parry") != "xuedao-daofa" && me->query_skill_mapped("parry") != "jingang-liantishu")
             	return notify_fail("你的招架不对，必须激发刀法为血刀刀法或金刚炼体术。\n");

        if( me->query_skill_mapped("force") != "xuedao-jing" && me->query_skill_mapped("force") != "shenzhao-jing")
                return notify_fail("你现在所使用的内功同「血刀刀法」向抵触，不能使出「穿心刀」的绝技！\n");

        if( (int)me->query("max_neili") < 1200 )
                return notify_fail("你的内力修为不够！\n");
        if((int)me->query("neili")<600)
                return notify_fail("你的真气不够！\n"); 
        if((int)me->query("jingli")<200)
                return notify_fail("你的精力不够！\n"); 

        weaname = weapon->query("name");

		msg = YEL "\n$N狂啸声中，运起"HIR"「穿心刀」"YEL"秘诀，刹时身法如电，往复奔跑中，蓦然回转\n双手握住"NOR+weaname+YEL"刀柄，直刺$n的心窝！\n"NOR;
        message_vision(msg,me,target);

        damage=me->query_skill("xuedao-jing",1)+me->query_skill("blade",1)+lvl;
		damage=damage*4;
		damage=damage+random(damage);
		if (damage>4000) damage=3000+random(1000);
		if (damage<1500) damage=1500;

		if (random(lvl)>target->query_skill("parry",1)/2
			||random(me->query("combat_exp"))>target->query("combat_exp")/2)
        {
						
		   msg = RED"$N迎面对$n一声大喝：「着！」，"+weapon->query("name")+RED"在$n胸口对穿而过!\n殷红的鲜血瞬间从$n胸口喷了出来，眼见是活不成了。\n"NOR;
		   p = (int)target->query("qi")*100/(int)target->query("max_qi");
           
		   target->receive_damage("qi", damage,me);
		   target->receive_wound("qi", damage/3,me);
 
		  // target->set_temp("last_damage_from", me);
           
		   msg += damage_msg(damage, "刺伤");
           msg += "( $n"+eff_status_msg(p)+" )\n";
           msg = replace_string( msg, "$l", "胸口" );
           msg = replace_string( msg, "$w", weapon->query("name"));
		   message_vision(msg, me, target);
		   
		  if(userp(me) && me->query("env/damage"))
			   tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage*4/3+ WHT"点攻击伤害。\n"NOR); 
			
		   if (!userp(target)&&random(target->query("kar")) < 5){
                 message_vision(CYN"$n哪里见过如此狠辣的招数，双眼惊恐地看着$N,一刀穿心，倒地而亡。"NOR, me, target);
                 target->die();
           }


        }
		

		me->add_temp("apply/blade", lvl/5);
        me->add_temp("apply/attack", lvl/3);
        me->add_temp("apply/damage", lvl/4);
		me->set_temp("xddf/chuanxin",1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->delete_temp("xddf/chuanxin");
		
		me->add_temp("apply/blade", -lvl/5);
        me->add_temp("apply/attack", -lvl/3);
        me->add_temp("apply/damage", -lvl/4);

        me->add("neili", -50-random(200));
        if(me->query("neili")<0) me->set("neili",0);
        me->add("jingli", -80);
        me->start_busy(1);
        me->start_perform(3,"穿心刀");        
        return 1;
}

int help(object me)
{
	write(RED"\n血刀刀法之「穿心刀」："NOR"\n\n");
        write(@HELP

	穿心诀乃是血刀老祖独门武技，变幻莫测的刀法绝技
	在交战过程中，忽然转身，以诡异的角度出刀，一刀
	穿心而过，端的是防不胜防。乃是血刀门入门武技。
	注：对非玩家有一刀穿心效果。
	
	指令: perform blade.chuanxin

要求：
	最大内力 1200 以上；
	当前内力 600  以上；
	当前精力 400  以上；
	基本身法 28   以上；
	基本刀法 100  级以上
	血刀经   100  级以上
	血刀刀法 100  级以上；
	激发刀法血刀刀法；
	激发招架为血刀刀法或金刚护体术；
	激发内功血刀经；
	装备刀类武器；
HELP
        );
        return 1;
}