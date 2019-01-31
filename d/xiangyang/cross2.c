#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "南丁字街");
        set("long", @LONG
这里是军事重镇襄阳城中通往南门和东门的丁字路口，不时地有顶盔贯甲
的士兵走来走去。向南出城可以去湖南，向东出城可以去安徽、江苏。北面方
向有一座高大的牌楼。
LONG
        );
        set("outdoors", "襄阳");
        set("xyjob",1);
        set("exits", ([
                "east" : __DIR__"djie1",
                "north" : __DIR__"dpailou",
		"west" : __DIR__"njie1",
        ]));
        set("objects",([
		__DIR__"npc/wuxiuwen" : 1,
			__DIR__"npc/xyxunbu" : 1,
        ]));
        set("incity",1);
	setup();
}


void init()
{
             object me = this_player();
             int time,total ;
			 int maxjl,maxnl;
             string vip;
             if(!userp(me)) return;
        /*    if(me->query_condition("db_exp",1)>10000)
                me->apply_condition("db_exp", 10000);
             if(!mapp(me->query_conditions_by_type("db_exp")))
                me->apply_condition("db_exp", 10000);
	    */	//else
              //  me->add_condition("db_exp", 10000);
             //if(me->query("combat_exp")<100000) me->apply_condition("db_exp", 1000);
            // time = me->query("vip/vip_time") - time();
/*    
        if((me->query("str")> 32 
	  || me->query("int")> 32
	  || me->query("con")>32 
	  || me->query("dex")> 32 ) 
         && me->query("combat_exp")<=12000000 ) {
      me->move("d/wizard/xhw");
      tell_object(me, "你因为天赋异常，需要进行档案检查，暂时呆在这里吧。\n");	

}*/
//自动升级vip
if( me->query("rmb_used")>=500  && !me->query("buyvip/start") ) me->set("buyvip/start",1);
if(!me->query("cw_exp"))  me->delete("relife/exp_ext");
//清理因为卡设置问题导致的标记混乱

if (me->query("buyvip"))
{
	me->delete("m-card-vip");
	//write("因为你是终身，所以删掉月卡标记\n");
	me->delete("y-card-vip");
	//write("因为你是终身，所以删掉年卡标记\n");
	if (me->query("vip/vip_time")-time()<86400)
	{
		me->set("vip/vip_start_time",time());    
		me->set("vip/vip_time",time());   
		me->add("vip/vip_time",3*365*24*3600);
	}
	

}
else if (me->query("y-card-vip"))
{
	me->delete("m-card-vip");	
	//write("因为你是年卡，所以删掉月卡标记\n");
}
//调整因为丸子造成的id最大内力和精力溢出


	maxnl=(int)(me->query_skill("force")-me->query_temp("apply/force")) * 8 + me->query("combat_exp") / 1000;
	maxjl=(int)(me->query_skill("force")-me->query_temp("apply/force")) * 8;

/*
time = time() - me->query("char_check",1);	
total =  me->query("SJ_Credit",1)+me->query("SJ_Credit_Used",1);

if( time >=86400 ){
  
  if(me->query("registered")<=3) vip =HIG"普通会员"NOR;
  if(me->query("m-card-vip"))   vip =HIM"月卡贵宾"NOR;
  if(me->query("y-card_vip")==1)   vip =HIR"年卡贵宾"NOR;
  if(me->query("buyvip"))       vip =HIW"荣誉贵宾"NOR;
  	
  me->set("char_check",time());

 tell_object(me,HIG"现在开始核查人物状态。。\n您目前还剩"
          + chinese_number(me->query("SJ_Credit"))+"个书剑通宝，您已经累计消费了" 
           + chinese_number(me->query("SJ_Credit_Used")) +"个书剑通宝。\n"NOR);
 log_file( "static/check_CREDIT",sprintf("%s(%s)  | 剩余:%s  累计使用:%s,总计拥有%d。参悟天赋%d，参悟EXP%d，贵宾等级%s。目前经验%d。\n", 
             me->name(),
             me->query("id"),
             chinese_number(me->query("SJ_Credit")),
             chinese_number(me->query("SJ_Credit_Used")),
              total,
              me->query("relife/gifts/total"),
              me->query("relife/exp_ext"),
              vip,
              me->query("combat_exp")
              
              
              
              
                      ));
            }
*/
//暂时将六脉限制在30
	//if (me->query_skill("liumai-shenjian",1)>30)
	    // me->set_skill("liumai-shenjian",30); 

	if (!me->query("quest/jiuyin1/pass")){
      if( me->query_skill("jiuyin-zhengong",1)>221) me->set_skill("jiuyin-zhengong",221); 
      if( me->query_skill("jiuyin-shenfa",1)>221) me->set_skill("jiuyin-shenfa",221);
	}
//修复并记录bug档案

	if(me->query("registered")<=3) vip =HIG"普通会员"NOR;
	if(me->query("m-card-vip"))   vip =HIM"月卡贵宾"NOR;
	if(me->query("y-card_vip"))   vip =HIR"年卡贵宾"NOR;
	if(me->query("buyvip"))       vip =HIW"荣誉贵宾"NOR;
	
/*
	if(me->query_condition("db_exp",1)<10)
	{
		//tell_object(me,HIY"你的双倍经验异常，请及时与巫师联系，你的数据信息已经记录在案。\n"NOR);
		//me->set("bug/db_exp",me->query_condition("db_exp"));
		me->apply_condition("db_exp",10000);
	}
*/	
/*
if (me->query("buyvip") && me->query("SJ_Credit")>75000)
	{
		tell_object(me,HIR"你是"+vip+HIR"身份，但你的通宝异常，现在额为"+me->query("SJ_Credit")+HIR"请及时与巫师联系，你的数据信息已经记录在案。\n"NOR);
		me->set("bug/SJ_Credit",me->query("SJ_Credit"));
		me->set("SJ_Credit",60000);
		log_file("quest/edittongbao", sprintf("%s(%s) 此时的通宝为%d个。双倍经验：%d；当前经验：%d，VIP身份为%s。\n",   
          me->name(1),
          me->query("id"), 
          me->query("SJ_Credit"),
          me->query_condition("db_exp"),
          me->query("combat_exp"),
			vip) );
		//tell_object(me,HIY"你的通宝异常，请及时与巫师联系，你的数据信息已经记录在案。\n"NOR);

	}
	if (me->query("y-card_vip")&&me->query("SJ_Credit")>20000)
	{
		tell_object(me,HIR"你是"+vip+HIR"身份，但你的通宝异常，现在额为"+me->query("SJ_Credit")+HIR"请及时与巫师联系，你的数据信息已经记录在案。\n"NOR);
		me->set("bug/SJ_Credit",me->query("SJ_Credit"));
		me->set("SJ_Credit",8000);
		log_file("quest/edittongbao", sprintf("%s(%s) 此时的通宝为%d个。双倍经验：%d；当前经验：%d，VIP身份为%s。\n",   
          me->name(1),
          me->query("id"), 
          me->query("SJ_Credit"),
          me->query_condition("db_exp"),
          me->query("combat_exp"),
			vip) );

	}
	if (me->query("m-card_vip")&&me->query("SJ_Credit")>2500)
	{
		tell_object(me,HIR"你是"+vip+HIR"身份，但你的通宝异常，现在额为"+me->query("SJ_Credit")+HIR"请及时与巫师联系，你的数据信息已经记录在案。\n"NOR);
		me->set("bug/SJ_Credit",me->query("SJ_Credit"));
		me->set("SJ_Credit",2000);
		log_file("quest/edittongbao", sprintf("%s(%s) 此时的通宝为%d个。双倍经验：%d；当前经验：%d，VIP身份为%s。\n",   
          me->name(1),
          me->query("id"), 
          me->query("SJ_Credit"),
          me->query_condition("db_exp"),
          me->query("combat_exp"),
			vip) );

	}

*/                                      
	
}
