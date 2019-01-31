/* 
   wuxiang-zhi.c 无相劫指
   和少林罗汉拳(luohan-quan)互备
   取自佛法十二字“广大，智慧，真如，性海，颖悟，圆觉”。
   2/3/98 by snowman
*/

#include <ansi.h>
inherit SKILL;
#include <skill.h>
#include "/kungfu/skill/eff_msg.h";
string *xue_name = ({ 
"劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
"幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
"涌泉穴","大锥穴","风府穴",
});
mapping *action = ({
([
	"action" : "$N将双手拢在衣袖之中，一招「广大无相劫」，暗劲自袖中悄悄涌出，刺向$n",
	"weapon" : "指力",
	"lvl"   : 0,
	"skill_name" : "广大无相劫" ,           
	"damage_type" : "刺伤"
]),
([
	"action" : "$N微微一笑，一招「智慧无相劫」，衣袖连摆，指劲随机弹出，叫人琢磨不透，无法躲避",
	"weapon" : "指风",
	"lvl"   : 10,
	"skill_name" : "智慧无相劫" ,           
	"damage_type" : "刺伤"
]),
([
	"action" : "$N垂手站立，丝毫不动，但闻$n身前哧的一声，闻声不见物，是那招「真如无相劫」",
	"weapon" : "无形指力",
	"lvl"   : 30,
	"skill_name" : "真如无相劫" ,           
	"damage_type" : "刺伤"
]),
([
	"action" : "$N抬头往天，一指「性海无相劫」暗袭$n$l，本人却见丝毫不动，仿若无事发生一样",
	"weapon" : "指力",
	"lvl"   : 60,
	"skill_name" : "性海无相劫" ,           
	"damage_type" : "刺伤"
]),
([
	"action" : "$N一招「颖悟无相劫」向$n点出，闻得一破空之声，却见$P微笑点头，却再无任何动静",
	"weapon" : "指风",
	"lvl"   : 100,
	"skill_name" : "颖悟无相劫" ,           
	"damage_type" : "刺伤"
]),
([
	"action" : "但闻哧哧两声，$n脸色突变，$N却悠闲自在，并无动过手的迹象，这好象是那招「圆觉无相劫」",
	"weapon" : "指风",
	"lvl"   : 200,
	"skill_name" : "圆觉无相劫" ,           
	"damage_type" : "刺伤"
]),
});

int valid_enable(string usage)
{
	if ( this_player()->query("quest/sl/wxjz")!="pass")
		return usage=="finger" ||  usage=="parry"; 
}

int valid_combine(string combo)
{
	if(this_player()->query_skill("wuxiang-zhi", 1) >= 200
	&& this_player()->query_skill("luohan-quan",1) >= 200
	&& this_player()->query_con(1) > 45
	&& this_player()->query_int(1) > 45)
		return combo=="luohan-quan";
}

int valid_learn(object me)
{
	if (!me->query("wxz/done")) 
		return notify_fail("你突然感觉自己‘关元穴’上有点麻木，不禁一阵心惊。\n");
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练无相劫指必须空手。\n");
	if ( me->query_skill("yijin-jing", 1) < 180)
		return notify_fail("你的易筋经内功火候不够，无法学无相劫指。\n");
	if ( me->query("max_neili") < 3000 )
		return notify_fail("你的内力太弱，无法练无相劫指。\n");
	if ( me->query_skill("wuxiang-zhi",1) < 200)
		return notify_fail("你的无相劫指修为不够，目前还无法自行修习。\n");
	if ((int)me->query_int(1) < 50)
        return notify_fail("你的后天悟性不够50，目前还无法自行修习。\n");;
	
	if ( me->query_skill("mohe-zhi", 1) < 160)
	//|| me->query_skill("nianhua-zhi", 1) < 160
	//|| me->query_skill("yizhi-chan", 1) < 160 
		return notify_fail("你摩诃指这门基本指法还未掌握，无法学习无相劫指。\n");
	return 1;
}

