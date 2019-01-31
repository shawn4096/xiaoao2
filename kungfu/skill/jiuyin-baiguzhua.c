// jiuyin-baiguzhua.c 九阴白骨爪

#include <ansi.h>
inherit SKILL;
mapping *action = ({
([
	"action" : BLU"$N势若疯虎，形若邪魔，双爪如钢抓铁钩，左手手腕翻处，右手疾伸，五根手指抓向$n$l"NOR,
	"lvl" : 0,
   	"damage_type" : "抓伤"
]),
([
	"action" : BLU"突然人影闪动，$N迫到$n身后，袖中伸出手，五根手指向$n$l插了下去"NOR,
	"weapon" : "五指",
	"lvl" : 10,
	"damage_type" : "刺伤"
]),
([
	"action" : BLU"$N手臂关节喀喇一响，手臂斗然长了半尺，一掌按在$n$l，五指即要插进"NOR,
	"weapon" : "手指",
   	"lvl" : 20,
	"damage_type" : "刺伤"
]),
([
	"action" : BLU"$N双手微张，十根尖尖的指甲映出灰白光忙，突然翻腕出爪，五指猛地插落"NOR,
	"weapon" : "手爪",
	"lvl" : 30,
   	"damage_type" : "刺伤"
]),
([
	"action" : BLU"$N左手突然在$n眼前上围下钩，左旋右转，连变了七八般，蓦地里右手一伸，五根手指直插$n$l"NOR,
	"weapon" : "五根手指",
	"lvl" : 40,
	"damage_type" : "刺伤"
]),
([
	"action" : BLU "$N左爪虚晃，右爪蓄力，一招" HIR "「勾魂夺魄」" BLU "直插向$n的$l" NOR,
	"lvl"   : 100,
	"skill_name" : "勾魂夺魄" ,
	"damage_type" : "抓伤"
]),
([
	"action" : BLU "$N双手连环成爪，爪爪钩向$n，" HIR "「九子连环」" BLU "已向$n的$l抓出" NOR,
	"lvl"   : 120,
	"skill_name" : "九子连环" ,
	"damage_type" : "抓伤"
]),
([
	"action" : BLU "$N身形围$n一转，使出" HIR "「天罗地网」" BLU "，$n的$l已完全笼罩在爪影下" NOR,
	"lvl"   : 140,
	"skill_name" : "天罗地网" ,
	"damage_type" : "抓伤"
]),
([
	"action" : BLU "$N使一招" HIR "「风卷残云」" BLU "，双爪幻出满天爪影抓向$n全身" NOR,
	"lvl"   : 160,
	"skill_name" : "风卷残云" ,
	"damage_type" : "抓伤"
]),
([
	"action" : BLU "$N吐气扬声，一招" HIR "「唯我独尊」" BLU "双爪奋力向$n天灵戳下" NOR,
	"lvl"   : 180,
	"skill_name" : "唯我独尊" ,
	"damage_type" : "抓伤"
]),
});

int valid_enable(string usage)
{
	return usage=="claw" || usage=="parry" ;
}

int valid_combine(string combo) 
{
	object me;
	me = this_player(); 

	if ( me->query_int(1) > 30)
		return combo=="cuixin-zhang"; 
}


