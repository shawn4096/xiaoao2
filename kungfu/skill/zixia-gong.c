// zixia-gong.c 紫霞神功
// Update by lsxk@hsbbs 调整成华山派 Quest 内功  2007/7/26

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) {if (this_player()->query("quest/zixia/pass")) return usage == "force";
}

#include "force.h"

int valid_learn(object me)
{
        
        int lvl, i;
        lvl = (int)me->query_skill("zixia-gong", 1);
        i = (int)me->query("shen", 1);
        if (!me->query("quest/zixia/pass"))
                return notify_fail("紫霞神功只能通过解密学习。\n");
        if ( me->query("gender") == "无性" && lvl > 49)
                return notify_fail("你无根无性，阴阳不调，难以领会高深的紫霞神功。\n");

        if ( me->query("class") == "bonze" )
                return notify_fail("紫霞神功讲究阴阳调合，有违佛家六根清净之意，"
                        +RANK_D->query_respect(me)+"欲修此功，已是罪过。\n");

        if ((int)me->query_skill("force", 1) < 15)
                return notify_fail("你的基本内功火候还不够。\n");
/*
        if (me->query("quest/huashan")!="气宗")
                return notify_fail("你非华山气宗弟子，如何修习紫霞神功？\n");*/

        if ((lvl > 10 && lvl < 100 && i < lvl*lvl*lvl / 20 )
            || ( lvl >=100 && i < 100000))
                return notify_fail("你的侠义正气太低了，无法学习高深的紫霞神功。\n");

        return valid_public(me);
}

int practice_skill(object me)
{
       if((int)me->query_skill("zixia-gong", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("zixia-gong", (int)me->query("int"));
                   me->add("potential", -1*(1+random(3)));
                   me->add("neili", -100); 
                   return 1;
           }
           else return notify_fail("你现在的修为不足以提高紫霞功了。\n");
       }
        else return notify_fail("紫霞功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"zixia-gong/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : MAG + me->name()+"双手捏个剑诀，脸上紫气浮现"NOR,
		"start_my_msg" : MAG"你屏息静气，坐了下来，左手搭在右手之上，在胸前捏了个剑诀，引导内息游走各处经脉。\n"NOR,
		"start_other_msg" : MAG + me->name() +"坐了下来，少顷脸上隐隐笼罩了一层紫气。\n"NOR,
		"halt_msg" : MAG"$N心神一动，将内息压回丹田，双臂一振站了起来。\n"NOR,
		"end_my_msg" : MAG"你将内息走满一个周天，只感到全身通泰，丹田中暖烘烘的，双手一分，缓缓站了起来。\n"NOR,
		"end_other_msg" : MAG""+me->name()+"脸上紫气退了下去，站了起来。\n"NOR
	]);
}

int ob_hit(object ob, object me, int damage)
{
    int m_zxg,t_force,i;
    m_zxg = random((int)me->query_skill("zixia-gong",1));
    t_force = (int)ob->query_skill("force",1);

    if((int)me->query_skill("zixia-gong",1)>=300)
    if(me->query("env/紫霞神功")=="护体" && me->query_temp("zxg/zixia")){
        if(m_zxg > t_force*4/5 && !random(5)){
            i = - damage;
            message_vision(MAG"$N的紫霞神功依然入化境，$n刚一击中$N,$N脸上便紫气大盛，紫霞护体真气随意而起，"+
                "$n这招根本就没对$N造成任何伤害！\n"NOR,me,ob);
            me->add("neili",-800);
            return i;
        }
        else if(m_zxg > t_force*4/5){
            i = - damage/2 - random(damage/2);
            message_vision(MAG"$N微微一笑，紫霞神功随心而发，$n这招已然被$N化解了绝大半的攻击！\n"NOR,me,ob);
            me->add("neili",-600);
            return i;
        }
        else if(m_zxg > t_force/2){
            i = - damage/2;
            message_vision(MAG"$N当下催了数道紫霞内劲，登时将$n的攻势化去了一半!\n"NOR,me,ob);
            me->add("neili",-400);
            return i;
        }
        else if(m_zxg > t_force/3){
            i = - damage/3;
            message_vision(MAG"$N见$n来势凶猛异常，心下大惊，立即运起紫霞神功御敌，化解了$n的部分攻势!\n"NOR,me,ob);
            me->add("neili",-300);
            return i;
        }
        else{
            i = - damage/4 - random(damage/4);
            message_vision(MAG"$N立即催动紫霞神功，终于化解$n的一点攻击，心下不经骇然!\n"NOR,me,ob);
            me->add("neili",-150);
            return i;
        }
    }
    return 0;
}
