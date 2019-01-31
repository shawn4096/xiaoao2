// 断魂夺魄
// by Looklove@SJ
// Update By lsxk@hsbbs 2007/6/11

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
   int i, j, p, flag;
   i = (int)me->query_skill("qishang-quan", 1);

	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !me->is_fighting(target)
	 || !living(target)
	 || environment(target)!=environment(me))
		return notify_fail("「断魂夺魄」只能在战斗中对对手使用。\n");

	if( objectp(me->query_temp("weapon")))
		return notify_fail("你必须空手才能使用「断魂夺魄」！\n");

    if( (int)me->query_skill("qishang-quan", 1) < 520 )
		return notify_fail("你的七伤拳还不够娴熟，使不出「断魂夺魄」绝技。\n");

    if(!me->query_skill("jiuyang-shengong", 1) || (int)me->query_skill("jiuyang-shengong",1)<520)
    if( (int)me->query_skill("force", 1) < 520 )
           return notify_fail("你的基本内功等级还不够，使不出「断魂夺魄」绝技。\n");

    if( (int)me->query_skill("cuff",1) < 520 )
		return notify_fail("你的基本拳法等级不够，不能使用「断魂夺魄」。\n");

    if( me->query_str() < 80 )
		return notify_fail("你的膂力还不够强劲，使不出「断魂夺魄」来。\n");

	if( me->query_skill_prepared("cuff") != "qishang-quan"
	 || me->query_skill_mapped("cuff") != "qishang-quan")
		return notify_fail("你现在无法使用「断魂夺魄」！\n");


	if( me->query_skill_mapped("parry") != "qishang-quan"
	&& me->query_skill_mapped("parry") != "qiankun-danuoyi")
		return notify_fail("你需要激发招架为七伤拳，方能使用「断魂夺魄」。\n");


    if ( me->query_temp("qsq/duanhun"))
		return notify_fail("你正在使用「断魂夺魄」。\n");

    if( (int)me->query("max_neili") < 15000)
		return notify_fail("你的内力太弱，使不出「断魂夺魄」。\n");

    if( (int)me->query("neili") < 1500 )
		return notify_fail("你现在真气太弱，使不出「断魂夺魄」。\n");

    if( (int)me->query("jingli") < 1500 )
           return notify_fail("你现在太累了，使不出「断魂夺魄」。\n");

	message_vision(HBRED+HIG"\n$N大喝一声「断魂夺魄」，口中念起七伤断魂夺魄歌诀，将七伤拳意发挥得淋漓尽致，大喝一声全力打出数招！！\n"NOR,me);

    if( me->query_skill_mapped("force") == "jiuyang-shengong" && userp(me)||me->query("mjqkdny/pass"))
      {
		flag=1;        
		}
    else flag = 0;

	p = me->query_skill("qishang-quan", 1) / 70;
	if ( p > 7 ) p = 7;

	if (!me->query_skill("jiuyang-shengong", 1)&&!me->query("mjqkdny/pass"))
		if ( p > 5 ) p = 5;

   i = i/5*3 + (int)me->query_skill("jiuyang-shengong", 1)/5*2;   

   j = i/(8-p);                //有9yang是1/2,否则是1/3

	if ( i > 300 && p>4 )
		j = to_int( i/3.0 * i/ 300.0);  // 9yang 300级小飞

   if(userp(me) && !userp(target)) target->add_busy(1);
   
   me->add_temp("apply/cuff", j/2);
   me->add_temp("apply/attack", j/2);
   me->add_temp("apply/damage", j/2);
   
   if (wizardp(me))
   {
	   write("j="+j);
   }

 

   if(me->query_skill("jiuyang-shengong",1)>450 || me->query("mjqkdny/pass"))
	me->set_temp("qsq/duanhun",p);
