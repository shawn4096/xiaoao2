// xinjing.c 
// By River
// Modified by darken@SJ

#include <ansi.h>
inherit F_CLEAN_UP;
string *pictures=({
  HIY"少思、"YEL"少念、"HIC"少欲、"HIR"少事、"HIB"少语、"MAG"少笑"HIW,
  YEL"少愁、"CYN"少乐、"HIG"少喜、"HIR"少怒、"HIY"少好、"RED"少恶"HIW,
  HIC"多思"HIG"则"HIW"神怠，"HIB"多念"MAG"则"HIY"精散"HIW,
  HIR"多欲"YEL"则"BLU"智损，"MAG"多事"RED"则"HIG"形疲"HIW,
  HIB"多语"CYN"则"RED"气促，"HIR"多笑"HIC"则"BLU"肝伤"HIW,
  MAG"多愁"YEL"则"HIR"心慑，"RED"多乐"BLU"则"HIY"意溢"HIW,
  HIW"多喜"HIG"则"HIY"忘错"MAG"昏乱，"HIC"多怒"HIR"则"HIB"百脉"HIG"不定"HIW,
  HIG"多好"RED"则"BLU"专迷"HIG"不治，"HIW"多恶"HIB"则"MAG"焦煎"CYN"无宁"HIW
});
string exert_name(){ return HIW"玉女心经"NOR; }
int exert(object me)
{
        int skill;
        string picture;

        if((int)me->query("neili") < 500 ) 
                return notify_fail("你的内力不够。\n");
		if((int)me->query("max_neili") < 1500 ) 
                return notify_fail("你的最大内力不够。\n");
        if((int)me->query_temp("ynxj/xinjing")) 
                return notify_fail("你已经在运功中了。\n");

        if((int)me->query_skill("yunu-xinjing",1 ) < 100)
                return notify_fail("你的玉女心经等级不够，还不能体会十二少和十二多之妙处。\n");
		if((int)me->query_skill("force",1 ) < 100)
                return notify_fail("你的基本内功等级不够，还不能体会十二少和十二多之妙处。\n");
        if( me->query_skill_mapped("force") != "yunu-xinjing")
                return notify_fail("你现在不能使用「心经」字诀。\n");

        if( me->query("gender") == "无性" )
                return notify_fail("你无根无性，如何能领悟玉女心经的「心经」字诀。\n");
                
        skill = (int)me->query_skill("yunu-xinjing", 1);
        if (me->query("quest/jiuyingm/pass"))
        {
			skill=skill+me->query_skill("jiuyin-zhengong",1);
        }
		//if (skill > 250) skill = 250+ (skill-250)/5;
      
		me->add("neili", -(200+ random(200)));
        picture = pictures[random(sizeof(pictures))];
        message_vision(MAG"$N屏气凝神，口中默念"HIW"「"+picture+"」"MAG"的玉女心经正反要诀。\n" NOR, me);
          
        me->add_temp("apply/intelligence", (int)me->query_skill("yunu-xinjing",1)/10);
        me->add_temp("apply/dexerity", skill/5);

        //350小飞，增加命中
		if (skill > 350) {
          me->add_temp("apply/attack", skill/5);
        }
		if (skill > 450) {
          me->add_temp("apply/defense", skill/10);
        }
		//玉女心经第一变
		if (me->query("quest/gumu/ynxj/pass") )
		{
			message_vision(HIM"$N玉女心经运转不绝，周身劲气涌动,面色一片晕红,若隐若现,隐隐形成一股气罩笼罩周身。\n"NOR,me);
			me->add_temp("apply/dodge", skill/5);
            me->add_temp("apply/parry", skill/5);
            me->add_temp("apply/armor", skill/5);
		}
		//玉女心经第二变
		if (me->query("quest/jiuyingm/pass"))
		{
          
		  me->add_temp("apply/attack", skill/5);
          me->add_temp("apply/damage", skill/8);
		  me->add_temp("apply/whip", skill/5);
		  me->add_temp("apply/sword", skill/5);
		  message_vision(HBMAG+HIW"$N已经将玉女心经和九阴真经融合贯通，玉女心经的威力至此方显。\n"NOR,me);
		}        

        me->set_temp("ynxj/xinjing", skill);
		call_out("remove_effect",1,me,(int)skill/10);
        
		if( me->is_fighting() 
			&& userp(me)
			&& me->query_skill("yunu-xinjing",1)<500)
			me->start_busy(1+random(2));
        if ( !me->query("quest/gumu/ynxj/pass")) 
			me->start_exert(2,"「心经」字诀");
        return 1;
}

