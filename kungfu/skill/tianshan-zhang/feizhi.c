//by caiji@SJ
//出处：天龙八部，第3册，975页1996年11月重印版/三联出版社出版
// By Spiderii@ty 取消call die的效果判断
//by kingso add verify

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
string perform_name(){ return HIC"飞掷"NOR; }
int perform(object me, object target)
{
        object weapon;
        int damage,p;
        string msg,dodge_skill,tmp;;
		weapon = me->query_temp("weapon");
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        ||  !living(target))
                return notify_fail("「飞掷」只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("tianshan-zhang", 1) < 100 )
                return notify_fail("你的天山杖法功力太浅，别做梦了。\n");

        if( (int)me->query_skill("staff", 1) < 100 )
                return notify_fail("你的基本杖法功力太浅，别做梦了。\n");

        if( (int)me->query_skill("huagong-dafa", 1) < 100 )
                return notify_fail("你的内功功力太浅，别做梦了。\n");
                
        if( (int)me->query("max_neili") < 1400 )
                return notify_fail("你的内力太浅，别做梦了。\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不够，别做梦了。\n");
        if( (int)me->query("jingli") < 500 )
                return notify_fail("你的精力不够，别做梦了。\n");

		if ( me->query_temp("tsz/feizhi"))
                return notify_fail("你正在使用「飞掷」！\n");
        
		if (!objectp(weapon) 
			|| weapon->query("skill_type") != "staff"
            || me->query_skill_mapped("staff") != "tianshan-zhang")
                return notify_fail("你使得了「飞掷」么?\n");
                 
       
		
        message_vision(BLU "\n$N大喝一声，紧接着「呼」的一声猛响，$N把手中的"+weapon->query("name")+BLU"掷向$n。\n"NOR,me,target);
		 me->set_temp("tsz/feizhi", 1); 
        if(  random((int)me->query_skill("dodge",1)) >(int)target->query_skill("dodge",1)/2
			|| random((int)me->query("combat_exp"))>(int)target->query("combat_exp")/3)
		{
           //write(HIC"TESET1\n"NOR);
		   damage = 4 * ((int)me->query_skill("tianshan-zhang", 1)+me->query_skill("huagong-dafa", 1));
           damage = damage + random(damage) + 5*me->query("jiali");
		   if (!userp(target)) damage=2*damage;
		 
           me->add("neili", -200);
           me->add("jingli",-100);
           if (!userp(target))
           	   if(damage>4500) damage=4500+random(1000);
		   else if(damage>3000) damage=3000+random(1000);
           
		   message_vision(HIR"$n躲闪不及，被飞来的"+weapon->query("name")+HIR"重重击中！\n"NOR,me,target);
 
		   target->receive_damage("qi", damage,me);
           target->receive_wound("qi", damage/3,me);
           
           //p = (int)target->query("qi")*100/(int)target->query("max_qi");
         //  target->set_temp("last_damage_from", me);
          // msg += damage_msg(damage, "刺伤");
          // msg += "( $n"+eff_status_msg(p)+" )\n";
         //  msg = replace_string( msg, "$l", "胸口" );
       //    msg = replace_string( msg, "$w", weapon->query("name"));
		   
		  // message_vision(msg, me, target);
           
		  // COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

		   
		}   
        else {
			

             // dodge_skill = target->query_skill_mapped("dodge");
              //if( !dodge_skill ) dodge_skill = "dodge";
              //if (stringp(tmp = SKILL_D(dodge_skill)->query_dodge_msg(target, 1)))
		      //msg = tmp;
              me->add("neili", -100);
              me->start_busy(1); 
             // if( weapon->unequip())
              
			  if ( me->query("quest/xx/tsz/laoyue/pass") 
			   && me->query_skill_mapped("dodge")=="zhaixingshu"
			   && me->query("env/天山杖法")=="海底捞月") 
			  {
				message_vision(HIC"$N身子一纵，摘星术绝技发动，将飞出去的"+weapon->query("name")+HIC"接住。\n"NOR,me);
				me->add("neili",-random(150));
				me->add("jingli",-random(100));
		   
		       }//else weapon->move(environment(me));
			  
			  else if( random(me->query("kar"))< 5
              &&(int)target->query_encumbrance() *100 / (int)target->query_max_encumbrance()<85)
			  {
                	weapon->move(target);
                	message_vision(HIY"$n伸手轻轻一接，便把飞来的"+weapon->query("name")+HIY"接在手中！\n"NOR,me,target);
              } 
			  else if(random(me->query("kar"))<1)
			  {
                        
                        message_vision(HIY"$n运内力于掌上，对着飞来的"+weapon->query("name")+HIY"一砍，"+weapon->query("name")+HIY"顿时断为两段！\n"NOR,me,target);
                       // weapon->set("name", "断掉的" + weapon->query("name"));
                        //weapon->set("value", 0);
						//weapon->set("no_get", 1);
                      //  weapon->set("weapon_prop", 0);
						weapon->broken("震断的");
						//weapon->move(environment(me));
               } else weapon->move(environment(me));
                
				
        }
        me->delete_temp("tsz/feizhi"); 
        me->start_perform(3, "「飞掷」");
        return 1;
}

int help(object me)
{
   write(HIC"\n天山杖法「飞掷」："NOR"\n");
   write(@HELP
	天山杖法定位成星宿派初期中期武技，威力不俗
	星宿弟子以此横行江湖，此招为天山杖法中有去
	无回的招数，是以将手中武器灌以内力飞掷向对
	手的招数。
	注意：若跟大师兄请教关于天山杖法的使用海底
	捞月的技巧，将飞出去的杖子收回来。但将消耗
	一定的内力和精力。

	set 天山杖法 海底捞月

	perform staff.feizhi
	
要求：
	最大内力要求 1400 以上；
	当前内力要求 500 以上；
	天山杖法等级 100 以上；
	化功大法等级 100 以上；
	激发杖法为天山杖法；
	激发内功为化功大法；
	激发招架为天山杖法；
	需持杖类武器。

HELP
   );
   return 1;
}

