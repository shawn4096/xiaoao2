
#include <ansi.h>
inherit ROOM;
//#include "/d/thd/niujia/npc/sdyxz.h";
#define QUESTDIR "quest/射雕英雄传/"
#define QUESTDIR1 "quest/射雕英雄传/风雪惊变/"

int do_move(string);
int do_turn(string);
int story_1(object me);
int do_jiaoliang(object me);
int confirm(object me);
int yg_come(object me);
void create()
{
	set("short", "小酒店");
	set("long", @LONG
这是一家已经废弃了的小酒店，柜台上积满了灰，一个角落里堆着一大堆
干草，旁边斜躺着一个大铁叉；柜台后的橱架上凌乱地放着几摞破旧的青花瓷
碗(wan)。在门前坐着一个梳着朝天辫的小姑娘。
LONG
	);

	set("item_desc", ([
		"wan" : "一堆很凌乱地散放着的碗。\n",
		"bowl" : "一堆很凌乱地散放着的碗。\n",
		"tiewan" : "一只奇怪的碗，好象是固定在了架子上。\n",
		"ironbowl" : "一只奇怪的碗，好象是固定在了架子上。\n",
	]) );

	set("exits", ([
		"north" : __DIR__"njroad1.c",
	]));

	set("objects", ([
		__DIR__"npc/shagu.c":1,
		__DIR__"npc/qusan.c":1,
		"/d/baituo/npc/ouyangke.c":1,
	]));

	setup();
}

void init()
{
	object me,nv1,nv2,ke;
	me=this_player();
	add_action("do_move","move");
	add_action("do_move","yi");
	add_action("do_turn","turn");
	add_action("do_turn","zhuan");
	add_action("do_jiaoliang","jiaoliang");
	
	if (me->query_temp("slbw/story1"))
	{
	   if (!present("ouyang ke",this_object()))
	   {
		   ke=new("/d/baituo/npc/ouyangke.c");
	       ke->move("/d/thd/niujia/xiaodian");
		   ke->set("jiali",50);
		   ke->set("str",20);
	   }
	  if (!objectp(nv1=present("shao nv",this_object())))
	  {
		   nv1=new("/d/baituo/npc/baiyishaonv");
		   nv1->move("/d/thd/niujia/xiaodian");
	   }
	 
	   //nv2=new("/d/baituo/npc/baiyishaonv");
	   //nv2->move("/d/thd/niujia/xiaodian");
	   message_vision(HIC"欧阳克冷笑两声，抬头向着屋外说道：“这是那位朋友，既蒙枉顾，何不进来相见？\n"NOR,me);
	   
	   call_out("story_1",3,me);

	}
	//调用杨郭来的程序
	if (me->query_temp(QUESTDIR1+"askguo") 
		&& me->query(QUESTDIR+"start")
		&& me->query_temp(QUESTDIR1+"start"))
	{
		
		message_vision(CYN"$N闪身进入了这家小酒馆，向四周大量一下，只有一张桌子和四张长凳，一旁的酒店老板曲三正在忙碌着。\n"NOR,me);
		message_vision(CYN"$N在桌子上座下来，对曲三说道，“店家，来几壶上好的米酒”。\n"NOR,me);

		call_out("yg_come",3+random(4),me);
		me->delete_temp(QUESTDIR1+"start");
		me->delete_temp(QUESTDIR1+"askyang");
		me->delete_temp(QUESTDIR1+"askguo");
		//me->set_temp(QUESTDIR1+"");
		return ;
	}
}

int do_move(string arg)
{
	object me = this_player();

	if (me->is_busy() || me->is_fighting())	return notify_fail("你正忙着呢！\n");
	if (arg == "wan" || arg == "bowl") {
		write("你将架子上的碗使劲地摔到地上去，却发现有一只碗竟然拿不起来。仔细一看，才发现这是一只铁碗(tiewan)！\n");
		me->set_temp("mishi_temp",1);
		return 1;
	}
	return notify_fail("你要搬动什么？\n");
}

