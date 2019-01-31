// 罗汉伏魔神功 luohan-fumogong.c
//By kingso

inherit FORCE;
#include <ansi.h>

#include <combat_msg.h>

int valid_enable(string usage) { return usage == "force"; }

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
        if((int)me->query_skill("shenzhao-jing", 1) >= 1 )
                return notify_fail("你不散去神照经，怎么修炼罗汉伏魔功。\n");
    
        if((int)me->query_skill("lengquan-shengong", 1) >= 1 )
                return notify_fail("你不散去冷泉神功，怎么修炼罗汉伏魔功。\n");

        if((int)me->query_skill("jiuyin-zhengong", 1) >= 1 )
                return notify_fail("你不散去九阴真功，怎么修炼罗汉伏魔功。\n");

       if((int)me->query_skill("kuihua-shengong", 1) >= 1 )
                return notify_fail("你不散去葵花神功，怎么修炼罗汉伏魔功。\n");  
    
        if((int)me->query_skill("jiuyang-gong", 1) >= 1 )
                return notify_fail("你不散去九阳神功，怎么修炼罗汉伏魔功。\n");  
     
       if((int)me->query_skill("hamagong", 1) >= 1 )
                return notify_fail("你不散去蛤蟆功，怎么修炼罗汉伏魔功。\n");

        if((int)me->query_skill("taixuan-gong", 1) >= 1 )
                return notify_fail("你不散去太玄功，怎么修炼罗汉伏魔功。\n");       

        if ((int)me->query("int") < 33)
                return notify_fail("你先天悟性不足，难以领会罗汉伏魔神功。\n");

        if ((int)me->query("con") < 20)
                return notify_fail("你先天根骨孱弱，无法修炼罗汉伏魔神功。\n");
       
        if ( me->query("gender") == "无性" && me->query("luohan-fumogong", 1) > 29)
                return notify_fail("你无根无性，阴阳不调，难以领会高深的罗汉伏魔神功。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本内功火候不足，不能学罗汉伏魔神功。\n");

        if ((int)me->query("max_neili", 1) < 1000)
                return notify_fail("你的内力修为不足，不能学罗汉伏魔神功。\n");
        if(!me->query("quest/摩天崖/luohan")) 
                return notify_fail("你现在不能学习罗汉伏魔功。\n");


        return ::valid_learn(me);
}

