// /area/jiangbei/wudang/zixia.c 紫霄宫
// By River@SJ

inherit ROOM;
#include <ansi.h>
int do_heal(string arg);
int zhao_come(object me,object zsf);
int check_fight(object me,object asan);
//check_fight(me,zsf,asan);	

void create()
{
        set("short", HIW"紫霄宫"NOR);
        set("long", @LONG
规模宏大，气势磅礴的紫霄宫，座落在武当山展旗峰下。这里群峰山岭环
绕，松林翠柏幽深，环境优雅，气候宜人，历来被视为“紫霄福地”。紫霄宫
初建于宋宣和年间。宋徽宗赵佶一次做梦，梦见了“火神”，有一方士为他圆
梦，说要派水神到南方压镇，才能无忧。于是选中了七十二福地之一的武当山，
在展旗峰下为水神玄武建造了这座宫殿，并赐额“紫霄元圣宫”。 
LONG
        );

        set("exits", ([
                "out" : __DIR__"zxgdamen",
                "southup" : __DIR__"nanyan",
        ]));

        set("no_clean_up", 0);

        set("objects",([
                CLASS_D("wudang")+ "/wanqing" : 1,
                __DIR__"npc/daotong" :2,
        ]));

        set("outdoors", "武当");

        setup();
}
void init()
{
	object me=this_player();
	if (!me->query_temp("mwd/start")) return;
	
	if (me->query_temp("mwd/step6")
		&&me->query_temp("mwd/start")
		&&!me->query("mwd/over"))
	{
		me->start_busy(3);
		
		call_out("do_find",2+random(3),me);
		me->delete_temp("mwd/step6");
	}

}
int do_find(object me)
{
		object kongxiang;
		message_vision(HIG"\n\n$N心中焦虑，快步如飞，但看四周的小道士们似乎都在各自忙碌，似乎那种灾难还没有发生，心中不由大定。\n\n"
							+"正在$N行走间，忽然看到前方一位少林僧人正在匆匆奔走，神色似乎甚是慌张。\n"NOR,me);
	    me->delete_temp("mwd/step6");
		if (!objectp(kongxiang=present("kongxiang dashi",this_object())))
		{
		
			kongxiang=new("d/wudang/taiji/kongxiang");
			kongxiang->move(this_object());
			kongxiang->greeting();
		}
		me->set_temp("mwd/step7",1);
		call_out("find_yudaiyan",3+random(3),me,kongxiang);
		return 1;
}
int find_yudaiyan(object me,object kongxiang)
{
	message_vision(HIY"\n\n$N心中疑惑，心想这一路走来，看来是少林来此通报张真人的人员，不过这空相看起来好像甚是慌张的样子。\n\n"
							+"不多久，俞岱岩在小道童的搀扶下，缓缓走来，和空相谈了会，神色甚是紧张，吩咐小道童道，抬我去见祖师爷。\n"NOR,me);
	call_out("zhang_come",3+random(3),me,kongxiang);	
	return 1;
}
int zhang_come(object me,object kongxiang)
{

	object zsf;
	//object room;
	//room=load_object("d/wudang/houyuan");
	message_vision(HIC"\n\n半盏茶光景，一位须眉皆白的老道人缓步走来，正是名震武林的开山祖师张三丰！。\n\n"NOR,me);
	if (!objectp(zsf=present("zhang sanfeng",this_object())))
	{
		zsf=new("kungfu/class/wudang/zhang");
		zsf->move(this_object());
		//zsf->command("chat ....");
	}

	call_out("kx_kill",2+random(3),me,kongxiang,zsf);

}

