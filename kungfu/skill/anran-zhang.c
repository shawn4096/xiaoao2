// anran-zhang.c 黯然销魂掌
// By River 98.10.28
// Modified by snowman@SJ 20/06/2000

#include <ansi.h>
#include <combat.h>

inherit SKILL;

#include <combat_msg.h>
mapping *action = ({
([
	"action" :"$N身影陡转，如鬼魅般忽前忽后，瞬左瞬右，一式「徘徊空谷」掌风已至$n的$l",
	"lvl" : 0,
	"skill_name" : "徘徊空谷",
	"damage_type" : "瘀伤"
]),
([
	"action" :"$N长叹一声，身形凝重，一招「力不从心」，诱得$n全力进击之际，反手直拍$n的$l",
	"lvl" : 15,
	"skill_name" : "力不从心",
	"damage_type" : "瘀伤"
]),
([
	"action" :"$N面目僵然，四肢挺直，无弯无折，似「行尸走肉」般，刀臂剑腿，横斩直刺$n的$l",
	"lvl" : 30,
	"skill_name" : "行尸走肉",
	"damage_type" : "瘀伤"
]),
([
	"action" :"$N一式「庸人自扰」，左手锤胸，一边晃首不止，倏忽间绕敌身后，右掌暴击$n的$l",
	"lvl" : 45,
	"skill_name" : "庸人自扰",
	"damage_type" : "瘀伤"
]),
([
	"action" :"$N突然头下脚上，倒过身子，手代足行，只手一招「倒行逆施」闪电般拍向$n的$l",
	"lvl" : 60,
	"skill_name" : "倒行逆施",
	"damage_type" : "瘀伤"
]),
([
	"action" :"$N左手成掌，缓缓推出一招「废寝忘食」，$n只觉一股强劲无伦的掌管风横压而至",
	"lvl" : 75,
	"skill_name" : "废寝忘食",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N单臂负后，凝目远眺，一式「孤形只影」，$n略一迟疑，浑身已为$N掌力所绕",
	"lvl" : 90,
	"skill_name" : "孤形只影",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N左掌一招「饮恨吞声」将$n裹在掌风之中。$n犹如身陷洪涛巨浪，随着$N的掌风转动",
	"lvl" : 105,
	"skill_name" : "饮恨吞声",
	"damage_type" : "瘀伤"
]),
([
	"action" : "却见$N翻身坐倒，旋及旋向空中，凭空一式「六神不安」砸向$n，威力骇人，无法硬接",
	"lvl" : 120,
	"skill_name" : "六神不安",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N右手在$n脸前一拂，一招「穷途末路」击到$n胸前半尺之处，突然转弯，击在$n的$l",
	"lvl" : 135,
	"skill_name" : "穷途末路",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N脸上喜怒哀乐，怪状百出，乘$n心神难以自制之际，一招「面无人色」攻向$n的$l",
	"lvl" : 150,
	"skill_name" : "面无人色",
	"damage_type" : "瘀伤"
]),
([
	"action" : "$N忽然狂笑不止，忽又颠哭阵阵，$n正迷沉恍惚中，$N已一式「想入非非」攻向$n的$l",
	"lvl" : 165,
	"skill_name" : "想入非非",
	"damage_type" : "瘀伤"
]),
([
	"action" : "突见$N身形晃动，已攻至$n身畔，一式「呆若木鸡」，乘$n惊愕之时，疾打$n的$l。",
	"lvl" : 180,
	"skill_name" : "呆若木鸡",
	"damage_type" : "瘀伤"
]),
});

int valid_enable(string usage)
{
	if ( this_player()->query("gender")=="男性")
		return usage == "strike" || usage == "parry";
}

