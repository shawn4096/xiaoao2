// jindao-heijian 剑圈封闭对手
/*
    他见杨过提索出战，当即叫道：“看剑！”黑剑颤动，当胸刺去，可是剑尖并非直进，
却是在他身前乱转圈子。杨过不知这黑剑要刺向何方，大惊之下，急向后跃。
    公孙谷主出手快极，杨过后跃退避，黑剑划成的圆圈又已指向他身前，剑圈越划越大，
初时还只绕着他前胸转圈，数招一过，已连他小腹也包在剑圈之中，再使数招，剑圈渐渐扩
及他的头颈。杨过自颈至腹，所有要害已尽在他剑尖笼罩之下。金轮法王、尹克西、潇湘子
等生平从未见过这般划圈逼敌的剑法，无不大为骇异。
*/
#include <ansi.h>
inherit F_DBASE;
inherit F_SSERVER;
#include <combat_msg.h>
void remove_jianquan(object me);

int perform(object me, object target)
{
		int i,skill;
 		object *inv;
		object weapon,weapon2;
		string msg;
		weapon = me->query_temp("weapon");  
			
		skill=me->query_skill("jindao-heijian",1);
        
		if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("剑圈封闭对方只能对战斗中的对手使用。\n");
		if (!me->query_temp("jdhj/nizhuan"))
		{
			return notify_fail("金刀黑剑全凭一口气，你需运转金刀黑剑的逆转起手式。\n");
		}

        if( me->query_dex() < 60 )
                return notify_fail("你在身法上先天禀赋不足，不能使用剑圈封闭对方！\n");
        
        if( me->query_skill("dodge",1) < 400 )
                return notify_fail("剑圈封闭对方需要超绝的轻功配合，方能有效施展！\n");

        if( me->query_skill("sword",1) < 400 )
                return notify_fail("你剑法未到炉火纯青之境，还不会使用剑圈封闭对方！\n");
        if( me->query_skill("jindao-heijian",1) < 450 )
                return notify_fail("你金刀黑剑未到炉火纯青之境，还不会使用剑圈封闭对方！\n");

		if( me->query_skill("blade",1) < 400 )
                return notify_fail("你刀法未到炉火纯青之境，还不会使用剑圈封闭对方！\n");

       if( me->query("neili") <= 1000 )
                return notify_fail("你的内力不够使用剑圈封闭对方！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力不够使用剑圈封闭对方！\n");

        if (!weapon)
                return notify_fail("你手中无剑怎能使用剑圈封闭对方？！\n");
        if (target->is_busy())
                return notify_fail("对方正自顾不暇你可以放胆进攻！\n");
        //和倒乱刃冲突
	//	if (me->query_temp("jdhj/daoluanren"))
               // return notify_fail("你正在使用阴阳倒乱刃法无法再用剑圈封闭对方！\n");

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
	if (!objectp(weapon2)) return notify_fail("你只有一种兵器就想剑圈封闭对方？\n");
 	if (i>2) weapon=weapon2; 
		
		message_vision(HIM"$N叫道：“看剑！”"+weapon->name()+HIM"颤动，当胸刺去，可是剑尖并非直进，却是在$n身前乱转圈子。\n\n"+
		HIW"$n不知这"+weapon->name()+HIW"要刺向何方，大惊之下，急向后跃。\n"+
		HIM"$N出手快极，$n后跃退避，"+weapon->name()+HIM"划成的圆圈又已指向$n身前，剑圈越划越大，\n"+
		"初时还只绕着$n前胸转圈，数招一过，已连$n小腹也包在剑圈之中，再使数招，剑圈渐渐扩及$n的头颈。\n"+
		HIR"$n自颈至腹，所有要害已尽在他剑尖笼罩之下。\n"NOR,me,target);

	//提高命中
	/*
	if(random(me->query_skill("sword",1)> target->query_skill("parry",1)/2
		||random( me->query_skill("force",1)) >target->query_skill("force",1))/2)
	    ||target->is_busy())
	{
		damage = me->query_skill("jindao-heijian",1);
		damage += me->query_skill("sword",1);
		damage += random(damage);
		target->add_busy(damage/300);
    	target->add_temp("lost_attack", damage/100);
        target->apply_condition("no_perform", damage/1000);
        target->apply_condition("no_exert", damage/1000);
		target->add("neili",-(500+random(150)));
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		msg = damage_msg(damage, "割伤");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "小腹");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-300);
		me->add("jingli",-100);
	} else {
		damage=600;
		me->add_busy(1);
	}*/
        me->add("neili", -500);
        me->add("jingli", -500);
		//me->start_perform(damage/300,"剑圈封闭对方");
		me->set_temp("jdhj/jianquan",1);
		call_out("remove_jianquan",skill/60,me);
        return 1;
}

void remove_jianquan(object me)
{
	if (!me) return;
	me->delete_temp("jdhj/jianquan");
	message_vision(HIM"$N缓缓收功，将蓄积的剑圈逐渐收拢！\n"NOR,me);
	return;
}
string perform_name(){ return HBYEL+HIW"剑圈"NOR; }

int help(object me)
{
        write(HIC"\n金刀黑剑"+HBYEL"「剑圈」"NOR"\n");
        write(@HELP
	金刀黑剑是情人谷公孙芷的家传武功，左手金刀右手黑剑
	金刀以劈砍切削之攻击，黑剑乃刺扎削之效果，金刀以刚
	性为主，黑剑以阴性为主，两者组合后会令人防不胜防。
	尤其是铁掌裘千尺嫁给公孙芷后，对这门武功去腐存精加
	以完善。更达到炉火纯青之境。但此门武技的缺点也是显
	然，正如裘千尺所言“难练易破”，存在致命缺点。
	铁掌弟子可以凭借身份解救裘千尺并获得裘千尺的指点，
	则此门功夫将更上层楼。
	剑圈是将剑的柔性发挥极致，形成一个剑圈，将对方圈在
	内，让对方躲无所躲，然后一刀毙命。一旦施展此招，金
	刀黑剑的攻击力将极为犀利。
		
	指令：perform sword(blade).jianquan

要求：
	当前内力要求 1000 以上；
	当前精力要求 1000 以上；
	金刀黑剑等级 400 以上；
	基本轻功等级 400 以上；
	基本剑法等级 400 以上；
	基本刀法等级 400 以上；	
	后天身法等级 60 以上；	
	激发刀法为金刀黑剑。
	激发剑法为金刀黑剑。
	激发招架为金刀黑剑。
	激发内功不限；
	手持刀(剑)类武器并身上带对应配套武器。

HELP
        );
        return 1;
}