int practice_skill(object me) 
{      
       if((int)me->query_skill("shenzhao-jing", 1) >= 1 )
                return notify_fail("你不散去神照经，怎么修炼罗汉伏魔功。\n");
    
        if((int)me->query_skill("lengquan-shengong", 1) >= 1 )
                return notify_fail("你不散去冷泉神功，怎么修炼罗汉伏魔功。\n");

        if((int)me->query_skill("kuihua-mogong", 1) >= 1 )
                return notify_fail("你不散去葵花魔功，怎么修炼罗汉伏魔功。\n");

       if((int)me->query_skill("kuihua-shengong", 1) >= 1 )
                return notify_fail("你不散去葵花神功，怎么修炼罗汉伏魔功。\n");  
    
        if((int)me->query_skill("jiuyang-gong", 1) >= 1 )
                return notify_fail("你不散去九阳神功，怎么修炼罗汉伏魔功。\n");  
     
       if((int)me->query_skill("hamagong", 1) >= 1 )
                return notify_fail("你不散去蛤蟆功，怎么修炼罗汉伏魔功。\n");

        if((int)me->query_skill("taixuan-gong", 1) >= 1 )
                return notify_fail("你不散去太玄功，怎么修炼罗汉伏魔功。\n");       


       if((int)me->query_skill("luohan-fumogong", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("luohan-fumogong", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("你现在的修为不足以提高罗汉伏魔神功了。\n");       }
        else return notify_fail("你现在的罗汉伏魔神功修为只能用学(learn)的来增加熟练度。\n");

}

string exert_function_file(string func)
{
	return SKILL_D("luohan-fumogong/") + func;
}
mapping exercise_msg(object me)
{
  
    return ([
		"status_msg" : HBRED HIY + me->name()+"盘膝而坐，手结罗汉伏魔印，头上佛光隐现，外袍随真气鼓动。" NOR,
		"start_my_msg" : HBRED HIC "你排除一切杂念，手结伏魔罗汉印，一股强大的内息开始在体内运转。\n"NOR,
		"start_other_msg" : HBRED HIC + me->name()+"排除一切杂念，手结伏魔罗汉印，顿时周围产生一股强大的气场。\n"NOR,
		"halt_msg" : "$N长出一口气，将内息急速退了回去，站了起来。\n",
		"end_my_msg" : HBMAG HIY"你将内息运转一个大周天，流回丹田，收功站了起来。\n"NOR,
		"end_other_msg" :HBMAG HIY "只见笼罩"+me->name()+"的那团若隐若现的金光，慢慢消失。\n"NOR,
		"heal_msg" : HBMAG HIY"$N手结罗汉伏魔印，缓缓坐下，轻念“罗汉伏魔咒”，开始运功疗伤。\n"NOR,
		"heal_finish_msg" : HBMAG HIY"$N缓缓站起，周身环绕着若影若现的金光，犹如罗汉降世！”\n"NOR,
		"heal_unfinish_msg" : "$N吐出瘀血，缓缓站起，但脸色苍白，看来还有伤在身。\n",
		"heal_halt_msg" : HBMAG HIY"$N盘膝而坐，周身环绕着若影若现的金光，手结罗汉伏魔印，犹如罗汉降世。\n"NOR,
	]);

}

mixed hit_ob(object me, object ob, int damage)
{
	
	int busy,p;
	string msg;

	if(!me->query("quest/摩天崖/luohan")) return;
	if(me->query_temp("luohan_power"))
	{
		me->add_temp("luohan_power",-1);
		return;
	}
     
	 if(random(7)==3 && random(3)  )
	 {
		me->set_temp("luohan_power",1);
	 	me->delete_temp("combat_time");
	 	message_vision(HBMAG HIY"$N运起罗汉伏魔功，左手结罗汉伏魔印，周身金光闪现。\n"NOR,me);
	 	me->set_temp("action_flag",1);
	 	me->add_temp("apply/attack",me->query_temp("combat_time")*10);
	 	me->add_temp("apply/damage",me->query_temp("combat_time")*10);
	 	me->add_temp("apply/parry",me->query_temp("combat_time")*10);
	 	COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 3);
	 	me->add_temp("apply/attack",-me->query_temp("combat_time")*10);
	 	me->add_temp("apply/damage",-me->query_temp("combat_time")*10);
	 	me->add_temp("apply/parry",-me->query_temp("combat_time")*10);
		me->delete_temp("action_flag");
	 	return;
	 }
	 
	 else 
		 if(random(me->query("neili"))>1800
	 && me->query("jingli")>500
	 && me->query("jiali") > 30
	 && random(6)==1 
	 ){
		me->set_temp("luohan_power",5);
	 	msg = HBMAG HIY"只见$N周身金芒闪现，左手罗汉伏魔印顺势一转，突然间起身而上，还没等$n反应过来，一股雄浑的内劲透体而入。\n"NOR;
	 	damage = (me->query_str()*10+me->query_skill("force")-ob->query_skill("parry",1))*5;
	 	if(damage<=0) damage = 1;
	 	if(damage>2000) damage = 3500 + random(2000);
	 	ob->receive_wound("qi", damage - ob->query_temp("apply/armor"), me);
		p=(int)ob->query("qi")*100 / (int)ob->query("max_qi");
              if( me->query("env/罗汉伏魔") == "伏魔" ){ 
              ob->add_condition("luohan_hurt", random(me->query_con())); }
		msg += damage_msg(damage, "内伤");
		msg += "( $n"+eff_status_msg(p)+" )\n";
	 	return msg;
	 }
}


