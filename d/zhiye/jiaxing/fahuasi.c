// /u/beyond/hz/lingyinsi.c 灵隐寺
#include <ansi.h>
inherit ROOM;
int do_fail(object me);
int clear_here();

void create()
{
        set("short",HIY"法华寺"NOR);
        set("long", @LONG
法华寺是靠近临安那附近的一座古刹，因主持焦木大师德高望重
此地香火极为旺盛，附近村民来此烧香许愿络绎不绝。门口摆放了一
个巨大的化纸铜缸(tonggang)，同时门口竖立一个铜钟(zhong)，以备
平时早课时敲响。
LONG
        );
        set("exits", ([
            "northeast" : __DIR__"xiaojing1",
           //"east" : __DIR__"qsddao3",
            
		]));
		set("objects", ([ 
					"d/jiaxing/npc/jiaomu" : 1,
					"d/jiaxing/obj/tonggang" : 1,
		 ]) );

        setup();
}
int init()
{
	
	object me,obj;
	me=this_player();
	if (me->query_temp("quest/射雕英雄传/江南七怪/askkumu"))
	{
		
		message_vision(HIR"你刚进门就听到里面似乎有女声，有些模糊，但不确认！\n"NOR,me);
		message_vision(HIC"\n心中一横，决定硬闯，询问这老僧!\n"NOR,me);
		me->set_temp("quest/射雕英雄传/江南七怪/findfahuasi",1);
		me->delete_temp("quest/射雕英雄传/江南七怪/askkumu");
		return 1;
	}
	//add_action("do_ju","ju");
	if (me->query_temp("quest/射雕英雄传/江南七怪/yanyukillbing")||me->query("quest/射雕英雄传/江南七怪/yanyukillbing"))
	{
		message_vision(HIC"$N一进庙门边听到这八人计划对付自己，更将平素憎恨金兵之情，不禁胡须戟张，圆睁双眼，怒不可遏！\n"NOR,me);
		if (!present("ke zhene",this_object()))
		{
			obj=new("d/jiaxing/npc/kezhene");
			obj->move(this_object());
		}
		if (!present("zhu cong",this_object()))
		{
			obj=new("d/jiaxing/npc/zhucong");
			obj->move(this_object());
		}
		if (!present("han baoju",this_object()))
		{
			obj=new("d/jiaxing/npc/hanbaoju");
			obj->move(this_object());
		}
		if (!present("nan xiren",this_object()))
		{
			obj=new("d/jiaxing/npc/nanxiren");
			obj->move(this_object());
		}
		if (!present("zhang asheng",this_object()))
		{
			obj=new("d/jiaxing/npc/zhangasheng");
			obj->move(this_object());
		}
		if (!present("quan jinfa",this_object()))
		{
			obj=new("d/jiaxing/npc/quanjinfa");
			obj->move(this_object());
		}
		if (!present("han xiaoying",this_object()))
		{
			obj=new("d/jiaxing/npc/hanxiaoying");
			obj->move(this_object());
		}
		add_action("do_zhuang","zhuang");
		me->delete_temp("quest/射雕英雄传/江南七怪/yanyukillbing");
		me->set_temp("quest/射雕英雄传/江南七怪/fhscome2",1);
	}
	//在此比赛赌约
	add_action("do_bisai",({"bisai","dadu","duyue","du"}));
	return 1;
}
int valid_leave(object me, string dir)
{
	if (!wizardp(me) 
		&& objectp(present("tong gang", environment(me))) 
		&& !me->query_temp("quest/射雕英雄传/江南七怪/jugang")
		&&	dir == "northwest")
		return notify_fail("你总觉得这样离开不是太好，要举个重点的东西立威才可，断不可涨了对方士气。\n");
	return ::valid_leave(me, dir);
}

