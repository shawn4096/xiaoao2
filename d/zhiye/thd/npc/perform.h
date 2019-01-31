int ask_shenjian()
{
        object ob = this_player();
        int perform,time;
        
        if (ob->query("family/family_name") != "桃花岛") {
                command("say 是这幅对联的上联。");
                return 1;
        }
		if (!ob->query("quest/thd/dichuan"))
		{
			command("say 你虽然是我门中弟子，你为桃花岛做了什么先？\n");
			command("say 我东邪做事，向来是我行我素，非嫡传弟子不传？\n");
			return 1;
		}
        //perform = ob->query("thd/perform");
        if (ob->query("thd/wuji/luoying")) {
                command("say 你不是已经学会了吗？");
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say 要使用这样的绝招需要定力，你还是等长大些再说吧。");
                return 1;
        }
/*   // 落英掌的auto对女性适用；
        if (ob->query("gender") == "男性" && ob->query("age") < 40) {
                command("say 这招本来我也可以教授于你，不过你就不期望其它更好的途径吗？");
                return 1;
        }
*/
        if (ob->query_skill("luoying-zhang",1) < 200) {
                command("say 要使用这样的绝招需要深厚的掌力，你还是多练习练习“落英神剑掌”再说吧。");
                return 1;
        }
		time=time() - (int)ob->query("quest/shenjian/time");
       	if (ob->query("quest/shenjian/time") && time<86400)		
   		{
				command("say 小友还是去休息一下吧。");
				return 1;
		}
				 
		if (random(ob->query("kar"))<26)
		 {
                command("sigh "+ob->query("id"));
				command("say 要使用”桃花影落飞神剑“这样的绝招一定的毅力，你还是下次再说吧。\n");
				ob->set("quest/shenjian/time",time());
                return 1;
		 }
		  write("黄药师说道：你既然是桃花岛的弟子，我就教你一招“桃花影里飞神剑”吧！\n");
          write("黄药师细心地向你讲解这一招，你终于学会了。\n");
          //perform |= 2;
          ob->set("thd/wuji/luoying",1);
		  return 1;
  }

int ask_yuxiao()
{
        object ob = this_player();
        int perform,time;
        
        if (ob->query("family/family_name") != "桃花岛") {
                command("say 是这幅对联的下联。");
                return 1;
        }
        //perform = ob->query("thd/perform");
		if (!ob->query("quest/thd/dichuan"))
		{
			command("say 你虽然是我门中弟子，你为桃花岛做了什么先？\n");
			command("say 我东邪做事，向来是我行我素，非嫡传弟子不传？\n");
			return 1;
		}
        if (ob->query("thd/wuji/yuxiao")) {
                command("say 你不是已经学会了吗？");
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say 要使用这样的绝招需要定力，你还是等长大些再说吧。");
                return 1;
        }
/*
        if (ob->query("gender") == "男性" && ob->query("age") < 40) {
                command("say 这招本来我也可以教授于你，不过你就不期望其它更好的途径吗？");
                return 1;
        }
*/ 
	    if (ob->query_skill("yuxiao-jian",1) < 200) {
                command("say 要使用这样的绝招需要高深的剑法，你还是多练习练习“玉箫剑法”再说吧。");
                return 1;
        }
		time=time() - (int)ob->query("quest/yuxiao/time");
        if(ob->query("quest/yuxiao/time") && time<86400)		
   		{
				command("say 小友还是去休息一下吧。");
				return 1;
		}
	   
		if (random(ob->query("kar"))<27)
		 {
                command("sigh "+ob->query("id"));
				command("say 要使用”碧海潮生按玉箫“这样的绝招一定的毅力，你还是下次再说吧。\n");
				ob->set("quest/yuxiao/time",time());
                return 1;
		 }
		
        write("黄药师说道：你既然是桃花岛的弟子，我就教你一招“碧海潮生按玉箫”吧！\n");
        write("黄药师细心地向你讲解这一招，你终于学会了。\n");
       // perform |= 1;
        ob->set("thd/wuji/yuxiao",1);
        return 1;
}

