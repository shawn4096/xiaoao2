#include <ansi.h>
inherit FORCE;
#include <combat.h>

int valid_enable(string usage) 
{ 
    //解开九阴全才能作为武功，其他只能作为杂学
    if (this_player()->query("quest/jiuyin1/pass")) return usage == "force"; 
}
int valid_learn(object me)
{
	if((int) me->query_skill("jiuyin-zhengong", 1) < 220)
		return notify_fail("你只能通过研读九阴真经来提高九阴真功。\n");

	if ((int)me->query_skill("jiuyin-zhengong", 1) > me->query_skill("force", 1) + 10
	&& me->query_skill("jiuyin-zhengong", 1) >= 220 )
		return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

        if ((int)me->query_skill("jiuyin-zhengong", 1) + 10 > me->query_skill("daode-jing", 1)
			|| me->query_skill("daode-jing", 1) < 221)

			return notify_fail("你的道德经不够，不能继续修习九阴真功。\n");
       
        if((int)me->query_skill("shenzhao-jing", 1) >= 1 )
                return notify_fail("你不散去神照经，怎么修炼九阴真功。\n");
    
        if((int)me->query_skill("hamagong", 1) >= 1 )
                return notify_fail("你不散去蛤蟆功，怎么修炼九阴真功。\n");

        if((int)me->query_skill("lengquan-shengong", 1) >= 1 )
                return notify_fail("你不散去冷泉神功，怎么修炼九阴真功。\n");

        if((int)me->query_skill("kuihua-mogong", 1) >= 1 )
                return notify_fail("你不散去葵花魔功，怎么修炼九阴真功。\n");  
    
        if((int)me->query_skill("jiuyang-gong", 1) >= 1 )
                return notify_fail("你不散去九阳神功，怎么修炼九阴真功。\n");  
     
        if((int)me->query_skill("luohan-fumogong", 1) >= 1 )
                return notify_fail("你不散去罗汉伏魔功，怎么修炼九阴真功。\n");

        if((int)me->query_skill("taixuan-gong", 1) >= 1 )
                return notify_fail("你不散去太玄功，怎么修炼九阴真功。\n");  
      
        if (me->query("gender") == "无性")
                return notify_fail( HIW"【无根无性之人何以修得这道家无上心法】。\n");
 

        if ((int)me->query_dex()< 35)
                return notify_fail("你觉得自己的身法不够灵动，不可能掌握这么飘缈"
                                   "玄奇的内功心法。\n");
 
        if ((int)me->query_int()< 40)
                return notify_fail("你觉得自己的先天悟性不够，不可能领悟这么高深"
                                   "玄奇的内功心法。\n");
		if ((int)me->query_str()< 28)
                return notify_fail("你觉得自己的先天臂力不够，不可能领悟这么高深"
                                   "玄奇的内功心法。\n");

       

	return 1;
}

int practice_skill(object me)
{
	if((int)me->query_skill("jiuyin-zhengong", 1) >= 220 ) {
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200){
			me->improve_skill("jiuyin-zhengong", (int)me->query_int());
			me->add("neili", -150);
			me->add("potential", -1*(1+random(2)));
			return 1;
		}
		else return notify_fail("你现在的修为不足以提高九阴真功了。\n");
	}
	else return notify_fail("你现在的九阴真功修为只能研读(study)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return SKILL_D("jiuyin-zhengong/") + func;
}

