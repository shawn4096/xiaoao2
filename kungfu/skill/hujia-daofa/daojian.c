//daojian.c 胡家刀法和苗家剑法的融合
//by sohu@xojh 12/10/2013

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
string perform_name(){ return HBBLU+HIW"剑刀双绝"NOR; }
int perform(object me, object target)
{
	
	int skill, skill1, skill2;
	object weapon,weapon2;
    object *inv;
    int i, count;
	string bei_skill;
	if( !target) target= offensive_target(me);
    //&& ! me->query("quest/hubo/pass")
    
	if(!me->query("quest/雪山飞狐/武功/ronghe"))
		return notify_fail("你尚未领悟刀剑融合，不能使用这招绝技！\n");

    if( !target 
         || !me->is_fighting(target)
         || !objectp(target)
		 || !living(target)
         || environment(target)!= environment(me))
		return notify_fail("雪山飞狐武技刀剑融合双绝只能对战斗中的对手使用。\n");

	
    if( me->query_skill_mapped("sword") != "miaojia-jianfa" || me->query_skill_mapped("blade") != "hujia-daofa")
		return notify_fail("必须通晓并备有胡家刀法和苗家剑法才能使用刀剑双绝！\n");

     
    if(me->query_skill("miaojia-jianfa",1) <500)
		return notify_fail("你的苗家剑法不够熟练，不能使用刀剑双绝！\n");

	if(me->query_skill("hujia-daofa",1) <500)
		return notify_fail("你的胡家刀法不够熟练，不能使用刀剑双绝！\n");
/*
	if( me->query_skill_mapped("force") != "lengquan-shengong" )
		return notify_fail("你所用的并非冷泉神功心法，无法施展刀剑双绝！\n");

	if( me->query_skill("lengquan-shengong", 1) < 500 )
		return notify_fail("你的冷泉神功火候未到，无法施展刀剑双绝！\n");
	*/	
	if( !objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "blade" )
		return notify_fail("必须持有刀才能使用刀剑双绝！\n");

     inv = all_inventory(me);
     for(count=0, i=0; i<sizeof(inv); i++) {
           if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
           if( inv[i]->query("skill_type") == "sword" ) 
		   {
			   weapon2 = inv[i];
			   break;
		   }
     }

	if( !objectp(weapon2) )
		return notify_fail("必须持有刀剑才能使用刀剑双绝！\n");

	if( me->query("neili") <= 1500 )
		return notify_fail("你的内力不够使用刀剑双绝！\n");
	if( me->query("jingli") <= 1500 )
		return notify_fail("你的精力不够使用刀剑双绝！\n");
	if( me->query("max_neili") <= 15000 )
		return notify_fail("你的最大内力不够使用刀剑双绝！\n");

	skill =  ( me->query_skill("sword",1) + me->query_skill("miaojia-jianfa",1)
		+ me->query_skill("hujia-daofa",1) +me->query_skill("blade",1) 
		+ me->query_skill("force",1)) / 5; 

	if (me->query_skill("lengquan-shengong",1))
	{	
		message_vision(HIC"$N"+HIC"将冷泉神功威力彻底发挥出来，左手"HIG"苗家剑法"+HIC"右手"+HIR"胡家刀法"HIC"，融会贯通，\n"+
		"身形飘逸洒脱，在冷泉神功的激发下，刀剑双绝威力大增！\n" NOR, me);		
		skill+=me->query_skill("lengquan-shengong",1)/4;
		me->add_temp("apply/strength",  skill/15);

	}else {
		message_vision(HIW"$N"+HIW"将自身功力激发，劲力汹涌，左手"HIG"苗家剑法"+HIW"右手"+HIR"胡家刀法"HIW"，融会贯通，\n"+
		"身形飘逸洒脱，左右趋避，动若脱兔，刀剑融合后的双绝威力陡然大增！\n" NOR, me);

	}
    me->set_temp("feihu/ronghe", 1);

	me->add_temp("apply/attack", skill/2);
	me->add_temp("apply/damage", skill/4);
	me->add_temp("apply/dodge",  skill/2);
	me->add_temp("apply/sword",  skill/4);
	me->add_temp("apply/blade",  skill/4);
	me->add_temp("apply/parry",  skill/4);

    bei_skill = me->query_skill_mapped("blade");

    if (skill>=500 && !userp(target) ) target->set_temp("must_be_hit",1);
	  //weapon->unequip();
	  weapon2->unequip();
	  me->map_skill("blade", "hujia-daofa");
	  weapon->wield();
	  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  //胡家刀法 

   if(me->is_fighting(target)) {
     me->map_skill("sword", "miaojia-jianfa");

	  weapon->unequip();
	  weapon2->wield();
	  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);  //苗家剑法
	
     }                               

   if(me->is_fighting(target)) {
      weapon2->unequip();
	  weapon->wield();
	  me->map_skill("blade", "hujia-daofa");

      COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);  //胡家刀法 
      
	 }

   if(me->is_fighting(target)) {
	  weapon->unequip();
	  weapon2->wield();
      me->map_skill("sword", "miaojia-jianfa");         

	  COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);   //苗家剑法
	}

