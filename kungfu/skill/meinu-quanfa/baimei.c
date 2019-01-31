// baimei.c by sohu@xojh


#include <ansi.h>

inherit F_SSERVER;

string perform_name() {return MAG"百媚横生"NOR;}

int calc_damage(int,int,object,object);

int perform(object me, object target)
{
        object weapon;
        string msg,result;
        int i,total,mp,tp; 
        mp=me->query_per();tp=target->query_per();
        if( !target ) target = offensive_target(me);

        if( !objectp(target) || !target->is_character() || !me->is_fighting(target) || !living(target))
                return notify_fail("「百媚横生」只能在战斗时使用！\n");
 
        if( me->query("per")<28 )                              
             return notify_fail("你的先天容貌着实丑陋，施展「百媚横生」只能令人作呕！\n");  

        if( objectp(weapon=me->query_temp("weapon")) )                              
                return notify_fail("你手里拿着武器，无法施展「百媚横生」！\n");               
        
        if( (int)me->query_skill("meinu-quanfa", 1) < 100 )
                return notify_fail("你的美女拳法还不够熟练，不能使用「百媚横生」！\n");
		if( (int)me->query_skill("cuff", 1) < 100 )
                return notify_fail("你的基本拳法还不够熟练，不能使用「百媚横生」！\n");

        if (me->query_skill_mapped("cuff") != "meinu-quanfa"||me->query_skill_prepared("cuff") != "meinu-quanfa")
                return notify_fail("只有使用美女拳法时才能使用「百媚横生」！\n");
		if (me->query_skill_mapped("parry") != "meinu-quanfa")
                return notify_fail("只有使用美女拳法时才能使用「百媚横生」！\n");

        if( (int)me->query_skill("yunu-xinjing", 1) < 100 )
                return notify_fail("你的玉女心经还不够熟练，不能使用「百媚横生」！\n");       

        if((int)me->query("jingli") <500)
                return notify_fail("你现在精力不足，不能使用「百媚横生」！\n");       
        if((int)me->query("max_jingli") <1000)
                return notify_fail("你现在最大精力不足，不能使用「百媚横生」！\n");       

        if((int)me->query("max_neili") < 1500) 
                return notify_fail("你现在最大内力不足，不能使用「百媚横生」！\n");      		
        if((int)me->query("neili") < 800) 
                return notify_fail("你现在内力不足，不能使用「百媚横生」！\n");      	
        if( me->query_skill_mapped("force") != "yunu-xinjing")
                return notify_fail("你现在所使用的内功同玉女心经相抵触，不能使用「百媚横生」。\n");
        me->add("jingli",-100);
        me->add("neili",-random(200));
        if (me->query("gender")=="男性"&&me->query("per")>=28)
        {
			msg=HIG"$N虽然是身为男子，但因身残容貌着实不弱于女子，当下做女人状，轻声浅笑，身形款款之状。\n"+
				"趁$n稍微诧异走神之际，施展出古墓派绝技「百媚横生」。\n"NOR;
        }
        msg = HIC"$N轻声浅笑，身形款款，依依如柳，乘$n稍稍走神之机，施展出古墓派绝技「百媚横生」"NOR;
        if(random((int)me->query_skill("meinu-quanfa",1)) > (int)target->query_skill("parry",1)/2
          ||random((int)me->query("combat_exp"))> (int)target->query("combat_exp")/2
          ||target->is_busy() ){
                me->start_busy(1);
                total = 0;
                msg +=MAG "\n\n$N使出一招「"HIM"文姬归汉"MAG"」，纤腰轻扭，身子跃起空中，双掌挥舞，宛如挥指胡笳，连拍十八次拍向$n的小腹，\n"+
					"这招乃是美女拳中威力甚大的一招，一鼓作气势如虎，和先前娇滴滴的模样全然不同。\n"NOR;
                i = calc_damage((int)me->query_skill("meinu-quanfa",1),(int)me->query_skill("yunu-xinjing",1),me,target);
				if (me->query("gender")=="女性"&&mp>tp&&me->query("per")>29) 
					i=i*me->query_per(1)/100;
                total += i;
               if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
			//化学
				
				if (userp(target) && total>2000) total=2000+random(1000);
			   
                target->receive_damage("qi", total, me );
               // target->receive_wound("qi", total/6 , me);
                result = COMBAT_D->damage_msg(i,"瘀伤");
                result = replace_string( result, "$l", "腹部" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0); 

                msg =HIG "\n$N使出一招「"HIM"萍姬针神"HIG"」，神情肃然，俏眼圆睁，伸出一根芊芊玉手，戳向$n的右眼，\n"+
                         "还没待$n反应过来，$N莲步款款，身子一转，正好转到$n的右侧，这一指却是指向了$n的太阳穴。\n"NOR;

                //i = calc_damage((int)me->query_skill("meinu-qunfa",1),(int)me->query_skill("yunu-xinjing",1),me,target);
				//if (me->query("gender")=="女性"&&mp>tp&&me->query("per")>29) i=i*3/2;
                total += i/6;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
				
				if (userp(target) && total>2500) total=2500+random(1000);

                target->receive_damage("qi", total, me );
               // target->receive_wound("qi", total/3 , me);
                result = COMBAT_D->damage_msg(i,"瘀伤");
                result = replace_string( result, "$l", "面部" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     

                msg =HIR "\n$N使出一招「"HIB"古墓幽居"HIR"」，只见$N右手支颐，左手轻轻挥出，口中长叹一声，脸现寂寥之意。\n"+
                         "这招本为杨过年少时所创，虽为当时顽皮无聊之举，但经过他武功大成改良后却威力甚大。\n"NOR;

               // i = calc_damage((int)me->query_skill("meinu-quanfa",1),(int)me->query_skill("yunu-xinjing",1),me,target);
				//if (me->query("gender")=="女性"&&mp>tp&&me->query("per")>29) i=i*3/2;
                total += i/6;
                if(wizardp(me)) tell_object(me,sprintf("damage: %d \n",i));
				
				if (userp(target) && total>3000) total=3000+random(1000);

                target->receive_damage("qi", total, me );
                target->receive_wound("qi", total/4 , me);
                result = COMBAT_D->damage_msg(i,"内伤");
                result = replace_string( result, "$l", "胸口" );
                msg += result;
                message_vision(msg,me,target);
                COMBAT_D->report_status(target, 0);     
                if(wizardp(me)) tell_object(me,sprintf("Total damage: %d \n",total));
                me->start_perform(3,"「百媚横生」");
        }
         else {
                msg +=MAG "\n\n$N使出一招「"HIM"文姬归汉"MAG"」，纤腰轻扭，身子跃起空中，双掌挥舞，宛如挥指胡笳，连拍十八次拍向$n的小腹，\n"NOR;
                msg += "但是$n看破了$N的企图，没有上当，急急忙忙向旁边一闪，躲了过去。\n";
                msg =HIG "\n$N使出一招「"HIG"萍姬针神"HIG"」，神情肃然，俏眼圆睁，伸出一根芊芊玉手，戳向$n的右眼，\n"+
                         "还没待$n反应过来，莲步款款，身子一转，正好转到$n的右侧，这一指却是指向了$n的太阳穴。\n"NOR;
                msg += "$n吃了一惊，但随即冷静下来，在空中猛一蹬腿踢向$N面门，$N只得松开了手。\n";
                msg =HIR "\n$N使出一招「"HIB"古墓幽居"HIR"」，只见$N右手支颐，左手轻轻挥出，口中长叹一声，脸现寂寥之意。\n"+
                         "这招本为杨过年少时所创，虽为无聊之举，但却威力甚大。\n"NOR;
                msg += "$n被$N制住，但临危不乱，以内力护住要害，同时高高跃起，翻身以头撞地，把$N撞了出去！\n";
                message_vision(msg,me,target);
                me->start_busy(1+random(2));
                me->start_perform(4,"「百媚横生」");
        }
        return 1;
}

int calc_damage(int skill,int skill2,object me,object target)
{
			int i;

            i = (random(skill+skill2)*2-(int)target->query_skill("parry",1))*10;
            if (i<0) i = -i;
            i += random(i/2);

            if(!userp(me)) i = i/3;

			return i; 
}

int help(object me)
{
   write(WHT"\n美女拳法「"MAG"百媚横生"WHT"」："NOR"\n");
   write(@HELP
	为《神雕侠侣中》古墓派祖师林朝英所创。拳法每一招
	都是模拟一位古代美女，将千百年来美女变幻莫测的神
	韵仪态化入其中，招数名称极有诗意，像红玉击鼓、红
	拂夜奔、绿珠坠楼、文姬归汉、红线盗盒、木兰弯弓、
	班姬赋诗、嫦娥窃药、蛮腰纤纤、丽华梳妆、萍姬针神、
	西子捧心、洛神微步、曹令割鼻……每一招都出自一个历
	史典故，施展出来或步步生莲，或依依如柳，于婀娜妩
	媚中击敌制胜。杨过曾以此拳法智胜金轮法王的二弟子
	力大无比的达尔巴。
	注意：悟性大于40可以和天罗地网互备
	
	perform cuff.baimei
   
要求：
	当前内力要求 800 以上；
	当前精力要求 500 以上；
	最大精力要求 1000 以上
	最大内力要求 1400 以上；
	美女拳法等级 100 以上；
	基本拳法等级 100 以上；
	玉女心经等级 100 以上；
	先天容貌要求 27  以上
	激发并准备拳法为美女拳法；
	激发招架为美女拳法
	女性有优势，男性偏弱。
		
HELP
   );
   return 1;
}
