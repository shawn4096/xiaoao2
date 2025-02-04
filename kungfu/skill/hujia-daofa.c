// hujia-daofa.c
// query("quest/雪山飞狐/武功/hujiadaofa")是学习的基础条件
// query("quest/雪山飞狐/武功/ronghe") 是刀剑融合的标志
// query_temp("quest/雪山飞狐/武功/lengquan") 是冷泉内功yun lengquan之后的标志

inherit SKILL;
#include <ansi.h>
int perform_fdj(object,object);

string  *msg = ({
HIB"突然$n眼前一晕，有一种满天寒气逼来的感觉，$n躲闪不及，全身都冻僵了！"NOR,
HIB"这些$w"HIB"好像有形之物，在$n身前盘旋纵横，好像宇宙之间，已全被这所遮掩无馀"NOR,
HIB"只见$n周边寒气越来越重，狂风大作，寒气有如刀割，似要把$n从中劈开"NOR,
HIB"只见$N催动冷泉神功，$n感觉寒气越来越重，狂风大作，寒气竟也成了如刀般的利器"NOR,
HIB"突然一阵刀风袭来，$n钢要跃身闪过刀锋，不料一缕$w"HIB"已经透入$n体内"NOR,
HIB"$n周边寒气越来越重，就在$n不经意之中，$w"HIB"已经透入$n体内"NOR,
HIB"$N的刀锋突然蓝光陡强，寒气更是凝重，$n行动越来艰难"NOR,
HIB"只见$n周边寒气越来越重，突然狂风大作，寒气有如刀割，似要把$n从中劈开"NOR,
HIB"$n周边的寒气似乎渐渐加重，就在$n一呆之际，一缕$w已经透入$n体内"NOR,
HIB"突然，狂风夹杂着碎石漫天飞舞，把$n砸得遍体鳞伤"NOR,
});
mapping *action = ({
([      "action" : "$N手中$w横推，一招「推波助澜」，刀锋划了个半弧，$w一提一收，由上至下向$n砍去",
        "skill_name" : "推波助澜",
        "force"  : 120,
        "dodge"  : 30,
        "parry"  : 12,
        "lvl"    : 0,
        "damage" : 90,
        "damage_type" : "割伤",
]),
([      "action" : "$N一招「沙鸥掠波」，刀锋自下而上划了个半弧，$w一提一收，平刃挥向$n的颈部",
        "skill_name" : "沙鸥掠波",
        "force"  : 160,
        "dodge"  : 40,
        "parry"  : 15,
        "lvl"    : 30,
        "damage" : 100,
        "damage_type" : "割伤",
]),
([      "action" : "$N脚踏八卦方位，斜步上前，使出一招「天设牢笼」，将$w舞得如白雾一般压向$n",
        "skill_name" : "天设牢笼",
        "force"  : 185,
        "dodge"  : 45,
        "parry"  : 17,
        "lvl"    : 50,
        "damage" : 110,
        "damage_type" : "割伤",
]),
([      "action" : "$N手拖$w，转身跃起，一招「翼德闯帐」，飞身斜刺，忽然反手一刀横斩$n的腰部",
        "skill_name" : "翼德闯帐",
        "force"  : 255,
        "dodge"  : 60,
        "parry"  : 32,
        "lvl"    : 160,
        "damage" : 120,
        "damage_type" : "割伤",
]),
([      "action" : "$N低吼一声，挥舞$w，使出一招「白鹤舒翅」，上劈下撩，左挡右开，齐齐罩向$n",
        "skill_name" : "白鹤舒翅",
        "force"  : 290,
        "dodge"  : 70,
        "parry"  : 35,
        "lvl"    : 180,
        "damage" : 130,
        "damage_type" : "割伤",
]),
([      "action" : "$N一招「春风送暖」，左脚跃步落地，刀锋虚点，$w顺势往前，挟风声劈向$n的$l",
        "skill_name" : "春风送暖",
        "force"  : 320,
        "dodge"  : 85,
        "parry"  : 35,
        "lvl"    : 190,
        "damage" : 140,
        "damage_type" : "割伤",
]),
([      "action" : "$N足尖一点，蓦的使一招「八方藏刀」，顿时剑光中无数朵刀花从四面八方涌向$n全身",
        "skill_name" : "八方藏刀",
        "force"  : 340,
        "dodge"  : 100,
        "parry"  : 50,
        "lvl"    : 200,
        "damage" : 150,
        "damage_type" : "割伤",
]),
});

