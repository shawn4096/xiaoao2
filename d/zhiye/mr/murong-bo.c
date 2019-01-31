// /u/leontt/npc/murong-bo.c  慕容博
// by leontt 1/5/2000
#include "murong-bo.h"

inherit NPC;
inherit F_MASTER;
#include <ansi.h>
string ask_blade();
string ask_armor();
string ask_me();
string ask_me1();
int ask_douzhuan();
int ask_canhezhi();
string *kill_name=({"张三丰","张无忌","枯荣长老","玄慈大师","穆人清","灭绝师太","洪七公",});
void create()
{
        object weapon,armor;
        set_name("慕容博",({"murong bo","murong","bo"}));
        set("title","姑苏慕容老爷子");
        set("nick","以彼之道 还施彼身");
        set("long",
              "他就是天下号称以彼之道，还彼之身的姑苏慕容博。\n"
              "他脸上带着不可一世的笑容。\n");
        set("age", 57);
        set("attitude", "friendly");
        set("no_bark",1);
        set("shen_type", -1);

        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 27);

        set("max_qi", 39500);
        set("max_jing", 7500);
        set("neili", 39500);
        set("max_neili", 39500);
        set("eff_jingli", 7000);
        set("jiali", 220);
        set("combat_exp", 14000000);
        set("score", 30000);
        set("chat_chance_combat", 80);

        set("chat_msg_combat", ({
                (: perform_action, "blade.daoying" :),
				(: perform_action, "blade.liandao" :),
                (: perform_action, "strike.riyue" :),
			    (: perform_action, "parry.bishen" :),
				(: exert_function, "shenyuan" :),
		}));

        set_skill("xingyi-zhang", 500);
        set_skill("strike", 500);
        set_skill("finger", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("canhe-zhi", 500);
        set_skill("murong-jianfa",500);
        set_skill("shenyuan-gong", 500);
        set_skill("yanling-shenfa", 500);
        set_skill("douzhuan-xingyi", 500);
        set_skill("parry", 500);
        set_skill("sword", 500);
        set_skill("literate", 300);
        set_skill("murong-daofa", 500);
        set_skill("blade",500);
        set_skill("xingyi-jianzhen",500);

        map_skill("blade", "murong-daofa");
        map_skill("finger", "canhe-zhi");
        map_skill("force", "shenyuan-gong");
        map_skill("dodge", "yanling-shenfa");
        map_skill("parry", "douzhuan-xingyi");
        map_skill("sword", "murong-jianfa");
        map_skill("strike", "xingyi-zhang");

        prepare_skill("strike","xingyi-zhang");

        create_family("姑苏慕容",1,"弟子");

        set("inquiry",  ([
		"name" : "我就是以彼之道，还施彼身的姑苏慕容博。\n",
		"here" : "这里是少林寺的藏经楼。\n",
		"rumors" : "我那复儿在武林之中闯出了名头，老爷子我是真高兴呀！\n",
		"宝刀" : (: ask_blade :),
		"绿波香露刀" : (: ask_blade :),
		"龙袍" : (: ask_armor :),
		"心愿" : (: ask_me :),
		"无名老僧" : "他老人家无论武功还是禅宗修为都已到达身不可测的境界,但是最近偶尔也和我提起一些心愿.\n",
		"经书" : (: ask_me1 :),
		"斗转星移绝学" : (: ask_douzhuan :),
		"参合指绝学" : (: ask_canhezhi :),
	]));

        set_temp("apply/damage", 50);
        set_temp("apply/dodge", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/armor", 40);

        setup();
        if (clonep()){
                weapon = unew(BINGQI_D("blade/lvbo-dao"));
                if(!weapon) weapon=new(BINGQI_D("blade"));
                weapon->move(this_object());
                weapon->wield();

                armor=unew("/clone/armor/longpao");
                if( ! armor) armor = new(ARMOR_D("cloth"));
                armor->move(this_object());
                armor->wear();
        }
        add_money("gold", 1);
}

void attempt_apprentice(object ob)
{
	object me  = this_player();

	string name, new_name;
	name = ob->query("name");

	if (present("jiaxin", me)) {
		if (me->query_skill("douzhuan-xingyi",1)<400)
		{
			command("say 你的斗转星移如此之差，居然连400都不到，赶紧先回去修炼去！\n");
			return ;
		}
		destruct(present("jiaxin",me));
		command("say 好吧，既然" + RANK_D->query_respect(ob) + "有我儿的信件，难为你" +
			"如此辛苦跑来，我就收下你吧。");

		new_name = "慕容" + name[<4..<1];
		ob->set("name", new_name);
		command("say 从今以后你就叫做" + new_name + "，希望你能把慕容功夫发扬光大！");
		command("recruit " + ob->parse_command_id_list()[0]);
		command("chat* 淡淡一笑，谁言 以彼之道 还施彼身 绝迹江湖！");
		command("chat* haha");
	}
	else
		command("say 我慕容博岂能随便收徒!");
	return;
}

void reset()
{
	object ob;

	if (clonep() && (ob = unew(BINGQI_D("blade/lvbo-dao")))) {
		ob->move(this_object());
		command("wield lvboxianglu dao");
	}
	if (clonep() && (ob = unew(ARMOR_D("longpao")))) {
		ob->move(this_object());
		command("wear long pao");
	}
}

string ask_blade()
{
	object blade;
	object me, ob;
	mapping fam;

	me = this_player();
	ob = this_object();

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "姑苏慕容")
		return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";

	if (this_player()->query("combat_exp") < 150000)
		return RANK_D->query_respect(this_player())+"看来功力不够，恐怕不能保住这把宝刀。";

	if ( present("lvboxianglu dao", this_player()))
		return RANK_D->query_respect(this_player()) +
			"绿波香露刀只有一把，而且就在你身上，真是贪得无厌！";

	if ( present("lvboxianglu dao", this_object())) {
		command("give lvboxianglu dao to "+this_player()->query("id"));
		blade = unew(BINGQI_D("blade"));
		if(clonep(blade)){
			blade->move(this_object());
			command("wield dao");
		}
		else{
			blade = unew(BINGQI_D("blade"));
			blade->move(this_object());
			command("wield dao");
		}
		return "望你能为我慕容做出些惊天地、泣鬼神的壮举，才不负我对你的一片期望，这把绿波香露刀就送给你吧！";
	}
	return "抱歉，你来晚了，我的绿波香露刀已给别人取走了。";
}
string ask_armor()
{
        object armor;
        object me, ob;
        mapping fam;

        me = this_player();
        ob = this_object();

        if (!(fam = this_player()->query("family")) || fam["family_name"] != "姑苏慕容")
		return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";
        if (this_player()->query("combat_exp") < 150000)
		return RANK_D->query_respect(this_player())+"看来功力不够，恐怕不能保住这见龙袍。";
        if ( present("longpao", this_player()))
		return RANK_D->query_respect(this_player()) +
                "龙袍只有一件，而且就在你身上，真是贪得无厌！";
        if ( present("longpao", this_object())) {
        	command("give longpao to "+this_player()->query("id"));
		if(clonep(armor)){
			armor = unew(ARMOR_D("cloth"));
			armor->move(this_object());
			command("wear cloth");
		}
		else{
			armor = unew(ARMOR_D("cloth"));
			armor->move(this_object());
			command("wear cloth");
		}
		return "望你能为我慕容做出些惊天地、泣鬼神的壮举，才不负我对你的一片期望，这件龙袍就送给你吧！";
	}
	return "抱歉，你来晚了，我的龙袍已给别人取走了。";
}