int valid_learn(object me)
{
	int skill = me->query_skill("anran-zhang", 1);
	
	if (!me->query("quest/anran/pass")) return notify_fail("你的尚未得到杨过同意。\n");

	if ( me->query("max_neili") < 1500)
		return notify_fail("你的内力不够。\n");
	if ( me->query("gender")!="男性")
		return notify_fail("黯然掌需要男人才能修炼。\n");
	if ( me->query_str(1) < 30 )
		return notify_fail("你没有强劲的膂力无法学黯然消魂掌。\n");

	if ( me->query_con(1) < 26 )
		return notify_fail("你没有雄厚的体质无法学黯然消魂掌。\n");

	if ((int)me->query_skill("force", 1) < (skill-30)
	&& (int)me->query_skill("anran-zhang", 1) < 230)
		return notify_fail("你的基本内功火候太浅。\n");
	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

string *xue_name = ({
HIW"徘徊空谷"NOR,BLU"力不从心"NOR,HIC"行尸走肉"NOR,HIG"庸人自扰"NOR,HIY"倒行逆施"NOR,
HIR"废寝忘食"NOR,YEL"孤形只影"NOR,CYN"饮恨吞声"NOR,MAG"六神不安"NOR,GRN"穷途末路"NOR,
HIM"面无人色"NOR,RED"想入非非"NOR,WHT"呆若木鸡"NOR,
});

mapping query_action(object me, object weapon)
{
	int i, j,n, level,tmp;
	object target;
	string msg, name;

	level = (int) me->query_skill("anran-zhang",1);
	if (!userp(me))
		tmp = 1 + random(level/20);
	else
		tmp = 1 + random(level/5);

	name = xue_name[random(sizeof(xue_name))];
	
	if( me->query("gender") != "男性") tmp = tmp /3*2;

	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			target = offensive_target(me);
			if(me->query_temp("arz/shengyou")){
				switch(me->query_temp("arz/shengyou")){
					case 2: msg = HIY"$N心下万念俱灰，没精打采的挥袖卷出，拍出一掌，只听得噗的一声，这一掌正好击向$n肩头"NOR; break;
					case 1: msg = HIR"紧跟着$N踢出一脚。这一脚发出时恍恍惚惚，隐隐约约，若有若无。砰的一响，向$n胸口袭去"NOR; break;
					default: msg = HIC"$N心下万念俱灰，没精打采的挥袖卷出，拍出一掌，只听得噗的一声，这一掌正好击向$n肩头"NOR; break;
				}
				me->add_temp("arz/shengyou", -1);
				return ([
					"action":msg,
					"force" : 250+random(350),
					"dodge": random(30),
					"parry": random(20)+10,
					"damage" : 150 + random(50),
					"damage_type" : "瘀伤",
				]);
			}
			if ( me->query_temp("jishi")){
				switch(me->query_temp("jishi")){
					case 2: msg = HIY"$N趁势纵身长啸，将一式「"+xue_name[random(sizeof(xue_name))]+HIY"」使得是出神入化，想将$n罩入掌影之中"NOR; break;
					case 1: msg = HIY"$N不待$n看的真切，使出得意绝学「"+xue_name[random(sizeof(xue_name))]+HIY"」，$n被罩入掌影之中，早已头晕目眩"NOR; break;
					default : msg = HIY"$N趁势纵身长啸，将一式「"+xue_name[random(sizeof(xue_name))]+HIY"」使得是出神入化，想将$n罩入掌影之中"NOR; break;
				}
				me->add_temp("jishi", -1);
				return ([
					"action": msg,
					"force" : 250+random(350),
					"dodge": random(30),
					"parry": random(20)+10,
					"damage" : 180 + random(50),
					"damage_type" : "瘀伤",
				]);
			}
			if(me->query_temp("arz/sanzhao")){
				switch(me->query_temp("arz/sanzhao")) {
					case 1 :
						msg =  HIW"$N抬头向天，浑若不见，呼的一掌向头顶空空拍出，手掌斜下，掌力化成弧形，四散落下\n"NOR;
						msg += RED"结果$n被这一招「杞人忧天」带得别说挣扎，竟连站定脚步也是不能"NOR;
						break;
					case 2 :
						msg =  YEL"$N右手云袖飘动，宛若流水，左掌却重滞之极，便似带着几千斤泥沙一般\n"NOR;
						msg += RED"结果$n被这一招「拖泥带水」带得犹如身陷洪涛巨浪，跌跌撞撞"NOR;
						break;
					case 3 :
						msg =  HIB"突然间$N手足齐动，左掌右袖、双足头锤、连得胸背腰腹尽皆有招式发出\n"NOR;
						msg += RED"结果$n被这一招「无中生有」带得自身全然身不由主的境地"NOR;
						break;
				}
				return ([
					"action": msg,
					"force" : 250+random(350),
					"dodge": random(30),
					"parry": random(20)+10,
					"damage" : 250 + random(50),
					"damage_type" : "瘀伤",
				]);
			}
			if( me->query_temp("arz/qiren") && me->query("jiali")) {
				return ([
					"action" : random(2)? HIB+action[j]["action"]+NOR :MAG+action[j]["action"]+NOR,
					"force" : 350+random(350),
					"dodge": random(30)+10,
					"parry": 30,
					"damage" : 200 + random(50),
					"damage_type" : "割伤",
				]);
			}
			return ([
				"action" : action[j]["action"],
				"lvl" : action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force" : 200+random(350),
				"dodge": random(30)-10,
				"parry": random(20),
				"damage" : 120 + random(50),

			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("anran-zhang", 1);
	int i = sizeof(action);
	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ( me->query_temp("weapon") || (int)me->query_temp("secondary_weapon"))
		return notify_fail("练黯然销魂掌必须空手。\n");

	if ( me->query("jingli") < 50)
		return notify_fail("你的体力不够练黯然销魂掌。\n");

	if ( me->query("neili") < 20)
		return notify_fail("你的内力不够练黯然销魂掌。\n");
	

	me->receive_damage("jingli", 40);
	me->add("neili", -15 );
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"anran-zhang/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int j;
	string who;
	if( damage_bonus < 100 ) return 0;
	j = me->query_skill("anran-zhang", 1);

	if ( random(10) > 6
	 && !victim->is_busy()
	 && j > 140
	 && me->query_skill_mapped("strike") == "anran-zhang"
	 && me->query_skill_prepared("strike") == "anran-zhang"
	 && me->query("neili") > 1000
	 && me->query("max_neili") > 1500
	 && random(j) > victim->query_skill("dodge",1)/2
	 //&& !me->query_temp("anran")
	 //&& !me->query_temp("jishi")
		 ) {
		victim->add_busy(1+random(2));
		me->set_temp("sanzhao", 1);
		call_out("check_fight", 5, me, victim);
	}
    //增加面无人色，摄心大法效果
	/*杨过道：“这虽是一招，其实中间变化多端.脸上喜怒哀乐，怪状百出，敌人一见，登
时心神难以自制，我喜敌喜，我忧敌忧，终至听命于我。【此乃无声无影的胜敌之法】，比之长啸镇慑敌人又高出一筹。”周伯通道：”这是从
九阴真经的慑心大法中变化出来的么？”杨过道：“正是！”*/
	if (me->query_temp("arz/wuse")
		&& random(me->query_per(1))>(victim->query_per(1)/3)
		&& random(10)>5)
	{
		if (me->query("gender")=="男性")
		{
			who="师兄";
			message_vision(HIY"$n忽觉$N非常像自己年幼时照顾自己的师兄，一举一动，极为神似，$n不禁大哭道，“师兄！”\n"NOR,me,victim);
		}
		if (me->query("gender")=="女性")
		{
			who="师姐";
			message_vision(HIC"$n忽觉$N非常像自己年幼时照顾自己的师姐，神似恍然间，$n不禁大哭道，“师姐！”\n"NOR,me,victim);
		}
		switch (random(3))
		{
			case 0:
				message_vision(HIY"$n受面无人色招式影响，行动不觉间变得迟缓起来，脚步踉跄，如陷沼泽。\n"NOR,me,victim);
				victim->add_busy(2);
				victim->add_condition("no_exert",1);
				break;
			case 1:
				message_vision(HIR"$n感觉自己仿佛没有意识，大脑空白，又好像在空中飞，浑身无力，面色苍白，竟然无法出招！\n"NOR,me,victim);
				victim->receive_damage("jing",random(1000),me);
				victim->add_condition("no_perform",1);
				break;
			case 2:
				message_vision(HIC"$n宛如回到自己年轻时代，自己在跟随"+who+HIC"学习武技，一招一式的模仿起来。\n"NOR,me,victim);
				victim->add_temp("apply/damage",j/4);
				COMBAT_D->do_attack(victim, victim, me->query_temp("weapon"), 3);
				victim->add_temp("apply/damage",-j/4);
				break;		
		}
	}
}

void check_fight(object me,object victim)
{
	if(!me) return;
	if(!me->query_temp("sanzhao")) return;
	if( !victim
	 || !me->is_fighting(victim)
	 || me->query_skill_prepare("strike") != "anran-zhang"
	 || me->query_skill_mapped("strike") != "anran-zhang"
	 || me->query_temp("weapon")) {
	 	me->delete_temp("sanzhao");
		return;
	}
	call_out("check_fight", 1, me, victim);
}

int ob_hit(object ob, object me, int damage)
{
	object weapon;
	string msg;
	int ap, dp, j = 0, skill;

	if( me->query_temp("fanzhen")) {
		me->delete_temp("fanzhen");
		return 1;
	}

	if( ob->query("env/invisibility") ) return 0;

	if (me->query_skill("anran-zhang", 1) < 100
	 || me->query_skill_mapped("parry") != "anran-zhang"
	 || me->query("combat_exp") < ob->query("combat_exp")/2
	 || me->query_temp("weapon")) return 0;

	skill = me->query_skill("anran-zhang", 1);
	weapon = ob->query_temp("weapon");

	if ( me->query("neili") < ob->query("neili")/5 ) return 0;

	if(objectp(weapon))
		msg = weapon->query("skill_type");
	else {
		mapping prepare = ob->query_skill_prepare();
		if (!sizeof(prepare)) msg = "unarmed";
		else msg = keys(prepare)[0];
	}

	ap = COMBAT_D->skill_power(ob, msg, SKILL_USAGE_ATTACK) / 1000;
	if ( weapon ) ap *= 2;
	if ( ob->query("neili") > me->query("neili") * 2 ) ap += ap/2;

	dp = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE) / 1000;
	if ( me->is_busy() ) dp /= 2;
	if ( me->query("neili") > ob->query("neili") * 2 ) dp *= 2;
	else if ( me->query("neili") > ob->query("neili") / 2 * 3 ) dp += dp/2;
	if ( userp(me) && ! userp(ob)) dp /= 2;

	ap = ABS(ap);
	dp = ABS(dp);

	if ( skill > 400 ) dp += random(dp);

	if ( random(dp + ap) > ap && ! random(5)) {
		me->set_temp("fanzhen", 1);
		if( me->query("neili") > random(ob->query("neili"))){
			if( weapon ) msg = HIY"$n手中"+weapon->name()+HIY"刚要触到$N身上，突觉$P小腹肌肉颤动，同时胸口向内一吸，倏地弹出！\n"NOR;
			else msg = HIY"$n刚要触到$N身上，突觉$P小腹肌肉颤动，同时胸口向内一吸，倏地弹出！\n"NOR;
			ob->receive_damage("qi", damage/3 + ob->query("jiali")*2, me);
			ob->receive_wound("qi", ob->query("jiali")+1, me);
			j = (int)ob->query("qi") * 100 / (int)ob->query("max_qi");
			msg += damage_msg(damage, "瘀伤") + "( $n"+eff_status_msg(j)+" )\n";
			if( weapon ) {
				msg += "同时，$n手中"+weapon->name()+"也被一震，险些拿握不住。\n";
				ob->add_busy(2+random(2));
				if (random(me->query_str())>ob->query_str()/3)
				{
					msg+=weapon->name()+HIY"在$n的手里晃了晃，把持不住，最终仍旧是被这招心惊肉跳给震落地上。\n"NOR;
					weapon->move(environment(ob));
				}
			}
			j = -6000;
		}
		else {
			msg = "$N凝目远眺，脚下虚浮，一式「心惊肉跳」，吸胸凹腹，避开$n的招数！\n";
			j = -6000;
		}
	}
	else
		return 0;
	message_vision(msg, me, ob);
	return j;
}

int help(object me)
{
        write(HIB"\n黯然销魂掌："NOR"\n\n");
        write(@HELP
        杨过自和小龙女在绝情谷断肠崖前分手，不久便由神雕带着在海潮之中练功，
        数年之后，除了内功循序渐进之外，别的无可再练，心中整日价思念小龙女，
        渐渐的形销骨立，了无生趣。一日在海滨悄然良久，百无聊赖之中随意拳打脚
        踢，其时他内功火候已到，一出手竟具极大威力，轻轻一掌，将海滩上一只大
        海龟的背壳打得粉碎。他由此深思，创出了一套完整的掌法，出手与寻常武功
        大异，厉害之处，全在内力，一共是一十七招。他生平受过不少武学名家的指
        点，自全真教学得玄门正宗内功的口诀，自小龙女学得「玉女心经」，在古墓
        中见到「九阴真经」，欧阳锋以蛤蟆功和逆转经脉，洪七公与黄蓉授以打狗棒
        法，黄药师授以弹指神通和玉箫剑法，除了一阳指之外，东邪、西毒、北丐、
        中神通的武学无所不窥，而古墓派的武学又于五大高人之外别创蹊径，此时融
        会贯通，已是卓然成家。只因他单剩一臂，是以不在招数变化取胜，反而故意
        与武学通理相反。他将这套掌法定名为“黯然销魂掌”，取的是江淹「别赋」
        中那一句“黯然销魂者，唯别而已矣”之意。

        要求：
               最大内力 1500;
               后天根骨 26;
               后天膂力 30;
               黯然销魂掌 230 级前大于玉女心经 30 级。

HELP
        );
        return 1;
}
