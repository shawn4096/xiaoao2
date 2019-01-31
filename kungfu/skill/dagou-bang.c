// dagou-bang.c 打狗棒法
// Code By Looklove@SJ 2001/4/1
// Modify By Looklove 2001.4.7
// Modify By Looklove 2001.4.8
// Looklove modified at 2001.5.5
// Looklove modified at 2001.5.15
// Looklove modified at 2001.5.18
//update by jpei 2010 增加死亡次数对棒决的威力。

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
        "action": "$N一声轻吟，挥起$w，使出一式「打草惊蛇」，猛扫向$n的$l",
        "force": 80,
        "lvl" : 0,
        "skill_name": "打草惊蛇",
        "damage_type": "挫伤"
]),
([
        "action": "$N步伐跳跃，手中$w左右晃动，一招「拨草寻蛇」向$n的$l攻去",
        "force": 100,
        "lvl":10,
        "skill_name": "拨草寻蛇",
        "damage_type": "内伤"
]),
([
        "action": "$N手中$w一圈，使出一招「关门打狗」将$n四面八方围个密不透风",
        "force": 140,
        "lvl" : 20,
        "skill_name": "关门打狗",
        "damage_type": "淤伤"
]),

([
        "action": "$N步踏坤位，施出「拨狗朝天」，反手将$w由下往上向$n撩去",
        "force": 160,
        "lvl" : 30,
        "skill_name": "拨狗朝天",
        "damage_type": "挫伤"
]),
([
        "action": "$N大喝一声「狗急跳墙」！抢上一步，将$w劈头抡向$n的$l",
        "force": 180,
        "lvl" : 50,
        "skill_name": "狗急跳墙",
        "damage_type": "挫伤"
]),
([
        "action": "$N使出一招「棒打双犬」，手中$w化作两道青光砸向$n的$l",
        "force": 200,
        "lvl" : 80,
        "skill_name": "棒打双犬",
        "damage_type": "挫伤"
]),
([
        "action": "$N手腕一翻，一招「恶犬拦路」，将手中$w向$n的去势封了过去",
        "force": 220,
        "lvl" : 100,
        "skill_name": "恶犬拦路",
        "damage_type": "挫伤"
]),
([
        "action": "$N一招「棒打狗头」，只见$w突然飞起，直击$n的顶门",
        "force": 240,
        "lvl" : 120,
        "skill_name": "棒打狗头",
        "damage_type": "挫伤"
]),
([
        "action": "只见$N使出一招「斜打狗背」，侧身拧腰，$w斜劈向$n的$l",
        "force": 260,
        "lvl" : 140,
        "skill_name": "斜打狗背",
        "damage_type": "挫伤"
]),
([
        "action": "$N灵机一动，使出一招「反截狗臀」，反手将$w戳向$n的$l",
        "force": 270,
        "lvl" : 160,
        "skill_name": "反截狗臀",
        "damage_type": "挫伤"
]),
([
        "action": "$N一招「打狗入洞」，将$w舞了个棒花，横扫$n的$l",
        "force": 280,
        "lvl" : 180,
        "skill_name": "打狗入洞",
        "damage_type": "挫伤"
]),
([
        "action": "$N反身错步，手中$w一幌，使一招「压肩狗背」，夹头夹脸打向$n的$l",
        "force": 300,
        "lvl" : 200,
        "skill_name": "压肩狗背",
        "damage_type": "内伤"
]),
});

int valid_enable(string usage) { return (usage == "stick") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((string)me->query("family/master_name")!="洪七公")
                return notify_fail("打狗棒只能从洪七公处学到。\n");
		//if (!me->query("quest/gb/dgb/pass"))
               // return notify_fail("你只是听说过打狗棒，但从未受过传授。\n");
        if ((int)me->query_skill("stick", 1) < 20)
                return notify_fail("你的基本棒法太差, 还领会不了打狗棒法。\n");

        if (me->query("gender") == "无性")
                return notify_fail("你一个不男不女之人如何能学打狗棒？\n");

        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力不够。\n");
        return 1;
}