int valid_learn(object me)
{
	if( !me->query("quest/jiuyin2/pass") && !me->query("quest/jiuyin1/pass"))
		return notify_fail("你不可练习九阴白骨爪。\n");
	if( (int)me->query_skill("jiuyin-baiguzhua", 1 ) < 150 )
		return notify_fail("你现在不能练习九阴白骨爪。\n");
	if( (int)me->query_skill("jiuyin-shenzhua", 1 ) >= 1 )
		return notify_fail("会九阴神抓了，还想学九阴白骨爪？\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练九阴白骨爪必须空手。\n");
	if ((int)me->query_skill("claw", 1) < 41)
		return notify_fail("你的基本爪功火候不够，无法学习。\n");
	if ((int)me->query("max_neili") < 1000)
		return notify_fail("你的内力太弱，无法练九阴白骨爪。\n");
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
	level   = (int) me->query_skill("jiuyin-baiguzhua",1);
	
	if (me->query_temp("jybgz/bgz"))
	{
			return ([
				"action":	action[j]["action"],
				"weapon":	action[j]["weapon"],
				"damage":	300+random(100),
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"force":	250 + random(300),
				"dodge":	random(30)-10,
				"parry":	random(20),
			]);
	}
	for(i = sizeof(action); i > 0; i--) {
		if(level >= action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			
			return ([
				"action":	action[j]["action"],
				"weapon":	action[j]["weapon"],
				"damage":	200+random(100),
				"lvl":		action[j]["lvl"],
				"damage_type":	action[j]["damage_type"],
				"force":	250 + random(300),
				"dodge":	random(30)-10,
				"parry":	random(20),
			]);
		}
	}
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 50)
		return notify_fail("你的体力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练九阴白骨爪。\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"jiuyin-baiguzhua/" + action;
}

void skill_improved(object me)
{
	tell_object(me, "你练着练着忽然从心底生出一股邪念！\n");
	me->add("shen", -(me->query_skill("jiuyin-baiguzhua", 1)/100));
}

mixed hit_ob(object me, object target)
{
    string msg;
    int j,damage;
    j = me->query_skill("jiuyin-baiguzhua", 1);
	damage=j+me->query_skill("poision",1)+me->query_skill("taoism",1);
	damage=damage*me->query_str()/6+random(damage);

    if (random(me->query_con()) >= target->query_con()/2
		&& j > 450 
		&& me->query_skill("force",1) > 450
		&& me->query("jingli")>300
		&& random(10)>6
		&& random(me->query("combat_exp")) > target->query("combat_exp")/2 
		&& me->query("neili")>500)
   {
          switch(random(3))
          {
            case 0 :
               msg = YEL "$N右手成爪，吟道“面北背南朝天坐，气行任督贯大椎。意聚丹田一柱香，分支左右聚掌心。打开气海命门穴，气满冲贯十指爪。”！\n";
               if (random(me->query_skill("claw",1))>target->query_skill("parry",1)/2)
               {               
				   msg = msg + "$n只觉头顶处被$N手指插入，头疼欲裂，痛叫一声！\n"NOR; 
				   target->recevied_damage("qi",  damage,me);
				   me->add("neili",-600);
				   target->add_condition("bgz_poison", 2+random(2));
               }else msg = msg + HIW"$n急忙向旁闪开！\n"NOR; 
               break;
            case 1 :
               msg = HIR "$N左爪轻晃，吟道“打开丹田前后门，三昧磷火化无形。吸进鬼狱阴鬼精，阴功在此更为进”。斜插$n额头而去！\n";
			   if (random(me->query_str())>target->query_dex()/2)
			   {
			   
				   msg += "$n只觉前额剧痛，已被$N插了个满面挑花开！\n"NOR;
				   target->recevied_damage("qi",  damage,me);               
				   target->add_condition("bgz_poison", 2+random(3));
				   me->add("neili",-400);
			   } else msg = msg + HIC"$n一个铁板桥躲过此招，不由滴吓了一身冷汗！\n"NOR; 
               //message_vision(msg, me, target);
               
               break;
			case 2 :
               msg = HIB "$N长啸一声，吟道“五指发劲，无坚不破，摧敌首脑，如穿腐土”，双手指力弥漫，嗤嗤有声，直插$n头顶而去！\n";
			   if (random(me->query_str())>target->query_str()/2)
			   {
			   
				   msg += "$n只觉头顶剧痛无比，宛如天塌地陷一般，眼前一昏，被$N插中头顶！\n"NOR;
				   target->recevied_damage("qi", damage,me);               
				   target->add_condition("bgz_poison", 2+random(3));
				   me->add("neili",-400);
			   } else msg = msg + HIC"$n冷哼一声，闪身躲开！\n"NOR; 
               //message_vision(msg, me, target);
               
               break;
          }         
          message_vision(msg, me, target);
   }
}
