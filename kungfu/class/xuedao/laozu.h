
#include <ansi.h>

//血刀

string ask_xuedao()
{
        object me=this_player() , weapon;
        int i;

        if ((string)me->query("family/family_name") != "血刀门"&&me->query("family/master_id")!="xudao laozu")
			return "血刀是我血刀门至宝，你我无缘无故，凭什么给你？\n";
	
        if(!me->query("quest/xd/dichuan")) return "你非血刀门嫡传弟子！\n";
		
		if (me->query("job_time/雪谷激战")<200) return "你的雪谷激战数不足200次！\n";
		
        weapon = present("xue dao", this_object());
                if(!objectp(weapon))    weapon = unew(BINGQI_D("xuedao"));
                if(!objectp(weapon))
                      return "血刀现在不在我手里。";  

                command("unwield xue dao");
                weapon->move(me);
                command("emote 给你一把血刀。");
                command("wield xinyue dao");
                me->set_temp("xs/xs_job",0);
  
        return "好，这把血刀你拿去吧，记着多杀几个人来祭刀啊！";
}

string ask_zijindao()
{
        object me=this_player() , weapon;

        if ((string)me->query("family/family_name") != "血刀门")
                return "你非我门中人，这把刀怎么能给你呢！";

        if ((int)me->query("xs_job") < 1000 )
                return "心动不如行动，雪山工作不租1000，拿点实际成绩来给我看嘛。\n";

        weapon = present("zijin dao", this_object());
        if(!objectp(weapon))    weapon = unew(BINGQI_D("zijin-dao"));
        if(!objectp(weapon))
                return "紫金刀现在不在我手里。";        

        command("unwield zijin dao");
        weapon->move(me);
        command("emote 给你一把紫金刀。");
        command("wield xinyue dao");

        return "好，这把紫金刀你拿去吧，记住不要给外人呀！";
}

void destroying(object obj)
{
	if (!obj) return;
	if (userp(obj))
		command("drop "+obj->parse_command_id_list()[0]);
	else
		destruct(obj);
}
string ask_diyun()
{
	object me,ob;
	me = this_player();
	ob = this_object();
	if(me->query_condition("killer"))
	{
	   command("fear "+me->query("id"));
	   return ""+RANK_D->query_respect(me) +"还是自己小心通缉吧！";
	}
	if(me->query(QUESTDIR1+"over" ))
	{
	   command("claw "+me->query("id"));
	   return "那个癞痢头狄小子怎么突然这么厉害了？";
	}
	if(!me->query(QUESTDIR1+"start" ))
	{
	   command("say");
	   return "被我打到雪谷深沟去了，估计早就饿死了。";
	}
	if(!me->query_temp(QUESTDIR1+"askbaoxiang" ))
	{
	   command("say");
	   command("claw "+me->query("id"));
	   return "哪个狄云？你找谁？";
	}
	if(me->query_temp(QUESTDIR1+"asklaozu"))
	{
	   command("en");
	   return "那个癞痢头我也到处找不到他，应该饿死了！";
	}
	command("smash");
	message_vision(HIY"$N神色自傲地看着$n。\n", ob,me);
	command("noshame");
	me->set_temp(QUESTDIR1+"asklaozu",1);
	return "他竟然和我作对，只能自讨苦吃，被我打到雪谷深沟去了，估计早就饿死了。";
}