int kx_kill(object me,object kongxiang,object zsf)
{
	
	message_vision(HIC"\n\n空相一见张三丰来到，扑通一声跪倒，嚎啕大哭。\n\n"NOR,me);
	kongxiang->greet2();
	message_vision(HIY"\n\n张三丰眼见空相如此难过，也长长叹了一口气道，“你先起来，我们再商议商议。”说罢就想将空相搀扶起来。\n"NOR,me);
	message_vision(HIR"\n\n那知此时，风云突变，空相忽然变得面目狰狞，一掌拍向张三丰的小腹！！”\n"NOR,me);
	kongxiang->kill_ob(zsf);
	zsf->kill_ob(kongxiang);
	zsf->receive_wound("qi",2000+random(1000),kongxiang);
	zsf->apply_condition("neishang",10);
	me->delete_temp("mwd/step7");
	me->set_temp("mwd/step8",1);
	add_action("do_heal","heal");
	return 1;
}

int do_heal(string arg)
{
	object me=this_player();
	object zsf,kongxiang;
	zsf=present("zhang sanfeng",this_object());
	
	if (objectp(kongxiang=present("kongxiang dashi",this_object())))
	{
		return notify_fail("空相正在和张真人生死搏斗，你要干什么？");
	}
	if (!objectp(zsf)) return 0;

	if (me->is_fighting() || zsf->is_fighting())
	{
		return notify_fail("你现在正在很忙。\n");
	}
	if (!me->query_temp("mwd/step8"))
	{
		return notify_fail("你没事莫名其妙的跑来瞎捣乱，疗什么伤？");
	}
	if (!arg || arg !="张三丰")
	{
		return notify_fail("你要为谁疗伤？");
	}
	message_vision(YEL"\n\n$N纵身而起，将手搭在张三丰的背后，运功为其疗伤。张三丰只觉一股内劲磅礴而来，惊讶的看了$N一眼。\n"NOR,me);
	message_vision(HIY"\n\n\n在$N的全力运转之下，$n伤势大为好转，但随即又吐了一口鲜血，$n深知方才这一掌着实受伤不轻。\n"NOR,me,zsf);
	message_vision(HIR"\n\n$n抬头看了一眼$N，轻笑道，没想到我武当派居然还有如此高手，你是谁的门下？\n"NOR,me,zsf);
	message_vision(HIG"\n\n$n说道，$N这一身功夫甚是了得，看来我武当要大兴了，哈哈哈哈！？\n"NOR,me,zsf);
	message_vision(HIG"\n\n俞岱岩默然不答，心知山上除了师父和自己之外，其余三四代弟子的武功都不足道，出面御敌，\n"
						+"只有徒然送死，今日之事，惟有自己舍却一命，和敌人敷衍周旋，让师父避地养伤，日后再复大仇，\n"
						+"于是朗声道：“灵虚，你去跟那些人说，我便出来相见，让他们在三清殿等着。”灵虚答应着去了。\n"NOR,me);
	message_vision(YEL"\n\n张三丰和俞岱岩师徒相处日久，心意相通，听他这么说，已知其意，说道：“岱岩，生死胜负，无足介怀，\n"
						+"武当派的绝学却不可因此中断。我坐关十八月，得悟武学精要，一套太极拳和太极剑，此刻便传了你罢。\n"
						+"俞岱岩一呆，心想自己残废已久，那还能学什么拳法剑术？何况此时强敌已经入观，怎有余暇传习武功\n"
						+"只叫了声：“师父！”便说不下去了。\n"NOR,me);
	message_vision(WHT"\n\n张三丰淡淡一笑，说道：“我武当开派以来，行侠江湖，多行仁义之事，以大数而言，决不该自此而绝。\n"
						+"我这套太极拳和太极剑，跟自来武学之道全然不同，讲究以静制动、后发制人。你师父年过百龄纵使不遇强敌，。\n"
						+"又能有几年好活？所喜者能于垂暮之年，创制这套武功出来。远桥、莲舟、松溪、梨亭、声谷都不在身边，\n"
						+"第三四代弟子之中。除青书外并无杰出人材，何况他也不在山上。岱岩你身负传我生平绝艺的重任。武当派\n"
						+"一日的荣辱，有何足道？只须这套太极拳能传至后代，我武当派大名必能垂之千古。”说到这里，神采飞扬，\n"
						+"豪气弥增，竟似浑没将压境的强敌放在心上。俞岱岩唯唯答应，已明白师父要自己忍辱负重，以接传本派绝技为第一要义。\n"NOR,me);
	message_vision(CYN"\n\n张三丰缓缓站起身来，双手下垂，手背向外，手指微舒，两足分开平行，接着两臂慢慢提起至胸前，左臂半环\n"
						+"掌与面对成阴掌，右掌翻过成阳掌，说道：“这是太极拳的起手式。”跟着一招一式的演了下去,又口中叫着招式的\n"
						+"名称：揽雀尾、单鞭、提手上式、白鹤亮翅，搂膝拗步、进步搬拦锤、如封似闭、十字手、抱虎归山\n"
						+"$N初时还道太师父故意将姿势演得特别缓慢，使俞岱岩可以看得清楚，但看到第七招‘手挥琵琶’之时，只见他左掌阳、右掌阴\n"
						+"目光凝视左手手臂，双掌，慢慢合拢，竟是凝重如山，却又轻灵似羽。张无忌陡然之间省悟：“这是以慢打快、以静制动的上乘武学\n"
						+"想不到世间竟会有如此高明的功夫。$N武功本就极高，一经领会，越看越入神，但见张三丰双手圆转，每一招都含着太极式的阴阳变化，\n"
						+"精微奥妙，实是开辟了武学中从所未有的新天地。。\n"NOR,me);
	message_vision(HIW"\n\n张三丰道：“这拳劲首要在似松非松，将展未展，劲断意不断……”正要往下解说，只听得前面三清殿上远远传来\n"
						HIR+"\n\n一个苍老悠长的声音：“张三丰老道既然缩头不出，咱们把他徒子徒孙先行宰了。”另一个粗豪的声音道：“好啊！\n"
						+"先一把火烧了这道观再说。”又有一个尖锐的声音道：“烧死老道，那是便宜了他。咱们擒住了他，\n"
						+"绑到各处门派中游行示众，让大家瞧瞧这武学泰斗老而不死的模样。”\n"NOR,me);
	
	me->set_temp("mwd/step9",1);
	me->delete_temp("mwd/step8");
	call_out("zhao_come",2+random(3),me,zsf);
	return 1;

}

