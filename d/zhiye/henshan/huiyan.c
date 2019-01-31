inherit ROOM;
#include <ansi.h>

int qcdz_come(object me);
int linghu_come(object me);

int do_answer(string arg);

void create()
{
	set("short", "回雁楼");
        set("long", @LONG
这里是衡阳回雁楼，是本地最大的酒楼。往日这时已经十分忙碌
的酒楼今天却有点异样。一个年近四十的白衣汉子，正端坐自饮，桌
面横放着一把快刀，旁边却坐着一个小尼姑，满脸忧急愁苦之色，容
貌却十分秀丽。
LONG );
	set("exits", ([
	       "down" : __DIR__"shop",
	]));
	set("objects", ([
	        __DIR__"npc/tian"   : 1,
	        __DIR__"npc/yilin"  : 1,
	]));

       ////set("no_clean_up", 0);

	//set("coor/x", -10);
	//set("coor/y", -120);
	//set("coor/z", 10);
	setup();
	//replace_program(ROOM);
}

void init()
{
	add_action("do_answer","answer");

}
int do_answer(string arg)
{
	object me=this_player();
	if (!arg) return notify_fail("你要回答什么？\n");
	if (arg=="yes" && me->query_temp("kuaidao/askyilin"))
	{
		message_vision(HIG"田伯光说道，“既然$N有此心就替我看看是青城四秀还是青城四兽”！\n"NOR,me);
		me->set_temp("kuaidao/answeryes",1);
		call_out("qcdz_come",3+random(5),me);
		me->delete_temp("kuaidao/askyilin");
	}
	if (arg=="yes" && me->query_temp("kuaidao/asklhc"))
	{
		message_vision(HIY"田伯光说道，“既然$N有此心就替我斗斗这令狐冲”！\n"NOR,me);
		me->set_temp("kuaidao/answerlhcyes",1);
		call_out("linghu_come",3+random(5),me);
		me->delete_temp("kuaidao/asklhc");
	}

	return 1;
	
}

int qcdz_come(object me)
{
	object tian,renying,renxiong,renjie,renhao;
	if (!objectp(tian=present("tian boguang",this_object())))
	  return notify_fail("田伯光不在此地！\n");
	message_vision(HIR"\n\n忽听楼下有人喝道，“那个狗贼如此大胆，竟然敢侮辱我青城派？\n"NOR,me);
	
	if (!objectp(renjie=present("yu renjie",this_object())))
	{
		renjie=new("d/henshan/npc/huiyan/yurenjie");
		renjie->move(environment(this_object()));
	}
	renjie->kill_ob(tian);
	if (!objectp(renxiong=present("hong renxiong",environment(this_object()))))
	{
		renxiong=new("d/henshan/npc/huiyan/hongrenxiong");
		renxiong->move(environment(this_object()));
	}
	if (!objectp(renying=present("hou renying",environment(this_object()))))
	{
		renying=new("d/henshan/npc/huiyan/hou renying");
		renying->move(environment(this_object()));
	}
	if (!objectp(renhao=present("yu renhao",environment(this_object()))))
	{
		renhao=new("d/henshan/npc/huiyan/yurenhao");
		renhao->move(environment(this_object()));
	}
	renxiong->kill_ob(tian);
//	me->kill_ob(renxiong);
	renhao->kill_ob(tian);
	renying->kill_ob(tian);
	if (objectp(tian))
		call_out("taishan_come",1,me,tian);
	else return notify_fail("田伯光已经被青城派弟子杀死，解密失败！\n");
	return 1;
}
int taishan_come(object me,object tian)
{
	object yuling;
	if (!objectp(yuling=present("yuling zi",environment(this_object()))))
	{
		yuling=new("d/taishan/npc/yulingzi");
		yuling->move(environment(this_object()));
		
	}
	message_vision(HIR"这时，泰山长老玉灵子忽然喊道，“既然田伯光这淫贼在这儿，大伙并肩子上啊！”\n"NOR,me);
	yuling->kill_ob(tian);

	return 1;
}

int linghu_come(object me)
{
	//environment()
	object linghu,tian;
	if (!objectp(tian=present("tian boguang",this_object())))
		return notify_fail("田伯光不在此地,解密过程结束！\n");
	
	message_vision(HIY"正在这时，忽然听到楼下有人喊，“谁在这里大喊天下第二！难道不怕风大闪了舌头么？”\n"NOR,me);

	message_vision(HIR"\n\n一个身影一闪而出，喝道，“田伯光，你想试试我新创天下武功第一的“茅厕剑法”么？\n"NOR,me);
	
	if (!objectp(linghu=present("linghu chong",environment(this_object()))))
	{
		linghu=new("d/huashan/npc/linghuchong");
		linghu->move(environment(this_object()));
	}
	linghu->kill_ob(tian);
	tian->kill_ob(linghu);
	//me->kill_ob(linghu);
	return 1;
}