// yunu-jianfa 玉女素心
// by dubei
// Modify By River 99.5.26
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string perform_name(){ return HBMAG+HIW"玉女素心诀"NOR; }
int perform(object me, string arg)
{
      object weapon, target;
      int dex,armor,skill;       
      dex = me->query_dex()*2;
      armor = me->query_int()*3;
      skill = me->query_skill("yunu-jianfa",1)/5;

	  if (me->query("gender") == "女性") skill *= 5/4; //女性互博威力增加
      weapon = me->query_temp("weapon");

      if( !target ) target = offensive_target(me);

      if( !target || !me->is_fighting(target) )
               return notify_fail("「玉女素心」只能在战斗中对对手使用。\n");

      if ( !weapon
        || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "yunu-jianfa" 
        || me->query_skill_mapped("parry") != "yunu-jianfa")
               return notify_fail("你没用玉女素心剑怎么使出「玉女素心」呢？别做梦了！\n");

      if((int)me->query_skill("yunu-jianfa", 1) < 350 )
               return notify_fail("你的玉女剑法修为不够 。\n");

      if((int)me->query_skill("sword", 1) < 350 )
               return notify_fail("你的基本功还不够娴熟，使不出「玉女素心」绝技。\n");

      if((int)me->query_dex() < 60)
               return notify_fail("你的身法还不够迅捷，使不出「玉女素心」绝技。\n");

      if((int)me->query_skill("yunu-xinjing", 1) < 350 )   
               return notify_fail("你的玉女心经修为不够，无法使用「玉女素心」绝技。\n");  
      if( me->query_skill_mapped("force") != "yunu-xinjing" && userp(me))
                return notify_fail("你现在无法使用「玉女素心」！\n");
      if((int)me->query_temp("gumu_suxin")) 
               return notify_fail("你现在正在使用「玉女素心」绝技。\n"); 

      if( me->query_temp("wujian") )
                return notify_fail("你正在使用「无剑胜有剑」呢！\n");
      if(me->query_temp("ynjf/suxin"))
               return notify_fail("你正在使用「玉女素心」绝技。\n"); 
      if((int)me->query_temp("ynxj/hebi"))
               return notify_fail("你正在施展双剑合壁，无法使用「玉女素心」绝技。\n"); 

      if((int)me->query("max_neili") < 5000)
               return notify_fail("你的内力修为不够。\n");

      if((int)me->query("neili") < 1500)
               return notify_fail("你的内力不够。\n");

      if((int)me->query("jingli") < 1500)
               return notify_fail("你的精力不够。\n");

       me->add("neili", -300);
       me->add("jingli", -150);
	   
    
	   if (me->query_temp("ynxj/xinjing")
		&& me->query("gender")=="女性"
		&& me->query("env/玉女剑法")=="素心")
	   {
		   skill=skill+me->query_skill("yunu-xinjing",1)/5;
	   }
 	   
       message_vision(HBMAG+HIW"\n$N信手一剑，极尽潇洒脱逸之妙，手中"+weapon->name()+HBMAG+HIW"幻化出无数虹芒，向$n电掣攻去。\n"
								+"\n$N的招式忽变，这显然已经是玉女心经中最后一章的武功招式了。\n"NOR,me,target);
	   
	   me->add_temp("apply/armor", armor);
       me->add_temp("apply/dexerity",dex);
       
	   me->add_temp("apply/attack", skill/4);
	   me->add_temp("apply/sword",skill/6);
	   
	   if (me->query("quest/hubo/pass"))
	   {
		   me->add_temp("apply/sword", skill/6);
		   me->add_temp("apply/damage", skill/6);
		   message_vision(HIW"\n$N已经对于双手互博的奥妙融会贯通，念头通达，功力随心而行，玉女素心剑威力爆发，顿时剑气纵横。\n"NOR,me,target);
		   //me->start_perform(1,"「玉女素心」");
	   }
	   me->set_temp("ynjf/suxin", skill); 
	

	   if (me->query_skill("yunu-jianfa",1) < 550)
	       me->start_perform(2,"「玉女素心诀」");
       call_out("check_fight", 1, me, dex, armor, skill);
       return 1;
}

void remove_effect(object me, int dex, int armor, object weapon)
{      
       int skill=me->query_temp("ynjf/suxin");
	   me->add_temp("apply/armor", -armor);
       me->add_temp("apply/dexerity",-dex);
	   me->add_temp("apply/attack", -skill/4);
	   me->add_temp("apply/sword",-skill/6);

	   if (me->query("quest/hubo/pass"))
	   {
		   me->add_temp("apply/sword", -skill/6);
		   me->add_temp("apply/damage", -skill/6);
		}
       me->delete_temp("ynjf/suxin");
       tell_object(me, HBMAG+HIW"你「玉女素心」施展完毕，缓缓舒了一口气。\n" NOR); 
}

void check_fight(object me, int dex, int armor, int skill)
{
       object weapon;
       if (!me) return;
       if(!objectp(weapon = me->query_temp("weapon"))
         || me->query_skill_mapped("sword") != "yunu-jianfa"
         || me->query_skill_mapped("parry") != "yunu-jianfa"
         || me->query_skill_mapped("force") != "yunu-xinjing"
         || weapon->query("skill_type") != "sword"){
           remove_effect(me, dex, armor, weapon);
           return;
       }
       if( skill < 1 || !me->is_fighting()) {
           remove_effect(me, dex, armor, weapon);
           return;
       }
       call_out("check_fight", 1, me, dex, armor, skill-1);
}
int help(object me)
{
        write(HIM"\n玉女剑法之"HBMAG+HIW"「玉女素心诀」："NOR"\n");
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
	境归纳为古墓绝技，【玉女素心诀】。
	玉女素心诀乃是玉女心经后半部的精要所在，重点
	是心无旁骛，心静如水。会短时间内大幅提升玉女
	剑法的威力。注意：女性比男性有优势,550后大飞。
		
	perform sword.suxin
	注意：set 玉女剑法 素心 女性有特殊加成
		
要求：
	最大内力要求 5000 以上；      
	当前内力要求 1500 以上；
	当前精力要求 1500 以上；
	玉女心经等级 350 以上；
	玉女剑法等级 350 以上；
	基本剑法等级 350 以上；
	有效身法等级 60  以上；
	激发剑法和招架为玉女剑法；
	手持剑类兵器。
	提示：若开的周伯通的双手互搏，
	素心诀威力将彻底释放；
                
                
HELP
        );
        return 1;
}