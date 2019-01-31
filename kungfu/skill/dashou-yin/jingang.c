// jingang.c 密宗大手印之金刚印
//By sohu@xojh

#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return HBYEL+HIR"金刚印诀"NOR; }

int perform(object me, object target)
{
	int damage;
	string msg;

		if( !target ) target = offensive_target(me);

		if( !target || !target->is_character() || !me->is_fighting(target) )
			return notify_fail("「金刚印」诀只能对战斗中的对手使用。\n");


		if( objectp(me->query_temp("weapon")) )
			return notify_fail("你必须空手才能使用「金刚印」诀！\n");		
		if((int)me->query_skill("longxiang-boruo",1)<100)
            return notify_fail("你的龙象般若功修为不够。\n");	
        if( (int)me->query_skill("dashou-yin", 1) < 100 )
			return notify_fail("你的密宗大手印修为不够，不能使用「金刚印」诀。\n");
        if((int)me->query("max_neili",1)<1000)
            return notify_fail("你的内力修为太差无法使用本势。\n");                        
        if( (int)me->query("neili", 1) < 500 )
			return notify_fail("你现在内力太弱，不能使用「金刚印」诀。\n");
		if (me->query_skill_mapped("hand")!="dashou-yin"
		||me->query_skill_prepared("hand")!="dashou-yin")
			return notify_fail("你没有激发，不能使用「金刚印」诀。\n");

		message_vision(RED "$N" RED "面容庄重，形如金刚，单手携着劲风朝$n" RED "猛然拍出，正是密宗绝学「"HIY"金刚印"NOR"」!\n" NOR,me,target);

		damage = 100+random((int)me->query_skill("dashou-yin",1)
			+(int)me->query_skill("longxiang-boruo",1)
			+(int)me->query_skill("poison",1));
                
		damage = damage*2 + random(damage);
        
		me->add("neili", -150);
 
		if (userp(target)) damage=damage/2;
       
		if (damage <1000) damage=1000;
		
		message_vision( RED"$N为这一掌掌风所压制，顿时气息不畅。\n" NOR,me,target);
	
		target->receive_damage("qi", damage,me);
		tell_object(me,"你对对方造成了"+damage+"点的伤害！\n");
		//target->receive_wound("qi", damage/3,me);
        
	
          
		if (random(me->query("combat_exp")) > target->query("combat_exp")/2
			||random(me->query_str())>target->query_str()/2)
		{
			damage = 1000+random((int)me->query_skill("dashou-yin", 1)
			+(int)me->query_skill("longxiang-boruo",1)
			+(int)me->query_skill("poison",1));
			if ( (int)me->query_str() > (int)target->query_con())
				damage = random( (damage*(int)me->query_str())/5 );
			else damage = damage + random(damage/2);
            
			if ( damage > 2500 ) damage = 2500 +random(1000); 

			target->receive_damage("qi", damage,me);
			target->receive_wound("qi", damage/3,me);
			tell_object(me,"连招发出，你对对方又造成了"+damage+"点的伤害！\n");

			me->add("neili", -150);
			
			if( damage < 1000 ) msg = HIY"$n气凝于手，挥掌抵御，将对手掌力悉数化解。\n"NOR;
        	else if( damage < 3000 ) msg = HIY"$n运气发力，与$N硬拼了一掌，虽不吃亏，但胸腹之间气血翻涌已极是不舒服。\n"NOR;
        	else if( damage < 5000 ) msg = RED"$n勉强以双手化解敌招，但觉$N内力如怒海狂涛源源而至，挟着一股热气直透$n胸臆！\n"NOR;
            else msg = HIR"$n不及闪避，被$N重重一掌正印中胸口膳中气海，$n只觉真气四散，口一张鲜血狂喷而出。\n"NOR;
			message_vision(msg, me, target);

		} else 
		{
            me->start_busy(3);

			message_vision(CYN"可是$p成竹在胸，两掌轻拍早将$P的掌力化为无形。\n"NOR,me,target);
		}
		me->start_perform(3,"金刚印");
		return 1;
}
int help(object me)
{
        write(HIY"\n密宗大手印「金刚印诀」："NOR"\n");
        write(@HELP
	密宗大手印绝技「金刚印诀」,能在战斗中呈怒目金刚势
	一掌挥出，宛如泰山压顶。给予对方强大且凌厉的攻击。
	灵智上人在同全真教抗衡过程中用过此招，甚是厉害
	纯粹是以雄浑的掌力来完成。
	
	指令：perform hand.jingang

要求：  
	当前内力 500 以上；      
	最大内力 1000 以上；
	当前精力 300 以上；  
	密宗大手印等级 100 以上；
	激发手法为密宗大手印
	备手法大手印；
	
HELP
        );
        return 1;
}

