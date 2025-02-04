// dongjing.c 太极拳「动静诀」诀
// by snowman@SJ 02/03/2000
// Modified by snowman@SJ 24/05/2001

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

#define TAIJI                "/kungfu/skill/yinyun-ziqi/taiji"

int is_pfm() { return 1;}
string perform_name(){ return MAG"动静诀"NOR; }

int perform(object me, object target)
{ 
        if( !target ) target = offensive_target(me);

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「动静诀」只能对战斗中的对手使用。\n");

	    if( userp(me) &&( me->query_skill_mapped("parry") != "taiji-quan" && me->query_skill_mapped("parry") != "taiji-jian") )
                return notify_fail("「动静诀」必须在用太极拳或太极剑激发招架的情况下才能使用。\n");
        if( userp(me) && (me->query_skill_mapped("force") != "yinyun-ziqi"|| me->query_skill_prepared("cuff") != "taiji-quan") )
                return notify_fail("你的内功或拳法不对，根本不能发挥出「动静诀」的优势。\n");  
        if( me->query_skill("taiji-quan", 1) < 400 )
                return notify_fail("太极拳精要在于动急则急应，动缓则缓随，你的太极拳功力太低，又如何能使用「动静诀」？\n");
        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("你现在真气不够，强行使用「动静诀」是发挥不了它的威力的！\n");                   
        if( me->query_temp("weapon"))
                return notify_fail("你先放下手中的武器再说吧？！\n");     
        if( target->query_condition("no_exert") )
                return notify_fail("( 对方气息不匀，看来是已经不能施用内功了。)\n");
                        
        return (int)call_other( this_object(), "main", me, target);
}

int main(object me, object target)
{
        int damage = 1, ap, dp;
        string msg, force, str;

        if( !target ) target = offensive_target(me);

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target) 
        || me->query("neili") < 300 || me->query("jingli") < 100 || me->query_temp("weapon"))
                return 0;     
                
        if(intp(me->query_temp("tjq/"+target->query("id")) > 3))
                me->add_temp("tjq/"+target->query("id"), -3);
        else me->delete_temp("tjq/"+target->query("id"));
        
       str = (string)me->query("env/六合劲"); 
        if(str != "钻翻" && str != "螺旋" && str != "软手" && str != "开合" && str != "静恒" && str != "虚灵")
                str = "无";
                
        msg = MAG"\n$N使出太极拳中极高明之"RED"「动静诀」"MAG"的功夫，";
        
        if(me->query_skill_mapped("force") != "yinyun-ziqi"
        || me->query_skill("yinyun-ziqi", 1) < 100){
                msg += "突然一下冲到$n面前，试图要抓住$n！\n"NOR;
                str = "无";
        } 
        else msg += "静之则合，无过不及，随曲就伸，让$n搭住自己的双手！\n"NOR;
        
        if(TAIJI->check_force(target) == str || me->query_skill("taiji-quan", 1) > 450)
                damage = 3;
        
        //me->start_perform(4, "「动静诀」");

        if(!stringp(force = to_chinese(target->query_skill_mapped("force"))))
                force = "内功";
        
        if(wizardp(me) && (string)me->query("env/combat")=="verbose")
                tell_object(me, "Str = "+str+"，Force = "+force+"，Damage = "+damage+"\n");

	//ap = me->query("combat_exp", 1) * me->query_str(1)/1000;
	//dp = target->query("combat_exp", 1) * target->query_con(1)/1000;
	ap = me->query("combat_exp")/100000;
	dp = target->query("combat_exp")/100000;
	if (target->is_busy())
		dp -= dp/2;

	if ( random(ap) > dp/2 
		||random(me->query_dex(1))>target->query_dex(1)/2) 
	{
		msg += HBMAG+HIW"$p看着$P的动作慢吞吞的样子，心中不以为然，很随意的将手搭在$P的臂膀之上！\n"NOR;
		
		if (me->query_skill("taiji-quan",1)<550)
		{
			//me->start_busy(1);
			msg += YEL"$P太极拳尚未流畅自然，觉得有些迟缓！\n"NOR;
			me->start_perform(1, "「动静诀」");
		}
		target->add_busy(2);
		call_out("hurt", 1,  me, target, damage, str, force);  
	}
	else{
		msg += HIY"可$p毕竟感觉不对，马上退后放开了$P的手腕！\n"NOR;
	    me->start_perform(2, "「动静诀」");
		me->start_busy(1+random(1));
	}
	message_vision(msg, me, target);
        return 1;
}

