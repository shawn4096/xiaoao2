//meihuo.c 魅惑
//cre by sohu@xojh 
//根据匕首定位女性而且神龙岛的女性大多妖媚，以此增加匕法的命中和突袭

#include <ansi.h>
#include <combat.h>
//#include <combat_msg.h>

inherit F_SSERVER;

string perform_name() {return HBYEL"魅惑"NOR;}

int perform(object me, object target)
{
	    object weapon;
        int ap,dp,skill; 
		weapon=me->query_temp("weapon");
        skill=me->query_skill("tenglong-bifa",1);

		if( !target ) target = offensive_target(me);

         if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("【魅惑】只能在战斗时使用！\n");

        if( !weapon || weapon->query("skill_type")!="dagger")
                return notify_fail("你必须拿着匕首才能用【魅惑】！\n");
		if( !me->query("quest/sld/tlbf/meihuo/pass"))
                return notify_fail("你只是知道有这门绝技，但尚无法能用【魅惑】！\n");
		if (me->query_skill_prepared("hand") != "chansi-shou"
            || me->query_skill_mapped("hand") != "chansi-shou" )
                return notify_fail("你没激发且备金蛇缠丝手，现在无法使用【魅惑】进行攻击。\n");  

        if( (int)me->query_skill("chansi-shou", 1) < 350 )
                return notify_fail("你的缠丝手还不够熟练，不能使用【魅惑】！\n");

        if (me->query_skill_mapped("hand") != "chansi-shou")
                return notify_fail("只有使用缠丝手时才能使用【魅惑】！\n");

        if( (int)me->query_skill("shenlong-tuifa", 1) < 350 )
                return notify_fail("你的神龙腿法还不够熟练，不能使用【魅惑】！\n");

        if (me->query_skill_mapped("leg") != "shenlong-tuifa")
                return notify_fail("只有使用神龙腿法时才能使用【魅惑】！\n");

        if( (int)me->query_skill("tenglong-bifa", 1) < 350 )
                return notify_fail("你的腾龙匕法还不够熟练，不能使用【魅惑】！\n");

        if (me->query_skill_mapped("dagger") != "tenglong-bifa")
                return notify_fail("只有使用腾龙匕法时才能使用【魅惑】！\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 350 )
                return notify_fail("你的毒龙大法功力不足，不能用【魅惑】。\n");

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("你现在精力不足，不能使用【魅惑】！\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("你现在内力不足，不能使用【魅惑】！\n");  
		if( me->query("gender")!="女性") 
                return notify_fail("你一个大老爷们搔首弄姿的，让人徒增厌倦！\n");  
        if(me->query("per")<25) 
                return notify_fail("你的先天容貌欠佳，无法施展这魅惑技能！\n");  
		if( me->query_skill_mapped("force") != "dulong-dafa")
                return notify_fail("你现在所使用的内功同毒龙大法向抵触，不能使用【魅惑】。\n");
		//if( target->query_temp("tlbf/meiguo"))
              //  return notify_fail("对方已经中了你所施展的【魅惑】绝技。\n");

		if( target->is_busy())
                return notify_fail("对方已经手忙脚乱了，你赶紧放手进攻吧。\n");

		message_vision(HIM"$N将"+weapon->query("name")+HIM"藏在身后，冲$n嫣然一笑，刹那间宛如小露含春，百花绽放，\n"NOR,me,target);
		message_vision(HIY"\b$N轻步缓缓，粉面含春，一步三摇，$n刹那间觉得$N如风中百合，摇曳多姿。\n"NOR,me,target);
		
		ap=(int)me->query_per()*me->query("combat_exp")/10000;
		
		if (target->query("family/family_name")=="少林派"||target->query("family/family_name")=="天龙寺")
			dp=(int)me->query("buddhism",1)/10*me->query("combat_exp")/10000;
		else if (target->query("family/family_name")=="峨嵋派")
			dp=(int)me->query("dacheng-fofa",1)/10*me->query("combat_exp")/10000;
		else if (target->query("family/family_name")=="大轮寺")
			dp=(int)me->query("mizong-fofa",1)/10*me->query("combat_exp")/10000;
		else if (target->query("family/family_name")=="血刀门")
			dp=(int)me->query("huanxi-chan",1)*me->query("combat_exp")/200000;
		else if (target->query("family/family_name")=="武当派"||target->query("family/family_name")=="全真教")
			dp=(int)me->query("taoism",1)/10*me->query("combat_exp")/10000;
		else dp=(int)me->query_per()*me->query("combat_exp")/10000;
		
		if (random(ap)>dp/2 
			|| random(me->query_skill("dagger",1))>target->query_skill("parry",1)/2
			|| random(me->query_per())>target->query_per()/2)
		{
			//message_vision(HIR"\n$N深情款款，悄然靠近$n不足三尺，趁$n一时间为$N美色所惑的瞬间，身形跃起，拔出袖中藏的"+weapon->query("name")+HIR"刺向$n!\n"NOR,me,target);
			if (userp(target)) target->add_busy(2);
			else target->add_busy(4);
			//target->set_temp("tlbf/meihuo",skill);
			if (!target->query_temp("tlbf/meihuo")
				&&me->query("gender")=="男性")
			{
				target->add_temp("apply/attack",-skill/3);
				target->add_temp("apply/parry",-skill/4);
				target->add_temp("apply/dodge",-skill/4);
				target->set_temp("tlbf/meihuo",skill);
				call_out("remove_effect",1,target);
				message_vision(HIM"$N巧笑倩然，笑容动人心魄，令$n梦牵魂绕，神魂颠倒，呼吸开始急促起来！\n"NOR,me,target);
			}
			//if (me->is_fighting()&&objectp(target))
				//call_out("remove_effect",5,me,target);
			
		}
		else {
			message_vision(HIC"$N搔首弄姿的卖弄了半天，$n冷笑几声，并没收到$N的影响。\n"NOR,me,target);
			me->start_busy(1);
		}
		me->add("neili",random(200));
		me->add("jingli",random(200));	
        
		return 1;
}
void remove_effect(object target)
{
      int skill;
	  if (!objectp(target)) return ;
	  skill=target->query_temp("tlbf/meihuo");
	  target->add_temp("apply/attack",skill/3);
	  target->add_temp("apply/parry",skill/4);
	  target->add_temp("apply/dodge",skill/4);

	  tell_object(target,target->query("name")+HIC"意识到自己失态，急忙运功，强行压制这种魅惑。\n"NOR);
	  target->delete_temp("tlbf/meihuo");
	
	  return ; 
}

int help(object me)
{
   write(WHT"\n腾龙匕法「"HBYEL"魅惑"WHT"」："NOR"\n");
   write(@HELP
	腾龙匕法乃是神龙岛主夫人苏荃的不传之谜
	变化多端，防不胜防。可谓将女人的优势发
	挥的淋漓尽致。
	因神龙岛洪岛主身上藏有一个大秘密，所以
	神龙岛的女弟子大都如花似玉，且对魅惑之
	术钻研甚是精通，久而久之，举手投足之间
	都能带将出来。此绝技乃是腾龙匕法的一个
	暗杀辅助技能，和容貌以及战斗经验有关联
	注意：因为出家人、道士、喇嘛等是修习明
	心的法门，对于此绝技有一定的克制功效，
	但最终还是于后天容貌的效果有关。对女人
	效果不佳。
	   
	指令：perform dagger.meihuo

要求：
	最大内力要求 4000 以上；
	最大精力要求 2500 以上；
	当前内力要求 1500 以上；
	当前精力要求 800 以上；
	腾龙匕法等级 350 以上；
	基本匕法等级 350 以上；
	毒龙大法等级 350 以上；
	基本内功等级 350 以上；
	先天容貌要求 25 以上；
	激发腿法神龙腿法
	激发手法为金蛇缠丝手
	激发匕法为腾龙匕法；
	手持匕首类武器；
	性别需求女性。
HELP
   );
   return 1;
}
