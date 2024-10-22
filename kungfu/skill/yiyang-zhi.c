//cool@SJ,19990628
// Modified by snowman@SJ 20/08/2000
// Modified by Cool@SJ 09/10/2000,change autopfm and yyz_hurt as qishang-quan.
// Update By lsxk@hsbbs 2007/6/13 add 六脉6种效果
/*
        少泽-----------有几率造成对方无法exert,并造成一阳指内伤
        少冲-----------有几率使对方丢失下一次攻击，有几率打飞对方武器,并且造成忙乱.
        关冲-----------有几率使得敌方无法perform,并造成一阳指内伤
        中冲-----------有几率受到一点五倍伤害并附破坏护具或武器
        商阳-----------有几率进行数连击
        少商-----------有几率造成三倍伤害,并附加一阳指内伤
                                           By lsxk@hsbbs 2007/6/13
*/

#include <ansi.h>
#include <skill.h>

inherit SKILL;
#include "/kungfu/skill/eff_msg.h";
#include "/kungfu/skill/yiyang-zhi/liumai_skill_msg.h"

string *xue_name = ({ 
"劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
"幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
"涌泉穴","大锥穴","风府穴",
}); 

string Gmsg;

mapping *action_finger = ({
([
        "action" : "忽听嗤嗤轻响，一股柔和的气流自$N手指涌出，正是一招「阳春暖融」，缓缓点向$n$l",
        "weapon" : "一阳指力",
        "force": 200,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "阳春暖融",
	    "lvl": 0,
        "damage_type" : "刺伤"
]),
([
        "action" : "$N右手食指微点，出招「晓天初阳」，一股雄浑的一阳指力射向$n，出手沉稳，招数正大",
        "weapon" : "一阳指力",
        "force": 150,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "晓天初阳",
	"lvl": 20,
        "damage_type" : "刺伤"
]),
([
        "action" : "$N一指「日出霞光」，激出的一股罡气涌向$n，看似是温淳平和，但沛然浑厚，无可与抗",
        "weapon" : "一阳指力",
        "force": 180,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "日出霞光",
	    "lvl": 30,
        "damage_type" : "内伤"
]),
([
        "action" : "忽听嗤嗤轻响，一股柔和的气流自$N手指涌出，正是一招「阳春暖融」，缓缓点向$n$l",
        "weapon" : "一阳指力",
        "force": 220,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "阳春暖融",
	    "lvl": 40,
        "damage_type" : "刺伤"
]),
([
        "action" : "$N踏前一步，伸指凌空轻轻一点，$n只觉气息一紧，已被「赤日焦阳」的刚阳气劲触到$l",
        "weapon" : "纯阳真气",
        "force": 260,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "赤日焦阳",
	    "lvl": 50,
        "damage_type" : "刺伤"
]),
([
        "action" : "$N衣袖轻摆，罡阳柔气从袖底挥出，涌向$n的$l，正是玄功若神的一招「晓阳云暖」",
        "skill_name" : "晓阳云暖",
        "force": 300,
        "dodge": random(20),
        "parry": random(10),
        "weapon" : "一阳指力",
	    "lvl": 60,
        "damage_type" : "内伤"
]),
([
        "action" : "$N面带微笑，伸出右食指，缓缓点向$n胸口，这招「暮云映日」劲气弥漫，却无丝毫破空之声",
        "weapon" : "一阳指力",
        "force": 330,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "暮云映日",
	    "lvl": 70,
        "damage_type" : "刺伤"
]),
([
        "action" : "只见$N食指微屈，一指「九天乾阳」点出，气象森严，雍容肃穆，于威猛之中不脱王者风度！",
        "weapon" : "纯阳真气",
        "force": 380,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "九天乾阳",
	    "lvl": 80,
        "damage_type" : "内伤"
]),
([     
        "action" : "$N头顶白气氤氲，渐聚渐浓，便似蒸笼一般，食指伸出，一式「三阳开泰」按向$n！",
        "weapon" : "纯阳真气",
        "force": 420,
        "dodge": random(20),
        "parry": random(10),
        "skill_name" : "三阳开泰",
    	"lvl": 90,
        "damage_type" : "震伤"
])
});

