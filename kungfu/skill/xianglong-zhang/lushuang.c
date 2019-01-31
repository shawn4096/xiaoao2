// lushuang.c 履霜冰至
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
         return notify_fail("「履霜冰至」只能在战斗中用。\n");

  if( me->query_temp("weapon")) 
         return notify_fail("你手握武器，如何使得出「履霜冰至」？\n");
         
  if( me->query_temp("combat_yield") )
         return notify_fail("你不出手，如何使得出「履霜冰至」？\n");
  if( !me->query("quest/gb/xlz/slbw/pass") )
         return notify_fail("你尚未得到洪七功传授此招，如何使得出「履霜冰至」？\n");
  if( (int)me->query_temp("xlz/lushuang") )
         return notify_fail("你刚施展完「履霜冰至」，先调息一下吧！\n");
         
  if( (skill = (int)me->query_skill("xianglong-zhang", 1)) < 450 )
         return notify_fail("你的降龙十八掌不够娴熟，不会使「履霜冰至」！\n");

  if( (int)me->query_skill("huntian-qigong", 1) < 450 )
         return notify_fail("你的混天气功火候不够，不会使用「履霜冰至」！\n");

  if( me->query_skill_mapped("force") != "huntian-qigong")
         return notify_fail("你所用的内功和「履霜冰至」相互冲突！\n");

  if (me->query_skill_prepared("strike") != "xianglong-zhang" ||
      me->query_skill_mapped("strike") != "xianglong-zhang"
      ||me->query_skill_mapped("strike") != "xianglong-zhang")
         return notify_fail("你必须先将降龙十八掌运用于掌法之中才行。\n");

  if( (jiali = (int)me->query("jiali")) < 200 )
         return notify_fail("降龙十八掌招招需要最大加力，怎么使得出「履霜冰至」来？\n");
  if( (int)me->query_str() < 60 )
         return notify_fail("履霜冰至需要较高的臂力，你臂力不足60，不能施展「履霜冰至」！\n");
  if( (neili = (int)me->query("neili")) < 3000 )
         return notify_fail("你的真气不足，不能施展「履霜冰至」！\n");
  if( (int)me->query("max_neili") < 8000 )
         return notify_fail("你的内力不足，不能施展「履霜冰至」！\n");
  if( (int)me->query("jingli") < 1500 )
         return notify_fail("你的精力不足，不能施展「履霜冰至」！\n");

  me->set_temp("xlz/lushuang",5);
  me->receive_damage("neili", 1200);
  me->receive_damage("jingli", 200);
 // me->start_perform(2,"履霜冰至");
  message_vision(HBBLU+HIW"$N深吸一口气，两肘往上微抬，右拳左掌，直击横推，将掌力一快一慢的打将出去！\n"NOR,me,target);
  message_vision(HBBLU+HIW"$N这一招之中刚柔并济，正反相成，实是妙用无穷。正是降龙掌绝技「履霜冰至」！\n"NOR,me,target);
  if( random( me->query("combat_exp") ) < target->query("combat_exp")/2 && userp(target)) {
         dodge_skill = target->query_skill_mapped("dodge");
         if( !dodge_skill ) dodge_skill = "dodge";
         msg = HIW"$n感觉$N的这招异常奥妙，宛如一个大的旋转漩涡，带动自己站立不稳，心中吃惊，哪里敢小觑！\n" + SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
         message_vision(msg+NOR, me, target);         
         }
  
  msg =HIB "$n感觉$N的这招精深奥妙，左右掌拉扯之间，自己宛如陷入一个漩涡中，掌力的阴劲带动自己站立不稳！\n"NOR;
  neili = me->query("neili");
  neili2 = target->query("neili");
  if (me->query_skill("jiuyin-zhengong",1)>450)
  {
     message_vision(HIR"$N勤练"HIW"九阴真功"HIR"，此时功力已达高深之境，掌力忽阴忽阳，闪烁不定.\n"NOR);
	 //skill=skill+me->query_skill("jiuyin-zhengong",1)/4;
  }
  target->add_busy(2+random(2));
//双方对比优劣势

  if( me->query_skill("force",1) < target->query_skill("force",1)/2
     && neili < neili2/2){
         msg +=HIG "结果双方相拼之下，$n全身功利勃发，利用深厚功力，将$N反震出去！\n";
         damage = target->query_skill("force",1) * 2;
         me->receive_damage("qi", damage, target);
         me->receive_wound("qi",damage/2, target);
         p = (int)me->query("qi")*100/(int)me->query("max_qi");
         msg += damage_msg(damage, "内伤") + "( $N"+eff_status_msg(p)+" )\n";     
         }
  else if( me->query_skill("force",1) < target->query_skill("force",1)/3*2
         && neili < neili2/3*2)        
         msg +=HIC "结果相拼之下，两人都晃了一晃，谁也没有占到好处！\n"NOR;
            
  else {
         msg+=HIY"$n只觉自己跌跌撞撞，不能自己，尽管自己奋力挣扎，但脚下毫不着力，绵软无比。\n"NOR;
		 damage =me->query_skill("xianglong-zhang",1) + me->query_skill("force",1) +me->query_skill("huntian-qigong",1)+ jiali * (3+random(5));
		 damage=damage+random(damage);
		 if (me->query("gender")=="男性") damage*=3;		 
         if(neili > neili2*2) damage *= 2;
         if(userp(me)&& damage > 4000) damage = 4000;
         if(damage < 1000) damage = 1000;         
           
         if(random(3)) {
          target->apply_condition("no_fight",1);
		 //target->set_temp("no_fight",1);
		 }
         target->receive_damage("qi", damage,  me);
         target->receive_wound("qi", damage/3, me);
         //p = (int)target->query("qi")*100/(int)target->query("max_qi");
         msg += damage_msg(damage, "内伤") + "( $n"+eff_status_msg(p)+" )\n"; 
         if(objectp(target)&&me->is_fighting())
            call_out("perform2", 0, me, target, p, damage);
         else call_out("remove_effect", 3, me);		 
		 
		        
         //p = 5;
         //if(p < 7) p = 7;
         //call_out("remove_effect", p, me);
   }
         message_vision(msg, me, target);
		 
		 message_vision(HIY"$N的这股降龙掌力闪烁不定，由"HIW"柔"NOR"转"HIR"刚"HIY"，$n有些根本无法适应这掌力的变化多端，只能被动挨打!\n"NOR,me,target);
		 me->add_temp("apply/attack",(int)me->query_skill("xianglong-zhang",1)/3);
		 me->add_temp("apply/damage",(int)me->query_skill("xianglong-zhang",1)/5);

		 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

		 me->add_temp("apply/attack",-(int)me->query_skill("xianglong-zhang",1)/3);
		 me->add_temp("apply/damage",-(int)me->query_skill("xianglong-zhang",1)/5);
		 call_out("remove_effect",4,me);
		 me->start_perform(4,"履霜冰至");
         return 1;
}

