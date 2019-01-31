//Create By lsxk@hsbbs 2007/6/14

#include <ansi.h>

inherit F_SSERVER;

string exert_name() {return HIM"紫霞剑意"NOR;}

int exert(object me, object target)
{
        object weapon = me->query_temp("weapon");  
        int skill=me->query_skill("zixia-gong",1);
        string jianyi_set;
        
        if( !target ) target = offensive_target(me);

        if(!me->is_fighting() )
                return notify_fail("「紫霞剑意」只能在战斗中使用。\n");

        if(userp(me) && !me->query("quest/huashan/zixia/pass"))
          if(me->query("quest/huashan")!="气宗")
                return notify_fail("紫霞神功乃华山气宗绝学，你非华山气宗弟子，哪里偷学来的紫霞神功？\n");

        if((int)me->query_skill("zixia-gong", 1) < 450 )
                return notify_fail("你的紫霞神功不够，不能使用「紫霞剑意」。\n");
    
        if((int)me->query_skill("force", 1) < 450 )
                return notify_fail("你的基本内功不够，不能使用「紫霞剑意」。\n");

        if ((int)me->query_skill("huashan-jianfa", 1) < 450 )
                return notify_fail("你的华山剑法不够娴熟，不能真正发挥「紫霞剑意」。\n");
    
        if (!weapon 
         || weapon->query("skill_type") != "sword")
                return notify_fail("你现在手中无剑，无法使用「紫霞剑意」。\n");
    
        if ((int)me->query("neili") < 1000 )
                return notify_fail("你现在内力太弱，不能使用「紫霞剑意」。\n");

        if ((int)me->query("jingli") < 500 )
                return notify_fail("你现在精力太少，不能使用「紫霞剑意」。\n");

        if ((int)me->query_temp("zxg/jianyi/君子"))
                return notify_fail("你正在使用「君子剑法」绝技。\n"); 

        if ((int)me->query_temp("zxg/jianyi/淑女"))
                return notify_fail("你正在使用「淑女剑法」绝技。\n"); 
   
        if ( (int)me->query_temp("zxg/jianyi/希夷") ) 
                return notify_fail("你正在使用「希夷剑法」。\n");
        if ( (int)me->query_temp(" zxg/jianyi/融合") ) 
                return notify_fail("你正在使用「剑意融合」。\n");
        if ( (int)me->query_temp("zxg/jianyi") ) 
                return notify_fail("你正在使用「紫霞剑意」。\n");

        if (me->query_skill_mapped("force") != "zixia-gong")
                return notify_fail("你的内功有误，无法使用「紫霞剑意」。\n");

        if(me->query("env/紫霞剑意")) jianyi_set = me->query("env/紫霞剑意");
	    // else return 0;
		//若没设定，则默认融合
        if(jianyi_set!="君子"
        && jianyi_set!="淑女"
        && jianyi_set!="希夷"
        && jianyi_set!="融合") jianyi_set = "融合";

        if( jianyi_set=="君子"){
            message_vision(HIM"$N暗催紫霞神功内劲附于手中"+weapon->name()+HIM"上，"+HIC"君子剑意"+HIM"随心而起，招数凌厉吓人！\n"+
            HIC"$N刹那间领会了以气驭剑之精要，便更将"+HIC"君子剑意"+HIM"发挥的淋漓尽致，剑招威力大增！\n"NOR,me,target);
            if (me->query_skill("zixia-gong",1)<350) me->start_exert(1,"「紫霞剑意」");
            if (me->query_skill("zixia-gong",1)<450) me->start_perform(6+random(3));
            me->add_temp("apply/damage",skill/6);
			me->add_temp("apply/strength",skill/15);
			
			me->set_temp("zxg/jianyi/君子",1);
            me->add("neili", -400);
            me->add("jingli", -200);              

            call_out("check_fight", 1, me, weapon, skill);
            return 1;
        }
        if(jianyi_set=="淑女"){
            message_vision(HIM"$N暗运紫霞剑意，手中"+weapon->name()+HIM"招数一变，剑招轻盈灵巧之极,正是"+HIG"淑女剑意"+HIM"！\n"+
            "$N手中"+weapon->name()+HIM"随意出招，手中剑招一一展开，行云流水，动作之灵巧，实所罕见！\n"NOR,me,target);
            if (me->query_skill("zixia-gong",1)<350) me->start_exert(1,"「紫霞剑意」");
            if (me->query_skill("zixia-gong",1)<450) me->start_perform(1,"「紫霞剑意」");
            me->add("neili", -300);
            me->add("jingli", -100);
            me->set_temp("zxg/jianyi/淑女",1);

            skill = (int)me->query_skill("huashan-jianfa", 1);
            me->add_temp("apply/dexerity",  skill/5);            
            me->add_temp("apply/dodge",  skill/4);
			me->add_temp("apply/attack",  skill/15);
            call_out("check_fight", 1, me, weapon, skill);
            return 1;
        }
        if(jianyi_set=="希夷"){
            message_vision(HIM"但见$N突然一个变招，剑招虽快，却无凌厉之势，实乃匪夷所思！正是华山剑法的"+HIW"希夷剑意"+
            HIY"\n$N紫霞剑意不绝，剑招竟舞得似一座铜墙铁壁，防御之力顿时大增，$n哪有半点可乘之机？！\n"NOR,me,target);
            if (me->query_skill("zixia-gong",1)<350) me->start_exert(1,"「紫霞剑意」");
            if (me->query_skill("zixia-gong",1)<450) me->start_perform(2,"「紫霞剑意」");
            me->add("neili", -300);
            me->add("jingli", -100);
            me->set_temp("zxg/jianyi/希夷",1);

           
            me->add_temp("apply/armor",  skill/2);
            me->add_temp("apply/parry",  skill/4*3);
            me->add_temp("apply/dodge",  skill/4*3);
            me->add_temp("apply/attack",  -skill/4);

            call_out("check_fight", 1, me, weapon, skill);
            return 1;
        }
        if(jianyi_set=="融合"&&(int)me->query_skill("huashan-jianfa", 1) > 550){
            message_vision(HIM"$N暗运紫霞神功，更将紫霞剑意彻底融合运用于剑法之中，招数使得纯熟之极！"+
            HIW"\n$N暗将华山剑法之君子，淑女，希夷三式剑意融合一气，招式恢弘气扬，剑意渐增雄浑之势！"+
			HIR"\n$N紫霞神功已臻至登峰造极的地步，将气驭剑之精要发挥的淋漓尽致，剑招威力大增！\n"NOR,me,target);
            //me->start_exert(1+random(2),"「紫霞剑意」");
            //me->start_perform(3+random(3),"「紫霞剑意」");
            me->add("neili", -1000);
            me->add("jingli", -600);
            me->set_temp("zxg/jianyi/融合",1);

            skill = (int)me->query_skill("huashan-jianfa", 1);
            me->add_temp("apply/damage",  skill/4);
            me->add_temp("apply/armor",  skill/6);
            me->add_temp("apply/parry",  skill/4);
            me->add_temp("apply/dodge",  skill/4);
			me->add_temp("apply/strength",  skill/25);
            me->add_temp("apply/dexerity",  skill/15);
			me->add_temp("apply/sword",  skill/10);

            call_out("check_fight", 1, me, weapon, skill);
            return 1;
        }


}

