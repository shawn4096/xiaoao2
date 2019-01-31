// kuaijian.c 狂风快剑
// by darken@SJ
// modified olives@SJ
// Update By lsxk@hsbbs 2007/6/14
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

string perform_name() {return HIG"狂风快剑"NOR;}

int perform(object me, object target)
{
        object wp;
		wp=me->query_temp("weapon");
		if( !target || target == me) target = offensive_target(me);

        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("狂风快剑只能对战斗中的对手使用。\n");
    	
		if (me->query("huashan/quest") == "气宗")
        {
           if (me->query_skill_mapped("force") != "zixia-gong"
             &&me->query_skill_mapped("force") != "huashan-qigong" )
                return notify_fail("你的内功有误，无法使用「狂风快剑」。\n");
        } 

        if( (int)me->query_dex() < 70 )
                return notify_fail("你在身法上先天禀赋不足，不能使用狂风快剑！\n");
        
        if( (int)me->query_skill("zixia-gong", 1) < 400
          &&(int)me->query_skill("huashan-qigong", 1) < 400)
                return notify_fail("你的华山特殊内功火候未到，无法施展狂风快剑！\n");

        if( (int)me->query_skill("dodge",1) < 400 )
                return notify_fail("狂风快剑需要超绝的轻功配合，方能有效施展！\n");

        if( (int)me->query_skill("sword",1) < 400 )
                return notify_fail("你剑法未到炉火纯青之境，还不会使用狂风快剑！\n");

        if( (int)me->query("neili") <= 5000 )
                return notify_fail("你的内力不够使用狂风快剑！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力不够使用狂风快剑！\n");

        if( me->query_temp("hsj_kf",))
                return notify_fail("你正在运用狂风快剑！\n");

        if(!me->query_temp("weapon") || wp->query("skill_type") != "sword" 
        || me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("你手中无剑怎能使用狂风快剑？！\n");

        message_vision(HBGRN+HIW"$N仰天一声清啸，斜行而前，长剑横削直击，迅捷无比，未到五六招，剑势中已发出隐隐风声。$N出剑如风，宛如潮水般攻向$n。\n"NOR
		               +HBGRN+HIW"越来越快，风声也是渐响。剑招一剑快似一剑，所激起的风声也越来越强。一百零八式「狂风快剑」顷刻间全向$n身上招呼！\n"NOR, me, target);
        me->set_temp("hsj_kf",1);
        me->add("neili",-1000);
        me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1)/6);
        me->add_temp("apply/damage",me->query_skill("huashan-jianfa",1)/10);
		//男性更有威力
		if(me->query("gender")=="男性")
		{
          me->add_temp("apply/sword",me->query_skill("huashan-jianfa",1)/6);
		  me->add_temp("apply/strength",me->query_skill("huashan-jianfa",1)/6);
		}
		//剑宗增加伤害和命中
		if (me->query("quest/huashan")=="剑宗")
		{
          me->add_temp("apply/damage",me->query_skill("huashan-jianfa",1)/7);
          me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1)/5);
		}
        call_out("kuangfeng", 0, me, target);
        me->start_perform(999,"「狂风快剑」");
        return 1;
}

