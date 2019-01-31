// jianjue.c 全真剑法 剑气
// modified by xjqx@SJ 2009/01/01
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int skill,improve;

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「剑气」只能对战斗中的对手使用。\n");
        if( me->query("family/family_name") !="全真教" || !me->query("quest/qzjf/jianjue") )
                return notify_fail("你没有得到全真真传，无法使出全真剑法的无形「剑气」。\n");
        if( !objectp(weapon = me->query_temp("weapon"))
         || weapon->query("skill_type") != "sword" )
                return notify_fail("你手中无剑，如何能够使出「剑气」？！\n");

        if( (int)me->query_skill("quanzhen-jianfa", 1) < 350 )
                return notify_fail("你的全真剑法不够娴熟，无法使出「剑气」。\n");
                
        if( me->query_temp("qzjf/jianqi"))
                return notify_fail("你正在使用「剑气」！\n");

        if( (int)me->query_skill("xiantian-gong", 1) < 350 )
            return notify_fail("你的特殊内功火候不够，无法使出「剑气」！\n");

        if( me->query_skill_mapped("force") != "xiantian-gong")
            return notify_fail("你的现在使用的内功不对，无法使出「剑气」！\n");    

        if (me->query_skill_mapped("sword") != "quanzhen-jianfa"
         || (me->query_skill_mapped("parry") != "quanzhen-jianfa" && me->query_skill_mapped("parry") != "kongming-quan" ))
                return notify_fail("你现在无法使用「剑气」进行攻击。\n");

        if( me->query("max_neili") <= 3500 )
                return notify_fail("你的内力修为不足，劲力不足以施展「剑气」！\n");

        if( me->query("neili") <= 1500 )
                return notify_fail("你的内力不够，劲力不足以施展「剑气」！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力有限，不足以施展「剑气」！\n");

        message_vision(HBCYN+HIC"$N神情肃穆，左手捏一个剑诀，右手握起" +NOR+weapon->name() +HBCYN+HIC"，将雄厚的先天功力注入剑中，\n"+
		        "$N的剑尖上闪烁一股若有若无的无形"+NOR+HIR+"「剑气」"HBCYN+HIC"!\n"NOR, me);
        if(userp(me)){
           me->add("neili", -300);
           me->add("jingli", -50);
        }
        skill = me->query_skill("xiantian-gong",1)/2+me->query_skill("quanzhen-jianfa",1);
      	improve = skill/5 + random(skill/5);//原来是5
      	if ( improve > 150 ) improve = 150 + random(improve-150) / 5;

        me->set_temp("qzjf/jianqi", improve);
        me->add_temp("apply/damage", improve/2);
        me->add_temp("apply/sword", improve);
        me->add_temp("apply/strength", improve/5);
        call_out("remove_effect", 1,  me, weapon, improve);
        if (me->query_skill("quanzhen-jianfa",1)<450) me->start_perform(5, "「剑气」");
        return 1;
}

void remove_effect(object me,object weapon,int count)
{
        int i;
        if(!me) return;
        if(! me->is_fighting()
         || !weapon
         || me->query_skill_mapped("sword") != "quanzhen-jianfa"
         || (me->query_skill_mapped("parry") != "quanzhen-jianfa" && me->query_skill_mapped("parry") != "kongming-quan")
         || count < 1 ){
          i = me->query_temp("qzjf/jianqi");
          me->add_temp("apply/sword", -i);
          me->add_temp("apply/damage", -i/2);
          me->add_temp("apply/strength", -i/5);
          me->delete_temp("qzjf/jianqi");
	    if (weapon)
                message_vision(HIW"$N使完"NOR"「"HIR"剑气"NOR+HIW"」，"NOR+weapon->name()+HIW"的剑气逐渐消失，威力大减。\n"NOR, me);
		
          return;
        }
        else {
          //me->start_perform(1,"「剑气」");//这里不能set，否则无法halt
          call_out("remove_effect", 1, me, weapon, count -1);
        }
}              
string perform_name(){ return HIC"剑气"NOR; }

int help(object me)
{
        write(HIG"\n全真剑法之"+HIC"「剑气」："NOR"\n\n");
        write(@HELP
	全真剑法是王重阳所创全真教的入门剑法，大道初修通九窍，
	又窍原在尾闾穴。先从涌泉脚底冲，涌泉冲起渐至膝。过膝
	徐徐至尾闾，泥丸顶上回旋急。金锁关穿下鹊桥，重楼十二
	降宫室。变化精微，与全真教的全真心法相得益彰。
	全真教乃是内家功法为主，全凭一口真气运转，所以当玩家
	功力高深后，运使先天功，将功力逼入兵器之中，形成剑气
	
	指令：perform sword.jianqi
	
要求：
	当前内力 1500 以上；
	最大内力 3500 以上；
	当前精力 1000 以上；
	全真剑法等级 350 以上；
	先天功等级 350 以上；
	基本剑法等级 350 以上；
	激发剑法为全真剑法；
	激发招架为全真剑法或空明拳；
	激发内功为先天功。450后大飞。
HELP
        );
        return 1;
}
