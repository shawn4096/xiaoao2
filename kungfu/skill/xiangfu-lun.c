// /kungfu/skill/xiangfu-lun.c
// xiangfu-lun.c 降伏轮
// dubei
// snowman(98,12,22)
// iceland(99.8.3)
#include <ansi.h>
inherit SKILL;
#include <combat.h>
inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";
mapping *action = ({
([
	"action" : "$N一招「大赞叹光明势」，右手立掌护胸，左手单臂抡起$w，当胸砍向$n的$l",
	"skill_name" : "大赞叹光明势",
	"lvl" : 0,
	"damage_type" : "割伤",
]),
([
	"action" : "$N将手中$w抛上半空，跃起一掌砸在$w上，这招「大皈依光明势」有如流星坠地，直轰$n",
	"skill_name" : "大皈依光明势",
	"lvl" : 20,
	"damage_type" : "瘀伤",
]),
([
	"action" : "凭空闪出一道雪白的光幕，光电闪烁中$w挟「大功德光明势」的无上劲力，从$N手中飞出砍向$n的$l",
	"skill_name" : "大功德光明势",
	"lvl" : 40,
	"damage_type" : "割伤",
]),
([
	"action" : "$N双眼磕闭，全身衣物却在内劲鼓荡下涨如气球，那$w在这「大常乐光明势」的推动下，向$n缓缓压去",
	"skill_name" : "大常乐光明势",
	"lvl" : 60,
	"damage_type" : "内伤",
]),
([
	"action" : "$N双手越转越急，光幕俨如一轮明月，将$n笼罩，这「大吉祥光明势」的劲力带着$w以排山倒海之势飞旋而出",
	"skill_name" : "大吉祥光明势",
	"lvl" : 80,
	"damage_type" : "砸伤",
]),
([
	"action" : "$N口中高唱「降魔咒」，一招「大三昧光明势」挥出，$w幻化的漫天的轮影犹如行云流水般涌向$n",
	"skill_name" : "大三昧光明势",
	"lvl" : 100,
	"damage_type" : "瘀伤",
]),
([
	"action" : "$N面现瑞气，以无上降魔大法催动「大般若光明势」，$w舞出的光云慢慢逼近$n。",
	"skill_name" : "大般若光明势",
	"lvl" : 120,
	"damage_type" : "瘀伤",
]),
([
	"action" : "$N提一口真气，手中$w上下翻飞，轮番砸出，这「大智慧光明势」让$n眼前轮影乱舞，应接不暇。",
	"skill_name" : "大智慧光明势",
	"lvl" : 140,
	"damage_type" : "砸伤",
]),
([
	"action" : "$N面带微笑，眼露慈光，全身所散发出的「大慈悲光明势」气劲宛如惊涛骇浪，$w一波接一波地涌向$n",
	"skill_name" : "大慈悲光明势",
	"lvl" : 160,
	"damage_type" : "瘀伤",
]),
([
	"action" : "$N双手高举$w，大喝一声使出「大圆满光明势」自上而下斩向$n，其快绝无比，气势汹涌，已达圆满之境",
	"skill_name" : "大圆满光明势",
	"lvl" : 180,
	"damage_type" : "刺伤",
]),
});

string *wushuai_msg = ({
HIR"$N伸手搭在法轮上往斜里一拨，法轮在空中划出一道弧线，向$n飞去，势如猛牛！"NOR,
HIR"$N不待法轮落地，抢上前伸脚一挑一送，法轮陡然飞起，从不可思议的角度撞向$n"NOR,
HIR"$N吐气发力，双掌齐推，法轮去势劲急，呜的一声冲向$n。"NOR,
HIR"$N双手箕张，拦在$n身前，法轮在空中旋转而回，袭向$n的后脑。"NOR,
HIR"$N霹雳般一声断喝，侧身单拳硬生生击在法轮上，法轮方向猛的一转，直追向$n。"NOR,
HIR"$N右手圈转，将法轮轻轻巧巧接在手中，紧接着手腕急翻，左手平推，法轮旋向$n的前胸。"NOR,
HIR"$N凭内力将法轮定在手掌心上急旋，眼光扫向$n，法轮紧跟着飞了过去。"NOR,
HIR"$N跃入半空，双掌自上而下推出，法轮凭空加速，威势惊人。"NOR,
HIR"$N抢前几步，手腕一转，借势送出法轮，随后向$n虚拍几掌，封住了$n的退路。"NOR,
});