void skill_improved(object me)
{
	int skill;
	int neili=me->query("max_neili");
	int poison;

	skill = me->query_skill("wuxiang-zhi", 1);
	if( skill<=100 && skill%20==0 && me->query("wxz/improve")<skill ) {
		tell_object(me, HIG"你练了一阵，不禁觉得心情有些烦乱。\n"NOR);
		tell_object(me,"你的禅宗心法退步了。\n");
		me->set_skill("buddhism",me->query_skill("buddhism",1)-1);
		me->set("wxz/improve",skill);
		return;
	}
	if( skill>100 && skill<=150 && skill%10==0 && me->query("wxz/improve")<skill ) {
		tell_object(me, HIG"你忽然觉得有些神思不属，不禁站了起来。\n"NOR);
		me->set_skill("buddhism",me->query_skill("buddhism",1)-1);
		tell_object(me,"你的禅宗心法退步了。\n");
		me->set("wxz/improve",skill);
		return;
	}
	if( skill>150 && skill<=200 && skill%5==0 && me->query("wxz/improve")<skill ) {
		tell_object(me, HIG"你心烦意乱，不禁从心底升起一阵杀气。\n"NOR);
		me->set_skill("buddhism",me->query_skill("buddhism",1)-1);
		tell_object(me,"你的禅宗心法退步了。\n");
		me->set("wxz/improve",skill);
		return;
	}

	if( skill > 200 ) me->add("wxz/poison",skill+random(skill));
	else return;
	poison=me->query("wxz/poison");

	if (neili/poison>=10) tell_object(me, HIG"你突然感觉自己小腹上‘梁门’、‘太乙’两穴隐隐疼痛。\n"NOR);
	else if(neili/poison>=5) tell_object(me, HIG"你突然感觉自己‘关元穴’上有点麻木，不禁一阵心惊。\n"NOR);
	else if(neili/poison>=2) {
		tell_object(me, HIG"你突然感觉自己阳白、廉泉、风府三处穴道，如万针攒刺，痛不可当。\n"NOR);
		me->unconcious();
	} else if(neili/poison==1) {
		tell_object(me, HIG"你突然感觉体内内息乱窜，无法克制，眼前一黑，昏倒在地。\n"NOR);
		me->add("max_neili", -skill/2);
		me->set_skill("force",me->query_skill("force",1)-1);
		me->set_skill("yijin-jing",me->query_skill("yijin-jing",1)-1);
		me->unconcious();
	} else if(neili/poison==0) {
		tell_object(me, HIG"你突然感觉体内内息澎湃，如洪水般到处流淌乱窜，不禁眼前一黑，倒在地上。\n"NOR);

		me->die();
                log_file("skills/wxjz",sprintf("%s(%s)修炼无相劫经脉俱断而亡。\n", me->query("name"),getuid(me)), me);
		message("channel:chat",	HIC"【江湖传闻】"+ me->query("name") +"因为强练少林武功，经脉俱断而亡。\n" NOR,users());
	}
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action); i > 0; i--)
		if(level >= action[i-1]["lvl"])
			return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level, j;
	string name,msg;
	level   = (int) me->query_skill("wuxiang-zhi",1);
	
	name= xue_name[random(sizeof(xue_name))];
	if (me->query_temp("wxz_wuxiang")){
		switch(me->query_temp("wxz_wuxiang")){
			case 6: msg = HIB"$N向前一纵身，「起手式」蕴含佛家无虚假、无真实本意。直袭$n前胸「"+HIC+name+NOR+HIB"」"NOR; break;
			case 5: msg = HIC"$N第二式「昙花」，$n顿觉眼前宛如昙花一现，似纷华如锦将$n「"+RED+name+NOR+HIC"」笼罩在内。"NOR; break;
			case 4: msg = HIY"$N施展第三式「黄粱」，人本痴迷，几时方能拨云见天，吹醒黄粱梦，近身戳向$n的「"+HIB+name+NOR+HIY"」"NOR; break;
			case 3: msg = HIR"$N食指和中指捏了个兰花状，便凌空一捻，第四式「倾城」，$n顿觉一切如过眼云烟，不知所措。"NOR; break;
			case 2: msg = HIG"$N仰头向后，第五式「登天」，仿佛看破执迷，方能无羁绊，内劲直透指尖，在$n胸腹处连点了数十下。"NOR; break;
			case 1: msg = HIW"这时$N带起一股强烈的旋风，第六式「无我无相」施展出来，劲力汹涌，戳在$n的「"+HIB+name+NOR+HIW"」之上。"NOR; break;
		}
		me->add_temp("wxz_wuxiang", -1);                  
		return([
			"action": msg,
			"force" : 300+random(200),
			"dodge" : random(35),
			"parry" : random(35),
            "damage": 200 + random(200),
			"damage_type" :"戳伤",
		]);
	}
	
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);
			return ([
				"action": action[j]["action"],
				"damage_type": action[j]["damage_type"],
				"lvl": action[j]["lvl"],
				"force": 200 + random(350),
				"dodge": random(30)-10,
				"damage": 150 + random(100),
				"parry": random(20),
				"weapon": action[j]["weapon"],
			]);
		}
	}
}

