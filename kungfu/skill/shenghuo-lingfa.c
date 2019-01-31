// shenghuo-lingfa 圣火令法
// 1997-5-14
inherit SKILL;
#include <ansi.h>
inherit F_SSERVER;
int hit_ob(object me,object victim,int damage);
string  *msgl = ({
"$N一式「以意相求」忽地放手，$w的尾端向上弹起，以意想不到方位呼的向$n拍去",
"$N平平一令击出，一式「风回路转」，$w在半空古古怪怪的转了个弯，打向$n的$l",
"$N突然一声清啸，双令一招「三虚七实」虚虚实实，是是而非的击向$n的$l",
"$N忽然低头，一式「头头是道」，一个头锤向$n撞去，手中$w却暗中的向$n的$l击去",
"$N突然纵身而起，一式「翻江倒海」连翻三个空心筋斗，白光忽闪，$w向$n的$l砸去",
"$N坐地锤胸，一式「瞒天过海」呼天抢地的哭号，突然间脚踢飞沙，抽出$w向$n疾刺",
"$N默念口诀，$w一招「应左则后」，明指前胸，突地一转弯，向$n的背心大穴砸去",
"$N使出的是圣火令中的一招「须右仍前」，凌空虚点$n右臂，$w却向对方胸前大穴刺去",
"$N一招「无中生有」，不知如何，手中已经多出$w，手腕一摆，快速无比的刺向$n的$l",
"$N手中的$w划出一个个的圈子，这招「天方地园」一出，顿时裹得$n眼花缭乱，不知所措"
});
string  *msgc = ({
"$N反守为攻，一招「乱中求胜」，身体斜飞，连环的向$n踢出四脚",
"$N一式「坐地求全」，忽地在地上一坐，左手抱向$n的$l，右手击向“中都”穴",
"$N突然间一式「以进为退」，接着向前一个空心筋斗，凌空落下，双足向$n$l踢去",
"$N呼的一声，一式「庶天蔽日」，纵身半空翻了几个空心筋斗，伸臂向$n的$l抓去",
"$N一个筋斗，一式「万流归宗」，身在半空，落下时右脚的膝盖在$n关顶一脆",
"$N向前一坐，一式「投怀送抱」，撞入$n的怀中，双肘向$n$l的穴道撞去",
"$N坐地锤胸，一式「飞沙走石」，呼天抢地的哭号，突然间脚踢飞沙，单手向$n疾点"
});

string  *msg2 = ({
HIW"$N直抢而前，脚下一踬，忽然一个筋斗摔了过去，双手$w"HIW"却已向$n胸口拍了过去"NOR,
HIR"$N平平一令击出，$w"HIR"在半途古古怪怪的转了个弯，拍的一响，拍向$n的$l"NOR,
MAG"$N将$w"MAG"插入怀中，右手一探，已抓住$n左脚，硬生生将$n在半空中拉了回来"NOR,
HIY"$N双手$w"HIY"急挥横扫，$n身形一转，向左避开，不意拍的一响，$l已被$w"HIY"击中"NOR,
YEL"$n左手倏地抓住了$N左手的$w"YEL"。岂知那$w"YEL"尾端向上弹起，拍的一响，正好打中$n手腕"NOR,
GRN"$N坐倒在地，双拳猛捶自己胸膛，待$n靠近突然间脚踢飞沙，抽出$w"GRN"向$n的$l疾刺"NOR,
HIG"$N上身微斜，右臂弯过，$w"HIG"从莫名其妙的方位转了过来，拍的一声，向$n的$l重重打去"NOR
});

