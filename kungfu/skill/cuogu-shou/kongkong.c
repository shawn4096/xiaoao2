// kongkong.c 妙手空空
// Modified by sohu@xojh
// 偷对方武器或宝物

#include <ansi.h>
inherit F_SSERVER;

string perform_name() { return HBWHT+HIW"妙手空空"NOR; }

int perform(object me, object who)
{
     
		object target;
		target = present(who,environment(me));
        
       if( !objectp(target)
			|| !target->is_character())
             return notify_fail("「妙手空空」只能对同一地点的活人使用。\n");
         if( objectp(me->query_temp("weapon")) )
               return notify_fail("你必须空手使用「妙手空空」！\n");
        if( environment(me)->query("no_fight") )
                return notify_fail("这里禁止行窃。\n");
		
		if( (int)me->query_skill("cuogu-shou", 1) < 350 )
                return notify_fail("你的分筋错骨手不够娴熟，无法施展出「妙手空空」。\n");
		if( (int)me->query_skill("stealing", 1) < 200 )
                return notify_fail("你的妙手空空不够娴熟，无法施展出「妙手空空」。\n");
        if ((int)me->query_skill("force", 1) < 350)
                return notify_fail("你的基本内功火候不够，无法施展出「妙手空空」。\n");
        if ( (int)me->query("max_neili") < 5000)
                return notify_fail("你的最大内力不够，无法施展出「妙手空空」。\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("你的真气不够，无法施展出「妙手空空」。\n");
		if (me->query_dex() < 60)
                return notify_fail("你的后天身法不够，无法施展出「妙手空空」。\n");
        if (me->query_skill_prepared("hand") != "cuogu-shou"
		    || me->query_skill_mapped("parry") != "cuogu-shou"
            || me->query_skill_mapped("hand") != "cuogu-shou")
                return notify_fail("你现在激发不对，无法使用「妙手空空」进行攻击！\n");
        if (me->query_temp("cgs/kongkong"))
                return notify_fail("你正在使用「妙手空空」绝技！\n");
        
        if( !wizardp(me) && wizardp(target) )
                return notify_fail("玩家不能对巫师使用此技能。\n");


		if ( userp(me) && userp(target) && me->query("no_pk"))
			return notify_fail("你已经金盆洗手了，就不要偷别人东西了。\n");

		if ( userp(me) && userp(target) && target->query("no_pk"))
			return notify_fail(target->name()+"已经金盆洗手了，就不要偷他的东西了。\n");
		
		if ( target->query("job_npc") || target->query("no_quest"))
			return notify_fail(target->name()+"看起来没什么油水，不用偷了。\n");

		if( !target->is_character() || target->is_corpse() || target->is_container() )
            return notify_fail(target->name()+"里的东西用的着偷吗？随便拿就行了。\n");

	    if( me->is_busy()) return notify_fail("你正忙着呢。\n");


		message_vision(WHT"$N脚下轻功发动，不动声色，悄然接近$n的身边！\n"NOR,me, target);
		
		if (random(me->query_skill("cuogu-shou",1)+me->query_skill("stealing",1))>target->query_skill("parry",1)/2
			||random(me->query_int(1))>target->query_int(1)/2)
		{
			message_vision(HBYEL"$n身形一顿，为$N身形所阻，不由地身形一滞！\n"NOR,me, target);
			
			target->add_busy(1);
			me->set_temp("cgs/kongkong",1);
		//	if (objectp(me)&&objectp(target))
			call_out("start_steal",1,me,target);
		}	
		else{
			message_vision(HIY"$n豁然发现$N的手伸向自己的包裹！顿时大怒！\n"NOR,me, target);
			me->add_busy(2);
			target->kill_ob(me);
		}
		me->add("neili",-150);
		me->add("jingli",-100);

        return 1;	
}

void start_steal(object me, object target)
{
        object ob,*inv;
		int i;
        if (!me) 
return;
		me->delete_temp("cgs/kongkong");
		
		if (!target) return;
		
		message_vision(RED "$n只觉似乎被$N轻轻撞了一下，猛然抬头看去，却见$N已经飘然远去！\n"NOR,me, target);
		inv = all_inventory(target);
		
		for (i=0;sizeof(inv);i++ )
		{
			ob=inv[random(sizeof(inv))];
			switch (me->query("env/妙手空空"))
			{
				  case "黄金":
					if (ob->query("id")=="gold")
					{
						ob->move(me);
						message_vision(HBYEL "$n下意识的一摸，发现自己的黄金不见了，顿时心中大怒，冲$n远去的背影破口大骂！\n"NOR,me, target);
						
					}
					break;
				 case "白银":
					if (ob->query("id")=="silver")
					{
						ob->move(me);
						message_vision(HBYEL "$n下意识的一摸，发现自己的白银不见了，顿时心中大怒，冲$n远去的背影破口大骂！\n"NOR,me, target);
						
					}
					break;
				case "宝物":
					if (ob->query("treasure"))
					{
						ob->move(me);
						message_vision(HBYEL "$n下意识的一摸，发现自己的"+ob->query("name")+"宝物不见了，顿时心中大怒，冲$n远去的背影破口大骂！\n"NOR,me, target);
					}
					break;
				case "稀有品":
					if (ob->query("unique"))
					{
						ob->move(me);
						message_vision(HBYEL "$n下意识的一摸，发现自己的"+ob->query("name")+"不见了，顿时心中大怒，冲$n远去的背影破口大骂！\n"NOR,me, target);
					}
					break;
				default:break;
			}

		}

		me->start_perform(2, "妙手空空");
		return;
}
int help(object me)
{
        write(HIG"\n分筋挫骨手之「妙手空空」："NOR"\n");
        write(@HELP
	分筋错骨手是江南七怪之二圣手书生朱聪的绝技。朱聪
	手法精妙，以分筋挫骨将对方点穴或拿捏重要经脉，瞬
	间将对方拿住并给与重创。
	注意：此技能为妙手书生独家绝技，需解密方可修习。

	set 妙手空空 (黄金、白银、宝物、稀有品)则在双方交
	错之际，顺手牵羊而去。实乃江湖中一罕有绝技，但此
	技能为武林人士所不齿且极容易招惹人嫉恨，切记切记！

	指令：perform hand.cuogu

要求：
	基本内功的等级 350  以上；
	分筋错骨手等级 350  以上；
	基本手法的等级 350  以上；
	妙手空空的等级 200  以上；
	最大的内力要求 5000 以上；
	当前内力的要求 500  以上；
	后天身法的要求 60   以上；
	激发且备手法为分筋错骨手；
	空手且备手法为分筋错骨手；
	内功不限。

HELP
        );
        return 1;
}