//no1
    
	COMBAT_D->do_attack(me, target, 0, 3);

	if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, 3);

	if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);

	if ( me->is_fighting(target) && p > 1)
           COMBAT_D->do_attack(me, target, 0,  userp(me)?3:1);
	
	if ( me->is_fighting(target))
           COMBAT_D->do_attack(me, target, 0, userp(me)?3:1);

	if ( me->is_fighting(target) && p > 2)
           COMBAT_D->do_attack(me, target, 0,  userp(me)?3:1);

	if ( me->is_fighting(target) && p > 4)
           COMBAT_D->do_attack(me, target, 0, (flag==1)?3:1);
	//乾坤开了多一招
    if ( me->is_fighting(target) && me->query("mjqkdny/pass")&&me->query_skill("qiankun-danuoyi",1)>450)
	{
           message_vision(HBBLU"$N将第七层乾坤大挪移神功运使起来，全身精力弥漫，一拳打出，带出一片呼啸之音。\n"NOR,me,target);
		   target->set_temp("must_be_hit",1);
		   target->add_temp("apply/damage",me->query_skill("qiankun-danuoyi",1)/4);
		   COMBAT_D->do_attack(me, target, 0, 3);
		   target->add_temp("apply/damage",-me->query_skill("qiankun-danuoyi",1)/4);
		   target->delete_temp("must_be_hit");
	}
	//九阳开了再多一招
	if ( me->is_fighting(target) && me->query("mj/jiuyang/pass")&&me->query_skill("jiuyang-shengong",1)>450)
	{
           message_vision(HBRED"$N九阳神功融汇贯通，七伤拳威力倍增，至此七伤拳的威力方显大成。\n"NOR,me,target);
		   target->set_temp("must_be_hit",1);
		   target->add_temp("apply/damage",me->query_skill("jiuyang-shengong",1)/4);
		   COMBAT_D->do_attack(me, target, 0, 3);
		   target->add_temp("apply/damage",-me->query_skill("jiuyang-shengong",1)/4);
		   target->delete_temp("must_be_hit");
	}

    me->add_temp("apply/cuff", -j/2);
    me->add_temp("apply/attack",-j/2 );
    me->add_temp("apply/damage", -j/2);
	
  
	me->delete_temp("qsq/duanhun");
    me->add("jingli", -100*p);
    me->add("neili", -200*p);
    me->start_busy(random(3));
    me->start_perform(5+ random(1),"「断魂夺魄」");
	return 1;
}

string perform_name(){ return HBRED+HIY"断魂夺魄"NOR; }
int help(object me)
{
	write(HIR"\n七伤拳之「断魂夺魄」"NOR"\n");
	write(@HELP
	原本为崆峒派传世武功，后来明教金毛狮王谢逊夺得
	《七伤拳谱》古抄本，终于练成。此拳法出拳时声势
	煊赫，一拳中有七股不同的劲力，或刚猛、或阴柔、
	或刚中有柔，或柔中有刚，或横出，或直送，或内缩
	敌人抵挡不住这源源而来的劲力，便会深受内伤。谢
	逊曾以此拳击毙少林神僧空见大师。但这七伤拳倘由
	内力未臻化境的人来练，对自己便有极大伤害。人体
	内有阴阳二气、金木水火土五行，一练七伤，七者皆
	伤。所以所谓“七伤”，乃是先伤己，再伤人。
	「断魂夺魄」是在短时间内连续发出七招，招招毙命
	的打法，威力巨大。
	注意：七伤拳解开乾坤大挪移融合和九阳神功后大飞
	且本门武功因是谢逊偷自崆峒武技，不需本门内功

	指令：perform cuff.duanhun

要求：
	最大内力需求 15000 以上；
	当前内力需求 1500 以上；
	当前精力需求 1500 以上；
	七伤拳法等级 520 以上；
	基本内功等级 520 以上；
	后天膂力需求 80 以上；
	激发拳法为七伤拳；
	激发招架为七伤拳或乾坤大挪移：
	备拳法为七伤拳且空手。
HELP
        );
        return 1;
}