int zhao_come(object me,object zsf)
{
	object zhao,he,lu,laoda,laoer,laosan;
	if (!objectp(zhao=present("zhao min",this_object())))
	{
		zhao=new("d/city/kedian/zhao");
		zhao->move(this_object());
	}
	
	if (!objectp(he=present("he biweng",this_object())))
	{
		he=new("d/city/kedian/hebw");
		he->move(this_object());
	}
	if (!objectp(lu=present("lu zhangke",this_object())))
	{
		lu=new("d/city/kedian/luzk");
		lu->move(this_object());
	}
	//阿大，阿二，阿三
	if (!objectp(laosan=present("a san",this_object())))
	{
		laosan=new("d/wudang/taiji/asan");
		laosan->move(this_object());
	}
	if (!objectp(laoer=present("a er",this_object())))
	{
		laoer=new("d/wudang/taiji/aer");
		laoer->move(this_object());
	}
	if (!objectp(laoer=present("a da",this_object())))
	{
		laoda=new("d/wudang/taiji/ada");
		laoda->move(this_object());
	}
	zhao->greet_zhang();
	laosan->greet_zhang();
	
	message_vision(HIG"\n\n阿三见张三丰居然飘然下场，心下倒生了三分怯意，但转念又想：“今日我便和这老道拼个两败俱伤，\n"
						+"那也是耸动武林的盛举了。”当下屏息凝神，双目盯住在张三丰脸上，内息暗暗转动，周身骨骼劈劈拍拍，！\n"
						+"不绝发出轻微的爆响之声。众人又均相顾一愕，知道这是佛门正宗的最上武功，自外而内，不带半分邪气，乃\n"
						+"是金刚伏魔神通。张三丰见到他这等神情，也是悚然一惊：“此人来历不小啊！不知我这太极拳是否对付得了？”\n"NOR,me);


	message_vision(HIC"\n\n张三丰年近百岁，又受刚相偷袭受伤，不知道能否抵抗的住这位高手？"+HIR"你是否愿意代替张三丰出战（douquan）？\n"NOR,me);
	
	add_action("do_bishi1","douquan");
	return 1;

}
int do_bishi1()
{

	object me=this_player();
	object asan;
	asan=present("a san",this_object());
	if (!me->query_temp("mwd/step9"))
	{
		return notify_fail("你没事莫名其妙的跑来做什么斗拳？");
	}
	if (!asan)
	{
		asan=new("d/wudang/taiji/asan");
		asan->move(this_object());
	}
	if (me->query_skill_mapped("cuff")!="taiji-quan"||me->query_skill_mapped("parry")!="taiji-quan")
	{
		return notify_fail("张真人让你用太极拳去斗阿三，你没有激发太极拳。\n");
	}
	message_vision(HIY"\n\n$N诚心要在$n面前显示武当派的威风，运功朗声说道，请祖师歇息片刻，这等小毛贼，徒儿打法他就是了。\n"
						+"也好让他见识见识我武当派的武功，省的他坐井观天，不知中原豪杰。\n"NOR,me,asan);
    message_vision(CYN"\n\n张三丰见你出场，知道你内功了得，于是微微笑道道。“也好，既然这位金刚伏魔神功的英雄想见识见识”\n"
						+"我武当的神技，那就把我这新近参悟的太极拳的奥秘说与你听听，看你是否能融会贯通。\n"NOR,me,asan);
	
	message_vision(HIR"\n\n$N听了张三丰祖师的讲解，对于太极拳的理解又深了一层。\n"	NOR,me);

	asan->fight_ob(me);
	me->fight_ob(asan);

	call_out("check_fight",3+random(3),me,asan);
	return 1;
}

