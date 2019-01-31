// jiuqu.c by sohu@xojh
// 九曲剑 钟镇绝技
//九曲变化之意
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
int ssj_songyang(object me,int count);

int perform(object me, object target)
{
	int damage,skill,p;
	string msg;

	object weapon = me->query_temp("weapon");
    skill=me->query_skill("songshan-jian",1);
	if( !target ) target = offensive_target(me);
   
	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("「九曲剑」只能对战斗中的对手使用。\n");
 
	if( me->query_skill_mapped("force")!="hanbing-zhenqi")
		if( me->query_skill_mapped("force")!="lengquan-shengong" )
		return notify_fail("你激发的内功非寒冰真气或冷泉神功，无法施展「九曲剑」！\n");
	if( me->query_skill("hanbing-zhenqi")<450)
		if( me->query_skill("lengquan-shengong")<450)
		return notify_fail("你的寒冰真气或冷泉神功修为不够，无法施展「九曲剑」！\n");
	if( userp(me)&&!me->query("quest/ss/ssj/jiuqu/pass"))
		return notify_fail("你没有得到钟镇师傅的传授，无法施展「九曲剑」！\n");

	if( me->query_skill("songshan-jian", 1) < 450 )
		return notify_fail("你的剑法程度还不能使用「九曲剑」！\n");

	if( me->query_skill("force", 1) < 450 )
		return notify_fail("你的基本内功修为还不够！\n");

	if( me->query("neili") < 1500 )
		return notify_fail("你的内力不够使用「九曲剑」！\n");

	if( me->query("jingli") < 1000 )
		return notify_fail("你的精力不够使用「九曲剑」！\n");

 	if (!weapon
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("sword") != "songshan-jian"
	 || me->query_skill_mapped("parry") != "songshan-jian" )
		return notify_fail("你激发必须使用嵩山剑法！\n");
	
	if( me->query_temp("ssj/jiuqu"))
		return notify_fail("你正在使用「九曲剑」！\n");

	message_vision(CYN"\n$N剑招互变，脚步轻移间瞬间向$n刺出九剑，每一剑都出招即回，迅捷无比，变化莫测，正是「"HIG"九曲剑"CYN"」的剑法变化！\n" NOR, me,target);
	message_vision(CYN"\n$N龙行虎步，虎视眈眈，这招九曲剑灵动异常，蓄势无穷，去回之际宛如毒蛇！\n" NOR, me);

  

        
	me->set_temp("ssj/jiuqu",1);

	//带来busy
	if (random(me->query_skill("songshan-jian",1))>target->query_skill("parry",1)/2
		||random(me->query("combat_exp"))>target->query("combat_exp")/2)
	{
		message_vision(HIC"\n$N经验极为丰富，招式变化极快，$n见这招变化如此迅捷，始料不及，顿时一阵手忙脚乱！\n" NOR, me,target);
		target->add_busy(1);
		if (!userp(target))
		{
			target->add_busy(3);
		}
	}
	//带来随机伤害
	if (random(me->query_skill("songshan-jian",1))>target->query_skill("parry",1)/2
		||random(me->query_int(1))>target->query_int(1)/2)
	{
		message_vision(HIR"\n$N见$n招式用老，猛然一剑从不可能的角度刺中$n！\n" NOR, me,target);
		damage=skill+me->query_skill("force",1);
		damage=damage*me->query_str(1)/10;
		damage=damage+random(damage);
		target->receive_damage("qi",damage,me);
		target->receive_wound("qi",damage/3,me);
		p = target->query("qi")*100/(target->query("max_qi")+target->query_temp("apply/qi"));
		msg = COMBAT_D->damage_msg(damage, "刺伤");
		msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		
		msg = replace_string( msg, "$w", weapon->query("name"));
		msg = replace_string( msg, "$l", target->query("limbs")[random(sizeof(target->query("limbs")))]);
		message_vision(msg,me,target);
	}
	if (objectp(me)&&objectp(target))
		call_out("attack_jiuqu",2+random(3),me,target);
	else {
		me->delete_temp("ssj/jiuqu");
		me->start_temp(2,"九曲剑");
	}
 
	me->add("neili", -300);
	me->add("jingli", -150);
	return 1;
}

int remove_jiuqu(object me,object target)
{
	int i,j,skill;
	
	if (!me||!me->is_fighting()) return 0;
	if (!target)
	{
		me->delete_temp("ssj/jiuqu");
		me->start_temp(2,"九曲剑");
		return 1;
	}
	skill=me->query_skill("songshan-jian",1);
	j=me->query_skill("songshan-jian",1)/150;
	if (random(me->query("combat_exp")>target->query("combat_exp")/2)
		||!userp(target))
	{

		message_vision(HIY"$N将「九曲剑」蓄积的无穷剑意瞬间释放，唰唰连续数剑刺向$n周身，仿佛九曲黄河天上水，磅礴而至！\n"NOR,me);
		me->add_temp("apply/sword",skill/4);
		me->add_temp("apply/attack",skill/4);
		for (i=0;i<j;i++ )
		{
			
			if (me->is_fighting()&&objectp(target))
			{
				COMBAT_D->do_attack(me, target,me->query_temp("weapon"),userp(me)?3:1);

			}
		}
		me->add_temp("apply/sword",-skill/4);
		me->add_temp("apply/attack",-skill/4);
				
	}	
	me->delete_temp("ssj/jiuqu");
	me->start_perform(3+random(2), "「九曲剑」");

	return 1;
}



string perform_name(){ return HIG"九曲剑"NOR; }

int help(object me)
{
        write(HIW"\n嵩山剑法之「九曲剑」："NOR"\n\n");
        write(@HELP
	嵩山剑法有“内八路，外九路”之称，总共十七路长短快慢的剑法
	应有尽有。当年五岳剑派与魔教十长老两度会战华山，五岳剑派
	的好手死伤殆尽，五派剑法的许多惊世绝招随五派高手而消逝。
	嵩山派掌门左冷禅会集本派残存的耆老，将各人所记得的剑招不
	论粗精，尽数录了下来，汇成一部剑谱。
	「九曲剑」是嵩山十三太保之一钟镇绝技，钟镇的武技和嵩山剑
	厚重浑朴的招式向左，走其轻灵路线，一剑九招，蓄势无穷，灵
	动异常，宛如毒蛇伺服一侧，一旦对手疏忽，一剑穿心，端的是
	狠毒。此招需要向钟镇请教。

	指令；perform sword.jiuqu
	
要求：
	当前内力需求 1500 以上；
	当前精力需求 1000 以上；
	嵩山剑法等级 450 以上；
	基本内功等级 450 以上；
	大嵩阳手等级 450 以上；
	激发剑法为嵩山剑法；
	激发招架为嵩山剑法；
	激发内功为冷系功法；	
	且手持剑类兵器。	

HELP
        );
        return 1;
}
