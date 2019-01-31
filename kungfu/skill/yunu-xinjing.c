// yunu-xinjing.c 玉女心经
// Modify By River 10/98

inherit FORCE;
#include <ansi.h>

int valid_enable(string usage) { return usage == "force"; }

#include "force.h"

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("yunu-xinjing", 1);

	if ( me->query("gender") == "无性") 
		return notify_fail("你无根无性，阴阳不调，难以领会高深的玉女心经神功。\n");

        if ( lvl < 120)
                return notify_fail("你现在还只能通过合修来领会高深的玉女心经神功。\n");

        if ((int)me->query_skill("yunu-xinjing", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("yunu-xinjing", 1) >= 200 )
               return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

        return valid_public(me);
}

int practice_skill(object me)
{
	if((int)me->query_skill("yunu-xinjing", 1) >= 200 )
	{
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
		{
			me->improve_skill("yunu-xinjing", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("你现在的修为不足以提高玉女心经了。\n");
	}
	else return notify_fail("你现在的玉女心经修为只能用学(learn)的来增加熟练度。\n");

}
void skill_improved(object me)
{
	int i = (int)me->query_skill("yunu-xinjing", 1);   

	if (i == 100)
	{
		 tell_object(me,HIM"玉女心经的奥妙功夫你已经修炼到了第一层了。\n");
	     me->set("xinjing/degree",1);
	}
	if (i == 150)
	{
		tell_object(me,HIM"玉女心经的奥妙功夫你已经修炼到了第二层了。\n");
        me->set("xinjing/degree",2);
	}
	if (i == 200) 
	{
		tell_object(me,HIM"玉女心经的奥妙功夫你已经修炼到了第三层了。\n");
	    me->set("xinjing/degree",3);
	}
	if (i == 250)
	{
		tell_object(me,HIM"玉女心经的奥妙功夫你已经修炼到了第四层了。\n");
	    me->set("xinjing/degree",4);
	}
	if (i == 300)
    {
		tell_object(me,HIM"玉女心经的奥妙功夫你已经修炼到了第五层了。\n");
	     me->set("xinjing/degree",5);
	}
	if (i == 350)
	{
		tell_object(me,HIM"玉女心经的奥妙功夫你已经修炼到了第六层了。\n");
	    me->set("xinjing/degree",6);
	}
	if (i == 400)
	{
		tell_object(me,HIM"玉女心经的奥妙功夫你已经修炼到了第七层了。\n");
	    me->set("xinjing/degree",7);
	}
	if (i == 450)
    {
		tell_object(me,HIM"玉女心经的奥妙功夫你已经修炼到了第八层了。\n");
	     me->set("xinjing/degree",8);
	}
	if (i == 550)
	{
		tell_object(me,HIM"历经千辛万苦，你终于将玉女心经的奥妙功夫修炼到了第九层巅峰状态了。\n");
	    me->set("xinjing/degree",9);
	}
	
	return ;
	
}

string exert_function_file(string func)
{
	return __DIR__"yunu-xinjing/" + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIB + me->name()+"姿态悠雅，神态清冷"NOR,
		"start_my_msg" : "你轻轻的吸一口气，闭上眼睛，运起玉女心经，内息在脉络中开始运转。\n",
		"start_other_msg" : me->name()+"神态突然开始变的清冷无比，可是姿势又变的悠雅异常。\n",
		"halt_msg" : "$N内息一转，迅速收气，停止了内息的运转。\n",
		"end_my_msg" : "你慢慢收气，归入丹田，睁开眼睛，轻轻的吐了一口气。\n",
		"end_other_msg" : "只见"+me->name()+"睁开眼睛，轻轻的吐出了一口气，神态恢复自然。\n"
	]);
}

