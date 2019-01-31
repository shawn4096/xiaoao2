// quanzhen-jianfa 全真剑法
// Modify By River 99.5.26
inherit SKILL;
#include <ansi.h>
mapping *action = ({
([
	"action" : "$N剑影晃动，踏奇门，走偏锋，一式「分花拂柳」，$w径直刺向$n的$l",
	"lvl" : 0,
	"skill_name" : "分花拂柳",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N向前跃上一步，左手剑诀，右手$w使出一式「横行漠北」直刺$n的$l",
	"lvl" : 10,
	"skill_name" : "横行漠北",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N拔步挺腰，一式「排山倒海」，手中$w沉滞无比，缓缓挥向$n的$l",
	"lvl" : 25,
	"skill_name" : "排山倒海",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N身子微侧，$w自左而右划出一个大弧，一式「顺水推舟」，平平地向$n的$l挥去",
	"lvl" : 30,
	"skill_name" : "顺水推舟",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N回身拧腰，右手虚抱成圆，一式「马蹴落花」，手中$w中宫直进，刺向$n的$l",
	"lvl" : 50,
	"skill_name" : "马蹴落花",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N一式「开天辟地」，$w从上至下猛劈，剑锋直出，挟爆裂之声骤然斩向$n的$l",
	"lvl" : 70,
	"skill_name" : "开天辟地",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N运气施出「雷电交加」，$w逼出一道丈许青芒，闪电般破空射向$n的$l",
	"lvl" : 90,
	"skill_name" : "雷电交加",
	"damage_type" : "刺伤"
]),
([
	"action" : "$N双腿半屈半蹲，一式「人神共愤」，$w划出无数圆圈，狂风骤起，笼罩天地",
	"lvl" : 110,
	"skill_name" : "人神共愤",
	"damage_type" : "刺伤"
]),
});
//天枢、天璇、天玑、天权、玉衡、开阳、摇光
mapping *actionqs = ({
([
	"action" : HIG"$N身形向左横跨三步，抢占「天枢」位置，右手剑影晃动，轻轻吟道「一气混沌灌我形，禹步相推登阳明」，\n以极其怪异的角度径直刺向$n的$l。"NOR,
	"lvl" : 0,
	"skill_name" : "天枢",
	"damage_type" : "刺伤"
]),
([
	"action" : HIR"$N向前跃上一步，转向「天璇」，左手剑诀，轻吟道「天回地转履六甲，蹑罡履斗齐九灵」\n使出一式「横行漠北」直刺$n的$l"NOR,
	"lvl" : 10,
	"skill_name" : "天璇",
	"damage_type" : "刺伤"
]),
([
	"action" : HIY"$N拔步挺腰，跨入「天玑」位，一式「排山倒海」，口中吟道「太极阴阳少人修，吞吐开合问刚柔。」\n手中武器沉滞无比，缓缓挥向$n的$l"NOR,
	"lvl" : 25,
	"skill_name" : "天玑",
	"damage_type" : "刺伤"
]),
([
	"action" : HIB"$N身子微侧，向右前方急转，抢占「天权」位置，$w自左而右划出一个大弧，一式「顺水推舟」\n轻吟道「正隅收放任君走，动静变里何须愁？」平平地向$n的$l挥去!"NOR,
	"lvl" : 30,
	"skill_name" : "天权",
	"damage_type" : "刺伤"
]),
([
	"action" : HIM "$N回身飞起，滑落「玉衡」位置。轻吟道「生克二法随着用，闪进全在动中求。」\n右手虚抱成圆，一式「马蹴落花」，手中$w中宫直进，刺向$n的$l。"NOR,
	"lvl" : 50,
	"skill_name" : "玉衡",
	"damage_type" : "刺伤"
]),
([
	"action" : HIC"$N向空中纵起，难以想象的落到「开阳」位置。轻吟道「轻重虚实怎的是？重里现轻勿稍留。」\n一式「开天辟地」从上至下猛劈，剑锋直出，挟爆裂之声骤然斩向$n的$l。"NOR,
	"lvl" : 70,
	"skill_name" : "开阳",
	"damage_type" : "刺伤"
]),
([
	"action" : HIW"$N弯腰侧身，脚下原地转身，突然踏入「摇光」位置。轻吟道「七星运转如此妙？摇光斗转星光移。」\n运气施出「雷电交加」，手中武器逼出一道丈许青芒，闪电般破空射向$n的$l。"NOR,
	"lvl" : 90,
	"skill_name" : "摇光",
	"damage_type" : "刺伤"
]),

});