string *parry_msg = ({
HIC"$n不躲不避，手中法轮摆开，在$N跟前形成了一道光幕，$N此招根本无法递出。\n"NOR,
HIM"却见$n踏前一步，手中法轮翻飞，力道威猛，$N见势心怯，闪身而退。\n"NOR,
HIY"$n轮法突变，法轮带着风声飞舞出去，后发先至，在$N还没攻出时就破了$N的招数。\n"NOR,
MAG"但见$n力贯双臂，举法轮硬架，乒的一声震开了来势汹汹的$N。\n"NOR,
MAG"$n看准来势，法轮摆个天地势，将$N进路封死，$N这招只发得一半就攻不进去了。\n"NOR,
MAG"$N一招运足，才发现$n手中法轮指向自己的$l，正是此招的空门，连忙收招闪避。\n"NOR,
});

string  *msg = ({
CYN"$w"CYN"已彷佛幻化成了千百条般挥舞不息，漫天的轮影形成了一个多角形的图案，每一轮的攻出都是如此凌厉而猛辣"NOR,
HIY"空中那几只法轮对击，声若龙吟，悠悠不绝，就在$n一呆之际，法轮飞砸了出去！"NOR,
YEL"呜呜声响中，法轮旋转飞舞着撞向$n，在$p便要挡隔时，却绕过他飞到了身後"NOR,
YEL"$w"YEL"法轮连续掷出，连续飞回，绕著$n兜个圈子，忽高忽低，或正或斜，所发声音也是有轻有响，扰得$n眼花撩乱，心神不定"NOR,
YEL"一声「小心了！」，蓦然间法轮合体归一，并排向$n撞去，势若狂牛冲阵，威不可挡"NOR,
HIC"蓦而$n身前五丈方圆内起了一阵回旋的风暴，光华灿然中，法轮飞舞而出，几似龙降九天"NOR,
HIG"这$w"HIG"好似彼比连接在一起的巨龙，在$n身前盘旋纵横，鳞甲闪烁，好像宇宙之间，已全被这所遮掩无馀"NOR,
MAG"只见$w"MAG"呜呜响声不绝，绕著$n上下翻飞，掀的阵阵狂风有如刀割，似要把$n从中劈开"NOR,
YEL"突然狂风大作，激荡中那$w"YEL"相碰相撞，数轮归一，合并了向$n砸去"NOR,
HIM"法轮再次合围，紫电精芒围著$n的四周旋舞闪射，千百轮影幻映出一幅美丽而眩目的图案，似是一片多角形的紫色雪晶体"NOR,
YEL"法轮在$n身前环饶，猛地向$p迎头击下，接着又飞来一轮，一抄一送，呜呜声响，兜向$n$l"NOR,
YEL"呼呼飞啸声中，那几只法轮或直飞、或斜飞、或回旋、或下坠、或上升，霎时间$n的全部退路已被封死"NOR,
BLU"猛地里$w"BLU"向$n$l飞砸下，在$p沉肩卸避之时，法轮又突然上飞击出，砸向$p的$l"NOR,
YEL"那法轮飞旋砸到，$n却并不回头，听风辨器，一一挡开，但法轮便如长上了眼睛一般，竟然又旋飞到了$n$l"NOR,
HIY"随着$N的厉吼，$w"HIY"蓦而急颤晃动，轮身嗡嗡震响，耀目的电光金蛇四射迸闪，飞掠周遭，迅捷无匹的击向$n"NOR,
});

string  *msga = ({
HIY"$N伸手搭在法轮上往斜里一拨，法轮在空中划出一道弧线，向$n飞去。\n"NOR,
HIC"$N不待法轮落地，抢上前伸脚一挑一送，法轮陡然飞起，撞向$n的。\n"NOR,
BLU"$N吐气发力，双掌齐推，法轮去势劲急，呜的一声冲向$n。\n"NOR,
HIY"$N双手箕张，拦在$n身前，法轮在空中旋转而回，袭向$n的后脑。\n"NOR,
HIY"$N右手圈转，将法轮轻轻巧巧接在手中，紧接着手腕急翻，左手平推，法轮旋向$n的前胸。\n"NOR,
HIY"$N跃入半空，双掌自上而下推出，法轮凭空加速，威势惊人。\n"NOR,
HIW"$N抢前几步，手腕一转，借势送出法轮，随后向$n虚拍几掌，封住了$n的退路。\n"NOR,
});

