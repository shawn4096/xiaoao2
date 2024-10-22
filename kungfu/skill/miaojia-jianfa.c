// hujia-daofa.c
// query("quest/雪山飞狐/武功/miaojiajianfa")是学习的基础条件
// query("quest/雪山飞狐/武功/ronghe") 是刀剑融合的标志
// query_temp("quest/雪山飞狐/武功/lengquan") 是冷泉内功yun lengquan之后的标志

#include <ansi.h>
inherit SKILL;
#include <combat_msg.h>

mapping *action = ({
([   "action" : "$N面露微笑，手中$w一抖，回身侧步，迅疾无比，剑光暴长，手中的$w挽了一个剑花洒向$n",
     "force"  : 150,
     "dodge"  : 10,
     "parry"  : 25,
     "damage" : 80,
     "lvl"    : 0,
     "damage_type":  "刺伤"
]),
([   "action" : "$N手中$w颤动的极快，只幌得$n眼花撩乱，浑不知从何攻来，$w从一个绝想不到的方位斜刺向$n",
     "force"  : 160,
     "dodge"  : 25,
     "parry"  : 30,
     "damage" : 100,
     "lvl"    : 10,
     "damage_type":  "刺伤"
]),
([   "action" : "$N暴退数尺，低首抚剑，身形突闪，剑招陡变，左撤步，手中$w骤然穿上，一闪而上刺向$n",
     "force"  : 170,
     "dodge"  : 22,
     "parry"  : 32,
     "damage" : 100,
     "lvl"    : 20,
     "damage_type":  "刺伤"
]),
([   "action" : "$N却身提步，手中的$w似挡非挡，身形一晃，疾掠而上，手中$w龙吟一声，对准$n的$l连递数剑",
     "force"  : 180,
     "dodge"  : 40,
     "parry"  : 35,
     "damage" : 125,
     "lvl"    : 30,
     "damage_type":  "刺伤"
]),
([   "action" : "$N一抖手中的$w，挽出数个剑花，笼罩了$n，剑锋往来运转如梭，手中$w“铮”然有声，往$n刺去",
     "force"  : 190,
     "dodge"  : 45,
     "damage"  : 100,
     "damage" : 100,
     "lvl"    : 40,
     "damage_type":  "刺伤"
]),
([   "action" : "$N碎步急进，提剑沿剑身方向疾速上崩，手中$w由内自外一刺，没有任何花巧，然而快得不可思议",
     "force"  : 200,
     "dodge"  : 50,
     "parry"  : 45,
     "damage" : 100,
     "lvl"    : 50,
     "damage_type":  "刺伤"
]),
([   "action" : "$N身体左转，左手剑指，微微一个转身，手中$w幻化作满天星点，手中$w却已自肋下穿出刺向$n",
     "force"  : 210,
     "dodge"  : 40,
     "parry"  : 47,
     "damage" : 100,
     "lvl"    : 60,
     "damage_type":  "刺伤"
]),
([   "action" : "$N神色微变，平剑斜洗，臂圆剑直，一招「丹凤朝阳」，剑招顿时变得凌厉无比，如匹链般洒向$n",
     "force"  : 220,
     "dodge"  : 30,
     "parry"  : 52,
     "damage" : 140,
     "lvl"    : 70,
     "damage_type":  "刺伤"
]),
([   "action" : "$N左手剑指缓缓划转，腰部一扭，一招「洗剑怀中抱月」，手中$w中宫直进，迅捷无比往$n刺去",
     "force"  : 230,
     "dodge"  : 20,
     "parry"  : 54,
     "damage" : 100,
     "lvl"    : 80,
     "damage_type":  "刺伤"
]),
([   "action" : "$N纵步上走，单腿踢向$n腰间，$n正要抽身回防，只见刹那间剑光一闪，一招「迎门腿反劈华山」",
     "force"  : 240,
     "dodge"  : 30,
     "parry"  : 62,
     "damage" : 120,
     "lvl"    : 90,
     "damage_type":  "刺伤"
]),
([   "action" : "$N矮身侧步，一招「返腕翼德闯帐」，手中$w反手疾挑而出，手中$w轻轻颤动自上而下扎向$n",
     "force"  : 250,
     "dodge"  : 65,
     "parry"  : 65,
     "damage" : 120,
     "lvl"    : 100,
     "damage_type":  "刺伤"
]),
([   "action" : "$N屈腕抬臂，一招「黄龙转身吐须」，蓦地疾退一步，又冲前三步，一道凌厉的弧光往$n刺去",
     "force"  : 260,
     "dodge"  : 40,
     "parry"  : 68,
     "damage" : 150,
     "lvl"    : 110,
     "damage_type":  "刺伤"
]),
([   "action" : "$N一招「上步云边摘月」，纵身跃起，接着却又从半空中穿下，双手握着$w，声势逼人地刺向$n",
     "force"  : 270,
     "attack" : 97,
     "dodge"  : 60,
     "parry"  : 72,
     "damage" : 150,
     "lvl"    : 120,
     "damage_type":  "刺伤"
]),
([   "action" : "$N一招「提撩剑白鹤舒翅」，手中$w“嗤”的一声斜刺向天空，随即向下“唰唰”划出一个叉字",
     "force"  : 280,
     "attack" : 100,
     "dodge"  : 45,
     "parry"  : 75,
     "damage" : 150,
     "lvl"    : 130,
     "damage_type":  "刺伤"
]),
([   "action" : "$N屈腕抬臂，左腿微抬，一招「冲天掌苏秦背剑」，右手$w猛的自下方挑起，激起一股劲风反挑$n",
     "force"  : 300,
     "dodge"  : 50,
     "parry"  : 82,
     "damage" : 150,
     "lvl"    : 140,
     "damage_type":  "刺伤"
]),
});