int check_fight(object me,object asan)
{
	if (me->is_fighting(asan))
	{
		remove_call_out("check_fight");
		call_out("check_fight",2,me,asan);
		return 1;
	}
	if (!living(me))
	{
		call_out("fight_fail",1,me);
		return notify_fail("被阿三打晕，任务失败。\n");
	}
	message_vision(HIC"\n\n$N对$n说道，“我新学的这套拳术，乃我师父张真人多年心血所创，叫作‘太极拳’。晚辈初学乍练，\n"
						+"未必即能领悟拳法中的精要，三十招之内，恐怕不能将你击倒。但那是我学艺未精，并非\n"
						+"这套拳术不行，这一节你须得明白。\n"NOR,me,asan);
	
	message_vision(HIY"\n\n\n张三丰对$N说道，”用意不用力，太极圆转，无使断绝。当得机得势，令对手其根自断。一招一式，务须节节\n"
						+"贯串，如长江大河，滔滔不绝。”张三丰适才见$N临敌使招，已颇得太极三味，只是他原来武功太强，\n"
						+"拳招中棱角分明，未能体会太极拳那‘圆转不断’之意。\n"NOR,me);
	asan->greet_yu();
	asan->kill_ob(me);
	me->kill_ob(asan);
	call_out("douquan_finish",3+random(2),me,asan);
	return 1;

}
int douquan_finish(object me,object asan)
{

	if (!objectp(me))
	{
		return 0;
	}
	if (!living(me))
	{
		me->delete_temp("mwd");
		call_out("fight_fail",1,me);
		return notify_fail("你终究是太极拳功力不纯，为阿三大力金刚指所伤，昏迷不醒。");
	}
	if (objectp(asan))
	{
		remove_call_out("douquan_finish");
		call_out("douquan_finish",2,me,asan);
		return 1;
	}

	message_vision(HIY"\n\n经过激烈的打斗，$N将阿三彻底杀死，了却了这一段往日的恩怨，张三丰看在眼里，喜在心上，看着$N越看越是欣赏。\n"NOR,me);
	message_vision(HIY"\n\n张三丰对$N微微一笑道，“你这孩子真是不错，这次如果武当派渡过危机，你可以到后院去找我请教关于太极拳的奥利。”\n"NOR,me);
	
	message_vision(HIG"\n\n这时，忽听场外阿二喝道，“兀那秃贼，你可敢与我比拼内力么？"+HIR+"继续比斗（answer yes）or 放弃（answer no）”\n"NOR,me);
	message_vision(HIG"\n\n$N见这个瘦子，太阳穴凹陷极深，双目中神光含蕴，一看就是内功修炼到极为高深的境界，$N心中凛然，看来这是一场内力比拼啊！！！”\n"NOR,me);
	//第一战结束
	me->set_temp("mwd/step9",1);
	me->delete_temp("mwd/step8");
	me->set_temp("helpwd/fightasan",1);
	me->set("helpwd/fightasan",1);
	add_action("do_answer","answer");
	return 1;	

}

