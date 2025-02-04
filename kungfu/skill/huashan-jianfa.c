// huashan-jianfa.c 华山剑法
// modified by darken@SJ
// Update by lsxk@hsbbs 2007/7/26

inherit SKILL;
#include <combat.h>
#include <ansi.h>
mapping *action_male = ({
([
	"action" : "$N一招「白云出岫」，做一起首试，顿时豪情一片，手中$w蓄试点向$n的$l",
	"lvl" : 0,
	"skill_name" : "白云出岫",
	"parry":0,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N使出「有凤来仪」，剑势飞舞而出，轻盈灵动，$w闪烁不定，刺向$n的$l",
	"lvl" : 10,
	"skill_name" : "有凤来仪",
	"parry":10,
	"damage_type" : "刺伤" 
]),
([
	"action" : "$N一招「天绅倒悬」，满场游走，$w自上而下划出一个大弧，向$n劈砍下去",
	"lvl" : 30,
	"skill_name" : "天绅倒悬",
	"parry":10,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N向前跨上一步，手中$w看似来势既缓，又无力道，但是$N突然剑锋一转，使出「白虹贯日」直刺$n的$l",
	"lvl" : 50,
	"skill_name" : "白虹贯日",
	"parry":0,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N手中的$w一晃，满场游走，一身青衫化成了一片青影，一招「苍松迎客」直刺$n的$l",
	"lvl" : 80,
	"skill_name" : "苍松迎客",
	"parry":30,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N手中$w斜晃反挑，一式「无边落木」，这一下出招急快，抑且如梦如幻，直逼$n的$l",
	"lvl" : 110,
	"skill_name" : "无边落木",
	"parry":20,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N突然右手后缩，跟着剑柄疾收，似乎要撞上自己的胸膛，突然一式「青山隐隐」,反身刺向$n",
	"lvl" : 140,
	"skill_name" : "青山隐隐",
	"parry":30,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N右臂轻提，手中$w提了两尺，剑尖一抬，一招「古柏森森」只等$n撞了上来",      
	"lvl" : 180,
	"skill_name" : "古柏森森",
	"parry":40,
	"damage_type" : "刺伤"
]),
});

mapping *action_famale = ({
([
	"action" : "$N使出「有凤来仪」，剑势飞舞而出，轻盈灵动，$w闪烁不定，刺向$n的$l",
	"lvl" : 0,
	"skill_name" : "有凤来仪",
	"parry":10,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N向前跨上一步，手中$w看似来势既缓，又无力道，但是$N突然剑锋一转，使出「白虹贯日」直刺$n的$l",
	"lvl" : 10,
	"skill_name" : "白虹贯日",
	"parry":0,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N手中的$w一晃，满场游走，一身青衫化成了一片青影，一招「苍松迎客」直刺$n的$l",
	"lvl" : 30,
	"skill_name" : "苍松迎客",
	"parry":30,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N手中$w斜晃反挑，一式「无边落木」，这一下出招急快，抑且如梦如幻，直逼$n的$l",
	"lvl" : 50,
	"skill_name" : "无边落木", 
	"parry":20,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N威仪整肃一式「玉井天池」，$w轰然一动，犹如千军万马奔驰而来，疾疾刺向$n的$l",
	"lvl" : 80,
	"skill_name" : "玉井天池",
	"parry":20,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N剑转一式「叠翠浮青」，俨然长枪大戟，黄沙千里，$w电闪雷鸣，将$n笼罩于重重剑气之中",
	"lvl" : 110,
	"skill_name" : "叠翠浮青",
	"parry":30,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N左手向外一分，右手$w向右掠出一招「无双无对」，剑气森然地向$n的$l挥去",
	"lvl" : 140,
	"skill_name" : "无双无对",
	"parry":20,
	"damage_type" : "刺伤"
]),
([
	"action" : "$N轻叹一声，手中$w怀中一抱，一式「落花无意」，$w锵然跃出倏的化作几点带露的桃花，飘然飞向$n的$l",
	"lvl" : 180,
	"skill_name" : "落花无意",
	"parry":40,
	"damage_type":  "刺伤"
]),
});