int valid_enable(string usage)
{
	return (usage == "sword") || (usage == "parry"); 
}

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("你的内力不够。\n");
	if (me->query("family/family_name")=="全真教")
	{
		if (me->query("family/generation")>3)
		{
			return notify_fail("全真教弟子需要扎实基础，非三代弟子不可学\n");
		}
		if (me->query_skill("xiantian-gong",1)<350)
		{
			return notify_fail("全真剑法是全真教高深武技，你的先天功太弱不足350，无法修习全真剑法!\n");
		}
	}
	if(!me->query_skill("xiantian-gong"))
	  if ((int)me->query_skill("yunu-xinjing", 1) < 20)
		return notify_fail("你的玉女心经火侯太浅。\n");
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
	int i, j, level,xtg;
	level = me->query_skill("quanzhen-jianfa",1);
	xtg = me->query_skill("xiantian-gong", 1);
     //七星
	if (me->query_temp("htz/lianhuan")) {
	  for(i = sizeof(actionqs); i > 0; i--){
		if(level > actionqs[i-1]["lvl"]){
			j = NewRandom(i, 20, level/5);
				return ([  
					"action":actionqs[j]["action"],
					"lvl" : actionqs[j]["lvl"],
					"force" : 100 + random(100),
					"dodge": random(20)+xtg/15,
					"damage": 100 + random(50) + xtg/10,
					"parry": random(15)+xtg/15,//原来是15
					//"weapon" : random(2)?"剑气":"剑锋",
					"damage_type" : actionqs[j]["damage_type"],
				]);           
            }
	    }
	 }
	  
	
			//合璧
		
	  else if ( me->query_temp("hebi") && random(2) || me->query_temp("hubo")) { 
		    for(i = sizeof(action); i > 0; i--){
		      if(level > action[i-1]["lvl"]){
			   j = NewRandom(i, 20, level/5);
							
				return ([  
                    "action" :random(2)? HIB + replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIB)+NOR
							   : MAG + replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"MAG)+NOR,
					"force" : 200 + random(350),
					"dodge": random(30),
					"damage": 80 + random(140),
					"parry": random(30),
					"weapon" : random(2)?"剑气":"剑锋",
					"damage_type" : random(2)?"刺伤":"割伤",
				]);
				}
			 }
		}
		else if ( me->query_temp("sanqing1")) 
		{ 
		    for(i = sizeof(action); i > 0; i--){
		      if(level > action[i-1]["lvl"]){
			   j = NewRandom(i, 20, level/5);
							
				return ([  
                    "action" :random(2)? HIB + replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIB)+NOR
							   : MAG + replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"MAG)+NOR,
					"force" : 200 + random(350),
					"dodge": random(30),
					"damage": 100 + random(140),
					"parry": random(30),
					"weapon" : random(2)?"剑气":"剑锋",
					"damage_type" : random(2)?"刺伤":"割伤",
				]);
				}
			 }
		}
			//三清
		else if( me->query_temp("sanqing")){
			for(i = sizeof(action); i > 0; i--){
		      if(level > action[i-1]["lvl"]){
			   j = NewRandom(i, 20, level/5);
				
				return ([  
					"action":HIC+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIC), NOR, HIC)+NOR,
					"lvl" : action[j]["lvl"],
					"force" : 120 + random(250) + xtg/10,
					"dodge": random(20)- 5 +xtg/15,
					"damage": 60 + random(80) + random((level+xtg)/4),
					"parry": random(15)+xtg/10,//原来是15
					//"weapon" : random(2)?"剑气":"剑锋",
					//"damage_type" : random(2)?"刺伤":"割伤",
					"damage_type" : action[j]["damage_type"],
				]);
				}
			}
		}

			//连
		else if( me->query_temp("qzjf/lian")){
			for(i = sizeof(action); i > 0; i--){
		      if(level > action[i-1]["lvl"]){
			   j = NewRandom(i, 20, level/5);	
				return ([  
					"action":HIR+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIR), NOR, HIR)+NOR,
					"lvl" : action[j]["lvl"],
					"force" : 120 + random(250) + xtg/10,
					"dodge": random(20)- 5 +xtg/15,
                    "damage": 100 + random(50) + xtg/10,

					"parry": random(15)+xtg/10,//原来是15
					//"weapon" : random(2)?"剑气":"剑锋",
					"damage_type" : action[j]["damage_type"],
				]);
				}
			  }
			}						
		else {
		for(i = sizeof(action); i > 0; i--){
		  if(level > action[i-1]["lvl"]){
			j = NewRandom(i, 20, level/5);	
			return ([
				"action": action[j]["action"],
				"force" : 100 +random(250),
				"dodge": random(20)-10,
				"parry": random(10),
				"damage": 80 +random(80),
				"lvl": action[j]["lvl"],
				"damage_type": action[j]["damage_type"],
			]);
		  }
		}
	}	  
	
	
}

