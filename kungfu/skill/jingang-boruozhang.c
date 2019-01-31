// jingang-boruozhang.c -金刚般若掌
#include <ansi.h>;
#include "/kungfu/skill/eff_msg.h";
inherit SKILL;
string *xue_name = ({ 
"劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
}); 

mapping *action = ({
([
	"action" : "$N前腿踢出，后腿脚尖点地，一式「横空出世」，二掌直出，攻向$n的上中下三路",
	"damage_type" : "瘀伤",
	"lvl" : 0,
	"skill_name" : "横空出世"
]),
([
	"action" : "$N左掌划一半圆，一式「长虹贯日」，右掌斜穿而出，疾拍$n的胸前大穴",
	"damage_type" : "瘀伤",
	"lvl" : 12,
	"skill_name" : "长虹贯日"
]),
([
	"action" : "$N使一式「云断秦岭」，右掌上引，左掌由后而上一个甩劈，斩向$n的$l",
	"damage_type" : "劈伤",
	"lvl" : 18,
	"skill_name" : "云断秦岭"
]),
([
	"action" : "$N左掌护胸，右拳凝劲后发，一式「铁索拦江」，缓缓推向$n的$l",
	"damage_type" : "瘀伤",
	"lvl" : 24,
	"skill_name" : "铁索拦江"
]),
([
	"action" : "$N使一式「狂风卷地」，全身飞速旋转，双掌一前一后，猛地拍向$n的胸口",
	"damage_type" : "瘀伤",
	"lvl" : 30,
	"skill_name" : "狂风卷地"
]),
([
	"action" : "$N合掌抱球，猛吸一口气，一式「怀中抱月」，双掌疾推向$n的肩头",
	"damage_type" : "瘀伤",
	"lvl" : 36, 
	"skill_name" : "怀中抱月"
]),
([
	"action" : "$N向上高高跃起，一式「高山流水」，居高临下，掌力笼罩$n的全身",
	"damage_type" : "瘀伤",
	"lvl" : 42,
	"skill_name" : "高山流水"
]),
([
	"action" : "$N使一式「摘星换斗」，劲气弥漫，双掌如轮，一环环向$n的$l斫去",
	"damage_type" : "劈伤",
	"lvl" : 48,
	"skill_name" : "摘星换斗"
]),
([
	"action" : "$N两掌上下护胸，一式「翻江搅海」，骤然化为满天掌雨，攻向$n",
	"damage_type" : "瘀伤",
	"lvl" : 54,
	"skill_name" : "翻江搅海"
]), 
([
	"action" : "$N一式「金刚伏魔」，双手合十，对着$n微微一揖，全身内劲如巨浪般汹涌而出",
	"damage_type" : "瘀伤",
	"lvl" : 60,
	"skill_name" : "金刚伏魔"
])
});

// for pfm zhangdao
mapping *action1 = ({
([
	"action" : "$N面带微笑，一招「烈火烧身」，举手掌对着$n连环砍了八八六十四刀，刀气纵横，宛如烈火般扑向$p，迅雷不可挡",
	"lvl" : 0,
	"skill_name" : "烈火烧身",
	"damage_type" : "割伤"
]),
([
	"action" : "$N运起内功一招「点木生火」，在手掌上带出火红的无比劲气，迅速划了一个大弧，从上而下劈向$n的$l",
	"lvl" : 20,
	"skill_name" : "点木生火",
	"damage_type" : "割伤"
]), 
([
	"action" : "$N手臂一沉一拉，使出「张弓望月」，手掌划出一道雪亮刀光，就在$n躲避之时猛地拦腰反切，劈向$n的$l",
	"lvl" : 40,
	"skill_name" : "张弓望月",
	"damage_type" : "割伤"
]),
([
	"action" : "$N挥舞手掌上劈下撩，左挡右开，使出一招「烈火腾云」，卷起阵阵刀风，每一圈都都划出不同的气流，齐齐罩向$n",
	"lvl" : 60,
	"skill_name" : "烈火腾云",
	"damage_type" : "割伤"
]),
([
	"action" : "$N一招「火中取栗」，划个大圈后左脚跃步落地，手掌往前直伸，刀走剑势，挟着炙热的风声点向$n的$l",
	"lvl" : 90,
	"skill_name" : "火中取栗",
	"damage_type" : "刺伤" 
]),
([
	"action" : "$N腾空而起，半空中一招「玉石俱焚」猛烈扑下，手掌迅速连劈，满天流光般的刀影排山倒海般地向$n的全身卷去",
	"lvl" :100,
	"skill_name" : "玉石俱焚",
	"damage_type" : "割伤"
]),
});