int practice_skill(object me)
{
	if (!me->query("wxz/done")) 
		return notify_fail("你突然感觉自己阳白、廉泉、风府三处穴道，如万针攒刺，痛不可当。\n");

	if ( me->query("jingli") < 50)
		return notify_fail("你的体力太低了。\n");
	if ( me->query("neili") < 20)
		return notify_fail("你的内力不够练无相劫指。\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

mixed hit_ob(object me, object target)
{
	string msg;
	int j;
	j = me->query_skill("wuxiang-zhi", 1)+me->query_skill("yijin-jing", 1);
	
 
  
	if ( random(me->query_str()) >= target->query_dex()/3
	 && j > 450 //450后飞跃 
	 && random(10) > 5
	 && me->query_skill("finger",1) > 449
	 && me->query("jingli") > 300
	 && random(me->query("combat_exp")) > target->query("combat_exp")/2
	 && me->query("neili") > 500) 
     {
		 switch(random(3)) {
			case 0 :
				message_vision(HIY"$N默运易筋经神功，袖子微动，「袖里乾坤」绝技悄然而发，一股阴柔之极的指风轻飘飘地点向$n！\n"NOR,me,target);
				message_vision(HIC "$n只觉任脉全身一麻，立即半身不遂状，显然已被$N一招点中「关元穴」！\n"NOR,me,target); 
				target->add_busy(1+random(3));
				target->apply_condition("no_exert",1+random(2));
				break;
			case 1 :
				message_vision(HIR"$N运使指风犀利，由无相化有相，形成一道实质的无形剑气，刺向$n的「神阙穴」，全身真气狂泻而出。\n"NOR,me,target);
			  	target->recevied_damage("neili", j);
				if ( target->query("neili") < 0 )
					target->set("neili", 0);
				me->add("neili",-20);
				target->apply_condition("no_perform",1+random(2));
				break;
			case 2 :
			if (me->query_skill_mapped("cuff")=="luohan-quan" 
				&& me->query_skill_prepared("cuff")=="luohan-quan")
			{
				
				message_vision(HIY"$N已经将罗汉拳的招式融会贯通，一式「井栏」，双臂弯曲如环，将$n的招式封闭了起来。\n"NOR,me,target);
			  	target->recevied_damage("qi", j,me);
				target->add_busy(2);
				me->add_temp("apply/cuff",j/3);
				me->add_temp("apply/damage",j/4);
		        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
				me->add_temp("apply/cuff",-j/3);
				me->add_temp("apply/damage",-j/4);
			}
				break;
			
		}
		//message_vision(msg, me, target);
	}
}
int ob_hit(object ob, object me, int damage)
{
        string name,msg;
        int skill, neili, neili1, sh;
        int j = 0;
		skill = me->query_skill("wuxiang-zhi", 1);
        neili = me->query("neili");
        neili1 = ob->query("neili");
        name = xue_name[random(sizeof(xue_name))];

          	                  
        if(random(me->query_str()) > ob->query_dex()/2
         && random(me->query("combat_exp")) > ob->query("combat_exp")/2
		 && random(me->query_skill("finger",1))>ob->query_skill("dodge",1)/2
         && me->query_skill_mapped("finger") == "wuxiang-zhi"
         && neili > 2000 
         && skill > 300 
         && me->query_temp("wxz_wuxiang") //只有开了无相劫才会有此反击
         && random(10) > 6){
         	                    
                ob->receive_damage("qi", (damage>2000)?2000:damage , me);
                ob->receive_wound("qi", (damage>2000)?2000:damage , me);
              	j = (int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi");
              	message_vision(HIY "$N不等$n收招，指力一转直向$n的「"RED""+name+""HIY"」点去，$n闪避不及，被$N一指点中。\n"NOR,me,ob);
                msg = damage_msg(damage, "瘀伤") + "( $n"+eff_status_msg(j)+" )\n";
                j = -(damage*2+skill*3)/3;

				message_vision(msg, me, ob);
                return j;
          }
          else if(random(10) < 3 
                && !me->is_busy()
                && !ob->is_busy()  
                && me->query_skill_mapped("parry") == "wuxiang-zhi"
                && !me->query_temp("wxz_wuxiang")
                && random(me->query("neili"))> ob->query("neili")/2
                  ){
          	        //me->add_temp("yiyang-zhi", 5);
                    ob->receive_damage("jing", (damage>2000)?2000:damage , me);
                    ob->receive_wound("jing", (damage>1000)?1000:damage , me);
              		ob->start_busy(2);
              		//j = (int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi");
              		message_vision(BLU"$N不等$n收招，指力一转直向$n的「"HIW""+name+""BLU"」点去，$n慌忙退让，攻势顿时迟滞。\n"NOR,me,ob);
              		msg = damage_msg(damage, "瘀伤") + "( $n"+eff_status_msg(j)+" )\n";
              		message_vision(msg, me, ob);
                    j = -(damage*2+skill*3) /3;
 
				return j;
              	} 
              	    
          return j; 
        
          
}


string perform_action_file(string action)
{
	return __DIR__"wuxiang-zhi/" + action;
}

int help(object me)
{
	write(
@HELP
无相劫指
    取自佛法十二字“广大，智慧，真如，性海，颖悟，圆觉”。
    上乘佛门功夫，但是随着级别的提高，体内会积聚较多的因为练功积累的戾气，如果
    不及时化解，会使身体受损，可以向无相禅师请教佛法来化解之，如果积聚多多，将
    会带来各种可怕后果，包括降低内力，直到最后走火入魔，终身残废
    可以和罗汉拳(luohan-quan)互备，互备最低要求后天根骨 60，后天悟性 60，该两门
    功夫各 450 级。具体参看各自pfm参数。
HELP
	);
	return 1;
}