void check_fight(object me, object weapon,int skill)
{  
        object wep;

        if (!me) return;
        wep = me->query_temp("weapon");  
        if( !me->is_fighting()
         || !living(me)
         || me->is_ghost()
         || !wep
         //|| me->query_skill_mapped("parry") != "huashan-jianfa"
         //|| me->query_skill_mapped("sword") != "huashan-jianfa"
         || weapon != wep ){
             if(me->query_temp("zxg/jianyi/君子")){
                 me->add_temp("apply/damage",-skill/6);
				 me->add_temp("apply/strength",-skill/15);
                 me->delete_temp("zxg/jianyi");
             }
             else if(me->query_temp("zxg/jianyi/淑女")){
                 me->add_temp("apply/dexerity", -skill/5);            
                 me->add_temp("apply/dodge",  -skill/4);
			     me->add_temp("apply/attack",  -skill/15);
                 me->delete_temp("zxg/jianyi");
             }
             else if(me->query_temp("zxg/jianyi/希夷")){
                 me->add_temp("apply/armor",  -skill/2);
			     me->add_temp("apply/parry",  -skill/4*3);
                 me->add_temp("apply/dodge",  -skill/4*3);
                 me->add_temp("apply/attack",  skill/4);
                 me->delete_temp("zxg/jianyi");
             }
             else if(me->query_temp("zxg/jianyi/融合")){
                 me->add_temp("apply/damage",  -skill/4);
                 me->add_temp("apply/armor",  -skill/6);
                 me->add_temp("apply/parry",  -skill/4);
                 me->add_temp("apply/dodge",  -skill/4);
			     me->add_temp("apply/strength",  -skill/25);
                 me->add_temp("apply/dexerity",  -skill/15);
			     me->add_temp("apply/sword",  -skill/10);
                 me->delete_temp("zxg/jianyi");
             }
             else{
                 message_vision(HIR"程序出错，请立即通知在线wiz!\n"NOR, me);
             }
           if(living(me) && !me->is_ghost())
              message_vision(HIM"$N凝神收式，紫霞剑意缓缓收功，四周弥漫的剑气渐渐消失。\n"NOR, me);
           return;
        } 
        call_out("check_fight", 1, me, weapon, skill);
        return ;
}

int help(object me)
{
    write(YEL"\n紫霞神功「"HIM"紫霞剑意"YEL"」："NOR"\n");
    write(@HELP
	紫霞神功乃华山气宗的根基所在，所谓“华山九功，紫霞第一”
	既为此功的深刻注解，习得紫霞功后，整个华山武技将大幅提升
	剑意乃是紫霞功力高深后，将华山剑法的剑意蕴含在紫霞功中施
	展出来，威力不同凡响。
	紫霞剑意分为四种不同设置，使用为 【set 紫霞剑意 xx】
	其中，
	【君子】：乃是发出以紫霞内劲发出君子剑意，可以短时间
		内大幅提升伤害或臂力，属于攻击性类别。
	【淑女】：发出淑女剑意，可短时内大幅提升身法和轻功，
		和玉女十九式配合效果绝佳。
	【希夷】：将华山剑法的希夷剑意施展出来，短时间内大幅
		提升防御,牺牲一部分伤害。
	【融合】：将三式融合为一体。和单项相比较弱，但总体攻
		防效果明显。
	说明；350级小飞，450级大飞，550级紫霞功大成可使用融合
	要求：
		紫霞神功等级 450 以上；
		基本内功等级 450 以上；
		华山剑法等级 450 以上；
		当前内力要求 1000 以上；
		当前精力要求 500 以上。

HELP
    );
    return 1;
}
