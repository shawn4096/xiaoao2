// luanhuan.c 太极拳「乱环诀」诀
// by snowman@SJ 26/11/1999
// Modified by snowman@SJ 24/05/2001
// Update By lsxk@hsbbs 2007/5/28

inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

#define TAIJI "/kungfu/skill/yinyun-ziqi/taiji"

int is_pfm() {return 1;}
int hurt(object,object,int,string,string);

string perform_name(){ return HIC"乱环诀"NOR; }

int perform(object me, object target)
{ 
        int damage = 1, ap, dp;
        string msg, force, str, tmpTJstr;

	    if( !target ) target = offensive_target(me);

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「乱环诀」只能对战斗中的对手使用。\n");

	    if( userp(me) 
          &&( me->query_skill_mapped("parry") != "taiji-quan" && me->query_skill_mapped("parry") != "taiji-jian") )
          return notify_fail("「乱环诀」必须在用太极拳或太极剑激发招架的情况下才能使用。\n");
        if( me->query_skill_prepared("cuff") != "taiji-quan" )
                return notify_fail("你的内功或拳法不对，根本不能发挥出「乱环诀」的优势。\n");  
        if( me->query_skill("taiji-quan", 1) < 450 )
                return notify_fail("太极拳精要在于立如秤准，活如车轮，太极拳功力不到，又如何能使用「乱环诀」？\n");
		 if( me->query_skill("yinyun-ziqi", 1) < 450 )
                return notify_fail("太极拳精要在于内功，氤氲紫气功力不到，又如何能使用「乱环诀」？\n");
        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("你现在真气不够，强行使用「乱环诀」是发挥不了它的威力的！\n");                   
        if( me->query_temp("weapon"))
                return notify_fail("你先放下手中的武器再说吧？！\n");     
        

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target) 
        || me->query("neili") < 1000 || me->query("jingli") < 200 || me->query_temp("weapon"))
        	return 0;                    

	    if(intp(me->query_temp("tjq/"+target->query("id")) > 5))
		    me->add_temp("tjq/"+target->query("id"), -5);
	    else me->delete_temp("tjq/"+target->query("id"));
	              
        tmpTJstr = (string)me->query("env/六合劲"); 
        if(str != "钻翻" && str != "螺旋" && str != "软手" && str != "开合" && str != "静恒" && str != "虚灵")
        	str = "无";
        	
        msg = HIC"\n$N使出太极拳中"RED"「乱环诀」"HIC"的功夫，";
        
        if(me->query_skill("force", 1) < 100){
        	msg += "连划了几个圈子，罩住了$n！\n"NOR;
        	str = "无";
        }        
        
        else msg += "运起氤氲紫气，右肩斜闪，左手凭空划了几个圈子，套住$n，\n"+"欲其左则左，欲其右则右，"+
        "然后将一个个太极圆圈发出，以四两微力，拨动$p千斤巨力！\n"NOR;
        
        if((int)me->query_skill("taiji-quan",1)>350)
           damage = 2;
//550后出现super攻击，大器晚成
        if((int)me->query_skill("taiji-quan",1)>550){ 
            me->set("env/六合劲",TAIJI->check_force(target)); 
            str = me->query("env/六合劲");
            me->set_temp("tjq/super_lh",1);
        }

        if(TAIJI->check_force(target) == str )
        	damage = 3;
       
        me->start_perform(2, "「乱环诀」");
        if(!stringp(force = to_chinese(target->query_skill_mapped("force"))))
        	force = "内功";

        if(wizardp(me) && (string)me->query("env/combat")=="verbose")
		tell_object(me, "Str = "+str+"，Force = "+force+"，Damage = "+damage+"\n");

	    ap = me->query("combat_exp")/ 100000 * me->query_int(1);
	    dp = target->query("combat_exp")/100000 * target->query_int(1);

	    if ( target->is_busy())
		 dp -= dp/2;

	    if( random(ap + dp) > dp ){
           msg += HIC"结果$n身不由己，被推进了$P的无形圈内！\n"NOR;
           target->add_busy(2+random(2));
		   me->start_perform(2, "「乱环诀」");
           message_vision(msg, me, target);
           hurt(me, target, damage, str, force);
	     }
	
        else{
		msg += HIY"可是$p急中生智奋力一挣，竟然脱出了「乱环诀」的包围！\n"NOR;
		me->add("neili", -100);
		me->add("jingli", -50);
         message_vision(msg, me, target);
	    }


      if (me->query_temp("tjq/super_lh") ){
            me->add_temp("apply/attack", (int)me->query_skill("taiji-quan",1)/4);
			me->add_temp("apply/damage", (int)me->query_skill("taiji-quan",1)/6);
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
            me->add_temp("apply/attack", -(int)me->query_skill("taiji-quan",1)/4);
			me->add_temp("apply/damage", -(int)me->query_skill("taiji-quan",1)/6);
            if( (int)me->query("neili",1)> 800 ) me->add("neili",-800);
            else me->set("neili",0);
            me->delete_temp("tjq/super_lh");
            me->start_busy(1);
            me->start_perform(3, "「乱环诀」");
        }

        return 1;
}


