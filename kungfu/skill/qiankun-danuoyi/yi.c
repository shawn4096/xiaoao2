// yi.c 乾坤大挪移「移」字诀
#include <ansi.h>
inherit F_SSERVER;
string perform_name(){ return HIB"移字诀"NOR; }

int perform(object me, string target)
{
	object ob,ob2,weapon;
	weapon=me->query_temp("weapon");
	if(!target)
		return notify_fail("你想把对方的劲力挪移至谁？\n");
    //if(me->query_temp("weapon"))
		//return notify_fail("你手握兵刃，无法施展挪移神功？\n");
	if(!objectp(ob = present(target, environment(me))))
		return notify_fail("这里没有你想挪移的这个人。\n");	

	//if (!me->is_killing(target) || !me->is_fighting(target)) return notify_fail("他并没有和你在战斗中。\n");
	
	if (me->query_temp("qkdny/yi"))
	{		
		if (me->query_temp("qkdny/yi")==ob) return notify_fail("你刚将攻击转移给他，目前暂时无法再次转移。\n");
	}
	
	
	if(!me->is_fighting())
		return notify_fail("你没在打架，移什么移！\n");

    if(!ob->is_character()) 
		return notify_fail("看清楚一点，那并不是生物。\n");

	if(!living(ob))
		return notify_fail(ob->name()+"已经无法战斗了。\n"); 

	if(ob==me) return notify_fail("你不能攻击自己。\n");               
	
	if(userp(ob) && !me->is_killing(ob))
		return notify_fail("除非跟对方有深仇大恨，你不能陷害玩家。\n");

	if(me->is_fighting(ob))
		return notify_fail("你正和他打着呢。\n");

	if(me->query_skill("qiankun-danuoyi", 1) < 450 )
		return notify_fail("你的乾坤大挪移还不够娴熟，不会使用「移」字诀。\n");

	if (!me->query_skill("jiuyang-shengong", 1))
	if( me->query_skill("shenghuo-shengong", 1) < 450 )
		return notify_fail("你的圣火神功等级不够。\n");

	if(me->query_skill_mapped("parry") != "qiankun-danuoyi")
		return notify_fail("你没有使用乾坤大挪移作为招降，无法使用「移」字诀！\n"); 
	
	if((int)me->query("neili") < 8000 )
		return notify_fail("你的内力不够！\n");
	
	if((int)me->query_skill("force") < 450 )
		return notify_fail("「移」字诀需要深厚的内功基础，你的条件好象还不够。\n");

	me->add("neili", -300);
	
	message_vision(BLU"你暗运乾坤大挪移「移」字诀，企图要把对方下一招的力道转移到"+ob->name()+"身上！\n"NOR,me,target); 
	//设置标记，改成防御自带auto，否则无法出现转嫁第三者 by renlai
/*
	if (random(me->query_int(1))>target->query_int(1)/2 && me->query("mjqkdny/pass"))
	{
      message_vision(HIC"$n忽然觉得自己方才施展的这一招半途中竟然忽然转了方向，竟然莫名其妙地打在"+ ob->name() +"的身上！\n"NOR,me,target); 
	  
	  COMBAT_D->do_attack(target, ob, target->query_temp("weapon"), 3);
	  
	}
	*/
	if (!me->query("mjqkdny/pass")) me->start_perform(1, "移字诀");	
	    me->set_temp("qkdny/yi",ob);
		ob->set_temp("qkdny/yi",me);//标记下
	return 1;
}

int help(object me)
{
        write(HIB"\n乾坤大挪移「移字诀」："NOR"\n");
        write(@HELP
	《倚天屠龙记》中张无忌的招牌武功，在中原明教的禁地中习得。
	功法源自波斯拜火教，乃镇教之宝，武学道理多元精妙，变化神
	奇，是西域武林最巅峰的武功。此功分七层境界，悟性高者修习，
	第一层需七年，第二层加倍，如此愈发困难，秘笈作者本人只练
	至第六层，习至第七层者实是古往今来第一人。主要有九大功能，
	包括激发最大潜力，集武功道理大成，制造对手破绽，积蓄劲力，
	粘住掌力，牵引挪移敌劲，反击对手，转换阴阳二气，借力打力
	等。
	特别注意：若解开乾坤大挪移的第七层神功时，乾坤大挪移可以
	自由使用各个绝技,且需要强大内力支撑方可有效。
	移字诀是将对方的武技转移的神奇功法，玩家当自己探索奥秘。
	
	perform parry.yi

要求：
	当前内力 8000 以上；
	乾坤大挪移等级 450 以上；
	基本内功等级 450 以上；
	圣火神功等级 450 以上；
	激发招架为乾坤大挪移。
	解密融合后会产生飞跃。
HELP
        );
        return 1;
}
