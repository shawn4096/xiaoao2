// 回风拂柳剑
// Modified by Lane@SJ 2005/4/15
// By Spiderii加入飞跃

#include <ansi.h>
#include <combat.h>
inherit SKILL;
#include <combat_msg.h>

string *msg = ({
"$N一式「清风袭月」，剑锋平指，剑势如风，一股剑气直接冲向$n，气势如宏地猛攻$n的$l",
"$N向前跃上一步，左手剑诀，右手$w使出一式「飘雪穿云」，$w的剑风好似一片雪花，直逼$n的$l",
"$N手中$w斜指苍天，一式「千峰竞秀」，化出无数个剑尖，好似万道光辉笼罩$N，裹向$n的$l",
"$N一式「万流归宗」，$w自上而下缓缓划出一个大弧，这一招看似缓慢，但突然从中向$n的$l刺出",
"$N回身拧腰，一式「乌龙搅柱」，$w随身平划，看似无奇，实际上蕴藏绝顶厉害的招数，刺向$n的$l",
"$N一式「大雁啼沙」，全身贴地平飞，身剑合一，霎时间奔向$n，好似闪电般地刺向$n的$l",
"$N施出「进退龙游」，$w脱手飞出，如游龙般翱翔青宇，破空之声乍响，射向$n的$l",
"$N长啸一声，一式「天地鹤翔」，腾空飞起，全身迸出无数道雪亮剑芒，照耀天际！使得$n无可适从",
});

string *feiyue_msg = ({
""HIC"$N$w"HIC"招式陡变，东趋西走，连削四剑八式！这招叫作「"WHT"四通八达"HIC"」，乃是当年得自神雕大侠杨过所授"NOR"",
""HIC"$N看也不看$n的招式，但见$w"HIC"寒芒吞吐，电闪星飞，一招「"HIG"铁锁横江"HIC"」推送而上，此招凌厉之极，青霜到处已是避无可避"NOR"",
""HIC"$N倒转剑柄，以剑代指，一招「"HIR"一阳指"HIC"」，迳点$n手腕上“腕骨”、“阳谷”、“养老”三穴！这一指点三穴的手法，正是一阳指功夫的精要所在"NOR"",
""HIC"$N$w"HIC"轻扬，飘身而进，姿态飘飘若仙，剑锋向$n的下盘连点数点，却是自古墓小龙女处学来的一招玉女剑法「"HIY"小园艺菊"HIC"」"NOR"",
""HIC"$N身形一晃，抢上数丈，反手刷刷刷三剑，一剑比一剑快，一剑比一剑狠，乃是娥嵋派嫡传的「"HIY"金顶九式"HIC"」"NOR"",
""HIC"$N$w"HIC"斜走，使一招「"WHT"顺水推舟"HIC"」，斜着切向$n的$l空隙，这招精密细腻，实乃要将$p逼入绝路"NOR"",
""HIC"$N将$w"HIC"幌了几幌，使的竟是“打狗棒法”中的一招「"HIG"恶犬拦路"HIC"」，乃属“封”字诀，但见白光闪动，剑锋来势神妙无方"NOR"",
""HIC"$N回身拧腰，$w"HIC"随身而走，从上至下一式「"HIW"飞瀑流泉"HIC"」，霞光洒出，宛如瀑水直落，划向$n的要穴"NOR"",
""HIC"$N使出「"HIR"万紫千红"HIC"」，嗤的一声，$w"HIC"当胸直刺过去，剑尖不住颤动，使$n瞧不定剑尖到底攻向何处"NOR"",
""HIC"$N当下一招「"HIR"月落西山"HIC"」，$w"HIC"直刺$n$l，此招简单而精细，已达返璞归真！娥嵋派剑术高明之处，果然名不虚传"NOR"",
""HIC"$N将$w"HIC"回转，自下而上倒刺，却是全真派剑法中一招「"HIW"大绅倒悬"HIC"」，经娥嵋派历代高人去劣存精，威力已大超从前"NOR"",
""HIC"$N使出桃花岛落英剑法中的一式「"HIY"落英缤纷"HIC"」,$n眼中所见尽是剑光错落，青光激荡，剑花点点，好似落英缤纷，四散而下"NOR"",
""HIC"$N$w"HIC"变换交错，若有若无，正是自老顽童周伯通得意杰作七十二路空明拳中第五十四路「"HIW"妙手空空"HIC"」幻化而来"NOR"",
""HIC"$N左手一扬，和身欺上，右手$w"HIC"伸出，直指$n下颚,竟是少林罗汉拳中一式「"HIY"苦海回头"HIC"」，此时$N以$w"HIC"用来，更见威力"NOR"",
});
int valid_enable(string usage) 
{ 
        return usage == "sword" || usage == "parry"; 
}

