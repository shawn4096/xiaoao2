

//by sohu.c

int accept_object(object who, object ob)
{
  if(userp(ob)) return 0;
   //找到皇冠
   if(ob->query("id")=="zijin guan") {
	
		command("ah");
		command("chat* smile");
		command("say 大燕国皇冠终于重现江湖，看来真是天助我也，大燕国复兴有望了！");
		who->set_temp("quest/mr/dzxy/giveguan",1);
		who->set("quest/mr/dzxy/giveguan",1);
		//destruct(ob);		
	
	  return 1;
	 
   }
   //拿到世袭表
   if(ob->query("id")=="shixi biao") {
	  if (who->query_temp("quest/mr/dzxy/getshixibiao"))
	  {
		command("ah");
		command("chat* laugh");
		command("chat 大燕国世袭表终于重现江湖，看来真是天助我也，大燕国复兴有望了！");
		who->set_temp("quest/mr/dzxy/givebiao",1);
		who->set("quest/mr/dzxy/givebiao",1);
		destruct(ob);		
	  }
	  else {
		  command("say 你从哪儿找来这么一张破布来糊弄我？难道以为我人老糊涂好欺负么？");
		  command("consider");
	  }
	  return 1;
	 
   }
	//杀头颅和首级

   if(who->query_temp("quest/mr/canhe")) 
	if(ob->query("id") == "shouji" 
	   && ob->query("kill_by")
	   && ob->query("kill_by")==who
	   && ((ob->query("victim_id")=="zuo lengchan"&&who->query_temp("quest/mr/canhe/lengchan"))
	       ||(ob->query("victim_id")=="zhang wuji"&&who->query_temp("quest/mr/canhe/wuji"))
		   ||(ob->query("victim_id")=="miejue shitai"&&who->query_temp("quest/mr/canhe/miejue"))
		   ||(ob->query("victim_id")=="xuanci dashi"&&who->query_temp("quest/mr/canhe/xuanci"))
		   //||(ob->query("victim_id")=="mu renqing"&&who->query_temp("quest/mr/canhe/mu"))
		   ||(ob->query("victim_id")=="hong qigong"&&who->query_temp("quest/mr/canhe/hong"))
		   ||(ob->query("victim_id")=="kurong zhanglao")&&who->query_temp("quest/mr/canhe/kurong")))
   {
		
       
		  command("smile "+who->query("id"));	  
		  if(ob->query("victim_id")=="zuo lengchan")
		  {
			  command("whisper "+who->query("id")+" 不错，嵩山那个老杂毛没想到也有今天，你再去替我杀一个所谓名门正派的掌门。");
			  who->set_temp("quest/mr/canhe/klengchan",1);
		  }
		  if(ob->query("victim_id")=="zhang wuji")
		  {
			  command("whisper "+who->query("id")+" 不错，明教那个小家伙没想到也有今天，这里有个天大的秘密可以告诉你。");
			  who->set_temp("quest/mr/canhe/kwuji",1);

		  }
		  if(ob->query("victim_id")=="kurong zhanglao")
		 {
			  command("whisper "+who->query("id")+" 不错，大理那个死秃子没想到也有今天，这里有个天大的秘密可以告诉你。");
			  who->set_temp("quest/mr/canhe/kkurong",1);

		 }
		  if(ob->query("victim_id")=="hong qigong")
		  {
			  command("whisper "+who->query("id")+" 不错，丐帮那个老叫花没想到也有今天，你再去替我杀一个所谓名门正派的掌门。");
			  who->set_temp("quest/mr/canhe/khong",1);

		  }
		  if(ob->query("victim_id")=="miejue shitai")
		  {
			  command("whisper "+who->query("id")+" 不错，峨嵋那个老变态没想到也有今天，这里有个天大的秘密可以告诉你。");
		      who->set_temp("quest/mr/canhe/kmiejue",1);

		  }
		  if(ob->query("victim_id")=="xuanci dashi")
		 {
			  command("whisper "+who->query("id")+" 不错，少林那个老秃驴没想到也有今天，这里有个天大的秘密可以告诉你。");
			  who->set_temp("quest/mr/canhe/kxuanci",1);

		 }
		  command("addoil "+who->query("id"));
		  who->add_temp("quest/mr/canhe/give_shouji",1);
		  //不足6个继续杀
		  if (who->query_temp("quest/mr/canhe/give_shouji")<6)
		  {		  
				command("say 你已经杀了"+who->query_temp("quest/mr/canhe/give_shouji")+"位掌门了，不足六个请继续。\n");
				destruct(ob);
				 return 1;

		  }
		  else {
				command("nod "+who->query("id"));
				command("admire "+who->query("id"));
				command("say "+who->query("id")+"，你已经杀够了六个，真不愧是我慕容世家的核心弟子，现在可以继续向我请教了。\n");
				who->set("quest/mr/canhe/give_shouji",1);
				return 1;
			}
	 
   }else {	
			command("say 你是按照我说的杀人去杀的么？难道想浑水摸鱼？再来！\n");
			command("angry "+who->query("id"));
   }
   return 1;
}