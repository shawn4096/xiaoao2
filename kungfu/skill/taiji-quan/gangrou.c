// gangrou.c 太极拳「刚柔诀」诀
// by snowman@SJ 26/11/1999
// Modified by snowman@SJ 08/05/2001


inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

#define TAIJI	"/kungfu/skill/yinyun-ziqi/taiji"

int is_pfm() {return 1;}
string perform_name(){ return RED"刚柔诀"NOR; }

int perform(object me, object target)
{ 
	    if( !target ) target = offensive_target(me);

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「刚柔诀」只能对战斗中的对手使用。\n");

	    if( userp(me) 
        &&( me->query_skill_mapped("parry") != "taiji-quan"
        && me->query_skill_mapped("parry") != "taiji-jian") )
                return notify_fail("「刚柔诀」必须在用太极拳或太极剑激发招架的情况下才能使用。\n");
        if( userp(me) && (me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill_prepared("cuff") != "taiji-quan") )
                return notify_fail("你的内功或拳法不对，根本不能发挥出「刚柔诀」的优势。\n");  
        if(me->query_skill("taiji-quan", 1) < 350 )
                return notify_fail("太极拳精要在于立如秤准，活如车轮，太极拳功力不到，又如何能使用「刚柔诀」？\n");
		if(me->query_skill("yinyun-ziqi", 1) < 350 )
                return notify_fail("你的氤氲紫气功力不够，不能施展刚柔诀\n");
        if( (int)me->query("neili", 1) < 2500 )
                return notify_fail("你现在真气不够，强行使用「刚柔诀」是发挥不了它的威力的！\n");                   
        if( me->query_temp("weapon"))
                return notify_fail("你先放下手中的武器再说吧？！\n");     
         if( target->query_temp("tjq/gangrou"))
                return notify_fail("对方已经中了你的刚柔诀？！\n");     

        return (int)call_other( this_object(), "main", me, target);
}

int main(object me, object target)
{
    int damage = 1, j, ap, dp;
        string msg, str;

    if( !target ) target = offensive_target(me);


    if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target) 
        || me->query("neili") < 1000 || me->query("jingli") < 200 || me->query_temp("weapon")){
        	write("你目前用不了「刚柔诀」。\n");
		return 1;
        }                

	if( target->query_condition("neishang") ){
		write("对方已经身受内伤，你不必再用「刚柔诀」了。\n");
		return 1;
	 }
	if(intp(me->query_temp("tjq/"+target->query("id")) > 4))
		me->add_temp("tjq/"+target->query("id"), -4);
	else me->delete_temp("tjq/"+target->query("id"));
	              
    str = (string)me->query("env/六合劲"); 
    if(str != "钻翻" && str != "螺旋" && str != "软手" && str != "开合" && str != "静恒" && str != "虚灵")
        	str = "无";
        	
    msg = HIB"\n$N使出太极拳中"RED"「刚柔诀」"HIB"的功夫，";
        
    if(me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill("yinyun-ziqi", 1) < 350){
        	msg += "右手一翻，拍向$n！\n"NOR;
        	str = "无";
     }  
     else msg += "右手一掌拍向$n，中和元气，拳路随意所之，意之所向，变化犹龙！\n"
		+"人莫能测，运用在心，此是太极真诀！\n"NOR;
        
    if( TAIJI->check_force(target) == str || me->query_skill("taiji-quan", 1) > 350 )
        	damage = 2;
       
    if (me->query_skill("taiji-quan",1)<450)
    {
	   me->start_perform(2, "「刚柔诀」");
	   me->start_busy(1);
     } 
	me->add("neili", -100);
	me->add("jingli", -50);
	
	if(!target->is_busy()) target->start_busy(1+random(1));

	ap = me->query("combat_exp")/ 1000000 ;
	dp = target->query("combat_exp")/1000000 ;
    //开了太极后会增加伤害
	if (me->query("taiji/pass"))
    {
		ap *=2;
		damage *=2;
    }
	if( random(ap + dp) > dp ||random(me->query_str(1))>target->query_con(1)/2){
		msg += HIY"$n眼见$P攻来，嘿嘿一笑，抬手就封住了$N这一掌！\n"NOR;
		me->add("neili", -100);
		me->add("jingli", -50);
		target->set_temp("tjq/gangrou",1);
		call_out("hurt", 0, me, target, damage);	
	}
	else if( random(ap) > dp/3 ){
		damage *= (me->query_skill("cuff") + me->query("jiali")) * 2;
		target->receive_damage("qi", damage, me);
        target->receive_wound("qi", damage/2, me);
        j = (int)target->query("qi")*100/(int)target->query("max_qi");
        msg += damage_msg(damage, "内伤")+"( $n"+eff_status_msg(j)+" )\n"; 
        if(userp(me) && me->query("env/damage"))
		   tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR);
	
    if(userp(target)&& target->query("env/damage"))
		   tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR); 
	    me->add("neili", -150);
		me->add("jingli", -50);
	}
        else {
		msg += HIY"可是$p经验老到，脚下一退，闪开了「刚柔诀」！\n"NOR;
	}
        message_vision(msg, me, target);
        return 1;
}

int hurt(object me,object target, int damage)
{
        string msg;

		if ( ! me) return 0;

        if( !target || !target->is_character() )
                return 0;
                
        msg = HIR"\n突然$N全身一震，气息翻腾，原来是被「刚柔诀」左手的柔劲抚到了！\n"NOR;
        if( target->query("neili") <= 1000 || target->query("qi") <= 1000 ){
		tell_object(target, "你猛然发觉自己真气已然枯竭耗尽，无法运劲相抗了！\n");
		msg += RED"结果只见$N猛地口中鲜血狂喷，全身骨骼碎裂，眼见是活不成了！！\n"NOR;
		target->receive_damage("qi", (int)target->query("qi")+1, me);
		target->set("eff_qi", 10);
                msg += "( $N"+eff_status_msg(1)+" )\n";   
	}
	
	else if( target->query_skill("force") > 450 ) 
		target->apply_condition("neishang", 5+random(3));
	else target->apply_condition("neishang", 1);
	target->delete_temp("tjq/gangrou");
	message_vision(msg, target);
        return 1;
}

int help(object me)
{
	write(WHT"\n太极拳之"RED"「刚柔诀」："NOR"\n");
	write(@HELP
	使太极拳「刚柔诀」，其为气也，至大至刚，直养无害
	充塞天地，配义与道，端由集义，浑灏流行，自然一气
	轻如杨花，坚如金石，虎威比猛，鹰扬比疾。行同乎水
	流，止伴乎山立。伤敌于内，可破横练、气猛之对手。
	「刚柔诀」乃太极拳中阴阳变化的重要口诀，350后威力
	小飞，450后大飞。且该技能会成为太极拳重要的辅助进
	攻技能。注意：若六合劲设置得当，太极拳威力倍增。
	
	指令：perform cuff.gangrou

要求：	
	当前内力 2500 以上；
	太极拳法 350  以上；
	氤氲紫气 350  以上；
	最少精力 200 以上；      
	运用太极拳且手无兵器。
HELP
	);
	return 1;
}