int valid_learn(object me)
{
        object weapon;
        if (!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");
        if ( me->query("max_neili") < 100)
                return notify_fail("你的内力不够。\n");

        if ( me->query_skill("linji-zhuang", 1) < 20)
                return notify_fail("你的临济十二庄火候太浅。\n");

        if ( me->query_skill("parry", 1) < 10)
                return notify_fail("你的基本招架火候太浅。\n");
        return 1;
}
mapping query_action(object me, object weapon)
{
        int i, j, level, damage;

        level = me->query_skill("huifeng-jian", 1);
        i = random(me->query_skill("force"))+50;
        if( i<100 ) i = 100;
        j = random(40)-5;
        damage = (random(6)+1)*35;
        if( damage < 50 ) damage =50;
		if( me->query_temp("hfj/ronghe") )
		{
                       return ([
                                       "action": HIR+replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$w"), "$w", "$w"HIR)+NOR,                                   
                                       "damage": 250 + random(120),
                                       "damage_type": "刺伤",
                                       "dodge":  random(20),
                                       "parry":  random(20),
                                       "force":  300 + random(250),
                                        "attack" : random(30),
                                        "damage_type" : "剑伤",
                                ]);     // 剑法威力不变，辅助变更
        }

        if( me->query_temp("liaoyuan") && me->query("jiali"))
		{
                       return ([
                                       "action": HIW+replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$w"), "$w", "$w"HIW)+NOR,                                   
                                       "damage": 150 + random(120),
                                       "damage_type": "刺伤",
                                       "dodge":  random(20),
                                       "parry":  random(20),
                                       "force":  300 + random(250),
                                        "attack" : random(30),
                                        "damage_type" : "剑伤",
                                ]);     // 剑法威力不变，辅助变更
        }
		//回风诀
		if( me->query_temp("hjf/huifeng") && me->query("jiali"))
		{
                       return ([
                                       "action": HIY+replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$w"), "$w", "$w"HIY)+NOR,                                   
                                       "damage": 200 + random(50),
                                       "damage_type": "刺伤",
                                       "dodge":  random(20),
                                       "parry":  random(20),
                                       "force":  300 + random(250),
                                        "attack" : random(30),
                                        "damage_type" : "剑伤",
                                ]);    
        }

        if( level > 550 ) {
             //    if( level > 400 ) level = 400;
                             return ([
                                "action": feiyue_msg[random(sizeof(feiyue_msg))],
                                "damage": 200 + random(150),
                                "damage_type": "刺伤",
                                "dodge":  random(20),
                                "parry":  random(20),
                                "force":  350 + random(270),
                                "attack" : random(50),
                             ]);
                        }
                
             return ([
                "action":msg[random(sizeof(msg))],
                "damage": 80 + random(140),
                "damage_type": "刺伤",
                "dodge": random(30)-10,
                "parry": random(20),
                "force": 200 + random(350),
        ]);
}

int practice_skill(object me)
{
        if( (int)me->query("jingli") < 50 || me->query("neili") < 20 )
                return notify_fail("你的体力不够练回风拂柳剑。\n");

        me->receive_damage("jingli", 40);
        me->add("neili", -15);
        return 1;
}


int ob_hit(object ob, object me, int damage)
{
        object weapon, weapon1;
        string msg, *limbs, limb;
        int ap, dp, skill, j, i;

        if( ob->query("env/invisibility") ) return 0;
        if( !userp(me) && random(2) ) return 0;

        weapon1 = me->query_temp("weapon");

        if( me->query_skill("huifeng-jian", 1) < 150
         || me->query_skill_mapped("sword") != "huifeng-jian"
         || me->query_skill_mapped("parry") != "huifeng-jian"   // 招架必须是回风拂柳剑
         || !weapon1
         || weapon1->query("skill_type") != "sword" ) return 0;

        if( random(me->query_skill("parry")) > ob->query_skill("force")/3
         || random(me->query_con()) > ob->query_str()/3 )
                me->add_temp("hfj/"+ob->query("id"), 1);        // 添加反击参数

//      原来后发先至的判断，去除了反复判断
        if( me->query("combat_exp") < ob->query("combat_exp")/2 
			|| me->is_busy() 
			|| damage < 100 ) return 0;

        skill = me->query_skill("huifeng-jian", 1);
        weapon = ob->query_temp("weapon");

        if( objectp(weapon) )
                msg = weapon->query("skill_type");
        else {
                mapping prepare = ob->query_skill_prepare();
                if( !sizeof(prepare) ) msg = "unarmed";
                else msg = keys(prepare)[0];
        }

        if ( me->query("neili") < ob->query("neili")/5 ) return 0;

        ap = COMBAT_D->skill_power(ob, msg, SKILL_USAGE_ATTACK) / 1000;
        if ( weapon ) ap *= 2;
        if ( ob->query("neili") > me->query("neili") * 2 ) ap += ap/2;

        dp = COMBAT_D->skill_power(me, "parry", SKILL_USAGE_DEFENSE) / 1000;
        if ( me->query("neili") > ob->query("neili") * 2 ) dp *= 2;  
        else if ( me->query("neili") > ob->query("neili") / 2 * 3 ) dp += dp/2;

        ap = ABS(ap);
        dp = ABS(dp);

        if ( random(me->query("dex")) > ob->query("dex")/2) dp += random(dp/2);
        if ( skill > 350 ) dp += random(dp);

        if ( wizardp(me) ) tell_object(me, sprintf("ap: %d, dp: %d\n", ap ,dp ));

        if ( random(dp + ap) > ap && !random(2) ) {     // 概率降低点
                limbs = ob->query("limbs");
                limb = limbs[random(sizeof(limbs))];
                msg = HIW+"只见$N后发先至，";
                msg += query_action(me, weapon1)["action"];
                msg = replace_string( msg, "$l", limb);
                msg = replace_string( msg, "$w", weapon1->name()+HIW) + "！\n"NOR;
                if( userp(ob) && !userp(me) && damage > 3000 )
                        damage = 3000 + (damage-3000)/10;       // 修改了伤害的控制
//      伤害不能全部来自于对手
//              ob->receive_damage("qi", damage/3*2 + ob->query("jiali")*2, me);
//              ob->receive_wound("qi", damage/2, me);
                j = damage + me->query_skill("sword",1) + me->query("jiali");
                if( wizardp(me) ) tell_object(me, "你的后发先至伤害为："+j+"。\n"NOR);
                ob->receive_damage("qi", j, me);
                ob->receive_wound("qi", j/2, me);
                msg += COMBAT_D->damage_msg(j, "刺伤");
                msg = replace_string( msg, "$l", limb);
                msg = replace_string( msg, "$w", weapon1->name());
                message_vision(msg, me, ob);
                COMBAT_D->report_status(ob, ob->query("qi") >= 0 || ob->query("eff_qi")+ob->query_temp("apply/qi") < 0);
                return -6000;
        }
        
//      峨嵋剑诀的效果 “后发制人”
        else if( me->query_temp("hfj/"+ob->query("id")) > ( 1 + random(4) ) 
         && ( random(me->query_skill("parry",1)) > ob->query_skill("force",1)/2
         || random(me->query_con()) > ob->query_str()/2 ) ) 
		{
                me->delete_temp("hfj/"+ob->query("id"));
                msg = HIW"$N摸透了$n的武功套路，"+weapon1->name()+HIW"微侧，向旁斜指，剑光如雪，随即便即抢攻，竟不挡格$n的来招！！"NOR;
                message_vision(msg, me, ob);
                i = ob->query("qi");
                me->set_temp("jianjue", 1);
                me->add_temp("apply/attack",  me->query_skill("huifeng-jian", 1)/4);
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), random(3)?1:3);
                me->add_temp("apply/attack", -me->query_skill("huifeng-jian", 1)/4);
                me->delete_temp("jianjue");
                if( i > ob->query("qi") ) return -damage/2;
                else return -damage;
        }
        return 0;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