int perform2(object me, object target, int p, int damage)
{
        string msg, dodge_skill;
		int skill;
		skill=me->query_skill("xianglong-zhang",1);

        if( !target || !target->is_character() ||  !me->is_fighting(target) 
           || environment(target)!=environment(me) || !living(target))
                return notify_fail("对手已经不能再战斗了。\n");

        if( (int)me->query("neili") < me->query_skill("force",1) )
                return notify_fail("你待要再发一掌，却发现自己的内力不够了！\n");     

        msg = HBRED+HIY"\n$n"HBRED+HIY"正在身形跌跌撞撞之间，$N"HIY"的掌力忽然化作一股刚猛的阳刚之力，降龙十八掌本是纯阳至刚一路，\n"+
			"但刚到极处，自然而然的刚中有柔！柔中带刚。\n"NOR;        
       if ( me->query("neili") > target->query("neili") / 2 
          || random( me->query("combat_exp") ) > target->query("combat_exp")/3){
                //me->start_busy(2);
                me->receive_damage("neili", me->query_skill("force")*2);
                me->receive_damage("jingli", 20);                              
                if (me->query("gender")=="男性")
                damage = damage*2;
				
                if(me->query("neili") > target->query("neili")*2 ) 
                       damage += random(damage);
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
				target->apply_condition("no_force",1+random(1));
				target->apply_condition("no_perform",1+random(1));
				if (damage<target->query("neili"))
					target->add("neili",-damage);
				else target->receive_damage("neili",target->query("neili")-100);
				message_vision(HIB"。\n"NOR,me,target);
				//target->add_busy(1);
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
		 me->add_temp("apply/damage",skill/4);
		 me->add_temp("apply/attack",skill/3);
		 me->add_temp("apply/strike",skill/4);
		 if (objectp(target)&&me->is_fighting())
		 {
		
			message_vision(HBYEL+HIR"$N一掌接一掌的发出，此时$N的降龙掌已然融会贯通，招式再无半点晦涩，降龙掌的大威力至此方显！\n"NOR,me,target);
			target->set_temp("must_be_hit",1);

			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			target->delete_temp("must_be_hit");
		 
			me->add_temp("apply/damage",-skill/4);
			me->add_temp("apply/attack",-skill/3);
			me->add_temp("apply/strike",-skill/4);
		}
		me->start_perform(4,"履霜冰至");
		call_out("remove_effect",4,me);
        return 1;
}

void remove_effect(object me)
{
        if (!me) return;
        me->delete_temp("xlz/lushuang");
        if(living(me))
            tell_object(me, "\n你将劲气缓缓回收，又可以使用「履霜冰至」绝技了。\n"); 
}
string perform_name(){ return HBRED+CYN"履霜"+HIW"冰至"NOR; }
int help(object me)
{
        write(HBBLU+HIW"\n降龙十八掌法之「履霜冰至」："NOR"\n\n");
        write(@HELP 
	降龙十八掌乃是武林第一大帮丐帮的镇派两大绝技之一，讲究刚柔并
	济，当刚则刚，当柔则柔，轻重刚柔随心所欲，刚劲柔劲混而为一，
	劲力忽强忽弱，忽吞忽吐，从至刚之中生出至柔，天下阳刚第一，掌
	法之妙，天下无双，招招须用真力，说是外门武学中的巅峰绝诣，动
	作虽似简单无奇，但掌掌现神龙，招招威力无穷，招式简明而劲力精
	深的武功，精要之处，全在运劲发力，全凭劲强力猛取胜，当真是无
	坚不摧、无固不破，虽招数有限，但每出一掌均有龙吟虎啸之势、每
	出一招均具绝大的威力。
	降龙十八掌必须得到帮主的传授方可习得，而「履霜冰至」乃是降龙
	掌最终绝技之一，非深厚内力不得施展。乃洪七公当日在宝应刘氏宗
	祠中所传，一招之中刚柔并济，正反相成，实是妙用无穷。需要向洪
	七功请教。
	
	指令：perform strike.lushuang

要求：	
	最大内力 8000 以上；
	当前内力 3000 以上；
	当前精力 1500 以上；
	降龙掌等级 450 以上；
	混天气功等级 450 以上；
	需要加力不少于 200；
	有效臂力 60 以上：
	激发掌法降龙掌；
	激发内功为混天气功；
	激发招架为降龙掌。
HELP
        );
        return 1;
}
