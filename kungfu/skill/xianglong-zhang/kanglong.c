// 亢龙有悔
// by snowman@SJ 16/10/99
// modify by looklove 2001.10.04
// Modify by lsxk@hsbbs 2007/7/2
// By Spiderii@ty 判断绝对有问题,我改了!
// 重新调整，作为著名武技
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
string perform_name(){ return HIR"亢龙有悔"NOR; }
int kanglong_attack(object me, int flag);

int perform(object me, object target)
{
    int tmp,damage,lvl;
   string msg;
 
   if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !me->is_fighting(target) 
         || !living(target)
         || environment(target)!=environment(me))
               return notify_fail("「亢龙有悔」只能对战斗中的对手使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("你必须空手才能使用「亢龙有悔」！\n");

	if( (int)me->query_skill("xianglong-zhang", 1) < 500 )
		return notify_fail("你的降龙十八掌还不够娴熟，使不出「亢龙有悔」绝技。\n");

	if( (int)me->query_skill("huntian-qigong", 1) < 500 )
		return notify_fail("你的混天气功等级还不够，使不出「亢龙有悔」绝技。\n");

	if( me->query_skill_mapped("force") != "huntian-qigong" )
		return notify_fail("你所用的内功不对，使不出「亢龙有悔」绝技。\n");

	if( (int)me->query_skill("force") < 500 )
		return notify_fail("你的内功等级不够，不能使用「亢龙有悔」。\n");

	if( (int)me->query_str(1) < 70 )
		return notify_fail("你的膂力还不够强劲，使不出「亢龙有悔」绝技。\n");

	if( me->query_skill_prepared("strike") != "xianglong-zhang"
	 || me->query_skill_mapped("strike") != "xianglong-zhang"
	 || me->query_skill_mapped("parry") != "xianglong-zhang")
		return notify_fail("你现在无法使用「亢龙有悔」！\n");

	if( (int)me->query("max_neili") < 15000 )
		return notify_fail("你现在内力太弱，使不出「亢龙有悔」。\n");

	if( (int)me->query("neili") < 3000 )
		return notify_fail("你现在真气太弱，使不出「亢龙有悔」。\n");

	if( (int)me->query("jingli") < 1500 )
		return notify_fail("你的精力不够，无法使用「亢龙有悔」绝技。\n");

	if( !me->query("kanglong/pass") )
		return notify_fail("你还没领悟到「亢龙有悔」的精髓，无法使用此招数攻击。\n");

   lvl = (int)me->query_skill("xianglong-zhang",1);
   tmp = 1 + (lvl-200)/10;
   if(tmp>18) tmp = 18;
   damage=tmp*lvl;
   damage=damage+random(damage);
   message_vision(HIY"\n$N叫道：「看招！」左腿微屈，右掌划了个圆圈，平推出去，正是降龙十八掌中的「亢龙有悔」。\n"+
   "初推出去看似轻描淡写，但一遇阻力，刹时之间连加"+ chinese_number(tmp)+ "道後劲，一道强似一道，重重叠叠。\n"+
   "直至无坚不摧，无强不破！\n"NOR,me);
//   if (userp(target)&& damage>5000)
      // damage=damage+(damage-5000)/10;
   me->start_perform(3+random(3), "「亢龙有悔」");
   me->receive_damage("neili", random(2000));
   //me->receive_wound("qi", damage/3);
   me->receive_damage("jingli", random(1000));
   if(((int)me->query("pur")>28 && random(3))
     ||random((int)me->query("combat_exp")) > (int)target->query("combat_exp")/2
    // ||random((int)me->query_str()) > target->query_con()/2
     ||random((int)me->query_skill("xianglong-zhang",1)) > (int)target->query_skill("parry",1)/2
     ||target->is_busy() ) {
       damage = lvl*(tmp + (int)me->query_str()/10)/2;
       if(me->query("gender")!="男性" || !userp(me)) damage = damage/3;
       if(wizardp(me)) write("damage is "+ damage + "!\n");
       if (target->is_busy())
           target->add_busy(2);
	   else target->start_busy(2+random(1));
	   target->receive_damage("qi", damage, me );
       target->receive_wound("qi", damage*2/3 , me);
       target->set_temp("xlz/kanglong1",1);
       msg = HIR"$n直被这一掌逼得退无可退，让无可让，重重地被击中胸口，口中鲜血狂喷！\n"NOR;
       msg += COMBAT_D->damage_msg(damage,"内伤");
       message_vision(msg,me,target);
       COMBAT_D->report_status(target, 0);
   }
   else{
       message_vision(HIC"$n哪里见过如此刚猛的掌法？连忙就地一滚，远远的躲了开去，只吓地连冒冷汗！\n"NOR,me,target);
       target->add_busy(2+random(2));
       target->delete_temp("xlz/kanglong1");
       me->start_perform(3, "「亢龙有悔」");
   }
   if(userp(me) && lvl>=450 && target->query_temp("xlz/kanglong1") && me->query("combat_exp") > target->query("combat_exp")/2)
       if(random((int)me->query_str()) > target->query_con()/2 || target->is_busy()){
         msg = HIW"这「亢龙有悔」之精要不在‘亢’字而在‘悔’字！$N这"+ chinese_number(tmp)+ "道後劲刚发出，便立即收了回来！\n"+
               "$n却哪里知道？只道是$N奋力一击，便下意识催动全身内劲与之抗衡，可这"+ chinese_number(tmp)+ "道後劲却突然凭\n"+
               "空消失，$n体内这股抗衡内劲却无法收回，顿时便被自己的这股内劲冲得眼前一黑，五脏六腑犹如炸开\n"+
               "一般难受，浑身劲力收不住，浑身乱窜，再也支持不住了！\n"NOR;
         message_vision(msg,me,target);
		 //call die...
         if((int)target->query("con")<16
           ||( random(me->query("str")) > target->query("con")*2/3
           && random(me->query("combat_exp")) > target->query("combat_exp")*2/3)){
               
			   target->set("eff_qi",-1);
               target->delete_temp("xlz/kanglong1");
               COMBAT_D->report_status(target,1);
               return 1;
         }
       damage = lvl*(tmp + 4 - (int)target->query("con")/10 + (int)me->query("str")/10)/2;
	  // if (userp(target)&& damage>8000)
	     // damage=damage+(damage-8000)/10;
       if(me->query("gender")!="男性") damage = damage/3;
       if(wizardp(me)) write("damage is "+ damage +"!\n");
       
	   target->receive_damage("qi", damage, me );
       target->receive_wound("qi", damage/2, me);
       
	   message_vision(COMBAT_D->damage_msg(damage,"内伤"),me,target);
       COMBAT_D->report_status(target, 0);
       //target->delete_temp("xlz/kanglong1");
      // return 1;
   }
   target->delete_temp("xlz/kanglong1");
   //return 1;
   //新增xlz 的辅助攻击
   tell_object(me, HIY"\n你缓缓将双掌提到胸前，内息在体内重重运转，浑天气功运功越来越快，丹田气游走全身，劲气汹涌澎湃。\n\n"NOR);
	me->set_temp("no_fight", 1);
	if (me->query_skill("xianglong-zhang",1)<450)
	{
		me->start_busy(random(2));
	}
	//me->start_perform(4, "「亢龙有悔」");
    
	call_out("kanglong_attack",1,me,2);
	return 1; 
}


