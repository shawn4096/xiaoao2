// kong.c  
// by tiantian@sj 2000.6.19

#include <ansi.h>
inherit SKILL;
inherit F_SSERVER;
#include <combat_msg.h>
int hurt(object me,object target, int damage);
string perform_name(){ return HIW"空"NOR; }

int perform(object me,object target)
{
	
	int ap,dp,j;
	int damage;
	string msg;
    ap = me->query("combat_exp")/ 100 * me->query_str();
	dp = target->query("combat_exp")/100 * target->query_dex();
	damage = me->query_skill("cuff",1) + me->query_skill("kongming-quan",1)+me->query("jiali") * 2;	
	if (!target) target = offensive_target(me);
	if (!objectp(target)|!living(target) || !me->is_fighting(target))
		return notify_fail("“空”字诀只能在战斗中使用。\n");                
    if (me->query_temp("weapon"))
		return notify_fail("你手持兵器，不能使用“空”字诀。\n");     
	if (me->query_skill("kongming-quan", 1) < 350)
		return notify_fail("你的空明拳尚不纯熟，还不能使用“空”字诀。\n");        
	if (me->query("max_neili") < 5000)
		return notify_fail("你现在内力不足，不能使用“空”字诀！\n");
    if (!me->query("quest/jiebai/pass"))
        return notify_fail("你没有和周伯通结义，不能使用“空”字诀。\n");
	
	if (me->query_temp("kongming/kong"))
		return notify_fail("你正在使用“空”字诀！\n");      
//	if (me->query_temp("kongming/ming"))
//		return notify_fail("你正在使用“明”字诀！\n");      
	 message_vision(HIW"\n$N拳法互变，一拳打出，正是以柔克刚的绝顶武学，$n猛觉得对方拳力若有若无，自己掌力\n"
		+"使实了固然不对，使虚了也是极其危险，不禁暗暗吃惊。\n"NOR, me,target);
	

	if( random(ap + dp) > dp ){
		message_vision( HIY"\n$n见这招如棉如水，似乎力度不大，眼见$P攻来，下意识地意图封住$N这一拳！\n"NOR,me,target);
		me->add("neili", -100);
		me->add("jingli", -50);
		if (me->query("quest/hubo/pass")&&me->is_fighting()&&objectp(target))
		{
			call_out("hurt", 1, me, target, damage);	
		}
		else message_vision(HIC"\n$N没有领悟先天功以虚击实的奥秘，空字诀的威力施展不出，只好作罢。\n"NOR,me,target);
	}
	
	if( random(ap) > dp/3 ){
		
		target->receive_damage("qi", damage, me);
        target->receive_wound("qi", damage/4, me);
		if (wizardp(me))
		{
			write("damage="+damage);
		}
        j = (int)target->query("qi")*100/(int)target->query("max_qi");
		msg = HIR"结果重重的打在$n的胸口，登时鲜血狂喷。\n"NOR;
	    msg += "( $n"+eff_status_msg(j)+" )\n"; 
       // message_vision(msg, me, target);
        msg += damage_msg(damage, "内伤")+"( $n"+eff_status_msg(j)+" )\n"; 
		COMBAT_D->report_status(target,random(2));
        
		if(userp(me) && me->query("env/damage"))
		    tell_object(me,WHT"你对"+ target->query("name") +"造成了"RED+damage+ WHT"点攻击伤害。\n"NOR);
	
        if(userp(target)&& target->query("env/damage"))
		    tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"RED+damage+ WHT"点伤害。\n"NOR); 
	    me->add("neili", -150);
		me->add("jingli", -50);
	  }
 	   else {
		msg = HIY"可是$n陡然想起这路数正是名震江湖的空明拳，心中顿时明了，脚下一退，闪开了这招「空字诀」！\n"NOR;
	}
     message_vision(msg, me, target);
     //return 1;
	

	me->add("neili", -300); 
	
	if (!me->query("quest/hubo/pass"))
		me->start_perform(4,"“空”字诀");
	else 
	{
		me->start_perform(2,"“空”字诀");
        me->add_temp("apply/attack",me->query_skill("kongming-quan",1));
	    me->add_temp("apply/damage",me->query_skill("kongming-quan",1)/3);
	}
	me->set_temp("kongming/kong", 1);
	call_out("remove_effect",1,me,(int)me->query_skill("kongming-quan",1)/10);
	return 1;
}

