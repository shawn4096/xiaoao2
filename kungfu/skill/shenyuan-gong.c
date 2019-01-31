#include <ansi.h>
inherit FORCE;

int valid_enable(string usage)
{
	  if (this_player()->query("family/family_name")=="姑苏慕容" )
		 // || this_player()->query("cw_mp/姑苏慕容")
        return usage == "force";
}

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
		mapping fam  = me->query("family");
	if ((!fam || fam["family_name"] != "姑苏慕容" )&& !me->query("cw_mp/姑苏慕容") )
			 	return notify_fail("你并非慕容弟子，如何习得了慕容神功。\n");
        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("你的基本内功火候还不够，无法领会神元功。\n");

	if ( me->query("gender") == "无性")
		return notify_fail("你无根无性，阴阳不调，难以领会高深的神元功。\n");

        if ((int)me->query_skill("shenyuan-gong", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("shenyuan-gong", 1) >= 200 )
               return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

        return valid_public(me);
}

int practice_skill(object me)
{
       if((int)me->query_skill("shenyuan-gong", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("shenyuan-gong", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("你现在的修为不足以提高神元功了。\n");
       }
        else return notify_fail("你现在的神元功修为只能用学(learn)的来增加熟练度。\n");

              
}

string exert_function_file(string func)
{
        return __DIR__"shenyuan-gong/" + func;
}
mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIB + me->name()+"眼神凌厉，神态极为凝重" NOR,
		"start_my_msg" : "你随意一站，双手缓缓抬起，深吸一口气，真气开始在体内运转。\n",
		"start_other_msg" : me->name()+"随意在那里一站，双手缓缓抬起，眼神开始变的凌厉起来。\n",
		"halt_msg" : "$N眉头一皱，急速运气，把手放了下来。\n",
		"end_my_msg" : "你将真气在体内沿脉络运行了一圈，缓缓纳入丹田，放下手，长吐了一口气。\n",
		"end_other_msg" : "只见"+me->name()+"的眼睛慢慢闭上，立刻睁开，把手放下，长吐了一口气。\n"
	]);
}





mixed hit_ob(object me,object victim,int damage)
{
	string msg;
	int j;
	j = me->query_skill("douzhuan-xingyi", 1)+random(me->query_skill("shenyuan-gong", 1));
	//j=j/2;
	if (!objectp(victim)) return;
	
     if (me->query_skill_prepared("finger") != "canhe-zhi"
           || me->query_skill_mapped("finger") != "canhe-zhi"
		   ||!me->query_temp("shenyuan")
		   ||!me->query("quest/mr/dzxy/pass"))
      return 0;  
  
  //设置成quest模式。
 
	if ( random(me->query_skill("force",1)) > victim->query_skill("force",1)/2
         //&& random(10)>5
	     && me->query("jingli") > 300
		 && me->query_temp("shenyuan")
	     && random(me->query("combat_exp")) > victim->query("combat_exp")/2
         && me->query("neili") > 500
		
         || ( userp(me) && me->query_temp("lianhuan") && random(j)>=300 )
         ||( !userp(victim) && me->query_temp("lianhuan")) )
         {
		   switch(random(3))
		   {
			case 0 :
				message_vision(HIW"$N默运神元神功，一股阴柔的指风轻飘飘地点向$n，一股内劲无声无息的绕向$n周身大穴！\n"NOR,me,victim);
				if (random(me->query_skill("finger",1))>victim->query_skill("parry",1)/2)
				{
					message_vision(HIR"$n只觉全身一麻，已被一招点中「神阖穴」！\n"NOR,me,victim); 
				    if (me->query("quest/mr/dzxy/pass")) {
						victim->add_busy(3);
						victim->apply_condition("no_perform",2);
					}
				    else victim->add_busy(1);
						
				}
				else
                    message_vision( GRN"$n识破了$N的招式，向旁边躲闪开去！\n"NOR,me,victim); 
				break;
			case 1 :
				//if (!random(2)) break;
				
			    message_vision(HBRED"$N指风犀利，似一道无形剑气，将$n笼罩于内！$n只觉胸口一痛，全身真气狂泻而出。\n"NOR,me,victim);
				victim->recevied_damage("neili", j*2);
                victim->add_busy(1+random(2));
                victim->add_condition("no_exert",1+random(2));				
				if ( victim->query("neili") < 0 )
					victim->set("neili", 0);
				me->add("neili",-20);
				break;
			case 2 :
				if (me->query_skill_mapped("parry")!="douzhuan-xingyi") break;
				
			    msg = HIG"$N想起慕容家传绝学神元功,劲力涌动，配合斗转星移绝技忽然施展出来一招。\n"NOR;
			    if (random(me->query_str(1))>victim->query_dex(1)/2)
			    {
					 message_vision(HIC"$n只觉自己的所有攻击都被$N所封死,宛如陷入到泥潭之中，浑身酸软无力。\n"NOR,me,victim);
					victim->recevied_damage("jing", j,me);
					victim->set_temp("lost_attack",1+random(3));
					victim->add_busy(1+random(3));
					if (victim->quuery("neili")>3000)
						victim->add("neili",-random(3000));
					if ( victim->query("neili",1) < 0 )
						victim->set("neili", 0);
					me->add("neili",-20);
				}
				else 
                   message_vision(HIY"他运力于足，一招燕子回翔，轻飘飘腾身而起，跃出$N的劲力笼罩范围范围。\n"NOR,me,victim);
				break;
				//default: break;
		}
		//message_vision(msg, me, victim);
		
	}
}
