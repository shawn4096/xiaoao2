// Room: /d/huashan/cave.c
// Date: Look 99/03/25
// Update by lsxk@hsbbs 2007/8/8  add huashan perform fengyi quest

#include <ansi.h>
string look_dazi();
inherit ROOM;
#include "fengyi5.h"
void create()
{
        set("short", "密洞");
        set("long",@long
你走进来，发现石壁后面，别有洞天，是个可容得千人之众的大洞，洞中
有七具骸骨，或坐，或卧，身旁均有兵刃。山洞四壁离地数丈突出一块大石，
似是一个平台，大石之下刻着十六个大字(dazi)。你举起火把更往石壁上照看
时，只见一行字刻道：张乘风张乘云破华山剑法于此。这一行之旁的石墙(wall)
上刻着无数人形，显然是使棍子的人形在破解使剑人形的剑法。这些人形之旁，
赫然出现一行字迹(ziji)，你不禁想看(kan)清楚写了些什么。
long);
        set("exits", ([
                "out" : __DIR__"rukou",
			    "east" : __DIR__"cave1",
        ]));
	set("item_desc", ([
            	"dazi" :  (:look_dazi:),
            	"wall" : @TEXT

       o    | o      o    \ o      o      o     <o     <o>
    --^|\    ^|^  --v|^    v|v    |/v   \|X|    \|      |
       /\     >\    /<      >\    /<      >\    /<      >\

       o>     o      o      o      o      o      o      o
       \ __   x     </     <|>    </>    <\>    <)>     |\__
      /<      >\    /<      >\    /<      >\     >>     L


TEXT
        ]));
        //set("no_fight", 1);
        setup();
}

void init()
{
    object me=this_player();
	if ((me->query("family/family_name")=="嵩山派" 
		||me->query("family/family_name")=="华山派"
	    ||me->query("family/family_name")=="日月神教")
		&& me->query_temp("hssb/juejiasked"))
	{
	    message_vision(HIC"$N刚进入山洞，看到角落里似乎有几个人影晃动，看来华山石壁的消息已经泄漏了。\n"NOR,me);
	    message("channel:rumor", HIM"【谣言】某人："+me->query("name")+"机缘巧合，发现华山石壁内的秘密！\n"NOR, users());
		//me->delete_temp("hssb/juejiasked");
		//me->set_temp("hssb");
	}
	//凤仪4没开先解fy4
	if(this_player()->query("quest/hsjf/fengyi4_fail")){
        add_action("do_yanjiu", "yanjiu");
        this_player()->set_temp("quest/huashan/fengyi_yanjiu",1);
    }
	//开了4，没开5，相隔一天，没有杀过killer
    if(this_player()->query("quest/hsjf/fengyi4")=="pass"
      &&this_player()->query("quest/hsjf/fengyi5")!="pass"
     // &&(int)this_player()->query("quest/hsjf/fengyi5_fail")<5
      && time()-(int)this_player()->query("quest/hsjf/fengyi4_time")>86400
      &&this_player()->query("quest/huashan")=="气宗"
      &&!this_player()->query("quest/hsjf/fy5/kill_killer_pass")
      &&(!this_player()->query("quest/hsjf/fy5")||this_player()->query("quest/hsjf/fy5/yanlian")!="pass"))
     {
            this_player()->set_temp("fengyi5_zhuomo",1);
            call_out("fengyi5_init",3+random(4),this_player());
     }

    add_action("do_kan", "kan");

    if(this_player()->query("quest/hsjf/fy5/chuaimo")
       &&this_player()->query("quest/hsjf/fy5/kill_killer_pass")
       &&this_player()->query("quest/hsjf/fy5/yanlian")=="pass")
        add_action("do_chuaimo", "chuaimo");
}
//揣摩的是凤仪5
//揣摩的是
int do_chuaimo(string arg)
{
    int i,j;
	object me = this_player();
    if (me->query("family/family_name")!="华山派"||me->query("quest/huashan")!="气宗")
        return notify_fail("你费尽所思，但终因不是华山气宗核心弟子而无法领悟这华山绝技？\n");
    if(!arg)
        return notify_fail("你要揣摩什么？\n");

    if(arg!="有凤来仪" && arg!="剑招")
        return notify_fail("你要揣摩什么？\n");
	
	if ((time()-me->quest("quest/hsjf/fengyi5_time"))>86400) return notify_fail("你来的太频繁了？\n");
	
	if  (me->query("quest/hsjf/fengyi5")) return notify_fail("你已经解开谜题，还揣摩什么？\n");
	
    if(me->query("rigister")<3 &&(int)me->query("quest/hsjf/fengyi5_fail")>=5)
	{
        me->delete("quest/hsjf/fy5");
        return notify_fail(HIR"你对照着石壁上的剑招，揣摩来揣摩去都还是无法弄懂，你觉得这辈子要弄懂这个似乎有点超出你的能力范围了。。。\n"NOR);
    }
	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	i=random(j);
	me->set("quest/hsjf/fengyi5_time",time());//加时间间隔
	if (me->query("kar")>25 && i<3)
	{
	
        write(HIG"你对照着石壁上的剑招，回想起刚才蒙面恶人所使用的招数，突然间领会了\n"+
                 "这“有凤来仪”的最后一招，你不禁哈哈大笑道：“哈哈~！原来如此啊!”\n"NOR);

        me->set("quest/hsjf/fengyi5","pass");
		//增加华山石壁的标记
		me->set("quest/hs/hssb/pass",1);
        me->delete("quest/hsjf/fy5");
        log_file("quest/fengyi5", sprintf(HIG"fy5成功!有凤来仪5Quest记录：%s(%s)在华山秘洞失败%d次后"HIW"揣摩"HIG"成功。经验%d。\n"NOR, me->name(1),me->query("id"), me->query("quest/hsjf/fengyi5_fail"), me->query("combat_exp")) );
        return 1;
    }
    write(HIY"你对照着石壁上的剑招，慢慢揣摩刚才蒙面恶人的剑招，虽然觉得有点思路，但还是无法理解透彻！\n"NOR);
    me->add("quest/hsjf/fengyi5_fail",1);	
    log_file("quest/fengyi5", sprintf(HIR"fy5失败！有凤来仪5Quest记录：%s(%s)在华山秘洞"HIW"揣摩"HIR"失败%d次。经验%d。\n"NOR, me->name(1),me->query("id"),me->query("quest/hsjf/fengyi5_fail"), me->query("combat_exp")) );

    return 1;
}


