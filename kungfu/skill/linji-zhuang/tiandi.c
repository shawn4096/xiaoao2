// Modified by Lane@SJ 2005/4/14
// edit by sohu@xojh 2014.1
#include <ansi.h>
int exert(object me)
{
   int cure;
  
   if( !me->is_fighting() )
      return notify_fail("你现在这么闲，慢慢打坐疗伤吧。\n");
   if( me->query("class") != "bonze" && me->query("family/generation") > 4 )
		return notify_fail("你不是出家人，无法领会临济十二庄的「无我」字决！\n");

   if( (int)me->query_skill("linji-zhuang", 1) < 300 )
      return notify_fail("你的内功修为还不够。\n");

   if( (int)me->query_skill("medicine", 1) < 120 )
      return notify_fail("你的本草术理修为还不够。\n");

    if( (int)me->query("neili") < 3000 )
       return notify_fail("你的真气不够。\n");

    if( (int)me->query("eff_qi") >= (int)me->query("max_qi") )
        return notify_fail("没受伤，疗什么伤啊？\n");

    if( (int)me->query("eff_qi") < (int)me->query("max_qi")*3/10 ) // 改为30%上限
        return notify_fail("你已经受伤过重，经受不起真气震荡！\n");

    if( me->query_temp("ljz/wuwo") )// 改成 不能和 wuwo 同时使用
       return notify_fail("你正在运用临济十二庄的「无我」字决！\n");
    if (me->query("emjy/pass"))
	{
	   message_vision(HIR"$N面部腾起一片红润之色，峨嵋九阳功的威力当真不同凡响。\n"NOR,me);
	   cure=(int)me->query_skill("linji-zhuang",1)+(int)me->query_skill("medicine",1)+(int)me->query_skill("jingmai-xue",1);
	 }
    else  cure=(int)me->query_skill("linji-zhuang",1)/2+(int)me->query_skill("medicine",1)/2+(int)me->query_skill("jingmai-xue",1)/2;
   
    message_vision(HIW"$N运起临济庄天地桩的秘诀，全身真气流传不绝，调理自身伤势，脸色看来好多了。\n"NOR,me);
    me->receive_curing("qi",cure );
    me->add("neili", -100);
    me->start_exert(1,"天地");
    if (me->is_busy())
       me->add_busy(1);
	else me->start_busy(1);
    return 1;
}
string exert_name(){ return HIG"天地字决"NOR; }

int help(object me)
{
        write(HIW"\n临济十二庄「天地字诀」："NOR"\n\n");
        write(@HELP
	峨嵋临济庄乃是开派祖师郭襄女侠集成了家传武学以及九阴真经和
	九阳神功所创建。因历代掌门均为女性，所以峨嵋内功具有显然的
	阴柔特征且极为实用。
	天地诀，乃是战斗中疗伤所用。和本草以及经脉学和特殊内功等级
	都有影响。功力越高疗伤效果越好，且只能战斗中疗伤，和无我诀
	有冲突。450后大飞。
	
指令：exert tiandi

要求：  
	当前内力 3000 以上；
	临济十二庄等级 300 以上；
	本草术理 120 以上；
	不能和「无我」字诀同时使用。
HELP
        );
        return 1;
}
