// yinyun-ziqi.c 氤氲紫气

#include <ansi.h>
inherit FORCE;
#include <combat.h>
inherit SKILL;
#include <combat_msg.h>
#include "force.h"
//#include "force1.h"
//内功反震，功力高深时候运用
string *fanzhen_msg = ({
"$n劲力只觉得陷入棉花堆中，$N借势劲力反击，只震得$n胸内五脏六腑一齐翻转！\n",
"$N向后退一步，“缠丝劲”发动，趁借力卸力之际，抢先反震，将$n震得脸如白纸，全无血色！\n",
"太极功力到处，柔劲使出，震得$n心肺欲裂，腾腾腾连退数步！\n",
"$N功力已布满全身，将$n的力量反震回去！\n",
"震得$n天旋地转，腾腾腾连退七八步！\n",
"和$n一撞，只震的$p胸口气血翻涌！\n",
"$n便如撞在一堵棉花作面，钢铁为里的厚墙上一般，震退数步！\n",
"$n刚碰到$P，突然身子一震，登时飞了出去！\n",
});

int get_bouns(int damage,int t,int level,int flag);

int valid_enable(string usage) { return usage == "force"; }
int valid_learn(object me)
{
	int lvl = (int)me->query_skill("yinyun-ziqi", 1);
	int t = 1, j;

	for( j = 1; j < lvl / 10; j++) t *= 2;
	if( t > 5000 ) t = 5000;
	if( me->query("gender") == "无性" && lvl > 49 )
		return notify_fail("你无根无性，阴阳不调，难以领会高深的氤氲紫气神功。\n");

	if( me->query("class") == "bonze" )
		return notify_fail("氤氲紫气讲究阴阳调合，有违佛家六根清净之意，" +RANK_D->query_respect(me)+"欲修此功，已是罪过。\n");

	if( (int)me->query_skill("force", 1) < 15 )
		return notify_fail("你的基本内功火候还不够。\n");

	if( (int)me->query_skill("yinyun-ziqi", 1) > me->query_skill("force", 1) + 10
	&& me->query_skill("yinyun-ziqi", 1) >= 200 )
		return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

	if( (lvl > 10 && lvl < 100 && (int)me->query("shen") < t * 200)
	|| ( lvl >=100 && (int)me->query("shen") < 10000) )
		return notify_fail("你的侠义正气太低了。\n");

	if( me->query("menggu") )
		return notify_fail("你已投降蒙古，无法再进一步提高氤氲紫气。\n");

	return valid_public(me);
}

int practice_skill(object me)
{
	if( (int)me->query_skill("yinyun-ziqi", 1) >= 200 ) {
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200) {
			me->improve_skill("yinyun-ziqi", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("你现在的修为不足以提高氤氲紫气了。\n");
	}
	else return notify_fail("你现在的氤氲紫气修为只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return __DIR__"yinyun-ziqi/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : MAG + me->name()+"头顶氤气蒸蒸，神色威严" NOR,
		"start_my_msg" : "你盘膝而坐，双目紧闭，深深吸一口气引入丹田，慢慢让一股内息在周身大穴流动，渐入忘我之境。\n",
		"start_other_msg" : me->name()+"盘膝坐了下来，双手虚握成拳，不一会，头顶冒出氤氤紫气。\n",
		"halt_msg" : "$N微一簇眉，将内息压回丹田，长出一口气，站了起来。\n",
		"end_my_msg" : "你将内息在体内运行十二周天，返回丹田，只觉得全身暖洋洋的。\n",
		"end_other_msg" : me->name()+"长出一口气，一抖衣襟，站了起来，眼中精光一闪。\n"
	]);
}

int ob_hit(object ob, object me, int damage)
{
    int m_yyzq,t_force,i,t,p;
	string msg;
    m_yyzq = random((int)me->query_skill("yinyun-ziqi",1)+(int)me->query_skill("force",1));
    t_force = (int)ob->query_skill("force",1);
    //set 氤氲紫气 以柔克刚 yun taiji后的临时变量为 yyzq/taiji
    //缠丝劲 化解 卸劲 反震 
    if((int)me->query_skill("yinyun-ziqi",1)>=350)
    {
       if(userp(me)&& me->query_temp("tj/taiji"))
		{
        
		 if (me->query("env/氤氲紫气")=="以柔克刚" )
        {
                me->add("jingli", -50);
				me->add("neili", -100);
                ob->add("jingli", -10);
               	ob->add("neili", -20);
				msg = HIY"只听「啪」的一声，$N和对方内力相触，氤氲紫气以柔克刚「缠丝劲」的功夫显现出来。\n"NOR;
				ob->receive_damage("qi", damage*2,me);
			    ob->receive_wound("qi", damage*2,me);
				ob->start_busy(random(2));
				message_vision(msg, me,ob);
				//damage=call_out(get_bouns(damage,6,me->query_skill("yinyun-ziqi",1),1));
				return -damage;
				
           }	
       /* if (me->query_temp("yinyun")&& random(1))
         {
			    msg += fanzhen_msg[random(sizeof(fanzhen_msg))]+NOR;
			    if(ob->query_skill("force") > me->query_skill("force")*3/2) p = p*2/3;

				if ( me->is_busy())
					p /= 2;

				if(p < 10) p = 10;

				ob->receive_damage("qi", p, me);
				ob->receive_wound("qi", p/5*2, me);
				p = (int)ob->query("qi") * 100 / (int)ob->query("max_qi");
				msg += "( $n"+eff_status_msg(p)+" )\n";
				damage = -8000+(-damage);
                message_vision(msg, me, ob);
				return damage;
        }*/
		if(m_yyzq > t_force*2/5 && !random(3)){
            i = - damage;
            message_vision(WHT"$N的氤氲紫气已入化境，$n刚一击中$N,$N脸上便紫气大盛，护体真气随意而起，"+
                "$n这招根本就没对$N造成任何伤害！\n"NOR,me,ob);
            me->add("neili",-800);
            return i;
        }
        else if(m_yyzq > t_force*3/5){
            i = - damage/2 - random(damage/2);
            message_vision(WHT"$N微微一笑，氤氲紫气随心而发，$n这招已然被$N化解了绝大半的攻击！\n"NOR,me,ob);
            me->add("neili",-600);
            return i;
        }
        else if(m_yyzq > t_force/2){
            i = - damage/2;
            message_vision(WHT"$N当下催了数道紫霞内劲，登时将$n的攻势化去了一半!\n"NOR,me,ob);
            me->add("neili",-400);
            return i;
        }
        else if(m_yyzq > t_force/3){
            i = - damage/3;
            message_vision(WHT"$N见$n来势凶猛异常，心下大惊，立即运起氤氲紫气御敌，化解了$n的部分攻势!\n"NOR,me,ob);
            me->add("neili",-300);
            return i;
        }
        else{
            i = - damage/4 - random(damage/4);
            message_vision(WHT"$N立即催动氤氲紫气，终于化解$n的一点攻击，心下不经骇然!\n"NOR,me,ob);
            me->add("neili",-150);
            return i;
        }

	   }
         
    }
    return 0;
}
/*
int get_bouns(int damage,int t,int level,int flag)
{
	int dm;
	dm= (damage*(t+level/20))/(t+level/20+10);
	if(flag && level>350) dm += dm/2;
	if (falg && level>450) dm += dm/2;
	if (falg && level>550) dm += dm;
	return dm;
}*/