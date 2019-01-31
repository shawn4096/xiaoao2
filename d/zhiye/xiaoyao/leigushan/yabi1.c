// Room: /d/wizard/yabi.c
#include <ansi.h>
inherit ROOM; //继承 ROOM 类

string qipan();
void create() // 创建函数;在里面定义各种属性
{
	set("short", HIB"崖壁前"NOR); // 房间的 短描述
	set("long","路到此处便已断绝，陡峭的崖壁上不知被谁以大神通凿刻出经纬之线形成\n"
		"一副棋盘(qipan)，棋盘上已落有数子，这便是著名的["HIC"珍"HIG"珑"HIY"棋局"NOR"]，传说解开此\n"
		"棋局者便有大机缘。江湖上很多高手都来此一试，但无人能解开此局。\n"
		);// 房间的长描述
	set("exits", ([ "east" : __DIR__"shangu",])); // 不同的方向指令,跳转到
	//set("valid_startroom", 1);//使该房间可以成为下一次进来的地方
	set("outdoors","xiaoyao");
	set("no_fight",1);
	set("no_get",1);
	set("item_desc", (["qipan" : (: qipan :),]));


	set("objects", (["/d/xiaoyao/npc/suxinghe" : 1 ]) );
	
	setup(); //不用管它,照抄就是
}
string qipan()
{	
	object me=this_player();
	if (me->query("quest/天龙八部/北冥神功/look")<1 && me->query("quest/天龙八部/北冥神功/step1")<1)
	{
		return "["HIC"珍"HIG"珑"HIY"棋局"NOR"]\n";
	}
	if (me->query("quest/天龙八部/北冥神功/look")>0 && me->query("quest/天龙八部/北冥神功/step1")<1)
	{
		me->start_busy(180);
		call_out("qipan1", 3,this_player());
	}
	if (me->query("quest/天龙八部/北冥神功/step1")>0)
	{
		return "恭喜！["HIC"珍"HIG"珑"HIY"棋局"NOR"]已被你破解了。\n";
	}
}

void qipan1(object me)
{
		message("vision","\n你盯着棋盘仔细端详，眼前景象却渐渐模糊。。。。\n", this_object());
		remove_call_out("qipan2");
		call_out("qipan2", 3,me);
}
void qipan2(object me)
{
	message("vision",HIG"\n\n棋局上的白子黑子似乎都化作了将官士卒，东一团人马，西一块阵营，你围住我，我围住你，\n"
		"互相纠缠不清的厮杀。你眼睁睁见到，己方白旗白甲的兵马被黑旗黑甲的敌人围住了，左冲右\n"
		"突，始终杀不出重围，心中越来越是焦急。\n"NOR, this_object());

			remove_call_out("qipan3");
			call_out("qipan3", 3,me);
}

void qipan3(object me)
{

	message("vision",HIY"\n\n仿佛又若两大武功高手你来我往，作对厮杀，拳掌翻飞，此去彼来，战作一团。你认真观察双\n"
		"方招数，你平日里武学深处那些参悟不透的地方渐渐若有所悟，但仔细深思却又不得其解。你\n"
		"只觉全身真气仿佛失去了控制在血脉里逆行乱窜，不由的气息粗重起来。\n"NOR, this_object());
	if(me->query("quest/天龙八部/北冥神功/temp")<1)	//此处解开条件以后加 现在为方便测试 请 call me->set(quest/天龙八部/北冥神功/temp,1或者0)来测试 0代表失败 1代表成功
	{
		me->start_busy(-1);
		me->unconcious();//晕倒，失败。
		me->set("quest/天龙八部/北冥神功/step1",0);
		me->set("quest/天龙八部/北冥神功/fail",1);
	}
	else
	{
		message("vision",HIW"\n\n你突然福灵心至，管他三七二十一，捡起旁边白色棋子，一子点在棋盘中央【"HIR"天元位"HIW"】，此子\n"
		"一落下，白子闭目落子而杀了自己一大块白棋后，局面顿呈开朗，黑棋虽然大占优势，白棋却\n"
		"已有回旋的余地，不再像以前这般缚手缚脚，顾此失彼。\n"NOR, this_object());
			remove_call_out("xiaqi1");
			call_out("xiaqi1", 3,me);

	}
}

void xiaqi1(object me)
{
	message("vision",CYN"\n\n\n苏星河大笑三声，道：“好一招倒脱靴！”\n"
		NOR"苏星河对这局棋的千变万化，每一着都早已了然于胸，当即应了一着黑棋。\n"NOR, this_object());
			remove_call_out("xiaqi2");
			call_out("xiaqi2", 3,me);

}
void xiaqi2(object me)
{
	message("vision",NOR"\n你略加思索，捡起旁边的白子下在了【"HIM"“去”位的八八路"NOR"】。\n"NOR, this_object());
			remove_call_out("xiaqi3");
			call_out("xiaqi3", 3,me);
}

void xiaqi3(object me)
{
	message("vision",NOR"\n苏星河微微一笑又应了一着黑棋。\n"
		CYN"苏星河道：“此招你又如何破解呢？”\n"NOR, this_object());
			remove_call_out("xiaqi4");
			call_out("xiaqi4", 3,me);
}

void xiaqi4(object me)
{
	message("vision",NOR"\n你【"HIR"天元位"NOR"】自杀一片白子后珍珑之局已破，棋路豁然开朗。\n"
		"随即便在【"MAG"“平”位二八路"NOR"】上落了一子。\n"NOR, this_object());
			remove_call_out("xiaqi5");
			call_out("xiaqi5", 3,me);
}

void xiaqi5(object me)
{
	message("vision",NOR"\n棋至此番，白棋已经占尽上峰，本来必输之势乾坤扭转，苏星河仰天大笑数声，眼中似乎有泪光流转。\n"
		CYN"苏星河道：“想不到当年师傅留下的棋局三十年来无人能破解，今日得有缘之人以【"HIG"倒脱靴"CYN"】之法破解此局，妙也！妙也！”\n"
		HIR"\n\n\n苏星河突然转过身来，抓住你的衣服，一脚将你踹向崖壁！\n"
		HIB"你只觉一股大力在臀部猛力一撞，身不由主，便是一个筋斗，向前直翻了出去。\n"
		HIC"\n\n你心中一慌，大叫一声不妙，不由的闭上了眼睛。。。 。。。\n\n"NOR, this_object());
		me->start_busy(-1);
		me->set("quest/天龙八部/北冥神功/step1",1);//step1成功！
		me->set("quest/天龙八部/北冥神功/look",0);
		me->move(__DIR__"shandong");
}