int kanglong_attack(object me, int flag)
{
	object target;
	int i;

	if( !me ) return 0;

	me->delete_temp("no_fight");

	if( !living(me) || me->is_ghost() ) return 0;

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !living(target)
	 || !me->is_fighting(target)
	 || environment(target) != environment(me) ) {
		tell_object(me,"「亢龙有悔」只能在战斗中对对手使用。\n"); 
		return 1;
	}

	if( me->query_skill_prepared("strike") != "xianglong-zhang"
	 || me->query_skill_mapped("strike") != "xianglong-zhang"
	 || me->query_skill_mapped("parry") != "xianglong-zhang"
	 || me->query_temp("weapon")){
 		tell_object(me,"你现在无法使用「亢龙有悔」！\n"); 
		return 1;
	}

	if( me->query_skill_mapped("force") != "huntian-qigong" ) {
 		tell_object(me,"你所用的内功不对，无法使出「亢龙有悔」！\n"); 
		return 1;
	}

	if( objectp(me->query_temp("weapon")) ) {
 		tell_object(me,"你现在无法使用「亢龙有悔」！\n"); 
		return 1;
	}

	if( (int)me->query("neili") < 1500 ) {
		tell_object(me,"你现在真气不足，使不出「亢龙有悔」。\n");
		return 1;
	}

	if( (int)me->query("jingli") < 1000 ) {
		tell_object(me,"你现在精力不够，使不出「亢龙有悔」。\n");
		return 1;
	}

	if( (int)me->query_temp("xlz/xiao") ) {
		tell_object(me,"你已经开始了「降龙啸」。\n");
		return 1;
	}

	if( me->is_busy() ) {
		call_out("kanglong_attack", 1, me, 1);
		//me->set_temp("no_fight", 1);
		if( wizardp(me) ) tell_object(me,"你手忙脚乱自顾不暇，等待中...\n");
		return 1;
	}

	i = me->query_skill("xianglong-zhang", 1) + random(me->query_str(1));

	if( userp(target) ) i = i*2/3;

