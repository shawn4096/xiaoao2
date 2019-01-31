// Room: /d/huashan/song.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","山崖松");
	set("long",@long
这是一株从山崖旁边自然长成的一株大松树，虽然山风凛冽，
但松树生得异常遒劲，年代古远，树根由石缝中长出，紧紧攀着
崖壁，仅容一人藏身之处。
long);
/*
	set("exits",([
	"enter" : __DIR__"hole2",
	"down" : __DIR__"v-road-5",
	]));*/
	set("cang",10);
    set("outdoors", "华山");

	setup();
}
void init()
{
    object me=this_player();
	//if (me->query_temp("pxj/tiaochuang"))	  
	//{
		//call_out("pxj_jiasha",5+random(10),me);
	//}
	add_action("do_gou","gou");
	add_action("pxj_cang","cang");
	add_action("do_bang","bang");
	add_action("do_climb","pa");

}
int pxj_cang()
{
	object me=this_player();
	if (me->query_temp("hspxj/cang"))
	{
		return notify_fail("你已经藏好了！\n");
	}
	if (me->query_skill("pixie-jian",1)<=150)
	{
		me->move("d/huashan/qinshi");
		message_vision(HIC"你刚想躲藏起来，忽听屋内岳不群的声音喊道，"+me->query("name")+"别躲了，我看到你了，鬼鬼祟祟的捉迷藏么？\n"NOR,me);
		message_vision(HIC"$N讪讪的从树后跃回到寝室中，面红耳赤，神情尴尬。\n"NOR,me);
		return 1;
	}
	if (this_object()->query("cang")>0)
	{
		message_vision(HIY"\n\n$N忽然听有人脚步声响从寝室外传来，心中一惊，急忙躲藏在松树后躲好。\n"NOR,me);
		this_object()->add("cang",-1);
		me->set_temp("hspxj/cang",1);
		call_out("pxj_jiasha",5+random(5),me);
		return 1;
	}else {

		message_vision(HIR"$N刚想藏身松树后，忽然发现树后已经藏了一个人，大惊之下，脚下站立不稳，一声惊叫掉下山崖。\n"NOR,me);
		me->move("/d/huashan/v-road-1.c");
		me->set("qi",0);
		me->unconcious();
	
	if (me->query("kar")<10)
		me->die();
		me->set_temp("last_damage_from","从山崖山摔下而");
		return 1;
	}

}

int pxj_jiasha(object me)
{
   message_vision(HIC"\n\n你刚在松树后藏好，互听寝室内传来脚步声，由远及近，似乎有两个人先后走了进来。\n"NOR,me);
   call_out("pxj_d1",3,me);
}

int pxj_d1(object me)
{
   message_vision(HIG"\n\n”师妹，师妹，你等会，方才是我不小心，师妹.....“$N一听知道这是岳不群的声音，心中甚是好奇。\n"NOR,me);
   call_out("pxj_d2",5,me);
}