string ask_xuedaojj()
{
	object me,ob;
	int i,j,k; 

	me = this_player();
	if (time()-me->query("quest/xd/xdj/xuedao/time")<86400)
	{
		//command("say 你");
		return "你来的太频繁了，武功最忌讳心气浮躁？？\n";
	}
	if (me->query("family/family_name")!="血刀门")
	{
		return "你不是血刀门弟子，来此消遣我么？\n";
	}

	if (!me->query("quest/xd/xdj/xuedao/start"))
	{
		return "你不努力去雪谷中为我杀那些掌门，不要来骚扰我！？\n";
	}
	if (me->query("quest/xd/xdj/xuedao/pass"))
	{
		me->set("title",HBRED+HIG"血刀大法传人"NOR);
		return "你已经解开血刀秘籍绝世武技了！？\n";
	}
	if (me->query("con")<40)
	{
		
		return "你先天根骨不够，学不了那血刀大法秘籍？？\n";
	}

	if (!me->query("quest/xd/dichuan"))
	{
		//command("say 你");
		return "血刀需要的是始终如一的忠诚弟子，你非嫡传，焉能传授你高级武功？？\n";
	}

		command("say 血刀门的根本全在于刀法上，但运使刀法的诀窍却在内功法门上。\n");
		command("say 这些法门俱都编写在《血刀秘籍》这本武功秘籍上。\n");

		command("say 你既然如此努力和勤奋，我就传授于你，看你能否领悟了\n");

	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	j=random(j);
	k=random(me->query("con"));
	if (i>26
	  && j<3
	  && k>40
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIG"\n$N劲气运转如意，手腕寸关穴忽然一痛，这奇经八脉的末梢经络豁然打通。”\n"NOR,me); 
		 message_vision(HIC"\n这些经脉都是先前$N所根本不知道的经脉，在老祖的指导下，你豁然发现人身竟然如此奇妙。”\n"NOR,me); 

         message_vision(HIY"\n$N福至心灵，运转真气在这些新经脉中周转不息。\n忍不住「哈哈哈」仰天大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N经过不断领悟，终于领悟了血刀门终极秘籍<<血刀经>>的真正奥秘！”\n"NOR,me); 
		 command("chat* laugh "+me->query("id"));
		 command("chat* thumb "+me->query("id"));
		 command("chat pat "+me->query("id"));
		 command("chat 恭喜"+me->query("id")+"修成血刀经终极秘籍！\n");
		 log_file("quest/xjdxuedao", sprintf("%s(%s) 血刀秘籍融会贯通成功！第%d次参悟，机缘巧合下，成功参悟血刀秘籍的奥秘，随机幸运值：%d,当前随机值：%d,当前悟性值：%d,当前经验：%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/xdj/xuedao/fail"),
		 i,
		 j,
		 k,
         me->query("combat_exp"),
		 ));

		 me->set("quest/xd/xdj/xuedao/time",time());
		 me->set("quest/xd/xdj/xuedao/pass",1);
		 me->set("title",HBRED+HIG"血刀大法传人"NOR);
		 me->set("mytitle/quest/xuddaotitle",HBRED+HIG"血刀大法传人"NOR);
		 return "佩服佩服！";
     }
	 else {
	     message_vision(HIG"\n$N神情沮丧，自言自语地说道：“看来这血刀秘籍真是不好解啊，继续努力吧。”\n"NOR,me); 
		 message_vision(HIY"\n参悟血刀秘籍绝技解密失败！\n"NOR,me); 
         log_file("quest/xdjxuedao", sprintf("%s(%s) 失败！参悟血刀秘籍第%d次失败，随机幸运值：%d,当前随机值：%d,当前悟性值：%d,当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/xdj/xuedao/fail",1),
		 i,
		 j,
		 k,
         me->query("combat_exp"),));        
		 me->add("quest/xd/xdj/xuedao/fail",1);
		 me->set("quest/xd/xdj/xuedao/time",time());
		 me->start_busy(2);
		 return "懒得理你，笨到姥姥家去了！\n";
   }
	
}

