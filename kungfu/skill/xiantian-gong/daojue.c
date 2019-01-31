// wuqi.c
// action@SJ 2009/1/17

#include <ansi.h>
inherit F_CLEAN_UP;
string exert_name(){ return CYN"大道歌诀"NOR; }

string *koujue= ({ 
CYN"大道初修通九窍，九窍原在尾闾穴"NOR,
MAG"先从涌泉脚底冲，涌泉冲过渐至膝"NOR,
WHT"膝过徐徐至尾闾，泥丸顶上回旋急"NOR,
YEL"秘语师传悟本初，来时无余去无踪"NOR,
BLU"历年尘垢皆磨净，遍体灵明耀太虚"NOR,
RED"修真活计有何凭，心死群情今不生"NOR,
HBGRN+HIW"精气充盈功行具，灵光照耀满神京"NOR,
HIC"金锁关穿下鹊桥，重楼十二降宫室"NOR,

}); 


int exert(object me, object target)
{
	int skill,count,i,j;
	string kou_jue;
	
	kou_jue=koujue[random(sizeof(koujue))];
	if( me->query("neili") < 100 )
		return notify_fail("你的内力不够。\n");

	if( me->query_skill("xiantian-gong", 1) < 100 )
		return notify_fail("你的先天功等级不够。\n");

	if( me->query_skill_mapped("force") != "xiantian-gong" )
		return notify_fail("你的内功不对。\n");
	
	if (me->is_fighting()&&!me->query("quest/qz/xtg/daojue"))
	{
		return notify_fail("你的先天功尚未到打通生死玄关的地步，无法在战斗中运功。\n");
	}
	
	if( me->query_temp("xtg/daojue") )
		return notify_fail("你已经在运「大道歌诀」了。\n");

	skill = me->query_skill("xiantian-gong",1);
	
	me->receive_damage("neili", -300);
	
	message_vision(HIW"$N默念道家「大道歌诀」之"+kou_jue+HIW",一股真气若有若无，绵绵若存。\n" NOR, me);
	
	if (!me->is_fighting() )
	{
		if (CHAR_D->addbuff(me,"parry",to_int(skill/20),to_int(skill/20),"xtg/daojue",HIW"$N的["+HIR+"大道歌诀"+HIW+"]运行完毕，将内力收回丹田。"))
		message_vision(WHT"$N真气缓缓流动，说不出来的舒服惬意，运转一周天后功力元转如意！\n" NOR, me);	

	}
	else if (me->is_fighting()&&me->query("quest/qz/xtg/daojue/pass"))
	{
	//乾坤内丹，外丹效果
		if (me->query("gender")=="女性")
		{			
		if(CHAR_D->addbuff(me,"armor|parry|dodge",to_int(skill/10),to_int(skill/10),"xtg/daojue",MAG"$N的先天功缓缓收功，将丹田的坤丹凝聚成一团！"))
		 {
			
			//me->add_temp("apply/armor", skill/10);
			//me->add_temp("apply/parry", skill/10);
			//me->add_temp("apply/dodge", skill/10);
			//me->add_temp("apply/constitution",skill/15);
			//坤丹效果
			message_vision(MAG"$N的先天功缓缓运转不绝，周身真气愈加显得充盈，辛苦修炼的坤内丹渐渐显现出来！周身防御力大增！\n" NOR, me);

		 }
		}
		if (me->query("gender")=="男性")
		{
			if(CHAR_D->addbuff(me,"damage",to_int(skill/10),to_int(skill/10),"xtg/daojue",HIR"$N的先天功缓缓收功，将丹田的乾丹凝聚成一团！"))			
                   {
	                message_vision(HIR"$N的先天功缓缓运转不绝，辛苦修炼的乾内丹渐渐显现出来！手上筋骨力气大增！\n" NOR, me);
                   }
		}
			
			//me->add_temp("apply/damage", skill/10);
			//me->add_temp("apply/constitution",skill/30);
			//乾丹效果
			//message_vision(HIR"$N的先天功缓缓运转不绝，辛苦修炼的乾内丹渐渐显现出来！手上筋骨力气大增！\n" NOR, me);

	}
	//	me->set_temp("xtg/dj_fighting",skill);
	
	
    //每运行一次，增加一次周天数
	 me->add("quest/qz/xtg/daojue/times",1);

	//me->set_temp("xtg/daojue", skill ); 
		
	//call_out("remove_effect", (int)skill/10, me );
	me->add("neili",-50);
	
	
	
	//如果修炼得法，过程中会冲关
	
		kou_jue=koujue[random(sizeof(koujue))];		
		count=me->query("quest/qz/xtg/daojue/times");
		
		i = 20;
		if(me->query("m-card-vip")) i =  18;
		if(me->query("y-card-vip")) i =  15;
		if(me->query("buyvip"))     i =  10;
		i=random(i);
		j=random(me->query("kar"));
		
		if( i<3
			&& me->query("kar")<31
			&& random(count)>5000
			&& random(me->query("con"))>=30
			&& j > 26 
            && !me->query("quest/qz/xtg/daojue/pass"))			
		{
			tell_object(me,"\n你忽然福灵心至，联想起早期自己所修炼先天功的的种种心得，两下印照。\n"NOR);
			tell_object(me,HIG"\n你运气冲关，忽然会阴穴一痛，一股劲气若隐若现，自由运转，灵活无比。\n"			    
							 +"你多年辛苦修炼的大道歌诀终于达成，忍不住仰天长啸。\n"NOR);
			command("shout "+kou_jue);
			command("shout 贫道今日先天功略有小成，全真教先天功果然天下第一！");
			me->set("quest/qz/xtg/daojue/pass",1);
			log_file("quest/xtgdaojue", sprintf("%8s(%8s) 机缘巧合领悟先天功道诀彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前根骨取值：%d|经验：%d。\n",
				me->name(1),me->query("id"), i,j,me->query("con"),me->query("combat_exp")) );			
			
			tell_object(me,HIR"恭喜先天功道诀豁然贯通，先天功更上一层楼!\n");    

		}	

	

	return 1;
}

