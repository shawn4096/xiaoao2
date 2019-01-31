// yinsuo-jinling.c 银索金铃
// By River
#include <ansi.h>
inherit SKILL;

string  *msg = ({
"$N左手轻扬，手中$w忽地甩了出来，直扑$n的$l。无声无息，事先竟没半点朕兆",
"$N手持$w矫矢似灵蛇击向$n，再加两枚金球不断发出玎玎之声，更是扰人心魄",
"$n又听得金球中发出玎玎声响，声虽不大，却是十分怪异，入耳荡心摇魄。",
"$N身形一变，转手一挥$w，$n大惊之下，身子後仰，$w离脸数寸急掠而过",
"$N手腕微抖，$w翻将过去，自下而上，打向$n身上$l处的「合谷穴」",
"$N手中两条$w犹如水蛇般蜿蜒而出，玎玎两响，$n手腕上的「灵道穴」都被$w点中",
"$N微微一笑跨前一步，右手$w一抖，$w矫夭飞舞，好比彩凤朝阳一般抽向$n",
});

int valid_enable(string usage)
{ 
	return usage == "whip" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
	//三无三不手最后一招
	if(me->query_temp("sanwu/buwei")){
		if((int)me->query_skill("yinsuo-jinling",1)>549)
			return ([
                "action":HIW +replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$w"), "$w", "$w"HIW)+NOR,
                "damage":       150 + random(100),
                "damage_type":  "拉伤",
                "dodge":        10+random(30),
                "force":        random(300) + 200,
                "parry":        random(30),
            ]);
		
		else if((int)me->query_skill("yinsuo-jinling",1)>450)
	        return ([
                "action":HIR +replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$w"), "$w", "$w"HIR)+NOR,
                "damage":       120 + random(100),
                "damage_type":  "拉伤",
                "dodge":        20+random(30),
                "force":        random(300) + 200,
                "parry":        random(30),
            ]);
     }
     //卷字诀
	 if(me->query_temp("juan") && (int)me->query_skill("yinsuo-jinling",1)>=350)
        return ([
                "action":HIG +replace_string(replace_string(msg[random(sizeof(msg))], "$w", "$w"), "$w", "$w"HIG)+NOR,
                "damage":       120 + random(150),
                "damage_type":  "拉伤",
                "dodge":        10+random(30),
                "force":        random(300) + 200,
                "parry":        random(30),
            ]);
	 //普通招式
	 return ([
		"action":	msg[random(sizeof(msg))],
		"damage":	60 + random(100),
		"damage_type":	"拉伤",
		"dodge":	random(30),
		"force":	random(300) + 150,
		"parry":	random(30),
     ]);
}

int valid_learn(object me)
{
	object weapon;
	if( (int)me->query("max_neili") < 500 )
		return notify_fail("你的内力不足，没有办法练银索金铃, 多练些内力再来吧。\n");
	if ((int)me->query_skill("yunu-xinjing", 1) < 100)
		return notify_fail("你的玉女心经内功火候太浅。\n");
	if (!objectp(weapon = me->query_temp("weapon"))
	 || ( string)weapon->query("skill_type") != "whip" )
		return notify_fail("你使用的武器不对。\n");
	return 1;
}
 
