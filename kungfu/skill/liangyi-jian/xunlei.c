
//xunlei.c 迅雷剑意意
// cre by sohu@xojh 
//主要考虑就是将迅雷剑意的武功由前期迅雷剑意意传承过来，
//主要就是快攻招式，夹杂在攻击中出招，不死不休。

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
void checking(object me, object target, int count);
void xunlei_end(object me);

int perform(object me, object target)
{
        object weapon, ob;
        string msg, string1;
        int speed, attack, lv, damage;

        lv = (int)me->query_skill("liangyi-jian", 1); 
      
        speed = me->query_skill("lianyi-jian",1)/20;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
			return notify_fail("两仪剑之「迅雷剑意」只能对战斗中的对手使用。\n");
		if( !me->query("quest/kl/lyj/xunlei/pass"))
                return notify_fail("你只是听过有这门绝技，无法施展出"HIG"迅雷剑意"NOR"。\n");
        if( me->query_temp("lyj/xunlei"))
			return notify_fail("你正在施展迅雷剑意，剑势未尽，不能再施展「迅雷剑意」！\n");
	//	if( me->query_temp("lyj/hundun") )
                //return notify_fail("你的正在使用混沌剑网绝技，无法施展出"HIG"迅雷剑意"NOR"绝技。\n");
        if (!objectp(weapon = me->query_temp("weapon"))
			|| (string)weapon->query("skill_type") != "sword")
			 return notify_fail("你使用的武器不对。\n");
		if( me->query_dex() < 70 )
			return notify_fail("你的后天身法不够！\n");

        if( (int)me->query("neili") < 1500 )
			return notify_fail("你的内力不够！\n");
		if( (int)me->query("neili") < 1000 )
			return notify_fail("你的精力不够！\n");
        if( me->query_skill("liangyi-jian", 1) < 450 )
			return notify_fail("你的「两仪剑法」未臻高妙境界，无法使用「迅雷剑意」！\n");
		if( me->query_skill_mapped("sword") !="liangyi-jian"
			||me->query_skill_mapped("parry") !="liangyi-jian" )
			return notify_fail("你没激发「两仪剑法」，无法使用「迅雷剑意」！\n");
        if( me->query_skill_mapped("force") !="xuantian-wuji")
			return notify_fail("你没激发「玄天无极」功，无法使用「迅雷剑意」！\n");
		
		if( me->query_skill("xuantian-wuji", 1) < 450 )
             return notify_fail("你的玄天无极修为不够，无法使用「迅雷剑意」！\n");

        msg = HIG "\n$N手中"+weapon->query("name")+HIG"剑尖指向自己胸口，剑柄斜斜向外，怪异之极，竟似回剑自戕一般！\n" NOR;
        msg += HIG "这招正是两仪剑的绝技「迅雷剑意」，招式施展中剑势如虹，隐隐有风雷之声！\n" NOR;

		message_vision(msg, me,target);
        
		if (me->query_skill("liangyi-jian",1)<550)
			me->start_busy(1);
        
        me->set_temp("lyj/xunlei",lv);
        me->add("neili", -500);
        if (me->is_fighting()&& objectp(target))
            call_out("checking", 1, me, target,speed);
        else
			call_out("xunlei_end",1);
		return 1;
}

