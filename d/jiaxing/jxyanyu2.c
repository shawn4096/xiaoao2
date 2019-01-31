// Room: /d/jiaxing/yanyu.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIC"烟雨楼二楼"NOR);
	set("long", @LONG
站在二楼，登高远望，湖面终年不断的水气把它笼罩得迷迷蒙蒙的。
经常有文人墨客到这里游玩，凭栏远眺，观赏嘉兴的湖光山色。店小二正
在忙碌着。楼内有不少侠客，彼此间好像在谈论什么事，神情有些紧张。
LONG
	);
	//set("group", 1);
	set("exits", ([
		"down" :  "/d/jiaxing/jxyanyu1",
		"east" :  "/d/jiaxing/jxyanyukefang",
	]));
	set("objects", ([ 
                "d/jiaxing/npc/kezhene" : 1,
	 ]) );

	//set("outdoors", "嘉兴城");
	setup();
}
int init()
{
	object me,jiaomu,gang;
	
	me=this_player();
	if (objectp(gang=present("tong gang",me))
		&&gang->query("jiu")
		&&me->query_temp("quest/射雕英雄传/江南七怪/zhuangjiu"))
	{
		message_vision(HIR"\n\n$N单手举装满了酒水的铜缸，举步轻松，登上二楼，踩得木梯咯吱咯吱的乱响！\n"NOR,me);
		message_vision(HIR"\n$N将那个大铜缸往二楼一顿，又压得地板严重变形！\n"NOR,me);
		
		message_vision(HIY"\n$N吓得二楼的部分食客拼命往楼下跑去！\n"NOR,me);
		me->set_temp("quest/射雕英雄传/江南七怪/fanggangwait",1);
		me->delete_temp("quest/射雕英雄传/江南七怪/zhuangjiu");
		gang->move(this_object());

		if (!objectp(jiaomu=present("jiaomu dashi",this_object())))
		{
			jiaomu=new("d/jiaxing/npc/jiaomu");
			jiaomu->move(this_object());
		}
		//call_out("jiaomu_talk",3+random(3),me,jiaomu);
	}
	add_action("do_jingjiu",({"jingjiu","jing"}));
	add_action("do_doujiu","doujiu");
}
//第一场，敬酒
int do_jingjiu(string arg)
{
	object me,gang,zhang;
	string msg;
	me=this_player();
	if (!arg) return notify_fail("你要给谁敬酒？\n");
	
	if (!objectp(gang=present("tong gang",me)))
		return notify_fail("你并没有举起铜缸，如何敬酒？\n");
	if (!gang->query("jiu")) 
		return notify_fail("你的铜缸内没有酒，如何敬酒？\n");
	if (!me->query_temp("quest/射雕英雄传/江南七怪/pingli"))
	{		

		return notify_fail("你举起大铜缸自己喝了一大口，入口香滑，正是正宗的女儿红！\n");
	}

	
	message_vision(HIG"\n\n$N说道：“好，我敬七位每人一口酒。各位喝了酒再伸手吧。”说着右手一沉，放低铜缸，\n"
						"张口在缸里喝了一大口酒，叫道：“请吧！”手一抖，那口铜缸又向张阿生飞来。\n"NOR,me);
	switch (arg)
	{
		case "张阿生":
			if (!present("zhang asheng",this_object()))
			{
				return notify_fail("张阿生不在此地，你只能自己举起铜缸又喝了一口，原来是正宗江南女儿红！\n");
			}
			message_vision(CYN"\n$N对张阿生说道，“在下敬张五侠”！\n"
						HIY"\n张啊生心想：“要是再象刚才那样把铜缸举在头顶，怎能喝酒？”\n"
						"当即退后两步，双手挡在胸口，待铜缸飞到，双手向外一分，铜缸正撞在胸口。他生得肥胖，\n"
						"胸口累累的都是肥肉，犹如一个软垫般托住了铜缸，随即运气，胸肌向外弹出，已把铜缸飞\n"
						"来之势挡住，双手合围，紧紧抱住了铜缸，低头在缸里喝了一大口酒，赞道：“好酒！”双手\n"
						"突然缩回，抵在胸前，铜缸尚未下落，已是一招“双掌移山”，把铜缸猛推出去。这一招劲道\n"
						"既足，变招又快，确是外家的高明功夫。$N在一旁看得暗暗心惊。\n"NOR,me);
			me->set_temp("quest/射雕英雄传/江南七怪/jingzhang",1);
			break;
		case "柯镇恶":
			if (!present("ke zhene",this_object()))
			{
				return notify_fail("柯镇恶不在此地，你只能自己举起铜缸又喝了一口，原来是正宗江南女儿红！\n");
			}
			message_vision(CYN"\n$N对柯镇恶说道，“在下敬柯大侠”！\n"
						HIG"\n柯镇恶位居江南七怪之首，武功也为七人之冠，他听辨细微暗器尚且不差厘毫，这口巨大\n"
						"的铜缸掷来时呼呼生风，自然辨得清楚。只见他意定神闲的坐着，恍如未觉，直至铜缸飞临头顶，\n"
						"这才右手一举，铁杖已顶在缸底。那铜缸在铁杖上溜溜转的飞快，犹如耍盘子的人用竹棒顶住了\n"
						"瓷盘玩弄一般。突然间铁杖一歪，铜缸微微倾斜，眼见要跌下来打在他的头顶，这一下还不打得\n"
						"他脑浆迸裂？那知铜缸倾斜，却不跌下来，缸中酒水如一条线般射将下来。柯镇恶张口接住，上\n"
						"面的酒不住倾下，他骨都骨都的大口吞饮，饮了三四口，铁杖稍挪，又已顶在缸底正中，随即向\n"
						"上一送，铜缸飞了起来。他挥杖横击，当的一声巨响，震耳欲聋，那缸便飞向$N而去，四下里\n"
						"嗡嗡之声好一阵不绝。\n"NOR,me);
			me->set_temp("quest/射雕英雄传/江南七怪/jingke",1);
			break;
		case "南希仁":
			if (!present("nan xiren",this_object()))
			{
				return notify_fail("南希仁不在此地，你只能自己举起铜缸又喝了一口，原来是正宗江南女儿红！\n");
			}
			message_vision(CYN"$N对南希仁说道，“贫贱不能移，此之谓大丈夫。我敬南四哥一缸！”！\n"
						HIR"\n南希仁一言不发，待铜缸飞到，举起扁担在空中挡住，当的一声，铜缸在空中受阻，落了下\n"
						"来。南希仁伸手在缸里抄了一口酒，就手吃了，扁担打横，右膝跪倒，扁担在左膝之上，右手在扁\n"
						"担一端扳落，扁担另一端托住铜缸之底，扳起铜缸，又飞在空中。\n"
						NOR,me);
			me->set_temp("quest/射雕英雄传/江南七怪/jingnan",1);
			break;
		case "全金发":
			if (!present("quan jinfa",this_object()))
			{
				return notify_fail("全金发不在此地，你只能自己举起铜缸又喝了一口，原来是正宗江南女儿红！\n");
			}
			message_vision(CYN"全金发对$N说道，“兄弟做小生意，爱占小便宜，就不费力的讨口酒吃吧。”！\n"
						HIC"\n全金发抢到南希仁身边，待铜缸再次落下时，也抄一口酒吃了，忽地跃起，双足抵在缸边，\n"
						"空中用力，双脚一挺，身子如箭般向后射出，那铜缸也给他双脚蹬了出去。他和铜缸从相反方向飞出，\n"
						"铜缸迳向丘处机飞去。他身子激射到板壁之上，轻轻滑下。\n"
						NOR,me);
			me->set_temp("quest/射雕英雄传/江南七怪/jingquan",1);
			
			break;
		case "朱聪":
			if (!present("zhu cong",this_object()))
			{
				return notify_fail("朱聪不在此地，你只能自己举起铜缸又喝了一口，原来是正宗江南女儿红！\n");
			}
			message_vision(CYN"$N对朱聪说道，“妙哉，妙哉！在下敬二哥一缸。”！\n"
						HIW"\n朱聪狂叫起来：“啊哟，使不得，小生手无缚鸡之力，肚无杯酒之量，不压死也要醉死……”呼叫\n"
						"未毕，铜缸已向他当头飞到。朱聪大叫：“压死人啦，救命，救命……”伸扇子在缸中一捞，送入口中，\n"
						"倒转扇柄，抵住缸边往外送出，腾的一声，楼板已被他蹬破一个大洞，身子从洞里掉了下去，“救命，\n"
						"救命”之声不住从洞里传将上来。众人都知他是装腔作势，谁也不觉惊讶。完颜洪烈见他扇柄一抵，铜\n"
						"缸便已飞回，小小一柄折扇，所发劲力竟不弱与南希仁那根沉重的铜铁扁担，心下暗自骇异。\n"
						NOR,me);
			me->set_temp("quest/射雕英雄传/江南七怪/jingzhu",1);
			
			break;
		case "韩小莹":
			if (!present("han xiaoying",this_object()))
			{
				return notify_fail("韩小莹不在此地，你只能自己举起铜缸又喝了一口，原来是正宗江南女儿红！\n");
			}
			message_vision(CYN"韩小莹对$N说道，“我来喝一口！”！\n"
						HIM"\n韩小莹右足一点，身子如飞燕掠波，倏地在铜缸上空跃过，头一低，已在缸中吸到了一口酒，轻飘飘的\n"
						"落在对面窗格之上。她擅于剑法轻功，肩力却非所长，心想轮到这口笨重已极的铜缸向自己掷来，接挡\n"
						"固是无力，要掷还给这个道士更是万万不能，是以乘机施展轻功吸酒。\n"
						NOR,me);
			me->set_temp("quest/射雕英雄传/江南七怪/jingying",1);
			
			break;
		case "韩宝驹":
			if (!present("han baoju",this_object()))
			{
				return notify_fail("韩宝驹不在此地，你只能自己举起铜缸又喝了一口，原来是正宗江南女儿红！\n");
			}
			message_vision(CYN"这时那铜缸仍一股劲的往街外飞去，街上人来人往，落将下来，势必酿成极大灾祸。$N暗暗心惊，\n"
							"$N正拟跃到街上去接住。只听呼的一声，身旁一个黄衣人斜刺越过，口中一声呼哨，楼下那匹黄马奔\n"
							"到了街口。\n"
						HIW"\n楼上众人都抢到窗口观看，只见空中一个肉团和铜缸一撞，铜缸下坠之势变为向前倾落，肉团和铜缸\n"
						"双双落在黄马背上。那黄马驶出数丈，转过身来，直奔上楼。马王神韩宝驹身在马腹之下，左足勾住镫子，\n"
						"双手及右足却托住铜缸，使它端端正正的放在马鞍之上，不致倾侧。那黄马跑的又快又稳，上楼如驶平地。\n"
						"韩宝驹翻身上马，探头在缸中喝了一大口酒，左臂一振，把铜缸推在楼板之上，哈哈大笑，一提缰，那黄马\n"
						"倏地从窗口窜了出去，犹如天马行空，稳稳当当的落在街心。韩宝驹跃下马背，和朱聪挽手上楼。\n"
						NOR,me);
			me->set_temp("quest/射雕英雄传/江南七怪/jinghan",1);
			
			break;
		default:
			message_vision("你百无聊赖，只能自己举起铜缸又喝了一口，原来是正宗江南女儿红！\n",me);
			break;
	}	
	msg="当前$N在嘉兴烟雨楼已经敬酒的大侠为：\n";
	if (me->query_temp("quest/射雕英雄传/江南七怪/jingke")) msg+="柯镇恶\n";
	if (me->query_temp("quest/射雕英雄传/江南七怪/jingzhu")) msg+="朱聪\n";
	if (me->query_temp("quest/射雕英雄传/江南七怪/jinghan")) msg+="韩宝驹\n";
	if (me->query_temp("quest/射雕英雄传/江南七怪/jingnan")) msg+="南希仁\n";
	if (me->query_temp("quest/射雕英雄传/江南七怪/jingzhang")) msg+="张阿生\n";
	if (me->query_temp("quest/射雕英雄传/江南七怪/jingquan")) msg+="全金发\n";
	if (me->query_temp("quest/射雕英雄传/江南七怪/jingying")) msg+="韩小莹\n";
	message_vision(msg,me);
	if (me->query_temp("quest/射雕英雄传/江南七怪/jingke")
		&&me->query_temp("quest/射雕英雄传/江南七怪/jingzhu")
		&&me->query_temp("quest/射雕英雄传/江南七怪/jinghan")
		&&me->query_temp("quest/射雕英雄传/江南七怪/jingnan")
		&&me->query_temp("quest/射雕英雄传/江南七怪/jingzhang")
		&&me->query_temp("quest/射雕英雄传/江南七怪/jingquan")
		&&me->query_temp("quest/射雕英雄传/江南七怪/jingying"))
	{
		me->set("quest/射雕英雄传/江南七怪/敬酒完成",1);
	}
	return 1;


}

