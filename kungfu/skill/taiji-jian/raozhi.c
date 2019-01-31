// 2005.7.4 by Lane@SJ

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string *xue_name = ({ 
"劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
"幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
"涌泉穴","大锥穴","风府穴",
}); 
int perform(object me, object target)
{
	string msg, dodge_skill;
	object weapon;
	int ap, dp,i,skill;
    
	if( !target ) target = offensive_target(me);

	if( !me->query("raozhi") )
		return notify_fail("你未得传授「绕指柔剑」。\n");

	if( !objectp(target)
	|| !target->is_character()
	|| !me->is_fighting(target)
	|| !living(target) )
		return notify_fail("「绕指柔剑」只能对战斗中的对手使用。\n");

	//if( me->query_temp("tjj/lian") )
		//return notify_fail("你正在使用「连」字诀。\n");

	//if( me->query_temp("tjj/chan") )
		//return notify_fail("你正在使用「缠」字诀。\n");

	if( (int)me->query_skill("taiji-jian", 1) < 200 )
		return notify_fail("你的太极剑法功力太浅了。\n");

	if( (int)me->query_skill("sword", 1) < 200 )
		return notify_fail("你的基本剑法功力太浅了。\n");

	if( (int)me->query_skill("yinyun-ziqi", 1) < 200 )
		return notify_fail("你的内功功力太浅了。\n");

	if( (int)me->query("max_neili") < 3000 )
		return notify_fail("你的内力太浅了。\n");

	if( (int)me->query("neili") < 1000 )
		return notify_fail("你的真气不够。\n");

	if( me->query_skill_mapped("force") != "yinyun-ziqi" )
		return notify_fail("你用什么为内功基础来使「绕指柔剑」？\n");
	if( me->query_temp("tjj/raozhi") )
		return notify_fail("你正在使用「绕指柔剑」\n");
	if( target->query_temp("tjj/raozhi") )
		return notify_fail("对方已经为你「绕指柔剑」所制。\n");
	if( !objectp(weapon = me->query_temp("weapon"))
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("sword") != "taiji-jian"
	 || me->query_skill_mapped("parry") != "taiji-jian" )
		return notify_fail("你使得了「绕指柔剑」么?\n");
	
	//if( target->is_busy() )
		//return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");
	//For npc Chan+Raozhi 流氓至极
      
	ap = me->query("combat_exp")/100000;
	dp = target->query("combat_exp")/100000;
	//550级后增加命中
	if( me->query_skill("taiji-jian", 1) > 549 )
	{
		ap += random(ap/2);
       // me->set_temp("apply/armor",me->query("yinyun-ziqi",1)/3);
	}	      

	message_vision(HIY"\n$N施展出太极剑法中的绕指柔剑，手中"+weapon->query("name")+HIY"竟似了一条软蛇，弯曲自如，攻势奇诡！\n"NOR,me,target);
	
	skill=(int)me->query_skill("taiji-jian",1);
	
	if (me->query("quest/wd/yyzq/taiji/pass"))
	{
		skill=skill+me->query_skill("yinyun-ziqi",1)/2;
	}
	
	if ( random( ap + dp ) > dp 
		||random(me->query_dex())>target->query_dex()/2) {
		message_vision(HIC"\n$n不由感到害怕，只感觉前后左右都似有$N攻来，一下子不知道如何是好！\n"NOR,me,target);		
		
		if (userp(target)) target->add_busy(2);
		else target->add_busy(5);
		
		if( target->query_temp("lost_attack") < 1 )
			target->add_temp("lost_attack", 1+random(3));
		me->add("neili", -300);
		me->add("jingli", -100);
		//降低对方防御
		me->set_temp("tjj/raozhi",skill);

		target->add_temp("apply/dodge",-skill/4);
		target->add_temp("apply/attack",-skill/4);
		target->add_temp("apply/parry",-skill/4);
		
		target->set_temp("tjj/raozhi",skill);
		call_out("rz_back",skill/40,target);

	//350后增加防御
		if( me->query_skill("taiji-jian", 1) > 349 )
                me->add_temp("apply/parry",me->query("yinyun-ziqi",1)/3);
	//450后增加轻功
		if( me->query_skill("taiji-jian", 1) > 449 )
                me->add_temp("apply/dodge",me->query("yinyun-ziqi",1)/3);
	//550 后增加命中

		
		//if (objectp(target) && me->is_fighting())
		call_out("raozhi_effect",1,me,target,(int)skill/20);

		if (me->query_skill("taiji-jian",1)< 550)
				me->start_perform(2, "「绕指柔剑」");
	}
	else {
		//dodge_skill = target->query_skill_mapped("dodge");
		//if( !dodge_skill ) dodge_skill = "dodge";
		//msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
		message_vision(HIC"$n轻轻一纵，躲了开去，$N一招失手，顿时有些忙乱。\n"NOR, me, target);
		me->add("neili", -100);
		me->add("jingli", -50);
		me->start_busy(1);
		me->start_perform(2+random(2), "「绕指柔剑」");
	}	
	return 1;
}
int rz_back(object target)
{
	int skill;
	if (!target) return 0;
	if (target->query_temp("tjj/raozhi"))
	{
		skill=target->query_temp("tjj/raozhi");
		tell_object(target, HIW"你逐渐恢复了身中「绕指柔剑」所带来的虚弱状态。\n"NOR);
				//tell_object(me,WHT+target->query("name")+WHT"逐渐恢复了身中你所施展「绕指柔剑」所带来的负面状态。\n"NOR);
		target->add_temp("apply/attack", skill/4);
		target->add_temp("apply/dodge", skill/4);
		target->add_temp("apply/parry", skill/4);
		target->delete_temp("tjj/raozhi");
		return 1;
		
	}

}