int fengyi5_init(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave")
         return 1;

        write(HIY"你故地重游，无意间又见到了这石壁之上所刻的“"HIC"有凤来仪"HIY"”的破解\n"+
              "招数。可是这次吸引你的不是破解一方的招数，而是本门的这招“"HIC"有\n"+
              "凤来仪"HIY"”！\n"+
            HIR"\n你只觉得这招“"HIC"有凤来仪"HIR"”攻势凌厉，但似乎更有上乘的后招紧跟其\n"+
              "后，你不禁开始慢慢琢磨起来......\n\n"NOR);
        add_action("do_zhuomo","zhuomo");
        add_action("do_zhuomo","琢磨");
    return 1;
}

int do_zhuomo(string arg)
{

    object me = this_player();

    if(!me->query_temp("fengyi5_zhuomo"))
        return notify_fail("你瞎琢磨啥呢？该干啥干啥去！\n");

    if(me->is_fighting()||me->is_busy())
        return notify_fail("你正忙着呢！\n");

    if(!arg) return notify_fail("你要琢磨什么？\n");

    if(arg!="有凤来仪")
        return notify_fail("你瞎琢磨啥呢？\n");

    if((int)me->query_skill("huashan-jianfa",1)<350)
        return notify_fail("你的华山剑法实在太差,瞎琢磨了半天还是放弃了!\n");

    if(me->query("quest/hsjf/fengyi5")=="pass")
        return notify_fail("怎么着？还想自创第六招？\n"NOR);

    if((int)me->query("quest/hsjf/fengyi5_fail")>=5 && me->query("registered")<3)
        return notify_fail("你已绞尽脑汁,但依然未果,只恐怕今生再也无法参透这其中奥秘了！\n"NOR);

    fengyi5_zhuomo(me);

    return 1;
}
//看大字
string look_dazi()
{

       return "每四个字一排，一共四排，每个字都有尺许见方，深入山石，\n"
              "是用极锋利的兵刃刻入，深达数寸。十六个字棱角四射，大有剑拔弩张之态。\n"

        "\n"
          "      ※※※※※※※※※※※※※※※※※\n"
          "      ※※※※　　　　　　　　　※※※※\n"
          "      ※※※※　五　岳　剑　派　※※※※\n"
          "      ※※※※　无　耻　下　流　※※※※\n"
          "      ※※※※　比　武　不　胜　※※※※\n"
          "      ※※※※　暗　算　害　人　※※※※\n"
          "      ※※※※　　　　　　　　　※※※※\n"
          "      ※※※※※※※※※※※※※※※※※\n"
          "      ※※※※※※※※※※※※※※※※※\n";
}

