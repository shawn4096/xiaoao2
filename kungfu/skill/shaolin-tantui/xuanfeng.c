// xuanfeng.c 旋风腿
// by sohu@xojh
//腿法线路图
#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
int perform(object me, object target)
{

	int i,damage,p,skill;
	string msg;
	if( !target ) target = offensive_target(me);

     if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
		return notify_fail("「旋风腿」只能在战斗中对对手使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("使用「旋风腿」时双手必须空着！\n");

	if( (int)me->query_skill("shaolin-tantui", 1) < 300 )
		return notify_fail("你的旋风腿腿不够娴熟，不会使用「旋风腿」。\n");
	if( (int)me->query_skill("leg", 1) < 300 )
		return notify_fail("你的基本腿法腿不够娴熟，不会使用「旋风腿」。\n");
	if( (int)me->query_skill("yijin-jing", 1) < 300 )
		if( (int)me->query_skill("hunyuan-yiqi", 1) < 300 )
		return notify_fail("你的易筋经或混元一气等级不够，不能使用「旋风腿」。\n");

	if (me->query_skill_mapped("force") != "yijin-jing")
		if (me->query_skill_mapped("force") != "hunyuan-yiqi")
		return notify_fail("你目前的内功无法支持你使用「旋风腿」进行攻击。\n");  
	
	if (me->query_skill("leg",1)<100)
		return notify_fail("你目前的基本腿法不足100，不支持你使用「旋风腿」进行攻击。\n");  
		
	if( (int)me->query_dex() < 50 )
		return notify_fail("你的身法不够50，不能使用「旋风腿」。\n");

	if (me->query_skill_prepared("leg") != "shaolin-tantui"
	|| me->query_skill_mapped("leg") != "shaolin-tantui")
		return notify_fail("你现在无法使用「旋风腿」进行攻击。\n");  
											       
	if( (int)me->query("max_neili") < 5000 )
		return notify_fail("你现在最大内力太弱，不能使用「旋风腿」。\n");
	if( (int)me->query("neili") < 800 )
		return notify_fail("你目前内力太少，不能使用「旋风腿」。\n");

	if( (int)me->query("jingli") < 500 )
		return notify_fail("你现在精力太少，不能使用「旋风腿」。\n");


	message_vision(HIW"\n$N双脚呈丁字步站定，大喝一声，以左脚为原点，施展"HIG"「旋风腿」"HIW"的招式向$n方向连续出腿，迅捷无比，宛如狂风暴雨！\n" NOR,me, target);
	
	skill=me->query_skill("shaolin-tantui",1);

	if(random(me->query_dex()) > target->query_dex()/2
	  ||random(me->query_skill("leg",1))>target->query_skill("dodge",1)/2)
	{
		   message_vision(HIR"\n$n一时不查，左侧连续被$N的「旋风腿」招式踢中，不由地一阵气血翻腾！\n\n"NOR,me,target);            

           damage = me->query_skill("leg",1)+me->query_skill("shaolin-tantui",1)+me->query_skill("dodge",1);
		   damage=damage*me->query_dex()/5;
           damage =3*damage;
		   damage += random(damage);
           
           
		   if (wizardp(me))
           {
			   message_vision("damage="+damage+"\n",me);
           }
		   
		   if (damage>3500) damage=3500+random(100);
		   if (userp(target)&& damage > 2500) damage = 2500;

	      
           
		   target->receive_damage("qi", damage, me);
		   target->apply_condition("neishang",3+random(2));
           target->receive_wound("qi", damage/4, me);
           
           
		 //  limbs = target->query("limbs");
           p = (int)target->query("qi")*100/(int)target->query("max_qi");
           tell_room(environment(target), HIR + target->name()+"忽感全身像被压了一块大石一样，一阵一阵眩晕憋气！\n" NOR, ({ target }));  
           msg = damage_msg(damage, "内伤");
            msg += "( $n"+eff_status_msg(p)+" )\n";
          
		   message_vision(msg, me, target);
           
		   if(userp(me) && me->query("env/damage"))
	          tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ damage+ WHT"点攻击伤害。\n"NOR);
           
			if(userp(target)&& target->query("env/damage"))
	         tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ damage+ WHT"点伤害。\n"NOR);
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
	}
		

		message_vision(HIC "\n$N这一腿踢完，空中借势回旋，急速旋转，右腿又旋即而至。\n" NOR,me);
		if (objectp(me)&&objectp(target))
			call_out("remove_xuanfeng",1,me,skill/50);
		
		me->add_temp("apply/leg",skill/4);
		me->set_temp("sltt/xuanfeng", skill);
		me->add("neili", -280);
		me->add("jingli", -180);


		return 1;
}



int remove_xuanfeng(object me,int count)
{
	int skill;
	object target;
	if (!me) return 0;
	skill=me->query_temp("sltt/xuanfeng");
	target = offensive_target(me);
	if (!objectp(target)
		||!me->is_fighting()
		||me->is_busy()
		||count<0)
	{
		me->add_temp("leg",-skill/4);
		me->delete_temp("sltt/xuanfeng");
		message_vision(HIC "\n$N双脚站定，气定神闲，徐徐突出一口浊气，散掉旋风腿功力。\n" NOR,me);
		return 1;
	}
	if (objectp(me)&&me->is_fighting())
	{
		me->add_temp("apply/attack",skill/4);
		me->add_temp("apply/damage",skill/5);
		
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(3)?3:1);
		me->add_temp("apply/attack",-skill/4);
		me->add_temp("apply/damage",-skill/5);
	}
	call_out("remove_xuanfeng",1,me,count--);
}
string perform_name(){ return HIG"旋风腿"NOR; }
int help(object me)
{
        write(HIC"\n少林弹腿之「旋风腿」绝技："NOR"\n");
        write(@HELP
	少林弹腿为少林入门腿法，利用坚实的腿功和强大的内力，身
	子纵起空中，趁对方不备向对方踢出一脚绝命杀招，令对手防
	不胜防，躲无可躲，端的是厉害非常。
	旋风腿是以一腿为中心，连续旋转，为近身对战中的远程袭击
	武技。一旦施展，循环出招，不死不求。此招极为损耗体力，
	玩家当慎用。

	指令：perform leg.xuanfeng

要求：  
	最大内力需求 5000 以上；      
	当前内力需求 800  以上
	当前精力需求 500  以上；  
	少林弹退等级 300 以上；
	易筋经功等级 300 以上；
	基本腿法等级 300 以上；	
	激发腿法为少林弹腿；
	激发招架为少林弹腿；
	且手无兵器；
	有效身法不得小于50。
                
HELP
        );
        return 1;
}