string query_skill_name(int level)
{
        int i = sizeof(action);
        while (i--)
                if(level > action[i]["lvl"])
                return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, j, level, glvl, d, p;
        string msg;

        d = (int)me->query_dex() * (random(4)+1);
        p = (int)me->query_int() * (random(2)+2);
		level = me->query_skill("dagou-bang", 1);
		weapon = me->query_temp("weapon");

		if (me->query("gender")=="女性") glvl = level/3;
		else glvl = level/6; 
		
		//if (glvl > 100) glvl = 100;

		//天下无狗六招
		if( me->query_temp("dgb/wugou")){
                switch((int)me->query_temp("dgb/wugou"))
				{
					case 6: msg = HIR"$N施展出「天下无狗」第六变，只见"+ weapon->name() +HIR"招招不离$n的脑门，漫天棒影劈天盖地般打来"NOR; break;
					case 5: msg = HIB"只见漫天棒影骤然一停，$N将「天下无狗」第五变使出，脚在"+ weapon->name() +HIB"一端一踢，"+ weapon->name() +HIB"突然倒飞向$n的丹田穴戳来"NOR; break;
					case 4: msg = HIG"$N使出「天下无狗」第四变，将"+ weapon->name() +HIG"双手握住，陡然间戳向$n的眼睛，在$n下意识躲避间，一掌拍向小腹"NOR; break;
					case 3: msg = HIW"$N闪身后跳，反身使出「天下无狗」第三变，手中"+ weapon->name() +HIW"猛扫向$n的脚踝，连绵不绝，如影随形"NOR; break;
					case 2: msg = HIY"忽然$N急走数步，回身"+ weapon->name() +HIY"斜劈，使出「天下无狗」第二变，在地上啪啪啪连点数下，借助反弹之力忽然弹向$n的后背督脉大穴"NOR;break;
					case 1: msg = HIC"$N棒走偏峰，忽左忽右，忽前忽后，不见风声，只见棒影霍霍，将"+ weapon->name() +HIC"舞成满天棒影，竟然使的是「天下无狗」第一变的招式"NOR; break;
					default: msg = HIC"$N棒走偏峰，将"+ weapon->name() +HIC"舞成满天棒影，竟然使的是「天下无狗」的诸般变化"NOR; break;
                }
                me->add_temp("dgb/wugou", -1);
                return ([
					"action": msg,
					"dodge":me->query("gender")=="女性"?level/10+d:level/15+d/2,
					"parry": glvl/2+p/2,
					"damage": me->query("gender")=="女性"?glvl/2+p/2:glvl/4+p/4,
					"force" : me->query("gender")=="女性"?action[j]["force"]:action[j]["force"]*3/2,
					"lvl" : action[j]["lvl"],
					"damage_type" : action[j]["damage_type"],
                ]);
        }
		//双绝
        if( me->query_temp("shuangjue/dgb")){
                switch((int)me->query_temp("shuangjue/dgb")){
                        case 2: msg = HIG"$N忽然斜挪一步，眼中灵光一闪，手中$w"HIG"横扫向$n的$l"NOR; break;
                        case 1: msg =  HIW"$N招数突变，忽然跃起，只见$w"HIW"化作一团棒影直向$n的$l打去"NOR;break;
                        default: msg = HIW"$N晃身错步，猛然一声长啸，舞起漫天棒影攻向$n的$l"NOR; break;
                }
                me->add_temp("shuangjue/dgb", -1);
                return ([
                "action": msg,
                "dodge": glvl,
                "parry": p+d,
                "damage": glvl + p/2,
                "force": level+glvl+p,
                "damage_type": "挫伤"
                ]);
        }


//寻常攻击
        for(i = sizeof(action); i > 0; i--)
		{
            if(level >= action[i-1]["lvl"]) 
				j = NewRandom(i, 20, level/5);
                       
                
			if (level > 450 && userp(me))
			{
				 return ([
                        "action" : action[j]["action"],
                        "dodge":(d+p)/2,
                        "parry": glvl/2+(p+d)/2,
                        "damage": glvl/4+(p+d)/2,
                        "force" : action[j]["force"]+glvl/2+p+d,
                        "lvl" : action[j]["lvl"],
                        "damage_type" : action[j]["damage_type"],
                        ]);
			}else {
				return ([
                "action" : action[j]["action"],
                "dodge":me->query("gender")=="女性"?level/10+d:level/15+d/2,
                "parry": glvl/2+p/2,
                "damage": me->query("gender")=="女性"?glvl/2+p/2:glvl/4+p/4,
                "force" : me->query("gender")=="女性"?action[j]["force"]:action[j]["force"]*3/2,
                "lvl" : action[j]["lvl"],
               "damage_type" : action[j]["damage_type"],
				]);
			}
		}
}

