// jindao-heijian 刀剑齐挥
/*
    公孙谷主大喜，当当当，挥剑砍了三刀，左手刀却同时使了“定阳针”、“虚式分
金”、“荆轲刺秦”、“九品莲台”四招。这四手剑招飘逸流转，四剑夹在三刀之中。杨过
尚能勉力抵御，小龙女却意乱心慌，想挥剑去削他刀锋，但金刀势如飞凤，劈削不到。杨过
情知不妙，拚着自身受伤，使一招全真剑法中的“马蹴落花”，平膀出剑，剑锋上指，将对
*/
#include <ansi.h>
string perform_name(){ return HBBLU"刀剑齐挥"NOR; }

inherit F_DBASE;
inherit F_SSERVER;
void attack_ob(object me, object target,object weapon,object weapon2);
int perform(object me, object target)
{
		int i;
		object *inv;
		object weapon2;
        object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);

        if( !target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("刀剑齐挥只能对战斗中的对手使用。\n");
		if (!me->query_temp("jdhj/nizhuan"))
		{
			return notify_fail("金刀黑剑全凭一口气，你需运转金刀黑剑的逆转起手式。\n");
		}

        if( me->query_dex() < 70 )
                return notify_fail("你在身法上先天禀赋不足，不能使用刀剑齐挥！\n");
        
        if( me->query_skill("dodge",1) < 500 )
                return notify_fail("刀剑齐挥需要超绝的轻功配合，方能有效施展！\n");

        if( me->query_skill("sword",1) < 500 )
                return notify_fail("你剑法未到炉火纯青之境，还不会使用刀剑齐挥！\n");
        if( me->query_skill("blade",1) < 500 )
                return notify_fail("你刀法未到炉火纯青之境，还不会使用刀剑齐挥！\n");
        if( me->query_skill("jindao-heijian",1) < 500 )
                return notify_fail("你金刀黑剑未到炉火纯青之境，还不会使用剑圈封闭对方！\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("你的内力不够使用刀剑齐挥！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力不够使用刀剑齐挥！\n");

        if (!weapon)
                return notify_fail("你手中无剑怎能使用刀剑齐挥？！\n");
       // if (me->query_temp("jdhj/luanren",1))
         //       return notify_fail("你正在使用阴阳倒乱刃法无法再刀剑齐挥！\n");

        if ( me->query_skill_mapped("sword") != "jindao-heijian"
          || me->query_skill_mapped("parry") != "jindao-heijian"
          || me->query_skill_mapped("blade") != "jindao-heijian"
          && userp(me))
             	return notify_fail("你必须先将黑剑金刀相互配合。\n");
       inv = all_inventory(me);
       for(i=0; i<sizeof(inv); i++) {
           if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
		if (weapon->query("skill_type") == "blade") {
        	   if( inv[i]->query("skill_type") == "sword" ) 
		   {
			   weapon2 = inv[i];
			   i = 3;
			   break;
		   }
		}
		if (weapon->query("skill_type") == "sword") {
   	        if( inv[i]->query("skill_type") == "blade" ) 
		   {
			   weapon2 = inv[i];
			   i = 2;
			   break;
		   }
		}
       }
		if (!objectp(weapon2)) return notify_fail("你只有一种兵器就想刀剑齐挥？\n");
			
			
		message_vision(HBCYN+HIW"$N大喝一声，刀剑齐挥，立时武功招式奇幻无方，刀沉力猛，大开大合，剑势绵密，滴水不漏！\n"NOR, me, target);
		me->add_temp("apply/attack", me->query_skill("jindao-heijian",1)/8);
		me->add_temp("apply/damage", me->query_skill("jindao-heijian",1)/8);

		if (weapon->query("skill_type")=="blade") {
			weapon->unequip();
			weapon2->wield();
			if (objectp(target)&&me->is_fighting())
				COMBAT_D->do_attack(me, target, weapon2,1);
			if (objectp(target)&&me->is_fighting())
				COMBAT_D->do_attack(me, target, weapon2,1);
			if (objectp(target)&&me->is_fighting())
				COMBAT_D->do_attack(me, target, weapon2,3);
			weapon2->unequip();
			weapon->wield();
		} else if (weapon->query("skill_type")=="sword") {
			if (objectp(target)&&me->is_fighting())
				COMBAT_D->do_attack(me, target, weapon2,1);
			if (objectp(target)&&me->is_fighting())
				COMBAT_D->do_attack(me, target, weapon2,1);
			if (objectp(target)&&me->is_fighting())
				COMBAT_D->do_attack(me, target, weapon2,3);
		}
        me->add_temp("apply/attack", -me->query_skill("jindao-heijian",1)/8);
		me->add_temp("apply/damage", -me->query_skill("jindao-heijian",1)/8);

        me->add("neili", -1500);
        me->add("jingli", -500);
	//解开裘千尺谜题后刀剑齐辉威力大增
	if (me->query("quest/tz/jdhj/daojian/pass")&&objectp(target))
		call_out("attack_ob",1,me,target,weapon,weapon2);
	me->start_perform(6,"刀剑齐挥");
    return 1;
}
void attack_ob(object me, object target,object weapon,object weapon2)
{
	int i;
	if (!me) return ;
	if (!weapon2||!weapon || !target || !living(me) || !me->is_fighting(target)) {
		return ;
	}
	message_vision(HIR"\n紧接着$N毫不停留左手刀同时使了“定阳针”、“虚式分金”、“荆轲刺秦”、“九品莲台”四招。\n"+
"这四手剑招飘逸流转，四剑夹在三刀之中。\n"+"$n勉力抵御，想挥剑去削他刀锋，但"+
weapon->name()+weapon2->name()+HIR"势如飞凤，劈削不到。\n"NOR,me,target);
    
	me->add_temp("apply/attack", me->query_skill("jindao-heijian",1)/8);
	me->add_temp("apply/damage", me->query_skill("jindao-heijian",1)/8);

	if (weapon->query("skill_type")=="blade") {
		COMBAT_D->do_attack(me, target, weapon,3);
		COMBAT_D->do_attack(me, target, weapon,3);
		COMBAT_D->do_attack(me, target, weapon,3);
		COMBAT_D->do_attack(me, target, weapon,3);
	} else if (weapon->query("skill_type")=="sword") {
		weapon->unequip();
		weapon2->wield();
		COMBAT_D->do_attack(me, target, weapon2,3);
		COMBAT_D->do_attack(me, target, weapon2,3);
		COMBAT_D->do_attack(me, target, weapon2,3);
		COMBAT_D->do_attack(me, target, weapon2,3);
		weapon2->unequip();
		weapon->wield();
	}
    me->add_temp("apply/attack", -me->query_skill("jindao-heijian",1)/8);
	me->add_temp("apply/damage", -me->query_skill("jindao-heijian",1)/8);

	return;
}


int help(object me)
{
        write(HIC"\n金刀黑剑"+HBBLU"「刀剑齐挥」"NOR"\n");
        write(@HELP
	金刀黑剑是情人谷公孙芷的家传武功，左手金刀右手黑剑
	金刀以劈砍切削之攻击，黑剑乃刺扎削之效果，金刀以刚
	性为主，黑剑以阴性为主，两者组合后会令人防不胜防。
	尤其是铁掌裘千尺嫁给公孙芷后，对这门武功去腐存精加
	以完善。更达到炉火纯青之境。但此门武技的缺点也是显
	然，正如裘千尺所言“难练易破”，存在致命缺点。
	铁掌弟子可以凭借身份解救裘千尺并获得裘千尺的指点，
	则此门功夫将更上层楼。
	三刀四剑一起发出，招式凌厉，剑中夹杂刀势，刀中隐藏
	剑法招式，端的是极为狠辣的招式。
		
	指令：perform sword(blade).daojian

要求：
	当前内力要求 1000 以上；
	当前精力要求 1000 以上；
	金刀黑剑等级 500 以上；
	基本轻功等级 500 以上；
	基本剑法等级 500 以上；
	基本刀法等级 500 以上；	
	后天身法等级 70 以上；	
	激发刀法为金刀黑剑。
	激发剑法为金刀黑剑。
	激发招架为金刀黑剑。
	激发内功不限；
	手持刀(剑)类武器并身上带对应配套武器。

HELP
        );
        return 1;
}