string ask_me()
{
        object me = this_player();

	mapping my_fam  = me->query("family");

	if (my_fam["generation"] == 35)
		return RANK_D->query_respect(this_player())+ "都找过回来了,难道没事拿大爷我来消遣!";

	if (!(my_fam) || my_fam["family_name"] != "少林派" || my_fam["generation"] != 36
	 || (string)me->query("class")!="bonze" )
		return RANK_D->query_respect(this_player())+  "此事需我少林武功才智具佳之人,你不知道也罢.";

	if (me->query_temp("sl_wm1"))
		return RANK_D->query_respect(this_player()) +  "我不是和你说过了吗?你当我慕容博什麽人?";

	me->set_temp("sl_wm1",1);
	return "听师傅偶尔提到昔年他的师兄天明大师奉方丈重托去寻找一部达摩祖师手写的金刚经,\n"+
		"一去数十载渺无音信,师傅言谈中似乎有挂怀之意,我也出去打探过但是也没什麽消息。";
}

string ask_me1()
{
	object me = this_player();

        if ( file_name(environment(this_object())) != this_object()->query("startroom"))
        	return "我现在在外面，等我回去再说吧。";

	if (!present("fanwen jing", me))
		return RANK_D->query_respect(this_player()) + "身上没有经书,怎和老衲打诳语?";
	command("nod");
	tell_room(me,HIY "慕容博袍袖一摆,"+ me->name()
		+ "仿佛腾云驾雾一般飞进了里屋。\n"NOR, ({ me }));
	write(HIY"你觉得一股内劲轻轻把你托起抛进了里屋。\n"NOR);

	me->move("/d/shaolin/liwu");
	return "轻声念道,阿弥陀佛.";
}