void remove_effect(object me, int count)
{       
    int skill;
	if(!me || !objectp(me)) return;
	skill = me->query_temp("ynxj/xinjing");
    
    if (count < 1 || me->query_skill_mapped("force")!="yunu-xinjing")
    {	    
        me->add_temp("apply/intelligence", -(int)me->query_skill("yunu-xinjing",1)/10);
        me->add_temp("apply/dexerity", -skill/5);
        if (skill > 350)
        {
            me->add_temp("apply/attack", -skill/5);
        }
		if (skill > 450)
        {
            me->add_temp("apply/defense", -skill/10);
        }
		if (me->query("quest/gumu/ynxj/pass"))
		{
			me->add_temp("apply/dodge", -skill/5);
            me->add_temp("apply/parry", -skill/5);
            me->add_temp("apply/armor", -skill/5);
		}
        if (me->query("quest/jiuyingm/pass"))
		{
			me->add_temp("apply/attack", -skill/5);
			me->add_temp("apply/damage", -skill/8);
			me->add_temp("apply/whip", -skill/5);
			me->add_temp("apply/sword", -skill/5);
			
		}
        me->delete_temp("ynxj/xinjing");
        if (me->query("quest/jiuyingm/pass"))
			tell_object(me, HBMAG+HIW"你的玉女心经「心经」字诀运功完毕，将内力收回丹田。\n"NOR);
		else tell_object(me, HIM"你的玉女心经「心经」字诀运功完毕，将内力收回丹田。\n"NOR);
		return;
    }
	count=count-1;
	call_out("remove_effect", 2, me, count);
	return;
}

int help(object me)
{
        write(HIW"\n玉女心经之"HIY"「心经」："NOR"\n");
        write(@HELP
	林朝英心念王重阳，竭尽心智，研究出了克制
	全真派武功的《玉女心经》。但因幻想终有一
	日能与意中人并肩击敌，要练到最后一章终须
	二人分使全真剑法和玉女剑法相互应援，分进
	合击。最终二人因高傲不群的性格未能长相厮
	守，所以林朝英所收皆为女徒，并要她们立誓
	终身不出古墓，除非有一男子甘愿为其献出生
	命，誓言方破。因此，此墓中人武功虽强，却
	未起门派名字，后因其居住古墓，李莫愁行走
	江湖自称师门为古墓派。
		
	古墓派玉女功养生修炼之“十二少，十二多”正
	反要诀：“少思、少念、少欲、少事、少语、少
	笑、少愁、少乐、少喜、少怒、少好、少恶。
	行此十二少，乃养生之都契也。多思则神怠，
	多念则精散，多欲则智损，多事则形疲，多
	语则气促，多笑则肝伤，多愁则心慑，多乐
	则意溢，多喜则忘错昏乱，多怒则百脉不定，
	多好则专迷不治，多恶则焦煎无宁。此十二
	多不除，丧生之本也。
	
	古墓弟子全身武功系于内功，玉女心经总共
	分为三变，初期技能随小飞和大飞不断增强
	命中和防御，第二变开始玉女心经女性的优
	势得以发挥，而第三变后玉女心经的威力将
	彻底释放。500级彻底大飞，解开第二变，取
	消激发busy。
	
	指令：yun xinjing
	
要求：
	玉女心经等级 100 级以上；
	基本内功等级 100 级以上；
	最大内力要求 1500 以上；      
	当前内力要求 500  以上；
			    
                
HELP
        );
        return 1;
}