int hurt(object me, object target, int damage, string str, string force)
{
        object weapon;
        string msg;
        int p, i;
        
        if( !me || !living(me) || me->is_ghost() || !me->is_fighting()) return 0;
        
        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || damage < 1
        || environment(target)!=environment(me) || !target)
                return 0;
        
        msg = MAG"\n太极者，无极而生；动之则分，静之则合！";
        switch(str){
                case "钻翻": msg += "$N双手一翻，反搭住$n，太极拳的"HIW"「"+str+"劲」"MAG"猛然冲开"+force+"使出，将$n一送，甩了出去！\n"NOR;break;
                case "螺旋": msg += "$N反手一旋，抓住$n，"HIW"「"+str+"劲」"MAG"透入$n护身的"+force+"一纽，抓起$p从肩背上甩了出去！\n"NOR;break;
                case "软手": msg += "$N将"HIW"「"+str+"劲」"MAG"一送，震散了$p的"+force+"，刚好又在$n要急力挣脱时一抖一放，让$p自己摔了一大交！\n"NOR;break;
                case "开合": msg += "$N双掌一分，带着"HIW"「"+str+"劲」"MAG"当胸撞$n，让$p的"+force+"来不及反应！\n"NOR;break;
                case "静恒": msg += "$N双掌不动，全身"HIW"「"+str+"劲」"MAG"催动，一下子就破掉了$n的"+force+"，还将$p震得站立不稳！\n"NOR;break;
                case "虚灵": msg += "$N立如秤准，活如车轮，运起"HIW"「"+str+"劲」"MAG"带动$n的"+force+"一送，让$p马步不稳，全力都打向空处！\n"NOR;break;
                default: msg = MAG"\n$N突然反手拉住$n双掌一送一震，氤氲紫气随心而发，劲力汹涌，顿时破了$p的内功气劲！\n"NOR;break;
        }    
        
    if (target->query("neili") <= 200){
                message_vision(msg, me, target);
                tell_object(target, "你发觉自己真气已然枯竭耗尽，根本无法相抗了！\n");
                target->receive_damage("qi", (int)target->query("qi")+1, me);
                msg = RED"结果$N措手不及，被自己的劲力震得头昏目眩，摇摇欲坠！\n"NOR;
                msg += damage_msg(target->query("max_qi"), "摔伤") + "( $N"+status_msg(5)+" )\n"; 
                message_vision(msg, target, target);
                //me->start_busy(random(2));
		return 1;
	}
        
	else if(me->query("neili")*3 < target->query("neili")) {
		me->start_busy(1);
		msg += HIR"不料$p内力雄厚，经验老到，顺势一冲，从$P身边擦过！！\n"NOR;   
		message_vision(msg, me, target);
		return 1;
	}

	p = (int)me->query_skill("taiji-quan",1)*3 + random(me->query_skill("force",1)*2);
	if (me->query_skill("taiji-quan",1)>450)
	   p*=3;
	if (me->query_skill("taiji-quan",1)>550)
	   p*=2;

	target->receive_damage("qi", p, me);
	target->receive_wound("qi", p/2, me);
	target->receive_wound("jing", me->query_int(1)*2 + me->query_dex(1)*2, me);
	msg += damage_msg(p, "摔伤")+
	"( $n"+eff_status_msg((int)target->query("qi")*100/(int)target->query("max_qi"))+" )\n"; 
        
	message_vision(msg, me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
    if(userp(me) && me->query("env/damage")) 
		tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+ p+ WHT"点攻击伤害。\n"NOR);
	
