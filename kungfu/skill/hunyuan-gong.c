//by sohu@xojh 混元功 

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { if (this_player()->query("quest/chengkun/pass")) return usage == "force"; }

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
	if ( me->query("gender") == "无性")
		return notify_fail("你无根无性，阴阳不调，难以领会高深的混元功。\n");

        if ((int)me->query_skill("hunyuan-gong", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("hunyuan-gong", 1) >= 200 )
               return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

        return valid_public(me);
}

int practice_skill(object me)
{
       if((int)me->query_skill("hunyuan-gong", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("hunyuan-gong", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("你现在的修为不足以提高混元功了。\n");       }
        else return notify_fail("你现在的混元功修为只能用学(learn)的来增加熟练度。\n");

}
void skill_improved(object me)
{
        int skill, lit;
        skill = me->query_skill("hunyuan", 1);
        lit = me->query_skill("literate", 1);
        if(skill >= 300 && !me->query("hyg/300") && me->query("age")>35){
                tell_object(me, HIR"\n无意中你感觉一股热浪，从丹田涌出，你多年修炼的内力有了提高！\n"NOR);
                me->add("max_neili", random(lit + skill));
                me->set("hyg/300", 1);
        }
}


string exert_function_file(string func)
{
        return SKILL_D("hunyuan-gong/") + func;
}
mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIW + me->name()+"盘膝而坐，神情肃穆。" NOR,
		"start_my_msg" : "你盘膝坐下，双手相对，成球状，开始运起混元劲心法，一股热流涌向面庞。\n",
		"start_other_msg" : me->name()+"盘膝坐在那里，双手相对，合抱成球，脸上呈现一片殷红之色。\n",
		"halt_msg" : "$N微微睁开双眼，平息翻腾的胸口，缓缓站了起来。\n",
		"end_my_msg" : "你运转一个周天，气落丹田，双手缓缓抬起，站了起来。\n",
		"end_other_msg" : "只见"+me->name()+"双手吗慢慢抬起，站了起来，脸上的潮红逐渐褪去。\n"
	]);
}