int do_turn(string arg)
{
	int temp;
	object me = this_player();

	if (me->is_busy() || me->is_fighting())	return notify_fail("你正忙着呢！\n");
	if (arg == "tiewan left" || arg == "tiewan zuo") {
		temp = me->query_temp("mishi_temp");
		if (!temp) return 0;
		if (temp < 4) temp++;
		else temp = 1;
		write("你将铁碗用劲地向左扳动，发出了“咯吱”的声音。\n");
		me->set_temp("mishi_temp",temp);
		return 1;
	}
	if (arg == "tiewan right" || arg == "tiewan you") {
		temp = me->query_temp("mishi_temp");
		if (!temp) return 0;
		if (temp > 3) temp++;
		else temp = 1;
		write("你将铁碗用劲地向右扳动，发出了“咯吱”的声音。\n");
		if (temp == 7) {
			write("只听“喀啦”一声巨响，你的眼前出现了一道门。你毫不犹豫的走了进去。\n");
			message("vision", "橱架后面忽然现出一道暗门，" + me->name() + "举步走了进去，橱架吱呀呀地又关上了。\n", this_object(), me);
			me->delete_temp("mishi_temp");
			me->move(__DIR__"mishi");
			message("vision", me->name() + "打开暗门，走了进来。\n", environment(me), me);
		}
		else me->set_temp("mishi_temp",temp);
		return 1;
	}
	return notify_fail("你要做什么？\n");
}

int story_1(object me)
{
   object li,ke;
   if (!objectp(li=present("li sheng",environment(me))))
   {
	    li=new("/kungfu/class/gaibang/lisheng.c");
        li->move("/d/thd/niujia/xiaodian");
   }
   else
	   li=present("li sheng",environment(me));
   message_vision(HIW"隐在墙头屋角的$N知道已被他察觉，欧阳克侧头向地下的布袋看了一眼，冷笑道：“想不到美人儿的大驾这么容易请到“\n"
   +HIC"\n欧阳克缓步上前，折扇轻挥，已折成一条铁笔模样。$N见了他的手势和脸色，吃了一惊，知他已看破布袋中藏着敌人，便要痛下毒手。匆忙中将\n"
   +"手中扣了三枚钢针，只待他折扇下落，立刻发针相救黎生。忽听得飕飕两声，窗格中打进两枝袖箭，疾向欧阳克背心飞去，原来丐帮中人\n"
   +"也已看出情势凶险，先动上了手。\n"
   +HIB"\n\n\n欧阳克翻过左手，食指与中指夹住一箭，无名指与小指夹住另一箭，喀喀两响，两枝短箭折成了四截。群丐见他如此功夫，无不骇然。余兆兴叫道：“\n"
   +"黎师叔，出来罢。”语声未毕，嗤的一声急响，布袋已然撕开，两柄飞刀激射而出，刀光中黎生着地滚出，扯着布袋一抖，护在身前，随即跃起。\n"NOR,me);
  
   ke=present("ouyang ke",environment(me));
   if (!objectp(ke))
     return 0;
   li->kill_ob(ke);
   me->delete_temp("slbw/story1");
   me->set_temp("slbw/keli",1);
   return 1;  

}

int do_jiaoliang(object me)
{
	object ke;
	me=this_player();
	if (objectp(present("hong qigong",environment(me))))
	 return notify_fail("洪七公已经在场，还用的着你来跟欧阳克较量？\n");
	ke=present("ouyang ke",environment(me));
	if(file_name(environment(me))!="/d/thd/niujia/xiaodian" ) 
         return 1;
	if (!objectp(ke))
	   return 0;
	//ke->add_temp("apply/damage",-50);
    //ke->add_temp("apply/attack",-150);
	
	if (me->query("quest/gb/xlz/slbw/pass"))
	    return notify_fail("你今天已经解开，不要费劲了。\n");
	if (time()-me->query("quest/gb/xlz/slbw/time")<86400)
	    return notify_fail("你今天已经解密一次，请24小时再来。\n");
	if (ke->is_busy())
	   return notify_fail("欧阳克正在忙碌，等他不忙了才能理你？\n");
	if (!me->query_temp("slbw/keli"))
	   return notify_fail("欧阳克和黎生没有战斗过，你是从哪儿来的？\n");   
	
	if (me->query_skill_mapped("strike")!="xianglong-zhang"||me->query_skill_prepared("strike")!="xianglong-zhang")
	  return notify_fail("你没有激发降龙掌，如何和欧阳克较量！\n");   
	
	if (objectp(ke)&&me->query_temp("slbw/keli"))
	{
		ke->kill_ob(me);
		message_vision(HIY"$N喝道，‘欧阳克你这淫贼，可敢与我较量一番？’说完运使降龙十八掌的招式就和欧阳克斗在一起。\n",me);
        message_vision(HIB"欧阳克冷笑道，‘就凭你那几下三脚猫的功夫，也敢跟我斗？今天我就让你见识见识西域武学的真正厉害。\n",me);
		message_vision(HIG"$N转眼间两人拆了四十余招，$N已把十五掌招数反复使用了几遍，足够自保，但欧阳克武功实高出\n"
		+"他甚多，要想取胜，却也不能。再斗十余招，欧阳克拳法斗变，前窜后跃，声东击西，身法迅捷之极。\n",me);
	     		  
		  //me->set_temp("slbw/fightke",1);
          remove_call_out("confirm");
	      call_out("confirm", 20, me);
		  message_vision(HIB"\n\n\n欧阳克正在激斗之中，忽然间一物向自己飞来。大惊之下，立时跃开，喝道：“鼠辈暗算公子爷，有种的光明正大出来……”\n"
		                   +"语音未毕，突听得头顶风声微响，想要闪避，但那物来得好快，不知怎样，口中忽然多了一物，舌头上觉得有些鲜味，\n"
						   +"欧阳克又惊又恐，慌忙吐出，似是一块鸡骨。欧阳克惊惶中抬头察看，只见梁上一把灰尘当头罩落，忙向旁跃开，噗的一声，口\n"
						   +"中又多了一块鸡骨。这次却是一块鸡腿骨，只撞得牙齿隐隐生疼。\n"NOR,me);
        	
		return 1;
	}

}

