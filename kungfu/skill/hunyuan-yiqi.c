// hunyuan-yiqi.c 混元一气功
// dts@xkx, cleansword@xkx

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage)
{
	return usage == "force";
}

#include "force.h"

int valid_learn(object me)
{
	int nb, nf, nh, ns;
	nb = (int)me->query_skill("buddhism", 1);
	nf = (int)me->query_skill("force", 1);
	nh = (int)me->query_skill("hunyuan-yiqi", 1);
	ns = (int)me->query("guilty");

	if ( me->query("gender") != "男性" )
		return notify_fail("你纯阳之体，不能练习混元一气功。\n");
	//if (me->query("divorce"))
		//return notify_fail("你元阳泄露，不能学习混元一气功。\n");
	if (me->query("family/family_name")!="少林派")
		return notify_fail("你非少林弟子，不能学习混元一气功。\n");
	if ( nb < 220 && nb <= nh )
		return notify_fail("你的禅宗心法修为不够，无法领会更高深的混元一气功。\n");

	if ( nf < 20)
		return notify_fail("你的基本内功火候还不够20级，无法领会混元一气功。\n");

	//if ( ns > 0 ) 
		//return notify_fail("你屡犯僧家数戒，无法领会更高深的混元一气功。\n");

	return valid_public(me);
}

int practice_skill(object me)
{
       if((int)me->query_skill("hunyuan-yiqi", 1) >= 220 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("hunyuan-yiqi", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("你现在的修为不足以提高混元一气功了。\n");       }
        else return notify_fail("你现在的混元一气功修为只能用学(learn)的来增加熟练度。\n");

}

string exert_function_file(string func)
{
	return __DIR__"hunyuan-yiqi/" + func;
}
mapping exercise_msg(object me)
{
  return ([
    "status_msg" : HIR + me->name()+"脸上红光隐现，气象庄严" NOR,
      "start_my_msg" : "你五心向天，成五心向天的姿势，排除一切杂念，内息顺经脉缓缓流动。\n",
          "start_other_msg" : me->name()+"五心向天，一会工夫，从口鼻处缓缓吐出白气，白气越吐越浓，渐渐笼罩了全身。\n",
    "halt_msg" : "$N长出一口气，将内息急速退了回去，站了起来。\n",
              "end_my_msg" : "你将内息走了个小周天，流回丹田，收功站了起来。\n",
                  "end_other_msg" : "只见笼罩"+me->name()+"的白气渐渐消散，又从口鼻处吸了回去。\n"
                    ]);
}
