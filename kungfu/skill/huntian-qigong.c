#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }
int ob_hit(object ob, object me, int damage);
int get_bouns(int damage,int t,int level,int flag);

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
	if ( me->query("gender") == "无性")
		return notify_fail("你无根无性，阴阳不调，难以领会高深的混天气功。\n");

        if ((int)me->query_skill("huntian-qigong", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("huntian-qigong", 1) >= 200 )
               return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

        return valid_public(me);
}

int practice_skill(object me)
{
       if((int)me->query_skill("huntian-qigong", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("huntian-qigong", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("你现在的修为不足以提高混天气功了。\n");       }
        else return notify_fail("你现在的混天气功修为只能用学(learn)的来增加熟练度。\n");

}
void skill_improved(object me)
{
        int skill, lit;
        skill = me->query_skill("huntian-qigong", 1);
        lit = me->query_skill("literate", 1);
        if(skill >= 300 && !me->query("htqg/300") && me->query("age")>55){
                tell_object(me, HIR"\n无意中你感觉一股热浪，从丹田涌出，你多年修炼的内力有了提高！\n"NOR);
                me->add("max_neili", random(lit + skill));
                me->set("htqg/300", 1);
        }
}


string exert_function_file(string func)
{
        return SKILL_D("huntian-qigong/") + func;
}
mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIW + me->name()+"面带神光，衣袍飞舞" NOR,
		"start_my_msg" : "你随意坐下，双手平放在双膝，默念口诀，开始运起独门心法。\n",
		"start_other_msg" : me->name()+"随意在那里坐下，双手平放在双膝，嘴唇微微颤动，身上的衣袍开始鼓动起来。\n",
		"halt_msg" : "$N面色一沉，迅速收气，站了起来。\n",
		"end_my_msg" : "你吸气入丹田，真气运转渐缓，慢慢收功，双手抬起，站了起来。\n",
		"end_other_msg" : "只见"+me->name()+"双手抬起，站了起来，衣袍慢慢垂了下来。\n"
	]);
}


int ob_hit(object ob, object me, int damage)
{
    int t,i;
    t = random(10); 
	i=me->query("neili")-ob->query("neili");
	if (i<=0) i=0;
	if (i>3000) i=2000+random(1000);
	
	if(!environment(me)) return 0;
	if( me->query_temp("htqg/powerup")&& t>7)		
	{
		if (random(me->query("neili"))>ob->query("neili")/2)
		{
			message_vision(HIR"$n猛然间感觉$N劲力勃发，一股大力传来，受到了不小的反震！\n"NOR,me,ob);
			ob->receive_damage("qi",random(i),me);
			ob->receive_wound("qi",100+random(100),me);
            return 1;
			//return -get_bouns(damage,t,me->query_skill("huntian-qigong",1),1);
		}
	
		//return -get_bouns(damage,t,me->query_skill("huntian-qigong",1),1);
	}
	
    if( (me->query("qi")-damage) >= 3000 ) return 0;
	
    if ( t >= 6 && me->query("env/混天气功")=="神罡" )
      {       
	       message_vision("$N"+HIY"眼见对方勇猛的很，激发心中血气，长啸一声，越战越勇，见$n打来竟然不躲，生生扛过了这致命的一击！\n" NOR, me,ob);
	       return -damage;
      }
}
int get_bouns(int damage,int t,int level,int flag)
{
	int dm;
	dm= (damage*flag*(t+level/20))/(t+level/20+10);
	if(flag && level>350) dm += dm/2;
	if(flag && level>450) dm += dm/2;
	
	return dm;
}