string ask_xuesha()
{
	object me,ob;
	int i,j,k; 

	me = this_player();
	if (time()-me->query("quest/xd/xdj/xuesha/time")<86400)
	{
		//command("say 你");
		return "你来的太频繁了，武功最忌讳心气浮躁？？\n";
	}
	if (me->query("family/family_name")!="血刀门")
	{
		return "你不是血刀门弟子，来此消遣我么？\n";
	}

	if (me->query("quest/xd/xdj/xuesha/pass"))
	{
	//	me->set("title",HBRED+HIG"血刀大法传人"NOR);
		return "你已经解开血刀经中血煞武技了！？\n";
	}
	if (me->query_skill("xuedao-jing",1)<350)
	{
		
		return "你血刀经等级不够350，学不了那血煞？？\n";
	}
	if (me->query("PKS")<5)
	{
		return "你连人都没杀过，去给我杀五个人练练胆子先，否则学不了那血煞，此门武功和你无缘？\n";

	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say 你");
		return "血刀需要的是始终如一的忠诚弟子，你非嫡传，焉能传授你高级武功？？\n";
	}
	command("say 血刀门的内功是比较奇特的武功，练到高深境界虽然不能摘花伤人，但也有其独特奥妙！\n");
	command("say 我曾在大雪谷一战，光吓也能把所谓的江南四大掌门吓死。\n");
	command("say 这其实需要一些胆识和历练的,你初练此功，虽然不能吓死对方，但让对方害怕还是能做到的!\n");
	command("say 你附耳过来，我跟你说些要诀，但最重要还是看你悟性。\n");
	command("say 记住你杀玩家越多，这门心法和口诀越厉害，如果没有杀过人，终身与此门武功无缘。\n");

	command("say 你既然如此努力和勤奋，我就传授于你，看你能否领悟了\n");

	i=random(me->query("kar"));
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	j=random(j);
	k=random(me->query("PKS"));
	if (i>25
	  && j<5
	  && k>20
	  && me->query("kar")<31)
 	{ 
        
         me->start_busy(3);
		 message_vision(HIG"\n$N忽然间福至心灵，血刀经运转如意，脸上顿时显现一股妖异的红色。”\n"NOR,me); 
		 message_vision(HIC"\n$N整个人都显得如此邪恶和恐怖！\n"NOR,me); 

         message_vision(HIY"\n\n忍不住「哈哈哈」仰天大笑几声，说道：“原来如此，原来如此。”\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N经过不断领悟，终于领悟了血刀经中血煞的真正奥秘！”\n"NOR,me); 
		 command("chat* smile "+me->query("id"));
		 command("chat* nip "+me->query("id"));
		 command("chat* pat "+me->query("id"));
		 log_file("quest/xjdxuesha", sprintf("%s(%s) 血刀经血煞秘技贯通成功！第%d次参悟，机缘巧合下，成功参悟血煞秘技的奥秘，随机幸运值：%d,当前随机值：%d,当前杀人值：%d,当前经验：%d,\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/xdj/xuesha/fail"),
		 i,
		 j,
		 k,
         me->query("combat_exp"),
		 ));

		 me->set("quest/xd/xdj/xuesha/time",time());
		 me->set("quest/xd/xdj/xuesha/pass",1);
		// me->set("title",HBRED+HIG"血刀大法传人"NOR);
		 return "小子，本事不错啊，为师的唬人招式你都学会了！\n";
     }
	 else {
	     message_vision(HIG"\n$N神情沮丧，自言自语地说道：“看来这血煞秘技真是不好解啊，继续努力吧。”\n"NOR,me); 
		 message_vision(HIY"\n参悟血煞秘技解密失败！\n"NOR,me); 
         log_file("quest/xdjxuedao", sprintf("%s(%s) 失败！参悟血煞秘技第%d次失败，随机幸运值：%d,当前随机值：%d,当前杀人值：%d，当前经验：%d。\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/xd/xdj/xuesha/fail",1),
		 i,
		 j,
		 k,
         me->query("combat_exp"),));        
		 me->add("quest/xd/xdj/xuesha/fail",1);
		 me->set("quest/xd/xdj/xuesha/time",time());
		 me->start_busy(2);
		 return "这都不会，以后别说你是我的弟子！\n";
   }
	
}
