// zuo.h
// Lklv creat at 2001.10.19

string do_cancel()
{
	object me;
	int exp, i;

	me = this_player();
	exp = me->query("combat_exp");

	if(!me->query_temp("quest") || me->query_temp("quest/family") != "嵩山派")
		return "你没有领任务，和我嚷嚷什么？";

	me->add("combat_exp",-(20+random(50)));
	if(exp > 500000){
	      me->add("combat_exp",-(30+random(40)));
	}
	i = 40 - me->query_condition("job_busy");
	if ( i >= 9 )
		me->apply_condition("job_busy", 1);
	else
		me->apply_condition("job_busy", 9 - i);
	me->delete_temp("songshan_job");
	me->delete_temp("quest");
	return "既然你干不了也没关系，再去刻苦练功吧，以后再来为我们的并派大计出力！";
}

string do_ask()
{
	object me, ob;
	string type, t;
	mapping quest;

	me = this_player();
	ob = this_object();

	if(ob->is_busy()) return "我正忙着呢，你等等。";
	

	if(me->query("combat_exp") > 4000000)
		return "你的功夫这么高，不用你跑腿了。";

	if( me->query("combat_exp") < 100000
	 || me->query("shen") > -1000)
		return RANK_D->query_respect(ob)+"我看你手脚散漫，行动迟缓，再加满脸稚气。怎能放心让你去办大事呢？";

	if( me->query("job_name") == "嵩山并派")
		return "嗯，我现在正在思考并派大计，你别打扰。";

	if( me->query_temp("quest/id")&& me->query_temp("songshan_job"))
		return "不是让你去"+HIY+me->query_temp("quest/place")+CYN+me->query_temp("quest/type")+HIG+me->query_temp("quest/name")+CYN+"了吗，怎么还在这里？";

	if( me->query_condition("job_busy"))
		return "嗯，我现在忙，你别打扰。";

	type = random(2)?"请":"杀";

	// get a random npc from TASK_D.
	if(!mapp(quest= TASK_D->get_quest(me, 0, type, "嵩山派")))
		return "嗯，我现在正在思考并派大计，你别打扰。";

	me->set_temp("quest", quest);
	me->apply_condition("job_busy", 40);
	t = TASK_D->get_time(quest["time"]);   // get time limit.

	me->set_temp("songshan_job", 1);
	if(type == "杀"){
		command("grin");
		command("say 你听好了，有弟子回报"HIR+quest["name"]+CYN"这人对我五岳并派之举深表不满，那么……");
		return "嘿嘿，他在"HIY+quest["place"]+CYN"一带，你去将他杀了，务必在"+t+CYN"之前带着他的尸体赶回来。\n";
	}
	else{
		command("nod");
		command("say 对了，"HIG+quest["name"]+CYN"和我交情不错，如得他相助，五岳并派之事简直易如反掌。");
		return "你就代表我去"HIY+quest["place"]+CYN"邀请他，务必在"+t+CYN"之前赶回来。";
	}
}

