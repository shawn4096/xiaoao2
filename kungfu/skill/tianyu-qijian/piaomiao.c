// 缥缈剑法
#include <ansi.h>
#include <combat.h> 
#include <skill.h>
string perform_name(){ return HBMAG"缥缈剑法"NOR; }
inherit F_SSERVER;

int perform(object me, object target)
{
    string dodge_skill,msg;
    int i, j;
    object weapon;

		 if( !target ) target = offensive_target(me);
     
		 if(!objectp(target) || !me->is_fighting(target) || !living(target)
			|| environment(target)!=environment(me))
                return notify_fail("「缥缈剑法」只能对战斗中的对手使用。\n");

 
		 if (me->query_skill_mapped("force") != "beiming-shengong")
			if (me->query_skill_mapped("force") != "bahuang-gong" )                
                return notify_fail("你的内功有误，无法使用「缥缈剑法」！\n");

		 if(!wizardp(me) && (int)me->query_skill("beiming-shengong", 1) < 400 )
       		if(!wizardp(me) && (int)me->query_skill("bahuang-gong", 1) < 400 )
                return notify_fail("你的内功还未练成，不能使用「缥缈剑法」！\n");

		 if((int)me->query_skill("force", 1) < 400 )
                return notify_fail("你的基本内功不够娴熟，无法支持「缥缈剑法」。\n");

		 if( (int)me->query_skill("tianyu-qijian", 1) < 400 ) 
                return notify_fail("你的剑法还未练成，不能使用「缥缈剑法」！\n");

		 if((int)me->query_skill("sword", 1) < 400 )
                return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用「缥缈剑法」。\n");

		 if((int)me->query_skill("dodge", 1) < 400 )
                return notify_fail("你的基本轻功不够娴熟，不能使用「缥缈剑法」。\n");

		 if (!objectp(weapon = me->query_temp("weapon")) 
			|| weapon->query("skill_type") != "sword")
                return notify_fail("你手里无剑，如何使用「缥缈剑法」？\n");
         if (me->query_skill_mapped("sword") != "tianyu-qijian"
			|| me->query_skill_mapped("parry") != "tianyu-qijian")
                return notify_fail("你没有激发天羽奇剑，如何使用「缥缈剑法」？\n");       
		 if((int)me->query("max_neili") < 10000 )
                return notify_fail("你最大内力不足，不能使用「缥缈剑法」！\n");

		 if((int)me->query("neili") < 1000 )
                return notify_fail("你现在真气不足，不能使用「缥缈剑法」！\n");

		 if((int)me->query("jingli") < 1000 )
                return notify_fail("你现在太累了，不能使用「缥缈剑法」！\n");

		 msg = HBMAG "$N贯通灵鹫宫武学，使出了灵鹫宫天羽奇剑的绝学之精髓！\n" NOR;
	    

		 message_vision(msg, me, target);          
         me->set_temp("tyqj/piaomiao", 1);

         message_vision(MAG"\n$N"+weapon->name()+MAG"微微晃动，当气势蓄至巅峰时，双眉耸竖，大步前跨，一股彻骨的剑气，立即潮涌而去。\n"NOR,me,target);
         i = me->query_skill("tianyu-qijian", 1);
         j = me->query_skill("sword", 1) ;
         
		 me->add_temp("apply/attack", j/2);
         me->add_temp("apply/damage", j/5); 
         
		 msg = HIC "$w"HIC"在$N用劲的指引下，忽似轻巧起来，破空之声反收至净尽，变成沉雄的呼啸，更增使人心寒胆落的威势！" NOR;  
         COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3,msg); 
         msg = HIG "$N挥剑起舞，一时剑气纵横，生出亦静亦动，静时有若波平如镜的大海，动时则似怒海激涛，变化莫测！" NOR;             
         COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3,msg);      
         msg = HIM "$N每一姿态都妙至毫巅，轻灵飘逸，闲雅清隽,和$n一沾即走，当真便似一对花间蝴蝶，蹁跹不定，于这“逍遥”二字发挥了到淋漓尽致！" NOR; 
         COMBAT_D->do_attack(me,target, me->query_temp("weapon"),3,msg);	

         me->add_temp("apply/attack", -j/2);
         me->add_temp("apply/damage", -j/5);
		 
		 message_vision(HIW"\n$N和$n这一交上手，但见一个娴雅清秀，宛如神仙，一个长袖飘飘，冷若御风，宛如花间蝴蝶。\n"
		                    +"这二人招招凶险，攻向对方要害，偏生姿式却如此优雅美观，直如舞蹈。\n"NOR,me,target);
	     if (random(me->query("combat_exp")) > target->query("combat_exp")/2 ){
		     message_vision(HIR"结果$n躲闪不及被$N攻了正着，" + weapon->name() + HIR"一剑刺向$n的胸口。\n"NOR,me,target);
			 target->reveive_damage("qi",target->query("qi")/3,me);
			 target->reveive_wound("qi",random(1000),me);
			 target->add_busy(1+random(2));
			}
	     else  {
			   message_vision(HIR"结果$n一个懒驴打滚躲过了$N的" + weapon->name() + HIR"刺向$n的胸口一招。\n"NOR,me,target);
               /*
			   dodge_skill = target->query_skill_mapped("dodge");
	           if( !dodge_skill ) dodge_skill = "dodge";
			   if (target) message_vision(SKILL_D(dodge_skill)->query_dodge_msg(target, 1), me, target);	
			   */
		   }
		
         weapon->unequip();

         me->add_temp("apply/strength", i/10);
         if (me->query("family/family_name") == "灵鹫宫")
			 me->add_temp("apply/damage",j/4);
         
		 message_vision(HIM"\n$N放下手中兵器，忽然施展出天山折梅手和天山六阳掌的招式，点、戳、缠、抓、捏、擒拿缤彩纷呈。\n"NOR,me,target);
         COMBAT_D->do_attack(me,target, me->query_temp("weapon"), userp(target)?3:1,msg);                                
         
		 message_vision(HIC"【弹 梅】"NOR, me, target); 
         COMBAT_D->do_attack(me,target, me->query_temp("weapon"),userp(target)?3:1,msg);                                     
         
		 message_vision(HIW"【落 雪】"NOR, me, target); 
         COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 3,msg);                                       
         message_vision(HIM"【散花香】\n"NOR, me, target); 
         me->start_busy(2);
         me->add_temp("apply/strength", -i/10);
         if (me->query("family/family_name") == "灵鹫宫") 
			 me->add_temp("apply/damage",-j/4);
         me->delete_temp("tyqj/piaomiao");
         weapon->wield();
         me->add("neili", -300);
         me->add("jingli", -300);
		 me->start_perform(4+random(3),"「缥缈剑法」");

		 return 1;
 }

int help(object me)
{
    write(WHT"\n天羽奇剑之「"MAG"缥缈剑法"WHT"」："NOR"\n");
         write(@HELP
	天羽奇剑乃是天山童姥绝学之一，因天山派
	渊源和逍遥派休戚相关，乃三大分支之一，
	所以天羽奇剑的意境含有天然的虚幻飘渺之
	意，看似风轻云淡，但其中却蕴藏无限杀机
		 
	天羽奇剑之绝技缥缈剑法，以虚无缥缈之意
	境连出三剑三掌。风雨雷电弹梅落雪散花香。
	
	perform sword.piaomiao

要求：
	八荒功的等级 400 以上;
	天羽奇剑等级 400 以上；
	基本剑法等级 400 以上；
	基本轻功等级 400 以上；
	最大内力需求 10000 以上
	当前内力需求 1000  以上
	当前精力需求 1000  以上
	激发剑法为天羽奇剑；
	激发招架为天羽奇剑；
	手持剑类武器；
HELP
    );
        return 1;
}
 