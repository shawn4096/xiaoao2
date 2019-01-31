// songyangjue.c by darken@SJ
// Lklv@SJ modified 2001.10.22

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
int ssj_songyang(object me,int count);

int perform(object me, object target)
{
	int i,skill;
	object weapon = me->query_temp("weapon");
    skill=me->query_skill("songshan-jian",1);
	if( !target ) target = offensive_target(me);
   
	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("嵩阳诀只能对战斗中的对手使用。\n");
	
	if( me->query_skill("hanbing-zhenqi", 1) < 350 )
		return notify_fail("你的寒冰真气不够，无法施展嵩阳诀！\n");
	if( !me->query("quest/ss/ssj/songyang/pass"))
		return notify_fail("你没有得到左掌门的传授，无法施展嵩阳诀！\n");

	if( me->query_skill("songshan-jian", 1) < 350 )
		return notify_fail("你的剑法程度还不能使用嵩阳诀！\n");

	if( me->query_skill("songyang-shou", 1) < 350 )
		return notify_fail("你对大嵩阳手认识还不够！\n");

	if( me->query("neili") < 1500 )
		return notify_fail("你的内力不够使用嵩阳诀！\n");

	if( me->query("jingli") < 300 )
		return notify_fail("你的精力不够使用嵩阳诀！\n");

 	if (!weapon
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("sword") != "songshan-jian"
	 || me->query_skill_mapped("parry") != "songshan-jian" )
		return notify_fail("你必须使用嵩山剑法！\n");
	
	if( me->query_temp("ssj/songyang"))
		return notify_fail("你正在使用嵩阳诀！\n");

	    message_vision(HIY"\n$N长啸一声，剑法突变，施展出嵩阳剑法之「"HIC"嵩阳剑诀"HIY"」！\n" NOR, me);
		message_vision(HIY"\n嵩山剑法讲究的是厚重凝实，力大剑沉，招式雄浑，大开大合中蕴藏杀机！\n" NOR, me);

        if (!userp(target))
          i=skill+me->query_skill("hanbing-zhenqi",1)/6;

        
		me->add_temp("apply/attack", i/6);

        me->add_temp("apply/damage", i/6);

        me->add_temp("apply/sword", i/6);
		me->add_temp("apply/hand", i/6);
		me->add_temp("apply/strike",i/6);

	    me->set_temp("ssj/songyang", i);


		
 
		me->add("neili", -200);
		me->add("jingli", -100);

		call_out("ssj_songyang",1,me,(int)skill/40);
		return 1;
}

int ssj_songyang(object me,int count)
{
	int i;
	object target,weapon;

	if (!me) return 1;
	i=me->query_temp("ssj/songyang");
	weapon=me->query_temp("weapon");
	if (count<0
		||!weapon
		||weapon->query("skill_type")!="sword"
		|| me->query_skill_mapped("sword") != "songshan-jian"
		|| me->query_skill_mapped("parry") != "songshan-jian" 
		||!me->is_fighting())
	{
		me->add_temp("apply/attack", -i/6);
        me->add_temp("apply/damage", -i/6);
        me->add_temp("apply/sword", -i/6);
		me->add_temp("apply/hand", -i/6);
		me->add_temp("apply/strike",-i/6);


		me->delete_temp("ssj/songyang");
		message_vision(HIY"$N已经将嵩阳诀的心法发挥的淋漓极致，长吁一口气，缓缓收了剑势！\n"NOR,me);
		me->start_perform(2+random(2), "嵩阳诀");
		me->start_busy(random(2));

		return 1;
	}
	target=offensive_target(me);
	switch (random(7))
	{
		case 0:
			break;
		case 1:
			if( me->is_fighting()&& objectp(target)
				&&me->query_skill("songyang-shou", 1) > 350 
				&&me->query_skill_mapped("hand")=="songyang-shou" 
				&&me->query_skill_prepared("hand")=="songyang-shou" )  
			{
					target->add_busy(1);
					weapon->unequip();
					message_vision(CYN"\n$N默念嵩阳诀心法要旨，趁$n不注意间随手拍出一招「大嵩阳手」！\n" NOR, me,target);
					me->add_temp("apply/hand",i/4);
					COMBAT_D->do_attack(me, target,me->query_temp("weapon"),userp(me)?3:1);
					me->add_temp("apply/hand",-i/4);
         			weapon->wield();
			}
			break;
		case 2:
			if( me->is_fighting()&& objectp(target)
				&&me->query_skill("hanbing-shenzhang", 1) > 450 
				&&me->query_skill_mapped("strike")=="hanbing-shenzhang" 
				&&me->query_skill_prepared("strike")=="hanbing-shenzhang" )  
				{
					target->add_busy(1+random(1));
					weapon->unequip();
					message_vision(HIW"\n$N默念嵩阳诀心法要旨，纵身翻转$n身后，推出两掌「寒冰神掌」！\n" NOR, me,target);
					me->add_temp("apply/strike",i/4);
					COMBAT_D->do_attack(me, target,me->query_temp("weapon"),userp(me)?3:1);
					me->add_temp("apply/strike",-i/4);
         			weapon->wield();
				}

			break;
		case 3:
		case 4:
		case 6:
		default:
			break;
	
	}

	call_out("ssj_songyang",1,me,count--);

}



string perform_name(){ return YEL"嵩阳诀"NOR; }

int help(object me)
{
        write(HIW"\n嵩山剑法之「嵩阳诀」："NOR"\n\n");
        write(@HELP
	嵩山剑法有“内八路，外九路”之称，总共十七路长短快慢的剑法
	应有尽有。当年五岳剑派与魔教十长老两度会战华山，五岳剑派
	的好手死伤殆尽，五派剑法的许多惊世绝招随五派高手而消逝。
	嵩山派掌门左冷禅会集本派残存的耆老，将各人所记得的剑招不
	论粗精，尽数录了下来，汇成一部剑谱。
	嵩阳诀是嵩山剑法的心法类武技，是将嵩山的所有武功都融合在
	一起的必要心法辅助进攻武技，为嵩山派不传之秘,需向掌门请教

	指令；perform sword.songyang
	
要求：
	当前内力需求 1500 以上；
	当前精力需求 300 以上；
	嵩山剑法等级 350 以上；
	寒冰真气等级 350 以上；
	大嵩阳手等级 350 以上；
	激发剑法为嵩山剑法；
	激发招架为嵩山剑法；
	激发手法为大嵩阳手或寒冰神掌；
	且手持兵器。


HELP
        );
        return 1;
}