int do_kan(string arg)
{
    object me = this_player();

    if(me->is_fighting()||me->is_busy())
        return notify_fail("你正忙着呢！\n");

    if (!arg || (arg != "ziji" && arg != "字迹") )
		return notify_fail("你想看什么？\n");

      switch (me->query("family/family_name"))
      {
        case "日月神教":
         if(me->query("quest/hmy/dlsmf/jueji")=="pass"||me->query_skill("dali-shenmofu",1)>1)
          return notify_fail("你看了墙上的棍法招式。甚是投入，但忽觉尽力翻涌，看来是功力相冲所致！\n");  
         if(me->query("quest/hmy/tmgf/jueji")=="pass")
          return notify_fail("你微微一笑，心道：天魔棍法绝技已经尽在我心中！\n");
			
		 break;
	    case "嵩山派":
         if(me->query("quest/ssjf/jueji")=="pass")
           return notify_fail("你微微一笑，心道：大嵩山剑法绝技已经尽在我心中！\n");           
		 break;
	    case "华山派":
         if(me->query("quest/hsjf/fengyi5")=="pass")
			return notify_fail("你微微一笑，心道：想要真正尽破华山剑法，恐怕难于登天！\n");    
         //if(me->query("quest/hsjf/fengyi4_fail"))
			//return notify_fail("这些字迹早已铭刻在你心中，此刻你只想研究出拆解之道！\n");    
         if(me->query("quest/huashan")!="气宗" ) 
			return notify_fail("你上前瞄了两眼，没发现有啥好玩的东东，顿时郁闷了半天！\n");
		break;    
    }	

    tell_object(me,HIY"你手举火把，走上前去，定睛一看，竟是如下十二个大字：\n\n"NOR);
    tell_object(me,HIR"                     张张\n"+
                      "                     乘乘\n"+
                      "                     云风\n"+
                   HIM"                      尽\n"+
                      "                      破\n"+
                   HIR"                      华\n"+
                      "                      山\n"+
                      "                      剑\n"+
                      "                      法\n"+
                      "                      !\n"NOR);

    if (me->query("family/family_name")=="华山派"&&me->query("quest/huashan")=="气宗"&&me->query_temp("hssb/juejiasked"))
       call_out("fengyi_quest1",2,me);
	if (me->query("family/family_name")=="日月神教" && me->query_temp("hssb/juejiasked"))
       call_out("tmgf_1",2,me); //解密天魔棍法谜题
	
	me->delete_temp("hssb/juejiasked");

	return 1;
	//看字迹2
  

}

//解密天魔棍法
int tmgf_1(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave" ) 
         return 1;
    
    if(me->is_fighting()||me->is_busy())
        return notify_fail("你正忙着呢！\n");
   
    write(HIY"你不禁心中既叹又喜，心道：“久闻教中长老传闻，我神教张氏兄弟的棍法冠绝天下，\n"+
             "今日一见果然非比寻常，自他们二人在十大长老围攻华山而下落不明，原来他们竟然‘\n"+
             "殒身于此，真是造化弄人，看来这十大长老是受敌人奸计所困，否则以他们的神奇武技\n"+
			 "焉能会脱不了身？”\n"NOR);
    
    call_out("tmgf_2",5,me);
    return 1;
}

