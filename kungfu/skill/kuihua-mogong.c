// By KinGSo@舞林 2006年4月25日 
// kuihua-shengong 葵花魔功


inherit FORCE;
#include <ansi.h>

string *dodge_msg = ({
        "$n微微一动，已然远去，使$N的进攻全然无用。\n",
        "$n霎时间平移了数步，如鬼如魅，使$N全然无法掌握。\n",
        "$n忽的一退，闪去天下任何追击。\n",
        "$n足不离地，腰肢猛摆，居然将$N的进攻全部躲过。\n",
});

string *finger_name = ({ "左手中指", "左手无名指", "左手食指",
                         "右手中指", "右手无名指", "右手食指", }); 

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("kuihua-mogong", 1);
        return lvl * lvl * 18 * 15 / 100 / 200;
}

mapping *actionf = ({
([      "action":"$N倏的近前，身形快极，手指戳向$n的$l",
        "force" : 310,
       
        "dodge" : 60,
        "parry" : 20,
        "damage": 190,
        "damage_type":  "刺伤"
]),
([      "action":"$N扑向前来，身形如同鬼魅，令人难以捉摸，手指忽的刺向$n的$l",
        "force" : 310,
        
        "dodge" : 65,
        "parry" : 20,
        "damage": 200,
        "damage_type":  "刺伤"
]),
([      "action":"$N身形一转，手指刺出，直指$n的$l",
        "force" : 330,
        
        "dodge" : 70,
        "parry" : 20,
        "damage": 210,
        "damage_type":  "刺伤"
]),
([      "action":"$N飘然远去，忽又进前，速度快的不可思议，一指如闪电般刺向$n的$l",
        "force" : 345,
        
        "dodge" : 75,
        "parry" : 35,
        "damage": 190,
        "damage_type":  "刺伤"
]),
([      "action":"$N身体一晃，突然飞起一脚，踢向$n的$l",
        "force" : 350,
        
        "dodge" : 70,
        "parry" : 25,
        "damage": 200,
        "damage_type":  "瘀伤"
]),
([      "action":"$N足下疾走，身形变幻莫测，突然一指插向$n的$l",
        "force" : 450,
       
        "dodge" : 85,
        "parry" : 25,
        "damage": 220,
        "damage_type":  "刺伤"
]),
});

mapping *actionw = ({
([      "action":"$N倏的近前，身形快极，手中的$w戳向$n的$l",
        "force" : 360,
       
        "dodge" : 70,
        "parry" : 20,
        "damage": 420,
        "damage_type":  "刺伤"
]),
([      "action":"$N扑向前来，身形如同鬼魅，令人难以捉摸，手中的$w忽的刺向$n的$l",
        "force" : 390,
        
        "dodge" : 60,
        "parry" : 25,
        "damage": 430,
        "damage_type":  "刺伤"
]),
([      "action":"$N身形一转，$w刺出，直指$n的$l",
        "force" : 365,
        
        "dodge" : 80,
        "parry" : 15,
        "damage": 450,
        "damage_type":  "刺伤"
]),
([      "action":"$N飘然远去，忽又进前，速度快的不可思议，$w如闪电般刺向$n的$l",
        "force" : 380,
        
        "dodge" : 75,
        "parry" : 15,
        "damage": 560,
        "damage_type":  "刺伤"
]),
([      "action":"$N身体一晃，突然飞起一脚踢向$n的下阴，蓦的又收回，反手$w刺向$n的$l",
        "force" : 400,
       
        "dodge" : 80,
        "parry" : 17,
        "damage": 580,
        "damage_type":  "刺伤"
]),
([      "action":"$N足下疾走，身形变幻莫测，突然一扬手，$w飞也似的插向$n的$l",
        "force" : 420,
        
        "dodge" : 95,
        "parry" : 20,
        "damage": 650,
        "damage_type":  "刺伤"
]),
});

