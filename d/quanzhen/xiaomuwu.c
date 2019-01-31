inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "小木屋");
        set("long", @LONG
这是一个小木屋，乃是猎人们为了防止夜间被野兽偷袭而刻意建在术上
看起来甚是结实，屋内摆放了不少的日常生活用品，大概因为猎人入山打猎
的缘故，这些家具和碗筷上蒙了一层薄薄的灰尘。墙角有一张大床，米面等
杂粮摆放在床底下，风吹过缝隙，传来隐约的呜呜之声。
LONG);
        set("outdoors", "quanzhen");
        /*set("exits", ([
                "down" : __DIR__"pingdi",
               // "enter" : __DIR__"shandong",
        ]));*/
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
int init()
{
	object me=this_player();
	if (me->query_temp("tzjj/askqiu"))
	{
		call_out("do_ting",2+random(3),me);
	}
	add_action("do_jump","jump");

}

int do_ting(object me)
{
	message_vision(HIC"$N四处打量一番，觉得这个小木屋甚是静谧，风声传来，呜呜作响。\n"NOR,me);
	message_vision(HIY"屋外大雪纷飞，忽然间$N听见屋外传来有人说话的声音。\n"NOR,me);
	add_action("do_ting1","ting");
	//call_out("do_ting1",2+random(2),me);
}

int do_ting1(string arg)
{
	object me=this_player();
	if (!arg||arg!="屋外")
	{
		return notify_fail("你要听什么？\n");
	}
	call_out("do_ting2",2+random(2),me);
	return 1;
}


int do_ting2(object me)
{
	message_vision(HIC"只听得屋外一人说道：“阿弥陀佛，贫僧山中遇雪，向施主求借一宿。”只见雪地里站着两个老僧，一个白眉长垂，\n"
					+"神色慈祥，另一个身材矮小 得多，留着一部苍髯，身披缁衣，虽在寒冬腊月，两人衣衫均甚单薄。\n"NOR,me);
	
	message_vision(CYN"\n\n\n$N俯眼板壁缝中张望，只见白眉僧从背囊中取出四团炒面，交给黑衣僧两团， 另两团自行缓缓嚼食。\n"NOR,me);
	call_out("do_ting3",2+random(2),me);
	return 1;


}
int do_ting3(object me)
{

  message_vision(YEL"\n\n那白眉僧脸上大有关怀之色，低声道：“又要发作麽？”黑衣僧道：“弟子一路上老是觉得不对，只怕又要发作。”\n"
					+"突然间跪倒在地，双手合十，说道：“求佛 祖慈悲。”他说了那句话后，低首缩身，一动不动的跪着，过了一会，\n"
					+"身子轻轻颤抖，口中喘气，渐喘渐响，到后来竟如牛吼一般，连木屋的板壁也被吼声震动，篷头白雪扑蔌蔌地掉将下来。\n"NOR,me);
  call_out("do_ting4",2+random(3));
  return 1;

}

int do_ting4()
{
	object me=this_player();
	message_vision(HIC"\n\n只听白眉僧继续念偈：“若人罪能悔， 悔已莫复忧，如是心安乐，不应常念着。不以心悔故，不作而能作，诸恶事已作，\n"
						+"不能令不作。” 他念完偈后，黑衣僧喘声顿歇，呆呆思索，低声念道：“若人罪能悔，悔已莫 复忧......师父，弟子深知\n"
						+"过往种种，俱是罪孽，烦恼痛恨，不能自已。弟子便是 想着「诸恶事已作，不能令不作。」心中始终不得安乐，如何是好？”\n"
						+"白眉僧道： “行事而能生悔，本为难得，人非圣贤，孰能无过？知过能改，善莫大焉。” 　\n"NOR,me);
	call_out("do_ting5",2+random(3));
	return 1;
}
int do_ting5()
{
	object me=this_player();

	message_vision(YEL"\n\n白眉僧喟然长叹，说道：“你心中充满憎恨，虽知过去行为差失，只因少了仁 爱，总是恶念难除。我说个「佛说鹿母经」\n"
					+"的故事给你听听。”黑衣僧道：“弟子 恭聆。”说着盘膝坐下。$N隔着板壁，也是默然静听。白眉僧道：“从前有只母鹿，生了两\n"
					+"只小鹿。母鹿不慎为猎人所掳，猎人便欲 杀却。母鹿叩头哀求，说道：「我生二子，幼小无知，不会寻觅水草，乞假片时， 使\n"
					+"我告知孩儿觅食之法，决当回来就死。」猎人不许。母鹿苦苦哀告，猎人心动， 纵之使去。” 　　“母鹿寻到二子，低头鸣吟，\n"
					+"舔子身体，心中又喜又悲，向二子说道：「一切 恩爱会，皆由因缘合，会合有别离，无常难得久。今我为尔母，恒恐不自保，\n"
					+"生死多畏惧，命危于晨露。」二鹿幼小，不明其意。于是母鹿带了二子，指点美好水草，涕泪交流，说道：「吾期行不遇，误坠\n"
					+"猎者手；即当临屠割，碎身化糜朽。念汝求 哀来，今当还就死；怜汝小早孤，努力活自己。」” \n"NOR,me);
	call_out("do_ting6",2+random(3));
	return 1;
}
int do_ting6()
{
	object me=this_player();
	message_vision(HIC"\n\n但听得慈恩呼呼喘气，大声道：“师父，我生来是恶人，上天不容我悔过。我 虽无意杀人，终究免不了伤人性命，我不做和尚啦！”\n"
					+"一灯道：“罪过，罪过！我 再说段佛经给你听。”慈恩粗声道：“还听甚麽佛经？你骗了我十多年，我再也不 信你啦。”格喇、格喇两声，\n"
					+"手足铁铐上所连的铁链先后崩断。一灯柔声道：“慈恩，已作莫忧，勿须烦恼。” \n"NOR,me);
	
	message_vision(HIC"\n\n这时，忽听那黑衣僧喝道，我要杀人了！我要杀人了!!\n"
					+"$N站在屋内，听着屋外二人的对话，陷入沉思。\n"NOR,me);

	call_out("do_ting7",2+random(3));
    return 1;
}
int do_ting7()
{
	object me=this_player();
	message_vision(HIR"\n\n\n这时忽听屋外那慈恩和尚喝道，“谁？谁在那小屋内？给我滚出来？”\n\n"NOR,me);
	me->delete_temp("tzjj/askqiu");
	me->set_temp("tzjj/tingover",1);	
	return 1;

}

int do_jump(string arg)
{
	object me=this_player();
	if (!arg || arg!="down")
	{
		return notify_fail("你要往哪儿跳？\n");
	}
	if (me->query_skill("dodge",1)<350)
	{
		return notify_fail("你的轻身基本功不够350，回去好好练习吧。\n");
	}
	message_vision(HIC"\n你纵身一跃，跳到平地之上，气定神闲。\n"NOR,me);
	me->move("d/quanzhen/pingdi");
	return 1;

}
