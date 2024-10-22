// hanbing-zhenqi.c 寒冰真气
// Created by Numa 1999
// Modified by Numa 2000.1.5
// Modified by Numa 2000.1.25
// Modified by darken@SJ
// Lklv@SJ 2001.10.22 modified

#include <ansi.h>
inherit FORCE;
#include "/kungfu/skill/force.h"
#include <combat.h>

#include <combat_msg.h>
mixed hit_ob(object me, object ob, int damage);
int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
	int i = me->query_skill("hanbing-zhenqi", 1);

	if ((int)me->query_skill("force", 1) < 20)
		return notify_fail("你的基本内功火候还不够。\n");
	if ( i > me->query_skill("force", 1) + 10
	 && i >= 200 )
		return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");
        return 1;
}

void skill_improved(object me)
{
        int pl1,pl2;

        pl1 = me->query_skill("hanbing-zhenqi", 1);
        pl2 = me->query_skill("hanbing-shenzhang", 1);
        if (pl1>=220 && !me->query("ss/hbzq_220")){
                tell_object(me, HIW"\n忽然，你感觉体内寒气越聚越盛，全身似乎堕入冰窖，寒冷刺骨！\n"NOR);
                tell_object(me, HIW"\n过了一会，体内寒气逐渐聚在丹田处，全身精神为之一振，功力修为大大提升！\n"NOR);
                me->delete("ss/hb_improve");
                me->add("max_neili", pl1 + random(pl2));
                me->set("ss/hbzq_220", 1);
        }
}

int ob_hit(object ob, object me, int damage)
{
	int skill, ap, dp, p;
	object weapon;
	string msg;

	skill = me->query_skill("hanbing-zhenqi", 1);
	
	if ( damage < 100 ) return 0;
	if ( me->query_temp("fanzhen")) {
		me->delete_temp("fanzhen");
		return 0;
	}

	if ( skill < 220
	 || me->query("combat_exp") < ob->query("combat_exp")/2
	 || me->is_busy()
	 || ! me->query_temp("hbzq/huti")) return 0;

	weapon = ob->query_temp("weapon");

	if(objectp(weapon))
		msg = weapon->query("skill_type");
	else {
		mapping prepare = ob->query_skill_prepare();
		if (!sizeof(prepare)) msg = "unarmed";
		else msg = keys(prepare)[0];
	}

	ap = COMBAT_D->skill_power(ob, msg, SKILL_USAGE_ATTACK) / 1000;
	dp = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE) / 1000;

	if ( weapon && !me->query_temp("weapon")) ap *= 2;

	if ( me->query_temp("weapon"))
		dp = dp *2/3;

	if ( wizardp(me))
		tell_object(me, sprintf("ap = %d, dp = %d.\n", ap ,dp));

	if ( random(dp + ap) > ap && !random(3)) {
		msg = HIB"突然之间，$n身子一晃，一步步的慢慢退开，一言不发的瞪视着$N。\n"+
			"$n身子发颤，手足不动，便如是给人封了穴道一般，原来是被$N的护体寒冰真气所伤。\n"NOR;
		ob->receive_damage("jing", skill * 2, me);
		ob->receive_wound("jing", skill, me);
		//ob->add_condition("cold_poison",1);
		//新增冻
		
		msg += COMBAT_D->damage_msg(damage, "内伤");
		if ( random(2))
		{
			ob->add_condition("cold_poison", 2);
            ob->add_busy(1+random(3));
		}
		else
			ob->add_busy(1+random(2));
		me->add_temp("fanzhen", 1);
		p = ob->query("eff_jing")*100/ob->query("max_jing");
		msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		message_vision(msg, me, ob);
		return -damage/2;
	}
	return 0;
}

int practice_skill(object me)
{
	int i = me->query_skill("hanbing-zhenqi", 1);

	if (i >= 200){
		if (i < 220)
			return notify_fail("你的寒气过重，需要向左冷禅请教了。\n");
		if ((int)me->query("potential", 1) > 5
		 && (int)me->query("neili", 1) > 200){
			me->improve_skill("hanbing-zhenqi", (int)me->query_int());
			me->add("neili", -100);
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else
			return notify_fail("你现在的修为不足以提高寒冰真气了。\n");
	}
	return notify_fail("你现在的寒冰真气修为只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
       return __DIR__"hanbing-zhenqi/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIW + me->name()+"脸上寒气浮现，隐隐有微光流动" NOR,
		"start_my_msg" : "你手捏剑诀，将寒冰真气提起在体内慢慢转动。\n",
		"start_other_msg" : HIB + me->name()+"摆了个盘膝打坐的姿势，全身笼罩在一片寒气之内。\n"NOR,
		"halt_msg" : "$N双眼一睁，极速压下内息站了起来。\n",
		"end_my_msg" : "你将寒冰真气按周天之势搬运了一周，感觉精神充沛多了。\n"NOR,
		"end_other_msg" : HIW"只见"+me->name()+"缓缓睁开双眼站起，浑身散发出一股冰冷的寒气。\n"NOR,
		"heal_msg" : HIW"$N运起寒冰真气，开始缓缓运气疗伤。\n"NOR,
		"heal_finish_msg" : HIY"$N内息一停，却见伤势已经全好了。\n"NOR,
		"heal_unfinish_msg" : "$N眉头一皱，“哇”地吐出一口瘀血，看来这伤还没有全好。\n",
		"heal_halt_msg" : "$N急急把内息一压，也不顾身上的伤势立即站了起来。\n",
		]);
}