int confirm(object me)
{
   
    object ob,hong,li,nv;
	int i,j,t;
	
	ob=present("ouyang ke",environment(me));
	li=present("li sheng",environment(me));
	nv=present("shao nv",environment(me));
	//girl1
	//if (!me->query_temp("slbw/fightke"))
	  // return notify_fail("你没有听到洪七公的教诲，打败欧阳克，老叫化对你很失望！\n");   
	if (!objectp(hong=present("hong qigong",environment(me))))
	{
	  hong=new("kungfu/class/gaibang/h7g.c");
	  hong->move(environment(me));
	 }
	//else hong=present("hong qigong",environment(me));
	
	message_vision(CYN"\n\n一道青影从梁上飘然而落，淡淡道：“我要真是指点$N几招捉蛇的招式，难道收拾不了$n你这个小笨蛋?\n"NOR, me,ob);
	message_vision(HIG"\n\n$N只听得洪七公在自己耳边轻声给自己讲解降龙十八掌最后三招的奥妙，一招是‘履霜冰至’，还有‘飞龙在天’，最后是‘神龙摆尾’。\n"
			+"这些招式一一教给了$N，最后只听洪七公说道，先把这小子打败再说。\n"NOR,me);
	//i=random(15);
	j=random(me->query("kar"));
	t = 20;
    if(me->query("m-card-vip")) t =  18;
    if(me->query("y-card-vip")) t =  15;
    if(me->query("buyvip"))     t =  10;
	i= random(t);
	
	if (me->query("kar")<31
		&&j>26
		&&i<3)
	{
       message_vision(HIC"\n\n$N终于将降龙掌最后三招学全，融会贯通，威力大增，$n招架不住，飞身向外逃去。洪七公随之也轻叹一声悄然离去。\n"NOR,me,ob);
	   message("channel:rumor", HIM"【谣言】某人："+me->query("name")+"机缘巧合，学全降龙十八掌，降龙掌达到了运用自如的境界！\n"NOR, users());
	   message("channel:chat", HIC"【聊天】洪七公："+me->query("name")+"乃是我北丐终于收到了一位得意弟子，还请各位江湖大佬以后多多眷顾。！\n"NOR, users());
	   message("channel:chat", HIC"【聊天】洪七公：丐帮降龙十八掌乃是武林中最霸道的掌法。！\n"NOR, users());
	   message("channel:chat", HIC"【聊天】洪七公：东邪、西毒、南帝、北丐、中神通乃是武林五绝。乖徒儿你千万不能弱了我大丐帮的威风！\n"NOR, users());
		if (objectp(ob))
			destruct(ob);
	    if (objectp(hong))
			destruct(hong);	
		if (objectp(li))
			destruct(li);
		if (objectp(nv))
			destruct(nv);
	   //me->add("combat_exp",15000);
	   log_file("quest/xlzslbw",sprintf("%s(%s) 在和欧阳克战斗后，得到洪七公的亲自指点，打跑欧阳克。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/slbw/fail"),me->query("combat_exp"),me));
	   me->set("title",HIC"北丐"HIR"降龙十八掌传人"NOR);
	   me->set("quest/gb/xlz/slbw/pass",1);
	   me->delete_temp("slbw/keli");
	   return 1;
	}
	else
	{
		message_vision(HIY"\n\n$N虽然听洪七公说了明白了这三招，但对于如何使用的劲力法门一时之间却是难以理解。降龙十八掌的\n"
		+"威力并没有发挥出来，看来你还是有待于重新跟洪七公学习了。洪七公见你如此驽钝，随之也轻叹一声悄然离去。\n"NOR,me,ob);
		log_file("quest/xlzslbw",sprintf("%8s%-10s在和欧阳克战斗后，得到洪七公的亲自指点，但并没有成功，尚须努力。富源：%d。随机数：%d。失败：%d。经验值：%d。\n",
			me->name(1), me->query("id"),j,i,me->query("xlz/slbw/fail"),me->query("combat_exp"),me));
		message("channel:chat", HIC"【聊天】洪七公长叹一声，似乎对"+me->query("name")+"甚是失望。！\n"NOR, users());
		me->add("quest/gb/xlz/slbw/fail",1);
		me->set("quest/gb/xlz/slbw/time",time());
		me->delete_temp("slbw/keli"); 	
		if (objectp(ob))
			destruct(ob);
	    if (objectp(hong))
			destruct(hong);	
		if (objectp(li))
			destruct(li);
		if (objectp(nv))
			destruct(nv);
        return 1;
	}     
     return 1;
}


