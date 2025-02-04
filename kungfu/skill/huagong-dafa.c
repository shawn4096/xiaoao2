// huagong-dafa.c 化功大法
// By Spiderii 增加auto效果！
// 再次修改，标记累加的问题
//还是我。。555..修改为yun power才有auto效果！
#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }
#include "/kungfu/skill/force.h"
#include <combat_msg.h>

int valid_learn(object me)
{
	int j, t, lvl, shen, mforce;
	lvl = (int)me->query_skill("huagong-dafa", 1);
	shen = (int)me->query("shen");
	mforce = me->query_skill("force", 1);

	t = 1;

	for ( j = 1; j < lvl / 10; j++) t *= 2;
	if ( t > 5000 ) t = 5000;

	if ( me->query_skill("buddhism",1) || me->query_skill("taoism",1) )
		return notify_fail("你练了别派心法，再学化功大法会走火入魔！\n");

	if ( mforce < 10)
		return notify_fail("你的基本内功还差点儿, 学不了化功大法。\n");

	if ( lvl > mforce + 10 && lvl >= 200 )
		return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

	if ( (lvl > 10 && lvl < 100 && shen > -(t * 200))
	|| ( lvl >=100 && shen > -50000))
		return notify_fail("你的邪气太少了。\n");

        return valid_public(me);
}

int practice_skill(object me)
{
	if( me->query_skill("huagong-dafa", 1) >= 200 ){
		if( me->query("potential", 1) > 5 && me->query("neili", 1) > 200) {
			me->improve_skill("huagong-dafa", me->query_int());
			me->add("neili", -100);
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		return notify_fail("你现在的修为不足以提高化功大法了。\n");
	}
	return notify_fail("你现在的化功大法修为只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return __DIR__"huagong-dafa/" + func;
}

void skill_improved(object me)
{
	int skill, poison;
	skill = me->query_skill("huagong-dafa", 1);
	poison = me->query_skill("poison", 1);

	if(skill >= 100 && !me->query("hgdf") && poison > 100){
		tell_object(me, HIY"冥冥中你感觉到体内的化功大法和毒技相互相济，使你的内力修为有所提高！\n"NOR);
		me->add("max_neili", 50);
		me->set("hgdf", 1);
	}
	if(skill >= 150 && me->query("hgdf")==1 && poison > 150){
		tell_object(me, HIY"冥冥中你感觉到体内的化功大法和毒技相互相济，使你的精力修为有所提高！\n"NOR);
		me->add("max_jingli", 50);
		me->add("eff_jingli", 50);
		me->set("hgdf", 2);
	}
	if(skill >= 200 && me->query("hgdf")==2 && poison > 200){
		tell_object(me, HIY"冥冥中你感觉体内的化功大法和毒技相互相济，使你的武功修为有所提高！\n"NOR);
		me->add("combat_exp", 5000);
		me->set("hgdf", 3);
	}
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : BLU + me->name()+"正坐在地上修练内息，身体被一股青烟环绕着" NOR,
		"start_my_msg" : "你气运丹田，将体内毒素慢慢逼出，控制着它环绕你缓缓飘动。你感觉到内劲开始有所加强了。\n",
		"start_other_msg" : me->name()+"盘膝坐下运功，身体渐渐被一股青烟所包围。\n",
		"halt_msg" : "$N双眼一睁，眼中射出一道精光，接着阴阴一笑，站了起来。\n",
		"end_my_msg" : "你感觉毒素越转越快，就快要脱离你的控制了！你连忙收回毒素和内息，冷笑一声站了起来。\n",
		"end_other_msg" : me->name()+"阴阴一声冷笑，呼出一口青烟，站起身来藐视地扫了在场的人一眼。\n"
	]);
}

