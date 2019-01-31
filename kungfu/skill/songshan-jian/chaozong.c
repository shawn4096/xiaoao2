// chaozong.c 嵩山剑法 万岳朝宗
// modified by sohu@xojh 2013
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int skill,improve;

        if( !target && me->is_fighting() ) target = offensive_target(me);
      
         if( !target
         || !target->is_character()
	     || !living(target)
         || !me->is_fighting(target) )
                return notify_fail("「万岳朝宗」只能对战斗中的对手使用。\n");
		

        if( me->query("family/family_name") !="嵩山派" || !me->query("quest/ss/ssj/chaozong/pass") )
                return notify_fail("你没有得到嵩山剑法真传，无法使出这起手式「万岳朝宗」。\n");
        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "sword" )
                return notify_fail("你手中无剑，如何能够使出「万岳朝宗」？！\n");

        if( (int)me->query_skill("songshan-jian", 1) < 350 )
                return notify_fail("你的嵩山剑法不够娴熟，无法使出「万岳朝宗」。\n");
                
        if( me->query_temp("ssj/chaozong"))
                return notify_fail("你正在使用「万岳朝宗」！\n");

        if( (int)me->query_skill("hanbing-zhenqi", 1) < 350 )
			if( (int)me->query_skill("lengquan-shengong", 1) < 350 )
            return notify_fail("你的寒冰真气或冷泉神功火候不够，无法使出「万岳朝宗」！\n");

        if( me->query_skill_mapped("force") != "hanbing-zhenqi")
			if( me->query_skill_mapped("force") != "lengquan-shengong")
            return notify_fail("你的现在使用的内功不对，无法使出「万岳朝宗」！\n");    

        if (me->query_skill_mapped("sword") != "songshan-jian"
         || me->query_skill_mapped("parry") != "songshan-jian")
                return notify_fail("你现在无法使用「万岳朝宗」进行攻击。\n");

        if( me->query("max_neili") <= 3500 )
                return notify_fail("你的内力修为不足，劲力不足以施展「万岳朝宗」！\n");

        if( me->query("neili") <= 1500 )
                return notify_fail("你的内力不够，劲力不足以施展「万岳朝宗」！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力有限，不足以施展「万岳朝宗」！\n");

        message_vision(HBYEL+HIG"$N神情凝重，双手执剑，"NOR+weapon->name()+HBYEL+HIG+"剑尖朝下，剑柄超上，状若恭敬\n"+
		        "宛如与门中长辈请教一般，这正是嵩山剑法中最正宗的起手式"+NOR+HIR+"「万岳朝宗」，状甚谦恭！\n"NOR, me);
		if(userp(me)){
           me->add("neili", -300);
           me->add("jingli", -50);
        }
        skill = me->query_skill("hanbing-zhenqi")/2+me->query_skill("songshan-jian");
      	improve = skill/5 + random(skill/5);//原来是5
      	if ( improve > 100 ) improve = 100 + random(improve-100) / 5;

        me->set_temp("ssj/chaozong", improve);
		me->set_temp("ssj/chaozong1",1);
        me->add_temp("apply/parry", improve);
        //me->add_temp("apply/sword", improve);
        me->add_temp("apply/defense", improve);
        call_out("remove_effect", 1,  me, weapon, improve);
		//一招自动还手姿势。。
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		me->delete_temp("ssj/chaozong1");

        if (me->query_skill("songshan-jian",1)<450) me->start_perform(2, "「万岳朝宗」");
        return 1;
}

void remove_effect(object me,object weapon,int count)
{
        int i;
        if(!me) return;
        if(!me->is_fighting()
         ||!weapon
		 ||weapon->query("skill_type")!="sword"
         || me->query_skill_mapped("sword") != "songshan-jian"
         || me->query_skill_mapped("parry") != "songshan-jian"
         || count < 1 ){
          i = me->query_temp("ssj/chaozong");
          me->add_temp("apply/parry", -i);

          me->add_temp("apply/defense", -i);
          me->delete_temp("ssj/chaozong");
          message_vision(HIW"$N使完"NOR"「"HIR"万岳朝宗"NOR+HIW"」，嵩山剑法的防御功效逐渐消失。\n"NOR, me);
		  me->start_perform(3,"「万岳朝宗」");
		
  return;
        }
        else {
           call_out("remove_effect", 1, me, weapon, count -1);
        }
}              
string perform_name(){ return HIC"万岳朝宗"NOR; }

int help(object me)
{
        write(HIG"\n嵩山剑法之"+HIY"「万岳朝宗」："NOR"\n\n");
        write(@HELP
	“万岳朝宗”是嫡系正宗的嵩山剑法。这一招含意甚是恭敬，
	嵩山弟子和本派长辈拆招，必须先使用此招，意思是说并
	非敢和前辈动手，只是请您老人家指教的意思。此招施展
	后，嵩山剑法的防御将大大提升。
	
	指令：perform sword.chaozong

要求：
	当前内力需求 1500 以上；
	最大内力需求 3500 以上；
	当前精力需求 1000 以上；
	嵩山剑法等级 350 以上；
	寒冰真气等级 350 以上；
	基本剑法等级 350 以上；
	激发剑法为嵩山剑法；
	激发招架为嵩山剑法；
	需手持剑类武器；
	激发内功为寒冰真气。450后大飞。
HELP
        );
        return 1;
}