int do_zhuang(string arg)
{
	object me,gang;
	me=this_player();
	if (!arg||arg!="zhong")
	{
		return notify_fail("你要撞什么？\n");
	}
	if (!objectp(present("jiaomu dashi",environment(me)))) 
		return notify_fail("焦木大师不在此地，你再如何撞钟也没用！\n");
	if (!me->query_temp("quest/射雕英雄传/江南七怪/fhscome2"))
		return notify_fail("你拿起木桩撞向此钟，发出清亮的钟声,敲响晨钟暮鼓声！\n");
	
	if (!objectp(gang=present("tong gang",me))) 
		return notify_fail("你拿起木桩撞向此钟，发出清亮的钟声！\n");
	
	message_vision(HIR"\n$N正托着铜缸，正在敲撞大殿上悬着的那口铁钟，数击之下，铜缸已出现了裂口。\n"
				   HIC"\n\n江南七怪不知$N本来也非如此一味蛮不讲理之人，只因他连日追寻段天德不得，\n"
					"怒火与日俱增，更将平素憎恨金兵之情，尽皆加在一起。七怪却道他恃艺欺人，决意\n"
					"跟他大拚一场。$N威名越盛，七怪越是不肯忍让，倘若$N只是个无名之辈，反而易于分说了。\n"NOR,me);
	call_out("qg_fight1",2+random(4),me);
	me->set_temp("quest/射雕英雄传/江南七怪/zhuangzhong",1);
	me->delete_temp("quest/射雕英雄传/江南七怪/fhscome2");

	return 1;
}
int qg_fight1(object me)
{
	object han,ying;
	if (!me) return 0;
	if (!present(me,this_object()))
	{
		do_fail(me);
		return notify_fail("临阵脱逃，被江南七怪打败！无颜面见江东父老！\n");
	}
	message_vision(CYN"韩宝驹对韩小莹说道，“七妹，咱们先上”！\n"NOR,me);
	if (!objectp(han=present("han baoju",this_object())))
	{
		han=new("d/jiaxing/npc/hanbaoju");
		//han->set_super(me);
		han->move(this_object());
	}
	han->kill_ob(me);
	if (!objectp(ying=present("han xiaoying",this_object())))
	{
		ying=new("d/jiaxing/npc/hanxiaoying");
		//han->set_super(me);
		ying->move(this_object());
	}
	ying->kill_ob(me);
	call_out("qg_fight2",3+random(4),me);
	return 1;

}
int qg_fight2(object me)
{
	object nan,zhang;
	if (!me) return 0;
	if (!present(me,this_object()))
	{
		do_fail(me);
		return notify_fail("临阵脱逃，被江南七怪打败！无颜面见江东父老！\n");
	}
	message_vision(HIG"\n\n数招一过，$N看出韩小莹剑法奥妙，当下以快打快。她剑法快，$N出手更快，右手以铜缸\n"
					"挡住韩宝驹的金龙鞭，左掌招招抢快，硬打硬拿，要强行夺取韩小莹手中长剑。片刻之间，\n"
					"韩小莹倏遇险招，被逼得退到了佛像之旁。\n"NOR,me);
	message_vision(CYN"\n\n张阿生和南山樵子南希仁彼此看了一眼，喝道“出手”！\n"NOR,me);

	if (!objectp(nan=present("nan xiren",this_object())))
	{
		nan=new("d/jiaxing/npc/nanxiren");
		//han->set_super(me);
		nan->move(this_object());
	}
	nan->kill_ob(me);
	if (!objectp(zhang=present("zhang asheng",this_object())))
	{
		zhang=new("d/jiaxing/npc/zhangasheng");
		//han->set_super(me);
		zhang->move(this_object());
	}
	zhang->kill_ob(me);
	call_out("qg_fight3",3+random(4),me);
	return 1;
}
int qg_fight3(object me)
{
	object zhu,quan;
	if (!me) return 0;
	if (!present(me,this_object()))
	{
		do_fail(me);
		return notify_fail("临阵脱逃，被江南七怪打败！无颜面见江东父老！\n");
	}
	message_vision(HIC"\n\n朱聪见己方四人联手，兀自处于下风，向全金发一招手，两人从两侧攻了上去！\n"NOR,me);
	message_vision(CYN"\n\n张阿生和南山樵子南希仁彼此看了一眼，喝道“出手”！\n"NOR,me);

	if (!objectp(zhu=present("zhu cong",this_object())))
	{
		zhu=new("d/jiaxing/npc/zhucong");
		//han->set_super(me);
		zhu->move(this_object());
	}
	zhu->kill_ob(me);
	if (!objectp(quan=present("quan jinfa",this_object())))
	{
		quan=new("d/jiaxing/npc/quanjinfa");
		//han->set_super(me);
		quan->move(this_object());
	}
	quan->kill_ob(me);
	call_out("qg_fight4",3+random(4),me);
	return 1;
}
int qg_fight4(object me)
{
	object ke;
	if (!me) return 0;
	if (!present(me,this_object()))
	{
		do_fail(me);
		return notify_fail("临阵脱逃，被江南七怪打败！无颜面见江东父老！\n");
	}
	message_vision(HIC"\n\n柯镇恶听得五弟六弟受伤不轻，挺起铁杖，便要上前助战。全金发叫道：“大哥，发铁菱吧！\n"
					"打‘晋’位，再打‘小过’！”叫声未歇，飕飕两声，两件暗器一前一后往$N眉心与右胯飞到。！\n"NOR,me);
	//message_vision(CYN"\n\n张阿生和南山樵子南希仁彼此看了一眼，喝道“出手”！\n"NOR,me);

	if (!objectp(ke=present("ke zhene",this_object())))
	{
		ke=new("d/jiaxing/npc/kezhene");
		//han->set_super(me);
		ke->move(this_object());
	}
	ke->kill_ob(me);
	message_vision(HIG"\n\n柯镇恶心念一动：“他听了六弟的叫喊，先有了防备，自然打他不中了。”这时全金发声音越来越轻，\n"
						"叫声中不住夹着哼吟，想是伤痛甚烈，而张啊生竟是一言不作，不知生死如何。只听全金发道：\n"
						"“打……打……他……‘同人’。”柯镇恶这次却是不依言，双手一扬，四枚铁菱一齐飞出，两枚分打‘同人’\n"
						"之右的‘节’位、‘损’位，另外两枚分打‘同人’之左的‘丰’位、‘离’位。\n"
						"\n\n$N向左跨一大步，避开了‘同人’的部位，没料到柯镇恶会突然用计，只听两个人同时惊呼。\n"
						"右肩中了一菱，另外对准‘损’位发出的一菱，却打在韩小莹背心。柯镇恶又惊又喜，喝道：“七妹，快来！”\n"NOR,me);
	me->apply_condition("heixue_poison",20);
    message_vision(HBCYN+HIB"\n\n$N一时不妨，为柯镇恶毒镖所中！\n"NOR,me);
	call_out("qg_fight5",3+random(4),me);
	return 1;
}
int qg_fight5(object me)
{
	object jiaomu;
	if (!me) return 0;
	if (!present(me,this_object()))
	{
		do_fail(me);
		return notify_fail("临阵脱逃，被江南七怪打败！无颜面见江东父老！\n");
	}
	message_vision(HIC"\n\n柯镇恶叫道：“快抛剑投降，再挨的片刻，你性命不保。”\n"
					"$N知道柯镇恶这暗器上有毒，！\n"NOR,me);
	


	message_vision(HIG"\n\n$N心想那恶僧与金兵及官兵勾结，寺中窝藏妇女，行为奸恶之极，江南七怪既与他一伙，江湖上\n"
						"所传侠名也必不确，丘某宁教性命不在，岂能向奸人屈膝？当下长剑挥动，向外杀出。不料彼此都重伤\n"
						HIR"\n\n段天德一直躲在地窖之中，听众僧说相斗双方人人死伤倒地，当真是不胜之喜，焦木重伤之余，\n"
						"见段天德要行凶伤人，提气叫道：“不……不可伤他！”\n"
						HIG"段天德哈哈大笑，道：“要我放下刀子？哈哈！立地成佛么？”举起腰刀，向$N顶门便砍。\n"
						"焦木怒极，奋起平生之力，将手中一段乌焦木头对准段天德掷去。段天德身子急侧，可是武功实在太差，\n"
						"没能避开，这段焦木打在他嘴角之上，登时撞下了三颗牙齿。段天德疼极，恶性大发，也不顾焦木于自己有恩，\n"
						"举刀便往他头上砍落，站在他身旁的小沙弥狠命拉住他右臂，另一个去拉他衣领。段天德怒极，回刀将两个\n"
						"小沙弥砍翻在地。\n"
						HIY"\n\n李萍大叫：“恶贼，快住手！”她给段天德拉了东奔西逃，本想伺机杀了他为夫报仇，这时见到满地鲜血，\n"
						"而这恶贼又欲杀人，再也忍耐不住，当即扑上去狠命厮打。\n"
						HIC"\n\n柯镇恶眼睛瞎了，耳朵特别灵敏，一听她叫嚷之声，便知是女子，叹道：“焦木和尚，我们都给你害死啦。\n"
						"你寺里果真藏着女人！”\n"
						HIR"\n\n焦木一怔，立时醒悟，心想自己一时不察，给这畜牲累死，无意中出卖了良友，又气又急，双手在地上一撑，\n"
						"和身纵起，双手箕张，猛向段天德扑去。段天德见他来势猛恶，大骇避开。焦木重伤后身法呆滞，竟尔一头撞在大\n"
						"殿柱上，脑浆迸裂，立时毙命。段天德吓的魂不附体，那里还敢停留，拉了李萍，急奔而出。李萍大叫：“救命啊，\n"
						"我不去，救命啊！”终于声音越来越远。\n"NOR,me);
	if (objectp(jiaomu=present("jiaomu dashi",this_object())))
	{		
		jiaomu->die();
	}
	me->set("quest/射雕英雄传/江南七怪/法华寺激战",1);

	me->set_temp("quest/射雕英雄传/江南七怪/fhsfight7g",1);
	return 1;
}
//打赌比赛