int pxj_d2(object me)
{
 message_vision(HIY"\n\n师哥，我觉得你近来神色不对，是不是练那紫霞神功有些儿麻烦？可别太求精进，惹出乱子来。这似乎是岳夫人的声音。\n"NOR,me);
 call_out("pxj_d3",random(5),me);
}
int pxj_d3(object me)
{
 message_vision(HIG"\n\n\n岳不群笑了一声，说道：“没有啊，练功顺利得很。”。\n"NOR,me);
 call_out("pxj_d4",random(5),me);
}
int pxj_d4(object me)
{
 message_vision(HIC"\n\n\n岳夫人道：‘你别瞒我，为什么你近来说话的嗓子变了，又尖又高，倒像女人似的。’。\n"NOR,me);
 call_out("pxj_d5",random(5),me);
}
int pxj_d5(object me)
{
 message_vision(HIG"\n\n\n岳不群道：‘胡说八道！我说话向来就是这样的。’$N听得他说这句话，嗓声就尖得很，确象是个女子在大发脾气。\n"NOR,me);
 call_out("pxj_d6",random(5),me);
}
int pxj_d6(object me)
{
 message_vision(HIC"\n\n\n岳夫人说道：‘还说没变？你一生之中，就从来没对我这样说过话。我俩夫妻多年，你心中有什么解不开的事，何以瞒我？’。\n"NOR,me);
 call_out("pxj_d7",random(5),me);
}
int pxj_d7(object me)
{
 message_vision(HIG"\n\n\n岳不群道：‘有什么解不开的事？嗯嵩山之会不远，左冷禅意图吞并四派，其心昭然若揭。我为此烦心，那也是有的。’。\n"NOR,me);
 call_out("pxj_d8",random(5),me);
}
int pxj_d8(object me)
{
 message_vision(HIC"\n\n\n岳夫人道：‘我说了出来，你可别发火。我知道你是冤枉了冲儿。’\n"NOR,me);
 call_out("pxj_d9",random(5),me);
}
int pxj_d9(object me)
{
 message_vision(HIG"\n\n\n岳不群道：‘冲儿？他和魔教中人交往，和魔教那个姓任的姑娘结下私情，天下皆知，有什么冤枉的？’”\n"NOR,me);
 call_out("pxj_d10",random(5),me);
}
int pxj_d10(object me)
{
 message_vision(HIC"\n\n\n岳夫人说道：‘那定是他另有际遇。我断定他决计没拿辟邪剑谱。冲儿任性胡闹，不听你我的教训，那是有的。\n"
 +"但他自小光明磊落，决不做偷偷摸摸的事。自从珊儿跟平儿要好，将他撇下之后，他这等傲性之人，"
 +"\n便是平儿双手将剑谱奉送给他，他也决计不收。’”\n"
 +"\n\n岳夫人又继续说道：‘他犯了门规，你执行祖训，清理门户，无人可以非议。但你说他结交左道，罪名已经够了，\n"
 +"何必再冤枉他偷盗剑谱？其实你比我还明白得多。你明知他没拿平儿的辟邪剑谱。’岳不群却叫了起来：‘我怎么知道？我怎么知道？’”\n"NOR,me);
 call_out("pxj_d11",random(5),me);
}
int pxj_d11(object me)
{
 message_vision(HIB"\n\n\n岳不群的声音也是既高且锐，他尖声怒叫，静夜之中，有如厉枭夜啼，$N不由得毛骨悚然。\n"NOR,me);
 call_out("pxj_d12",random(5),me);
}
int pxj_d12(object me)
{
 message_vision(HIC"\n\n\n隔了一会，才听岳夫人缓缓的道：‘你自然知道，只因为这部剑谱，是你取了去的。’\n"
 +HIG"岳不群怒声吼叫：‘你……你说……是我……’但只说了几个字，突然住口。\n"
 +"\n\n岳夫人声音十分平静，说道：‘那日冲儿受伤昏迷，我替他止血治伤之时，见到他身上有件袈裟，\n"
 +"写满了字，似乎是剑法之类。第二次替他换药，那件袈裟已经不见了，共时冲儿仍然昏迷未醒。\n"
 +"这段时候之中，除了你我二人，并无别人进房。这件袈裟可不是我拿的。’”\n"
 +HIC"\n\n\n岳夫人语声渐转柔和，说道：‘师哥，我华山一派的剑术，自有独到的造诣，紫霞神功的气功更是不凡，\n"
 +"以此与人争雄，自亦足以树名声于江湖，原不必再去另学别派剑术。只是近来左冷禅野心大炽，图并四派。华山\n"
 +"一派在你手中，说什么也不能沦亡于他手中。咱们联络泰山、恒山、衡山三派，到时以四派斗他一派，我看还是\n"
 +"占了六成赢面。就算真的不胜，大伙儿轰轰烈烈的剧斗一场，将性命送在嵩山，也就是了，到了九泉之下，也不致\n"
 +"愧对华山派的列祖列宗。我劝你还是悬崖勒马，及早别学了罢。’”\n"NOR,me);
 call_out("pxj_d13",random(5),me);
}
int pxj_d13(object me)
{
 message_vision(HIG"\n\n\n岳不群大声道：‘你怎知我在学辟邪剑法？你……你……在偷看我吗？’岳夫人道：‘我又何必偷看才知道？’\n"
 +"岳不群大声道：‘你说，你说！’他说得声嘶力竭，话音虽响，却显得颇为气馁。”\n"
 +HIC"\n\n岳夫人道：‘你说话的声音，就已经全然变了，人人都听得出来，难道你自己反而不觉得？’岳不群还在强辩：\n"
 +"‘我向来便是如此。’岳夫人道：‘每天早晨，你被窝里总是落下许多胡须……’岳不群却尖叫一声：‘你瞧见了？’语音\n"
 +"甚是惊怖。岳夫人叹道：‘我早瞧见了，一直不说。你粘的假须，能瞒过旁人，却怎瞒得过和你做了几十年夫妻的枕边人？’\n"
 +HIG"\n\n\n岳不群见事已败露，无可再辩，隔了良久，问道：‘旁人还有谁知道了？’岳夫人道：‘没有。’岳不群问：‘珊儿呢？’\n"
 +HIC"\n\n岳夫人道：‘她不会知道的。’岳不群道：‘平之自然敢不知了？’岳夫人道：‘不知。’岳不群道：‘好，我听你的劝，这件袈裟，\n"
 +"明儿咱们就设法交给平之，再慢慢想法替令狐冲冼刷清白。这路剑法，我今后也不练了。’岳夫人十分欢喜，说道：‘那当真再好\n"
 +"也没有。不过这剑谱于人有损，岂可让平儿见到？还是毁去了的为是。’”\n"NOR,me);
 call_out("pxj_d14",random(5),me);
}
int pxj_d14(object me)
{
  message_vision(HIB"\n\n\n岳不群当时说道：‘很好，我立即毁去剑谱！’\n"
 +"$N大吃一惊，便想出声阻止，剑谱是林家之物，管他有益有害，岳不群可无权毁去。”\n"
 +HIR"\n\n便在此时，只听得窗子呀的一声打开，$N急忙缩头，眼前红光一闪，那件袈裟飘将下来，跟着窗子又即关上。\n"NOR,me);
 me->delete_temp("pxj/tiaochuang");
 me->set_temp("pxj/yueover",1);
 return 1;
}
//绑定
int do_bang(string arg)
{
	object me=this_player();
	if (!arg || arg!="千年松")
	{
		return notify_fail("你要绑什么？\n");
	}
	if (!present("sheng zi",me))
	{
		return notify_fail("你要用什么来绑？\n");

	}
	message_vision(HIC"$N将绳子一端绑在松树上，一端系在自己的腰部。\n"NOR,me);
	me->set_temp("pxj/bang",1);
	return 1;
}