int valid_enable(string usage)
{
        
		if (!this_player()->query("quest/mj/shlf/givezhang"))
        {
			return notify_fail("你根本不知道圣火令法的使用之法，现在激发不了圣火令法。\n");
        }
		return usage == "dagger" || usage== "cuff" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
	string msg;

	if(me->query_temp("tisha")){
		switch(me->query_temp("tisha")) {
			case 4: msg = CYN"$N直抢而前，脚下一踬，忽然一个筋斗摔了过去，双手已向$n胸口拍了过去"NOR; break;
			case 3: msg = CYN"$N坐倒在地，双拳猛捶自己胸膛，待$n靠近突然间脚踢飞沙，抽出$w"CYN"向$n的$l疾刺"NOR;break;
			case 2: msg = CYN"$n在霎时之间，但觉飞雪扑面，双眼不能见物，茫然不知所措，$N趁势用肩部从背后向$n撞去"NOR; break;
			case 1: msg = CYN"$N随着$n的去式，巧运乾坤大挪移神功，钻到$n的身前，将手中$w"CYN"向$n的$l插去"NOR;break;
			default: msg = CYN"$N直抢而前，脚下一踬，忽然一个筋斗摔了过去，双手已向$n胸口拍了过去"NOR; break;
		}  
		me->add_temp("tisha", -1);
		return ([
			"action": msg,
			"force" : 150 + random(150),
			"dodge": random(30),
			"parry": random(30),
			//"damage": me->query_temp("type")? 50+random(50):100 + random(100),//原来是130+random(140)
			"damage":200+random(100),
			"damage_type" : me->query_temp("type")? "刺伤":"割伤",
		]);
	}
	if(me->query_temp("shlf/lianji")){
		switch(me->query_temp("shlf/lianji")) {
			case 12: msg = YEL"$N欺身直进，左手持$w向$n天灵盖上平平拍落,便在这一瞬之间，$N滚身向左，抽空已然一拳打在$n的$l上"NOR; break;
			case 11: msg = YEL"$n右足一点，向后退开，在这顷刻之间，后心已重重中了$N一拳，只打得他胸腹间五脏六俯似乎都移了位置"NOR;break;
			case 10: msg = YEL"$n一个踉跄，$N横$w"YEL"戳向$n的后心，突然间$N纵身夺令，快速无比，巧妙无伦"NOR; break;
			case 9: msg = YEL"$n身形一转，向左避开，不意拍的一响，后心已被$N一令击中。这一下打中，$n眼前一黑，几欲晕去"NOR;break;
			case 8: msg = YEL"那$w"YEL"尾端向上弹起，拍的一响，正好打中$n手腕。"NOR; break;
			case 7: msg = YEL"$n左手五根手指一阵麻木，只得放下左手中已然夺到的兵刃，手臂酸麻异常，痛彻入骨"NOR;break;
			case 6: msg = HIY"$n端立不动，知$N这一招似拙实巧，必定伏下厉害异常的后着,$N这招还没用老，陡然间纵身而起，踢出连环三脚"NOR; break;
			case 5: msg = HIR"蓦地里$N跃身半空，向$n头顶坐了下来。这一招更是怪异，竟以臀部攻人，天下武学之道虽繁，从未有这一路既无用、又笨拙的招数"NOR;break;
			case 4: msg = CYN"$n不动声色，向旁又是一让，突觉胸口一痛，已被$N手肘撞中"NOR; break;
			case 3: msg = HIR"$N双手急挥横扫，$N突然连翻三个空心筋斗。$n不知他是何用意，心想还是避之为妙，刚向左踏开一步，眼前白光急闪，右肩已被$N的$w重重击中"NOR;break;
			case 2: msg = YEL"$n还没转过身来，但觉腰胁中一阵疼痛，已被$N从一个莫名的角度，踢中了一脚，极为不可思议"NOR; break;
			case 1: msg = CYN"$n跃起身来，欲待抢夺，突然间嗤的一声响，后心衣衫被$N抓了一大截下来。$N指甲在$n背心上划破了几条爪痕，隐隐生痛"NOR;break;
			default: msg = CYN""NOR; break;
		}  
		me->add_temp("shlf/lianji", -1);
		return ([
			"action": msg,
			"force" : 150 + random(150),
			"dodge": random(30),
			"parry": random(30),
			//"damage": me->query_temp("type")? 50+random(50):100 + random(100),//原来是130+random(140)
			"damage":150+random(100),
			"damage_type" : me->query_temp("type")? "刺伤":"割伤",
		]);
	}
	if (!weapon)
		return ([
			"action":msgc[random(sizeof(msgc))],
			"damage_type":"瘀伤",
			"dodge":random(30),
			"parry":random(30),
			"force":random(300)+ 150,
		]);
	if( me->query_temp("lian"))
		return ([
			"action" :msg2[random(sizeof(msg2))],
			"force" : random(350) + 300,
			"dodge": random(30),
			"parry": random(30),
			"damage": 180+ random(100),
			"damage_type":random(2)?"刺伤":"割伤",
		]);
	
	return ([
		"action":msgl[random(sizeof(msgl))],
		"damage": 80 + random(100),
		"damage_type":random(2)?"刺伤":"割伤",
		"dodge": random(30)-10,
		"force": random(350)+200,
		"parry": random(20),
		"post_action": (: call_other, WEAPON_D, "bash_weapon" :)
	]);
}

