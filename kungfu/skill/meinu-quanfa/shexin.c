// shexin.c 摄心
// edit by sohu@xojh
#include <ansi.h>

inherit F_SSERVER;

void affectob(object ,object ,int ,int ,int);
void dohit(object,object);
string perform_name(){ return HIW"摄心"NOR; }
int perform(object me, object target)
{
	int affect,skill,hits;
	string msg;
	
	if(!me->is_fighting())
		return notify_fail("你没在战斗中呢！\n");

	if(!target) target = offensive_target(me);

	if( (skill=(int)me->query_skill("meinu-quanfa", 1)) < 200 )
		return notify_fail("你的美女拳法还不够纯熟，无法施展「摄心」绝技。\n");
	if( me->query_skill("cuff", 1) < 200 )
		return notify_fail("你的基本拳法还不够纯熟，无法施展「摄心」绝技。\n");
	if( me->query_skill("force", 1) < 200 )
		return notify_fail("你的基本内功还不够纯熟，无法施展「摄心」绝技。\n");
	if( me->query_skill("yunu-xinjing", 1) < 200 )
		return notify_fail("你的玉女心经还不够纯熟，无法施展「摄心」绝技。\n");

	if( me->query_skill_mapped("cuff") != "meinu-quanfa"
		||me->query_skill_prepared("cuff") != "meinu-quanfa"
		||me->query_skill_mapped("parry") != "meinu-quanfa")
		return notify_fail("你没有激发美女拳法如何用的了摄心绝技！\n");
	
	if ( me->query_temp("weapon"))
		return notify_fail("你手持武器，如何使用「摄心」绝技？\n");

	if(me->query("gender")=="无性")
		return notify_fail("你阴阳不调，你如何施展「摄心」绝技？\n");
	if(target->query("gender")=="无性")
		return notify_fail("对方阴阳不调，无欲无求，你如何施展「摄心」绝技？\n");
	if(me->query_temp("mnq/shexin"))
		return notify_fail("对方已经中了「摄心」绝技\n");

    if(target->query("gender")==me->query("gender"))
		if (me->query_per(1)<target->query_per(1))
			return notify_fail("面对同性对手，你的容貌不如对方，如何施展「摄心」绝技。\n");
	if(me->query("max_neili")<2500)
		return notify_fail("你最大内力不够，无法使用「摄心」绝技。\n");
	if(me->query("neili")< 800 )
		return notify_fail("你当前内力不够，无法使用「摄心」绝技。\n");
	if(me->query("jingli")< 500)
		return notify_fail("你当前精力不够，无法使用「摄心」绝技。\n");
	affect=me->query_per()+random(me->query("per")/2);
    
	if (me->query("gender")=="男性") affect=affect / 2;
	me->set_temp("mnq/shexin",1);
	if (   target->query_skill("buddhism") > (skill+random(affect))  
	    || target->query_skill("dacheng-fofa") > (skill+random(affect))
		|| target->query_skill("mizong-fofa") > (skill+random(affect))
	    || target->query_skill("taoism") > (skill+random(affect)) )
	{
		msg = HIY"\n$N对$n轻轻一笑，眼光之中流露出妩媚之意，想施展「摄心」绝技。\n"+
			HIY"不料$n平素修心功法了得，定了定神，突然大喝一声，顿时把$N惊出一身冷汗。\n"NOR;
		message_vision(msg,me,target);
		me->start_busy(1);
	}
	else if (target->query_per()>=me->query_per())
	{
		msg = HIY"\n$N忽然对$n轻轻一笑，眼光四处流动，所经过之处似乎充满了妩媚。\n"NOR; 
		message_vision(msg, me, target);
		message_vision(HIW"但是$N沮丧地发觉，$n比自己漂亮，「摄心」绝技无法施展。\n"NOR,me,target);
		me->start_busy(2);
	}
   else if (random(10)>5)
	{
		msg = HIM"\n$N忽然对$n轻轻一笑，眼光四处流动，所经过之处似乎充满了妩媚，$n不由得一呆。\n"NOR; 
      
		message_vision(msg, me, target);

		if ( random(skill) > target->query_skill("force",1)/2 )
		{
			target->add_temp("apply/dexerity", -affect);
			hits = skill / 10;
			me->start_perform(4,"摄心");
			target->apply_condition("no_perform", 3);
			target->set_temp("shexin", 1);
            target->add_busy(3);
			me->add("jingli",-100);
			me->add("neili",-300);
			dohit(me,target);
			dohit(me,target);
			call_out("affectob",2, me, target, affect, hits,3);
		}
		else 
		{
			message_vision(CYN"\n但见$n心中意识到危险，大喝一声，想用雄浑的内力打破$N四周这妩媚的气氛！\n"+
					"结果$n只发出两、三招，就无法忍受$N妩媚的眼光了。\n"NOR, me, target);

            target->add_busy(2);

			me->add("neili",-100);
			target->add_temp("apply/dexerity", -affect);
			dohit(me,target);
			dohit(me,target);
			if (skill >= 250) dohit(me,target); //200级后飞跃
			target->add_temp("apply/dexerity", affect);
			
		//	me->delete_temp("muq/shexin");

			me->start_perform(4,"摄心");
		}
	}
	else
	{
		msg = HIY"\n$N忽然对$n轻轻一笑，想施展「摄心」绝技。\n"+
			HIM"谁知$n根本就没有上当。\n"NOR; 
		message_vision(msg, me, target);
		//me->delete_temp("muq/shexin");
		me->start_perform(5,"摄心");
	}
	me->delete_temp("mnq/shexin");

	return 1;
}

