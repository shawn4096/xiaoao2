// qixian-wuxingjian.c
// modified by action@SJ 2009/1/10
//updated by Zmud@Sjmud 10/3/2009

#include <ansi.h>
#include <skill.h>

inherit SKILL;

string *xue_name = ({ 
"劳宫穴", "膻中穴", "曲池穴", "关元穴", "曲骨穴", "中极穴", "承浆穴", "天突穴", "百会穴",
"幽门穴", "章门穴", "大横穴", "紫宫穴", "冷渊穴", "天井穴", "极泉穴", "清灵穴", "至阳穴", }); 

string  *msg = ({
"$N使一招「弦外有音」，手中$w弹出一股气流，如风一般卷向$n的$l",
"$N伸指在$w上一弹，一招「吴阳琴音」，整个剑身顿时发出一声龙吟，呼啸着斩向$n的$l",
"$N一招「天河紫气」，手中$w剑芒顿时暴长数尺，光华四射，直直削向$n的$l",
"$N手中$w一式「七盘绝刹」对准$n的$l一连刺出数剑，刹时剑气纵横，势不可挡",
"$N的$w凭空一指，一招「黄龙吐珠」直直刺出，剑尖陡然生出半寸吞吐不定的青芒刺向$n的$l",
"$N手中$w向外一分，使一招「清心普善」，单手在剑身轻轻弹拨，顿时一股剑气直涌$n$l而去",
"$N忽然眼中精光四射，一招「星河气旋」，一股淳厚无比的剑气从$w上激射而出，直逼$n",
});

string *feiyue_msg = ({
"$N左小指轻弹，一招宫韵悄然划向$n的后心，$w不住颤抖，向$n$l刺去",
"$N右手无名指若有若无的一划，将琴弦并做一处，商韵已将$n笼罩住在剑气之中",
"$N五指疾挥，一式角韵无形的刺向$n的左肋，忽然又$N一个转身，又向$n右肋刺去",
"$N将手中剑横扫，同时左右手如琵琶似的疾弹，正是一招支韵，感觉妩媚无比",
"$N使出羽韵，将剑提至唇边，如同清音出箫，剑掌齐出，划向$n的$l",
"$N的脸色变了，人剑一合，使出羽韵，$N手中又多了一柄剑，猛地向$n刺去",
"$N使一招宫韵，手中$w弹出一股气流，如风一般卷向$n的$l，招式极为飘逸",
"$N伸指在$w上一弹，一招商韵，整个剑身顿时发出一声龙吟，呼啸着斩向$n的$l",
"$N一招角韵，手中$w剑芒顿时暴长数尺，光华四射，直直削向$n的$l，$n已然无法躲避",
"$N手中$w一式角韵对准$n的$l一连刺出数剑，刹时剑气纵横，势不可挡，犹如狂风骤雨",
"$N的$w凭空一指，一招支韵直直刺出，剑尖陡然生出半寸吞吐不定的青芒刺向$n的$l",
"$N手中$w向外一分，使一招羽韵，单手在剑身轻轻弹拨，顿时一股剑气直涌$n$l而去",
"$N忽然眼中精光四射，一招宫韵，一股淳厚无比的剑气从$w上激射而出，直逼$n",
});
string *qianbian_msg = ({
"$N将$w在空中虚劈一剑，这一剑自上而下，只不过移动了两尺光景，$n但觉耳中竟然嗡嗡之声大作",
"$N将$w斜刺$n左胸，守中带攻，攻中有守，乃是一招攻守兼备的凌厉剑法",
"$N将$w挥转，指向$n右肩，仍是守中带攻、攻中有守的妙着。$n一凛，只觉来剑中竟无半分破绽",
"$N将$w直入中门，试图制$n要害，$n只得横剑一封，剑尖斜指，$N这一剑含有刺向$n小腹之意，也是守中有攻的妙招",
"$N招式忽变，由先前的绵密化作大开大合，刚猛异常，乃是一招少林派达摩剑法的【三绝剑】招式，三招连出",
"$N的剑招忽变成阴柔婉转之势，人剑合一，使出太极剑法的绕指柔云剑术，剑光闪烁地向$n刺去",
"$N手中$w弹出一股气流，如风一般卷向$n的$l，招式极为飘逸，正是峨嵋剑法中的回风拂柳剑招式",
"$N伸指在$w上一弹，一招嵩山剑法的【龙吟凤祥】，整个剑身顿时发出一声龙吟，呼啸着斩向$n的$l",
"$N脚下快速奔跑，左手不断掐算，右手$w忽然暴长数尺，光华四射，直直削向$n的$l，却是泰山派泰山剑法不传之谜--岱宗如何",
"$N剑招忽然化成华山剑法的【夺命连环三仙剑】招式，手中$w对准$n的$l一连刺出数剑，刹时剑气纵横，势不可挡，犹如狂风骤雨",
"$N招式忽然变得诡异无比，正是衡山派绝技--【衡山云雾回风十三式】，剑尖陡然生出半寸吞吐不定的青芒刺向$n的$l",
"$N将$w向外一分，使出恒山派的【绵里藏针】绝技，剑尖不断向四周轻轻弹拨，顿时一股剑气直涌$n的$l而去",
});

