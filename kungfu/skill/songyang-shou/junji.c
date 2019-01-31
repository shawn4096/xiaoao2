// junji.c
// by snowman@SJ 13/05/99

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

string perform_name() {return WHT"峻极神掌"NOR;}

int perform(object me, object target)
{
  string msg, dodge_skill;
  int damage, p, jiali, skill, neili, neili2;
  int focus = me->query_temp("ss/focus");

  if( !target ) target = offensive_target(me);

  if( !target || !target->is_character() ||  !me->is_fighting(target) 
      || environment(target)!=environment(me) || !living(target))
         return notify_fail("「峻极神掌」只能在战斗中用。\n");

  if( me->query_temp("weapon")) 
         return notify_fail("你手握武器，如何使得出「峻极神掌」？\n");
         
  if( (skill = (int)me->query_skill("songyang-shou", 1)) < 200 )
         return notify_fail("你的大嵩阳手不够娴熟，不会使「峻极神掌」！\n");

  if( (int)me->query_skill("hanbing-zhenqi", 1) < 200 )
         return notify_fail("你的内功火候不够，不会使用「峻极神掌」！\n");

  if( me->query_skill_mapped("force") != "hanbing-zhenqi")
	  if( me->query_skill_mapped("force") != "lengquan-shengong")
         return notify_fail("你所用的内功和「峻极神掌」相互冲突！\n");

  if (me->query_skill_prepared("hand") != "songyang-shou" ||
      me->query_skill_mapped("hand") != "songyang-shou")
         return notify_fail("你必须先将大嵩阳手运用于手法之中才行。\n");

  if( (jiali = (int)me->query("jiali")) < 50 )
         return notify_fail("你掌上不带内力，怎么使得出「峻极神掌」来？\n");

  if( (neili = (int)me->query("neili")) < 500 )
         return notify_fail("你的真气不足，不能施展「峻极神掌」！\n");
  if( (int)me->query("max_neili") < 1500 )
         return notify_fail("你的内力不足，不能施展「峻极神掌」！\n");
  if( (int)me->query("jingli") < 300 )
         return notify_fail("你的精力不足，不能施展「峻极神掌」！\n");

  me->receive_damage("neili", random(100) );
  me->receive_damage("jingli", 50);
  msg = HIC "\n手腕晃动，只听“啪”的一声响，$N"HIC"抢上前，对着$n"HIC"迅速击出一掌，\n";

  if( random( me->query("combat_exp") ) < target->query("combat_exp")/3) {
         dodge_skill = target->query_skill_mapped("dodge");
         if( !dodge_skill ) dodge_skill = "dodge";
         msg += "掌风凛冽，不可小视！\n"NOR + SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
         message_vision(msg, me, target);
         return 1;
         }
 
  
  msg += HIY"$p慌忙出手，双掌随即相交！\n"NOR;
  neili = me->query("neili")*(focus+1);
  neili2 = target->query("neili");
  
  if( me->query_skill("force",1) < target->query_skill("force",1)/2
     && neili < neili2/2){
         msg += "结果相拼之下，$n立占上风，将$N一下子震了开来！\n";
         damage = target->query_skill("force",1) / 2;
         me->receive_damage("qi", damage,  target);
         me->receive_wound("qi", damage/2, target);
         p = (int)me->query("qi")*100/(int)me->query("max_qi");
         msg += RED+damage_msg(damage, "内伤") +NOR+ "( $N"+eff_status_msg(p)+" )\n";     
         }
  else if( me->query_skill("force",1) < target->query_skill("force",1)/3*2
         || neili < neili2/3*2)        
         msg += "结果相拼之下，两人都晃了一晃，谁也没有占到好处！\n";
            
  else {
         damage = me->query_skill("hanbing-zhenqi",1) +me->query_skill("songyang-shou",1)+ jiali * (5+random(5))*focus;
         if(neili > neili2*2) damage *= 2;
         if (userp(target)) damage= damage +random(1000);
         else damage=damage+500+random(1000);
		// if( userp(target)&& damage > 2000) damage = 2000;
         if(damage < 1500) damage = 1500;         
         if(damage > 3000) damage = 3000;         
         if(!target->is_busy())
                 target->start_busy(1+random(2));
		 if (damage>2000&&userp(target))
         {
					damage=2000+random(1000);
         }
         target->receive_damage("qi", damage,  me);
		 
		 if (!userp(target))
		     target->receive_wound("qi", damage/2, me);
		 else target->receive_wound("qi", damage/4, me);
		 if (me->query_temp("ss/hb")){
			 message_vision(HIB"$N运起寒冰真气，劲力外吐，一股极其阴冷的寒毒立即侵入$n的经脉!\n"NOR,me,target);
		     target->add_condition("cold_poison",1);
		 }
         p = (int)target->query("qi")*100/(int)target->query("max_qi");
         msg += HIW+damage_msg(damage, "内伤")+NOR + "( $n"+eff_status_msg(p)+" )\n"; 
         //if(target->is_killing(me->query("id"))
           // || me->is_fighting(target->query("id")))
         if (me->is_fighting()
			&&objectp(target)
			&&me->query_skill("songyang-shou",1)>120)
            	 call_out("perform2", 0, me, target, p, damage);
                 
         }
		message_vision(msg, me, target);
		me->start_busy(1+random(1));
		me->start_perform(3,"峻极绝技");
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

        msg = WHT "\n$N"WHT"微微一笑，双掌陡然相交，$n"WHT"欲待再催内力，已然不及，$P的掌力如排山倒海般压到！\n"NOR;        
        if ( me->query("neili") > target->query("neili") / 2 
        || random(me->query_str())>target->query_str()/2  
		|| random( me->query("combat_exp") ) > target->query("combat_exp")/3){
                target->start_busy(1);
                me->receive_damage("neili", me->query_skill("force",1));
                me->receive_damage("jingli", 100);                              
                damage = damage*2;
                if(me->query("neili") > target->query("neili")*2 ) 
                       damage += random(damage);
                if (damage>3500) damage=3500;
               
				if (damage>2500&&userp(target))
                {
					damage=2500+random(1000);
                }
				target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/3, me);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += HIW+damage_msg(damage, "内伤") +NOR+ "( $n"+eff_status_msg(p)+" )\n"; 
        } 
        else 
        {
                me->start_busy(3);
                me->add("neili", -200);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
        }
        message_vision(msg, me, target); 
		me->start_perform(3,"峻极绝技");
        return 1;
}
int help(object me)
{
	write(HIW"\n大嵩阳手之「峻极绝技」："NOR"\n\n");
        write(@HELP
	大嵩阳手乃是嵩山弟子入门武技，峻极乃是取嵩山峻
	极峰之意，但这门武功中蕴含的意境去不容小觑。这
	招的特点是依靠自己强大内力以及臂力和对方以掌对
	掌抗衡，所以若功力高深者，运用此招，再辅助以独
	门内劲寒冰真气，则会使得对方防不胜防，当然，若
	比对方功力低，则会为对方内力反震，嵩山弟子需谨
	慎使用。注意，120级后会有后招变化。
	
	指令：perform hand.junji

要求：
	最大内力  1400 以上；
	当前内力  500  以上；
	当前精力  300  以上；
	寒冰真气  200  级以上；
	大嵩阳手  200  级以上；
	激发手法为嵩阳手；
	激发招架为嵩阳手
	激发内功为寒冰真气或阴性内功;
	备手法为嵩阳手；
	空手；
HELP
        );
        return 1;
}