int practice_skill(object me)
{
        object weapon;
        int lvl = me->query_skill("dagou-bang", 1);
        int i = sizeof(action);

        while (i--) if (lvl == action[i]["lvl"]) return 0;

        if (!objectp(weapon = me->query_temp("weapon"))
         ||(string)weapon->query("skill_type") != "stick")
                return notify_fail("你使用的武器不对。\n");

        if( me->query("gender") == "无性")
                return notify_fail("你一个不男不女之人如何能练打狗棒？\n");

        if ((int)me->query("jingli") < 40)
                return notify_fail("你的精力不够练打狗棒法。\n");

        if ((int)me->query("neili") < 30)
                return notify_fail("你的内力不够练打狗棒。\n");

        me->receive_damage("jingli",40);
        me->add("neili", -5);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"dagou-bang/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int b, x, p, level, damage, quest;
	object weapon, tweapon;
	string msg;

	quest = (int)me->query("dgb/wugou");
	//取消death 关联
	//b = me->query_skill("bangjue", 1) + me->query("death_times",1) ;
	b = me->query_skill("bangjue", 1) ;

	level = me->query_skill("dagou-bang", 1);
	weapon = me->query_temp("weapon");
	tweapon = victim->query_temp("weapon");

	if (me->query_skill_mapped("parry") != "dagou-bang") return 0;
	if (!me->is_fighting(victim) || !weapon || !userp(me)) return 0;
	if ( !living(me) || !living(victim)) return 0;
	//if ( damage_bonus < 100 ) return 0;
	//if ( damage_bonus > 300 ) damage_bonus = 300;

	//打狗棒口诀 1/5概率,造成牵制和辅助伤害
	if ( random(b) >= 100
	 && random(level) > 100
	 &&	!me->query("quest/gb/dgb/bangjue/pass")
	 && random((int)me->query("neili")) > 400
	 && (int)me->query("max_neili") >= 1200
	 && random(20) > 15 )
	{
		victim->add_busy(1);
		damage = damage_bonus/10 + random(damage_bonus)/10*level/40;
		if (!random(2))
		{
			msg = MAG"紧跟着$N朗声诵道：「狗急跳墙如何打？ 快击狗臀劈狗尾。」，随之向$n下盘接连攻出数招。\n";
			msg += "$n叫声不好，不及回身招架，向前窜跃趋避，岂知$N的点打连绵不断，$n一个疏神，连连中招!\n"NOR;
			victim->receive_damage("qi",damage/2,me);
			victim->recieve_wound("qi",damage/4,me);
			p = (int)victim->query("qi")*100/(int)victim->query("max_qi");
			msg += COMBAT_D->damage_msg(damage, "劈伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
			message_vision(msg, me, victim);
		}
		else {
			msg = YEL"$N悄声念道：「棒回掠地施妙手 ，横打双犬莫回头。」, 随之棒影横掠而下，$n躲闪不及连中几下。\n"NOR;
			victim->receive_damage("qi",damage/3,me);
			victim->receive_wound("qi", damage/6,me);
                        p = (int)victim->query("qi")*100/(int)victim->query("max_qi");
                        msg += COMBAT_D->damage_msg(damage, "劈伤");
                        msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
			message_vision(msg, me, victim);
        }
		me->add("neili", -100);
		
	}
	//绊，劈，戳、挑，引，转
	//write(HIC"巫师测试数值damage="+damage_bonus+"\n"NOR);
	if (random(10)<5) return 0;

	switch (random(5))
	{
		case 0:
			message_vision(HBRED+HIW"$N使出打狗棒法「劈字诀」，挥舞起手中"+weapon->query("name")+HBRED+HIW"如狂风暴雨般的向$n劈头盖脸打去！\n"NOR,me,victim);
			if (random(me->query("combat_exp"))>victim->query("combat_exp")/3)
			{
				message_vision(CYN"$n经验显然不足，躲闪不及，为"+weapon->query("name")+CYN"所劈中前胸！\n"NOR,me,victim);
				victim->receive_damage("qi",damage_bonus,me);
				victim->receive_wound("qi", damage_bonus/2,me);				
			}else {
				message_vision(HIY"$n战斗经验异常丰富，轻微一笑，一个鲤鱼跃龙门，躲过$N这招犀利的杀招！\n"NOR,me,victim);
				me->add_busy(1);
				
			}
			break;
		case 1:
			message_vision(HIY"$N打狗棒法「戳字诀」随手施展，双手握住"+weapon->query("name")+HIY"幻起一片尖锐的啸声，向$n的后背猛然戳去！！\n"NOR,me,victim);
			if (random(me->query_dex(1))>victim->query_dex()/2)
			{
				message_vision(HIG"$n身法欠缺，躲闪不及，为"+weapon->query("name")+HIG"所戳中后背"+HIR"命门穴"+HIG"，真气立泄！\n"NOR,me,victim);
				victim->receive_damage("qi",damage_bonus,me);
				victim->apply_condition("neishang",2+random(3));	
				victim->apply_condition("no_exert",2);
				victim->add("neili",-damage_bonus);
			}else {
				message_vision(HIR"$n身形闪动，运起轻功躲过$N这招诡异的招式！\n"NOR,me,victim);
				me->add_busy(1);				
			}
			break;
		case 2:
			message_vision(WHT"$N使出打狗棒法「缠字诀」，手中"+weapon->query("name")+WHT"宛如一条灵蛇般的灵动异常，攻势诡异！\n"NOR,me,victim);
			if (random(me->query_skill("dagou-bang",1))>victim->query_skill("parry",1)/2)
			{
				message_vision(HIY"$n忽觉自己前后左右均为一片棍影所笼罩，顿时有些手足无措起来！\n"NOR,me,victim);
				victim->add_busy(2+random(2));
			}else {
				message_vision(HIY"$n功力流转不息，招式化繁为简，轻轻化解了$N的攻击！\n"NOR,me,victim);
				me->add_busy(1);
				
			}
			break;
			case 2:
		case 3:
			message_vision(HIG"$N使出打狗棒法「转字诀」，手中"+weapon->query("name")+HIG"附着在$n前后左右，如跗骨之蛆，招招不离$n的前后大穴！\n"NOR,me,victim);
			if (random(me->query_skill("staff",1))>victim->query_skill("dodge",1)/2)
			{
				message_vision(CYN"$n急忙不断向左转向右转，试图躲避，但"+weapon->query("name")+CYN"如影随形，$n转了几个圈后忽然间有些头晕目眩起来！\n"NOR,me,victim);
				victim->add_busy(2+random(2));
				victim->receive_damage("jing",damage_bonus/3,me);
				victim->receive_damage("jingli",damage_bonus/6,me);
			}else {
				message_vision(CYN"$n轻功发动，躲闪趋避间化解了$N的攻击！\n"NOR,me,victim);
				me->add_busy(1);
				
			}
			break;
		case 4:
			if (!tweapon) break;
			
			message_vision(HIM"$N使出打狗棒法「挑字诀」，手中"+weapon->query("name")+HIM"附着在$n的"+tweapon->query("name")+HIM"之上，$n立即觉得沉重无比！\n"NOR,me,victim);
			if (random(me->query_str())>victim->query_str()/2)
			{
				message_vision(HIW"$n手中越来越沉，越来越不受控制，手中"+tweapon->query("name")+HIW"被$N所挑飞，脱手而出！\n"NOR,me,victim);
				victim->add_busy(2+random(2));
				tweapon->move(environment(victim));
			}else {
				message_vision(HIY"$n劲力运使于双臂之间，紧紧握住自己的"+tweapon->query("name")+"不被挑飞！\n"NOR,me,victim);
				me->add_busy(1);
				
			}
			break;
	
	}
	return 1;
}

int ob_hit(object ob, object me, int damage)
{
	object wp,twp;
	string msg;
	int j, p, bj, level;
	if (!me||!ob) return 0;
	
	wp = me->query_temp("weapon");
	twp = ob->query_temp("weapon");
	level = (int)me->query_skill("dagou-bang",1);
	//取消death 关联
	//bj = me->query_skill("bangjue",1) + me->query("death_times",1);
	if (level<500) return 0;
	//没开棒诀则不出
	if (me->query("quest/gb/dgb/bangjue/pass")) return 0;
	
	if (!wp ||wp->query("skill_type") != "stick") return 0;
	if (me->query_skill_mapped("stick")!="dagou-bang"||me->query_skill_mapped("parry") != "dagou-bang") return 0;
	
	//封是反击类,引

	bj= me->query_skill("bangjue",1);
	
	if(random(level) > 100
	 && random(bj) > 100
	 && (int)me->query("neili") > 500
	 && random(level)> (int)ob->query_skill("parry",1)/2
	 && random(20) > 15) 
	{
		me->add("neili", -50);
		if(twp) {
			msg = HIM"$n"+ twp->name() +HIM"一招甫出，但见$N使个「封字诀」，棒影飘飘，登时将自己\n"NOR;
			msg += HIM"身前数尺之地尽数封住了。$n见方才攻势失效，无奈之下，只有后退一步，静观变化。\n"NOR;
			
			if(!ob->is_busy())
			{
				ob->add_busy(1);
				me->add("neili",-70);
				ob->apply_condition("no_perform",2);
			}
			
			me->add("neili",-40);
			j = -damage;
		}
		else {
			msg = HIM"$n的手指刚要碰到$N手腕，突然只见青影闪动，"NOR;
			msg += HIM""+wp->name() +HIM "一势「封字诀」，来势神妙无方，\n"NOR;
			msg += HIM"手腕已被重重地敲了一下。$n慌忙后退两步，变色斜睨，背上惊出了一阵冷汗。\n"NOR;
			
			ob->add_busy(1);
			me->add("neili",-50);
			
			if (ob->query("max_qi")<damage) damage=ob->query("max_qi");//防止反击太强 by renlai
			
			ob->receive_damage("qi", damage/3, me);
			ob->receive_wound("qi", damage/6, me);
			p = (int)ob->query("qi")*100/(int)ob->query("max_qi");
			msg += COMBAT_D->damage_msg(damage, "劈伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
			me->add("neili",-100);
			j = -damage/2;
		}
		
		message_vision(msg, me, ob);
		return j;
	}else if (random(me->query_int())>ob->query_int()/2)
	{
		//引字诀，让对方自己攻击
		
			message_vision(HIY"$N微微一笑，手中的"+wp->query("name")+HIY"顺势搭在$n的腕上，$n只觉一股大力传来，身子不由自主地为$N所控制！\n"NOR,me,ob);
			message_vision(HIY"$N这招正是闻名江湖的打狗棒法「"HIC"引字诀"HIY"」$n的身形完全不受自己控制，为$N忽左忽右，忽前忽后！\n"NOR,me,ob);
			message_vision(HIG"忽然间$N的"+wp->query("name")+HIG"劲力极为奇巧的反压$n手臂，$n方才这一招顿时打在自己身上！\n"NOR,me,ob);
			ob->set_temp("must_be_hit",1);
			//ob->add_temp("apply/damage",200);				
			COMBAT_D->do_attack(ob, ob, me->query_temp("weapon"), 3);
			//ob->add_temp("apply/damage",-200);
			ob->delete_temp("must_be_hit");
			return 0;
	}
}

int help(object me)
{
        write(HIG"\n打狗棒："NOR"\n");
        write(@HELP
        打狗棒共有绊、劈、缠、戳、挑、引、封、转八诀，是闻名天下的
        丐帮镇帮绝技。以轻、灵、奇、巧诸称，舞将起来是四处只见棒影
        不见人影。武学中有言道：“四两拨千斤”，乃打狗棒法的精妙招
        数精髓体现。修习时如不同时学习棒诀，终将无法大成。

HELP
        );
        return 1;
}