mixed hit_ob(object me, object ob, int damage)
{
	
	int busy,p;
	string msg;
    object weapon;
	weapon=me->query_temp("weapon");
	//没解开绝世威力发挥不出来
	if (!me->query("quest/ss/hbzq/pass")) return 0;
	//寒冰诀
	if( !me->query_temp("ss/hb")) return 0; 
	
	if( ob->is_busy() && !random(2) &&!me->query_temp("action_flag") )
	{
			message_vision(HBBLU+HIW"$N见$n处于忙乱之中，寒冰真气随心而起，周身竟然腾起一股薄薄的冰霜!\n"
			+"$n忍不住打了个冷颤，$N趁其失神的刹那，急忙疾攻数招。"NOR,me,ob);
	 		me->set_temp("action_flag",1);
	 		me->add_temp("apply/attack",me->query_skill("hanbing-zhenqi",1)/5);
	 		me->add_temp("apply/damage",me->query_skill("hanbing-zhenqi",1)/5);
	 	
	 		COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), userp(me)?3:1);
			if (me->is_fighting(ob))
				COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 3);
	 		me->add_temp("apply/attack",-me->query_skill("hanbing-zhenqi",1)/5);
	 		me->add_temp("apply/damage",-me->query_skill("hanbing-zhenqi",1)/5);
	 	
			me->delete_temp("action_flag");
	 		return;
	}
	else if( !ob->is_busy()
	       && me->query_str()*10/2+random(me->query_str()*10/2) > random(ob->query_con()*10) 
	       && random(me->query("neili"))>1000
	       && me->query("jingli")>1000
	       && !random(2))
	      // && me->query("hbzq/powerup")	     
	{
	        switch(random(2))
	        {
	          case 0:
		        if (weapon)
		            msg = HBWHT+HIB"$N运使寒冰真气，一股寒冷之极的劲力忽然从"+weapon->query("name")+HBWHT+HIB"的剑尖上窜出，点中$n的穴道。\n"NOR;
	   	        else msg = HBBLU+WHT"$N运使寒冰真气，一股寒冷之极的劲力随着掌力拍入$n的心脉。\n"NOR;
		        busy = me->query_str()-ob->query_con();
	 	        if(busy<=0) busy = 1+random(2);
	 	        if(busy>5) busy=5;
	 	        ob->add_busy(busy);
	 	        ob->add("neili", -busy*1000);
		        ob->apply_condition("no_exert",2);
                me->add("neili",busy*100); 
				ob->add_condition("cold_poison",1);
	 	        return msg;
		       break;
		       case 1:
                   msg = HBRED+HIW"$N寒气内聚，在强大内力激发下，寒冰真气宛如实质，化成数道若隐若现的冰锥射向$n的诸身大穴。\n"NOR;
	   	           busy = me->query_str()-ob->query_con();
	 	           if(busy<=0) busy = 1+random(2);
	 	           if(busy>5) busy=5;
	 	           ob->add_busy(busy);
	 	           ob->add("jingli", -busy*1000);
		           ob->apply_condition("no_perform",2);
                   me->add("neili",busy*100); 
				   ob->add_condition("cold_poison",1);
	 	          return msg;
		        break;
		     }
	   }else if(random(me->query("neili"))>9000
	         && me->query("jingli")>500
	         && me->query("jiali") >=200
	         && !me->query_temp("weapon")
	         && !random(2))
	   {
		
	 	msg =HBBLU+HIW"$N双手挥动间，寒气大起，$n一时避之不急，被$N在胸口重重击了一掌。\n"NOR;
	 	damage = (me->query_str()*10+me->query_skill("force")-ob->query_skill("parry",1))*5;
	 	if(damage<=0) damage = 1;
	 	if(damage>4000) damage = 4000;
		if (userp(me)&&!userp(ob))
		   damage =damage*2;	 	
	 	ob->receive_wound("qi", damage - ob->query_temp("apply/armor"), me);
		ob->add_condition("cold_poison",1);
		p=(int)ob->query("qi")*100 / (int)ob->query("max_qi");
		msg += damage_msg(damage, "内伤");
		msg += "( $n"+eff_status_msg(p)+" )\n";
	 	return msg;
	    } 
  
}