int do_bisai(string arg)
{
	object me,ke,zhu,han,nan,zhang,quan,ying;
	me=this_player();
	if (!arg||arg!="江南七怪")
	{
		return notify_fail("你要和谁打赌？\n");
	}
	if (!me->query_temp("quest/射雕英雄传/江南七怪/fhsfight7g"))
	{
		return notify_fail("无缘无故，你要和谁打赌？\n");

	}
	if (me->is_busy()||me->is_fighting())
	{
		return notify_fail("你正在忙碌，无暇分心？\n");

	}
	if (!objectp(ke=present("ke zhene",this_object()))) 
	{
		do_fail(me);
		return notify_fail("你脾气暴躁，结果柯镇恶为你失手杀死，任务失败！\n");
	}
	if (!objectp(zhu=present("zhu cong",this_object())))
	{
		do_fail(me);
		return notify_fail("你脾气暴躁，结果朱聪为你失手杀死，任务失败！\n");
	}
	if (!objectp(han=present("han baoju",this_object())))
	{
		do_fail(me);
		return notify_fail("你脾气暴躁，结果韩宝驹为你失手杀死，任务失败！\n");
	}
	if (!objectp(nan=present("nan xiren",this_object())))
	{
		do_fail(me);
		return notify_fail("你脾气暴躁，结果南希仁为你失手杀死，任务失败！\n");
	}
	if (!objectp(zhang=present("zhang asheng",this_object())) )
	{
		do_fail(me);
		return notify_fail("你脾气暴躁，结果张阿生为你失手杀死，任务失败！\n");
	}
	if (!objectp(quan=present("quan jinfa",this_object())) )
	{
		do_fail(me);
		return notify_fail("你脾气暴躁，结果全金发为你失手杀死，任务失败！\n");
	}
	if (!objectp(ying=present("han xiaoying",this_object())))
	{
		do_fail(me);
		return notify_fail("你脾气暴躁，结果韩小莹为你失手杀死，任务失败！\n");
	}
	if (!living(ke)) return notify_fail("先把柯镇恶弄醒再说！\n");
	if (!living(zhu)) return notify_fail("先把朱聪弄醒再说！\n");
	if (!living(han)) return notify_fail("先把韩宝驹弄醒再说！\n");
	if (!living(nan)) return notify_fail("先把南希仁弄醒再说！\n");
	if (!living(zhang)) return notify_fail("先把张阿生弄醒再说！\n");
	if (!living(quan)) return notify_fail("先把全金发弄醒再说！\n");
	if (!living(ying)) return notify_fail("先把韩小莹弄醒再说！\n");
	me->start_busy(30);
	
	me->set("quest/射雕英雄传/江南七怪/dadu",1);
	
	message_vision(HIC"$N坐了下来，道：“我这个法子，时候是拖得长些，可是赌的却是真功夫真本事，并非单拚一时的血气之勇。\n"
					"刀剑拳脚上争先决胜，凡是学武的个个都会。咱们都是武林中的成名人物，决不能再像后生小子们那样不成器。”\n"
					"江南七怪都想：“不用刀剑拳脚决胜负，又用甚么怪法子？难道再来比喝酒？”$N昂然道：“咱们来个大比赛，我\n"
					"一人对你们七位，不但比武功，还得斗恒心毅力，斗智巧计谋，这一场大比拚下来，要看到得头来，到底谁是真\n"
					"英雄真豪杰。”这番话只听得江南七怪个个血脉贲张。\n"
					NOR,me);
	call_out("do_bisai1",4+random(4),me);
	return 1;
}
int do_bisai1(object me)
{
	message_vision(YEL"\n\n$N道：“推本溯源，咱们误打误伤，是为了拯救忠义的后代而起，那么这件事还得归结在这上面。”于是把如何结识\n"
					"郭杨二人、如何追赶段天德的经过说了。江南七怪听在耳中，不住口的痛骂金人暴虐，朝廷官吏无耻。$N述毕，\n"
					"说道：“那段天德带出去的，便是郭啸天的妻子李氏，除了柯大哥与韩家兄妹，另外四位都见到他们了。”柯镇恶道：\n"
					"“我记得她的声音，永世不会忘记。”$N道：“很好。至于杨铁心的妻子包氏，却不知落在何方。那包氏贫道曾经见过，\n"
					"各位却不认得。贫道与各位赌的就是这回事。因此法子是这样……”韩小莹抢着道：“我们七人去救李氏，你去救包氏，\n"
					"谁先成功谁胜，是不是？”\n"
					NOR,me);
	call_out("do_bisai2",4+random(4),me);
	return 1;
}

