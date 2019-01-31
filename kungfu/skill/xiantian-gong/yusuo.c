// yusuo.c
// 
//金关玉锁诀
//by sohu
#include <ansi.h>
inherit F_CLEAN_UP;
string exert_name(){ return MAG"金关玉锁二十四诀"NOR; }


int exert(object me, object target)
{
	int skill,i,j;
	i=(int)me->query("yusuo/degree");
	skill = me->query_skill("jinguan-yusuojue",1);
	if (i>9) i=9;
	
	if( me->query("neili") < 100 )
		return notify_fail("你的内力不够。\n");

	if( me->query_skill("xiantian-gong", 1) < 350 )
		return notify_fail("你的先天功等级不够。\n");
	if( me->query_skill("force", 1) < 350 )
		return notify_fail("你的基本内功等级不够。\n");
	if( me->query_skill("jinguan-yusuojue", 1) < 350 )
		return notify_fail("你的金关玉锁诀等级不够。\n");
	
	if( me->query_skill_mapped("force") != "xiantian-gong" )
		return notify_fail("你的内功不对。\n");
	
	if( me->query("jingli") <2000)
		return notify_fail("你的精力不足，无法施展「金关玉锁诀」了。\n");
	if( me->query("neili") <2500)
		return notify_fail("你的内力不足，无法施展「金关玉锁诀」了。\n");
	if (skill<i*100)
	{
		return notify_fail("你的金关玉锁诀修行功夫不足，无法施展「金关玉锁诀」了。\n");
	}
	if( me->query_temp("xtg/yusuo") )
		return notify_fail("你已经在运「金关玉锁诀」了。\n");
	
	if((int)me->query("yusuo/degree")<3 )
		return notify_fail("你尚未领悟金关玉锁诀的精妙，现在无法施展金关玉锁诀。\n");
	
	
	me->receive_damage("neili", -300);	
	j=12-i;	
	
	if (CHAR_D->addbuff(me,"damage",to_int(skill/j),to_int(skill/30),"xtg/yusuo",HIR"$N先天功运转，将["+HIW+"金关玉锁二十四诀"+HIR+"]缓缓收功！"))
	{
		me->add("neili",-200*i);
	    me->add("jingli",-150*i);
		if (i<6)
		message_vision(HIR"$N"HIR"将「"HIC"金关玉锁二十四诀"HIR"」第"HIY+chinese_number(i)+HIR"重境界的功夫施展出来，中气充沛之极，举手投足间真如龙吟虎啸一般。\n" NOR, me);
	else message_vision(HBWHT+HIR"$N"HBWHT+HIR"将「"NOR+HIC"金关玉锁二十四诀"HBWHT+HIR"」第"HIY+chinese_number(i)+HIR"重境界的功夫施展出来，中气充沛之极，举手投足间真如龙吟虎啸一般。\n" NOR, me);
		
	}
	
	
	//me->add_temp("apply/damage", skill/j);

	
	//me->set_temp("xtg/yusuo", j ); 
	//me->add("neili",-200*i);
	//me->add("jingli",-150*i);
		
	//call_out("remove_effect",1, me, (int)skill/30);
	

	return 1;
}

void remove_effect(object me,int count)
{
        int skill,j;
        if(!me)  return;
		skill = me->query_skill("jinguan-yusuojue",1);

		j= me->query_temp("xtg/yusuo"); 

		if (!me->is_fighting()
			&&count--<0)
        {
		//	me->add_temp("apply/attack", -skill/8);
			me->add_temp("apply/damage", -skill/j);
			me->delete_temp("xtg/yusuo");

			message_vision(HIR"$N先天功运转，将["+HIW+"金关玉锁二十四诀"+HIR+"]缓缓收功！\n" NOR, me);

			return;
        }
		call_out("remove_effect",1,me,count--);
		return;
}

int help(object me)
{
	write(HIC"\n先天功之"MAG"「金关玉锁二十四诀」："NOR"\n\n");
        write(@HELP
	先天功是全真教王重阳最为重要的内功心法，修到
	高深境界，可飞花摘叶伤人于无形。少于第三重境
	界，无法施展金关玉锁诀。

	金关玉锁二十四诀是全真教重要的心法，是先天功
	的重要心法，修炼此诀，命中和伤害都会大幅增加
	当初马钰和江南七怪一起合战梅超风的时候，随口
	说句几句话，蕴含二十四诀的功夫，吓走梅超风。
		
	金关玉锁诀总共有九重境界，获得师傅指点后获得
	第一层境界，然后在修行室中闭关修炼。直达九重
	境界，境界越高，出手威力越大。金关玉锁诀和先
	天功修行休戚相关，是极为重要的辅助选项，切记
	金关玉锁诀和解密重数关联。

	指令：exert yusuo

要求：
	当前精力需求  300  以上；
	当前内力需求  500  以上；
	基本内功等级  350  以上,
	先天功法等级  350  以上,
	金关玉锁诀    350  以上
	激发内功先天功;
HELP
        );
        return 1;
}