int raozhi_effect(object me,object target,int count)
{

        object weapon;
		int skill;
		string xname;
	    
		//name=xue_name[random(sizeof(xue_name))];
		xname = xue_name[random(sizeof(xue_name))];
		//攻击方死亡，被攻击方存活
		//1、如果攻击方死了，被攻击方活了，恢复被攻击方的负面效果,不管攻击方属性
	
	//if (!objectp(target)) return 0;
		//不激发太极剑或不用剑退出			
		if (!me) return 1;
		
		weapon=me->query_temp("weapon");

		if (!objectp(target)
			|| !me->is_fighting()
			|| me->query_skill_mapped("sword")!="taiji-jian"
			|| me->query_skill_mapped("parry")!="taiji-jian"
			|| !weapon
			|| !me->query_temp("tjj/raozhi")
			|| count-- < 0
			|| weapon->query("skill_type")!="sword")
		{				
			//350级后增加防御
			if( me->query_skill("taiji-jian", 1) > 349 )
                me->add_temp("apply/parry",-me->query("yinyun-ziqi",1)/3);
			//450后增加轻功
			if( me->query_skill("taiji-jian", 1) > 449 )
                me->add_temp("apply/dodge",-me->query("yinyun-ziqi",1)/3);
			
			me->delete_temp("tjj/raozhi");
			if (objectp(weapon))
				message_vision(HIY"$N将手中的"+weapon->query("name")+HIY"舞个剑花，随后插入剑鞘之中，绕指柔剑缓缓收功。\n"NOR,me);	
			else message_vision(HIY"$N将蓄积内力缓缓释放，绕指柔剑缓缓收功。\n"NOR,me);	
			return 1;
		}
		//绕指剑额外攻击 
        //绕指带来的辅助攻击
		if (!random(3))
		{	
				switch (random(3))
				{
					case 0:
						if (objectp(target) && target->query_temp("tjj/raozhi"))
						{	
							message_vision(HIY"$N将深厚的功力融入到剑法中，绕指柔剑越来越诡异难测，$n一不小心为$N所刺中"+HIR+xname+HIY"!\n"NOR,me,target);
							target->receive_damage("qi",100+random(1000),me);
						}
						break;
					case 1:
						if (objectp(target) && target->query_temp("tjj/raozhi"))
						{
							message_vision(RED"$N手中剑光抖动，绕指柔剑意迸发，见$n疏忽，剑光弯曲如弓，剑尖竟瞬间刺中$n的"+HIG+xname+RED"!\n"NOR,me,target);
							target->receive_damage("jingli",100+random(500),me);
							target->apply_condition("neishang",1);
						}
						break;
					case 2:
						if (objectp(target) && target->query_temp("tjj/raozhi"))
						{
							message_vision(MAG"$N氤氲紫气运转不休，剑光诡异，宛如一条灵蛇般的刺中了$n的臂膀，顺接以剑柄戳中$n的"+HIR+xname+MAG"!\n"NOR,me,target);
							target->receive_wound("qi",100+random(500),me);
							target->apply_condition("no_exert",1);
						}
						break;
				}							
                 target->add_busy(1);						
			}
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);                        
			if (objectp(target)&&me->is_fighting())
				call_out("raozhi_effect", 2, me, target, count);  
			else call_out("remove_effect",1,me);
            
			return 1;
	  
}

int remove_effect(object me)
{
	

	object weapon;
	if (!me) return 0;
	weapon=me->query_temp("weapon");
	if( me->query_skill("taiji-jian", 1) > 349 )
                me->add_temp("apply/parry",me->query("yinyun-ziqi",1)/3);
	//450后增加轻功
    if( me->query_skill("taiji-jian", 1) > 449 )
                me->add_temp("apply/dodge",me->query("yinyun-ziqi",1)/3);
	//550 后增加命中
	me->delete_temp("tjj/raozhi");
	message_vision(HIY"$N将手中的"+weapon->query("name")+HIY"插入剑鞘中，绕指柔剑缓缓收功。\n"NOR,me);	
    
	
	return 1;

}

string perform_name(){ return MAG"绕指柔剑"NOR; }

int help(object me)
{
        write(MAG"\n太极剑法之「绕指柔剑」："NOR"\n\n");
        write(@HELP
	绕指柔剑是武当七侠中莫声谷所创，诀窍是将深厚内功
	融入到剑中，逼使剑变形，从而造成对方的误判，达到
	有效杀伤对方的目的。该武功需要向莫声谷请教。
	
	perform sword.raozhi

要求：  
	当前内力要求 1000 以上;
	最大内力要求 3000 以上；
	太极剑法等级 200 以上；
	氤氲紫气等级 200 以上；
	基本剑法等级 200 以上；
	激发剑法为太极剑法；
	激发招架为太极剑法；
	激发内功为氤氲紫气；
	需得到传授「绕指柔剑」。

HELP
        );
        return 1;
}
