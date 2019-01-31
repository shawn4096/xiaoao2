// 5lun_npc.c
// Created by snowman@SJ
// Modified by snowman@SJ 28/11/2000
// Modified by snowman@SJ 27/04/2001

#include <ansi.h>

inherit F_SSERVER;

string perform_name(){ return HIY"五轮大转"NOR; }

int perform(object me,object target)
{
            object obj, weapon,weapon2;
			int lvf,lvl;
			lvf=me->query_skill("longxiang-boruo",1);
            lvl=me->query_skill("xiangfu-lun",1);
    	weapon = me->query_temp("weapon");  
        
		if( !target ) target = offensive_target(me);
        
		if( !objectp (target) || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
             return notify_fail("「五轮大转」只能对战斗中的对手使用。\n");

  	    if ( (int)me->query_skill("longxiang-boruo", 1) < 350 )
        	 return notify_fail("你的内功等级不够，不能使用「五轮大转」。\n");
    
    	if ( (int)me->query_skill("xiangfu-lun", 1) < 350 )
        	 return notify_fail("你的金刚降伏轮法不够娴熟，使不出「五轮大转」。\n");
        if (target->query_temp("dazhuan"))
             return notify_fail("你正在使用「五轮大转」！\n");
    	if ( objectp(obj = me->query_temp("dazhuan_npc")) && present(obj, environment(me)) ) {
    		message_vision(HIC "\n$N将手一伸，轰轰之声大作，召回了飞舞着的五轮！\n"NOR, me);
    		obj->die();
			target->delete_temp("dazhuan");
    		me->start_perform(2 + random(2), "「五轮大转」");
        	return notify_fail("你收回了正在使用的「五轮大转」。\n");
        }
        
    	if (!weapon || weapon->query("skill_type") != "hammer"
         || me->query_skill_mapped("hammer") != "xiangfu-lun")
        	return notify_fail("你现在无法使用「五轮大转」。\n");
    	if( weapon->query_amount() < 5 
			//&& weapon->query("id") != "fenghuo lun" 
			&& weapon->query("hammer_count") < 5 )
        	return notify_fail("你需要五个轮子才能使用「五轮大转」。\n");
        if ( (int)me->query("max_neili") < 3800 )
        	return notify_fail("你现在内力太弱，不能使用「五轮大转」。\n");
    	if ( (int)me->query("neili") < 1000 )
        	return notify_fail("你现在真气太弱，不能使用「五轮大转」。\n");
        
    	if( me->query_skill_mapped("force") != "longxiang-boruo" )
        	return notify_fail("你目前的内功无法支持你使用「五轮大转」。\n");

    	message_vision(HIY "\n$N纵跃退後，立时呜呜、嗡嗡、轰轰之声大作，金光闪闪，银光烁烁，五只轮子从五个不同方位飞袭出来！\n"+
		HIG"※※※ "HIY"五 轮 大 转 "HIG"※※※ \n\n"NOR, me);
    	target->set_temp("dazhuan",1);
		if (me->query_skill("xiangfu-lun", 1) < 449)
		{
			me->start_busy(1);
            me->start_perform(3 + random(3), "「五轮大转」");
		}
		
    	me->receive_damage("neili", 300);
    	me->receive_damage("jingli", 100);  
        obj = new(__DIR__"5lun_npc");
    	if( obj->move(environment(me)) ){
    		me->set_temp("dazhuan_npc", obj);
			me->add_temp("apply/attack", lvl/5);
			if (weapon->query("id") == "fenghuo lun" )
			{
              me->add_temp("apply/attack", lvl/10);
              me->add_temp("apply/damage", lvl/10);
			  me->add_temp("apply/hammer", lvl/10);
			}
    		me->add_temp("apply/parry", 100);
    		me->add_temp("apply/armor_vs_force", 200);
                    if(weapon->query("id")=="fenghuo lun"){
                      weapon2 = new("/clone/weapon/5lun_weapon");
                      weapon2->move(obj);
                      obj->set_master_player(me, weapon2);
                     }
                    else{
                      weapon->unequip();
                      weapon->move(obj);
                      obj->set_master_player(me, weapon);
                    }
    	}
    	else write(HIR"\n「五轮大转」出错！请通知巫师： Obj cannot move to environment()\n\n"NOR);
    	return 1;
}

int help(object me)
{
        write(HIY"\n金刚降伏轮之「五轮大转」："NOR"\n");
        write(@HELP
	当年密宗金轮法王横扫西域，威镇草原，一手藏密金刚降伏轮
	使得出神入画！此「五轮大转」绝技乃法王得意之作，全由龙
	象之力以御气操作，法轮飞舞旋转，如飞龙降世，金刚开山！
	当世可挡之人寥寥无几！此招乃降伏轮中五轮飞转的绝技，需
	要高深内力配合且，龙象波若功达到九级方能施展。
	
	perform hammer.dazhuan
        
要求：
	龙象般若功法等级 350 以上；
	金刚降伏轮法等级 350 以上；
	最大内力的需求为 3800 以上；
	当前内力的需求为 1000 以上；
	激发锤法为降伏轮；
	激发招架为降伏轮；
	此招若从金轮法王处获得风火轮
	则威力更上一筹;
	手握五轮,450后飞跃。

HELP
        );
        return 1;
}


