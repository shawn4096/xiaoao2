// Modify By River 98/12
inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "后院");
	set("long", @LONG
进了后院小舍，这是间简陋的小房子，地上放着几个蒲团，西首的蒲团上
坐着一个满脸皱纹，身行高大的老僧。
LONG
	); 
	set("exits", ([ /* sizeof() == 1 */
	    "south" : __DIR__"dadian",
        ]));

        set("objects", ([
        	__DIR__"npc/huangmei" : 1,
        ]));

	set("coor/x",-200);
  set("coor/y",-400);
   set("coor/z",10);
   setup();
}

void init()
{
     object ye,me,huang,gao,yun,yue,yanqing;
	 me = this_player();
     //一阳指第五段
	 if(me->query_temp("yyzhi/helpnhs"))
     {
        tell_object(me,HIY"\n\n\n你一进门，猛然看到屋内正在进行一场激烈的战斗，几个人影围绕一位老僧正在厮杀！\n\n"NOR);

		if (!objectp(ye=present("ye erniang",environment(me))))
		{
			ye=new("d/dali/wuliang/npc/erniang");
			ye->move(this_object());
		}
		if (!objectp(huang=present("huangmei heshang",environment(me))))
		{
			huang=new("d/dali/dalieast/npc/huangmei");
			huang->move(this_object());
		}
		/*
		if (!objectp(gao=present("gao shengtai",environment(me))))
		{
			gao=new("d/dali/npc/gaoshengtai");
			gao->move(this_object());
		}*/

		if (!objectp(yun=present("yun zhonghe",environment(me))))
		{
			yun=new("d/dali/wuliang/npc/yunzhonghe");
			yun->move(this_object());
		}
		if (!objectp(yue=present("nanhai eshen",environment(me))))
		{
			yue=new("d/dali/wuliang/npc/eshen");
			yue->move(this_object());
		}
		if (!objectp(yanqing=present("duan yanqing",this_object())))
		  {
			  yanqing=new("d/dali/wuliang/npc/dyq1");
			  yanqing->move(this_object());
		  }
	
		yue->kill_ob(huang);
		//yue->kill_ob(gao);
		yue->kill_ob(me);
		yun->kill_ob(me);
		yun->kill_ob(huang);
		ye->kill_ob(me);
		ye->kill_ob(huang);
		yanqing->kill_bo(me);
		yanqing->kill_bo(huang);
		call_out("check_huang",1,me,huang);
    }
	  //解段家剑以剑代指
	 else if (me->query_temp("yanqing/askzhong"))
	  {
		  if (!objectp(yanqing=present("duan yanqing",this_object())))
		  {
			  yanqing=new("d/dali/wuliang/npc/dyq");
			  yanqing->move(this_object());
		  }
		    if (!objectp(huang=present("huangmei heshang",environment(me))))
		  {
			huang=new("d/dali/dalieast/npc/huangmei");
			huang->move(this_object());
		  } 
		  tell_object(me,HIG"一位青袍客冷冷的站在那儿，以腹语在说话，“黄眉老儿，你既然受段正明的恩惠，就不要躲藏”!\n"NOR);
		  tell_object(me,HIG"我们在手上功夫分个分晓，你输了，这拈花寺就归我了，你若赢了，我就既往不咎”!\n"NOR);
		  call_out("huang_duan",3+random(2),me,yanqing,huang);/**/

	  }
}

int check_huang(object me,object huang)
{
	
	object ye,yun,yanqing,yue;
	ye=present("ye erniang",this_object());
	yue=present("nanhai eshen",this_object());
	yun=present("yun zhonghe",this_object());
	yanqing=present("duan yanqing",this_object());
	//gao=present("gao shengtai",this_object());
	if (!me)
	{
		return 0;
	}
	if (!objectp(huang)||huang->query("qi")<huang->query("max_qi")/3)
	{
		tell_object(me,HIW"黄眉僧受到四大恶人袭击，受伤严重，无法接受你的邀请。\n"NOR);
		tell_object(me,HIW"救援任务失败！！\n"NOR);
		me->add("yyzhi/tls/yyz/start/fail",1);
		me->delete_temp("yyzhi");
		if (objectp(ye)) destruct(ye);
		if (objectp(yue)) destruct(yue);
		if (objectp(yun)) destruct(yun);
		if (objectp(yanqing)) destruct(yanqing);
		
		return 1;

	}
    if (!me->is_fighting()
		&&!objectp(ye)
		&&!objectp(yue)
		&&!objectp(yun)
		&&!objectp(yanqing)
		&&objectp(present("huangmei heshang",this_object())))
	{
		tell_object(me,HIW"终于将四大恶人打跑。\n"NOR);
		tell_object(me,HIW"请黄眉僧救援任务成功！！\n"NOR);
		me->delete_temp("yyzhi");
		me->set_temp("yyzhi/helpnhsover",1);
		me->set("yyzhi/tls/yyz/start/helpnhsover",1);
		if (objectp(ye)) destruct(ye);
		if (objectp(yue)) destruct(yue);
		if (objectp(yun)) destruct(yun);
		if (objectp(yanqing)) destruct(yanqing);
	
		return 1;

	}
    call_out("check_huang",1,me,huang);
	return 1;


}

//解剑法

int huang_duan(object me,object yanqing,object huang)
{

	tell_object(me,HIY"既然受人之托，那就不得不要面对，为了天南三年免税，老衲就不推辞了！\n"NOR);
	huang->fight_ob(yanqing);
	yanqing->fight_ob(huang);
	

}