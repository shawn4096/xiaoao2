// qiankun.c 
// tiantian@sj 2000.10.14 
// Modified by snowman@SJ 12/12/2000

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
      string msg;
      int improve;

      if( !target ) target = offensive_target(me);
     
      if( !objectp(target)
         //|| !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
          return notify_fail("都那样了，你还使用「袖里乾坤」？\n");

        if( me->query("family/family_name")!="少林派" )
                return notify_fail("你不是少林弟子，如何能使用少林绝技？\n");
        if( me->query("shen")<0 )
                return notify_fail("你心术不正，不能使用慈悲为怀的少林武功？\n");
        if(me->query_condition("killer")>200)
                return notify_fail("一日不过三，别杀上瘾了。\n");
        if(environment(me)->query("no_fight"))
                return notify_fail("这里不能攻击别人。\n");
        if(target->query("combat_exp")<100000)
                return notify_fail("这么差的人，用得着如此费劲么？\n");
                
        if( me->query("no_pk") && userp(target) && (!me->query_temp("xyjob") || !target->query_temp("xyjob")))
                return notify_fail("你已经退出江湖，还是老老实实的吧。\n");

        if( target->query("no_pk") && userp(me) && (!me->query_temp("xyjob") || !target->query_temp("xyjob")))
                return notify_fail( target->name()+"已经退出江湖了，得饶人处且饶人吧！\n");
          
        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手使用「袖里乾坤」！\n");
      
        if( (int)me->query_skill("wuxiang-zhi",1) < 450 )
               return notify_fail("你的无相劫指不够娴熟，不会使用「袖里乾坤」！\n");
        if( (int)me->query_str() < 60 )
               return notify_fail("你的臂力太低，不会使用「袖里乾坤」！\n");
		if( (int)me->query_dex() < 60 )
               return notify_fail("你的身法太低，不会使用「袖里乾坤」！\n");
        if( (int)me->query_skill("yijin-jing",1) < 450 )
              return notify_fail("你的易筋经内功等级不够，不能使用「袖里乾坤」！\n");  
      
        if( (int)me->query("max_neili") < 9000 )
              return notify_fail("你的内力太弱，不能使用「袖里乾坤」！\n");
      
        if( (int)me->query("neili") < 3000 )
              return notify_fail("你的内力太少了，无法使用出「袖里乾坤」！\n");   
                                                                                 
        if (me->query_skill_prepared("finger") != "wuxiang-zhi"
            || me->query_skill_mapped("finger") != "wuxiang-zhi"
			|| me->query_skill_mapped("parry") != "wuxiang-zhi")
           return notify_fail("你现在无法使用「袖里乾坤」进行攻击。\n");                                                                                 
        if (!me->query("quest/sl/yjj/powerup"))
        {
			if( me->query_temp("slpfm/jgqbrz") )
                return notify_fail("你正在使用少林绝技「"+me->query_temp("slpfm/jgqbrz")+"」！\n");
            if( me->query_temp("slpfm/rytqys") )
                return notify_fail("你正在使用少林绝技「"+me->query_temp("slpfm/rytqys")+"」！\n");
            if( me->query_temp("slpfm/lzgyzc") )
                return notify_fail("你正在使用少林绝技「"+me->query_temp("slpfm/lzgyzc")+"」！\n");
        }
		
        if( target == me )
                return notify_fail("自己点自己啊！\n");

        if (target->is_corpse() || !target->is_character())
               return notify_fail("那不是活物耶！\n");
        if(!living(target))
                return notify_fail("对方都这样了，还用的着这么费劲么？\n");

        if(  target->is_busy() ) 
                return notify_fail("对方正自顾不暇，放胆攻击吧！\n");
        if (!me->query("quest/sl/yjj/powerup"))
           {
             me->set_temp("slpfm/lzgyzc","袖里乾坤");
             me->set_temp("slpfm/jgqbrz","袖里乾坤");
             me->set_temp("slpfm/rytqys","袖里乾坤");
           }
             tell_object(me, HIY"你面带微笑，将双手拢在衣袖之中，指力从衣袖中暗暗发出，一股若有若无的微风向着"
             +target->name()+"袭去。\n" NOR);  
             me->start_call_out( (: call_other, __FILE__, "remove_effect", me, improve :), 6 );
        if( random(me->query("combat_exp")) > random(target->query("combat_exp")/3)) {
             tell_object(me,HIR"结果"+target->query("name")+"被你指风点中，登时动弹不得。\n"NOR);
             tell_object(target,HIC"你只觉得一股若有若无的微风从身上拂过，不经意间发现自己已经无法动弹。\n"NOR);
             me->add("neili", -450);    
             target->start_busy(4 + random(me->query_skill("wuxiang-zhi",1))/40);
        } else {
                 if( me->query_skill("wuxiang-zhi", 1)/3*2 > random(target->query_skill("dodge",1))){
                        msg = HIY"$n只觉得一股若有若无的微风从身上拂过，却又不知道发生了什么事情。\n"NOR;
                        me->start_busy(1+random(2));
                } else {
                        msg = HIY"$n只觉得一股若有若无的微风从身上拂过，回头看去，原来是$N在实施暗算。\n"NOR;
                        me->start_busy(2+random(3));
                        me->kill_ob(target);
                        target->kill_ob(me);
                }
                message_vision(msg, me, target);  
			    me->start_perform(5, "袖里乾坤");

                me->add("neili", -200);
      }
      return 1;
}

void remove_effect(object me, int improve)
{
   me->delete_temp("slpfm/lzgyzc");
        me->delete_temp("slpfm/rytqys");
        me->delete_temp("slpfm/jgqbrz");
}

string perform_name(){ return HIY"袖里乾坤"NOR; }

int help(object me)
{
        write(HIR"\n无相劫指之「袖里乾坤」："NOR"\n\n");
        write(@HELP 
	出自金庸小说中《天龙八部》，乃少林寺七十二绝技之一，
	唯有少林玄悲大师习得。无相劫指全凭一股纯阳真气炽热非
	常，中招之人必定全身焦黑如火烧一般。后来为大轮寺圣僧
	鸠摩智施展出来，虽然不是正宗，但功力却非凡。		
	说明：袖里乾坤乃无相劫指第一式起手式，无我无相，无虚
	假、无真实，为近身攻击招式。无相劫指  无相劫指。
	
	perform finger.qiankun
	
要求：
	当前内力需求 9000 以上；
	最大内力需求 5000 以上；
	当前精力需求 2500 以上；
	无相劫指等级 450 以上；
	基本内功等级 450 以上；
	基本指法等级 450 以上；
	后天身法要求大于等于60；
	后天臂力要求大于等于60；
	激发指法为无相劫指；
	激发招架为无相劫指；
	激发内功不限。
HELP
        );
        return 1;
}