// kuihua-shengong.c 葵花神功

inherit FORCE;
#include <ansi.h>

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
	int i = (int)me->query_skill("kuihua-shengong", 1);
	int t = 1, j;
	for (j = 1; j < i / 10; j++) t*= 2;
	if ((int)me->query_skill("force", 1) < 10)
        return notify_fail("你的基本内功火候不足，不能学葵花心法。\n");
	
	if ( !QUEST_D->queryquest(me,"kuihua/book") || me->query("gender") == "女性" )
		return notify_fail("你是怎么得到「葵花宝典」的？\n");
        
//	if (i > 100 && (int)me->query("shen") > t )
//		return notify_fail("学葵花心法，要心狠手辣，奸恶歹毒，你可做得不够呀！\n");
		
	if ( me->query_skill("buddhism",1) || me->query_skill("taoism",1) )
		return notify_fail("你练了秃驴牛鼻子们的心法，还学葵花心法做什麽！\n");

	if (
	   me->query_skill("shenzhao-jing",1)
	|| me->query_skill("taixuan-gong",1)
	|| me->query_skill("jiuyin-zhengong",1)
	|| me->query_skill("hamagong",1))

		return notify_fail("你不先散了别派内功，怎能学葵花心法？！\n");
	return 1;
}

int practice_skill(object me)
{
	if((int)me->query_skill("kuihua-shengong", 1) >= 200 ) {
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200) {
			me->improve_skill("kuihua-shengong", me->query_int());
			me->add("neili", -100);
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("你现在的修为不足以提高葵花神功了。\n");
	}
	else return notify_fail("葵花神功不可随便练习。\n");
}

string exert_function_file(string func)
{
	return __DIR__"kuihua-shengong/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : MAG + me->name()+"手捏绣花针，双目低垂内视"NOR ,
		"start_my_msg" : MAG"你手捏绣花针，盘膝坐下，默运葵花神功，只觉冷热两股紫气开始在体内缓缓游动。\n"NOR,
		"start_other_msg" : MAG + me->name()+"手捏绣花针盘膝坐下，周身似乎笼罩在一层紫气之中。\n"NOR,
		"halt_msg" : MAG"$N放下绣花针，两股真气迅速交汇消融。\n"NOR,
		"end_my_msg" : MAG"你将紫气在体内运行了一个周天，冷热紫气收于丹田，慢慢抬起了眼睛。\n"NOR,
		"end_other_msg" : MAG"只见"+me->name()+"慢慢睁开眼睛，周身笼罩的紫气逐渐隐去。\n"NOR,
	]);
}



mixed ob_hit(object ob, object me, int damage)
{
	 //By kingso 2007 01 26从新编辑，也感谢Counter小姐给告诉我底层不支持+= ([   
        int ap, dp;
        int  lvl;
        lvl = me->query_skill("kuihua-shengong", 1);
        if ( lvl < 150
          || me->query("neili") < 300
          || me->query_skill_mapped("force") != "kuihua-shengong")
         	return 0;
         	
        ap = ob->query_skill("parry");
        dp = me->query_skill("force");
        if (random(dp)> ap/2)
        {
	        me->add("neili", -50);
          me->receive_curing("qi", damage);
          me->receive_heal("qi", damage);

                return random(2) ?  HBMAG HIY "$N"HBMAG HIY"眼睛一花，$n"HBMAG HIY"已没了踪影。突然$n" 
                                    HBMAG HIY"从身后拍了一下$N"HBMAG HIY"的头，轻轻跃开。\n" NOR:
                                                        
                                    HBMAG HIC"忽然间，只见$n"HBMAG HIC"腰枝一摆，顿时出现无数个"
                                    HBMAG HIC"$n"HBMAG HIC"的影子，$N"HBMAG HIC"却无法辨别出$n"HBMAG HIC"的方位。\n" NOR;
                     }
}


mixed hit_ob(object me, object target)
{
    string msg;
    int j;
    j = me->query_skill("kuihua-shengong", 1);
   
    if (random(me->query_dex()) >= (target->query_dex()/4) && j > 120 &&
        me->query_skill("dodge",1) > 120 &&
        me->query("jingli")>300 && 
        !target->is_busy() &&
        me->query("combat_exp")/2 > random(target->query("combat_exp")) && 
        me->query("neili")>500)
   {
          switch(random(2))
          {
            case 0 :
               msg = HIC "$N默运葵花神功，身型飘忽不定，出招极快.一招指向$n周身大穴！\n";
               msg = msg + "$n只觉全身一麻，已被几招点中"HIY"「曲池穴」「风府穴」「大椎穴」！\n"NOR; 
               target->recevied_damage("qi", j +random(300));
               target->start_busy(2+random(2));
               break;
            case 1 :
               msg = HIW "$N出招诡异，指东打西.顿时劲气暴涨,将$n笼罩于内！\n";
               msg += "$n只觉周身要穴一麻，已被几招点中"HIY"「神风穴」「劳宫穴」「百会穴」！\n"NOR;
               target->recevied_damage("qi", j + random(300));
               target->start_busy(3+random(2));
               me->add("neili",-50);
               message_vision(msg, me, target);
               return j/(4-random(2));
               break;
            
          }         
          message_vision(msg, me, target);
   }
}