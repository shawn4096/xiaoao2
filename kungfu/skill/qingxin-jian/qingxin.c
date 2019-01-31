// qingxin.c 清心诀诀
#include <ansi.h>
//改名叫清心诀--by sohu@xojh

inherit F_SSERVER;
void remove_effect(object me, int count);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int i, attack_time, lvl;
        if( !target ) target = offensive_target(me);
        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
            return notify_fail("「清心普善咒」只能对战斗中的对手使用。\n");
        if (!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "sword")
            return notify_fail("你使用的武器不对。\n");
        if( me->query_skill("qinxin-jian",1) < 200 )
            return notify_fail("你的清心普善剑还不够火候，使不出「清心普善咒」。\n");
        if( me->query_skill("force",1) < 200 )
            return notify_fail("你的玄天无级功还不够火候，使不出「清心普善咒」。\n");
        if( me->query_skill_mapped("sword") != "qinxin-jian"
			||me->query_skill_mapped("parry") != "qinxin-jian" )
          return notify_fail("你现在没激发清心普善剑，无法使用这个绝招！\n");
     //   if( me->query_skill("force",1) <200)
       //     return notify_fail("你不用玄天无级内功支持是无法使用这个绝招的！\n");
        if( me->query("quest/hmy/qxj/qingxin/pass") )
               return notify_fail("你尚未得到任盈盈的传授，不能使用「清心普善咒」了。\n");
        if( me->query_skill("art",1)<100 )
               return notify_fail("你的琴技太差，不能使用「清心普善咒」了。\n");

        if( me->query_temp("qxj/qingxin") )
               return notify_fail("你现在已经在向对手使用「清心普善咒」了。\n");
       
        if( me->query("max_neili", 1) < 3000 )
               return notify_fail("你的最大内力修为不够使用「清心普善咒」！\n");
        if( me->query("jingli") < 500 )
			return notify_fail("你的精力修为不够使用「清心普善咒」！\n");
	 	if( me->query_dex() < 40 )
			return notify_fail("你的后天有效身法修为不够使用「清心普善咒」！\n");
        if( me->query("neili")<500)
            return notify_fail("你的真气不够！\n"); 

		msg = YEL "$N手中"+weapon->name()+YEL"轻轻敲击几下剑身，发出悦耳动听的叮咚叮咚声音，$n仔细听来，却是「清心普善咒」的曲调。\n"NOR;
        msg=HIW"$n只听得叮咚琴声轻轻响起，宛如一股清泉在缓缓流过，又缓缓注入了四肢百骸,$n全身轻飘飘地，更无半分着力处\n";
		msg=HIW"便似飘上了云端,$n宛如置身于棉絮般的白云之上。过了良久，琴声越来越低，终于细不可闻而止。\n"NOR;
		message_vision(msg, me, target);
        
		lvl = me->query_skill("art", 1) ;
        lvl = lvl/3;
		if (me->query("gender")!="女性")
		lvl=lvl/6;

		me->set_temp("qxj/qinxin", lvl);
        
		me->add_temp("apply/damage", lvl/3);
        me->add_temp("apply/sword", lvl);
        me->add_temp("apply/attack", lvl);
        
        if (me->query_skill("qinxin-jian",1)<200)
			me->start_perfrom(2,"「清心普善咒」");
        me->add("neili", -300);
        me->add("jingli", -80);
       
        call_out("remove_effect",0,me,(int)lvl/10);
        return 1;
}

void remove_effect(object me,int count)
{
        int lvl;
		object weapon;
		if (!me) return;
		lvl =(int)me->query_temp("xlj/benlei");
		weapon=me->query_temp("weapon");

        if (count < 0 
			|| !me->is_fighting()
			|| !weapon
			|| weapon->query("skill_type")!="sword"
			|| me->query_skill_mapped("sword")!="qinxin-jian")
        {      
			me->add_temp("apply/damage", -lvl/3);
			me->add_temp("apply/sword", -lvl);
			me->add_temp("apply/attack", -lvl);
			me->delete_temp("qxj/qingxin");

			message_vision(YEL"$N的的清心普善咒慢慢停了下来，长吁一口气。\n"NOR,me);
			return;
		}
		call_out("remove_effect",1,me,count -2);
		return;

}
string perform_name() {return HIW"清心普善咒"NOR;}

int help(object me)
{
    write(HIY"\n清心普善剑「"HIW"清心普善咒"WHT"」："NOR"\n");
    write(@HELP
	清心普善剑是源自任盈盈的武学所演化，招式
	大都采集笑傲江语原著，名字不可靠，但为了
	纪念这位聪明睿智，心狠手辣的小魔女同时兼
	顾日月女性玩家的癖好以及特点归纳而成。
	清心剑乃初级武功，为以后剑法线路的七弦无
	形剑做准备。女性有优势，不限内功。
	
	清心普善咒需要找到任盈盈，完成把令狐冲引
	到盈盈面前的任务时，方可得到传授。
	清心普善咒的附加伤害与自身的琴技有关，琴
	技越高，效果越明显。

	指令：perform sword.qingxin
	
要求：
	清心普善剑等级 200 级以上；
	基本剑法等级 200 级以上，
	最大内力要求 3000 以上，
	当前内力要求 500 以上，
	当前精力要求 500 以上，
	激发剑法清心普善剑；
	激发招架清心普善剑；
	需手持剑类武器。    
HELP
	);
	return 1;
}