//-------------------冷泉450飞------------------//
    if(me->query_skill("lengquan-shengong",1) >= 500)
     {

       if(me->is_fighting(target)) {
         weapon2->unequip();
	     weapon->wield();
		 me->map_skill("blade", "hujia-daofa");
         COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);         //苗家剑法
	   }
  
     if(me->is_fighting(target)) {
	     weapon->unequip();
	     weapon2->wield();
         me->map_skill("sword", "miaojia-jianfa");         

	     COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);   //胡家刀法
	    }
      }

      me->map_skill("blade", bei_skill);
	  weapon2->unequip();
	  weapon->wield();

	me->add("jingli", -random(400));
	me->add("jing", -100);
	me->add("neili", -random(1000));
	me->start_busy(1+random(2));
    
	if(target){
       target->start_busy(1+random(2));  
       target->delete_temp("must_be_hit");
	  }
	   me->add_temp("apply/attack", -skill/2);
	   me->add_temp("apply/damage", -skill/4);
	   me->add_temp("apply/dodge",  -skill/2);
	   me->add_temp("apply/sword",  -skill/4);
	   me->add_temp("apply/blade",  -skill/4);
	   me->add_temp("apply/parry",  -skill/4);
	   if (me->query_skill("lengquan-shengong"))
	   {
		   me->add_temp("apply/strength",  -skill/15);
	   }
	   
       me->delete_temp("feihu/ronghe");
       me->start_perform(6, "「刀剑双绝」");

	   message_vision(HIY "\n$N周身真气缓缓收入丹田，刀剑双绝收招！\n\n" NOR, me);

	return 1;
}

int help(object me)
{
        write(HIB"\n苗家剑法之「剑刀双绝」："NOR"\n");
        write(@HELP
		
	苗家剑法和胡家刀法各自称雄于武林，胡家刀法以刚猛著称，
	苗家剑法却以阴柔扬名，乃武林两大著名武功，后来胡斐在
	寻找杀父仇人的过程中，不断和苗人凤比试切磋，却发现这
	两门神功的攻防有互补之势，后来在苗人凤的点拨下恍然明
	白真相。这门刀剑双绝神功只有在深厚的冷泉神功支持之下
	才能发挥出极大的威力。
		
	指令;perform sword.daojian

要求：  
	最大内力 15000 以上；      
	当前内力 1500  以上；
	当前精力 1500  以上；
	胡家刀法等级 500 以上；
	苗家剑法等级 500 以上；
	基本内功等级 500 以上；
	激发剑法为苗家剑法；
	激发刀法为胡家刀法；
	手持剑类兵器，且身上带刀；
	内功不限；
                
HELP
        );
        return 1;
}