int practice_skill(object me)
{
	object weapon;
	if (!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query("neili") < 10)
		return notify_fail("你的内力不够练全真剑法。\n");
	if ((int)me->query("jingli") < 30)
		return notify_fail("你的体力不够练全真剑法。\n");
	me->receive_damage("jingli", 20);
	me->add("neili", -5);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"quanzhen-jianfa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
//      增加全真剑诀，辅助攻击，概率很低
        object weapon; 
        int i,damage;
        weapon = me->query_temp("weapon");
        i = me->query_skill("quanzhen-jianfa", 1);
		damage=i+me->query_skill("xiantian-gong", 1)+me->query_skill("tiangang-beidouzhen", 1);
		damage=damage*me->query_str()/20+random(damage);

        if( !userp(me) && random(2) ) return 0;

        if( !weapon || weapon->query("skill_type") != "sword" ) return 0;
        //全真同归不能用剑诀
		//无剑诀不能有auto
		if( i < 450
			||me->query_skill("xiantian-gong",1)<450
			||!me->query("qzjf/tonggui")
			|| !living(victim)
			|| me->query_skill_mapped("parry") != "quanzhen-jianfa"
            || me->query_skill_mapped("force") != "xiantian-gong"
            || me->query_skill_mapped("sword") != "quanzhen-jianfa"
			|| !me->query("quest/qz/qzjf/jianjue/pass")
		) return 0;        
         
       
       if( random(me->query_str()) > victim->query_con()/2
		  && !random(3)
          && random(me->query_skill("sword",1)) > victim->query_skill("parry",1)/2 )
           {
               
                switch(random(4)){
                    case 0:
                        message_vision(HBMAG"$N忆起天罡北斗大阵中所悟的「斗柄东指，天下皆春；斗柄南指，天下皆夏」右手猛的运剑回转，剑尖中一缕剑气随劲而起！\n"NOR, me);
                        me->add_temp("apply/sword",  me->query_skill("quanzhen-jianfa", 1)/4);
						message_vision(HIG"$n一不小心为七星剑诀发出的剑气所伤，心口处一阵酸麻，手脚顿时为之一缓。\n"NOR,me,victim);
						victim->add_busy(2+random(2));
                        COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), userp(me)?3:1);
                        me->add_temp("apply/sword", -me->query_skill("quanzhen-jianfa", 1)/4);
                        break;
					case 1:
                        message_vision(HBRED"$N默念全真剑诀，「斗柄西指，天下皆秋；斗柄北指，天下皆冬。」紧接着"+weapon->name()+HBRED"猛的回转再次刺出！\n"NOR, me);
                        me->set_temp("jianjue", 1);
                        me->add_temp("apply/attack",  me->query_skill("quanzhen-jianfa", 1)/4);
						message_vision(HIG"$n为七星剑诀发出的剑气所伤，鲜血直冒。\n"NOR,me,victim);

						victim->receive_damage("qi",damage,me);
						victim->receive_wound("qi",damage/3,me);
                        COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(2)?1:3);
                        me->add_temp("apply/attack", -me->query_skill("quanzhen-jianfa", 1)/4);
                        me->delete_temp("jianjue");
					    break;
					case 2:
                        message_vision(HBGRN"$N默念七星剑诀，「北斗七星天时周运转，临兵斗阵者皆列于前。」紧接着"+weapon->name()+HBGRN"大开大合，招式迅猛，全然不要命的打法！\n"NOR, me);
                        me->set_temp("jianjue", 1);
                        me->add_temp("apply/damage",  me->query_skill("quanzhen-jianfa", 1)/4);
						//victim->receive_damage("qi",2*i+random(i));
						//victim->receive_wound("qi",i);
                        COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);
                        me->add_temp("apply/damage", -me->query_skill("quanzhen-jianfa", 1)/4);
                        me->delete_temp("jianjue");
					    break;

					case 3:
                        message_vision(MAG"$N左手捏了剑指，右手剑尖猛然回挑，「认星先从北斗来，由北往西再展开」顿时剑气纵横，将$n彻底压制！\n"NOR, me, victim);
                        victim->add_temp("lost_attack", 1);
						victim->set_temp("no_fight",1);
						
						victim->add_busy(2+random(1));
						if (!victim->query_temp("qzjf/jianjue"))
						{
							victim->add_temp("apply/attack",i/4);
							victim->add_temp("apply/dodge",i/4);
							victim->add_temp("apply/parry",i/4);
							victim->set_temp("qzjf/jianjue",i);
						}
						call_out("check_fight",5,victim);
				       break;
				}
		   }
        return 1;
}
//消除掉lost_attack 标记
void check_fight(object victim)
{
	int i;
	if(!victim) return;
	victim->delete_temp("no_fight");
	victim->delete_temp("lost_attack");
	i=victim->query_temp("qzjf/jianjue");
	if (!victim->query_temp("qzjf/jianjue"))
	{
		victim->add_temp("apply/attack",i/4);
		victim->add_temp("apply/dodge",i/4);
		victim->add_temp("apply/parry",i/4);
		victim->delete_temp("qzjf/jianjue");
		message_vision(HIW"$N内力一震，全真剑诀的压制消失！\n"NOR,victim);
	}
	return;
    
}
