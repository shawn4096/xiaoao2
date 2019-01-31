// Room: /d/huashan/cave1.c
// Date: sohu@xojh
// 大力神魔斧和嵩山剑法高级quest

#include <ansi.h>
string look_dazi();
int dlsmf_1(object me);
int dlsmf_2(object me);
int dlsmf_3(object me);
int do_lianxi();
inherit ROOM;
//#include "fengyi5.h"
void create()
{
        set("short", "密洞");
        set("long",@long
你走进来，发现石壁后面，别有洞天，是个可容得千人之众的大洞，洞中
有七具骸骨，或坐，或卧，身旁均有兵刃。山洞四壁离地数丈突出一块大石，
似是一个平台，大石之下刻着十六个大字(dazi)。你举起火把更往石壁上照看
时，只见一行字刻道：范松赵鹤破嵩山剑法于此。这一行之旁的石墙(wall)之
上刻着无数人形，粗略一计，少说也有五六百个，显然是使斧的人形在破解使
剑人形的剑法。这些人形之旁，赫然出现一行字迹(ziji)，你不禁想看(kan)
清楚写了些什么。
long);
        set("exits", ([
              //  "out" : __DIR__"rukou",
			    "west" : __DIR__"cave",
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
    //object me=this_player();
//add_action("do_lianxi", "lianxi");
    add_action("do_kan", "kan");

}

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
//若解开棍子，则不会出现字迹。
    switch (me->query("family/family_name"))
    {
      case "日月神教":
        //if(me->query("quest/hmy/tmgf/jueji")=="pass")
          //return notify_fail("你看了墙上的招式，已然全部洞悉，心道：天魔棍法绝技已经尽在我心中！\n");  
        if(me->query("quest/hmy/dlsmf/jueji")=="pass")
          return notify_fail("你微微一笑，心道：大力神魔斧绝技已经尽在我心中！\n");				
		
		break;
	  case "嵩山派":
        if( me->query("quest/ss/ssjf/jueji/pass"))
          return notify_fail("你微微一笑，心道：大嵩山剑法绝技已经尽在我心中！\n");           
		break;
	
    }	
        tell_object(me,YEL"你举起火把，走上前去，定睛一看，竟是如下十个大字：\n\n"NOR);
        tell_object(me,HIC"                     范赵\n"+
                          "                     松鹤\n"+                   
                       HIR"                      尽\n"+
                          "                      破\n"+
                       HIC"                      嵩\n"+
                          "                      山\n"+
                          "                      剑\n"+
                          "                      法\n"+
                          "                      !\n"NOR);
   
	
	me->set_temp("hssb/lookzi1",1);
	if (me->query_temp("hssb/juejiasked")&&me->query("family/family_name")=="嵩山派")
	{
		message_vision(HIY"\n\n$N看到这行字，顿时勃然大怒，愤然喝道，”哪里的无知之徒，竟然敢号称尽破嵩山剑法“！\n"NOR,me);
		message_vision(HIC"\n\n\n$N越想越气，忍不住举起火把，盯住墙壁观看起来...。\n"NOR,me);

		me->start_busy(3);
		me->delete_temp("hssb/juejiasked");
		//remove_call_out("ssjf/quest");
		call_out("ssjf_quest",3+random(3),me);
		//me->set_temp("hssb/loo");
	}
    add_action("do_chuaimo", "chuaimo");
	return 1;
		
}

//解密大力神魔斧头
int do_chuaimo(string arg)
{
    object me = this_player();
    if (!me->query_temp("hssb/lookzi1"))
       return notify_fail("你没事瞎揣摩什么？\n");
    if(!arg)
        return notify_fail("你要揣摩什么？\n");

    if(arg!="大力神魔斧" && arg!="斧招")
        return notify_fail("你要揣摩什么？\n");
    //和天魔棍冲突
	if(me->query_skill("tianmo-gun",1)>1){
       
        return notify_fail(HIR"你对照着石壁上的斧法，揣摩来揣摩去都还是无法弄懂，你揣摩良久方才明白，原来是和自己所学的天魔棍法相冲突。\n"NOR);
    }
	if(me->query_skill("qixian-wuxingjian",1)>1){
       
        return notify_fail(HIR"你对照着石壁上的斧法，揣摩来揣摩去都还是无法弄懂，你揣摩良久方才明白，原来是和自己所学的七弦无形剑相冲突。\n"NOR);
    }
/*	if (me->query("quest/hmy/dlsmf/pass") )
	{
		message_vision(HIC"你揣摩良久，对大力神魔斧头似有所得。\n" NOR,me);
		me->improve_skill("dali-shenmofu",random(me->query_int(1)));
		return 1;

	}*/
	if (!me->query_skill("dali-shenmofu"))
	{	
      if ((time()-me->query("quest/hmy/dlsmf/time"))<86400 )
	    return notify_fail("你来的也太勤快点了？\n"); 
	  //if (me->query("kar")>1 && random(10)>1)
	  if (me->query("kar")>28 && random(10)>7)     
	  {
	
        write(HIG"你对照着石壁上的斧头招式,不断演练，突然间灵光一闪，顿时领会了\n"+
                 "这“大力神魔斧”的招式，你不禁哈哈大笑道：“哈哈~！原来如此啊!”\n"NOR);

        me->set("quest/hmy/dlsmf/pass",1);
        me->improve_skill("dali-shenmofu",20);
        log_file("quest/dlsmfu", sprintf("大力神魔斧解密成功记录：%s(%s)在华山秘洞失败%d次后揣摩大力神魔斧成功。经验%d。\n"NOR, me->name(1),me->query("id"), me->query("quest/hmy/dlsmf/fail"), me->query("combat_exp")) );
        return 1;
      }
	  else {
	  
       write(HIY"你对照着石壁上的招式，慢慢揣摩大力神魔斧招，虽然觉得有点思路，但还是无法理解透彻！\n"NOR);
       me->add("quest/hmy/dlsmf/fail",1);
	   me->set("quest/hmy/dlsmf/time",time());
	   me->delete_temp("hssb/lookzi1");
       log_file("quest/dlsmfu", sprintf("%s(%s)在华山秘洞揣摩大力神魔斧头绝技失败%d次。经验%d。\n"NOR, me->name(1),me->query("id"),me->query("quest/hmy/dlsmf/fail"), me->query("combat_exp")) );
       return 1;
	  }
	  
	  //如果解密通过
    }else if ((me->query_skill("dali-shenmofu",1)<450))
    {
      
	   write(YEL"你对照着石壁上的招式，慢慢揣摩大力神魔斧招，摇头晃脑，似乎颇有心得！\n"NOR);
	   me->improve_skill("dali-shenmofu",me->query_int()/2);
	   me->receive_damage("jing",random(20));
	   me->start_busy(random(1));	   

	}
	//450后方可演习绝招
    else
      {
	   me->delete_temp("hssb/lookzi1"); 
	   me->set_temp("dlsmf/yanjiu",1);
	   message_vision(HIG"$N梳理了下自己的所悟招式，基本已经修习，但发现还有一招需要通过研究(yanjiu)方可习得。\n"NOR,me);
	   add_action("dlsmf_yanjiu", "yanjiu");
	   return 1;
       }
   // return 1;
}
//解密绝招
int dlsmf_yanjiu(string arg)
{
	object me=this_player();
	if (!me->query_temp("dlsmf/yanjiu"))
	    return notify_fail("你这点本事还研究什么？\n");
	if(arg!="神魔" && arg!="绝技" && arg!="大力神魔斧绝技")
        return notify_fail("你要研究什么？\n");
	if(me->query_temp("dlsmf/chuaimo"))
        return notify_fail("你正在揣摩过程中！\n");
	
	write(HIC"你聚精会神在钻研石壁上大力神魔斧头最后一招的招式，颇有心得！\n"NOR);
	me->start_busy(1);
	if ((int)me->query_skill("dali-shenmofu",1)>450 && !random(5))
	{
		me->set_temp("dlsmf/chuaimo",1);
		
		call_out("dlsmf_1",2,me);
		
	}
   
   return 1;


}
int dlsmf_1(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave1" ) 
         return 1;

    if(me->is_fighting()||me->is_busy())
        return notify_fail("你正忙着呢！\n");
   

    write(HIY"你不禁心中既叹又喜，心道：“久闻教中长老传闻，我神教有大力神魔斧的绝技，\n"+
             "乃是我神教大力神魔范松长老所创，可惜后来围攻华山而下落不明，原来他们‘\n"+
             "竟然殒身于此，真是造化弄人，看来这十大长老是受敌人奸计所困，否则以他们的\n"+
			 "神妙绝技，焉能会脱不了身？”\n"NOR);
    
    call_out("dlsmf_2",5,me);
    return 1;
}


int dlsmf_2(object me)
{
  
	if(file_name(environment(me))!="/d/huashan/cave1") 
         return 1;

    write(HIC"\n你再一凝神,察觉此处石质甚是坚硬，要在这石壁上绘图写字，纵有利器，也是十分不\n"
    "易!不由再次细心察看石壁上所绘图案,岂知越看越是心惊,使斧头人形虽只草草数笔，线\n"
    "条甚为简陋，但从姿形之中可以明白，那正是大力神魔斧的招式，招式虽然极为简单,但是\n"
    "与之对拆的人形手中持着的是一把宽剑，显然是嵩山的独门兵器，尽管对方的剑法犀利狠辣\n"
    "但在这斧头的招式下对方的剑法被其克制的绝无还手之力。霎时间，你仿佛看到一个前所未有\n"
    "的武学境界，一力降十会！\n\n"NOR);
    //write(HIR"就在你全神贯注研究绝招之际，忽然间窜出几个黑影将你围了起来。\n"NOR);
    call_out("dlsmf_3",2,me);
    return 1;
}

int dlsmf_3(object me)
{
    int i;
	object cs_npc;
	if(file_name(environment(me))!="/d/huashan/cave1" )
         return 1;

    write(HIR"你心下大喜,本派传下来的武功招式当真如此威猛,岂能让人给尽数看到?\n"
             "你不禁想要研究个透彻，这大力神魔斧还是尽快学成，再将其铲除，以免为别人所学到？！\n"+
			 "就在你沉思之际，这时忽然窜出三个蒙面人将你围了起来。\n"NOR);
    for(i=0;i<3;i++){
        cs_npc = new("/d/huashan/npc/cave_npc");
        cs_npc->set("cs_kill_id",me->query("id"));
        cs_npc->move(environment(me));
		
		cs_npc->set("combat_exp",me->query("combat_exp")*4/3);
        cs_npc->set("qi",me->query("qi")*3/2);
		cs_npc->set("max_neili",me->query("max_neili"));
		
    }
    me->delete_temp("dlsmf/chuaimo");
	//me->delete_temp("");
	me->set_temp("dlsmf/fightnpc",1);
    add_action("do_lianxi", "lianxi");

    return 1;
}
int do_lianxi()
{
	int i,g,j;
	object me=this_player();
	me->start_busy(10);
	if(file_name(environment(me))!="/d/huashan/cave1" ){
		message_vision(HIY"因为你心中胆怯，不战而逃，已经离开华山秘洞，解密失败。\n"NOR,me);
        me->set("dlsmf/jueji/time",time());
		me->add("dlsmf/jueji/fail",1);
		
        return 1;
	}
	if (present("gao shou",environment(me)))
	  return notify_fail("你还没有杀完这些高手，如何能静心领悟大力神魔斧！\n");
	
	//if(arg !="绝招" && arg != "绝技" && arg !="大力神魔绝技")
        //return notify_fail("你要通过练习来领悟什么？\n");
	if (me->query("quest/hmy/dlsmf/jueji")=="pass")
	   return notify_fail("你已经完全领悟大力神魔斧，无需再浪费时间！\n");
	
	if (time()-me->query("dlsmf/jueji/time")<86400)
	    return notify_fail("你来的太频繁了！\n");
	if(me->query("str")<40)
    {
    	
    	write("大力神魔斧头需要极高的先天臂力（40）方能施展出威力，你先天臂力太低还是赶紧参悟去吧。\n");
		return 1;
	}
	if(me->query_skill("dali-shenmofu",1)<450)
    {
    	
    	write("大力神魔斧法没有大飞，赶紧修炼去吧。\n");
		return 1;
	}
  //  i=random(10);
//	j=random(me->query("kar"));
	//g=random(me->query("relife/gifts/total"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	  i=random(j);
	
	if (me->query("kar")<31
		&& random(me->query("kar"))>28
		&& i<3
		&& random(me->query("str"))>40)
	{
       message_vision(HIC"$N恍然大悟，这大力神魔斧要想练成绝非一日之功，对于臂力要求是很高的。\n"NOR,me);
	   message_vision(HIY"$N管他什么灵动还是诡异，我只管一斧头劈出去就是了！\n"NOR,me);
	   message_vision(HIG"$N恭喜你，历经千难万险，终于领悟大力神魔斧头绝技的真谛。\n"NOR,me);
	  
	   log_file("quest/dlsmfjueji",sprintf("%s(%s) 在华山石壁，彻底领悟大力神魔斧绝技。富源：%d。随机数i：%d。失败：%d。经验值：%d。gift值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("dlsmf/jueji/fail"),me->query("combat_exp"),g,me));
	   me->set("title",HIY"日月神教"HIR"大力神魔"NOR);
	   me->set("quest/hmy/dlsmf/jueji","pass");
	   me->delete_temp("dlsmf/fightnpc");
	
	   me->start_busy(1);
	   return 1;
	}
	else
	{
		message_vision(HIY"\n$N虽然知道大力神魔斧的招式，但对于如何使用的劲力法门一时之间却是难以理解。大力神魔斧的\n"
		                      +"威力并没有发挥出来，看来你还是有待于重新来华山石壁领悟学习了。\n"NOR,me);
		log_file("quest/dlsmfjueji",sprintf("%8s%-10s在华山石壁，领悟大力神魔斧绝技并没有成功，尚须努力。富源：%d。随机数：%d。失败：%d。经验值：%d。gift值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("dlsmf/jueji/fail"),me->query("combat_exp"),g,me));
		me->add("dlsmf/jueji/fail",1);
		me->set("dlsmf/jueji/time",time());
		me->delete_temp("dlsmf/fightnpc");
	
		me->start_busy(1);
        return 1;
	}
	

}

//解密嵩山剑法绝技

int ssjf_quest(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave1"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave1") 
         return 1;

    if(me->is_fighting()||me->is_busy())
        return notify_fail("你正忙着呢！\n");

    write(HIC"你不禁勃然大怒，心道：“无耻鼠辈，大胆狂妄已极。嵩山剑法精微奥妙，天\n"+
             "下能挡得住的已屈指可数，有谁胆敢说得上一个‘破’字？更有谁胆敢说是‘\n"+
             "尽破’？”\n"NOR);
    call_out("ssjf_temp",5,me);
    return 1;
}


int ssjf_temp(object me)
{
    if(file_name(environment(me))!="/d/huashan/cave1"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave1") 
         return 1;

    write(HIY"\n你再一凝神,察觉此处石质甚是坚硬，要在这石壁上绘图写字，纵有利器，也是十分不\n"
    "易!不由再次细心察看石壁上所绘图案,岂知越看越是心惊,使剑人形虽只草草数笔，线条甚是潦草，\n"
    "但从姿形之中可以明白，那正是嵩山剑法，剑势飞舞而出，大气磅礴，正是嵩山剑法套路,细看之下。\n"
    "与之对拆的人形手中持着的是一条直线形的兵刃，不知道是棒棍还是狼牙棒。眼见使棍之人\n"
    "形的雷震挡法来势凌厉之极，正是嵩山剑法的克星,被其克制的绝无还手之力。霎时间，你\n"
    "不由对本派武功信心全失。\n\n"NOR);

    call_out("ssjf_temp2",2,me);
    return 1;
}

int ssjf_temp2(object me)
{
    object cs_npc;
	int i;
	if(file_name(environment(me))!="/d/huashan/cave1"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave1")
         return 1;

    write(HIG"\n\n你心下大骇,难道本派传下来的武功剑招当真如此不济,让人给尽数破了去?\n"
             "你不禁想要研究（yanjiu）个透彻，这嵩山剑法难道真的如此不堪一击？！\n\n"NOR);
	
	write(HIR"\n\n\n你心下大喜,本派传下来的武功招式当真如此犀利,岂能让人给尽数看到?\n"
             "你不禁想要研究个透彻，这嵩山剑法还是尽快学成，再将其铲除，以免为别人所学到？！\n"+
			 "就在你沉思之际，这时忽然窜出三个蒙面人将你围了起来。\n"NOR);
    
	for(i=0;i<3;i++){
        cs_npc = new("/d/huashan/npc/cave_npc");
        cs_npc->set("cs_kill_id",me->query("id"));
        cs_npc->move(environment(me));
		
		cs_npc->set("combat_exp",me->query("combat_exp")*4/3);
        cs_npc->set("qi",me->query("qi")*3/2);
		cs_npc->set("max_neili",me->query("max_neili"));
		
    }
    me->set_temp("hssb/yanjiu",1);
	me->delete_temp("hssb/lookzi1");
    add_action("do_yanjiu", "yanjiu");
    return 1;
}

int do_yanjiu(string arg)
{
    object me = this_player();
    int i;

    if(!me) return 0;

	if(file_name(environment(me))!="/d/huashan/cave1"
      &&file_name(environment(me))!="/u/lsxk/partyskill/newhs/quest/cave1")
         return 1;
	if (!me->query_temp("hssb/yanjiu"))
	    return notify_fail("你要干什么！!\n");  

    me->delete_temp("hssb/yanjiu");	
	
    if (present("gao shou",environment(me)))
	  return notify_fail("你还没有杀完这些外派高手，如何能静心研究嵩山剑法真谛？！\n");

    if(me->is_fighting()||me->is_busy())
        return notify_fail("你正忙着呢！\n");

    if(!arg) return notify_fail("你要研究什么？\n");

    if(arg!="嵩山剑法" && arg!="嵩山绝技")
        return notify_fail("你要研究哪里的什么东西？\n");

    if((int)me->query_skill("songshan-jian",1)< 450)
        return notify_fail("你的嵩山剑法实在太差（不足450）,看不懂石壁上的精妙剑招!\n");

    if( me->query("quest/ss/ssjf/jueji/pass"))
        return notify_fail("你已经参透“嵩山剑法”绝技的招式了!\n"NOR);

    if(time()-(int)me->query("quest/ss/ssjf/jueji/time")<86400 )
        return notify_fail("你刚刚才研究过剑招，还是先休息下吧！\n");

    message_vision(HIC"\n\n$N仔细的研究着石壁上的剑招，竟发现许多乃是失传已久，剑招精妙绝伦！\n同时$N心中顿时惊骇万分，这些招式竟然连师父都不知道！\n"NOR,me);
	i=me->query("int");
/*
	if (me->query("kar")<31
		&& random(me->query("kar"))>25
		&& i<3
		&& random(me->query("int"))>40)		*/
	if (me->query("kar")<31
		&& random(me->query("kar"))>26)
	{
		 write(HIC"\n你突然在石壁上发现了“纵横捭阖”这一招，你知这招剑招乃藏数个后招，但从未参透这后续的招式。\n"+
                  "但见这石壁上使招之人，剑势轻盈灵动，剑势虽为古怪但却雄浑大气，正是嵩山剑法的精髓所在。\n"+
               HIR"\n当下，你突然领悟到，师父居然没有传授给自己呢？你初看之时大喜过望，但越看却越觉得糊涂，\n"+
                  "下意识模仿嵩山剑法剑随意而走，随心而动，你知道这才是上成的嵩山剑法啊！但为何这么多招式？\n"+
                  "你逐渐陷入到纷繁芜杂的剑招之中，时而是嵩山剑法，时而是魔教长老的棍法，渐渐有走火入魔之状。\n"+
               HIY"\n\n\n\就在你陷入迷茫之际，寒冰真气陡然发动，让你清醒了过来，你领悟到此，看了下那“尽破”二字.\n"+
					"不禁对破了嵩山剑招的魔教长老感到既憎恨又害怕，思前想后，还是决定回去请教师傅为好!\n"NOR);
		me->set_temp("quest/ss/ssjf/jueji/hssb",1);
		me->set("quest/ss/ssjf/jueji/hssb",1);
		me->set("quest/ss/ssjf/jueji/time",time());
		log_file("quest/ssjfjj", sprintf("成功！%8s(%8s) 失败%d次后，看懂了华山石壁嵩山武技。i先天悟性：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/ss/ssjf/jueji/fail"),i,me->query("combat_exp")) );

	}else {

		write(HIY"你看了半天，终究是陷入到招式之中，时而兴奋，时而失落，逐渐有走火入魔之状态。\n"NOR);
		message_vision(HIR"$N忽然觉的全身真气暴走，哇的一声突出一口鲜血，显然受伤不轻。\n"NOR,me);
		message_vision(HBBLU+HIW"解密失败，继续再来。\n"NOR,me);

		me->apply_condition("neishang",5);
		me->apply_condition("liuxue",5);
		me->add_busy(4);
		me->set("quest/ss/ssjf/jueji/time",time());
		me->set("quest/ss/ssjf/jueji/combat",me->query("combat_exp"));
		me->set("quest/ss/ssjf/jueji/giftint",me->query("int"));
		me->add("quest/ss/ssjf/jueji/fail",1);
		log_file("quest/ssjfjj", sprintf("成功！%8s(%8s) 失败%d次后，亦然没看懂华山石壁嵩山剑法奥妙。i先天悟性：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/ss/ssjf/jueji/fail"),i,me->query("combat_exp")) );

	}
	
    return 1;
}