int ask_douzhuan()
{
	object ob=this_player();
    mapping fam;
	int time;
  

    if (!(fam = this_player()->query("family")) || fam["family_name"] !="姑苏慕容"){
		command("? " + ob->query("id"));
        command("say 你与本派素无来往，不知为何有此一问？");
        return 0;
       }
	if (ob->query("quest/mr/dzxy/pass")) {
		command("? " + ob->query("id"));
		ob->set("title", HIC"斗"HIG"转"HIB"星"HIY"移"NOR);
		command("say 你不是已经明白其中的奥妙了吗？");
		return 1;
	}
	if (ob->query("sydzxy/fail") >=3 && ob->query("registered") < 3){
		command("hmm");
		command("say 你受天资所限,看来此生无望了！");
		return 1;
	}
 	if (!ob->query("mr/qinchuan"))
	{
		command("say 你非我慕容世家嫡传弟子，还的好好修炼一番，我再告诉你。");
		return 1;
	}
	time = time()-(int)ob->query("quest/mr/dzxy/time");

	if ( ob->query("quest/mr/dzxy/time") && time< 86400 ) {
		command("shake");
		command("say 你解迷时间未到,请稍后再来。");
		return 1;
	}
	if (!ob->query_temp("quest/mr/dzxy/giveguan"))
	{
		command("say 你若有心就替我把慕容世家的皇冠给我找来，否则别来烦我。\n");
		return 1;
	}
	if (!ob->query_temp("quest/mr/dzxy/givebiao"))
	{
		command("say 你若有心就替我把慕容世家的皇帝世系表给我找来，我就教你。\n");
		return 1;
	}
    if ( ob->query_skill("shenyuan-gong",1) < 450) {

		command("shake "+ ob->query("id"));
		command("say 这位"+RANK_D->query_respect(ob)+"你的斗转星移武功过于浮躁,不到大飞别来烦我，现在还不是告诉你的时候。");
		return 1;
	}
	message_vision(HIC"慕容博说道，“我慕容一脉乃大燕国后裔，先祖慕容垂、慕容龙城名震天下。靠的就是\n"+
	                   "这套独步武林的斗转星移绝技，其厉害之处不仅仅在于以彼之道还施彼身，功力高后，\n"+
		               "意念一动,敌人即可束手。可叹我慕容一脉至今未能有人完成这项伟业。”\n "NOR,ob);
	command("sigh ");
	command("shake ");
	command("consider ");
	command("say 王图霸业，终将成尘，你若真想习得这门神功，我就传授给你吧，能否领悟看你的机缘和悟性了。\n");
	ob->start_busy(999);
	remove_call_out("thinking_xingyi");
	call_out("thinking_xingyi",2,ob);
	return 1;
}