string  *msgd = ({
HIC"$n见法轮旋转奇疾，锋利只怕犹如刀剑，连忙一个筋斗跃起，法轮呼的从脚下飞过。\n\n"NOR,
HIC"$n不慌不忙，如陀螺般急转了个圈，避了开来。\n\n"NOR,
HIC"$n措手不及，危急中弯腰缩头，法轮刚好从头顶飞过。\n\n"NOR,
HIC"$n一个侧翻，身体在空中横滚出去，避过了这雷霆一击。\n\n"NOR,
HIC"$n大出意料之外，无奈之下只得滚倒在地，险些未能避过。\n\n"NOR,
HIC"$n看准来势，双手一兜一分，将法轮荡了开去。\n\n"NOR,
HIC"$n倒退几步，拧腰一闪，将法轮让了开去。\n\n"NOR,
HIC"$n双掌运足内力疾拍，法轮被荡得失了准头，从$n身旁飞了过去。\n\n"NOR,
});
int valid_enable(string usage) { return usage == "hammer" || usage == "parry"; }

void skill_improved(object me)
{
	int skill = me->query_skill("xiangfu-lun", 1);
	if( skill >= 200 && !me->query("ryl_add")){
		me->set("ryl_add", 1);   
		tell_object(me, HIW"\n忽然，你感道内息越转越快，瞬时功力已经上升到了一个新的境界！"NOR);
		me->add("max_jingli", skill/2+random(skill));
		me->add("max_neili", skill/2+random(skill));
	}
}

int valid_learn(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon")) || ((string)weapon->query("skill_type") != "hammer") && ((string)weapon->query("skill_type") != "lun"))
		return notify_fail("你使用的武器不对。\n");
	if( me->query_str(1) <=35)
		return notify_fail("你的臂力不够学降伏轮。\n");
	if( me->query("max_neili") < 2000)
		return notify_fail("你的内力不够。\n");
	if( me->query_skill("longxiang-boruo", 1) <= 160)
		return notify_fail("需要有第八层以上龙象般若功火候,才能学降伏轮。\n");
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
	int i, level, j;
	level = (int) me->query_skill("xiangfu-lun",1);
    //npc 只能用这招式，好像没必要
	
	if( !userp(me)
	 && me->query("env/invisibility")
	 && me->query("master_user/user")){
		return ([
			"action": msg[random(sizeof(msg))],
			"damage": 200+random(100),
			"damage_type":random(2)?"砸伤":"瘀伤",
			"dodge": 5,
			"force": 250+random(250)
		]);
	}
	//五衰的pfm
	/*
	if(me->query_temp("xfl/wushuai")) {
	   for(i = sizeof(wushuai_msg); i > 0; i--) {
		if(level > wushuai_msg[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
                    return ([
                            "action": wushuai_msg[random(sizeof(wushuai_msg))],
                            "damage_type":random(2)?"砸伤":"瘀伤",
                            "dodge":random(25),
                            "force":250+random(100),
                            "parry":random(30),
                            "damage":250+random(100),
                            ]);
	    }
	   }
	}*/
     if(me->query_temp("xfl/wushuai")) {
	   
                    return ([
                            "action": wushuai_msg[random(sizeof(wushuai_msg))],
                            "damage_type":random(2)?"砸伤":"瘀伤",
                            "dodge":random(25),
                            "force":250+random(100),
                            "parry":random(30),
                            "damage":250+random(100),
                            ]);
	    
	   }
	//非五衰
	return ([  
				"action": action[j]["action"],
				"lvl": action[j]["lvl"],
				"damage_type" : action[j]["damage_type"],
				"force":200+random(350),
				"dodge":random(30)-10,
				"damage":180+random(50),
				"parry":random(20),
			]);
	
}

mixed query_parry_msg(object weapon, object me, int attack_type)
{
	if (objectp(weapon = me->query_temp("weapon")) 
	&& (((string)weapon->query("skill_type") == "hammer") || ((string)weapon->query("skill_type") == "lun"))  //|| ((string)weapon->query("skill_type") == "lun")
	&& me->query_skill_mapped("hammer") == "xiangfu-lun"
	&& me->query_skill_mapped("parry") == "xiangfu-lun")
		return parry_msg[random(sizeof(parry_msg))];
}

