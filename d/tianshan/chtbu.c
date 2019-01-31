// Room: /d/tianshan/chtbu.c
// By Linux

#include <ansi.h>
inherit ROOM;
string look_deng1();
string look_deng2();
string look_deng3();
string look_deng4();

void create()
{
	set("short", "成天部");
	set("long", @LONG
眼前是一个可容纳数百人的大厅，是成天部的所在地，大厅墙壁上画满了
浮雕，天顶上画的是一个青衫男子，头上有角，左手持长剑，右手握剑诀，骑
着一只青龙，冲天而起。地面以青色岩石磨就，分毫无缝，浑然天成。大厅四
角点着数盏明灯，弥漫在大厅里的香气好象就是从灯里发出。
LONG);

	set("exits", ([
                "eastdown" : __DIR__"dadao9",
        ]));       

        set("objects", ([
                __DIR__"npc/f-dizi" : 1,
        ]));    

	set("item_desc", ([
		"east deng" : (: look_deng1 :),
		"south deng" : (: look_deng2 :),
		"west deng" : (: look_deng3 :),
		"north deng" : (: look_deng4 :),
	]));
	set("zhbfang", 1);
	setup();	
}

void init()
{
	add_action("do_smell", ({"smell", "wen"}));
	add_action("do_move", ({"move", "yi"}));
	//add_action("do_dunwu","dunwu");
}

void reset()
{
	set("zhbfang", 1);
}

string look_deng1()
{
	object me = this_player();
	if (!me->query_temp("ts/smell")) return "什么？\n";
	if(random(me->query("kar")+me->query("per")+me->query("pur")) <= 40){
		me->delete_temp("ts/smell");
		return "你仔细看着点燃在大厅东角的铜灯，发现没有什么两样。\n";
	}
	else {
		me->set_temp("ts/smell2",1);
		return "你仔细看着点燃在大厅东角的铜灯，终于发现其中一盏的灯座，似乎可以移动。\n";
	}
}

string look_deng2()
{
	object me = this_player();
	if (!me->query_temp("ts/smell")) return "什么？\n";
	if(random(me->query("kar")+me->query("per")+me->query("pur")) <= 40){
		me->delete_temp("ts/smell");
		return "你仔细看着点燃在大厅南角的铜灯，发现没有什么两样。\n";
	}
	else {
		me->set_temp("ts/smell2",1);
		return "你仔细看着点燃在大厅南角的铜灯，终于发现其中一盏的灯座，似乎可以移动。\n";
	}
}

string look_deng3()
{
	object me = this_player();
	if (!me->query_temp("ts/smell")) return "什么？\n";
	if(random(me->query("kar")+me->query("per")+me->query("pur")) <= 40){
		me->delete_temp("ts/smell");
		return "你仔细看着点燃在大厅西角的铜灯，发现没有什么两样。\n";
	}
	else {
		me->set_temp("ts/smell2",1);
		return "你仔细看着点燃在大厅西角的铜灯，终于发现其中一盏的灯座，似乎可以移动。\n";
	}
}

string look_deng4()
{
	object me = this_player();
	if (!me->query_temp("ts/smell")) return "什么？\n";
	if(random(me->query("kar")+me->query("per")+me->query("pur")) <= 40){
		me->delete_temp("ts/smell");
		return "你仔细看着点燃在大厅北角的铜灯，发现没有什么两样。\n";
	}
	else {
		me->set_temp("ts/smell2",1);		
		return "你仔细看着点燃在大厅北角的铜灯，终于发现其中一盏的灯座，似乎可以移动。\n";
	}
}

int do_smell(string arg)
{
	object me=this_player();
	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢！\n");
	tell_object(me,"你仔细闻着空气里的香气，似乎和其他几个大厅的气味不同，不由的暗自起疑!\n");
	me->set_temp("ts/smell",1);
	me->add_busy(2);
	return 1;
}

int do_move(string arg)
{
	object ob, *ob2;
	object here = this_object();
	object me = this_player();
	int i;

	if (me->is_busy() || me->is_fighting())	return notify_fail("你正忙着呢！\n");
	if (!me->query_temp("ts/smell2"))
		return notify_fail("什么？\n");
	if( (!arg) || !((arg == "deng") || (arg == "灯") || (arg == "tong deng") || (arg == "铜灯")))
		return notify_fail("你要移动什么？\n");
	if (query("zhbfang") < 1)
		return notify_fail ("你把铜灯往旁边移了移，但没发现任何东西。\n");

	ob=new(__DIR__"npc/zhbfan");
	ob->move(environment(me));
	message_vision(HIW"$N把铜灯往旁边移了移。\n"NOR, me);
	message_vision(HIW"突然一条人影向$N扑了过来。\n"NOR, me);
	message_vision(HIR"卓不凡对$N大喝一声：既然我上的山来，就是要和你们这些所谓仙子，拼个你死我活，\n"+
			"既然被你个" + RANK_D->query_rude(me) + "发现了，不是你死就是我活。\n"NOR, me);
	here->add("zhbfang",-1);
	ob2 = all_inventory(here);
	for(i=0; i<sizeof(ob2); i++) {
		if(!ob2[i]->is_character()) continue;
		if( ob2[i]->is_corpse()) continue;
		//if(ob2[i]!=me) continue;
		ob->kill_ob(ob2[i]);
		ob2[i]->kill_ob(ob);
	}
	if (me->is_fighting(ob)&&objectp(ob))
	{
		call_out("check_zhuo",1,me,ob);
	}
	me->delete_temp("ts/smell1");
	me->delete_temp("ts/smell2");
	return 1;
}

int valid_leave(object me,string dir)
{
	me->delete_temp("ts/smell");
	me->delete_temp("ts/smell2");
	return ::valid_leave(me);
}
//战斗中判断

