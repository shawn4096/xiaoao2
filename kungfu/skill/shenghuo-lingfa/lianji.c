// lianji.c 圣火令连击法
// cre by sohu@xojh
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int checking(object me, object target);
int perform(object me, object target)
{
	int skill,count,i;
	object weapon,weapon2;
	object *inv;
	 //判断是否有2把武器

	skill = (int)me->query_skill("shenghuo-lingfa", 1);

	if( !target ) target = offensive_target(me);
	 weapon=me->query_temp("weapon");
	 weapon2=target->query_temp("weapon");

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("你只能对战斗中的对手使用「连击技」。\n");

	if((int)me->query("neili") < 5000 )
		return notify_fail("你的内力不够。\n");

	if((int)me->query("jingli") < 3000 )
		return notify_fail("你的精力不够。\n");

	if((int)me->query_temp("shlf/lianji"))
		return notify_fail("你已经用双令的双击来扰乱对方了。\n");

	if(!me->query("quest/mj/shlf/lianji/pass"))
		return notify_fail("你只是听说过明教有此绝技，但并不会用。\n");
	if(skill < 500)
		return notify_fail("你的圣火令法等级还不够。\n");

	if (!me->query_skill("jiuyang-shengong"))
	  if(me->query_skill("shenghuo-shengong", 1) < 550)
		return notify_fail("你的圣火神功等级还不够。\n");

	if(!weapon
		||weapon->query("skill_type")!="dagger")
		return notify_fail("你没有武器如何实现彼此双击？\n");	

	if ( me->query_skill_mapped("dagger") != "shenghuo-lingfa"
	 //|| me->query_skill_mapped("cuff") != "shenghuo-lingfa"
	 //|| me->query_skill_prepared("cuff") != "shenghuo-lingfa"
	 && userp(me))
		return notify_fail("你必须先将圣火令法功结合使用。\n");

	if( me->query_skill_mapped("parry") != "shenghuo-lingfa"
	&& me->query_skill_mapped("parry") != "qiankun-danuoyi")
		return notify_fail("你需要激发招架为圣火令法，方能使用此绝技。\n");

	me->add("jingli", -1000);
	me->add("neili", -1500);
		message_vision(HBYEL+HIW"\n$N飞身上前，双手将两柄"+weapon->query("name")+HBYEL+HIW"挥舞,如刀、似匕、似凿、似剑。连续数招将$n笼罩在内。\n"NOR,me,target);
	
		me->set_temp("shlf/lianji", 12);
	  
		me->add_temp("apply/attack", skill/3);
		me->add_temp("apply/damage",skill/4);
		me->add_temp("apply/cuff",skill/4);
		me->add_temp("apply/dagger",skill/4);

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);          //第1招空手
		
		weapon->unequip();
		if (me->is_fighting()&& objectp(target))
		{
			me->add_temp("apply/cuff",skill/4);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);  //第2招空手
			me->add_temp("apply/cuff",-skill/4);
		}        
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);          //第3招空手
		weapon->wield();

		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);          //第4招空手
		if (me->is_fighting()&&objectp(target))
		{
			message_vision(HIG"$n向$N虚晃一招，左手倏地伸出，已抓住了$N左手的"+weapon->query("name")+HIG",猛然间一夺，岂知$N忽地放手。\n"NOR,me,target);
			
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);          //第5招空手
			if (weapon2 && random(me->query_str())>target->query_str()*2/3)
			{
				message_vision(HIB"$n只觉一股大力传来，手指酸麻，手中的"+weapon2->query("name")+HIB"把持不住，脱手而飞。\n"NOR,me,target);
				weapon2->move(environment(me));
			}

		}
		weapon->unequip();
		if (me->is_fighting()&&objectp(target))
		{
			message_vision(BLU"$n忽然低头，一个头锤向$N撞来，如此打法原是武学中大忌，竟以自己最要紧的部位送向敌人，\n"NOR,me,target);
			me->add_temp("apply/damage",skill/4);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);  		//第6招空手
			me->add_temp("apply/damage",-skill/4);
		}
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),random(3)?1:3);          //第7招空手
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);          //第8招空手
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);          //第9招空手
		if (me->is_fighting()&&objectp(target))
		{
			weapon->wield();
			message_vision(HIY"$N同时飞身而前，双手"+weapon->query("name")+HIY"相互一击，铮的一响，$n心神一荡，身子从半空中直堕下来，\n"NOR,me,target);
			message_vision(HIC"$n只觉的双耳一阵眩晕，顿时有些头昏脑涨，\n"NOR,me,target);

			target->apply_condition("no_exert",2);
			target->add_busy(1);
			target->add_temp("apply/attack",-skill/3);
			target->add_temp("apply/damage",-skill/5);
			call_out("target_back",5,me,target,skill);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);          //第10招空手
		}
		if (me->is_fighting()&&objectp(target))
		{
		weapon->unequip();
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);          //第11招空手
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);          //第12招空手		
		weapon->wield();
		}
		me->add_temp("apply/attack", -skill/3);
		me->add_temp("apply/damage",-skill/4);
		me->add_temp("apply/cuff",-skill/4);
		me->add_temp("apply/dagger",-skill/4);

		me->start_perform(6,"连击诀");
		me->add_busy(3);
		me->delete_temp("shlf/lianji");

	return 1;
}

int target_back(object me, object target,int skill)
{
	if (!target) return;
	message_vision(HIC"$N功力运转，将心中的烦躁和呕吐之意压制下来。\n"NOR,target);
	target->add_temp("apply/attack",skill/3);
	target->add_temp("apply/damage",skill/5);
	return 1;
}


string perform_name(){ return HBYEL+HIW"连击诀"NOR; }

int help(object me)
{
	write(HIY"\n圣火令法之「连击诀」："NOR"\n\n");
	write(@HELP
	本武功源自波斯霍山老人，乃西域绝学。后传入中土
	走的是奇兵怪异路线，施展起来往往令人防不胜防，
	「击」字诀，乃是将浑身阴柔内力注入兵器中，利用
	内功的柔性带来兵器的颤动，领对方产生迷惑并大幅
	降低攻防的一种武技450后大飞，成为圣火令法的起
	手式。需要注意的是，倘若和圣火神功融合匹配，会
	出现令对手大幅降低攻防的意外结果。

指令：perform dagger.lianji

要求：
	当前内力需求 5000 以上；
	当前精力需求 3000 以上；
	圣火令法等级 500 以上；
	圣火神功等级 500 以上；
	激发令法为圣火令法；
	激发拳法为圣火令法；
	激发招架为圣火令法或乾坤大挪移；
	备拳法为圣火令法；
	且手持两把匕首类兵器。
	450后呈现大飞效果.

HELP
        );
        return 1;
}