int do_gou(string arg)
{
	int i,j,s;
	object ob,me;
	me=this_player();
   // i=random(10);
	i=random(me->query("kar"));
	//ob=new("/d/fuzhou/obj/kuihua.c");
	if (time()-me->query("quest/pxj/super2/time")<86400)
	{
		return notify_fail("你太勤快了耶！\n");
	}

    if (me->query("quest/pxj/super2/pass"))
	{
		return notify_fail("你已经解开了辟邪剑法高级篇,无需这么折腾了！\n");
	}

	if (!arg||arg!="袈裟")
	{
		return notify_fail("你乱伸脚要去够什么,表演杂技么？\n");

	}	

	if (!me->query_temp("pxj/yueover"))
	{
		return notify_fail("山崖下如此危险，你乱伸脚要做什么,表演杂技么？\n");
	}
  
	if (me->query("kar")>30)
	{
		log_file("quest/bugzuobi",sprintf("%s(%s)在解密华山后悬崖辟邪剑高级篇分支过程中作弊嫌疑。富源：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("quest/pxj/super2/fail"),me->query("combat_exp"),me));
		return 1;
	}
    message_vision(HIY"\n\n\n$N眼看那袈裟从身旁飘过，心中着急伸手一抓，差了数尺，没能抓到。这辟邪剑法能否得到就开是否抓到这袈裟了。\n"
    +"$N全将个人生死置之度外，右手搭在崖上的松树枝，左脚拚命向外一勾。\n"NOR,me);
   
   if ((int)me->query_encumbrance() * 100 / (int)me->query_max_encumbrance() >= 50) 
   {
       message_vision(HIC"\n$N借助绳子向峭壁爬了上去，因为身上负重过多，突然$N脚下一滑，摔了下来。\n"NOR, me);
		me->move("/d/huashan/v-road-1.c");
		me->set("qi",0);
		me->unconcious();
	
		if (me->query("kar")<10) {
			me->die();
			me->set_temp("last_damage_from","从山崖山摔下而");
		}
		return 1;
	}

  
//不绑绳子就死，，，嘿嘿
   if (!me->query_temp("pxj/bang"))
   {
	   message_vision(HIR"$N一不小心，心中贪念发作，动作过大，失手摔落山崖，向下落去！！！！！！！！！！！\n"NOR,me);
	   call_out("do_wait1",2,me);
       return 1;
    }
	
	

	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	s=random(j);
    
	if (me->query("kar")<31
		&& i>26
		&& random(me->query("int"))>35
		&& s<2)
	{
       message_vision(HIG"\n\n$N只觉脚尖似乎碰到了袈裟，立即缩将回来，当真幸运得紧，竟将那袈裟勾到了，没落入万仞深渊中。\n"NOR,me);
	   message_vision(HIR"\n\n恭喜你，机缘巧合之下，得到辟邪剑法进阶篇。\n"NOR,me);
	  
	   ob=unew("d/fuzhou/obj/kuihua");
	   if (ob)
	   {
		   
			message_vision("$N轻轻地用脚勾住袈裟，小心翼翼的塞入怀中。\n", me);
			ob->set("reader", me->query("id"));
			ob->move(me);
		}
		else {
			message_vision("$N小心谨慎地挪动袈裟，忽然间袈裟被风一吹，瞬间飘落山崖。\n", me);

		}
	   me->set("quest/pxj/super2/pass",1);	  
	  // ob->move(me);
	   me->set("title",HIM"群邪辟易"NOR);
	   me->set("mytitle/quest/pxjtitle",HIM"群邪辟易"NOR);
	   message("channel:rumor", HIM"【谣言】"+me->query("name")+"机缘巧合之下，获得一件神秘袈裟！\n"NOR, users());
	   log_file("quest/pxjf2", sprintf("%s(%s) 成功！第%d次努力，机缘巧合下，成功获得辟邪剑法进阶篇，当前幸运值i：%d,当前随机值s：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/pxj/super2/fail"),
		 i,
		 s,
         me->query("combat_exp")));	
	   
	   
	}
	else
	{
		message_vision(HIY"\n\n$N虽然努力伸出一脚，但一阵狂风忽然间吹过，将这件袈裟吹向万丈深渊。\n"NOR,me);
	    log_file("quest/pxjf2", sprintf("%s(%s) 辟邪剑法进阶篇失败%d次，当前幸运值i：%d,当前随机值s：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/pxj/super2/fail"),
		 i,
		 s,
         me->query("combat_exp")));
		
		me->add("quest/pxj/super2/fail",1);
		me->set("quest/pxj/super2/time",time());		
	    //destruct(ob);       
	} 
	me->move("/d/huashan/v-road-1.c");
	me->delete_temp("hspxj");
	me->delete_temp("pxj");
	message_vision(HIY"\n\n$N借助绳子的作用，几个起落间下到崖底，想起方才的惊险，不禁有些后怕。\n"NOR,me);
	return 1; 
   
}