void remove_effect(object me)
{
        int skill,count,i,j;
      	string kou_jue;
		kou_jue=koujue[random(sizeof(koujue))];

        if(!me)  return;

		skill = me->query_temp("xtg/daojue"); 
		count=me->query("quest/qz/xtg/daojue/times");

		if (me->query_temp("xtg/dj_fighting") )
        {
			if (me->query("gender")=="女性")
			{
				me->add_temp("apply/armor", -skill/8);
				me->add_temp("apply/parry", -skill/8);
				me->add_temp("apply/dodge", -skill/8);
				me->add_temp("apply/constitution",-skill/15);
				//坤丹效果
				message_vision(MAG"$N的先天功缓缓收功，将丹田的坤丹凝聚成一团！\n" NOR, me);

			}
			if (me->query("gender")=="男性")
			{
				me->add_temp("apply/damage", -skill/10);
				me->add_temp("apply/constitution",-skill/30);
				//乾丹效果
				message_vision(HIR"$N的先天功缓缓收功，将丹田的乾丹凝聚成一团！\n" NOR, me);

			}
			me->delete_temp("xtg/dj_fighting");

        }
		//如果修炼得法，过程中会冲关
		i = 20;
		if(me->query("m-card-vip")) i =  18;
		if(me->query("y-card-vip")) i =  15;
		if(me->query("buyvip"))     i =  10;
		i=random(i);
		j=random(me->query("kar"));
		
		if( i<3
			&& me->query("kar")<31
			&& random(count)>5000
			&& random(me->query("con"))>=30
			&& j > 26 ) 
		{
			tell_object(me,"\n你忽然福灵心至，联想起早期自己所修炼先天功的的种种心得，两下印照。\n"NOR);
			tell_object(me,HIG"\n你运气冲关，忽然会阴穴一痛，一股劲气若隐若现，自由运转，灵活无比。\n"			    
							 +"你多年辛苦修炼的大道歌诀终于达成，忍不住仰天长啸。\n"NOR);
			command("shout "+kou_jue);
			command("shout 贫道今日先天功略有小成，全真教先天功果然天下第一！");
			me->set("quest/qz/xtg/daojue/pass",1);
			log_file("quest/xtgdaojue", sprintf("%8s(%8s) 机缘巧合领悟先天功道诀彻底融会贯通。随机数i取值：%d|随机富源j取值：%d|当前根骨取值：%d|经验：%d。\n",
				me->name(1),me->query("id"), i,j,me->query("con"),me->query("combat_exp")) );
			
			
			tell_object(me,HIR"恭喜先天功道诀豁然贯通，先天功更上一层楼!\n");      

		}
	
 
	me->delete_temp("xtg/daojue");
       
	tell_object(me, HIW"你的["+HIR+"大道歌诀"+HIW+"]运行完毕，将内力收回丹田。\n"NOR);
	return;
}

int help(object me)
{
	write(HIC"\n先天功之「大道歌诀」："NOR"\n\n");
        write(@HELP
	先天功是全真教王重阳最为重要的内功心法，修到
	高深境界，可飞花摘叶伤人于无形，其中大道歌诀
	乃是先天功入门的基本心法，若寻常时修炼，运使
	大道歌诀修炼打坐，内力转换效果有不小的增幅。
	若战斗时运转大道歌诀，男女修炼的乾丹和坤丹的
	效果又自不同。请玩家自己尝试体验。
	注意：战斗中运使大道歌诀需要解密

	指令：exert daojue

要求：
	最大内力  100  以上；
	当前内力  100  以上；
	先天功法  100  以上,
	激发内功先天功
HELP
        );
        return 1;
}
