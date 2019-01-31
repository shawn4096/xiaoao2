// dian.c 银索金铃 点穴
// keinxin@sj2 2003.4
// edit by sohu@xojh
#include <ansi.h>

inherit F_SSERVER;

string *xue_name = ({ 
"劳宫穴","膻中穴","曲池穴","关元穴","曲骨穴","中极穴","承浆穴","天突穴","百会穴",
"幽门穴","章门穴","大横穴","紫宫穴","冷渊穴","天井穴","极泉穴","清灵穴","至阳穴",
"涌泉穴","大锥穴","风府穴",
}); 
int perform(object me, object target)
{
	object weapon;
	object ob;		
	string msg,xue;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("「点穴」只能对战斗中的对手使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
		|| (string)weapon->query("skill_type") != "whip")
			return notify_fail("你使用的武器不对。\n");

	if( (int)me->query_skill("yinsuo-jinling", 1) < 300 )
		return notify_fail("你的银索金铃不够纯熟，还不能认穴\n");
	if( (int)me->query_skill("whip", 1) < 300 )
		return notify_fail("你的基本鞭法不够纯熟，还不能认穴\n");
	if( (int)me->query_skill("yunu-xinjing",1)< 300)
		return notify_fail("你的内功修为太差，劲力无法封闭穴道\n");
	
	if( (int)me->query("max_neili")<5000)
		return notify_fail("你的最大内力不足以施展点穴功夫.\n");
	if(target->is_busy())
		return notify_fail("对方已经陷入忙乱之中，放胆进攻吧.\n");
			
	if ( (int)me->query("neili") < 1500 )
		return notify_fail("你的当前内力不够点穴。\n");
	
	me->add("neili", - 300);
	xue = xue_name[random(sizeof(xue_name))];

	msg = HIW"$N"HIW"手上"+weapon->query("name")+HIW"飞出,使出银索金铃绝技,矢矫如龙，直取$p"HIW"的"+HIR+xue+NOR"。\n";
	ob = target->query_temp("weapon");
	
	if( random( me->query_skill("force",1) ) > target->query_skill("force",1)/2
		||random(me->query_dex(1))> target->query_dex(1)/2)
	{
		if (me->query("yueyin")
			&&me->query("env/银索金铃")=="铃铛"
			&&me->query_skill("yinsuo-jinling",1)>350
			&&me->query_temp("weapon")
			)
			call_out("yueyin_attack",1,me,target,(int)me->query_skill("yinsuo-jinling",1)/40);
		//对方空手

		if (!objectp(ob))
		{
			int damage = 0;
			if (target->query_skill("dodge",1) > 300 && !random(2))
			{
				switch (random(2)){
				case 0:
					msg += HIR "$p连续变了几种上乘身法，终于没能躲过，"
						"$N的金铃正点在$p的檀中穴上，$p只觉得一口"
						"凉气，自丹田而上，心里有种说不出的难受。\n"NOR;
					damage = 3;
					break;
				case 1:
					msg += HIR "$p轻身飘开，身法灵动之极，众人正要喝彩，"
              					"听「噗」的一声，如击败革，$p脸色煞白，摇摇欲坠。\n"NOR;
					damage = 5;
					break;
				}
			} 
			else if (target->query_skill("force",1) > 300 && random(2) == 0)
			{
				switch(random(2))
				{
				case 0:
					msg += HIR "$p冷哼一声，自持内力高强，反手出招，「啵」"
						"的一声轻响，掌铃相交，$p身行微晃，脸如金纸。\n"NOR;
					damage = 3;
					break;
				case 1:
					msg += HIR "$p一声长啸，双手幻化出无数掌影，护住身前。"
						"只听「嗤」的一声，掌影顿消，$p已经变得脸色惨白。\n"NOR;
					damage = 4;
					break;
				}
			}
			else
			{
				switch(random(2))
				{
					case 0:
						msg += HIR "$p看到这招，竟然不知躲避，「嗤」的一声，$N"
						"的金铃正点在$p的大椎穴上,$p全身酸软,跌倒在地。\n"NOR;
						target->receive_damage("qi", target->query("qi")/2,me);
						target->receive_wound("qi", target->query("qi")/3,me);
						target->add_busy(1);
						damage = 0;
						break;
					case 1:
						msg += HIR "$p一转念，已经想出了九十九种化解的办法，"
						"尚未来得及施展，只听「嗤」的一声，已被$N点中印堂穴,$p顿时眼冒金星，精力大幅流失。\n"NOR;
						target->receive_damage("jing", target->query("jing")/2,me);
						target->receive_wound("jing", target->query("jing")/3,me);
						target->add_busy(1);
						damage = 0;
					break;
				}
			}
			if (damage > 0) 
			{
				target->receive_damage("qi", target->query("qi")/3,me);
                target->receive_wound("qi", target->query("qi")/5,me);
			}
			if (damage > 2) 
			{
				target->receive_damage("jing", target->query("jing")/2,me);
				 message_vision(HIB"$N耳听一阵铃声响动，震人心魄，心神顿时失守，眼前金星乱冒!\n"NOR,me);
               // target->receive_wound("jing", target->query("qi")/5,me);
			}

			//点中对方标记，附加夺刺或乐音威力加大
			target->set_temp("ysjl/dian",1);
			message_vision(msg, me, target);
			//陷入忙乱中
			if (userp(target))
				target->add_busy(1);
			else target->add_busy(3);
			
			return 1;
		}

//若带兵器，非宝物打断
	 if (ob && ob->query("imbued") < 3 && ob->query("sharpness") > 0 && !random(3)&& me->query("env/银索金铃")=="铃铛")
     {
				msg += HIW "$p连忙招架，只听见「啪」地一声，$p手中的" + ob->name()
				+ "寸寸断裂，散落一地！\n";
				ob->unequip();
				ob->move(environment(target));
				ob->set("name", "断掉的" + ob->query("name"));
				ob->set("value", 0);
				ob->set("weapon_prop", 0);
           
	  }
	  target->add_busy(2);
//若没点中
	} else
	  {
		int busy = 0;
		if (target->query_skill("dodge") > 200 && random(2) == 0)
		{
			switch (random(2))
			{
			case 0:
				msg += "$p一声轻笑，连续变化了几次身法，扰人耳目，一时让$N无法进攻。\n";
				busy = 2;
				break;
			case 1:
				msg += "$p突然向后飘去，疾若闪电，令$N所有的后继变化无从施展。\n";
				busy = 1;
				break;
			}
		} else
		if (target->query_skill("force") > 200 && random(2) == 0)
		{
			switch (random(2))
			{
			case 0:
				msg += "$p脸色凝重，加快格架，以巧对巧，让$N无从下手，只能收回金铃。\n";
				busy = 3;
				break;
			case 1:
				msg += "$p满脸不屑，冷笑一声，双掌齐出，其快无比，令$N只能回招自救。\n";
				busy = 1;
				break;
			}
		} else
		{
			switch (random(3))
			{
			case 0:
				msg += "$p左摇右晃，看上去毫无章法，偏偏躲过了$N这一击。\n";
				busy = 2;
				break;
			case 1:
				msg += "$p金铃点出，看上去灵动精妙，$N一呆，攻势顿缓。\n";
				busy = 2;
				break;
			case 2:
                if (ob)
                {
				   msg += "$p摄住心神，真气贯注" + ob->query("name")
					 + "，堪堪封住了$N的进攻。\n";
                 }
				busy = 2;
				break;
			}
		}
		target->start_busy(busy);
		//me->start_busy(2);
	}
	message_vision(msg + NOR, me, target);

	return 1;
}

