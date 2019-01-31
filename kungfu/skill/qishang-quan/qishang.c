// qishang.c 
// Update By lsxk@hsbbs 2007/6/11

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int remove_effect(object me,int count);
int remove_effect(object me,int count);

string *songs = ({"五行之气调阴阳","损心伤肺摧肝肠","藏离精失意恍惚","三焦齐逆兮魂魄飞扬"});
string *num_color = ({HIR,HIC,HIG,HIM,HIY,HIB,HBRED});


int perform(object me, object target)
{
	string song,ncolor;
	int skill;

	song = songs[random(sizeof(songs))];
	ncolor=num_color[random(sizeof(num_color))];

	skill=me->query_skill("qishang-quan",1);
	
	if( !target ) target = offensive_target(me);

	if( !objectp(target)
	 || !target->is_character()
	 || !me->is_fighting(target) || !living(target) )
		return notify_fail("「七伤总诀」只能在战斗中对对手使用。\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("你必须空手使用「七伤总诀」！\n");

   if( (int)me->query_skill("qishang-quan",1) < 500 )
		return notify_fail("你的七伤拳不够娴熟，不会使用「七伤总诀」！\n");
   if( !me->query("quest/mj/qsq/zongjue/pass"))
		return notify_fail("你的七伤拳尚未融会贯通，不会使用「七伤总诀」！\n");

   if(!me->query_skill("jiuyang-shengong", 1) || (int)me->query_skill("jiuyang-shengong",1)< 200 )
   if(userp(me) && (int)me->query_skill("force",1) < 500 )
           return notify_fail("你的特殊内功等级不够，不能使用「七伤总诀」！\n");
   if( (int)me->query_con(1) < 38 )
		return notify_fail("你的身体根骨不够强壮，不能使用「七伤总诀」！\n");

   if( (int)me->query("max_neili") < 9000 )
		return notify_fail("你的内力太弱，不能使用「七伤总诀」！\n");

   if( (int)me->query("neili") < 1500 )
		return notify_fail("你的内力太少了，无法使用出「七伤总诀」！\n");

   if( (int)me->query("jingli") < 1000 )
		return notify_fail("你的精力太少了，无法使用出「七伤总诀」！\n");
	if( me->query_skill_mapped("parry") != "qishang-quan"
	&& me->query_skill_mapped("parry") != "qiankun-danuoyi")
		return notify_fail("你需要激发招架为七伤拳，方能使用「七伤总诀」进行攻击。\n");

	if (me->query_skill_prepared("cuff") != "qishang-quan"
	 || me->query_skill_mapped("cuff") != "qishang-quan")
           return notify_fail("你激发不对，现在无法使用「七伤总诀」进行攻击。\n");

    if(me->query_temp("qsq/qishang"))
           return notify_fail("你正在施展「七伤总决」，不用费劲了！\n");

	message_vision(HIY"\n$N双脚呈丁字步站定，长鲸吸水般的长吸一口气，施展出七伤拳绝技"+HBRED+HIY"「七伤总诀」"HIY"！\n"NOR,me);
	message_vision(WHT"$N眼射精光，朗声念出句似歌非歌、似诗非诗的拳诀：“"+ncolor+song+WHT"”，砰的一拳击向$n的前胸！\n"NOR,me, target);

	if (random(me->query_str())>target->query_dex()/2)
	{
		target->add_busy(1+random(3));
		message_vision(YEL"$n被这七股劲气打中，不由地身子一歪，瞬间有些手脚忙乱！\n"NOR,me,target);
	}
  
	
	me->add_temp("apply/attack",skill/3);
	me->add_temp("apply/damage",skill/6);
	me->add_temp("apply/cuff",skill/6);
	me->add_temp("apply/strength", skill/8);
	
	me->set_temp("qsq/qishang",skill);
	
	remove_effect(me,(int)skill/50);
//调用额外攻击
	
	call_out("qishang_attack",1+random(1),me,target);

    me->add("neili",-400);
	me->add("jingli",-300);
	return 1;
}
//总决效果

int remove_effect(object me,int count)
{
	int skill;
	if (!me) return 0;
	skill=me->query_temp("qsq/qishang");
	if (!me->is_fighting()
		||count<0
		||me->query_skill_prepared("cuff")!="qishang-quan"
		||me->query_skill_mapped("cuff")!="qishang-quan")
	{
		me->add_temp("apply/attack",-skill/3);
		me->add_temp("apply/damage",-skill/6);
		me->add_temp("apply/cuff",-skill/6);
		me->add_temp("apply/strength", -skill/8);

		me->delete_temp("qsq/qishang");
		message_vision(HIY"$N面色潮红，长吁一口真气，缓缓按下躁动的真气。\n"NOR,me);
		return 1;
	}

	call_out("remove_effect",1,me,count--);
	
}

int qishang_attack(object me,object target)
{

	int ap,dp,damage,qi_wound;
	string msg;
	
	if (!me||!target) return 0; 

	ap=me->query_skill("qishang-quan");
	dp=me->query_skill("dodge");
   
    if(target->is_busy()) dp=dp/2;
	if (me->query_skill_prepared("cuff")!="qishang-quan"
		||me->query_skill_mapped("cuff")!="qishang-quan")
	{
			return 0;
	}
	//tell_object(me, num_color[(int)target->query_temp("qishang")]+"在刚一触到"+target->name(1)+"的身体时，你便暗暗发力，将隐藏在拳内的第"+HIW+chinese_number(1+(int)target->query_temp("qishang"))+NOR+num_color[(int)target->query_temp("qishang")]+"股内劲送了过去！\n"NOR);

	tell_object(me, num_color[random(sizeof(num_color))]+"七伤拳拳法刚猛，劲力触到"+target->query("name")+"的身体，你便暗暗发力，将隐藏在拳内的第"+HIW+chinese_number(1+(int)target->query_temp("qishang"))+NOR+num_color[random(sizeof(num_color))]+"股内劲送了过去！\n"NOR);

	
	if ( random(ap + dp ) > dp/2
		||random(me->query_str())>target->query_dex()/2)
	{
        qi_wound = ((int)me->query_skill("cuff",1)+(int)me->query_skill("qishang-quan",1)) ;
        
		if(wizardp(me)) write("damage is :"+qi_wound+"!\n");
		
		target->receive_damage("qi", qi_wound, me);
		target->receive_wound("qi", qi_wound/2, me);
		target->add_busy(1);
        
		if(userp(me) && me->query("env/damage"))
			tell_object(me,WHT"你对"+ target->query("name") +"造成了"HIR+qi_wound+ WHT"点攻击伤害。\n"NOR);
		
		if(userp(target)&& target->query("env/damage"))
			tell_object(target,WHT""+ me->query("name") +"的攻击对你造成了"HIR+qi_wound+ WHT"点伤害。\n"NOR);
		if((me->query("neili") + me->query_con(1)*(20+random(40))) < target->query("neili"))
			tell_object(me, HIR"你只觉"+target->name()+"体内内力极强，你暗藏在拳内的各种力道根本送不出去！\n"NOR);
		else{
			damage = target->query_str(1)/2;
			damage += target->query_int(1)/2;
			damage += target->query_con(1)/2;
			damage += target->query_dex(1)/2;
                   damage /= 8;
                   tell_object(target, HIW"你一晃眼，只见"+me->name(1)+"的拳已经打在你的身上，跟着一股说不出的暗劲顺势传了过来！\n"NOR);
			me->add("neili", -400);
			me->add("jingli", -50);
			me->start_perform(1, "「七伤总诀」");
			target->set("qishang", damage);
            if(!target->query_temp("qishang"))
			{
				target->add_temp("apply/strength", -damage);
				target->add_temp("apply/dexerity", -damage);
				//target->add_temp("apply/intelligence", -damage);
				target->add_temp("apply/constitution", -damage);               
                target->add_condition("no_perform", 6);
				target->set_temp("qishang",damage);
				//添加描述 by renlai
				if (QUEST_D->queryquest(me,"was/save")) 
				{
		              target->set_temp("qszj",1);
					  target->add_condition("qishang_poison", 20);
		              message_vision(RED"$N因得崆峒五老宗维侠的秘传，七伤决得以补全，$n被这股劲气打中，五脏内腑均已受创！\n"NOR,me,target);
	            }
				else  target->add_condition("qishang_poison", 9);
						
				target->start_call_out( (: call_other, __FILE__, "remove_qishang", target ,damage :), me->query_skill("cuff", 1)/4);
            }
              target->add_temp("qishang", 1);
		}
		
	}
	else {
		me->start_busy(1+random(2));
		me->add("neili", -150);
		me->add("jingli", -200);
		message_vision(YEL"只见$p轻轻一转身，已经绕到了$P身后。而$N却因劲力打空不受控制，头脑眩晕！\n"NOR,me,target);
	}
	return 1;


}

void remove_qishang(object target,int damage)
{
	if( !target || !target->query_temp("qishang")) return;
	
	target->add_temp("apply/strength", damage);
	target->add_temp("apply/dexerity", damage);
	//target->add_temp("apply/intelligence", damage);
	target->add_temp("apply/constitution", damage);
	target->clear_condition("no_perform");
	target->delete_temp("qishang");
	tell_object(target, HIW"\n终于体内那几股七伤拳的暗劲在遍布你的全身之后，开始慢慢散去了。\n"NOR);
}

string perform_name(){ return HBWHT+HIB"七伤总诀"NOR; }

int help(object me)
{
	write(HIR"\n七伤拳之「七伤总诀」"NOR"\n");
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
	「七伤总诀」是七伤拳的总纲，功力深厚后施展出来
	一方面可以伤敌，有效打压对方的防御，同时也会短
	时间内提升自己的拳法战斗力。
	注意：七伤拳解开乾坤大挪移融合和九阳神功后大飞
	且本门武功因是谢逊偷自崆峒武技，不需本门内功
	
	指令：perform cuff.qishang

要求：
	最大内力需求 9000 以上；
	当前内力需求 1500 以上；
	当前精力需求 1500 以上；
	七伤拳法等级 500 以上；
	基本内功等级 500 以上；
	后天膂力需求 65 以上；
	激发拳法为七伤拳；
	激发招架为七伤拳或乾坤大挪移：
	备拳法为七伤拳且空手。
HELP
        );
        return 1;
}
