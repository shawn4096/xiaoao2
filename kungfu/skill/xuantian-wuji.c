// xuantian-wuji 玄天无极功
// by augx@sj  8/28/2001

#include <ansi.h>

inherit FORCE;
#include "/kungfu/skill/force.h"

int valid_enable(string usage)
{
	return usage == "force";
}

int valid_learn(object me)
{
	int na, nf, nx;
	nf = (int)me->query_skill("force", 1);
	na = (int)me->query_skill("art", 1);
	nx = (int)me->query_skill("xuantian-wuji", 1);

	if ( nf < 20)
		return notify_fail("你的基本内功火候还不够，无法领会玄天无极功。\n");

	if ( me->query("gender") == "无性")
		return notify_fail("你无根无性，阴阳不调，难以领会高深的玄天无极功。\n");

	if ( me->query("family/master_name") == "何足道" ) {
		if ( na < 120 && na <= nx )
			return notify_fail("你的琴棋书画造诣太浅，无法配合玄天无极功的修为。\n");
	}

	if ((int)me->query_skill("xuantian-wuji", 1) > me->query_skill("force", 1) + 10
	 && me->query_skill("xuantian-wuji", 1) >= 200 )
		return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

	return valid_public(me);
}

int practice_skill(object me)
{
	if((int)me->query_skill("xuantian-wuji", 1) >= 200 ) {
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200) {
			me->improve_skill("xuantian-wuji", (int)me->query_int());
			me->add("neili", -100);
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("你现在的修为不足以提高玄天无极功了。\n");
	}
	else return notify_fail("玄天无极功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return __DIR__"xuantian-wuji/" + func;
}

int ob_hit(object ob, object me, int damage)
{
	int i, j, lvl, jing, cur = 0;
	lvl = me->query_skill("xuantian-wuji",1);
	if( lvl > 500 ) lvl = 500;
	
	if (me->query_temp("txwh/taxue") > 0 ) {
		if (me->query_skill_mapped("dodge") == "taxue-wuhen"
		 && me->is_busy()
		 && !random(3)) {
			message_vision(CYN"$n的招式击中$N，只感觉象打在棉花中，无法使足力道。\n"NOR, me,ob);
			cur = damage/2;
		}
	}

/*	// 保留以前的 riyue

	if (me->query_temp("xtwj/riyue") > 0 ) {
		i = 0;
		lvl = me->query_skill("xuantian-wuji",1);
		if(lvl>350) lvl = 350;
		if (me->query("neili")>100) {
			i = damage * (23 - lvl*2/100)/10;
			if( lvl>400 ) i = i * 6/7;
			jing = i / 3;
			if( (me->query("jing")-100) < jing ) jing = 0;
			me->add("jing",-jing);
			me->add("neili",-(i-jing));
			if(me->query("neili")<0) me->set("neili",0);

			if(wizardp(me) && me->query("env/test"))
				tell_object(me,sprintf("d:%d, n:%d, j:%d ",damage,i-jing,jing));
			message_vision(MAG"$n的招式被$N身前的无极气墙所阻挡，根本不能对$N造成任何伤害。\n"NOR, me,ob);
			i = damage;
		}
*/

	

	if( me->query_temp("xtwj/riyue") > 0 && me->query("neili") > lvl ) {

		if( damage < 1000 && !userp(ob) && !random(3)) { // 伤害很小，没必要判断
			me->add("neili", -(random(60)+20));
			message_vision(MAG"$n的招式被$N身前的无极气墙所阻挡，根本不能对$N造成任何伤害。\n"NOR, me,ob);
			i = damage;
		}

	else if( random(me->query_con()) > ob->query_str()*2/3 && random(2) ) { // 判断化解的比率
	
			if( damage > lvl*3 ) { // 如果伤害过大，最多只能化解 lvl 3 倍的伤害
				i = lvl*3 * (23 - lvl*2/100)/15;
				if( lvl > 400 ) i = i * 4/5;
				jing = i/4; // 精只能代替 1/4 的消耗
				if( (me->query("jing")-100) < jing ) jing = 0;
				me->add("jing", -jing);
				me->add("neili", -(i-jing));
				if( me->query("neili") < 0 ) me->set("neili",0);
				if( wizardp(me) && me->query("env/test") )
					tell_object(me,sprintf("-damage lvl*3, d:%d, n:%d, j:%d ",damage,i-jing,jing));
				message_vision(MAG"$n的招式击在$N身前的无极气墙上，被化去了部分的劲力。\n"NOR, me,ob);
				i = lvl*3;
			}			
			else { // 伤害小于 lvl 3 倍的话，全部化解
				i = damage * (23 - lvl*2/100)/15;
				if( lvl > 400 ) i = i * 4/5;
				jing = i/4; // 精只能代替 1/4 的消耗
				if( (me->query("jing")-100) < jing ) jing = 0;
				me->add("jing", -jing);
				me->add("neili", -(i-jing));
				if( me->query("neili") < 0 ) me->set("neili",0);
				if( wizardp(me) && me->query("env/test") )
					tell_object(me,sprintf("d:%d, n:%d, j:%d ",damage,i-jing,jing));
				message_vision(MAG"$n的招式被$N身前的无极气墙所阻挡，根本不能对$N造成任何伤害。\n"NOR, me,ob);
				i = damage;
			}

		}

	else { // 随机化解对手造成的部分伤害
			j = 3 + random(4);
			i = damage/j * (23 - lvl*2/100)/15; // 消耗内力减少
			if( lvl > 400 ) i = i * 4/5;
			jing = i/3; // 精可以代替 1/3 的消耗
			if( (me->query("jing")-100) < jing ) jing = 0;
			me->add("jing", -jing / 10);
			me->add("neili", -(i-jing));
			if( me->query("neili") < 0 ) me->set("neili",0);
			if( wizardp(me) && me->query("env/test") )
				tell_object(me,sprintf("-damage/"+j+", d:%d, n:%d, j:%d ",damage,i-jing,jing));
			message_vision(MAG"$n的招式犀利无比，$N身前的无极气墙根本不能完全阻挡$n的攻击。\n"NOR, me,ob);
			i = damage/j;
		}
		

		if( me->query("neili") <= lvl ) {
			message_vision(MAG"\n$N身前的气墙逐渐缩小，终于消失于无形。\n\n"NOR,me);
			me->delete_temp("xtwj/riyue");
		}
		cur += i;
	}
	return -cur;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIC + me->name()+HIC"周身被一股飘渺的无极真气包围着。" NOR,
		"start_my_msg" : "你运起玄天无极神功，气聚丹田，一股真气在四肢百脉中流动。\n",
		"start_other_msg" : me->name()+"运起玄天无极神功，气聚丹田，一股真气在四肢百脉中流动。\n",
		"halt_msg" : "$N匆匆将内息退了回去，吸一口气缓缓站了起来。\n",
		"end_my_msg" : "过了片刻，你感觉自己已经将玄天无极神功气聚丹田，深吸口气站了起来。\n",
		"end_other_msg" : "过了片刻，"+me->name()+"感觉其已经将玄天无极神功气聚丹田，深吸口气站了起来。\n",
		"heal_msg" : HIW"$N盘膝坐下，蓦然想起"HIC"百鸟朝凤"HIW"的琴音在耳边游走飘荡，实以柔和的音律调理伤势。\n"NOR,
		"heal_finish_msg" : HIW"过了良久，琴音顿止，$N蓦觉一股清幽安宁的感觉遍透全身。\n"NOR,
		"heal_unfinish_msg" : HIR"过了一会，$N头晕脑涨，热血上涌，骤觉这伤势，非浅薄的琴音所能调理。\n"NOR,
		"heal_halt_msg" : HIW"突然间琴音在脑海中止歇，$N便即惊醒，深吸了一口气，站起身来。\n"NOR,
	]);
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
	int j, k,damage;
	object weapon;
	weapon=me->query_temp("weapon");
	
	j = me->query_skill("art", 1);
	k = me->query_skill("xuantian-wuji",1);
    // && !me->query_temp("yxj_qimen")
	// && !me->query_temp("thd/feiying")
	//if (me->query_skill_mapped("sword")!="liangyi-jian") return;
	
 
	//琴剑双绝
	damage = me->query_skill("liangyi-jian",1) + me->query_skill("art",1)+(int)me->query_skill("xuantian-wuji", 1)*2+(int)me->query_skill("liangyi-jue", 1)*2;
	damage = damage +random(damage);
	damage *= 2;			
	if (damage>3500) damage = 3500;

	if( random(10) >= 5 
		&& random(j) > 150
		&& k > 450
		&& me->query_skill_mapped("sword")=="liangyi-jian"	
		&& me->query_skill_mapped("parry")=="liangyi-jian"	
		&& objectp(weapon) 
		&& me->query_temp("xtwj/riyue")
		&& weapon->query("skill_type") == "sword"
		&& me->query_temp("xtwj/qinjian"))
	{
		
		message_vision(HIC"$N右手微微轻挑琴弦，仙翁一声，琴音大盛！\n同时左手运剑如风，剑如车轮，虽然没有进退趋变之形，但却极为凌厉，剑气弥漫！\n\n"NOR, me, victim );

		if( random(me->query_skill("force",1)) > victim->query_skill("force",1)/2 
			|| victim->is_busy())
		{        
			message_vision( HIY "$n一时不查，为琴音所干扰，茫然中身形不由地一滞,手上的力道一松！\n\n"NOR, me, victim );
			victim->add_busy(2);
			victim->add_condition("no_exert",1);
			victim->set("jiali",0);
			message_vision( RED "$n手忙脚乱中躲闪不及，已经被飞散的剑气击中，几个小孔鲜血如注！\n\n"NOR, me, victim );

            victim->receive_damage("jing", random( damage/2 ),me);
            victim->receive_damage("qi", 20 + random(damage),me);
            victim->receive_wound("qi", 20 + damage,me);
            
                
        }
		else if( random(me->query_int()) > victim->query_int()/2 || victim->is_busy())
		{
 
          message_vision( BBLU+HIW "$N将玄天无极发挥到及至，"HIG"五韵七弦"BBLU+HIW"剑气激射而出，此时手中无剑亦有剑！\n\n"
						+ NOR + RED"$n惨叫一声，身上已经被无形剑气击中！\n"NOR, me, victim );
 
                        damage *= 2;
                        victim->receive_wound("jing", random( damage/2 ),me);
                        victim->receive_damage("qi", 20 + random(damage),me);
                        victim->receive_wound("qi", 20 + damage,me);
                        victim->add_condition("no_perform",1);
         }
	}
	
	

            
}