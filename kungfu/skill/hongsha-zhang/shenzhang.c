// hongsha.c
// by sohu@xojh 2015

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return RED"红砂神掌"NOR;}

int perform(object me, object target)
{
  string msg, dodge_skill;
  int damage, p, jiali, skill, neili, neili2;
  

  if( !target ) target = offensive_target(me);

  if( !target || !target->is_character() ||  !me->is_fighting(target) 
      || environment(target)!=environment(me) || !living(target))
         return notify_fail("「红砂神掌」只能在战斗中用。\n");

  if( me->query_temp("weapon")) 
         return notify_fail("你手握武器，如何使得出「红砂神掌」？\n");
         
  if( (skill = (int)me->query_skill("hongsha-zhang", 1)) < 100 )
         return notify_fail("你的红砂掌不够娴熟，不会使「红砂神掌」！\n");

  if( (int)me->query_skill("xuedao-jing", 1) < 100 )
         return notify_fail("你的内功火候不够，不会使用「红砂神掌」！\n");

  if( me->query_skill_mapped("force") != "xuedao-jing")
         return notify_fail("你所用的内功和「红砂神掌」相互冲突！\n");

  if (me->query_skill_prepared("strike") != "hongsha-zhang" ||
      me->query_skill_mapped("strike") != "hongsha-zhang")
         return notify_fail("你必须先将红砂掌运用于掌法之中才行。\n");

  if( (jiali = (int)me->query("jiali")) < 50 )
         return notify_fail("你掌上不带内力，怎么使得出「红砂神掌」来？\n");

  if( (neili = (int)me->query("neili")) < 500 )
         return notify_fail("你的真气不足，不能施展「红砂神掌」！\n");
  if( (int)me->query("max_neili") < 1500 )
         return notify_fail("你的内力不足，不能施展「红砂神掌」！\n");
  if( (int)me->query("jingli") < 300 )
         return notify_fail("你的精力不足，不能施展「红砂神掌」！\n");

  me->receive_damage("neili", random(100) );
  me->receive_damage("jingli", 50);
  
  message_vision(RED "\n$N轻轻纵起，不逃不避，掌影晃动，淫笑几声，对着$n"RED"的双掌推出，\n"NOR,me,target);

  if( random( me->query("combat_exp") ) < target->query("combat_exp")/5) 
  {
         dodge_skill = target->query_skill_mapped("dodge");
         if( !dodge_skill ) dodge_skill = "dodge";
         msg = "掌风带有一股若隐若现的淡红色血腥气息，不可小视！\n"NOR + SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
         message_vision(msg, me, target);
         return 1;
  }
 
  
  msg = HIY"$p仓促间慌忙出手，双掌随即相交！只听“噗噗”的两声轻响！腾起两股淡红色血雾，宛如击在破棉花一般。\n"NOR;
  
  neili = me->query("neili");
  neili2 = target->query("neili");
  
  if( me->query_skill("force",1) < target->query_skill("force",1)/3
     && neili < neili2/3)
 {
         msg += "两掌相触之下，$n立占上风，将$N一下子震了开来！\n";
         damage = target->query_skill("force",1) / 2;
         me->receive_damage("qi", damage,  target);
         me->receive_wound("qi", damage/2, target);
         p = (int)me->query("qi")*100/(int)me->query("max_qi");
         msg += damage_msg(damage, "内伤") + "( $N"+eff_status_msg(p)+" )\n";     
  }
  else if( me->query_skill("force",1) < target->query_skill("force",1)/3*2
         || neili < neili2/3*2)        
         msg += "结果相拼之下，两人都晃了一晃，谁也没有占到好处！\n";
            
  else {
         damage = me->query_skill("xuedao-jing",1) +me->query_skill("hongsha-zhang",1)+ jiali * (5+random(5));
         if(neili > neili2*2) damage *= 2;
         if (userp(target)) damage= damage*2 +random(1000);
         else damage=damage+500+random(1000);
		// if( userp(target)&& damage > 2000) damage = 2000;
         
		 if(damage < 1500) damage = 1500;         
           
         target->add_busy(1+random(2));
         target->receive_damage("qi", damage,  me);
		 
		 if (!userp(target))
		     target->receive_wound("qi", damage/2, me);
		 else target->receive_wound("qi", random(damage/3), me);
		 
		 if (me->query_temp("xdj/yuxue"))
		    target->add_condition("neishang_poison",1);
         p = (int)target->query("qi")*100/(int)target->query("max_qi");
         msg +=HIR+damage_msg(damage, "内伤") +NOR+ "( $n"+eff_status_msg(p)+" )\n"; 
         //if(target->is_killing(me->query("id"))
           // || me->is_fighting(target->query("id")))
         if (me->is_fighting()
			 &&objectp(target)
			 &&me->query_skill("hongsha-zhang",1)>=120)
            	 call_out("perform2", 0, me, target, p, damage);
                 
			//call_out("remove_effect", p, me);
         }
		message_vision(msg, me, target);
		
		me->start_busy(1+random(1));
		me->start_perform(3,"红砂神掌绝技");
		return 1;
}

int perform2(object me, object target, int p, int damage)
{
        string msg, dodge_skill;

        if( !target || !target->is_character() ||  !me->is_fighting(target) 
           || environment(target)!=environment(me) || !living(target))
                return notify_fail("对手已经不能再战斗了。\n");

        if( (int)me->query("neili") < me->query_skill("force")*2 )
                return notify_fail("你待要再发一掌，却发现自己的内力不够了！\n");     

        msg = HIR "\n$N"HIR"心中暗道“早等着你了”，双掌嘿然推出，$n"HIR"欲待再催内力，已然不及，$P的掌力如排山倒海般压到！\n"NOR;        
        if ( me->query("neili") > target->query("neili") / 2 
        || random(me->query_str())>target->query_str()/2  
		|| random( me->query("combat_exp") ) > target->query("combat_exp")/3){
                me->start_busy(1);
                me->receive_damage("neili", me->query_skill("force",1)*3);
                me->receive_damage("jingli", 20);                              
                damage = damage*2;
                if(me->query("neili") > target->query("neili")*2 ) 
                       damage += random(damage);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);

                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg +=RED+ damage_msg(damage, "内伤")+NOR + "( $n"+eff_status_msg(p)+" )\n"; 
        } 
        else 
        {
                me->start_busy(3);
                me->add("neili", -100);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_vision(msg, me, target); 
		me->start_perform(4,"红砂神掌绝技");
        return 1;
}
int help(object me)
{
	write(RED"\n红砂掌之「红砂神掌」："NOR"\n\n");
        write(@HELP
	红砂掌乃是血刀门弟子入门武技，红砂乃是取大雪山
	剧毒之物，以自身鲜血滋养，久而久之，血液中带有
	毒性。同时因为血液中蕴含这些奇物之毒，这红砂掌
	对于血刀门的心法却有滋养之意。
	红砂神掌就是凭借自身红砂掌之毒和对方硬拼，除了
	掌力比拼外，同时让对方中了红砂之毒。端的是险恶
	万分。注意，120级后会有后招变化。
	
	指令：perform strike.hongsha

要求：
	最大内力  1500 以上；
	当前内力  500  以上；
	血刀大法  100  级以上；
	红砂掌法  100  级以上；
HELP
        );
        return 1;
}