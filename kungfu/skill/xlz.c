// xianglong-zhang.c 降龙十八掌
// Rebuild By looklove 2001.4.6
// Modify by looklove 2001.5.2 for rumo
// Modify by Looklove 2001.5.6 for slbw
// Modify by Looklove 2001.7.20 for fz
// Modify at 2001.10.05 for bxsj
// Modify By lsxk@hsbbs 2007/7/13 add no_fight condition

#include <ansi.h>
inherit SKILL;
#include <combat.h>

string *parry_msg = ({
"$n不待回身，半招「神龙摆尾」，做势反劈。$N见这招势凶狠，不敢硬接，纵身避开。\n",
"只见$n左掌圆劲，右掌直推，挡在身前。一招纯是防御，却似在双方之间布了一道坚壁。\n",
"$n当下不敢怠慢，双掌当胸平推，将自己全身笼罩在掌力之下。守得稳若渊停岳峙，毫无半点破绽。\n",
"$n只觉对方劲力之强无法闪避，无奈之下，$n双眼一闭，大喝一声，双掌上扬，硬接了$N这一招。\n",
"$n脚下一转，左掌架开了$N攻来的招式，右掌暗藏在腰间，伺机反击。\n",
"$n胸有成竹，辨清了$N的招式，双掌一拍，轻轻一笑间，已封住了对方的招式。\n",
});

string query_parry_msg(object weapon, object victim)
{
	if( victim->query_temp("weapon")
	 || victim->query_skill("xianglong-zhang", 1) < 100
	 || victim->query_skill_prepared("parry") != "xianglong-zhang" )
		return SKILL_D("parry")->query_parry_msg(weapon);
	else
		return parry_msg[random(sizeof(parry_msg))];
}