//射雕英雄传情节
//杨铁心和郭啸天进入小店
int yg_come(object me)
{
	object yang,guo;
	message_vision(HIW"\n\n外面大雪纷飞，天寒地冻，你忍不住打了个哆嗦，正在四处打量之际。\n"NOR,me);
	message_vision(HIY"不多会，忽听外面两个爽朗的声音传来，郭大哥，来，一起喝酒！\n"NOR,me);
	if (!objectp(yang=present("yang tiexin",this_object())))
	{
		yang=new("d/thd/niujia/npc/yang");
		yang->move("d/thd/niujia/xiaodian");
	}
	if (!objectp(yang=present("guo xiaotian",this_object())))
	{
		yang=new("d/thd/niujia/npc/guo");
		yang->move("d/thd/niujia/xiaodian");
	}
	me->set_temp(QUESTDIR1+"ygcome",1);
	add_action("do_hejiu","hejiu");

}
int do_hejiu()
{
	object me,yang,guo;
	me=this_player();
	
	if (!objectp(yang=present("yang tiexin",this_object())))
	{
		return notify_fail("杨铁心不在此地，故事无法继续，请从头再来！\n");
	}
	if (!objectp(guo=present("guo xiaotian",this_object())))
	{
		return notify_fail("郭啸天不在此地，故事无法继续，请从头再来！\n");
	}
	if (me->query_temp(QUESTDIR1+"hejiu"))
	{
		return notify_fail("你和杨铁心郭啸天方才不是一起喝过酒！？\n");
	}
	message_vision(HIC"$N端起酒杯对杨铁心和郭啸天说道，“今日在此小酒店中偶遇二位英雄，实乃是在下荣幸至极”！\n"NOR,me);
	message_vision(HIC"$N说道，“天寒地冻，我敬二位一杯”！\n"NOR,me);
	message_vision(HIY"这时杨铁心忽然说道，“郭大哥你看，前面那个道人武功不俗”！\n"NOR,me);
	message_vision(HIC"$n说道，“这世道比较乱，也不知道他是好人还是坏人，我远观此人面带杀气，还是小心为妙”！\n"NOR,me,guo);/**/
	tell_object(me,HIY"杨铁心说道，“要是坏蛋，难道我们还怕了他不成？”！\n"NOR);
	
	me->set_temp(QUESTDIR1+"hejiu",1);
	me->set(QUESTDIR1+"hejiu",1);
	call_out("qiu_come",3+random(2),me);
	return 1;
}