int valid_enable(string usage)
{
	//if (this_player()->query("quest/xxdf/pass")) 
	return usage == "sword" || usage == "parry";
}
int practice_skill(object me)
{
	mapping fam  = me->query("family");
	
	if (!fam || fam["family_name"] != "日月神教" || fam["master_name"] != "任我行")
		return notify_fail("七弦无形剑只能从任我行处学到。\n");
	
	if( (int)me->query("jingli") < 50 || me->query("neili") < 20 )
		return notify_fail("你的体力不够练七弦无形剑。\n");
    if (me->query_skill("dali-shenmofu",1)>1)
		return notify_fail("大力神魔斧以强大的臂力为前提条件，这和剑法的灵动功夫不符，你无法修习七弦无形剑。\n");
	if (me->query_skill("tianmo-gun",1)>1)
		return notify_fail("天魔棍藏拙绝技和剑法的灵动功夫不符，功力相冲，你无法练习七弦无形剑。\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

int valid_learn(object me)
{
	mapping fam  = me->query("family");
	object weapon = me->query_temp("weapon");
	
	if (!fam || fam["family_name"] != "日月神教" || fam["master_name"] != "任我行")
		return notify_fail("七弦无形剑只能从任我行处学到。\n");
	
    if (me->query_skill("dali-shenmofu",1)>1)
		return notify_fail("大力神魔斧以强大的臂力为前提条件，这和剑法的灵动功夫不符，你无法修习七弦无形剑。\n");
    if (me->query_skill("tianmo-gun",1)>1)
		return notify_fail("剑法讲求的是灵动飘逸，你身手天魔棍法影响，无法修习七弦无形剑。\n");
	if( !weapon || weapon->query("skill_type") != "sword" )
		return notify_fail("你使用的武器不对。\n");

	if( (int)me->query("max_neili") < 800 )
		return notify_fail("你的内力不够。\n");

	//if( (int)me->query_skill("xixing-dafa", 1) < 200 )
		//return notify_fail("你的吸星大法火候太浅。\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, j, level, damage,n;
	string str;

	level = me->query_skill("qixian-wuxingjian", 1);
	i = random(me->query_skill("sword"))+50;
	if( i<100 ) i = 100;
	j = random(40)-5;
	damage = (random(6)+1)*35;
	if( damage < 50 ) damage =50;
	//任我行的功夫,千变万化，，放弃，置入pfm设计中
	
	if (intp(n=me->query_temp("qxwxj/qianbian")) && n>=0)
	{
		switch(n){
			case 12: str = HIW"$N"HIW"将$w"HIW"在空中虚劈一剑，这一剑自上而下，只不过移动了两尺光景，$n"HIW"但觉耳中竟然嗡嗡之声大作"NOR;break;
			case 11: str = HIC"$N"HIC"将$w"HIC"斜刺$n"HIC"左胸，守中带攻，攻中有守，乃是一招攻守兼备的凌厉剑法"NOR; break;
			case 10: str = HIY"$N"HIY"将$w"HIY"挥转，指向$n"HIY"右肩，仍是守中带攻、攻中有守的妙着。$n"HIY"一凛，只觉来剑中竟无半分破绽"NOR; break;
			case 9: str = HIG"$N"HIG"将$w"HIG"直入中门，试图制$n"HIG"要害，$n"HIG"只得横剑一封，剑尖斜指，$N"HIG"这一剑含有刺向$n"HIG"小腹之意，也是守中有攻的妙招"NOR; break;
			case 8: str = HIR"$N"HIR"招式化作大开大合，凌厉刚猛，三剑齐出，正是一招少林派达摩剑法「"HIC"达摩三绝剑"HIR"」！"NOR; break;
			case 7: str = HIC"$N"HIC"的剑招忽变成阴柔婉转之势，人剑合一，使出太极剑法的绕指「柔云剑术」，剑光闪烁地向$n"HIC"刺去"NOR; break;
			case 6: str = HIY"$N"HIY"手中$w"HIY"弹出一股气流，如风一般卷向$n"HIY"的$l，招式极为飘逸，正是峨嵋剑法中的「回风拂柳剑」招式"NOR; break;
			case 5: str = HIG"$N"HIG"伸指在$w"HIG"上一弹，一招嵩山剑法的【龙吟凤祥】，整个剑身顿时发出一声龙吟，呼啸着斩向$n"HIG"的$l"NOR; break;
		    case 4: str = HIB"$N"HIB"脚下快速奔跑，左手不断掐算，右手$w"HIB"忽然暴长数尺，光华四射，直直削向$n"HIB"的$l，却是泰山派泰山剑法不传之谜「"HIG"岱宗如何"HIB"」"NOR; break;
			case 3: str = HIC"$N"HIC"剑招忽然化成华山剑法的「"HIR"夺命连环三仙剑"HIC"」招式，手中$w"HIC"对准$n"HIC"的$l一连刺出数剑，刹时剑气纵横，势不可挡，犹如狂风骤雨"NOR; break;
			case 2: str = HIY"$N"HIY"招式忽然变得诡异无比，正是衡山派绝技--【"HIR"衡山云雾回风十三式"HIY"】，剑尖陡然生出半寸吞吐不定的青芒刺向$n"HIY"的$l"NOR; break;
			case 1: str = HIG"$N"HIG"一招昆仑剑术中「疑是银河落九天」,招式宛如一道瀑布由上而下，呼啸而去"NOR; break;
		    case 0: str = HIR"$N"HIR"将$w"HIR"向外一分，使出恒山派的【"HIC"绵里藏针"HIR"】绝技，剑尖不断向四周轻轻弹拨，顿时一股剑气直涌$n"HIR"的$l而去"NOR; break;
			
		}
		me->add_temp("qxwxj/qianbian", -1);
		return ([
			"action":str,
            "damage": me->query("quest/hmy/qxwxj/qianbian/pass")?200 + random(100):100+random(100),
			"damage_type": "刺伤",
			"dodge": random(30),
			"parry": random(30),
			"force": 250 + random(250),
		]);

	}
	
	//泼墨披麻剑
	if(me->query_temp("qxwxj/pomo")){
		switch(me->query_temp("qxwxj/pomo")){
			case 3: str = HIC"$N想起看丹青生所绘的那副泼墨披麻画意的意境，心中微有熏意，「"HIY"长虹贯日"HIC"」向$n使出，将「泼墨披麻剑」绝技发挥的淋漓尽致"NOR; break;
			case 2: str = HIY"$N的剑光闪烁，剑化画笔，辗转腾挪，轻重有别，正是泼墨披麻剑第二招「"HIR"腾蛟起凤"HIY"」"NOR; break;
			case 1: str = HIG"$N以剑作笔，笔意纵横，此时意境进入当时丹青生微醉时的剑意状态，手中第三招「"HIC"春风杨柳"HIG"」顺势而出"NOR; break;
		    default: str = HIR"$N这$w"HIR"上的招数却和琴音恰正相反，$N出招快速而琴音却加倍悠闲，$n势必无法招架，此招功夫非同小可，威力极强"NOR; break;
		}
		me->add_temp("qxwxj/pomo", -1);
		return ([
			"action":str,
            "damage": 150 + random(50),
			"damage_type": "刺伤",
			"dodge": random(30),
			"parry": random(30),
			"force": 250 + random(250),
		]);
	}
//连环
	   if(me->query_temp("qxwxj/lianhuan") ) {
			return ([
                "action": WHT+replace_string(replace_string(feiyue_msg[random(sizeof(feiyue_msg))], "$w", "$w"), "$w", "$w"WHT)+NOR,
				"damage": 200 + random(100),
				"damage_type": "刺伤",
				"dodge":  random(20),
				"parry":  random(20),
				"force":  300 + random(250),

			]);
		}
//普通招式	
		return ([
			"action": msg[random(sizeof(msg))],
			"damage": 100 + random(100),
			"damage_type": "刺伤",
			"dodge":  random(30),
			"force":  250 + random(300),
		]);
}
	
string perform_action_file(string action)
{
	return __DIR__"qixian-wuxingjian/" + action;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
	object weapon, weapon1;
	string name;
	int i,j;
	weapon = me->query_temp("weapon");
	weapon1= victim->query_temp("weapon");

	if( !objectp(weapon) ) return;
    

	i = me->query_skill("qixian-wuxingjian", 1);	
	
	
	
	//五音攻击 宫、商、角、徵、羽
  	
	if (present("qin",me) 
		&& random(10)>7 
		&& me->query_temp("qxwxj/wuxian")
		&& me->query("quest/hmy/qxwxj/wuxian/pass")	)
	{

	 switch (!random(4))
	 {
	   case 0:
          message_vision(HIY"$N手指轻抚琴弦，按在「宫」音上，发出厚重的琴音，$n感觉自己的丹田一阵剧烈跳动，似乎要跳出一般。\n"NOR,me,victim);
	      if (random(me->query_skill("qixian-wuxingjian",1))>me->query_skill("parry",1)/3)
	      {
			  message_vision(HIW"$n感觉自己的精气在不断流失。\n"NOR,me,victim);
			  victim->receive_damage("jing",random(1000),me);
			  victim->receive_wound("jing",random(1000),me);
			  if (victim->query("neili")>3000)
			     victim->add("neili",-1000-random(3000));
	      }
		  else message_vision(HIC"$n忽然意识到这是$N的以琴音攻击的手段，不由地冷笑一声，默不作声。\n"NOR,me,victim);
		  break;
	   case 1:
		  message_vision(HIW"$N轻拢慢捻，「商」音发出，有金属碰撞之声，$n感觉自己的丹田一疼，似乎有一根针扎在此处似得。\n"NOR,me,victim);
	      if (random(me->query_skill("force",1))>me->query_skill("dodge",1)/3)
	      {
			  message_vision(HIC"$n感觉自己的丹田真气涣散，四处奔走，乱成一团。\n"NOR,me,victim);
			  me->apply_condition("no_force",1);
			  me->add_condition("neishang",1);
			  me->add_condition("no_exert",1);
			  if (victim->query("neili")>3000)
			     victim->add("neili",-1000-random(3000));
	      }
		  else message_vision(HIY"$n熟知音律,心无旁骛，$N的商音攻击失效。\n"NOR,me,victim);
		  break;
       case 2:
		  message_vision(HIG"$N左手若兰花状，轻轻一挑琴音「角」音发出，如木裂，似劈柴。\n"NOR,me,victim);
	      if (random(me->query_skill("neili",1))>me->query_skill("neili",1)/2)
	      {
			  message_vision(HIB"$n感觉宛如陷入沼泽之地，身形周转之际，体力消耗甚大，身形顿时受制，缓了下来。\n"NOR,me,victim);
			  victim->add("jingli",-1000-random(1000));
			  //victim->add("jingli",-random(1000));
			  victim->add_busy(1);
			  if (victim->query("neili")>3000)
			     victim->add("neili",-1000-random(3000));
	      }
		  else message_vision(HIY"$n熟知音律,心无旁骛，$N的商音攻击失效。\n"NOR,me,victim);
		  break;

		case 3:
		  message_vision(HIG"$N右手食指以劲气发出，按在琴上，「徵」音发出，势若烈火，琴音袅袅，有燎原之势。\n"NOR,me,victim);
	      if (random(me->query_int(1))>me->query_int(1)/2)
	      {
			  message_vision(HIW"$n忽觉丹田气血涌动，旋即又压制不动，脸色顿时一片惨白。\n"NOR,me,victim);
			   victim->receive_damage("qi",-1000-random(4000),me);
			  victim->receive_wound("qi",-random(4000),me);
			  victim->add_busy(1);
	      }
		  else message_vision(HIC"$n熟知音律,心无旁骛，$N的徵音攻击失效。\n"NOR,me,victim);
		  break;
		 case 4:
		  message_vision(HIC"$N左手大拇指、食指做跳跃式波动，宛如清泉流水，又似水花四溅，正是「羽」音。\n"NOR,me,victim);
	      if (random(me->query_con(1))>me->query_con(1)/2)
	      {
			  message_vision(HIB"$n感受全身经脉为$N琴音所控，真气受制。\n"NOR,me,victim);
			  victim->add_condition("no_exert",1);
			  if (victim->query("neili")>3000)
			     victim->add("neili",-1000-random(3000));
			  
	      }
		  else message_vision(HIY"$n熟知音律,心无旁骛，$N的羽音攻击失效。\n"NOR,me,victim);
		  break;	
	    }
	}
   if(i>=550 && !random(4)){
       if(random(i)>(int)victim->query_skill("parry",1)*2/3
        &&!victim->query_temp("must_be_hit")
        &&!victim->query_condition("no_fight")){
            message_vision(HIG"\n$N剑劲连绵，护住全身，竟无半分空隙，竟能如此毫无破绽，$n暗暗惊异！\n"NOR,me,victim);
            victim->set_temp("must_be_hit",1);
            call_out("qxwxj_must_be_hit",2,me,victim,random(i/50));
       }
   }

   else if(i>=500 && !random(3)){
       if(random(i)>(int)victim->query_skill("dodge",1)/2
        &&!victim->query_temp("must_be_hit")
        &&!victim->query_condition("no_fight")){
            message_vision(HBRED"\n$n从未遇到过如此强敌，$N剑法中也并非没有破绽，只是招数变幻无方，无法攻其暇隙！\n"NOR,me,victim);
            //victim->set_temp("no_fight",1); //太恶毒了，，居然没有取消标记
            victim->apply_condition("no_exert",1);
       }
   }  
  else if(i>=450 && !random(5)){
       if(random(i)>(int)victim->query_skill("dodge",1)/2
        &&!victim->query_temp("must_be_hit")
        &&!victim->query_condition("no_fight")){
            message_vision(HIW"\n$N手腕一震，将体内的无形剑气发动，配合一阵淡淡的琴音侵入$n的全身穴脉！\n"NOR,me,victim);
            //victim->set_temp("no_fight",1);
            victim->apply_condition("no_perform",1);
            victim->add_busy(1);
       }
   }  
   
   name = xue_name[random(sizeof(xue_name))];
   if(i>=350 && !random(3)){
   	if(random(i)>(int)victim->query_skill("dodge",1)/3
        &&!victim->query_temp("must_be_hit")
        &&!victim->query_condition("no_fight")){
            message_vision(HIB "\n只听一阵淳厚的弦音从" + weapon->query("name") +HIB "处传来，$n" HIY "『" + name + "』"
                       NOR + HIB "顿时受震，两耳轰鸣，全身真气乱窜不止！\n" NOR,me,victim);
            //victim->set_temp("no_fight",1);
            victim->add_busy(2+random(2));
            victim->apply_condition("no_exert",1);
       }
   }  
   	 
}

void qxwxj_must_be_hit(object me,object target,int i)
{
    if(!target) return;
    if(!me) {
        target->delete_temp("must_be_hit");
        if(living(target))
            message_vision(HIY"$n终于松了口气，手脚恢复了正常！\n"NOR,target);
        return;
    }
    if(wizardp(me) && me->query("env/qxwxj_test")) write("i is "+i+"\n"NOR);
    
	if(me->query_skill_mapped("sword")!="qixian-wuxingjian"
     ||me->query_skill_mapped("parry")!="qixian-wuxingjian"
     ||i<=0){
        if(living(target))
            message_vision(HIY"$n终于松了口气，手脚恢复了正常！\n"NOR,me,target);
        target->delete_temp("must_be_hit");
		target->delete_temp("no_fight");
        return;
    }
    call_out("qxwxj_must_be_hit",1,me,target,--i);
}
