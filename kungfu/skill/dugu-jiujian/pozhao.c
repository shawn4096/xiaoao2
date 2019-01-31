// By Spiderii 合并那些乱七八糟的pobian.posuo等等。。。

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HIG"破招"NOR; }

int perform(object me, object target)
{
        string msg, *skillname, *skilltype = ({});
        object weapon,weapon1;
	    mapping skills;
		int i,damage;
        int skill = me->query_skill("dugu-jiujian",1);
        
        if( !target ) target = offensive_target(me);
		
		//weapon=me->query_temp("weapon");
        weapon1=target->query_temp("weapon");
        
		if( !objectp(target)
        ||  !target->is_character()
		||  !living(target)
        ||  !me->is_fighting(target) )
                return notify_fail("「破招」只能对战斗中的对手使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
            || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if (skill < 400 )
                return notify_fail("你的独孤九剑还不够火候。\n");
        if ( me->query_skill("sword",1)< 400 )
                return notify_fail("你的基本剑法还不够火候。\n");
        if (me->query_skill_mapped("sword") != "dugu-jiujian" )
                return notify_fail("你现在无法使用「破招」！\n");


        if ((string)me->query_skill_mapped("parry") != "dugu-jiujian" 
            && userp(me))
                return notify_fail("你现在无法使用「破招」！\n");


	   // if(target->query_temp("dgjj/pozhao"))
				//return notify_fail("对手已经被你的破招给克制住了。\n");
        //if(me->query_skill("strike",1)<450||me->query_skill("cuff",1)<450)
				//return notify_fail("你的基本掌法和拳法太低，无法使用独孤九剑之破招。\n");
        if((int)me->query("jingli") < 2000)
                return notify_fail("你的精力不够！\n"); 
        if((int)me->query("neili") < 2000)
                return notify_fail("你的内力不够！\n"); 
        message_vision(HIC"\n$N胸藏剑意，随意挥洒而出，招招锁定$n招式中的破绽所在，显是独孤九剑已达到收发自如的境界！\n"NOR,me,target);
		message_vision(HBYEL+HIR"\n$N这招正是独孤九剑的「破招式」！\n"NOR,me,target);
        me->add("jingli", -1000);
        me->start_perform(3,"「破招」");
       if ( random(me->query_int(1)) >= target->query_int(1)/2
			|| random(me->query("combat_exp")) > target->query("combat_exp")/2 )
	   {
		   

           message_vision(HIG"\n$n但觉$N一剑攻出，时若游龙穿空，时若惊鸿渡云。心慌意乱之间，只觉周身武功竟发挥不出平时一半！\n"NOR,me,target);

           //weapon1 = target->query_temp("weapon");
		   //若有武器
          if (weapon1) {
               switch((string)weapon->query("skill_type"))
               {
                  case("sword")    : skilltype += ({"apply/sword"}); 
                                     break;
                  case("blade")    : skilltype += ({"apply/blade"}); 
                                     break;
                  case("axe")      : skilltype += ({"apply/axe"}); 
                                     break;
                  case("brush")    : skilltype += ({"apply/brush"}); 
                                     break;
                  case("club")     : skilltype += ({"apply/club"}); 
                                     break;
                  case("hammer")   : skilltype += ({"apply/hammer"}); 
                                     break;
                  case("dagger")   : skilltype += ({"apply/dagger"}); 
                                     break;
                  case("spear")    : skilltype += ({"apply/spear"}); 
                                     break;
                  case("hook")     : skilltype += ({"apply/hook"}); 
                                     break;
                  case("stick")    : skilltype += ({"apply/stick"}); 
                                     break;
                  case("staff")    : skilltype += ({"apply/staff"}); 
                                     break;
                  case("whip")     : skilltype += ({"apply/whip"}); 
                                     break;
                  case("throwing") : skilltype += ({"apply/throwing"}); 
                                     break;
							
			   }
				//如果有武器，有概率打掉对方的武器
				message_vision(HIY"$N独孤九剑已经融会贯通，剑气弥漫，$n一不小心，为$N刺中手腕“关元穴”，手中的"+weapon1->query("name")+HIY"掉落地上。\n"NOR,me,target);
				weapon1->move(environment(target));
				target->add_busy(1+random(2));
			
            }
			else {
                  skills = target->query_skill_prepare();
                  if ( skills ) {
                       skillname = keys(skills);
                       foreach (string item in skillname) {
                          if (!target->query_skill(item))
                                  continue;
                          switch(item) { 
                              case("cuff")   : skilltype += ({"apply/cuff"}); 
                                               break;
                              case("strike") : skilltype += ({"apply/strike"}); 
                                               break;
                              case("finger") : skilltype += ({"apply/finger"}); 
                                               break;
                              case("hand")   : skilltype += ({"apply/hand"}); 
                                               break;
                              case("leg")    : skilltype += ({"apply/leg"}); 
                                               break;
                              case("claw")   : skilltype += ({"apply/claw"}); 
                                               break;
                          }
                          i++;
                    }
				  //空手则刺血，busy
				  if (objectp(target))
				  {
					 target->set_temp("faint_by",me);//增加一个标记，避免莫名其妙死亡 by renlai
					 //target->set_temp("last_damage_from", "被"+me->query("name")+"所使独孤九剑绝技击杀");
					message_vision(HIR"$N独孤九剑精妙无比，$n双手忽觉一阵剧痛，顿时为"+weapon->query("name")+HIR"所刺中，献血直流。\n"NOR,me,target);
					damage=me->query_skill("sword",1)+me->query_skill("dugu-jiujian",1)+me->query_skill("force",1);
					if (!userp(target)){
						damage=damage*4;
						damage=damage+random(damage);
					}
					else
						damage=damage*3+random(damage);
					target->receive_damage("qi",damage,me);
					target->receive_wound("qi",damage/2,me);
					target->add_busy(1+random(2));
				   }

               }
				
            
            }
			
			if (!target->query_temp("dgjj/pozhao"))
			{		
		//若是没激发，则采纳unarmed
				if (sizeof(skilltype) == 0) skilltype += ({"apply/unarmed"});
		//虚弱对方招式和基本参数
				for (i=0; i < sizeof(skilltype); i++)
					target->add_temp(skilltype[i],-skill);
				message_vision(RED"\n$N独孤九剑攻其所必救，$n只觉自己周身防御被这「"HIG"破招式"RED"」所破，防御大为降低！\n"NOR,me,target);
				
				//target->add_temp("apply/attack",-skill/2);
				//target->add_temp("apply/damage",-skill/2);
				target->add_temp("apply/dodge",-skill/3);
				target->add_temp("apply/parry",-skill/3);
				target->add_temp("apply/defense",-skill/3);
				target->add_temp("apply/dexerity",-skill/10);
				target->apply_condition("no_perform", 2+random(2));
				target->set_temp("dgjj/pozhao",skill);
				target->delete("jiali");			
				call_out("remove_effect", (int)skill/60, target, (int)skill/30, skilltype);
		   }
        } else {
            message_vision(HIG"\n$n突觉$N剑法一滞，招式无法连贯，感觉周身为独孤九剑所造成的压力顿时减轻。\n"NOR,me,target);
			me->add_busy(2);

        }
        //message_vision(msg,me,target);
		//随后连续进攻四招
		me->set_temp("dgjj/pozhao",1);
	    if ( me->is_fighting(target))
		        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if ( me->is_fighting(target))
		        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if ( me->is_fighting(target))
		        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		if ( me->is_fighting(target))
		        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->delete_temp("dgjj/pozhao");

		me->add_busy(2+random(1));
		me->start_peform(4,"破招");
        return 1;
}

void remove_effect(object target, int count, string *skilltype)
{
        int i,skill;
        if (!objectp(target)) return;
		
		skill=target->query_temp("dgjj/pozhao");
			target->add_temp("apply/dodge",skill/3);
			target->add_temp("apply/parry",skill/3);
			target->add_temp("apply/defense",skill/3);
			target->add_temp("apply/dexerity",skill/10);
			target->delete_temp("dgjj/pozhao");
			
        for (i=0; i < sizeof(skilltype); i++)      
              target->add_temp(skilltype[i],skill);
	    
		message_vision(HIW"\n$N内功运转不绝，功力一震，感觉自己的为独孤九剑克制的武功逐渐开始恢复正常了。\n"NOR, target);
		return;
}

int help(object me)
{
	write(HIG"\n独孤九剑「破招」："NOR"\n");
	write(@HELP
	独孤九剑招招进攻，无需防守，其中关键就是快捷
	和料敌机先，招招制敌。当然这其中运独孤九剑剑
	意非常重要，破敌之招数，以无招胜有招。独孤九
	剑号称破解天下武技，破招后，会随机攻击对方数
	招。乃当世绝技。
	
	指令：perform sword.pozhao

要求：
	激发独孤九剑为剑法；
	激发独孤九剑为招架；
	独孤九剑等级 400 以上；
	基本剑法等级 400 以上；
	最大精力不小于 2000；
	当前内力不小于 2000；
	在战斗中持剑使用。
HELP
        );	
        return 1;
}