mapping *action_19 = ({
([
   "action":HIW"$N使一式「悠悠顺自然」，手中$w"+HIW"嗡嗡微振，幻成一条白光刺向$n的$l"NOR,
	"lvl" : 10,
	"skill_name" : "悠悠顺自然",
	"damage_type":  "刺伤"
]),
([
   "action":HIC"$N错步上前，使出「来去若梦行」，剑意若有若无，$w"+HIC"淡淡地向$n的$l挥去"NOR,
	"lvl" : 15,
	"skill_name" : "来去若梦行",
	"damage_type":  "割伤"
]),
([
   "action":HIM"$N一式「志当存高远」，纵身飘开数尺，运发剑气，手中$w"+HIM"遥摇指向$n的$l"NOR,
	"lvl" : 20,
	"skill_name" : "志当存高远",
	"damage_type":  "刺伤"
]),
([
   "action":HIG"$N纵身轻轻跃起，一式「表里俱澄澈」，剑光如水，一泻千里，洒向$n全身"NOR,
	"lvl" : 25,
	"skill_name" : "表里俱澄澈",
	"damage_type":  "割伤"
]),
([
	"action":HIY"$N手中$w"+HIY"中宫直进，一式「随风潜入夜」，无声无息地对准$n的$l刺出一剑"NOR,
	"lvl" : 30,
	"skill_name" : "随风潜入夜",
	"damage_type":  "刺伤"
]),
([
	"action":HIR"$N手中$w"+HIR"一沉，一式「润物细无声」，无声无息地滑向$n的$l"NOR,
	"lvl" : 40,
	"skill_name" : "润物细无声",
	"damage_type":  "割伤"
]),
([
   "action":HIW"$N手中$w"+WHT"斜指苍天，剑芒吞吐，一式「云龙听梵音」，对准$n的$l斜斜击出"NOR,
	"lvl" : 50,
	"skill_name" : "云龙听梵音",
	"damage_type":  "刺伤"
]),
([
	"action":HIR"$N左指凌空虚点，右手$w"+RED"逼出丈许雪亮剑芒，一式「万里一点红」刺向$n的咽喉"NOR,
	"lvl" : 60,
	"skill_name" : "万里一点红",
	"damage_type":  "刺伤"
]),
([
	"action":HIC"$N合掌跌坐，一式「我心化云龙」，$w"+CYN"自怀中跃出，如疾电般射向$n的胸口"NOR,
	"lvl" : 70,
	"skill_name" : "我心化云龙",
	"damage_type":  "刺伤"
]),
([
   "action":HIC"$N呼的一声拔地而起，一式「日月与同辉」，$w"+HIC"幻出万道光影，将$n团团围住"NOR,
	"lvl" : 80,
	"skill_name" : "日月与同辉",
	"damage_type":  "割伤"
]),
([
	"action":HIM"$N随风轻轻飘落，一式「清风知我意」，手中$w"+MAG"平指，缓缓拍向$n脸颊"NOR,
	"lvl" : 90,
	"skill_name" : "清风知我意",
	"damage_type":  "刺伤"
]),
([
	"action":HIG"$N剑尖微颤作龙吟，一招「高处不胜寒」，切骨剑气如飓风般裹向$n全身"NOR,
	"lvl" : 100,
	"skill_name" : "高处不胜寒",
	"damage_type":  "割伤"
]),
([
	"action":HIY"$N募的使一招「红叶舞秋山」，顿时剑光中几朵血花洒向$n全身"NOR,
	"lvl" : 110,
	"skill_name" : "红叶舞秋山",
	"damage_type":  "刺伤"
]),
});