int valid_enable(string usage) { 
	if (this_player()->query("sl/jgbr/pass")) return usage=="strike" ||  usage=="parry";
    else return notify_fail("你听过金刚般若掌招式，但却无法使用。\n");
}

int valid_combine(string combo) 
{
	object me;
	me = this_player(); 

	if ( me->query_int(1) > 40)
		return combo=="jingang-zhi"; 
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练金刚般若掌必须空手。\n");
	if ( me->query_skill("yijin-jing", 1) < 300)
		return notify_fail("你的易筋经内功火候不够，无法学金刚般若掌。\n");
	if ( me->query_int(1) > 30){
		return 1;
	}
	else {
		if ( me->query_skill("jingang-quan", 1)
		 && me->query_skill("yizhi-chan", 1)
		 && me->query_skill("longzhua-gong", 1)
		 && me->query_skill("nianhua-zhi", 1)
		 && me->query_skill("qianye-shou", 1)
		 && me->query_skill("ruying-suixingtui", 1)
		 && me->query_skill("sanhua-zhang", 1))
			return notify_fail("你的功力不够，无法同时学习两种以上的上乘功夫。\n");
	}
	if ((int)me->query("max_neili") < 600)
		return notify_fail("你的内力太弱，无法练般若掌。\n");
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
	int i, level, j, num=0;
	object ob;

	level = (int)me->query_skill("jingang-boruozhang",1);
	ob = me->select_opponent();	
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action": action[j]["action"],
				"damage_type": action[j]["damage_type"],
				"lvl": action[j]["lvl"],
				"force": 150 + random(300),
				"dodge": random(30),
				"damage": 100+random(80),
				"parry": random(30),
			]);
		}
	}
}

int practice_skill(object me)
{
	int lvl = me->query_skill("jinbang-boruozhang", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 40)
		return notify_fail("你的精力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练般若掌。\n"); 
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}


string perform_action_file(string action)
{
	return __DIR__"jingang-boruozhang/" + action;
}


int hit_ob(object me, object ob, int damage)
{
        string name,msg;
        int skill, neili, neili1, sh;
        int j = 0;
		skill = me->query_skill("jingang-banruozhang", 1);
        neili = me->query("neili");
        neili1 = ob->query("neili");
        name = xue_name[random(sizeof(xue_name))];

         	                  
        if(random(me->query_str(1)) > ob->query_dex(1)/2
         && me->query("combat_exp") > ob->query("combat_exp")/2
         && me->query_skill_mapped("parry") == "jingang-banruozhang"
         && neili > 3000 
         && skill > 450 
         && random(10) > 6){
                
				switch (random(3))
				{
				  case 0:
                       random(2)?msg=HIY"$N内功强劲，金刚般若掌已经是外门功夫的极致，掌风凛冽，呼呼作响，带动下，$n有些站立不稳。\n"NOR:
					              msg=HIC"$N功夫极为了得，陡然一掌从$n的肋下穿过，拍在$n的"+HIR+name+HIC"。上\n"NOR;
				       ob->start_busy(1+random(2));
					   ob->receive_damage("qi",skill*3);
					   message_vision(msg,me,ob);
					   COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), userp(me)?3:1);

					break;
				  case 1:
                       ob->receive_damage("qi", (damage>2000)?2000:damage,me );
                       ob->receive_wound("qi", (damage>2000)?2000:damage,me );
				       ob->add_busy(1+random(2));
              	       j = (int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi");
              	       random(2)?message_vision(HIR "$N运起金刚掌劲力，掌向外转变成拳状收回置于腰间，后换左掌。然后忽然双掌齐出。\n"NOR,me,ob):
					           message_vision(HIB"$N丹田之气猛然喷发，劲力向右掌奔涌而出，同时右掌向前冲出，拍向$n的"+HIC+name+HIB"。\n"NOR,me,ob);
                       msg = damage_msg(damage, "瘀伤") + "( $n"+eff_status_msg(j)+" )\n";
                       message_vision(msg,me,ob);
					   COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), userp(me)?3:1);
					  break;
				  case 2:
                      message_vision(RED"$N趁$n不备，连续两掌拍出，罡风凛冽，劲气汹涌。\n"NOR,me,ob);
				      COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), userp(me)?3:1);
				      COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), userp(me)?3:1);
					  break;				
				}             
                return 1; 
          }                    
}