void skill_improved(object me)
{
	if( me->query_skill("jiuyin-zhengong",1) > 0
	&& !me->query("jiuyin/bonus")){
		tell_object(me, "你的九阴真功增加了你的内力修为！\n");
		me->set("jiuyin/bonus", 1);
		me->add("max_neili", 10); 
	}
	if( me->query_skill("jiuyin-zhengong",1) >= 250
	&& me->query("jiuyin/bonus") < 2 ){
		tell_object(me, "你的九阴真功增加了你的内力修为！\n");
		me->add("jiuyin/bonus", 1);
		me->add("max_neili", 200);
	}
	if( me->query_skill("jiuyin-zhengong",1) >= 350
	&& me->query("jiuyin/bonus") < 3 ) {
		tell_object(me, "你的九阴真功增加了你的内力修为！\n");
		me->add("jiuyin/bonus", 1);
		me->add("max_neili", 400); 
	}
	if( me->query_skill("jiuyin-zhengong",1) >= 450
	&& me->query("jiuyin/bonus") < 4 ) {
		tell_object(me, HIC"你的九阴真功增加了你的精力修为！\n"NOR);
		me->add("jiuyin/bonus", 1);
		me->add("max_jingli", 400);
		tell_object(me, HIC"你的九阴真功增加了你的内力修为！\n"NOR);
		me->add("max_neili", 800); 
	}
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIC + me->name() + "双眼微闭，被一股九阴真气围绕著。" NOR,
                "start_my_msg" : HIC"你盘腿坐下，双目微闭，双手掌心相向成虚握太极，天人合一，练气入虚。\n"NOR,
                "start_other_msg" : me->name() + "盘腿坐下，双目微闭，双手掌心相向成虚握太极。轻风吹过，" + me->name() + "身上的衣袍竟然不为所动。\n",
                "end_my_msg" : HIC"你将内息又运了一个小周天，缓缓导入丹田，双臂一震，站了起来。\n"NOR,
                "end_other_msg" : me->name() + "的脸上陡然一暗，又立刻隐去。随即双臂一震，站了起来。\n"
        ]);
}
//增加内功攻击和牵制效果

mixed ob_hit(object ob, object me, int damage)
{
	string msg;
	int ap, dp, j, neili, neili1;
	object weapon;

	if( !me->query_temp("jiuyin/powerup")) return 0;
    if (me->query("env/九阴真功")!="护体") return 0;
   
	neili = me->query("neili");
	neili1 = ob->query("neili");

	if(me->query_skill_mapped("force")!="jiuyin-shengong") {
		
		return 0;
	}

	if( me->query_temp("fanzhen")) {
		me->delete_temp("fanzhen");
		return 0;
	}

	if (me->query_skill("parry",1) < 500
	 || me->query("combat_exp") < ob->query("combat_exp")/2
	 || neili < 400 ) return 0;

	weapon = ob->query_temp("weapon");

	if(objectp(weapon))
		msg = weapon->query("skill_type");
	else {
		mapping prepare = ob->query_skill_prepare();
		if (!sizeof(prepare)) msg = "unarmed";
		else msg = keys(prepare)[0];
	}

	ap = COMBAT_D->skill_power(ob, msg, SKILL_USAGE_ATTACK) / 1000;
	if ( weapon ) ap *= 2;
	if ( ob->query("neili") > me->query("neili") * 2 ) ap += ap/2;
        
	dp = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE) / 1000;
	if ( me->is_busy() ) dp /= 2;   
	if ( me->query("neili") > ob->query("neili") * 2 ) dp *= 2;  
	else if ( me->query("neili") > ob->query("neili") / 2 * 3 ) dp += dp/2;
         
	if ( random(10) < 5 ) me->set_temp("fanzhen", 1);

	ap = ABS(ap);
	dp = ABS(dp);

	if ( me->query_temp("jiuyin/powerup"))
		dp += ap/2 + random(ap/2);

	if ( wizardp(me))
		tell_object(me, sprintf("ap: %d, dp: %d\n", ap, dp));

	if( random(dp) > ap && random(2)) {
		msg = CYN "$N默运九阴真经的口诀，真气流转不绝，隐隐在$N周身形成一层若隐若现的气罩。\n" NOR;
		//tell_object(ob, WHT "你只见对手突然身子一侧，将半边身子迎了上来！\n" NOR);
	   if (random(neili)>neili1/2 )
	   {
			msg +=HIW "$n一招打在$N的身上，只觉似乎打在一团棉花上，九阴真经劲气勃发，形成极强的反震之力。\n"NOR;
			ob->receive_damage("qi",random(4000),me);
            ob->receive_wound("jing",random(500),me);
			ob->add_busy(2);
			ob->apply_condition("no_exert",1);
            me->set_temp("fanzhen",1);
			j=-damage;
	    }		
	    else if(neili >= neili1 + random(damage)) {
			msg +=HIC "结果$n的攻击被$N的九阴真功化掉了！\n"NOR,
			j = -damage;
	    }
	    else if( neili > neili1 + random(damage) ) {
			msg += WHT"结果$n的攻击被$N的九阴真气化掉了大半！\n"NOR,
			j = -damage/3*2;
	    }
	    else {
			msg += WHT"结果$N只化掉了$n的一小半力道！\n"NOR,
			j = -damage/2;
	    }
		message_vision(msg, me, ob);
		return j;
	}
}