int do_answer(string arg)
{
	object me=this_player();
	object aer;
	int ap,dp;
	
	aer=present("a er",this_object());
	if (!me->query_temp("mwd/step9"))
	{
		return notify_fail("你没事莫名其妙的跑来做什么乱回答什么？");
	}
	if (!aer)
	{
		aer=new("d/wudang/taiji/laoer");
		aer->move("d/wudang/zixia");
	}
	
	ap=me->query_skill("force",1)*me->query("neili")/1000;
	dp=aer->query_skill("force",1)*aer->query("neili")/1000;
	if (arg=="yes")
	{
		message_vision(HIC"\n\n你朗声喝道，我大武当的内功号称天下第一，不服就来战！\n"NOR,me);
		message_vision(HIY"\n\n那秃头阿二闪身而出，右掌疾向$N胸口劈来，掌尖未至，$N已觉气息微窒，当下一招‘斜飞式’，\n"
					+"将他掌力引偏。这秃头老者一声不出，下盘凝稳，如牢钉在地，专心致志，一掌一掌的劈出，内力雄浑无比。\n"NOR,me);
		aer->kill_ob(me);
		me->kill_ob(aer);
		aer->start_busy(999);
		me->start_busy(999);
		
		message_vision(HIC"\n\n$N一声喝处，右拳挥出，砰的一声大响，那秃头阿二连退三步，双目鼓起，胸口气血翻涌，\n"
					+"只听那秃头阿二周身骨节劈劈拍拍的发出响声，正自运劲。阿二双臂一振，一股力道排山倒海般推了过来\n"NOR,me);
		if (random(ap)>dp/4)
		{
			message_vision(HIY"\n\n$N踏上一步，却不出击,吸了一口气，体内真气流转，双掌挥出，一拒一迎，将对方掌力尽行碰了回去。\n"
					+"这两股巨力加在一起，那阿二大叫一声，身子犹似发石机射出的一块大石，喀喇喇一声响，撞破墙壁，冲了出去。\n"NOR,me);
			aer->set("qi",1);
			aer->set("neili",1);
			if (me->query("neili")>aer->query("neili"))
			{
				me->add("neili",-aer->query("neili"));
			}else me->set("neili",100);
		}else {
			message_vision(HIR"\n\n$N踏上一步，却不出击,吸了一口气，体内真气流转，双掌挥出，一拒一迎，将对方掌力尽行碰了回去。\n"
						+"但是阿二功力终究是高你一筹，这两股巨力加在一起反弹回来，$N身子犹似发石机射出的一块大石，\n"
						+"喀喇喇一声响，撞破墙壁，冲了出去。\n"NOR,me);						
						me->set("qi",1);
						me->set("neili",0);
						call_out("fight_fail",1,me);
						return 0;
		}
	}else if (arg=="no")
	{
		message_vision(HIC"$N想了会，觉得自己实力还是不足，决定暂时先放弃。\n"NOR,me);
		return 0;
		
	}
	me->start_busy(2);
	aer->start_busy(2);
	call_out("check_fight2",2,me,aer);
	return 1;
}