mapping *action_kf = ({
([
	"action":HBCYN"$N手上$w"+HBCYN"慢慢点出，突然间在空中一颤，一招「泉鸣芙蓉」，剑刃暗发嗡嗡之声，$w"+HBCYN"来路如鬼如魅，顷刻间竟然已绕到了$n背后"NOR,
	"lvl" : 0,
	"skill_name" : "泉鸣芙蓉",
	"damage_type":  "刺伤"
]),
([
	"action":HBCYN"$N全不理会对方攻势来路，使出一招「鹤翔紫盖」，变化莫测地攻向$n，剑势竟无丝毫迹象可寻"NOR,
	"lvl" : 10,
	"skill_name" : "鹤翔紫盖",
	"damage_type":  "刺伤"
]),
([
   "action":HBCYN"$N手中$w"+HBCYN"晃动，「石廪书声」使将出来，剑招奇变横生，$n瞧得心惊神眩，不知$N究竟出了多少招"NOR,
	"lvl" : 20,
	"skill_name" : "石廪书声",
	"damage_type":  "割伤"
]),
([
   "action":HBCYN"$N$w"+HBCYN"如云雾变化，正是一招「天柱云气」，极尽诡奇之能事，动向无定，不可捉摸，$n觉一阵眼花缭乱，顿感穷於应付"NOR,
	"lvl" : 30,
	"skill_name" : "天柱云气",
	"damage_type":  "割伤"
]),
([
	"action":HBCYN"$N突然间身子往斜里窜出，使出「雁回祝融」，听$w"+HBCYN"陡发铮然之音，无数光环乱转，霎时之间已将$n裹在一团剑光之中"NOR,
	"lvl" : 50,
	"skill_name" : "雁回祝融",
	"damage_type":  "割伤"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
	if ( me->query("max_neili", 1) < 100)
		return notify_fail("你的内力不够。\n"); 
   if ( me->query_skill("zixia-gong", 1) < 20 && me->query_skill("huashan-qigong",1)<20)
		return notify_fail("你的华山特殊内功火候太浅。\n");
	if ( me->query_skill("sword", 1) < 20 )
		return notify_fail("你的基本剑法还不够娴熟，无法学习华山剑法。\n");
	if ( me->query_skill("poyu-quan", 1) < 15)
		return notify_fail("你的破玉拳太弱，无法学习到华山剑法的精髓。\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level, j, r_force, r_dodge, r_damage;
   string str;

	level = me->query_skill("huashan-jianfa",1);

	if( me->query_temp("hsj_19")) {
		for(i = sizeof(action_19); i > 0; i--) { 
			if(level >= action_19[i-1]["lvl"]) {
				j = NewRandom(i, 20, level/5);
				return ([
					"action": action_19[j]["action"],
					"lvl": action_19[j]["lvl"],
					"damage_type": action_19[j]["damage_type"],
					"force": 150 + random(300),
					"dodge": random(30),
					"parry": random(30),
					"damage": 100+ random(100),
				]);
			}
		}
	}
	if( me->query_temp("hsj_kf") ) {
		for(i = sizeof(action_kf); i > 0; i--) {
			if(level >= action_kf[i-1]["lvl"]) {
				j = NewRandom(i, 20, level/5);
				return ([
					"action": action_kf[j]["action"],
					"lvl": action_kf[j]["lvl"],
					"damage_type": action_kf[j]["damage_type"],
					"force": 200 + random(350),
					"dodge": random(30)-random(10),
					"parry": random(30)-random(10),
					"damage": 120 + random(100),
				]);
			}
		}
	}
	if( me->query_temp("hsj_wushuang")) {
		for(i = sizeof(action_kf); i > 0; i--) {
			if(level >= action_kf[i-1]["lvl"]) {
				j = NewRandom(i, 20, level/5);
				return ([
					"action": HIW"$n大吃一惊，惊叫一声：“哎呀！”其时$w"+HIW+"剑尖已刺破他衣衫。$N右手向前疾送，$w"+HIW+"护手\n"+
						"已碰到$n的胸膛，眼见这一剑是在$n身上对穿而过，直没至柄"NOR,
					"lvl": action_kf[j]["lvl"],
					"damage_type": action_kf[j]["damage_type"],
					"force": 200 + random(350),
					"dodge": random(30)-10,
					"parry": random(20),
					"damage": 250 + random(50),
				]);
			}
		}
	}
	//男性、无性
    if( me->query("gender") != "女性" )
	{
           for(i = sizeof(action_male); i > 0; i--) 
		   {
			 if(level >= action_male[i-1]["lvl"])
			 {
                j = NewRandom(i, 20, level/5);
				if(me->query_temp("hsjf/luomu"))
				{
					str=HIC+replace_string(action_male[j]["action"],"$w","$w"HIC)+NOR;
					r_force = 200+random(150);
					r_dodge = 30+random(30);
					r_damage = 150 + random(200);
				}
				else if(me->query_temp("hsqg/yjs"))
				{
					str=HIG+replace_string(action_male[j]["action"],"$w","$w"HIG)+NOR;
					r_force = 200+random(150);
					r_dodge = 10+random(20);
					r_damage = 100 + random(150);
				}
				else if(me->query_temp("hsjf/lianhuan"))
				{
					str=HIW+replace_string(action_male[j]["action"],"$w","$w"HIW)+NOR;
					r_force = 200+random(150);
					r_dodge = 10+random(20);
					r_damage = 100 + random(150);
				}
				 else if(me->query_temp("zxg/zixia"))
				{
					str=MAG+replace_string(action_male[j]["action"],"$w","$w"MAG)+NOR;
					r_force = 200 + random(150);
					r_dodge = 10+random(30);
					r_damage = 120 + random(180);
				}
				else{
					str=action_male[j]["action"];
					r_force = 200 + random(250);
					r_dodge = random(30)-10;
					r_damage = 180 + random(140);
				}
//                   for(i = sizeof(action_male); i > 0; i--) {
//                   if(level >= action_male[i-1]["lvl"]) {
//                           j = NewRandom(i, 20, level/5);
                           return ([
                                   "action": str,
                                   "lvl": action_male[j]["lvl"],
                                   "damage_type": action_male[j]["damage_type"],
                                   "force": r_force,
                                   "dodge": r_dodge,
                                   //"parry": random(20),
                                   "parry": action_male[j]["parry"],
                                   "damage": r_damage,
								]);
			 }
          }
   }
//女性群体
   for(i = sizeof(action_famale); i > 0; i--) 
   {
           if(level >= action_famale[i-1]["lvl"]) 
		   {
                   j = NewRandom(i, 20, level/5);
				if(me->query_temp("hsjf/luomu"))
				{
					str=HIC+replace_string(action_famale[j]["action"],"$w","$w"HIC)+NOR;
					r_force = 200+random(150);
					r_dodge = 30+random(30);
					r_damage = 150 + random(200);
				}
				else if(me->query_temp("hsqg/yjs"))
				{
					str=HIG+replace_string(action_famale[j]["action"],"$w","$w"HIG)+NOR;
					r_force = 200+random(150);
					r_dodge = 10+random(20);
					r_damage = 100 + random(150);
				}

				else if(me->query_temp("hsjf/lianhuan"))
				{
						str=HIW+replace_string(action_male[j]["action"],"$w","$w"HIW)+NOR;
						r_force = 200+random(150);
						r_dodge = 10+random(20);
						r_damage = 100 + random(150);
				}
				else if(me->query_temp("zxg/zixia")){
						str=MAG+replace_string(action_famale[j]["action"],"$w","$w"MAG)+NOR;
						r_force = 200 + random(150);
						r_dodge = 10+random(30);
						r_damage = 120 + random(180);
				}
				else{
						str=action_famale[j]["action"];
						r_force = 200 + random(250);
						r_dodge = random(30)-10;
						r_damage = 80 + random(140);
				}
//   for(i = sizeof(action_famale); i > 0; i--) {
//           if(level >= action_famale[i-1]["lvl"]) {
//                   j = NewRandom(i, 20, level/5);
               return ([
                           "action": str,
                           "lvl": action_famale[j]["lvl"],
                           "damage_type": action_famale[j]["damage_type"],
                           "force": r_force,
                           "dodge": r_dodge,
                           //"parry": random(20),
                           "parry": action_famale[j]["parry"],
                           "damage": r_damage,
                   ]);
           }
    }
}


int practice_skill(object me)
{
	int lvl = me->query_skill("huashan-jianfa", 1);
	int i;

	if ( me->query("gender") != "女性") {
		i = sizeof(action_male);
		while (i--) if (lvl == action_male[i]["lvl"]) return 0;
	}
	else {
		i = sizeof(action_famale);
		while (i--) if (lvl == action_famale[i]["lvl"]) return 0;
	}

	if ( me->query("jingli") < 50)
		return notify_fail("你的体力不够练华山剑法。\n");
	if ( me->query("neili") < 20)
		return notify_fail("你的内力不够练习华山剑法。\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"huashan-jianfa/" + action;
}

int ob_hit(object ob, object me, int damage)
{
	object weapon = me->query_temp("weapon");
	int p, ap, dp;
	string msg;

	ap = me->query("combat_exp") /1000 * me->query_int(1);
	dp = ob->query("combat_exp") /1000 * ob->query_int(1);

	p = (int)me->query("qi")*100/(int)me->query("max_qi");

	if ( me->query_skill("huashan-jianfa", 1) < 120
	|| me->query_skill_mapped("sword") != "huashan-jianfa"
	|| me->query_skill_mapped("parry") != "huashan-jianfa"
	|| me->query_skill_prepared("cuff") != "poyu-quan" 
	|| p > 20 
	|| me->is_busy())
		return 0;

	if ( (20 - p) > random(10) && weapon ) {
		msg = "$N手中"+weapon->name()+"被$n一击，脱手飞出！\n"NOR;
		weapon->move(environment(me));
		msg += HIW"$N灵机一动，右手五指急刺，以手指使出一招“金玉满堂”！\n"NOR;
		if (random(ap) > dp/10 ) {
			msg += HBRED"结果正中$n的膻中穴！\n"NOR;
                        ob->add_busy(5+random(3));
		} 
		else {
			msg += HBGRN"结果$n早已料到，轻轻闪过。\n"NOR;
		}
		message_vision(msg, me, ob);
		return -damage;
	}
	return 0;
}
//mixed hit_ob(object me, object victim, int damage_bonus)
mixed hit_ob(object me, object ob, int damage)
{
     object weap,weapon;
	int skill;
	string msg;
	weapon=me->query_temp("weapon");
    weap = ob->query_temp("weapon");
	skill=me->query_skill("huashan-jianfa",1);
	//快剑
	if(me->query_temp("hsj_kf") ){
		if( random((int)me->query_skill("huashan-jianfa", 1)) > ob->query_skill("parry",1)*2/5
			&& me->query("neili") > 2000
			&& random(4)==1 ){
                   if ( weap && me->query("quest/huashan")=="剑宗" ){
               		message_vision(HIR "$N出招如此之快，$n一不留神，手中" + weap->name() +HIR"已被"HIG"狂风快剑"HIR"之剑气所滞。\n" NOR, me,ob ); 
               		if (random((int)me->query_skill("parry", 1)) > (int)ob->query_skill("parry", 1)/2 ){
                 		message_vision(HIY "$n越是着急，手中" + weap->name() + HIY"就越是不听使唤，突然$N一个变招，$n手中" + weap->name() + HIY"便脱手而出!\n" NOR, me,ob );
                 		weap->unequip();
                 		weap->move(environment(me));
                 		ob->reset_action();
                           ob->add_busy(2);
               		}
               		else{ 
                 		message_vision(HIW "$n眼看$N所使的剑气将要顺自己手中的" + weap->name() + HIW"之势斩向手腕，$n情急之下只能将手中的" + weap->name() + HIW"放下。\n" NOR, me,ob );
                 		weap->unequip();
                 		ob->reset_action();
                           ob->add_busy(2);
                     }
               		me->add("neili", -30);
             	   }
        }

	}
	//气宗落木的auto攻击 
	if(me->query_temp("hsjf/luomu") && me->query("quest/huashan")=="气宗" )
	{
      if( random(skill) > ob->query_skill("parry",1)/2
        && me->query("neili") > 2000		
        && !random(5) )
	  {
              if ( weap )
			  {
               		message_vision(HIR "$N出招如此之快，已达以气御剑的极境，$n一不留神，拿" + weap->name() +HIR"的手腕寸关穴已被"HIC"无边落木"HIR"之剑气所伤。\n" NOR, me,ob ); 
               		if (random((int)me->query_skill("sword", 1)) > (int)ob->query_skill("parry", 1)/4 )
					{
                 		message_vision(HIY "$n见$N剑气弥漫，不自觉受制。心中慌乱，突然$N一个变招，$n手中" + weap->name() + HIY"便脱手而出!\n" NOR, me,ob );
                 		weap->unequip();
                 		weap->move(environment(me));
						ob->receive_damage("qi",random(1500),me);
						ob->apply_condition("no_exert",1);
                 		//ob->reset_action();
                        ob->add_busy(2+random(2));
               		}
			  }
              else if (!ob->is_busy())
              { 
                 		message_vision(HIW "$N劲力澎湃，所使出的剑气弥漫，瞬间数股真气刺中$n的手腕!\n" NOR, me,ob );
                 		//weap->unequip();
                 		//ob->reset_action();
						ob->apply_condition("no_force",1);
                        ob->add_busy(1+random(1));
              }
              me->add("neili", -30);
             
        }

	}
	//华山石壁解开谜题后，增加攻击
	//五岳剑法+金蛇剑法解密后会出
	
	if (me->query("quest/hs/hssb/pass")&& random(10)>7)
	{
		 me->add_temp("apply/sword",skill/4);
		 me->add_temp("apply/damage",skill/8);
		 me->add_temp("apply/attack",skill/4);
		 switch (random(6))
		 {
			 //想办法替代先前的描述。。厉害杀招
			case 0:
				message_vision(HIG "$N右手执"+ weapon->query("name") +HIG"，左手握拳，身形满场游走，不断计算方位，正是一招泰山派绝技「"HIR"岱宗如何"HIG"」\n" NOR, me,ob );
			   // message_vision(replace_string( HIG "$N右手执"+ weapon->query("name") +HIG"，左手握拳，身形满场游走，不断计算方位，正是一招泰山派绝技「"HIR"岱宗如何"HIG"」\n",	"$l", limbs[random(sizeof(limbs))]) + "！\n\n", me, ob);
				//msg=HIG "$N右手执"+ weapon->query("name") +HIG"，左手握拳，身形满场游走，不断计算方位，正是一招泰山派绝技「"HIR"岱宗如何"HIG"」\n";
				COMBAT_D->do_attack(me,ob,me->query_temp("weapon"), 3);
				break;
			case 1:
				message_vision(HIR "$N手中"+ weapon->query("name") +HIR"，忽然变化，不可捉摸，正是衡山派绝技「"HIY"千变万化，云雾十二式"HIR"」\n" NOR, me,ob );
				ob->add_busy(1);
				
				COMBAT_D->do_attack(me,ob,me->query_temp("weapon"), 3);

				break;
			case 2:
				message_vision(HIB "$N手中"+ weapon->query("name") +HIB"，挥剑防守，正是恒山派绝技「"HIW"绵里针"HIB"」\n" NOR, me,ob );
				ob->add_busy(1);
				COMBAT_D->do_attack(me,ob,me->query_temp("weapon"), 3);
				ob->receive_damage("qi",100+random(1500),me);
				ob->receive_wound("qi",100+random(500),me);
				break;
			case 3:
				message_vision(HIY "$N手中"+ weapon->query("name") +HIY"，大开大合，如斧如刀，正是嵩山派绝技「"HIR"千古人龙"HIB"」\n" NOR, me,ob );
				COMBAT_D->do_attack(me,ob,me->query_temp("weapon"), 3);	
				break;
			case 4:
				if (me->query_skill("jinshe-jianfa",1)>450)
				{
					message_vision(HIC"$N忽然间将自己所悟的金蛇郎君的金蛇剑法绝技「"HIR"万蛇出洞"HIC"」施展出来，和先前华山剑法迥异。\n" NOR, me,ob );
					ob->add_busy(2);
				
					message_vision(HIY"$n冷不防这招突变，一时间适应不过来$N这种变招,有些手忙脚乱。"NOR,me,ob);
					COMBAT_D->do_attack(me,ob,me->query_temp("weapon"), 3);		
				}

				break;
			case 5:
				if (me->query_skill("jinshe-zhangfa",1)>450)
				{
					message_vision(HIG"$N剑交左手，右手忽然间将自己所悟的金蛇郎君的金蛇掌法绝技「"HIR"金蛇缠身"HIC"」施展出来。\n" NOR, me,ob );
					weapon->unequip();
					ob->add_busy(3);
					write("5");
					message_vision(HIR"$N以极不可能的招式一掌打中$n的左肋，$n显然受伤不轻。\n"NOR,me,ob);
					ob->receive_damage("qi",random(2000),me);
					ob->receive_wound("qi",random(1000),me);
					COMBAT_D->do_attack(me,ob,me->query_temp("weapon"), 3);		
					weapon->wield();
				}
				break;
			default: break;
	
		 }
		 me->add_temp("apply/sword",-skill/4);
		 me->add_temp("apply/damage",-skill/8);
		 me->add_temp("apply/attack",-skill/4);

	}
	
	 return;
}