int accept_object(object who, object ob,object me)
{
       int type,count,exp,pot;
       me=this_object();

       // check job.

       if( who->query_temp("quest/family") != "嵩山派")
		    return 0;

       type = TASK_D->is_target(ob, who);
       switch (type){
	    case 0: command("say 你拿个"+ob->name()+"给我干嘛？");
		    return 0;
	    case -1:command("say 耶？让请人你不去，倒杀人丢脸去了，滚开！");
		    return 0;
	    case -2:command("say 嘿嘿，谁让你去乱杀人了？简直是给我嵩山派抹黑！");
		    who->apply_condition("job_busy", 9);
		    return 0;
	    case -3:command("say 嗯，这么久才办完，你干什么去了？给我滚一边去！");
		    who->apply_condition("job_busy", 9);
		    return 0;
	    case -4:command("say 哦，这是个同名同性的人，算他倒霉吧！");
		    return 0;
	    default:command("haha");
		    command("say 好！好！你办事不错，是块好料子。");
		    message_vision("\n$N给$n讲解一些武学上的疑难，$n若有所思地点着头。\n",me, who);
		    // give rewards.
		    TASK_D->give_reward(who, who->query_temp("quest"), -1, ABS(me->query("job_time/嵩山")/100) ,this_object(),"嵩山" );

	//who->add("job_time/嵩山", 1);
	//GIFT_D->check_count(who,this_object(),"嵩山");
	
	who->delete_temp("songshan_job");
	count = who->query("job_time/嵩山");
	if (count<1) count=1;
	pot= who->query_temp("quest/pot_reward");
	exp= who->query_temp("quest/exp_reward");
	who->delete_temp("quest");
	if (random(who->query("job_time/嵩山"))>800 && random(who->query("kar"))>25 && !who->query("quest/ss/dichuan")&& who->query("family/family_name")=="嵩山派")
	{
				message_vision("$N在"+who->query("job_time/嵩山")+"次嵩山请人任务中获得左冷禅的认可！把你当做核心弟子看待。\n",who);
				who->set("title",YEL"五岳盟主嫡传弟子"NOR);
				who->set("quest/ss/dichuan",1);
	}
    if (me->query("quest/ss/dichuan"))
	{
				me->set("title",YEL"五岳盟主嫡传弟子"NOR);
	}
	log_file("job/songshan",sprintf("%8s%-10s第%4d次嵩山杀人任务获得%3d点经验，%2d点潜能，经验：%d\n",
	who->name(),"("+who->query("id")+")",count,exp,pot,who->query("combat_exp")),who);
	who->set("job_name", "嵩山并派");
	who->clear_condition("job_busy");
	call_out("destroy", 1, ob);
	return 1;
	    }
      return 1;
}

void destroy(object ob)
{
	destruct(ob);
}
//寒冰地点--这个
string ask_hb()
{
	object me = this_player();

	if (!me->query_temp("hbzq/askzuo"))
		return "什么这个那个的呀？！";
	if (random(2)==1)
		return "这个嘛，具体地点我也不是很清楚！";
	me->set_temp("ss/hb_1",1);
		return "大概地点就在一个峡谷附近，具体地点我实在想不起来了。\n不过我记得很清楚，当时邓师弟以新学的嵩阳鞭法和我比武，我失手把他的紫阳鞭打落山崖！\n";
}

void reset()
{
	object ob;

	if (clonep() && (ob = unew(BINGQI_D("sword/guanri-jian")))) {
		ob->move(this_object());
		command("wield guanri qin");
	}
}

string ask_grj()
{
	object me=this_player() , weapon;

	if (me->query("family/master_name") != "左冷禅")
		return 0;
	weapon = present("guanri jian", this_object());
	if (!me->query("quest/ss/dichuan"))
	{
		command("say 你不是我的嫡传弟子，为什么要给你？");
		return "哼！";
	}
	if (!objectp(weapon))
		return "观日剑已经被你师兄拿走了,现在不在我手里。";
	command("unwield guanri jian");
	command("give guanri jian to " + me->query("id"));
	return "这观日剑就给你了，你可要妥善保管好！";
}

string ask_times()
{
	object me = this_player();
	int i;

	if(!intp(i = me->query("job_time/嵩山")))
		return "你这个小混蛋，你是请过人，还是杀过人？想骗我？";
	message_vision("$N对着$n想了想，说道，你目前已记功" + chinese_number(i) + "次。\n", this_object(),me);
	return "我嵩山向来赏罚分明，继续努力吧！";
}

