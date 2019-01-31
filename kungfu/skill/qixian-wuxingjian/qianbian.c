// qianbian.c 任我行千变万化 之剑
// cre by sohu@xojh 6/6/2014

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int i, a,j,b,c;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target)
	 || !living(target) )
		return notify_fail("「千变万化」只能对战斗中的对手使用。\n");

	if( !me->query("quest/hmy/qxwxj/qianbian/pass") )
		return notify_fail("你虽然听说过千变万化，但却无法使用「千变万化」。\n");
 
        if( (int)me->query_skill("qixian-wuxingjian", 1) < 500 )
		   return notify_fail("你的七弦无形剑等级不足，无法使出「千变万化」。\n");
 
        if( (int)me->query_skill("sword", 1) < 500 )
		   return notify_fail("你的基本剑法等级不足，无法使出「千变万化」。\n");


        if( (int)me->query_skill("force", 1) < 500 )
		    return notify_fail("你的基本内功等级不足，无法使出「千变万化」。\n");

        if( (int)me->query("max_neili") < 15000 )
		   return notify_fail("你的内力修为太浅，无法使出「千变万化」。\n");

	    if( (int)me->query("neili") < 2000 )
		   return notify_fail("你的真气不足，无法使出「千变万化」。\n");
		
		if( (int)me->query("jingli") < 1000 )
		   return notify_fail("你的精力不足，无法使出「千变万化」。\n");

	  
     
	    if( !objectp(weapon = me->query_temp("weapon"))
	     || weapon->query("skill_type") != "sword"
	     || me->query_skill_mapped("sword") != "qixian-wuxingjian" )
	    	return notify_fail("你使得了「千变万化」么?\n");

        i = (int)me->query_skill("qixian-wuxingjian",1) +(int)me->query_skill("xixing-dafa",1) /2;
        
        me->add("neili",-800); 
        me->add("jingli",-300); 
		message_vision(HBYEL+RED"$N手中"+weapon->query("name")+HBYEL+RED"挥转，指向$n周身，乃守中带攻、攻中有守的妙着。$n一凛，只觉来剑中竟无半分破绽，\n"NOR,me,target);
        message_vision(HBYEL+RED"$n眼见$N剑法变化繁复无比，瞬间接连变换八门上乘剑法，有的攻势凌厉，有的招数连绵，有的小巧迅捷，有的威猛沉稳。\n"NOR,me,target);

		j=6;
		b=1;
		
		if (me->query("quest/hmy/qxwxj/qianbian/pass"))
		{
			j=12;
			b=3;						
		}

		me->set_temp("qxwxj/qianbian",j);
        
		me->add_temp("apply/attack", i/2);                 
		me->add_temp("apply/sword", i/2);
        if (me->query("quest/hmy/qxwxj/qianbian/pass"))
			me->add_temp("apply/damage", i/2);
		for(a=0;a<j;a++)
        {     	   
		        if (me->is_fighting() && objectp(target))
		        {
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), b);
		        }
                else
				{
                  	
					break;								
				}
			            
        }
		if (me->query("quest/hmy/qxwxj/qianbian/pass"))
			 me->add_temp("apply/damage", -i/2);
        
		me->add_temp("apply/sword", -i/2);
        me->add_temp("apply/attack", -i/2);		
		me->delete_temp("qxwxj/qianbian");
		
		message_vision(HIG+"$N忽感一阵气竭，剑招亦逐渐舒缓下来，随即趁势收招。\n"NOR,me,target);
		
        me->start_perform( 3 + random(2), "「千变万化」");
        me->start_busy(2);
        return 1;
}

string perform_name(){ return HIY"千变万化"NOR; }
int help(object me)
{
        write(HIB"\n七弦无形剑"+HIY"「千变万化」"NOR"\n");
        write(@HELP
	本武技源自令狐冲和任我行在梅庄地牢比剑那段描述。任我行期初
	以破绽极少的剑招和令狐冲打斗，但后来接连变换八门上乘剑法，
	有的攻势凌厉，有的招数连绵，有的小巧迅捷，有的威猛沉稳。招
	式乃是好剑招，若不是令狐冲身负独孤九剑，根本无法和任我行抗
	横，可见这门剑法的厉害之处。
要求：
	基本内功等级 500 以上；
	基本剑法等级 500 以上；
	七弦无形剑   500 以上；
	无需特定门派内功支持,
	吸星大法有额外加成。

HELP
        );
        return 1;
}

