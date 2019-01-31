// Room: /d/shaolin/cjlou1.c
// Date: YZC 96/01/19
#include <ansi.h>
inherit ROOM;
string look_tjing();
int do_dian(string arg);
int yjj_wait1(object me);
int yjj_fight(object me);
int do_mo(string arg);
void create()
{
	set("short", "藏经阁二楼");
	set("long", @LONG
千余年来少林寺执中原武林之牛耳，自达摩老祖以下，历代人材辈出。其
中有不少高僧遗著留存，汇集至今，终成名震天下的少林七十二绝艺。少林精
华，尽集于此。二楼四面开窗，确保通风。中间排列着五排大书架。四周则陈
列矮几，以供阅读。几位老僧手执经卷，正在闭目凝思。
LONG
	);

	set("exits", ([
		"down" : __DIR__"cjlou",
	]));
	set("cant_hubiao", 1);
    set("item_desc", ([
		
		"铜镜" : (: look_tjing :),
	]));
     set("yjjbook",1);
	set("objects",([
		CLASS_D("shaolin") + "/hui-zhen" : 1,
		__DIR__"obj/wuji1" : 1,
		__DIR__"obj/wuji2" : 1,
		__DIR__"obj/wuji3" : 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	object ob;

	if ((ob = present("huizhen zunzhe", this_object())) && living(ob))
		if (dir == "down" ) {
			foreach(ob in deep_inventory(me))
				if (ob->id("shaolin wuji"))
					return notify_fail("慧真说道：武功秘籍只许在藏经阁内研习，不得携带外出！\n");
		}
	return ::valid_leave(me, dir);
}

void init()
{
	object me = this_player();
	add_action("do_jump", ({ "jump", "tiao" }));
	add_action("do_tui", ({ "tui", "push" }));
	add_action("do_dian", ({ "dian", "light" }));
	add_action("do_mo", "mo"); 
	add_action("do_mo", "find"); 
	if (me->query_temp("yjj/lookdown"))
	{
		call_out("yjj_fight",3,me);
	}
	if (!present("zhiqing",environment(me)))
	{ 
		new("/d/shaolin/npc/zhiqing.c")->move(environment(me));
		//new("/d/shaolin/npc/zhiyuan.c")->move(environment(me));
	}
} 

int do_jump(string arg)
{
	object me;
	me = this_player(); 
	//if (arg != "chuang" ) return 0;
	if ( !arg ) return 0;
	if (arg == "chuang")
	{
		if (!me->query_temp("marks/推"))
			return notify_fail("你要做什么？\n");

		if (me->is_busy() || me->is_fighting()) 
			return notify_fail("你正忙着呢。\n");

		if( (int)me->query_skill("dodge",1) < 100 )
		{
			message_vision(HIR"$N推开窗户，纵身跃起直奔窗外，无奈轻功不够，摔了下来！\n"NOR, me);
			me->unconcious();
			return 1;     
		}
		message_vision("$N推开窗户，纵身跃出窗户，一眨眼就不见了 。\n", me);
		me->move(__DIR__"xiaojin1");
		tell_room(environment(me), me->name() + "从藏经阁飞身跃了过来。\n", ({ me }));
		me->delete_temp("marks/推");
		return 1;
	}
	if (me->query_temp("yjj/consider")&& (arg =="up"||arg =="佛像"))
	{
		message_vision(HIC"$N见有人来，轻轻一纵身跃起，跳到第三尊佛像之后，躲避起来。\n"NOR,me);
		me->move("/d/shaolin/foxiang3.c");
		return 1;
	} 
}

int do_tui(string arg)
{
	object me = this_player();

	if( !arg || arg !=  "chuang") return 0;

	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢。\n");

	write("你轻轻的将藏经阁的窗户推开。\n");
	me->set_temp("marks/推", 1);
	return 1;
}

string look_tjing()
{	
	object mj,me=this_player();
	if (!present("mian ju",me)||!present("mask",me))
		return "你没有易容，这么大摇大摆进来，是想掩耳盗铃？";
	if (me->query_temp("yjj/rushi"))
	{
		me->set_temp("yjj/lookjing",1);
		return "镜中将自己的人影照了出来，铜镜上镌着四句经偈，佛像前点着几盏油灯，昏黄的灯光之下，看不清楚。\n";
	}
	return "这是一面铜镜，上面蒙满了灰尘。\n";
}

int do_dian(string arg)
{
   object me=this_player();
   if (!present("fire",me))
       return notify_fail("你用什么点蜡烛？\n");
   if (!arg||arg!="蜡烛")
	    return notify_fail("你要点什么？");
   if (me->query_temp("yjj/lookjing"))
   {
	   message_vision(CYN"借助蜡烛的灯火，$N依稀看到铜镜上写了：“一切有为法，如梦幻泡影，如露亦如电，当作如是观。”。\n"NOR,me);
       me->delete_temp("yjj/lookjing");
	   me->set_temp("yjj/fire",1);
	   call_out("yjj_wait1",3,me);
   }
   return 1;
}

int yjj_wait1(object me)
{
	me=this_player();
	message_vision(HIY"\n\n$N一笑回首，正要举步，猛然间心头似视什么东西猛力一撞，登时呆了，他只知在这一霎时间，\n"
                       +"想起了一件异常重要的事情。然而是什么事，却模模糊糊的捉摸不住。\n"
					   +HIG"\n\n$N怔立片刻，无意中回头又向铜镜瞧了一眼，见到了自己的背影，猛地省悟：“我不久之前曾见过我自己的背影\n"
					   +"那是在什么地方？怎能如此清晰的见到我自己背影？”正自出神，忽听得院外脚步声响，有数人走了进来。\n",me);
	me->delete_temp("yjj/fire");
	me->set_temp("yjj/consider",1);
	return 1;
}

//重新调下来战斗。。。
int yjj_fight(object me)
{ 
	object xbei,xsh;
	object xji;
	me = this_player();

	if (!present("xuan bei",environment(me)))
	{
		xbei = new("/kungfu/class/shaolin/xuan-bei.c");
		xbei->move(environment(me));
	}
	else xbei=present("xuan bei",environment(me));
	if (!present("xuan sheng",environment(me)))
	{
		xsh = new("/kungfu/class/shaolin/xuan-sheng.c");
		xsh->move(environment(me));
	}
	else xsh=present("xuan sheng",environment(me));
	if (!present("xuan ji",environment(me)))
	{
		xji = new("/kungfu/class/shaolin/xuan-ji.c");
		xji->move(environment(me));
	}
	else xji=present("xuan nan",environment(me));
	xbei->kill_ob(me);	 
	xsh->kill_ob(me);
	xji->kill_ob(me);	
	me->delete_temp("yjj/lookdown");
	me->set_temp("yjj/mostart",1);
	return 1;
}

int do_mo(string arg)
{
	int i,j,g;
	object yjjbook;
	object me=this_player();
	if (!me->query_temp("yjj/mostart"))
		return notify_fail("你没事跑到藏经楼乱摸什么东西？");
	if (me->is_busy()||me->is_fighting())
		return notify_fail("你正在忙碌,到处乱摸什么东西？");
	if (!arg||arg!="book")
		return notify_fail("你到处乱摸什么东西？");
	if (me->query("yjj/powerup"))
		return notify_fail("你已经将易筋经神功融会贯通，还在这里干什么？");
	if (time()-me->query("yjj/time")<86400)
		return notify_fail("你太勤快了耶？");
    message_vision(HIC"\n\n$N奔到铜镜之前，伸出右手食指，在镜上那首经偈第一行第一个“一”字上一掀。紧跟着又在第二行的“梦”这耻掀了一下，\n"
	                 +"\n$N心想：“那僧人说秘密是‘一梦如是’，镜上共有四个‘如’字，不知该掀那一个？$N想了会，伸指在第三行的第一个‘如’字上一掀，\n"
					 +"$N会议方才所见的整个过程，又在第四行的‘是’字上一掀。$N手指未离镜面，只听得轧轧声响，铜镜已缓缓翻起。\n"NOR,me);
	message_vision(HIG"\n\n$N忽然发现镜子后面居然有一个小洞，于是伸手向那个小洞内摸去。\n"NOR,me);
	message_vision(HIC"$N摸了半天却什么也摸不到。$N一顿足，显是十分失望,正在犹豫不决，是否转身离去。\n"NOR,me);
	i = random(15);
	j = random(me->query("kar"));
	g = random(me->query("relife/gifts/total"));

	//富源，随机参悟>=15点，且根骨>45
	if (me->query("kar")<31&&j>27&&i==3&& g>=15&&me->query("con")>=45)
	{
		message_vision(HIC"\n\n$N忽然矮身往铜镜的背面一张，低声喜呼：“在这里了！”伸手从铜镜背面摘下一个小小包裹，揣在怀里，\n"
			+"便欲觅路逃走，但这时四面八方群僧大集，已无去路。$N四面一望，当即从藏经阁的前门中奔了出去。\n"NOR,me);
		message_vision(HIY"\n\n恭喜你，因机缘巧合，历尽千辛万苦，你终于获得了少林第一神功--《易筋经》。\n"NOR,me);
	   
		yjjbook = new("/d/shaolin/obj/book-yijinjing.c"); 
		yjjbook->move(me);
		//CHANNEL_D->do_channel(this_object(), "rumor",me->name(1) + "机缘巧合之下,得到一张" + HIW + "人皮面具" + NOR + "。\n"); 

		log_file("quest/yijj",sprintf("%s(%s) 机缘巧合得到少林第一神功---少林易筋经。富源：%d。随机数：%d。失败：%d。经验值：%d。gift值：%d。\n",
		me->name(1), me->query("id"),j,i,me->query("yjj/fail"),me->query("combat_exp"),g,me));
		me->set("title",HIR"少林派"HIC"易筋经神功传人"NOR);
		me->set("yjj/powerup",1);
		me->delete_temp("yjj/mostart");
		return 1;
	}
	else
	{
		message_vision(HIY"$N虽然得知易筋经的所在，但因机缘不到，不能得到易筋经真传。\n"NOR,me);
		log_file("quest/yijj",sprintf("%8s%-10s解密易筋经失败，尚须努力。富源：%d。随机数：%d。失败：%d。经验值：%d。gift值：%d。\n", me->name(1), me->query("id"),j,i,me->query("yjj/fail"),me->query("combat_exp"),g,me));
		me->add("yjj/fail",1);
		me->set("yjj/time",time());
		me->delete_temp("yjj/mostart");
		return 1;
	}
	return 1;
}