int hit_ob(object me, object ob, int damage)
{
	object weapon,weap1;
	int i,j,skill;
	string msg;
	if (!me->query("quest/gm/dichuan")) return 0;
	if (!me->query_temp("ynxj/xinjing")) return 0;
	
	skill=me->query_skill("yunu-xinjing",1);
	//damage=skill+me->query_skill("yunu-xinjing",1);
	//damage=damage*2+random(damage);

	if( me->query_int(1) > 40
	 && me->query_dex(1) > 40
	 && me->query_skill_mapped("hand") == "tianluo-diwang"
	 && me->query_skill_mapped("cuff") == "meinu-quanfa"
	 && me->query_skill("hand") > 450
	 && me->query_skill("cuff") > 450
	 && me->query("neili") > 500
	 && me->query("jingli") > 500
	 && me->query("family/family_name") == "古墓派"
	 && me->query("env/玉女心经") == "融合"
	// &&!ob->is_busy()
//	 &&!ob->is_lost()
	 && !random(3))
	{		
         
		if (me->query("quest/jiuyingm/pass") && random(10)>4)
		{            
		  switch (random(5))
		  {
           case 0:
				  //男，若激发parry黯然掌反击，女妩媚busy
			  if (me->query("gender")=="男性")
			  {
				 if (me->query_skill_mapped("parry")=="anran-zhang"&&me->query_skill("anran-zhang",1)>450)
				 {
					 msg=YEL"$N将杨过所传的黯然掌功夫陡然施展出来，神情萧然间，随意拍出一掌。\n"NOR;
					 if (random(me->query_str(1))>ob->query_dex(1)/2)
					 {
						 msg+=HIC"对方没有料想你的招式看似缓慢，但威力却太的很，一不小心被$N一掌打在肩部。\n"NOR;
						 ob->add_busy(2);
					     ob->receive_damage("qi",damage,me);
					     ob->receive_wound("qi",damage/3,me);
					 }
					 else 
					 {
						 msg+=HIC"对方见你的招式太过威猛，猛然间一个懒驴打滚，躲过了你的这招反击。\n"NOR;		
					     me->add_busy(random(1));
					 }
					 message_vision(msg,me,ob);
				 }
			  } else
			  {
				   if (me->query("gender")=="女性")
			       {
				     if (me->query_skill_mapped("strike")=="meinu-quanfa"&&me->query_skill("meinu-quanfa",1)>450)
				     {
					    msg=HIC"$N将小龙女所传的美女拳法功夫陡然施展出来，神情清冷，姿态优雅，巧笑倩然，韵味无穷。\n"NOR;
					    if (random(me->query_dex(1))>ob->query_con(1)/2)
				    	{
						 msg+=HIY"对方为你神采所迷惑，一时间忘记出招，被$N一掌打在后背。\n"NOR;
						 ob->add_busy(1);
					     ob->receive_damage("qi",damage/2,me);
					     ob->receive_wound("qi",damage/4,me);
				    	}
					    else 
					    {
						 msg+=HIC"对方见你的招式太过威猛，猛然间一个懒驴打滚，躲过了你的这招反击。\n"NOR;		
					     me->add_busy(random(1));
					    }
					   message_vision(msg,me,ob);
				     }
			       }

			   }
			   break;
		  case 1:
				  //互博之术，追加一招
                    if (me->query_skill("kongming-quan",1)>450&&me->query("quest/hubo/pass"))
				      {
					    msg=HIR"$N将从老顽童处领悟到的空明拳融合到招式之中，双手互博顺势而出，宛如两个人在同时进攻一样。\n"NOR;
						message_vision(msg,me,ob);
					    COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 3);
					    
						if (ob->query("neili")>2000) ob->add("neili",-random(2000));
					    
					  }
					 break;
		  case 2:
				  //摄魂 。。
		      message_vision(HIM"$N将九阴真经中的功夫运用起来，脸上突然开始做出各样奇怪的表情。\n"NOR, me, ob);

              if ( random(me->query_int()) > ob->query_int()/2) 
              {        	    
                message_vision(HIW"$n看了准备取笑$N，却不知不觉的学起$N的表情。\n"NOR, me, ob);
	     	    message_vision(HIW"$N猛然做出向自己攻击的动作，$n立刻向自己发疯似的攻击起来，出手越来越重！\n"NOR, me, ob);
		        //ob->add_temp("apply/attack",skill/3);
		        ob->add_temp("apply/damage",skill/3);
				ob->add_busy(2);
                ob->set_temp("must_be_hit",1);
                COMBAT_D->do_attack(ob, ob, ob->query_temp("weapon"), 3);
              //  if( me->is_fighting(ob)&& !random(2)) COMBAT_D->do_attack(ob, ob, ob->query_temp("weapon"),random(2)?1:3);
                //if( me->is_fighting(ob)&& !random(4)) COMBAT_D->do_attack(ob, ob, ob->query_temp("weapon"),3);
                if(ob)
                {
					//ob->add_temp("apply/attack",-skill/3);
					ob->add_temp("apply/damage",-skill/3);
					ob->delete_temp("must_be_hit");
				 }
			  }
              else
				   message_vision(HIW"不管$N怎么变化表情，$n总是冷冷的无动于衷。\n"NOR, me, ob); 
				   
		   break;
		  case 3:
				  //九阴抓
		      if (me->query_skill_mapped("claw")=="jiuyin-shenzhua" && me->query_skill("jiuyin-shenzhua",1)>450)
			  {	 
				  message_vision(HIR"$N随手一招九阴伸爪，招式光明正大，但威力巨大，一招抓向$n的面庞。\n"NOR, me, ob);
				  ob->receive_damage("qi",damage,me);
				  ob->receive_wound("qi",damage/2,me);
			  }else if (me->query_skill_mapped("claw")=="jiuyin-baiguzhua"&&me->query_skill("jiuyin-baiguzhua",1)>450)
			  {

				  message_vision(RED"$N阴阴一笑，手指间嗤嗤有声，真是臭名昭著的“九阴白骨抓”！\n"NOR,me,ob);
				  ob->receive_damage("qi",damage/2,me);
				  ob->receive_wound("qi",damage/4,me);
			  }
		     break;
          
		 default: 
			 if (objectp(weap1=present("yufeng zhen", me)))
			 {
				message_vision(HIW"\n$N将武器交左手，右手袖袍一挥，由身上摸出一枚玉蜂针从袖底飞出直向$n急射而去。\n"NOR,me,ob);
				if (random(me->query_dex(1))>ob->query_dex(1)/3)
				{
					message_vision(HIY"$n眼见一道金光向自己飞来，一不小心为玉峰针所伤。\n"NOR,me,ob);
					ob->add_condition("bee_poison",5);
					ob->receive_damage("qi",damage,me);
					ob->receive_wound("qi",damage/3,me);
				}
			 }
			else if (objectp(weap1=present("bingpo yinzhen", me)))
			 {
				message_vision(HIB"\n$N将武器交左手，右手袖袍一挥，由身上摸出一枚冰魄银针从袖底飞出直向$n急射而去。\n"NOR,me,ob);
				if (random(me->query_dex(1))>ob->query_dex(1)/3)
				{
					message_vision(HIY"$n眼见一道银光向自己飞来，一不小心为冰魄银针所伤。\n"NOR,me,ob);
					ob->add_condition("bing_poison",7);
					ob->receive_damage("qi",damage,me);
					ob->receive_wound("qi",damage/2,me);
				}

			}
			else message_vision(HIC"$n冷哼一声，识破了$N的意图，闪开一旁。\n"NOR,me,ob);	 	
			
		   break;
          }    
		}
		
//克制全真教武功 开了花丛的玉女心经

		//if (objectp(weapon=me->query_temp("weapon")))
			//message_vision(HIC"$N将手中的"+weapon->query("name")+HIC"一收，",me);
		//else
			//message_vision(HIC"$N招式随之一变，玉女心经的功夫随心而起。\n",me);
        //道家taosim,和尚，喇嘛，大乘佛法收到压制和克制
		//克制全真剑法
        
		if (ob->query("family/family_name")=="全真教"&&me->query("quest/gumu/ynxj/pass")&&!random(3))
        {
			if (random(me->query("combat_exp")) > ob->query("combat_exp")*2/3 && random(me->query_int())>ob->query_int()/2)
			{
				message_vision("$N已经在运使玉女心经最后一章的武功，$n只觉得自己处处受制，对方每一招似乎都对自己的招式形成克制。\n",me,ob);
				ob->add_temp("lost_attack",3+random(3));
			}
        }

	   else if(ob->query("class") != "bonze"
		 && ob->query("class") != "huanxi" 
		 && !random(3)
		 && ob->query("class") != "taoism"
		 && me->query("gender") != ob->query("gender")){
			message_vision(HIC"施展出古墓派嫡传美女拳法,招式曼妙，招人遐想！\n", me);
			if (random(me->query_per()) > ob->query_per()/2)
			{
				message_vision(HIR"$n心神一乱，险些被$N击中要害，一阵手忙脚乱！\n"NOR, me, ob);
				ob->add_busy(2+random(3));
				me->add("jingli",-50);
				me->add("neili",-100);
			}
			else message_vision(HIC"$n心神一乱，连忙自行镇慑心神！\n"NOR, me, ob);
		}
		else {
			 message_vision(HIC"忽然间施展出古墓派嫡传天罗地网势，双手挥动，形成一片手影！\n", me);
			 if (random(me->query_dex(1)) > ob->query_dex(1)/2
				 &&random(10)>5)
			 {
				message_vision(HIR"$n连连受挫，自顾不暇，无法准确的向$N攻击！\n"NOR, me, ob);
				ob->add_temp("lost_attack",1);
				call_out("remove_lost",4,ob);
				me->add("neili",-50);
				me->add("jingli",-100);
			 }
			 else {
				message_vision(HIC"$n以快打快，瞬间破解了$N的奇袭！\n"NOR, me, ob);
				me->add_busy(1);
			 }
		}
	}
	return 1;
}
int remove_lost(object ob)
{
	if (!ob) return 0;
	ob->delete_temp("lost_attack");
	return 1;
}
/*
mixed ob_hit(object ob, object me, int damage)
{
	    int ap, dp;
        int  lvl,i;
        lvl = me->query_skill("yunu-xinjing", 1);
        if ( lvl < 500
          || me->query("neili") < 2000
		  || random(10)<3 
          || me->query_skill_mapped("force") != "yunu-xinjing")
         	return 0;
        if (!me->query_temp("")) return 0;       
		//if(!me->query("tjg/pass")) return 0;
        if (!me->query("quest/gm/dichuan")) return 0;
		if (!me->query_temp("ynxj/xinjing")) return 0;
	 
        ap = ob->query_skill("force",1);
        dp = me->query_skill("force",1);

        if (random(dp)> ap*2 /3 && random(me->query("neili")) > ob->query("neili")*2/3 )
        {
	        i = -damage;
         

            message_vision(HIC"$N已经将九阴真经和玉女心经彻底融合，内力汹涌，循环不绝！\n"NOR,me,ob);
			message_vision(HIC"$n感觉一股阴柔的内劲传来，绵绵不绝，但却威力不凡！\n"NOR,me,ob);

            ob->receive_damage("qi", damage/2,me);
            ob->receive_wound("qi", damage/4, me);
            return i;                              
         }    
        else if (random(dp)> ap /2 && random(me->query_con(1)) > ob->query_con(1)/2 )
         {
	      i = -damage;        //削减并反弹所有攻击。
          message_vision(HIC"$N玉女心经最后一章的武功施展出来后，真气流转，将$n的攻击抵消少许。\n"NOR,me,ob);
          return i/2;                               
          }     
      
} 
*/