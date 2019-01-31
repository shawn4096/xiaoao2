// feipu.c 百丈飞瀑 
// by sohu@xojh 2014

#include <ansi.h>
#include <combat.h>
#include <weapon.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
       int damage, attp, defp;
        object obj;
        string w_name;
        object weapon,jwq;

        if( !target ) target = offensive_target(me);
		if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「百丈飞瀑」只能对战斗中的对手使用。\n");
        if (!objectp(weapon = me->query_temp("weapon"))
			 || (string)weapon->query("skill_type") != "sword")
                return notify_fail("开什么玩笑，没装备剑就想使「百丈飞瀑」？\n");
       
        if ((int)me->query_skill("liangyi-jian", 1) < 250)
                return notify_fail("你的两仪剑法不够娴熟，无法使出两仪剑绝技之一的「百丈飞瀑」。\n");
        if ((int)me->query_skill("xuantian-wuji", 1) < 250)
                return notify_fail("你的玄天无极功火侯太浅，无法使出「百丈飞瀑」。\n"); 
        if ((int)me->query("neili",1) < 1500)
                return notify_fail("你的内力不够，无法使出两仪剑中「百丈飞瀑」的绝技。\n"); 

//只见白光一闪，嗤的一响，蒋涛反剑掠上，高则成左臂中剑，鲜血冒出。
        
		message_vision( BBLU+HIW "$N聚气于剑，翻身回剑，剑诀斜引，一招「百丈飞瀑」剑锋从半空中直泻下来。\n"NOR, me, target );                
//		message_vision( BBLU+HIW "$N聚气于剑，翻身回剑，剑诀斜引，一招「百丈飞瀑」剑锋从半空中直泻下来。\n"NOR, me, target );                

      
     
        
        message_vision( HIW "$N大喝一声，默运内力，只听“铮”的一声，天地为之一窒，但见银光点点，$N手中\n"
         + "长剑竟被强大的气劲化为无数宛如实质的碎片，如百丈飞瀑般向$n激射而出！\n\n"NOR, me, target );
      
        attp = me->query_skill("xuantian-wuji",1) + me->query_skill("liangyi-jian",1);

        defp = target->query_skill("dodge",1);

        if( random( attp ) > random( defp )/2 
			||random(me->query_skill("dodge"))>target->query_skill("parry")/2
			|| target->is_busy()){
        
               message_vision( RED "$n躲闪不及，已经被飞散的碎片击中，全身血肉飞溅，千疮百孔！\n\n"NOR, me, target );
        
                damage = me->query_skill("liangyi-jian",1) + (int)me->query_skill("xuantian-wuji", 1)*2;
                damage = damage - random( target->query_skill("dodge",1)/3 );
                damage *= 2;
                if (damage>5000) damage = 5000+random(1000);                
               
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/3,me);
                target->add_busy(2 + random(2));
                COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3);
                
                //追加攻击
				if( me->query_skill_mapped("force")=="xuantian-wuji"
					&& random(me->query_dex(1))>target->query_dex()/3) 
				{
				  	message_vision(HBBLU+HIW "$N将玄天无极发挥到极致，右手执剑，左手轻抚"+weapon->query("name")+HBBLU+HIW"剑尖，弯若圆月，然后松开，数道剑气激射而出！\n\n"NOR 
								 +RED"$n缩身急躲，但$N的剑势不到用老，中途变招，剑尖抖动，“嘿！”的一声呼喝，刺入了$n左腿。$n惨叫一声！\n"NOR,me,target);
				//  message_vision( BBLU+HIW "$N将玄天无极发挥到极致，右手执剑，左手轻抚"+jwq->query("name")"以琴为剑，真气激射而出！\n\n"
				//				+ NOR + RED"$n惨叫一声，身上已经被无形剑气穿透！\n"NOR, me, target );
                    damage *= 2;                        
                    target->receive_damage("qi", damage,me);
					target->receive_wound("qi", damage,me);

                    target->add("neili",-damage);
                    if (!userp(target))
						target->add_busy(2 + random(8));
					else target->add_busy(2);
					COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3); 
				}       
        }
        else {

                message_vision( HIY "$p不慌不忙地晃动身形，瞬时间躲过了剑雨。\n" NOR, me, target );
				me->add_busy(2);
        }
   //奖励攻击
        if( (int)me->query_skill("art", 1) >= 200
			&& me->query("quest/kl/lyj/feipu/pass")
			&& me->query_skill_mapped("sword")=="liangyi-jian") {
				
		 message_vision( BBLU+HIW "$N将师门秘授剑意发挥的淋漓尽致！右手执剑，左手轻抚剑尖，弯若圆月，然后松开，数道剑气激射而出。\n"NOR, me, target );    
			  	
			 me->add_temp("apply/sword",me->query_skill("liangyi-jian",1)/4);
			 me->add_temp("apply/damage",me->query_skill("liangyi-jian",1)/5);
			 me->add_temp("apply/attack",me->query_skill("liangyi-jian",1)/3);

              if (objectp(target) && me->is_fighting())
				COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
              if (objectp(target) && me->is_fighting())
				COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(me)?3:1);
			  me->add_temp("apply/sword",-me->query_skill("liangyi-jian",1)/4);
			 me->add_temp("apply/damage",-me->query_skill("liangyi-jian",1)/5);
			 me->add_temp("apply/attack",-me->query_skill("liangyi-jian",1)/3);

        }
        me->add("neili", -300);
/*
        if (weapon->query("imbued") < 3)
        {
			weapon->move(environment(me));
			weapon->set("name", "断掉的"+weapon->query("name"));
			weapon->set("id", "cliped "+weapon->query("id"));
			weapon->unequip();
			weapon->set("value", 0);
			weapon->set("weapon_prop", 0);
			weapon->broken("削断的");
			
        }*/
		
		me->start_perform(3+random(3),"「百丈飞瀑」");      
        return 1;

}

string perform_name() {return HIY"百丈飞瀑"NOR;}

int help(object me)
{
    write(WHT"\n两仪剑法「"HIY"百丈飞瀑"WHT"」："NOR"\n");
    write(@HELP
	两仪剑法乃是昆仑派绝技，当初昆仑三圣何足道以此
	剑法横扫西域诸雄。后来在少林大战中一战成名，凭
	借的就是此剑法。两仪剑乃是正宗的正两仪剑法，剑
	法轻灵迅捷，不以力胜，但却将剑法灵动多变发挥到
	极致。若琴棋书画到达 200级且得到何太冲的指点后
	此招将更上一层楼。注意基本轻功的修炼甚是重要。
		
	指令：perform sword.feipu
	
要求：
	玄天无极等级 250 级以上；
	两仪剑法等级 250 级以上；
	基本剑法等级 250 级以上，
	最大内力要求 2500 以上，
	当前内力要求 1000 以上，
	当前精力要求 1000 以上，
	琴棋书画等级 160 级以上
	激发剑法两仪剑，
	激发招架两仪剑，
	需手持剑类武器。    

HELP
	);
	return 1;
}