mapping *action_sword = ({
([
        "action" : "$N嘴角轻笑，提$w平胸，看准时机一剑刺出，激起呼呼风声，迅猛无比地直插$n$l",
	    "lvl":0,
        "damage_type" : "刺伤",
]),
([ 
        "action" : "$N左手捏个剑诀，右腕传动，将一阳指神功化于$w之上，出剑凝重，平平正正地刺向$n",
	    "lvl":20,
        "damage_type" : "刺伤",
]),
([ 
        "action" : "只见$N屏息凝神，脚步沉着，剑走刀势，一式横劈，砍向$n$l，招式威猛正大",
	     "lvl":30,
        "damage_type" : "割伤",
]),
([
        "action" : "$N脚下步法微变，身随剑走，端凝自重，极飘逸的一剑向$n刺出，轻灵中却也不失王者气象",
		"lvl":100,
        "damage_type" : "刺伤",
]),
([
        "action" : "$N平推一剑，手中的$w看似渐渐沉重，使动时略比先前滞涩，但实是举轻若重，威猛之极",
	    "lvl":180,
        "damage_type" : "刺伤",
]),
});

int valid_enable(string usage) 
{  
       //增加指剑，取消激发sword by sohu
	   return usage=="finger" || usage=="parry" ; 
}

int valid_learn(object me)
{     
       if ((string)me->query("gender") != "男性") 
                return notify_fail("一阳指乃是纯阳玄功，你如何可以修习？\n");
       if (!me->query("quest/tls/yyz/pass")) 
                return notify_fail("一阳指大理段氏绝技，你不得段氏真传如何可以修习？\n");

	   if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练一阳指必须空手。\n");
       if ((int)me->query("max_neili") < 1000)
                return notify_fail("你的内力太弱，无法练一阳指。\n");
       return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action_finger)-1; i >= 0; i--)
                return action_finger[i]["skill_name"];
}
void skill_improved(object me)
{
	int i = (int)me->query_skill("yiyang-zhi", 1);   

	if (i == 100)
	{
		 tell_object(me,HIY"你经过辛苦修炼，终于将一阳指提升到九品境界。\n");
	     me->set("yyz/degree",9);
	 }
	if (i == 200)
	{
		tell_object(me,HIY"你经过辛苦修炼，终于将一阳指提升到八品境界。。\n");
        me->set("yyz/degree",8);
	 }
	if (i == 300) 
	{
		tell_object(me,HIY"你经过辛苦修炼，终于将一阳指提升到七品境界。。\n");
        me->set("yyz/degree",7);
	 }
	if (i == 350)
	  {
		tell_object(me,HIY"你经过辛苦修炼，终于将一阳指提升到六品境界。。\n");
        me->set("yyz/degree",6);
	 }
	if (i == 400)
     {
		tell_object(me,HIY"你经过辛苦修炼，终于将一阳指提升到五品境界。。\n");
        me->set("yyz/degree",5);
	 }
	if (i == 450)
    {
		tell_object(me,HIY"你经过辛苦修炼，终于将一阳指提升到四品境界。。\n");
        me->set("yyz/degree",4);
	 }
	if (i == 500)
	{
		tell_object(me,HIY"你经过辛苦修炼，终于将一阳指提升到三品境界。。\n");
        me->set("yyz/degree",3);
	 }
	if (i == 550)
	{
		tell_object(me,HIY"你经过辛苦修炼，终于将一阳指提升到二品境界。。\n");
        me->set("yyz/degree",2);
	 }
	if (i == 600)
	 {
		tell_object(me,HIY"你经过辛苦修炼，终于将一阳指提升到一品境界。一阳指臻于大成。\n");
        me->set("yyz/degree",1);
	 }

}
mapping query_action(object me, object weapon)
{
        int i, level, n,j;
        mapping skill_name;
        string msg,msglm, *lmsj_msg;

        level = me->query_skill("yiyang-zhi",1);
        me->delete_temp("hit_ob_hit");
        //一阳指激发剑法功效
		if( objectp(weapon) ){
           for(i = sizeof(action_sword); i > 0; i--) { 
			if(level >= action_sword[i-1]["lvl"]) {
				j = NewRandom(i, 20, level/5);
				return ([
					"action": action_sword[j]["action"],
					"lvl": action_sword[j]["lvl"],
					"damage_type": action_sword[j]["damage_type"],
					"force": 150 + random(300),
					"dodge": random(30),
					"parry": random(30),
					"damage": 100+ random(100),
				]);
			}
		   }
		}        
          //yz3m,激发一指三脉
         if( intp(n = me->query_temp("yyz/yz3m")) && n > 0 ){
                switch(n){
                   case 4: msg = "$N忽地跃起，左掌抚胸，右手食指点出，招式未老，立即缩回，快似闪电，但着指之处，竟无分毫偏差，连点向\n"+
                               "$n的强间、脑户、风府、大椎、陶道、身柱、神道、灵台．．等督脉三十大穴"; break;
				   case 3: msg = "$N右手食指微曲，突然点出，使的竟然便是＂一阳指＂。但见$N食指幌动，来势虽缓，$n上半身正面大穴\n"+
                                "却已全在$N一指笼罩之下，竟不知要点的是那一处穴道，九处大穴皆大指之虞";break;
                   case 2: msg = "$N招数未完，抢上数步，又是一指点出，这次却是指向$n小腹，这一指所盖罩的要穴更广，肚腹间冲脉十二大穴，自幽门、\n"+
                                "通谷，下至中注、四满，直抵横骨、会阴，尽处于这一指威力之下"; break;
                   case 1: msg = "跟着第三指又出，这一指迅如闪电，直指$n眉心，指尖闪动，似乎头部太阳，人中，百会．．等各大要穴尽在这一指笼罩";break;
                  
				   //default:break;
                }
				me->add_temp("yyz/yz3m",-1);
                if (level>=550) msg=RED+msg+NOR;
                else if (level>=450) msg = YEL + msg + NOR;
                else if (level>=350) msg = CYN + msg + NOR;
                return ([
                        "action":msg,
                        "damage_type":"内伤",
                        "dodge": 20,
				    	"damage":me->query("yideng/ronghe","pass")?(250+random(100)):(150+random(100)),
                        //"damage":200+random(50),
						"force": level + me->query("jiali"),
                        "skill_name" : "一指点三脉",
                        "weapon" : "一阳指力",
                ]);
        }
		//六脉剑,需要六脉学全方可使用
		 if( intp(n = me->query_temp("yyz/lmsj")) && n > 0 ){
               switch(n){
                   case 6: msglm =HIC"\n$N左手小指一伸，使出「少泽剑法」，一股劲气从$P少泽穴中激射而出，指向身前$n！\n"+
										 "$n只觉得一股无形剑气向你的$l激射而来，其变化精微，快绝无比，当真是忽来忽去，变化精微\n"NOR;break;
                   case 5: msglm =MAG"\n$N无名指一挥，拙滞古朴的关冲剑气直射而出，端端正正地刺向$n的$l,正是「关冲剑法」\n"+
									"$n感觉到那无形剑气拙滞古朴，奇正有别，委实难以架挡,无形剑气竟然使你无从躲避\n"NOR;break;
                   case 4: msglm =HIG"\n$N拇指一屈，食指点出，变成了「商阳剑法」，一缕剑气向$n$l刺出，其轻灵迅速，快速无比\n"+
									"那无形的剑气巧妙灵活，难以琢磨，幻化间直奔$n而来，瞬间已逼到了$跟前\n"NOR;break;

				   case 3: msglm =HIR"\n$N身形一恭，双手前伸，一式「中冲剑法」,双手合使，两道凌厉无比的剑气破空刺向$n的$l\n"+
										"猛然间$n感到周身大穴都被一股大开大合，气势雄伟的无形剑气所包围\n"NOR;break;
                   case 2: msglm =CYN"\n$N掌托于胸前，伸出右小指，一招「少冲剑法」,缓缓地点向$n的周身大穴，弹指无声，但却嗤嗤作响\n"+
										"$n待那剑气到得近前，竟是劲气弥漫，破空之声甚厉,无形剑气似‘拙’而不缓，‘缓’而不弱，有如神剑\n"NOR;break;
                   case 1: msglm =HIB"\n$N大拇指向前双按，「少商剑气」便如是一幅泼墨山水相似，纵横倚斜，寥寥数笔，却是剑路雄劲\n"+
									 "$n见那无形剑气颇有石破天惊、风雨大至之势，大开大阖，气派宏伟逼得$n纵高伏低，东闪西避！\n"NOR;break;

				   default:break;
                }
                if (n>1) n-1;
                return ([
                        "action":msglm,
                        "damage_type":"刺伤",
                        "dodge": 20,
				    	"damage":200+random(100),
						"force": level + me->query("jiali"),
                        "skill_name" : "六脉神剑",
                        "weapon" : "无形剑气",
                ]);
        }

 //  ####六脉#### 单剑或此去彼来
        if ( stringp(msg = me->query("env/liumai")) 
        && me->query("jiali") > 50 
        && mapp(skill_name = me->query("liumai-shenjian")) 
        && me->query_skill("liumai-shenjian", 1) )
        {
                n = member_array(msg, keys(skill_name));
           if (sizeof(keys(skill_name))<2){
                if( n != -1 )
                        switch(msg){
                                case "shaoze": msg = shaoze[random(sizeof(shaoze))]; break;
                                case "guanchong": msg = guanchong[random(sizeof(guanchong))]; break;
                                case "shangyang": msg = shangyang[random(sizeof(shangyang))]; break;
                                case "shaochong": msg = shaochong[random(sizeof(shaochong))]; break;
                                case "zhongchong": msg = zhongchong[random(sizeof(zhongchong))]; break;
                                case "shaoshang": msg = shaoshang[random(sizeof(shaoshang))]; break;
                                default: msg = "";
                        }
                else msg = "";
           }
           else{
               if( n != -1 )
                   switch(msg){
                       case "shaoze": msg = shaoze[random(sizeof(shaoze))]; break;
                       case "guanchong": msg = guanchong[random(sizeof(guanchong))]; break;
                       case "shangyang": msg = shangyang[random(sizeof(shangyang))]; break;
                       case "shaochong": msg = shaochong[random(sizeof(shaochong))]; break;
                       case "zhongchong": msg = zhongchong[random(sizeof(zhongchong))]; break;
                       case "shaoshang": msg = shaoshang[random(sizeof(shaoshang))]; break;
                       default: msg = "";
                   }
               else if( n == -1 && msg == "shenjian") {
                   lmsj_msg = keys(me->query("liumai-shenjian"));
                   Gmsg = lmsj_msg[random(sizeof(lmsj_msg))];
                   switch(Gmsg){
                       case "shaoze": msg = shaoze[random(sizeof(shaoze))]; break;
                       case "guanchong": msg = guanchong[random(sizeof(guanchong))]; break;
                       case "shangyang": msg = shangyang[random(sizeof(shangyang))]; break;
                       case "shaochong": msg = shaochong[random(sizeof(shaochong))]; break;
                       case "zhongchong": msg = zhongchong[random(sizeof(zhongchong))]; break;
                       case "shaoshang": msg = shaoshang[random(sizeof(shaoshang))]; break;
                       default: msg = "";
                   }
               }
               else msg = "";
           }
                
            //hoho here is a bug,如果jiali <50的话，这个时候msg还是stringp,就是set的那个，所以加个判断:)
        	if( stringp(msg) && msg!=""){
                	me->set_temp("hit_ob_hit", 1);
                	me->set_temp("liumai_hit", me->query_str()*2);
                	
                	return ([
                        	"action": msg,
                        	"damage": 200+me->query_skill("liumai-shenjian", 1),
                        	"damage_type": "刺伤",
                        	"dodge": random(me->query_dex()),
                        	"force": me->query_skill("force")/2 + me->query_str() * 5 + me->query("jiali") * 2,
                        	"parry": random(me->query_con()),
                        	"weapon" : "剑气",
                	]);
        	}
        }
     // ####一阳指####普通攻击 
        
		for(i = sizeof(action_finger); i > 0; i--)
                if(level >= action_finger[i-1]["lvl"])
			return action_finger[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{ 
        if ((int)me->query("jingli") < 70)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 30)
                return notify_fail("你的内力不够练一阳指。\n");                         
        me->receive_damage("jingli", 40);
        me->receive_damage("neili", 10+random(10));
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yiyang-zhi/" + action;
}
int ob_hit(object ob, object me, int damage)
{
        string name,msg;
        int skill, neili, neili1, sh;
        int j = 0;
		skill = me->query_skill("yiyang-zhi", 1);
        neili = me->query("neili");
        neili1 = ob->query("neili");
        name = xue_name[random(sizeof(xue_name))];
/*
        if(me->query_temp("yiyang-zhi")){
                me->delete_temp("yiyang-zhi");
                return j;
        }
		*/
          	                  
        if(random(me->query_str(1)) > ob->query_dex(1)/2
         && random(me->query("combat_exp")) > ob->query("combat_exp")/2
         && me->query_skill_mapped("finger") == "yiyang-zhi"
         && neili > 2000 
         && skill > 350 
         && !me->query_temp("yiyang-zhi")
         && random(10) > 7){
         	    //me->add_temp("yiyang-zhi", 5);                 
                ob->receive_damage("qi", (damage>2000)?2000:damage , me);
                ob->receive_wound("qi", (damage>2000)?2000:damage , me);
              	j = (int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi");
              	message_vision(CYN "$N不等$n收招，指力一转直向$n的「"RED""+name+""CYN"」点去，$n闪避不及，被$N一指点中。\n"NOR,me,ob);
                msg = damage_msg(damage, "瘀伤") + "( $n"+eff_status_msg(j)+" )\n";
                j = -(damage*2+skill*3)/3;

				message_vision(msg, me, ob);
                return j;
          }
          else if(random(10) < 5 
                && !me->is_busy()
                && !ob->is_busy()  
                && me->query_skill_mapped("parry") == "yiyang-zhi"
                && !me->query_temp("yiyang-zhi")
                && me->query("neili")> ob->query("neili")
                  ){
          	        //me->add_temp("yiyang-zhi", 5);
                    ob->receive_damage("jing", (damage>800)?800:damage , me);
                    ob->receive_wound("jing", (damage>400)?400:damage , me);
              		ob->start_busy(2);
              		j = (int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi");
              		message_vision(BLU"$N不等$n收招，指力一转直向$n的「"HIW""+name+""BLU"」点去，$n慌忙退让，攻势顿时迟滞。\n"NOR,me,ob);
              		msg = damage_msg(damage, "瘀伤") + "( $n"+eff_status_msg(j)+" )\n";
              		message_vision(msg, me, ob);
                    j = -(damage*2+skill*3) /3;
 
				return j;
              } 
              	    
         // return j; 
        
          
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
       int hurt, lvl = me->query_skill("yiyang-zhi");
       int i, target_force, target_dodge, target_parry,j;
        string name,name2,liumai_set;
        object weapon = victim->query_temp("weapon");
        object *inv;
        name = xue_name[random(sizeof(xue_name))];
        name2 = xue_name[random(sizeof(xue_name))];
		
		i=me->query("yyz/degree");
        
		target_force = (int)victim->query_skill("force",1);
        target_dodge = (int)victim->query_skill("dodge",1);
        target_parry = (int)victim->query_skill("parry",1);
        if(me->query("env/liumai")) liumai_set = me->query("env/liumai");
       if( me->query_temp("yyz/yz3m")&&me->query("env/一阳指点穴"))
		{
          switch(random(4)){
			case 0:
		      if((!me->query_temp("weapon")&&me->query("neili")>2000&& random(lvl+target_parry) > target_parry) 
              || random(me->query_skill("jingmai-xue")) > victim->query_skill("jingmai-xue") /2){
		          message_vision(HIW"$n哪里知道这一指点三脉的精妙？一个招架不周，「"+HIR+name+HIW+"」已被点中，立时内息大乱！\n"NOR,me,victim);
                  if(!victim->query_condition("no_exert")) victim->apply_condition("no_exert",1+random(2));
				  else victim->add_condition("no_exert",1+random(2));
                  victim->add_condition("yyz_hurt",1+random(3));
				  }
				break;
			case 1:
             if(random(me->query("combat_exp"))> victim->query("combat_exp")/2)
	     	  {
                message_vision(HIC"$n见$N的这招一指点三脉笼罩督脉三十六道大穴，实在躲无所躲，「"+HIR+name+HIC+"」已被点中，一阵剧痛传来，忍不住吐了一口鲜血！\n"NOR,me,victim);
                victim->receive_damage("jing", 2000,me);
				victim->receive_damage("qi", 2000,me);
                victim->add_condition("yyz_hurt",1+random(3));
		      }
			  break;
			case 2:
              message_vision(HIG"$n见$N的这招一指点三脉笼罩整个任脉，心中一慌，「"+HIR+name+HIG+"」已被点中，身形顿时受制！\n"NOR,me,victim);
              if (victim->is_busy()) victim->add_busy(1+random(3));
              else victim->start_busy(1+random(3));
			  victim->add_condition("yyz_hurt",1+random(3));
			  break;
			case 3:
              if ((int)me->query("yyz/degree")<5)
              {             
			    message_vision(HIY"$N一阳指已然到达"+HIR+chinese_number(i)+"品"+HIY+"境界，右手食指点穴，出指可缓可快，缓时潇洒飘逸，快则疾如闪电，但着指之处，分毫不差，忽觉「"+HIR+name+HIY+"」酸痛！\n"NOR,me,victim);
                if (victim->is_busy()) victim->add_busy(1+random(3));
                else victim->start_busy(1+random(3));
				victim->receive_wound("jing",random(500),me);
				victim->add("jingli",-random(1000));
				victim->add_condition("yyz_hurt",1+random(3));
			  }
			  break;
		  }
		}
//六脉的auto,要加力大于50
        if((int)me->query("jiali")>50
        && !me->query_temp("weapon") 
        && (int)me->query_skill("liumai-shenjian",1)>29
        && !me->query_temp("yyz/yz3m") ){
             //少泽Auto
            if((Gmsg =="shaoze"&&liumai_set=="shenjian" || liumai_set=="shaoze") && me->query("liumai-shenjian/shaoze")
            && random(lvl) > target_force/4 && random(2) ){
                message_vision(HIC"$N脸上微微一笑,小拇指这股劲力去的竟是无声无息,$n根本无法察觉.\n"NOR,me,victim);
                message_vision(HIW"突然,$n顿觉「"+HIR+name+HIW+"」一麻,原来已被$N的"CYN"少泽剑气"HIW"点中,内息再也无法凝聚!\n"NOR,me,victim);
                //少泽剑破对方真气
				victim->receive_damage("qi",random(2000),me);
				message_vision(HIR"突然,$n顿觉全身真气狂泻而出!\n"NOR,me,victim);
				victim->add("neili",-random(2000));
				if(!victim->query_condition("no_exert")) victim->add_condition("no_exert",1+random(2));
					victim->add_condition("yyz_hurt",1+random(3));
					victim->add_busy(1);
            }
             //少冲Auto
            else if((Gmsg=="shaochong"&&liumai_set=="shenjian"||liumai_set=="shaochong") && me->query("liumai-shenjian/shaochong")
            && random(lvl) > target_force/4){
                if (weapon){
					message_vision(HIG"$N小拇指顺势轻轻一挑,顿时一股破空之气直刺$n手腕。\n"NOR,me,victim);
					if(!random(4)||(me->query_temp("yyz/6mai/6mai")&&random(2))){
						message_vision(HIY"$n手腕被袭，一个把持不住，"+weapon->query("name")+HIY"脱手而出，心下大惊，顿时手忙脚乱！\n"NOR,me,victim);
						weapon->unequip();
						weapon->move(environment(victim));
						victim->add_busy(2+random(3));
                }
                else{
                    message_vision(HIM"$n只觉这股内劲非同小可，连忙撤招避了开去。\n"NOR,me,victim);
                    victim->add_temp("lost_attack", 1);
                }
                }
                else{
                    message_vision(HIB"$n只觉一股剑气袭至,不敢正面接招,连忙撤招闪在了一边。\n"NOR,me,victim);
                    victim->add_temp("lost_attack", 1);
                }
            }
             //关冲Auto
            else if((Gmsg=="guanchong"&&liumai_set=="shenjian"||liumai_set=="guanchong") && me->query("liumai-shenjian/guanchong")
            && random(lvl) > target_force/4 && random(2) ){
                message_vision(HBRED"$N无名指一弹，竟然激起一股气流，电石火光间便刺中了$n的「"+HIW+name2+NOR+HBRED"」，$n顿觉气血翻腾，出招涩滞!\n"NOR,me,victim);
                if(!victim->query_condition("no_perform")) victim->add_condition("no_perform",1+random(2));
                victim->add_condition("yyz_hurt",1+random(3));
				victim->receive_damage("qi",random(2000),me);

                victim->add_busy(1);
            }
             //中冲Auto
            else if((Gmsg=="zhongchong"&&liumai_set=="shenjian"||liumai_set=="zhongchong") && me->query("liumai-shenjian/zhongchong")
            && random(lvl) > target_dodge/4 ){
                message_vision(HIG"$N更将六脉劲力附着在此招中，中指点出，气象庄重，内劲十足！\n"NOR,me,victim);
                damage_bonus = damage_bonus/2;
                inv = filter_array(all_inventory(victim),(:$1->query("equipped")=="worn":));
                inv -= ({0});
                if((!random(3) ||( me->query_temp("yyz/6mai/6mai") && random(2)))&& sizeof(inv) >= 1){
                    for(i=0; i<(1+random(sizeof(inv))); i++){
                        inv[i]->unequip();
                        inv[i]->move(environment(victim));
                        inv[i]->set("name", "碎裂的" + inv[i]->query("name"));
                        inv[i]->delete("value");
                        inv[i]->set("armor_prop", 0);
                    }
                    message_vision(HBBLU+HIC"这股六脉剑气如此刚劲有力，刚碰触到$n的护体防具，便将其震成碎片，纷纷掉落。\n"NOR,me,victim);
                }
                return damage_bonus;
            }
             //商阳Auto
            else if((Gmsg=="shangyang"&&liumai_set=="shenjian"||liumai_set=="shangyang") && me->query("liumai-shenjian/shangyang") ){
            if ( random(lvl) > target_parry/4 ){
                if(!me->query_temp("yyz/6mai/shangyang") && random(2) ){
                    message_vision(HIC"$N一指商阳剑法击中对手，食指临空虚点数下，$n顿觉几股凌厉剑气袭来！\n"NOR,me,victim);
                    me->set_temp("yyz/6mai/shangyang",1);
                    call_out("liumai_shangyang",0,me,victim,lvl);
                }
                else{
                    if(me->query_temp("yyz/6mai/shangyang")) me->delete_temp("yyz/6mai/shangyang");
                    message_vision(HIB"$N潜运商阳剑气，蓄势待发！\n"NOR,me,victim);
                }
            }
            else message_vision(HIB"$N潜运商阳剑气，蓄势待发！\n"NOR,me,victim);
            }
             //少商Auto
            else if((Gmsg=="shaoshang"&&liumai_set=="shenjian"||liumai_set=="shaoshang") && me->query("liumai-shenjian/shaoshang")
            && random(lvl) > target_parry/3 ){
                message_vision(HIR"$N面色凝重，运足内劲，大拇指一指点出，刹那间，一股罕见凌厉的剑气直刺$n,威力实乃骇人！\n"NOR,me,victim);
                victim->receive_damage("qi",random(2000),me);
				victim->add_condition("yyz_hurt",1+random(3));
                return damage_bonus*2;
            }
        }

        if(me->query_temp("autopfm_yyz")){
                me->delete_temp("autopfm_yyz");
                return 0;
        }
        
        if( me->is_perform() 
        || !me->query("env/一阳指点穴")
        || me->query("neili") < 1000
	    || me->query("max_neili") < 1500
        || me->query_skill("yiyang-zhi", 1) < 150 
        //|| me->query_temp("yyz/yz3m")
			)
        	return 0;       

        
        if ( lvl > 300) lvl = 300 + (lvl-300)/10;
        
        if (random(10) > 6
        && !me->query_temp("yyz/yz3m")
        && me->query_skill_prepared("finger") == "yiyang-zhi"
        && me->query("combat_exp") >= (victim->query("combat_exp")/3*2) ){
          	
                if (me->query("env/liumai")
                && me->query_temp("liumai_hit")
                && !me->query_temp("autopfm_yyz")
                && !victim->is_busy()
                && !objectp(weapon = me->query_temp("weapon"))
                && me->query("jiali") > 50  
                && random(10) > 3
                
                ){
                        if (me->query("neili") > 40)
                                me->add("neili", -40);
                        else	me->set("neili", 0);
                        hurt = (victim->query("neili") < lvl / 6 ? victim->query("neili") : lvl / 6);
                        victim->add("neili", -hurt/2);
                        victim->receive_wound("qi", -lvl / 6);
                        victim->add("jingli", -lvl / 6);
                        me->add_temp("autopfm_yyz",2);
                        me->delete_temp("liumai_hit");
                        victim->start_busy(2+random(2));    
                        return HBRED "电石火光间$N指锋一转,指力中携着一股六脉劲风拂向$n,\n"+
                                     "$n被$N一指点中【"+name+HBRED"】，丹田中真气一滞，身形微微一僵。\n" NOR;
                } 
                return 0;
        } 
        else if (lvl > 150 
        && random(10) > 3
        && !victim->query_temp("yyz")
        && !me->query_temp("autopfm_yyz")
        ) { if(me->query_temp("liumai_hit")){
                me->delete_temp("liumai_hit");
                return 0;
        } else {
            	switch (random(3)) {
               		case 0: 
                    		if (weapon){
                       			weapon->unwield();
                       			weapon->move(environment(victim));
                       			victim->add("neili", -lvl/5);
                       			
                       			me->set_temp("autopfm_yyz",3);
                       			return CYN "$N反手一指,这一招变化莫测,正点中$n的「"HIR+name+CYN"」，\n"NOR+
                       			       CYN "$n手一麻，"+weapon->query("name")+CYN"把持不住，掉在地上。\n" NOR; 
                       		} 
                       		else {
                       			victim->add("neili", -lvl*4);
                       			victim->add_busy(1);
                       			me->set_temp("autopfm_yyz",1);
                       			return CYN "$N反手一指,这一招变化莫测,正点中$n的「"HIR+name+CYN"」，\n"NOR+
                       			       YEL "紧接着$N食指一曲一弹,一道指力破空而出,正点中$n的「"RED""+name2+""YEL"」，$n的真气立刻涣散。\n" NOR; 
                       		}
                       		break;
               		case 1: 
               			victim->start_busy(2+random(2));
               			
               			me->set_temp("autopfm_yyz",3);
                    		return CYN "$N出指如电,刹那间数道一阳指力直逼$n的「"HIR+name+CYN"」，$n身子一滞,被击中要穴。\n" NOR;
                    		break;
               		case 2: 
               			victim->apply_condition("no_perform", 2+random(2));
               			victim->apply_condition("no_exert",1+random(2));
               			
               			me->set_temp("autopfm_yyz",3);
                    		return CYN "$N一指点出,正中$n的「"HIR+name+CYN"」，一阳指内劲直透入$n体内各大要穴。\n" NOR;
                    		break;
            	}
        }
}

}

int liumai_shangyang(object me, object target, int lvl)
{
    int i;
    if(me->query("env/liumai")
    && objectp(me)
    && objectp(target)
	&& me->query("env/liumai")=="shangyang"
    && me->query("liumai-shenjian/shangyang")
    && me->is_fighting()
    && (int)me->query("jiali")>50
    && !me->query_temp("weapon")
    && me->query_skill_prepared("finger") == "yiyang-zhi"
    && me->query_skill_mapped("finger") == "yiyang-zhi" ){
      message_vision(HIW"$N的那几股剑气刹那间已经袭到$n面前，直把$n点的手忙脚乱！\n"NOR,me,target);
	  if (target) target->add_busy(2);
      me->set_temp("yyz/6mai/shangyang",1);
      if(me->query_temp("yyz/6mai/6mai")){
          me->add_temp("apply/attack",lvl/4);
          me->add_temp("apply/dodge",lvl/4);
      }
      for(i=0;i<(2+random(2));i++){
        if (lvl>500) COMBAT_D->do_attack(me, target, 0, 3);
        else COMBAT_D->do_attack(me, target, 0, 1);
      }
      if(me->query_temp("yyz/6mai/6mai")){
          me->add_temp("apply/attack",-lvl/4);
          me->add_temp("apply/dodge",-lvl/4);
      }
    }
    return 1;
}