void affectob(object me,object target,int affect,int hits,int now)
{
	if( !me 
		|| !target 
		|| ( now > hits) 
		|| objectp(me->query_temp("weapon")) 
		|| target->is_ghost() 
		|| me->is_ghost()  
		|| !me->is_fighting(target) 
		|| me->query("neili") < 800 
		|| me->query_skill_prepared("cuff")!="meinu-quanfa"
		|| me->query_skill_prepared("parry")!="meinu-quanfa")
	{
		if( me ) message_vision(HIC"\n$N内力突然一顿，眼光又恢复平静。\n"NOR, me);
		me->delete_temp("muq/shexin");
		if( target && target->query_temp("shexin"))
			target->delete_temp("shexin");
		if ( target )  target->add_temp("apply/dexerity", affect);
			return;
	}

	if( now > (hits/2) && target->query_temp("shexin"))
		target->delete_temp("bujue_busy");

	dohit(me,target);
	dohit(me,target);
	me->start_perform(1,"摄心");
	call_out("affectob",2,me,target,affect,hits,now+1);
}

void dohit(object me,object target) 
{
	int neili,jiali;
	neili = me->query("neili");
	jiali = me->query("jiali");
	if (!userp(target))
	{  
	    message_vision(HIY"\n$N低眉浅笑，宛若处子，万千风流，集于一身,趁$n神情发呆之际连出三招！\n"NOR, me, target);
		me->add_temp("apply/attack",me->query_skill("meinu-quanfa",1)/2);
	    me->add_temp("apply/damage",me->query_skill("meinu-quanfa",1)/4);
		if (target->query("class")=="huanxi")
			   me->add_temp("apply/damage",me->query_skill("meinu-quanfa",1)/4);

		COMBAT_D->do_attack(me, target,0, 3);
		//me->set_temp("mnq",1);
		COMBAT_D->do_attack(me, target,0, 3);
		//me->delete_temp("mnq");
		COMBAT_D->do_attack(me, target,0, 3);
		me->add_temp("apply/attack",-me->query_skill("meinu-quanfa",1)/2);
	    me->add_temp("apply/damage",-me->query_skill("meinu-quanfa",1)/4);
		if (target->query("class")=="huanxi")
			   me->add_temp("apply/damage",-me->query_skill("meinu-quanfa",1)/4);
	}
	else COMBAT_D->do_attack(me, target,0, 3);
	if (me->query("neili")<neili && jiali>0) me->set("neili",neili-jiali/3);
}
int help(object me)
{
   write(WHT"\n美女拳法「"HBMAG"摄心"WHT"」："NOR"\n");
   write(@HELP
	美女拳法之摄心绝技乃是杨过熟读古墓九阴真经后结合
	美女拳的特点而创出的一招奇招。在刚出道时大散关之
	战，以弱冠之年大胜密宗法王传人达尔巴，成为当时的
	传奇。主要思路还是源自九阴真经的移魂大法，该大法
	融入美女拳后，结合美女靓丽的外形，对男性有额外的
	杀伤力和诱惑力。250级小飞。
	注意：同性间若后天容貌不如对方则会失效。公公无法
	施展此招。功力高深的密宗喇嘛、道士、大乘佛法、僧
	人效果弱些，遇到修欢喜禅者效果威力加倍。

	perform cuff.shexin
	
要求：
	最大内力 2500 以上；
	当前内力 800 以上；
	当前精力 500 以上；
	美女拳法等级 200 以上；
	基本掌法等级 200 以上；
	玉女心经等级 200 以上；
	激发且备拳法为美女拳法；
	激发招架为美女拳法；
	女性有优势，男性偏弱。
	
HELP
   );
   return 1;
}