//lingwu
int check_zhuo(object me,object ob)
{

	if (me->is_fighting(ob)&&objectp(ob))
	{
		call_out("check_zhuo",3,me,ob);
		return 1;
	}
	if (!present("zhuo bufan",environment(me)))
	{
		message_vision(HIC"\n\n$N历经艰险，将卓不凡好不容易杀掉，但内心却是若电闪雷鸣,这剑神卓不凡的剑术已然大成。\n"NOR,me);
		message_vision(HIC"\n\n$N想起方才卓不凡突然翻脸，陡施杀手，嗤得一声，剑刃从自己腋下穿过，将旧袍划破了长长口子。\n"NOR,me);
		message_vision(HIC"\n\n而卓不凡第二击不中，五分惊讶之外，更增了五分惧怕，身子滴溜溜的打了半个圈子，长剑一挺。\n"NOR,me);
		message_vision(HIC"\n\n剑尖上突然生出半尺吞吐不定的青芒。那剑芒犹似长蛇般伸缩不定，竟然是传说中的“剑芒”！。\n"NOR,me);
		message_vision(HIC"\n\n当时卓不凡脸露狞笑，丹田中提一口真气，青芒突盛，向自己胸口刺来。这卓不凡的剑术竟然如斯！\n"NOR,me);
		message_vision(HIC"\n\n你从未见过别人的兵刃上能生出青芒，料想是一门厉害武功，自己定然对付不了，脚步一错，滑了开去。\n"NOR,me);
		message_vision(HIC"\n\n卓不凡这一剑出了全力，中途无法变招，刷的一声响，长剑刺入了大石柱中，深入尺许。这根石柱乃极\n"
							+"\n\n坚硬的花岗石所制，软身的长剑居然刺入一尺有余，可见他附在剑刃上的真力实是非同小可。\n"NOR,me);
		message_vision(HIY"\n\n\n\n这招剑芒到底是一种什么样的招式？有了方才的一番战斗，使得你不觉开始进行顿悟(dunwu)状态。\n"NOR,me);	
		add_action("do_dunwu","dunwu");
		me->set_temp("tyqj/startdw",1);
		return 1;
	}

}


int do_dunwu()
{	
	object me = this_player();
	//int i=3+random(3);
//	me->start_busy(2);
	if (me->query("family/family_name") != "灵鹫宫" )
		return notify_fail("你不是灵鹫宫弟子来此作甚？\n");
		
	
	if (me->query("family/master_id")!="xu zhu"||me->query("family/master_name")!="虚竹")
			return notify_fail("你师傅不是虚竹，来此作甚？\n");

	if (!me->query_temp("tyqj/startdw"))
			return notify_fail("你没事来遛弯呢？\n");

    if (me->query("quest/ljg/tyqj/jianmang/pass"))	
			return notify_fail("你已经解开谜题了？\n");
//	if (me->is_busy())	
//			return notify_fail("你正在忙碌中？\n");
	if (time()-me->query("quest/ljg/tyqj/jianmang/time")<86400)
			return notify_fail("你也太勤快点了耶？\n");

		  
		//me->set_temp("tyqj/dwjm",1);
			
		message_vision(HIR"\n\n$N盘膝而坐，头顶蒸汽氤氲，似乎正在参悟什么功法。\n"NOR,me);
		me->start_busy(999);
		remove_call_out("thinking");
		call_out("thinking",1,me);
		me->delete_temp("tyqj/startdw");
		return 1;
			
}

int thinking(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  j=random(10);
  me->set("quest/ljg/tyqj/jianmang/time",time());
// if (!me->query_temp("tyqj/dwjm"))
	//return notify_fail("你要干什么呢。\n");
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟化骨绵掌时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_jianmang")<(30+random(10)))
   {  
	  me->add_temp("canwu_jianmang",1);
	  switch (random(7))
	  {
		case 0:
			tell_object(me,HIG"\n你仔细回忆方才的战斗过程，只觉得耳目一新...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n忽然，你似乎抓住了一些明悟。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你陷入馄饨状态，大脑一片空明，似乎要抓住那个线索了！..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，甚是无聊，神情抑郁，似乎有些累了.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎遇到瓶颈了..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n你思维漂浮在空中，宛如婴儿沐浴.神清气爽.\n"NOR);
			break;
		default:tell_object(me,YEL"\n你叹了一口气，精神总是不能有效集中.\n"NOR);
			break;

	  }
	  //去掉标记
     // me->delete_temp("tyqj/dwjm");


	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (i>=26
			&& j<3
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断领悟，终于领悟了这剑芒的奥秘，对于天羽奇剑这一招的领悟豁然贯通！”\n"NOR,me); 
         log_file("quest/tyqj_jianmang", sprintf("%s(%s) 成功！第%d次参悟，机缘巧合下，成功参悟天羽奇剑剑芒的奥秘，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/ljg/tyqj/jianmang/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/ljg/tyqj/jianmang/time",time());
		 me->set("quest/ljg/tyqj/jianmang/pass",1);
		 me->start_busy(1);
		 me->delete_temp("canwu_jianmang");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来又是一无所获啊。”\n"NOR,me); 
		 message_vision(HIY"\n参悟天羽奇剑剑芒绝技解密失败！\n"NOR,me); 
         log_file("quest/tyqj_jianmang", sprintf("%s(%s) 失败！第%d次失败参悟天羽奇剑剑芒，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/ljg/tyqj/jianmang/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/ljg/tyqj/jianmang/fail",1);
		 me->set("quest/ljg/tyqj/jianmang/time",time());
		 me->start_busy(1);
		 me->delete_temp("canwu_jianmang");
		 return 1;
   }

}