// bihai-chaosheng.c
#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) {
	if (this_player()->query("family/family_name")!="桃花岛")
	{
		return notify_fail("碧海潮生乃是桃花岛主黄老邪的秘传心法，没有得到他的传授，无法使用!\n");
	} 
	return usage == "force";
}

#include "force.h"

int valid_learn(object me)
{
	if ( me->query("gender") == "无性")
		return notify_fail("你无根无性，阴阳不调，难以领会高深的碧海潮生神功。\n");
	if (this_player()->query("family/family_name")!="桃花岛")
	{
		return notify_fail("碧海潮生乃是桃花岛主黄老邪的秘传心法，没有得到他的传授，无法使用!\n");
	} 
	if ((int)me->query_skill("bihai-chaosheng", 1) > me->query_skill("force", 1) + 10
	 && me->query_skill("bihai-chaosheng", 1) >= 200 )
		return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");
	if ((int)me->query_skill("bihai-chaosheng", 1) > me->query_skill("force", 1) + 10
	 && me->query_skill("bihai-chaosheng", 1) >= 200 )
		return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

	return valid_public(me);
}

int practice_skill(object me)
{
	if((int)me->query_skill("bihai-chaosheng", 1) >= 200 ){
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200){
			me->improve_skill("bihai-chaosheng", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("你现在的修为不足以提高碧海潮生功了。\n");
	}
	else return notify_fail("你现在的碧海潮生功修为只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return SKILL_D("bihai-chaosheng/") + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIC + me->name() + "面容肃穆，静坐如渊岳，沐轻风而不惊" NOR,
		"start_my_msg" : "你盘腿坐下，双目微闭，双手掌心相向成虚握太极，天人合一，练气入虚。\n",
		"start_other_msg" : me->name() + "盘腿坐下，双目微闭，双手掌心相向成虚握太极。轻风吹过，" + me->name() + "身上的衣袍竟然不为所动。\n",
		"end_my_msg" : "你将内息又运了一个小周天，缓缓导入丹田，双臂一震，站了起来。\n",
		"end_other_msg" : me->name() + "的脸上红光乍现，又立刻隐去。随即双臂一震，站了起来。\n",
		"heal_msg" : HIC"$N凝神静气，内息随悠扬箫声在全身游走，恰似碧海浪涛般冲击受损被封经脉。\n"NOR,
		"heal_finish_msg" : HIC"$N脸色渐渐变得舒缓，箫声亦随之急转直下，渐不可闻。\n"NOR,
		"heal_unfinish_msg" : HIR"$N内息微弱，难以为济，箫声募然高亢渐而消失，人随之站起，猛地吐出一口鲜血。\n"NOR,
		"heal_halt_msg" : HIC"$N突感周身不适，内息全然不受乐音指引，急忙停止吹奏，箫声骤然竭止。\n"NOR,
	]);
}

mixed hit_ob(object me, object ob, int damage)
{
	//催毒效果
	//迷阵效果
	//音乐伤精效果

	int lvl,num,dam;
	object weapon,tweapon;
	string msg;
	if (!me) return;
	weapon=me->query_temp("weapon");
	tweapon=ob->query_temp("weapon");
	
	lvl=me->query("bihai-chaosheng",1);
	num=ob->query_temp("thd/fugu");
	dam=lvl+me->query_skill("qimen-bagua",1);
	dam=dam+random(dam);
	//内功融合后开放
	if (me->query("thdjj/ronghe")!="pass") return;
	
	if (random(10)>7
		&& objectp(ob)
		&& me->is_fighting())
	{
		switch (random(3))
		{
	 	   case 0: //迷阵
		
				if(!ob->is_busy() || !ob->query_temp("thd/maze")) {

					message_vision(HIY"$N眼见$n摆脱了自己所布置的迷阵，立即又顺手捡起几块砖头和树枝重新布置了个小型迷阵!\n"+
						"形成大迷阵中嵌套小迷阵的效果，又重新将$n陷入迷阵之中！\n"NOR,me,ob);
					ob->add_busy(2);
				
					ob->add("jingli",-dam);
				}

			 	break;
			case 1: //催毒
				if (weapon
					&& weapon->query("id")=="xiao"
					&& ob->query_temp("thd/fugu")
					&&me->query("env/碧海潮生")=="催毒")
				{
					message_vision(HBCYN"$N眼见$n应接不暇，趁机将手中的"+weapon->query("name")+HBCYN"横在嘴边，幽幽吹响!\n"+
					"$n忽觉自己身上不经意间为$N所暗中所下的「"HIB+"腐骨毒"+HBCYN"」暗伤开始发作，痛彻入骨！\n"NOR,me,ob);
					ob->receive_wound("qi",random(lvl)*num,me);
					if (!ob->query_condition("fugu_poison"))
						ob->apply_condition("fugu_poison",num);
					message_vision(HIB"$N感觉丹田气乱窜，气血翻涌，极为痛楚。\n"NOR,ob);
					ob->add("neili",-damage);
				}
				break;
			case 2://play 
				if (weapon
					&& weapon->query("id")=="xiao"
					&& me->query("env/碧海潮生曲"))
				{
					message_vision(HBMAG+HIW"$N幽幽咽咽地吹奏起“碧海潮生曲”来，曲调如泣如述，柔情万端。\n"NOR, me,ob);
					if (random(me->query_skill("qimen-bagua",1)*me->query("pur"))>ob->query_skill("qimen-bagua",1)*ob->query("pur")/2)
					{
						message_vision(HIW"$S忽然觉得面红耳赤，百脉贲张，心旌摇动，呼吸急促。\n"NOR, me,ob);
						ob->receive_damage("jing",damage/2,me);
						ob->receive_wound("jing",damage/5,me);
						ob->apply_condition("no_exert",1);
					}else {
						message_vision(HIW"$S识破$N的招式，重重地冷哼一声，借此破掉$N的箫声对心神的攻击。\n"NOR, me,ob);
						me->add_busy(2);
					}

				}
				break;
		}

	}
	
	  

}