int valid_enable(string usage) {
   if ( this_player()->query("quest/雪山飞狐/武功/miaojiajianfa"))
                   return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 700)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 90)
                return notify_fail("你的内功火候太浅。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本剑法火候不够，无法学习苗家剑法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("miaojia-jianfa", 1))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的苗家剑法。\n");

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
        int i,level;
        object target;
        object *enemy;
		string str;
        level   = (int) me->query_skill("miaojia-jianfa",1);
        enemy = me->query_enemy();
        if(sizeof(enemy)>0)
        {
           target = enemy[random(sizeof(enemy))];
     	   if(me->query_temp("quest/雪山飞狐/武功/powerup")
		    ||(!me->query_temp("quest/雪山飞狐/武功/kongzhi")
		    && me->query_temp("quest/雪山飞狐/武功/lengquan")
		    && me->query_skill_mapped("parry") == "miaojia-jianfa"
			&& random(me->query_skill("force"))>target->query_skill("force")/4 
			&& random(me->query("combat_exp"))>target->query("combat_exp")/4
			))
		   {
			str =action[random(sizeof(action))]["action"];
			//SKILL_D("miaojia-jianfa")->query_action(me, me->query_temp("weapon"))["action"]
          	switch(random(2)){
                	case 0: str +="！\n";
						    str +=HIC"突然就在这一瞬之间，$N又刺出一剑，两剑合并一剑，本就快捷绝伦的剑法变得更加凌厉！"NOR;
							break;
                	case 1: str +="！\n";
						    str +=HIW"突然$N手中的"+weapon->name()+HIW"又是一颤，$n只觉得一缕冷风掠过，一道剑光直指$n破绽所在！" NOR;
							break;
            }
	        target->set_temp("must_be_hit",1);
			me->set_temp("quest/雪山飞狐/武功/kongzhi",1);
			//控制从这里开始，powerup招数出现之后，必须普通攻击至少两招之后才可能出现下次powerup招数
          	return ([
                	"action":str, 
                	"damage":(random(3)+3)*80,
                	"damage_type": "刺伤",
                	"dodge": random(40)+40,
                	"force": random(me->query_skill("force"))+250,
           ]);
           }
		}
        if(sizeof(enemy)>0)
        {
           target = enemy[random(sizeof(enemy))];
           if ( random(me->query_skill("force"))>(target->query_skill("force")/3) 
                && me->query("quest/雪山飞狐/武功/ronghe") 
                && !me->query_temp("quest/雪山飞狐/武功/ronghe") 
				&& random(10)>6
                && random(me->query_skill("lengquan-shengong", 1))>200
                && me->query_skill_mapped("force") == "lengquan-shengong")
                        call_out("autopfm",1,me,target);
        }
        if(me->query_temp("mjjf/lianhuan/color")
        && me->query_temp("mjjf/lianhuan/lq") ){
            str =action[random(sizeof(action))]["action"];
            return ([
                      "action" : HIB+replace_string(replace_string(str, "$w", "$W"), "$W", "$w"HIB)+NOR,
                      "damage_type": "刺伤",
                      "dodge": random(40)+10,
                      "damage":(random(3)+2)*70,
                      "force": random(me->query_skill("force"))+100,
           ]);
        }
        else if(me->query_temp("mjjf/lianhuan/color") ){
            str =action[random(sizeof(action))]["action"];
            return ([
                      "action" : HIW+replace_string(replace_string(str, "$w", "$W"), "$W", "$w"HIW)+NOR,
                      "damage_type": "刺伤",
                      "dodge": random(40)+10,
                      "force": random(me->query_skill("force"))+100,
					  "damage": 150+random(80),
           ]);
        }
        for(i = sizeof(action); i > 0; i--)
		          if(level >= action[i-1]["lvl"]) 
				 {
					/*if (me->query_temp("mjjf/lianhuan"))
					{
						return ([
						 "action" : HIY+replace_string(replace_string(str, "$w", "$W"), "$W", "$w"HIY)+NOR,
						 "damage_type": "刺伤",
						 "dodge": random(40)+10,
						 "force": random(me->query_skill("force"))+100,
						 "damage": 150+random(80),
						
						 ]);

					}*/
					return action[NewRandom(i, 20, level/5)];
				 }
                        

}

