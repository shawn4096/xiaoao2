// shengsifu.c by sohu@xojh 生死符
// 
#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
       object obj,obj2,tar;
       string msg;
       int assi_int,damage;
       int me_strike;
       int target_dodge;
       int me_bmsg,tar_bmsg;
       if( !target ) target = offensive_target(me);
       if( !target 
		   ||!living(target)
		   || !me->is_fighting(target) )
                return notify_fail("「生死符」只能在战斗中使用。\n");       
       if(!target)
             return notify_fail("你想给谁下生死符？\n");
       if(!objectp(tar = present(target, environment(me))))
            return notify_fail("这里没有你想对付的这个人。\n");
       if(!tar->is_character())
                return notify_fail("看清楚一点，那并不是生物,你真有个性。\n");
       if(!living(tar))
               return notify_fail(tar->name()+"都这样了，还要摧残他，不觉得太狠了?\n");
       if(tar==me) return notify_fail("你要给自己下？你不是自虐狂吧！\n");
       
	   if(me->is_busy())
             return notify_fail("你先忙完再说拼命的事。\n");
       if(me->query_temp("weapon"))
             return notify_fail("你手中有兵器，无法施展生死符？\n");

	   if(environment(me)->query("no_fight"))
                return notify_fail("在这里好像施展不开！\n");
     
       if( (int)me->query_skill("liuyang-zhang", 1) < 450 )
             return notify_fail("你的天山六阳掌不够娴熟，不能种生死符。\n");
       if( (int)me->query_skill("beiming-shengong", 1) < 450 )
		  if( (int)me->query_skill("bahuang-gong", 1) < 450 )
             return notify_fail("你的北冥神功或八荒功不够娴熟，不能种生死符。\n");
	   if( me->query_skill_mapped("strike")!="liuyang-zhang"
			||me->query_skill_prepared("strike")!="liuyang-zhang")
             return notify_fail("你没有激发六阳掌，不能种生死符。\n");

	   if( (int)me->query("neili", 1) < 5000 )
             return notify_fail("你现在内力太弱，不能种生死符。\n");
       if (!objectp(obj=present("jiudai", me))&&!objectp(obj2=present("hu lu",me)))
             return notify_fail("你身上没有酒袋，或酒袋中没有液体，不能化水为冰。\n");
       
	   if (me->query_skill_mapped("force")=="beiming-shengong")
		   msg = HIB "$N左掌掌心中暗运内功，逆转北冥真气，将掌中酒水化成七八片寒冰，向$n飕飕飕连拍三掌。\n"NOR;
       else if (me->query_skill_mapped("force")=="bahuang-gong")
           msg = HIY "$N左掌掌心中暗运内功，逆转八荒六合唯我独尊功，将掌中酒水化成七八片寒冰，向$n飕飕飕连拍三掌。\n"NOR;
	   if (target->query_condition("shengsi_poison"))
	   {
		   return notify_fail("对方已经身中生死符，无需如此费劲。\n");
	   }
       //me->start_busy(1);
       me_strike=random( (int) me->query_skill("liuyang-zhang",1) );
       target_dodge=random(target->query_skill("dodge")) ;
       assi_int=random(me->query("int")-target->query("int"))+ random(3);
	   
	   damage=me->query_skill("liuyang-zhang",1)+me->query_skill("strike",1)+me->query_skill("force",1);
	   damage=damage*2+random(damage);
       
	   if( assi_int>1 && me->query_int()>50 )
            me_strike = me_strike*assi_int;
       if( me_strike > target_dodge
		  || random(me->query("neili"))>target->query("neili")/2
		  && (int) random(me->query_skill("liuyang-zhang",1)) > (int) tar->query_skill("liuyang-zhang",1)/4            
         ){
             msg += HIW "\n$p觉得肩间"HIR"“缺盆穴”"HIW"上微微一寒，跟着小腹"HIR"“天枢穴”"HIW"、大腿"HIR"“伏兔穴”"HIW"、上臂"HIR"“天泉穴”"HIW"也觉凉飕飕地。\n" NOR;
             target->apply_condition("shengsi_poison",2+random(2));
             if( (int) me->query_skill("liuyang-zhang",1)> 450 )
             {
                msg += HIY "\n於是$p忙催掌力抵挡，忽然间后颈"HIB"“天柱穴”"HIY"、背心"HIB"“神道穴”"HIY"、后腰"HIB"“志室穴”"HIY"三处也是微微一凉。\n"NOR;
                target->receive_wound("qi",damage/3,me);
                target->receive_wound("jing", damage/5,me);
                target->add_condition("shengsi_poison", 2+random(2));
             }
             target->receive_wound("qi",damage/2,me);
             target->receive_wound("jing", damage/4,me);
             //target->apply_condition("shengsi_poison",  target->query_condition("shengsi_poison")+ 10);
             me->add("neili", -random(1000));
             target->start_busy(1+random(2));
             
       } else if( (int) me->query_skill("liuyang-zhang",1) < (int) tar->query_skill("liuyang-zhang",1) ||
                random((int) me->query_skill("liuyang-zhang",1)) < (int) tar->query_skill("douzhuan-xingyi",1)
              ){
                        //反弹
                    msg += HIB "可是$p经验老道，潜运北冥真气于全身，用同样的手法，向$P发出三掌!\n"NOR;
                    msg += HIY "$P大叫一声“不妙!”，结果发出的小块寒冰尽数打在自己身上。\n"NOR;
                    me->apply_condition("shengsi_poison",1+random(1));
                    me->receive_wound("qi",damage/3,me);
                    me->receive_wound("jing", damage/5,me);
                    me->add("neili", -100);
                    me->start_busy(2+random(2));
                  
                  }else
              {
                 msg += "可是$p急忙闪在一旁，躲了开去。\n" NOR;
                 me->start_busy(1+random(2));
              }
    message_vision(msg, me, target);
    //me->start_perform(2,"生死符");
    return 1;
}
string perform_name(){ return HIB"生死符"NOR; }
int help(object me)
{
   write(WHT"\n天山六阳掌之「"HIB"生死符"WHT"」"NOR"\n");
         write(@HELP
	在天山童姥被虚竹救往西夏皇宫冰库藏匿期间，当天山折梅手传授给虚竹后，
	为对付李秋水便打算一并把天山六阳掌教给他，不料虚竹不肯助其杀人，坚不
	肯学，甚至起意离开。为此，天山童姥用谋在虚竹身上种落生死符，再假称教
	他破解之道，把生死符克星天山六阳掌的功夫倾囊相授。因而在李秋水追入冰
	库要杀天山童姥时，虚竹无意间就使出了第二招「阳春白雪」、第七招「阳关
	三叠」以及「阳歌天钧」三招接下李秋水的攻击。
	在天山童姥死后，虚竹继承灵鹫宫，因可怜三十六洞、七十二岛众人身受生死
	符苦楚，遂使用天山六阳掌帮他们拔除生死符，赢得众人真心相随，后来也凭
	借天山六阳掌力斗丁春秋，用生死符逼他就范受擒。
	需要注意，生死符纯以内力逆转转化寒冰而为，因此内力深厚和悟性极为重要。
    只有北冥神功、八荒功、小无相方可施展。

	指令: perform strike.shengsifu

要求： 
	八荒六合唯我独尊功450级 或北冥神功450级
	天山六阳掌等级 450 级；
	当前内力不小于 5000；
	身上持有酒袋且有酒水类液体；
        
HELP
    );
        return 1;
}