int ask_kuangfeng()
{
        object ob = this_player();
        int perform,time;
        
        if (ob->query("family/family_name") != "桃花岛") {
                command("say " +  RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
                return 1;
        }
       // perform = ob->query("thd/perform");
        if (ob->query("thd/wuji/kuangfeng")) {
                command("say 你不是已经学会了吗？");
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say 要使用这样的绝招需要定力，你还是等长大些再说吧。");
                return 1;
        }
/*
        if (ob->query("gender") == "男性" && ob->query("age") < 40) {
                command("say 这招本来我也可以教授于你，不过你就不期望其它更好的途径吗？");
                return 1;
        }
*/
        if (ob->query_skill("luoying-zhang",1) < 100 && ob->query_skill("xuanfeng-tui",1) < 100) {
                command("say 要使用这样的绝招需要高深的掌法和腿法，你还是多练习练习“落英神剑掌”和“旋风扫叶腿”再说吧。");
                return 1;
        }
	/*	if( time()-ob->query("quest/kuangfeng/time")<86400)		
   		{
				command("say 你太勤快了，小友还是去休息一下吧。");
				return 1;
		}
	   
		 if (ob->query("kar")<20)
		 {
                command("sigh "+ob->query("id"));
				command("say 要使用”狂风绝技“这样的绝招一定的毅力，你还是下次再说吧。\n");
				ob->set("quest/kuangfeng/time",time());
                return 1;
		 }*/
        write("黄药师说道：你既然是桃花岛的弟子，我就教你一招我的看家功夫“狂风绝技”吧！\n");
        write("黄药师细心地向你讲解这一招，你终于学会了。\n");
        //perform |= 4;
        ob->set("thd/wuji/kuangfeng",1);
        return 1;
}

int ask_lingxi()
{
        object ob = this_player();
        int perform,time;
        
        if (ob->query("family/family_name") != "桃花岛") {
                command("say " +  RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
                return 1;
        }
        //perform = ob->query("thd/perform");
        if (ob->query("thd/wuji/lingxi")) {
                command("say 你不是已经学会了吗？");
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say 要使用这样的绝招需要定力，你还是等长大些再说吧。");
                return 1;
        }
		if (!ob->query("quest/thd/dichuan"))
		{
			command("say 你虽然是我门中弟子，你为桃花岛做了什么先？\n");
			command("say 我东邪做事，向来是我行我素，非嫡传弟子不传？\n");
			return 1;
		}
/*
        if (ob->query("gender") == "男性" && ob->query("age") < 40) {
                command("say 这招本来我也可以教授于你，不过你就不期望其它更好的途径吗？");
                return 1;
        }
*/
        if (ob->query_skill("tanzhi-shentong",1) < 200) {
                command("say 要使用这样的绝招需要很强的指劲，你还是多练习练习“弹指神通”再说吧。");
                return 1;
        }
		time=time() - (int)ob->query("quest/lingxi/time");
        if(ob->query("quest/lingxi/time") && time<86400)		
   		{
				command("say 小友还是去休息一下吧。");
				return 1;
		}
	   
		if (random(ob->query("kar"))<26)
		 {
                command("sigh "+ob->query("id"));
				command("say 要使用”灵犀一指“这样的绝招一定的毅力，你还是下次再说吧。\n");
				ob->set("quest/lingxi/time",time());
                return 1;
		 }
        write("黄药师说道：你既然是桃花岛的弟子，我就教你“弹指神通”的绝招“灵犀一指”吧！\n");
        write("黄药师细心地向你讲解这一招，你终于学会了。\n");
        //perform |= 8;
        ob->set("thd/wuji/lingxi",1);
        return 1;
}

int ask_huayu()
{
        object ob = this_player();
        int perform,time;
        
        if (ob->query("family/family_name") != "桃花岛") {
                command("say " +  RANK_D->query_respect(ob) + "与本派素无来往，不知此话从何谈起？");
                return 1;
        }
       // perform = ob->query("thd/perform");
        if (ob->query("thd/wuji/huayu")) {
                command("say 你不是已经学会了吗？");
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say 要使用这样的绝招需要定力，你还是等长大些再说吧。");
                return 1;
        }
		if (!ob->query("quest/thd/dichuan"))
		{
			command("say 你虽然是我门中弟子，你为桃花岛做了什么先？\n");
			command("say 我东邪做事，向来是我行我素，非嫡传弟子不传？\n");
			return 1;
		}
/*
        if (ob->query("gender") == "男性" && ob->query("age") < 40) {
                command("say 这招本来我也可以教授于你，不过你就不期望其它更好的途径吗？");
                return 1;
        }
*/
        if (ob->query_skill("tanzhi-shentong",1) < 120) {
                command("say 要使用这样的绝招需要很强的指劲，你还是多练习练习“弹指神通”再说吧。");
                return 1;
        }
		time=time() - ob->query("thd/huayu/time");
		if(ob->query("thd/huayu/time") && time<86400)		
   		{
				command("say 小友还是去休息一下吧。");
				return 1;
		}
	   
		if (random(ob->query("kar"))<15)
		 {
                command("sigh "+ob->query("id"));
				command("say 要使用”漫天花雨“这样的绝招一定的毅力，你还是下次再说吧。\n");
				ob->set("quest/huayu/time",time());
                return 1;
		 }
        write("黄药师说道：你既然是桃花岛的弟子，我就教你“弹指神通”的绝招“漫天花雨”吧！\n");
        write("黄药师细心地向你讲解这一招，你终于学会了。\n");
        //perform |= 16;
        ob->set("thd/wuji/huayu",1);
        return 1;
}
int ask_lhs()
{
        object ob = this_player();
        int perform,time;
        
        if (ob->query("family/family_name") != "桃花岛") {
                command("say 这是我们家传绝学，你想干什么？");
                return 1;
        }
       // perform = ob->query("thd/perform");
        if (ob->query("thd/wuji/lhs")) {
                command("say 你不是已经学会了吗？");
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say 要使用这样的绝招需要定力，你还是等长大些再说吧。");
                return 1;
        }
		if (!ob->query("quest/thd/dichuan"))
		{
			command("say 你虽然是我门中弟子，你为桃花岛做了什么先？\n");
			command("say 我东邪做事，向来是我行我素，非嫡传弟子不传？\n");
			return 1;
		}
        if (!ob->query("thd/finish")) {
                command("say 这招本来我也可以教授于你，不过你就不期望其它更好的途径吗？");
				command("say 我的九阴真经被这两个逆徒给偷走了，谁能帮我把这两个逆徒抓回来？ ");
                return 1;
        }

        if (ob->query_skill("lanhua-shou",1) < 200) {
                command("say 要使用这样的绝招需要高深的手法，你还是多练习练习“兰花手”再说吧。");
                return 1;
        }
		time=time() - (int)ob->query("quest/lhs/time");
		if(ob->query("quest/lhs/time") && time<86400)		
   		{
				command("say 小友还是去休息一下吧。");
				return 1;
		}
	   
		 if (random(ob->query("kar"))<27)
		 {
                command("sigh "+ob->query("id"));
				command("say 要使用”兰花拂穴“这样的绝招一定的毅力，你还是下次再说吧。\n");
				ob->set("quest/lhs/time",time());
                return 1;
		 }
        write("黄药师说道：你既然是桃花岛的弟子，我就教你一招“兰花拂穴”吧！\n");
        write("黄药师细心地向你讲解这一招，你终于学会了。\n");
       // perform |= 32;
        ob->set("thd/wuji/lhs",1);
	return 1;
}
//解密融合
int ask_ronghe()
{
        int i,j,time;
		object ob = this_player();
        
        
        if (ob->query("family/family_name") != "桃花岛"||ob->query("family/master_name")!="黄药师") {
                command("say 这是我们家传绝学，你想干什么？");
                return 1;
        }
		if (!ob->query("quest/thd/dichuan"))
		{
			command("say 你虽然是我门中弟子，你为桃花岛做了什么先？\n");
			command("say 我东邪做事，向来是我行我素，非嫡传弟子不传？\n");
			return 1;
		}
        if (ob->query("thdjj/ronghe")=="pass") {
                command("say 你不是已经学会了吗？");
				ob->set("title",HIM"桃花岛"+HIG"东邪传人"NOR);
				ob->set("mytitle/quest/thdrhtitle",HIM"桃花岛"+HIG"东邪传人"NOR);
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say 要使用这样的绝招需要定力，你还是等长大些再说吧。");
                return 1;
        }

//增肌title
        if (ob->query_skill("bihai-chaosheng",1) < 500) {
                command("say 要使用这样的绝招需要高深的内功，你还是多练习练习“碧海潮生功”再说吧。");
                return 1;
        }
		if (ob->query_skill("yuxiao-jian",1) < 500) {
                command("say 要使用这样的绝招需要高深的玉箫剑法，你还是多练习练习“碧海潮生功”再说吧。");
                return 1;
        }

		if (ob->query("int") < 40) {
                command("say 要使用这样的绝招需要很好的先天悟性（40），你还是等长大些再说吧。");
                return 1;
        }
         time=time() - (int)ob->query("thdjj/ronghe/time");
		if(ob->query("thdjj/ronghe/time") && time <86400)		
   		{
				command("say 你还是去休息一下吧。");
				return 1;
		}
	    //难度系数为1/15*10
	  //  j=random(20);
		write(HIC"黄药师说道：这九阴真经博大精深！\n"NOR);
		write(HIC"黄药师说道：你若好好领悟，这门绝技也可以彼此融合在一起！但能否领会贯通就看你的造化了。\n"NOR);

		j = 25;
		if(ob->query("m-card-vip")) j =  20;
		if(ob->query("y-card-vip")) j =  17;
		if(ob->query("buyvip"))     j =  15;
		j=random(j);
		i=random(ob->query("kar"));
		if (i>27 
			&& j<3
			&& random(ob->query("int"))>40)  
		 {

            write(HIY"黄药师说道：好徒儿，听仔细了！\n"NOR);
            write(HIC"黄药师细心地向你讲解这一招，你终于对桃花岛武学融会贯通！\n"NOR);
		    command("chat* haha "+ob->query("id"));
		    command("chat 桃花落英飞神剑，碧海涛声按玉箫。");
		    command("chat 得如此聪明伶俐的佳徒，我东邪一生不虚！自此后桃花岛东邪终于有传人出世了。");
		    command("chat 恭喜"+ob->query("name")+"深得我桃花岛真传！");
		    log_file("quest/thdfyjueji", sprintf("%8s(%8s) 失败%d次后，彻底领悟桃花岛终极绝技。随机数j取值：%d|随机富源i取值：%d|经验：%d。\n", ob->name(1),ob->query("id"), ob->query("thdjj/ronghe/fail"),j,i,ob->query("combat_exp")) );
	        ob->set("title",HIM"桃花岛"+HIG"东邪传人"NOR);
			ob->set("mytitle/quest/thdrhtitle",HIM"桃花岛"+HIG"东邪传人"NOR);
            ob->set("thdjj/ronghe","pass"); 
	        return 1;  
		 } else {     
		    command("sigh "+ob->query("id"));
			command("say 桃花岛的精髓就是要融合贯通，这是需要一定的毅力，你还是下次再说吧。\n");
			command("disapp "+ob->query("id"));
			ob->set("thdjj/ronghe/time",time());
			ob->add("thdjj/ronghe/fail",1);
			log_file("quest/tdhfyjueji", sprintf("%8s(%8s) 桃花岛融合绝技解密失败%d次。随机数j取值：%d|随机富源i取值：%d|经验：%d。\n", ob->name(1),ob->query("id"), ob->query("thdjj/ronghe/fail"),j,i,ob->query("combat_exp")) );
			return 1;
		 }
}	

int ask_lhssjj()
{
        int i,j,time;
		object ob = this_player();
        
        
        if (ob->query("family/family_name") != "桃花岛"||ob->query("family/master_name")!="黄药师") {
                command("say 这是我们家传绝学，你想干什么？");
                return 1;
        }
		if (!ob->query("quest/thd/dichuan"))
		{
			command("say 你虽然是我门中弟子，你为桃花岛做了什么先？\n");
			command("say 我东邪做事，向来是我行我素，非嫡传弟子不传？\n");
			return 1;
		}
        if (ob->query("quest/thd/lhs/lanhua/pass")) {
                command("say 你不是已经学会了吗？");
                ob->set("title",HIM"桃花岛"+HIC"兰花手传人"NOR);
				ob->set("mytitle/quest/thdlhstitle",HIM"桃花岛"+HIC"兰花手传人"NOR);
                return 1;
        }
        if (ob->query("age") < 14) {
                command("say 要使用这样的绝招需要定力，你还是等长大些再说吧。");
                return 1;
        }
		
//增肌title
        if (ob->query_skill("bihai-chaosheng",1) < 500) {
                command("say 要使用这样的绝招需要高深的内功，你还是多练习练习“碧海潮生功”再说吧。");
                return 1;
        }
		if (ob->query("str") < 40) {
                command("say 要使用这样的绝招需要很好的先天臂力（40），你还是等长大些再说吧。");
                return 1;
        }
        time=time() - (int)ob->query("quest/thd/lhs/lanhua/time");
		if(ob->query("quest/thd/lhs/lanhua/time") && time<86400)		
   		{
				command("say 你还是去休息一下吧。");
				return 1;
		}
	    //难度系数为1/15*10
	  //  j=random(20);
		write(HIC"黄药师说道：这兰花手乃是我桃花岛家传之绝技，非至亲之人不得传授！\n"NOR);
		write(HIC"黄药师说道：既然你如此有毅力，我就将此招式传授与你！能否领会贯通就看你的造化了。\n"NOR);

		j = 25;
		if(ob->query("m-card-vip")) j =  20;
		if(ob->query("y-card-vip")) j =  17;
		if(ob->query("buyvip"))     j =  15;
		j=random(j);
		i=random(ob->query("kar"));
		if (i>26 
			&& j<3
			&& random(ob->query("str"))>40)  
		 {

            write(HIR"黄药师细心地向你讲解这一招，你终于对桃花岛家传武学兰花三式融会贯通！\n"NOR);
		    command("chat* haha "+ob->query("id"));
		    command("chat 二十四桥明月夜，谁知兰花楚留香。");
		    command("chat 得如此聪明伶俐的佳徒，我东邪一生不虚！自此后桃花岛兰花手终于有传人出世了。");
		    command("chat 恭喜"+ob->query("name")+"深得我桃花岛兰花手绝技真传！");
		    log_file("quest/thdlhsjueji", sprintf("%8s(%8s) 失败%d次后，彻底领悟桃花岛兰花手终极绝技。随机数j取值：%d|随机富源i取值：%d|经验：%d。\n", ob->name(1),ob->query("id"), ob->query("quest/thd/lhs/lanhua/fail"),j,i,ob->query("combat_exp")) );
	        ob->set("title",HIM"桃花岛"+HIC"兰花手传人"NOR);
			ob->set("mytitle/quest/thdlhstitle",HIM"桃花岛"+HIC"兰花手传人"NOR);
            ob->set("quest/thd/lhs/lanhua/pass",1); 
	        return 1;  
		 } else {     
		    command("sigh "+ob->query("id"));
			command("say 桃花岛的兰花手是和先天臂力休戚相关。\n");

			command("say 桃花岛的兰花手乃是家传绝技，你一时间领悟不了，也有点难为你了，这是需要一定的毅力，你还是下次再说吧。\n");
			command("disapp "+ob->query("id"));
			ob->set("quest/thd/lhs/lanhua/time",time());
			ob->add("quest/thd/lhs/lanhua/fail",1);
			log_file("quest/thdlhsjueji", sprintf("%8s(%8s) 桃花岛兰花手绝技解密失败%d次。随机数j取值：%d|随机富源i取值：%d|经验：%d。\n", ob->name(1),ob->query("id"),ob->query("quest/thd/lhs/lanhua/fail"),j,i,ob->query("combat_exp")) );
	        return 1;
		 }
}	