int ask_canhezhi()
{
	object ob=this_player();
    mapping fam;
	string k_name;

	int i, time;
 	(int)time = (int)time()-(int)ob->query("canhe/time");


    if (!(fam = this_player()->query("family")) || fam["family_name"] !="姑苏慕容"){
		command("? " + ob->query("id"));
        command("say 你与本派素无来往，不知为何有此一问？");
        return 0;
    }
	if (ob->query("quest/mr/canhe/pass")) {
		command("? " + ob->query("id"));
		command("say 你不是已经明白其中的奥妙了吗？");
		return 1;
	}
	if (!ob->query("mr/qinchuan"))
	{
		command("say 你非我慕容世家亲传弟子，还的好好修炼一番，我再告诉你。");
		return ;
	}
	
	if (ob->query("int")< 40) {
		command("? " + ob->query("id"));
		command("say 你的先天悟性不足40，不用再来了？");
		return 1;
	}
	if (ob->query("canhe/fail") >=3 && ob->query("registered") < 3){
		command("hmm");
		command("say 你受天资所限,看来此生无望了！");
		return 1;
	}
	if ( ob->query("canhe/time") && time < 86400 ) {
		command("shake");
		command("say 你来的也太频繁了，明显解迷时间未到,请稍后再来。");
		return 1;
	}

    if ( ob->query_skill("douzhuan-xingyi",1) < 450||ob->query_skill("canhe-zhi",1) < 450) {

		command("shake "+ ob->query("id"));
		command("say 这位"+RANK_D->query_respect(ob)+"你的斗转星移武功过于浮躁,不到大飞别来烦我，现在还不是告诉你的时候。");
		return 1;
	}
	if (!ob->query("quest/天龙八部/复兴天下篇/over"))
	{
		command("heng "+ ob->query("id"));
		command("say 这位"+RANK_D->query_respect(ob)+"我大燕以复兴为己任，历代慕容弟子无不为此奋斗终生，你都做了什么？。");
		command("whisper 这位"+RANK_D->query_respect(ob)+"你若做完了天龙八部复兴篇，并替我去杀了一个掌门我就告诉你!");
		
		return 1;
	}
	
	if (ob->query_temp("quest/mr/canhe/give_shouji")<1)
	{
		command("nod ");
		command("whisper " + ob->query("id")+" 唉！只是所谓复兴大燕国，谈何容易，而且......");
		command("look " + ob->query("id"));
		command("whisper " + ob->query("id")+" 当今，天下武林所谓正派有“六派一帮”之说，就是少林派、武当派、全真教、峨嵋派、华山派、天龙寺与丐帮。");
		command("whisper " + ob->query("id")+" 其中少林、武当人称武林泰山北斗，卧龙藏虎之辈层出不穷，无名神僧和张三丰人称不死老怪物。");
		command("whisper " + ob->query("id")+" 而丐帮乃天下第一大帮，从前任帮主萧峰，到大侠郭靖、还是神丐洪七，都是名震一方的高手。");
		command("consider");
		command("whisper " + ob->query("id")+" 近年来，张无忌掌教西域明教，大有凌驾中原武林之势，且因武当关系紧密，影响力日益加剧。");
		command("whisper " + ob->query("id")+" 西南大理，枯荣复出，六脉重现，段誉更被称为青年第一高手，挟皇室之威，隐约成为江南武林之尊。");
		command("whisper " + ob->query("id")+" 因此，要复兴天下，必须扫除这“两派一帮一教一世家”。对付丐帮少林，我已经有了一个完全之策。");
		command("whisper " + ob->query("id")+" "+ RANK_D->query_respect(ob) +"竟然立志复兴天下，你就替我先去杀几个人，以明心志！");
		k_name=kill_name[random(sizeof(kill_name))];
		if (k_name=="张无忌")
		{
			if (!ob->query_temp("quest/mr/canhe/kwuji"))
			{
				command("say 既然如此，明教最近势大，将影响我大燕复兴，你现在替我去将张无忌这小贼的人头拿来。\n");
				ob->set_temp("quest/mr/canhe/kwuji",1);
			}else command("say 方才不是已经杀了张无忌了么？再继续问！看我心情再给你分配别的任务。");
		
		}else if (k_name=="张三丰")
		{
			if (!ob->query_temp("quest/mr/canhe/ksanfeng"))
			{
				command("say 既然如此，武当最近名声鹊起，将影响我大燕复兴，你现在替我去将张三丰这邋遢道人的人头拿来。\n");
				ob->set_temp("quest/mr/canhe/ksanfeng",1);
			}else command("say 方才不是已经杀了张三丰了么？再继续问！看我心情再给你分配别的任务。");

		}else if (k_name=="灭绝师太")
		{
			if (!ob->query_temp("quest/mr/canhe/kmiejue"))
			{
				command("say 既然如此，峨眉派最近人才鼎盛，将影响我大燕复兴，你现在替我去将灭绝师太这老变态的人头拿来。\n");
				ob->set_temp("quest/mr/canhe/kmiejue",1);
			}else command("say 方才不是已经杀了灭绝师太了么？再继续问！看我心情再给你分配别的任务。");
		}else if (k_name=="枯荣长老")
		{
			if (!ob->query_temp("quest/mr/canhe/kkurong"))
			{
				command("say 既然如此，大理天龙寺的枯荣很不安分，将影响我大燕复兴，你现在替我去将枯荣长老这老秃驴的人头拿来。\n");
				ob->set_temp("quest/mr/canhe/kkurong",1);
			}else command("say 方才不是已经杀了库容长老了么？再继续问！看我心情再给你分配别的任务。");
		}else if (k_name=="穆人清")
		{
			if (!ob->query_temp("quest/mr/canhe/kmu"))
			{
				command("say 既然如此，大理天龙寺的枯荣很不安分，将影响我大燕复兴，你现在替我去将枯荣长老这老秃驴的人头拿来。\n");
				ob->set_temp("quest/mr/canhe/kmu",1);
			}else command("say 方才不是已经杀了穆人清了么？再继续问！看我心情再给你分配别的任务。");
		}else if (k_name=="洪七公")
		{
			if (!ob->query_temp("quest/mr/canhe/khong"))
			{
				command("say 既然如此，丐帮好生兴旺，将影响我大燕复兴，你现在替我去将洪七公这个老叫化的人头拿来。\n");
				ob->set_temp("quest/mr/canhe/khong",1);
			}else command("say 方才不是已经杀了洪七公了么？再继续问！看我心情再给你分配别的任务。");
		}
		else {

			command("say 老夫我年纪大了，没挺清楚，你再问一遍我听听。\n");
			command("say 这都听不懂，你再问一遍这个谜题。\n");
		}
		return 1;
	}
	
	message_vision(MAG"慕容博似乎陷入一种往事回忆之中，你抬头看他时，只见他的眼眸中一会杀气腾腾，一会迷茫。\n"NOR,ob);
    message_vision(HIY"慕容博缓缓说道，“姑苏慕容氏的家传武功神奇精奥，举世无匹，只不过你没学到家而已，\n"+
		"难道当真就不及大理国段氏的“六脉神剑”了？瞧仔细了！”伸出食指，凌虚点了三下。\n"NOR,ob);
	remove_call_out("thinking_canhe");
	call_out("thinking_canhe",2,ob);
	ob->start_busy(999);
	return 1;
	
}