int do_wait1(object me)
{
   message_vision(HIY"只见山风呼啸而过，身体不受自己控制，急速下落，你吓的肝胆俱裂！\n"
	                 +"/         /        /       /        /              /\n"
                     +"\         \        \       \        \              /\n"
					 +"/         /        /       /        /              /\n"
					 +"/         /        /       /        /              /\n"
                     +"\         \        \       \        \              /\n"
					 +"/         /        /       /        /              /\n"
					 +HIC"\n\n\         \        \       \        \              /\n"
					 +"/         /        /       /        /              /\n"
					 +"\         \        \       \        \              /\n"
					 +"/         /        /       /        /              /\n"
					   +"/         /        /       /        /              /\n"
                     +"\         \        \       \        \              /\n"
					 +"/         /        /       /        /              /\n"
					 +"\         \        \       \        \              /\n"NOR
					 +HIR"\n\n\n\n\         \        \       \        \              /\n"
					 +"\         \        \       \        \              /\n"
					 +"\         \        \       \        \              /\n"
					   +"/         /        /       /        /              /\n"
                     +"\         \        \       \        \              /\n"
					 +"/         /        /       /        /              /\n"
					 +"\         \        \       \        \              /\n"NOR,me);
     
	 me->set_temp("last_damage_from","掉下山崖摔");
	 me->die();	 
     return 1;

}
int do_climb(string arg)
{
	object me=this_player();

	if (!arg||arg!="up")
	{
		return notify_fail("你要往那儿爬？\n");
	}
	if (!me->query_temp("pxj/bang"))
	{
		call_out("do_wait1",1,me);
		return 1;
	}
	if (arg=="up")
	{
		message_vision(HIY"$N紧了紧系在腰间的绳子，双手反复攀爬，借助绳子的力量终于爬上了山崖。\n"NOR,me);
		me->move("d/huashan/qinshi");
		message_vision(HIC"窗外山风呼啸，$N想起方才的情景，不禁有些后怕。\n"NOR,me);
		return 1;
	}

}