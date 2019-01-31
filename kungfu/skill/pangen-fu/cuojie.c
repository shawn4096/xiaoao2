// pangen-fu ,cuojie 错字诀
#include <ansi.h>
#include <combat.h>

#define CUO "「" HIR "错字诀" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int level,i;
	string msg;

        if (userp(me) && !me->query("quest/tls/pgf/pangen/pass"))
                return notify_fail("你只是听说过此招，但不会使用这种功能。\n");
		level=me->query_skill("pangen-fu",1);
		i=(int)level/200;
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(CUO "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) 
            ||(string)weapon->query("skill_type") != "axe")
                return notify_fail("你使用的武器不对，难以施展" CUO "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        if ( me->query_skill("pangen-fu", 1) < 300)
                return notify_fail("你盘根错节斧不够娴熟，难以施展" CUO "。\n");
		if ( me->query_skill("qiantian-yiyang", 1) < 300)
                return notify_fail("你的乾天一阳不够娴熟，难以施展" CUO "。\n");
        if ((int)me->query_skill("force",1) < 300)
                return notify_fail("你的内功火候不够，难以施展" CUO "。\n");

        if ((int)me->query("max_neili",1) < 3500)
                return notify_fail("你的内力修为不够，难以施展" CUO "。\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("你现在真气不够，难以施展" CUO "。\n");
        if ( me->query_temp("pgf/cuojie"))
                return notify_fail("你正在施展错字诀。\n");
        if( me->query_str() < 50 )
            return notify_fail("你的膂力不够，无法使用「盘根错节」斧法！\n");
        
		if (me->query_skill_mapped("axe") != "pangen-fu"
		   ||me->query_skill_mapped("parry") != "pangen-fu")
                return notify_fail("你没有激发盘根错节斧，难以施展" CUO "。\n");

        if (!living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

		msg = HIR "$N" HIR "高举手中" + weapon->name() + HIR "，陡然一声断喝，朝着$n"
              HIR "猛挥数斧，气势如虹。招招不离$n的关节要害，端得是厉害非常。\n" NOR;
		

        me->add("neili", -100-random(300));
        if (random(level) > (int)target->query_skill("parry", 1) / 2
			||random(me->query("combat_exp"))>target->query("combat_exp")/3
			|| random(me->query_str()) > target->query_dex()/2)
        {
		  msg += HIW "$p" HIW "见$P" HIW "来势汹涌，不得不中途"
                       "变招，这一下登时便失了先机！\n" NOR;
          
		  if (userp(target)) target->add_busy(1);
          else target->add_busy(3);
		  
		  //message_combatd(msg, me, target);
		  me->add_temp("apply/damage",(int)me->query_skill("pangen-fu",1)/6);
		  me->set_temp("pgf/cuojie",1);
		  call_out("check_fight",1,me,target,(int)level/20);
	    } else
        {
		  msg += CYN "可是$p" CYN "看破$P" CYN "招式的来路，斜"
                       "斜跳开，使这招未起到丝毫作用。\n" NOR;
		  
		  me->start_busy(1);
	     }
	     message_combatd(msg, me, target);
        if (me->query_skill("pangen-fu",1)<350)
		   me->start_perform(3,"错字诀");
	   
		
		return 1;
}

void check_fight(object me, object target,int count)
{
       object weapon,wp2;
	   if (!me) return;
	   weapon=me->query_temp("weapon");

	   if (count<0
		 ||!objectp(target)
		 ||!weapon
		 || me->query_skill_mapped("axe") != "pangen-fu"
         || me->query_skill_mapped("parry") != "pangen-fu"
         || me->query_skill_mapped("force") != "qiantian-yiyang"
         || weapon->query("skill_type") != "axe"
		 ||!me->is_fighting())
	   {
			me->add_temp("apply/damage",-(int)me->query_skill("pangen-fu",1)/6);
	   
			me->delete_temp("pgf/cuojie");
			tell_object(me, HIW"你盘根错节斧之「错字诀」施展完毕，缓缓舒了一口气。\n" NOR); 
			return;
	   }
	   //砍断对方兵器

		if (objectp(target))
		{
			wp2=target->query_temp("weapon");
			if (objectp(wp2)
				&& !random(3)
				&& random(me->query_str())>target->query_dex()/2)
			{
				if (weapon->query("sharpness") > wp2->query("rigidity") && wp2->query("imbued") <= 3)			
				{
					message_vision(HIR"$N大喝一声，抡起手中的"+weapon->query("name")+HIR"砍向$n手中的"+wp2->query("name")+HIR"，力大斧锐，顿时断为两截。\n"NOR,me,target);
					wp2->broken("削断的");
				} 
			}


		}
	

       call_out("check_fight", 2,me,target,count -1);
}


string perform_name() {return HIY"错字诀"NOR;}

int help(object me)
{
   write(WHT"\n盘根错节斧法之「"HIY"错字诀"WHT"」："NOR"\n\n");
   write(@HELP
	盘根错节斧乃是大理渔樵耕读四大护卫南山樵子
	古竺诚的独门武技，其斧法虽然招式平凡，但却
	在平凡的招式中蕴藏杀机。斧沉力猛，无论是上
	阵杀敌还是地下单打独斗都甚是威猛。
	
	perform axe.cuojie
   
要求: 
	最大内力 3500 以上；
	当前内力 1000 以上；
	盘根斧法 300  以上；
	基本斧法 300  以上；
	乾天一阳 300  以上；
	后天臂力 50   以上；
	激发斧法为盘根斧法；
	激发招架为盘根斧法;
	装备斧头。

          
HELP
   );
   return 1;
}
