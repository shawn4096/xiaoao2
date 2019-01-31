//jindao-heijian 刀剑逆转
//by fqyy 2003.5.9
/*
设置成金刀黑剑的起手式，刀非刀，剑非剑，全凭一口真气。
裘千尺曾言。
*/
//by sohu@xojh
#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;
void remove_po(object me);
void remove_nizhuan(object me,int count,object weapon,object weapon2);

int perform(object me, object target)
{
	int i,skill;
	object *inv;
	object weapon2;
        object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("逆转诀只能对战斗中的对手使用。\n");

        
        if( me->query_skill("dodge") < 100 )
                return notify_fail("逆转诀需要超绝的轻功配合，方能有效施展！\n");

        if( me->query_skill("sword") < 100 )
                return notify_fail("你剑法未到炉火纯青之境，还不会使用逆转诀！\n");
        if( me->query_skill("blade") < 100 )
                return notify_fail("你刀法未到炉火纯青之境，还不会使用逆转诀！\n");
        if( me->query_skill("jindao-heijian",1) < 100 )
                return notify_fail("你金刀黑剑等级不够，还不会使用剑圈封闭对方！\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("你的内力不够使用逆转诀！\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("你的精力不够使用逆转诀！\n");

        if (!weapon)
                return notify_fail("你手中无剑怎能使用逆转诀？！\n");
        if (me->query_temp("jdhj/nizhuan"))
                return notify_fail("你正在使用逆转诀无法再逆转诀！\n");
        if (me->query_temp("jdhj/ponizhuan"))
                return notify_fail("你的金刀黑剑功夫被破无法使用逆转诀？！\n");

        if ( me->query_skill_mapped("sword") != "jindao-heijian"
          || me->query_skill_mapped("parry") != "jindao-heijian"
          || me->query_skill_mapped("blade") != "jindao-heijian"
          && userp(me))
             	return notify_fail("你必须先将黑剑金刀相互配合。\n");
       inv = all_inventory(me);
       for(i=0; i<sizeof(inv); i++) {
           if( inv[i]->query("equipped") || weapon == inv[i] ) continue;
		if (weapon->query("skill_type") == "blade") {
        	   if( inv[i]->query("skill_type") == "sword" ) 
		   {
			   weapon2 = inv[i];
			   i = 3;
			   break;
		   }
		}
		if (weapon->query("skill_type") == "sword") {
   	        if( inv[i]->query("skill_type") == "blade" ) 
		   {
			   weapon2 = inv[i];
			   i = 2;
			   break;
		   }
		}
       }
		if (!objectp(weapon2)) return notify_fail("你只有一种兵器就想逆转诀？\n");
		
		message_vision(MAG"\n$N猛然间长吸一口真气，闭住各处死穴，左刀右攻，右剑左击，使出他平生绝学"HIW"“逆转诀”"HIC"来。\n" NOR, me);
		message_vision(YEL"\n$N猛地左刀右攻，右剑左击，使出他平生绝学"HIW"“阴阳倒乱刃法”"HIC"来。\n"+
					"剑法本来阴柔，此时突然硬砍猛斫，变成了阳刚的刀法，而笨重的刀法却刺挑削洗，\n"+
					"全走单剑的轻灵路子，刀成剑，剑变刀，当真是奇幻无方。\n\n" NOR, me);
		
		if (!me->query("quest/tz/jdhj/pass")
			&&target->query("quest/tz/jdhj/pass")
			&&random(target->query_int())>me->query_int()/2)
		{
			message_vision(HIC"$n已经尽得裘千尺的真传，对于金刀黑剑的招式了若指掌，不再感觉任何神奇!\n"	
				+"只听$n轻蔑地一笑，轻吟道“刀非刀，剑非剑，刀即刀，剑即剑”！信手破了$N的金刀黑剑的招式！\n",me,target);
			me->add_temp("apply/parry", -skill/5);
			me->add_temp("apply/sword", -skill/5 );
			me->add_temp("apply/blade", -skill/5 );
			me->set_temp("jdhj/ponizhuan",skill);
			call_out("remove_po",skill/50,me);
			return 1;
		}

        skill = me->query_skill("jindao-heijian", 1);
        me->add_temp("apply/parry", skill/5 );
        me->add_temp("apply/sword", skill/5 );
        me->add_temp("apply/blade", skill/5 );

        me->set_temp("jdhj/nizhuan",skill);
		remove_nizhuan(me,skill/50,weapon,weapon2);

		me->add("neili", -200);
        me->add("jingli", -100);
        return 1;
}

void remove_nizhuan(object me,int count,object weapon,object weapon2)
{
        int skill;
		
		if ( !me||!me->query_temp("jdhj/nizhuan") ) return;
		skill=me->query_temp("jdhj/nizhuan");
	    if (count<0
			||!me->is_fighting()
			||me->query_skill_mapped("sword")!="jindao-heijian"
			||me->query_skill_mapped("blade")!="jindao-heijian"
			||me->query_skill_mapped("parry")!="jindao-heijian"
			||!me->query_temp("weapon")
			||!objectp(weapon2)
			||weapon != me->query_temp("weapon"))			
	    {
			me->add_temp("apply/parry", -skill/5);
			me->add_temp("apply/sword", -skill/5 );
			me->add_temp("apply/blade", -skill/5 );
			me->delete_temp("jdhj/nizhuan");
			message_vision(HIC"\n$N知道自己这刀法剑法逆转的破绽极大，不敢多用，慢慢收回了攻势。\n\n" NOR, me);
			return;
	    }
		call_out("remove_nizhuan",1,me,count--,weapon,weapon2);
}
void remove_po(object me)
{
        int skill;
		if ( !me) return;
		skill=me->query_temp("jdhj/ponizhuan");
	    me->add_temp("apply/parry", skill/5);
		me->add_temp("apply/sword", skill/5 );
        me->add_temp("apply/blade", skill/5 );

        me->delete_temp("jdhj/ponizhuan");
        message_vision(MAG"\n$N被对方破去的金刀黑剑起手式又逐渐恢复。\n\n" NOR, me);
        return;
}

string perform_name(){ return HBMAG+HIW"逆转诀"NOR; }

int help(object me)
{
        write(HIC"\n金刀黑剑"+HBYEL"「逆转诀」"NOR"\n");
        write(@HELP
	金刀黑剑是情人谷公孙芷的家传武功，左手金刀右手黑剑
	金刀以劈砍切削之攻击，黑剑乃刺扎削之效果，金刀以刚
	性为主，黑剑以阴性为主，两者组合后会令人防不胜防。
	尤其是铁掌裘千尺嫁给公孙芷后，对这门武功去腐存精加
	以完善。更达到炉火纯青之境。但此门武技的缺点也是显
	然，正如裘千尺所言“难练易破”，存在致命缺点。
	铁掌弟子可以凭借身份解救裘千尺并获得裘千尺的指点，
	则此门功夫将更上层楼。
	逆转诀是整个金刀黑剑的起手式，也是运转的心法所在
	是所有金刀黑剑的基础，一旦此招被破，所有的后续招式
	都将发不出来且自身功力受损严重。
		
	指令：perform sword(blade).nizhuan

要求：
	当前内力要求 1000 以上；
	当前精力要求 1000 以上；
	金刀黑剑等级 100 以上；
	基本轻功等级 100 以上；
	基本剑法等级 100 以上；
	基本刀法等级 100 以上；	
	激发刀法为金刀黑剑。
	激发剑法为金刀黑剑。
	激发招架为金刀黑剑。
	激发内功不限；
	手持刀(剑)类武器并身上带对应配套武器。

HELP
        );
        return 1;
}

