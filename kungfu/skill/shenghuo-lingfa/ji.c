// ji.c 圣火令法--击
// By River@SJ
// Modified by snowman@SJ 26/04/2001
// bug bug bug fix by lane@SJ 看来益处的 pfm 不单这些啊

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
	 weapon=me->query_temp("weapon");
	 inv = all_inventory(me);
     for(count=0, i=0; i<sizeof(inv); i++) {
           if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
           if( inv[i]->query("skill_type") == "dagger" ) 
		   {
			   weapon2 = inv[i];
			   break;
		   }
     }

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("你只能对战斗中的对手使用「击」字诀。\n");

	if((int)me->query("neili") < 5000 )
		return notify_fail("你的内力不够。\n");

	if((int)me->query("jingli") < 3000 )
		return notify_fail("你的精力不够。\n");

	if((int)me->query_temp("shlf_ji"))
		return notify_fail("你已经用双令的双击来扰乱对方了。\n");

	skill = (int)me->query_skill("shenghuo-lingfa", 1);

	if(skill < 400)
		return notify_fail("你的圣火令法等级还不够。\n");

	if (!me->query_skill("jiuyang-shengong"))
	  if(me->query_skill("shenghuo-shengong", 1) < 400)
		return notify_fail("你的圣火神功等级还不够。\n");

	if(! weapon || !weapon2)
		return notify_fail("你没有武器如何实现彼此双击？\n");

	/*if( weapon->query_amount() < 2 && weapon->query("dagger_count") < 2 )
		return notify_fail("你只用一把令牌，怎么双击？\n");*/
	

	if ( me->query_skill_mapped("dagger") != "shenghuo-lingfa"
	 || me->query_skill_mapped("cuff") != "shenghuo-lingfa"
	 || me->query_skill_prepared("cuff") != "shenghuo-lingfa"
	 && userp(me))
		return notify_fail("你必须先将圣火令法功结合使用。\n");

	if( me->query_skill_mapped("parry") != "shenghuo-lingfa"
	&& me->query_skill_mapped("parry") != "qiankun-danuoyi")
		return notify_fail("你需要激发招架为圣火令法，方能使用此绝技。\n");

	me->add("jingli", -50);
	me->add("neili", -100);
	message_vision(HIY"\n$N飞身上前，双手将两柄"+weapon->query("name")+HIY"相互一击，铮的一声，声音非金非玉，十分古怪。\n"NOR,me);
	
	me->set_temp("shlf_ji", 1);
	checking(me,target);
	return 1;
}

int check_fight(object me, object target)
{
	object weapon;
	int skill;
	
	if (!me ||!me->query_temp("shlf_ji") || !living(me)){
		if( target) {
			skill= target->query_temp("ji");
			target->add_temp("apply/attack", skill/5);
			target->add_temp("apply/defense", skill/5);
			target->add_temp("apply/dodge", skill/5);
			target->delete_temp("ji");
			message_vision(HIW"\n$n耳边的噪音渐渐失去，神志又恢复了自然。\n"NOR,me,target);
			return 1;
		}
		return 1;
	}
	if (!target){
			me->delete_temp("shlf_ji");
			return 1;
	}
	me->delete_temp("shlf_ji");
	skill = me->query_skill("shenghuo-lingfa", 1);
	if(!weapon = me->query_temp("weapon")){
		if(target->is_busy()) target->start_busy(1);
		target->add_temp("apply/attack", skill/5);
		target->add_temp("apply/defense", skill/5);
		target->add_temp("apply/dodge", skill/5);
		message_vision(HIW"\n$N放下手中令牌，$n耳边的噪音失去，神志又恢复了自然。\n"NOR,me,target);
	}
	else if(environment(me) != environment(target)){
		if(target->is_busy()) target->start_busy(1);
		target->add_temp("apply/attack", skill/5);
		target->add_temp("apply/defense", skill/5);
		target->add_temp("apply/dodge", skill/5);
		message_vision(HIW"\n$N离开$n了，$n耳边的噪音失去，神志又恢复了自然。\n"NOR,me,target);
	}
	else if(!target->is_busy()){
		target->add_temp("apply/attack", skill/5);
		target->add_temp("apply/defense", skill/5);
		target->add_temp("apply/dodge", skill/5);
		message_vision(HIW"\n$n耳边的噪音渐渐失去，神志又恢复了自然。\n"NOR,me,target);
	}
	else if(!me->is_fighting(target)){
		if(target->is_busy()) target->start_busy(1);
		target->add_temp("apply/attack", skill/5);
		target->add_temp("apply/defense", skill/5);
		target->add_temp("apply/dodge", skill/5);
		message_vision(HIW"\n$N跳开战圈，$n耳边的噪音失去，神志又恢复了自然。\n"NOR,me,target);
	}
	else if (userp(me) && me->query_skill_mapped("dagger") != "shenghuo-lingfa"
	 || me->query_skill_mapped("cuff") != "shenghuo-lingfa"){
		if(target->is_busy()) target->start_busy(1);
		me->start_busy(1);
		target->add_temp("apply/attack", skill/5);
		target->add_temp("apply/defense", skill/5);
		target->add_temp("apply/dodge", skill/5);
		message_vision(HIW"\n$N不再用圣火令法攻击，$n耳边的噪音失去，神志又恢复了自然。\n"NOR,me,target);
	}
	else {
		me->set_temp("shlf_ji", 1);
		call_out("check_fight", 1, me, target, weapon);
		return 1;
	}
	return 1;
}

