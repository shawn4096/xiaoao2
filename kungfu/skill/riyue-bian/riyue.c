// riyue 日月鞭-日月
// campsun

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{

        int i = me->query_skill("riyue-bian", 1) /2;
     
        int j = me->query("jiali") + 20;//原来是10
   
        string msg,dodge_skill;

		object weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !objectp(target) || !me->is_fighting(target) )
                return notify_fail("「日月轮转」只能在战斗中对对手使用。\n");

        if (!weapon || weapon->query("skill_type") != "whip")
                return notify_fail("手中没有武器,如何使用「日月轮转」！\n");

        if( (int)me->query_skill("riyue-bian", 1) < 450 )
                return notify_fail("你的日月鞭法不够娴熟，不会使用「日月轮转」。\n");

        if( (int)me->query_skill("yijin-jing", 1) < 450 )
                return notify_fail("你的易筋经等级不够，不能使用「日月轮转」。\n");

        if( (int)me->query_skill("buddhism", 1) < 200 )
                return notify_fail("你的禅宗心法等级不够，不能使用「日月轮转」。\n");
          
        if( (int)me->query("max_neili") < 15000 )
				return notify_fail("你现在内力修为太弱，不能使用「日月」。\n");
      
        if( (int)me->query("jingli") < 500 )
				return notify_fail("你现在体力太少，不能使用「日月」。\n");
        if ( me->query_skill_mapped("whip") != "riyue-bian")
				return notify_fail("你激发鞭法不对，不能使用「日月」。\n");

        if ( me->query_skill_mapped("parry") != "riyue-bian")
				return notify_fail("你招架不对，不能使用「日月」。\n");
    
        if ( me->query_skill_mapped("force") != "yijin-jing")
				return notify_fail("你必须使用少林心法才能催动「日月轮转」。\n");
               
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在内力太弱，不能使用「日月轮转」。\n");

        msg = HIC "$N口中高宣佛号，使出日月鞭中「日月轮转」绝技，手中长索滚动飞舞，宛若灵蛇乱颤，自上而下劈向$n,\n" NOR;
        msg += HIC "接着$N手腕一抖，便如张牙舞爪的墨龙相似，急升而上，又往$n扑到。\n"NOR;
        message_vision(msg, me, target);
   
        me->set_temp("ryb/riyue", 1);
        me->add_temp("apply/attack", i);
        me->add_temp("apply/damage", j);
  //第一招
		
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3); 
   //第二招
		if( me->is_fighting(target) ) 
    		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
    //第三招
		if( me->is_fighting(target) && (int)me->query_skill("riyue-bian", 1) > 220)  
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

        me->add_temp("apply/damage", -j);
        me->add_temp("apply/attack", -i);
		
		if(me->is_fighting(target) )
		{
 	
			if(random(10)<5)
			{          
				msg = HIY"\n紧跟着$N高宣“阿弥陀佛！”，使出"HIR"「日 轮 」"HIY"字诀，手中长索一扬，向$n的咽喉点去，索头未到，索上所挟\n"
                 + "劲风犹如红日当空，令对方一阵气窒，只听见「啪啪」几声巨响，索头昂起，便如一条假死的毒蛇忽地反\n"
                 + "噬挥动，带动无数风沙，呼啸而出。\n"NOR; 
				message_vision(msg, me, target);
				
				me->set_temp("ryb/rilun",1);

				if( me->is_fighting(target) ) 
					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				if( me->is_fighting(target) ) 
  					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
				if( me->is_fighting(target) ) 
  					COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

				me->delete_temp("ryb/rilun");      
				me->add("neili", -400);
				me->add_busy(2+random(2));

			} 
			else{ 
				msg = HIC "\n紧跟着$N又宣“我佛慈悲！”，使出"HIB"「月 转」"HIC"字诀，内力返照空明，功力精纯，不露棱角，手中长索舞动时\n"
                     +"瞧不见半点影子无声无息，似缓实急，却又无半点风声，如鬼似魅，说不尽的诡异莫名。\n"NOR;
				
				message_vision(msg,me,target);
      
				
					msg=HIR"结果$n一不小心，登时淹没在漫天鞭影之中。\n"NOR;
					me->delete_temp("ryb/riyue");      
					target->addt_busy(2+random(2));
					msg+=HIG"这鞭头悄然昂起，无声之中突袭而至，直接刺中$n的前胸，鲜血迸溅！\n"NOR;
					//msg+=HIY"这鞭头悄然昂起，无声之中突袭而至，直接刺中$n的前胸，鲜血迸溅！\n"NOR;

					target->receive_damage("qi",5000+random(2000),me);
					target->receive_wound("qi",2000+random(2000),me);
					target->recieve_damage("jing",1000+random(1000),me);

					message_vision(msg,me,target);        
					target->set_temp("must_be_hit",1);
					me->add_temp("apply/damage",i/2);
					me->add_temp("apply/whip",i/2);
					//msg+=HIY"这鞭头悄然昂起，无声之中突袭而至，直接刺中$n的前胸，鲜血迸溅！\n"NOR;
					me->set_temp("ryb/yuelun",1);
					if( me->is_fighting(target) ) 
  						COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
					me->add_temp("apply/damage",-i/2);
					me->add_temp("apply/whip",-i/2);
					target->delete_temp("must_be_hit");
					
					me->delete_temp("ryb/yuelun");
					
					
					me->add("neili",-400);

           /*      }
				else {
					dodge_skill = target->query_skill_mapped("dodge");
					if( !dodge_skill ) dodge_skill = "dodge";
                    msg=HIR"$N见势不好，抽身急退，躲过了漫天鞭影。\n"NOR;
					message_vision(msg,target);
					me->delete_temp("ryb/riyue");      
					me->add("neili",-200);
                }*/
			}
       		if (me->query("quest/em/zzr/pass"))
			{
						message_vision(HIB"眼见$n攻势如潮，全力压向$N身前，日月鞭灵动性逐渐丧失，$N灵光一闪，施展出九阴真经中的"HIR"「飞龙诀」"HIB"招式顺手而出！\n"NOR,me,target);
						message_vision(HIW"\n$N身形一闪一晃，右手"+weapon->name()+HIW"猛的甩出，正如天外游龙，出手如电，矢矫而至。\n"NOR, me,target);

						call_out("jiuyin_feilong",1,me,target);
			}

	} 
	me->start_perform(5, "「日月轮转」");
	me->add("neili",-200);

    me->delete_temp("ryb/riyue");      
	return 1;

}
int jiuyin_feilong(object me,object target)
{
	
	int lvl;
	object weapon;
	weapon=me->query_temp("weapon");

	lvl=me->query_skill("yinlong-bian",1)/3;
	me->set_skill_mapped("whip","yinlong-bian");

	me->add_temp("apply/attack", lvl);
	me->add_temp("apply/damage", lvl/2);
//	me->add_temp("apply/claw", lvl);
	me->add_temp("apply/whip", lvl);
//第一招
	me->set_temp("feilong", 1);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);

