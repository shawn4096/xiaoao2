// feilong.c 飞龙在天
// by sohu@xojh
#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
  string msg, dodge_skill;
  int damage, p, jiali, skill, neili, neili2;

  if( !target ) target = offensive_target(me);

  if( !target || !target->is_character() ||  !me->is_fighting(target) 
      || environment(target)!=environment(me) || !living(target))
         return notify_fail("「飞龙在天」只能在战斗中用。\n");

  if( me->query_temp("weapon")) 
         return notify_fail("你手握武器，如何使得出「飞龙在天」？\n");
         
  if( me->query_temp("combat_yield") )
         return notify_fail("你不出手，如何使得出「飞龙在天」？\n");

  if( (int)me->query_temp("xlz/feilong") )
         return notify_fail("你刚施展完「飞龙在天」，先调息一下吧！\n");
         
  if( (skill = (int)me->query_skill("xianglong-zhang", 1)) < 400 )
         return notify_fail("你的降龙十八掌不够娴熟，不会使「飞龙在天」！\n");

  if( (int)me->query_skill("huntian-qigong", 1) < 400 )
         return notify_fail("你的混天气功火候不够，不会使用「飞龙在天」！\n");

  if( me->query_skill_mapped("force") != "huntian-qigong")
         return notify_fail("你所用的内功和「飞龙在天」相互冲突！\n");

  if (me->query_skill_prepared("strike") != "xianglong-zhang" ||
      me->query_skill_mapped("strike") != "xianglong-zhang"
      ||me->query_skill_mapped("strike") != "xianglong-zhang")
         return notify_fail("你必须先将降龙十八掌运用于掌法之中才行。\n");

  if( (jiali = (int)me->query("jiali")) < 200 )
         return notify_fail("降龙十八掌招招需要最大加力，怎么使得出「飞龙在天」来？\n");
  if( (int)me->query_dex() < 40 )
         return notify_fail("飞龙在天需要较高的身法，你身法不足40，不能施展「飞龙在天」！\n");
  if( (neili = (int)me->query("neili")) < 3000 )
         return notify_fail("你的真气不足，不能施展「飞龙在天」！\n");
  if( (int)me->query("max_neili") < 5000 )
         return notify_fail("你的内力不足，不能施展「飞龙在天」！\n");
  if( (int)me->query("jingli") < 1500 )
         return notify_fail("你的精力不足，不能施展「飞龙在天」！\n");

  me->start_busy(1+random(2));
  me->receive_damage("neili", 800);
  me->receive_damage("jingli", 100);
  
  message_vision(HBRED"$N身子飞跃而起，在空中头朝下，双掌交互拍出，居高下击，威力奇大。正是降龙掌中「飞龙在天」！\n"NOR,me,target);
  if( random( me->query("combat_exp") ) < target->query("combat_exp")/2&&userp(target)) {
         dodge_skill = target->query_skill_mapped("dodge");
         if( !dodge_skill ) dodge_skill = "dodge";
         msg = HIC"$n感觉$N的掌风异常凛冽，威力奇大，哪里敢小觑！\n" + SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
         message_vision(msg+NOR, me, target);
         return 1;
         }
  
  msg =HIY "$n不知道$N这招的真正奥秘，慌忙出手，双掌随即相交！\n"NOR;
  neili = me->query("neili");
  neili2 = target->query("neili");
  
  if( me->query_skill("force",1) < target->query_skill("force",1)/2
     && neili < neili2/2){
         msg +=HIG "结果双方相拼之下，$n全身功力勃发，利用深厚功力，将$N反震出去！\n";
         damage = target->query_skill("force",1) * 2;
         me->receive_damage("qi", damage, target);
         me->receive_wound("qi", random(damage/2), target);
         p = (int)me->query("qi")*100/(int)me->query("max_qi");
         msg += damage_msg(damage, "内伤") + "( $N"+eff_status_msg(p)+" )\n";     
         }
  else if( me->query_skill("force",1) < target->query_skill("force",1)/3*2
         && neili < neili2/3*2)        
         msg += "结果相拼之下，两人都晃了一晃，谁也没有占到好处！\n";
            
  else {
         damage = me->query_skill("force",1) +me->query_skill("huntian-qigong",1)+ jiali * (3+random(5));
		 damage=damage+me->query_skill("xianglong-zhang",1)+me->query_skill("strike",1);
		 if (me->query("gender")=="男性") damage*=3;		 
         if(neili > neili2*2) damage *= 2;
         if(!userp(me) && damage > 3000) damage = 3000;
         if(damage < 1500) damage = 1500;         
           
         if(!target->is_busy())
                 target->start_busy(1+random(2));
         target->receive_damage("qi", damage,  me);
         target->receive_wound("qi", damage/2, me);
         p = (int)target->query("qi")*100/(int)target->query("max_qi");
         msg += damage_msg(damage, "内伤") + "( $n"+eff_status_msg(p)+" )\n"; 
         if(target->is_killing(me->query("id"))
            || me->is_killing(target->query("id")))
                 call_out("perform2", 0, me, target, p, damage);
                 
         p = 30 - skill/10;
         if(p < 7) p = 7;
         call_out("remove_effect", p, me);
         }
         message_vision(msg, me, target);

  return 1;
}