int qiu_come(object me)
{
	object qiu,yang,guo,bing;
	if (!objectp(yang=present("yang tiexin",this_object())))
	{
		return notify_fail("杨铁心不在此地，故事无法继续，请从头再来！\n");
	}
	if (!objectp(guo=present("guo xiaotian",this_object())))
	{
		return notify_fail("郭啸天不在此地，故事无法继续，请从头再来！\n");
	}	
	if (!objectp(qiu=present("qiu chuji",this_object())))
	{
		qiu=new("d/thd/niujia/npc/qiuchuji");
		qiu->move("d/thd/niujia/xiaodian");
	}
	if (!objectp(bing=present("jin bing",this_object())))
	{
		bing=new("d/thd/niujia/npc/jinbing");
		bing->move("d/thd/niujia/xiaodian");
	}
	qiu->kill_ob(bing);
	bing->kill_ob(qiu);
	me->delete_temp(QUESTDIR1+"ygcome");

	message_vision(WHT"\n\n$N向远处一看，狂风呼啸之间，远远来了一个道人！\n"NOR,me);
	message_vision(WHT"\n\n$N那道人正在和一名黑衣人斗战！\n"NOR,me);

	message_vision(HIC"$n说道，“还真是一位高手，你看他行走之际，地上只留下浅浅的一层脚印，这难道是传说中的踏雪无痕”？\n"NOR,me,guo);
	message_vision(HIC"$n对那个道人说道，“天寒地冻，这位道长可否一起喝一杯”？\n"NOR,me,yang);
	message_vision(HIC"哪里料想，这道人也是爽快之人，当即将手中的包裹往桌子上一放，面带杀气道，“喝就喝，难道我还怕了你们人多不成？”\n"NOR,me,yang);
	add_action("do_check","chakan");
	add_action("do_check","check");
	return 1;
}
int do_check(string arg)
{
	object me,yang,guo,qiu;
	me=this_player();
	if (!arg||arg!="包裹") return notify_fail("你要查看什么？\n");
	
	if (!me->query_temp(QUESTDIR1+"hejiu"))
	{
		return notify_fail("你没有一起喝过酒，彼此都不熟悉，乱翻别人包裹很不礼貌！\n");
	}

	if (me->query_temp(QUESTDIR1+"chakan"))
	{
		return notify_fail("你已经查看过一次报过了，乱翻别人包裹很不礼貌！\n");
	}
	if (!objectp(yang=present("yang tiexin",this_object())))
	{
		return notify_fail("杨铁心不在此地，故事无法继续，请从头再来！\n");
	}
	if (!objectp(guo=present("guo xiaotian",this_object())))
	{
		return notify_fail("郭啸天不在此地，故事无法继续，请从头再来！\n");
	}
	if (!objectp(qiu=present("qiu chuji",this_object())))
	{
		return notify_fail("丘处机不在此地，故事无法继续，请从头再来！\n");
	}
	if (qiu->is_fighting())
	{
		return notify_fail("丘处机正在战斗，还没有把手中包裹放下来！你无法查看其包裹！\n");
	}
	message_vision(HIR"\n\n$N见那个道人仍在桌子上的包裹甚是好奇，仔细一看，好像是一个人头，外面正渗出丝丝殷红血迹！\n"NOR,me);
	message_vision(HIC"杨铁心和郭啸天也发现这个包裹的异常，对那个道人喝道，“道长包裹中是什么东西”？\n"NOR,me);
	message_vision(HIG"$n对那个道人说道，“哼，果然是一丘之貉，奸贼，纳命来吧！”？\n"NOR,me,yang);
	
	qiu->fight_ob(yang);
	qiu->fight_ob(guo);
	qiu->hit_ob(me);
	//查看包裹
	me->set_temp(QUESTDIR1+"chakan",1);


	call_out("do_fight1",10+random(3),me);
	return 1;
}

int do_fight1(object me)
{
	message_vision(HIG"\n\n丘处机忽然喝道，“停！”，然后对杨铁心说道，“你所使用的是杨家枪法，难道是杨家后人不成？”\n"NOR,me);
	message_vision(CYN"杨铁心眼见是一场误会，急忙介绍道，“在下坐不改名，行不改姓，我乃是岳元帅账下大将杨再兴后人杨铁心是也”\n"NOR,me);
	message_vision(CYN"杨铁心然后指了指郭啸天绍道，“这位是我结义兄弟，梁山好汉郭胜后人郭啸天，乃是在下大哥”\n"NOR,me);
	message_vision(CYN"杨铁心问道，“看道长乃是全真剑法的套路，为何做如此杀人越货的勾当？”\n"NOR,me);
	message_vision(MAG"丘处机恍然大悟，知道此事存在重大误会，于是解释道，“此人乃是金国间隙，被我一路追杀至此，他还有个同伙，已经被我所伤，追踪至此？”\n"NOR,me);
	message_vision(HIG"众人恍然大悟，知道是一场误会，方才的交手，不由地彼此间惺惺相惜，又开始喝起酒来！\n"NOR,me);
	//qiu->remove_enemy();
	call_out("go_home",4+random(3),me);
}
int go_home(object me)
{
	object yang,guo,qiu;
	if (!me) return 0;

	message_vision(HIY"\n\n酒过三巡，菜过五味，彼此间英雄惜英雄\n在杨铁心和郭啸天的盛情邀请下，决定到杨铁心家中继续喝酒！\n"NOR,me);
	me->set_temp(QUESTDIR1+"xiangzhi",1);
	me->set(QUESTDIR+"xiangzhi",1);
	
	if (objectp(yang=present("yang tiexin",this_object())))
		destruct(yang);
	if (objectp(guo=present("guo xiaotian",this_object())))
		destruct(guo);
	if (objectp(qiu=present("qiu chuji",this_object())))
		destruct(qiu);
	
	return 1;
}