int yueyin_attack(object me,object target,int num)
{
	object weapon;
	int damage;
	if (!me||!target || !me->query_temp("weapon")) return 0;

	weapon=me->query_temp("weapon");
	damage=me->query_skill("yinsuo-jinling",1)+me->query_skill("yunu-xinjing",1)+me->query_skill("whip",1);
	damage=damage+random(damage);
	
	if (!me->is_fighting()
		||num<0)
	{
		message_vision(WHT"$N长吁一口浊气，卸去浑身劲力，缓缓收功。\n"NOR,me);
		return 1;
	}
	message_vision(BLU"$N将手中"+weapon->query("name")+BLU"甩动，随着你手臂的摆动翻飞中，端头的铃铛发出有节奏的音律。\n"NOR,me,target);
	
	switch (random(3))
	{
		case 0:
			target->receive_damage("qi",damage/2,me);
			break;
		case 1:
			target->receive_damage("jing",damage/4,me);
			break;
		case 2:
			target->receive_damage("qi",damage/2,me);
			target->receive_damage("jing",damage/4,me);
			target->add_busy(1);
			break;
		
	}
	num=num-1;
	if (me->query_temp("weapon")) call_out("yueyin_attack",1,me,target,num);
	return 1;
}

string perform_name(){ return HIC"点穴"NOR; }
int help(object me)
{
        write(WHT"\n银索金铃之"HIC"「点穴」："NOR"\n");
        write(@HELP
	银索金铃乃是古墓独门武技，源自小龙女大战
	金轮法王和武林诸位英雄豪杰时的武技。银索
	乃是采用天山天蚕丝打造，极为坚韧，且阴柔
	无比，前端为一金色的铃铛，有干扰对方施展
	正常武技的功能。乐音绝技经由小龙女指点后
	方能使用，将古墓阴柔内力融入到银索中，催
	动索端的金玲，发出一阵阵杂音，干扰对方精
	力。尤其是漂亮的女性，对本武技的应用更是
	威力倍增，该武功判断容貌和身法。女性使用
	有优势。
	点穴绝技是利用银索金铃尖端的铃铛或其他硬
	物来打击对方穴道的绝技。
	注意：可以通过不同的设置来达到不同效果。
	
	set 银索金铃 铃铛
		功效：有封招闭穴特点且有概率打掉对方
		兵器的功效。若解开乐音绝技，则铃铛会
		持续发出袭扰对方。
	set 银索金铃 玉蜂针
		功效：有让对方中玉蜂针功效
	set 银索金铃 冰魄神针			
		功效：有让对方中冰魄毒功效
	
	perform whip.dian
	
要求：
	最大内力要求 5000 以上；      
	当前内力要求 1500 以上；
	玉女心经等级 300 以上；
	银索金铃等级 300 以上；
	玉女身法等级 300 以上；
	激发基本鞭法为银索金铃；
	激发招架为银索金铃；
	激发内功为玉女心经；
	手持鞭类兵器，
                
                
HELP
        );
        return 1;
}
