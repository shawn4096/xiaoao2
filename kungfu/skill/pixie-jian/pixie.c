// pixie.c 群邪辟易 Created by action 2007/7/25

#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return HIB"群邪辟易"NOR;}

int perform(object me, object target)
{
        object weapon;
        int i,a,j;

        weapon = me->query_temp("weapon");
       
        if(!objectp(target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
		return notify_fail("你只能对战斗中的对手使用「群邪辟易」绝技。\n");
 
        weapon = me->query_temp("weapon");
        if (!weapon || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "pixie-jian")
                return notify_fail("手中无剑,你怎么使得出「群邪辟易」绝技！\n");

        if( (int)me->query_skill("pixie-jian", 1) < 500 )
                return notify_fail("你的辟邪剑法功力太浅，无法使出辟邪剑法之「群邪辟易」绝技！\n");

        if( (int)me->query_skill("sword", 1) < 500 )
                return notify_fail("你的基本剑法太差,无法使出「群邪辟易」绝技！\n");

        if( (int)me->query_skill("kuihua-shengong", 1) < 500)
                return notify_fail("你的特殊内功太差,无法使出「群邪辟易」绝技！\n");

        if(me->query_skill_mapped("force") != "kuihua-shengong" )
            return notify_fail("你的特殊内功不对，无法使用「群邪辟易」！\n");

        if( (int)me->query("max_neili") < 15000 )
               return notify_fail("你的内力修为太浅，无法使出「群邪辟易」！\n");

        if( (int)me->query("neili") < 2000 )
                return notify_fail("你的当前真气不够，无法使出「群邪辟易」功夫！\n");
		if( (int)me->query("jingli") < 1000 )
                return notify_fail("你的当前精力不够，无法使出「群邪辟易」功夫！\n");

        if (   me->query_skill_mapped("sword") != "pixie-jian"
	          || me->query_skill_mapped("parry") != "pixie-jian"
	          || me->query_skill_mapped("dodge") != "pixie-jian")
                return notify_fail("你不使用辟邪剑法,如何使得了「群邪辟易」！\n");                         
                     
        message_vision(HIM"\n$N手中的"+weapon->query("name")+HIM"突然一晃，满场游走，一身紫衫化成了一片紫影，一招「"+GRN+"群"+
           "邪辟易"+HIM+"」直刺$n。\n"NOR,me,target);  
        i = ((int)me->query_skill("pixie-jian",1)+(int)me->query_skill("kuihua-shengong",1))/2;
        j = i /3;

	    if ( i > 200 )
		j = to_int(i/100.0 * i/3.0);
        
        if ( me->query("quest/pixie/super") ) {
        	message_vision(HBMAG"\n经岳不群指导之后，你这招「"+GRN+"群邪辟易"+HBMAG+"」绝技，使将出来的威力更胜从前，已达绝境！\n"NOR,me,target);
        	me->add_temp("apply/sword",j/2);
        	me->add_temp("apply/damage",j);
          }
        else if(QUEST_D->queryquest(me,"kuihua/book")) {
        	message_vision(HIW "\n$N这招「"+GRN+"群邪辟易"+HIW+"」已得葵花宝典精要,此时使将出来,威力乃今非昔比!\n"NOR,me,target);
          } 
            me->add("jingli",-300); 
            me->add("neilili",-500); 
            me->add_temp("apply/attack", j*4/5);
	        me->add_temp("apply/sword", j*2/5);
	        me->add_temp("apply/damage", j/2);
		    me->set_temp("pixie",4);
        
		for(a=0;a<7;a++)
         {
		     if(random(2)) me->set_temp("pxj/pixie",1);

		     if (me->query_temp("pxj/pixie")&& me->query("quest/pixie/super")&& QUEST_D->queryquest(me,"kuihua/book"))
		     {
		         if(me->is_fighting(target))
		            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
              } else {
                       if(me->is_fighting(target))
                       COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
              }
             me->delete_temp("pxj/pixie");
            }
		   me->delete_temp("pixie");
		   me->delete_temp("pxj/pixie");
           me->add_temp("apply/attack", -j*4/5);
           me->add_temp("apply/sword", -j*2/5);
           me->add_temp("apply/damage",-j/2);
           me->start_perform(5+ random(1), "「群邪辟易」");
           if ( me->query("quest/pixie/super") ) {
        	me->add_temp("apply/sword",-j/2);
        	me->add_temp("apply/damage",-j);
          }
}


int help(object me)
{
   write(WHT"\n辟邪剑法「"HIG"群邪辟易"WHT"」："NOR"\n");
   write(@HELP
	日月神教乃江湖中重要的一大邪派组织，做事全凭个人好恶
	教中长老武技各有所长，这辟邪剑法乃是现任教主东方不败
	的绝技，后来江湖流传各种版本，但正宗辟邪剑法以轻巧、
	灵活、多变而著称。
	「群邪辟易」更是教主东方不败的得意绝技，招数平平而毫
	无花俏，但若能真正领会其真正剑意，再配合葵花神功，实
	乃江湖绝顶的功夫绝技！当然，倘若机缘巧合能得到岳不群
	的指点，辟邪剑的威力也将成为第一等大杀招！
    
	指令：perform sword.pixie

要求：
	当前内力 2000 以上；
	最大内力 15000 以上；
	当前精力 1000 以上；
	辟邪剑法 500 以上；
	基本剑法 500 以上；
	葵花神功 500 以上。
	激发内功葵花神功
	激发剑法辟邪剑法
	激发招架辟邪剑法
	激发轻功辟邪剑法
	需手持剑类武器；

HELP
   );
   return 1;
}