//第三场和方东白大战

int check_fight2(object me,object aer)
{
	object zhao;
	zhao=present("zhao min",this_object());

	if (!objectp(me)) 
	{		
		return 1;
	}
	if (!living(me))
	{
		me->delete_temp("mwd");
		call_out("fight_fail",1,me);
		return notify_fail("你终究是内功功力不纯，为阿二深厚内力所伤，昏迷不醒。");
	}
	if (!objectp(aer))
	{
		zhao->greet_ada();
		message_vision(HIR"\n\n\n第三场比试即将开始了，对方是曾经的丐帮长老方东白，乃是剑术高手，你已经准备好了要参加（doujian）？\n"NOR,me);
		add_action("do_doujian","doujian");	
		me->set_temp("mwd/step10",1);
		me->delete_temp("mwd/step9");
		me->set_temp("helpwd/fightaer",1);
		me->set("helpwd/fightaer",1);
		return 1;
	}	
	call_out("check_fight2",2,me,aer);
	return 1;

}

int do_doujian()
{
	object ada,me,zhao;
	object weapon;
	me=this_player();
	zhao=present("zhao min",this_object());
	
	ada=present("a da",this_object());
	if (!ada)
	{
		ada=new("d/wudang/taiji/laoda");
		ada->move("d/wudang/zixia");
	}	
	if (!me->query_temp("mwd/step10"))
	{
		return notify_fail("你没事莫名其妙的跑来做什么斗剑？");
	}
	message_vision(HIC"\n\n$N暗暗发愁，这口倚天剑锋锐无匹，任何兵刃碰上即断，惟一对策，只有巧劲空手夺他兵刃。\n"
						+"然而伸手到这等锋利的宝剑之旁，只要对方的剑招稍奇，变化略有不测，自己一条手臂自指尖以至肩头\n"
						+"不论那一处给剑锋一带，立时削断，如何对敌，倒是颇费踌躇。忽听张三丰道：“$N，我创的太极拳，\n"
						+"已经交给你了，另有一套太极剑不妨现下传了你，可以用来跟这位施主过过招。$N喜道：“多谢师父。\n"
						+"$N转头向阿大道：“这位前辈，我剑术不精，须得请太师父指点一番，再来跟你过招。”\n"NOR,me);

	message_vision(HIW"\n\n那阿大对$N原本暗自忌惮，自己虽有宝剑在手，占了便宜，究属胜负难知，听说他要新学剑招。\n"
						+"那是再好不过，心想新学的剑招尽管精妙，总是不免生疏。剑术之道，讲究轻翔灵动，至少也得\n"
						+"练上一二十年，临敌时方能得心应手，熟极而流。他点了点头，说道：“你去学招罢，我在这里等\n"
						+"你。学两个时辰够了吗？张三丰道：“不用到旁的地方，我在这儿教，无忌在这儿学，即炒即卖，”\n"
						+"新鲜热辣。不用半个时辰，一套太极剑法便能教完。\n"NOR,me);

	message_vision(HIG"\n\n张三丰道：“老道这路太极剑法能得八臂神剑指点几招，荣宠无量。$N，你有佩剑么？”\n"
						+"旁边道童上前几步，呈上张无忌从赵敏处取来的那柄木制假倚天剑。张三丰接在手里，笑道：\n"
						+"“是木剑？老道这不是用来画符捏诀、作法驱邪么？”\n"	NOR,me);

	message_vision(HIY"\n\n张三丰当下站起身来，左手持剑，右手捏个剑诀，双手成环，缓缓抬起，这起手式一展，跟着三环套月”\n"
						+"大魁星、燕子抄水、左拦扫、右拦扫……一招招的演将下来，使到五十三式‘指南针’，双手同时画圆，\n"
						+"复成第五十四式‘持剑归原’。张无忌不记招式，只是细看剑招中‘神在剑先、绵绵不绝’之意。\n"	NOR,me);

						
	message_vision(CYN"\n\n只听张三丰问道：“孩儿，你看清楚了没有？”$N道：“看清楚了。”张三丰道：“都记得了没有？”$N道：”\n"
						+"“已忘记了一小半。”张三丰道：“好，那也难为了你。你自己去想想罢。”$N低头默想。过了一会，\n"
						+"张三丰问道：“现下怎样了？”$N道：“已忘记了一大半。”\n"	NOR,me);
	message_vision(HIG"\n\n只听张三丰问道：“孩儿，你看清楚了没有？”$N道：“看清楚了。”张三丰道：“都记得了没有？”$N道：”\n"
						+"“已忘记了一小半。”张三丰道：“好，那也难为了你。你自己去想想罢。”$N低头默想。过了一会，\n"
						+"张三丰问道：“现下怎样了？”$N道：“已忘记了一大半。”\n"	NOR,me);
	
	message_vision(HIY"\n\n$N听了张三丰祖师的讲解，对于太极剑的理解又深了一层。\n"	NOR,me);
	
	if (!objectp(weapon=me->query_temp("weapon"))
		||me->query_skill_mapped("sword")!="taiji-jian"
		||me->query_skill_mapped("parry")!="taiji-jian")
	{
		return notify_fail(HIR"\n\n张真人刚传授了你的太极剑，你不激发使用,如何去领悟其中的真意？\n"NOR);
	}
	ada->greet_ada();
	ada->kill_ob(me);
	me->kill_ob(ada);
	call_out("last_fight",1,me,ada);
	return 1;
}