int hurt(object me, object target, int damage, string str, string force)
{
        int p, j, m;
        float at;
        string msg;

	    if( !me || !living(me) || me->is_ghost() || !me->is_fighting()) return 0;
        if( !target || !target->is_character() || !me->is_fighting(target) || damage < 1
        || environment(target)!=environment(me) )
                return 0;        
        switch(str){
           case "钻翻": msg = HIC"$N双手左右连划，一个个圆圈层层叠叠已将$n的"+force+"扯开，太极拳的"HIW"「"+str+"劲」"HIC"随即使出！\n"NOR;break;
           case "螺旋": msg = HIC"但见$N双臂一圈一转，使出「六合劲」中的"HIY"「"+str+"劲」"HIC"，已将$n的护身"+force+"层层拨开！\n"NOR;break;
           case "软手": msg = HIC"$N双手轻灵似羽，在$n身前右捺左收，"HIM"「"+str+"劲」"HIC"使得犹如行云流水，潇洒无比地从$p"+force+"的空袭间穿过！\n"NOR;break;
           case "开合": msg = HIC"只见$N左掌阳、右掌阴，目光凝视左手手臂，竟然将$n的"+force+"慢慢拉开一个缺口，再又合拢，是凝重如山的"HIB"「"+str+"劲」"HIC"！\n"NOR;break;
           case "静恒": msg = HIC"$N右上左下双手半弧而住，$n只觉全身"+force+"都在$P双掌的"MAG"「"+str+"劲」"HIC"笼罩之下散开，已经无可闪避，无可抵御！\n"NOR;break;
           case "虚灵": msg = HIC"$N双手连划圆圈，虚灵顶劲，气沉丹田。不偏不倚，忽隐忽现，"HIG"「"+str+"劲」"HIC"潜进$n的"+force+"内层无极而生！\n"NOR;break;
           default: msg = HIC"$N左圈右圈，一个圆圈跟着一个太极圆圈发出，登时便套住$n！\n"NOR;break;
        }        
        
        if (target->query("neili") <= 1200){
			tell_object(target, "你猛然发觉自己真气已然枯竭耗尽，无法运劲相抗了！\n");
			msg += RED"结果只听一声巨响，$n被震得口中鲜血狂喷，全身骨骼碎裂，眼见是活不成了！！\n"NOR;
			target->receive_damage("qi", (int)target->query("qi")+1, me);
			msg += "( $n"+eff_status_msg(1)+" )\n";   
			message_vision(msg, me, target);
        return 1;
	}	
	
	else if(me->query("neili")*3 < target->query("neili")) {
		   me->start_busy(random(2));
           damage = (int)target->query_skill("force",1);
           damage = damage + random(damage);
                
		   me->receive_damage("qi", damage, me);
		   me->receive_wound("qi", damage/3, me);
		   target->add("neili", -damage/10);
                
     if( damage < 1000 ) msg += HIY"不料$P受到$p的内力反震，闷哼一声。\n"NOR;
          else if( damage < 2000 ) msg += HIY"不料$P被$p以内力反震，「嘿」地一声退了两步。\n"NOR;
          else if( damage < 4000 ) msg += RED"不料$P被$p以内力反震，胸口有如受到一记重锤，连退了五六步！\n"NOR;
          else    msg += HIR"不料$P被$p的内力反震，眼前一黑，身子向后飞出丈许！！\n"NOR;
          message_vision(msg, me, target);
          p = (int)me->query("qi")*100/(int)me->query("max_qi");
          msg += damage_msg(damage, "内伤") + "( $N"+eff_status_msg(p)+" )\n";    
          message_vision(msg, me, target);
		  me->start_perform(1, "「乱环诀」");
     if( !me->is_killing(target->query("id"))
		   && !target->is_killing(me->query("id"))
		   && !target->query("have_master")   // added by snowman
		   && me->query("qi")*2 <= me->query("max_qi")) 
			COMBAT_D->end_fight(target, me);
        	return 1;
	}        
	p = me->query_skill("force",1)*4;
	at = me->query("neili") / (target->query("neili")+1);

	if(at < 1){
        	if(at < 0.5) p /= 2;
            	p /= 2;
	}
	else p *= at;
	p *= damage;

	if( me->query_skill("taiji-quan", 1) > 400 ) 
		m = 5000 + ( me->query_skill("taiji-quan", 1) - 300 ) * 10 + random(500);
	else m = 5000;

	if( !userp(me) ) m = 5000;

	if( p > m ) p = m + (p-m)/15;
    if( p > 10000 ) p = p*2/3 + random(p/3) + 1;
    if( wizardp(me) ) tell_object(me, "你的「"HIC"乱环诀"NOR"」威力为： "+p+"。\n"NOR);

	target->receive_damage("qi", p, me);
	target->receive_wound("qi", p/2, me);

	if( target->query("neili") >= p/5 )
        	target->receive_damage("neili", p/5);
        else target->set("neili", 0);

        me->receive_damage("neili", 300);
        me->receive_damage("jingli", 120);
        
	if( p >= me->query_skill("taiji-quan", 1) * 10 )
           msg += HIR"太极之意连绵不断，有如自去行空，一个圆圈未完，第二个圆圈已生，喀喇一响，$p一处骨头被绞断！\n"NOR;
        	
        j = (int)target->query("qi")*100/(int)target->query("max_qi");
        msg += damage_msg(p, "内伤")+"( $n"+eff_status_msg(j)+" )\n"; 
        
        message_vision(msg, me, target);

        if (me->query_temp("tjq/super_lh") ){
          me->add_temp("apply/attack", (int)me->query_skill("taiji-quan",1)/4);
		  me->add_temp("apply/damage", (int)me->query_skill("taiji-quan",1)/6);
          COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		  COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
          if (userp(me)&&me->is_fighting())
          {
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
          }
		  
          me->add_temp("apply/attack", -(int)me->query_skill("taiji-quan",1)/4);
		  me->add_temp("apply/damage", -(int)me->query_skill("taiji-quan",1)/6);
          if( (int)me->query("neili",1)> 800 ) me->add("neili",-800);
          else me->set("neili",0);
          me->delete_temp("tjq/super_lh");
        }

        me->start_perform(2+random(3), "「乱环诀」");
        
        if( !me->is_killing(target->query("id"))
	       && !target->is_killing(me->query("id"))
	       && !me->query("have_master")   // added by snowman
	       && target->query("qi")*2 <= target->query("max_qi")) 
		   COMBAT_D->end_fight(me, target);
        return 1;
}

int help(object me)
{
	write(WHT"\n太极拳法之「乱环诀」："NOR"\n");
	write(@HELP
	使太极拳，双手凭空划圈，绵劲中蓄，一旦套住敌人双臂，便能运用六合劲
	震伤对方。此招数传直太极祖师张三丰，要旨是在左手所划的几个圆圈，对
	付内力低落的对手最是合适不过了。乱环诀主要要看双方的智力水平，智力
	高超之辈会将此招施展的行云流水。请注意，乱环诀和悟性有重大关联。
	注意：若六合劲设置得当，太极拳威力倍增。

	指令：perform cuff.luanhuan

要求：
	当前内力 2000 以上；      
	当前精力 1000 以上；
	太极拳法 450  以上；
	氤氲紫气 450  以上；
	运用太极拳且手无兵器。
HELP
	);
	return 1;
}
