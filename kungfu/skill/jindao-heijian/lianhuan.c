//jindao-heijian 连环三刀
//by fqyy
/*
    这一刀当头直砍，招数似乎颇为呆滞，杨过只须稍一侧身，便可轻易避过，然而谷主黑
剑所划剑圈却笼罩住了他前后左右，令他绝无闪避躲让之处。杨过只得举起半截钢杖，一招
“只手擎天”，硬接了他这招。但听得当的一声巨响，刀杖相交，只爆得火花四溅，杨过双
臂只感一阵酸麻。公孙谷主第二刀连着又上，招法与第一刀一模一样。杨过武学所涉既广，
临敌时又是机灵异常，但竟无法破解他这笨拙钝重的一招，除了同法硬架之外，更无善策。
刀杖二度相交，杨过双臂酸麻更甚，心想只要再给他这般砍上几刀，我手臂上的筋络也要给
震坏了。思念未定，谷主第三刀又砍了过来。再接数刀，杨过手中的半截钢杖已给金刀砍起
累累缺口，右手虎口上也震出血来。
    公孙谷主见他危急之中仍是脸带微笑，左手一刀砍过，右手黑剑□地往他小腹上刺去。
杨过此时已给他逼在厅角，眼见剑尖刺到，忙伸手平掌一挡，剑尖刺中他掌心，剑刃弯成弧
形，弹了回来。原来小龙女的掌套甚是坚密，黑剑虽利，却也伤它不得。
*/

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>
void next1(object me, object target, int i);
void next2(object me, object target, int i);
int perform(object me,object target)
{
	int i;
	string msg;
	object *inv;
	object weapon2;
        object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);
		
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("连环三击只能对战斗中的对手使用。\n");
		if (!me->query_temp("jdhj/nizhuan"))
		{
			return notify_fail("金刀黑剑全凭一口气，你需运转金刀黑剑的逆转起手式。\n");
		}
        if( me->query("neili") <= 1000 )
                return notify_fail("你的内力不够使用连环三击！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力不够使用连环三击！\n");
        if( me->query_skill("sword",1) < 250 )
                return notify_fail("你剑法未到炉火纯青之境，还不会使用刀剑齐挥！\n");
        if( me->query_skill("blade",1) < 250 )
                return notify_fail("你刀法未到炉火纯青之境，还不会使用刀剑齐挥！\n");
        if( me->query_skill("jindao-heijian",1) < 250 )
                return notify_fail("你金刀黑剑未到炉火纯青之境，还不会使用剑圈封闭对方！\n");

        if (!weapon)
                return notify_fail("你手中无剑怎能使用连环三击？！\n");
     //   if (!me->query_temp("jindao-heijian/luanren",1)||!me->query_temp("jindao-heijian/nizhuan",1))
               // return notify_fail("你不使用“阴阳(perform yinyang)倒乱(perform nizhuan)刃法”怎么能用连环三击封住敌人行动！\n");

        if ( me->query_skill_mapped("sword") != "jindao-heijian"
          || me->query_skill_mapped("parry") != "jindao-heijian"
          || me->query_skill_mapped("blade") != "jindao-heijian"
          && userp(me))
             	return notify_fail("你必须先将黑剑金刀相互配合。\n");
       inv = all_inventory(me);
       for(i=0; i<sizeof(inv); i++) {
           if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
		if (weapon->query("skill_type") == "blade") {
        	   if( inv[i]->query("skill_type") == "sword" ) 
		   {
			   weapon2 = inv[i];
			   i = 3;
			   break;
		   }
		}
		if (weapon->query("skill_type") == "sword") {
   	        if( inv[i]->query("skill_type") == "blade" ) 
		   {
			   weapon2 = inv[i];
			   i = 2;
			   break;
		   }
		}
       }
	if (!objectp(weapon2)) return notify_fail("你只有一种兵器就想连环三击？\n");

	msg = HIM"$N这一刀当头直砍，招数似乎颇为呆滞，$n只须稍一侧身，便可轻易避过，\n"+
		"然而$N所划剑圈却笼罩住了他前后左右，令$n绝无闪避躲让之处。\n"NOR;
	me->start_perform(5,"「连环三击」");
	if((random(me->query_skill("jindao-heijian",1)) + me->query_int()) >
	(target->query_skill("dodge",1)/3 + target->query_int())) {
		msg = msg + HIR "$n只得一招“只手擎天”，硬接了$N这招。\n" NOR;
		target->add_busy(random(i*5) + 2);
	}
	else {
		msg = msg + HIW "可是$n看破了$N的企图，飞快的向后退去。\n" NOR;
		me->start_busy(2);
	}
	message_vision(msg, me, target);
	next1(me, target, i);
	return 1;
}