mapping *action = ({
([
	"action": "$N双腿微曲，双掌平平提到胸前，右臂划个圆圈，呼的一声，使出降龙十八掌的第一招「亢龙有悔」拍向$n",
	"lvl" : 0,
	"skill_name": "亢龙有悔",
	"damage_type": "瘀伤"
]),
([
	"action": "但见$N左掌护胸，身体一侧，后转背对$n，右掌紧跟着一摆，一招「神龙摆尾」拍向身后的$n",
	"skill_name": "神龙摆尾",
	"lvl" : 10,
	"damage_type": "瘀伤"
]),
([
	"action": "但见$N一招未完，一招又起，左掌回收护胸，右掌向右横推而出，这是一招「见龙在田」，迅捷无比地劈向$n的$l",
	"lvl" : 20,
	"skill_name": "见龙在田",
	"damage_type": "瘀伤"
]),
([
	"action": "$N凝神闭气，提起双掌齐胸平推，施出「鸿渐于陆」，这招外表看似平凡朴实，但掌力夹却带着隐隐的风声，缓缓压向$n",
	"lvl" : 30,
	"skill_name": "鸿渐于陆",
	"damage_type": "瘀伤"
]),
([
	"action": "$N右掌聚成拳状，一式炮锤格开$n的手臂，接着近身上前左掌迅速推出，这是一招「潜龙勿用」，掌力雄浑涌向$n",
	"lvl" : 40,
	"skill_name": "潜龙勿用",
	"damage_type": "内伤"
]),
([
	"action": "爆喝声中$N飞身上前，单掌凝气，凌空劈出一招「利涉大川」，这降龙掌掌风如刀如刃，迅猛无比地砍向$n的$l",
	"weapon" : "降龙掌掌风",
	"skill_name": "利涉大川",
	"lvl" : 50,
	"damage_type": "割伤"
]),
([
	"action": "$N双掌相并，身体突然前跃，使出「突如其来」这招，掌力排山倒海般向$n正面推出，避无可避",
	"skill_name": "突如其来",
	"lvl" : 60,
	"damage_type": "瘀伤"
]),
([
	"action": "突见$N猛然大吼一声，中宫空门大开，双掌一上一下劈出两道惊人的劲，不顾一切地斩击$n，这是一招「震惊百里」",
	"skill_name": "震惊百里",
	"lvl" : 70,
	"damage_type": "瘀伤"
]),
([
	"action": "$N跨前一步，一招「或跃在渊」，左右双掌向$n连连拍出，一浪接着一浪，掌风更带起地上无数沙石",
	"skill_name": "或跃在渊",
	"lvl" : 80,
	"damage_type": "瘀伤"
]),
([
	"action": "$N身形向前移动，双掌分使两式「双龙取水」，凌厉的掌风一左一右，但却不分先后，同时压向$n$l",
	"skill_name": "双龙取水",
	"lvl" : 90,
	"damage_type": "瘀伤"
]),
([
	"action": "$N左脚微曲，身形飞起，于半空中拍出「鱼跃于渊」，双掌立砍，斧一般的掌劲齐向$n的$l劈下",
	"weapon" : "手掌",
	"skill_name": "鱼跃于渊",
	"lvl" : 110,
	"damage_type": "割伤"
]),
([
	"action": "$N扎个马部，使出一招「时乘六龙」，双掌一正一反，一上一下，一前一后向$n周身连连续续猛烈砍了六下",
	"skill_name": "时乘六龙",
	"lvl" : 130,
	"damage_type": "瘀伤"
]),
([
	"action": "$N使出一招「密云不雨」，左掌将掌力连连拍出，带起旋风封住$n了的退路，右掌跟着斜斜地劈向$n的$l",
        "weapon" : "降龙掌掌力",
	"skill_name": "密云不雨",
	"lvl" : 140,
	"damage_type": "割伤"
]),
([
	"action": "$N弓步向前，使出一招「损则有孚」，双掌看似软绵绵地拍向$n，但劲力过处，地上的沙石连连飞舞，着实潜力不小",
	"skill_name": "损则有孚",
	"lvl" : 160,
	"damage_type": "内伤"
]),
([
	"action": "$N脚下一转，突然欺身到$n身前，右掌斜转护住全身，左掌运劲一招「龙战于野」，猛然砍向$n的$l",
	"weapon" : "掌缘",
	"skill_name": "龙战于野",
	"lvl" : 170,
	"damage_type": "割伤"
]),
([
	"action": "$N一声爆喝，胸前门户大开，双掌相并，齐向$n猛地推去，正是一招至刚的「履霜冰至」，至自己于死地而不顾",
	"skill_name": "履霜冰至",
	"lvl" : 180,
	"damage_type": "瘀伤"
]),
([
	"action": "$N左掌低垂，右掌抬高，使出一招「羝羊触蕃」，两股雄浑的掌力打出，一上一下同时向中间的$n挤压下去",
	"skill_name": "羝羊触蕃",
	"lvl" : 190,
	"damage_type": "瘀伤"
]),
([
	"action": "$N突然一跃飞起半空，身形急速旋转，居高临下，双掌使出一招「飞龙在天」，夹杂着汹涌的罡气直向身下的$n压去",
	"lvl" : 200,
	"skill_name": "飞龙在天",
	"damage_type": "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
	if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
		return notify_fail("练降龙十八掌必须空手。\n");
	if( (string)me->query("family/master_name") != "洪七公" )
		return notify_fail("降龙十八掌只能从洪七公处学到。\n");
	if( (int)me->query_skill("huntian-qigong", 1) < 100 )
		return notify_fail("你的混天气功火候不够，无法练降龙十八掌。\n");
	if( me->query("gender") == "无性" )
		return notify_fail("你一个不男不女之人怎能学习降龙掌？\n");
	if( (int)me->query("max_neili") < 1000 )
		return notify_fail("你的内力太弱，无法学降龙十八掌。\n");
	if( (int)me->query_str(1) < 27 )
		return notify_fail("你没有雄壮的臂力无法学降龙十八掌。\n");
	if( (int)me->query_con(1) < 26 )
		return notify_fail("你没有雄厚的体质无法学降龙十八掌。\n");
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
	int i, j, pw, lvl, tmp, deads, m;	
	
	lvl = (int)me->query_skill("xianglong-zhang", 1);
	if( lvl > 300 ) lvl = 300;
	tmp = 2 + random(lvl/5);
	if( tmp < 10 ) tmp = 5 + random(5);
	if( tmp > 99 ) tmp = 99;
	pw = (int)me->query("xlz/power");

	deads = (int)me->query("death_times");
	deads -= 100;
	deads = deads/3 + random(deads/2);

	if( me->query("combat_exp") < 1000000 ) m = 30;
	else if( me->query("combat_exp") < 3000000 ) m = 60;
	else if( me->query("combat_exp") < 5000000 ) m = 90;
	else if( me->query("combat_exp") < 7000000 ) m = 120;
	else if( me->query("combat_exp") < 9000000 ) m = 150;
	else m = 180;

	if( deads < 0 ) deads = 0;
	if( deads > m ) deads = m;

	if( me->query_temp("shuangjue/xlz") ) {
		string msg;		
		switch(me->query_temp("shuangjue/xlz")) {
			case 2: msg = HIR"只听$N又一声龙吟，前棒刚至，突然换招，力发丹田，挟起掌风向$n的$l拍去"NOR; break;
//			case 1: msg = HIM"棒影一收，$n只觉得眼花缭乱，只听$N一声大喝：这个才是真的，看掌"NOR; break;
			case 1: msg = HIY"$N不等棒招用老，回身上步，大喝一声，猛然一掌拍出，端的是干净利落"NOR;break;
			default: msg = HIR"只听$N又一声龙吟，前棒刚至，突然换招，力发丹田，挟起掌风向$n的$l拍去"NOR; break;
		}
		me->add_temp("shuangjue/xlz", -1);
		return ([
			"action": msg,
			"dodge":  random(30),
			"parry":  random(30),
            "damage": 150 + random(100),

			"force":  random(deads)+300+random(200),
			"damage_type": "瘀伤"
		]);
	}

	if( me->query_temp("slbw") ) {
		me->delete_temp("slbw");
		return ([
			"action" : HIC"但见$N硬接了$p这一招，右掌紧接着向后一摆，一招「神龙摆尾」出其不意地按在了$n的$l上！"NOR,
			"force" : me->query("gender")=="男性"?600:450,
			"dodge":  me->query("gender")=="男性"?30:20,
			"parry":  me->query("gender")=="男性"?30:20,
			"damage_type" : "瘀伤",
		]);
	}
	else if( me->query_temp("xlz/hanglong") ) {
		me->delete_temp("xlz/hanglong");
		return ([
            "action": HIR"\n$N叫道：「看招！」左腿微屈，右掌划了个圆圈，平推出去，正是降龙十八掌中的「亢龙有悔」!"NOR,
			"dodge": -30 + 10 * tmp,
			"parry": -25 + 10 * tmp,
			"strike": 10 + 10 * tmp, 
			"force": 500 + 20 * tmp,
            "damage": 150 + 30 * tmp,

			"damage_type": random(2)?"内伤":"瘀伤"
		]);
	}

	else if( (int)me->query_temp("xlz/py_power") > 0 ) {
		string msg;
		if( random(3) )
			msg = HIR"$n只觉气息窒滞，$N掌力竟如怒潮狂涌，势不可当，如同一堵无形的气墙疾冲而来。"NOR;
		else
			msg = HIR"顿时间，只见天地间飞沙走石，$n眼前仿佛山崩地裂，只觉得耳边轰鸣，摇摇欲坠。"NOR;
		me->add_temp("xlz/py_power", -1);
		return ([
			"action": msg,
			"force" : me->query("gender")=="男性"?600:450,
			"dodge":  me->query("gender")=="男性"?30:20,
			"parry":  me->query("gender")=="男性"?30:20,
			"damage_type" : "瘀伤",
		]);
	}

	//force add 50 
	for(i = sizeof(action); i > 0; i--) {
		if( lvl > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, lvl/5);
			if( me->query_temp("xlz/xiao") && me->query("jiali") >= 50 )
				return ([
					"action" : HIY+action[j]["action"]+NOR,
					"force" :  me->query("gender")=="男性"?500+random(350):380+random(350),
					"dodge": random(30)+10,
                                        "damage": 150+random(50),
					"parry": me->query("gender")=="男性"?30:10,
					"lvl" : action[j]["lvl"],
					"weapon" : action[j]["weapon"],
					"damage_type" : action[j]["damage_type"],
				]);
			else if( (me->query("xlz/super") || me->query_temp("xlz/super") ) && random(10) > 5 )
				return ([
					"action" : HIW+action[j]["action"]+NOR,
					"force" : me->query("gender")=="男性"?450+random(350):350+random(320),
					"dodge": me->query("gender")=="男性"?random(30):random(30)-5,
					"parry": me->query("gender")=="男性"?random(30):random(25),
					"lvl" : action[j]["lvl"],
					"weapon" : action[j]["weapon"],
					"damage_type" : action[j]["damage_type"],
				]);
			else if( random(pw) > 5 || me->query_temp("xlz/power"))
				return ([
					"action" : HIC+action[j]["action"]+NOR,
					"force" : me->query("gender")=="男性"?450+random(350):350+random(320),
					"dodge": me->query("gender")=="男性"?random(30):random(30)-5,
					"parry": me->query("gender")=="男性"?random(30):random(25),
					"lvl" : action[j]["lvl"],
					"weapon" : action[j]["weapon"],
					"damage_type" : action[j]["damage_type"],
				]);
			else return ([
					"action" : action[j]["action"],
					"force" : me->query("gender")=="男性"?250+random(350):230+random(320),//250-50 /5*4
					"dodge":  random(30)-10,
					"parry": random(20),
					"lvl" : action[j]["lvl"],
					"weapon" : action[j]["weapon"],
					"damage_type" : action[j]["damage_type"],
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = (int)me->query_skill("xianglong-zhang", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if( me->query("jingli") < 50 )
		return notify_fail("你的体力太低了。\n");
	if( me->query("neili") < 20 )
		return notify_fail("你的内力不够练降龙十八掌。\n");
	me->receive_damage("jingli", 40);
	me->receive_damage("neili", 15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xianglong-zhang/" + action;
}

void skill_improved(object me)
{
	int lvl, x;

	lvl = me->query_skill("xianglong-zhang", 1);
	x = me->query_int();
	if( wizardp(me) ) lvl +=300;

	// 祝你走火入魔 :)
	if( random((int)me->query("xlz/zouhuo") ) > 20
	 && random(lvl) > 300
	 && !me->query("xlz/super")
	 && random((int)me->query("neili")) > 8000
	 && random(x)< 5 ) {
		me->add("xlz/zouhuo",-2);
		me->add("max_neili",-5);
		me->add("xlz/rumo",1);
		me->set_temp("xlz/rumo",1);
		message_vision(HIR"$N忽然感觉双手不听使唤，一股强劲的内力在体内乱蹿，好久才平息，不过$N的内力已经打了折扣。\n"NOR, me);
		tell_object(me, HIR"\n通过内功克制，你目前走火入魔的次数下降到了"+me->query("xlz/zouhuo")+" 次。\n"NOR);
		log_file("skills/xlz",sprintf("%8s%-10s第%5d次入魔扣除5点最大内力，当前经验：%d。\n",
                    me->name(),"("+me->query("id")+")",me->query("xlz/zouhuo"),me->query("combat_exp")), me);
	}

        // Power 级别的机会
	else if ( random(lvl) > 300
	 && lvl < 400
	 && random(x)>20
	 && !me->query("xlz/super")
	 && !me->query_temp("xlz/super")
	 && random(me->query_str()) > 25
	 && random((int)me->query("neili")) > 7000
	 && random(35)==1
	 && !me->query_temp("xlz/rumo") ) {
		message_vision(HIW"$N感觉浑身仿佛有使不完的力气。$N的降龙十八掌功力有了很大提高！\n"NOR, me);
		if( (int)me->query("xlz/power") < 20 )
			me->add("xlz/power",1);
		if( !me->query("xlz/power") )
			me->set("xlz/power",1);
		me->set_temp("xlz/power",1);
		me->add("max_neili", x/3 + random(lvl/50));
		log_file("skills/xlz",sprintf("%8s%-10s升级到Power级别。当前最大内力%d，当前经验：%d。\n",
                    me->name(),"("+me->query("id")+")",me->query("max_neili"),me->query("combat_exp")), me);
        }

	if( random(lvl) > 450
	 && me->query("con") > 20
	 && random(x) > 30
	 && !me->query("xlz/super")
	 && !me->query_temp("xlz/power")
	 && (string)me->query("gender")=="男性"
	 && me->query("xlz/zouhuo")
	 && !me->query_temp("xlz/zouhuo")
	 && random(40)==1 ) {
		message_vision(HIR"突然间，$N感觉双掌发热，双手不听使唤的乱舞起来。\n"NOR, me);
		// 报废的路 grin
		if( me->query_skill("huntian-qigong") < 100 ) {
			me->start_busy(10);
			if( (int)me->query("max_neili") > 100 )
			me->add("max_neili",-30);
                	me->add("xlz/zouhuo",1);
			me->set_temp("xlz/zouhuo",1);
			// 没有混天气功做基础，去死吧 !
			if( random(5)==1 ) {
				me->set_temp("last_damage_from","强练降龙十八掌走火入魔而");
				me->die();
			}
			else {
				message_vision(HIR"$N费了好大劲才将乱蹿的内劲收了回来，好险走火入魔。$N发现自己好久不能动弹。\n"NOR, me);
				tell_object(me, HIR"\n你目前已经有"+me->query("xlz/zouhuo")+" 次险些走火入魔。\n"NOR);
				log_file("skills/xlz",sprintf("%8s%-10s第%5d次险些走火扣除30点最大内力，当前经验：%d。\n",
					me->name(),"("+me->query("id")+")",me->query("xlz/zouhuo"),me->query("combat_exp")), me);
			}
		}
		// Super 级别提升
		else if( random((int)me->query_con()) > 60 && random((int)me->query("neili")) > 13500 ) {
			me->set("xlz/super",1);
			me->add("max_neili", x + random(lvl/4));
			me->delete("xlz/zouhuo");
			me->delete("xlz/rumo");
			message_vision(HIW"$N气收丹田，将双臂中乱蹿的内劲收了回来，感觉功力大增，忍不住纵声长啸！\n"NOR, me);
			log_file("skills/xlz",sprintf("%8s%-10s升级到Super级别。当前最大内力%d，当前经验：%d。\n",
				me->name(),"("+me->query("id")+")",me->query("max_neili"),me->query("combat_exp")), me);
                }
                // 走火入魔
		else {
			me->start_busy(10);
			if( (int)me->query("xlz/zouhuo") < 100 )
				me->add("max_neili",-2);
			me->add("xlz/zouhuo",1);
			me->set_temp("xlz/zouhuo",1);
			message_vision(HIR"$N费了好大劲才将乱蹿的内劲收了回来，好险走火入魔。$N发现自己好久不能动弹。\n"NOR, me);
			tell_object(me, HIR"\n你目前已经有"+me->query("xlz/zouhuo")+" 次险些走火入魔。\n"NOR);
			log_file("skills/xlz",sprintf("%8s%-10s第%5d次走火扣除2点最大内力，当前经验：%d。\n",
				me->name(),"("+me->query("id")+")",me->query("xlz/zouhuo"),me->query("combat_exp")), me);
                }
        }
}

int ob_hit(object ob, object me, int damage)
{
	int i, p, x, neili, lvl, jl, ap, dp;
	object wp, twp;
	string msg;

	lvl = (int)me->query_skill("xianglong-zhang", 1);
	wp = me->query_temp("weapon");
	twp = ob->query_temp("weapon");
	x = (int)me->query("xlz/power");
	ap = (int)me->query("combat_exp");
	dp = (int)ob->query("combat_exp");

	if( me->query_temp("fanzhen")) {
		me->delete_temp("fanzhen");
		return 0;
	}

	if( objectp(wp) || me->is_busy() ) return 0;
	if( me->query_skill_prepared("strike") != "xianglong-zhang"
	 || me->query_skill_mapped("parry") != "xianglong-zhang" )
		return 0;

// 反震 ,hehe
        if( random(me->query_con(1) + x ) > ob->query_con(1)/3
	&& random(ap) > dp/3
        && random(lvl) > 100
	&& random(me->query("neili")) > 1000
	&& random(2) ) {
		me->set_temp("xlz/fz", 1);
		if( objectp(twp) ) {
			msg = HIR"$N龙吟一声，突然抢上一步，掌缘外翻，运劲往" + twp->name() + HIR"上便拍。\n"NOR;
			if( me->query_str(1) > ob->query_str(1)*2/3
			 && random(me->query("neili")) > ob->query("neili") / 3 ) {
				msg += HIR"$n只觉得虎口发麻，手中" + twp->name() + HIR"险些脱手而出。\n"NOR;
				ob->add_busy(1+random(2));
				damage = -6000;
			}
			else {
				msg += HIR"$n早一料到$N有此一招，" + twp->name() + HIR"虚晃一招，躲了开去。\n"NOR;
				damage = -4000;
			}
			message_vision(msg, me, ob);
		}
		else {
			msg = HIR"$N眼见这一招已无处可避，双掌一翻，直拍$n胸膛，用的竟是两败俱伤的打法。\n"NOR;
			if( random(me->query_str(1)) > ob->query_str(1)/2
			 && random(me->query("neili")) > ob->query("neili")/4 ) {
				msg += HIR"$n的招式已经用老，无法收回，无奈之下只好和$N硬拼了一招。\n"NOR;
				damage = 10 + damage/2;
				ob->receive_damage("qi", damage/2, me);
				ob->receive_wound("qi", damage/5, me);
				p = (int)ob->query("qi")*100/(int)ob->query("max_qi");
				msg += COMBAT_D->damage_msg(damage, "瘀伤");
				msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
				me->add("neili",-50);
			}
			else if( random(me->query_con(1)) > ob->query_str(1)/2
			 && random(me->query("neili")) > ob->query("neili")/2 ) {
				msg += HIR"$n大叫一声“不好！”，连忙回招护住身前的空门。\n"NOR;
				ob->add_busy(random(2));
				damage = -5000;
			}
			else {
				msg += HIR"$n大吃一惊，无暇攻击$N，慌忙闪身避开$N的掌风。\n"NOR;
				damage = -4000;
			}
			message_vision(msg, me, ob);
        	}
		me->delete_temp("xlz/fz");
		me->set_temp("fanzhen", 1);
		return damage;
	}

      // 代号：猛鬼三招, grin Quest 暂时关闭^M
	if( !objectp(twp)
         && random(ap) > dp/4
	 && random(lvl) > 50
	 && lvl > 100
	 && random(me->query("neili")) > 1000 ) {
		i = me->query_skill("parry", 1);
		me->add("neili",-100);
		me->set_temp("xlz/3hit",1);
		damage = -damage;

         	if(!me->query_temp("xlz/xiao")){
         		me->set_temp("xlz/xiao", 1);
         		me->add_temp("apply/parry", i/5);

         		COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 0);

         		me->delete_temp("xlz/xiao");
         		me->add_temp("apply/parry", -i/5);
         	}
         	else if (!me->query("xlz/super")){
         		me->set_temp("xlz/super", 1);
         		me->add_temp("apply/strength", i/15);
         		me->add_temp("apply/parry", i/15);
         		me->set_temp("double_attack", 1);

         		COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);

         		me->delete_temp("double_attack");
         		me->delete_temp("xlz/super");
         		me->add_temp("apply/strength", -i/15);
         		me->add_temp("apply/parry", -i/15);
         	}
		else {
			me->set_temp("xlz/power", 1);
			me->add_temp("apply/strength", i/20);
			me->add_temp("apply/parry", i/10);

			COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);

         		me->delete_temp("xlz/power");
         		me->add_temp("apply/strength", -i/20);
         		me->add_temp("apply/parry", -i/10);

         	}
         	me->delete_temp("xlz/3hit",1);
         	me->set_temp("fanzhen", 1);
         	return damage;
         }
// 这里结束.
// slbw
	if( !objectp(twp)
         && random(me->query_str(1)) > ob->query_str(1)/5
         && random(ap) > dp/5
         && random(lvl) > 80
	 && me->query("neili") > 800
	 && me->query("qi") < me->query("max_qi")/2
	 && userp(me)
         && random(2) ) {

		i = me->query_skill("parry", 1);
		jl = me->query("jiali");
		neili = me->query("neili");

		me->set_temp("slbw", 1);
		ob->set_temp("slbw_hit", 1);
		me->set("jiali", me->query_skill("force") + 200);

		me->add_temp("apply/attack", lvl/2);
		me->add_temp("apply/strength", i/4);
		me->add_temp("apply/parry", i/5);
		me->set("slbw", jl);
		damage = -damage;

		COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 3);

		if( me->query("neili") < neili )
			me->set("neili", neili-100);
		me->set("jiali", me->query("slbw"));
		ob->delete_temp("slbw_hit");
		me->delete("slbw");
		me->delete_temp("slbw");

		me->add_temp("apply/attack", -lvl/2);
		me->add_temp("apply/strength", -i/4);
		me->add_temp("apply/parry", -i/5);
		me->set_temp("fanzhen", 1);
		return damage;
	}
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int i;

//	paiyun 重叠威力追加

	if( !me->query("paiyun_power") ) return;
	if( !me->query_temp("xlz/py_add") ) return;

	me->add_temp("xlz/py_add", -1);

	if( damage_bonus < me->query_skill("strike")*3 ) return;
	message_vision(HBRED"$N前招掌力未消，次招掌力又到，$n大惊之下，单掌出迎，顿时臂断腕折筋骨尽碎。\n"NOR, me, victim);
	i = me->query_skill("strike") * (2+random(3));
   //victim->set_temp("no_fight",1);
   victim->apply_condition("no_fight",3);
	if( i > damage_bonus*2/3 ) i = damage_bonus*2/3;
	return i;
}

int help(object me)
{
	write(HIW"\n降龙十八掌："NOR"\n");
	write(@HELP
	降龙十八掌，为丐帮世代相传震帮之宝。威力无匹，是外家刚猛一类的功夫。
	讲究攻击时的爆发力，全力一击，当者披靡。号称天下最霸道的空手。

	学习要求：
		混天气功等级 100 以上；
		内力 1000 以上；
		后天膂力 27 以上；
		后天根骨 26 以上；
		由洪七公亲传，或解谜后可得。
HELP
	);
	return 1;
}
