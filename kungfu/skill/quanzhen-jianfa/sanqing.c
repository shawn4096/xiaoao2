// by darken@SJ
// Modify By River@SJ 2001.6.18

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
string perform_name(){ return HIW"一剑化三清"NOR; }
int perform(object me, object target)
{
        int skill = me->query_skill("quanzhen-jianfa", 1);
        object weapon = me->query_temp("weapon");  
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("一剑化三清只能对战斗中的对手使用。\n");

        if( me->query_skill("force", 1) < 300 )
                return notify_fail("你的内功火候未到，无法施展一剑化三清！\n");
        if ( !weapon
			 || weapon->query("skill_type") != "sword"
			 || me->query_skill_mapped("sword") != "quanzhen-jianfa")
               return notify_fail("你现在无法使用一剑化三清。\n");
        if( me->query_skill("dodge") < 300 )
                return notify_fail("一剑化三清需轻功配合，方能施展！\n");

        if( me->query_skill("sword") < 300 )
                return notify_fail("你剑法火候未足，无法使用一剑化三清！\n");

        if( me->query("neili") < 500 )
                return notify_fail("你的内力不够使用一剑化三清！\n");
		if( me->query("max_neili") < 1500 )
                return notify_fail("你的最大内力不够使用一剑化三清！\n");
        if( me->query("jingli") < 500 )
                return notify_fail("你的精力不够使用一剑化三清！\n");
        if (me->query_temp("sanqing"))
        		return notify_fail("你正在使用一剑化三清！\n");
        if (me->query_temp("qzjf/sanqing"))
        		return notify_fail("你正在使用一剑化三清！\n");

       // if((int)me->query_temp("hebi"))
             //  return notify_fail("你正在施展双剑合壁，无法使用「一剑化三清」绝技。\n"); 

        if(!me->query_skill("xiantian-gong"))
          if(me->query_skill("yunu-xinjing", 1) < 200)
                return notify_fail("你的内功火候不够，无法使用一剑化三清。\n");

        if (!weapon 
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "quanzhen-jianfa"
		 || (me->query_skill_mapped("parry") != "quanzhen-jianfa" && me->query_skill_mapped("parry") != "kongming-quan" ))
                return notify_fail("你手中无剑怎能使用一剑化三清？！\n");

        msg = HIC"\n$N手中剑尖忽然极具颤动，随后一声清啸，使出全真剑法中的绝技一剑化三清，剑尖分成数点，刺向$n！宛如一招！\n" NOR;
       
		if (me->query("family/family_name")=="全真教")
    	{
			 
			skill=skill+me->query_skill("xiantian-gong",1)/5;
			
	    }		
		
		if (me->query("family/family_name")=="古墓派"
			&& me->query_skill("quanzhen-jianfa",1)<350
			&& me->query("gender")=="男性")
		{
			 msg += HIM"\n$N将玉女心经的阴柔功力附加在全真剑法中，这一剑化三清使来却也是有模有样！\n" NOR;
			 //target->start_busy(1+random(1));
			 skill=skill+me->query_skill("yunu-xinjing",1)/5;
		}
		message_vision(msg , me, target);
        
		me->set_temp("qzjf/sanqing",skill);
		me->add_temp("apply/attack", skill/3 );
        me->add_temp("apply/damage", skill/5 );
        me->add("neili", -300);
        me->add("jingli", -100);
        me->set_temp("sanqing1", 1);
		
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
        me->start_perform(3,"一剑化三清");
        me->delete_temp("sanqing1");
        
		me->add_temp("apply/attack", -skill/3 );
		me->add_temp("apply/damage", -skill/5 );

		//if (objectp(target)&&me->is_fighting())
       	call_out("check_fight", 1, me,(int)skill/30);

	//	else call_out("sanqing_finish",1,me);
        return 1; 
}
void check_fight(object me,int count)
{
    int skill;
	object target,weapon;

	if(!me) return;
	skill=me->query_temp("qzjf/sanqing");
	
	weapon=me->query_temp("weapon");
	
	target=offensive_target(me);

	if(!target
		|| !me->is_fighting()
        || !weapon
        || me->query_skill_mapped("sword") != "quanzhen-jianfa"
		|| me->query_skill_mapped("parry") != "quanzhen-jianfa"
        || count < 0 )
	{
                message_vision(HIW"\n这几剑一气呵成，剑意连环，剑势沉稳，一气化三清缓缓收功。\n\n"NOR, me);
                me->delete_temp("sanqing");
				me->delete_temp("qzjf/sanqing");
                me->add_temp("apply/attack", -skill/3);
                me->add_temp("apply/damage", -skill/5);
                return;
     }
     else {
              me->set_temp("sanqing", 1);
              me->add_temp("apply/sword", skill/5);
              message_vision(HIC"\n$N长吸一口气，迅捷刺出数招，这几剑一气呵成，剑意连环，剑势沉稳，取意道家一气化三清之意，乃是全真剑法中的精髓所在。\n\n"NOR, me);

			  if (me->query_skill("xiantian-gong", 1) > 350) 
				 {
				   if (me->is_fighting(target))
             	      COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);

			     }
             if (me->query_skill("xiantian-gong", 1) > 450) 
				 {
                   if (me->is_fighting(target))
             	     COMBAT_D->do_attack(me, target, me->query_temp("weapon"),userp(me)?3:1);
		 	     }
		     if (me->query_skill("xiantian-gong", 1) > 550) 
				 {
                   if (me->is_fighting(target)){
				     me->add_temp("apply/attack",me->query_skill("xiantian-gong",1)/10);
             	     COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
					 me->add_temp("apply/attack",-me->query_skill("xiantian-gong",1)/10);
					 }
				}
			 me->add_temp("apply/sword", -skill/5);

             me->delete_temp("sanqing");
             me->start_perform(3,"一剑化三清");
       }  
       call_out("check_fight", 2, me, count - 3);  
}

//结束函数
int sanqing_finish(object me)
{
	int skill;
	if (!me) return 0;

	skill=me->query_temp("qzjf/sanqing");
	
	me->add_temp("apply/attack", -skill/3 );
    me->add_temp("apply/damage", -skill/5 );
	me->delete_temp("sanqing");
	me->delete_temp("qzjf/sanqing",skill);
    message_vision(HIW"\n这几剑一气呵成，剑意连环，剑势沉稳，取意道家三清，乃是全真剑法中的精髓所在。\n\n"NOR, me);
	return 1;


}
int help(object me)
{
        write(HIG"\n全真剑法之"+HIW"「一气化三清」："NOR"\n\n");
        write(@HELP
	全真剑法是王重阳所创全真教的入门剑法，大道初修通九窍，
	又窍原在尾闾穴。先从涌泉脚底冲，涌泉冲起渐至膝。过膝
	徐徐至尾闾，泥丸顶上回旋急。金锁关穿下鹊桥，重楼十二
	降宫室。变化精微，与全真教的全真心法相得益彰。
	一气化三清，连续出招，每次都会三招连环不绝，为全真剑
	的厉害杀招。
	
	指令：perform sword.sanqing

要求：
	当前内力需求 500 以上；
	最大内力需求 1500 以上；
	当前精力需求 500 以上；
	全真剑法等级 300 以上；
	先天功法等级 300 以上；
	基本剑法等级 300 以上；
	基本轻功等级 300 以上；
	激发剑法为全真剑法；
	激发招架为全真剑法或空明拳；
	激发内功为先天功。
	手持剑类武器
	且全真弟子若以先天功激发，威力更甚。
HELP
        );
        return 1;
}