void next1(object me, object target, int i)
{
	string msg;
	int damage;
	object weapon;

	if (!me) return ;
	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		return ;
	}

	msg = HIG"\n$N第二刀连着又上，招法与第一刀一模一样。\n"+
		"$n武学所涉既广，临敌时又是机灵异常，但竟无法破解他这笨拙钝重的一招，除了同法硬架之外，更无善策。\n"NOR;

	if((random(me->query("max_neili")) + me->query_skill("force",1)) >
	    (target->query("max_neili") + target->query_skill("force",1))/3 ||(target->is_busy()&&random(2))){
		msg = msg + HIR"$N$n二度相拼，$n双臂酸麻更甚，只要再给$N这般砍上几刀，$n手臂上的筋络也要给震伤。\n"NOR;
		damage = me->query_skill("jindao-heijian",1);
		damage += me->query_skill("blade",1);
		damage += random(damage);
		if (!target->is_busy()) target->start_busy(damage/500);
		target->add("neili",-(500+random(150)));
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		msg += damage_msg(damage, "震伤");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "手臂");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-300);
		me->add("jingli",-100);
	} else {
		msg  =  msg + CYN"$n内力深厚硬生生接下了这一招。\n"NOR;
		message_vision(msg, me, target);
		me->start_busy(1+random(2));
		target->start_busy(1+random(2));
	}

	next2(me, target, i);

}

void next2(object me, object target, int i)
{
	string msg;
	int damage;
	object weapon;

	if( !me ) return ;

	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		return ;
	}

	msg = HIC "\n$n思念未定，$N第三刀又砍了过来。左手一刀砍过，右手剑法突地往$n小腹上刺去。\n"NOR;

	if((random(me->query("combat_exp")) + me->query_str()) >
	    (target->query("combat_exp") + target->query_str())/3 ||(target->is_busy()&&random(2))){
		msg = msg + HIW "$n此时已给$N逼在厅角，眼见剑尖刺到，忙伸手平掌一挡，剑尖刺中$n掌心！\n"NOR;
		damage = me->query_skill("jindao-heijian",1);
		damage += me->query_skill("sword",1);
		damage += random(damage);
		if (!target->is_busy()) target->start_busy(damage/500);
		target->add_temp("apply/attack", -100);
		target->add_temp("apply/dodge", -100);
		target->add_temp("apply/parry", -100);
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/3,me);
		msg += damage_msg(damage, "刺伤");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "手心");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-300);
		me->add("jingli",-150);
		call_out("back", 5 + random(me->query("jiali") / 20), target);
	} else {
		msg = msg + HIW "$n此时已给他逼在厅角，眼见剑尖刺到，忙伸手平掌一挡，剑尖刺中他掌心，\n$n内力深厚使得剑刃弯成弧形，弹了回来。\n" NOR;
		message_vision(msg, me, target);
		me->start_busy(1 + random(2));
		target->start_busy(1+random(2));
	}
}

void back(object target)
{
	if (!target) return;
	target->add_temp("apply/attack", 100);
	target->add_temp("apply/dodge", 100);
	target->add_temp("apply/parry", 100);
}
string perform_name(){ return HIR"连环三刀"NOR; }

int help(object me)
{
        write(HIC"\n金刀黑剑"+HIR"「连环三刀」"NOR"\n");
        write(@HELP
	金刀黑剑是情人谷公孙芷的家传武功，左手金刀右手黑剑
	金刀以劈砍切削之攻击，黑剑乃刺扎削之效果，金刀以刚
	性为主，黑剑以阴性为主，两者组合后会令人防不胜防。
	尤其是铁掌裘千尺嫁给公孙芷后，对这门武功去腐存精加
	以完善。更达到炉火纯青之境。但此门武技的缺点也是显
	然，正如裘千尺所言“难练易破”，存在致命缺点。
	铁掌弟子可以凭借身份解救裘千尺并获得裘千尺的指点，
	则此门功夫将更上层楼。
	金刀黑剑此时以刀主攻，完全是大开大合的路子，剑基本
	不用，仅仅以袭扰为主，此时攻击全部是强攻。
			
	指令：perform blade.lianhuan

要求：
	当前内力要求 1000 以上；
	当前精力要求 1000 以上；
	金刀黑剑等级 250 以上；
	基本剑法等级 250 以上；
	基本刀法等级 250 以上；	
	激发刀法为金刀黑剑。
	激发剑法为金刀黑剑。
	激发招架为金刀黑剑。
	激发内功不限；
	手持刀(剑)类武器并身上带对应配套武器。

HELP
        );
        return 1;
}