//      增加峨嵋剑诀，辅助攻击，概率很低
        object weapon; 
        int i,l;
        weapon = me->query_temp("weapon");
        i = me->query_skill("huifeng-jian", 1);
        l = me->query_skill("linji-zhuang", 1);
        if( !userp(me) && random(2) ) return 0;

        if( !weapon || weapon->query("skill_type") != "sword" ) return 0;
        if( i < 450 ) return 0; //大飞后出
        if( !me->query("emei/jianjue")) return 0;
        //if( me->query_temp("jianjue") ) return 0;
// 227:         if( me->query_temp("liaoyuan") ) return 0;
        if( damage_bonus < 100 ) return 0;
        if( !living(victim) ) return 0;
        if( i >= 450 
		 && random(10)>7
		 && me->is_fighting()
		 && me->query_skill("jiuyin-zhengong",1)>179
         && random(me->query_int(1)) > victim->query_int(1)/2
         ) {
                message_vision(HBBLU+HIW"$N将所学到的九阴真经功夫忽然施展出来，戳、拿、点、拍，连续施展出数种绝技,$n顿时受制。\n"NOR, me, victim);
               	victim->add_busy(2);
				if (random(4))
				   victim->apply_condition("no_perform",1);
				else victim->apply_condition("no_exert",1);
				
        }
        if( i >= 450 && !random(3)
         && random(me->query_str()) > victim->query_con()/3
         && random(me->query_skill("sword")) > victim->query_skill("parry")/3 ) {
                if( me->query_skill_prepared("hand") == "jieshou-jiushi"
                 && me->query_skill_mapped("hand") == "jieshou-jiushi"
                 && me->query_skill("jieshou-jiushi", 1) >= 450 && random(3) ) {
                        message_vision(HIW"$N默念峨嵋剑诀，“"CYN"先以心使身，从人不从己，由己则滞，从人则活。"HIW"”右手猛的运剑回转，左手截手九式随劲而起！"NOR, me);
                        weapon->unequip();
                        me->add_temp("apply/attack",  me->query_skill("jieshou-jiushi", 1)/4);
                        COMBAT_D->do_attack(me, victim, 0, userp(me)?3:1);
                        me->add_temp("apply/attack", -me->query_skill("jieshou-jiushi", 1)/4);
                        weapon->wield();
                } else {
                        message_vision(HIW"$N默念峨嵋剑诀，“"HIY"从身能从心，由己仍从人。前进后退，处处恰合。"HIW"”紧接着"+weapon->name()+HIW"猛的回转再次刺出！"NOR, me);
                        me->set_temp("jianjue", 1);
                        me->add_temp("apply/attack",  me->query_skill("huifeng-jian", 1)/6);
                        COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(4)?3:1);
                        me->add_temp("apply/attack", -me->query_skill("huifeng-jian", 1)/6);
                        me->delete_temp("jianjue");
                }
        }
        else if( i >= 550 
		 && random(2)
         && random(me->query("combat_exp")) > victim->query("combat_exp")/3
         && random(me->query_skill("sword",1)) > victim->query_skill("parry",1)/3
         && random(me->query_str()) > victim->query_con()/3
         && !victim->query_temp("lost_attack") ) {
                message_vision(HIW"$N默念峨嵋剑诀，“"HBRED+HIW"前后左右，全无定向，后发制人，先发制于人。"NOR+HIW"”顿时剑气纵横，将$n攻个措手不及！\n"NOR, me, victim);
                victim->add_temp("lost_attack", 2+random(3));
				victim->add_busy(1+random(1));
                return random(me->query_skill("sword",1))/3;
        }
        
        return 0;
}

string perform_action_file(string action)
{
        return __DIR__"huifeng-jian/" + action;
}