void checking(object me, object target, int count)
{
		int damage,k;
        object weapon;
		if (!me) return;
		
		damage = (int)me->query_skill("liangyi-jian", 1)+ (int)me->query_skill("xuantian-wuji", 1);
        damage = damage*2 + random(damage);
		
		if ( !objectp( me ) ) return;
        
		if( !target ) target = offensive_target(me);
		
		//weapon = me->query_temp("weapon");
	    //招数越高，威力越大
		//if (random(me->query_skill("liangyi-jian",1))>450) k=3;
	  //  else k=2;
	    

        if (!objectp(weapon = me->query_temp("weapon"))
			|| (string)weapon->query("skill_type") != "sword")
		{
			tell_object(me, HIR"\n你手中无剑，当下停止了迅雷剑意的架势。\n" NOR);
			me->delete_temp("lyj/xunlei");
			call_out("xunlei_end", 2, me);
			return;
		}
		else if ( weapon->query("weapon_prop") == 0 ) {
			tell_object(me,HIC "\n你的"+weapon->name()+HIC"已毁，无法持续迅雷剑意的攻势！\n\n" NOR);
            //退出
			call_out("xunlei_end", 2, me);
			me->delete_temp("lyj/xunlei");
			return;
		}
         else if ( (int)me->query("neili") < 1500  ) {
			message_vision(HIR"$N的内劲後继无力，不得不停止迅雷剑意的攻势！\n" NOR, me,target);
            call_out("xunlei_end", 2, me);
			me->delete_temp("lyj/xunlei");
			return;
		}
		else if ( me->query_skill_mapped("sword") != "liangyi-jian" ) {
			tell_object(me, HIR "\n你转而施展其他剑法，无法再以迅雷剑意攻敌！\n\n" NOR);
            call_out("xunlei_end", 2, me);
			me->delete_temp("lyj/xunlei");
			return;
		}

        else if ( //count <= 0 
			!me->is_fighting()
			|| !objectp(target)) 
		{
			tell_object(me, HIC "\n你蓄积的剑势耗尽，当下收回了迅雷剑意的攻势。\n" NOR);
            call_out("xunlei_end", 2, me);
			me->delete_temp("lyj/xunlei");
			return;
		}

		if( environment(target) != environment(me) ) {
			tell_object(me, "你见对方已经不在这里，当下停止了迅雷剑意的攻势。\n");
            call_out("xunlei_end", 2, me);
			me->delete_temp("lyj/xunlei");
			return;
		}
		me->set_temp("lyj/xunlei1",1);
        switch (random(3))
        {
			
			case 0:
				message_vision(HIY"$N纵身近前，"+weapon->name()+HIY"陡然弯弯弹出，剑尖直刺$n，出招之快疾若闪电，快若奔雷！\n" NOR, me,target);
				
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);
				//COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
				me->add("neili", -random(600));
				me->add("jingli", -random(500));

				message_vision(HIG"结果$n被剑招所逼，踉踉跄跄退了好几步！\n"NOR,me,target);
				target->add_busy(1+random(3));
				break;
		 	case 1:
				message_vision(HIW"$N伸指在"+weapon->name()+HIW"上一弹，剑声嗡嗡，有若龙吟，"+weapon->name()+HIW"颤处，剑锋来势神妙无方！\n" NOR, me,target);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?3:1);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
				//COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
				if ( random(me->query_dex(1))>target->query_dex(1)/2 )
				{   
					message_vision(RED"结果，$n已被长剑已刺入头部，深入寸许，鲜血如注！\n"NOR,me,target);
					target->receive_damage("qi",damage/2,me);
					target->receive_wound("qi",damage/4,me);        			
        		}
				me->add("neili", -random(200));
				me->add("jingli", -random(100));
				break;
			case 2:
				message_vision(HIG"$N陡然间大喝一声，"+weapon->name()+HIG"上寒光闪动，喝道：「"+target->name()+HIG"，可小心了！」\n" NOR, me,target);
				message_vision(HIR"只见$N随手挥剑，"+weapon->name()+HIR"颤处，前后左右，瞬息之间已攻出了四四一十六招！\n" NOR, me,target);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
				//COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
				message_vision(HIR"结果$n已被刺中数剑，口中鲜血狂喷而出！\n"NOR,me,target);    
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);		
				target->receive_damage("qi", damage,me);
				target->receive_wound("qi", damage/2,me);
				me->add("neili", -random(300));
				me->add("jingli", -random(200));
				break;
        }
		me->delete_temp("lyj/xunlei1");
		call_out("checking",2,me,target,count -1);
		return;
        	    
}

void xunlei_end(object me)
{
        object weapon;
		if ( !objectp( me ) ) return;
        
		weapon = me->query_temp("weapon");
        me->delete_temp("lyj/xunlei");

		message_vision(HIG "\n$N将长剑插入剑鞘，这迅雷剑诀极为耗费内力，$N暗自调息，渐渐平复腾涌的真气。\n\n" NOR,me);
      
		return;

}

string perform_name() {return HIR"迅雷剑意"NOR;}

int help(object me)
{
    write(WHT"\n两仪剑法「"HIR"迅雷剑意"WHT"」："NOR"\n");
    write(@HELP
    两仪剑法乃是昆仑派绝技，当初昆仑三圣何足道以此剑法横扫西域诸雄。
	后来在少林大战中一战成名，凭借的就是此剑法。两仪剑乃是正宗的正
	两仪剑法，剑法轻灵迅捷，不以力胜，但却将剑法灵动多变发挥到极致。
	倘若身法轻功好，则两仪剑法的威力更上一层楼。
	迅雷剑意是将何足道的迅雷剑法进行融合后，将迅雷剑意的迅捷快攻技
	巧，融入到两仪剑中，使得两仪剑在轻灵难测，变化多端中更显迅捷。
	500级第一次飞跃，550级后彻底大飞。
    
	指令：perform xunlei
	
要求：
	玄天无极等级 450 级以上；
	两仪剑法等级 450 级以上；
	有效身法等级 70    以上；
	基本剑法等级 450 级以上，
	当前内力要求 1500 以上，
	当前精力要求 1000 以上，
	激发内功玄天无极功；
	激发剑法和招架为两仪剑；
	需手持剑类武器。    

HELP
	);
	return 1;
}