//第二场斗酒


int do_doujiu(string arg)
{
	object me,gang,zhang;
	
	me=this_player();
	
	if (!arg||arg!="江南七怪")
	{
		return notify_fail("你要和谁斗酒？\m");
	}
		if (!present("ke zhene",this_object())) return notify_fail("柯镇恶不在此地，你无法与之斗酒\n");
		if (!present("zhu cong",this_object())) return notify_fail("朱聪不在此地，你无法与之斗酒\n");
		if (!present("han baoju",this_object())) return notify_fail("韩宝驹不在此地，你无法与之斗酒\n");
		if (!present("nan xiren",this_object())) return notify_fail("南希仁不在此地，你无法与之斗酒\n");
		if (!present("zhang asheng",this_object())) return notify_fail("张阿生不在此地，你无法与之斗酒\n");
		if (!present("quan jinfa",this_object())) return notify_fail("全金发不在此地，你无法与之斗酒\n");
		if (!present("han xiaoying",this_object())) return notify_fail("韩小莹不在此地，你无法与之斗酒\n");

	if (!objectp(gang=present("tong gang",me)))
		return notify_fail("你并没有举起铜缸，如何敬酒？\n");
	if (!gang->query("jiu")) 
		return notify_fail("你的铜缸内没有酒，如何敬酒？\n");
	if (time()-me->query("quest/射雕英雄传/time")<86400)
	{
		return notify_fail("你今天已经斗过酒了！\n");
	}
	//设定时间标记，防止乱用
	

	if (!me->query_temp("quest/射雕英雄传/江南七怪/jingke")
		||!me->query_temp("quest/射雕英雄传/江南七怪/jingzhu")
		||!me->query_temp("quest/射雕英雄传/江南七怪/jinghan")
		||!me->query_temp("quest/射雕英雄传/江南七怪/jingnan")
		||!me->query_temp("quest/射雕英雄传/江南七怪/jingzhang")
		||!me->query_temp("quest/射雕英雄传/江南七怪/jingquan")
		||!me->query_temp("quest/射雕英雄传/江南七怪/jingying"))
	{		

		return notify_fail("你尚未敬酒完毕，如何能和他人斗酒？！\n");
	}

	
	message_vision(HIG"\n\n$N说道：“江南七侠果然名不虚传！个个武功高强，贫道甚是佩服。冲着七位的面子，\n"
						"在下再不跟这焦木和尚为难，只要他交出那两个女子，就此既往不咎。”\n"
					HIY"\n\n柯镇恶道：“这就是你的不是了。这位焦木大师数十年清修，乃是有道的高僧，我们素来\n"
						"敬佩。法华寺也是嘉兴府有名的佛门胜地，怎么会私藏良家妇女？”$N说道：“天下之大，\n"
						"尽有欺世盗名之辈。”韩宝驹怒道：“如此说来，道长是不信我们的话了？”$N道：“我宁可信\n"
						"自己的眼睛。”韩宝驹道：“道长要待怎样？”他身子虽短，但话声响亮，说来自有一股威猛之气。\n"
					MAG"\n\n\$N道：“此事本来与七位无关，既然横加插手，必然自持技艺过人。贫道不才，只好和七位见个\n"
						"高下，若是不敌，听凭各位如何了断便了。”柯镇恶道：“道长既然一意如此，就请划下道儿来罢。”\n"
					YEL"\n\n\n$N微一沉吟，说道：“我和各位向无仇怨，久仰江南七侠也是英侠之士，动刀动拳，不免伤了和气。\n"
						"这样罢。”大声叫道：“酒保，拿十四个大碗来！”$N命他把大碗都到缸中陷满了酒，在楼上排成两列，\n"
						"向江南七怪说道：“贫道和各位斗斗酒量。各位共喝七碗，贫道一人喝七碗，喝道分出胜负为止。好不好？”\n"
					WHT"\n\n越女剑韩小莹虽是女子，生性却是十分豪爽，当下亢声说道：“好，先比了酒量再说。这般小瞧我们\n"
						"七兄弟的，小妹倒是第一次遇上。”说着端起一碗酒来，骨都古都的便喝了下去。她这碗酒喝得急了，\n"
						"顷刻之间，雪白的脸颊上，泛上了桃红。$N道：“韩姑娘真是女中丈夫。大家请罢！”七怪中其余六人各\n"
						"自举碗喝了。丘处机碗到酒干，顷刻间连尽七碗，每一碗都只咕的一声，便自口入肚，在喉咙间竟然不稍停留。\n"
						"酒保兴高采烈，大声叫好，忙又装满十四碗。八人又都喝了,喝到第三个十四碗时，韩小莹毕竟量窄，喝得半碗，\n"
						"右手微微发颤。张阿生接过她手中半碗酒来，道：“七妹，我代你喝了。”韩小莹道：“道长，这可不可以？”\n"
						"$N说道“行，谁喝都是一样。”再喝一轮，全金发也败了下去。\n"NOR,me);
	call_out("doujiu_quest",4+random(4),me);
	
	return 1;
}
	
	
int doujiu_quest(object me)
{
	

	message_vision(HIG"\n\n全金发心想己方还剩下五人，然而五人个个酒量兼人，每人再喝三四碗还可支持，难道对方的肚子\n"
					"里还装得下二十多碗酒？就算他酒量当真无底，肚量却总有限，料想胜算在握，正自高兴，无意中在\n"
					"楼板上一瞥，只见$N双脚之旁湿了好大一滩，不觉一惊，在朱聪耳边道：“二哥，你瞧这道士的脚。\n"
					"”朱聪一看，低声道：“不好，他是用内功把酒从脚上逼了出来。”全金发低声道：“不错，想不到他\n"
					"内功这等厉害，那怎么办？”。\n"
					HIY"\n\n朱聪寻思：“他既有这门功夫，便再喝一百碗也不打紧。须得另寻计较。”退后一步，突然从先前\n"
					"踹破的楼板洞中摔下去，只听他大叫：“醉了，醉了！”又从洞中跃上。又喝了一巡酒，丘处机足旁全是水渍，\n"
					"犹如有一道清泉从楼板上泊泊流出。这时南希仁、韩宝驹等也都瞧见了，见他内功如此精深，都是暗自钦服。\n"
					HIM"\n\n$N呵呵笑道：“江南七怪真是要强的紧。这样吧，朱二哥陪着我喝干了缸中之酒，只要不分胜败，\n"
					"在下就算输了，好不好？”这时缸中还剩下小半缸酒，无虑数十大碗，只怕要庙里两个弥勒佛的大肚子，才分\n"
					"装得下。但朱聪毫不在意，笑道：“兄弟酒量虽然不行，但当年远游，却也曾胜过几样厉害家伙，干啊！”他右\n"
					"手挥舞破扇，左手大袖飘扬，一面说，一面喝酒。\n"
					HIG"\n\n朱聪笑道：“道长喝酒用的是内功，兄弟用的却是外功，乃体外之功。你请瞧吧！”说着哈哈大笑，忽然倒\n"
					"翻一个筋斗，手里已提着一个木桶，随手一幌，酒香扑鼻，桶里装的竟是半桶美酒。这许多人个个武功高强，\n"
					"除柯镇恶外，无不眼光锐利，但竟没瞧清楚这木桶是从哪里来的，再看朱聪的肚子时，却是扁平如常，显然这\n"
					"木桶本来是藏在他的大袍子底下。江南七怪纵声大笑，$N不禁变色。\n"NOR,me);
	call_out("jinbing_come",3+random(4),me);

	return 1;


}