mapping *action_qm = ({
([      "action":HBMAG"$N手上$w"+HBCYN"突然间招法一变，一招「江上弄笛」，$w忽伸忽缩，招式诡奇绝伦。$n惊骇之中方寸大乱"NOR,
        "force" : 160,
        "dodge" : 5,
        "parry" : 5,
        "damage": 215,
        "lvl" : 0,
        "skill_name" : "江上弄笛",
        "damage_type":  "刺伤"
]),
([      "action":HBMAG HIY"$N向后疾退，$n紧追两步，突然间$N闪到$n面前，一招「花开见佛」，手中$w直指$n的$l"NOR,
        "force" : 200,
        "dodge" : 5,
        "parry" : 5,
        "damage": 225,
        "lvl" : 10,
        "skill_name" : "花开见佛",
        "damage_type":  "刺伤"
]),
([      "action":HBMAG HIW"$N手中$w"+HBCYN"晃动,身形飘忽，有如鬼魅，转了几转，一招「紫气东来」，移步到$n的左侧"NOR,
        "force" : 260,
        "dodge" : 8,
        "parry" : 8,
        "damage": 30,
        "lvl" : 220,
        "skill_name" : "紫气东来",
        "damage_type":  "割伤"
]),
([      "action":BBLU HIC"$N"+HBCYN"一声冷笑，一招「流星赶月」，蓦地里疾冲上前，一瞬之间，与$n相距已不到一尺，$w随即递出"NOR,
        "force" : 330,
        "dodge" : 10,
        "parry" : 15,
        "damage": 240,
        "lvl" : 30,
        "skill_name" : "流星赶月",
        "damage_type":  "割伤"
]),
([      "action":HBMAG HIC"$N喝道：“好！”，便即拔出$w，一招「飞燕穿柳」，反手刺出，跟着转身离去"NOR,
        "force" : 205,
        "dodge" : 35,
        "damage": 220,
        "lvl" : 80,
        "skill_name" : "反手刺出",
        "damage_type":  "刺伤"
]),
([      "action":HBBLU "$N蓦地冲到$n面前，一招「锺馗抉目」，手中$w直刺$n右眼！$n慌忙招架，不想$N的$w突然转向"NOR,
        "force" : 240,
        "dodge" : 50,
        "damage": 245,
        "lvl" : 90,
        "skill_name" : "直刺右眼",
        "damage_type":  "刺伤"
]),
([      "action":HBBLU HIG"$N飞身跃起，$n抬眼一望，但见得$N一招「流星飞堕」，从天直落而下，手中$w刺向$n的$l"NOR,
        "force" : 270,
        "dodge" : 60,
        "damage": 270,
        "lvl" : 100,
        "skill_name" : "飞身跃起",
        "damage_type":  "刺伤"
]),
([      "action":HBMAG HIM"$N一招「群邪辟易」，腰枝猛摆，$n眼前仿佛突然出现了七八个$N，七八只$w一起刺向$n"NOR,
        "force" : 300,
        "dodge" : 75,
        "damage": 300,
        "lvl" : 110,
        "skill_name" : "群邪辟易",
        "damage_type":  "刺伤"
]),
});
string *usage_skills = ({ "finger", "sword", "dodge",
                          "parry", "force" });

int valid_enable(string usage)
{
        
        return (member_array(usage, usage_skills) != -1);
}

int valid_combo(string combo)
{
        return combo == "kuihua-mogong";
}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{       int i, level;

	level=me->query_skill("kuihua-mogong",1);

        
        if( me->query_temp("kh_qm")) {
        for(i = sizeof(action_qm); i > 0; i--) 
                if(level >= action_qm[i-1]["lvl"])
                        return action_qm[NewRandom(i, 20, level/5)];
        }
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;
        
        if((int)me->query_skill("shenzhao-jing", 1) >= 1 )
                return notify_fail("你不散去神照经，怎么修炼葵花魔功。\n");
    
        if((int)me->query_skill("hamagong", 1) >= 1 )
                return notify_fail("你不散去蛤蟆功，怎么修炼葵花魔功。\n");

        if((int)me->query_skill("lengquan-shengong", 1) >= 1 )
                return notify_fail("你不散去冷泉神功，怎么修炼葵花魔功。\n");

       if((int)me->query_skill("jiuyin-zhengong", 1) >= 1 )
                return notify_fail("你不散去九阴真功，怎么修炼葵花魔功。\n");  
    
        if((int)me->query_skill("jiuyang-gong", 1) >= 1 )
                return notify_fail("你不散去九阳神功，怎么修炼葵花魔功。\n");  
     
       if((int)me->query_skill("luohan-fumogong", 1) >= 1 )
                return notify_fail("你不散去罗汉伏魔功，怎么修炼葵花魔功。\n");

        if((int)me->query_skill("taixuan-gong", 1) >= 1 )
                return notify_fail("你不散去太玄功，怎么修炼葵花魔功。\n");  

        if ((int)me->query("combat_exp") < 3000000)
                return notify_fail("你觉得葵花魔功深奥之极，"
                                   "凭自己的战斗经验一时间难以领会。\n");

       
            if (me->query("gender") != "无性")
                return notify_fail(BLINK HIY"【欲练神功挥刀自宫】。\n" NOR);
                
        
        

        if ((int)me->query_dex()< 35)
                return notify_fail("你觉得自己的身法不够灵动，不可能掌握这么飘缈"
                                   "玄奇的葵花魔功。\n");
 
       if ((int)me->query_int()< 32)
                return notify_fail("你觉得自己的先天悟性不够，不可能领悟这么高深"
                                   "玄奇的葵花魔功。\n");
       if ((int)me->query_str()< 25)
                return notify_fail("你觉得自己的先天臂力不够，不可能领悟这么高深"
                                   "玄奇的葵花魔功。\n");

      
 
       

        return 1;
}