int valid_enable(string usage) {
   if ( this_player()->query("quest/雪山飞狐/武功/hujiadaofa"))
             return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 300)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的内功火候太浅。\n");

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
        int i,j,level;
        object target;
        object *enemy;
		string str,msg;
        
		level   = (int) me->query_skill("hujia-daofa",1);

		enemy = me->query_enemy();
        //强制控制招式
		if(sizeof(enemy)>0)
        {
           target = enemy[random(sizeof(enemy))];
      	   if(me->query_temp("quest/雪山飞狐/武功/powerup")
			||(!me->query_temp("quest/雪山飞狐/武功/kongzhi")
		    && me->query_temp("quest/雪山飞狐/武功/lengquan")
		    && me->query_skill_mapped("parry") == "hujia-daofa"
			&& random(me->query_skill("force"))>target->query_skill("force")/4 
			&& random(me->query("combat_exp"))>target->query("combat_exp")/4))
			{
				str =action[random(sizeof(action))]["action"];
				//SKILL_D("hujia-daofa")->query_action(me, me->query_temp("weapon"))["action"]
				switch(random(2))
				{
						case 0: str +="！\n"+HIR"$N突然纵身跃起，心神合一，手中"+weapon->name()+HIR"呼啸而出，大力劈出一刀！"NOR;break;
						case 1: str +="！\n"+HIY"$N轻舒猿臂，手中的"+weapon->name()+HIY"吞吞吐吐，变化莫测，笼罩了$n"HIY"周身要害！" NOR; break;
				}
				target->set_temp("must_be_hit",1);
				me->set_temp("quest/雪山飞狐/武功/kongzhi",1);
				//控制从这里开始，powerup招数出现之后，必须普通攻击至少两招之后才可能出现下次powerup招数
				return ([
						"action":str, 
						"damage":(random(3)+3)*60,
						"damage_type": "刺伤",
						"dodge": random(40)+40,
						"force": random(me->query_skill("force"))+250,
			   ]);
           }
		}
		//融合招式
        if(sizeof(enemy)>0)
        {
           target = enemy[random(sizeof(enemy))];
           if ( random(me->query_skill("force"))>(target->query_skill("force")/3) 
	            && me->query("quest/雪山飞狐/武功/ronghe") 
                //&& !me->query_temp("quest/雪山飞狐/武功/ronghe") 
				&& random(10)>6
                && random(me->query_skill("lengquan-shengong", 1))>200
                && me->query_skill_mapped("force") == "lengquan-shengong")
                        call_out("autopfm",1,me,target);
        }
		//有了冷泉标记
        if(me->query_temp("hjdf/ldj/color")=="color"
        && me->query("quest/雪山飞狐/武功/lengquanshengong_teach")
        && me->query_temp("lqsg/lq") )
		{
            str =action[random(sizeof(action))]["action"];
            return ([
                      "action" : HIB+replace_string(replace_string(str, "$w", "$W"), "$W", "$w"HIB)+NOR,
                      "damage_type": "割伤",
                      "dodge": random(40)+10,
                      "damage":(random(3)+2)*70,
                      "force": random(me->query_skill("force"))+100,
           ]);
       }
        else if(me->query_temp("hjdf/ldj/color")=="color") 
		{
            str =action[random(sizeof(action))]["action"];
            return ([
                      "action" : HIR+replace_string(replace_string(str, "$w", "$W"), "$W", "$w"HIR)+NOR,
                      "damage_type": "割伤",
                      "dodge": random(40)+10,
                      "force": random(me->query_skill("force"))+100,
           ]);
       }