int do_hssb()
{
	object me = this_player();
	if (me->query("family/family_name")!="嵩山派")
	  return notify_fail("你不是我嵩山派弟子，来打听这个干吗？");
	if (!me->query("quest/ss/dichuan"))
	  return notify_fail("你不是我嵩山派亲传核心弟子，来打听这个干吗？");
	
	if (me->query("quest/ssjf/jueji/pass"))
	   return notify_fail("你已经尽得嵩山剑法奥秘真传，难道没事来消遣本盟主么？？");
	if( time()-me->query("quest/ss/ssjf/jueji/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到这里吧，明天吧。");
		return 1;
	}
	if(me->query_skill("songshan-jian",1)<450)
	{
		command("look "+me->query("id"));
		command("say 以你当前的剑法没有大飞，恐怕还是难以领悟，还是抓紧去练功去吧。\n");
		return 1;
	}
	if(me->query("int")<40)
	{
		command("look "+me->query("id"));
		command("say 以你当前的资质情况，恐怕还是难以领悟此项绝技，等你先天悟性40后再来找我。\n");
		return 1;
	}
	message_vision(HIC"$N对着$n想了想，说道，“想当初，五岳剑派会盟，魔教十大长老战华山，那一战\n"+
		"极为惨烈，魔教十长老最终命丧华山，下落不明，但五岳剑派好手也损失殆尽。\n"+
		"我大嵩山也是在此战中无数高手陨落，使得我派绝技至今仍然残缺不全，很多招式\n"+
		"即便是为师也难以明了，你若有心，就去华山石壁看看是否有此机缘。”\n"NOR, me);
	me->set_temp("hssb/juejiasked",1);
	return 1;
}

int do_jueji() 
{
	object me = this_player();
	
	if(this_object()->is_fighting()) return 0;
	if(me->query("family/family_name")!="嵩山派")
	{
		command("heng "+me->query_id());
		command("say 你和我门派有什么关系，赶紧给我滚！");
		return 1;
	}
	
	if(me->is_busy())
	{
		command("heng "+me->query_id());
		command("say 你如此毛躁急促，如何能领悟这门绝技真意？");
		return 1;
	}
	if(me->query("quest/ss/ssjf/jueji/pass"))
	{
		command("heng "+me->query_id());
		command("say 你已经将嵩山剑法融会贯通，来消遣本盟主么？");
		return 1;
	}
	if(me->query("quest/ss/ssjf/jueji/fail")>=3 && me->query("registered")<3)
	{
		command("shrug "+me->query("id"));
		command("say 已经多次传授，你怎么都还没有领悟,真够笨的！");
		command("puke "+me->query("id"));
		return 1;
	}
	
	if (!me->query("quest/ss/ssjf/jueji/hssb"))
	{
	   command("say 不是让你去华山石壁观摩学习本门剑法的奥秘么，你为何偷懒没有好好研究一番？\n");
	   return 1;
	}
	message_vision(HIC"$N向$n请教有关嵩山剑法绝技的终极奥妙。\n"NOR, me, this_object());
	
	command("look "+me->query("id"));	
	
	if( time()-me->query("quest/ss/ssjf/jueji/time")<86400)
	{
		command("shake "+me->query("id"));
		command("say 今天先教到这里吧，明天吧。");
		return 1;
	}
	if(me->query_skill("songshan-jian",1)<450)
	{
		command("look "+me->query("id"));
		command("say 以你当前的剑法没有大飞，恐怕还是难以领悟，还是抓紧去练功去吧。\n");
		return 1;
	}
    
	me->set("quest/ss/ssjf/jueji/time",time());
	me->set("quest/ss/ssjf/jueji/combat_exp",me->query("combat_exp")); 
	
	command("sigh "+me->query("id"));
	command("think ");
	command("consider ");
	command("say 原来是这样子的结局！\n");
	command("say 嵩山剑法自上代而流失太多，看在你如此勤奋的份上就将我所领悟的嵩山剑法奥秘说给你听听，看你有没有这个悟性了。");
    command("say 徒儿啊，这招绝技乃是为师多年心血所得，你学习后一定要用此绝技把那些伪君子和魔教教徒都给我全杀了。");
	command("whisper "+me->query("id"));
	
	command("smile "+me->query("id"));
	me->start_busy(999);
	remove_call_out("think_ssjf");
	call_out("think_ssjf",1,me);
	return 1;
}

