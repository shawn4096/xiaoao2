// liaoyuan.c 燎原百击

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int lvl, skill, skill1,jiali,i;
	object weapon;
	string name;

	weapon = me->query_temp("weapon");
	if (weapon) name = weapon->query("name");

	if( !target ) target = offensive_target(me);
     
	if( !objectp(target)
	 || !me->is_fighting(target) )
		return notify_fail("燎原百击只能在战斗中对对手使用。\n");

	if (!weapon
	 || weapon->query("skill_type") != "sword"
	 || me->query_skill_mapped("sword") != "huifeng-jian")
		return notify_fail("你手里没有剑，无法使用燎原百击！\n");             

	if( (int)me->query_skill("huifeng-jian",1) < 450 )
		return notify_fail("你的回风拂柳剑不够娴熟，不能使用燎原百击！\n");
      
	if( (int)me->query_skill("sword",1) < 450 )
		return notify_fail("你的基本剑法等级不够，不能使用燎原百击！\n");  

	if( (int)me->query_skill("jieshou-jiushi", 1) < 450 )
		return notify_fail("你的截手九式等级不够，不能使用燎原百击！\n");
      
	if( (int)me->query_skill("linji-zhuang", 1) < 450 )
		return notify_fail("你的临济十二庄等级不够，不能使用燎原百击！\n");

	if (me->query_skill_mapped("force") != "linji-zhuang")
		return notify_fail("你所使用的内功不对。\n");
	
	if( (int)me->query("max_neili") < 8000 )
		return notify_fail("你的内力太弱，不能使用燎原百击！\n");

	if( (int)me->query("neili") < 1500 )
		return notify_fail("你的内力太少了，无法使用出燎原百击！\n");
	if (me->query_skill_prepared("hand") != "jieshou-jiushi"
	 || me->query_skill_mapped("hand") != "jieshou-jiushi"
	 || me->query_skill_mapped("parry") != "huifeng-jian")
		return notify_fail("你的激发技能不对，现在无法使用燎原百击进行攻击。\n");
	if (me->query_temp("liaoyuan"))
		return notify_fail("你正在使用燎原百击攻击。\n");
	skill = me->query_skill("huifeng-jian", 1);
	skill1 = me->query_skill("jieshou-jiushi", 1);
    lvl = (skill + skill1) /8; 
	if (me->query_skill("huifeng-jian",1)>450&&me->query("em_powerup")&&!userp(target))
      lvl+=me->query_skill("linji-zhuang",1)/4;//由8 调成5
	else lvl+=me->query_skill("linji-zhuang",1)/8;
	
	jiali = me->query("jiali");

	message_vision(HIW"\n$N长啸一声，身子往高空升去，转身之间刚好拦住$n面前，右手中"+name+HIW"挥舞如风，剑光乍崩，剑气刹那间填满空间。\n"NOR, me,target);
	message_vision(HIC"左手使出截手九式，带起无数小气旋，威力顿然加强。\n"NOR, me,target);
	me->add("neili", -350); 
	me->add("jingli", -100); 