int tmgf_2(object me)
{
  
	if(file_name(environment(me))!="/d/huashan/cave") 
         return 1;

    write(HIC"\n你再一凝神,察觉此处石质甚是坚硬，要在这石壁上绘图写字，纵有利器，也是十分不\n"
    "易!不由再次细心察看石壁上所绘图案,岂知越看越是心惊,使剑人形虽只草草数笔，线\n"
    "条甚为简陋，但从姿形之中可以明白，那正是华山剑法，剑势飞舞而出出，轻盈灵动,\n"
    "与之对拆的人形手中持着的是一条直线形的兵刃，不知道是棒棍还是枪矛。眼见使棍人\n"
    "形的棍法来势凌厉之极，正是华山剑法的克星,被其克制的绝无还手之力。\n"NOR);
    //write(HIR"就在你全神贯注研究绝招之际，忽然间窜出几个黑影将你围了起来。\n"NOR);
    call_out("tmgf_3",2,me);
    return 1;
}

int tmgf_3(object me)
{
    int i;
	object cs_npc;
	if(file_name(environment(me))!="/d/huashan/cave" )
         return 1;

    write(HIR"你心下大喜,本神教传下来的武功招式当真如此威猛,岂能让人给尽数看到?\n"
             "你不禁想要研究个透彻，这大力神魔斧还是尽快学成，再将其铲除，以免为别人所学到？！\n"+
			 "就在你沉思之际，这时忽然窜出三个蒙面人将你围了起来。\n"NOR);
    for(i=0;i<3;i++){
        cs_npc = new("/d/huashan/npc/cave_npc");
        cs_npc->set("cs_kill_id",me->query("id"));
        cs_npc->move(environment(me));
		//cs_npc->kill_ob(me);		
    }
  //  me->delete_temp("tmgf");
	
	me->set_temp("tmgf/killnpc",1);
    add_action("do_lianxi", "lianxi");

    return 1;
}