//冷泉效果
        if(me->query_temp("hjdf/fdj/color")=="color"
        && me->query("quest/雪山飞狐/武功/lengquanshengong_teach")
        && me->query_temp("lqsg/lq") )
		{
            str =action[random(sizeof(action))]["action"];
            return ([
                      "action" : HIW+replace_string(replace_string(str, "$w", "$W"), "$W", "$w"HIW)+NOR,
                      "damage_type": "割伤",
                      "dodge": random(40)+10,
                      "damage":(random(3)+2)*70,
                      "force": random(me->query_skill("force"))+100,
           ]);
       }
        else if(me->query_temp("hjdf/fdj/color")=="color")
		{
            str =action[random(sizeof(action))]["action"];
            return ([
                      "action" : HIC+replace_string(replace_string(str, "$w", "$W"), "$W", "$w"HIC)+NOR,
                      "damage_type": "割伤",
                      "dodge": random(40)+10,
                      "force": random(me->query_skill("force"))+100,
           ]);
       }
        //乱刀诀
		if (me->query_temp("hjdf/ldj"))
        {
			for(i = sizeof(action); i > 0; i--)
			{
		      if(level > action[i-1]["lvl"])
			  {
				   j = NewRandom(i, 20, level/5);
				   if (me->query_temp("hjdf/ldja"))
				   {
					   return ([  
						"action":HIY+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIY), NOR, HIY)+NOR,
						"lvl" : action[j]["lvl"],
						 "skill_name" : action[j]["skill_name"],
						"force" : 20 + random(10),
						"dodge": 100+random(50),
						"damage": 200 + random(100),
						"parry": random(15)+10,
						"damage_type" : action[j]["damage_type"],
						]);
					}

					
					return ([  
						"action":WHT+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"WHT), NOR, WHT)+NOR,
						"lvl" : action[j]["lvl"],
						 "skill_name" : action[j]["skill_name"],
						"force" : 20 + random(10),
						"dodge": 100+random(50),
						"damage": 180 + random(80),
						"parry": random(15)+10,
						"damage_type" : action[j]["damage_type"],
						]);
				}
			}

        }
		//快刀
		if ( me->query_temp("quest/雪山飞狐/武功/kuaidao"))
		{
             return ([
                "action": HIC"突然之间，$N手中的$w"NOR+HIC"划出一道轻妙的圆弧，向$n斜斜劈出，$n顿觉呼吸一窒。"NOR,
                "damage": 250,
                "dodge" : 100,
                "damage_type": "割伤"
			 ]);
        }
        if( !userp(me) && me->query("env/invisibility")
             && me->query("master_user/user") )
		{
                return ([
                        "action": msg[random(sizeof(msg))],
                        "damage":(random(4)+2)*80,
                        "damage_type":random(2)?"内伤":"割伤",
                        "dodge": 5,
                        "force":250+random(250)
                ]);
        }
        
	   //若没有标记则出普通
        for(i = sizeof(action); i > 0; i--)
		          if(level >= action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

void autopfm(object me,object target)
{
        object weapon1,weapon2,* obj;
        int i;
        if(!me || !target || !me->is_fighting(target)) return;
        if(me->is_busy()) return;
        if( me->query_skill_mapped("sword") != "miaojia-jianfa") return;
        me->add("neili",-100);
        if (me->query("neili")<0) me->set("neili",0);
        weapon1 = me->query_temp("weapon");      
        if(!weapon1) return;
        obj = all_inventory(me);
        for(i=0; i<sizeof(obj); i++) 
          if(mapp(obj[i]->query("weapon_prop"))
             && obj[i]->query("skill_type")=="sword")
              weapon2 = obj[i];
        if(!weapon2) return;
        i = me->query_skill("sword",1)+me->query_skill("blade",1);
        if(random(2)) 	message_vision(HIC"\n紧跟着，$N顺手抽起"+weapon2->query("name")+HIC"，剑光光一闪，竟然使出苗家剑法！\n"NOR,me,target);
 		else message_vision(HIC"\n$N冷笑一声，突然"+weapon1->query("name")+HIC"虚招一晃，"+weapon2->query("name")+HIC"一闪，竟然使出苗家剑法！\n"NOR,me,target);
        weapon1->unequip(); 
        weapon2->wield();
		me->set_temp("quest/雪山飞狐/武功/ronghe",1);
		me->add_temp("apply/damage",i/8);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->add_temp("apply/damage",-i/8);
        me->delete_temp("quest/雪山飞狐/武功/ronghe");
		weapon2->unequip(); 
        weapon1->wield();       
        return;   
}


int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("jingli") < 80)
                return notify_fail("你的体力不够，练不了胡家刀法。\n");

        if ((int)me->query("neili") < 70)
                return notify_fail("你的内力不够，练不了胡家刀法。\n");

        me->receive_damage("jingli", -41-random(40));
        me->add("neili", -31-random(30));
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"hujia-daofa/" + action;
}

mixed hit_ob(object me, object victim, int damage)
{
       if (living(victim) && me->query_temp("hjdf/ldj") ){
          me->set_temp("hjdf/ldj/attack_chance",1);
       }
        if (me->query("quest/雪山飞狐/武功/lengquanshengong_teach")
        && me->query_temp("lqsg/lq")
        && me->query_skill_mapped("force") == "lengquan-shengong" )
        message_vision(HIY"$N已将冷泉神功运用得出神入化，每一招，每一式均附着冷泉内劲，威力惊人！\n"NOR, me);
        if(!me->query_temp("quest/雪山飞狐/武功/kongzhi")) return;
 		if(victim->query_temp("must_be_hit")) victim->delete_temp("must_be_hit");
	    if( me->query_skill_mapped("force") != "lengquan-shengong") return;
	    //if( me->query_skill_mapped("parry") != "hujia-daofa") return;
	    if( me->query_skill_mapped("blade") != "hujia-daofa") return;
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

int ob_hit(object me, object ob, int damage)
{
    if (living(me) && ob->query_temp("hjdf/fdj") && random(2)==0 ){
        perform_fdj(ob,me);
   }
}

int perform_fdj(object me,object target)
{
  if (!me->is_busy()){
    message_vision(HIY"正当$n出招一瞬间，$N就看出了$n此招破绽，便暗运「飞刀诀」功夫袭向$n！\n"NOR,me,target);
    me->set_temp("hjdf/fdj/color","color");
    target->set_temp("must_be_hit",1);
	me->add_temp("apply/damage",(int)me->query_skill("hujia-daofa",1)/4);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    for (;random(3);)
      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    me->delete_temp("hjdf/fdj/color");
	target->delete_temp("must_be_hit");
	me->add_temp("apply/damage",-(int)me->query_skill("hujia-daofa",1)/4);
  }
    return 1;
}