void kuangfeng(object me, object target)
{
        int i;
        object weapon;
        
        if (!me) return;
        weapon= me->query_temp("weapon");
        //若busy后，气宗停止狂风，但剑宗会继续
        if(me->is_busy() && me->query("quest/huashan") != "剑宗"){
            message_vision(HIG"$N的“狂风快剑”委实快极，一百零八招片刻间便已使完。\n"NOR, me);
            me->add_temp("apply/damage",-me->query_skill("huashan-jianfa",1)/10);
            me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/6);
			if(me->query("gender")=="男性")
		    {
				me->add_temp("apply/sword",-me->query_skill("huashan-jianfa",1)/6);
				me->add_temp("apply/strength",-me->query_skill("huashan-jianfa",1)/6);
	     	}
            me->delete_temp("hsj_kf");
            me->start_busy(3+random(3));
            me->start_perform(2+random(3),"「狂风快剑」");
            return;
        }
        if (me->is_fighting(target) &&
    //       !me->is_busy()          &&
            (int)me->query("jingli") > 1000 &&
            (int)me->query("neili") > 2000 &&
           objectp(target) && 
           !target->is_ghost() &&
           !me->is_ghost() && 
           me->query_temp("hsj_kf")<37 &&
           environment(me) == environment(target) &&
           weapon &&
           weapon->query("skill_type") == "sword"  
            ) {
               message_vision(HIG"旁观众人只觉寒气逼人，脸上、手上被$N剑法所带起的疾风刮得隐隐生疼，不由自主的后退。\n"NOR, me);
               if((int)me->query_temp("hsj_kf")%3==0 && me->query("quest/huashan") == "剑宗" && random(2)){
                  message_vision(HBRED"$n哪里见过如此快的剑招？当下暗暗吃惊，全力防守化解$N的凌厉攻势！\n"NOR, me, target);
                  target->add_temp("lost_attack",3+random(3)); 
			      target->add_busy(1);
             }
            for (i = 0; i < 4; i++) {
              if (me->is_fighting(target)) {
               if (me->query("quest/huashan") == "剑宗"){
					me->add_temp("apply/attack",me->query_skill("huashan-jianfa",1)/3);
					me->add_temp("apply/damage",me->query_skill("huashan-jianfa",1)/5);
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(5)?3:1);
					me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/3);
					me->add_temp("apply/damage",-me->query_skill("huashan-jianfa",1)/5);
			  
               } else COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
           }
          } 
          me->add("neili", -100-random(50));
          me->add("jingli", -80-random(30));
          me->add_temp("hsj_kf",1);
          call_out("kuangfeng", 1, me, target);
          return;
        }
        message_vision(HIG"$N的“狂风快剑”委实快极，一百零八招片刻间便已使完。\n"NOR, me);
        me->add_temp("apply/damage",-me->query_skill("huashan-jianfa",1)/10);
        me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/6);
		if (me->query("quest/huashan")=="剑宗")
		{
          me->add_temp("apply/damage",-me->query_skill("huashan-jianfa",1)/7);
          me->add_temp("apply/attack",-me->query_skill("huashan-jianfa",1)/5);
		}
		if(me->query("gender")=="男性")
		{
          me->add_temp("apply/sword",-me->query_skill("huashan-jianfa",1)/6);
		  me->add_temp("apply/strength",-me->query_skill("huashan-jianfa",1)/6);
		}
        me->delete_temp("hsj_kf");
        if(me->query("gender")!="男性")
             me->start_busy(3+random(3));
        else me->start_busy(1+random(2));
        me->start_perform(2+random(3),"「狂风快剑」");
}

int help(object me)
{
	write(WHT"\n华山剑法「"HIG"狂风快剑"WHT"」："NOR"\n");
	write(@HELP
    狂风快剑，此招便如其名，招数之快，当世之上恐再无任何武功可与
    其相较高下，此乃华山剑宗绝技，武林绝学，华山剑宗弟子终极绝技
    该招共有一百零八招，一气呵成，便如行云流水般地使出，即便旁观
    者也会为其剑气之厉害而骇然。此招对使用者的剑法、身法、内功要
    求颇高。华山气宗弟子也可使用，但威力却不及剑宗之三、四成。
	需要注意的是，此招乃剑宗绝技，所以男性玩家威力略强，对于内功
	要求也没有气宗那么严格。
    
	指令：perform sword.kuaijian

要求：
	华山气功 或者 紫霞神功 400级
	后天身法至少 70  以上
	基本剑法等级 400 级，
	基本轻功等级 400 级，
	当前内力需求 5000 以上，
	当前精力需求 1000 以上。
HELP
	);
	return 1;
}