int practice_skill(object me)
{
	if ( me->query("jingli") < 40)
		return notify_fail("你的体力不够练银索金铃。\n");
	if ( me->query("neili") < 20)
		return notify_fail("你的内力不够练银索金铃。\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	object weap,weap1,ob;
	int ap, dp,damage,i;
	string msg;
	weap = victim->query_temp("weapon");
	
	if (!me->query_temp("weapon"))
	{
		return;
	}

	weap1 = me->query_temp("weapon");
	damage=me->query_skill("yinsuo-jinling",1)+me->query_skill("throwing",1);
	if (objectp(present("yufeng zhen", me)))
	   ob=present("yufeng zhen", me);
//打掉兵器
	if(me->query("env/银索金铃")=="铃铛" 
	 && me->query_skill("yinsuo-jinling", 1) > 450
	 && me->query("neili") > 700
	 && victim->query_temp("weapon")
	 && random(me->query_skill("yinsuo-jinling",1)) > victim->query_skill("dodge", 1)/2 
	 && random(10) > 7) 
	{
		
		message_vision(CYN"只见$N急速挥舞"+ weap1->query("name") + CYN"，转出无数个大小圈子，以阴柔之劲缠住对方的" + weap->query("name") +CYN"！\n" NOR, me );
		message_vision(weap->query("name")+HIC"尖端的铃铛陡然间飞起，点中$n的合谷穴，$n顿时手中一麻！\n"NOR,me,victim);
		victim->add_busy(1);
		ap = me->query("combat_exp", 1) /10000 * me->query_dex(1);
		dp = victim->query("combat_exp", 1) /10000 * victim->query_dex(1);
		if (random(ap + dp ) > dp ) {
			message_vision(HIY"$N气运手臂用力一拽，"+ weap->query("name")+ HIY"却无法从"+weap1->query("name")+HIY"的缠绕中脱开，情急之下只好放弃了手中的兵刃。\n" NOR, victim );
			weap->move(environment(me));
			victim->reset_action();
		}
		else {
			message_vision(YEL"$N暗运巧劲，"+ weap->query("name")+YEL"顺着方向快速旋转数下，解开了"+weap1->query("name")+YEL"的缠绕。\n" NOR, victim );
			victim->add("neili", -500);
		}		

		me->add("neili", -(200+random(100)));
	}
	else if (me->query("env/银索金铃")=="铃铛" 
	 && me->query_skill("yinsuo-jinling", 1) > 450
	 && me->query("neili") > 700
	 && random(10) > 7
	 && !victim->query_temp("weapon"))
	{
		message_vision(HIR"只见$N挥舞"+ weap1->query("name") + HIR"，转出无数个大小圈子，以阴柔之劲缠住对方的手腕和手臂。\n" NOR, me );
		message_vision(HIC"尖端的所系铃铛陡然间回旋，分袭向$n的合谷穴、百汇、印堂诸大穴，$n顿时气血翻涌，劲力迟滞！\n"NOR,me,victim);
		victim->receive_damage("qi",random(1000),me);
		victim->receive_wound("qi",random(500),me);
		victim->add_busy(2);
		victim->add_condition("no_exert",2);

	}
    else if ( me->query("env/银索金铃")=="玉蜂针" 
		&& me->query_skill("yinsuo-jinling",1)>450
		&& random(10)>6
		&& objectp(ob))
	{
		message_vision(HIY"$N趁$n不在意，从怀中掏出数枚玉蜂针，安置在"+weap1->query("name")+HIY"的尖端，攻击更见犀利。\n"NOR,me,victim);
		if (random(me->query_skill("whip",1))>victim->query_skill("parry",1)/3)
		{
			message_vision(HIR"$n一时不查，为$N手中的"+weap1->query("name")+HIR"尖端上所置玉蜂针刺中关元穴。\n"NOR,me,victim);
			victim->apply_condition("bee_poison",5);
			victim->receive_damage("qi",random(800),me);
		}
	}
    else if (me->query("env/银索金铃")=="冰魄银针"
		&& random(10)>6 
		&& present("bingpo yinzhen",me))
	{
		message_vision(HIW"$N趁$n不在意，从怀中掏出数枚冰魄银针，安置在"+weap1->query("name")+HIW"的尖端，攻击更见犀利。\n"NOR,me,victim);
		if (random(me->query_skill("whip",1))>victim->query_skill("parry",1)/3)
		{
			message_vision(HIB"$n一时不查，为$N手中的"+weap1->query("name")+HIB"尖端上所置的冰魄银针刺中合谷穴。\n"NOR,me,victim);
			victim->apply_condition("bing_poison",5);
			victim->receive_damage("qi",random(1500),me);
		}
	}

	
//开了九阴后飞跃
    if (me->query("quest/jiuyingm/pass")
		&&objectp(victim)
		&&random(10)>5
		&&me->is_fighting())
    {
  
	 switch (random(3)){
		case 0:
	   case 1:
	 	
	    msg = HIW"\n$N手中"+weap1->name()+HIW"飘动，幻成一片云雾，又发出玎玎声响，忽急忽缓，忽轻忽重，竟尔如乐曲一般。\n"NOR;
        msg +=HIW"音乐乃依循天籁及人身自然节拍而组成，是故乐音则听之悦耳，嘈杂则闻之心烦。\n"NOR;
		if (random(me->query_per(1))>victim->query_per(1)/3 )
		{
		 // i=(int)me->query_skill("yinsuo-jinling",1)/100;
		  msg+=HIC"$n不由地一阵心烦，顿时手忙脚乱起来,一时不查，为$N的"NOR+weap1->name()+HIC"裹将起来。\n"NOR;
		  victim->add_busy(3);
		  victim->receive_damage("jing",500+random(800),me);
		 }
		 else msg+=HIY"$n平时养心功夫做得很好，临阵不乱，双手敲打发出一阵杂音，使得$N的乐音干扰顿时失效。\n"NOR;
		 message_vision(msg,me,victim);
		 break;

	 case 2:
		 msg = HIM "\n$N这"NOR+weap1->query("name")+HIM"竟能在空中转弯，只听得玎玎玎三声连响，金球疾颤三下，\n"+
                  "分点$n脸上「迎香」、「承泣」、「人中」三个穴道。\n";
         //me->start_busy(random(1));
         if((random(me->query("combat_exp")) > victim->query("combat_exp")/3 ) 
            && ((random(me->query_per(1) ) >= victim->query_per(1)/3 )
            || (random(me->query_dex()) >= victim->query_dex()/3) ))
		{
          msg += HIY "结果$p被$P攻了个措手不及！\n" NOR;
          victim->add_busy((int)me->query_skill("yinsuo-jinling")/50);
		  victim->receive_damage("qi",random(1000),me);
          } 
        else {
          msg += HIW "可是$p看破了$P的企图，趁铃铛点来之际，向旁边一闪身躲了过去。\n" NOR;
          me->start_busy(2);
          }
          message_vision(msg, me, victim);        
        break;
	
	  }
    }
	return ;
}

string perform_action_file(string action)
{
	return __DIR__"yinsuo-jinling/" + action;
}