int thinking_canhe(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("canwu_canhe")<(10+random(10)))
  { 
	  me->add_temp("canwu_canhe",1);
      if(random(2)) tell_object(me,HIG"\n你认真回想着刚才慕容博所展示的一招一式...\n"NOR);
             else tell_object(me,HIY"\n突然间，你似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking_canhe");
	  call_out("thinking_canhe",3+random(3), me);
   }
   else
   {  
	 
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  20;
      if(me->query("y-card-vip")) j =  17;
      if(me->query("buyvip"))     j =  15;
	  i= random(j);
 
	  if (random(me->query("kar"))>27 
			&& random(me->query("int")) >=40 
			&& me->query("kar") <31
			&& i==1)
		{
			command("look " + me->query("id"));
			command("nod " + me->query("id"));
			command("chat* pat" + me->query("id"));
			command("say 好吧,我就将姑苏慕容参合指绝技的终极奥妙告诉你吧。");
			command("chat 纵声长笑道：我姑苏慕容又有一人领悟参合指绝技精髓所在,何愁复国大业不成！");
			command("chat* laugh");
			log_file("quest/canhezhi",sprintf("%-18s失败%s次后，成功从慕容博处领悟参合指绝技的精髓所在，福：%d，悟：%d。\n",
			me->name(1)+"("+capitalize(getuid(me))+")",
			chinese_number(me->query("quest/mr/canhezhi/fail")), 
			me->query("kar"), 
			me->query("int")), me);
			me->set("quest/mr/canhezhi/pass", 1);
			me->set("canhe/pass",1);
			me->set("quest/mr/canhezhi/exp", me->query("combat_exp"));
			me->set("title",HIG"慕容参合指传人"NOR);
			me->delete_temp("quest/mr/canhe");
			me->delete_temp("canwu_canhe");
			me->start_busy(1);
			return 1;		
		
		}
	    else {
		command("sigh " + me->query("id"));
		command("poor ");
		command("say 看来你还是未到明白其中奥妙所在的时候,明天再来吧!");
		me->add("quest/mr/canhezhi/fail", 1);
		me->set("quest/mr/canhezhi/time", time());
		log_file("quest/canhezhi",
			sprintf("%-18s想从慕容博处领悟参合指绝技的精髓失败，失败%s次。\n",
				me->name(1)+"("+capitalize(getuid(me))+")",
				chinese_number(me->query("quest/mr/canhezhi/fail")) 
			), me
		);
		 me->delete_temp("quest/mr/canhe");
		 me->delete_temp("canwu_canhe");
		 me->start_busy(1);
	  }
  }
   return 1;
}

