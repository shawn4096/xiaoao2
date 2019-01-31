
// pfm luda
// 断别人兵器 & 化学效果
// create by olives@SJ
// 更新 再加一hit物理攻击取消性别限制--by daidai
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include <combat_msg.h>

string perform_name(){ return HIG"鲁达拔柳"NOR; }

int perform2(object me,object target);
int perform(object me, object target)
{
        int skill,ap,pp,damage,effect,p;
        object weapon = me->query_temp("weapon");
		object vweapon;
        string dodge_skill;
        if( !target ) target = offensive_target(me);

        if(!target
        || !target->is_character()
        || !me->is_fighting(target) )
                return notify_fail("你只能对战斗中的对手使用。\n");

		vweapon = target->query_temp("weapon");

        if(userp(me) && me->query("family/master_id")!="hong antong")
                return notify_fail("「鲁达拔柳」只有拜了教主后才能用！\n");

        if( (int)me->query_skill("canglang-goufa", 1) < 250 )
                return notify_fail("你的沧浪钩法不够娴熟，不会使用鲁达拔柳。\n");
		if( (int)me->query_skill("hook", 1) < 250 )
                return notify_fail("你的基本钩法不够娴熟，不会使用鲁达拔柳。\n");
		if( (int)me->query_skill("dulong-dafa", 1) < 250 )
                return notify_fail("你的毒龙大法不够娴熟，不会使用鲁达拔柳。\n");
    	if( (int)me->query("neili", 1) < 3000 )
       			return notify_fail("你现在内力不足！\n");
       	if( (int)me->query("jingli", 1) < 500 )
       			return notify_fail("你现在精力不足！\n");

    	if( (int)me->query("max_neili", 1) < 1500 )
       			return notify_fail("你内力修为不足！\n");
        if( (int)me->query_str() < 30  )
                return notify_fail("你的膂力太低，不能使用鲁达拔柳。\n");

        if(!weapon || weapon->query("skill_type")!="hook" )
                return notify_fail("你现在无法使用鲁达拔柳。\n");
        if(weapon->query("sharpness")<3)
        		return notify_fail("你手中钩子不够锋利，无法使用鲁达拔柳！\n");
		
		if (me->query_skill_mapped("hook") != "canglang-goufa"
		  ||me->query_skill_mapped("parry") != "canglang-goufa")
                return notify_fail("你所使用的武技不对，现在无法使用狄青降龙。\n");
		if (me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("你激发内功不对，现在无法使用狄青降龙。\n");

		skill = (int)me->query_skill("canglang-goufa", 1);
	    ap = me->query("combat_exp")/1000*me->query_str();
        pp = target->query("combat_exp")/1000*target->query_dex();
        
		if(me->query("gender")!="男性")
				return notify_fail("你不是男子，如何使用鲁达拔柳？\n");

			
		skill+= (int)me->query_skill("dulong-dafa", 1);  

	
        me->add("neili", -350);
        me->add("jingli", -200);
        if(objectp(vweapon))       
        {
		    ap *= weapon->query("sharpness");
	        pp *= vweapon->query("rigidity");

 		    message_vision(HIY"\n$N双腿一缩，似欲跪拜，右臂却横掠而出，"+weapon->query("name")+HIY"急削向$n手中"+vweapon->query("name")+HIY"！"NOR,me,target);
  			if(random(ap+pp)>pp  )
  			{

  				message_vision(WHT"\n结果$n手中"+vweapon->query("name")+WHT"应手而断！\n"NOR,me,target);
				vweapon->unequip();
				vweapon->move(environment(target));
				vweapon->set("name", "断掉的" + vweapon->query("name"));
				vweapon->set("value", 49);
				vweapon->set("weapon_prop", 0);
				target->reset_action();
			}
			else message_vision(CYN"\n结果$n向后一缩，躲过了$N这一削！\n"NOR,me,target);
 	   } else if((int)me->query_skill("canglang-goufa", 1)>350) 
	   { 
		    message_vision(HIY"\n$N双腿一缩，似欲跪拜，右臂却横掠而出，手中"+weapon->query("name")+HIY"急削向$n！"NOR,me,target);
            me->add_temp("apply/attack", me->query_skill("canglang-goufa", 1)/2); 
			me->add_temp("apply/damage", me->query_skill("canglang-goufa", 1)/5); 
            COMBAT_D->do_attack(me,target,weapon,3);
            me->add_temp("apply/attack", -me->query_skill("canglang-goufa", 1)/2); 
			me->add_temp("apply/damage", -me->query_skill("canglang-goufa", 1)/5); 
        }	
		message_vision( HIY"\n$N突然一个前滚翻，似欲向$n胯下钻过，但只一作势，左手抓向$n右脚足踝，右手"+weapon->query("name")+HIY"点向$n小腹！\n"NOR, me, target);
	    ap = (int)me->query_skill("dulong-dafa",1) * (int)me->query("neili") * (int)me->query_str()/1000;
        pp = (int)target->query_skill("force", 1) * (int)target->query("neili") * (int)target->query_dex()/1000;
        ap *= (int)me->query("combat_exp")/1000;
        pp *= (int)target->query("combat_exp")/1000;
        ap /= 1000;
        pp /= 1000;
	    if(!living(target)) pp = 1;
		if (me->query("gender")=="男性")
		   ap=ap*2;
       if(random(ap+pp) > pp/2){
                me->start_perform(4, "「鲁达拔柳」");
                if (!userp(target))
                   target->add_busy(2);
                damage =  me->query_skill("force",1)*2;
                damage += me->query("jiali") * 10;
                damage -= target->query_temp("apply/armor") * 2;
                effect = SKILL_D("dulong-dafa")->force_effect(target->query_skill_mapped("force"));
                damage *= (5-effect);
                if (damage < 0) damage = 0;
                damage = damage + random(damage);
                //if (!userp(me)&&damage > 5000) damage = 5000 + (damage-5000)/100;
				if (userp(target)&&damage > 5000) damage = 5000 + (damage-5000)/100;

              //  if(me->query("gender")!="男性")
                //   damage = damage/3; 
 // 非男性威力小   
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/4, me);
                target->add("neili",-random(2000));
                me->add("neili", -random(1000));
                if(damage >= 5000)
                        message_vision(HBYEL"这一招乃是使上了全力，丝毫不留余地，$n的生死存亡，便决于这顷刻之间！\n"NOR, me, target);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                //message_vision( damage_msg(damage, "刺伤"), me, target);
                message_vision("结果只听见$n一声惨嚎，"+weapon->name()+"已在$p的小腹对穿而出，鲜血溅得满地！！\n"NOR, me, target);
                message_vision( "( $n"+eff_status_msg(p)+" )\n", me, target);
             //   msg= replace_string( msg, "$l", "小腹");
                // msg= replace_string( msg, "$w", weapon->name());
                if(me->query_skill("canglang-goufa", 1)>450 && objectp(target) && me->is_fighting())
				{ 
					message_vision( HIY"\n$N一击命中，"+weapon->query("name")+HIY"一收乘势而前，又向$n连攻数招！"NOR, me, target); 
					perform2(me, target);  
				}
        }
       else {
               // me->start_perform(2, "「鲁达拔柳」");
                dodge_skill = target->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                message_vision( SKILL_D(dodge_skill)->query_dodge_msg(target, 1), me, target);
                message_vision( HIY"\n$N一击不中，"+weapon->name()+HIY"一收滚地而前，向$n连攻数招！"NOR, me, target); 
                perform2(me, target); 
          }         
		       me->add("neili", -400);
               me->add("jingli", -100);
			   me->start_perform(3,"「鲁达拔柳」");
        return 1; 
}

