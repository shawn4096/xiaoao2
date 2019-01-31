// By Snowman@SJ
// modified by snowman 20/06/2000
// modify by looklove 2001.5.22 update help
// add 450 飞跃 by sohu@xojh
#include <ansi.h>

inherit F_SSERVER;

void check_fight(object me,object target);
string perform_name(){ return HIY"降龙啸"NOR; }

int perform(object me, object target)
{
       int skill = me->query_skill("xianglong-zhang",1);

    if(!userp(me)) skill = skill /6; //降低npc的威力
	else skill=skill/3;


	if( !target ) target = offensive_target(me);

	if( !objectp(target) || !me->is_fighting(target) )
		return notify_fail("只能在战斗中使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("你必须空手才能使用「降龙啸」！\n");

	if( (int)me->query("neili") < 5000 )
		return notify_fail("降龙掌需要深厚的内功支撑，你的内力不够。\n");

	if( (int)me->query_temp("xlz/xiao") )
		return notify_fail("你已经开始了降龙啸。\n");

	if( (int)me->query_skill("xianglong-zhang", 1) < 450 )
		return notify_fail("你的降龙十八掌还不够娴熟，使不出「降龙啸」来。\n");

	if( (int)me->query_skill("force") < 450 )
		return notify_fail("你的内功等级不够，使不出「降龙啸」来。\n");

	if( (int)me->query_str(1) < 60 )
		return notify_fail("你的膂力还不够强劲，使不出「降龙啸」来。\n");

	if( (int)me->query_skill("huntian-qigong", 1) < 450 )
		return notify_fail("你的混天气功等级还不够，使不出「降龙啸」绝技。\n");

	if( me->query_skill_mapped("force") != "huntian-qigong" )
		return notify_fail("你所使用的内功不对。\n");

	if( me->query_skill_prepared("strike") != "xianglong-zhang"
	 || me->query_skill_mapped("strike") != "xianglong-zhang"
	 || me->query_skill_mapped("parry") != "xianglong-zhang")
		return notify_fail("你现在无法使用「降龙啸」！\n");

	me->add("neili", -400);
	me->add("jingli", -150);
	message_vision(YEL "\n降龙十八掌乃外门武技巅峰，越战越勇，$N仰天狂啸，所使降龙十八掌竟然势力大增，威不可当！\n"+
		"$N源源不绝的掌力排山倒海般地压向$n！$n只觉得$N的掌力劲气汹涌，顿时被压制的动弹不得。\n\n" NOR, me, target);
	if( me->query("jiali") < 50 )
		me->set("jiali", 50);
	me->set_temp("xlz/xiao", skill);
    me->add_temp("apply/attack", skill /2);
    me->add_temp("apply/strike",skill/5);
    //me->add_temp("apply/parry",skill/5);
    me->add_temp("apply/damage",skill/5);
        //me->set_temp("double_attack",1);        
    me->add_temp("apply/strength", skill/15); //提高临时臂力
	if (random(3)&&me->query_skill("xianglong-zhang",1)>500)
	{  
		message_vision(HIR"$N数十年的勤秀苦练，终于将降龙掌练得炉火纯青，内力闪烁，刚柔相济。$n一时不察，为$N降龙掌劲力所制。\n"NOR,me,target);
		target->apply_condition("no_perform",  1+random(2)); //降龙掌牵制
    }
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), userp(me)?3:1);
	if (me->query_skill("xianglong-zhang",1)<500)
	{
		me->start_perform(3, "「降龙啸」"); //450后大飞
	}
	call_out("check_fight", 1 , me, (skill/3 > 10?skill/3:10));
    return 1;
}

void check_fight(object me, int i)
{
	int j;

	if( !me ) return;
	if( !intp(j = me->query_temp("xlz/xiao"))) return;

	i--;
	if( !me->is_fighting()
	 || i < 1
	 || me->query_temp("weapon")
	 || me->query_temp("secondary_weapon")
	 || me->query_skill_prepared("strike") != "xianglong-zhang"
	 || me->query_skill_mapped("force") != "huntian-qigong"
	 || me->query_skill_mapped("parry") != "xianglong-zhang"
	 || me->query("neili") < j + 200) {

                me->add_temp("apply/attack", -j /2);
                me->add_temp("apply/strength", -j/15);
                me->add_temp("apply/strike",-j/5);
               // me->add_temp("apply/parry",-j/4);
                me->add_temp("apply/damage",-j/5);
		        me->delete_temp("xlz/xiao");
               // me->delete_temp("double_attack");

		        me->add("neili", -j );
                me->start_perform(6, "「降龙啸」");
		message_vision(YEL "\n$N长啸完毕，看来好象消耗了不少的内力，降龙十八掌的威力也恢复寻常了。\n" NOR, me);
		return;
	}
	call_out("check_fight", 1, me, i);
}

int help(object me)
{
	write(HIY"\n降龙十八掌之「降龙啸」："NOR"\n");
	write(@HELP
	降龙十八掌乃是武林第一大帮丐帮的镇派两大绝技之一，讲究刚柔并济，当刚则刚，
	当柔则柔，轻重刚柔随心所欲，刚劲柔劲混而为一，劲力忽强忽弱，忽吞忽吐，从
	至刚之中生出至柔，天下阳刚第一，掌法之妙，天下无双，招招须用真力，说是外
	门武学中的巅峰绝诣，动作虽似简单无奇，但掌掌现神龙，招招威力无穷，招式简
	明而劲力精深的武功，精要之处，全在运劲发力，全凭劲强力猛取胜，当真是无坚
	不摧、无固不破，虽招数有限，但每出一掌均有龙吟虎啸之势、每出一招均具绝大
	的威力。
	降龙十八掌必须得到帮主的传授方可习得，而「降龙啸」乃是降龙掌绝技，非深厚
	内力不得施展。可短时间内可提升降龙掌威力，但同时消耗内力巨大。500后大飞。
	
	指令：perform strike.xiao
	
要求：	
	当前内力 5000；
	降龙掌等级 450 以上；
	混天气功等级 450 以上；
	膂力 60 以上：
	激发掌法降龙掌；
	激发内功为混天气功；
	激发招架为降龙掌。
HELP
	);
	return 1;
}
