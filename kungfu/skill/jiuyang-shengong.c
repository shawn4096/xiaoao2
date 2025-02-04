// jiuyang-shengong.c 九阳神功

#include <ansi.h>


inherit FORCE;
#include <combat_msg.h>
//int get_bouns(int damage,int t,int level,int flag);
//int hit_ob(object me,object victim,int damage);
int valid_enable(string usage)
{
	if (this_player()->query("jiuyang/read"))
		return usage == "force";
}

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
	if( !me->query("jiuyang/read"))
		return notify_fail("九阳神功只能通过读全部四册的《九阳真经》来提高。\n");

	if( me->query_skill("jiuyang-shengong", 1) < 220)
		return notify_fail("你现在只能通过读全部四册的《九阳真经》来提高九阳神功。\n");

	if ((int)me->query_skill("jiuyang-shengong", 1) > me->query_skill("force", 1) + 10
	 && me->query_skill("jiuyang-shengong", 1) >= 220 )
               return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

	return 1;
}

int practice_skill(object me)
{
	if((int)me->query_skill("jiuyang-shengong", 1) >= 220 ){
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200){
			me->improve_skill("jiuyang-shengong", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("你现在的修为不足以提高九阳神功。\n");       
	}
	return notify_fail("九阳神功只能通过读全部四册的《九阳真经》来提高。\n");
}

string exert_function_file(string func)
{
	return __DIR__"jiuyang-shengong/" + func;
}

void skill_improved(object me)
{
	int i =2 +random(4);
	if( me->query_skill("jiuyang-shengong", 1) > 200
	 && me->query("jiuyang/gift") + 201 < me->query_skill("jiuyang-shengong", 1)){
		if( !me->query("jiuyang/gift"))
			me->set("jiuyang/gift", me->query_skill("jiuyang-shengong", 1) -200);
		else 
			me->add("jiuyang/gift", 1);
		me->add("max_neili", i); 
		tell_object(me,HIW"\n随着九阳神功的提高，你感觉自己内力增加了"+chinese_number(i)+"点。\n"NOR);
	}
}

mapping exercise_msg(object me)
{
	return ([
 		"status_msg" : HIR + me->name()+"呼翕九阳，进入人我两忘之境界" NOR,
 		"start_my_msg" : "你盘膝而坐，运使九阳，气向下沉，由两肩收入脊骨，注于腰间，进入人我两忘之境界。\n",
 		"start_other_msg" : me->name()+"盘膝而坐，运使九阳，气向下沉，由两肩收入脊骨，注于腰间，进入人我两忘之境界。\n",
 		"halt_msg" : "$N周身微微颤动，长出口气，站了起来。\n",
 		"end_my_msg" : "你呼翕九阳，抱一含元，缓缓睁开双眼，只觉得全身真气流动，体内阳气已然充旺之极。\n",
 		"end_other_msg" : "只见"+me->name()+"呼翕九阳，抱一含元，缓缓睁开双眼，只觉得全身真气流动，体内阳气已然充旺之极。\n",
		"heal_msg" : HIR"$N盘膝坐下，依照经中所示的法门调息，只觉丹田中暖烘烘地、活泼泼地，真气流动。\n"NOR,
		"heal_finish_msg" : HIR"九阳神功的威力，这时方才显现出来，在$N体内又运走数转，胸腹之间甚感温暖舒畅。\n"NOR,
		"heal_unfinish_msg" : HIR"$N神态庄严，缓缓站起身来，但脸上血红，看来伤势还没有完全恢复。\n"NOR,
		"heal_halt_msg" : HIR"$N脸颊胀红，头顶热气袅袅上升，猛地吸一口气，挣扎着爬了起来。\n"NOR,
	]);
}
/*  //暂时取消九阳的攻击
string* msgs =
({
        HBRED"$N将九阳真经融会贯通，一拳一脚都带有莫大的力量，$n宛如置身于一个大火炉一样！\n"NOR,
        HBWHT"$N\n"NOR,
        HBMAG"$N又是一口唾沫急吐，竟将痰涎唾沫也当作了攻敌利器，夹在拳招之中使用！\n"NOR, 
        HBWHT"$N蛤蟆功逆转运用，上者下之，左者右之，一掌拍回！\n"NOR,
        HBCYN"$N逆运经脉，更是厉害，一见对方招来，便口吐白沫，举头猛撞！\n"NOR, 

});*/

string *fanzhen_msg = ({
"只震得$n胸内腹中，有如五脏一齐翻转！\n",
"抢先反震，将$n震得脸如白纸，全无血色！\n",
"震得$n心肺欲裂，腾腾腾连退数步！\n",
"功力已布满全身，将$n的力量反震回去！\n",
"震得$n天旋地转，腾腾腾连退七八步！\n",
"和$n一撞，只震的$p胸口气血翻涌！\n",
"$n便如撞在一堵棉花作面，钢铁为里的厚墙上一般，震退数步！\n",
"$n刚碰到$P，突然身子一震，登时飞了出去！\n",
});
/*
int hit_ob(object me,object victim,int damage)
{
	if(!me) return 0;
	if(!environment(me)) return 0;
	if( me->query("env/蛤蟆功")=="逆转" )

	{
		int t;
                t = random(10);
		
            if( t > 6 )
		{
            message_vision(msgs[random(sizeof(msgs))],me);
      //    message_vision(msgs[random(sizeof(msgs))]+"$N经脉逆运，神智不清，出手却是越发凌厉。\n"NOR,me);
			return get_bouns(damage,t,me->query_skill("hamagong",1),1);
		}
	}
	return 0;
}

int get_bouns(int damage,int t,int level,int flag)
{
	int dm;
	dm= (damage*(t+level/20))/(t+level/20+10);
	if(flag && level>350) dm += dm/2;
	return dm;
}
*/
int ob_hit(object ob, object me, int damage)
{
	string msg;
	int p, skill, neili, neili1, i = 1, ap, dp;
	object weapon;
	skill = me->query_skill("jiuyang-shengong", 1);
	neili = me->query("neili") + 1 ;
	neili1 = ob->query("neili") + 1;

	if( skill > 300 ) 
             {
		i += me->query_temp("combat_yield");
	      }

	

     if( living(me)
	&& random(skill) * i + 100 > ob->query_skill("parry", 1)/2
	&& me->query("combat_exp") > ob->query("combat_exp")/2
	&& skill > 199
	&& neili > 500
	&& !me->query("menggu")
	&& living(ob)
	&& !ob->is_visible(me)
        && random(10) > 6 
         ) 
	{
	
		if(!objectp(weapon = ob->query_temp("weapon"))){
			me->add("neili", -(10+random(70)));
			msg = random(2)?HIC"$N默念“他强由他强，清风拂山岗”，九阳神功随心而起，":HIC"$N默念“他横由他横，明月照大江”，九阳神功随心而起，";
			if(neili1 > neili*4*i || random(damage) > (5000 + me->query_con(1) * 40 * i)){
				msg += "但却被$n的劲力一招震碎！\n"NOR;
				if (me->query("mj/jiuyang/pass")>2) //九阳发威
				{
					if (damage>ob->query("max_qi")) damage=ob->query("max_qi")/2;//防止秒杀
					ob->receive_damage("qi",2*damage,me);
				    ob->receive_wound("qi",2*damage,me);
					ob->set_temp("no_exert",1);
				}
				me->delete_temp("fanzhen");
				damage = random(damage/2);
			}
			else if(neili1 > neili*3*i) {
				msg += "但却根本无法阻挡$n的劲力！\n"NOR;
				damage = 0;
			}

			else if(neili1 > neili*3/2*i){
				msg += "结果抵消了部分$n的劲力！\n"NOR;
				damage = -damage/2;
			}
			else{
				msg += fanzhen_msg[random(sizeof(fanzhen_msg))]+NOR;
				p = (neili / neili1) * i;
				if( p < 1) p = 1;
				p *= damage/3;
				if(ob->query_skill("force") > me->query_skill("force")*3/2) p = p*2/3;

				if ( me->is_busy())
					p /= 2;

				if(p < 10) p = 10;
				
				if (p>ob->query("max_qi")) p=ob->query("max_qi")/2;//防止秒杀

				ob->receive_damage("qi", p, me);
				ob->receive_wound("qi", p/5*i, me);

				if(wizardp(me)) tell_object(me, "Fanzhen damage: "+p+"。\n");

				//p = (int)ob->query("qi") * 100 / (int)ob->query("max_qi");
				//msg += "( $n"+eff_status_msg(p)+" )\n";
				damage = -8000+(-damage);
			}
			message_vision(msg, me, ob);
		}
		else{
			msg = HIR"九阳护身真气好似一堵无形的墙在$N面前阻挡着，";
			switch(weapon->query("skill_type")) {
				case "whip"   : p = 10; break;
				case "sword"  : p = 8; break;
				case "hook"   : p = 6; break;
				case "blade"  : p = 5; break;
				case "club"   :
				case "stick"  : p = 2; break;
				case "staff"  :
				case "axe"    :
				case "hammer" : p = 1; break;
				default       : p = 3; break;
			}
			p *= weapon->query("rigidity");

			ap = me->query("combat_exp", 1) / 100 * (me->query("str") + p);
			dp = ob->query("combat_exp", 1) / 100 * (ob->query("str") + p);

			if( random(ap + dp ) > dp && neili*i > neili1*2/3) {
				message_vision(HIR"结果$N身上九阳神功随即反震，$n只觉虎口一热，" + weapon->name() + HIR"差点脱手飞出！\n\n"NOR, me, ob);
				if (me->query("mj/jiuyang/pass")>2) //九阳发威
				{
					ob->receive_damage("qi",2*damage,me);
				    ob->receive_wound("qi",2*damage,me);
					ob->set_temp("no_perform",1);
				}
				ob->add_busy(1+random(2));
				return -8000+(-damage/2);
			}
			else if(neili*i > neili1*2){
				msg += "结果$n"HIR"被九阳真气反震，震得"+ob->name()+HIR"手臂发麻！\n"NOR;
				ob->start_busy(1+random(3));
				damage = -8000+(-damage/2);
			}
			else if(neili*i > neili1*3/2){
				msg += "结果$n"HIR"不能前进一丝一毫！\n"NOR;
				damage = -8000+(-damage/2);
			}
			else if(neili*i > neili1){
				msg += "结果减缓了$n"HIR"前进的速度！\n"NOR;
				damage = -damage*3/2;
			}
			else if(neili*2*i > neili1){
				msg += "但并没有起到什么作用！\n"NOR;
				damage = -damage/4;
			}
			else{
				msg += "但却被$n"HIR"一下打破！\n"NOR;
				me->delete_temp("fanzhen");
				damage = random(damage/2);
			}
			message_vision(msg, me, weapon);
		}
		return damage;
	}
}