if(userp(target)&& target->query("env/damage")) 
		tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+ p+ WHT"点伤害。\n"NOR); 

	if(wizardp(me) && (string)me->query("env/combat")=="verbose") 
		tell_object(me, "Damage ="+p+"\n");

	if(random(2) == 1 && !wizardp(me)){
		if( !me->is_killing(target->query("id"))
		&& !target->is_killing(me->query("id"))
		&& !me->query("have_master")   // added by snowman
		&& target->query("qi")*2 <= target->query("max_qi")) 
			COMBAT_D->end_fight(me, target);
		return 1;
	}

	if(wizardp(me) && (string)me->query("env/combat")=="verbose") 
		tell_object(me, "Dongjing done.\n");
                
	force = target->query_skill_mapped("force");
/*
	switch(force) {
		case "huntian-qigong":
			if( intp(p = target->query_temp("htqg/powerup")) ){
				target->add_temp("apply/armor", - p*2);
				target->add_temp("apply/dodge", - p);
				target->delete_temp("htqg/powerup");
				tell_object(target, HIR"你的混天气功被氤氲紫气的「动静诀」一下震散，只得将内力收回丹田！\n"NOR);
				break;
			}
		case "yijin-jing":
			if( intp(p = target->query_temp("jingang_armor")) ){
				target->add_temp("apply/armor", - p);
				target->delete_temp("fanzhen");
				target->delete_temp("no_skill_hit_ob");
				target->delete_temp("jingang_armor");
				tell_object(target, HIR"你的「金刚不坏体神功」被一下震散，效应也相应地消失了！\n"NOR);
				break;
			}
		case "jiuyang-shengong":
			if( intp(p = target->query_temp("jiuyang/powerup")) ){
				target->add_temp("apply/armor", - p);
				target->add_temp("apply/dexerity", -p/2);
				target->delete_temp("jiuyang");
				target->delete_temp("no_skill_hit_ob");
				tell_object(target, HIR"你的「九阳神功」被一下震散，效应也相应地消失了！\n"NOR);
				break;
			}
		case "linji-zhuang":
			if( target->query_temp("ljz/riyue") ){
				target->delete_temp("ljz/riyue");
				tell_object(target, HIR"你的「日月」庄被一下震散，所聚天地之精气已散回日月之间！\n"NOR);
				break;
			}
			if( intp(p = target->query_temp("ljz/yinyang")) ){
				target->add("max_qi", - p);
				target->receive_wound("qi", p, "「阴阳」庄被破，脱力而");
				target->delete_temp("ljz/yinyang");
				tell_object(target, HIR"你的「阴阳」庄被一下震散，提升的效应也消失了！\n"NOR);
				break;
			}
			if( intp(p = target->query_temp("ljz/fengyun")) ){
				target->add_temp("apply/dexerity", - p);        
				target->delete_temp("ljz/fengyun");
				tell_object(target, HIR"你的「风云」庄被一下震散，略觉步履沉重了一些。\n"NOR);
				break;
			}
			if( target->query_temp("ljz/wuwo")){
				target->delete_temp("ljz/wuwo");
				tell_object(target, HIR"你的「无我」心法被一下震散，又恢复了原来的你！\n"NOR);
				break;
			}
		case "yinyun-ziqi":
			if( target->query_temp("tj/太极") ){
				target->delete_temp("tj/太极");
				tell_object(target, HIR"你在慌忙之中，太极不能连贯而行，效应也消失了！\n"NOR);
				break;
			}
		case "dulong-dafa":
			if( intp(p = target->query_temp("sld/wudi2") ) ){
				target->add_temp("apply/attack", - p);
				target->add("max_qi",- target->query_temp("sld/wudiqi"));
				target->add_temp("apply/armor", -target->query_temp("sld/wudi"));
				target->delete_temp("sld");
				if(target->query("eff_qi") > target->query("max_qi")) 
					target->set("eff_qi", target->query("max_qi"));
				tell_object(target, HIR"你给这「动静诀」一震，心神一松，再也支持不住了！！\n"NOR);
				if(random( target->query("qi")) < 100) 
					target->unconcious();
				break;
			}
			else if( intp(p = target->query_temp("sld/wudi")) ){
				target->add("max_qi",- target->query_temp("sld/wudiqi"));
				target->add_temp("apply/armor", -p);
				target->delete_temp("sld/wudiqi");
				target->delete_temp("sld/wudi");
				if(target->query("eff_qi") > target->query("max_qi")) 
					target->set("eff_qi",target->query("max_qi"));
				tell_object(target, HIR"你给这「动静诀」一震，心神一松，好象虚脱了一样，突然垮了下来！！\n"NOR);
				break;
			}
		case "hanbing-zhenqi":
			if ( intp(p = target->query_temp("hbzq/huti")) ){
				target->add_temp("apply/parry", -p);
				target->add_temp("apply/dodge", -p);
				target->delete_temp("hbzq/huti");
				tell_object(target, HIR"你给这「动静诀」一震，周身的寒气散尽，不再能起到保护的作用了。\n"NOR);
				break;
			}
			if( target->query_temp("ss/focus")){
				target->delete_temp("ss/focus");
				tell_object(target, HIR"你给这「动静诀」一震，周身的寒气渐渐的散去了。\n"NOR);
				break;
			}
			if( target->query_temp("ss/hb")){
				target->delete_temp("ss/hb");
				tell_object(target, HIR"你给这「动静诀」一震，手上的寒气渐渐的散去了。\n"NOR);
				break;
			}
		case "huagong-dafa":
			if( intp(p = target->query_temp("hgdf/judu")) ){
				target->add_temp("apply/armor", -p);
				target->delete_temp("hgdf/judu");
				tell_object(target, HIR"你给这「动静诀」一震，心神一松，所聚毒素全都垮了！！\n"NOR);
				break;
			}
			else if( intp(p = target->query_temp("hgdf/huadu")) ){
				target->add_temp("apply/dodge", -p); 
				target->add_temp("apply/armor_vs_force", -p/2);           
				target->delete_temp("hgdf/huadu");
				tell_object(target, HIR"你给这「动静诀」一震，心神一松，化毒所聚毒素全都垮了！！\n"NOR);
				break;
			}
		case "yunu-xinjing":
			if( target->query_temp("gm/xinjing") ){
				p  = target->query_temp("gm/xinjing");
				target->add_temp("apply/intelligence", -p/10);
				target->add_temp("apply/dexerity", -p/10);
				if ( target->query_skill("yunu-xinjing", 1) > 200 ){
					target->add_temp("apply/armor_vs_force", -p/5);
					if ( target->query("gender") == "女性") {
						target->add_temp("apply/dodge", -p/5);
						target->add_temp("apply/parry", -p/5);
						target->add_temp("apply/armor", -p/5);
					}
				}
				target->delete_temp("gm/xinjing");
				tell_object(target, HIR"你的「心经」字决被神功震散，效应也消失了！\n"NOR);
				break;
			}
		case "shenyuan-gong":
			if ( intp(p = target->query_temp("shenyuan")) ){
				target->add_temp("apply/parry", -p/3);
				target->add_temp("apply/dexerity", -p/5);
				target->delete_temp("shenyuan");
				tell_object(target, HIR"你给这「动静诀」一震，防守招式已经减弱了。\n"NOR);
				break;
			}
		case "xuantian-wuji":
			if ( target->query_temp("kl/riyue")){
				target->delete_temp("kl/riyue");
				tell_object(target, HIR"你给这「动静诀」一震，身前的气墙逐渐缩小，终于消失于无形。\n"NOR);
				break;
			}
			if ( intp( p = target->query_temp("kl/taxue")) ) {
				target->add_temp("apply/dodge", -p);
				target->delete_temp("kl/taxue");
				tell_object(target, HIR"立定了脚步，身法回复了正常！\n"NOR);
				break;
			}
		case "longxiang-boruo":
			if ( intp(p = target->query_temp("xs/shield")) ) {
				target->add_temp("apply/dodge", -p);
				target->add_temp("apply/armor", -p*2);
				target->delete_temp("xs/shield");
				tell_object(target, HIR"你被「动静诀」一震，脸上红光一闪，骨节啪啪轻响几声，散去了护体真气。\n" NOR);
				break;
			}
			if ( intp(p = target->query_temp("xs/longxiang")) ) {
				target->add_temp("apply/attack", -p);
				target->delete_temp("xs/longxiang");
				tell_object(target, HIR"你被「动静诀」一震，脸上紫气一闪，又恢复如常。\n" NOR);
				break;
			}
		case "qiantian-yiyang":
			if( intp(p = target->query_temp("dali_jing")) ){
				target->add_temp("apply/intelligence", -p);
				target->delete_temp("dali_jing");
				tell_object(target, HIR"你被「动静诀」一震，无法继续潜修了。\n" NOR);
				break;
			}
		case "guiyuan-tunafa":
			if ( intp(p = target->query_temp("tz/focus")) ){
				target->add_temp("apply/attack", p);
				target->add_temp("apply/damage", p/2);
				target->delete_temp("tz/focus");
				tell_object(target, HIR"你被「动静诀」一震，精神有些委顿，力道随即恢复常态。\n"NOR);
				break;
			}
		case "kurong-changong":
			if( intp(p = target->query_temp("pf_ku")) ){
				target->delete_temp("pf_ku");
				target->add_temp("apply/armor", -p/2);
				target->add_temp("apply/parry", -p/4);
				tell_object(target, HIR"你被「动静诀」一震，「枯」字大法立刻消散了！\n" NOR);
				break;
			}
			else if( intp(p = target->query_temp("pf_rong")) ){
				p = target->query_temp("pf_rong");
				target->delete_temp("pf_rong");
				target->add_temp("apply/strike", -p/4);
				target->add_temp("apply/damage",-p/5);
				tell_object(target, HIR"你被「动静诀」一震，「荣」字大法立刻消散了！\n" NOR);
				break;
			}
		case "bihai-chaosheng":
			if ( intp(p = target->query_temp("thd/maze")) ){
				target->add_temp("apply/armor", - (p/4));
				target->delete_temp("thd/maze");
                                if(weapon = target->query_temp("thd/maze_target") && weapon = target->query_temp("thd/mazed")){
					weapon->delete_temp("thd/mazed");
					weapon->add_temp("apply/dexerity", p/10);
					weapon->add_temp("apply/dodge", p/10);
					weapon->add_temp("apply/damage", p/10);
					tell_object(weapon, target->name() + "对你布的迷阵已经被"+me->name()+"的「动静诀」震散了。\n");
				}
				tell_object(target, HIR"你被「动静诀」一震，布的迷阵瞬间消散了！\n" NOR);
				break;
			}
	}*/
	i = random(me->query_skill("taiji-quan", 1)/20);
	if( i < 5) i = 5;
	if( i > 15 ) i = 15;
	if (me->query("quest/tjq/taiji")=="pass")
	{
		target->apply_condition("no_perform", i);
		target->apply_condition("no_exert", i);
	}else {
		if (!random(3)) 	target->apply_condition("no_perform", 1);
		else target->apply_condition("no_exert", 2);
	}
	if( !me->is_killing(target->query("id"))
	&& !target->is_killing(me->query("id"))
	&& !me->query("have_master")   // added by snowman
	&& target->query("qi")*2 <= target->query("max_qi")) 
		COMBAT_D->end_fight(me, target);
	return 1; 
}

int help(object me)
{
	write(WHT"\n太极拳法之"+MAG"「动静诀」："NOR"\n");
	write(@HELP
	太极拳经讲：动之则分，静之则合。无过不及，随曲就伸。立如秤准，活如
	车轮，偏沉则随，双重则滞。动静诀便是一以静制动，以动制静之绝招，吸
	引对手进前，伺机反制，不但能创伤对手，还能有效地破除对方的各类内功。
	「动静诀」乃是太极拳中极为高明的武技，550后大飞，成为重要的辅助进攻
	技能，有概率破了对方内功的激发效果，并使得对方处于闭气状态。
	
	注意：该技能和经验值、悟性与身法有重大关联。

	指令：perform cuff.dongjing

要求：	
	当前内力 5000 以上；      
	当前精力 200  以上；
	太极拳法 400  以上
	运用太极拳且手无兵器。
HELP
	);
	return 1;
}