//第二招
	if ( me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), random(2)?1:3);
     if(objectp(weapon)) weapon->unequip(); 
//第三招 少林空手或九阴白骨抓？？
	if (objectp(target)&&me->is_fighting()&&me->query("env/日月神鞭")=="九阴白骨抓")
	{
	
		if( me->is_fighting(target) 
		&& me->query_skill_prepared("claw") == "jiuyin-baiguzhua" 
		&& me->query_skill_mapped("claw") == "jiuyin-baiguzhua" )
		{
        
              	message_vision(HIM"\n$N运使九阴白骨爪，指爪挥动间九阴真气嘶嘶作响，威力大增，招数诡异狠辣，威力无比！\n"NOR, me,target);
                target->set_temp("must_be_hit",1);
                target->add_busy(3);
                COMBAT_D->do_attack(me, target, 0, random(2)?1:3);
				//COMBAT_D->do_attack(me, target, 0, random(2)?1:3);                      
               	message_vision(HIM"\n$N左手跟着前探，九阴白骨爪五指便抓向$n胸口,眼见这一抓之下，立时便是开膛破胸之祸！\n"NOR, me,target);               
                COMBAT_D->do_attack(me, target, 0, random(2)?1:3);
                target->delete_temp("must_be_hit") ; 
          }

	}
	if (objectp(target)&&me->is_fighting()&&me->query("env/日月神鞭")=="少林武技")
	{
                target->set_temp("must_be_hit",1);
                target->add_busy(3);
                COMBAT_D->do_attack(me, target, 0, random(2)?1:3);
				//COMBAT_D->do_attack(me, target, 0, random(2)?1:3);                      
                COMBAT_D->do_attack(me, target, 0, random(2)?1:3);
                target->delete_temp("must_be_hit") ; 

	}
	if (objectp(target)&&me->is_fighting()&&me->query("env/日月神鞭")=="环套")
	{
                message_vision(HIG"\n$N鞭子一抖，状如毒蛇，瞬间施展出「束缚诀」的招式，束鞭成环套中$n！\n"NOR, me,target);
                message_vision(HIR"\$n顿觉周身无法移动分毫，胸口宛如压了一块大石，全身劲气外泄如潮！\n"NOR, me,target);

                target->add_condition("no_exert",2);
				target->add_condition("no_perform",2);
				target->recieve_damage("jing",1000+random(1000),me);
				target->recieve_damage("jingLI",2000+random(2000),me);
				message_vision(RED"\$N劲力汹涌，忽然鞭头昂起，一招「直刺诀」戳向$n的胸口大穴！\n"NOR, me,target);
				call_out("attack_zhici",1,me,target);
                
	}

    if(objectp(weapon)) weapon->wield(); 
	me->add_temp("apply/attack", -lvl);
	me->add_temp("apply/damage", -lvl/2);
	//me->add_temp("apply/claw", lvl);
	me->add_temp("apply/whip", -lvl);
	message_vision(HIB"$N方才一番疾攻，颇为耗力，长吁一口气后，换回日月鞭的招式，心境也回到了宝相庄严！\n"NOR,me);

	me->set_skill_mapped("whip","riyue-bian");
	me->start_perform(5, "「日月轮转」");
	me->delete_temp("feilong");

	return 1;
}