int hurt(object me,object target, int damage)
{
    string msg;
	if ( ! me) return 0;

    if( !target || !target->is_character() )
                return 0;
    
	damage=me->query_skill("kongming-quan",1)+me->query_skill("xiantian-gong",1);
	damage=damage+me->query_skill("taoism",1);
	damage=damage*2;
	damage=damage*me->query_str()/10;
	
	if (userp(target)&&damage>3000) damage=3000+random(1000);
	
	if (damage>6000) damage=damage+(damage-6000)/10;
	
    msg = HIB"\n就在甚是得意之际，突然这空虚的拳法由虚转化为实，当即全身一震，气息翻腾！\n"NOR;
    if (me->query("neili")>target->query("neili")*3/2
		|| random(me->query_skill("xiantian-gong",1))>target->query_skill("force",1)/2)
    {
		  msg += RED"\n$N这一拳劲力传来，眼见即将滑过其身侧，哪知一股柔中带韧的拳风忽地迎面扑至，逼得他非倒退不可！！\n"NOR;
          me->set_temp("fanzhen",1);
		  target->receive_damge("qi",damage,me);
          target->receive_wound("qi",damage/3,me);
		  target->apply_condition("neishang", 1);
		  target->apply_condition("no_exert",1);
		  target->add_busy(1+random(2));
		  if (!userp(target))
		  {
			  target->add_busy(2+random(2));
		  }
	}
	else if( target->query("neili") <= 200 || target->query("qi") <= 500 ){
		   tell_object(target, CYN"你猛然发觉自己真气已然枯竭耗尽，无法运劲相抗了！\n"NOR);
		   msg += RED"结果只见$n猛地口中鲜血狂喷，全身骨骼相继为这柔性功力震碎碎裂，眼见是活不成了！！\n"NOR;
		   target->receive_damage("qi", (int)target->query("qi")+1, me);
		   target->set("eff_qi", 10);
           msg += "( $N"+eff_status_msg(1)+" )\n";   
	}
	
	else if( target->query_skill("force",1) > 450 ) 
		target->apply_condition("neishang",1);
	else target->apply_condition("neishang", 2);
	message_vision(msg, me);
    return 1;
}

void remove_effect(object me,int count)
{
	if (!me) return;
	
	if (!me->is_fighting()
		||me->query_skill_mapped("cuff")!="kongming-quan"
		||count<1)
	{
		if (me->query("quest/hubo/pass"))	
		{
			me->add_temp("apply/attack",-(me->query_skill("kongming-quan",1)));
			me->add_temp("apply/damage",-(me->query_skill("kongming-quan",1)/3));
		}
		me->delete_temp("kongming/kong");
		tell_object(me, HIW"\n你缓缓呼出一口浊气，真气流转，将内力纳入丹田。\n"NOR);
		return;
	}
	call_out("remove_effect",2,me,count--);
	
}
int help(object me)
{
	write(WHT"\n空明拳之「空字诀」："NOR"\n\n");
	write(@HELP
	空明拳是天下至柔的拳术，是周伯通从《道德经》中化
	出来的，《道德经》中有言道：“兵强则灭，木强则折。
	坚强处下，柔弱处上。”又云：“天下莫柔弱于水，而攻
	坚强者莫之能胜，其无以易之。弱之胜强，柔之胜刚，
	天下莫不知，莫能行。那降龙十八掌却是武学中至刚至
	坚的拳术。空明拳之空字诀，看似是空，实际是以虚化
	实的高明口诀，阴柔无比。攻击性不强，但反击力度靠
	自身的实力。
	
	指令：perform cuff.kong

要求：
	最大内力 3000 以上；
	当前内力 1500  以上；
	当前精力 1500  以上；
	空明拳等级 350 以上；
	激发拳法招架为空明拳；
	备拳法为空明拳且空手。
	解开双手互博后可以自由使用。

HELP
	);
	return 1;
}