int practice_skill(object me)
{
	if ( me->query("jingli") < 50)
		return notify_fail("你的体力不够练圣火令法。\n");         
	if ((int)me->query("neili") < 10)
		return notify_fail("你的内力不够练圣火令法。\n");
	me->receive_damage("jingli", 40);
	me->receive_damage("neili", 15);
	return 1;
}

int valid_learn(object me)
{
	object weapon = me->query_temp("weapon");
	int skill = me->query_skill("shenghuo-lingfa", 1);
       
	if (!weapon || weapon->query("skill_type") != "dagger")
		return notify_fail("你没有使用的武器。\n");

	if (me->query("max_neili") < 1000)
		return notify_fail("你的内力不够。\n");
	if (!me->query_skill("jiuyang-shengong"))
	if (me->query_skill("shenghuo-shengong", 1) < (skill-10)
	&& me->query_skill("shenghuo-shengong", 1) < 200)
		return notify_fail("你的圣火神功火候太浅。\n");
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"shenghuo-lingfa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
       int lvl;
        object weapon, weapon2;
        int i, ap, dpp, dpd, dpf,damg;
        string type, msg;
        weapon=me->query_temp("weapon");
		weapon2=victim->query_temp("weapon");
        lvl = me->query_skill("shenghuo-lingfa", 1);
        damg=lvl+me->query_skill("qiankun-danuoyi",1)/2;
        if (me->query("neili") < 2000
           || me->query_skill_mapped("dagger") != "shenghuo-lingfa"
           ||!objectp(weapon = me->query_temp("weapon"))
           || weapon->query("skill_type") != "dagger"
		   || me->query_skill_mapped("parry")!="qiankun-danuoyi"
           || !me->query("mjqkdny/pass"))
         return 0;

        ap = me->query_skill("dagger") + me->query_dex() + me->query_int();
        dpp = victim->query_skill("parry");
        dpd = victim->query_skill("dodge");
        dpf = victim->query_skill("force");
        me->add("neili", -100); 
 
        switch(random(5))
        {
            case 0:
              if (ap * 3/4 + random(ap) > dpp/3)
              {
                  
				  me->add("neili", -220);                  
                  //victim->receive_wound("qi", (me->query("max_qi")/3), me);
				 // victim->add_busy(1+random(2));
				  //victim->receive_wound("jingli", (me->query("max_jingli")/3), me);
                  msg=random(2)? BLU "$N已经从乾坤大挪移秘籍中领悟了西域霍山老人绝技的真传,心中痛快淋漓，手中随心所欲" + weapon->name() +BLU
                                     "\n之上又得「挪移乾坤」心法相辅，显然和先前有很大不同,威力陡然暴增。\n" NOR:		  
             				     HBMAG "$N喋喋狂笑，只觉得心中手中" + weapon->name() + HBMAG "欲发即发，欲收即收，招招怪异无比，根本不似中土武学，$n一见之下，心中大骇。\n" NOR;	
				  victim->add_busy(1+random(2));
				  me->add_temp("apply/damage",damg/2);
				  COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);	
				  me->add_temp("apply/damage",-damg/2);
				  message_vision(msg, me, victim);
             }
             break;
          case 1:
			   // 利用对方busy，或者制造缝隙，和个人悟性有关
              if (random(me->query_int(1))> victim->query_int(1)/3)
              {
                  me->add("neili", -200);                  
                  if (random(2))
                     message_vision(HBRED "$N运起乾坤大挪移的高深心法，沛然莫之能御全身, 欲发即发，欲收即收，一切全凭心意所之。\n"NOR,me,victim);
				  else
                     message_vision(HIY "$N手中" + weapon->name() + HIY "忽左忽右，忽前忽后，指南打北，指北打南，$n觉得对方招式没有任何轨迹可循，一不留神，为兵器中透出的阴风内劲所伤。\n" NOR,me,victim);                 ;
				  victim->apply_condition("no_exert",1+random(2));
				  COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);	
             }
             break;

          case 2:
            
		     if (random(me->query("combat_exp",1)) > victim->query("combat_exp",1)/3)
		      {		  		  
			   
		        message_vision(HBBLU"\n乾坤大挪移最擅长寻瑕抵隙,制造破绽，$N"+HBBLU+ "将自己领悟的"+HIR+"「挪移乾坤」"+HBBLU+"心法最高深的功夫运在\n"+
				   weapon->query("name")+HBBLU+"，$n百计防护，尚且不稳，何况自呈虚弱。 $n见$N手指上五股劲气丝丝作响,直指自己招式中的破绽！\n"NOR,me,victim);
			   //制造破绽
               victim->apply_condition("no_fight",1+random(2));
			   victim->apply_condition("no_perform",1+random(2));
                if (!me->is_busy())
                 {
                    weapon = me->query_temp("weapon");
                    weapon2 = victim->query_temp("weapon");
                    if (weapon2)type = weapon2->query("skill_type");

                    if (ap * 3 / 4 + random(ap) >= dpf/2 && weapon2
                      && type != "pin")
                    {
                           msg = BLU"$n" HIR "觉得心中烦闷不堪，手中"
                                 "的" + weapon2->name() + BLU "一时竟"
                                 "然拿捏不住，脱手而飞！\n" NOR;
                           weapon2->move(environment(me));      
                           me->add("neili", -100);                 
                      } else
                        {
                           msg = HIY "$n" HIR "略得空隙喘息，一时间却"
                                 "也无力反击。\n" NOR;
                           me->add("neili", -40);
                         }
               }else 
			     if (ap * 4 / 5 + random(ap) > dpd/2)
                 {
                          msg = HIY "$n" HIY "连忙抵挡，一时间不禁手忙脚乱，"
                                "无暇反击。\n" NOR;

                          me->start_busy(1+random(2));
                          victim->add_busy(1 + random(lvl / 100));
                    }
                  else
                   {
                          msg = HIC "$N" HIC "将"HIR"「挪移乾坤」"HIC"心法运在" + weapon->name() +
                                HIC "之上" HIC "，可是$n" HIC "防守的异常严密，$N"
                                HIC "一时竟然无法施为。\n" NOR;
                          me->start_busy(1 + random(2));
                          victim->start_busy(1);
                    }
               message_vision(msg, me, victim);
			 //COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 3);	
		  			   
			  }
             break;
          //起乾坤大挪移心法中最高深的功夫一掌轻轻拍出，击在他的腰里。这一掌中所运，正是「乾坤大挪移」的绝顶神妙武功，
		  //吞吐控纵之间，已将他自上向下的一股巨力，拨为自左至右
  
        case 3:
             if (ap * 4 / 5 + random(ap) > dpd/2 && 
                  me->query_dex() >= 40) 
                {
			    weapon = me->query_temp("weapon");
                message_vision(HIB "\n$N" HIB "练成[乾坤大挪移]神功,无论那一家那一派的武功，都能取为己用,当下微微一笑，手中" + weapon->name() + HIB 
                             "\n运起"HIR"「挪移乾坤」"HIB"的心法，显然已将$n招数中的破绽尽收眼底,$n不知不觉招式竟攻向自己。\n" NOR, me, victim);
                COMBAT_D->do_attack(victim, victim, weapon, 3);
                me->add("neili", -320);                
             }
             break;                        
      case 4 : 
		   if (ap * 4 / 5 + random(ap) > dpd/2 && 
                 ! me->is_busy() &&
                 ! me->query_temp("shenghuo-lingfa/lian") &&
                 me->query("dex") >= 40)
                {
			     weapon = me->query_temp("weapon");
                 message_vision(HIB "\n$N" HIY "仰天长啸，乾坤大挪移第七层神功劲力迸发，趁$n招式中空隙，连出数招。\n" NOR, me, victim);
                 me->add("neili", -320);				
			  	 me->set_temp("shenghuo-lingfa/lian", 1);
                for (i = 0; i < 3; i++) //由6调成3，6太狠了点
                {
                    if (! me->is_fighting(victim))
                            break;                   
                    if (! victim->is_busy() && random(2) == 1)
                            victim->add_busy(1);
                    COMBAT_D->do_attack(me, victim, weapon, random(4)?1:3);
                }
                me->delete_temp("shenghuo-lingfa/lian");
                
             }
             break;                        
	   }
}