int jinbing_come(object me)
{
	object obj;
	
	message_vision(HIW"\n\n$N道：“在下虽然认输，但两个朋友所遗下的寡妇却不能不救。”举手行礼，托起铜缸，说道：\n"
					"在下这就去法华寺要人。”柯镇恶怒道：“你既已认输，怎地又跟焦木大师纠缠不清？”丘处机道：“扶危\n"
					"解困，跟输赢可不相干。柯大侠，若是你朋友不幸遭难，遗孀受人欺辱，你救是不救？”说到这里，\n"
					"突然变色，叫道：“好家伙，还约了人啦，就是千军万马，在下便豁出了性命不要，也不能就此罢手。”\n"NOR,me);
	
	message_vision(HIR"\n众人忽然看见金兵冲了进来，全体一愣，其中一个金兵头领说道：“谁敢挡大爷捉拿要犯，都给我杀了。”\n"NOR, me);

	 
	 obj=new("d/thd/niujia/npc/jinbing");
     obj->set("kill_id",me->query("id"));	 
     obj->move(this_object());  
	 obj->kill_ob(me);
	 obj=new("d/thd/niujia/npc/jinbing");
     obj->set("kill_id",me->query("id"));	 
     obj->move(this_object());   
	 obj->kill_ob(me);

	 obj=new("d/thd/niujia/npc/jinbing");
     obj->set("kill_id",me->query("id"));	 
     obj->move(this_object());   
	 obj->kill_ob(me);
     obj=new("d/thd/niujia/npc/jinbing");
     obj->set("kill_id",me->query("id"));
     obj->move(this_object());  
	 obj->kill_ob(me);
     obj=new("d/thd/niujia/npc/jinbing");
     obj->set("kill_id",me->query("id"));
     obj->move(this_object());  
	 obj->kill_ob(me);
//调用判断
	 
	 call_out("check_fight",1,me);

	return 1;

}
int check_fight(object me)
{
	object bing;
	if (!me) 
	{
		me->set("quest/射雕英雄传/time",time());
		me->add("quest/射雕英雄传/fail",1);
		return notify_fail("你被金兵所杀，任务失败,请继续！\n");
	}

	if (!me->is_fighting()
		&&!present("jin bing",this_object())) 
	{
		me->set("quest/射雕英雄传/time",time());
		me->set("quest/射雕英雄传/烟雨楼成功杀死金兵",1);
		me->set_temp("quest/射雕英雄传/江南七怪/yanyukillbing",1);
		message_vision(HIY"\n$N更不答话，左手一抬，啪的一掌，打在一名金兵的顶门上。那金兵哼也没哼一声，登时脑浆迸裂而死。\n"
						"$N道：“法华寺我依然会去，人我还是要救，若一定要找金兵帮忙，这便是榜样！”说完袍袖一拂，径自下楼\n"NOR,me);
		return 1;
	}
	//me->set("quest/射雕英雄传/time",time());
	call_out("check_fight",1,me);
}