//日月的是练习
int do_lianxi()
{
	int i,g,j;
	object me=this_player();
	
	if(file_name(environment(me))!="/d/huashan/cave" ){
		message_vision(HIY"因为你心中胆怯，不战而逃，已经离开华山秘洞，解密失败。\n"NOR,me);
        me->set("tmgf/jueji/time",time());
		me->add("tmgf/jueji/fail",1);
		
        return 1;
	}
	if (me->query("quest/hmy/dlsmf/pass")||me->query_skill("dali-shenmofu",1))
	{
		message_vision(HIC"你练习一阵天魔棍法，忽然觉得气血翻涌，原来是和先前修习的大力神魔斧头法功力不符。\n"NOR,me);
		return 1;
	}
	if (present("gao shou",environment(me)))
	  return notify_fail("你还没有杀完这些高手，如何能静心领悟大力神魔斧！\n");
	if (!me->query_temp("tmgf/killnpc"))
	  return notify_fail("你要练习什么！\n");
	//if(arg !="绝招" && arg != "绝技" && arg !="大力神魔绝技")
        //return notify_fail("你要通过练习来领悟什么？\n");
	if (me->query("quest/hmy/tmgf/jueji")=="pass")
	   return notify_fail("你已经完全领悟天魔棍法绝技，无需再浪费时间！\n");
	
	if ((time()-me->query("tmgf/jueji/time"))<86400)
	    return notify_fail("你来的太频繁了！\n");
	if(me->query("dex")<40)
    {
    	write("天魔棍需要极高的先天身法（40）方能施展出威力，你先天身法太低还是赶紧参悟去吧。\n");
		return 1;
	}
	if(me->query_skill("tianmo-gun",1)<450)
    {
    	
    	write("天魔棍没有大飞，赶紧修炼去吧。\n");
		return 1;
	}
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	  i=random(j);
	//g=random(me->query("relife/gifts/total"));
	

	message_vision(HIC"$N见对方棍棒的还招软弱无力，纯系守势，不由得吁了口长气，心再看那使棍人形，但见他缩成一团，\n"+
					  "姿式极不雅观，一副招架无方的挨打神态，$N正觉好笑，突然之间，脸上笑容僵硬了起来，背上一阵冰凉，\n"+
					  "寒毛直竖。他目不转瞬的凝视那人手中所持棍棒，越看越觉得这棍棒所处方位实是巧妙到了极处。\n"NOR,me);
	
	if (me->query("kar")<31
		&& random(me->query("kar"))>25
		&& i<4
		&& random(me->query("dex"))>40
		&& me->query("dex")>=40)
	{
       message_vision(HIW"$N恍然大悟，这天魔棍要想练成绝非一日之功，对于身法要求是很高的。\n"NOR,me);
	   message_vision(HIY"对方尽管招式迅捷无比，但每一剑势必都刺在这棍棒之上，这棍棒骤看之下。\n"+
						"似是极拙，却乃极巧，形似奇弱，实则至强，当真到了“以静制动，以拙御巧”的极诣。！\n"NOR,me);
	   message_vision(HIC"$N恭喜你，历经千难万险，终于领悟天魔棍绝技的真谛。\n"NOR,me);
	  
	   log_file("quest/tmgfjueji",sprintf("%s(%s) 在华山石壁，彻底领悟天魔棍绝技。富源：%d。随机数：%d。失败：%d。经验值：%d。gift值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("tmgf/jueji/fail"),me->query("combat_exp"),g,me));
	   me->set("title",HIY"日月神教"HIC"金猿神魔"NOR);
	   me->set("quest/hmy/tmgf/jueji","pass");
	   me->delete_temp("tmgf/killnpc");
	   me->delete_temp("hssb/juejiasked");
	   me->start_busy(1);
	   return 1;
	}
	else
	{
		message_vision(HIY"\n$N虽然知道天魔棍的招式，但对于如何使用的劲力法门一时之间却是难以理解。\n"
		                      +"天魔棍的威力并没有发挥出来，看来你还是有待于重新来华山石壁领悟学习了。\n"NOR,me);
		log_file("quest/tmgfjueji",sprintf("%8s%-10s在华山石壁，领悟天魔棍法绝技并没有成功，尚须努力。富源：%d。随机数：%d。失败：%d。经验值：%d。gift值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("tmgf/jueji/fail"),me->query("combat_exp"),g,me));
		me->add("tmgf/jueji/fail",1);
		me->set("tmgf/jueji/time",time());
		me->delete_temp("tmgf/killnpc");
	    me->delete_temp("hssb/juejiasked");
		me->start_busy(1);
        return 1;
	}
	
}

//解密华山剑法凤仪4绝技
int fengyi_quest1(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave") 
         return 1;

    if(me->is_fighting()||me->is_busy())
        return notify_fail("你正忙着呢！\n");

    write(HIW"你不禁勃然大怒，心道：“无耻鼠辈，大胆狂妄已极。华山剑法精微奥妙，天\n"+
             "下能挡得住的已屈指可数，有谁胆敢说得上一个‘破’字？更有谁胆敢说是‘\n"+
             "尽破’？”\n"NOR);

    call_out("fengyi_temp",3+random(5),me);
    return 1;
}

int fengyi_temp(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave") 
         return 1;

    write(HIC"\n你再一凝神,察觉此处石质甚是坚硬，要在这石壁上绘图写字，纵有利器，也是十分不\n"
    "易!不由再次细心察看石壁上所绘图案,岂知越看越是心惊,使剑人形虽只草草数笔，线\n"
    "条甚为简陋，但从姿形之中可以明白，那正是华山剑法，剑势飞舞而出出，轻盈灵动,\n"
    "与之对拆的人形手中持着的是一条直线形的兵刃，不知道是棒棍还是枪矛。眼见使棍人\n"
    "形的棍法来势凌厉之极，正是华山剑法的克星,被其克制的绝无还手之力。霎时间，你\n"
    "不由对本派武功信心全失。\n\n"NOR);

    call_out("fengyi_temp2",3+random(5),me);
    return 1;
}

int fengyi_temp2(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave")
         return 1;

    write(HIM"你心下大骇,难道本派传下来的武功剑招当真如此不济,让人给尽数破了去?\n"
             "你不禁想要对石壁上的剑招研究（yanjiu）个透彻，这华山剑法难道真的如此不堪一击？！\n\n"NOR);

    me->set_temp("quest/huashan/fengyi_yanjiu",1);
    add_action("do_yanjiu", "yanjiu");

    return 1;
}
//华山的是研究
int do_yanjiu(string arg)
{
    object me = this_player();
    int i;

    if(!me) return 0;

    if(!me->query_temp("quest/huashan/fengyi_yanjiu"))
        return notify_fail("你还有空研究这玩意儿？专心做你自己的事去！\n");

    if(me->is_fighting()||me->is_busy())
        return notify_fail("你正忙着呢！\n");

    if(!arg) return notify_fail("你要研究什么？\n");

    if(arg!="剑招 at 石壁")
        return notify_fail("你要研究哪里的东西？\n");

    if((int)me->query_skill("huashan-jianfa",1)<450)
        return notify_fail("你的华山剑法实在太差,看不懂石壁上的精妙剑招!\n");

    if(me->query("quest/hsjf/fengyi4")=="pass")
        return notify_fail("你已经参透“有凤来仪”的第四后招了!\n"NOR);

    if((int)me->query("quest/hsjf/fengyi4_time")+86400 > time())
        return notify_fail("你刚刚才研究过剑招，还是先休息下吧！\n");

    if((int)me->query_temp("quest/huashan/fengyi_yanjiu")<5){
        i = (int)me->query_skill("huashan-jianfa",1);
        i = i*i/7;
        me->add_temp("quest/huashan/fengyi_yanjiu",1);
        me->add("jingli",-(int)me->query("eff_jingli")/5);
        me->add("jing",-500);
        me->add("neili",-600);
        me->add_busy(3+random(3));   
        return notify_fail(HIY"你仔细的研究着石壁上的剑招，竟发现许多乃是失传已久，剑招精妙绝伦！\n"NOR);
    }
    if(random((int)me->query_temp("quest/huashan/fengyi_yanjiu")+1)<5){
        if((int)me->query_temp("quest/huashan/fengyi_yanjiu")>=6 || random(me->query("kar"))<26){
            me->start_busy(2);
            me->add("quest/hsjf/fengyi4_fail",1);
            me->set("quest/hsjf/fengyi4_time",time());
            me->set("quest/hsjf/fengyi4_exp",me->query("combat_exp"));
            me->delete_temp("quest/huashan/fengyi_yanjiu");
            log_file("quest/fengyi", sprintf(HIR"失败！有凤来仪Quest记录：%s(%s)在华山秘洞领会第四后招失败。经验%d。\n"NOR, me->name(1),me->query("id"), me->query("combat_exp")) );
            return notify_fail(HIR"过了好久，你觉得自己的华山剑法造诣还是太低，无法领会石壁上的精美剑招！\n"NOR);
        }
        i = (int)me->query_skill("huashan-jianfa",1);
        i = i*i/7;
        me->add_temp("quest/huashan/fengyi_yanjiu",1);
        me->add("jingli",-(int)me->query("eff_jingli")/5);
        me->add("jing",-500);
        me->add("neili",-600);
        me->add_busy(3+random(3));
  
        return notify_fail("你仔细思考了良久，发现对华山剑法的认识又进了一步！\n");
    }
    else{
            me->set("quest/hsjf/fengyi4","pass");
			
            me->set("quest/hsjf/fengyi4_exp",me->query("combat_exp"));
            me->set("quest/hsjf/fengyi4_time",time());
            me->delete_temp("quest/huashan/fengyi_yanjiu");
            me->start_busy(2+random(2));
            write(HIC"\n你突然在石壁上发现了“有凤来仪”这一招，你知这招剑招乃藏五个后招，但从未参透这\n"+
                       "第四招和第五招。但见这石壁上使招之人，剑势轻盈灵动，剑势虽为古怪但却巧妙无比。\n"+
                  HIR"\n当下，你突然领悟到，剑招是死的，人却是活的，华山剑法剑招与剑招之间的衔接变化岂\n"+
                       "是一成不变的？剑随意而走，随心而动，剑招自然衔接的天衣无缝，这才是上成的华山剑\n"+
                       "法啊！\n"+
                  HIY"\n你领悟到此，看了下那“尽破”二字，不禁对破剑招之人感到可笑致极!\n"NOR);
            log_file("quest/fengyi", sprintf(HIG"成功！有凤来仪Quest记录：%s(%s)在华山秘洞成功领会有凤来仪第四后招。经验%d。\n"NOR, me->name(1),me->query("id"), me->query("combat_exp")) );
            return 1;
    }
}
