// xu.c 乾坤大挪移「蓄」字诀

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int check_fight(object me);
string perform_name(){ return HIY"蓄字诀"NOR; }

int perform(object me, string arg)
{
	object ob;
	string msg;
	int i, jiali, p, damage;
        
	if(!me->is_fighting())
		return notify_fail("你没在战斗中呢！\n");

	if(me->query_temp("weapon"))
		return notify_fail("「蓄」字诀乃空手绝技，你手握武器如何使得出？\n");

	if ( me->query_temp("qkdny/xu") == 1)
		return notify_fail("你已经使用了「蓄」字诀了。\n");

	if (!me->query("mjqkdny/pass"))
	{
        if ( me->query_temp("qkdny/yi") )
		   return notify_fail("你正在施展「移」字诀呢！\n");

	    if ( me->query_temp("qkdny/yin") )
		   return notify_fail("你正在施展「引」字诀呢！\n");

	    if ( me->query_temp("qkdny/hua") ) 
		   return notify_fail("你正在施展「化」字诀呢！\n");
	}
	
	if(me->query_temp("qkdny/xu") > 1) {
		if(arg && !objectp(ob = present(arg, environment(me))))
			return notify_fail("你没在战斗中呢！\n");
		else    ob = offensive_target(me);

		if(!ob 
		 || !ob->is_character() 
		 || !me->is_fighting(ob) 
		 || environment(ob) != environment(me) 
		 || !living(ob))
			return notify_fail("「蓄」字诀所积蓄的力量只能对战斗中对手使用。\n");
         	
		i = me->query_temp("qkdny/xu");
         	
		if(me->query("neili") < i)
			i = me->query("neili");
         		
		jiali = me->query("jiali");
         	
		if(jiali > i)
			i = jiali;
         		
		if(i < 10)
			return notify_fail("你「蓄」字诀所积蓄的力量太少，只怕没有什么作用！\n");
         	
		me->set("jiali", i+jiali);

		if(wizardp(me))
			tell_object(me, "「蓄」字诀加力 = "+i+"\n");

		msg = HIY"\n$N突然间大喝一声，将所积蓄的十余掌的力道归并成为一掌迅急拍向$n。\n"+
			"便如一座大湖在山洪爆发时储满了洪水，猛地里湖堤崩决，洪水急冲而出！"NOR;
	

		damage = me->query_temp("qkdny/xu") * (4+random(2));
		ob->receive_damage("qi", damage, me);
		ob->receive_wound("qi", damage/3*2 + random(damage/3), me);
		if (random(2)) {
			p = (ob->query("eff_qi")+ob->query_temp("apply/qi"))*100/(ob->query("max_qi")+ob->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "震伤");
			msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
		}
		else {
			p = ob->query("qi")*100/(ob->query("max_qi")+ob->query_temp("apply/qi"));
			msg += COMBAT_D->damage_msg(damage, "震伤");
			msg += "( $n"+COMBAT_D->status_msg(p)+" )\n";
		}
	//	msg+="世上原无如此大力，$p倘若受实了，势须立时腕骨、臂骨、肩骨、肋骨一齐折断，连\n"+
			//"血也喷不出来，当场成为一团血肉模糊，惨不可言！\n"NOR;
		message_vision(msg, me, ob);

		me->set("jiali", jiali);
		me->delete_temp("qkdny/xu");
		me->reset_action();
		me->start_busy(2);
		ob->add_busy(2);
  	 if (!me->query("mjqkdny/pass"))
	  {
		  me->start_perform(2, "「蓄」字诀");

	   }
	   return 1;
	}
	if(me->query_skill("qiankun-danuoyi", 1) < 400 )
		return notify_fail("你的乾坤大挪移还未练到第七层，不会使用「蓄」字诀。\n");

	if(me->query_skill_mapped("parry") != "qiankun-danuoyi")
		return notify_fail("你没有使用乾坤大挪移作为招降，无法使用「蓄」字诀！\n");

	if (!me->query_skill("jiuyang-shengong", 1))
	if( me->query_skill("shenghuo-shengong", 1) < 400 )
		return notify_fail("你的圣火神功等级不够。\n");
                 
	if((int)me->query("neili") < 4000 )
		return notify_fail("你目前的内力不够！\n");
	if((int)me->query_skill("force") < 400 )
		return notify_fail("「蓄」字诀需要深厚的内功基础，你的条件好象还不够。\n");
        
	if((int)me->query_temp("qkdny/yi") )
		return notify_fail("你正在施展「移」字诀呢！\n");
                
	me->add("neili", -200);
	tell_object(me, HIC"\n你暗暗运起乾坤大挪移心法中绝顶功夫，施展「蓄」字诀，将对方的掌力渐渐积蓄起来！\n\n"NOR); 
	me->set_temp("qkdny/xu", 1);
	check_fight(me);
	return 1;
}

int check_fight(object me)
{

	if (!me || !me->query_temp("qkdny/xu")) return 0;

	else if(me->is_ghost() || !living(me))
		me->delete_temp("qkdny/xu");
        
	else if(!me->is_fighting()){
		tell_object(me, BLU"\n你退出了战斗，便将积蓄的力量慢慢散了出去。\n"NOR);
		me->delete_temp("qkdny/xu");
	}

	else if(me->query("neili") <= 1000){
		tell_object(me, BLU"\n你突然发现本身的内力已经要枯竭了连忙把积蓄的力量散了出去！\n"NOR);
		me->delete_temp("qkdny/xu");
	}

	else if (me->query_skill_mapped("parry") != "qiankun-danuoyi"
	 || (me->query_temp("weapon")&&!me->query("mj/qkdny/ronghe"))){
		tell_object(me, BLU"\n你心念一转，改变了战术，把积蓄的力量散了出去！\n"NOR);
		me->delete_temp("qkdny/xu");
	}

	else call_out("check_fight", 1, me);
	return 1;
}

int help(object me)
{
        write(HIC"\n乾坤大挪移「蓄字诀」："NOR"\n");
        write(@HELP

	《倚天屠龙记》中张无忌的招牌武功，在中原明教的禁地中
	习得。功法源自波斯拜火教，乃镇教之宝，武学道理多元精
	妙，变化神奇，是西域武林最巅峰的武功。此功分七层境界
	悟性高者修习，第一层需七年，第二层加倍，如此愈发困难
	秘笈作者本人只练至第六层，习至第七层者实是古往今来第
	一人。主要有九大功能，包括激发最大潜力，集武功道理大
	成，制造对手破绽，积蓄劲力，粘住掌力，牵引挪移敌劲，
	反击对手，转换阴阳二气，借力打力等。
	特别注意：若解开乾坤大挪移的第七层神功时，乾坤大挪移
	可以自由使用各个绝技。蓄字诀乃是空手武技。
	
	使用指令：perform parry.xu
	
要求：
	当前内力的需求 4000 以上；
	乾坤大挪移等级 400 以上；
	基本内功的等级 400 以上；
	圣火神功的等级 400 以上；
	激发招架为乾坤大挪移。
	解密融合后会产生飞跃。
        
HELP
        );
        return 1;
}