int last_fight(object me,object ada)
{
	object lu,he,zhao;
	if (!objectp(zhao=present("zhao min",this_object())))
	{
		zhao=new("d/city/kedian/zhao");
		zhao->move("d/wudang/zixia");
	}	
	if (!objectp(he=present("he biweng",this_object())))
	{
		he=new("d/city/kedian/hebw");
		he->move("d/wudang/zixia");
	}
	if (!objectp(lu=present("lu zhangke",this_object())))
	{
		lu=new("d/city/kedian/luzk");
		lu->move("d/wudang/zixia");
	}
	if (!me)
	{		
		return 1;
	}
	if (!living(me))
	{
		me->delete_temp("mwd");
		call_out("fight_fail",1,me);
		return notify_fail("你功力终究是太极剑运使不纯，为阿大剑术所伤，顿时昏迷不醒。\n");

	}
	if (!objectp(ada)&& !me->is_fighting())
	{
		message_vision(HIC"\n\n赵敏眼见下属都死去，全不理睬，说道：“今日瞧在$N的脸上，放过了武当派。”\n"
						+"左手一挥，道：“走罢！”她手下部属抱起方东白、秃头阿二、阿三的尸体，向殿外便走。\n"
						+"$N叫道：“且慢！不留下黑玉断续膏，休想走下武当山。”纵身而上，伸手往赵敏肩头抓去。\n"NOR,me);

		message_vision(HIB"\n\n手掌离她肩头尚有尺许，突觉两股无声无息的掌风分自左右击到，事先竟没半点朕兆。”\n"
						+"$N一惊之下，双掌翻出，右手接了右边击来的一掌，左手接了从左边击来的一掌，四掌同时相碰，\n"
						+"只觉来劲奇强，掌力中竟夹着一股阴冷无比的寒气。正是闻名武林的玄冥神掌！\n"NOR,me);
		lu->kill_ob(me);
		me->kill_ob(lu);

		he->kill_ob(me);
		me->kill_ob(he);

		me->delete_temp("mwd/step10");
		me->set_temp("mwd/step11",1);
		me->set_temp("helpwd/fightada",1);
		me->set("helpwd/fightasan",1);
		call_out("check_fight3",10,me,lu,he,zhao);
		return 1;
	}
	call_out("last_fight",2,me,ada);
	return 1;
}

