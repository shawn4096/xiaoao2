// Room: /d/wizard/shandong.c
#include <ansi.h>
inherit ROOM; //继承 ROOM 类
string zhenlong();
void create()
{
	set("short", HIG"崖壁前"NOR); 
	set("long", @LONG
前方已经无路，此处是崖壁前，脚下万丈深渊，立足之处仅容一人之地，极为
险要，山风呼啸，一不小心将跌落万丈山崖，粉身碎骨。山崖下摆放了一个玉石制
作的棋盘，据说是江湖传说的珍珑棋局(zhenlong)，右前方一条小径通往山崖下的
青草坪。
LONG );
	set("exits", ([
		//"south" : __DIR__"midao3",
		"northeast" : "d/xiaoyao/qingcaop",
		//"west" : __DIR__"midao2",
		//"north" : __DIR__"midao1",
	]));
	//set("no_fight",1);
	set("item_desc", (["zhenlong" : (: zhenlong :),]));
	set("objects", ([
			"d/xiaoyao/obj/daqipan": 1,	
			"/d/xiaoyao/npc/suxingh" : 1
		]) );
	setup();
	replace_program(ROOM);
}

string zhenlong()
{	
	object me=this_player();
	int total,fy,wx,t,s;

	if (QUEST_D->queryquest(me,"xiaoyao/zhenlong"))
	{
		return "["HIC"珍"HIG"珑"HIY"棋"HIM"局"NOR"] 已经被你破解，棋虽在，人已非！\n";

	}
	if (!me->query_temp("xiaoyao/zhenlong/step1"))
	{
		me->start_busy(20);
		me->receive_damage("jing",random(10000),"执迷棋局导致精力透支");
		me->receive_damage("jingli",random(10000));
		message_vision(RED"$N扫了一眼这个棋局，陡然间感觉自己头晕目眩，仿佛有一股大力要将自己神魂扯进去一般！\n"NOR,me);
		return "你顿时吓得冷汗淋淋!\n";
	}
	//这里开始解棋局
	
	if (query("busy")) 
	{
		//独占模式
		return "先等其他人解完再来不迟。\n";
	}
	
	set("busy",1);
	me->delete_temp("xiaoyao/zhenlong/step1");//防止连续解密
	me->start_busy(20);
	tell_object(me,HIC"你目不转睛的瞧着棋局，凝神思索，过了良久，从棋盒拿出一枚白子，放在棋局之上。\n"+
                       "苏星河对这局棋的千变万化，每一着都早已了然于胸，当即应了一着黑棋。\n"+
                       "你想了一想，下了一子。苏星河道：“阁下这一着极是高明，且看能否破关，打开一条出路。”\n"+
                       "苏星河紧跟着下了一子黑棋，封住去路。\n"+
                       "你下一子，想一会，一子一子，越想越久，下到二十余子时，日已偏西\n"+
                       "你左手停在半空，微微发颤，始终点不下去。\n"+
                       "过了良久，你说道：“前无去路，后有追兵，正也不是，邪也不是，那可难也！\n"NOR);
	
	total=me->query("per")+me->query("pur");	
	t=random(total);	 
	
	if (QUEST_D->questing(me,10,180,0,"xiaoyao/zhenlong"))
		 {
			 tell_object(me,HIC"你双目呆呆的凝视棋局，危机生于顷刻，突然间灵机一动，\n"+
			 "解不开棋局，但捣乱一番，却是容易，只须心神一分，便有救了。既无棋局，何来胜败。”\n"+
             "你从棋盒中取过一枚白子，闭了眼睛，随手放在棋局之上。\n"+
			 "苏星河道：“你杀了自己一块棋子，黑棋再逼紧一步，你如何应法？\n"+
			 "你伸手入盒，取过一枚白子，下在棋盘之上。所下之处，却是提去白子后现出的空位。\n"+
			 "岂知你落子而杀了自己一大块白棋后，局面顿呈开朗，黑棋虽然大占优势，白棋却已有回旋的余地。\n"+
			 "这个新局面，苏星河是做梦也没想到过的，他一怔之下，思索良久，方应了一着黑棋。\n"+
			 "数着一下之后，局面竟起了大大变化，你才知这个“珍珑”的秘奥，正是要白棋先挤死了自己一大块。\n"+			 
			 "你对弈道虽所知甚少，但也知此着一下，便解破了这个珍珑棋局，拍手笑道：“好像是成了罢？\n"NOR);			
            set("busy",0);           
		 tell_object(me,HIB"苏星河走到那三间木屋之前，伸手肃客，道：“请进！”：\n"+
			  "你摆个马步，右手提起，发掌向木屋板门上劈了过去。\n"+
			  "你撞破一重板壁后，额头砰的一下，又撞在一重板壁之上，只撞得昏天黑地，险些晕去。\n"NOR);
         me->move("/d/leigushan/shandong");		 
            return "恭喜你，成功破解珍珑棋局。"	;		
		 }
		 else
		 {			  
			  tell_object(me,HIR"你心头一震，一时之间百感交集，反来覆去只是想着两句话：\n"+
			  "你连边角上的纠缠也摆脱不了，还想逐鹿中原么？\n"+
			  "时也命也，夫复何言？”突然间你大叫一声，一头栽倒在地。\n"NOR);
			  set("busy",0);              
         me->unconcious();         	 
			  return "很遗憾，破解珍珑棋局失败。";			 
		 }
}