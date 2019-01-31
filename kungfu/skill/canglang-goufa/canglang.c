#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string perform_name() {return HBGRN+HIW"沧浪意"NOR;}

int perform(object me, object target)
{			

		object weapon,tweapon;
        string msg;
        int lv,skill; 		
		tweapon = target->query_temp("weapon");
		lv=me->query_skill("canglang-goufa",1);
		skill=me->query_skill("canglang-goufa",1)+me->query_skill("dulong-dafa",1)/5;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()||!me->is_fighting(target) )
                return notify_fail("沧浪意只能在战斗时使用！\n");

        if(me->query("family/master_id")!="hong antong")
                return notify_fail("沧浪意只有拜了教主后才能用！\n");

        if( !objectp(weapon=me->query_temp("weapon")) ||weapon->query("skill_type")!="hook") 
		{
                              
                return notify_fail("你必须拿着钩才能用沧浪意！\n");
        }
        if(!me->query("quest/sld/clgf/canglang/pass"))
                return notify_fail("你只是听说过沧浪意境绝技，不能用「沧浪意」。\n");

        if( (int)me->query_skill("huagu-mianzhang", 1) < 250 )
                return notify_fail("你的化骨绵掌还不够熟练，不能使用沧浪意！\n");

        if (me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("只有使用化骨绵掌时才能使用沧浪意！\n");

        if( (int)me->query_skill("shenlong-tuifa", 1) < 250 )
                return notify_fail("你的神龙腿法还不够熟练，不能使用沧浪意！\n");

        if (me->query_skill_mapped("leg") != "shenlong-tuifa")
                return notify_fail("只有使用神龙腿法时才能使用沧浪意！\n");

        if( (int)me->query_skill("canglang-goufa", 1) < 250 )
                return notify_fail("你的沧浪钩法还不够熟练，不能使用沧浪意！\n");

        if (me->query_skill_mapped("hook") != "canglang-goufa")
                return notify_fail("只有使用沧浪钩法时才能使用沧浪意！\n");

        if( (int)me->query_skill("dulong-dafa", 1) < 250 )
                return notify_fail("你的毒龙大法功力不足，不能用沧浪意。\n");

        if (me->query_skill_mapped("hook") != "canglang-goufa")
                return notify_fail("只有使用沧浪钩法时才能使用沧浪意！\n");

        if( (int)me->query_skill("hook", 1) < 250 )
                return notify_fail("你的基本钩法还不够熟练，不能使用沧浪意！\n");
        if((int)me->query("max_neili", 1) < 4000) 
                return notify_fail("你现在内力修为尚低，不能使用沧浪意！\n"); 

        if((int)me->query("eff_jingli", 1) < 2500) 
                return notify_fail("你现在精力修为尚低，不能使用沧浪意！\n"); 

        if((int)me->query("jingli", 1) < 800)
                return notify_fail("你现在精力不足，不能使用沧浪意！\n");       

        if((int)me->query("neili", 1) < 1500) 
                return notify_fail("你现在内力不足，不能使用沧浪意！\n");  

		if( weapon->query("clgf/canglang") ) 
                return notify_fail("你手中的武器已经注入劲气，正在施展沧浪意境中。\n");
		if( weapon->query_temp("clgf/canglang") ) 
                return notify_fail("你正在施展沧浪意境中。\n");

        if(me->query("gender")!= "男性") 
                return notify_fail("只有男人才能使用「沧浪意」！\n");      
 
        me->add("jingli",-100);
        me->add("neili",-200);

        msg = HBGRN+HIW "$N谨记洪教主所授的沧浪意境，面带诡异的笑容,心神进入空灵境界，但手中"+weapon->query("name")+HBGRN+HIW"突然亮了下！\n"NOR;
		msg+=HBGRN+HIW"刹那间，"+weapon->query("name")+HBGRN+HIW"隐约发出隐晦之光。\n"NOR;

		message_vision(msg,me,target);
		weapon->set("clgf/canglang",1);
		me->set_temp("clgf/canglang",skill);
		
		weapon->set("s_rigidity",(int)weapon->query("rigidity"));
        weapon->set("s_sharpness",(int)weapon->query("sharpness"));
        weapon->add("rigidity",10);
        weapon->add("sharpness",20);
		
		me->add_temp("apply/attack",skill/3);
		me->add_temp("apply/damage",skill/8);
		me->add_temp("apply/hook", skill/8);
		call_out("remove_effect",1,me,target,weapon,(int)lv/20);
		
        return 1;
}

void remove_effect(object me,object target,object weapon,int lv)
{
		string msg;
		int skill;
		object tweapon;

		tweapon = target->query_temp("weapon");
		skill=me->query_temp("clgf/canglang");
		if(!objectp(weapon)) return;

		if (!weapon->query("clgf/canglang")) return;

		if (weapon->query("broken")) return;

		if (!me){
     
           weapon->set("rigidity",(int)weapon->query("s_rigidity"));
           weapon->set("sharpness",(int)weapon->query("s_sharpness"));
           weapon->delete("clgf/canglang");
           return ;
       }

       if (me->query_temp("weapon") != weapon
         ||!me->is_fighting()
         || lv<1
         ||me->query_skill_mapped("force") != "dulong-dafa"
         ||me->query("neili")<200 ){
             message_vision(weapon->query("name")+HBGRN+HIW"周身那层隐晦的光芒渐渐退去,又恢复了平常!\n"NOR,me);
             
             weapon->set("rigidity",(int)weapon->query("s_rigidity"));
             weapon->set("sharpness",(int)weapon->query("s_sharpness"));
             weapon->delete("clgf/canglang");
			 me->add_temp("apply/attack",-skill/3);
			 me->add_temp("apply/damage",-skill/8);
			 me->add_temp("apply/hook",-skill/8);
			 me->delete_temp("clgf/canglang");
             return ;
         }

		call_out("remove_effect",2,me,target,weapon,lv--);
	
		return ;
}

int help(object me)
{
   write(WHT"\n沧浪钩法「"HBGRN+HIW"沧浪意"WHT"」："NOR"\n");
   write(@HELP
	沧浪钩法乃是神龙岛主晚年后整理自己的所学武技
	后总体提炼出的一套钩法武技，去繁就简，诡异犀
	利，防不胜防，尤其对于臂力较大男弟子而言，更
	是非常实战的功夫。其中沧浪意乃是沧浪钩法重要
	的辅助进攻武技，利用自己的独特内功和法门，对
	手中武器短时间内大幅提高硬度和锋利度，对敌实
	施有效打击,此招需向教主请教。

	注意：set 沧浪钩法 钩 解开沧浪意有特效
	
	perform hook.canglang
	
要求：
	最大内力要求 4000 以上；
	最大精力要求 2500 以上；
	当前内力要求 1500 以上；
	当前精力要求 800 以上；
	化骨绵掌等级 350 以上；
	神龙腿法等级 350 以上；
	沧浪钩法等级 350 以上；
	毒龙大法等级 350 以上；
	基本钩法等级 350 以上；
	激发且备掌法为化骨绵掌；
	激发腿法为神龙腿法；
	激发钩法为沧浪钩法；
	激发内功为毒龙大法；
	手持钩类武器；
	性别需求 男性。
HELP
   );
   return 1;
}