int check_fight3(object me,object lu,object he,object zhao)
{
	object zhang;
	int exp;
	zhang=present("zhang sanfeng",this_object());
	if (!me) return 0;
	
	if (!living(me))
	{
		me->delete_temp("mwd");
		call_out("fight_fail",1,me);
		return notify_fail("你被玄冥神掌寒气所致，顿时一口气没有缓过来，昏倒在地，人事不省。\n");
	}
	
	if (!me->is_fighting())
	{
		message("channel:chat", HIC"【聊天】鹤笔翁："+me->query("name")+HIC"好大的名头，武当也不过如此而已！\n"NOR, users());
		message("channel:chat", HIC"【聊天】鹿杖客：什么泰山北斗，在我玄冥二老面前都是土鸡瓦狗之辈，嘿嘿！\n"NOR, users());
		message("channel:chat", HIC"【聊天】赵敏：今日瞧在"+me->query("name")+HIC"的面上，放过了武当派，我们走！\n"NOR, users());
		if (objectp(zhao))
			destruct(zhao);
		if (objectp(he)) destruct(he);
		if (objectp(lu)) destruct(lu);
		
		message_vision(HIY"\n\n众人见$N受伤，顿时围了上来，$N微微一笑，右手轻轻摆了一下，意示并不妨事，体内氤氲紫气神功发动，\n"
							+"将玄冥神掌的阴寒之气逼了出来，头顶便如蒸笼一般不绝有丝丝白气冒出。\n"NOR,me);

		message_vision(HIC"\n\n张三丰非常满意的看着$N，微微点头，说道，“经此一战，我相信你收获良多，”\n"
							+"你伤好了后，就去后山跟我请教，我好好跟你讲讲这太极的奥秘。“说完飘然而去。\n"NOR,me);
		if (objectp(zhang))
			destruct(zhang);
		me->set_temp("mwd/over",1);
	    me->set_temp("helpwd/fightxm",1);
		me->set("helpwd/fightxm",1);
		me->set("mwd/over",1);
		me->delete_temp("helpwd");
		me->delete_temp("mwd");
		exp=2000+random(500);
		me->add("combat_exp",exp);
		message_vision(HIY"\n\n你如此努力为门派杀敌，张真人决定给你些经验值奖励，你获得了"HIR+chinese_number(exp)+HIY"点经验值奖励，”\n"NOR,me);
		return 1;		
	}
	call_out("check_fight3",2,me,lu,he,zhao);
	return 1;
}

int fight_fail(object me)
{
	object zhao,zhang,lu,he,ada,aer,asan,room;
	room=load_object("d/wudang/houyuan");
	me->set("quest/wd/taiji/time",time());
	me->add("quest/wd/taiji/fail",1);
	if (objectp(zhao=present("zhao min",this_object())))
		destruct(zhao);
	if (objectp(he=present("he biweng",this_object())))
		destruct(he);
	if (objectp(lu=present("lu zhangke",this_object())))
		destruct(lu);
	if (objectp(ada=present("a da",this_object())))
		destruct(ada);
	if (objectp(aer=present("a er",this_object())))
		destruct(aer);
	if (objectp(asan=present("a san",this_object())))
		destruct(asan);
	if (objectp(zhang=present("zhang sanfeng",this_object())))
		if (!objectp(present("zhang sanfeng",environment(room))))
		{
			zhang->move("d/wudang/houyuan");
		}else destruct(zhang);
	me->delete_temp("mwd");
	me->delete_temp("helpwd");

	message_vision(HIR"非常抱歉，本次解救武当危机的任务失败，等你武功练高了后再来。\n"NOR,me);
	return 1;
}