void autopfm(object me,object target)
{
        object weapon1,weapon2,* obj;
        int i;
        if(!me || !target || !me->is_fighting(target)) return;
        if(me->is_busy()) return;
       if( me->query_skill_mapped("blade") != "hujia-daofa") return;
        me->add("neili",-100);
        if (me->query("neili")<0) me->set("neili",0);
        weapon1 = me->query_temp("weapon");      
        if(!weapon1) return;
        obj = all_inventory(me);
        for(i=0; i<sizeof(obj); i++) 
          if(mapp(obj[i]->query("weapon_prop"))
             && obj[i]->query("skill_type")=="blade")
              weapon2 = obj[i];
        if(!weapon2) return;
        i = me->query_skill("sword")+me->query_skill("blade");
        
        if(random(2))  message_vision(HIC"\n紧跟着，$N顺手抽起"+weapon2->query("name")+HIC"，刀光一闪，竟然使出胡家刀法！\n"NOR,me,target);
 		else message_vision(HIC"\n$N仰天一声清啸，突然"+weapon1->query("name")+HIC"虚招一晃，"+weapon2->query("name")+HIC"向$n雷霆般地击出一刀！\n"NOR,me,target);

        weapon1->unequip(); 
        weapon2->wield();
		me->set_temp("quest/雪山飞狐/武功/ronghe",1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->delete_temp("quest/雪山飞狐/武功/ronghe");
        weapon2->unequip(); 
        weapon1->wield();       
        return; 
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("jingli") < 80)
                return notify_fail("你的体力目前没有办法练习苗家剑法。\n");

        if ((int)me->query("neili") < 70)
                return notify_fail("你的内力不够，无法练习苗家剑法。\n");
        
        me->add("jingli", -41-random(40));
        me->add("neili", -31-random(30));
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"miaojia-jianfa/" + action;
}


mixed hit_ob(object me, object victim, int damage)
{
        if (me->query("quest/雪山飞狐/武功/lengquanshengong_teach")
        && me->query_temp("lqsg/lq")
        && me->query_skill_mapped("force") == "lengquan-shengong" )
        message_vision(HIR"$N更将冷泉神功运用得出神入化，每一招，每一式均附着冷泉内劲，威力惊人！\n"NOR, me);
        if(!me->query_temp("quest/雪山飞狐/武功/kongzhi")) return;
 		if(victim->query_temp("must_be_hit")) victim->delete_temp("must_be_hit");
	    if( me->query_skill_mapped("force") != "lengquan-shengong") return;
	    if( me->query_skill_mapped("parry") != "miaojia-jianfa") return;
	    if( me->query_skill_mapped("sword") != "miaojia-jianfa") return;
        if(!me->query_temp("weapon")) return;
        if(me->query_temp("quest/雪山飞狐/武功/kongzhi")>=3)
		{
           me->delete_temp("quest/雪山飞狐/武功/kongzhi");  //删除控制标志，有机会出powerup招数
		   return;
		}
		if (me->query_temp("quest/雪山飞狐/武功/lengquan") 
            && me->query_skill_mapped("force") == "lengquan-shengong"
            && (random(me->query("combat_exp"))>(victim->query("combat_exp")/3)
            || random(me->query_skill("lengquan-shengong"))>(victim->query_skill("force")/3)))
            me->add_temp("quest/雪山飞狐/武功/kongzhi",1); //控制powerup招数
}
int ob_hit(object ob, object me, int damage) //piaojian绝技
{
	if(!me->query_temp("mjjf/piaojian"))	return 1;
	//if( me->query_skill_mapped("force") != "lengquan-shengong") return 1;
	if( me->query_skill_mapped("parry") != "miaojia-jianfa") return 1;
	if( me->query_skill_mapped("sword") != "miaojia-jianfa") return 1;
    if(!me->query_temp("weapon")) return 1;
	if (random(me->query("combat_exp"))>ob->query("combat_exp")/2
		&& random(me->query_skill("sword",1))>ob->query_skill("dodge",1)/2)
	{
       if(me->is_busy())
	   {
           message_vision(HIW"$N突然使用「飘剑」绝技，剑势飘忽不定。$n吃惊之余，招数不由变缓。\n" NOR, me,ob);
               return  -damage*2/3-random(damage/3);
	   }
	   else 
	   {
           message_vision(HIW"$N略一提气，使出「飘剑」绝技，只见$N足不沾地，运起轻功，拔剑起舞，剑势飘忽不定。" NOR, me);
           me->set_temp("quest/雪山飞狐/武功/kongzhi",1);
		   COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 3);
		   me->delete_temp("quest/雪山飞狐/武功/kongzhi");
	  }
     // me->start_perform(3,"「飘字诀」");
               return  -damage;
	}
}
