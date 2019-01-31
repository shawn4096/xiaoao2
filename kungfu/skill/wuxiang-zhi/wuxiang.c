//wuxiang.c 
// creat by sohu@xojh

#include <ansi.h>
#include <combat.h>
#include <skill.h>
inherit F_SSERVER;

int perform(object me, object target)
{
      string msg;
      int improve,lvl,lvl2;

      if( !target ) target = offensive_target(me);
     
      if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
          return notify_fail("你要对谁使用「无相劫」？\n");

        if( me->query("family/family_name")!="少林派" )
                return notify_fail("你不是少林弟子，如何能使用少林绝技？\n");
  
		if( !me->query("wxjz/jueji") )
                return notify_fail("你虽然听说过无相劫指绝技，但并不会使用。\n");
		if( me->query_skill("buddhism",1)<200 )
                return notify_fail("你佛法不足，不能使用慈悲为怀的少林武功？\n");
        if(me->query_condition("killer")>500)
                return notify_fail("阿弥陀佛，杀人太多了，你已经无救了，一日不过三，别杀上瘾了。\n");
        if(environment(me)->query("no_fight"))
                return notify_fail("这里不能攻击别人。\n");
        if(target->query("combat_exp")<2000000)
                return notify_fail("功力这么差的人，用得着如此费劲么？\n");
                
        if( me->query("no_pk") && userp(target) && (!me->query_temp("xyjob") || !target->query_temp("xyjob")))
                return notify_fail("你已经退出江湖，还是老老实实的吧。\n");

        if( target->query("no_pk") && userp(me) && (!me->query_temp("xyjob") || !target->query_temp("xyjob")))
                return notify_fail( target->name()+"已经退出江湖了，得饶人处且饶人吧！\n");
          
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手使用「无相劫」！\n");
      
        if( (int)me->query_skill("wuxiang-zhi",1) < 550 )
               return notify_fail("你的无相劫指不够娴熟，不会使用「无相劫」！\n");
   
        if( (int)me->query_skill("yijin-jing",1) < 550 )
              return notify_fail("你的易筋经内功等级不够，不能使用「无相劫」！\n");  
      
        if( (int)me->query("max_neili") < 15000 )
              return notify_fail("你的最大内力太弱，不能使用「无相劫」！\n");
      
        if( (int)me->query("neili") < 3000 )
              return notify_fail("你的内力太少了，无法使用出「无相劫」！\n");   
                                                                                 
        if (me->query_skill_prepared("finger") != "wuxiang-zhi"
            || me->query_skill_mapped("finger") != "wuxiang-zhi"
			|| me->query_skill_mapped("parry") != "wuxiang-zhi")
           return notify_fail("你现在无法使用「无相劫」进行攻击。\n");                                                                                 
        if (!me->query("yjj/powerup"))
        {
			if( me->query_temp("slpfm/jgqbrz") )
                return notify_fail("你正在使用少林绝技「"+me->query_temp("slpfm/jgqbrz")+"」！\n");
            if( me->query_temp("slpfm/rytqys") )
                return notify_fail("你正在使用少林绝技「"+me->query_temp("slpfm/rytqys")+"」！\n");
            if( me->query_temp("slpfm/lzgyzc") )
                return notify_fail("你正在使用少林绝技「"+me->query_temp("slpfm/lzgyzc")+"」！\n");
        }
		
        if( target == me )
                return notify_fail("自己玩自己啊！\n");

        if (target->is_corpse() || !target->is_character())
               return notify_fail("那不是活物耶！\n");
        if(!living(target))
                return notify_fail("对方都这样了，还用的着这么费劲么？\n");

       if (!me->query("quest/sl/yjj/powerup"))
           {
            /*  me->set_temp("slpfm/lzgyzc","无相劫");
             me->set_temp("slpfm/jgqbrz","无相劫");
             me->set_temp("slpfm/rytqys","无相劫");*/
			 me->start_perform(5, "无相劫");
			 lvl=me->query_skill("wuxiang-zhi",1);
           }
		 else 
	     { 
			 lvl=me->query_skill("wuxiang-zhi",1)+me->query_skill("yijin-jing",1)/2;
			 me->start_perform(2,"无相劫");

		 }
         msg=HIW"$N将全身功力凝聚一指，纵身一跃，无相劫指的威力彻底融会贯通，施展出「无相劫」连环绝技！"NOR; 
		 message_vision(msg, me, target);  
  /*    if (random(me->query("combat_exp"))>target->query("combat_exp")/2
			||random(me->query_str())>target->query_dex()/2
			||random(me->query_int())>target->query_int()/2)
        {*/
       
		     me->add_temp("apply/attack",lvl);
             me->add_temp("apply/finger",lvl/3);
		     me->add_temp("apply/damage",lvl/3);
             me->set_temp("wxz_wuxiang", 6);
//第一招，起手式，无我
	         COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
	          me->add("neili", -80);
//第二招	    
	    	if(me->is_fighting(target)){
		      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
	    	   me->add("neili", -80);
     	     }
//第三招
		    if(me->is_fighting(target) && me->query_skill("wuxiang-zhi", 1) >= 250){
		      COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		      me->add("neili", -80);
	         }
//第四招
	        if(me->is_fighting(target) && me->query_skill("wuxiang-zhi", 1) >= 350){
		       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		      me->add("neili", -100);
	         }
//第五招
	// 5th kick is type_super. cannot be done in normal fight.
	         if(me->is_fighting(target) && me->query_skill("wuxiang-zhi", 1) >= 450) {
		        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		        me->add("neili", -150);
	          }
//第六招
             if(me->is_fighting(target) && me->query_skill("wuxiang-zhi", 1) >= 550) {
		       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_SUPER);
		       me->add("neili", -150);
	          }
			 

          	 me->add_temp("apply/attack",-lvl);
             me->add_temp("apply/finger",-lvl/3);
		     me->add_temp("apply/damage",-lvl/3);
      //  message_vision(msg, me, target);  
        me->add("neili", -800);
        me->delete_temp("wxz_wuxiang");
		me->start_perform(6, "无相劫");
		me->add_busy(3);
      return 1;
}

void remove_effect(object me, int improve)
{
        me->delete_temp("slpfm/lzgyzc");
        me->delete_temp("slpfm/rytqys");
        me->delete_temp("slpfm/jgqbrz");
}

string perform_name(){ return HIY"无相劫"NOR; }

int help(object me)
{
        write(HIR"\n无相劫指之「无相劫」："NOR"\n\n");
        write(@HELP 
	出自金庸小说中《天龙八部》，乃少林寺七十二绝技之一，
	唯有少林玄悲大师习得。无相劫指全凭一股纯阳真气炽热非
	常，中招之人必定全身焦黑如火烧一般。后来为大轮寺圣僧
	鸠摩智施展出来，虽然不是正宗，但功力却非凡。
		
	说明：无相劫乃无相劫指第一式起手式，无我无相，无虚假
	、无真实，为近身攻击招式。
。
	perform finger.wuxiang

要求：
	当前内力 3000 以上；
	最大内力 15000 以上；
	当前精力 2500 以上；
	无相劫指 550 以上；
	基本内功 550 以上；
	基本指法 550 以上；
	禅宗佛法 200 ；
	激发指法为无相劫指；
	激发招架为无相劫指；
	激发内功不限。
HELP
        );
        return 1;
}