int attack_zhici(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

    //    if (userp(me) && ! me->query("can_perform/riyue-bian/shang"))
      //          return notify_fail("你还没有受过高人指点，无法施展「直刺诀」。\n");
                 
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「直刺诀」只能在战斗中对对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "whip")
                return notify_fail("你使用的武器不对。\n");

        if (me->query_skill("force",1) < 200)
                return notify_fail("你的内功的修为不够，不能使用这一绝技！\n");

        if (me->query_skill("riyue-bian", 1) < 200)
                return notify_fail("你的日月鞭法修为不够，目前不能使用直刺诀！\n");
        if (me->query_skill("buddhism", 1) < 150)
                return notify_fail("你的日月鞭法修为不够150，目前不能使用直刺诀！\n");

        if (me->query("neili") < 500)
                return notify_fail("你的真气不够，无法使用直刺诀！\n");
        if (me->query("jingli") < 500)
                return notify_fail("你的精力不够，无法使用直刺诀！\n");

        if (me->query_skill_mapped("whip") != "riyue-bian")
                return notify_fail("你没有激发日月鞭法，不能使用直刺诀！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
        
		message_vision(HIY "$N" HIY "嘿然冷笑，手中的" + weapon->query("name") +
              HIY "一振，霎时变得笔直，如同流星一般飞刺向$n" + HIY "！\n"
				+"那" + weapon->query("name") +HIY "化成一条笔直的兵刃，如长矛，如杆棒，疾刺而至!\n" NOR,me,target);


        ap = me->query_skill("whip",1)+me->query_skill("riyue-bian",1);

        dp = me->query_skill("parry",1)+me->query_skill("dodge",1);

		me->add("jingli", -200); 

        if (random(ap)>dp / 3
			||random(me->query_skill("force",1))>target->query_skill("force",1)/2)
        {
               damage = ap+me->query_skill("force",1);
                damage=me->query_str()*damage/20;
				
				me->add("neili", -300); 

				target->receive_damage("qi",damage,me);
				target->receive_wound("qi",damage/2,me);

				if (me->query("env/damage"))
				{
					tell_object(me,WHT"你对"+target->query("name")+"造成"+damage+"的杀伤值!\n");
					tell_object(me,WHT"你对"+target->query("name")+"造成"+damage/2+"的伤害值!\n");
				}
                message_vision(HIR "只见$p" HIR "一声惨叫，" + weapon->query("name") + HIR "竟然插在$p" + HIR "的身上，直接对穿而过，鲜血飞溅数尺，惨不堪言！\n" NOR,me,target);
                                         
        } else
        {
                me->add("neili", -100);
                me->start_busy(3);
				message_vision( CYN "可是$p" CYN "运足内力，奋力挡住了$P" CYN "这神鬼莫测的一击！\n"NOR,me,target);
                me->start_busy(1 + random(2));

        }
		me->start_perform(3,"直刺诀");

        return 1;
}

string perform_name(){ return HIY"日"HIW"月"HIC"轮转"NOR; }
int help(object me)
{
	write(HIC"\n日月鞭「日月轮转」："NOR"\n");
	write(@HELP
	日月鞭是少林三大武器之一，乃是修炼到极高阳刚之意后的由刚化柔的武功
	此时少林内功以达内力返照空明，功力精纯，不露棱角的境界。越长越是灵
	动，越短功力越强。长短收缩，自由收发于心。张无忌救谢逊，孤身犯险，
	以一抵抗三大神僧，那一战固然成就了张无忌的威名，但同时，少林三老的
	日月鞭也名扬天下。
	日转是以阳刚之力，直接将鞭子化作长枪大戟，刺穿对方。而月轮转则是以
	鞭子的阴柔之力缠住，耗掉对方的精气。日月轮转乃是少林日月鞭的阳刚与
	阴柔的大乘之技。日轮强调攻击，月轮比较阴柔，且如果解开周芷若的谜题
	获得周芷若的指点，那么会得到银龙鞭的武技融合，在月轮绝技中带出飞龙
	的招式。
			
	注意：
		set 日月神鞭 九阴白骨抓  必须备九阴抓能出的是九阴白骨抓招式
		set 日月神鞭 少林武技    出的是自己所备的少林空手
		set 日月神鞭 环套        圈鞭成环，将对手陷入忙碌中且耗精
	
	指令：perform whip.riyue

要求：	
	最大内力 15000 以上；      
	当前内力 1000 以上； 
	当前精力 500 以上； 
	易筋经等级 450 以上；
	日月鞭法等级 450 以上；
	禅宗心法等级 450 以上；
	激发鞭法为日月鞭法；
	激发日月鞭法为招架；
	激发易筋经为内功；
	装备长鞭类兵器。     
HELP
	);
	return 1;
}