mixed hit_ob(object me, object ob, int damage)
{
	
	int busy,p;
	string msg;
	//散发星宿毒
	if (me->query_temp("hgdf_power")
		&&!random(3)
		&&me->query("env/化功大法")=="散毒")
	{
		message_vision(BLU"$N化功大法流转不息，带起一股若隐若现的蓝色毒雾散香$n周身。\n"NOR,me,ob);
		if (ob->query_condition("xx_poison")<10&&!random(2))
		{
			ob->add_condition("xx_poison",1);
			message_vision(BLU"$n一时不查一口吸入肺中，已经为星宿毒毒雾所浸染。\n"NOR,me,ob);

		}

	}
	
	if( me->query_temp("hgdf_power")) {
	 if( ob->is_busy() && random(4)==1  )
	  {
		message_vision(BLU"$N运起化功大法，周身围绕一股薄薄的蓝色气体，攻势凛然，旁人避之不急。\n"NOR,me);
	 	me->set_temp("action_flag",1);
	 	me->add_temp("apply/attack",me->query_skill("huagong-dafa",1)/5);
	 	me->add_temp("apply/damage",me->query_skill("huagong-dafa",1)/5);
	 	
	 	   COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), userp(me)?3:1);
		//if (me->is_fighting(ob))
		   //COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 3);
	 	me->add_temp("apply/attack",-me->query_skill("huagong-dafa",1)/5);
	 	me->add_temp("apply/damage",-me->query_skill("huagong-dafa",1)/5);
	 	
		me->delete_temp("action_flag");
	 	return;
	 }
	 else
		 if( !ob->is_busy()
	 && me->query_str()*10/2+random(me->query_str()*10/2) > random(ob->query_con()*10) 
	 && random(me->query("neili"))>1000
	 && me->query("jingli")>1000
	 && random(4)==3
	 && me->query("quest/hgdf/powerup")
	 ){
	   switch(random(2))
	   {
	 	 case 0:
		  msg = BLU"$N招式陡然一变，抬手便拿住了$n的胸口诸大要穴。\n$n本想挣扎，但觉自身内力竟然源源不断的被化掉，一时间吓得目瞪口呆。\n"NOR;
	   	  busy = me->query_str()-ob->query_con();
	 	  if(busy<=0) busy = 1+random(2);
	 	  if(busy>5) busy=5;
	 	  ob->add_busy(busy);
	 	  ob->add("neili", -busy*1000);
		  ob->apply_condition("no_exert",2);
		  ob->add_condition("xx_poison",2+random(1));
             // me->add("neili",busy*100); 化掉非吸掉
	 	  return msg;
		  break;
		 case 1:
          msg = HBBLU"$N化功大法运用到摘星术中，轻轻一跃跳到$n的背后，抬手便拿住了$n的后颈诸大要穴。\n$n本想挣扎，但觉自身精血竟然源源不断的被化掉，一时间吓得目瞪口呆。\n"NOR;
	   	  busy = me->query_str()-ob->query_con();
	 	  if(busy<=0) busy = 1+random(2);
	 	  if(busy>5) busy=5;
	 	  ob->add_busy(busy);
	 	  ob->add("jingli", -busy*1000);
		  ob->apply_condition("no_perform",2);
		  ob->add_condition("xx_poison",2+random(1));

             // me->add("neili",busy*100); 化掉非吸掉
	 	  return msg;
		  break;
		 }
	 }
	else 
		 if(random(me->query("neili"))>1500
	 && me->query("jingli")>500
	 && me->query("jiali") > 30
	 && !me->query_temp("weapon")
	 && random(5)==1 
	 ){
		
	 	msg = BLU"$N双手挥动间，腥风大起，$n一时避之不急，被$N在胸口重重击了一掌。\n"NOR;
	 	damage = (me->query_str()*10+me->query_skill("force")-ob->query_skill("parry",1))*5;
	 	if(damage<=0) damage = 1;
	 	if(damage>4000) damage = 4000;
		if (userp(me)&&!userp(ob))
		   damage =damage*2;
	 	
		ob->add_condition("xx_poison",1+random(1));

	 	ob->receive_wound("qi", damage - ob->query_temp("apply/armor"), me);
		p=(int)ob->query("qi")*100 / (int)ob->query("max_qi");
		msg += damage_msg(damage, "内伤");
		msg += "( $n"+eff_status_msg(p)+" )\n";
	 	return msg; 
	 }
  }
}