int think_ssjf(object me)
{
	//object me=this_player();
    int i,j;
	//i=random(20);
	j = 20;
    if(me->query("m-card-vip")) j =  18;
    if(me->query("y-card-vip")) j =  15;
    if(me->query("buyvip"))     j =  10;
	i=random(j);

	if(me->query_temp("canwu_ssjfjj")<(10+random(5)))
    {  
	  me->add_temp("canwu_ssjfjj",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你仔细聆听师傅的讲述，将师傅所传授的招式彼此印证，只觉得耳目一新...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n忽然，你似乎抓住了一些明悟。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你陷入馄饨状态，大脑一片空明，似乎要抓住那个线索了！..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，甚是无聊，神情抑郁，似乎有些累了.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎遇到瓶颈了..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n你思维漂浮在空中，宛如婴儿沐浴.神清气爽.\n"NOR);
			break;
		default:tell_object(me,YEL"\n你叹了一口气，精神总是不能有效集中.\n"NOR);
			break;
	  }     

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  //remove_call_out("think_ssjf");
	  call_out("think_ssjf",3+random(3), me);
	  return 1;

   } 
	else if( i<4
		&& random(me->query("int"))>40
		&& random(me->query("kar"))>25)
	{
		tell_object(me,HIG"\n你按照左盟主的指点，结合在华山石壁所得，对嵩山剑的终极奥妙似乎有些心得。\n"NOR);
		tell_object(me,HIC"\n你把左盟主所传授的招式从头开始演练，一路演练下来，潇洒自如。越练越是纯熟。\n"NOR);
        tell_object(me,HIR"\n忽然间，你灵光一闪，以前无论如何也想不明白的问题忽然间豁然贯通，忍不住哈哈大笑.\n"NOR);		
		
		command("look "+me->query("id"));
		command("chat "+"哈哈哈哈！！我大嵩山又崛起了一名杰出的弟子，统一武林看来又多了些把握！");
		command("chat*haha "+me->query("id"));
        command("chat*pat "+me->query("id"));
		command("chat "+"乖徒儿，好好干，以后这盟主之位就是你的了。");
		
		me->set("quest/ss/ssjf/jueji/pass",1);
		me->set("title",HIC"嵩山派"+HIY"嵩山剑法传人"NOR);
		me->set("quest/ss/ssjf/jueji/time",time());
		log_file("quest/ssjfjj", sprintf("成功！%8s(%8s) 失败%d次后，彻底领悟嵩山剑的绝技。i取值：%d|经验：%d。\n", me->name(1),me->query("id"), me->query("quest/ss/ssjf/jueji/fail"),i,me->query("combat_exp")) );
		me->delete_temp("canwu_ssjfjj");
		me->delete_temp("hssb");

	}
	else
	{
		command("heng "+me->query("id"));
		tell_object(me,HIY"你听了左盟主的指点，虽然看见了嵩山剑法的厉害招式，可是对嵩山剑法的真正奥妙全然不得要领。\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		log_file("quest/ssjfjj", sprintf("失败，%8s(%8s) 嵩山绝技解密失败%d次。i取值：%d|经验：%d。\n", me->name(1),me->query("id"),me->query("quest/ss/ssjf/jueji/fail"),i,me->query("combat_exp")) );
		me->set("quest/ss/ssjf/jueji/time",time());
		me->add("quest/ss/ssjf/jueji/fail",1);
		me->delete_temp("canwu_ssjfjj");
		me->delete_temp("hssb");
	}
	me->start_busy(1);
	return 1;

}

int do_chaozong()
{	
	object me = this_player();
	//int i=3+random(3);
	me->start_busy(2);
	if (me->query("family/family_name") != "嵩山派" ){
		command("say 你不是我嵩山派中人士来此作甚？\n");
		return 1;
	}
	if (me->query_skill("songshan-jian",1) < 300){
		command("say 你嵩山剑不足300，来此作甚？\n");
		return 1;
	}
	if (!me->query("quest/ss/dichuan")){
		command("say 你非我派核心弟子，还是去好好把为我五岳并派大计去多请几个高手来吧？\n");
		return 1;
	}
	if (me->query_skill("hanbing-zhenqi",1) < 300){
		command("say 你寒冰真气不足300，来此作甚？\n");
		return 1;
	}
	/*
	if (me->is_busy())
	{
		command("say 你太忙了？\n");
		return 1;
	}
	*/
	if (me->query("family/master_id")!="zuo lengchan"||me->query("family/master_name")!="左冷禅")
	{
		command("say 我记得没有这个弟子啊？\n");
		return 1;
	}
    if (me->query("quest/ss/ssj/chaozong/pass")){
		command("say 你已经开了这个谜题,还来此聒噪作甚？？\n");        	
		return 1;				
	}
	
	if (time()-me->query("quest/ss/ssj/chaozong/time")<86400){
		command("say 你也太勤快点了耶？？\n");        	
		return 1;				
	}
	command("say 嵩山剑法是我五岳剑派精华，我中岳嵩山正好是五岳之中，乃天然的独尊优势。\n");
	command("say 虽然我大嵩山剑法独领风骚，但并不是说我们偏可以到处张扬。\n");
	command("say 这招万岳朝宗就是在谦和中展示我大嵩山的傲气，让万岳来朝。\n\n\n");
			//me->set_temp("chaozong/askzuo",1);
			
	command("say 今天我正好心情高兴，乖徒儿，来来！我就把这万岳朝宗的精要说与你听听。你要听好了！\n");
	message_vision(HIR"\n\n$N恭恭敬敬地向师傅请教关于万岳朝宗的绝技。\n"NOR,me);
	me->start_busy(999);
	remove_call_out("thinking");
	call_out("thinking",1,me);
			//	me->delete_temp("chaozong/ask",1);
	return 1;

}

int thinking(object me)
{
  int i,j,k; 
  if(!me) return 0;
  i=random(me->query("kar"));
  //j=random(10);

  k = 20;
  if(me->query("m-card-vip")) k =  18;
  if(me->query("y-card-vip")) k =  15;
  if(me->query("buyvip"))     k =  10;
  j=random(k);

  me->set("quest/ss/ssj/chaozong/time",time());
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) 参悟万岳朝宗时，KAR异常，当前经验：%d。年龄：%d。kar:%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_chaozong")<(10+random(5)))
   {  
	  me->add_temp("canwu_chaozong",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n你仔细聆听师傅的讲述，将师傅所传授的心法彼此印证，只觉得耳目一新...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n忽然，你似乎抓住了一些明悟。\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n你陷入馄饨状态，大脑一片空明，似乎要抓住那个线索了！..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n你枯坐哪儿，甚是无聊，神情抑郁，似乎有些累了.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n你自言自语，神情疲倦之际，似乎遇到瓶颈了..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n你思维漂浮在空中，宛如婴儿沐浴.神清气爽.\n"NOR);
			break;
		default:tell_object(me,YEL"\n你叹了一口气，精神总是不能有效集中.\n"NOR);
			break;

	  }
      

	  tell_room(environment(me),HIC""+me->query("name")+"面色平和，浑然忘我，似乎在思索着什么...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (i>=26
			&& j<5
			&& me->query("kar")<31)
 	{         
         me->start_busy(3);     
         message_vision(HIY"\n$N「哈哈哈」大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HIY"\n$N经过不断领悟，终于领悟了万岳朝宗的奥秘，嵩山剑法豁然贯通！”\n"NOR,me); 
         log_file("quest/ssjchaozong", sprintf("%s(%s) 成功！第%d次参悟，机缘巧合下，成功参悟万岳朝宗的奥秘，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/ss/ssj/chaozong/fail"),
		 i,
		 j,
         me->query("combat_exp")));
		 me->start_busy(1);
		 me->set("quest/ss/ssj/chaozong/time",time());
		 me->set("quest/ss/ssj/chaozong/pass",1);
		 me->delete_temp("canwu_chaozong");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N长叹一生，自言自语地说道：“看来又是一无所获啊。”\n"NOR,me); 
		 message_vision(HIY"\n参悟万岳朝宗绝技解密失败！\n"NOR,me); 
         log_file("quest/ssjchaozong", sprintf("%s(%s) 失败！第%d次失败参悟万岳朝宗，当前幸运值：%d,当前随机值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/ss/ssj/chaozong/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/ss/ssj/chaozong/fail",1);
		 me->set("quest/ss/ssj/chaozong/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_chaozong");
		 return 1;
   }

}