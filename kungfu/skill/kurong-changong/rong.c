// rong.c 定位成疗伤功效，生机勃勃
// By Spiderii@ty 加个限制,防止强行为他人yun liao.造成对方busy
// edit by sohu@xojh 2014
#include <ansi.h>

string exert_name() {return HIG"荣字诀"NOR;}

int exert(object me, object target)
{
        int i,m,j,z;
		i=me->query_skill("kurong-changong",1)+me->query_skill("yiyang-zhi",1);
		m=me->query_skill("medicine",1);
		j=me->query_skill("jingmai-xue",1);
		z=i+m+j;
		if( !objectp(target) )
                return notify_fail("你要用一阳指为谁疗伤？\n");

        if(!present(target,environment(me)) )
                return notify_fail("你要用一阳指为谁疗伤？\n");

        if (target->is_corpse() || !target->is_character())
                return notify_fail("那不是活物耶！\n");

        if((int)me->query_skill("force",1) < 150 )
              return notify_fail("你的乾天一阳功不够娴熟，无法替人疗伤！\n");

        if( me->is_fighting()&& target != me)
                return notify_fail("战斗中无法替别人疗伤！\n");

        if( target->is_fighting()&&target != me)
                return notify_fail("对方正在战斗，无法替他疗伤！\n");
        if( (int)me->query("max_neili") < 1500 )
                return notify_fail("你的内力修为不够。\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不够。\n");

        if((int)me->query_skill("medicine", 1) < 80 )
               return notify_fail("看样子你的医理知识所知甚少，不知如何下手? \n");

        if( (int)target->query("eff_qi") >= (int)target->query("max_qi") )
                return notify_fail( target->name() + "并没有受伤！\n");
        // By Spiderii@ty 加个限制
        if( target->query("env/no_lifeheal"))
                return notify_fail( target->name()+"拒绝你帮其疗伤。\n");
        if (me->is_fighting() && (target==me))
        {
          message_vision(HIY"\n$N手臂颤动，犹如蜻蜓点水，一口气连点过自己胸口的十二道大穴，纯阳真气不断透入。。。\n\n"
                         HIM"只这片刻之间，$N脸色便有了红晕,伤势好多了。\n" NOR,me);
          me->add("neili",-random(200));
          me->receive_curing("qi",z/10);
          me->add("qi", z/10);
          if( (int)me->query("qi") > (int)me->query("eff_qi") )
			me->set("qi", (int)target->query("eff_qi"));
          if (me->query_skill("kurong-changong",1)<450)
          {
			  me->start_exert(2,"疗伤");
          }
        }
        else
        {
          if (target != me)
            message_vision(HIY"\n$N伸出右手食指，微一凝气，听得嗤嗤声响, 食指沿任、督二脉各穴依此点过，最后按在$n胸口的膻中大穴上，纯阳内力源源透入。。。\n\n"
                           HIM"\n$N头顶冒起丝丝白气，$n感觉一股温正平和的内力在体内循环流动，过了一盏茶时分，$N才放开手指。只这片刻之间，$n双颊\n"
                           HIM"便有了红晕，脸色看起来也好多了。\n" NOR,me,target);
          else
           message_vision(HIY"\n$N盘腿坐下，微一凝气，食指依任、督二脉各穴依此点过，食指一收，虚掌按在胸口膻中大穴，纯阳真气源源透入。。。\n\n"
                          HIM"$N头顶冒起丝丝白气，过了一盏茶时分，才放开手指,$N的脸色看起来也好多了。\n" NOR,me);
           if(target != me
           && userp(target)
           &&(int)target->query("eff_qi") < (int)target->query("max_qi")/5)
           {
             if(!random(4))
             	me->add("max_neili",-1);
             me->add("yyz_cure",1);
           }
           me->add("neili",-random(400));
           target->receive_curing("qi", z/10);
           target->add("qi", z/10);
           if((int)target->query("qi")>(int)target->query("eff_qi"))
           	target->set("qi", (int)target->query("eff_qi"));
           if(target!=me)
           	me->start_busy(3);
           target->start_busy(3);
        }
        return 1;
}


int help(object me)
{
        write(WHT"\n枯荣禅功"HIG"「荣字诀」："NOR"\n");
        write(@HELP
	枯荣禅功乃是大理国护国寺院--天龙寺主持枯荣长老的内功心法
	相传佛祖涅磐是在八棵树之间。这八棵树分东西南北两棵辆棵分
	列，它们分别是一枯一荣，东西南北分别是：常与无常，乐与无
	乐，我与无我，净与无净。 讲究心中无枯无荣方是大成。枯荣
	长老心中有物，是以终其一生，只参得半枯半荣。
	
	枯荣禅功乃是生机与死亡之间转换的一门佛门高级禅功，荣字诀
	是将浑身功力快速转化成生机活力，疗伤效果极好的一门内功。
	若修得一阳指绝学，效果更佳。

要求:
	枯荣禅功 150 级以上；
	最大内力 2000 以上；
	当前内力 1500 以上；
	本草药理 80 级以上，越高效果越好；
	需激发内功为枯荣禅功。

HELP
        );
        return 1;
}