int thinking_xingyi(object me)
{
  int i,j,total;
  if(!me) return 0;
	
  if(me->query_temp("canwu_xingyi")<(10+random(10)))
  { 
	  me->add_temp("canwu_xingyi",1);
      if(random(2)) tell_object(me,HIG"\n你认真回想着刚才慕容博所教给的斗转星移奥秘..\n"NOR);
             else tell_object(me,HIY"\n突然间，你似乎抓到了什么...\n"NOR);
	  tell_room(environment(me),HIC""+me->query("name")+"似乎在思索着什么，眉头紧皱。\n"NOR, ({}));
	  remove_call_out("thinking_xingyi");
	  call_out("thinking_xingyi",3+random(3), me);
	}
   else
   {  	 
      total = me->query("str") + me->query("con")+ me->query("dex")+ me->query("int");
      j = 25;
      if(me->query("m-card-vip")) j =  20;
      if(me->query("y-card-vip")) j =  17;
      if(me->query("buyvip"))     j =  15;
	  i= random(j);
 
	  if (random(me->query("kar"))>26 
			&& random(total) >=120 
			&& me->query("kar") <31
			&& i==1)
		{
			command("look " + me->query("id"));
			command("nod " + me->query("id"));
			command("chat* pat" + me->query("id"));
			command("say 好吧,我就将姑苏慕容斗转星移的终极奥妙告诉你吧。");
			command("chat 纵声长笑道：我姑苏慕容又有一人领悟斗转星移精髓所在,何愁复国大业不成！");
			command("chat* laugh");
			log_file("quest/xingyi",sprintf("%-18s失败%s次后，成功从慕容博处领悟斗转星移融合的精髓所在，福：%d，悟：%d。\n",
			me->name(1)+"("+capitalize(getuid(me))+")",
			chinese_number(me->query("quest/mr/dzxy/fail")), 
			me->query("kar"), 
			me->query("int")
		   ), me);
			me->set("quest/mr/dzxy/pass", 1);			
			me->set("quest/mr/dzxy/exp", me->query("combat_exp"));
		    me->set("title", HIC"斗"HIG"转"HIB"星"HIY"移"NOR);
			me->start_busy(1);
			me->delete_temp("canwu_xingyi");
			me->delete_temp("quest/mr/dzxy");
			return 1;	
		
		}
	    else {
		command("sigh " + me->query("id"));
		command("poor ");
		command("say 看来你还是未到明白这斗转星移的奥妙所在的时候,明天再来吧!");
		command("say 斗转星移乃是天下第一内功武技，你要有信心!");
		me->add("quest/mr/dzxy/fail", 1);
		me->set("quest/mr/dzxy/time", time());
		log_file("quest/xingyi",
			sprintf("%-18s想从慕容博处领悟斗转星移融合的精髓失败，失败%s次。\n",
				me->name(1)+"("+capitalize(getuid(me))+")",
				chinese_number(me->query("quest/mr/dzxy/fail")) 
			), me
		);
		 me->start_busy(1);
		 me->delete_temp("canwu_xingyi");
		 me->delete_temp("quest/mr/dzxy");
	  }
  }
   return 1;
}
