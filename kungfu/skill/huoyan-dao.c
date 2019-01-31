// huoyan-dao.c 火焰刀
// by snowman@SJ

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
	"action" : "$N内息转动，运劲于双臂，全身骨节一阵暴响，起手一式「示诞生」向$n劈出，将$n全身笼罩在赤热的掌风下",
	"skill_name" : "示诞生",
	"lvl" : 0,
	"damage_type" : "瘀伤",
]),
([
	"action" : "$N面带轻笑，一招「始心镜」，火焰刀内劲由内及外慢慢涌出，$P双掌如宝像合十于胸前，向着$n深深一鞠",
	"skill_name" : "始心镜",
	"lvl" : 20,
	"damage_type" : "震伤",
]),
([
	"action" : "$N双掌合十而又打开，这招「现宝莲」以火焰刀无上功力聚出一朵红莲，盛开的花瓣飞舞旋转，漫布在$n四周",
	"skill_name" : "现宝莲",
	"lvl" : 50,
	"weapon" : "红莲刀气",
	"damage_type" : "割伤",
]),
([
	"action" : "$N面带金刚相，双掌搓圆，使无数炙热的刀气相聚，这招「破法执」犹如一只巨大的手掌，凌空向$n飞抓而下",
	"skill_name" : "破法执",
	"lvl" : 70,
	"damage_type" : "内伤",
]),
([
	"action" : "$N暴喝一声，竟然使出伏魔无上的「开显圆」，气浪如飓风般围着$P飞旋，炎流将$n一步步向着$P拉扯过来",
	"skill_name" : "开显圆",
	"lvl" : 120,
	"damage_type" : "震伤",
]),
([
	"action" : "$N口念伏魔真经，双掌连连劈出，将$n笼罩在炙焰之下，这如刀切斧凿般的「显真常」气浪似乎要将$p从中劈开",
	"skill_name" : "显真常",
	"lvl" : 140,
	"weapon" : "无形刀气",
	"damage_type" : "割伤",
]),
([
	"action" : "$N现宝相，结迦兰，右手「归真法」单掌拍出，半空中刀气凝结不散，但发出炙灼的气浪却排山倒海般地涌向$n",
	"skill_name" : "归真法",
	"lvl" : 160,
	"damage_type" : "瘀伤",
]),
([
	"action" : "$N虚托右掌，一式「吉祥逝」，内力运转，跟着全身衣物无风自动，$P身体微倾，手掌闪电一刀，斩向$n$l",
	"skill_name" : "吉祥逝",
	"lvl" : 180,
	"weapon" : "无形气浪",
	"damage_type" : "割伤",
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练火焰刀必须空手。\n");
	if ( me->query("max_neili") < 1500)
		return notify_fail("以你的内力修为，还不足以练习火焰刀。\n");
	if ( me->query_con(1) < 30)
		return notify_fail("你的根骨太低，不能驾御火焰刀。\n");
	if ( me->query_skill("longxiang-boruo", 1) < 100)
		return notify_fail("火焰刀需要有龙象般若功第八层以上的火候才能学习。\n");
	if ( me->query_skill("force") < 100)
		return notify_fail("你的基本内功火候太浅，不能学火焰刀。\n");
	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i,j,k, level, neili, force, jiuyang;
	string msgs;
        
	level   = (int) me->query_skill("qishang-quan", 1);
	jiuyang = me->query_skill("jiuyang-shengong", 1);
	force = me->query_skill("force",1);
	neili = me->query("neili");

	level = (int) me->query_skill("huoyan-dao",1);

// 	添加 pfm ran
	if( me->query_temp("hyd_ran") ) {
		return ([
			"action" : RED"$N猛的运转内功，聚劲于双掌，火焰刀内劲由内及外慢慢涌出，挟著一股炙热的刀气向$n直涌而去！"NOR,
			"force":300+random(250)+me->query_str(),
			"dodge":random(30)-10,
			"damage":200+random(200),
			"parry":random(10)+10,
			"damage_type" : "瘀伤",
		]);
		me->delete_temp("hyd_ran");
	}
//红莲招式
	if( intp(j = me->query_temp("hyd/honglian/power")) && j > 0 ){
		switch(j) {
			//case 5: msgs =HIB"$N一声暴喝，连续出招，双掌不断向$n施压，顿时热浪滔天"NOR; break;
			case 4: msgs =RED"$N轻喧佛号，双掌改斩势为直击，火焰刀气不由大盛，$n已经被如波涛般热浪笼罩"NOR;break;
			case 3: msgs =HIC"$N双掌一收，趁$n深受火焰刀困扰之时，一个转身绕至$n的身后，将手肘击向$n的$l。"NOR ;break;
			case 2: msgs =HIR"$N双手合什，双掌倒成了掌刀，横的一刀斩出，两道火焰刀气合成一鼓向$n冲击"NOR;break;
			case 1: msgs =HIY"$N显然密宗神功大成，体内内息源源不断涌出，双手不停舞动，"HIR"红莲火"HIY"瞬间爆发。"NOR;break;
			default:msgs =HIR"$N将火焰刀气骤然提升，红色掌风带着强烈高温，突然“呼”的一掌斩出，确实威力非凡。"NOR; break;
		}
		if( me->query_temp("hyd/honglian/power") >= 1 )
			me->add_temp("hyd/honglian/power", -1);
		return ([
			"action": msgs,
			"damage_type" : "割伤",
			"dodge": 30+random(30),
			"parry": 30+random(30),
			"force": 250 + random(150),
			"damage": 150 + random(100),
		]);
	    me->delete_temp("hyd/honglian/power");
	}
//碧烟纵横招式
	  if( intp(k = me->query_temp("hyd/zongheng")) && k>0){
		switch(k) {
			case 6: msgs =HBBLU+HIG"$N运起龙象般若功，右掌虚按，左掌斜斜劈出，掌上已蓄积真力，使出的正是「火焰刀」中的一招手刀绝技"NOR; break;
			case 5: msgs =HBBLU+HIG"$N此刻双掌竖起，狠砍狠斫，全是少林派武功的路子。$N一刀劈落，「火焰刀」劲气翻涌，波的一轻响"NOR; break;
			case 4: msgs =HBBLU+HIG"$N运使「火焰刀」绝技，奇妙无方，动念即至，刀气汹涌，两道碧烟忽然卷向$n的$l"NOR;break;
			case 3: msgs =HBBLU+HIG"$N双掌如抱圆球，内力运出，六道碧烟慢慢向外蜿蜒而去，遥遥指着击向$n的诸身大穴"NOR ;break;
			case 2: msgs =HBBLU+HIG"$N连运内功三次强劲，「火焰刀」绝技威力倍增，沛然莫能抵御，绿烟嗤嗤作响，向$n猛烈冲击而去"NOR;break;
			case 1: msgs =HBBLU+HIG"$N运使火焰刀中一招“白虹贯日”，乃招式中精妙之作，一刀便要将向$n的$l砍了下来"NOR;break;
			default:msgs =HBBLU"$N将火焰刀气动念既至的意境施展出来，数股劲力随着碧烟而去，看似缓慢，但却迅捷无比"NOR; break;
		}
		if( me->query_temp("hyd/zongheng") > 0 )
			me->add_temp("hyd/zongheng", -1);
		return ([
			"action": msgs,
			"damage_type" : "割伤",
			"dodge": 30+random(30),
			"parry": 30+random(30),
			"force": 250 + random(350),
			"damage": 180 + random(100),
		]);
		
	}
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"weapon": action[j]["weapon"],
				"force":250+random(350),
				"dodge":random(30)-10,
				"parry":random(20),
				"damage":100+random(50),
			]);
		}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("huoyan-dao", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;
	if ( me->query("jingli") < 50 || (int)me->query("neili") < 20)
		return notify_fail("你的体力不够，练不了火焰刀。\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"huoyan-dao/" + action;
}

int ob_hit(object ob, object me, int damage)
{
	string msg;
	int j, skill, neili, neili1;

	skill = me->query_skill("huoyan-dao", 1);
	neili = me->query("neili");
	neili1 = ob->query("neili");

	if( me->query_temp("fanzhen")) {
		me->delete_temp("fanzhen");
		return 1;
	}
    
	if( random(skill) > ob->query_skill("parry", 1)/2
	&& me->query("combat_exp") > ob->query("combat_exp")/2
	&& me->query_skill_mapped("parry") == "huoyan-dao"
	&& me->query_skill("longxiang-boruo", 1) > 450  //大飞后方有反击
	&& neili > 1000 
	&& skill > 450 
	&& random(neili) > random(neili1)/2
	&& living(me)
    && !random(3)
	&& !me->query_temp("weapon")
	&& !ob->query_temp("weapon")
	&& !ob->is_visible(me)) {       
		if( me->query_temp("dazhuan_npc") ) neili += neili/2;

		msg = HBRED"只听得$N身前龙象般若功劲气鼓荡，气劲带动空气嗤嗤声响，「火焰刀」威势大盛，\n"NOR;            
		if (me->query("lx/gree")>10) me->set_temp("fanzhen", 1);
	    if (random(me->query_str(1))>ob->query_dex(1)/2 && me->query("lx/gree")>10 )
           { 
		      msg += YEL "$N这一掌上可同时生出数股力道，即便$n如何奋力进攻，$N也尽能反击回去！\n"NOR;
			  ob->receive_damage("qi",skill*3+random(skill),me);
			  ob->receive_wound("qi",skill,me);
			  //ob->set_temp("lost_fight",3);              
	         // message_vision(msg, me, target);
		}
		else if ( neili >= neili1+random(neili1)+damage*2&& skill >449 ){
			msg += HIY"$N龙象般若功随心而起，将$n招式上的内力抵消化解于无！\n"NOR, 
			j = -damage;
		}
		else if(neili >= neili1+damage) {
			msg += HIY"$P手掌扬处，以火焰刀劲力削弱了$n攻来的内力！\n"NOR, 
			j = -(damage/2+random(damage/2));               
		}
		else {
			msg += HIY"$P火焰刀法劲气涌动，抵挡住了一些$n的攻击！\n"NOR, 
			j = -damage/3; 
		}
		if ( wizardp(me)) tell_object(me, "Target damage = "+damage+" 。\n");   
		message_vision(msg, me, ob);
		return j;
	}
}

// 添加 pfm huoyan-dao 绝世 的附加威力
mixed hit_ob(object me, object target)
{
	string msg;
	int j,ls,hyd,damage;
	j = me->query_skill("strike",1);
    ls=me->query_skill("longxiang-boruo",1);
	hyd=me->query_skill("huoyan-dao",1);
	damage=ls+hyd+j;
	damage=damage+random(damage);
	if( !me->query("quest/dls/hyd/pass") ) return ;
    if (!me||!target) return;
    
    if (random(10)>6)
    {   
	 switch (random(3))
	 {
	  case 0:
             if(random(j) >target->query_skill("parry",1)/2
	            || random(me->query("neili")) > target->query("neili")/2 ) 
			{
				msg = CYN"$n只觉$N的火焰刀排山倒海般的涌来，势如破竹，根本无法抵挡,波的一声正中胸口！\n"NOR;
				target->receive_wound("qi", damage, me);
	         } 
			 else {
				msg = HIR"$n只觉$N的火焰刀排山倒海般的涌来，当即运起全内力，准备硬接这一掌！\n"NOR;
				target->add("neili",-j);
	     		if( !target->is_busy() )
					target->add_busy(2+random(2));
	          }
	         message_vision(msg, me, target);
	         break;
	 case 1:
            if (random(me->query("combat_exp"))>target->query("combat_exp")/2 && hyd >449&&objectp(target) )
             { 
		      message_vision(RED "\n$N此刻忽以手掌作刀状，狠砍狠斫，全是少林派武功的路子。一刀劈落，刀气迸发波的一响，$n顿时右臂中招！\n"NOR,me,target);
			  target->receive_damage("qi",damage,me);
			  target->apply_condition("no_perform",1);
              }
	        // message_vision(msg, me, target);
			 break;
	case 2:
             message_vision(RED"火焰刀的掌力无坚不摧，$n既然脉门被扣，已是听由宰割，全无相抗之力。\n",me,target);
		     target->add_busy(1+random(1));
		     if(random(me->query_skill("force",1)) >  target->query_skill("force",1)/3
				 && me->is_fighting()
				 && ls>449)
			{
                message_vision(HIR "$n只觉得全身燥热，内息四处乱冲！\n"NOR,me,target);
                target->receive_damage("qi", damage,me);
                target->apply_condition("no_exert",1);
				target->apply_condition("hyd_condition",3);
                target->add("neili", -random(damage));               
                me->add("neili",-400);
             } 
             else {
                message_vision( YEL "可是$n看破了$N的企图，当即运起全身内力将这股热气反震了回去。\n" NOR,me,target);
                if (!me->query("quest/longxiang/pass"))
				{
                   message_vision(HIR "$N只觉得全身燥热，内息乱冲，燥热难当！\n"NOR,me);
				   me->apply_condition("no_exert", 1);
                   me->receive_damage("qi", damage,me);
                   me->add("neili",-800);
				   me->start_busy(2);  
				}
				else {
				  message_vision(WHT"$N龙象般若功已然大成，瞬间将这股燥热压制下去，但心中却对$n的深厚功力很是佩服。\n"NOR,me,target);
				}
                me->add("neili",-400);    
               
			}
		    break;
	    }
	  }
}

int help(object me)
{
	write(HIR"\n雪山秘技「火焰刀」："NOR"\n");
	write(@HELP
	鸠摩智自获传火焰刀后，以此扫荡黑教。由於对少林七十二绝技深感兴趣，
	鸠摩智便以火焰刀功法跟慕容博交换二、三十门少林绝技。慕容博更与鸠
	摩智立约，若鸠摩智能取得大理段氏的《六脉神剑经》，则可到参合庄去
	取其馀少林七十二绝技的秘本。故日后才发生天龙寺夺经之战。
	最初，鸠摩智以火焰刀内力点燃暗藏火药的藏香，以内力推动碧烟攻击枯
	荣等六僧，但枯荣以静制动，鸠摩智在枯荣突袭下败阵。及后，鸠摩智将
	火焰刀内力一分为数，从多个方向攻击，枯荣心知不敌，以一阳指内力焚
	毁《六脉神剑经》。剑谱被毁使鸠摩智与天龙寺结下仇怨，鸠摩智便擒下
	保定帝为人质。段誉情急出手，引发一场无形刀剑之战，最终火燄刀不敌
	六脉神剑，但段誉却被鸠摩智擒下。自此一战，火焰刀名震江湖。
	
要求：
	最大内力 1500 以上；
	后天根骨 30 以上；
	龙象般若功等级 100 以上；
	内功等级 100 以上。     
HELP
	);
	return 1;
}