//	判断抗龙的威力等级
	if( !flag ) flag = 1;
	i /= flag;
//降龙掌乃是内力运使法门,彼身可以模拟招式,连内力都能模拟?
/*	
	if( me->query_temp("bishen_target") )
		target->set_temp("xlz/hanglong",1);
	else*/
		me->set_temp("xlz/hanglong", 1);

	me->add_temp("apply/attack", i);
	//me->add_temp("apply/strength", i);
	me->add_temp("apply/damage", i/2);
	me->add_temp("apply/strike", i/2);
	me->add_temp("xlz/py_power",1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	me->delete_temp("xlz/py_power");
	me->add_temp("apply/attack", -i);
	//me->add_temp("apply/strength", -i);
	me->add_temp("apply/damage", -i/2);
	me->add_temp("apply/strike", -i/2);

	me->delete_temp("xlz/hanglong");
	me->receive_damage("neili", 1000+random(500));
	me->add("jingli",-random(200));
	me->start_perform(3+random(2),"「亢龙有悔」");
	return 1;
}

int help(object me)
{
	write(YEL"\n降龙十八掌之「亢龙有悔」："NOR"\n");
	write(@HELP
	降龙十八掌乃是武林第一大帮丐帮的镇派两大绝技之一，讲究刚柔
	并济，当刚则刚，当柔则柔，轻重刚柔随心所欲，刚劲柔劲混而为
	一，劲力忽强忽弱，忽吞忽吐，从至刚之中生出至柔，天下阳刚第
	一，掌法之妙，天下无双，招招须用真力，说是外门武学中的巅峰
	绝诣，动作虽似简单无奇，但掌掌现神龙，招招威力无穷，招式简
	明而劲力精深的武功，精要之处，全在运劲发力，全凭劲强力猛取
	胜，当真是无坚不摧、无固不破，虽招数有限，但每出一掌均有龙
	吟虎啸之势、每出一招均具绝大的威力。
	降龙十八掌必须得到帮主的传授方可习得，而「亢龙有悔」乃是降
	龙掌所有招式的根基，懂得了这招，也就明白了降龙掌的精髓。
	
	指令；perform strike.kanglong

要求：	
	最大内力需求 15000 以上；
	当前内力需求 3000 以上；
	当前精力需求 1500 以上；
	降龙掌法等级 500 以上；
	混天气功等级 500 以上；
	需要加力至少 200 ；
	有效臂力需求 70 以上：
	激发掌法降龙掌；
	激发内功为混天气功；
	激发招架为降龙掌。
HELP
	);
	return 1;
}