int perform2(object me, object target)
{
	int lvl;
    object weapon = me->query_temp("weapon");
    if( !target
         || !target->is_character()
         || !me->is_fighting(target)
         || !living(target))
            	return notify_fail("只能在战斗中使用。\n");
    lvl = (int)me->query_skill("canglang-goufa", 1)  /4; 
	me->add_temp("apply/attack", lvl); 
    me->add_temp("apply/damage", lvl/2); 
    weapon->unequip(); 
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    weapon->wield();
    if ( me->is_fighting(target) 
		&& random(me->query_skill("canglang-goufa", 1)) > 250)
    COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    me->add_temp("apply/attack", -lvl); 
	me->add_temp("apply/damage", -lvl/2); 
    me->add("neili", -400);
    me->start_busy(1);
    me->add("jingli", -200);
	me->start_perform(4,"「鲁达拔柳」");
}

int help(object me)
{
   write(WHT"\n沧浪钩法「"HIG"鲁达拔柳"WHT"」："NOR"\n");
   write(@HELP
	沧浪钩法乃是神龙岛主晚年后整理自己的所学武技
	后总体提炼出的一套钩法武技，去繁就简，诡异犀
	利，防不胜防，尤其对于臂力较大男弟子而言，更
	是非常实战的功夫。其中鲁达拔柳乃是典型的强攻
	武技，利用自己高的臂力和锋利的武器，销段对方
	的兵器，且给敌人重创。
	注意：兵器越锋利度，效果越佳，钝兵器不能用。

	perform hook.luda

要求：
	最大内力要求 4000 以上；
	最大精力要求 2500 以上；
	当前内力要求 1500 以上；
	当前精力要求 800 以上；
	沧浪钩法等级 250 以上；
	毒龙大法等级 250 以上；
	基本钩法等级 250 以上；
	激发且备掌法为化骨绵掌；
	激发内功为毒龙大法；
	手持钩类武器，且锋利度不低于3
	性别需求 男性。
HELP
   );
   return 1;
}
