

//by sohu.c

int accept_object(object who, object ob)
{
  if(userp(ob)) return 0;
   //�ҵ��ʹ�
   if(ob->query("id")=="zijin guan") {
	
		command("ah");
		command("chat* smile");
		command("say ������ʹ��������ֽ�������������������Ҳ����������������ˣ�");
		who->set_temp("quest/mr/dzxy/giveguan",1);
		who->set("quest/mr/dzxy/giveguan",1);
		//destruct(ob);		
	
	  return 1;
	 
   }
   //�õ���Ϯ��
   if(ob->query("id")=="shixi biao") {
	  if (who->query_temp("quest/mr/dzxy/getshixibiao"))
	  {
		command("ah");
		command("chat* laugh");
		command("chat �������Ϯ���������ֽ�������������������Ҳ����������������ˣ�");
		who->set_temp("quest/mr/dzxy/givebiao",1);
		who->set("quest/mr/dzxy/givebiao",1);
		destruct(ob);		
	  }
	  else {
		  command("say ����Ķ�������ôһ���Ʋ�����Ū�ң��ѵ���Ϊ�����Ϻ�Ϳ���۸�ô��");
		  command("consider");
	  }
	  return 1;
	 
   }
	//ɱͷ­���׼�

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
			  command("whisper "+who->query("id")+" ������ɽ�Ǹ�����ëû�뵽Ҳ�н��죬����ȥ����ɱһ����ν�������ɵ����š�");
			  who->set_temp("quest/mr/canhe/klengchan",1);
		  }
		  if(ob->query("victim_id")=="zhang wuji")
		  {
			  command("whisper "+who->query("id")+" ���������Ǹ�С�һ�û�뵽Ҳ�н��죬�����и��������ܿ��Ը����㡣");
			  who->set_temp("quest/mr/canhe/kwuji",1);

		  }
		  if(ob->query("victim_id")=="kurong zhanglao")
		 {
			  command("whisper "+who->query("id")+" ���������Ǹ���ͺ��û�뵽Ҳ�н��죬�����и��������ܿ��Ը����㡣");
			  who->set_temp("quest/mr/canhe/kkurong",1);

		 }
		  if(ob->query("victim_id")=="hong qigong")
		  {
			  command("whisper "+who->query("id")+" ����ؤ���Ǹ��Ͻл�û�뵽Ҳ�н��죬����ȥ����ɱһ����ν�������ɵ����š�");
			  who->set_temp("quest/mr/canhe/khong",1);

		  }
		  if(ob->query("victim_id")=="miejue shitai")
		  {
			  command("whisper "+who->query("id")+" ���������Ǹ��ϱ�̬û�뵽Ҳ�н��죬�����и��������ܿ��Ը����㡣");
		      who->set_temp("quest/mr/canhe/kmiejue",1);

		  }
		  if(ob->query("victim_id")=="xuanci dashi")
		 {
			  command("whisper "+who->query("id")+" ���������Ǹ���ͺ¿û�뵽Ҳ�н��죬�����и��������ܿ��Ը����㡣");
			  who->set_temp("quest/mr/canhe/kxuanci",1);

		 }
		  command("addoil "+who->query("id"));
		  who->add_temp("quest/mr/canhe/give_shouji",1);
		  //����6������ɱ
		  if (who->query_temp("quest/mr/canhe/give_shouji")<6)
		  {		  
				command("say ���Ѿ�ɱ��"+who->query_temp("quest/mr/canhe/give_shouji")+"λ�����ˣ����������������\n");
				destruct(ob);
				 return 1;

		  }
		  else {
				command("nod "+who->query("id"));
				command("admire "+who->query("id"));
				command("say "+who->query("id")+"�����Ѿ�ɱ�����������治������Ľ�����ҵĺ��ĵ��ӣ����ڿ��Լ�����������ˡ�\n");
				who->set("quest/mr/canhe/give_shouji",1);
				return 1;
			}
	 
   }else {	
			command("say ���ǰ�����˵��ɱ��ȥɱ��ô���ѵ����ˮ���㣿������\n");
			command("angry "+who->query("id"));
   }
   return 1;
}