//500级后飞跃
	if ( skill > 500)
        lvl = to_int(lvl/6.0* skill/500.0);
	if (me->query("quest/emei/hfj/liaoyuan/pass"))
	{
		i=3;
		if ( skill > 500)
        //lvl = to_int(lvl/6.0* skill/300.0);
		lvl=lvl+lvl/5;
		message_vision(HIR"$N对于燎原剑法的奥义已经融会贯通，此时施展起来更是得心应手，威力大增！\n"NOR,me,target);
	}else {
		i=1;
		if ( jiali > 100)
		{
			me->set("jiali", 100);
			me->set_temp("lyjiali", 1);
		}
	}	
    if(!userp(me)) lvl = lvl / 3;
	if (me->query("class")=="bonze")
	   lvl+=lvl/4; //由6调成4,出家人威力增加
    if (me->query_skill("jiuyin-zhengong",1)>150)
    {
		message_vision(HBBLU+HIW"$N施展剑法的过程中将九阴真经的功夫自然施展出来，招式更见凌厉。\n"NOR, me);
		lvl +=lvl/6;
    }
	    me->set_temp("liaoyuan", 1);
        me->add_temp("apply/attack", lvl );
        me->add_temp("apply/damage", lvl );
        me->add_temp("apply/sword" , lvl );
        me->add_temp("apply/dexerity",lvl /8);
	    me->add_temp("apply/hand", lvl);


     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);

	if ( me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);//以前是random(4) by lsxk@hsbbs
                	
    if ( me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);//以前是random(4) by lsxk@hsbbs
   
         weapon->unequip(); 
		 //启动劫手九式，可能出现四招，判断剑诀
	if ( me->is_fighting(target) && me->query_skill("jieshou-jiushi",1) > 350)
       {                
	           if(me->query("env/截手九式") && me->query("emei/jianjue")) 
			   {
                  target->set_temp("must_be_hit",1);
                  COMBAT_D->do_attack(me, target, 0, i); //以前是random(4)?1:3  by lsxk@hsbbs
                  target->delete_temp("must_be_hit"); 
				}
               COMBAT_D->do_attack(me, target, 0, 3); //以前是random(4)?1:3  by lsxk@hsbbs                                       
       }
	if ( me->is_fighting(target) && me->query_skill("jieshou-jiushi", 1) > 450)
      {
              if(me->query("env/截手九式") && me->query("emei/jianjue"))
			  { 
                //target->set_temp("must_be_hit",1);
                COMBAT_D->do_attack(me, target, 0, i);
				//target->delete_temp("must_be_hit") ;
			  }
              COMBAT_D->do_attack(me, target, 0, i); 

      }
      weapon->wield();
	  //解开九阴或九阳，则威力大释放一招大招
	  
     if (me->query("emjy/pass")&&me->query_skill("jiuyin-zhengong",1)>150)
     {
		 message_vision(HIY"$N忽然间灵光一闪，以九阴之术纵身跃起,运起临济庄中的九阳之意，极其优美的挥出一剑！\n"NOR,me,target);
		 me->set_temp("hfj/ronghe",1);
		 target->set_temp("must_be_hit",1);
		 me->add_temp("apply/damage",lvl/4);
         COMBAT_D->do_attack(me, target, 0, 3);
		 me->add_temp("apply/damage",-lvl/4);
		 target->delete_temp("must_be_hit");
		 me->delete_temp("hfj/ronghe");
     }


	if ( me->query_temp("lyjiali"))
	{
 		me->set("jiali", jiali);
		me->delete_temp("lyjiali");
       }
        me->add_temp("apply/attack", -lvl);
	    me->add_temp("apply/sword", -lvl);
        me->add_temp("apply/damage", -lvl);
        me->add_temp("apply/dexerity", -lvl /8);
	    me->add_temp("apply/hand", -lvl);
        me->start_busy(1);
	    me->delete_temp("liaoyuan");
        me->start_perform(5, "燎原百击");
	
		return 1;
		
}

string perform_name(){ return HIR"燎原百击"NOR; }

int help(object me)
{
	write(HIR"\n回风拂柳剑之「燎原百击」："NOR"\n\n");
	write(@HELP
	回风拂柳剑乃是峨眉不传之秘，开山祖师郭襄因少年时期经历
	极为丰富，阅历非常深厚后来一生奇遇不断，结合家传武学，
	武功造诣极为深厚。后来因暗恋杨过不得，郁郁终生，四十岁
	后大彻大悟，出家为尼，开创峨眉武学--回风佛柳剑。解开门
	派谜题后，燎原百击威力倍增。

指令：perform sword.liaoyuan

要求：
	当前内力的需求 1500 以上；
	最大内力的需求 8000 以上；
	当前精力的需求 2000 以上；
	回风拂柳剑等级 450 以上；
	截手九式的等级 450 以上；
	临济十二庄等级 450 以上；
	基本剑法的等级 450 以上；
	激发内功为临济十二庄；
	激发剑法为回风拂柳剑；
	激发手法为截手九式；
	备手法为截手九式；
	且手持兵器。
HELP
        );
        return 1;
}
