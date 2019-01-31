// hebi.c 玉女剑与全真剑合壁左右互搏
//by sdong 07/98

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
string perform_name(){ return HIG"双手互搏"NOR; }
int perform(object me, object target)
{
	int skill, skill1, skill2;
	
	object weapon,weapon2;
       object *inv;
       int i, count,j;
	string bei_skill;

	if( !target) target= offensive_target(me);
    //&& ! me->query("quest/hubo/pass")
    if(!me->query("quest/gm/ynjf/hubo/pass") )
		return notify_fail("你尚未领悟左右互博绝技，不能双剑合壁左右互搏！\n");

    if( !target 
         || !me->is_fighting(target)
         || !objectp(target)
         || environment(target)!= environment(me))
		return notify_fail("双剑合壁左右互搏只能对战斗中的对手使用。\n");


	
	if( (int)me->query_temp("hubo") ) 
	{
		return notify_fail("你正进行双剑合壁左右互搏。\n");
	}

	if( (int)me->query_temp("hebi") ) 
	{
		return notify_fail("你正与人合壁，不能再进行双剑合壁左右互搏。\n");
	}


    if( me->query_skill_mapped("sword") != "yunu-jianfa" && me->query_skill_mapped("sword") != "quanzhen-jianfa")
		return notify_fail("必须通晓并备有玉女剑法与全真剑法才能双剑合壁左右互搏！\n");


	if(me->query_skill("quanzhen-jianfa",1) <500)
		return notify_fail("你的全真剑法不够熟练，不能双剑合壁左右互搏！\n");

	if(me->query_skill("yunu-jianfa",1) <500)
		return notify_fail("你的玉女剑法不够熟练，不能双剑合壁左右互搏！\n");

	if( me->query_skill_mapped("force") != "yunu-xinjing" )
		return notify_fail("你所用的并非玉女心经或先天功，无法施展双剑合壁左右互搏！\n");

	if( me->query_skill("yunu-xinjing", 1) < 500)
		return notify_fail("你的玉女心经火候未到，无法施展双剑合壁左右互搏！\n");
	
	if( !objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "sword" )
		return notify_fail("必须持有双剑才能合壁左右互搏！\n");

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
		return notify_fail("必须持有双剑才能合壁左右互搏！\n");
    if( me->query("max_neili") <= 15000 )
		return notify_fail("你的内力不够使用双剑合壁左右互搏！\n");
	if( me->query("neili") <= 2000 )
		return notify_fail("你的内力不够使用双剑合壁左右互搏！\n");
	
	if( me->query("jingli") <= 1000 )
		return notify_fail("你的精力不够使用双剑合壁左右互搏！\n");

	skill =  ( me->query_skill("sword",1) + me->query_skill("yunu-jianfa",1)
		+ me->query_skill("quanzhen-jianfa",1) +me->query_skill("yunu-xinjing",1) 
		+ me->query_skill("force")) / 5; 
	if (me->query("gender")=="女性"&&me->query("per")>29)
	{
		skill=skill+me->query_per(1);
	}

	message_vision(
	HIR "$N突然间左手抽出另一把剑，双手使出两种截然不同的剑法，正是左右互搏绝技。\n"
	+HBBLU+HIM"只见$N双剑一交，左右手玉女剑法与全真剑法配合得天衣无缝，攻拒击刺，宛似两大高手联手进攻一般，威力大增！\n\n" NOR, me);
    if (me->query("quest/jiuyingm/pass") && me->query("gender")=="女性")
	{ 
		me->add_temp("apply/attack", skill/4);
        me->add_temp("apply/damage", skill/6);
		me->add_temp("apply/sword", skill/6);
		message_vision(HIB"\n\n$N将自己所领悟的九阴真经和玉女心经最后一章武功彼此印证，豁然贯通！\n"NOR,me);
	}
	else me->add_temp("apply/attack", skill/7); //降低男性命中6改为7
	
	me->add_temp("apply/sword",  skill/3);
	me->add_temp("apply/damage", skill/4);
	me->add_temp("apply/dodge",  skill/3);
	me->add_temp("apply/parry",  skill/3);
	me->set_temp("hubo", 1);

	bei_skill = me->query_skill_mapped("sword");
    target->start_busy(2+random(2));
 
 if(me->is_fighting(target)) {
    me->map_skill("sword", "yunu-jianfa");
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if(weapon) weapon->unequip();
	weapon2->wield();
                                       }
 if(me->is_fighting(target)) {
    me->map_skill("sword", "quanzhen-jianfa");
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
		if(weapon2) weapon2->unequip();
	   if(weapon)	weapon->wield();
                                    }
 if(me->is_fighting(target)) {
    me->map_skill("sword", "yunu-jianfa");
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	if(weapon)	weapon->unequip();
	if(weapon2) 	weapon2->wield();
                                   }
 if(me->is_fighting(target)) {
    me->map_skill("sword", "quanzhen-jianfa");
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	if(weapon2)	 weapon2->unequip();
	if(weapon)	weapon->wield();
                                 }
 if(me->is_fighting(target)) {
    me->map_skill("sword", "yunu-jianfa");
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
	if(weapon)	weapon->unequip();
	if(weapon2)	 weapon2->wield();
                              }
 if(me->is_fighting(target)) {
    me->map_skill("sword", "quanzhen-jianfa");
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
                             }

    me->map_skill("sword", bei_skill);
   if(weapon2)	 weapon2->unequip();
   if(weapon)  weapon->wield();

	me->add("jingli", -100);
	me->add("jing", -100);
	me->add("neili", -300);
	me->start_busy(2+random(2));
    if(me->is_fighting(target))  target->start_busy(1+random(2));  
    
	if (me->query("quest/jiuyingm/pass")&&me->query("gender")=="女性")
    { 
		me->add_temp("apply/attack", -skill/4);
        me->add_temp("apply/damage", -skill/6);
		me->add_temp("apply/sword", -skill/6);
	}
	else me->add_temp("apply/attack", -skill/7);
	
	me->add_temp("apply/damage", -skill/4);
	me->add_temp("apply/dodge",  -skill/3);
	me->add_temp("apply/sword",  -skill/3);
	me->add_temp("apply/parry",  -skill/3);
    me->delete_temp("hubo");
	me->start_perform(5,"「左右互搏」");
	if(weapon)
	   message_vision(HIY "\n$N深吸了一口气，左手将"+"$n" + HIY "插回剑鞘，从容收招！\n\n" NOR, me,weapon);
    else 
   	   message_vision(HIY "\n$N深吸了一口气，从容收招！\n\n" NOR, me);
	return 1;
}
int help(object me)
{
        write(HIM"\n玉女剑法之「双手互博」："NOR"\n");
        write(@HELP
	玉女剑法乃一代女杰林朝英所创的独特剑法，不但
	剑招凌厉，而且讲究丰神脱俗，姿式娴雅，那玉女
	剑法果是全真剑法的克星，一招一式，恰好把全真
	剑法的招式压制得动弹不得，步步针锋相对，招招
	制敌机先，全真剑法不论如何腾挪变化，总是脱不
	了玉女剑法的笼罩。剑招凌厉，而且讲究丰神脱俗，
	姿式娴雅。飘身而进，姿态飘飘若仙。
	林朝英终其一生，郁郁不得志，将全副心思投入到
	玉女剑法的功夫之中，一招一式，一笑一颦均都融
	合到剑招之中，其中滋味难以诉说，后来将这种心
	境归纳为古墓绝技。
	小龙女自从周伯通哪儿习得左右互搏之术后，融汇
	贯通，终于领悟了古墓玉女心经最后一章的武功要
	义。全真剑法和玉女剑法双手使用，威力大增。
	注意：攻击力和容貌挂钩
		
	perform sword.hubo
		
要求：
	最大内力要求 15000 以上；      
	当前内力要求 2000 以上；
	当前精力要求 1000 以上；
	玉女心经等级 500 以上；
	玉女剑法等级 500 以上；
	基本剑法等级 500 以上；
	全真剑法等级 500 以上；
	有效身法等级 60  以上；
	激发剑法和招架为玉女剑法；
	激发内功为玉女心经；
	手持剑类兵器。
	提示：若解开的古墓九阴，威力再增，
	            
                
HELP
        );
        return 1;
}