int do_bisai2(object me)
{
	message_vision(WHT"\n\n$N道：“过得一十八年，孩子们都十八岁了，咱们再在嘉兴府醉仙楼头相会，大邀江湖上的英雄好汉，欢宴一场。\n"
					"酒酣耳热之余，让两个孩子比试武艺，瞧是贫道的徒弟高明呢，还是七侠的徒弟了得？”江南七怪面面相觑，哑口无言。\n"
					"$N又道：“要是七位亲自与贫道比试，就算再胜一场，也不过是以多赢少，也没甚么光彩。待得我把全身本事教给了一人，\n"
					"七位也将艺业传给一人。让他二人一对一的比拚，那时如果贫道的徒弟得胜，七侠可非得心服口服不可。”\n"
					HIR"\n\n柯镇恶豪气充塞胸臆，铁杖重重在地下一顿，叫道：“好，咱们赌了。”\n"NOR,me);
	call_out("do_bisai3",4+random(4),me);
	return 1;
}

int do_bisai3(object me)
{
	message_vision(HBYEL+HIW"\n\n恭喜你，终于完成《射雕英雄传》之《江南七怪》章节！\n"NOR,me);
	message_vision(HBYEL+HIW"\n\n敬请期待下一章节《大漠风沙》的精彩情节！\n"NOR,me);

	me->set_temp("quest/射雕英雄传/江南七怪/over",1);
	me->set("quest/射雕英雄传/江南七怪/over",1);
	me->set("quest/射雕英雄传/time",time());
	clear_here();
	return 1;
}
//失败函数
int do_fail(object me)
{
	if (!me)
	{
		me->delete_temp("quest/射雕英雄传/江南七怪");
		me->set("quest/射雕英雄传/time",time());
		me->add("quest/射雕英雄传/fail",1);

		return notify_fail("任务中被杀，失败！\n");
	}
	if (!living(me))
	{
		me->delete_temp("quest/射雕英雄传/江南七怪");
		me->set("quest/射雕英雄传/time",time());
		me->add("quest/射雕英雄传/fail",1);
		clear_here();
		return notify_fail("任务中被打晕，失败！\n");
	}
	return 1;
}

int clear_here()
{
	object ke,zhu,han,nan,zhang,quan,ying;

	if (objectp(ke=present("ke zhene",this_object()))) 
	{
		destruct(ke);
	}
	if (objectp(zhu=present("zhu cong",this_object())))
	{
		destruct(zhu);
	}
	if (objectp(han=present("han baoju",this_object())))
	{
		destruct(han);
	}
	if (objectp(nan=present("nan xiren",this_object())))
	{
		destruct(nan);
	}
	if (objectp(zhang=present("zhang asheng",this_object())) )
	{
		destruct(zhang);
	}
	if (objectp(quan=present("quan jinfa",this_object())) )
	{
		destruct(quan);
	}
	if (objectp(ying=present("han xiaoying",this_object())))
	{
		destruct(ying);
	}

	return 1;
}