int checking(object me, object target)
{
	int time, skill, exp, exp1, ap, dp;

	skill = (int)me->query_skill("shenghuo-lingfa", 1);
	time = random(skill/20) + 4;
	exp = me->query("combat_exp");
	exp1 = target->query("combat_exp");

	ap = exp/100 * me->query_str()/2;
	dp = exp1/100 * target->query_con()/2;
    if (me->query_temp("mj/shenghuo"))
	  	skill = (int)me->query_skill("shenghuo-lingfa", 1)+(int)me->query_skill("shenghuo-shengong", 1);
	  
	if( wizardp(me) ) tell_object(me, "双方参数为："+ap+"："+dp+"。\n"NOR);
    
	if( random( ap + dp ) > dp 
		||random(me->query_str(1)>target->query_str(1)/2) ) {
		message_vision(HIR"只听见铮的一响，$n心神一荡，劲力顿时无法控制，从半空中直堕下来。\n"NOR,me,target);
        message_vision(HIY"$n受$N这双击嘈杂晦涩声音的影响，心中烦躁，浑身劲力翻涌，防御之力似乎受到削弱。\n"NOR,me,target);
		target->add_busy(time);
		target->set_temp("ji",skill);
		target->add_temp("apply/attack", -skill/5);
		target->add_temp("apply/defense", -skill/5);
		target->add_temp("apply/dodge", -skill/5);
		me->set_temp("shlf_ji", 1);
		me->add("neili", -200);
		me->add("jingli", -10);
		if (me->query_skill("shenghuo-lingfa",1)<450) me->start_busy(random(2));//增加大飞效果
		if (me->query_skill("shenghuo-shengong",1) < 450 || !me->query_temp("mj/shenghuo"))
		    me->start_perform(3, "「击」字诀"); //提高buff能力
			
		call_out("check_fight", 1, me, target);
	}
	else {
		me->start_busy(random(2));
		message_vision(CYN"$n心神一震，但随即恢复了神志，没被令牌双击之声所迷惑。\n"NOR,me,target);
		me->start_perform(2,"「击」字诀");
		me->delete_temp("shlf_ji");
	}
	return 1;
}

string perform_name(){ return HIY"双击诀"NOR; }

int help(object me)
{
	write(HIY"\n圣火令法之「双击诀」："NOR"\n\n");
	write(@HELP
	本武功源自波斯霍山老人，乃西域绝学。后传入中土
	走的是奇兵怪异路线，施展起来往往令人防不胜防，
	「击」字诀，乃是将浑身阴柔内力注入兵器中，利用
	内功的柔性带来兵器的颤动，领对方产生迷惑并大幅
	降低攻防的一种武技450后大飞，成为圣火令法的起
	手式。需要注意的是，倘若和圣火神功融合匹配，会
	出现令对手大幅降低攻防的意外结果。

	指令：perform dagger.ji

要求：
	当前内力需求 5000 以上；
	当前精力需求 3000 以上；
	圣火令法等级 400 以上；
	圣火神功等级 400 以上；
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