int practice_skill(object me)
{
	int lvl = me->query_skill("xiangfu-lun", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;
	if ( me->query("jingli") < 50)
		return notify_fail("你的体力太低了。\n");
	if ( me->query("neili") < 20)
		return notify_fail("你的现在的内力不足,无法继续练降伏轮。\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xiangfu-lun/" + action;
}


mixed hit_ob(object me, object victim,int damage)
{
	object wp1, wp2; 
	string msg;
	int p, lx=me->query("lx/gree");
    damage = (int)me->query_skill("xiangfu-lun",1) + (int)me->query_skill("longxiang-boruo",1)/2; 
	wp1 = me->query_temp("weapon");
    wp2= victim->query_temp("weapon");
	//if( !objectp(wp2= victim->query_temp("weapon")) )
   // if( !objectp(wp1)||wp1->query("type")!="hammer" )
		//return;
            
	if( me->query_skill("longxiang-boruo",1)<350
        ||  me->query_skill("xiangfu-lun", 1) < 350 
	    || !me->query("jiali")
	    || me->query("neili") < 1000 
		|| me->query_skill_mapped("force")!="longxiang-boruo"
	    || me->query_skill_mapped("parry") != "xiangfu-lun" )
		return;

	if (me->query("env/锁")
		&& wp2 
		&& random(me->query("combat_exp")) > victim->query("combat_exp")/ 2 )

    {
		message_vision(HIC"$N手臂暴长，施展「锁」字诀，"+wp1->name()+HIC"探出，嚓的一声锁住了$n"+wp2->name()+HIC"。\n"NOR, me,victim);
		if( random(me->query_str(1)) > victim->query_str(1) ) {
			me->add("neili", -150);
			message_vision(HIR+me->query("name")+HIR"运劲回拉，只听得$N臂骨喀的一声，险些就被拉断，$N剧痛之下手一松，"+wp2->name()+HIR"被夺了过去丢在地上！\n"NOR, victim);
			wp2->unequip();
			wp2->move(environment(victim));
            victim->start_busy(2+random(2)); 
		}
		else if(random(me->query_str(1)) > victim->query_str(1)/3*2){           
			me->add("neili", -50);
			message_vision(HIR+me->query("name")+HIR"运劲回拉，$N被带得踉跄几步，但觉虎口剧痛，鲜血飞溅，"+wp2->name()+HIR"脱手飞出！\n"NOR, victim);
			victim->receive_wound("qi",victim->query_str(1)*me->query_skill("xiangfu-lun", 1)/3,me);
			victim->receive_damage("qi",victim->query_str(1)*me->query_skill("xiangfu-lun", 1),me);
			victim->apply_condition("no_perform",1+random(2));
			wp2->unequip();
			wp2->move(environment(victim));
		}
		else if( me->query_temp("shield") ){           
			me->add("neili", -50);
			message_vision(HIY"$N借势前冲，"+wp2->name()+HIY"直刺过去，但被"+me->query("name")+"护体真气荡得滑了开去。\n"NOR, victim);
		}
		//else message_vision(HIY"$N借势前冲，"+wp2->name()+HIY"直刺"+me->query("name")+"，"+me->query("name")+"变招奇快，"+wp1->name()+HIY"一抖松脱，纵身退了开去。\n"NOR, victim);
	}
  
    if (me->query("quest/wulun/pass")&&random(10)>5)
	{

	    switch(random(5)) {
                         case 0:
                                //msg=msga[random(sizeof(msga))];
						        message_vision(HBRED"$N龙象般若功沛然而发，凭内力将法轮定在手掌心上急旋，眼光扫向$n，法轮紧跟着飞了过去。\n"NOR,me,victim);
                                if (random(me->query_skill("hammer",1)) > random(victim->query_skill("parry",1) /3) ) {
                                        
                                        damage = damage*lx/7 + random(damage);
                                        message_vision(YEL"$n一不小心为高速旋转的法轮边齿所划伤，一阵剧痛传来，顿时鲜血飞溅。\n"NOR,me,victim);
										if( victim->query("qi")> 0)
                                        {  
                                             victim->receive_damage("qi", damage,me);
                                             victim->receive_wound("qi", damage/3,me);
                                        }
                                        me->add("neili", -200);
                                        me->add("jingli", -100);
                                       // p = (int)victim->query("qi")*100/(int)victim->query("max_qi");
                                        //msg += damage_msg(damage, "瘀伤");
                                      //  msg += "( $n"+eff_status_msg(p)+" )\n";
                                     //   if(wizardp(me) && me->query("env/test")) tell_object(me,sprintf("1-hit:damage:%d   ",damage));
                                        
                                }
                                else {
                                        me->add("neili", -100);
                                        //msg += msgd[random(sizeof(msgd))];
                                }
                               // message_vision(msg, me, victim);
                                break;
                    
                         case 1:
                                me->add_temp("apply/damage", me->query_skill("xiangfu-lun",1)/6 );
                                //msg=msga[random(sizeof(msga))];
								message_vision(HBRED"$N霹雳般一声断喝，侧身单拳硬生生击在法轮上，法轮方向猛的一转，直追向$n而去。\n"NOR,me,victim);
                                COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);                                
                                me->add_temp("apply/damage", -me->query_skill("xiangfu-lun",1)/6  ); 
                                me->add("neili", -100);
                                me->add("jingli", -50);
                                break;
                         case 2:
                                //msg=msga[random(sizeof(msga))];
                                message_vision(HIB"$N运起龙象般若功，口中不断念念有词，似乎是一种梵唱，引动周围的空气嗡嗡作响。\n"NOR,me,victim);
                                if (random(me->query("combat_exp")) > random(victim->query("combat_exp") /3) ) {
                                        //damage = (int)me->query_skill("xiangfu-lun",1) + (int)me->query_skill("longxiang-boruo",1);
                                        damage = damage/2 + random(damage);
										damage=damage/3;
										message_vision(RED"$n从没遇到这种情况，一时不查，大脑一阵剧烈的头疼传来。\n"NOR,me,victim);
                                        if( victim->query("neili")> 0)
                                        {  
                                             victim->add("neili", -damage);
                                             victim->receive_wound("jing",random(500),me);
                                        }
                                        me->add("neili", -200);
                                        me->add("jingli", -100);
                                       
                                }
                                else {
                                        me->add("neili", -150);
										message_vision(HIC"$n经验极其丰富，看破了$n的企图，冷笑一声，运功将双耳屏蔽，丝毫不为其影响。\n"NOR,me,victim);
                                        //msg += msgd[random(sizeof(msgd))];
                                }
                                //message_vision(msg, me, victim);
                                break;
                        case 3:
                                me->add_temp("apply/hammer", me->query_skill("force",1)/5); 
                                me->add_temp("apply/damage", me->query_skill("xiangfu-lun",1)/6  ); 
                                message_vision(HBBLU"$N趁其不备，将急速飞回的五个法轮再次连续飞出，宛如一串连珠一般，正是【五轮飞转】绝技。\n"NOR,me);
								victim->add_busy(1+random(1));
								COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
                                me->add_temp("apply/damage", -me->query_skill("xiangfu-lun",1)/6 ); 
                                me->add_temp("apply/hammer", -me->query_skill("force",1)/5 ); 
                                me->add("neili", -100);
                                me->add("jingli", -50);
                                break;
                       case 4:
                                msg=msga[random(sizeof(msga))];
                                if ( random(me->query_con()+me->query_str())*3 > victim->query_dex() ) {
                                        msg+=HIY"五只轮子在空中呜呜作响，配合龙象波若功的梵唱绝技，$n感觉一阵胸闷，头疼欲裂。\n"NOR;
                                        damage = damage+ random(damage);
										damage=damage/4;
                                        if( victim->query("jingli")> 1000)
                                        {  
                                             msg+=HIR"$n的脑海中回荡着一阵又一阵的梵唱，似乎有小刀子在哪儿不断抠挖，显然精力大损。\n"NOR;
											 victim->add("jingli", -random(1000));
                                            
                                        }
                                        me->add("neili", -400);
                                        me->add("jingli", -100);
                                     
                                }
                                else {
                                        me->add("neili", -150);
                                        msg += msgd[random(sizeof(msgd))];
                                }
                                message_vision(msg, me, victim);
                                break; 
                
				//return 1;
		}
	  }

}