int practice_skill(object me)
{
       if((int)me->query_skill("shenzhao-jing", 1) >= 1 )
                return notify_fail("你不散去神照经，怎么修炼葵花魔功。\n");
    
        if((int)me->query_skill("hamagong", 1) >= 1 )
                return notify_fail("你不散去蛤蟆功，怎么修炼葵花魔功。\n");

        if((int)me->query_skill("lengquan-shengong", 1) >= 1 )
                return notify_fail("你不散去冷泉神功，怎么修炼葵花魔功。\n");

       if((int)me->query_skill("kuihua-shengong", 1) >= 1 )
                return notify_fail("你不散去葵花神功，怎么修炼葵花魔功。\n");  
    
        if((int)me->query_skill("jiuyang-gong", 1) >= 1 )
                return notify_fail("你不散去九阳神功，怎么修炼葵花魔功。\n");  
     
       if((int)me->query_skill("luohan-fumogong", 1) >= 1 )
                return notify_fail("你不散去罗汉伏魔功，怎么修炼葵花魔功。\n");

        if((int)me->query_skill("taixuan-gong", 1) >= 1 )
                return notify_fail("你不散去太玄功，怎么修炼葵花魔功。\n");  



       if((int)me->query_skill("kuihua-mogong", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("kuihua-mogong", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -random(30));
                   return 1;
           }
           else return notify_fail("你现在的修为不足以提葵花魔功了。\n");       }
        else return notify_fail("你现在的葵花魔功修为只能用学(learn)的来增加熟练度。\n");

}
int difficult_level()
{
        return 1600;
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("kuihua-mogong", 1);
        if (lvl <= 200) return 70;
        if (lvl < 250) return 90;
        if (lvl < 300) return 100;
        if (lvl < 350) return 115;
        return 130;
}

mixed ob_hit(object ob, object me, int damage)
{
	 //By kingso 2007 01 26从新编辑，也感谢Counter小姐给告诉我底层不支持+= ([   
        int ap, dp;
        int  lvl;
        lvl = me->query_skill("kuihua-mogong", 1);
        if ( lvl < 150
          || me->query("neili") < 300
          || me->query_skill_mapped("force") != "kuihua-mogong")
         	return 0;
         	
        ap = ob->query_skill("parry");
        dp = me->query_skill("force");
        if (random(dp)> ap/2)
        {
	        me->add("neili", -50);
          me->receive_curing("qi", damage);
          me->receive_heal("qi", damage);

                return random(2) ?  HBMAG HIY "$N"HBMAG HIY"眼睛一花，$n"HBMAG HIY"已没了踪影。突然$n" 
                                    HBMAG HIY"从身后拍了一下$N"HBMAG HIY"的头，轻轻跃开。\n" NOR:
                                                        
                                    HBMAG HIC"忽然间，只见$n"HBMAG HIC"腰枝一摆，顿时出现无数个"
                                    HBMAG HIC"$n"HBMAG HIC"的影子，$N"HBMAG HIC"却无法辨别出$n"HBMAG HIC"的方位。\n" NOR;
                     }
}


mixed hit_ob(object me, object target)
{
    string msg;
    int j;
    j = me->query_skill("kuihua-mogong", 1);
   
    if (random(me->query_dex()) >= (target->query_dex()/4) && j > 120 &&
        me->query_skill("dodge",1) > 120 &&
        me->query("jingli")>300 && 
        !target->is_busy() &&
        me->query("combat_exp")/2 > random(target->query("combat_exp")) && 
        me->query("neili")>500)
   {
          switch(random(2))
          {
            case 0 :
               msg = HIC "$N默运葵花魔功，身型飘忽不定，出招极快.一招指向$n周身大穴！\n";
               msg = msg + "$n只觉全身一麻，已被几招点中"HIY"「曲池穴」「风府穴」「大椎穴」！\n"NOR; 
               target->recevied_damage("qi", j +random(300));
               target->start_busy(2+random(2));
               break;
            case 1 :
               msg = HIW "$N出招诡异，指东打西.顿时劲气暴涨,将$n笼罩于内！\n";
               msg += "$n只觉周身要穴一麻，已被几招点中"HIY"「神风穴」「劳宫穴」「百会穴」！\n"NOR;
               target->recevied_damage("qi", j + random(300));
               target->start_busy(3+random(2));
               me->add("neili",-50);
               message_vision(msg, me, target);
               return j/(4-random(2));
               break;
            
          }         
          message_vision(msg, me, target);
   }
}
string perform_action_file(string action)
{
        return __DIR__"kuihua-mogong/perform/" + action;
}

string exert_function_file(string action)
{
       return __DIR__"kuihua-mogong/exert/" + action;
}