int perform2(object me, object target, int p, int damage)
{
        string msg, dodge_skill;

        if( !target || !target->is_character() ||  !me->is_fighting(target) 
           || environment(target)!=environment(me) || !living(target))
                return notify_fail("对手已经不能再战斗了。\n");

        if( (int)me->query("neili") < me->query_skill("force",1) )
                return notify_fail("你待要再发一掌，却发现自己的内力不够了！\n");     

        msg = HIY "\n$n"HIY"没有意识到$N这招的真正威力，欲待再催内力，已然不及，$N"HIY"的掌力如排山倒海般压到！\n"NOR;        
        if ( me->query("neili") > target->query("neili") / 2 
          || random( me->query("combat_exp") ) > target->query("combat_exp")/3){
                //me->start_busy(2);
                me->receive_damage("neili", me->query_skill("force")*2);
                me->receive_damage("jingli", 20);                              
                damage = damage*2;
                if(me->query("neili") > target->query("neili")*2 ) 
                       damage += random(damage);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
				target->apply_condition("no_force",1+random(1));
				if (damage<target->query("neili"))
					target->receive_damage("neili",damage);
				else target->receive_damage("neili",target->query("neili")-100);
				message_vision(HIB"受到这股巨大的力量震动，$n感觉周身四肢百骸仿佛欲散架似的，一口浊气憋在胸口。\n"NOR,me,target);
				target->add_busy(1);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += damage_msg(damage, "内伤") + "( $n"+eff_status_msg(p)+" )\n"; 
        } 
        else 
        {
                me->start_busy(3);
                me->add("neili", -200);
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                msg += HIW+SKILL_D(dodge_skill)->query_dodge_msg(target, 1)+NOR;
        }
        message_vision(msg, me, target); 
        me->start_perform(4,"「飞龙在天」");
        return 1;
}

void remove_effect(object me)
{
        if (!me) return;
        me->delete_temp("xlz/feilong");
        if(living(me))
            tell_object(me, "\n你内力翻涌，稍待平息一段时间后可以使用「飞龙在天」了。\n"); 
}
string perform_name(){ return HBRED+HIW"飞龙在天"NOR; }
int help(object me)
{
        write(HBRED"\n降龙十八掌法之「飞龙在天」："NOR"\n\n");
        write(@HELP 
	降龙十八掌乃是武林第一大帮丐帮的镇派两大绝技之一，讲究刚柔并济，当刚则刚，
	当柔则柔，轻重刚柔随心所欲，刚劲柔劲混而为一，劲力忽强忽弱，忽吞忽吐，从
	至刚之中生出至柔，天下阳刚第一，掌法之妙，天下无双，招招须用真力，说是外
	门武学中的巅峰绝诣，动作虽似简单无奇，但掌掌现神龙，招招威力无穷，招式简
	明而劲力精深的武功，精要之处，全在运劲发力，全凭劲强力猛取胜，当真是无坚
	不摧、无固不破，虽招数有限，但每出一掌均有龙吟虎啸之势、每出一招均具绝大
	的威力。
	降龙十八掌必须得到帮主的传授方可习得，而「飞龙在天」乃是降龙掌最终绝技之
	一，非深厚内力不得施展。
	
	指令：perform strike.feilong

要求：	
	最大内力 5000 以上；
	当前内力 3000 以上；
	当前精力 1500 以上；
	降龙掌等级 400 以上；
	混天气功等级 400 以上；
	需要加力不少于 200；
	有效身法 40 以上：
	激发掌法降龙掌；
	激发内功为混天气功；
	激发招架为降龙掌。
HELP
        );
        return 1;
}
